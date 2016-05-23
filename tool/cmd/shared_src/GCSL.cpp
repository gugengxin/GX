#include "GCSL.h"
#include "GCTextEditor.h"
#include <QFile>
#include <QTextCodec>

/*
gxsl(GX Shading Language) 将被翻译成 glsl或hlsl




例子：
#def MASK 0
#def COLOR_MASK 1

vs {
    layout {
        high vec4 pos:POSITION;
        medi vec2 tex:TEXCOORD[0];
        #if MASK
        medi vec2 texMask:TEXCOORD[1];
        #end
        lowp vec4 color:COLOR[0];
        #if COLOR_MASK
        lowp vec4 colorMask:COLOR[1];
        #end
    }
    buffer[0] {
        high mat4 mvpMatrix;
    }
    bridge {
        medi vec2 v_tex;
        #if MASK
        medi vec2 v_tex_mask;
        #end
        lowp vec4 v_color;
        #if COLOR_MASK
        lowp vec4 v_color_mask;
        #end
    }

    main {
        gx_Position=mvpMatrix*pos;
        v_tex=tex;
        #if MASK
        v_tex_mask=texMask;
        #end
        v_color=color;
        #if COLOR_MASK
        v_color_mask=colorMask;
        #end
    }
}

fp {
    buffer[0] {
        lowp vec4 colorMul;
    }
    texture {
        lowp tex2d[0] tex;
        lowp tex2d[1] texMask;
    }
    main {
        gx_FragColor=tex[v_tex];
        #if MASK
        gx_FragColor+=texMask[v_tex_mask];
        #end
        gx_FragColor+=v_color;
        #if COLOR_MASK
        gx_FragColor+=v_color_mask;
        #end
        gx_FragColor*=colorMul;
    }
}
//*/


GCSL::GCSL(QObject *parent) : QObject(parent)
{
    m_Writer=NULL;
}


GCSL::~GCSL()
{

}

bool GCSL::compile(const QString &filePath, const QString &guessEncode, GCSLError *errOut)
{
    bool res=false;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray data=file.readAll();

        if(data.size()>=GCTextEditor::BOM8Bytes && memcmp(GCTextEditor::BOM8,data.data(),GCTextEditor::BOM8Bytes)==0) {
            QTextCodec* codec=QTextCodec::codecForName("UTF-8");
            if(codec) {
                m_Text=codec->toUnicode(data.data()+GCTextEditor::BOM8Bytes,data.size()-GCTextEditor::BOM8Bytes);
                res=true;
            }
        }
        else {
            QTextCodec* codec=QTextCodec::codecForName(guessEncode.toUtf8());
            if(codec) {
                m_Text=codec->toUnicode(data);
                res=true;
            }
        }
    }
    if(!res) {
        if(errOut) {
            errOut->setCode(GCSLError::C_ReadFile);
        }
        return false;
    }

    initWords();

    if(!translateToTokens(errOut)) {
        return false;
    }

    GCSLTokenReader reader(m_Tokens);
    m_Writer=new GCSLWRoot(this);
    return m_Writer->compile(reader,errOut);
}

void GCSL::clean()
{
    delete m_Writer;
    m_Writer=NULL;
    for(int i=0;i<m_Tokens.length();i++) {
        delete m_Tokens[i];
    }
    m_Tokens.clear();
    for(QMap<QString,GCSLWord*>::Iterator it=m_WordMap.begin();it!=m_WordMap.end();it++) {
        delete it.value();
    }
    m_WordMap.clear();
    m_Text.clear();
}

void GCSL::initWords()
{
#define  M_WORD_MAP_ADD(t,s) m_WordMap.insert(QString(s),new GCSLWord(GCSLToken::t,s,this))

    M_WORD_MAP_ADD(T_Semicolon     , ";"           );
    M_WORD_MAP_ADD(T_S_Brackets_L  , "("           );
    M_WORD_MAP_ADD(T_S_Brackets_R  , ")"           );
    M_WORD_MAP_ADD(T_M_Brackets_L  , "["           );
    M_WORD_MAP_ADD(T_M_Brackets_R  , "]"           );
    M_WORD_MAP_ADD(T_B_Brackets_L  , "{"           );
    M_WORD_MAP_ADD(T_B_Brackets_R  , "}"           );
    M_WORD_MAP_ADD(T_Comma         , ","           );
    M_WORD_MAP_ADD(T_Equal         , "="           );
    M_WORD_MAP_ADD(T_EqualEqual    , "=="          );
    M_WORD_MAP_ADD(T_Plus          , "+"           );
    M_WORD_MAP_ADD(T_PlusPlus      , "++"          );
    M_WORD_MAP_ADD(T_PlusEqual     , "+="          );
    M_WORD_MAP_ADD(T_Minus         , "-"           );
    M_WORD_MAP_ADD(T_MinusMinus    , "--"          );
    M_WORD_MAP_ADD(T_MinusEqual    , "-="          );
    M_WORD_MAP_ADD(T_Multiply      , "*"           );
    M_WORD_MAP_ADD(T_MultiplyEqual , "*="          );
    M_WORD_MAP_ADD(T_Div           , "/"           );
    M_WORD_MAP_ADD(T_DivEqual      , "/="          );
    M_WORD_MAP_ADD(T_Period        , "."           );
    M_WORD_MAP_ADD(T_And           , "&&"          );
    M_WORD_MAP_ADD(T_Or            , "||"          );
    M_WORD_MAP_ADD(T_Not           , "!"           );
    M_WORD_MAP_ADD(T_Colon         , ":"           );
    M_WORD_MAP_ADD(T_HT_Def        , "#def"        );
    M_WORD_MAP_ADD(T_HT_If         , "#if"         );
    M_WORD_MAP_ADD(T_HT_Else       , "#else"       );
    M_WORD_MAP_ADD(T_HT_Elif       , "#elif"       );
    M_WORD_MAP_ADD(T_HT_End        , "#end"        );
    M_WORD_MAP_ADD(T_Vs            , "vs"          );
    M_WORD_MAP_ADD(T_Fp            , "fp"          );
    M_WORD_MAP_ADD(T_Main          , "main"        );
    M_WORD_MAP_ADD(T_Lowp          , "lowp"        );
    M_WORD_MAP_ADD(T_Medi          , "medi"        );
    M_WORD_MAP_ADD(T_High          , "high"        );
    M_WORD_MAP_ADD(T_Float         , "float"       );
    M_WORD_MAP_ADD(T_Vec2          , "vec2"        );
    M_WORD_MAP_ADD(T_Vec3          , "vec3"        );
    M_WORD_MAP_ADD(T_Vec4          , "vec4"        );
    M_WORD_MAP_ADD(T_Mat2          , "mat2"        );
    M_WORD_MAP_ADD(T_Mat3          , "mat3"        );
    M_WORD_MAP_ADD(T_Mat4          , "mat4"        );
    M_WORD_MAP_ADD(T_Tex1d         , "tex1d"       );
    M_WORD_MAP_ADD(T_Tex2d         , "tex2d"       );
    M_WORD_MAP_ADD(T_Layout        , "layout"      );
    M_WORD_MAP_ADD(T_Buffer        , "buffer"      );
    M_WORD_MAP_ADD(T_Bridge        , "bridge"      );
    M_WORD_MAP_ADD(T_Texture       , "texture"     );
    M_WORD_MAP_ADD(T_POSITION      , "POSITION"    );
    M_WORD_MAP_ADD(T_TEXCOORD      , "TEXCOORD"    );
    M_WORD_MAP_ADD(T_COLOR         , "COLOR"       );
    M_WORD_MAP_ADD(T_gx_Position   , "gx_Position" );
    M_WORD_MAP_ADD(T_gx_FragColor  , "gx_FragColor");

#undef M_WORD_MAP_ADD
}

void GCSL::skip_white_space(QChar& ch, GCSLReader& reader)
{
    while (ch==' ' || ch=='\t' || ch=='\n' || ch=='\r') {
       if(ch=='\r') {
           reader.wrap();
           ch=reader.getChar();
           if(ch!='\n') {
               return;
           }
       }
       else if(ch=='\n') {
           reader.wrap();
           ch=reader.getChar();
           if(ch!='\r') {
               return;
           }
       }
       ch=reader.getChar();
    }
}

void GCSL::parse_comment0(QChar& ch, GCSLReader& reader)
{
    ch=reader.getChar();
    while(true) {
        while(true) {
            if(ch=='\n' || ch=='\r' || ch<=0) {
                break;
            }
            else {
                ch=reader.getChar();
            }
        }
        if(ch=='\n') {
            reader.wrap();
            ch=reader.getChar();
            if(ch=='\r') {
                ch=reader.getChar();
            }
            return;
        }
        else if(ch=='\r') {
            reader.wrap();
            ch=reader.getChar();
            if(ch=='\n') {
                ch=reader.getChar();
            }
            return;
        }
        else {
            break;
        }
    }
}

void GCSL::parse_comment1(QChar& ch, GCSLReader& reader)
{
    ch=reader.getChar();
    while(true) {
        while(true) {
            if(ch=='\n' || ch=='\r' || ch=='*' || ch<=0) {
                break;
            }
            else {
                ch=reader.getChar();
            }
        }
        if(ch=='\n') {
            reader.wrap();
            ch=reader.getChar();
            if(ch=='\r') {
                ch=reader.getChar();
            }
        }
        else if(ch=='\r') {
            reader.wrap();
            ch=reader.getChar();
            if(ch=='\n') {
                ch=reader.getChar();
            }
        }
        else if(ch=='*') {
            ch=reader.getChar();
            if(ch=='/') {
                ch=reader.getChar();
                return;
            }
        }
        else {
            break;
        }
    }
}

void GCSL::preprocess(QChar& ch, GCSLReader& reader)
{
    while(true) {
        if(ch==' ' || ch=='\t' || ch=='\n' || ch=='\r') {
            skip_white_space(ch,reader);
        }
        else if(ch=='/') {
            ch=reader.getChar();
            if(ch=='/') {
                parse_comment0(ch,reader);
            }
            else if(ch=='*') {
                parse_comment1(ch,reader);
            }
            else {
                reader.ungetChar();
                ch='/';
                break;
            }
        }
        else {
            break;
        }
    }
}

void GCSL::parse_ID(QChar &ch, GCSLReader &reader, QString& strOut)
{
    strOut.append(ch);
    ch=reader.getChar();
    while(ch.isLetterOrNumber() || ch=='_') {
        strOut.append(ch);
        ch=reader.getChar();
    }
}

void GCSL::parse_number(QChar &ch, GCSLReader &reader, QString& strOut)
{
    strOut.append(ch);
    ch=reader.getChar();
    bool hasPoint=false;
    while(ch.isNumber() || (ch=='.' && !hasPoint)) {
        strOut.append(ch);
        if(ch=='.') {
            hasPoint=true;
        }
        ch=reader.getChar();
    }
}

bool GCSL::getToken(QChar& ch,GCSLReader& reader,GCSLToken* tokenOut,GCSLError* errOut)
{
    preprocess(ch,reader);

    tokenOut->setRC(reader);

    if( ch.isLetter() || ch=='_' || ch=='#' ) {
        QString str;
        parse_ID(ch,reader,str);
        GCSLWord* p=m_WordMap[str];
        if(!p) {
            p=new GCSLWord(GCSLToken::T_Variable,str,this);
            m_WordMap[str]=p;
        }
        tokenOut->setType(p->getTokenType(),str);
    }
    else if (ch.isNumber()) {
        QString str;
        parse_number(ch,reader,str);
        if(!str.contains('.')) {
            tokenOut->setType(GCSLToken::T_Integer,str);
        }
        else {
            tokenOut->setType(GCSLToken::T_Floating,str);
        }
    }
    else if(ch==';') {
        tokenOut->setType(GCSLToken::T_Semicolon,";");

        ch=reader.getChar();
    }
    else if(ch=='(') {
        tokenOut->setType(GCSLToken::T_S_Brackets_L,"(");

        ch=reader.getChar();
    }
    else if(ch==')') {
        tokenOut->setType(GCSLToken::T_S_Brackets_R,")");

        ch=reader.getChar();
    }
    else if(ch=='[') {
        tokenOut->setType(GCSLToken::T_M_Brackets_L,"[");

        ch=reader.getChar();
    }
    else if(ch==']') {
        tokenOut->setType(GCSLToken::T_M_Brackets_R,"]");

        ch=reader.getChar();
    }
    else if(ch=='{') {
        tokenOut->setType(GCSLToken::T_B_Brackets_L,"{");

        ch=reader.getChar();
    }
    else if(ch=='}') {

        tokenOut->setType(GCSLToken::T_B_Brackets_R,"}");

        ch=reader.getChar();
    }
    else if(ch==',') {
        tokenOut->setType(GCSLToken::T_Comma,",");

        ch=reader.getChar();
    }
    else if(ch=='=') {
        ch=reader.getChar();

        if(ch=='=') {
            tokenOut->setType(GCSLToken::T_EqualEqual,"==");
            ch=reader.getChar();
        }
        else {
            tokenOut->setType(GCSLToken::T_Equal,"=");
        }

    }
    else if(ch=='+') {
        ch=reader.getChar();

        if(ch=='+') {
            tokenOut->setType(GCSLToken::T_PlusPlus,"++");
            ch=reader.getChar();
        }
        else if(ch=='=') {
            tokenOut->setType(GCSLToken::T_PlusEqual,"+=");
            ch=reader.getChar();
        }
        else {
            tokenOut->setType(GCSLToken::T_Plus,"+");
        }

    }
    else if(ch=='-') {
        ch=reader.getChar();

        if(ch=='-') {
            tokenOut->setType(GCSLToken::T_MinusMinus,"--");
            ch=reader.getChar();
        }
        else if(ch=='=') {
            tokenOut->setType(GCSLToken::T_MinusEqual,"-=");
            ch=reader.getChar();
        }
        else {
            tokenOut->setType(GCSLToken::T_Minus,"-");
        }

    }
    else if(ch=='*') {
        ch=reader.getChar();

        if(ch=='=') {
            tokenOut->setType(GCSLToken::T_MultiplyEqual,"*=");
            ch=reader.getChar();
        }
        else {
            tokenOut->setType(GCSLToken::T_Multiply,"*");
        }

    }
    else if(ch=='/') {
        ch=reader.getChar();

        if(ch=='=') {
            tokenOut->setType(GCSLToken::T_DivEqual,"/=");
            ch=reader.getChar();
        }
        else {
            tokenOut->setType(GCSLToken::T_Div,"/");
        }
    }
    else if(ch=='.') {
        tokenOut->setType(GCSLToken::T_Period,".");

        ch=reader.getChar();
    }
    else if(ch=='&') {
        ch=reader.getChar();
        if(ch=='&') {
            tokenOut->setType(GCSLToken::T_And,"&&");
        }
        else {
            if(errOut) {
                reader.ungetChar();
                errOut->setCode(GCSLError::C_UnknownChar);
                errOut->setRC(reader);
            }
            return false;
        }
        ch=reader.getChar();
    }
    else if(ch=='|') {
        ch=reader.getChar();
        if(ch=='|') {
            tokenOut->setType(GCSLToken::T_Or,"||");
        }
        else {
            if(errOut) {
                reader.ungetChar();
                errOut->setCode(GCSLError::C_UnknownChar);
                errOut->setRC(reader);
            }
            return false;
        }
        ch=reader.getChar();
    }
    else if(ch=='!') {
        tokenOut->setType(GCSLToken::T_Not,"!");

        ch=reader.getChar();
    }
    else if(ch==':') {
        tokenOut->setType(GCSLToken::T_Colon,":");

        ch=reader.getChar();
    }
    else if(ch<=0) {
        tokenOut->setType(GCSLToken::T_EOF,"");
    }
    else {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnknownChar);
            errOut->setRC(reader);
            errOut->setMessage(ch);
        }
        return false;
    }
    return true;
}

bool GCSL::translateToTokens(GCSLError *errOut)
{
    GCSLReader reader(&m_Text);
    QChar ch=reader.getChar();

    while(true) {
        GCSLToken* token=new GCSLToken(this);

        if(getToken(ch,reader,token,errOut)) {
            m_Tokens.append(token);
            if(token->getType()==GCSLToken::T_EOF) {
                break;
            }
        }
        else {
            delete token;
            return false;
        }
    }
    return true;
}

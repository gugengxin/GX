#include "GCSL.h"
#include "GCTextEditor.h"
#include <QFile>
#include <QTextCodec>

/*
gxsl(GX Shading Language) 将被翻译成 glsl或hlsl

例子：
#def TEX
#def TEX_MASK
vs {
    layout {
        high vec4 pos:POSITION;
        #if TEX
        medi vec2 texCoord:TEXCOORD0;
        #end
        #if TEX_MASK
        medi vec2 texCoordMask:TEXCOORD1;
        #end
        lowp vec4 color:COLOR0;
        lowp vec4 colorMask:COLOR1;
    }
    buffer {
        high mat4 mvpMatrix;
    }
    bridge {
        medi vec2 v_texCoord:TEXCOORD0;
        #if MASK
        medi vec2 v_texCoord_mask:TEXCOORD1;
        #end
        lowp vec4 v_color:COLOR0;
        #if COLOR_MASK
        lowp vec4 v_color_mask:COLOR1;
        #end
    }

    main {
        vec4 abc(1.0,2.0,3.0,1.0);
        gx_Position=mul(mvpMatrix,layout.pos);
        gx_Position*=abc;
        bridge.v_texCoord=layout.texCoord;
        #if MASK
        bridge.v_texCoord_mask=layout.texCoordMask;
        #end
        bridge.v_color=layout.color;
        #if COLOR_MASK
        bridge.v_color_mask=layout.colorMask;
        #end
    }
}

fp {
    buffer {
        lowp vec4 colorMul;
    }
    texture {
        lowp tex2d[0] tex;
        lowp tex2d[1] texMask;
    }
    main {
        gx_FragColor=tex2d(tex,bridge.v_texCoord);
        #if MASK
        gx_FragColor+=tex2d(texMask,bridge.v_texCoord_mask);
        #end
        gx_FragColor+=bridge.v_color;
        #if COLOR_MASK
        gx_FragColor+=bridge.v_color_mask;
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
    QString src;

    bool res=false;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray data=file.readAll();

        if(data.size()>=GCTextEditor::BOM8Bytes && memcmp(GCTextEditor::BOM8,data.data(),GCTextEditor::BOM8Bytes)==0) {
            QTextCodec* codec=QTextCodec::codecForName("UTF-8");
            if(codec) {
                src=codec->toUnicode(data.data()+GCTextEditor::BOM8Bytes,data.size()-GCTextEditor::BOM8Bytes);
                res=true;
            }
        }
        else {
            QTextCodec* codec=QTextCodec::codecForName(guessEncode.toUtf8());
            if(codec) {
                src=codec->toUnicode(data);
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

    return compile(src,errOut);
}

bool GCSL::compile(const QString &src, GCSLError *errOut)
{
    m_Text=src;

    initWords();

    if(!translateToTokens(errOut)) {
        return false;
    }

    GCSLTokenReader reader(m_Tokens);
    m_Writer=new GCSLWRoot(this);
    return m_Writer->compile(reader,errOut);
}

bool GCSL::make(GCSLWriter::SLType slType, const char *strWarp, QString &vsOut, QString &fpOut, GCSLError *errOut)
{
    GCSLWriter::MakeParam param(slType,strWarp);

    if(!m_Writer->makeVS(param,vsOut,errOut)) {
        return false;
    }

    param.lineLevel=0;
    if(!m_Writer->makeFP(param,fpOut,errOut)) {
        return false;
    }

    return true;
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
    m_WordList.clear();
    m_WordMap.clear();
    m_Text.clear();
}

void GCSL::initWords()
{
#define M_WORD_MAP_ADD(t,s) \
    {GCSLWord* word=new GCSLWord(GCSLToken::t,s,this);m_WordList.append(word);m_WordMap.insert(QString(s),word);}
#define M_WORD_MAP_ADD_OID(t,s,gl,gles,hl) \
    {GCSLWord* word=new GCSLWord(GCSLToken::t,s,gl,gles,hl,this);m_WordList.append(word);m_WordMap.insert(QString(s),word);}

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
    M_WORD_MAP_ADD_OID(T_HT_Def    , "#def"        ,"#define"   ,"#define"  ,"#define"  );
    M_WORD_MAP_ADD_OID(T_HT_If     , "#if"         ,"#if"       ,"#if"      ,"#if"      );
    M_WORD_MAP_ADD_OID(T_HT_Else   , "#else"       ,"#else"     ,"#else"    ,"#else"    );
    M_WORD_MAP_ADD_OID(T_HT_Elif   , "#elif"       ,"#elif"     ,"#elif"    ,"#elif"    );
    M_WORD_MAP_ADD_OID(T_HT_End    , "#end"        ,"#endif"    ,"#endif"   ,"#endif"   );
    M_WORD_MAP_ADD(T_Vs            , "vs"          );
    M_WORD_MAP_ADD(T_Fp            , "fp"          );
    M_WORD_MAP_ADD(T_Main          , "main"        );
    M_WORD_MAP_ADD_OID(T_Lowp      , "lowp"    ,""  ,"lowp"     ,""    );
    M_WORD_MAP_ADD_OID(T_Medi      , "medi"    ,""  ,"mediump"  ,""    );
    M_WORD_MAP_ADD_OID(T_High      , "high"    ,""  ,"highp"    ,""    );
    M_WORD_MAP_ADD_OID(T_Float     , "float"   ,"float" ,"float","float"    );
    M_WORD_MAP_ADD_OID(T_Vec2      , "vec2"    ,"vec2"  ,"vec2" ,"float2"   );
    M_WORD_MAP_ADD_OID(T_Vec3      , "vec3"    ,"vec3"  ,"vec3" ,"float3"   );
    M_WORD_MAP_ADD_OID(T_Vec4      , "vec4"    ,"vec4"  ,"vec4" ,"float4"   );
    M_WORD_MAP_ADD_OID(T_Mat2      , "mat2"    ,"mat2"  ,"mat2" ,"float2x2" );
    M_WORD_MAP_ADD_OID(T_Mat3      , "mat3"    ,"mat3"  ,"mat3" ,"float3x3" );
    M_WORD_MAP_ADD_OID(T_Mat4      , "mat4"    ,"mat4"  ,"mat4" ,"matrix" );
    M_WORD_MAP_ADD_OID(T_Tex1d     ,"tex1d","sampler1D","sampler1D","Texture1D");
    M_WORD_MAP_ADD_OID(T_Tex2d     ,"tex2d","sampler2D","sampler2D","Texture2D");
    M_WORD_MAP_ADD(T_Layout        , "layout"      );
    M_WORD_MAP_ADD(T_Buffer        , "buffer"      );
    M_WORD_MAP_ADD(T_Bridge        , "bridge"      );
    M_WORD_MAP_ADD(T_Texture       , "texture"     );
    M_WORD_MAP_ADD_OID(T_POSITION  , "POSITION" ,"","", "POSITION"  );
    M_WORD_MAP_ADD_OID(T_TEXCOORD  , "TEXCOORD" ,"","", "TEXCOORD"  );
    M_WORD_MAP_ADD_OID(T_COLOR     , "COLOR"    ,"","", "COLOR"     );
    M_WORD_MAP_ADD_OID(T_gx_Position   , "gx_Position" ,"gl_Position" ,"gl_Position" ,"gx_Position");
    M_WORD_MAP_ADD_OID(T_gx_FragColor  , "gx_FragColor","gl_FragColor","gl_FragColor","gx_FragColor");
    M_WORD_MAP_ADD(T_Mul           , "mul"         );

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

        bool notFound=true;
        for(int i=(int)GCSLToken::T_POSITION;i<=(int)GCSLToken::T_COLOR;i++) {
            QString& wid=m_WordList[i]->getID();
            if(str.startsWith(wid) && (str.length()<=wid.length() || str[wid.length()].isNumber())) {
                tokenOut->setType((GCSLToken::Type)i,wid);

                reader.ungetChar(str.length()-wid.length()+1);
                ch=reader.getChar();
                notFound=false;
                break;
            }
        }

        if(notFound) {
            GCSLWord* p=m_WordMap[str];
            if(!p) {
                p=new GCSLWord(GCSLToken::T_Variable,str,this);
                m_WordMap[str]=p;
            }
            tokenOut->setType(p->getTokenType(),str);
        }
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
        GCSLWord* p=m_WordMap[str];
        if(!p) {
            p=new GCSLWord(tokenOut->getType(),str,this);
            m_WordMap[str]=p;
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

GCSLWord *GCSL::getWord(const QString &key)
{
    return m_WordMap[key];
}

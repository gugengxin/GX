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
        medi vec2 tex:TEXCOORD0;
        #if MASK
        medi vec2 texMask:TEXCOORD0;
        #end
        lowp vec4 color:COLOR0;
        #if COLOR_MASK
        lowp vec4 colorMask:COLOR0;
        #end
    }
    buffer(0) {
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

    void main()
    {
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
    buffer(0) {
        lowp vec4 colorMul;
    }
    lowp tex2d(0) tex;
    lowp tex2d(1) texMask;

    void main()
    {
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
            errOut->m_Code=GCSLError::C_ReadFile;
        }
        return false;
    }

    TextInputStream semIn(&m_Text);

    if(!translateToTokens(semIn,errOut)) {
        return false;
    }



    return true;
}

static void skip_white_space(QChar& ch, GCSL::TextInputStream& sem)
{
    while (ch==' ' || ch=='\t' || ch=='\n' || ch=='\r') {
       if(ch=='\r') {
           sem.wrap();
           ch=sem.getChar();
           if(ch!='\n') {
               return;
           }
       }
       else if(ch=='\n') {
           sem.wrap();
           ch=sem.getChar();
           if(ch!='\r') {
               return;
           }
       }
       ch=sem.getChar();
    }
}

static void parse_comment0(QChar& ch, GCSL::TextInputStream& sem)
{
    ch=sem.getChar();
    while(true) {
        while(true) {
            if(ch=='\n' || ch=='\r' || ch<=0) {
                break;
            }
            else {
                ch=sem.getChar();
            }
        }
        if(ch=='\n') {
            sem.wrap();
            ch=sem.getChar();
            if(ch=='\r') {
                ch=sem.getChar();
            }
            return;
        }
        else if(ch=='\r') {
            sem.wrap();
            ch=sem.getChar();
            if(ch=='\n') {
                ch=sem.getChar();
            }
            return;
        }
        else {
            break;
        }
    }
}

static void parse_comment1(QChar& ch, GCSL::TextInputStream& sem)
{
    ch=sem.getChar();
    while(true) {
        while(true) {
            if(ch=='\n' || ch=='\r' || ch=='*' || ch<=0) {
                break;
            }
            else {
                ch=sem.getChar();
            }
        }
        if(ch=='\n') {
            sem.wrap();
            ch=sem.getChar();
            if(ch=='\r') {
                ch=sem.getChar();
            }
        }
        else if(ch=='\r') {
            sem.wrap();
            ch=sem.getChar();
            if(ch=='\n') {
                ch=sem.getChar();
            }
        }
        else if(ch=='*') {
            ch=sem.getChar();
            if(ch=='/') {
                ch=sem.getChar();
                return;
            }
        }
        else {
            break;
        }
    }
}

static void preprocess(QChar& ch, GCSL::TextInputStream& sem)
{
    while(true) {
        if(ch==' ' || ch=='\t' || ch=='\n' || ch=='\r') {
            skip_white_space(ch,sem);
        }
        else if(ch=='/') {
            ch=sem.getChar();
            if(ch=='/') {
                parse_comment0(ch,sem);
            }
            else if(ch=='*') {
                parse_comment1(ch,sem);
            }
            else {
                sem.ungetChar();
                ch='/';
                break;
            }
        }
        else {
            break;
        }
    }
}

bool GCSL::translateToTokens(GCSL::TextInputStream &sem, GCSLError *errOut)
{
    QChar ch=sem.getChar();

    while(true) {
        preprocess(ch,sem);

        if( ch.isLetter() ) {

        }
        else if (ch.isNumber()) {

        }
        else if(ch==';') {
            GCSLToken* token=new GCSLToken(this);
            token->setType(GCSLToken::T_Semicolon);
            m_Tokens.append(token);
            ch=sem.getChar();
        }
        else if(ch=='(') {
            GCSLToken* token=new GCSLToken(this);
            token->setType(GCSLToken::T_S_Brackets_L);
            m_Tokens.append(token);
            ch=sem.getChar();
        }
        else if(ch==')') {
            GCSLToken* token=new GCSLToken(this);
            token->setType(GCSLToken::T_S_Brackets_R);
            m_Tokens.append(token);
            ch=sem.getChar();
        }
        else if(ch=='[') {
            GCSLToken* token=new GCSLToken(this);
            token->setType(GCSLToken::T_M_Brackets_L);
            m_Tokens.append(token);
            ch=sem.getChar();
        }
        else if(ch==']') {
            GCSLToken* token=new GCSLToken(this);
            token->setType(GCSLToken::T_M_Brackets_R);
            m_Tokens.append(token);
            ch=sem.getChar();
        }
        else if(ch=='{') {
            GCSLToken* token=new GCSLToken(this);
            token->setType(GCSLToken::T_B_Brackets_L);
            m_Tokens.append(token);
            ch=sem.getChar();
        }
        else if(ch=='}') {
            GCSLToken* token=new GCSLToken(this);
            token->setType(GCSLToken::T_B_Brackets_R);
            m_Tokens.append(token);
            ch=sem.getChar();
        }
        else if(ch==',') {
            GCSLToken* token=new GCSLToken(this);
            token->setType(GCSLToken::T_Comma);
            m_Tokens.append(token);
            ch=sem.getChar();
        }
        else if(ch=='=') {
            ch=sem.getChar();
            GCSLToken* token=new GCSLToken(this);
            if(ch=='=') {
                token->setType(GCSLToken::T_EqualEqual);
                ch=sem.getChar();
            }
            else {
                token->setType(GCSLToken::T_Equal);
            }
            m_Tokens.append(token);
        }
        else if(ch=='+') {
            ch=sem.getChar();
            GCSLToken* token=new GCSLToken(this);
            if(ch=='+') {
                token->setType(GCSLToken::T_PlusPlus);
                ch=sem.getChar();
            }
            else if(ch=='=') {
                token->setType(GCSLToken::T_PlusEqual);
                ch=sem.getChar();
            }
            else {
                token->setType(GCSLToken::T_Plus);
            }
            m_Tokens.append(token);
        }
        else if(ch=='-') {
            ch=sem.getChar();
            GCSLToken* token=new GCSLToken(this);
            if(ch=='-') {
                token->setType(GCSLToken::T_MinusMinus);
                ch=sem.getChar();
            }
            else if(ch=='=') {
                token->setType(GCSLToken::T_MinusEqual);
                ch=sem.getChar();
            }
            else {
                token->setType(GCSLToken::T_Minus);
            }
            m_Tokens.append(token);
        }
        else if(ch=='*') {
            ch=sem.getChar();
            GCSLToken* token=new GCSLToken(this);
            if(ch=='=') {
                token->setType(GCSLToken::T_MultiplyEqual);
                ch=sem.getChar();
            }
            else {
                token->setType(GCSLToken::T_Multiply);
            }
            m_Tokens.append(token);
        }
        else if(ch=='/') {
            ch=sem.getChar();
            GCSLToken* token=new GCSLToken(this);
            if(ch=='=') {
                token->setType(GCSLToken::T_DivEqual);
                ch=sem.getChar();
            }
            else {
                token->setType(GCSLToken::T_Div);
            }
            m_Tokens.append(token);
        }
        else if(ch=='.') {
            GCSLToken* token=new GCSLToken(this);
            token->setType(GCSLToken::T_Period);
            m_Tokens.append(token);
            ch=sem.getChar();
        }
        else if(ch<=0) {
            break;
        }
        else {
            if(errOut) {
                errOut->m_Code=GCSLError::C_UnknownChar;
                errOut->m_Row=sem.getRow();
                errOut->m_Column=sem.getColumn();
                errOut->m_Message=ch;
            }
            return false;
        }
    }
    return true;
}

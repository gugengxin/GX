#include "GCSLWMainLine.h"

GCSLWMainLine::GCSLWMainLine(QObject *parent) : GCSLWriter(parent)
{

}

bool GCSLWMainLine::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    GCSLToken::Type types[]={
        GCSLToken::T_S_Brackets_L  , // "("
        GCSLToken::T_S_Brackets_R  , // ")"
        GCSLToken::T_M_Brackets_L  , // "["
        GCSLToken::T_M_Brackets_R  , // "]"
        GCSLToken::T_B_Brackets_L  , // "{"
        GCSLToken::T_B_Brackets_R  , // "}"
        GCSLToken::T_Comma         , // ","
        GCSLToken::T_Equal         , // "="
        GCSLToken::T_EqualEqual    , // "=="
        GCSLToken::T_Plus          , // "+"
        GCSLToken::T_PlusPlus      , // "++"
        GCSLToken::T_PlusEqual     , // "+="
        GCSLToken::T_Minus         , // "-"
        GCSLToken::T_MinusMinus    , // "--"
        GCSLToken::T_MinusEqual    , // "-="
        GCSLToken::T_Multiply      , // "*"
        GCSLToken::T_MultiplyEqual , // "*="
        GCSLToken::T_Div           , // "/"
        GCSLToken::T_DivEqual      , // "/="
        GCSLToken::T_Period        , // "."
        GCSLToken::T_Lowp          , // "lowp"
        GCSLToken::T_Medi          , // "medi"
        GCSLToken::T_High          , // "high"
        GCSLToken::T_Float         , // "float"
        GCSLToken::T_Vec2          , // "vec2"
        GCSLToken::T_Vec3          , // "vec3"
        GCSLToken::T_Vec4          , // "vec4"
        GCSLToken::T_Mat2          , // "mat2"
        GCSLToken::T_Mat3          , // "mat3"
        GCSLToken::T_Mat4          , // "mat4"
        GCSLToken::T_Tex1d         , // "tex1d"
        GCSLToken::T_Tex2d         , // "tex2d"
        GCSLToken::T_Layout        , // "layout"
        GCSLToken::T_Buffer        , // "buffer"
        GCSLToken::T_Bridge        , // "bridge"
        GCSLToken::T_gx_Position   , // "gx_Position"
        GCSLToken::T_gx_FragColor  , // "gx_FragColor"
        GCSLToken::T_Mul           , // "mul"
        GCSLToken::T_Variable      ,
        GCSLToken::T_Integer       ,
        GCSLToken::T_Floating      ,
    };

    reader.ungetToken();

    while(true) {
        GCSLToken* token=reader.getToken();

        if(token->isSemicolon()) {
            return true;
        }

        int i=0;
        for(;i<(int)(sizeof(types)/sizeof(types[0]));i++) {
            if(token->getType()==types[i]) {
                m_Tokens.append(token);
                break;
            }
        }

        if(i>=(int)(sizeof(types)/sizeof(types[0]))) {
            if(errOut) {
                errOut->setCode(GCSLError::C_UnexceptToken);
                errOut->setRC(token);
            }
            return false;
        }
    }
    return true;
}

bool GCSLWMainLine::make(GCSLWriter::MakeParam &param,GCSLTokenReader& reader,QString &strOut, GCSLError *errOut)
{
    GCSLToken* token=NULL;
    GCSLToken* tokenLast;
    while(true) {
        tokenLast=token;
        token=reader.getToken();
        if(!token) {
            break;
        }

        if(token->isLMH()) {
            if(param.slType==SLT_GLSL_ES) {
                if(tokenLast && !tokenLast->isSymbol()) {
                    strOut.append(" ");
                }
                strOut.append(getWordSLID(token,param.slType));
            }
        }
        else if(token->isTex()) {
            if(tokenLast && !tokenLast->isSymbol()) {
                strOut.append(" ");
            }

            tokenLast=token;
            token=reader.getToken();

            if(!token) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnexceptEOF);
                    errOut->setRC(tokenLast);
                }
                return false;
            }
            else if(token->getType()!=GCSLToken::T_S_Brackets_L) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnsupportToken);
                    errOut->setRC(token);
                }
                return false;
            }

            tokenLast=token;
            token=reader.getToken();

            if(!token) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnexceptEOF);
                    errOut->setRC(tokenLast);
                }
                return false;
            }
            else if(token->getType()!=GCSLToken::T_Variable) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnsupportToken);
                    errOut->setRC(token);
                }
                return false;
            }
            GCSLToken* tTex=token;

            tokenLast=token;
            token=reader.getToken();

            if(!token) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnexceptEOF);
                    errOut->setRC(tokenLast);
                }
                return false;
            }
            else if(token->getType()!=GCSLToken::T_Comma) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnsupportToken);
                    errOut->setRC(token);
                }
                return false;
            }

            GCSLTokenReader myReader;
            if(!myReader.addTokensToSBR(reader)) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnexceptEOF);
                    errOut->setRC(reader);
                }
                return false;
            }

            switch (param.slType) {
            case SLT_GLSL:
            case SLT_GLSL_ES:
            {
                strOut.append(QString("texture2D(%1,").arg(getWordSLID(tTex,param.slType)));
            }
                break;
            case SLT_HLSL:
            {
                strOut.append(QString("%1.Sample(%2_s,").arg(getWordSLID(tTex,param.slType)).arg(getWordSLID(tTex,param.slType)));
            }
                break;
            case SLT_MSL:
            {
                strOut.append(QString("%1.sample(%2_s,").arg(getWordSLID(tTex,param.slType)).arg(getWordSLID(tTex,param.slType)));
            }
                break;
            default:
                return false;
            }

            if(!make(param,myReader,strOut,errOut)) {
                return false;
            }

            strOut.append(")");
        }
        else if(token->getType()==GCSLToken::T_Bridge || token->getType()==GCSLToken::T_Layout) {

            switch (param.slType) {
            case SLT_GLSL:
            case SLT_GLSL_ES:
            {
                tokenLast=token;
                token=reader.getToken();

                if(!token) {
                    if(errOut) {
                        errOut->setCode(GCSLError::C_UnexceptEOF);
                        errOut->setRC(tokenLast);
                    }
                    return false;
                }
                else if(token->getType()!=GCSLToken::T_Period) {
                    if(errOut) {
                        errOut->setCode(GCSLError::C_UnsupportToken);
                        errOut->setRC(token);
                    }
                    return false;
                }
                //append null, jump
            }
                break;
            case SLT_HLSL:
            case SLT_MSL:
            {
                if(tokenLast && !tokenLast->isSymbol()) {
                    strOut.append(" ");
                }
                strOut.append(getWordSLID(token,param.slType));
            }
                break;
            default:
                return false;
            }
        }
        else if(token->getType()==GCSLToken::T_Buffer) {
            switch (param.slType) {
            case SLT_GLSL:
            case SLT_GLSL_ES:
            case SLT_HLSL:
            {
                tokenLast=token;
                token=reader.getToken();

                if(!token) {
                    if(errOut) {
                        errOut->setCode(GCSLError::C_UnexceptEOF);
                        errOut->setRC(tokenLast);
                    }
                    return false;
                }
                else if(token->getType()!=GCSLToken::T_Period) {
                    if(errOut) {
                        errOut->setCode(GCSLError::C_UnsupportToken);
                        errOut->setRC(token);
                    }
                    return false;
                }
            }
                break;
            case SLT_MSL:
            {
                if(tokenLast && !tokenLast->isSymbol()) {
                    strOut.append(" ");
                }
                strOut.append("uniformBuf");
            }
                break;
            default:
                return false;
            }
        }
        else if(token->getType()==GCSLToken::T_gx_Position) {
            if(tokenLast && !tokenLast->isSymbol()) {
                strOut.append(" ");
            }
            switch (param.slType) {
            case SLT_GLSL:
            case SLT_GLSL_ES:
            {
                strOut.append("gl_Position");
            }
                break;
            case SLT_HLSL:
            case SLT_MSL:
            {
                strOut.append("bridge.gx_Position");
            }
                break;
            default:
                return false;
            }
        }
        else if(token->getType()==GCSLToken::T_gx_FragColor) {
            if(tokenLast && !tokenLast->isSymbol()) {
                strOut.append(" ");
            }
            switch (param.slType) {
            case SLT_GLSL:
            case SLT_GLSL_ES:
            {
                strOut.append("gl_FragColor");
            }
                break;
            case SLT_HLSL:
            case SLT_MSL:
            {
                strOut.append("gx_FragColor");
            }
                break;
            default:
                return false;
            }
        }
        else if(token->getType()==GCSLToken::T_Mul) {
            if(tokenLast && !tokenLast->isSymbol()) {
                strOut.append(" ");
            }

            tokenLast=token;
            token=reader.getToken();

            if(!token) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnexceptEOF);
                    errOut->setRC(tokenLast);
                }
                return false;
            }
            else if(token->getType()!=GCSLToken::T_S_Brackets_L) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnsupportToken);
                    errOut->setRC(token);
                }
                return false;
            }

            GCSLTokenReader myReader0;
            if(!myReader0.addTokensToComma(reader)) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnexceptEOF);
                    errOut->setRC(reader);
                }
                return false;
            }
            GCSLTokenReader myReader1;
            if(!myReader1.addTokensToSBR(reader)) {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnexceptEOF);
                    errOut->setRC(reader);
                }
                return false;
            }

            QString str0,str1;

            if(!make(param,myReader0,str0,errOut)) {
                return false;
            }
            if(!make(param,myReader1,str1,errOut)) {
                return false;
            }

            switch (param.slType) {
            case SLT_GLSL:
            case SLT_GLSL_ES:
            {
                strOut.append(str0);
                strOut.append("*");
                strOut.append(str1);
            }
                break;
            case SLT_HLSL:
            {
                strOut.append(QString("mul(%1,%2)").arg(str1).arg(str0));
            }
                break;
            case SLT_MSL:
            {
                strOut.append(str1);
                strOut.append("*");
                strOut.append(str0);
            }
                break;
            default:
                return false;
            }
        }
        else {
            if(tokenLast && !tokenLast->isSymbol() && !token->isSymbol()) {
                strOut.append(" ");
            }
            strOut.append(getWordSLID(token,param.slType));
        }
    }
    return true;
}

bool GCSLWMainLine::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    strAppendTab(strOut,param.lineLevel);

    GCSLTokenReader reader(m_Tokens);
    if(!make(param,reader,strOut,errOut)) {
        return false;
    }
    strOut.append(";");
    strOut.append(param.strWarp);
    return true;
}

bool GCSLWMainLine::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    return makeVS(param,strOut,errOut);
}

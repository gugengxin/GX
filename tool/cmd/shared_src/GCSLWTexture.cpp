#include "GCSLWTexture.h"
#include "GCSLWHT.h"

GCSLWTexture::GCSLWTexture(QObject *parent) : GCSLWriter(parent)
{

}

bool GCSLWTexture::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    GCSLToken* token=reader.getToken();

    if(token->getType()!=GCSLToken::T_B_Brackets_L) {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnsupportToken);
            errOut->setRC(token);
        }
        return false;
    }
    GCSLTokenReader myReader;
    if(!myReader.addTokensToBBR(reader)) {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnexceptEOF);
            errOut->setRC(reader);
        }
        return false;
    }

    while(true) {
        token=myReader.getToken();
        if(!token) {
            return true;
        }
        if(token->isHT()) {
            if(!GCSLWHT::compile(this,token,myReader,errOut)) {
                return false;
            }
        }
        else if (token->isLMH()) {
            GCSLWTextureVar* wr=new GCSLWTextureVar(this);
            this->addSubWrite(wr);

            if(!wr->compile(myReader,errOut)) {
                return false;
            }
        }
        else {
            if(errOut) {
                errOut->setCode(GCSLError::C_UnsupportToken);
                errOut->setRC(token);
            }
            return false;
        }

    }
    return true;
}








GCSLWTextureVar::GCSLWTextureVar(QObject *parent) : GCSLWriter(parent)
{
    m_LMH=NULL;
    m_Type=NULL;
    m_Slot=0;
}

bool GCSLWTextureVar::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    reader.ungetToken();
    m_LMH=reader.getToken();

    GCSLToken* token=reader.getToken();
    if(token->isTex()) {
        m_Type=token;
    }
    else {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnexceptToken);
            errOut->setRC(token);
        }
        return false;
    }

    token=reader.getToken();
    if(token->getType()!=GCSLToken::T_M_Brackets_L) {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnsupportToken);
            errOut->setRC(token);
        }
        return false;
    }

    token=reader.getToken();
    if(token->getType()==GCSLToken::T_Integer) {
        m_Slot=token->getID().toInt();
    }
    else {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnsupportToken);
            errOut->setRC(token);
        }
        return false;
    }

    token=reader.getToken();
    if(token->getType()!=GCSLToken::T_M_Brackets_R) {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnsupportToken);
            errOut->setRC(token);
        }
        return false;
    }

    token=reader.getToken();
    if(token->getType()==GCSLToken::T_Variable) {
        m_Name=token->getID();
    }
    else {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnexceptToken);
            errOut->setRC(token);
        }
        return false;
    }

    token=reader.getToken();
    if(!token->isSemicolon()) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NeedSemicolon);
            errOut->setRC(token);
        }
        return false;
    }

    return true;
}

bool GCSLWTextureVar::makeVS(GCSLWriter::MakeParam &, QString &, GCSLError *)
{
    return true;
}

bool GCSLWTextureVar::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *)
{
    strAppendTab(strOut,param.lineLevel);
    if(param.slType==SLT_GLSL || param.slType==SLT_GLSL_ES) {
        strOut.append("uniform ");
        if(param.slType==SLT_GLSL_ES) {
            strOut.append(getWordSLID(m_LMH,param.slType));
            strOut.append(" ");
        }
    }
    strOut.append(getWordSLID(m_Type,param.slType));
    strOut.append(" ");
    strOut.append(m_Name);

    if(param.slType==SLT_HLSL) {
        strOut.append(QString(":register(t%1);").arg(m_Slot));
        strOut.append(param.strWarp);

        strAppendTab(strOut,param.lineLevel);
        strOut.append("SamplerState ");
        strOut.append(m_Name);
        strOut.append("_s");
        strOut.append(QString(":register(s%1)").arg(m_Slot));
    }
    strOut.append(";");
    strOut.append(param.strWarp);

    return true;
}

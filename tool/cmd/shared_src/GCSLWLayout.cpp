#include "GCSLWLayout.h"
#include "GCSLWHT.h"

GCSLWLayout::GCSLWLayout(QObject *parent) : GCSLWriter(parent)
{

}

bool GCSLWLayout::compile(GCSLTokenReader &reader, GCSLError *errOut)
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
            GCSLWLayoutVar* wr=new GCSLWLayoutVar(this);
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

bool GCSLWLayout::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    switch (param.slType) {
    case SLT_GLSL:
    case SLT_GLSL_ES:
    {
        return GCSLWriter::makeVS(param,strOut,errOut);
    }
        break;
    case SLT_HLSL:
    {
        strAppendTab(strOut,param.lineLevel);
        strOut.append("struct VertexInputType {");
        strOut.append(param.strWarp);
        param.lineLevel++;
        if(!GCSLWriter::makeVS(param,strOut,errOut)) {
            return false;
        }
        param.lineLevel--;
        strAppendTab(strOut,param.lineLevel);
        strOut.append("};");
        strOut.append(param.strWarp);
    }
        break;
    default:
        return false;
    }
    return true;
}

bool GCSLWLayout::makeFP(GCSLWriter::MakeParam &, QString &, GCSLError *)
{
    return true;
}







GCSLWLayoutVar::GCSLWLayoutVar(QObject *parent) : GCSLWriter(parent)
{
    m_LMH=NULL;
    m_Type=NULL;
    m_SemanticName=NULL;
    m_SemanticIndex=0;
}

bool GCSLWLayoutVar::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    reader.ungetToken();
    m_LMH=reader.getToken();

    GCSLToken* token=reader.getToken();
    if(token->isFloat() || token->isVec() || token->isMat()) {
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
    if(token->getType()!=GCSLToken::T_Colon) {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnexceptToken);
            errOut->setRC(token);
        }
        return false;
    }

    m_SemanticName=reader.getToken();
    if(!m_SemanticName->isSemantic()) {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnexceptToken);
            errOut->setRC(m_SemanticName);
        }
        return false;
    }

    token=reader.getToken();
    if(token->getType()==GCSLToken::T_Integer) {
        m_SemanticIndex=token->getID().toInt();
        token=reader.getToken();
    }

    if(!token->isSemicolon()) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NeedSemicolon);
            errOut->setRC(token);
        }
        return false;
    }

    return true;
}

bool GCSLWLayoutVar::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *)
{
    strAppendTab(strOut,param.lineLevel);
    if(param.slType==SLT_GLSL || param.slType==SLT_GLSL_ES) {
        strOut.append("attribute ");
        if(param.slType==SLT_GLSL_ES) {
            strOut.append(getWordSLID(m_LMH,param.slType));
            strOut.append(" ");
        }
    }
    strOut.append(getWordSLID(m_Type,param.slType));
    strOut.append(" ");
    strOut.append(m_Name);

    if(param.slType==SLT_HLSL) {
        strOut.append(":");
        strOut.append(getWordSLID(m_SemanticName,param.slType));
        strOut.append(QString::number(m_SemanticIndex));
    }
    strOut.append(";");
    strOut.append(param.strWarp);

    return true;
}

bool GCSLWLayoutVar::makeFP(GCSLWriter::MakeParam &, QString &, GCSLError *)
{
    return true;
}

#include "GCSLWBuffer.h"
#include "GCSLWHT.h"

GCSLWBuffer::GCSLWBuffer(QObject *parent) : GCSLWriter(parent)
{
}

bool GCSLWBuffer::compile(GCSLTokenReader &reader, GCSLError *errOut)
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
        if (token->isLMH()) {
            GCSLWBufferVar* wr=new GCSLWBufferVar(this);
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

bool GCSLWBuffer::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
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
        strOut.append("cbuffer UniformBuffer : register(b0) {");
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

bool GCSLWBuffer::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
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
        strOut.append("cbuffer UniformBuffer : register(b0) {");
        strOut.append(param.strWarp);
        param.lineLevel++;
        if(!GCSLWriter::makeFP(param,strOut,errOut)) {
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












GCSLWBufferVar::GCSLWBufferVar(QObject *parent) : GCSLWriter(parent)
{
    m_LMH=NULL;
    m_Type=NULL;
}

bool GCSLWBufferVar::compile(GCSLTokenReader &reader, GCSLError *errOut)
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
    if(!token->isSemicolon()) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NeedSemicolon);
            errOut->setRC(token);
        }
        return false;
    }

    return true;
}

bool GCSLWBufferVar::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *)
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
    strOut.append(";");
    strOut.append(param.strWarp);

    return true;
}

bool GCSLWBufferVar::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    return makeVS(param,strOut,errOut);
}

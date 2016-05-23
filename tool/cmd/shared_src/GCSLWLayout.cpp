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
    if(token->getType()==GCSLToken::T_M_Brackets_L) {
        token=reader.getToken();
        if(token->getType()==GCSLToken::T_Integer) {
            m_SemanticIndex=token->getID().toInt();

            token=reader.getToken();
            if(token->getType()==GCSLToken::T_M_Brackets_R) {
                token=reader.getToken();
            }
            else {
                if(errOut) {
                    errOut->setCode(GCSLError::C_UnexceptToken);
                    errOut->setRC(token);
                }
                return false;
            }
        }
        else {
            if(errOut) {
                errOut->setCode(GCSLError::C_UnexceptToken);
                errOut->setRC(token);
            }
            return false;
        }
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

#include "GCSLWHT.h"

GCSLWHTDef::GCSLWHTDef(QObject *parent) :
    GCSLWriter(parent)
{
    m_Index=-1;
}

bool GCSLWHTDef::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    GCSLToken* token=reader.getToken();

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

    GCSLToken* token0=reader.getToken();
    if(token0->getType()==GCSLToken::T_Integer) {
        m_Index=token0->getID().toInt();
        token0=reader.getToken();
    }

    if(token0->getRow()<=token->getRow()) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NeedWarp);
            errOut->setRC(token0);
        }
        return false;
    }

    return true;
}





GCSLWHTIf::GCSLWHTIf(QObject *parent) :
    GCSLWriter(parent)
{

}

bool GCSLWHTIf::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    GCSLToken* token=reader.getToken();

    int bkLv=0;
    while(true) {
        if(token->getType()==GCSLToken::T_Variable) {
            m_Conds.append(token);
            token=reader.getToken();
        }
        else if(token->getType()==GCSLToken::T_S_Brackets_L) {
            bkLv++;
            m_Conds.append(token);
            token=reader.getToken();
        }
        else if(token->getType()==GCSLToken::T_S_Brackets_R) {
            bkLv--;
            if(bkLv>=0) {
                m_Conds.append(token);
                token=reader.getToken();

                if(token->getType()==GCSLToken::T_And ||
                        token->getType()==GCSLToken::T_Or ) {


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
        else {
            if(errOut) {
                errOut->setCode(GCSLError::C_UnexceptToken);
                errOut->setRC(token);
            }
            return false;
        }
    }

}




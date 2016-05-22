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

    token=reader.getToken();
    if(token->getType()==GCSLToken::T_Integer) {
        m_Index=token->getID().toInt();
    }

    if( !reader.nextIsWarpped() ) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NeedWarp);
            errOut->setRC(token);
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
    if(reader.nextIsWarpped()) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NotNeedWarp);
            errOut->setRC(reader);
        }
        return false;
    }

    GCSLToken::Type types[]={
        GCSLToken::T_Variable,
        GCSLToken::T_S_Brackets_L,
        GCSLToken::T_S_Brackets_R,
        GCSLToken::T_And,
        GCSLToken::T_Or,
        GCSLToken::T_Not,
    };

    while(true) {

        GCSLToken* token=reader.getToken();

        int i=0;
        for(;i<(int)(sizeof(types)/sizeof(types[0]));i++) {
            if(token->getType()==types[i]) {
                m_Conds.append(token);

                if(reader.nextIsWarpped()) {
                    return true;
                }
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

}






GCSLWHTElif::GCSLWHTElif(QObject *parent) :
    GCSLWriter(parent)
{

}

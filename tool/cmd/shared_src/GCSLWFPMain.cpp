#include "GCSLWFPMain.h"
#include "GCSLWHT.h"

GCSLWFPMain::GCSLWFPMain(QObject *parent) : GCSLWriter(parent)
{

}

bool GCSLWFPMain::compile(GCSLTokenReader &reader, GCSLError *errOut)
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
            //TODO
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

#include "GCSLWVSMain.h"
#include "GCSLWHT.h"
#include "GCSLWMainLine.h"

GCSLWVSMain::GCSLWVSMain(QObject *parent) : GCSLWriter(parent)
{

}

bool GCSLWVSMain::compile(GCSLTokenReader &reader, GCSLError *errOut)
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
        else {
            GCSLWMainLine* wr=new GCSLWMainLine(this);
            this->addSubWrite(wr);

            if(!wr->compile(myReader,errOut)) {
                return false;
            }
        }
    }
    return true;
}

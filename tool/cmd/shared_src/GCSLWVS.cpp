#include "GCSLWVS.h"
#include "GCSLWHT.h"
#include "GCSLWLayout.h"
#include "GCSLWBuffer.h"
#include "GCSLWBridge.h"
#include "GCSLWVSMain.h"

GCSLWVS::GCSLWVS(QObject *parent) : GCSLWriter(parent)
{

}

bool GCSLWVS::compile(GCSLTokenReader &reader, GCSLError *errOut)
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
        else if (token->getType()==GCSLToken::T_Layout) {
            GCSLWLayout* wr=new GCSLWLayout(this);
            this->addSubWrite(wr);

            if(!wr->compile(myReader,errOut)) {
                return false;
            }
        }
        else if (token->getType()==GCSLToken::T_Buffer) {
            GCSLWBuffer* wr=new GCSLWBuffer(this);
            this->addSubWrite(wr);

            if(!wr->compile(myReader,errOut)) {
                return false;
            }
        }
        else if (token->getType()==GCSLToken::T_Bridge) {
            GCSLWBridge* wr=new GCSLWBridge(this);
            this->addSubWrite(wr);

            if(!wr->compile(myReader,errOut)) {
                return false;
            }
        }
        else if (token->getType()==GCSLToken::T_Main) {
            GCSLWVSMain* wr=new GCSLWVSMain(this);
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

bool GCSLWVS::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    return GCSLWriter::makeVS(param,strOut,errOut);
}

bool GCSLWVS::makeFP(GCSLWriter::MakeParam &, QString &, GCSLError *)
{
    return true;
}

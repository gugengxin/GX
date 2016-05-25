#include "GCSLWFP.h"
#include "GCSLWHT.h"
#include "GCSLWBuffer.h"
#include "GCSLWTexture.h"
#include "GCSLWFPMain.h"

GCSLWFP::GCSLWFP(QObject *parent) : GCSLWriter(parent)
{

}

bool GCSLWFP::compile(GCSLTokenReader &reader, GCSLError *errOut)
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
        else if (token->getType()==GCSLToken::T_Buffer) {
            GCSLWBuffer* wr=new GCSLWBuffer(this);
            this->addSubWrite(wr);

            if(!wr->compile(myReader,errOut)) {
                return false;
            }
        }
        else if (token->getType()==GCSLToken::T_Texture) {
            GCSLWTexture* wr=new GCSLWTexture(this);
            this->addSubWrite(wr);

            if(!wr->compile(myReader,errOut)) {
                return false;
            }
        }
        else if (token->getType()==GCSLToken::T_Main) {
            GCSLWFPMain* wr=new GCSLWFPMain(this);
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

bool GCSLWFP::makeVS(GCSLWriter::MakeParam &, QString &, GCSLError *)
{
    return true;
}

bool GCSLWFP::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    return GCSLWriter::makeFP(param,strOut,errOut);
}

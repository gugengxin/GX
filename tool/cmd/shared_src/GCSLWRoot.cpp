#include "GCSLWRoot.h"
#include "GCSLWHT.h"
#include "GCSLWVS.h"
#include "GCSLWFP.h"


GCSLWRoot::GCSLWRoot(QObject* parent) :
    GCSLWriter(parent)
{

}


bool GCSLWRoot::compile(GCSLTokenReader& reader,GCSLError* errOut)
{
    while(true) {
        GCSLToken* token=reader.getToken();

        if(token->isHT()) {
            if(!GCSLWHT::compile(this,token,reader,errOut)) {
                return false;
            }
        }
        else if(token->getType()==GCSLToken::T_EOF) {
            break;
        }
        else if(token->getType()==GCSLToken::T_Vs) {
            GCSLWVS* wr=new GCSLWVS(this);
            this->addSubWrite(wr);
            if(!wr->compile(reader,errOut)) {
                return false;
            }
        }
        else if(token->getType()==GCSLToken::T_Fp) {
            GCSLWFP* wr=new GCSLWFP(this);
            this->addSubWrite(wr);
            if(!wr->compile(reader,errOut)) {
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

    //bridge add to fp
    GCSLWriter* wrBridge=NULL;
    for(int i=0;i<getSubWriteCount();i++) {
        GCSLWriter* wr=getSubWrites(i);
        if(wr->inherits("GCSLWVS")) {
            for(int j=0;j<wr->getSubWriteCount();j++) {
                GCSLWriter* wr0=wr->getSubWrites(j);
                if(wr0->inherits("GCSLWBridge")) {
                    wrBridge=wr0;
                    break;
                }
            }
            break;
        }
    }
    if(wrBridge) {
        for(int i=0;i<getSubWriteCount();i++) {
            GCSLWriter* wr=getSubWrites(i);
            if(wr->inherits("GCSLWFP")) {
                for(int j=0;j<wr->getSubWriteCount();j++) {
                    if(wr->getSubWrites(j)->inherits("GCSLWFPMain")) {
                        wr->insertSubWrites(j,wrBridge);
                        break;
                    }
                }
                break;
            }
        }
    }


    return true;
}

bool GCSLWRoot::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    if(param.slType==GCSLWriter::SLT_MSL) {
        strOut.append("#include <metal_stdlib>");
        strOut.append(param.strWarp);
        strOut.append("using namespace metal;");
        strOut.append(param.strWarp);
    }

    for(int i=0;i<getSubWriteCount();i++) {
        if(!getSubWrites(i)->makeVS(param,strOut,errOut)) {
            return false;
        }
    }
    return true;
}

bool GCSLWRoot::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    for(int i=0;i<getSubWriteCount();i++) {
        if(!getSubWrites(i)->makeFP(param,strOut,errOut)) {
            return false;
        }
    }

    return true;
}

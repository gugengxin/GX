#include "GCSLWRoot.h"
#include "GCSLWHT.h"
#include "GCSLWVS.h"
#include "GCSLWFP.h"


GCSLWRoot::GCSLWRoot(QObject* parent) :
    GCSLWriter(parent)
{

}


void GCSLWRoot::addMainWHTDef(GCSLWHTMDef *v)
{
    v->setParent(this);
    m_MainWHTDefs.append(v);
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
    return true;
}

bool GCSLWRoot::make(QString &strWarp, QString &vsOut, QString &fpOut, GCSLError *errOut)
{
    GCSLWriter::MakeParam mp(strWarp,0);
    for(int i=0;i<m_MainWHTDefs.length();i++) {
        if(!m_MainWHTDefs[i]->makeVS(mp,vsOut,errOut)) {
            return false;
        }
    }
    for(int i=0;i<getSubWriteCount();i++) {
        if(!getSubWrites(i)->makeVS(mp,vsOut,errOut)) {
            return false;
        }
    }

    mp.lineLevel=0;
    for(int i=0;i<m_MainWHTDefs.length();i++) {
        if(!m_MainWHTDefs[i]->makeFP(mp,fpOut,errOut)) {
            return false;
        }
    }
    for(int i=0;i<getSubWriteCount();i++) {
        if(!getSubWrites(i)->makeFP(mp,fpOut,errOut)) {
            return false;
        }
    }

    return true;
}

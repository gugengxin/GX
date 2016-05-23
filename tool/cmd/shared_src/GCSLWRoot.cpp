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
    return true;
}

bool GCSLWRoot::make(QString &strWarp, QString &strOut, GCSLError *errOut)
{
   if(!GCSLWriter::make(strWarp,strOut,errOut)) {
       return false;
   }

   return true;
}

void GCSLWRoot::addMainWHTDef(GCSLWHTMDef *v)
{
    v->setParent(this);
    m_MainWHTDefs.append(v);
}

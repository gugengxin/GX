#include "GCSLWRoot.h"
#include "GCSLWHT.h"


GCSLWRoot::GCSLWRoot(QObject* parent) :
    GCSLWriter(parent)
{

}

bool GCSLWRoot::compile(GCSLTokenReader& reader,GCSLError* errOut)
{
    while(true) {
        GCSLToken* token=reader.getToken();

        if(token->getType()==GCSLToken::T_EOF) {
            break;
        }
        else if(token->getType()==GCSLToken::T_HT_Def) {
            GCSLWHTDef* wr=new GCSLWHTDef(this);
            this->addSubWrite(wr);

            if(!wr->compile(reader,errOut)) {
                return false;
            }
        }
        else if(token->getType()==GCSLToken::T_HT_If) {
            GCSLWHTIf* wr=new GCSLWHTIf(this);
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

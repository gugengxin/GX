#include "GCSLWRoot.h"
#include "GCSLWHTDef.h"
#include "GCSLWHTIf.h"


GCSLWRoot::GCSLWRoot(QObject* parent) :
    GCSLWriter(parent)
{

}

bool GCSLWRoot::compile(GCSLTokenReader& reader,GCSLError* errOut)
{
    GCSLToken* token=reader.getToken();

    while(true) {
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

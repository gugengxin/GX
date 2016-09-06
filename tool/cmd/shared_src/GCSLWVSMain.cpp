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

bool GCSLWVSMain::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    switch (param.slType) {
    case SLT_GLSL:
    case SLT_GLSL_ES:
    {
        strAppendTab(strOut,param.lineLevel);
        strOut.append("void main()");
        strOut.append(param.strWarp);
        strAppendTab(strOut,param.lineLevel);
        strOut.append("{");
        strOut.append(param.strWarp);

        param.lineLevel++;
        if(!GCSLWriter::makeVS(param,strOut,errOut)) {
            return false;
        }
        param.lineLevel--;
        strAppendTab(strOut,param.lineLevel);
        strOut.append("}");
        strOut.append(param.strWarp);
    }
        break;
    case SLT_HLSL:
    {
        strAppendTab(strOut,param.lineLevel);
        strOut.append("PixelInputType main(VertexInputType layout)");
        strOut.append(param.strWarp);
        strAppendTab(strOut,param.lineLevel);
        strOut.append("{");
        strOut.append(param.strWarp);

        param.lineLevel++;

        strAppendTab(strOut,param.lineLevel);
        strOut.append("PixelInputType bridge;");
        strOut.append(param.strWarp);


        if(!GCSLWriter::makeVS(param,strOut,errOut)) {
            return false;
        }

        strAppendTab(strOut,param.lineLevel);
        strOut.append("return bridge;");
        strOut.append(param.strWarp);

        param.lineLevel--;
        strAppendTab(strOut,param.lineLevel);
        strOut.append("}");
        strOut.append(param.strWarp);
    }
        break;
    case SLT_MSL:
    {
        strAppendTab(strOut,param.lineLevel);
        strOut.append("vertex PixelInputType mainVS(VertexInputType layout [[stage_in]],constant UniformBufferVS& uniformBuf[[ buffer(1) ]])");
        strOut.append(param.strWarp);
        strAppendTab(strOut,param.lineLevel);
        strOut.append("{");
        strOut.append(param.strWarp);

        param.lineLevel++;

        strAppendTab(strOut,param.lineLevel);
        strOut.append("PixelInputType bridge;");
        strOut.append(param.strWarp);


        if(!GCSLWriter::makeVS(param,strOut,errOut)) {
            return false;
        }

        strAppendTab(strOut,param.lineLevel);
        strOut.append("return bridge;");
        strOut.append(param.strWarp);

        param.lineLevel--;
        strAppendTab(strOut,param.lineLevel);
        strOut.append("}");
        strOut.append(param.strWarp);
    }
        break;
    default:
        return false;
    }
    return true;
}

bool GCSLWVSMain::makeFP(GCSLWriter::MakeParam &, QString &, GCSLError *)
{
    return true;
}

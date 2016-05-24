#include "GCSLWHT.h"


bool GCSLWHT::compile(GCSLWriter *parent, GCSLToken *token, GCSLTokenReader &reader, GCSLError *errOut)
{
    if(token->getType()==GCSLToken::T_HT_MDef) {
        GCSLWHTMDef* wr=new GCSLWHTMDef(parent);
        parent->addMainWHTDef(wr);

        return wr->compile(reader,errOut);
    }
    else if(token->getType()==GCSLToken::T_HT_Def) {
        GCSLWHTDef* wr=new GCSLWHTDef(parent);
        parent->addSubWrite(wr);

        return wr->compile(reader,errOut);
    }
    else if(token->getType()==GCSLToken::T_HT_If) {
        GCSLWHTIf* wr=new GCSLWHTIf(parent);
        parent->addSubWrite(wr);

        return wr->compile(reader,errOut);
    }
    else if(token->getType()==GCSLToken::T_HT_Elif) {
        GCSLWHTElif* wr=new GCSLWHTElif(parent);
        parent->addSubWrite(wr);

        return wr->compile(reader,errOut);
    }
    else if(token->getType()==GCSLToken::T_HT_Else) {
        GCSLWHTElse* wr=new GCSLWHTElse(parent);
        parent->addSubWrite(wr);

        return wr->compile(reader,errOut);
    }
    else if(token->getType()==GCSLToken::T_HT_End) {
        GCSLWHTEnd* wr=new GCSLWHTEnd(parent);
        parent->addSubWrite(wr);

        return wr->compile(reader,errOut);
    }

    return false;
}


GCSLWHTMDef::GCSLWHTMDef(QObject *parent) :
    GCSLWriter(parent)
{
}

bool GCSLWHTMDef::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    GCSLToken* token=reader.getToken();

    if(token->getType()==GCSLToken::T_Variable) {
        m_Name=token->getID();
    }
    else {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnexceptToken);
            errOut->setRC(token);
        }
        return false;
    }

    //    token=reader.getToken();
    //    if(token->getType()==GCSLToken::T_Integer) {
    //        m_Index=token->getID().toInt();
    //    }

    if( !reader.currentIsWarpped() ) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NeedWarp);
            errOut->setRC(token);
        }
        return false;
    }

    return true;
}

bool GCSLWHTMDef::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *)
{
    strAppendTab(strOut,param.lineLevel);
    strOut.append("#define ");
    strOut.append(m_Name);
    strOut.append(param.strWarp);

    return true;
}

bool GCSLWHTMDef::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    return makeVS(param,strOut,errOut);
}







GCSLWHTDef::GCSLWHTDef(QObject *parent) :
    GCSLWriter(parent)
{

}

bool GCSLWHTDef::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    GCSLToken* token=reader.getToken();

    if(token->getType()==GCSLToken::T_Variable) {
        m_Name=token->getID();
    }
    else {
        if(errOut) {
            errOut->setCode(GCSLError::C_UnexceptToken);
            errOut->setRC(token);
        }
        return false;
    }

    if( !reader.currentIsWarpped() ) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NeedWarp);
            errOut->setRC(token);
        }
        return false;
    }

    return true;
}

bool GCSLWHTDef::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *)
{
    strAppendTab(strOut,param.lineLevel);
    strOut.append("#define ");
    strOut.append(m_Name);
    strOut.append(param.strWarp);

    return true;
}

bool GCSLWHTDef::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    return makeVS(param,strOut,errOut);
}





GCSLWHTIf::GCSLWHTIf(QObject *parent) :
    GCSLWriter(parent)
{

}

bool GCSLWHTIf::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    if(reader.currentIsWarpped()) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NotNeedWarp);
            errOut->setRC(reader);
        }
        return false;
    }

    GCSLToken::Type types[]={
        GCSLToken::T_Variable,
        GCSLToken::T_S_Brackets_L,
        GCSLToken::T_S_Brackets_R,
        GCSLToken::T_And,
        GCSLToken::T_Or,
        GCSLToken::T_Not,
    };

    while(true) {

        GCSLToken* token=reader.getToken();

        int i=0;
        for(;i<(int)(sizeof(types)/sizeof(types[0]));i++) {
            if(token->getType()==types[i]) {
                m_Conds.append(token);

                if(reader.currentIsWarpped()) {
                    return true;
                }
                break;
            }
        }

        if(i>=(int)(sizeof(types)/sizeof(types[0]))) {
            if(errOut) {
                errOut->setCode(GCSLError::C_UnexceptToken);
                errOut->setRC(token);
            }
            return false;
        }
    }
    return true;
}

bool GCSLWHTIf::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *)
{
    strAppendTab(strOut,param.lineLevel);
    strOut.append("#if");

    for(int i=0;i<m_Conds.length();i++) {
        strOut.append(" ");
        if(m_Conds[i]->getType()==GCSLToken::T_Variable) {
            strOut+=QString("defined(%1)").arg(m_Conds[i]->getID());
        }
        else {
            strOut.append(m_Conds[i]->getID());
        }
    }

    strOut.append(param.strWarp);

    return true;
}

bool GCSLWHTIf::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    return makeVS(param,strOut,errOut);
}






GCSLWHTElif::GCSLWHTElif(QObject *parent) :
    GCSLWriter(parent)
{

}

bool GCSLWHTElif::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    if(reader.currentIsWarpped()) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NotNeedWarp);
            errOut->setRC(reader);
        }
        return false;
    }

    GCSLToken::Type types[]={
        GCSLToken::T_Variable,
        GCSLToken::T_S_Brackets_L,
        GCSLToken::T_S_Brackets_R,
        GCSLToken::T_And,
        GCSLToken::T_Or,
        GCSLToken::T_Not,
    };

    while(true) {

        GCSLToken* token=reader.getToken();

        int i=0;
        for(;i<(int)(sizeof(types)/sizeof(types[0]));i++) {
            if(token->getType()==types[i]) {
                m_Conds.append(token);

                if(reader.currentIsWarpped()) {
                    return true;
                }
                break;
            }
        }

        if(i>=(int)(sizeof(types)/sizeof(types[0]))) {
            if(errOut) {
                errOut->setCode(GCSLError::C_UnexceptToken);
                errOut->setRC(token);
            }
            return false;
        }
    }
    return true;
}

bool GCSLWHTElif::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *)
{
    strAppendTab(strOut,param.lineLevel);
    strOut.append("#elif");

    for(int i=0;i<m_Conds.length();i++) {
        strOut.append(" ");
        if(m_Conds[i]->getType()==GCSLToken::T_Variable) {
            strOut+=QString("defined(%1)").arg(m_Conds[i]->getID());
        }
        else {
            strOut.append(m_Conds[i]->getID());
        }
    }

    strOut.append(param.strWarp);

    return true;
}

bool GCSLWHTElif::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    return makeVS(param,strOut,errOut);
}




GCSLWHTElse::GCSLWHTElse(QObject *parent) :
    GCSLWriter(parent)
{

}

bool GCSLWHTElse::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    if(!reader.currentIsWarpped()) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NeedWarp);
            errOut->setRC(reader);
        }
        return false;
    }
    return true;
}

bool GCSLWHTElse::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *)
{
    strAppendTab(strOut,param.lineLevel);
    strOut.append("#else");
    strOut.append(param.strWarp);

    return true;
}

bool GCSLWHTElse::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    return makeVS(param,strOut,errOut);
}




GCSLWHTEnd::GCSLWHTEnd(QObject *parent) :
    GCSLWriter(parent)
{

}

bool GCSLWHTEnd::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    if(!reader.currentIsWarpped()) {
        if(errOut) {
            errOut->setCode(GCSLError::C_NeedWarp);
            errOut->setRC(reader);
        }
        return false;
    }
    return true;
}

bool GCSLWHTEnd::makeVS(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *)
{
    strAppendTab(strOut,param.lineLevel);
    strOut.append("#endif");
    strOut.append(param.strWarp);

    return true;
}

bool GCSLWHTEnd::makeFP(GCSLWriter::MakeParam &param, QString &strOut, GCSLError *errOut)
{
    return makeVS(param,strOut,errOut);
}





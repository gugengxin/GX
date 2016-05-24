#include "GCSLTokenReader.h"

GCSLTokenReader::GCSLTokenReader(QObject *parent) : QObject(parent)
{
    m_Index=0;
}

GCSLTokenReader::GCSLTokenReader(QList<GCSLToken *>& tlist, QObject *parent) : QObject(parent)
{
    m_Tokens.append(tlist);
    m_Index=0;
}

GCSLToken *GCSLTokenReader::getToken()
{
    if(m_Index>=m_Tokens.length()) {
        return NULL;
    }
    return m_Tokens[m_Index++];
}

void GCSLTokenReader::ungetToken()
{
    m_Index--;
}

bool GCSLTokenReader::currentIsWarpped()
{
    return  m_Index>=m_Tokens.length() || (m_Index>0 && m_Tokens[m_Index]->getRow() > m_Tokens[m_Index-1]->getRow());
}

//bool GCSLTokenReader::nextIsWarpped()
//{
//    return m_Index>=0 && m_Index<m_Tokens.length()-1 && m_Tokens[m_Index]->getRow() < m_Tokens[m_Index+1]->getRow();
//}

int GCSLTokenReader::getRow()
{
    if(m_Tokens.length()<=0) {
        return 0;
    }

    if(m_Index<0) {
        return m_Tokens[0]->getRow();
    }
    else if(m_Index>=m_Tokens.length()) {
        return m_Tokens[m_Tokens.length()-1]->getRow();
    }
    return m_Tokens[m_Index]->getRow();
}

int GCSLTokenReader::getColumn()
{
    if(m_Tokens.length()<=0) {
        return -1;
    }
    if(m_Index<0) {
        return m_Tokens[0]->getColumn();
    }
    else if(m_Index>=m_Tokens.length()) {
        return m_Tokens[m_Tokens.length()-1]->getColumn();
    }
    return m_Tokens[m_Index]->getColumn();
}

bool GCSLTokenReader::addTokensToBBR(GCSLTokenReader &reader)
{
    int lvBB=0;
    while (true) {
        GCSLToken* token=reader.getToken();
        if(!token || token->getType()==GCSLToken::T_EOF) {
            return false;
        }
        else if(token->getType()==GCSLToken::T_B_Brackets_L) {
            lvBB++;
        }
        else if(token->getType()==GCSLToken::T_B_Brackets_R) {
            if(lvBB<=0) {
                break;
            }
            else {
                lvBB--;
            }
        }
        m_Tokens.append(token);
    }
    return true;
}

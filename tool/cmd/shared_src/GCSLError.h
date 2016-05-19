#ifndef GCSLERROR_H
#define GCSLERROR_H

#include <QObject>
#include "GCSLReader.h"
#include "GCSLToken.h"

class GCSLError : public QObject
{
    Q_OBJECT
public:
    typedef enum _Code {
        C_None,
        C_ReadFile,
        C_UnknownChar,
        C_UnsupportToken,
        C_UnexceptToken,
        C_NeedWarp,
    } Code;

public:
    explicit GCSLError(QObject *parent = 0);

    void setCode(Code v) {
        m_Code=v;
    }
    void setRC(int row,int col) {
        m_Row=row;
        m_Column=col;
    }
    void setRC(GCSLReader& reader) {
        m_Row=reader.getRow();
        m_Column=reader.getColumn();
    }
    void setRC(GCSLToken* token) {
        m_Row=token->getRow();
        m_Column=token->getColumn();
    }

    void setMessage(QString& v) {
        m_Message=v;
    }
    void setMessage(QChar& ch) {
        m_Message=ch;
    }

private:
    Code    m_Code;
    int     m_Row;
    int     m_Column;
    QString m_Message;
};

#endif // GCSLERROR_H

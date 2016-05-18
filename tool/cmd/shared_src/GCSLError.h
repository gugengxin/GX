#ifndef GCSLERROR_H
#define GCSLERROR_H

#include <QObject>

class GCSLError : public QObject
{
    friend class GCSL;
    Q_OBJECT
public:
    typedef enum _Code {
        C_None,
        C_ReadFile,
        C_UnknownChar,
    } Code;

public:
    explicit GCSLError(QObject *parent = 0);

signals:

public slots:

private:
    Code    m_Code;
    int     m_Row;
    int     m_Column;
    QString m_Message;
};

#endif // GCSLERROR_H

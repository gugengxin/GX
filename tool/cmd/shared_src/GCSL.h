#ifndef GCSL_H
#define GCSL_H

#include <QObject>
#include <QMap>

#include "GCSLReader.h"
#include "GCSLToken.h"
#include "GCSLWord.h"
#include "GCSLError.h"
#include "GCSLWRoot.h"

class GCSL : public QObject
{
    Q_OBJECT
public:
    explicit GCSL(QObject *parent = 0);
    ~GCSL();

    bool compile(const QString& filePath,const QString& guessEncode="UTF-8", GCSLError* errOut=NULL);
    bool make(QString& strWarp,QString& vsOut,QString& fpOut,GCSLError* errOut=NULL);
    void clean();
private:
    void initWords();
private:
    void skip_white_space(QChar& ch, GCSLReader& reader);
    void parse_comment0(QChar& ch, GCSLReader& reader);
    void parse_comment1(QChar& ch, GCSLReader& reader);
    void preprocess(QChar& ch, GCSLReader& reader);
    void parse_ID(QChar& ch, GCSLReader& reader, QString &strOut);
    void parse_number(QChar& ch, GCSLReader& reader, QString &strOut);
    bool getToken(QChar &ch, GCSLReader& reader, GCSLToken* tokenOut, GCSLError* errOut);
    bool translateToTokens(GCSLError* errOut);
private:

signals:

public slots:

private:
    QString                 m_Text;
    QMap<QString,GCSLWord*> m_WordMap;
    QList<GCSLToken*>       m_Tokens;
    GCSLWRoot*              m_Writer;
};

#endif // GCSL_H

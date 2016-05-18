#ifndef GCSL_H
#define GCSL_H

#include <QObject>
#include <QList>

#include "GCSLToken.h"
#include "GCSLError.h"

class GCSL : public QObject
{
    Q_OBJECT
public:
    class TextInputStream {
    public:
        TextInputStream(QString* pText) {
            m_Text=pText;
            m_CurIdx=0;
            m_Row=0;
            m_Column=-1;
        }

        QChar getChar() {
            if(m_CurIdx>=m_Text->length()) {
                return '\0';
            }
            return m_Text->at(m_CurIdx++);
        }
        void ungetChar() {
            m_CurIdx--;
            m_Column--;
            if(m_Column<0) {
                m_Row--;
            }
        }

        void wrap() {
            m_Row++;
            m_Column=-1;
        }

        int getRow() {
            return m_Row;
        }
        int getColumn() {
            return m_Column;
        }

    private:
        QString* m_Text;
        int m_CurIdx;
        int m_Row;
        int m_Column;
    };

public:
    explicit GCSL(QObject *parent = 0);

    bool compile(const QString& filePath,const QString& guessEncode="UTF-8", GCSLError* errOut=NULL);
private:
    bool translateToTokens(TextInputStream& sem,GCSLError* errOut=NULL);
signals:

public slots:

private:
    QString m_Text;
    QList<GCSLToken*> m_Tokens;
};

#endif // GCSL_H

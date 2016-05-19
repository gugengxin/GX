#ifndef GCSLREADER_H
#define GCSLREADER_H

#include <QObject>

class GCSLReader : public QObject
{
    Q_OBJECT
public:
    GCSLReader(QString* pText,QObject* parent=NULL);

    QChar getChar();
    void ungetChar();

    void wrap();

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

#endif // GCSLREADER_H

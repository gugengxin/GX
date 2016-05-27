#ifndef GCSLREADER_H
#define GCSLREADER_H

#include <QObject>
#include <QList>

class GCSLReader : public QObject
{
    Q_OBJECT
public:
    GCSLReader(QString* pText,QObject* parent=NULL);

    QChar getChar();
    void ungetChar();
    void ungetChar(int num);

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
    QList<int> m_ColList;
};

#endif // GCSLREADER_H

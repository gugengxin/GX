#ifndef GCTEXTEDITOR_H
#define GCTEXTEDITOR_H

#include <QObject>
#include <QTextCodec>

class GCTextEditor : public QObject
{
    Q_OBJECT
public:
    static const char BOM8[];
    static const int BOM8Bytes;
public:
    explicit GCTextEditor(QObject *parent = 0);
    ~GCTextEditor();


    void setText(const QString& v) {
        m_Text=v;
    }

    const QString& getText() {
        return m_Text;
    }

    bool readFile(const QString& filePath,const QString& guessEncode);
    bool writeFile(const QString& filePath,const QString& encode="",bool hasBOM8=false);

    //fromStrSuf!="" 代表替换 fromStr-fromStrSuf 之间的字符串
    //toStrPS=="\" || toStrPS=="/" 代表替换的是路径，即会先把toStr替换出现的路径分隔符为toStrPS,然后查找路径字符串匹配fromStr和fromStrSuf，最后进行替换
    int replace(const QString& fromStr,const QString& toStr,
                 Qt::CaseSensitivity fromCs=Qt::CaseSensitive,
                 const QString& fromStrSuf="",Qt::CaseSensitivity fromCsSuf=Qt::CaseSensitive,
                 const QString& toStrPS="",
                 int idxStart=0,int idxCount=0);
    int fileList(const QString& signPre, const QString& signSuf,
                 const QString& dir, const QList<QString>& extensions,
                 const QString &strPre, const QString &strSuf,
                 const QList<QString>& filters,const QString &strFPre, const QString &strFSuf,
                 const QList<QString>& ignores);


signals:

public slots:


private:
    bool    m_TextBOM8;
    QString m_Text;
    QTextCodec* m_TextCodec;
};

#endif // GCTEXTEDITOR_H

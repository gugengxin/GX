#include "GCTextEditor.h"
#include <QFile>
#include <QFileInfoList>
#include <QDir>


const char GCTextEditor::BOM8[]={(const char)0xEF,(const char)0xBB,(const char)0xBF};
const int GCTextEditor::BOM8Bytes=(int)sizeof(BOM8);


GCTextEditor::GCTextEditor(QObject *parent) : QObject(parent)
{
    m_TextCodec=NULL;
    m_TextBOM8=false;
}

GCTextEditor::~GCTextEditor()
{

}

bool GCTextEditor::readFile(const QString &filePath, const QString &guessEncode)
{
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray data=file.readAll();

        if(data.size()>=BOM8Bytes && memcmp(BOM8,data.data(),BOM8Bytes)==0) {
            m_TextBOM8=true;
            m_TextCodec=QTextCodec::codecForName("UTF-8");
            if(m_TextCodec) {
                m_Text=m_TextCodec->toUnicode(data.data()+BOM8Bytes,data.size()-BOM8Bytes);
                return true;
            }
        }
        else {
            m_TextBOM8=false;
            m_TextCodec=QTextCodec::codecForName(guessEncode.toUtf8());
            if(m_TextCodec) {
                m_Text=m_TextCodec->toUnicode(data);
                return true;
            }
        }
    }
    return false;
}

bool GCTextEditor::writeFile(const QString &filePath, const QString &encode, bool hasBOM8)
{
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly)) {

        QTextCodec* codec;
        if(encode.size()<=0) {
            codec=m_TextCodec;
            hasBOM8=m_TextBOM8;
        }
        else {
            codec=QTextCodec::codecForName(encode.toUtf8());
            if(encode.compare("UTF-8",Qt::CaseInsensitive)!=0) {
                hasBOM8=false;
            }
        }

        if(codec) {
            if(hasBOM8) {
                if(file.write(BOM8,BOM8Bytes)!=BOM8Bytes) {
                    return false;
                }
            }
            QByteArray data=codec->fromUnicode(m_Text);
            if(file.write(data)!=data.size()) {
                return false;
            }
            return true;
        }
    }
    return false;
}

static int _ReplaceString(QString& str,const QString& strFrom,Qt::CaseSensitivity fromCs,const QString& strTo)
{
    if(strFrom.size()>0 && strTo.size()>0) {
        int idx=0;
        int i=0;
        while(true) {
            i=str.indexOf(strFrom,i,fromCs);
            if(i>=0) {
                idx++;
                str.replace(i,strFrom.size(),strTo);
                i+=strTo.size();
            }
            else {
                return idx;
            }
        }
    }
    return 0;
}

static int _FindPathString(const QString& str,const QString& strPath,int from)
{
    QString strTemp=strPath;
    _ReplaceString(strTemp,QString("\\"),Qt::CaseSensitive,QString("/"));
    int res=str.indexOf(strTemp,from,Qt::CaseInsensitive);
    if(res>=0) {
        return res;
    }
    strTemp=strPath;
    _ReplaceString(strTemp,QString("/"),Qt::CaseSensitive,QString("\\"));
    res=str.indexOf(strTemp,from,Qt::CaseInsensitive);
    return res;
}

static QFileInfoList _GetFileList(QString path)
{
    QFileInfoList res;

    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::Dirs | QDir::NoDotAndDotDot,QDir::Name);

    for(int i = 0; i < file_list.size(); i++)
    {
        QFileInfo fi = file_list.at(i);
        if(fi.isDir()) {
            QFileInfoList child_file_list = _GetFileList(fi.absoluteFilePath());
            res.append(child_file_list);
        }
        else {
            res.append(fi);
        }
    }

    return res;
}



int GCTextEditor::replace(const QString &fromStr, const QString &toStr, Qt::CaseSensitivity fromCs, const QString &fromStrSuf, Qt::CaseSensitivity fromCsSuf, const QString &toStrPS, int idxStart, int idxCount)
{
    if(fromStr.size()>0 && toStr.size()>0) {

        QString strTo=toStr;
        bool strToIsPath=false;
        if(toStrPS=="\\" || toStrPS=="/") {
            _ReplaceString(strTo,QString("\\"),Qt::CaseSensitive,toStrPS);
            _ReplaceString(strTo,QString("/"),Qt::CaseSensitive,toStrPS);
            strToIsPath=true;
        }


        int i=0;
        int idx=-1;
        int res=0;
        while (true) {
            if(strToIsPath) {
                i=_FindPathString(m_Text,fromStr,i);
            }
            else {
                i=m_Text.indexOf(fromStr,i,fromCs);
            }
            if(i>=0) {
                if(fromStrSuf.size()<=0) {
                    idx++;
                    if (idx >= idxStart && (idxCount <= 0 || idx<idxStart + idxCount)) {
                        m_Text.replace(i,fromStr.size(),strTo);
                        res++;
                        if(idxCount>0 && (idx>=idxStart + idxCount)) {
                            break;
                        }
                        i+=strTo.size();
                    }
                    else {
                        i+=fromStr.size();
                    }
                }
                else {
                    i+=fromStr.size();
                    int start=i;
                    if(strToIsPath) {
                        i=_FindPathString(m_Text,fromStrSuf,i);
                    }
                    else {
                        i=m_Text.indexOf(fromStrSuf,i,fromCsSuf);
                    }
                    if(i>=0) {
                        idx++;
                        if (idx >= idxStart && (idxCount <= 0 || idx<idxStart + idxCount)) {
                            int len=i-start;
                            m_Text.replace(start,len,strTo);
                            res++;
                            if(idxCount>0 && (idx>=idxStart + idxCount)) {
                                break;
                            }
                            i = i - len + strTo.size() + fromStrSuf.size();
                        }
                        else {
                            i+=fromStrSuf.size();
                        }
                    }
                    else {
                        break;
                    }
                }
            }
            else {
                break;
            }
        }
        return res;
    }
    return 0;
}

int GCTextEditor::fileList(const QString& signPre,const QString& signSuf,
                           const QString& dir,const QList<QString>& extensions,
                           const QString& strPre,const QString& strSuf,
                           const QList<QString>& filters,const QString &strFPre, const QString &strFSuf,
                           const QList<QString>& ignores)
{
    QString fileListString("\n");
    QFileInfoList fileList=_GetFileList(dir);
    for(int i=0;i<fileList.size();i++) {
        QString path=fileList[i].absoluteFilePath();

        bool bAdd=false;
        for(int j=0;j<extensions.size();j++) {
            if(path.endsWith(extensions[j],Qt::CaseInsensitive)) {
                bAdd=true;
                break;
            }
        }
        if(bAdd) {
            for(int j=0;j<ignores.size();j++) {
                if(path.endsWith(ignores[j],Qt::CaseInsensitive)) {
                    bAdd=false;
                    break;
                }
            }
        }
        if(bAdd) {
            bool bFiltered=false;
            for(int j=0;j<filters.size();j++) {
                if(path.endsWith(filters[j],Qt::CaseInsensitive)) {
                    bFiltered=true;
                    break;
                }
            }

            if(bFiltered) {
                fileListString.append(strFPre);
                fileListString.append(path.right(path.length()-dir.length()));
                fileListString.append(strFSuf);
            }
            else {
                fileListString.append(strPre);
                fileListString.append(path.right(path.length()-dir.length()));
                fileListString.append(strSuf);
            }
        }
    }

    return replace(signPre,fileListString,Qt::CaseSensitive,signSuf,Qt::CaseSensitive);
}



#include <QCoreApplication>
#include <QTextStream>
#include <QTextCodec>
#include "GCSL.h"
#include <QFile>
#include "GCTextEditor.h"

int main(int argc, char *argv[])
{
    QList<QString> argList;
    for(int i=0;i<argc;i++) {
        argList.append(QString((const char*)argv[i]));
    }
    /*
    argList.append("-i");
    argList.append("/Users/GuGengxin/Desktop/gxsl_test.txt");
    argList.append("-ie");
    argList.append("UTF-8");
    argList.append("-o");
    argList.append("/Users/GuGengxin/Desktop/gxsl_test.gxsl");
    //*/

    //QTextStream cin(stdin, QIODevice::ReadOnly);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QTextStream cerr(stderr, QIODevice::WriteOnly);



    if(argList.size()<=1) {
        QString cmd=argList[0];
        int idx=cmd.lastIndexOf("/");
        if(idx<0) {
            idx=cmd.lastIndexOf("\\");
        }
        if(idx>=0) {
            cmd=cmd.right(cmd.length()-idx-1);
        }
        cout<< "Help:\n";
        cout<< cmd;
        cout<< " -i (file path) [-ie (file guess encoding,default UTF-8)]\n";
        cout<< " -o (out file)\n";

        QList<QByteArray> acs=QTextCodec::availableCodecs();
        if(acs.size()>0) {
            cout << "available encoding:\n";
            for(int i=0;i<acs.size();i++) {
                cout<<"\t" << acs[i];
                if(i%5==4) {
                    cout <<"\n";
                }
            }
        }
        cout<<endl;
    }
    else {
        bool err=false;
        QString in,ine="UTF-8";
        QString out;
        for(int i=1;i+1<argList.size();i+=2) {
            QString& str=argList[i];
            if(str=="-i") {
                in=argList[i+1];
            }
            else if(str=="-ie") {
                ine=argList[i+1];
            }
            else if(str=="-o") {
                out=argList[i+1];
            }
            else {
                cerr<< "unknown option \"" << str << "\"" <<endl;
                err=true;
                break;
            }
        }
        if(!err) {

            QString src;
            {
                QString srcTemp;
                QFile file(in);
                if(file.open(QIODevice::ReadOnly)) {
                    QByteArray data=file.readAll();

                    if(data.size()>=GCTextEditor::BOM8Bytes && memcmp(GCTextEditor::BOM8,data.data(),GCTextEditor::BOM8Bytes)==0) {
                        QTextCodec* codec=QTextCodec::codecForName("UTF-8");
                        if(codec) {
                            srcTemp=codec->toUnicode(data.data()+GCTextEditor::BOM8Bytes,data.size()-GCTextEditor::BOM8Bytes);
                        }
                    }
                    else {
                        QTextCodec* codec=QTextCodec::codecForName(ine.toUtf8());
                        if(codec) {
                            srcTemp=codec->toUnicode(data);
                        }
                    }
                }
                if(srcTemp.length()>0) {
                    bool find=false;
                    QString s("/*//GX_SL"),e("*///GX_SL");
                    int idxS=srcTemp.indexOf(s);
                    if(idxS>=0) {
                        int idxE=srcTemp.indexOf(e,idxS+s.length());
                        if(idxE>=0) {
                            src=srcTemp.mid(idxS+s.length(),idxE-(idxS+s.length()));
                            find=true;
                        }
                    }
                    if(!find) {
                        src=srcTemp;
                    }
                }
                else {
                    cerr<< "src nothing" <<endl;
                    err=true;
                }
            }

            if(!err) {
                GCSL worker;
                GCSLError error;
                if(worker.compile(src,&error)) {

                    QString outStr;

                    for(int i=0;i<4;i++) {
                        if(i==0) {
                            outStr.append("#if defined(GX_OPENGL) && !defined(GX_OPENGL_ES)\n");
                        }
                        else if(i==1) {
                            outStr.append("#if defined(GX_OPENGL) && defined(GX_OPENGL_ES)\n");
                        }
                        else if(i==2) {
                            outStr.append("#if defined(GX_DIRECTX)\n");
                        }
                        else if(i==3) {
                            outStr.append("#if defined(GX_METAL)\n");
                        }

                        QString vsStr,fpStr;
                        if(worker.make((GCSLWriter::SLType)i," \\n\\\n",vsStr,fpStr,&error)) {
                            outStr.append("static const gchar* g_SrcVS=\\\n\"");
                            outStr.append(vsStr);
                            outStr.append("\";\n");
                            //outStr.append(QString("const gint g_SrcVSLen=%1;\n").arg(vsStr.toUtf8().length()));

                            outStr.append("static const gchar* g_SrcFP=\\\n\"");
                            outStr.append(fpStr);
                            outStr.append("\";\n");
                            //outStr.append(QString("const gint g_SrcFPLen=%1;\n").arg(fpStr.toUtf8().length()));

                            outStr.append("#endif\n");

                            QFile file(out);
                            if(file.open(QIODevice::WriteOnly)) {
                                QTextCodec* codec=QTextCodec::codecForName("UTF-8");
                                QByteArray data=codec->fromUnicode(outStr);
                                if(file.write(data)!=data.size()) {
                                    cerr<< "write file error" <<endl;
                                }
                            }
                            else {
                                cerr<< "can't open out file" <<endl;
                            }
                        }
                        else {
                            cerr<< "make error: " << error.getCode() << "(" << error.getRow() << "," << error.getColumn() <<")" <<endl;
                        }
                    }
                }
                else {
                    cerr<< "compile error: " << error.getCode() << "(" << error.getRow() << "," << error.getColumn() <<")" <<endl;
                }
            }
        }
        else {
            cerr<< "do nothing" <<endl;
        }
    }


    return 0;
}

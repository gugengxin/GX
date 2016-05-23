#include <QCoreApplication>
#include <QTextStream>
#include <QTextCodec>
#include "GCSL.h"

int main(int argc, char *argv[])
{
    QList<QString> argList;
    for(int i=0;i<argc;i++) {
        argList.append(QString((const char*)argv[i]));
    }
    //*
    argList.append("-i");
    argList.append("E:\\gxsl_test.txt");
    argList.append("-ie");
    argList.append("UTF-8");
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
        for(int i=1;i+1<argList.size();i+=2) {
            QString& str=argList[i];
            if(str=="-i") {
                in=argList[i+1];
            }
            else if(str=="-ie") {
                ine=argList[i+1];
            }
            else {
                cerr<< "unknown option \"" << str << "\"" <<endl;
                err=true;
                break;
            }
        }
        if(!err) {
            GCSL worker;
            GCSLError error;
            if(!worker.compile(in,ine,&error)) {
                cerr<< "error: " << error.getCode() <<endl;
            }
        }
        else {
            cerr<< "do nothing" <<endl;
        }
    }


    return 0;
}

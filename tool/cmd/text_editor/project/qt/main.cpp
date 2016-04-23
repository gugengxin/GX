#include <QCoreApplication>
#include <QTextStream>
#include "GCTextEditor.h"

#define M_CS_TO_QTCS(cs) ((cs)==0? Qt::CaseSensitive : Qt::CaseInsensitive )

int main(int argc, char *argv[])
{
    QList<QString> argList;
    for(int i=0;i<argc;i++) {
        argList.append(QString((const char*)argv[i]));
    }

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

        cout<< " [-rs (source string)] [-rscs 0=CaseSensitive 1=CaseInsensitive]\n";
        cout<< " [-rss (source suffix string)] [-rsscs 0=CaseSensitive 1=CaseInsensitive]\n";
        cout<< " [-rsp \"\\\" or \"/\" source string is path]\n";
        cout<< " [-rd (destination string)]\n";
        cout<< " [-ris (index start,default 0)] [-ric (index count,default 0:all)]\n";

        cout<< " -o (new file path) [-oe new file encoding,none will use old] [-oebom8 1/0 add (or not) bom8]\n";

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
        QString rs;int rscs=0;
        QString rss,rsp;int rsscs=0;
        QString rd;
        int ris=0,ric=0;
        QString out,oute;int outbom8=0;
        for(int i=1;i+1<argList.size();i+=2) {
            QString& str=argList[i];
            if(str=="-i") {
                in=argList[i+1];
            }
            else if(str=="-ie") {
                ine=argList[i+1];
            }
            else if(str=="-rs") {
                rs=argList[i+1];
            }
            else if(str=="-rscs") {
                rscs=argList[i+1].toInt();
            }
            else if(str=="-rss") {
                rss=argList[i+1];
            }
            else if(str=="-rsscs") {
                rsscs=argList[i+1].toInt();
            }
            else if(str=="-rsp") {
                rsp=argList[i+1];
            }
            else if(str=="-ris") {
                ris=argList[i+1].toInt();
            }
            else if(str=="-ric") {
                ric=argList[i+1].toInt();
            }
            else if(str=="-rd") {
                rd=argList[i+1];
            }
            else if(str=="-o") {
                out=argList[i+1];
            }
            else if(str=="-oe") {
                oute=argList[i+1];
            }
            else if(str=="-oebom8") {
                outbom8=argList[i+1].toInt();
            }
            else {
                cerr<< "unknown option \"" << str << "\"" <<endl;
                err=true;
                break;
            }
        }
        if(!err) {
            GCTextEditor worker;
            if(in.length()>0) {
                if(!worker.readFile(in,ine)) {
                    cerr<< "Read Fail:" << in <<endl;
                    err=true;
                }
            }
            else {
                cerr<< "no -i" <<endl;
                err=true;
            }
            if(out.length()<=0) {
                cerr<< "no -o" <<endl;
                err=true;
            }

            bool doThings=false;
            if(!err) {
                if(rs.length()>0 && rd.length()>0) {
                    doThings=true;

                    if(!worker.replace(rs,rd,M_CS_TO_QTCS(rscs),rss,M_CS_TO_QTCS(rsscs),rsp,ris,ric)) {
                        cerr<< "Replace Fail!" <<endl;
                        err=true;
                    }
                }
            }

            if(!err && !doThings) {
                //do other thing
            }

            if(!err) {
                if(!worker.writeFile(out,oute,outbom8!=0)) {
                    cerr<< "Write Fail:" << out <<endl;
                    err=true;
                }
            }
        }
        else {
            cerr<< "do nothing" <<endl;
        }
    }
    return 0;
}

#include <QCoreApplication>
#include <QTextStream>
#include "GCTextEditor.h"

#define M_CS_TO_QTCS(cs) ((cs)==0? Qt::CaseSensitive : Qt::CaseInsensitive )




int main(int argc, char *argv[])
{
    QList<QString> argList;
    for(int i=0;i<argc;i++) {
        GCTextEditor te;
        te.setText(QString((const char*)argv[i]));
//#if defined(Q_OS_OSX)
        te.replace(QString("\\n"),QString("\n"));
        te.replace(QString("\\t"),QString("\t"));
//#endif
        argList.append(te.getText());
    }
    /*
    argList.append("-i");
    argList.append("C:\\Users\\GuGengxin\\Desktop\\Test.txt");
    argList.append("-ie");
    argList.append("UTF-8");
    argList.append("-rs");
    argList.append("___A/B/C____");
    argList.append("-rss");
    argList.append("__A\\A\\A__");
    argList.append("-rd");
    argList.append("___D/E/F____");
    argList.append("-rsp");
    argList.append("\\");

    argList.append("-ris");
    argList.append("0");
    argList.append("-ric");
    argList.append("0");

    argList.append("-o");
    argList.append("C:\\Users\\GuGengxin\\Desktop\\TestO.txt");
    argList.append("-oe");
    argList.append("UTF-8");
    argList.append("-oebom8");
    argList.append("1");
    //*/
    /*
    argList.append("-i");
    argList.append("/Users/GuGengxin/Desktop/GX.pro");
    argList.append("-o");
    argList.append("/Users/GuGengxin/Desktop/GXTemp.pro");

    argList.append("-fp");
    argList.append("#__START__\n");

    argList.append("-fs");
    argList.append("#__END__");

    argList.append("-fd");
    argList.append("/Users/GuGengxin/Documents/MyCodes/GX/src");

    argList.append("-fe");
    argList.append(".cpp");
    argList.append("-fe");
    argList.append(".c");

    argList.append("-fsp");
    argList.append("\t../../src");

    argList.append("-fss");
    argList.append(" \\\n");

    argList.append("-ff");
    argList.append("GBuffer.cpp");

    argList.append("-fsfp");
    argList.append("\t#../../src");

    argList.append("-fsfs");
    argList.append(" \\\n");

    argList.append("-fi");
    argList.append("GXPthread.cpp");

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
        cout<< " -o (new file path) [-oe new file encoding,none will use old] [-oebom8 1/0 add (or not) bom8]\n";
        cout<< "\n";
        cout<< " [-rs (source string)] [-rscs 0=CaseSensitive 1=CaseInsensitive]\n";
        cout<< " [-rss (source suffix string)] [-rsscs 0=CaseSensitive 1=CaseInsensitive]\n";
        cout<< " [-rsp \"\\\" or \"/\" source string is path]\n";
        cout<< " [-rd (destination string)]\n";
        cout<< " [-ris (index start,default 0)] [-ric (index count,default 0:all)]\n";
        cout<< "\n";
        cout<< " [-fp (file list sign-pre) -fs (file list sign-suf)]\n";
        cout<< " [-fd (file list dir)]\n";
        cout<< " [-fe (file list add extension)]\n";
        cout<< " [-fsp (file list string-pre) -fss (file list string-suf)]\n";
        cout<< " [-ff (file list add filter)]\n";
        cout<< " [-fsfp (file list filter string-pre) -fsfs (file list filter string-suf)]\n";
        cout<< " [-fi (file list add ignore)]\n";
        cout<< "\n";

        QList<QByteArray> acs=QTextCodec::availableCodecs();
        if(acs.size()>0) {
            cout << " available encoding:\n";
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
        QString out,oute;int outbom8=0;
        //Replace
        QString rs;int rscs=0;
        QString rss,rsp;int rsscs=0;
        QString rd;
        int ris=0,ric=0;
        //File
        QString fp,fs;
        QString fd;
        QList<QString> fe;
        QString fsp,fss;
        QList<QString> ff;
        QString fsfp,fsfs;
        QList<QString> fi;

        for(int i=1;i+1<argList.size();i+=2) {
            QString& str=argList[i];
            if(str=="-i") {
                GCTextEditor te;
                te.setText(QString((const char*)argv[i+1]));
                te.replace(QString("\t"),QString("\\t"));
                in=te.getText();
            }
            else if(str=="-ie") {
                ine=argList[i+1];
            }
            else if(str=="-o") {
                GCTextEditor te;
                te.setText(QString((const char*)argv[i+1]));
                te.replace(QString("\t"),QString("\\t"));
                out=te.getText();
            }
            else if(str=="-oe") {
                oute=argList[i+1];
            }
            else if(str=="-oebom8") {
                outbom8=argList[i+1].toInt();
            }
            //Replace
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
            //File
            else if(str=="-fp") {
                fp=argList[i+1];
            }
            else if(str=="-fs") {
                fs=argList[i+1];
            }
            else if(str=="-fd") {
                fd=argList[i+1];
            }
            else if(str=="-fe") {
                fe.append(argList[i+1]);
            }
            else if(str=="-fsp") {
                fsp=argList[i+1];
            }
            else if(str=="-fss") {
                fss=argList[i+1];
            }
            else if(str=="-ff") {
                ff.append(argList[i+1]);
            }
            else if(str=="-fsfp") {
                fsfp=argList[i+1];
            }
            else if(str=="-fsfs") {
                fsfs=argList[i+1];
            }
            else if(str=="-fi") {
                fi.append(argList[i+1]);
            }
            //////////
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

                    if(worker.replace(rs,rd,M_CS_TO_QTCS(rscs),rss,M_CS_TO_QTCS(rsscs),rsp,ris,ric)<0) {
                        cerr<< "Replace Fail!" <<endl;
                        err=true;
                    }
                }
            }

            if(!err && !doThings) {
                if(fp.length()>0 && fs.length()>0 && fd.length()>0 && fe.size()>0) {
                    doThings=true;

                    if(worker.fileList(fp,fs,fd,fe,fsp,fss,ff,fsfp,fsfs,fi)<0) {
                        cerr<< "File Fail!" <<endl;
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

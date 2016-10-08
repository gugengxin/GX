#include <QCoreApplication>
#include <QTextStream>
#include <QUuid>

int main(int argc, char *argv[])
{
    QList<QString> argList;
    for(int i=0;i<argc;i++) {
        argList.append(QString((const char*)argv[i]));
    }

    //QTextStream cin(stdin, QIODevice::ReadOnly);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QTextStream cerr(stderr, QIODevice::WriteOnly);

    bool err=false;
    QString m("u32");
    for(int i=1;i<argList.size();i++) {
        QString& str=argList[i];
        if(str=="-h") {
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
            cout<< " -h (show this help)\n";
            cout<< " -m (output mode) u32/u64 default:u32\n";
            return 0;
        }
        else if(str=="-m" && i+1<argList.size()) {
            m=argList[i+1];
            i++;
        }
        else {
            cerr<< "unknown option \"" << str << "\"" <<endl;
            err=true;
            break;
        }
    }

    if(!err) {
        QUuid uuid=QUuid::createUuid();
        QByteArray ba=uuid.toByteArray();
        QString outStr;
        if(m=="u32") {
            uint* p=(uint*)(const void*)ba;
            for(int i=0;i<4;i++) {
                if(i>0) {
                    outStr.append(", ");
                }
                outStr.append("0x");
                outStr.append(QString::number(p[i],16).toUpper());
            }
            cout<<outStr<<endl;
        }
        else if(m=="u64") {
            qulonglong* p=(qulonglong*)(const void*)ba;
            for(int i=0;i<2;i++) {
                if(i>0) {
                    outStr.append(", ");
                }
                outStr.append("0x");
                outStr.append(QString::number(p[i],16).toUpper());
                outStr.append("ULL");
            }
            cout<<outStr<<endl;
        }
        else {
            cerr<< "unknown mode \"" << m << "\"" <<endl;
        }
    }

    return 0;
}

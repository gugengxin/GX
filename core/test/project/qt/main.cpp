#include "mainwindow.h"
#include <QApplication>
#include "AppDge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GApplication::main(argc,argv,"AppDge");

    MainWindow w;
    w.show();

    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include "AppDge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GApplication::InitData initData;
    GApplication::main(AppDge::shared(),&initData);

    MainWindow w;
    w.show();

    return a.exec();
}

#include "MainWindow.h"
#include <QApplication>
#include "AppDge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    GApplication::InitData initData(&w);
    GApplication::main(AppDge::shared(),&initData);

    return a.exec();
}

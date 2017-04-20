#include "MainWindow.h"
#include <QApplication>
#include "AppDge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    GApplication::main(argc,argv,"AppDge");
    GWindow::main(&w,"Game");

    return a.exec();
}

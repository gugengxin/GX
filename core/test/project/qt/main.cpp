#include "mainwindow.h"
#include <QApplication>
#include "AppDge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GApplication::main(AppDge::shared());

    MainWindow w;
    w.show();

    return a.exec();
}

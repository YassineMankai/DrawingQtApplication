#include "mainwindow.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QDir dir(QDir::current());
    dir.mkdir("files");

    w.show();
    return a.exec();
}

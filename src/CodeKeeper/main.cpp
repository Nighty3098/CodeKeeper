#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QFile file(":/stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);

    QApplication a(argc, argv);

    a.setStyleSheet(file.readAll());

    MainWindow w;
    w.show();
    return a.exec();
}

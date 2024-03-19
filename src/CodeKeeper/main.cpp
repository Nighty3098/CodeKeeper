#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QFile file(":/stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);

    QApplication a(argc, argv);
    MainWindow w;

    a.setStyleSheet(file.readAll());

    w.setWindowIcon(QIcon("://icon.png"));

    w.show();
    return a.exec();
}

#include "mainwindow.h"
#include <QFile>
#include <QApplication>

#include "db/create_connect_to_keeper.cpp"
#include "db/create_connect_to_settings.cpp"

int main(int argc, char *argv[])
{
    QFile file(":/stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);

    QApplication a(argc, argv);
    MainWindow w;

    if (createConnectionToKeeper() == false) {
        return -1;
    }

    if (createConnectionToSettings() == false) {
        return -1;
    }

    a.setStyleSheet(file.readAll());

    w.setWindowIcon(QIcon("://icon.png"));

    w.show();
    return a.exec();
}

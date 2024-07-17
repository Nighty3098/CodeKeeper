#include <QApplication>
#include <QFile>
#include <QSplashScreen>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow keeper;

    keeper.setWindowIcon(QIcon(":/icon.png"));

    keeper.show();

    return a.exec();
}

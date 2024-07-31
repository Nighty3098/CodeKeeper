#include <QApplication>
#include <QFile>
#include <QSplashScreen>
#include <QTranslator>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("CodeKeeper_ru_RU.qm");
    // qApp->installTranslator(&translator);

    MainWindow keeper;

    keeper.setWindowIcon(QIcon(":/icon.png"));

    keeper.show();

    return a.exec();
}

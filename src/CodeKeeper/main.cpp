#include <QApplication>
#include <QFile>
#include <QSplashScreen>
#include <QTranslator>
#include <QSettings>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QSettings* globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    QString appLang = globalSettings->value("lang").value<QString>();

    QTranslator translator;

    if (appLang == "Ru") {
        QString file = "CodeKeeper_ru_RU.qm";
        qDebug() << "Loading " << file;
        translator.load(file);
    }
    if (appLang == "En") {
        qDebug() << "Loading " << "Eng";
    }

    qApp->installTranslator(&translator);


    MainWindow keeper;
    keeper.setWindowIcon(QIcon(":/icon.png"));
    keeper.show();

    return a.exec();
}

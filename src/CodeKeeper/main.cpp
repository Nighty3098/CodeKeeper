#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QSplashScreen>
#include <QTranslator>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings *globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    int appLang = globalSettings->value("lang").value<int>();

    QTranslator translator;
    if (appLang == 1)
    {
        QString file = ":/CodeKeeper_ru_RU.ts";
        qDebug() << "Loading " << file;
        translator.load(file);
    }
    if (appLang == 0)
    {
        qDebug() << "Loading "
                 << "English";
    }
    if (appLang == 2)
    {
        qDebug() << "Loading "
                 << "Japanese";
    }
    if (appLang == 3)
    {
        qDebug() << "Loading "
                 << "Germany";
    }
    if (appLang == 4)
    {
        qDebug() << "Loading "
                 << "Spanish";
    }
    qApp->installTranslator(&translator);

    MainWindow keeper;
    keeper.setWindowIcon(QIcon(":/icon.png"));
    keeper.setMinimumSize(900, 700);
    keeper.show();

    return a.exec();
}

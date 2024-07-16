#include <QApplication>
#include <QFile>
#include <QSplashScreen>

#include "mainwindow.h"

bool loadApp(QSplashScreen *psplash)
{
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("https://google.com/"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    QObject::connect(&nam, SIGNAL(finished(QNetworkReply *)), &loop, SLOT(quit()));

    if (!reply->isFinished()) {
        loop.exec();
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Connected";
            return true;
        } else {
            qDebug() << "Error: " << reply->errorString();
            return false;
        }
    }
}

int main(int argc, char *argv[])
{
    QFile file(":/stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);

    QApplication a(argc, argv);

    // QSplashScreen splash(QPixmap(":/icon.png"));
    // splash.show();

    MainWindow keeper;
    // a.setStyleSheet(file.readAll());

    keeper.setWindowIcon(QIcon(":/icon.png"));

    // loadApp(&splash);
    // splash.finish(&keeper);
    keeper.show();

    return a.exec();
}

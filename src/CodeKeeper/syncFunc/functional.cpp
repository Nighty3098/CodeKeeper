#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "syncwindow.h"

void SyncWindow::setFontStyle()
{
    appName->setFont(selectedFont);

    infoLabel->setFont(selectedFont);
    infoLabel->setStyleSheet("font-size: " + font_size + "px;");

    syncingProgress->setFont(selectedFont);

    startSyncing->setFont(selectedFont);
    startSyncing->setStyleSheet("font-size: " + font_size + "px;");

    stopSyncing->setFont(selectedFont);
    stopSyncing->setStyleSheet("font-size: " + font_size + "px;");
}

void SyncWindow::startSyncingFunc()
{
    qDebug() << "Starting syncing...";

    syncingProgress->setValue(90);
}

void SyncWindow::cancelSyncingFunc()
{
    qDebug() << "Canceling syncing...";

    this->close();
}

bool SyncWindow::checkConnection()
{
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    manager = new QNetworkAccessManager();
    reply = manager->get(QNetworkRequest(QUrl("http://www.google.com")));

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            qDebug() << "Internet connection is available";
            return true;
        }
        else
        {
            qDebug() << "No internet connection found";
            return false;
        }
    });
}

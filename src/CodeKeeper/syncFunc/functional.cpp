#include <QNetworkAccessManager>
#include <QNetworkReply>

void SyncWindow::setFontStyle()
{
    appName->setFont(selectedFont);

    infoLabel->setFont(selectedFont);
    infoLabel->setStyleSheet("font-size: " + font_size + "pt;");

    syncingProgress->setFont(selectedFont);

    startSyncing->setFont(selectedFont);
    startSyncing->setStyleSheet("font-size: " + font_size + "pt;");

    stopSyncing->setFont(selectedFont);
    stopSyncing->setStyleSheet("font-size: " + font_size + "pt;");
}

void SyncWindow::startSyncingFunc()
{
    qDebug() << "\033[0m\033[32mStarting syncing...";

    syncingProgress->setValue(90);
}

void SyncWindow::cancelSyncingFunc()
{
    qDebug() << "\033[0m\033[31mCanceling syncing...";

    this->close();
}

bool SyncWindow::checkConnection()
{
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    manager = new QNetworkAccessManager();
    reply = manager->get(QNetworkRequest(QUrl("http://www.google.com")));

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "\033[0m\033[32mInternet connection is available";
            return true;
        } else {
            qDebug() << "\033[0m\033[31mNo internet connection found";
            return false;
        }
    });
}

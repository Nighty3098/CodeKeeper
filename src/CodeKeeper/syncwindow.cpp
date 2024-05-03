#include "syncwindow.h"
#include "syncFunc/functional.cpp"

#include <QtWidgets>
#include <QNetworkAccessManager>
#include <QNetworkReply>

SyncWindow::SyncWindow(QWidget *parent) : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    selectedFont = globalSettings->value("font").value<QFont>();
    font_size = globalSettings->value("fontSize").value<QString>();
    dir = globalSettings->value("path").value<QString>();

    mainLayout = new QGridLayout;

    mainTitle = new QLabel("Sync with Git");

    mainLayout->addWidget(mainTitle, 3, 0, 1, 1);

    centralWidget->setLayout(mainLayout);
}

SyncWindow::~SyncWindow() { }

bool SyncWindow::checkConnection()
{
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    manager = new QNetworkAccessManager();
    reply = manager->get(QNetworkRequest(QUrl("http://www.google.com")));

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Internet connection is available";
            return true;
        } else {
            qDebug() << "No internet connection found";
            return false;
        }
    });
}

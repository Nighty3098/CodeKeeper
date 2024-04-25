#include "syncwindow.h"
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

    manager = new QNetworkAccessManager();
    reply = manager->get(QNetworkRequest(QUrl("http://www.google.com")));

    mainTitle = new QLabel("");

    mainLayout->addWidget(mainTitle, 3, 0, 1, 1);

    centralWidget->setLayout(mainLayout);

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Internet connection is available";
        } else {
            qDebug() << "No internet connection found";
        }
    });
}

SyncWindow::~SyncWindow() { }

void SyncWindow::checkConnection() { }

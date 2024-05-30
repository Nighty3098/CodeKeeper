#include "accountwindow.h"
#include "accountFunc/functional.cpp"
#include <QtWidgets>
#include "mainwindow.h"

AccountWindow::AccountWindow(QWidget *parent) : QMainWindow{ parent }
{
    QFile file(":/stylesheet/stylesheet_setting_window.qss");
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QGridLayout(centralWidget);
    setFixedSize(400, 660);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    getSettingsData();

    profilePicture = new QLabel();
    profilePicture->setStyleSheet("border-radius: 145px;");

    profileInfo = new QLabel();
    profileInfo->setText(git_user);
    profileInfo->setAlignment(Qt::AlignHCenter);

    codeKeeperStats = new QLabel();

    MainWindow *mainWindow = static_cast<MainWindow *>(parent);
    QString stats = mainWindow->getKeeperStats();
    codeKeeperStats->setText(stats);
    codeKeeperStats->setAlignment(Qt::AlignHCenter);

    userName = new QLabel();
    userName->setText(git_user);
    userName->setAlignment(Qt::AlignHCenter);
    userName->setStyleSheet("font-size: 36pt;");

    closeWindow = new QPushButton("");
    closeWindow->setFixedSize(15, 15);

    setFontStyle();
    setUserData(git_user, profilePicture);

    mainLayout->addWidget(closeWindow, 0, 0, 1, 3, Qt::AlignLeft);
    mainLayout->addWidget(profilePicture, 1, 0, 3, 3, Qt::AlignCenter);
    mainLayout->addWidget(userName, 5, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(profileInfo, 6, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(codeKeeperStats, 7, 0, 1, 3, Qt::AlignCenter);

    connect(closeWindow, SIGNAL(clicked()), this, SLOT(closeWindowSlot()));
}

AccountWindow::~AccountWindow(){};

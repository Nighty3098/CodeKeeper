#include "accountwindow.h"
#include "accountFunc/functional.cpp"
#include <QtWidgets>

AccountWindow::AccountWindow(QWidget *parent) : QMainWindow{ parent }
{
    QFile file(":/stylesheet/stylesheet_setting_window.qss");
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QGridLayout(centralWidget);
    setFixedSize(400, 640);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    getSettingsData();

    profilePicture = new QLabel();
    profilePicture->setStyleSheet("border-radius: 145px;");

    profileInfo = new QLabel();
    profileInfo->setText(git_user);
    profileInfo->setAlignment(Qt::AlignHCenter);

    closeWindow = new QPushButton("");
    closeWindow->setFixedSize(15, 15);

    setFontStyle();
    setUserData(git_user, profilePicture);

    mainLayout->addWidget(closeWindow, 0, 0, 1, 3, Qt::AlignLeft);
    mainLayout->addWidget(profilePicture, 1, 0, 3, 3, Qt::AlignCenter);
    mainLayout->addWidget(profileInfo, 5, 0, 1, 3, Qt::AlignCenter);

    connect(closeWindow, SIGNAL(clicked()), this, SLOT(closeWindowSlot()));
}

AccountWindow::~AccountWindow(){};

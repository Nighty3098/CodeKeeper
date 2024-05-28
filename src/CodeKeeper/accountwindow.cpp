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
    setFixedSize(400, 600);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    getSettingsData();

    profilePicture = new QLabel("Profile picture");

    profileName = new QLabel();
    profileName->setText(git_user);

    mainLayout->addWidget(profilePicture, 0, 0, 2, 3, Qt::AlignCenter);
    mainLayout->addWidget(profileName, 3, 0, 1, 3, Qt::AlignCenter);
}

AccountWindow::~AccountWindow(){};
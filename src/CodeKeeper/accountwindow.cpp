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

    profilePicture = new QLabel();
    profilePicture->setStyleSheet("border-radius: 145px;");

    profileName = new QLabel();
    profileName->setText(git_user);
    profileName->setAlignment(Qt::AlignHCenter);

    closeWindow = new QPushButton(QPixmap(":/quit.png").scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation), " close");
    closeWindow->setFixedSize(100, 25);

    setFontStyle();
    setUserData(git_user, profilePicture);

    mainLayout->addWidget(profilePicture, 0, 0, 3, 3, Qt::AlignCenter);
    mainLayout->addWidget(profileName, 4, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(closeWindow, 5, 0, 1, 3, Qt::AlignCenter);

    connect(closeWindow, SIGNAL(clicked()), this, SLOT(closeWindowSlot()));
}

AccountWindow::~AccountWindow(){};

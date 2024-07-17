#include "accountwindow.h"
#include "accountFunc/functional.cpp"
#include <QtWidgets>
#include "mainwindow.h"
#include <git2.h>

AccountWindow::AccountWindow(QWidget* parent) : QMainWindow { parent }
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QGridLayout(centralWidget);
    setFixedSize(400, 750);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    getSettingsData();

    profilePicture = new QLabel();
    profilePicture->setText("Loading...");
    profilePicture->setStyleSheet("border-radius: 145px;");

    profileInfo = new QLabel();
    profileInfo->setText("Loading...");
    profileInfo->setAlignment(Qt::AlignHCenter);

    codeKeeperStats = new QLabel();

    MainWindow* mainWindow = static_cast<MainWindow*>(parent);
    QString stats = mainWindow->getKeeperStats();
    codeKeeperStats->setText(stats);
    codeKeeperStats->setAlignment(Qt::AlignHCenter);

    tasksStatsProgress = new QProgressBar();
    tasksStatsProgress->setFixedHeight(25);
    tasksStatsProgress->setAlignment(Qt::AlignCenter);

    userName = new QLabel();
    userName->setText(git_user);
    userName->setAlignment(Qt::AlignHCenter);
    userName->setStyleSheet("font-size: 36pt;");

    openRepo = new QPushButton("Open Git");
    openRepo->setFixedSize(100, 25);

    closeWindow = new QPushButton("");
    closeWindow->setFixedSize(15, 15);

    QThread* styleThread = new QThread;
    QObject::connect(styleThread, &QThread::started, this, [this]() {
        setFontStyle();

        qDebug() << "styleThread started";
    });
    styleThread->start();

    QThread* setUserDataThread = new QThread;
    QObject::connect(setUserDataThread, &QThread::started, this, [this]() {
        setUserData(git_user, profilePicture);
        setTasksProgress();

        qDebug() << "setUserDataThread started";
    });
    setUserDataThread->start();

    mainLayout->addWidget(closeWindow, 0, 0, 1, 3, Qt::AlignLeft);
    mainLayout->addWidget(profilePicture, 1, 0, 3, 3, Qt::AlignCenter);
    mainLayout->addWidget(userName, 5, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(profileInfo, 6, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(tasksStatsProgress, 9, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(codeKeeperStats, 10, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(openRepo, 13, 0, 1, 3, Qt::AlignCenter);

    connect(closeWindow, SIGNAL(clicked()), this, SLOT(closeWindowSlot()));
    connect(openRepo, SIGNAL(clicked()), this, SLOT(onOpenRepoClicked()));
}

AccountWindow::~AccountWindow() {};

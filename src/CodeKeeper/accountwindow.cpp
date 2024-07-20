#include <QtWidgets>
#include <QHBoxLayout>

#include "accountwindow.h"
#include "accountFunc/functional.cpp"
#include "mainwindow.h"
#include "custom/circleProgressbar/ProgressCircle.h"

#include <git2.h>

AccountWindow::AccountWindow(QWidget* parent) : QMainWindow { parent }
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    this->setStyleSheet(" QWidget { background-color: #222126; } QPushButton {background-color: #0a070d; }");

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QGridLayout(centralWidget);
    setFixedSize(800, 500);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    getSettingsData();

    tasksTitle = new QLabel();
    tasksTitle->setText("\nTasks\n");

    projectTitle = new QLabel();
    projectTitle->setText("\n\nProjects\n");

    profilePicture = new QLabel();
    profilePicture->setText("Loading...");
    profilePicture->setFixedSize(300, 300);
    profilePicture->setStyleSheet("border-radius: 145px;");

    profileInfo = new QLabel();
    profileInfo->setText("Loading...");
    profileInfo->setAlignment(Qt::AlignHCenter);

    codeKeeperStats = new QLabel();

    MainWindow* mainWindow = static_cast<MainWindow*>(parent);
    QString stats = mainWindow->getKeeperStats();
    codeKeeperStats->setText(stats);
    codeKeeperStats->setAlignment(Qt::AlignHCenter);

    tasksStatsProgress = new CircleProgressBar();
    tasksStatsProgress->setFixedSize(60, 60);
    tasksStatsProgress->setBackgroundColor(QColor(Qt::transparent));
    tasksStatsProgress->setLineWidth(font_size.toInt());
    tasksStatsProgress->setDisplayMode(CircleProgressBar::Percent); // Percent, CustomText, NoPercent, Hidden

    userName = new QLabel();
    userName->setText(git_user);
    userName->setAlignment(Qt::AlignHCenter);

    openRepo = new QPushButton("Open Git");
    openRepo->setFixedSize(100, 25);

    closeWindow = new QPushButton("");
    closeWindow->setFixedSize(15, 15);

    QHBoxLayout* projectsStatsLayout = new QHBoxLayout();

    notStartedProjectsProgress = new CircleProgressBar();
    notStartedProjectsProgress->setFixedSize(60, 60);
    notStartedProjectsProgress->setBackgroundColor(QColor(Qt::transparent));
    notStartedProjectsProgress->setProgressColor(QColor("#c75d5e"));
    notStartedProjectsProgress->setLineWidth(font_size.toInt());

    startedProjectsProgress = new CircleProgressBar();
    startedProjectsProgress->setFixedSize(60, 60);
    startedProjectsProgress->setBackgroundColor(QColor(Qt::transparent));
    startedProjectsProgress->setProgressColor(QColor("#e09132"));
    startedProjectsProgress->setLineWidth(font_size.toInt());

    reviewProjectsProgress = new CircleProgressBar();
    reviewProjectsProgress->setFixedSize(60, 60);
    reviewProjectsProgress->setBackgroundColor(QColor(Qt::transparent));
    reviewProjectsProgress->setProgressColor(QColor("#b1e032"));
    reviewProjectsProgress->setLineWidth(font_size.toInt());

    completedProjectsProgress = new CircleProgressBar();
    completedProjectsProgress->setFixedSize(60, 60);
    completedProjectsProgress->setBackgroundColor(QColor(Qt::transparent));
    completedProjectsProgress->setProgressColor(QColor("#78b3ba"));
    completedProjectsProgress->setLineWidth(font_size.toInt());

    projectsStatsLayout->addWidget(notStartedProjectsProgress);
    projectsStatsLayout->addWidget(startedProjectsProgress);
    projectsStatsLayout->addWidget(reviewProjectsProgress);
    projectsStatsLayout->addWidget(completedProjectsProgress);

    QThread* styleThread = new QThread;
    QObject::connect(styleThread, &QThread::started, this, [this]() {
        setFontStyle();

        qDebug() << "styleThread started";
    });
    styleThread->start();

    QThread* setUserDataThread = new QThread;
    QObject::connect(setUserDataThread, &QThread::started, this, [this]() {
        qDebug() << "setUserDataThread started";

        setUserData(git_user, profileInfo);
        setTasksProgress();
        setProjectsStats();
    });
    setUserDataThread->start();

    QThread* setUserImageThread = new QThread;
    QObject::connect(setUserImageThread, &QThread::started, this, [this]() {
        qDebug() << "setUserImageThread started";

        get_image_url(git_user, profilePicture);
    });
    setUserImageThread->start();

    mainLayout->addWidget(closeWindow, 0, 0, 1, 6, Qt::AlignLeft);
    mainLayout->addWidget(profilePicture, 2, 0, 3, 3, Qt::AlignCenter);

    mainLayout->addWidget(userName, 2, 3, 1, 3, Qt::AlignCenter);

    mainLayout->addWidget(tasksTitle, 3, 3, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(tasksStatsProgress, 4, 3, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(projectTitle, 5, 3, 1, 3, Qt::AlignCenter);
    mainLayout->addLayout(projectsStatsLayout, 6, 3, 1, 3, Qt::AlignCenter);

    mainLayout->addWidget(profileInfo, 14, 0, 3, 3, Qt::AlignCenter);
    mainLayout->addWidget(codeKeeperStats, 14, 3, 3, 3, Qt::AlignCenter);
    mainLayout->addWidget(openRepo, 17, 0, 1, 6, Qt::AlignCenter);

    connect(closeWindow, SIGNAL(clicked()), this, SLOT(closeWindowSlot()));
    connect(openRepo, SIGNAL(clicked()), this, SLOT(onOpenRepoClicked()));
}

AccountWindow::~AccountWindow() {};

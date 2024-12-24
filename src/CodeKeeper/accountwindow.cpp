#include "accountwindow.h"

#include <QHBoxLayout>
#include <QtWidgets>
#include <qt/QtWidgets/qgridlayout.h>

#include "accountFunc/functional.cpp"
#include "custom/ColorValueDisplay/ColorValueDisplay.h"
#include "custom/circleChart/CircleChart.h"
#include "custom/circleProgressbar/ProgressCircle.h"
#include "mainwindow.h"

AccountWindow::AccountWindow(QWidget *parent) : QMainWindow{parent}
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    MainWindow *mainWindow = static_cast<MainWindow *>(parent);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QGridLayout(centralWidget);
    setFixedSize(800, 550);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    getSettingsData();

    tasksTitle = new QLabel();
    tasksTitle->setText(tr("Tasks"));
    tasksTitle->setAlignment(Qt::AlignCenter);

    projectTitle = new QLabel();
    projectTitle->setText(tr("Projects"));
    projectTitle->setAlignment(Qt::AlignCenter);

    profilePicture = new QLabel();
    profilePicture->setAlignment(Qt::AlignCenter);
    profilePicture->setPixmap(mainWindow->changeIconColor(QPixmap(":/user.png")).scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    profilePicture->setFixedSize(300, 300);
    profilePicture->setStyleSheet("border-radius: 145px;");

    profileInfo = new QLabel();
    profileInfo->setText(tr("Loading..."));
    profileInfo->setAlignment(Qt::AlignHCenter);

    tasksStatsLayout = new QHBoxLayout();

    tasksStatsProgress = new CircleProgressBar();
    tasksStatsProgress->setFixedSize(60, 60);
    tasksStatsProgress->setBackgroundColor(QColor(Qt::transparent));
    tasksStatsProgress->setLineWidth(font_size.toInt());
    tasksStatsProgress->setDisplayMode(CircleProgressBar::Percent); // Percent, CustomText, NoPercent, Hidden

    tasksChartValuesDisplay = new ColorValueDisplay();
    tasksChartValuesDisplay->setFixedSize(160, 85);

    tasksStatsLayout->addWidget(tasksStatsProgress);
    tasksStatsLayout->addWidget(tasksChartValuesDisplay);
    tasksStatsLayout->setSpacing(5);

    userName = new QLabel();
    userName->setText(git_user);
    userName->setFixedHeight(35);
    userName->setAlignment(Qt::AlignHCenter);

    openRepo = new QPushButton(tr("Open Git"));
    openRepo->setFixedSize(100, 25);

    closeWindow = new QPushButton("");
    closeWindow->setObjectName("closeBtn");
    closeWindow->setFixedSize(13, 13);

    projectsStatsLayout = new QHBoxLayout();
    projectsStatsLayout->setSpacing(5);

    projectsChart = new CircleChart();
    projectsChart->setAlignment(Qt::AlignCenter);
    projectsChart->setFixedSize(120, 120);
    projectsChart->setHeight(90);

    chartValuesDisplay = new ColorValueDisplay();
    chartValuesDisplay->setFixedSize(160, 85);

    projectsStatsLayout->addWidget(projectsChart);
    projectsStatsLayout->addWidget(chartValuesDisplay);

    QVBoxLayout *statsLayout = new QVBoxLayout();
    statsLayout->setSpacing(20);
    statsLayout->addWidget(tasksTitle, Qt::AlignHCenter | Qt::AlignBottom);
    statsLayout->addLayout(tasksStatsLayout);
    statsLayout->addWidget(projectTitle, Qt::AlignHCenter | Qt::AlignBottom);
    statsLayout->addLayout(projectsStatsLayout);

    statsWidget = new QWidget();
    statsWidget->setFixedSize(350, 300);
    statsWidget->setLayout(statsLayout);

    QVBoxLayout *gitProfileLayout = new QVBoxLayout();
    gitProfileLayout->addWidget(userName, Qt::AlignVCenter);
    gitProfileLayout->addWidget(profilePicture, Qt::AlignVCenter);
    gitProfileLayout->addWidget(profileInfo, Qt::AlignVCenter);

    QThread *styleThread = new QThread;
    QObject::connect(styleThread, &QThread::started, this, [this]() {
        setFontStyle();

        qDebug() << "styleThread started";
    });
    styleThread->start();

    QThread *setUserDataThread = new QThread;
    QObject::connect(setUserDataThread, &QThread::started, this, [this]() {
        qDebug() << "setUserDataThread started";

        setUserData(git_user, profileInfo);
        setTasksProgress();
        setProjectsStats();
    });
    setUserDataThread->start();

    QThread *setUserImageThread = new QThread;
    QObject::connect(setUserImageThread, &QThread::started, this, [this]() {
        qDebug() << "setUserImageThread started";

        get_image_url(git_user, profilePicture);
    });
    setUserImageThread->start();

    mainLayout->addWidget(closeWindow, 0, 0, 1, 8, Qt::AlignLeft);
    mainLayout->addWidget(userName, 1, 0, 1, 8, Qt::AlignCenter);
    mainLayout->addWidget(profilePicture, 2, 0, 7, 4, Qt::AlignCenter);
    mainLayout->addWidget(statsWidget, 2, 4, 7, 4, Qt::AlignCenter);
    mainLayout->addWidget(profileInfo, 12, 0, 1, 8, Qt::AlignCenter);
    mainLayout->addWidget(openRepo, 16, 0, 1, 8, Qt::AlignCenter);

    connect(closeWindow, SIGNAL(clicked()), this, SLOT(closeWindowSlot()));
    connect(openRepo, SIGNAL(clicked()), this, SLOT(onOpenRepoClicked()));
}

AccountWindow::~AccountWindow() {};

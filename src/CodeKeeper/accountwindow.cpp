#include "accountwindow.h"

#include <git2.h>

#include <QHBoxLayout>
#include <QtWidgets>

#include "accountFunc/functional.cpp"
#include "custom/ColorValueDisplay/ColorValueDisplay.h"
#include "custom/circleChart/CircleChart.h"
#include "custom/circleProgressbar/ProgressCircle.h"
#include "mainwindow.h"

AccountWindow::AccountWindow(QWidget *parent) : QMainWindow{parent}
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QGridLayout(centralWidget);
    setFixedSize(800, 600);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    getSettingsData();

    tasksTitle = new QLabel();
    tasksTitle->setText(tr("\n\nTasks"));

    projectTitle = new QLabel();
    projectTitle->setText(tr("\n\nProjects"));

    langsTitle = new QLabel();
    langsTitle->setText(tr("\n\nLanguages"));

    profilePicture = new QLabel();
    profilePicture->setText(tr("Loading..."));
    profilePicture->setFixedSize(300, 300);
    profilePicture->setStyleSheet("border-radius: 145px;");

    profileInfo = new QLabel();
    profileInfo->setText(tr("Loading..."));
    profileInfo->setAlignment(Qt::AlignHCenter);

    MainWindow *mainWindow = static_cast<MainWindow *>(parent);

    QHBoxLayout *tasksStatsLayout = new QHBoxLayout();

    tasksStatsProgress = new CircleProgressBar();
    tasksStatsProgress->setFixedSize(60, 60);
    tasksStatsProgress->setBackgroundColor(QColor(Qt::transparent));
    tasksStatsProgress->setLineWidth(font_size.toInt());
    tasksStatsProgress->setDisplayMode(CircleProgressBar::Percent); // Percent, CustomText, NoPercent, Hidden

    tasksChartValuesDisplay = new ColorValueDisplay();
    tasksChartValuesDisplay->setFixedSize(160, 85);

    tasksStatsLayout->addWidget(tasksStatsProgress);
    tasksStatsLayout->addWidget(tasksChartValuesDisplay);
    tasksStatsLayout->setSpacing(20);

    userName = new QLabel();
    userName->setText(git_user);
    userName->setAlignment(Qt::AlignHCenter);

    openRepo = new QPushButton(tr("Open Git"));
    openRepo->setFixedSize(100, 25);

    closeWindow = new QPushButton("");
    closeWindow->setFixedSize(15, 15);

    QHBoxLayout *projectsStatsLayout = new QHBoxLayout();
    projectsStatsLayout->setSpacing(20);

    projectsChart = new CircleChart();
    projectsChart->setAlignment(Qt::AlignCenter);
    projectsChart->setFixedSize(90, 90);
    projectsChart->setHeight(90);

    chartValuesDisplay = new ColorValueDisplay();
    chartValuesDisplay->setFixedSize(160, 85);

    projectsStatsLayout->addWidget(projectsChart);
    projectsStatsLayout->addWidget(chartValuesDisplay);

    QHBoxLayout *langsStatsLayout = new QHBoxLayout();
    langsStatsLayout->setSpacing(20);

    langsChart = new CircleChart();
    langsChart->setFixedSize(100, 100);
    langsChart->setAlignment(Qt::AlignCenter);
    langsChart->setHeight(90);

    langsValuesDisplay = new ColorValueDisplay();
    langsValuesDisplay->setFixedSize(160, 100);

    langsStatsLayout->addWidget(langsChart);
    langsStatsLayout->addWidget(langsValuesDisplay);

    QThread *langsStatsThread = new QThread;
    QObject::connect(langsStatsThread, &QThread::started, this, [this]() {
        MainWindow *mainWindow = qobject_cast<MainWindow *>(this->parent());

        QStringList urls = mainWindow->getAllReposUrl();
        QString langsStatsS = getLangByRepo(urls);

        qDebug() << langsStatsS;
        setLangsStats(langsStatsS);

        qDebug() << "langsStats started";
    });
    langsStatsThread->start();

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

    mainLayout->addWidget(closeWindow, 0, 0, 1, 6, Qt::AlignLeft);
    mainLayout->addWidget(profilePicture, 2, 0, 8, 3, Qt::AlignCenter);
    mainLayout->addWidget(userName, 2, 3, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(tasksTitle, 3, 3, 1, 3, Qt::AlignHCenter);
    mainLayout->addLayout(tasksStatsLayout, 4, 3, 1, 3, Qt::AlignHCenter);
    mainLayout->addWidget(projectTitle, 5, 3, 1, 3, Qt::AlignHCenter);
    mainLayout->addLayout(projectsStatsLayout, 6, 3, 1, 3, Qt::AlignHCenter);
    mainLayout->addWidget(langsTitle, 13, 3, 1, 3, Qt::AlignHCenter);
    mainLayout->addWidget(profileInfo, 13, 0, 4, 3, Qt::AlignCenter);
    mainLayout->addLayout(langsStatsLayout, 14, 3, 3, 3, Qt::AlignCenter);
    mainLayout->addWidget(openRepo, 17, 0, 2, 6, Qt::AlignCenter);

    connect(closeWindow, SIGNAL(clicked()), this, SLOT(closeWindowSlot()));
    connect(openRepo, SIGNAL(clicked()), this, SLOT(onOpenRepoClicked()));
}

AccountWindow::~AccountWindow() {};

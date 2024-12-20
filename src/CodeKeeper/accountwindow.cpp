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

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QGridLayout(centralWidget);
    setFixedSize(800, 670);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    getSettingsData();

    tasksTitle = new QLabel();
    tasksTitle->setText(tr("Tasks"));
    tasksTitle->setAlignment(Qt::AlignCenter);

    projectTitle = new QLabel();
    projectTitle->setText(tr("Projects"));
    projectTitle->setAlignment(Qt::AlignCenter);

    langsTitle = new QLabel();
    langsTitle->setText(tr("Languages"));
    langsTitle->setAlignment(Qt::AlignCenter);

    profilePicture = new QLabel();
    profilePicture->setAlignment(Qt::AlignCenter);
    profilePicture->setPixmap(QPixmap(":/user.png").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    profilePicture->setFixedSize(300, 300);
    profilePicture->setStyleSheet("border-radius: 145px;");

    profileInfo = new QLabel();
    profileInfo->setText(tr("Loading..."));
    profileInfo->setAlignment(Qt::AlignHCenter);

    MainWindow *mainWindow = static_cast<MainWindow *>(parent);

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
    userName->setAlignment(Qt::AlignHCenter);

    openRepo = new QPushButton(tr("Open Git"));
    openRepo->setFixedSize(100, 25);

    closeWindow = new QPushButton("");
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

    langsStatsLayout = new QHBoxLayout();
    langsStatsLayout->setSpacing(5);

    langsChart = new CircleChart();
    langsChart->setFixedSize(100, 100);
    langsChart->setAlignment(Qt::AlignCenter);
    langsChart->setHeight(90);

    langsValuesDisplay = new ColorValueDisplay();
    langsValuesDisplay->setFixedSize(160, 100);

    langsStatsLayout->addWidget(langsChart);
    langsStatsLayout->addWidget(langsValuesDisplay);
    langsStatsLayout->setSpacing(5);

    GitLangsStatsLayout = new QHBoxLayout();
    GitLangsStatsLayout->setSpacing(5);

    GitLangsChart = new CircleChart();
    GitLangsChart->setFixedSize(100, 100);
    GitLangsChart->setAlignment(Qt::AlignCenter);
    GitLangsChart->setHeight(90);

    GitLangsValuesDisplay = new ColorValueDisplay();
    GitLangsValuesDisplay->setFixedSize(160, 140);

    GitLangsStatsLayout->addWidget(GitLangsChart);
    GitLangsStatsLayout->addWidget(GitLangsValuesDisplay);

    gitLangsWidget = new QWidget;
    gitLangsWidget->setLayout(GitLangsStatsLayout);

    LangsWidget = new QWidget;
    LangsWidget->setLayout(langsStatsLayout);

    langsCard = new QToolBox();
    langsCard->addItem(gitLangsWidget, tr("From Git profile"));
    langsCard->addItem(LangsWidget, tr("From local data"));

    QVBoxLayout *statsLayout = new QVBoxLayout();
    statsLayout->setSpacing(20);
    statsLayout->addWidget(tasksTitle, Qt::AlignHCenter | Qt::AlignBottom);
    statsLayout->addLayout(tasksStatsLayout);
    statsLayout->addWidget(projectTitle, Qt::AlignHCenter | Qt::AlignBottom);
    statsLayout->addLayout(projectsStatsLayout);
    // statsLayout->addWidget(langsTitle, Qt::AlignHCenter);
    // statsLayout->addWidget(langsCard, Qt::AlignCenter);

    statsWidget = new QWidget();
    statsWidget->setFixedSize(350, 600);
    statsWidget->setLayout(statsLayout);

    QVBoxLayout *gitProfileLayout = new QVBoxLayout();
    gitProfileLayout->addWidget(userName, Qt::AlignCenter);
    gitProfileLayout->addWidget(profilePicture, Qt::AlignCenter);
    gitProfileLayout->addWidget(profileInfo, Qt::AlignCenter);

    /*
    QThread *GitLangsStatsThread = new QThread;
    QObject::connect(GitLangsStatsThread, &QThread::started, this, [this]() {
        auto gitLangsWidget = this->gitLangsWidget;
        auto langsWidget = this->LangsWidget;
        auto langsCard = this->langsCard;
        auto langsTitle = this->langsTitle;

        auto git_urls = getAllGitReposUrls(git_user);
        auto gitLangsStatsS = getLangByRepo(git_urls);

        if (gitLangsStatsS.isEmpty())
        {
            gitLangsWidget->hide();
        }
        else
        {
            qDebug() << gitLangsStatsS;
            setLangsStats(gitLangsStatsS, GitLangsChart, GitLangsValuesDisplay);
            qDebug() << "gitLangsStats started";
        }

        MainWindow *mainWindow = qobject_cast<MainWindow *>(this->parent());
        auto urls = mainWindow->getAllReposUrl();
        auto langsStatsS = getLangByRepo(urls);

        if (langsStatsS.isEmpty())
        {
            langsWidget->hide();
        }
        else
        {
            qDebug() << langsStatsS;
            setLangsStats(langsStatsS, langsChart, langsValuesDisplay);
            qDebug() << "langsStats started";
        }

        if (gitLangsStatsS.isEmpty() && langsStatsS.isEmpty())
        {
            langsCard->hide();
            langsTitle->hide();
        }
    });

    GitLangsStatsThread->start();

    */

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
    mainLayout->addLayout(gitProfileLayout, 1, 0, 13, 3, Qt::AlignCenter);
    mainLayout->addWidget(statsWidget, 1, 3, 13, 3, Qt::AlignCenter);
    mainLayout->addWidget(openRepo, 14, 0, 2, 6, Qt::AlignCenter);

    connect(closeWindow, SIGNAL(clicked()), this, SLOT(closeWindowSlot()));
    connect(openRepo, SIGNAL(clicked()), this, SLOT(onOpenRepoClicked()));
}

AccountWindow::~AccountWindow() {};

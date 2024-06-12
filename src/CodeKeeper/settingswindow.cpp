#include "settingswindow.h"

#include <QGraphicsBlurEffect>
#include <QSpacerItem>
#include <QtWidgets>
#include <QThread>

#include "mainwindow.cpp"
#include "mainwindow.h"
#include "settingsFunc/functional.cpp"

SettingsWindow::SettingsWindow(QWidget *parent) : QMainWindow{ parent }
{
    // visual
    QFile file(":/stylesheet/stylesheet_setting_window.qss");
    file.open(QFile::ReadOnly);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    selectedFont = globalSettings->value("font").value<QFont>();
    font_size = globalSettings->value("fontSize").value<QString>();
    theme = globalSettings->value("theme").value<QString>();
    path = globalSettings->value("path").value<QString>();

    git_repo = globalSettings->value("git_repo").value<QString>();
    git_user = globalSettings->value("git_user").value<QString>();
    git_token = globalSettings->value("git_token").value<QString>();

    isTimeB = globalSettings->value("isTime").value<bool>();
    isDateB = globalSettings->value("isDate").value<bool>();
    isHostB = globalSettings->value("isHost").value<bool>();
    isAutoSyncB = globalSettings->value("isAutoSync").value<bool>();

    isCustomTitlebar = globalSettings->value("isCustomTitlebar").value<bool>();

    isCreated = globalSettings->value("isCreated").value<bool>();
    isReleaseDate = globalSettings->value("isReleaseDate").value<bool>();
    isLastCommit = globalSettings->value("isLastCommit").value<bool>();
    isPullReq = globalSettings->value("isPullReq").value<bool>();
    isLicense = globalSettings->value("isLicense").value<bool>();
    isRelease = globalSettings->value("isRelease").value<bool>();
    isIssue = globalSettings->value("isIssue").value<bool>();
    isDownloads = globalSettings->value("isDownloads").value<bool>();
    isCommit = globalSettings->value("isCommit").value<bool>();
    isLang = globalSettings->value("isLang").value<bool>();
    isStars = globalSettings->value("isStars").value<bool>();
    isForks = globalSettings->value("isForks").value<bool>();
    isRepoSize = globalSettings->value("isRepoSize").value<bool>();

    this->setStyleSheet(file.readAll());
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    setFixedSize(600, 600);

    // tabs
    tabs = new QTabWidget();
    tabs->setMovable(true);

    QHBoxLayout *BtnsL = new QHBoxLayout();

    saveBtn = new QPushButton(QPixmap(":/save.png")
                                      .scaled(font_size.toInt() + 1, font_size.toInt() + 1,
                                              Qt::KeepAspectRatio, Qt::SmoothTransformation),
                              " Apply");
    saveBtn->setFixedSize(100, 25);

    quitBtn = new QPushButton(QPixmap(":/quit.png")
                                      .scaled(font_size.toInt() + 1, font_size.toInt() + 1,
                                              Qt::KeepAspectRatio, Qt::SmoothTransformation),
                              " Quit");
    quitBtn->setFixedSize(100, 25);

    BtnsL->addWidget(saveBtn);
    BtnsL->addWidget(quitBtn);

    // control buttons

    // main
    QVBoxLayout *appInfoL = new QVBoxLayout();
    QVBoxLayout *subAppInfoL = new QVBoxLayout();
    QHBoxLayout *checkUpdatesBtnL = new QHBoxLayout();

    appName = new QLabel("CodeKeeper");
    appName->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    appName->setStyleSheet("font-size: 32px;");

    urlToRepo = new QLabel();
    urlToRepo->setText("<a style='color: #84a0bf; text-decoration: none; font-size: " + font_size
                       + "' "
                         "href=\"https://github.com/Nighty3098/CodeKeeper\">Source</a>");
    urlToRepo->setTextFormat(Qt::RichText);
    urlToRepo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    urlToRepo->setOpenExternalLinks(true);
    urlToRepo->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    versionInfo = new QLabel();
    versionInfo->setText("0.1.7.1");
    versionInfo->setAlignment(Qt::AlignCenter);

    checkUpdatesBtn =
            new QPushButton(QPixmap(":/retry.png")
                                    .scaled(font_size.toInt() + 1, font_size.toInt() + 1,
                                            Qt::KeepAspectRatio, Qt::SmoothTransformation),
                            " Chech for updates");
    checkUpdatesBtn->setFixedSize(200, 25);
    checkUpdatesBtnL->addWidget(checkUpdatesBtn);

    subAppInfoL->addWidget(appName);
    subAppInfoL->addWidget(urlToRepo);
    subAppInfoL->addWidget(versionInfo);
    subAppInfoL->addLayout(checkUpdatesBtnL);

    appInfoL->addLayout(subAppInfoL);

    // sync
    QGridLayout *mainSyncLayout = new QGridLayout();

    gitLabel = new QLabel("Sync settings");
    gitLabel->setStyleSheet("font-size: 24px;");
    gitLabel->setAlignment(Qt::AlignCenter);

    gitLabel2 = new QLabel("Data in commit");
    gitLabel2->setStyleSheet("font-size: 24px;");
    gitLabel2->setAlignment(Qt::AlignCenter);

    gitToken = new QLineEdit();
    gitToken->setPlaceholderText("GitHub token");
    gitToken->setAlignment(Qt::AlignCenter);
    gitToken->setFixedSize(200, 25);
    gitToken->setText(git_token);

    gitUser = new QLineEdit();
    gitUser->setPlaceholderText("GitHub user");
    gitUser->setAlignment(Qt::AlignCenter);
    gitUser->setFixedSize(200, 25);
    gitUser->setText(git_user);

    gitRepo = new QLineEdit();
    gitRepo->setPlaceholderText("GitHub repo");
    gitRepo->setAlignment(Qt::AlignCenter);
    gitRepo->setFixedSize(200, 25);
    gitRepo->setText(git_repo);

    autoSyncAfterStart = new QCheckBox("Auto sync after start");

    isDate = new QCheckBox("Date");
    isDate->setChecked(isDateB);
    isTime = new QCheckBox("Time");
    isTime->setChecked(isTimeB);
    isHost = new QCheckBox("Host");
    isHost->setChecked(isHostB);
    isSync = new QCheckBox("Auto sync after start");
    isSync->setChecked(isAutoSyncB);

    repoAvailability = new QLabel("Repo");
    repoAvailability->setAlignment(Qt::AlignHCenter);

    mainSyncLayout->setSpacing(10);
    mainSyncLayout->addWidget(gitLabel, 0, 2, 1, 1);
    mainSyncLayout->addWidget(gitToken, 1, 2, 1, 1);
    mainSyncLayout->addWidget(gitUser, 2, 2, 1, 1);
    mainSyncLayout->addWidget(gitRepo, 3, 2, 1, 1);
    mainSyncLayout->addWidget(repoAvailability, 4, 2, 1, 1, Qt::AlignHCenter);
    mainSyncLayout->addWidget(isSync, 5, 2, 1, 1, Qt::AlignHCenter);
    mainSyncLayout->addWidget(gitLabel2, 6, 2, 1, 1);
    mainSyncLayout->addWidget(isDate, 7, 2, 1, 1, Qt::AlignHCenter);
    mainSyncLayout->addWidget(isTime, 8, 2, 1, 1, Qt::AlignHCenter);
    mainSyncLayout->addWidget(isHost, 9, 2, 1, 1, Qt::AlignHCenter);

    // appereance
    QGridLayout *layout1 = new QGridLayout();

    mainTitle = new QLabel("App settings");
    mainTitle->setAlignment(Qt::AlignCenter);
    mainTitle->setStyleSheet("font-size: 32px;");

    fontLabel = new QLabel("Font:");
    fontLabel->setAlignment(Qt::AlignCenter);
    fontSizeLabel = new QLabel("Font size:");
    fontSizeLabel->setAlignment(Qt::AlignCenter);
    themeLabel = new QLabel("Theme:");
    themeLabel->setAlignment(Qt::AlignCenter);

    fontSize = new QSpinBox();
    fontSize->setFixedHeight(25);
    fontSelector = new QFontComboBox();
    fontSelector->setFixedHeight(25);
    themeSelector = new QComboBox();
    themeSelector->setFixedHeight(25);

    customTitleBar = new QCheckBox();
    customTitleBar->setText("Use custom titlebar");
    customTitleBar->setChecked(isCustomTitlebar);

    themeSelector->addItem("Dark");
    themeSelector->addItem("Light");

    layout1->addWidget(mainTitle, 0, 2, 0, 4);
    layout1->addWidget(customTitleBar, 1, 2, 1, 4, Qt::AlignHCenter);
    layout1->addWidget(fontLabel, 2, 3);
    layout1->addWidget(fontSelector, 2, 4);
    layout1->addWidget(fontSizeLabel, 3, 3);
    layout1->addWidget(fontSize, 3, 4);
    layout1->addWidget(themeLabel, 4, 3);
    layout1->addWidget(themeSelector, 4, 4);

    // storage tab
    QGridLayout *storageL = new QGridLayout;
    storageL->setSpacing(25);

    storageLabel = new QLabel();
    storageLabel->setText("Storage settings");
    storageLabel->setAlignment(Qt::AlignCenter);
    storageLabel->setStyleSheet("font-size: 32px;");

    pathToFolder = new QLineEdit();
    pathToFolder->setText("Directory");
    pathToFolder->setPlaceholderText("Directory");
    pathToFolder->setMaximumHeight(25);
    pathToFolder->setText(path);

    openFolder = new QPushButton(QPixmap(":/open.png")
                                         .scaled(font_size.toInt() + 1, font_size.toInt() + 1,
                                                 Qt::KeepAspectRatio, Qt::SmoothTransformation),
                                 " Browse");
    openFolder->setMaximumHeight(25);

    storageL->setSpacing(25);
    storageL->addWidget(storageLabel, 0, 1, 0, 4);
    storageL->addWidget(pathToFolder, 1, 3);
    storageL->addWidget(openFolder, 2, 3);

    // projects content tab
    QGridLayout *projectsContentL = new QGridLayout;
    projectsContentL->setSpacing(10);
    projectsContentL->setAlignment(Qt::AlignCenter);

    projectsContentLabel = new QLabel("Projects content");
    projectsContentLabel->setStyleSheet("font-size: 32px;");
    projectsContentLabel->setAlignment(Qt::AlignCenter);
    projectsContentLabel->setFixedHeight(150);

    CisCreated = new QCheckBox("Created time");
    CisCreated->setChecked(isCreated);
    CisReleaseDate = new QCheckBox("Last release time");
    CisReleaseDate->setChecked(isReleaseDate);
    CisLastCommit = new QCheckBox("Last commit time");
    CisLastCommit->setChecked(isLastCommit);
    CisPullReq = new QCheckBox("Total pull requests");
    CisPullReq->setChecked(isPullReq);
    CisLicense = new QCheckBox("License");
    CisLicense->setChecked(isLicense);
    CisRelease = new QCheckBox("Release");
    CisRelease->setChecked(isRelease);
    CisIssue = new QCheckBox("Issues");
    CisIssue->setChecked(isIssue);
    CisDownloads = new QCheckBox("Downloads");
    CisDownloads->setChecked(isDownloads);
    CisCommit = new QCheckBox("Commits");
    CisCommit->setChecked(isCommit);
    CisLang = new QCheckBox("Langs");
    CisLang->setChecked(isLang);
    CisStars = new QCheckBox("Stars");
    CisStars->setChecked(isStars);
    CisForks = new QCheckBox("Forks");
    CisForks->setChecked(isForks);
    CisRepoSize = new QCheckBox("Repo size");
    CisRepoSize->setChecked(isRepoSize);

    projectsContentL->addWidget(projectsContentLabel, 0, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisCreated, 1, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisReleaseDate, 2, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisLastCommit, 3, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisPullReq, 4, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisLicense, 5, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisRelease, 6, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisIssue, 7, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisDownloads, 8, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisCommit, 9, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisLang, 10, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisStars, 11, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisForks, 12, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addWidget(CisRepoSize, 13, 0, 1, 1, Qt::AlignCenter);

    // info tab
    QWidget *aboutTab = new QWidget();
    QVBoxLayout *aboutTabLayout = new QVBoxLayout(aboutTab);

    aboutTabLayout->addLayout(appInfoL);

    tabs->addTab(aboutTab, "About");

    // sync tab
    QWidget *syncTab = new QWidget();
    QVBoxLayout *syncTabLayout = new QVBoxLayout(syncTab);

    syncTabLayout->addLayout(mainSyncLayout);

    tabs->addTab(syncTab, "Sync");

    // storage tab
    QWidget *storageTab = new QWidget();
    QVBoxLayout *storageTabLayout = new QVBoxLayout(storageTab);

    storageTabLayout->addLayout(storageL);

    tabs->addTab(storageTab, "Storage");

    // main tab
    QWidget *appereanceTab = new QWidget();
    QVBoxLayout *appereanceTabLayout = new QVBoxLayout(appereanceTab);

    appereanceTabLayout->addLayout(layout1);

    tabs->addTab(appereanceTab, "Appereance");

    // projects content
    QWidget *projectsContentTab = new QWidget();
    projectsContentTab->setLayout(projectsContentL);
    tabs->addTab(projectsContentTab, "Projects");

    QIcon aboutIco;
    QIcon syncIco;
    QIcon storageIco;
    QIcon paletteIco;
    QIcon projectsIco;

    aboutIco.addFile(":/about.png");
    syncIco.addFile(":/sync.png");
    storageIco.addFile(":/storage.png");
    paletteIco.addFile(":/palette.png");
    projectsIco.addFile(":/project.png");

    tabs->setTabIcon(tabs->indexOf(aboutTab), aboutIco);
    tabs->setTabIcon(tabs->indexOf(syncTab), syncIco);
    tabs->setTabIcon(tabs->indexOf(storageTab), storageIco);
    tabs->setTabIcon(tabs->indexOf(appereanceTab), paletteIco);
    tabs->setTabIcon(tabs->indexOf(projectsContentTab), projectsIco);

    tabs->setIconSize(QSize(font_size.toInt(), font_size.toInt()));
    tabs->setTabBarAutoHide(true);

    mainLayout->addWidget(tabs);
    mainLayout->addLayout(BtnsL);

    // connects
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveData()));
    connect(quitBtn, SIGNAL(clicked()), this, SLOT(QuitW()));
    connect(checkUpdatesBtn, SIGNAL(clicked()), this, SLOT(checkUpdates()));
    connect(openFolder, SIGNAL(clicked()), this, SLOT(fopenFolder()));

    QTimer *repoTimer = new QTimer(this);
    qDebug() << "checking";

    QThread *repoTimerThread = new QThread;
    QObject::connect(repoTimerThread, &QThread::started, this, [this, repoTimer]() {
        connect(repoTimer, &QTimer::timeout, [=]() { checkRepo(); });
        repoTimer->start(100);

        qDebug() << "repoTimerThread started";
    });
    repoTimerThread->start();

    QThread *styleThread = new QThread;
    QObject::connect(styleThread, &QThread::started, this, [this]() {
        int font_size_int = font_size.toInt();
        setFontPr2(&selectedFont, &font_size_int);

        qDebug() << "styleThread started";
    });
    styleThread->start();
}

SettingsWindow::~SettingsWindow() { }

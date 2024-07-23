#include "settingswindow.h"

#include <QGraphicsBlurEffect>
#include <QSpacerItem>
#include <QtWidgets>
#include <QThread>

#include "mainwindow.cpp"
#include "mainwindow.h"
#include "settingsFunc/functional.cpp"

SettingsWindow::SettingsWindow(QWidget* parent) : QMainWindow { parent }
{
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
    isCustomTheme = globalSettings->value("isCustomTheme").value<bool>();

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

    isAutoCheckUpdates = globalSettings->value("isAutoCheckUpdates").value<bool>();

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    setMinimumSize(600, 600);

    // tabs
    tabs = new QTabWidget();
    tabs->setMovable(true);
    tabs->setTabPosition(QTabWidget::South);

    QHBoxLayout* BtnsL = new QHBoxLayout();

    saveBtn = new QPushButton("Apply");
    saveBtn->setFixedSize(100, 30);

    quitBtn = new QPushButton();
    quitBtn->setFixedSize(15, 15);

    QSpacerItem* spacer = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    BtnsL->addWidget(quitBtn);
    BtnsL->addItem(spacer);
    BtnsL->addWidget(saveBtn);

    // main
    QVBoxLayout* appInfoL = new QVBoxLayout();
    QVBoxLayout* subAppInfoL = new QVBoxLayout();
    QHBoxLayout* checkUpdatesBtnL = new QHBoxLayout();
    QHBoxLayout* updatesL = new QHBoxLayout();

    appName = new QLabel("CodeKeeper");
    appName->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    appName->setStyleSheet("font-size: 32px;");

    urlToRepo = new QLabel();
    urlToRepo->setText("<a style='color: #84a0bf; text-decoration: none; font-size: " + font_size
                       + "' "
                         "href=\"https://github.com/DXS-GROUP/CodeKeeper\">Source</a>");
    urlToRepo->setTextFormat(Qt::RichText);
    urlToRepo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    urlToRepo->setOpenExternalLinks(true);
    urlToRepo->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    versionInfo = new QLabel();
    versionInfo->setText("0.2.0");
    versionInfo->setAlignment(Qt::AlignCenter);

    checkUpdatesBtn = new QPushButton(
            QPixmap(":/retry.png").scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
            " Chech for updates");
    checkUpdatesBtn->setFixedSize(200, 30);
    checkUpdatesBtnL->addWidget(checkUpdatesBtn);

    autoUpdates = new QCheckBox("Check for updates automatically");
    autoUpdates->setChecked(isAutoCheckUpdates);

    updatesL->addWidget(autoUpdates);
    updatesL->setAlignment(Qt::AlignCenter);

    subAppInfoL->addWidget(appName);
    subAppInfoL->addWidget(urlToRepo);
    subAppInfoL->addWidget(versionInfo);
    subAppInfoL->addLayout(checkUpdatesBtnL);
    subAppInfoL->addLayout(updatesL);

    appInfoL->addLayout(subAppInfoL);

    // sync
    QGridLayout* mainSyncLayout = new QGridLayout();

    gitLabel = new QLabel("Sync settings");
    gitLabel->setStyleSheet("font-size: 24px;");
    gitLabel->setAlignment(Qt::AlignCenter);

    gitLabel2 = new QLabel("Data in commit");
    gitLabel2->setStyleSheet("font-size: 24px;");
    gitLabel2->setAlignment(Qt::AlignCenter);

    gitToken = new QLineEdit();
    gitToken->setPlaceholderText("GitHub token");
    gitToken->setAlignment(Qt::AlignCenter);
    gitToken->setFixedSize(300, 30);
    gitToken->setText(git_token);

    gitUser = new QLineEdit();
    gitUser->setPlaceholderText("GitHub user");
    gitUser->setAlignment(Qt::AlignCenter);
    gitUser->setFixedSize(300, 30);
    gitUser->setText(git_user);

    gitRepo = new QLineEdit();
    gitRepo->setPlaceholderText("GitHub repo");
    gitRepo->setAlignment(Qt::AlignCenter);
    gitRepo->setFixedSize(300, 30);
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
    QGridLayout* layout1 = new QGridLayout();

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
    fontSize->setFixedHeight(30);
    fontSelector = new QFontComboBox();
    fontSelector->setFixedHeight(30);
    themeSelector = new QComboBox();
    themeSelector->setFixedHeight(30);

    customTitleBar = new QCheckBox();
    customTitleBar->setText("Use custom titlebar");
    customTitleBar->setChecked(isCustomTitlebar);

    qDebug() << "isCustomTheme: " << isCustomTheme;

    customTheme = new QCheckBox();
    customTheme->setText("Use custom theme");
    customTheme->setChecked(isCustomTheme);

    themeSelector->addItem("Dark");
    themeSelector->addItem("Light");

    layout1->addWidget(mainTitle, 0, 2, 0, 4);
    layout1->addWidget(customTheme, 1, 2, 1, 4, Qt::AlignHCenter);
    layout1->addWidget(customTitleBar, 2, 2, 1, 4, Qt::AlignHCenter);
    layout1->addWidget(fontLabel, 3, 3);
    layout1->addWidget(fontSelector, 3, 4);
    layout1->addWidget(fontSizeLabel, 4, 3);
    layout1->addWidget(fontSize, 4, 4);
    layout1->addWidget(themeLabel, 5, 3);
    layout1->addWidget(themeSelector, 5, 4);

    // storage tab
    QGridLayout* storageL = new QGridLayout;
    storageL->setSpacing(10);

    storageLabel = new QLabel();
    storageLabel->setText("Storage settings");
    storageLabel->setAlignment(Qt::AlignCenter);
    storageLabel->setStyleSheet("font-size: 32px;");

    pathToFolder = new QLineEdit();
    pathToFolder->setText("Directory");
    pathToFolder->setPlaceholderText("Directory");
    pathToFolder->setMaximumHeight(30);
    pathToFolder->setText(path);
    pathToFolder->setAlignment(Qt::AlignCenter);

    openFolder = new QPushButton(
            QPixmap(":/open.png").scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation), " Browse");
    openFolder->setMaximumHeight(30);

    storageL->setSpacing(10);
    storageL->addWidget(storageLabel, 0, 1, 0, 4);
    storageL->addWidget(pathToFolder, 1, 3);
    storageL->addWidget(openFolder, 2, 3);

    // projects content tab
    QGridLayout* projectsContentL = new QGridLayout;
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

    QSpacerItem* checkBoxSpacer1 = new QSpacerItem(30, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem* checkBoxSpacer2 = new QSpacerItem(30, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    QVBoxLayout* checkboxLayout = new QVBoxLayout();
    checkboxLayout->setAlignment(Qt::AlignCenter);

    checkboxLayout->addItem(checkBoxSpacer1);
    checkboxLayout->addWidget(CisCreated);
    checkboxLayout->addWidget(CisReleaseDate);
    checkboxLayout->addWidget(CisLastCommit);
    checkboxLayout->addWidget(CisPullReq);
    checkboxLayout->addWidget(CisLicense);
    checkboxLayout->addWidget(CisRelease);
    checkboxLayout->addWidget(CisIssue);
    checkboxLayout->addWidget(CisDownloads);
    checkboxLayout->addWidget(CisCommit);
    checkboxLayout->addWidget(CisLang);
    checkboxLayout->addWidget(CisStars);
    checkboxLayout->addWidget(CisForks);
    checkboxLayout->addWidget(CisRepoSize);
    checkboxLayout->addItem(checkBoxSpacer2);

    projectsContentL->addWidget(projectsContentLabel, 0, 0, 1, 1, Qt::AlignCenter);
    projectsContentL->addLayout(checkboxLayout, 2, 0, 1, 1, Qt::AlignCenter);

    // info tab
    QWidget* aboutTab = new QWidget();
    QVBoxLayout* aboutTabLayout = new QVBoxLayout(aboutTab);

    aboutTabLayout->addLayout(appInfoL);

    tabs->addTab(aboutTab, "About");

    // sync tab
    QWidget* syncTab = new QWidget();
    QVBoxLayout* syncTabLayout = new QVBoxLayout(syncTab);

    syncTabLayout->addLayout(mainSyncLayout);

    tabs->addTab(syncTab, "Sync");

    // storage tab
    QWidget* storageTab = new QWidget();
    QVBoxLayout* storageTabLayout = new QVBoxLayout(storageTab);

    storageTabLayout->addLayout(storageL);

    tabs->addTab(storageTab, "Storage");

    // main tab
    QWidget* appereanceTab = new QWidget();
    QVBoxLayout* appereanceTabLayout = new QVBoxLayout(appereanceTab);

    appereanceTabLayout->addLayout(layout1);

    tabs->addTab(appereanceTab, "Appereance");

    // projects content
    QWidget* projectsContentTab = new QWidget();
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

    mainLayout->addLayout(BtnsL);
    mainLayout->addWidget(tabs);

    // connects
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveData()));
    connect(quitBtn, SIGNAL(clicked()), this, SLOT(QuitW()));
    connect(checkUpdatesBtn, SIGNAL(clicked()), this, SLOT(checkUpdates(true)));
    connect(openFolder, SIGNAL(clicked()), this, SLOT(fopenFolder()));

    QTimer* repoTimer = new QTimer(this);
    qDebug() << "checking";

    QThread* repoTimerThread = new QThread;
    QObject::connect(repoTimerThread, &QThread::started, this, [this, repoTimer]() {
        connect(repoTimer, &QTimer::timeout, [=]() { checkRepo(); });
        repoTimer->start(100);

        qDebug() << "repoTimerThread started";
    });
    repoTimerThread->start();

    QThread* styleThread = new QThread;
    QObject::connect(styleThread, &QThread::started, this, [this]() {
        int font_size_int = font_size.toInt();
        setStyle2(&selectedFont, &font_size_int);

        qDebug() << "styleThread started";
    });
    styleThread->start();
}

SettingsWindow::~SettingsWindow() { }

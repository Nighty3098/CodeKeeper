#include "settingswindow.h"

#include <QGraphicsBlurEffect>
#include <QSpacerItem>
#include <QThread>
#include <QtWidgets>

#include "mainwindow.cpp"
#include "mainwindow.h"
#include "settingsFunc/functional.cpp"

SettingsWindow::SettingsWindow(QWidget *parent) : QMainWindow{parent}
{
    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    selectedFont = globalSettings->value("font").value<QFont>();
    font_size = globalSettings->value("fontSize").value<QString>();
    theme = globalSettings->value("theme").value<int>();
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
    appLang = globalSettings->value("lang").value<int>();

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setMinimumSize(650, 650);

    mainLayout = new QVBoxLayout(centralWidget);

    sizeGrip = new QSizeGrip(this);

    sizeGrip->setFixedSize(11, 11);
    sizeGrip->setVisible(true);
    sizeGrip->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    // tabs
    tabs = new QTabWidget();
    tabs->setMovable(true);
    tabs->setTabPosition(QTabWidget::South);

    QHBoxLayout *BtnsL = new QHBoxLayout();

    saveBtn = new QPushButton(tr("Apply"));
    saveBtn->setFixedSize(100, 25);

    quitBtn = new QPushButton();
    quitBtn->setFixedSize(13, 13);

    QSpacerItem *spacer = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    BtnsL->addWidget(quitBtn);
    BtnsL->addItem(spacer);
    BtnsL->addWidget(saveBtn);

    // main
    QGridLayout *subAppInfoL = new QGridLayout();

    appName = new QLabel("CodeKeeper");
    appName->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    appName->setStyleSheet("font-size: 42px;");

    urlToRepo = new QLabel();
    urlToRepo->setText("<a style='color: #a9bf85; text-decoration: none; font-size: " + font_size +
                       "' "
                       "href=\"https://github.com/DXS-GROUP/CodeKeeper\">Source</a>");
    urlToRepo->setTextFormat(Qt::RichText);
    urlToRepo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    urlToRepo->setOpenExternalLinks(true);
    urlToRepo->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

    versionInfo = new QLabel();
    versionInfo->setText("0.2.3");
    versionInfo->setAlignment(Qt::AlignCenter);

    checkUpdatesBtn = new QPushButton(
        QPixmap(":/retry.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr(" Check for updates"));
    checkUpdatesBtn->setFixedSize(200, 25);

    autoUpdates = new QCheckBox(tr("Check for updates automatically"));
    autoUpdates->setChecked(isAutoCheckUpdates);

    warningLabel =
        new QLabel(tr("Some chips are in development and may not work properly.\nIf you notice a bug, please "
                      "write about it to the developer or to the support bot."));
    warningLabel->setAlignment(Qt::AlignCenter);

    subAppInfoL->addWidget(appName, 0, 0, 2, 2, Qt::AlignCenter);
    subAppInfoL->addWidget(urlToRepo, 3, 0, 1, 2, Qt::AlignCenter);
    subAppInfoL->addWidget(versionInfo, 4, 0, 1, 2, Qt::AlignHCenter | Qt::AlignBottom);
    subAppInfoL->addWidget(checkUpdatesBtn, 5, 0, 1, 2, Qt::AlignCenter);
    subAppInfoL->addWidget(autoUpdates, 6, 0, 1, 2, Qt::AlignCenter | Qt::AlignTop);
    subAppInfoL->addWidget(warningLabel, 7, 0, 1, 2, Qt::AlignCenter);

    // sync
    QGridLayout *mainSyncLayout = new QGridLayout();

    gitLabel = new QLabel(tr("Sync settings"));
    gitLabel->setStyleSheet("font-size: 24px;");
    gitLabel->setAlignment(Qt::AlignCenter);

    gitLabel2 = new QLabel(tr("Data in commit"));
    gitLabel2->setStyleSheet("font-size: 24px;");
    gitLabel2->setAlignment(Qt::AlignCenter);

    gitToken = new QLineEdit();
    gitToken->setPlaceholderText(tr("GitHub token"));
    gitToken->setAlignment(Qt::AlignCenter);
    gitToken->setFixedSize(300, 25);
    gitToken->setText(git_token);
    gitToken->setEchoMode(QLineEdit::Password);

    gitUser = new QLineEdit();
    gitUser->setPlaceholderText(tr("GitHub user"));
    gitUser->setAlignment(Qt::AlignCenter);
    gitUser->setFixedSize(300, 25);
    gitUser->setText(git_user);

    gitRepo = new QLineEdit();
    gitRepo->setPlaceholderText(tr("GitHub repo"));
    gitRepo->setAlignment(Qt::AlignCenter);
    gitRepo->setFixedSize(300, 25);
    gitRepo->setText(git_repo);

    autoSyncAfterStart = new QCheckBox(tr("Auto sync after start"));

    isDate = new QCheckBox(tr("Date"));
    isDate->setChecked(isDateB);
    isTime = new QCheckBox(tr("Time"));
    isTime->setChecked(isTimeB);
    isHost = new QCheckBox(tr("Host"));
    isHost->setChecked(isHostB);
    isSync = new QCheckBox(tr("Auto sync after start"));
    isSync->setChecked(isAutoSyncB);

    repoAvailability = new QLabel(tr("Repo"));
    repoAvailability->setAlignment(Qt::AlignHCenter);

    mainSyncLayout->setSpacing(5);
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

    mainTitle = new QLabel(tr("App settings"));
    mainTitle->setAlignment(Qt::AlignCenter);
    mainTitle->setStyleSheet("font-size: 32px;");

    fontLabel = new QLabel(tr("Font:"));
    fontLabel->setAlignment(Qt::AlignCenter);
    fontSizeLabel = new QLabel(tr("Font size:"));
    fontSizeLabel->setAlignment(Qt::AlignCenter);
    themeLabel = new QLabel(tr("Theme:"));
    themeLabel->setAlignment(Qt::AlignCenter);

    fontSize = new QSpinBox();
    fontSize->setFixedHeight(25);
    fontSelector = new QFontComboBox();
    fontSelector->setFixedHeight(25);
    themeSelector = new QComboBox();
    themeSelector->setFixedHeight(25);

    customTitleBar = new QCheckBox();
    customTitleBar->setText(tr("Use custom titlebar"));
    customTitleBar->setChecked(isCustomTitlebar);

    qDebug() << "isCustomTheme: " << isCustomTheme;

    customTheme = new QCheckBox();
    customTheme->setText(tr("Use custom theme"));
    customTheme->setChecked(isCustomTheme);

    if (isCustomTheme)
    {
        themeSelector->setEnabled(true);
    }
    else
    {
        themeSelector->setEnabled(false);
    }

    themeSelector->addItem(tr("Dark"));
    themeSelector->addItem(tr("Light"));
    themeSelector->setCurrentIndex(theme);

    langSelector = new QComboBox();
    langSelector->setFixedHeight(25);
    langSelector->addItem(QIcon(":/usa.png"), tr("English"));
    langSelector->addItem(QIcon(":/russian.png"), tr("Russian"));
    // langSelector->addItem(QIcon(":/japan.png"), tr("Japanese"));
    // langSelector->addItem(QIcon(":/german.png"), tr("Germany"));
    // langSelector->addItem(QIcon(":/spanish.png"), tr("Spanish"));

    langSelector->setCurrentIndex(appLang);

    langLabel = new QLabel(tr("Language:"));
    langLabel->setAlignment(Qt::AlignCenter);

    layout1->setSpacing(5);
    layout1->addWidget(mainTitle, 0, 2, 0, 4);
    layout1->addWidget(customTheme, 1, 2, 1, 4, Qt::AlignHCenter);
    layout1->addWidget(customTitleBar, 2, 2, 1, 4, Qt::AlignHCenter);
    layout1->addWidget(fontLabel, 3, 3);
    layout1->addWidget(fontSelector, 3, 4);
    layout1->addWidget(fontSizeLabel, 4, 3);
    layout1->addWidget(fontSize, 4, 4);
    layout1->addWidget(themeLabel, 5, 3);
    layout1->addWidget(themeSelector, 5, 4);
    layout1->addWidget(langLabel, 6, 3);
    layout1->addWidget(langSelector, 6, 4);

    // storage tab
    QGridLayout *storageL = new QGridLayout;
    storageL->setSpacing(5);

    storageLabel = new QLabel();
    storageLabel->setText(tr("Storage settings"));
    storageLabel->setAlignment(Qt::AlignCenter);
    storageLabel->setStyleSheet("font-size: 32px;");

    pathToFolder = new QLineEdit();
    pathToFolder->setText(tr("Directory"));
    pathToFolder->setPlaceholderText(tr("Directory"));
    pathToFolder->setMaximumHeight(25);
    pathToFolder->setText(path);
    pathToFolder->setAlignment(Qt::AlignCenter);

    openFolder = new QPushButton(
        QPixmap(":/open.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        " Browse");
    openFolder->setMaximumHeight(25);

    storageL->setSpacing(5);
    storageL->addWidget(storageLabel, 0, 1, 0, 4);
    storageL->addWidget(pathToFolder, 1, 3);
    storageL->addWidget(openFolder, 2, 3);

    // projects content tab
    QGridLayout *projectsContentL = new QGridLayout;
    projectsContentL->setSpacing(5);
    projectsContentL->setAlignment(Qt::AlignCenter);

    projectsContentLabel = new QLabel(tr("Projects content"));
    projectsContentLabel->setStyleSheet("font-size: 32px;");
    projectsContentLabel->setAlignment(Qt::AlignCenter);
    projectsContentLabel->setFixedHeight(150);

    CisCreated = new QCheckBox(tr("Created time"));
    CisCreated->setChecked(isCreated);
    CisReleaseDate = new QCheckBox(tr("Last release time"));
    CisReleaseDate->setChecked(isReleaseDate);
    CisLastCommit = new QCheckBox(tr("Last commit time"));
    CisLastCommit->setChecked(isLastCommit);
    CisPullReq = new QCheckBox(tr("Total pull requests"));
    CisPullReq->setChecked(isPullReq);
    CisLicense = new QCheckBox(tr("License"));
    CisLicense->setChecked(isLicense);
    CisRelease = new QCheckBox(tr("Release"));
    CisRelease->setChecked(isRelease);
    CisIssue = new QCheckBox(tr("Issues"));
    CisIssue->setChecked(isIssue);
    CisDownloads = new QCheckBox(tr("Downloads"));
    CisDownloads->setChecked(isDownloads);
    CisCommit = new QCheckBox(tr("Commits"));
    CisCommit->setChecked(isCommit);
    CisLang = new QCheckBox(tr("Langs"));
    CisLang->setChecked(isLang);
    CisStars = new QCheckBox(tr("Stars"));
    CisStars->setChecked(isStars);
    CisForks = new QCheckBox(tr("Forks"));
    CisForks->setChecked(isForks);
    CisRepoSize = new QCheckBox(tr("Repo size"));
    CisRepoSize->setChecked(isRepoSize);

    QSpacerItem *checkBoxSpacer1 = new QSpacerItem(30, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *checkBoxSpacer2 = new QSpacerItem(30, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    QVBoxLayout *checkboxLayout = new QVBoxLayout();
    checkboxLayout->setSpacing(5);
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
    QWidget *aboutTab = new QWidget();
    QVBoxLayout *aboutTabLayout = new QVBoxLayout(aboutTab);

    aboutTabLayout->addLayout(subAppInfoL);

    tabs->addTab(aboutTab, tr("About"));

    // sync tab
    QWidget *syncTab = new QWidget();
    QVBoxLayout *syncTabLayout = new QVBoxLayout(syncTab);

    syncTabLayout->addLayout(mainSyncLayout);

    tabs->addTab(syncTab, tr("Sync"));

    // storage tab
    QWidget *storageTab = new QWidget();
    QVBoxLayout *storageTabLayout = new QVBoxLayout(storageTab);

    storageTabLayout->addLayout(storageL);

    tabs->addTab(storageTab, tr("Storage"));

    // main tab
    QWidget *appereanceTab = new QWidget();
    QVBoxLayout *appereanceTabLayout = new QVBoxLayout(appereanceTab);

    appereanceTabLayout->addLayout(layout1);

    tabs->addTab(appereanceTab, tr("Appereance"));

    // projects content
    QWidget *projectsContentTab = new QWidget();
    projectsContentTab->setLayout(projectsContentL);
    tabs->addTab(projectsContentTab, tr("Projects"));

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
    connect(checkUpdatesBtn, &QPushButton::clicked, this, [=]() { checkUpdates(); });
    connect(openFolder, SIGNAL(clicked()), this, SLOT(fopenFolder()));

    QTimer *repoTimer = new QTimer(this);
    qDebug() << "checking";

    QThread *repoTimerThread = new QThread;
    QObject::connect(repoTimerThread, &QThread::started, this, [this, repoTimer]() {
        connect(repoTimer, &QTimer::timeout, [=]() { checkRepo(); });
        repoTimer->start(2000);

        qDebug() << "repoTimerThread started";
    });
    repoTimerThread->start();

    QThread *styleThread = new QThread;
    QObject::connect(styleThread, &QThread::started, this, [this]() {
        int font_size_int = font_size.toInt();
        setStyle2(&selectedFont, &font_size_int);

        qDebug() << "styleThread started";
    });
    styleThread->start();
}

SettingsWindow::~SettingsWindow()
{
}

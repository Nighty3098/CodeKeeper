#include "settingswindow.h"

#include <QGraphicsBlurEffect>
#include <QSpacerItem>
#include <QtWidgets>

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
    path = globalSettings->value("path").value<QDir>();

    git_repo = globalSettings->value("git_repo").value<QString>();
    git_user = globalSettings->value("git_user").value<QString>();
    git_token = globalSettings->value("git_token").value<QString>();

    isTimeB = globalSettings->value("isTime").value<bool>();
    isDateB = globalSettings->value("isDate").value<bool>();
    isHostB = globalSettings->value("isHost").value<bool>();
    isAutoSyncB = globalSettings->value("isAutoSync").value<bool>();

    this->setStyleSheet(file.readAll());

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    setMinimumSize(500, 500);

    // tabs
    tabs = new QTabWidget();
    tabs->setMovable(true);

    QHBoxLayout *BtnsL = new QHBoxLayout();

    saveBtn = new QPushButton(QPixmap(":/save.png"), " Save");
    saveBtn->setFixedSize(100, 30);

    quitBtn = new QPushButton(QPixmap(":/quit.png"), " Quit");
    quitBtn->setFixedSize(100, 30);

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
    urlToRepo->setText("<a style='color: #84a0bf' "
                       "href=\"https://github.com/Nighty3098/CodeKeeper\">Nighty3098/"
                       "CodeKeeper</a>");
    urlToRepo->setTextFormat(Qt::RichText);
    urlToRepo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    urlToRepo->setOpenExternalLinks(true);
    urlToRepo->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    versionInfo = new QLabel();
    versionInfo->setText("Version: 0.1.0");
    versionInfo->setAlignment(Qt::AlignCenter);

    checkUpdatesBtn = new QPushButton(QPixmap(":/retry.png"), " Chech for updates");
    checkUpdatesBtn->setFixedSize(200, 30);
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
    gitToken->setFixedSize(200, 30);
    gitToken->setText(git_token);

    gitUser = new QLineEdit();
    gitUser->setPlaceholderText("GitHub user");
    gitUser->setAlignment(Qt::AlignCenter);
    gitUser->setFixedSize(200, 30);
    gitUser->setText(git_user);

    gitRepo = new QLineEdit();
    gitRepo->setPlaceholderText("GitHub repo");
    gitRepo->setAlignment(Qt::AlignCenter);
    gitRepo->setFixedSize(200, 30);
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

    mainSyncLayout->setSpacing(10);
    mainSyncLayout->addWidget(gitLabel, 0, 2, 1, 1);
    mainSyncLayout->addWidget(gitToken, 1, 2, 1, 1);
    mainSyncLayout->addWidget(gitUser, 2, 2, 1, 1);
    mainSyncLayout->addWidget(gitRepo, 3, 2, 1, 1);
    mainSyncLayout->addWidget(isSync, 4, 2, 1, 1, Qt::AlignHCenter);
    mainSyncLayout->addWidget(gitLabel2, 5, 2, 1, 1);
    mainSyncLayout->addWidget(isDate, 6, 2, 1, 1, Qt::AlignHCenter);
    mainSyncLayout->addWidget(isTime, 7, 2, 1, 1, Qt::AlignHCenter);
    mainSyncLayout->addWidget(isHost, 8, 2, 1, 1, Qt::AlignHCenter);

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
    fontSelector = new QFontComboBox();
    themeSelector = new QComboBox();

    themeSelector->addItem("Dark");
    themeSelector->addItem("Light");

    layout1->addWidget(mainTitle, 0, 2, 0, 4);
    layout1->addWidget(fontLabel, 1, 3);
    layout1->addWidget(fontSelector, 1, 4);
    layout1->addWidget(fontSizeLabel, 2, 3);
    layout1->addWidget(fontSize, 2, 4);
    layout1->addWidget(themeLabel, 3, 3);
    layout1->addWidget(themeSelector, 3, 4);

    // storage tab
    QGridLayout *storageL = new QGridLayout;
    storageL->setSpacing(30);

    storageLabel = new QLabel();
    storageLabel->setText("Storage settings");
    storageLabel->setAlignment(Qt::AlignCenter);
    storageLabel->setStyleSheet("font-size: 32px;");

    pathToFolder = new QLineEdit();
    pathToFolder->setText("Directory");
    pathToFolder->setPlaceholderText("Directory");
    pathToFolder->setMaximumHeight(30);
    pathToFolder->setText(path.absolutePath());

    openFolder = new QPushButton(QPixmap(":/open.png"), " Browse");
    openFolder->setMaximumHeight(30);

    storageL->setSpacing(10);
    storageL->addWidget(storageLabel, 0, 1, 0, 4);
    storageL->addWidget(pathToFolder, 1, 3);
    storageL->addWidget(openFolder, 2, 3);

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

    QIcon aboutIco(":/about.png");
    QIcon syncIco(":/refresh.png");
    QIcon storageIco(":/storage.png");
    QIcon paletteIco(":/palette.png");

    tabs->setTabIcon(tabs->indexOf(aboutTab), aboutIco);
    tabs->setTabIcon(tabs->indexOf(syncTab), syncIco);
    tabs->setTabIcon(tabs->indexOf(storageTab), storageIco);
    tabs->setTabIcon(tabs->indexOf(appereanceTab), paletteIco);

    mainLayout->addWidget(tabs);
    mainLayout->addLayout(BtnsL);

    // connects
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveData()));
    connect(quitBtn, SIGNAL(clicked()), this, SLOT(QuitW()));
    connect(checkUpdatesBtnL, SIGNAL(clicked()), this, SLOT(checkUpdates()));
    connect(openFolder, SIGNAL(clicked()), this, SLOT(fopenFolder()));

    setFontPr2();
}

SettingsWindow::~SettingsWindow() { }

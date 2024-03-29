#include "settingswindow.h"

#include <QGraphicsBlurEffect>
#include <QSpacerItem>
#include <QtWidgets>

#include "mainwindow.cpp"
#include "mainwindow.h"
#include "settingsFunc/functional.cpp"

SettingsWindow::SettingsWindow(QWidget *parent) : QMainWindow{parent} {
    // visual
    QFile file(":/stylesheet/stylesheet_setting_window.qss");
    file.open(QFile::ReadOnly);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    selectedFont = globalSettings->value("font").value<QFont>();
    font_size = globalSettings->value("fontSize").value<QString>();
    theme = globalSettings->value("theme").value<QString>();
    path = globalSettings->value("path").value<QString>();

    this->setStyleSheet(file.readAll());

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    // setStyleSheet("background-color: #444c5d; color: #ffffff;");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    setMinimumSize(500, 500);

    // tabs
    tabs = new QTabWidget();
    tabs->setMovable(true);
    // tabs->setTabPosition(QTabWidget::South);

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
    // urlToRepo->setPixmap(QPixmap(":/github.png"));
    urlToRepo->setText(
        "<a style='color: #84a0bf' "
        "href=\"https://github.com/Nighty3098/CodeKeeper\">Nighty3098/"
        "CodeKeeper</a>");
    urlToRepo->setTextFormat(Qt::RichText);
    urlToRepo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    urlToRepo->setOpenExternalLinks(true);
    urlToRepo->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    versionInfo = new QLabel();
    versionInfo->setText("Version: 0.0.3");
    versionInfo->setAlignment(Qt::AlignCenter);

    checkUpdatesBtn =
        new QPushButton(QPixmap(":/retry.png"), " Chech for updates");
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

    gitUser = new QLineEdit();
    gitUser->setPlaceholderText("GitHub user");
    gitUser->setAlignment(Qt::AlignCenter);
    gitUser->setFixedSize(200, 30);

    gitRepo = new QLineEdit();
    gitRepo->setPlaceholderText("GitHub repo");
    gitRepo->setAlignment(Qt::AlignCenter);
    gitRepo->setFixedSize(200, 30);

    autoSyncAfterStart = new QCheckBox("Auto sync after start");

    isDate = new QCheckBox("Date");
    isTime = new QCheckBox("Time");
    isHost = new QCheckBox("Host");

    mainSyncLayout->addWidget(gitLabel, 0, 2);
    mainSyncLayout->addWidget(gitToken, 1, 2);
    mainSyncLayout->addWidget(gitUser, 2, 2);
    mainSyncLayout->addWidget(gitRepo, 3, 2);
    mainSyncLayout->addWidget(gitLabel2, 4, 2);
    mainSyncLayout->addWidget(isDate, 5, 2);
    mainSyncLayout->addWidget(isTime, 6, 2);
    mainSyncLayout->addWidget(isHost, 7, 2);

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
    QGridLayout* storageL = new QGridLayout;
    storageL->setSpacing(30);

    storageLabel = new QLabel();
    storageLabel->setText("Storage settings");
    storageLabel->setAlignment(Qt::AlignCenter);
    storageLabel->setStyleSheet("font-size: 32px;");

    pathToFolder = new QLineEdit();
    pathToFolder->setText("Directory");
    pathToFolder->setPlaceholderText("Directory");
    pathToFolder->setMaximumHeight(30);
    pathToFolder->setText(path);

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

    mainLayout->addWidget(tabs);
    mainLayout->addLayout(BtnsL);


    // connects
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveData()));
    connect(quitBtn, SIGNAL(clicked()), this, SLOT(QuitW()));
    connect(checkUpdatesBtnL, SIGNAL(clicked()), this, SLOT(checkUpdates()));
    connect(openFolder, SIGNAL(clicked()), this, SLOT(fopenFolder()));

    setFontPr2();
}

SettingsWindow::~SettingsWindow() {}

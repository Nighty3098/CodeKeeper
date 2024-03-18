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
    QFont selectedFont = globalSettings->value("font").value<QFont>();
    QString font_size = globalSettings->value("fontSize").value<QString>();
    QString theme = globalSettings->value("theme").value<QString>();

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

    saveBtn = new QPushButton("Save");
    saveBtn->setFixedSize(100, 30);

    quitBtn = new QPushButton("Quit");
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
        new QPushButton(QPixmap(":/retry.png"), "Chech for updates");
    checkUpdatesBtn->setFixedSize(200, 30);
    checkUpdatesBtnL->addWidget(checkUpdatesBtn);

    subAppInfoL->addWidget(appName);
    subAppInfoL->addWidget(urlToRepo);
    subAppInfoL->addWidget(versionInfo);
    subAppInfoL->addLayout(checkUpdatesBtnL);

    appInfoL->addLayout(subAppInfoL);

    // sync
    QVBoxLayout *mainSyncLayout = new QVBoxLayout();

    gitLabel = new QLabel("Sync settings");
    gitLabel->setStyleSheet("font-size: 24px;");
    gitLabel->setAlignment(Qt::AlignCenter);

    gitLabel2 = new QLabel("Data in commit");
    gitLabel2->setStyleSheet("font-size: 24px;");
    gitLabel2->setAlignment(Qt::AlignCenter);

    QVBoxLayout *syncLayout = new QVBoxLayout();
    QHBoxLayout *tokenL = new QHBoxLayout();
    QHBoxLayout *userL = new QHBoxLayout();
    QHBoxLayout *repoL = new QHBoxLayout();
    QHBoxLayout *autoSyncL = new QHBoxLayout();

    QVBoxLayout *sync2Layout = new QVBoxLayout();

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

    tokenL->addWidget(gitToken);
    userL->addWidget(gitUser);
    repoL->addWidget(gitRepo);

    autoSyncL->addWidget(autoSyncAfterStart);
    autoSyncL->setAlignment(Qt::AlignCenter);

    syncLayout->addWidget(gitLabel);
    syncLayout->addLayout(tokenL);
    syncLayout->addLayout(userL);
    syncLayout->addLayout(repoL);
    syncLayout->addLayout(autoSyncL);

    QVBoxLayout *sync2LayoutL = new QVBoxLayout();
    sync2LayoutL->addWidget(gitLabel2);

    sync2Layout->addWidget(isDate);
    sync2Layout->addWidget(isTime);
    sync2Layout->addWidget(isHost);
    sync2Layout->setAlignment(Qt::AlignCenter);

    sync2LayoutL->addLayout(sync2Layout);

    mainSyncLayout->addLayout(syncLayout);
    mainSyncLayout->addLayout(sync2LayoutL);

    // appereance

    QVBoxLayout *layout1 = new QVBoxLayout();
    QHBoxLayout *fontSizeL = new QHBoxLayout();
    QHBoxLayout *fontL = new QHBoxLayout();
    QHBoxLayout *themeL = new QHBoxLayout();

    mainTitle = new QLabel("App settings");
    mainTitle->setAlignment(Qt::AlignCenter);
    mainTitle->setStyleSheet("font-size: 32px;");

    fontLabel = new QLabel("Font:");
    fontSizeLabel = new QLabel("Font size:");
    themeLabel = new QLabel("Theme:");

    fontSize = new QSpinBox();
    fontSelector = new QFontComboBox();
    themeSelector = new QComboBox();

    themeSelector->addItem("Dark");
    themeSelector->addItem("Light");

    fontSizeL->addWidget(fontSizeLabel);
    fontSizeL->addWidget(fontSize);

    fontL->addWidget(fontLabel);
    fontL->addWidget(fontSelector);

    themeL->addWidget(themeLabel);
    themeL->addWidget(themeSelector);

    layout1->addWidget(mainTitle);
    layout1->addLayout(fontL);
    layout1->addLayout(fontSizeL);
    layout1->addLayout(themeL);

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

    tabs->addTab(storageTab, "Storage");

    // main tab
    QWidget *appereanceTab = new QWidget();
    QVBoxLayout *appereanceTabLayout = new QVBoxLayout(appereanceTab);

    appereanceTabLayout->addLayout(layout1);

    tabs->addTab(appereanceTab, "Appereance");

    mainLayout->addWidget(tabs);
    mainLayout->addLayout(BtnsL);



    // set font 
    tabs->setFont(selectedFont);
    tabs->setStyleSheet("font-size: " + font_size + "pt;");

    saveBtn->setFont(selectedFont);
    saveBtn->setStyleSheet("font-size: " + font_size + "pt;");

    quitBtn->setFont(selectedFont);
    quitBtn->setStyleSheet("font-size: " + font_size + "pt;");

    appName->setFont(selectedFont);

    urlToRepo->setFont(selectedFont);
    urlToRepo->setStyleSheet("font-size: " + font_size + "pt;");

    versionInfo->setFont(selectedFont);
    versionInfo->setStyleSheet("font-size: " + font_size + "pt;");

    checkUpdatesBtn->setFont(selectedFont);
    checkUpdatesBtn->setStyleSheet("font-size: " + font_size + "pt;");

    fontSize->setFont(selectedFont);
    fontSize->setStyleSheet("font-size: " + font_size + "pt;");

    fontSelector->setFont(selectedFont);
    fontSelector->setStyleSheet("font-size: " + font_size + "pt;");

    themeSelector->setFont(selectedFont);
    themeSelector->setStyleSheet("font-size: " + font_size + "pt;");

    gitLabel->setFont(selectedFont);

    gitLabel2->setFont(selectedFont);

    gitUser->setFont(selectedFont);
    gitUser->setStyleSheet("font-size: " + font_size + "pt;");

    gitRepo->setFont(selectedFont);
    gitRepo->setStyleSheet("font-size: " + font_size + "pt;");

    autoSyncAfterStart->setFont(selectedFont);
    autoSyncAfterStart->setStyleSheet("font-size: " + font_size + "pt;");

    isDate->setFont(selectedFont);
    isDate->setStyleSheet("font-size: " + font_size + "pt;");

    isTime->setFont(selectedFont);
    isTime->setStyleSheet("font-size: " + font_size + "pt;");

    isHost->setFont(selectedFont);
    isHost->setStyleSheet("font-size: " + font_size + "pt;");

    mainTitle->setFont(selectedFont);

    fontLabel->setFont(selectedFont);
    fontSizeLabel->setFont(selectedFont);

    fontSizeLabel->setFont(selectedFont);
    fontSizeLabel->setStyleSheet("font-size: " + font_size + "pt;");

    themeLabel->setFont(selectedFont);
    themeLabel->setStyleSheet("font-size: " + font_size + "pt;");

    // set Data
    fontSelector->setCurrentText(selectedFont.toString());
    fontSize->setValue(font_size.toInt());
    themeSelector->setCurrentText(theme);

    // connects
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveData()));
    connect(quitBtn, SIGNAL(clicked()), this, SLOT(QuitW()));
    connect(checkUpdatesBtnL, SIGNAL(clicked()), this, SLOT(checkUpdates()));
}

SettingsWindow::~SettingsWindow() {}

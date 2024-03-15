#include "settingswindow.h"
#include <QtWidgets>
#include <QSpacerItem>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QMainWindow{parent}
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    setMinimumSize(500, 500);

    // tabs
    tabs = new QTabWidget();
    tabs->setMovable(true);
    // tabs->setTabPosition(QTabWidget::South);
   
    QHBoxLayout *saveBtnL = new QHBoxLayout();
    saveBtn = new QPushButton("Save Quit");
    saveBtn->setFixedSize(200, 30);
    saveBtnL->addWidget(saveBtn);


    // main

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


    // main tab
    QWidget *mainTab = new QWidget();
    QVBoxLayout *mainTabLayout = new QVBoxLayout(mainTab);

    mainTabLayout->addLayout(layout1);

    tabs->addTab(mainTab, "App settings");

    // sync tab 
    QWidget *syncTab = new QWidget();
    QVBoxLayout *syncTabLayout = new QVBoxLayout(syncTab);

    syncTabLayout->addLayout(mainSyncLayout);

    tabs->addTab(syncTab, "Sync settings");

    // storage tab 
    QWidget *storageTab = new QWidget();
    QVBoxLayout *storageTabLayout = new QVBoxLayout(storageTab);

    tabs->addTab(storageTab, "Storage");



    mainLayout->addWidget(tabs);
    mainLayout->addLayout(saveBtnL);
}

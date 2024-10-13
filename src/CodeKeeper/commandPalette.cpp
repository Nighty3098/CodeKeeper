#include "commandPalette.h"
#include "mainwindow.h"

#include "keeperFunc/commandsFunc.cpp"

CommandPalette::CommandPalette(QWidget *parent) : QMainWindow{parent}
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QGridLayout(centralWidget);
    mainLayout->setSpacing(10);

    int font_size_int = font_size.toInt();

    getSettingsData();
    setWindowSize();
    setWindowPosition();

    searchBar = new QLineEdit();
    searchBar->setPlaceholderText(tr("CodeKeeper"));
    searchBar->setFixedHeight(30);
    searchBar->setAlignment(Qt::AlignCenter);

    closeBtn = new QPushButton();
    closeBtn->setFixedSize(13, 13);
    closeBtn->setFlat(true);

    closeBtn->setStyleSheet("QPushButton {"
                            "    border-radius: 6px;"
                            "    border-color: rgba(0, 0, 0, 0);"
                            "    background-color: #e08581;"
                            "    background-repeat: no-repeat;"
                            "    background-attachment: fixed;"
                            "}"

                            "QPushButton:hover {"
                            "    border-radius: 6px;"
                            "    border-color: rgba(0, 0, 0, 0);"
                            "    background-repeat: no-repeat;"
                            "    background-color: #e06a65;"
                            "    background-attachment: fixed;"
                            "}");

    listItems = new QListWidget();
    listItems->setSelectionMode(QAbstractItemView::SingleSelection);
    listItems->setStyleSheet(
        "QListWidget::item:selected {color: #000000; background-color: #a9bf85;border-radius: 5px; font-size: " +
        font_size + "pt;} QListWidget {font-size: " + font_size + "pt;}");

    settingsItem = new QListWidgetItem(tr("Settings"));
    syncItem = new QListWidgetItem(tr("Sync"));
    helpItem = new QListWidgetItem(tr("Help"));
    aboutItem = new QListWidgetItem(tr("About"));
    clearAllDataItem = new QListWidgetItem(tr("Remove all data"));
    userProfileItem = new QListWidgetItem(tr("User account"));

    listItems->addItem(settingsItem);
    listItems->addItem(syncItem);
    listItems->addItem(aboutItem);
    listItems->addItem(helpItem);
    listItems->addItem(clearAllDataItem);
    listItems->addItem(userProfileItem);

    searchBar->setFont(selectedFont);
    searchBar->setStyleSheet("font-size: " + font_size + "pt;");

    listItems->setFont(selectedFont);

    mainLayout->addWidget(closeBtn, 0, 0, Qt::AlignLeft);
    mainLayout->addWidget(searchBar, 1, 0);
    mainLayout->addWidget(listItems, 2, 0);

    connect(closeBtn, &QPushButton::clicked, this, [this]() { close(); });
    connect(searchBar, &QLineEdit::textChanged, this, &CommandPalette::filterList);
    connect(listItems, &QListWidget::itemActivated, this, &CommandPalette::activateCommand);
}

CommandPalette::~CommandPalette() {};

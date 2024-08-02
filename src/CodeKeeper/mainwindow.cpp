#include "mainwindow.h"

#include <md4c-html.h>

#include <QDragEnterEvent>
#include <QInputDialog>
#include <QMimeData>
#include <QPropertyAnimation>
#include <QSizeGrip>
#include <QThread>
#include <QWebEngineView>
#include <QtWidgets>

#include "3rdParty/qmarkdowntextedit/markdownhighlighter.h"
#include "keeperFunc/addConnects.cpp"
#include "keeperFunc/createMenu.cpp"
#include "keeperFunc/functional.cpp"
#include "keeperFunc/notesFunc.cpp"
#include "keeperFunc/projectsFunc.cpp"
#include "keeperFunc/tasksFunc.cpp"
#include "sql_db/projectsDB.cpp"
#include "sql_db/tasksDB.cpp"

Q_DECLARE_METATYPE(QDir)

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QTime startup;
    startup.start();

    qDebug() << "Starting CodeKeeper";

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setMinimumSize(900, 900);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    getSettingsData();

    if (isCustomTheme)
    {
        QFile custom_theme(":/stylesheet/custom_stylesheet.qss");
        if (custom_theme.open(QFile::ReadOnly))
        {
            QString customStyleSheet = custom_theme.readAll();
            qDebug() << "Loading custom stylesheet";
            setStyleSheet(customStyleSheet);
            custom_theme.close();
        }
        else
        {
            qDebug() << "Failed to open custom stylesheet file";
        }
    }
    else
    {
        QFile theme_file(":/stylesheet/stylesheet.qss");
        if (theme_file.open(QFile::ReadOnly))
        {
            QString defaultStyleSheet = theme_file.readAll();
            qDebug() << "Loading default stylesheet";
            setStyleSheet(defaultStyleSheet);
            theme_file.close();
        }
        else
        {
            qDebug() << "Failed to open default stylesheet file";
        }
    }

    QThread *updatesThread = new QThread;
    QObject::connect(updatesThread, &QThread::started, this, [this]() {
        qDebug() << "updatesThread started";

        if (isAutoCheckUpdates)
        {
            settingsWindow = new SettingsWindow(this);

            QString currentAppVersion = settingsWindow->versionInfo->text();
            QString newAppVersion = settingsWindow->getNewAppVersion();

            qDebug() << "Current app version:" << currentAppVersion;
            qDebug() << "New app version:" << newAppVersion;

            if (currentAppVersion == newAppVersion)
            {
            }
            else
            {
                settingsWindow->checkUpdates();
            }
        }
        else
        {
        }
    });
    updatesThread->start();

    closeBtn = new QPushButton();
    minimizeBtn = new QPushButton();
    maximizeBtn = new QPushButton();

    winControlL = new QHBoxLayout;
    winControlL->setSpacing(7);

    isFullScreen = false;

    sizeGrip = new QSizeGrip(this);
    sizeGrip->setFixedSize(11, 11);
    sizeGrip->setVisible(true);
    sizeGrip->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    sizeGrip2 = new QSizeGrip(this);
    sizeGrip2->setFixedSize(11, 11);
    sizeGrip2->setVisible(true);
    sizeGrip2->setStyleSheet("background-color: #febe30; border-radius: 5px;");

    sizeGrip3 = new QSizeGrip(this);
    sizeGrip3->setFixedSize(11, 11);
    sizeGrip3->setVisible(true);
    sizeGrip3->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    sizeGrip4 = new QSizeGrip(this);
    sizeGrip4->setFixedSize(11, 11);
    sizeGrip4->setVisible(true);
    sizeGrip4->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    windowTitle = new QLabel(tr(" ~ CodeKeeper ~ "));

    createCustomTitlebar();

    this->setMouseTracking(true);
    this->setMinimumSize(560, 400);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowIcon(QPixmap(":/icon.png"));

    mainLayout = new QGridLayout(centralWidget);
    mainLayout->setSpacing(0);

    // ========================================================
    timeLabel = new QLabel("");
    timeLabel->setAlignment(Qt::AlignBottom);

    dateLabel = new QLabel("");
    dateLabel->setAlignment(Qt::AlignTop);

    helloLabel = new QLabel();
    helloLabel->setAlignment(Qt::AlignVCenter);

    openSettingsBtn = new QPushButton(
        QPixmap(":/settings.png")
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    openSettingsBtn->setToolTip("<p style='color: #ffffff; border-radius: 5px; background-color: "
                                "#0D1117;'>Settings</p>");
    openSettingsBtn->setFixedSize(50, 50);
    openSettingsBtn->setFlat(true);

    syncDataBtn = new QPushButton(
        QPixmap(":/sync.png")
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    syncDataBtn->setToolTip("<p style='color: #ffffff; border-radius: 5px; "
                            "background-color: #0D1117;'>Sync</p>");
    syncDataBtn->setFixedSize(50, 50);
    syncDataBtn->setFlat(true);

    openAccountWindow = new QPushButton(
        QPixmap(":/user.png")
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    openAccountWindow->setToolTip("<p style='color: #ffffff; border-radius: 5px; background-color: "
                                  "#0D1117;'>Account</p>");
    openAccountWindow->setFixedSize(50, 50);
    openAccountWindow->setFlat(true);

    // ========================================================
    QHBoxLayout *menuLayout = new QHBoxLayout;
    QHBoxLayout *contentLayout = new QHBoxLayout;
    QVBoxLayout *notesCLayout = new QVBoxLayout;

    QSplitter *noteSplitter = new QSplitter(Qt::Horizontal);

    contentLayout->setSpacing(0);
    notesCLayout->setSpacing(0);

    menuLayout->setSpacing(0);
    menuLayout->setSizeConstraint(QLayout::SetFixedSize);
    menuLayout->setAlignment(Qt::AlignHCenter);

    QStringList filters;
    filters << ""
            << "*.md";

    iconProvider = new CustomIconProvider();

    notesDirModel = new QFileSystemModel();
    notesDirModel->setNameFilters(filters);
    notesDirModel->setNameFilterDisables(false);
    notesDirModel->iconProvider();
    notesDirModel->setIconProvider(iconProvider);

    notesList = new notesTree();
    notesList->setAnimated(true);
    notesList->setWordWrap(true);
    notesList->setDragDropMode(QAbstractItemView::DragDrop);
    notesList->setDefaultDropAction(Qt::MoveAction);
    notesList->setDragEnabled(true);
    notesList->setMaximumWidth(300);
    notesList->setHeaderHidden(true);
    notesList->setColumnHidden(1, true);
    notesList->setSortingEnabled(true);

    mdPreview = new QWebEngineView();
    mdPreview->setMinimumWidth(300);
    mdPreview->setAutoFillBackground(true);
    mdPreview->page()->setBackgroundColor(Qt::transparent);

    noteEdit = new NoteEditor();
    noteEdit->setPlaceholderText(tr(" Just start typing"));
    noteEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    noteEdit->setLineNumberEnabled(true);
    noteEdit->setLineNumbersCurrentLineColor("#51afef");
    noteEdit->setLineWidth(font_size.toInt());
    noteEdit->setHighlightingEnabled(true);

    noteSplitter->addWidget(notesList);
    noteSplitter->addWidget(noteEdit);
    noteSplitter->addWidget(mdPreview);

    noteSplitter->setStretchFactor(0, 1);
    noteSplitter->setStretchFactor(1, 1);
    noteSplitter->setStretchFactor(2, 1);

    // title
    noteNameLabel = new QLabel(tr("Note"));
    noteNameLabel->setAlignment(Qt::AlignCenter);
    connect(noteEdit, &QMarkdownTextEdit::textChanged, this, &MainWindow::setHeader);

    menuButton = new QToolButton;
    menuButton->setIcon(
        QPixmap(":/main.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    menuButton->setIconSize(QSize(10, 10));
    menuButton->setPopupMode(QToolButton::InstantPopup);

    menu = new QMenu(menuButton);

    createNotesMenu(menu, font_size);

    menuButton->setMenu(menu);

    setH1B = new QPushButton(
        QPixmap(":/h1.png")
            .scaled(font_size.toInt() + 3, font_size.toInt() + 3, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setH2B = new QPushButton(
        QPixmap(":/h2.png")
            .scaled(font_size.toInt() + 3, font_size.toInt() + 3, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setH3B = new QPushButton(
        QPixmap(":/h3.png")
            .scaled(font_size.toInt() + 3, font_size.toInt() + 3, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setListB = new QPushButton(
        QPixmap(":/list.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setLinkB = new QPushButton(
        QPixmap(":/link.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setBoldB = new QPushButton(
        QPixmap(":/bold.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setItalicB = new QPushButton(
        QPixmap(":/italic.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setStrikeB = new QPushButton(
        QPixmap(":/strikethrough.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setTaskB = new QPushButton(
        QPixmap(":/checkbox.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setNumListB = new QPushButton(
        QPixmap(":/numList.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setTableB = new QPushButton(
        QPixmap(":/table.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setQuoteB = new QPushButton(
        QPixmap(":/quote.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");

    setH1B->setFixedSize(20, 20);
    setH2B->setFixedSize(20, 20);
    setH3B->setFixedSize(20, 20);
    setListB->setFixedSize(20, 20);
    setLinkB->setFixedSize(20, 20);
    setBoldB->setFixedSize(20, 20);
    setItalicB->setFixedSize(20, 20);
    setStrikeB->setFixedSize(20, 20);
    setTaskB->setFixedSize(20, 20);
    setNumListB->setFixedSize(20, 20);
    setTableB->setFixedSize(20, 20);
    setQuoteB->setFixedSize(20, 20);

    menuLayout->addWidget(menuButton);
    menuLayout->addWidget(setH1B);
    menuLayout->addWidget(setH2B);
    menuLayout->addWidget(setH3B);

    menuLayout->addWidget(setBoldB);
    menuLayout->addWidget(setItalicB);
    menuLayout->addWidget(setStrikeB);
    menuLayout->addWidget(setQuoteB);

    menuLayout->addWidget(setListB);
    menuLayout->addWidget(setNumListB);
    menuLayout->addWidget(setLinkB);
    menuLayout->addWidget(setTaskB);
    menuLayout->addWidget(setTableB);

    notesCLayout->addLayout(menuLayout);
    notesCLayout->addWidget(noteSplitter);

    notesList->setVisible(isVisibleNotesList);
    mdPreview->setVisible(isVisiblePreview);

    // ========================================================
    QGridLayout *tasksGLayout = new QGridLayout;
    tasksGLayout->setSpacing(0);

    QHBoxLayout *tasksStatsL = new QHBoxLayout;
    tasksStatsL->setSpacing(10);

    QSpacerItem *spacer1 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacer2 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    tasksMenuBtn = new QToolButton;
    tasksMenuBtn->setIcon(
        QPixmap(":/main.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    tasksMenuBtn->setIconSize(QSize(50, 50));
    tasksMenuBtn->setFixedSize(30, 30);
    tasksMenuBtn->setPopupMode(QToolButton::InstantPopup);

    tasksMenu = new QMenu(tasksMenuBtn);

    createTaskMenu(tasksMenu, font_size);

    tasksMenuBtn->setMenu(tasksMenu);

    tasksProgress = new QProgressBar();
    tasksProgress->setMaximum(100);
    tasksProgress->setMaximumWidth(300);
    tasksProgress->setFixedHeight(20);
    tasksProgress->setAlignment(Qt::AlignCenter);

    tasksStatsL->addItem(spacer1);
    tasksStatsL->addWidget(tasksMenuBtn);
    tasksStatsL->addWidget(tasksProgress);
    tasksStatsL->addItem(spacer2);

    label_1 = new QLabel(tr("Incomplete"));
    label_1->setFixedHeight(30);
    label_1->setAlignment(Qt::AlignCenter);

    incompleteTasks = new QListWidget();
    incompleteTasks->setDragDropMode(QListWidget::DragDrop);
    incompleteTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    incompleteTasks->setWordWrap(true);
    incompleteTasks->setSpacing(5);
    incompleteTasks->setObjectName("IncompleteTasks");

    label_2 = new QLabel(tr("Inprocess"));
    label_2->setFixedHeight(30);
    label_2->setAlignment(Qt::AlignCenter);

    inprocessTasks = new QListWidget();
    inprocessTasks->setDragDropMode(QListWidget::DragDrop);
    inprocessTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    inprocessTasks->setWordWrap(true);
    inprocessTasks->setSpacing(5);
    inprocessTasks->setObjectName("InprocessTasks");

    label_3 = new QLabel(tr("Complete"));
    label_3->setFixedHeight(30);
    label_3->setAlignment(Qt::AlignCenter);

    completeTasks = new QListWidget();
    completeTasks->setDragDropMode(QListWidget::DragDrop);
    completeTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    completeTasks->setWordWrap(true);
    completeTasks->setSpacing(5);
    completeTasks->setObjectName("CompleteTasks");

    taskText = new QLineEdit();
    taskText->setPlaceholderText(tr(" Task..."));
    taskText->setFixedHeight(25);

    tasksGLayout->addLayout(tasksStatsL, 0, 0, 1, 3);

    tasksGLayout->addWidget(label_1, 1, 0);
    tasksGLayout->addWidget(label_2, 1, 1);
    tasksGLayout->addWidget(label_3, 1, 2);

    tasksGLayout->addWidget(incompleteTasks, 2, 0);
    tasksGLayout->addWidget(inprocessTasks, 2, 1);
    tasksGLayout->addWidget(completeTasks, 2, 2);

    tasksGLayout->addWidget(taskText, 3, 1);

    // ========================================================

    // projects tab
    QGridLayout *projectsGLayout = new QGridLayout;
    projectsGLayout->setSpacing(0);

    QHBoxLayout *projectsStatsL = new QHBoxLayout();
    projectsStatsL->setSpacing(0);

    QSpacerItem *spacer3 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacer4 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    // menu
    projectsMenuButton = new QToolButton();
    projectsMenuButton->setIcon(
        QPixmap(":/main.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    projectsMenuButton->setPopupMode(QToolButton::InstantPopup);
    projectsMenuButton->setFixedSize(30, 25);
    projectsMenuButton->setIconSize(QSize(40, 40));

    projectsMenu = new QMenu(projectsMenuButton);

    createProjectMenu(projectsMenu, font_size);

    projectsMenuButton->setMenu(projectsMenu);

    projectsMainLabel = new QLabel(tr("Projects"));
    projectsMainLabel->setAlignment(Qt::AlignCenter);

    totalProjectsL = new QLabel();
    totalProjectsL->setFixedHeight(30);
    totalProjectsL->setAlignment(Qt::AlignCenter);

    nsProjects = new QLabel(tr("Not started"));
    nsProjects->setAlignment(Qt::AlignHCenter);
    notStartedProjects = new QListWidget();
    notStartedProjects->setDragEnabled(true);
    notStartedProjects->setDragDropMode(QListWidget::DragDrop);
    notStartedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    notStartedProjects->setWordWrap(true);
    notStartedProjects->setSpacing(5);
    notStartedProjects->setObjectName("NotStartedProjects");
    notStartedProjects->setContextMenuPolicy(Qt::CustomContextMenu);

    sProjects = new QLabel(tr("Started"));
    sProjects->setAlignment(Qt::AlignHCenter);
    startedProjects = new QListWidget();
    startedProjects->setDragEnabled(true);
    startedProjects->setDragDropMode(QListWidget::DragDrop);
    startedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    startedProjects->setWordWrap(true);
    startedProjects->setSpacing(5);
    startedProjects->setObjectName("StartedProjects");
    startedProjects->setContextMenuPolicy(Qt::CustomContextMenu);

    flProjects = new QLabel(tr("For review"));
    flProjects->setAlignment(Qt::AlignHCenter);
    finishlineProjects = new QListWidget();
    finishlineProjects->setDragEnabled(true);
    finishlineProjects->setDragDropMode(QListWidget::DragDrop);
    finishlineProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    finishlineProjects->setWordWrap(true);
    finishlineProjects->setSpacing(5);
    finishlineProjects->setObjectName("FinishlineProjects");
    finishlineProjects->setContextMenuPolicy(Qt::CustomContextMenu);

    fProjects = new QLabel(tr("Finished"));
    fProjects->setAlignment(Qt::AlignHCenter);
    finishedProjects = new QListWidget();
    finishedProjects->setDragEnabled(true);
    finishedProjects->setDragDropMode(QListWidget::DragDrop);
    finishedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    finishedProjects->setWordWrap(true);
    finishedProjects->setSpacing(5);
    finishedProjects->setObjectName("FinishedProjects");
    finishedProjects->setContextMenuPolicy(Qt::CustomContextMenu);

    projectsStatsL->addItem(spacer3);
    projectsStatsL->addWidget(projectsMenuButton);
    projectsStatsL->addWidget(totalProjectsL);
    projectsStatsL->addItem(spacer4);

    projectsGLayout->addLayout(projectsStatsL, 0, 0, 1, 2);
    projectsGLayout->addWidget(nsProjects, 1, 0);
    projectsGLayout->addWidget(notStartedProjects, 2, 0);
    projectsGLayout->addWidget(sProjects, 1, 1);
    projectsGLayout->addWidget(startedProjects, 2, 1);
    projectsGLayout->addWidget(flProjects, 3, 0);
    projectsGLayout->addWidget(finishlineProjects, 4, 0);
    projectsGLayout->addWidget(fProjects, 3, 1);
    projectsGLayout->addWidget(finishedProjects, 4, 1);

    // ========================================================
    // tabs

    tabs = new QTabWidget();
    tabs->setMovable(true);
    tabs->setTabPosition(QTabWidget::South);

    // main tab
    QWidget *mainTab = new QWidget();
    QGridLayout *firstLayout = new QGridLayout(mainTab);

    firstLayout->addWidget(timeLabel, 0, 1, 2, 2, Qt::AlignBottom);
    firstLayout->addWidget(dateLabel, 2, 1, 1, 2, Qt::AlignTop);
    firstLayout->addWidget(helloLabel, 3, 0, 3, 6, Qt::AlignCenter);

    tabs->addTab(mainTab, tr("Homepage"));

    // notes tab
    QWidget *notesTab = new QWidget();
    QVBoxLayout *notesLayout = new QVBoxLayout(notesTab);

    notesLayout->addLayout(notesCLayout);

    tabs->addTab(notesTab, tr("Doc"));

    // tasks tab
    QWidget *tasksTab = new QWidget();
    QVBoxLayout *tasksLayout = new QVBoxLayout(tasksTab);

    tasksLayout->addLayout(tasksGLayout);

    tabs->addTab(tasksTab, tr("Tasks"));

    // projects tab
    QWidget *projectsTab = new QWidget();
    QVBoxLayout *projectsLayout = new QVBoxLayout(projectsTab);

    projectsLayout->addLayout(projectsGLayout);

    tabs->addTab(projectsTab, tr("Projects"));

    QPixmap mainIco(":/main.png");
    QPixmap projectsIco(":/project.png");
    QPixmap noteIco(":/document.png");
    QPixmap tasksIco(":/task.png");

    tabs->setTabIcon(tabs->indexOf(mainTab), mainIco);
    tabs->setTabIcon(tabs->indexOf(notesTab), noteIco);
    tabs->setTabIcon(tabs->indexOf(tasksTab), tasksIco);
    tabs->setTabIcon(tabs->indexOf(projectsTab), projectsIco);

    tabs->setIconSize(QSize(font_size.toInt(), font_size.toInt()));
    tabs->setTabBarAutoHide(true);
    tabs->setTabVisible(0, false);
    tabs->setTabVisible(1, false);
    tabs->setTabVisible(2, false);
    tabs->setTabVisible(3, false);

    if (isCustomTitlebar)
    {
        mainLayout->addLayout(winControlL, 0, 0, 1, 2);

        QTimer *connectionTimer = new QTimer(this);
        connect(connectionTimer, &QTimer::timeout, this, &MainWindow::setConnectionStatus);
        connectionTimer->start(1000); // 1000ms = 1s
    }
    else
    {
        sizeGrip2->hide();
    }

    isConnected = new QPushButton("");
    isConnected->setFixedSize(15, 15);

    isAutoSync = new QPushButton("");
    isAutoSync->setFixedSize(15, 15);

    QSpacerItem *headerSp = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *headerSp3 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *headerSp4 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    winControlL->addWidget(windowTitle);

    winControlL->addItem(headerSp);

    winControlL->addWidget(isConnected);
    winControlL->addWidget(isAutoSync);
    winControlL->addWidget(sizeGrip2);

    QVBoxLayout *tabButtons = new QVBoxLayout();

    mainTabButton = new QPushButton(
        QPixmap(":/main.png")
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    mainTabButton->setFixedSize(50, 50);
    mainTabButton->setFlat(true);

    tasksTabButton = new QPushButton(
        QPixmap(":/task.png")
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    tasksTabButton->setFixedSize(50, 50);
    tasksTabButton->setFlat(true);

    notesTabButton = new QPushButton(
        QPixmap(":/document.png")
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    notesTabButton->setFixedSize(50, 50);
    notesTabButton->setFlat(true);

    projectsTabButton = new QPushButton(
        QPixmap(":/project.png")
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    projectsTabButton->setFixedSize(50, 50);
    projectsTabButton->setFlat(true);

    QSpacerItem *headerSp5 = new QSpacerItem(30, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *headerSp6 = new QSpacerItem(30, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    tabButtons->addItem(headerSp5);
    tabButtons->addWidget(mainTabButton);
    tabButtons->addWidget(tasksTabButton);
    tabButtons->addWidget(notesTabButton);
    tabButtons->addWidget(projectsTabButton);
    tabButtons->addItem(headerSp6);
    tabButtons->addWidget(openAccountWindow);
    tabButtons->addWidget(syncDataBtn);
    tabButtons->addWidget(openSettingsBtn);

    // open homepage
    tabs->setCurrentIndex(0);

    mainLayout->addLayout(tabButtons, 1, 0);
    mainLayout->addWidget(tabs, 1, 1);

    QThread *dbThread = new QThread;
    QObject::connect(dbThread, &QThread::started, this, [this]() {
        createConnection(dir);

        create_tasks_connection();
        create_projects_connection();

        loadNotes();
        loadTasks();
        loadProjects();

        qDebug() << "dbThread started";
    });
    dbThread->start();

    QThread *styleThread = new QThread;
    QObject::connect(styleThread, &QThread::started, this, [this]() {
        int font_size_int = font_size.toInt();
        setStyle(&selectedFont, &font_size_int);

        qDebug() << "styleThread started";
    });
    styleThread->start();

    QThread *connectsThread = new QThread;
    QObject::connect(connectsThread, &QThread::started, this, [this]() {
        createShortcuts();
        createConnects();

        qDebug() << "connectsThread started";
    });
    connectsThread->start();

    QThread *timedateThread = new QThread;
    QObject::connect(timedateThread, &QThread::started, this, [this]() {
        QTimer *dateTimer = new QTimer();
        dateTimer->setInterval(1000);
        QObject::connect(dateTimer, &QTimer::timeout, this, [this]() { emit updateTime(); });
        dateTimer->start();
    });
    timedateThread->start();

    QThread *checkTasks = new QThread;
    QObject::connect(checkTasks, &QThread::started, this, [this]() {
        QTimer *tasksTimer = new QTimer();
        tasksTimer->setInterval(1000);
        QObject::connect(tasksTimer, &QTimer::timeout, this, [this]() {
            int incompleteTasksCount = incompleteTasks->count();

            int totalTasksCount = completeTasks->count() + inprocessTasks->count() + incompleteTasks->count();

            if (incompleteTasksCount >= 1)
            {
                helloLabel->setText(tr("Welcome, ") + git_user + tr("!\n\nYou have ") +
                                    QString::number(incompleteTasksCount) + tr(" uncompleted tasks out of ") +
                                    QString::number(totalTasksCount) + "");
            }
            else
            {
                helloLabel->setText(tr("Welcome, ") + git_user +
                                    tr("!\n\nYou have completed all of your tasks for the day. Good job!"));
            }
        });
        tasksTimer->start();
    });
    checkTasks->start();

    qDebug() << "" << dir;
    qDebug() << "Load time:" << startup.elapsed() << "ms";
}

MainWindow::~MainWindow()
{
    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    globalSettings->setValue("geometry", saveGeometry());
}

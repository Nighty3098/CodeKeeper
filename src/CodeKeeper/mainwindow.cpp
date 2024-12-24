#include "mainwindow.h"

#include <QDragEnterEvent>
#include <QElapsedTimer>
#include <QInputDialog>
#include <QMimeData>
#include <QPropertyAnimation>
#include <QSizeGrip>
#include <QSystemTrayIcon>
#include <QThread>
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
    QElapsedTimer startup;
    startup.start();

    qDebug() << "Starting CodeKeeper";

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");

    getSettingsData();

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icon.png"));
    trayIcon->setVisible(true);
    trayIcon->setToolTip(tr("CodeKeeper"));

    QMenu trayMenu;
    createTrayMenu(&trayMenu, font_size);
    trayIcon->setContextMenu(&trayMenu);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
            SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    trayIcon->showMessage("CodeKeeper", "Welcome back, " + git_user + "!", QSystemTrayIcon::Information, 3000);

    if (firstRun)
    {
        globalSettings->setValue("isCustomTheme", true);
        globalSettings->setValue("isCustomTitlebar", true);
        globalSettings->setValue("theme", 0);
        showWelcomeMessage();
    }

    loadStyleSheetFile();

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

            QStringList currentParts = currentAppVersion.split('.');
            QStringList newParts = newAppVersion.split('.');

            bool isDevVersion = false;

            for (int i = 0; i < qMin(currentParts.size(), newParts.size()); ++i)
            {
                int currentPart = currentParts[i].toInt();
                int newPart = newParts[i].toInt();

                if (currentPart > newPart)
                {
                    isDevVersion = true;
                    break;
                }
                else if (currentPart < newPart)
                {
                    break;
                }
            }

            if (isDevVersion)
            {
                verLabel->setText("You are using the dev version !");
                qDebug() << "You are using the developer version. It's not stable";
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
    closeBtn->setObjectName("closeBtn");
    minimizeBtn = new QPushButton();
    minimizeBtn->setObjectName("minimizeBtn");
    maximizeBtn = new QPushButton();
    maximizeBtn->setObjectName("maximizeBtn");

    winControlL = new QHBoxLayout;
    winControlL->setSpacing(10);

    isFullScreen = false;

    sizeGrip = new QSizeGrip(this);
    sizeGrip->setFixedSize(13, 13);
    sizeGrip->setVisible(true);
    sizeGrip->setObjectName("indicator");

    windowTitle = new QLabel(tr(" ~ CodeKeeper ~ "));

    createCustomTitlebar();

    this->setMouseTracking(true);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowIcon(QPixmap(":/icon.png"));

    mainLayout = new QGridLayout(centralWidget);
    mainLayout->setSpacing(0);

    // ========================================================
    timeLabel = new QLabel("");
    timeLabel->setAlignment(Qt::AlignBottom);
    timeLabel->setObjectName("timeLabel");

    dateLabel = new QLabel("");
    dateLabel->setAlignment(Qt::AlignTop);
    dateLabel->setObjectName("dateLabel");

    helloLabel = new QLabel();
    helloLabel->setAlignment(Qt::AlignLeft);
    helloLabel->setObjectName("helloLabel");

    verLabel = new QLabel();
    verLabel->setAlignment(Qt::AlignBottom);
    verLabel->setObjectName("helloLabel");

    decorationLabel = new QLabel();
    decorationLabel->setAlignment(Qt::AlignHCenter);
    decorationLabel->setPixmap(QPixmap(":/tea.svg").scaled(260, 260, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    openSettingsBtn = new QPushButton(
        changeIconColor(QPixmap(":/settings.png"))
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    openSettingsBtn->setToolTip(tr("Settings"));
    openSettingsBtn->setFixedSize(50, 50);
    openSettingsBtn->setFlat(true);

    syncDataBtn = new QPushButton(
        changeIconColor(QPixmap(":/sync.png"))
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    syncDataBtn->setToolTip(tr("Sync"));
    syncDataBtn->setFixedSize(50, 50);
    syncDataBtn->setFlat(true);

    openAccountWindow = new QPushButton(
        changeIconColor(QPixmap(":/user.png"))
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    openAccountWindow->setToolTip(tr("Account"));
    openAccountWindow->setFixedSize(50, 50);
    openAccountWindow->setFlat(true);

    // ========================================================
    QHBoxLayout *menuLayout = new QHBoxLayout;
    QHBoxLayout *contentLayout = new QHBoxLayout;
    QVBoxLayout *notesCLayout = new QVBoxLayout;

    QSplitter *noteSplitter = new QSplitter(Qt::Horizontal);

    contentLayout->setSpacing(5);
    notesCLayout->setSpacing(5);

    menuLayout->setSpacing(10);
    menuLayout->setSizeConstraint(QLayout::SetFixedSize);
    menuLayout->setAlignment(Qt::AlignHCenter);

    QStringList filters;
    filters << ""
            << "*.md";

    notesDirModel = new QFileSystemModel();
    notesDirModel->setNameFilters(filters);
    notesDirModel->setNameFilterDisables(false);

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
    notesList->setContextMenuPolicy(Qt::CustomContextMenu);

    noteEdit = new NoteEditor();
    noteEdit->setPlaceholderText(tr(" Just start typing"));
    noteEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    noteEdit->setLineNumberEnabled(true);
    noteEdit->setLineNumbersCurrentLineColor("#51afef");
    noteEdit->setLineWidth(font_size.toInt());
    noteEdit->setHighlightingEnabled(true);

    noteSplitter->addWidget(notesList);
    noteSplitter->addWidget(noteEdit);

    noteSplitter->setStretchFactor(0, 1);
    noteSplitter->setStretchFactor(1, 1);
    noteSplitter->setStretchFactor(2, 1);

    // title
    noteNameLabel = new QLabel(tr("Note"));
    noteNameLabel->setAlignment(Qt::AlignCenter);
    connect(noteEdit, &QMarkdownTextEdit::textChanged, this, &MainWindow::setHeader);

    menuButton = new QToolButton;
    menuButton->setIcon(
        changeIconColor(QPixmap(":/main.png"))
            .scaled(font_size.toInt() + 3, font_size.toInt() + 3, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    menuButton->setIconSize(QSize(50, 50));
    menuButton->setFixedSize(30, 30);
    menuButton->setPopupMode(QToolButton::InstantPopup);

    menu = new QMenu(menuButton);

    createNotesMenu(menu, font_size);

    menuButton->setMenu(menu);

    setH1B = new QPushButton(
        changeIconColor(QPixmap(":/h1.png"))
            .scaled(font_size.toInt() + 4, font_size.toInt() + 4, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setH2B = new QPushButton(
        changeIconColor(QPixmap(":/h2.png"))
            .scaled(font_size.toInt() + 4, font_size.toInt() + 4, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setH3B = new QPushButton(
        changeIconColor(QPixmap(":/h3.png"))
            .scaled(font_size.toInt() + 4, font_size.toInt() + 4, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setListB = new QPushButton(
        changeIconColor(QPixmap(":/list.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setLinkB = new QPushButton(
        changeIconColor(QPixmap(":/link.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setBoldB = new QPushButton(
        changeIconColor(QPixmap(":/bold.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setItalicB = new QPushButton(
        changeIconColor(QPixmap(":/italic.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setStrikeB = new QPushButton(
        changeIconColor(QPixmap(":/strikethrough.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setTaskB = new QPushButton(
        changeIconColor(QPixmap(":/checkbox.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setNumListB = new QPushButton(
        changeIconColor(QPixmap(":/numList.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setTableB = new QPushButton(
        changeIconColor(QPixmap(":/table.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    setQuoteB = new QPushButton(
        changeIconColor(QPixmap(":/quote.png"))
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

    // ========================================================
    QGridLayout *tasksGLayout = new QGridLayout;
    tasksGLayout->setSpacing(5);

    QHBoxLayout *tasksStatsL = new QHBoxLayout;
    tasksStatsL->setSpacing(20);

    QSpacerItem *spacer1 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacer2 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    tasksMenuBtn = new QToolButton;
    tasksMenuBtn->setIcon(
        changeIconColor(QPixmap(":/main.png"))
            .scaled(font_size.toInt() + 3, font_size.toInt() + 3, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    tasksMenuBtn->setIconSize(QSize(50, 50));
    tasksMenuBtn->setFixedSize(30, 30);
    tasksMenuBtn->setPopupMode(QToolButton::InstantPopup);

    tasksMenu = new QMenu(tasksMenuBtn);

    createTaskMenu(tasksMenu, font_size);

    tasksMenuBtn->setMenu(tasksMenu);

    projectsList = new QComboBox();
    projectsList->setFixedSize(450, 25);
    projectsList->setPlaceholderText(tr("Select your project ... "));

    tasksProgress = new QProgressBar();
    tasksProgress->setMaximum(100);
    tasksProgress->setFixedWidth(500);
    tasksProgress->setFixedHeight(25);
    tasksProgress->setAlignment(Qt::AlignCenter);
    tasksProgress->setObjectName("tasksProgress");

    tasksStatsL->addItem(spacer1);
    tasksStatsL->addWidget(tasksMenuBtn);
    tasksStatsL->addWidget(projectsList);
    tasksStatsL->addItem(spacer2);

    inprocessWidget = new QWidget();
    inprocessWidget->setStyleSheet("padding: 0px; margin: 0px;");
    incompleteWidget = new QWidget();
    incompleteWidget->setStyleSheet("padding: 0px; margin: 0px;");
    completeWidget = new QWidget();
    completeWidget->setStyleSheet("padding: 0px; margin: 0px;");

    QVBoxLayout *incompleteLayout = new QVBoxLayout(incompleteWidget);
    QVBoxLayout *inprocessLayout = new QVBoxLayout(inprocessWidget);
    QVBoxLayout *completeLayout = new QVBoxLayout(completeWidget);

    label_1 = new ClickableLabel(tr("Incomplete"));
    label_1->setFixedHeight(13);
    label_1->setAlignment(Qt::AlignCenter);

    incompleteTasks = new QListWidget();
    incompleteTasks->setDragDropMode(QListWidget::DragDrop);
    incompleteTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    incompleteTasks->setWordWrap(true);
    incompleteTasks->setSpacing(5);
    incompleteTasks->setObjectName("IncompleteTasks");
    incompleteTasks->setContextMenuPolicy(Qt::CustomContextMenu);
    incompleteTasks->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    incompleteLayout->addWidget(label_1);
    incompleteLayout->addWidget(incompleteTasks);

    label_2 = new ClickableLabel(tr("Inprocess"));
    label_2->setFixedHeight(13);
    label_2->setAlignment(Qt::AlignCenter);

    inprocessTasks = new QListWidget();
    inprocessTasks->setDragDropMode(QListWidget::DragDrop);
    inprocessTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    inprocessTasks->setWordWrap(true);
    inprocessTasks->setSpacing(5);
    inprocessTasks->setObjectName("InprocessTasks");
    inprocessTasks->setContextMenuPolicy(Qt::CustomContextMenu);
    inprocessTasks->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    inprocessLayout->addWidget(label_2);
    inprocessLayout->addWidget(inprocessTasks);

    label_3 = new ClickableLabel(tr("Complete"));
    label_3->setFixedHeight(13);
    label_3->setAlignment(Qt::AlignCenter);

    completeTasks = new QListWidget();
    completeTasks->setDragDropMode(QListWidget::DragDrop);
    completeTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    completeTasks->setWordWrap(true);
    completeTasks->setSpacing(5);
    completeTasks->setObjectName("CompleteTasks");
    completeTasks->setContextMenuPolicy(Qt::CustomContextMenu);
    completeTasks->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    completeLayout->addWidget(label_3);
    completeLayout->addWidget(completeTasks);

    taskText = new QLineEdit();
    taskText->setPlaceholderText(tr(" Task..."));
    taskText->setFixedHeight(25);
    taskText->setMaximumWidth(400);

    tasksGLayout->addLayout(tasksStatsL, 0, 0, 1, 3);

    tasksSplitter = new QSplitter();
    tasksSplitter->setOrientation(Qt::Horizontal);
    tasksSplitter->setStyleSheet("QSplitter::handle:horizontal {background-color: transparent; color: transparent;} "
                                 "QSplitter::handle:vertical {background-color: transparent; color: transparent;}");

    tasksSplitter->addWidget(incompleteWidget);
    tasksSplitter->addWidget(inprocessWidget);
    tasksSplitter->addWidget(completeWidget);

    tasksSplitter->setStretchFactor(0, 1);
    tasksSplitter->setStretchFactor(1, 1);
    tasksSplitter->setStretchFactor(2, 1);

    tasksGLayout->addWidget(tasksProgress, 1, 1);
    tasksGLayout->addWidget(tasksSplitter, 2, 0, 1, 3);
    tasksGLayout->addWidget(taskText, 4, 1);

    // ========================================================

    // projects tab
    QGridLayout *projectsGLayout = new QGridLayout;
    projectsGLayout->setSpacing(0);

    QHBoxLayout *projectsStatsL = new QHBoxLayout();
    projectsStatsL->setSpacing(20);

    QSpacerItem *spacer3 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacer4 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    // menu
    projectsMenuButton = new QToolButton();
    projectsMenuButton->setIcon(
        changeIconColor(QPixmap(":/main.png"))
            .scaled(font_size.toInt() + 3, font_size.toInt() + 3, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    projectsMenuButton->setPopupMode(QToolButton::InstantPopup);
    projectsMenuButton->setFixedSize(30, 25);
    projectsMenuButton->setIconSize(QSize(40, 40));

    projectsMenu = new QMenu(projectsMenuButton);

    createProjectMenu(projectsMenu, font_size);

    projectsMenuButton->setMenu(projectsMenu);

    projectsMainLabel = new QLabel(tr("Projects"));
    projectsMainLabel->setAlignment(Qt::AlignCenter);

    totalProjectsL = new QLabel();
    totalProjectsL->setFixedHeight(25);
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
    notStartedProjects->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

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
    startedProjects->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

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
    finishlineProjects->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

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
    finishedProjects->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

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

    firstLayout->addWidget(decorationLabel, 6, 0, 3, 8, Qt::AlignBottom | Qt::AlignRight);
    firstLayout->addWidget(timeLabel, 0, 1, 2, 4, Qt::AlignBottom);
    firstLayout->addWidget(dateLabel, 2, 1, 1, 4, Qt::AlignTop);
    firstLayout->addWidget(verLabel, 9, 1, 1, 7, Qt::AlignLeft);
    firstLayout->addWidget(helloLabel, 7, 1, 2, 7, Qt::AlignLeft | Qt::AlignHCenter);

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

    isConnected = new QPushButton("");
    isConnected->setFixedSize(14, 14);

    isAutoSync = new QPushButton("");
    isAutoSync->setFixedSize(14, 14);

    QSpacerItem *headerSp = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *headerSp3 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *headerSp4 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    winControlL->addWidget(windowTitle);
    winControlL->addItem(headerSp);
    winControlL->addWidget(isConnected);
    winControlL->addWidget(isAutoSync);
    winControlL->addWidget(sizeGrip);

    winControlL->setAlignment(Qt::AlignVCenter);

    winControlW = new QWidget();
    winControlW->setFixedHeight(30);
    winControlW->setLayout(winControlL);

    if (isCustomTitlebar)
    {
        mainLayout->addWidget(winControlW, 0, 0, 1, 2);

        QTimer *connectionTimer = new QTimer(this);
        connect(connectionTimer, &QTimer::timeout, this, &MainWindow::setConnectionStatus);
        connectionTimer->start(1000);
    }
    else
    {
        sizeGrip->hide();
    }

    tabButtonsWidget = new QWidget();
    tabButtons = new QVBoxLayout();

    tabButtonsWidget->setStyleSheet("margin: 0px; padding: 0px;");
    tabButtonsWidget->setMaximumWidth(55);

    tabButtonsWidget->setLayout(tabButtons);

    mainTabButton = new QPushButton(
        changeIconColor(QPixmap(":/main.png"))
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    mainTabButton->setFixedSize(50, 50);
    mainTabButton->setFlat(true);
    mainTabButton->setToolTip(tr("Home"));

    tasksTabButton = new QPushButton(
        changeIconColor(QPixmap(":/task.png"))
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    tasksTabButton->setFixedSize(50, 50);
    tasksTabButton->setFlat(true);
    tasksTabButton->setToolTip(tr("Tasks"));

    notesTabButton = new QPushButton(
        changeIconColor(QPixmap(":/document.png"))
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    notesTabButton->setFixedSize(50, 50);
    notesTabButton->setFlat(true);
    notesTabButton->setToolTip(tr("Notes"));

    projectsTabButton = new QPushButton(
        changeIconColor(QPixmap(":/project.png"))
            .scaled(font_size.toInt() + 10, font_size.toInt() + 10, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        "");
    projectsTabButton->setFixedSize(50, 50);
    projectsTabButton->setFlat(true);
    projectsTabButton->setToolTip(tr("Projects"));

    QSpacerItem *headerSp5 = new QSpacerItem(30, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *headerSp6 = new QSpacerItem(30, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    tabButtons->addItem(headerSp5);
    tabButtons->addWidget(mainTabButton);
    tabButtons->addWidget(projectsTabButton);
    tabButtons->addWidget(tasksTabButton);
    tabButtons->addWidget(notesTabButton);
    tabButtons->addItem(headerSp6);
    tabButtons->addWidget(openAccountWindow);
    tabButtons->addWidget(syncDataBtn);
    tabButtons->addWidget(openSettingsBtn);

    isHideMenu = false;

    // open homepage
    tabs->setCurrentIndex(0);

    mainLayout->addWidget(tabButtonsWidget, 1, 0);
    mainLayout->addWidget(tabs, 1, 1);

    QThread *dbThread = new QThread;
    QObject::connect(dbThread, &QThread::started, this, [this]() {
        createConnection(dir);

        create_tasks_connection();
        create_projects_connection();

        loadNotes();
        loadTasks();
        loadProjects();
        loadProjectsList(projectsList);

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
            int startedProjectsCount = startedProjects->count() + finishlineProjects->count();
            int notstartedProjectsCount = notStartedProjects->count();

            if (incompleteTasksCount >= 1)
            {
                helloLabel->setText(tr("Welcome, ") + git_user + tr("!\n\nYou have ") +
                                    QString::number(incompleteTasksCount) + tr(" uncompleted tasks out of ") +
                                    QString::number(totalTasksCount) + tr("\nAnd ") +
                                    QString::number(startedProjectsCount) + tr(" started projects"));
            }
            else
            {
                helloLabel->setText(tr("Welcome, ") + git_user +
                                    tr("!\n\nYou have completed all of your tasks for the day.\n\nGood job!"));
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

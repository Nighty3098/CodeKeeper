#include "mainwindow.h"

#include <QPropertyAnimation>

#include "keeperFunc/functional.cpp"
#include "qmarkdowntextedit/markdownhighlighter.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    setMinimumSize(560, 400);
    setAttribute(Qt::WA_TranslucentBackground);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    restoreGeometry(globalSettings->value("geometry").toByteArray());

    selectedFont = globalSettings->value("font").value<QFont>();
    font_size = globalSettings->value("fontSize").value<QString>();
    theme = globalSettings->value("theme").value<QString>();

    path = globalSettings->value("path").value<QString>();

    qDebug() << path;

    bool isVisibleNotesList =
        globalSettings->value("isVisibleNotesList", true).toBool();
    bool isVisiblePreview =
        globalSettings->value("isVisiblePreview", false).toBool();
    bool isVisibleFolders =
        globalSettings->value("isVisibleFolders", true).toBool();

    // ========================================================

    // title
    mainTitle = new QLabel("CodeKeeper");
    mainTitle->setAlignment(Qt::AlignCenter);
    mainTitle->setStyleSheet("font-size: 42px;");

    // settings btn
    QHBoxLayout *settingsBtnLayout = new QHBoxLayout;
    openSettingsBtn = new QPushButton(QPixmap(":/settings.png"), " Settings");
    openSettingsBtn->setFixedSize(200, 30);
    settingsBtnLayout->addWidget(openSettingsBtn);

    // sync btn
    QHBoxLayout *syncDataLayout = new QHBoxLayout;
    syncDataBtn = new QPushButton(QPixmap(":/retry.png"), " Sync data");
    syncDataBtn->setFixedSize(200, 30);
    syncDataLayout->addWidget(syncDataBtn);

    // folder btn
    QHBoxLayout *openFolderlayout = new QHBoxLayout;
    openFolderBtn = new QPushButton(QPixmap(":/open.png"), " Open folder");
    openFolderBtn->setFixedSize(200, 30);
    openFolderlayout->addWidget(openFolderBtn);

    // ========================================================

    QVBoxLayout *notesL0 = new QVBoxLayout;
    QHBoxLayout *notesL1 = new QHBoxLayout;
    QVBoxLayout *notesL2 = new QVBoxLayout;
    QHBoxLayout *notesL3 = new QHBoxLayout;
    QHBoxLayout *notesL4 = new QHBoxLayout;

    notesList = new QListWidget();
    notesList->setWordWrap(true);
    notesList->setDragDropMode(QAbstractItemView::DragDrop);
    notesList->setDefaultDropAction(Qt::MoveAction);
    notesList->setDragEnabled(true);
    notesList->setMaximumWidth(200);

    foldersList = new QListWidget();
    foldersList->setWordWrap(true);
    foldersList->setDragDropMode(QAbstractItemView::DragDrop);
    foldersList->setDefaultDropAction(Qt::MoveAction);
    foldersList->setDragEnabled(true);
    foldersList->setMaximumWidth(200);

    // other
    noteName = new QLineEdit();
    noteName->setFixedHeight(30);
    noteName->setPlaceholderText(" Name ...");

    mdPreview = new QTextBrowser();
    mdPreview->setOpenLinks(true);
    mdPreview->setOpenExternalLinks(true);

    noteEdit = new QMarkdownTextEdit();
    noteEdit->setPlaceholderText(" Just start typing");

    MarkdownHighlighter *highlighter =
        new MarkdownHighlighter(mdPreview->document());

    noteEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    // noteEdit->setLineNumberEnabled(true);
    // noteEdit->setLineNumbersCurrentLineColor("#fbcd76");
    noteEdit->setLineWidth(font_size.toInt());
    noteEdit->setHighlightingEnabled(true);

    timeLabel = new QLabel(getCurrentDateTimeString());
    timeLabel->setAlignment(Qt::AlignCenter);

    noteNameLabel = new QLabel("Note");
    noteNameLabel->setAlignment(Qt::AlignCenter);

    // update title
    connect(noteEdit, &QMarkdownTextEdit::textChanged, this,
            &MainWindow::setHeader);

    notesList->setVisible(isVisibleNotesList);
    foldersList->setVisible(isVisibleFolders);
    mdPreview->setVisible(isVisiblePreview);

    // menu
    menuButton = new QToolButton;
    menuButton->setText("...");
    menuButton->setPopupMode(QToolButton::InstantPopup);

    QMenu *menu = new QMenu(menuButton);
    menu->setFont(selectedFont);

    // actions for menu

    QAction *newNote = menu->addAction(QPixmap(":/new.png"), "New Note", this,
                                       SLOT(createNote()));
    QAction *rmNote = menu->addAction(QPixmap(":/delete.png"), "RM note", this,
                                      SLOT(removeNote()));
    QAction *newFolder = menu->addAction(
        QPixmap(":/new_folder.png"), "New folder", this, SLOT(createFolder()));
    QAction *rmFolder = menu->addAction(QPixmap(":/delete.png"), "RM folder",
                                        this, SLOT(removeFolder()));

    menu->addSeparator();

    QAction *showFolders =
        menu->addAction("Show folders list", this, SLOT(showFolders()));
    showFolders->setCheckable(true);
    showFolders->setChecked(isVisibleFolders);

    QAction *showList =
        menu->addAction("Show notes list", this, SLOT(hideNotesList()));
    showList->setCheckable(true);
    showList->setChecked(isVisibleNotesList);

    QAction *showPreview =
        menu->addAction("Show md preview", this, SLOT(showPreview()));
    showPreview->setCheckable(true);
    showPreview->setChecked(isVisiblePreview);

    menuButton->setMenu(menu);

    notesL4->addWidget(menuButton);
    notesL4->addWidget(noteNameLabel);
    // notesL4->addWidget(timeLabel);

    notesL2->addWidget(noteEdit);

    notesL1->addWidget(foldersList);
    notesL1->addWidget(notesList);
    notesL1->addLayout(notesL2);
    notesL1->addWidget(mdPreview);

    notesL0->addLayout(notesL4);
    notesL0->addLayout(notesL1);

    // ========================================================

    QVBoxLayout *tasksL1 = new QVBoxLayout;
    QHBoxLayout *tasksL2 = new QHBoxLayout;
    QHBoxLayout *tasksL3 = new QHBoxLayout;

    QVBoxLayout *incompleteLayout = new QVBoxLayout;
    label_1 = new QLabel("Incomplete");
    label_1->setFixedHeight(20);
    // label_1->setStyleSheet("color: #b9676b;");
    label_1->setAlignment(Qt::AlignHCenter);

    incompleteTasks = new QListWidget();
    incompleteTasks->setDragEnabled(true);
    incompleteTasks->setDragDropMode(QListWidget::DragDrop);
    incompleteTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    incompleteTasks->setWordWrap(true);
    incompleteTasks->setSpacing(5);

    QVBoxLayout *inprocessLayout = new QVBoxLayout;
    label_2 = new QLabel("Inprocess");
    // label_2->setStyleSheet("color: #e8cc91;");
    label_2->setFixedHeight(20);
    label_2->setAlignment(Qt::AlignHCenter);

    inprocessTasks = new QListWidget();
    inprocessTasks->setDragEnabled(true);
    inprocessTasks->setDragDropMode(QListWidget::DragDrop);
    inprocessTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    inprocessTasks->setWordWrap(true);
    inprocessTasks->setSpacing(5);

    QVBoxLayout *completeLayout = new QVBoxLayout;
    label_3 = new QLabel("Complete");
    label_3->setFixedHeight(20);
    // label_3->setStyleSheet("color: #9dda67;");
    label_3->setAlignment(Qt::AlignHCenter);

    completeTasks = new QListWidget();
    completeTasks->setDragEnabled(true);
    completeTasks->setDragDropMode(QListWidget::DragDrop);
    completeTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    completeTasks->setWordWrap(true);
    completeTasks->setSpacing(5);

    taskText = new QLineEdit();
    taskText->setPlaceholderText("Task...");
    taskText->setMaximumHeight(30);

    addTask = new QPushButton(" + ");
    addTask->setFixedSize(40, 30);

    rmTask = new QPushButton(" - ");
    rmTask->setFixedSize(40, 30);

    incompleteLayout->addWidget(label_1);
    incompleteLayout->addWidget(incompleteTasks);

    inprocessLayout->addWidget(label_2);
    inprocessLayout->addWidget(inprocessTasks);

    completeLayout->addWidget(label_3);
    completeLayout->addWidget(completeTasks);

    tasksL3->addLayout(incompleteLayout);
    tasksL3->addLayout(inprocessLayout);
    tasksL3->addLayout(completeLayout);

    tasksL2->addWidget(taskText);
    tasksL2->addWidget(addTask);
    tasksL2->addWidget(rmTask);

    tasksL1->addLayout(tasksL3);
    tasksL1->addLayout(tasksL2);

    // ========================================================

    // projects tab
    QVBoxLayout *FinalProjectsL = new QVBoxLayout;

    QVBoxLayout *projectsL1 = new QVBoxLayout;
    QVBoxLayout *projectsL2 = new QVBoxLayout;

    QHBoxLayout *projectsSubL1 = new QHBoxLayout;
    QHBoxLayout *projectsSubL2 = new QHBoxLayout;

    projectsMainLabel = new QLabel("Projects");
    projectsMainLabel->setAlignment(Qt::AlignCenter);

    nsProjects = new QLabel("Not started");
    nsProjects->setAlignment(Qt::AlignHCenter);
    notStartedProjects = new QListWidget();
    notStartedProjects->setDragEnabled(true);
    notStartedProjects->setDragDropMode(QListWidget::DragDrop);
    notStartedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    notStartedProjects->setWordWrap(true);
    notStartedProjects->setSpacing(5);

    sProjects = new QLabel("Started");
    sProjects->setAlignment(Qt::AlignHCenter);
    startedProjects = new QListWidget();
    startedProjects->setDragEnabled(true);
    startedProjects->setDragDropMode(QListWidget::DragDrop);
    startedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    startedProjects->setWordWrap(true);
    startedProjects->setSpacing(5);

    flProjects = new QLabel("Finishline");
    flProjects->setAlignment(Qt::AlignHCenter);
    finishlineProjects = new QListWidget();
    finishlineProjects->setDragEnabled(true);
    finishlineProjects->setDragDropMode(QListWidget::DragDrop);
    finishlineProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    finishlineProjects->setWordWrap(true);
    finishlineProjects->setSpacing(5);

    fProjects = new QLabel("Finished");
    fProjects->setAlignment(Qt::AlignHCenter);
    finishedProjects = new QListWidget();
    finishedProjects->setDragEnabled(true);
    finishedProjects->setDragDropMode(QListWidget::DragDrop);
    finishedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    finishedProjects->setWordWrap(true);
    finishedProjects->setSpacing(5);

    // actions
    // menu
    projectsMenuButton = new QToolButton;
    projectsMenuButton->setText("...");
    projectsMenuButton->setPopupMode(QToolButton::InstantPopup);
    projectsMenuButton->setFixedSize(40, 30);

    projectsMenu = new QMenu(projectsMenuButton);

    // actions for menu
    QAction *newProject = projectsMenu->addAction(
        QPixmap(":/new.png"), "New project", this, SLOT(createProject()));
    QAction *rmProject = projectsMenu->addAction(
        QPixmap(":/delete.png"), "Remove project", this, SLOT(removeProject()));

    projectsMenuButton->setMenu(projectsMenu);

    QHBoxLayout *headerProjectsL = new QHBoxLayout;
    QVBoxLayout *notStartedL = new QVBoxLayout;
    QVBoxLayout *StartedL = new QVBoxLayout;
    QVBoxLayout *finishlineL = new QVBoxLayout;
    QVBoxLayout *finishedL = new QVBoxLayout;

    notStartedL->addWidget(nsProjects);
    notStartedL->addWidget(notStartedProjects);

    StartedL->addWidget(sProjects);
    StartedL->addWidget(startedProjects);

    finishlineL->addWidget(flProjects);
    finishlineL->addWidget(finishlineProjects);

    finishedL->addWidget(fProjects);
    finishedL->addWidget(finishedProjects);

    projectsSubL1->addLayout(notStartedL);
    projectsSubL1->addLayout(StartedL);

    projectsSubL2->addLayout(finishlineL);
    projectsSubL2->addLayout(finishedL);

    headerProjectsL->addWidget(projectsMainLabel);
    headerProjectsL->addWidget(projectsMenuButton);

    FinalProjectsL->addLayout(headerProjectsL);
    FinalProjectsL->addLayout(projectsSubL1);
    FinalProjectsL->addLayout(projectsSubL2);

    // ========================================================
    // tabs

    tabs = new QTabWidget();
    tabs->setMovable(true);
    tabs->setTabPosition(QTabWidget::South);

    // main tab
    QWidget *mainTab = new QWidget();
    QVBoxLayout *firstLayout = new QVBoxLayout(mainTab);

    firstLayout->addWidget(mainTitle);
    firstLayout->addLayout(syncDataLayout);
    firstLayout->addLayout(openFolderlayout);
    firstLayout->addLayout(settingsBtnLayout);

    tabs->addTab(mainTab, "Homepage");

    // notes tab
    QWidget *notesTab = new QWidget();
    QVBoxLayout *notesLayout = new QVBoxLayout(notesTab);

    notesLayout->addLayout(notesL0);

    tabs->addTab(notesTab, "Doc");

    // tasks tab
    QWidget *tasksTab = new QWidget();
    QVBoxLayout *tasksLayout = new QVBoxLayout(tasksTab);

    tasksLayout->addLayout(tasksL1);

    tabs->addTab(tasksTab, "Tasks");

    // projects tab
    QWidget *projectsTab = new QWidget();
    QVBoxLayout *projectsLayout = new QVBoxLayout(projectsTab);

    projectsLayout->addLayout(FinalProjectsL);

    tabs->addTab(projectsTab, "Projects");

    // ========================================================
    // set font and font size

    // tasks
    connect(addTask, SIGNAL(clicked()), this, SLOT(addNewTask()));
    connect(rmTask, SIGNAL(clicked()), this, SLOT(removeTask()));

    // main
    connect(openSettingsBtn, SIGNAL(clicked()), this,
            SLOT(openSettingsWindow()));

    connect(openFolderBtn, SIGNAL(clicked()), this, SLOT(openFolder()));

    connect(notStartedProjects, &QListWidget::itemClicked, this,
            &MainWindow::on_listWidget_itemClicked);
    connect(startedProjects, &QListWidget::itemClicked, this,
            &MainWindow::on_listWidget_itemClicked);
    connect(finishlineProjects, &QListWidget::itemClicked, this,
            &MainWindow::on_listWidget_itemClicked);
    connect(finishedProjects, &QListWidget::itemClicked, this,
            &MainWindow::on_listWidget_itemClicked);

    connect(incompleteTasks, &QListWidget::itemClicked, this,
            &MainWindow::on_listWidget_itemClicked);
    connect(inprocessTasks, &QListWidget::itemClicked, this,
            &MainWindow::on_listWidget_itemClicked);
    connect(completeTasks, &QListWidget::itemClicked, this,
            &MainWindow::on_listWidget_itemClicked);

    // sync scroll
    // connect(noteEdit->verticalScrollBar(), &QAbstractSlider::valueChanged,
    // [=](int value)
    // {mdPreview->verticalScrollBar()->setSliderPosition(value);});
    // connect(mdPreview->verticalScrollBar(), &QAbstractSlider::valueChanged,
    // [=](int value)
    // {noteEdit->verticalScrollBar()->setSliderPosition(value);});

    mainLayout->addWidget(tabs);

    loadNotes(QDir(path));
    loadTasks();
    loadProjects();
    setFontPr1();
}

MainWindow::~MainWindow() {
    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    globalSettings->setValue("geometry", saveGeometry());
}

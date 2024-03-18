#include "mainwindow.h"

#include "keeperFunc/functional.cpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    setMinimumSize(560, 400);

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    restoreGeometry(globalSettings->value("geometry").toByteArray());

    QFont selectedFont = globalSettings->value("font").value<QFont>();
    QString font_size = globalSettings->value("fontSize").value<QString>();
    QString theme = globalSettings->value("theme").value<QString>();

    bool isVisibleNotesList =
        globalSettings->value("isVisibleNotesList", true).toBool();
    bool isVisiblePreview =
        globalSettings->value("isVisiblePreview", false).toBool();

    // ========================================================

    // title
    mainTitle = new QLabel("CodeKeeper");
    mainTitle->setFont(selectedFont);
    mainTitle->setAlignment(Qt::AlignCenter);
    mainTitle->setStyleSheet("font-size: 32px;");

    // settings btn
    QHBoxLayout *settingsBtnLayout = new QHBoxLayout;
    openSettingsBtn = new QPushButton("Settings");
    openSettingsBtn->setFont(selectedFont);
    openSettingsBtn->setStyleSheet("font-size: " + font_size + "pt;");
    openSettingsBtn->setFixedSize(200, 30);
    settingsBtnLayout->addWidget(openSettingsBtn);

    // sync btn
    QHBoxLayout *syncDataLayout = new QHBoxLayout;
    syncDataBtn = new QPushButton("Sync data");
    syncDataBtn->setFont(selectedFont);
    syncDataBtn->setStyleSheet("font-size: " + font_size + "pt;");
    syncDataBtn->setFixedSize(200, 30);
    syncDataLayout->addWidget(syncDataBtn);

    // folder btn
    QHBoxLayout *openFolderlayout = new QHBoxLayout;
    openFolderBtn = new QPushButton("Open folder");
    openFolderBtn->setFont(selectedFont);
    openFolderBtn->setStyleSheet("font-size: " + font_size + "pt;");
    openFolderBtn->setFixedSize(200, 30);
    openFolderlayout->addWidget(openFolderBtn);

    // ========================================================

    QVBoxLayout *notesL0 = new QVBoxLayout;
    QHBoxLayout *notesL1 = new QHBoxLayout;
    QVBoxLayout *notesL2 = new QVBoxLayout;
    QHBoxLayout *notesL3 = new QHBoxLayout;
    QHBoxLayout *notesL4 = new QHBoxLayout;

    notesList = new QTreeWidget();
    notesList->setAnimated(true);
    notesList->setFont(selectedFont);
    notesList->setStyleSheet("font-size: " + font_size + "pt;");
    notesList->setHeaderHidden(true);
    notesList->setWordWrap(true);
    notesList->setDragDropMode(QAbstractItemView::DragDrop);
    notesList->setDefaultDropAction(Qt::MoveAction);
    notesList->setDragEnabled(true);
    notesList->setMaximumWidth(200);

    notesList->setVisible(isVisibleNotesList);

    // menu
    menuButton = new QToolButton;
    // menuButton->setIcon(QIcon(":/menu.png"));
    menuButton->setText("...");
    menuButton->setPopupMode(QToolButton::InstantPopup);
    menuButton->setFixedSize(40, 30);
    menuButton->setFont(selectedFont);
    menuButton->setStyleSheet("font-size: " + font_size + "pt;");

    QMenu *menu = new QMenu(menuButton);
    menu->setFont(selectedFont);

    // actions for menu
    QAction *newNote = menu->addAction(QPixmap(":/new.png"), "New Note");
    QAction *rmNote = menu->addAction(QPixmap(":/delete.png"), "RM note");
    QAction *newFolder =
        menu->addAction(QPixmap(":/new_folder.png"), "New folder");

    menu->addSeparator();

    QAction *showList =
        menu->addAction("Show notes list", this, SLOT(hideNotesList()));
    showList->setCheckable(true);
    showList->setChecked(notesList->isVisible());

    QAction *showPreview =
        menu->addAction("Show md preview", this, SLOT(showPreview()));
    showPreview->setCheckable(true);
    showPreview->setChecked(false);

    menuButton->setMenu(menu);

    // other
    noteName = new QLineEdit();
    noteName->setFixedHeight(30);
    noteName->setPlaceholderText(" Note name ...");
    noteName->setFont(selectedFont);
    noteName->setStyleSheet("font-size: " + font_size + "pt; color: #8ebecf;");

    mdPreview = new QTextBrowser();
    mdPreview->setFont(selectedFont);
    mdPreview->setStyleSheet("font-size: " + font_size + "pt;");
    mdPreview->setVisible(false);

    noteEdit = new QMarkdownTextEdit();
    noteEdit->setFont(selectedFont);
    noteEdit->setStyleSheet("font-size: " + font_size + "pt;");
    noteEdit->setPlaceholderText(" Note ...");
    noteEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);

    timeLabel = new QLabel(getCurrentDateTimeString());
    timeLabel->setFont(selectedFont);
    timeLabel->setStyleSheet("font-size: " + font_size + "pt; color: #8ebecf;");
    timeLabel->setAlignment(Qt::AlignHCenter);

    noteNameLabel = new QLabel("Note");
    noteNameLabel->setFont(selectedFont);
    noteNameLabel->setStyleSheet("font-size: " + font_size + "pt; color: #8ebecf;");
    noteNameLabel->setAlignment(Qt::AlignHCenter);

    // md preview
    // connect(noteEdit, &QMarkdownTextEdit::textChanged, this,
    // &MainWindow::updateMDPreview);

    // update title
    connect(noteEdit, &QMarkdownTextEdit::textChanged, this,
            &MainWindow::setHeader);

    notesL4->addWidget(menuButton);
    notesL4->addWidget(noteNameLabel);
    notesL4->addWidget(timeLabel);

    // notesL3->addWidget(noteName);
    //  notesL3->addWidget(menuButton);

    // notesL2->addLayout(notesL4);
    // notesL2->addLayout(notesL3);
    notesL2->addWidget(noteEdit);

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
    incompleteTasks->setStyleSheet(
        "color: #b9676b; border-width: 3px; border-color: #b9676b; font-size: " + font_size + "pt;");
    incompleteTasks->setDragEnabled(true);
    incompleteTasks->setDragDropMode(QListWidget::DragDrop);
    incompleteTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    incompleteTasks->setWordWrap(true);

    QVBoxLayout *inprocessLayout = new QVBoxLayout;
    label_2 = new QLabel("Inprocess");
    // label_2->setStyleSheet("color: #e8cc91;");
    label_2->setFixedHeight(20);
    label_2->setAlignment(Qt::AlignHCenter);

    inprocessTasks = new QListWidget();
    inprocessTasks->setDragEnabled(true);
    inprocessTasks->setStyleSheet(
        "color: #e8cc91; text-decoration: underline; border-width: 3px; font-size: " + font_size + "pt;"
        "border-color: #e8cc91;");
    inprocessTasks->setDragDropMode(QListWidget::DragDrop);
    inprocessTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    inprocessTasks->setWordWrap(true);

    QVBoxLayout *completeLayout = new QVBoxLayout;
    label_3 = new QLabel("Complete");
    label_3->setFixedHeight(20);
    // label_3->setStyleSheet("color: #9dda67;");
    label_3->setAlignment(Qt::AlignHCenter);

    completeTasks = new QListWidget();
    completeTasks->setDragEnabled(true);
    completeTasks->setStyleSheet(
        "color: #9dda67; text-decoration: line-through; border-width: 3px; font-size: " + font_size + "pt;"
        "border-color: #9dda67;");
    completeTasks->setDragDropMode(QListWidget::DragDrop);
    completeTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    completeTasks->setWordWrap(true);

    taskText = new QLineEdit();
    taskText->setPlaceholderText("Task...");
    taskText->setMaximumHeight(30);
    taskText->setFont(selectedFont);
    taskText->setStyleSheet("font-size: " + font_size + "pt;");

    addTask = new QPushButton(" + ");
    addTask->setFixedSize(40, 30);
    addTask->setFont(selectedFont);
    addTask->setStyleSheet("font-size: " + font_size + "pt;");

    rmTask = new QPushButton(" - ");
    rmTask->setFixedSize(40, 30);
    rmTask->setFont(selectedFont);
    rmTask->setStyleSheet("font-size: " + font_size + "pt;");


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
    projectsMainLabel->setStyleSheet("font-size: 32px;");

    QLabel *nsProjects = new QLabel("Not started");
    nsProjects->setFont(selectedFont);
    nsProjects->setAlignment(Qt::AlignHCenter);
    notStartedProjects = new QListWidget();
    notStartedProjects->setStyleSheet(
        "color: #b9676b; border-width: 3px; border-color: #b9676b; font-size: " + font_size + "pt;");
    notStartedProjects->setDragEnabled(true);
    notStartedProjects->setDragDropMode(QListWidget::DragDrop);
    notStartedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    notStartedProjects->setWordWrap(true);

    QLabel *sProjects = new QLabel("Started");
    sProjects->setFont(selectedFont);
    sProjects->setAlignment(Qt::AlignHCenter);
    startedProjects = new QListWidget();
    startedProjects->setStyleSheet(
        "color: #e8cc91; border-width: 3px; border-color: #e8cc91; font-size: " + font_size + "pt;");
    startedProjects->setDragEnabled(true);
    startedProjects->setDragDropMode(QListWidget::DragDrop);
    startedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    startedProjects->setWordWrap(true);

    QLabel *flProjects = new QLabel("Finishline");
    flProjects->setFont(selectedFont);
    flProjects->setAlignment(Qt::AlignHCenter);
    finishlineProjects = new QListWidget();
    finishlineProjects->setStyleSheet(
        "color: #8ebecf; border-width: 3px; border-color: #8ebecf; font-size: " + font_size + "pt;");
    finishlineProjects->setDragEnabled(true);
    finishlineProjects->setDragDropMode(QListWidget::DragDrop);
    finishlineProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    finishlineProjects->setWordWrap(true);

    QLabel *fProjects = new QLabel("Finished");
    fProjects->setFont(selectedFont);
    fProjects->setAlignment(Qt::AlignHCenter);
    finishedProjects = new QListWidget();
    finishedProjects->setStyleSheet(
        "color: #9dda67; border-width: 3px; border-color: #9dda67; font-size: " + font_size + "pt;");
    finishedProjects->setDragEnabled(true);
    finishedProjects->setDragDropMode(QListWidget::DragDrop);
    finishedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    finishedProjects->setWordWrap(true);

    projectsMainLabel->setFont(selectedFont);
    notStartedProjects->setFont(selectedFont);
    startedProjects->setFont(selectedFont);
    finishlineProjects->setFont(selectedFont);
    finishedProjects->setFont(selectedFont);

    notStartedProjects->addItem(
        "CodeKeeper\nNighty3098/CodeKeeper\n16.02.2024");

    // actions
    // menu
    projectsMenuButton = new QToolButton;
    projectsMenuButton->setText("...");
    projectsMenuButton->setFont(selectedFont);
    projectsMenuButton->setPopupMode(QToolButton::InstantPopup);
    projectsMenuButton->setFixedSize(40, 30);

    QMenu *projectsMenu = new QMenu(projectsMenuButton);
    projectsMenu->setFont(selectedFont);

    // actions for menu
    QAction *newProject =
        projectsMenu->addAction(QPixmap(":/new.png"), "New project");
    QAction *rmProject =
        projectsMenu->addAction(QPixmap(":/delete.png"), "Remove project");

    projectsMenu->addSeparator();

    QAction *showAddInfo = projectsMenu->addAction("Show additional info");
    showAddInfo->setCheckable(true);
    showAddInfo->setChecked(false);

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

    tabs->addTab(notesTab, "Notes");

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

    tabs->setFont(selectedFont);
    tabs->setStyleSheet("font-size: " + font_size + "pt;");

    incompleteTasks->setFont(selectedFont);
    inprocessTasks->setFont(selectedFont);
    completeTasks->setFont(selectedFont);

    label_1->setFont(selectedFont);
    label_2->setFont(selectedFont);
    label_3->setFont(selectedFont);




    // tasks
    connect(addTask, SIGNAL(clicked()), this, SLOT(addNewTask()));

    // main
    connect(openSettingsBtn, SIGNAL(clicked()), this,
            SLOT(openSettingsWindow()));

    mainLayout->addWidget(tabs);
}

MainWindow::~MainWindow() {
    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    globalSettings->setValue("geometry", saveGeometry());
}


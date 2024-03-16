#include "mainwindow.h"

#include "keeperFunc/functional.cpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    setMinimumSize(560, 400);

    // ========================================================

    // title
    mainTitle = new QLabel("CodeKeeper");
    mainTitle->setAlignment(Qt::AlignCenter);
    mainTitle->setStyleSheet("font-size: 32px;");

    // settings btn
    QHBoxLayout *settingsBtnLayout = new QHBoxLayout;
    openSettingsBtn = new QPushButton("Settings");
    openSettingsBtn->setFixedSize(200, 30);
    settingsBtnLayout->addWidget(openSettingsBtn);

    // sync btn
    QHBoxLayout *syncDataLayout = new QHBoxLayout;
    syncDataBtn = new QPushButton("Sync data");
    syncDataBtn->setFixedSize(200, 30);
    syncDataLayout->addWidget(syncDataBtn);

    // folder btn
    QHBoxLayout *openFolderlayout = new QHBoxLayout;
    openFolderBtn = new QPushButton("Open folder");
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
    notesList->setHeaderHidden(true);
    notesList->setWordWrap(true);
    notesList->setDragDropMode(QAbstractItemView::DragDrop);
    notesList->setDefaultDropAction(Qt::MoveAction);
    notesList->setDragEnabled(true);
    notesList->setMaximumWidth(200);

    // menu
    menuButton = new QToolButton;
    // menuButton->setIcon(QIcon(":/menu.png"));
    menuButton->setText("...");
    menuButton->setPopupMode(QToolButton::InstantPopup);
    menuButton->setFixedSize(40, 30);

    QMenu *menu = new QMenu(menuButton);

    // actions for menu
    QAction *newNote = menu->addAction(QPixmap(":/new_file.png"), "New Note");
    QAction *rmNote = menu->addAction(QPixmap(":/rm_file.png"), "Remove Note");

    menu->addSeparator();

    QAction *showList = menu->addAction("Show notes list", this, SLOT());
    showList->setCheckable(true);
    showList->setChecked(false);

    QAction *showPreview = menu->addAction("Show md preview");
    showPreview->setCheckable(true);
    showPreview->setChecked(true);

    menuButton->setMenu(menu);

    // other
    noteName = new QLineEdit();
    noteName->setFixedHeight(30);
    noteName->setPlaceholderText(" Note name ...");
    noteName->setStyleSheet("font-size: 16px; color: #8ebecf;");

    noteEdit = new QMarkdownTextEdit();
    // noteEdit = new QPlainTextEdit();
    noteEdit->setPlaceholderText(" Note ...");
    noteEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);

    timeLabel = new QLabel(getCurrentDateTimeString());
    timeLabel->setStyleSheet("font-size: 13px; color: #8ebecf;");
    timeLabel->setAlignment(Qt::AlignHCenter);





    notesL4->addWidget(timeLabel);
    notesL4->addWidget(menuButton);

    notesL3->addWidget(noteName);
    // notesL3->addWidget(menuButton);
    
    // notesL2->addLayout(notesL4);
    notesL2->addLayout(notesL3);
    notesL2->addWidget(noteEdit);

    notesL1->addWidget(notesList);
    notesL1->addLayout(notesL2);

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
        "color: #b9676b; border-width: 3px; border-color: #b9676b;");
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
        "color: #e8cc91; text-decoration: underline; border-width: 3px; "
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
        "color: #9dda67; text-decoration: line-through; border-width: 3px; "
        "border-color: #9dda67;");
    completeTasks->setDragDropMode(QListWidget::DragDrop);
    completeTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    completeTasks->setWordWrap(true);

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
    projectsMainLabel->setStyleSheet("font-size: 32px;");

    QLabel *nsProjects = new QLabel("Not started");
    notStartedProjects = new QListWidget();
    notStartedProjects->setStyleSheet(
        "color: #b9676b; border-width: 3px; border-color: #b9676b;");
    notStartedProjects->setDragEnabled(true);
    notStartedProjects->setDragDropMode(QListWidget::DragDrop);
    notStartedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    notStartedProjects->setWordWrap(true);

    QLabel *sProjects = new QLabel("Started");
    startedProjects = new QListWidget();
    startedProjects->setStyleSheet(
        "color: #e8cc91; border-width: 3px; border-color: #e8cc91;");
    startedProjects->setDragEnabled(true);
    startedProjects->setDragDropMode(QListWidget::DragDrop);
    startedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    startedProjects->setWordWrap(true);

    QLabel *flProjects = new QLabel("Finishline");
    finishlineProjects = new QListWidget();
    finishlineProjects->setStyleSheet(
        "color: #8ebecf; border-width: 3px; border-color: #8ebecf;");
    finishlineProjects->setDragEnabled(true);
    finishlineProjects->setDragDropMode(QListWidget::DragDrop);
    finishlineProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    finishlineProjects->setWordWrap(true);

    QLabel *fProjects = new QLabel("Finished");
    finishedProjects = new QListWidget();
    finishedProjects->setStyleSheet(
        "color: #9dda67; border-width: 3px; border-color: #9dda67;");
    finishedProjects->setDragEnabled(true);
    finishedProjects->setDragDropMode(QListWidget::DragDrop);
    finishedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    finishedProjects->setWordWrap(true);

    notStartedProjects->addItem("CodeKeeper");

    // actions
    // menu
    projectsMenuButton = new QToolButton;
    projectsMenuButton->setText("...");
    projectsMenuButton->setPopupMode(QToolButton::InstantPopup);
    projectsMenuButton->setFixedSize(40, 30);

    QMenu *projectsMenu = new QMenu(projectsMenuButton);

    // actions for menu
    QAction *newProject =
        projectsMenu->addAction(QPixmap(":/new_file.png"), "New project");
    QAction *rmProject =
        projectsMenu->addAction(QPixmap(":/rm_file.png"), "Remove project");

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

    // tasks
    connect(addTask, SIGNAL(clicked()), this, SLOT(addNewTask()));

    // main
    connect(openSettingsBtn, SIGNAL(clicked()), this,
            SLOT(openSettingsWindow()));

    mainLayout->addWidget(tabs);
}

MainWindow::~MainWindow() {}


#include "mainwindow.h"

#include <QPropertyAnimation>

#include "keeperFunc/functional.cpp"
#include "qmarkdowntextedit/markdownhighlighter.h"

Q_DECLARE_METATYPE(QDir)
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
    path = globalSettings->value("path").value<QDir>();
    QString dir = path.absolutePath();

    qDebug() << path;

    bool isVisibleNotesList =
        globalSettings->value("isVisibleNotesList", true).toBool();
    bool isVisibleFolders =
        globalSettings->value("isVisibleFolders", true).toBool();
    bool isVisiblePreview =
        globalSettings->value("isVisiblePreview", false).toBool();

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
    // openFolderlayout->addWidget(openFolderBtn);

    // ========================================================

    QGridLayout *notesGLayout = new QGridLayout;
    QHBoxLayout *syntaxMenu = new QHBoxLayout;
    syntaxMenu->setSpacing(1);
    syntaxMenu->setSizeConstraint(QLayout::SetFixedSize);
    syntaxMenu->setAlignment(Qt::AlignLeft);

    notesList = new QTreeWidget();
    notesList->setAnimated(true);
    notesList->setHeaderHidden(true);
    notesList->setWordWrap(true);
    notesList->setDragDropMode(QAbstractItemView::DragDrop);
    notesList->setDefaultDropAction(Qt::MoveAction);
    notesList->setDragEnabled(true);
    notesList->setMaximumWidth(250);

    // other
    noteName = new QLineEdit();
    noteName->setFixedHeight(30);
    noteName->setPlaceholderText(" Name ...");

    QFileSystemModel *model = new QFileSystemModel();
    model->setRootPath(".");

    mdPreview = new QTextBrowser();
    mdPreview->setOpenLinks(true);
    mdPreview->setOpenExternalLinks(true);

    noteEdit = new QMarkdownTextEdit();
    noteEdit->setPlaceholderText(" Just start typing");
    noteEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    noteEdit->setLineNumberEnabled(true);
    noteEdit->setLineNumbersCurrentLineColor("#fbcd76");
    noteEdit->setLineWidth(font_size.toInt());
    noteEdit->setHighlightingEnabled(true);

    timeLabel = new QLabel(getCurrentDateTimeString());
    timeLabel->setAlignment(Qt::AlignCenter);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            [=]() { timeLabel->setText(getCurrentDateTimeString()); });

    //    timer->start(1000);

    noteNameLabel = new QLabel("Note");
    noteNameLabel->setAlignment(Qt::AlignCenter);

    // update title
    connect(noteEdit, &QMarkdownTextEdit::textChanged, this,
            &MainWindow::setHeader);

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

    menu->addSeparator();

    QAction *showList =
        menu->addAction("Show notes list", this, SLOT(hideNotesList()));
    showList->setCheckable(true);
    showList->setChecked(isVisibleNotesList);

    QAction *showPreview =
        menu->addAction("Show md preview", this, SLOT(showPreview()));
    showPreview->setCheckable(true);
    showPreview->setChecked(isVisiblePreview);

    menuButton->setMenu(menu);

    setH1B = new QPushButton(QPixmap(":/h1.png"), "");
    setH2B = new QPushButton(QPixmap(":/h2.png"), "");
    setH3B = new QPushButton(QPixmap(":/h3.png"), "");
    setListB = new QPushButton(QPixmap(":/list.png"), "");
    setLinkB = new QPushButton(QPixmap(":/link.png"), "");
    setBoldB = new QPushButton(QPixmap(":/bold.png"), "");
    setItalicB = new QPushButton(QPixmap(":/italic.png"), "");
    setStrikeB = new QPushButton(QPixmap(":/strikethrough.png"), "");
    setTaskB = new QPushButton(QPixmap(":/checkbox.png"), "");

    setH1B->setStyleSheet("background-color: #222436; border-color: #222436;");
    setH2B->setStyleSheet("background-color: #222436; border-color: #222436;");
    setH3B->setStyleSheet("background-color: #222436; border-color: #222436;");
    setListB->setStyleSheet(
        "background-color: #222436; border-color: #222436;");
    setLinkB->setStyleSheet(
        "background-color: #222436; border-color: #222436;");
    setBoldB->setStyleSheet(
        "background-color: #222436; border-color: #222436;");
    setItalicB->setStyleSheet(
        "background-color: #222436; border-color: #222436;");
    setStrikeB->setStyleSheet(
        "background-color: #222436; border-color: #222436;");
    setTaskB->setStyleSheet(
        "background-color: #222436; border-color: #222436;");

    setH1B->setFixedSize(30, 30);
    setH2B->setFixedSize(30, 30);
    setH3B->setFixedSize(30, 30);
    setListB->setFixedSize(30, 30);
    setLinkB->setFixedSize(30, 30);
    setBoldB->setFixedSize(30, 30);
    setItalicB->setFixedSize(30, 30);
    setStrikeB->setFixedSize(30, 30);
    setTaskB->setFixedSize(30, 30);

    setH1B->setToolTip("<p style='color: #ffffff;'>Heading 1</p>");
    setH2B->setToolTip("<p style='color: #ffffff;'>Heading 2</p>");
    setH3B->setToolTip("<p style='color: #ffffff;'>Heading 3</p>");
    setListB->setToolTip("<p style='color: #ffffff;'>List</p>");
    setLinkB->setToolTip("<p style='color: #ffffff;'>Link</p>");
    setBoldB->setToolTip("<p style='color: #ffffff;'>Bold text</p>");
    setItalicB->setToolTip("<p style='color: #ffffff;'>Italic text</p>");
    setStrikeB->setToolTip("<p style='color: #ffffff;'>Strikethrough text</p>");
    setTaskB->setToolTip("<p style='color: #ffffff;'>Task</p>");

    connect(setH1B, &QPushButton::clicked, this, &MainWindow::setH1);
    connect(setH2B, &QPushButton::clicked, this, &MainWindow::setH2);
    connect(setH3B, &QPushButton::clicked, this, &MainWindow::setH3);
    connect(setListB, &QPushButton::clicked, this, &MainWindow::setList);
    connect(setLinkB, &QPushButton::clicked, this, &MainWindow::setLink);
    connect(setBoldB, &QPushButton::clicked, this, &MainWindow::setBold);
    connect(setItalicB, &QPushButton::clicked, this, &MainWindow::setItalic);
    connect(setStrikeB, &QPushButton::clicked, this, &MainWindow::setStrike);
    connect(setTaskB, &QPushButton::clicked, this, &MainWindow::setTask);

    syntaxMenu->addWidget(setH1B);
    syntaxMenu->addWidget(setH2B);
    syntaxMenu->addWidget(setH3B);

    syntaxMenu->addWidget(setBoldB);
    syntaxMenu->addWidget(setItalicB);
    syntaxMenu->addWidget(setStrikeB);

    syntaxMenu->addWidget(setListB);
    syntaxMenu->addWidget(setLinkB);
    syntaxMenu->addWidget(setTaskB);

    notesGLayout->addWidget(menuButton, 0, 5);
    notesGLayout->addLayout(syntaxMenu, 0, 2);
    notesGLayout->addWidget(noteNameLabel, 0, 3);
    // notesGLayout->addWidget(timeLabel, 0, 3);
    // notesGLayout->addWidget(foldersList, 1, 0);
    notesGLayout->addWidget(notesList, 1, 1);
    notesGLayout->addWidget(noteEdit, 1, 2);
    notesGLayout->addWidget(mdPreview, 1, 3);

    notesList->setVisible(isVisibleNotesList);
    // foldersList->setVisible(isVisibleFolders);
    mdPreview->setVisible(isVisiblePreview);

    // ========================================================
    QGridLayout *tasksGLayout = new QGridLayout;

    tasksMenuBtn = new QToolButton;
    tasksMenuBtn->setText("...");
    tasksMenuBtn->setFixedSize(30, 20);
    tasksMenuBtn->setPopupMode(QToolButton::InstantPopup);
    tasksMenuBtn->setStyleSheet("border-radius: 2px;");

    QMenu *tasksMenu = new QMenu(tasksMenuBtn);
    tasksMenu->setFont(selectedFont);

    QAction *addTask = tasksMenu->addAction(QPixmap(":/new.png"), "Add task",
                                            this, SLOT(addNewTask()));
    QAction *rmTask = tasksMenu->addAction(
        QPixmap(":/delete.png"), "Delete task", this, SLOT(removeTask()));

    tasksMenuBtn->setMenu(tasksMenu);

    tasksProgress = new QProgressBar();
    tasksProgress->setMaximum(100);
    tasksProgress->setMaximumWidth(400);
    tasksProgress->setFixedHeight(20);
    tasksProgress->setAlignment(Qt::AlignCenter);

    label_1 = new QLabel("Incomplete");
    label_1->setStyleSheet("font-size: 16px;");
    label_1->setFixedHeight(25);
    label_1->setAlignment(Qt::AlignHCenter);

    incompleteTasks = new QListWidget();
    incompleteTasks->setDragEnabled(true);
    incompleteTasks->setDragDropMode(QListWidget::DragDrop);
    incompleteTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    incompleteTasks->setWordWrap(true);
    incompleteTasks->setSpacing(5);

    label_2 = new QLabel("Inprocess");
    label_2->setStyleSheet("font-size: 16px;");
    label_2->setFixedHeight(25);
    label_2->setAlignment(Qt::AlignHCenter);

    inprocessTasks = new QListWidget();
    inprocessTasks->setDragEnabled(true);
    inprocessTasks->setDragDropMode(QListWidget::DragDrop);
    inprocessTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    inprocessTasks->setWordWrap(true);
    inprocessTasks->setSpacing(5);

    label_3 = new QLabel("Complete");
    label_3->setStyleSheet("font-size: 16px;");
    label_3->setFixedHeight(25);
    label_3->setAlignment(Qt::AlignHCenter);

    completeTasks = new QListWidget();
    completeTasks->setDragEnabled(true);
    completeTasks->setDragDropMode(QListWidget::DragDrop);
    completeTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
    completeTasks->setWordWrap(true);
    completeTasks->setSpacing(5);

    taskText = new QLineEdit();
    taskText->setPlaceholderText(" Task...");
    taskText->setFixedHeight(30);

    tasksGLayout->addWidget(tasksMenuBtn, 0, 2);
    tasksGLayout->addWidget(tasksProgress, 0, 1);

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

    projectsMainLabel = new QLabel("Projects");
    projectsMainLabel->setAlignment(Qt::AlignCenter);

    nsProjects = new QLabel("Not started");
    nsProjects->setStyleSheet("font-size: 16px;");
    nsProjects->setAlignment(Qt::AlignHCenter);
    notStartedProjects = new QListWidget();
    notStartedProjects->setDragEnabled(true);
    notStartedProjects->setDragDropMode(QListWidget::DragDrop);
    notStartedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    notStartedProjects->setWordWrap(true);
    notStartedProjects->setSpacing(5);

    sProjects = new QLabel("Started");
    sProjects->setStyleSheet("font-size: 16px;");
    sProjects->setAlignment(Qt::AlignHCenter);
    startedProjects = new QListWidget();
    startedProjects->setDragEnabled(true);
    startedProjects->setDragDropMode(QListWidget::DragDrop);
    startedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    startedProjects->setWordWrap(true);
    startedProjects->setSpacing(5);

    flProjects = new QLabel("Finishline");
    flProjects->setStyleSheet("font-size: 16px;");
    flProjects->setAlignment(Qt::AlignHCenter);
    finishlineProjects = new QListWidget();
    finishlineProjects->setDragEnabled(true);
    finishlineProjects->setDragDropMode(QListWidget::DragDrop);
    finishlineProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
    finishlineProjects->setWordWrap(true);
    finishlineProjects->setSpacing(5);

    fProjects = new QLabel("Finished");
    fProjects->setStyleSheet("font-size: 16px;");
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

    projectsGLayout->addWidget(projectsMainLabel, 0, 0, 1, 0);
    projectsGLayout->addWidget(projectsMenuButton, 0, 2);
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
    QVBoxLayout *firstLayout = new QVBoxLayout(mainTab);

    firstLayout->addWidget(mainTitle);
    firstLayout->addLayout(syncDataLayout);
    firstLayout->addLayout(openFolderlayout);
    firstLayout->addLayout(settingsBtnLayout);

    tabs->addTab(mainTab, "Homepage");

    // notes tab
    QWidget *notesTab = new QWidget();
    QVBoxLayout *notesLayout = new QVBoxLayout(notesTab);

    notesLayout->addLayout(notesGLayout);

    tabs->addTab(notesTab, "Doc");

    // tasks tab
    QWidget *tasksTab = new QWidget();
    QVBoxLayout *tasksLayout = new QVBoxLayout(tasksTab);

    tasksLayout->addLayout(tasksGLayout);

    tabs->addTab(tasksTab, "Tasks");

    // projects tab
    QWidget *projectsTab = new QWidget();
    QVBoxLayout *projectsLayout = new QVBoxLayout(projectsTab);

    projectsLayout->addLayout(projectsGLayout);

    tabs->addTab(projectsTab, "Projects");

    // task
    connect(taskText, &QLineEdit::returnPressed, [=] {
        QString text = taskText->text();

        if (!text.isEmpty()) {
            taskText->clear();
            incompleteTasks->addItem(text);
        } else {
            qDebug() << "Task is empty";
        }
    });

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

    connect(noteEdit, &QMarkdownTextEdit::textChanged, this,
            &MainWindow::updateMDPreview);

    connect(tabs, &QTabWidget::currentChanged, this, [=]() {
        updateTasksProgress(tabs, incompleteTasks, inprocessTasks,
                            completeTasks, tasksProgress);
    });

    connect(completeTasks, &QListWidget::itemDoubleClicked, this,
            [=](QListWidgetItem *item) {
                renameItemOnDoubleClick(completeTasks, item);
            });

    connect(incompleteTasks, &QListWidget::itemDoubleClicked, this,
            [=](QListWidgetItem *item) {
                renameItemOnDoubleClick(completeTasks, item);
            });

    connect(inprocessTasks, &QListWidget::itemDoubleClicked, this,
            [=](QListWidgetItem *item) {
                renameItemOnDoubleClick(completeTasks, item);
            });

    connect(
        notStartedProjects, &QListWidget::itemDoubleClicked, this,
        [=](QListWidgetItem *item) { openProject(notStartedProjects, item); });
    connect(startedProjects, &QListWidget::itemDoubleClicked, this,
            [=](QListWidgetItem *item) { openProject(startedProjects, item); });
    connect(
        finishlineProjects, &QListWidget::itemDoubleClicked, this,
        [=](QListWidgetItem *item) { openProject(finishlineProjects, item); });
    connect(
        finishedProjects, &QListWidget::itemDoubleClicked, this,
        [=](QListWidgetItem *item) { openProject(finishedProjects, item); });

    connect(
        notesList, &QTreeWidget::itemDoubleClicked, this,
        [=](QTreeWidgetItem *item) { onNoteDoubleClicked(item, noteEdit, 0); });

    mainLayout->addWidget(tabs);

    displayDirectoryStructure(path, notesList);
    loadTasks();
    loadProjects();
    setFontPr1();
}

MainWindow::~MainWindow() {
    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    globalSettings->setValue("geometry", saveGeometry());
}

#include "mainwindow.h"

#include "keeperFunc/functional.cpp"
#include "keeperFunc/notesFunc.cpp"
#include "keeperFunc/projectsFunc.cpp"
#include "keeperFunc/tasksFunc.cpp"
#include "qmarkdowntextedit/markdownhighlighter.h"
#include "sql_db/projectsDB.cpp"
#include "sql_db/tasksDB.cpp"
#include <QInputDialog>
#include <QPropertyAnimation>
#include <QSizeGrip>
#include <QtWidgets>

Q_DECLARE_METATYPE(QDir)

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  // for startup time
  QTime startup;
  startup.start();

  centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
  this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
  this->setMouseTracking(true);
  this->setMinimumSize(560, 400);
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setWindowIcon(QIcon(":/icon.png"));

  sizeGrip = new QSizeGrip(this);
  sizeGrip->setFixedSize(12, 12);
  sizeGrip->setVisible(true);
  sizeGrip->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

  sizeGrip2 = new QSizeGrip(this);
  sizeGrip2->setFixedSize(12, 12);
  sizeGrip2->setVisible(true);
  sizeGrip2->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

  sizeGrip3 = new QSizeGrip(this);
  sizeGrip3->setFixedSize(12, 12);
  sizeGrip3->setVisible(true);
  sizeGrip3->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

  sizeGrip4 = new QSizeGrip(this);
  sizeGrip4->setFixedSize(12, 12);
  sizeGrip4->setVisible(true);
  sizeGrip4->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

  winControlL = new QHBoxLayout;
  winControlL->setSpacing(7);

  isFullScreen = false;

  QSpacerItem *headerSp =
      new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

  closeBtn = new QPushButton();
  minimizeBtn = new QPushButton();
  maximizeBtn = new QPushButton();

  closeBtn->setFixedSize(15, 15);
  minimizeBtn->setFixedSize(15, 15);
  maximizeBtn->setFixedSize(15, 15);

  closeBtn->setStyleSheet("QPushButton {"
                          "    border-color: rgba(0, 0, 0, 0);"
                          "    background-color: rgba(0, 0, 0, 0);"
                          "    background-image: url(':/red.png');"
                          "    background-repeat: no-repeat;"
                          "}"

                          "QPushButton:hover {"
                          "    border-color: rgba(0, 0, 0, 0);"
                          "    background-image: url(':/redHovered.png');"
                          "    background-repeat: no-repeat;"
                          "    background-color: rgba(0, 0, 0, 0);"
                          "}");
  minimizeBtn->setStyleSheet("QPushButton {"
                             "    border-color: rgba(0, 0, 0, 0);"
                             "    background-color: rgba(0, 0, 0, 0);"
                             "    background-image: url(':/yellow.png');"
                             "    background-repeat: no-repeat;"
                             "}"

                             "QPushButton:hover {"
                             "    border-color: rgba(0, 0, 0, 0);"
                             "    background-image: url(':/yellowHovered.png');"
                             "    background-repeat: no-repeat;"
                             "    background-color: rgba(0, 0, 0, 0);"
                             "}");

  maximizeBtn->setStyleSheet("QPushButton {"
                             "    border-color: rgba(0, 0, 0, 0);"
                             "    background-color: rgba(0, 0, 0, 0);"
                             "    background-image: url(':/green.png');"
                             "    background-repeat: no-repeat;"
                             "}"

                             "QPushButton:hover {"
                             "    border-color: rgba(0, 0, 0, 0);"
                             "    background-image: url(':/greenHovered.png');"
                             "    background-color: rgba(0, 0, 0, 0);"
                             "    background-repeat: no-repeat;"
                             "}");

  winControlL->addWidget(closeBtn);
  winControlL->addWidget(minimizeBtn);
  winControlL->addWidget(maximizeBtn);
  winControlL->addItem(headerSp);
  winControlL->addWidget(sizeGrip2);

  mainLayout = new QGridLayout(centralWidget);

  globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
  restoreGeometry(globalSettings->value("geometry").toByteArray());

  selectedFont = globalSettings->value("font").value<QFont>();
  font_size = globalSettings->value("fontSize").value<QString>();
  theme = globalSettings->value("theme").value<QString>();
  path = globalSettings->value("path").value<QDir>();

  QString dir = path.absolutePath();
  qDebug() << dir;

  bool isVisibleNotesList =
      globalSettings->value("isVisibleNotesList", true).toBool();
  bool isVisibleFolders =
      globalSettings->value("isVisibleFolders", true).toBool();
  bool isVisiblePreview =
      globalSettings->value("isVisiblePreview", false).toBool();
  bool isViewMode = globalSettings->value("isViewMode", false).toBool();

  // ========================================================

  // title
  mainTitle = new QLabel("CodeKeeper");
  mainTitle->setAlignment(Qt::AlignCenter);
  mainTitle->setStyleSheet("font-size: 46px;");

  QPropertyAnimation *animation =
      new QPropertyAnimation(mainTitle, "background-color: ");
  animation->setDuration(
      2000); // Set the duration of the animation to 2 seconds

  QColor startColor("#aaff6a"); // Set the start color to red
  QColor endColor("#ffea6a");   // Set the end color to green

  animation->setStartValue(startColor);
  animation->setEndValue(endColor);

  // settings btn
  QHBoxLayout *settingsBtnLayout = new QHBoxLayout;
  openSettingsBtn = new QPushButton(QPixmap(":/settings.png"), " Settings");
  openSettingsBtn->setFixedSize(200, 25);
  settingsBtnLayout->addWidget(openSettingsBtn);

  // sync btn
  QHBoxLayout *syncDataLayout = new QHBoxLayout;
  syncDataBtn = new QPushButton(QPixmap(":/retry.png"), " Sync data");
  syncDataBtn->setFixedSize(200, 25);
  syncDataLayout->addWidget(syncDataBtn);

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

  // icons
  iconProvider = new CustomIconProvider();

  QStringList filters;
  filters << ""
          << "*.md"
          << "*.txt"
          << "*.html";

  notesDirModel = new QFileSystemModel();
  notesDirModel->setIconProvider(iconProvider);
  notesDirModel->setRootPath("../");
  notesDirModel->setNameFilters(filters);
  notesDirModel->setNameFilterDisables(false);

  notesList = new QTreeView();
  notesList->setAnimated(true);
  notesList->setWordWrap(true);
  notesList->setDragDropMode(QAbstractItemView::DragDrop);
  notesList->setDefaultDropAction(Qt::MoveAction);
  notesList->setDragEnabled(true);
  notesList->setMinimumWidth(100);
  notesList->setHeaderHidden(true);
  notesList->setColumnHidden(1, true);
  notesList->setSortingEnabled(true);
  notesList->setRootIndex(notesDirModel->index("../"));

  notesList->setModel(notesDirModel);
  notesList->setColumnWidth(0, 297);
  notesList->setColumnHidden(1, true);
  notesList->setColumnHidden(2, true);
  notesList->setColumnHidden(3, true);
  notesList->setColumnHidden(4, true);

  noteName = new QLineEdit();
  noteName->setFixedSize(200, 30);
  noteName->setPlaceholderText(" Name ...");

  mdPreview = new QTextBrowser();
  mdPreview->setOpenLinks(true);
  mdPreview->setOpenExternalLinks(true);
  mdPreview->setAlignment(Qt::AlignHCenter);

  noteEdit = new QMarkdownTextEdit();
  noteEdit->setPlaceholderText(" Just start typing");
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
  noteNameLabel = new QLabel("Note");
  noteNameLabel->setAlignment(Qt::AlignCenter);
  connect(noteEdit, &QMarkdownTextEdit::textChanged, this,
          &MainWindow::setHeader);

  menuButton = new QToolButton;
  menuButton->setIcon(QPixmap(":/main.png"));
  menuButton->setIconSize(QSize(10, 10));
  menuButton->setPopupMode(QToolButton::InstantPopup);
  menuButton->setStyleSheet(
      "background-color: #222436; border-color: #222436; border-width: 4px;");

  QMenu *menu = new QMenu(menuButton);
  menu->setFont(selectedFont);

  QMenu *viewMenu = new QMenu("View", menu);

  // actions for menu
  newNote = menu->addAction(QPixmap(":/new.png"), "New Note", this,
                            SLOT(createNote()), Qt::CTRL + Qt::Key_N);
  rmNote = menu->addAction(QPixmap(":/delete.png"), "Remove", this,
                           SLOT(removeNote()), Qt::CTRL + Qt::Key_Delete);
  newFolder =
      menu->addAction(QPixmap(":/new_folder.png"), "New folder", this,
                      SLOT(createFolder()), Qt::CTRL + Qt::SHIFT + Qt::Key_N);

  menu->addSeparator();

  showList = viewMenu->addAction("Show notes list", this, SLOT(hideNotesList()),
                                 Qt::CTRL + Qt::SHIFT + Qt::Key_L);
  showList->setCheckable(true);
  showList->setChecked(isVisibleNotesList);

  showRender = viewMenu->addAction("Show md preview", this, SLOT(showPreview()),
                                   Qt::CTRL + Qt::SHIFT + Qt::Key_P);
  showRender->setCheckable(true);
  showRender->setChecked(isVisiblePreview);

  viewMenu->addSeparator();

  viewMode =
      viewMenu->addAction(QPixmap(":/view.png"), "Reading mode", this,
                          SLOT(toViewMode()), Qt::CTRL + Qt::SHIFT + Qt::Key_V);
  viewMode->setCheckable(true);
  viewMode->setChecked(isViewMode);

  QMenu *editMenu = new QMenu("Edit", menu);

  setH1A =
      editMenu->addAction(QPixmap(":/h1.png"), "Set H1", this, SLOT(setH1()));
  setH2A =
      editMenu->addAction(QPixmap(":/h2.png"), "Set H2", this, SLOT(setH2()));
  setH3A =
      editMenu->addAction(QPixmap(":/h3.png"), "Set H3", this, SLOT(setH3()));

  editMenu->addSeparator();

  setListA = editMenu->addAction(QPixmap(":/list.png"), "Add list item", this,
                                 SLOT(setList()));
  setNumListA = editMenu->addAction(
      QPixmap(":/numList.png"), "Add numbered list", this, SLOT(setNumList()));
  setLinkA = editMenu->addAction(QPixmap(":/link.png"), "Add link", this,
                                 SLOT(setLink()));
  setTaskA = editMenu->addAction(QPixmap(":/checkbox.png"), "Add task", this,
                                 SLOT(setTask()));

  editMenu->addSeparator();

  setBoldA = editMenu->addAction(QPixmap(":/bold.png"), "Set bold", this,
                                 SLOT(setBold()));
  setItalicA = editMenu->addAction(QPixmap(":/italic.png"), "Set italic", this,
                                   SLOT(setItalic()));
  setStrikeA =
      editMenu->addAction(QPixmap(":/strikethrough.png"), "Set strikethrough",
                          this, SLOT(setStrike()));

  setTableA = editMenu->addAction(QPixmap(":/table.png"), "Add table", this,
                                  SLOT(setTable()));

  menu->addMenu(editMenu);
  menu->addMenu(viewMenu);
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
  setNumListB = new QPushButton(QPixmap(":/numList.png"), "");
  setTableB = new QPushButton(QPixmap(":/table.png"), "");

  setH1B->setStyleSheet("background-color: #222436; border-color: #222436;");
  setH2B->setStyleSheet("background-color: #222436; border-color: #222436;");
  setH3B->setStyleSheet("background-color: #222436; border-color: #222436;");
  setListB->setStyleSheet("background-color: #222436; border-color: #222436;");
  setLinkB->setStyleSheet("background-color: #222436; border-color: #222436;");
  setBoldB->setStyleSheet("background-color: #222436; border-color: #222436;");
  setItalicB->setStyleSheet(
      "background-color: #222436; border-color: #222436;");
  setStrikeB->setStyleSheet(
      "background-color: #222436; border-color: #222436;");
  setTaskB->setStyleSheet("background-color: #222436; border-color: #222436;");
  setNumListB->setStyleSheet(
      "background-color: #222436; border-color: #222436;");
  setTableB->setStyleSheet("background-color: #222436; border-color: #222436;");

  setH1B->setFixedSize(30, 30);
  setH2B->setFixedSize(30, 30);
  setH3B->setFixedSize(30, 30);
  setListB->setFixedSize(30, 30);
  setLinkB->setFixedSize(30, 30);
  setBoldB->setFixedSize(30, 30);
  setItalicB->setFixedSize(30, 30);
  setStrikeB->setFixedSize(30, 30);
  setTaskB->setFixedSize(30, 30);
  setNumListB->setFixedSize(30, 30);
  setTableB->setFixedSize(30, 30);

  setH1B->setToolTip("<p style='color: #ffffff;'>Heading 1</p>");
  setH2B->setToolTip("<p style='color: #ffffff;'>Heading 2</p>");
  setH3B->setToolTip("<p style='color: #ffffff;'>Heading 3</p>");
  setListB->setToolTip("<p style='color: #ffffff;'>List</p>");
  setLinkB->setToolTip("<p style='color: #ffffff;'>Link</p>");
  setBoldB->setToolTip("<p style='color: #ffffff;'>Bold text</p>");
  setItalicB->setToolTip("<p style='color: #ffffff;'>Italic text</p>");
  setStrikeB->setToolTip("<p style='color: #ffffff;'>Strikethrough text</p>");
  setTaskB->setToolTip("<p style='color: #ffffff;'>Task</p>");
  setNumListB->setToolTip("<p style='color: #ffffff;'>Numbered list</p>");
  setTableB->setToolTip("<p style='color: #ffffff;'>Insert table</p>");

  menuLayout->addWidget(menuButton);
  menuLayout->addWidget(setH1B);
  menuLayout->addWidget(setH2B);
  menuLayout->addWidget(setH3B);

  menuLayout->addWidget(setBoldB);
  menuLayout->addWidget(setItalicB);
  menuLayout->addWidget(setStrikeB);

  menuLayout->addWidget(setListB);
  menuLayout->addWidget(setNumListB);
  menuLayout->addWidget(setLinkB);
  menuLayout->addWidget(setTaskB);
  menuLayout->addWidget(setTableB);

  // contentLayout->addWidget(notesList);
  // contentLayout->addWidget(noteEdit);
  // contentLayout->addWidget(mdPreview);

  notesCLayout->addLayout(menuLayout);
  notesCLayout->addWidget(noteSplitter);
  // notesCLayout->addLayout(contentLayout);

  notesList->setVisible(isVisibleNotesList);
  mdPreview->setVisible(isVisiblePreview);

  // ========================================================
  QGridLayout *tasksGLayout = new QGridLayout;
  tasksGLayout->setSpacing(0);

  QHBoxLayout *tasksStatsL = new QHBoxLayout;
  tasksStatsL->setSpacing(10);

  QSpacerItem *spacer1 =
      new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
  QSpacerItem *spacer2 =
      new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

  tasksMenuBtn = new QToolButton;
  tasksMenuBtn->setIcon(QPixmap(":/main.png"));
  tasksMenuBtn->setIconSize(QSize(50, 50));
  tasksMenuBtn->setFixedSize(30, 30);
  tasksMenuBtn->setPopupMode(QToolButton::InstantPopup);
  tasksMenuBtn->setStyleSheet(
      "background-color: #222436; border-color: #222436; border-width: 0px;");

  QMenu *tasksMenu = new QMenu(tasksMenuBtn);
  tasksMenu->setFont(selectedFont);

  addTask = tasksMenu->addAction(QPixmap(":/new.png"), "Add task", this,
                                 SLOT(addNewTask()), Qt::Key_Return);
  rmTask = tasksMenu->addAction(QPixmap(":/delete.png"), "Delete task", this,
                                SLOT(removeTask()), Qt::Key_Delete);

  tasksMenuBtn->setMenu(tasksMenu);

  tasksProgress = new QProgressBar();
  tasksProgress->setMaximum(100);
  tasksProgress->setMaximumWidth(300);
  tasksProgress->setFixedHeight(25);
  tasksProgress->setAlignment(Qt::AlignCenter);

  tasksStatsL->addItem(spacer1);
  tasksStatsL->addWidget(tasksMenuBtn);
  tasksStatsL->addWidget(tasksProgress);
  tasksStatsL->addItem(spacer2);

  label_1 = new QLabel("Incomplete");
  label_1->setStyleSheet("font-size: 16px;");
  label_1->setFixedHeight(30);
  label_1->setAlignment(Qt::AlignCenter);

  incompleteTasks = new QListWidget();
  // incompleteTasks->setDragEnabled(true);
  incompleteTasks->setDragDropMode(QListWidget::DragDrop);
  incompleteTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
  incompleteTasks->setWordWrap(true);
  incompleteTasks->setSpacing(5);
  incompleteTasks->setObjectName("IncompleteTasks");

  label_2 = new QLabel("Inprocess");
  label_2->setStyleSheet("font-size: 16px;");
  label_2->setFixedHeight(30);
  label_2->setAlignment(Qt::AlignCenter);

  inprocessTasks = new QListWidget();
  // inprocessTasks->setDragEnabled(true);
  inprocessTasks->setDragDropMode(QListWidget::DragDrop);
  inprocessTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
  inprocessTasks->setWordWrap(true);
  inprocessTasks->setSpacing(5);
  inprocessTasks->setObjectName("InprocessTasks");

  label_3 = new QLabel("Complete");
  label_3->setStyleSheet("font-size: 16px;");
  label_3->setFixedHeight(30);
  label_3->setAlignment(Qt::AlignCenter);

  completeTasks = new QListWidget();
  // completeTasks->setDragEnabled(true);
  completeTasks->setDragDropMode(QListWidget::DragDrop);
  completeTasks->setDefaultDropAction(Qt::DropAction::MoveAction);
  completeTasks->setWordWrap(true);
  completeTasks->setSpacing(5);
  completeTasks->setObjectName("CompleteTasks");

  taskText = new QLineEdit();
  taskText->setPlaceholderText(" Task...");
  taskText->setFixedHeight(30);

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

  QSpacerItem *spacer3 =
      new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
  QSpacerItem *spacer4 =
      new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

  // menu
  projectsMenuButton = new QToolButton();
  projectsMenuButton->setIcon(QPixmap(":/main.png"));
  projectsMenuButton->setPopupMode(QToolButton::InstantPopup);
  projectsMenuButton->setFixedSize(30, 30);
  projectsMenuButton->setIconSize(QSize(40, 40));
  projectsMenuButton->setStyleSheet(
      "background-color: #222436; border-color: #222436; border-width: 0px;");

  projectsMenu = new QMenu(projectsMenuButton);

  // actions for menu
  newProject =
      projectsMenu->addAction(QPixmap(":/new.png"), "New", this,
                              SLOT(createProject()), Qt::CTRL + Qt::Key_N);
  rmProject = projectsMenu->addAction(QPixmap(":/delete.png"), "Remove", this,
                                      SLOT(removeProject()), Qt::Key_Delete);

  projectsMenuButton->setMenu(projectsMenu);

  projectsMainLabel = new QLabel("Projects");
  projectsMainLabel->setAlignment(Qt::AlignCenter);

  totalProjectsL = new QLabel();
  totalProjectsL->setFixedHeight(30);
  totalProjectsL->setAlignment(Qt::AlignCenter);

  nsProjects = new QLabel("Not started");
  nsProjects->setStyleSheet("font-size: 16px;");
  nsProjects->setAlignment(Qt::AlignHCenter);
  notStartedProjects = new QListWidget();
  notStartedProjects->setDragEnabled(true);
  notStartedProjects->setDragDropMode(QListWidget::DragDrop);
  notStartedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
  notStartedProjects->setWordWrap(true);
  notStartedProjects->setSpacing(5);
  notStartedProjects->setObjectName("NotStartedProjects");

  sProjects = new QLabel("Started");
  sProjects->setStyleSheet("font-size: 16px;");
  sProjects->setAlignment(Qt::AlignHCenter);
  startedProjects = new QListWidget();
  startedProjects->setDragEnabled(true);
  startedProjects->setDragDropMode(QListWidget::DragDrop);
  startedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
  startedProjects->setWordWrap(true);
  startedProjects->setSpacing(5);
  startedProjects->setObjectName("StartedProjects");

  flProjects = new QLabel("For review");
  flProjects->setStyleSheet("font-size: 16px;");
  flProjects->setAlignment(Qt::AlignHCenter);
  finishlineProjects = new QListWidget();
  finishlineProjects->setDragEnabled(true);
  finishlineProjects->setDragDropMode(QListWidget::DragDrop);
  finishlineProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
  finishlineProjects->setWordWrap(true);
  finishlineProjects->setSpacing(5);
  finishlineProjects->setObjectName("FinishlineProjects");

  fProjects = new QLabel("Finished");
  fProjects->setStyleSheet("font-size: 16px;");
  fProjects->setAlignment(Qt::AlignHCenter);
  finishedProjects = new QListWidget();
  finishedProjects->setDragEnabled(true);
  finishedProjects->setDragDropMode(QListWidget::DragDrop);
  finishedProjects->setDefaultDropAction(Qt::DropAction::MoveAction);
  finishedProjects->setWordWrap(true);
  finishedProjects->setSpacing(5);
  finishedProjects->setObjectName("FinishedProjects");

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
  // tabs->setTabPosition(QTabWidget::West);

  // main tab
  QWidget *mainTab = new QWidget();
  QVBoxLayout *firstLayout = new QVBoxLayout(mainTab);

  firstLayout->addWidget(mainTitle);
  firstLayout->addLayout(syncDataLayout);
  firstLayout->addLayout(settingsBtnLayout);

  tabs->addTab(mainTab, "Homepage");

  // notes tab
  QWidget *notesTab = new QWidget();
  QVBoxLayout *notesLayout = new QVBoxLayout(notesTab);

  notesLayout->addLayout(notesCLayout);

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

  QIcon mainIco(":/main.png");
  QIcon projectsIco(":/project.png");
  QIcon noteIco(":/edit.png");
  QIcon tasksIco(":/task.png");

  tabs->setTabIcon(tabs->indexOf(mainTab), mainIco);
  tabs->setTabIcon(tabs->indexOf(notesTab), noteIco);
  tabs->setTabIcon(tabs->indexOf(tasksTab), tasksIco);
  tabs->setTabIcon(tabs->indexOf(projectsTab), projectsIco);

  tabs->setTabBarAutoHide(true);

  mainLayout->addLayout(winControlL, 0, 0, 1, 2);
  mainLayout->addWidget(tabs, 1, 0);
  mainLayout->addWidget(sizeGrip3, 2, 0);
  mainLayout->addWidget(sizeGrip4, 2, 1);

  // connects
  connect(openSettingsBtn, SIGNAL(clicked()), this, SLOT(openSettingsWindow()));

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
    updateTasksProgress(tabs, incompleteTasks, inprocessTasks, completeTasks,
                        tasksProgress);
  });

  connect(tabs, &QTabWidget::currentChanged, this, [=]() {
    getTotalTasks(tabs, incompleteTasks, inprocessTasks, completeTasks);
  });

  connect(tabs, &QTabWidget::currentChanged, this, [=]() {
    getTotalProjects(tabs, notStartedProjects, startedProjects,
                     finishedProjects, finishlineProjects);
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
  connect(finishedProjects, &QListWidget::itemDoubleClicked, this,
          [=](QListWidgetItem *item) { openProject(finishedProjects, item); });

  connect(setH1B, &QPushButton::clicked, this, &MainWindow::setH1);
  connect(setH2B, &QPushButton::clicked, this, &MainWindow::setH2);
  connect(setH3B, &QPushButton::clicked, this, &MainWindow::setH3);
  connect(setListB, &QPushButton::clicked, this, &MainWindow::setList);
  connect(setLinkB, &QPushButton::clicked, this, &MainWindow::setLink);
  connect(setBoldB, &QPushButton::clicked, this, &MainWindow::setBold);
  connect(setItalicB, &QPushButton::clicked, this, &MainWindow::setItalic);
  connect(setStrikeB, &QPushButton::clicked, this, &MainWindow::setStrike);
  connect(setTaskB, &QPushButton::clicked, this, &MainWindow::setTask);
  connect(setNumListB, &QPushButton::clicked, this, &MainWindow::setNumList);
  connect(setTableB, &QPushButton::clicked, this, &MainWindow::setTable);

  connect(notesList, &QTreeView::clicked, this,
          &MainWindow::onNoteDoubleClicked);

  connect(noteEdit, &QMarkdownTextEdit::textChanged, this,
          &MainWindow::saveNote);

  connect(notesList, &QTreeView::entered, this, [=](const QModelIndex &index) {
    if (index.isValid()) {
      QDateTime lastModified =
          notesDirModel->data(index, Qt::UserRole + 1).toDateTime();
      if (lastModified.isValid()) {
        QString toolTip = "Last modified: " + lastModified.toString();
        notesList->setToolTip(toolTip);
        qDebug() << toolTip;
      }
    }
  });

  QShortcut *toFirstTab =
      new QShortcut(QKeySequence(Qt::ALT + Qt::Key_1), this);
  QShortcut *toSecondTab =
      new QShortcut(QKeySequence(Qt::ALT + Qt::Key_2), this);
  QShortcut *toThirdTab =
      new QShortcut(QKeySequence(Qt::ALT + Qt::Key_3), this);
  QShortcut *toFourthTab =
      new QShortcut(QKeySequence(Qt::ALT + Qt::Key_4), this);

  // Connect QShortcuts to QTabWidget's setCurrentIndex function
  connect(toFirstTab, &QShortcut::activated, tabs,
          [this]() { tabs->setCurrentIndex(0); });
  connect(toSecondTab, &QShortcut::activated, tabs,
          [this]() { tabs->setCurrentIndex(1); });
  connect(toThirdTab, &QShortcut::activated, tabs,
          [this]() { tabs->setCurrentIndex(2); });
  connect(toFourthTab, &QShortcut::activated, tabs,
          [this]() { tabs->setCurrentIndex(3); });

  connect(
      incompleteTasks, &QListWidget::itemChanged, this,
      [=](QListWidgetItem *item) { onMovingTaskTo(item, incompleteTasks); });
  connect(inprocessTasks, &QListWidget::itemChanged, this,
          [=](QListWidgetItem *item) { onMovingTaskTo(item, inprocessTasks); });
  connect(completeTasks, &QListWidget::itemChanged, this,
          [=](QListWidgetItem *item) { onMovingTaskTo(item, completeTasks); });

  connect(
      incompleteTasks, &QListWidget::itemEntered, this,
      [=](QListWidgetItem *item) { onMovingTaskFrom(item, incompleteTasks); });
  connect(
      inprocessTasks, &QListWidget::itemEntered, this,
      [=](QListWidgetItem *item) { onMovingTaskFrom(item, inprocessTasks); });
  connect(
      completeTasks, &QListWidget::itemEntered, this,
      [=](QListWidgetItem *item) { onMovingTaskFrom(item, completeTasks); });

  connect(notStartedProjects, &QListWidget::itemChanged, this,
          [=](QListWidgetItem *item) {
            onMovingProjectTo(item, notStartedProjects);
          });
  connect(
      startedProjects, &QListWidget::itemChanged, this,
      [=](QListWidgetItem *item) { onMovingProjectTo(item, startedProjects); });
  connect(finishlineProjects, &QListWidget::itemChanged, this,
          [=](QListWidgetItem *item) {
            onMovingProjectTo(item, finishlineProjects);
          });
  connect(finishedProjects, &QListWidget::itemChanged, this,
          [=](QListWidgetItem *item) {
            onMovingProjectTo(item, finishedProjects);
          });

  connect(notStartedProjects, &QListWidget::itemEntered, this,
          [=](QListWidgetItem *item) {
            onMovingProjectFrom(item, notStartedProjects);
          });
  connect(startedProjects, &QListWidget::itemEntered, this,
          [=](QListWidgetItem *item) {
            onMovingProjectFrom(item, startedProjects);
          });
  connect(finishlineProjects, &QListWidget::itemEntered, this,
          [=](QListWidgetItem *item) {
            onMovingProjectFrom(item, finishlineProjects);
          });
  connect(finishedProjects, &QListWidget::itemEntered, this,
          [=](QListWidgetItem *item) {
            onMovingProjectFrom(item, finishedProjects);
          });

  connect(closeBtn, &QPushButton::clicked, this, [this]() { close(); });
  connect(minimizeBtn, &QPushButton::clicked, this,
          [this]() { showMinimized(); });
  connect(maximizeBtn, &QPushButton::clicked, this, [this]() {
    this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
    isFullScreen = this->windowState() & Qt::WindowFullScreen;
    if (isFullScreen) {
      maximizeBtn->setStyleSheet(
          "QPushButton {"
          "    border-color: rgba(0, 0, 0, 0);"
          "    background-color: rgba(0, 0, 0, 0);"
          "    background-image: url(':/green.png');"
          "    background-repeat: no-repeat;"
          "}"

          "QPushButton:hover {"
          "    border-color: rgba(0, 0, 0, 0);"
          "    background-image: url(':/greenInHovered.png');"
          "    background-color: rgba(0, 0, 0, 0);"
          "    background-repeat: no-repeat;"
          "}");

    } else {
      maximizeBtn->setStyleSheet(
          "QPushButton {"
          "    border-color: rgba(0, 0, 0, 0);"
          "    background-color: rgba(0, 0, 0, 0);"
          "    background-image: url(':/green.png');"
          "    background-repeat: no-repeat;"
          "}"

          "QPushButton:hover {"
          "    border-color: rgba(0, 0, 0, 0);"
          "    background-image: url(':/greenHovered.png');"
          "    background-color: rgba(0, 0, 0, 0);"
          "    background-repeat: no-repeat;"
          "}");
    }
  });

  create_tasks_connection();
  create_projects_connection();

  loadTasks();
  loadProjects();
  setFontPr1();

  animation->start();

  qDebug() << path;
  qDebug() << "Load time:" << startup.elapsed() << "ms";
}

MainWindow::~MainWindow() {
  globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
  globalSettings->setValue("geometry", saveGeometry());
}

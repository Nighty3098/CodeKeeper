#include "mainwindow.h"

void MainWindow::createConnects()
{
    int font_size_int = globalSettings->value("fontSize").value<int>();

    connect(openSettingsWindowQS, &QShortcut::activated, this, [this]() { openSettingsWindow(); });

    connect(label_1, &ClickableLabel::clicked, [=]() {
        if (this->width() < 1400)
        {
            incompleteTasks->setVisible(!incompleteTasks->isVisible());
            if (incompleteWidget->height() > font_size_int * 2.5)
            {
                incompleteWidget->setMaximumHeight(font_size_int * 2.5);
            }
            else
            {
                incompleteWidget->setMaximumHeight(1000000);
            };
        }
    });
    connect(label_2, &ClickableLabel::clicked, [=]() {
        if (this->width() < 1400)
        {
            inprocessTasks->setVisible(!inprocessTasks->isVisible());
            if (inprocessWidget->height() > font_size_int * 2.5)
            {
                inprocessWidget->setMaximumHeight(font_size_int * 2.5);
            }
            else
            {
                inprocessWidget->setMaximumHeight(1000000);
            };
        }
    });
    connect(label_3, &ClickableLabel::clicked, [=]() {
        if (this->width() < 1400)
        {
            completeTasks->setVisible(!completeTasks->isVisible());
            if (completeWidget->height() > font_size_int * 2.5)
            {
                completeWidget->setMaximumHeight(font_size_int * 2.5);
            }
            else
            {
                completeWidget->setMaximumHeight(1000000);
            };
        }
    });

    connect(toFirstTab, &QShortcut::activated, tabs, [this]() {
        tabs->setCurrentIndex(0);
    });

    connect(toSecondTab, &QShortcut::activated, tabs, [this]() {
        tabs->setCurrentIndex(1);
    });

    connect(toThirdTab, &QShortcut::activated, tabs, [this]() {
        tabs->setCurrentIndex(2);
    });

    connect(toFourthTab, &QShortcut::activated, tabs, [this]() {
        tabs->setCurrentIndex(3);
    });

    connect(mainTabButton, &QPushButton::clicked, [this]() {
        tabs->setCurrentIndex(0);
        windowTitle->setText(" ~ CodeKeeper ~ ");
        setWindowTitle("CodeKeeper");
    });

    connect(tasksTabButton, &QPushButton::clicked, [this]() {
        tabs->setCurrentIndex(2);
        windowTitle->setText(" ~ Tasks ~ ");
        setWindowTitle(tr("Tasks"));
        loadProjectsList(projectsList);
    });

    connect(notesTabButton, &QPushButton::clicked, [this]() {
        tabs->setCurrentIndex(1);
        windowTitle->setText(" ~ Notes ~ ");
        setWindowTitle(tr("Notes"));
    });

    connect(projectsTabButton, &QPushButton::clicked, [this]() {
        tabs->setCurrentIndex(3);
        windowTitle->setText(" ~ Projects ~ ");
        setWindowTitle(tr("Projects"));
    });

    connect(openCommandPalette, &QShortcut::activated, this, [this]() {
        qDebug() << "Opening command palette...";
        commandPalette = new CommandPalette(this);
        commandPalette->show();
    });

    connect(projectsList, &QComboBox::currentTextChanged, this, [this]() { filterTasksByProject(projectsList); });

    connect(hideMenuQS, &QShortcut::activated, this, [this]() { hideMenu(); });

    connect(incompleteTasks, &QListWidget::itemChanged, this,
            [=](QListWidgetItem *item) { onMovingTaskTo(item, incompleteTasks); });
    connect(inprocessTasks, &QListWidget::itemChanged, this,
            [=](QListWidgetItem *item) { onMovingTaskTo(item, inprocessTasks); });
    connect(completeTasks, &QListWidget::itemChanged, this,
            [=](QListWidgetItem *item) { onMovingTaskTo(item, completeTasks); });

    connect(incompleteTasks, &QListWidget::itemEntered, this,
            [=](QListWidgetItem *item) { onMovingTaskFrom(item, incompleteTasks); });
    connect(inprocessTasks, &QListWidget::itemEntered, this,
            [=](QListWidgetItem *item) { onMovingTaskFrom(item, inprocessTasks); });
    connect(completeTasks, &QListWidget::itemEntered, this,
            [=](QListWidgetItem *item) { onMovingTaskFrom(item, completeTasks); });

    connect(notStartedProjects, &QListWidget::itemChanged, this,
            [=](QListWidgetItem *item) { onMovingProjectTo(item, notStartedProjects); });
    connect(startedProjects, &QListWidget::itemChanged, this,
            [=](QListWidgetItem *item) { onMovingProjectTo(item, startedProjects); });
    connect(finishlineProjects, &QListWidget::itemChanged, this,
            [=](QListWidgetItem *item) { onMovingProjectTo(item, finishlineProjects); });
    connect(finishedProjects, &QListWidget::itemChanged, this,
            [=](QListWidgetItem *item) { onMovingProjectTo(item, finishedProjects); });

    connect(notStartedProjects, &QListWidget::itemEntered, this,
            [=](QListWidgetItem *item) { onMovingProjectFrom(item, notStartedProjects); });
    connect(startedProjects, &QListWidget::itemEntered, this,
            [=](QListWidgetItem *item) { onMovingProjectFrom(item, startedProjects); });
    connect(finishlineProjects, &QListWidget::itemEntered, this,
            [=](QListWidgetItem *item) { onMovingProjectFrom(item, finishlineProjects); });
    connect(finishedProjects, &QListWidget::itemEntered, this,
            [=](QListWidgetItem *item) { onMovingProjectFrom(item, finishedProjects); });

    connect(incompleteTasks, &QListWidget::customContextMenuRequested, this,
            [this](const QPoint &pos) { activateTasksContextMenu(pos, incompleteTasks); });
    connect(inprocessTasks, &QListWidget::customContextMenuRequested, this,
            [this](const QPoint &pos) { activateTasksContextMenu(pos, inprocessTasks); });
    connect(completeTasks, &QListWidget::customContextMenuRequested, this,
            [this](const QPoint &pos) { activateTasksContextMenu(pos, completeTasks); });

    connect(notStartedProjects, &QListWidget::customContextMenuRequested, this,
            [this](const QPoint &pos) { activateProjectContextMenu(pos, notStartedProjects); });

    connect(startedProjects, &QListWidget::customContextMenuRequested, this,
            [this](const QPoint &pos) { activateProjectContextMenu(pos, startedProjects); });

    connect(finishlineProjects, &QListWidget::customContextMenuRequested, this,
            [this](const QPoint &pos) { activateProjectContextMenu(pos, finishlineProjects); });

    connect(finishedProjects, &QListWidget::customContextMenuRequested, this,
            [this](const QPoint &pos) { activateProjectContextMenu(pos, finishedProjects); });

    connect(closeBtn, &QPushButton::clicked, this, [this]() { close(); });
    connect(minimizeBtn, &QPushButton::clicked, this, [this]() { showMinimized(); });
    connect(maximizeBtn, &QPushButton::clicked, this, [this]() {
        this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
        isFullScreen = this->windowState() & Qt::WindowFullScreen;
        if (isFullScreen)
        {
            maximizeBtn->setStyleSheet("QPushButton {"
                                       "    border-radius: 6px;"
                                       "    border-color: rgba(0, 0, 0, 0);"
                                       "    background-color: #9bbf60;"
                                       "    background-repeat: no-repeat;"
                                       "    background-attachment: fixed;"
                                       "}"

                                       "QPushButton:hover {"
                                       "    border-radius: 6px;"
                                       "    border-color: rgba(0, 0, 0, 0);"
                                       "    background-color: #9bbf60;"
                                       "    background-repeat: no-repeat;"
                                       "    background-attachment: fixed;"
                                       "}");
        }
        else
        {
            maximizeBtn->setStyleSheet("QPushButton {"
                                       "    border-radius: 6px;"
                                       "    border-color: rgba(0, 0, 0, 0);"
                                       "    background-color: #a9bf85;"
                                       "    background-repeat: no-repeat;"
                                       "    background-attachment: fixed;"
                                       "}"

                                       "QPushButton:hover {"
                                       "    border-radius: 6px;"
                                       "    border-color: rgba(0, 0, 0, 0);"
                                       "    background-color: #9bbf60;"
                                       "    background-repeat: no-repeat;"
                                       "    background-attachment: fixed;"
                                       "}");
        }
    });

    connect(tabs, &QTabWidget::currentChanged, this,
            [=]() { updateTasksProgress(tabs, incompleteTasks, inprocessTasks, completeTasks, tasksProgress); });

    connect(tabs, &QTabWidget::currentChanged, this,
            [=]() { getTotalTasks(tabs, incompleteTasks, inprocessTasks, completeTasks); });

    connect(tabs, &QTabWidget::currentChanged, this, [=]() {
        getTotalProjects(tabs, notStartedProjects, startedProjects, finishedProjects, finishlineProjects);
    });

    connect(openSettingsBtn, &QPushButton::clicked, this, &MainWindow::openSettingsWindow);
    connect(openAccountWindow, &QPushButton::clicked, this, &MainWindow::fOpenAccountWindow);
    connect(syncDataBtn, &QPushButton::clicked, this, &MainWindow::openSyncWindow);

    // fix
    connect(notStartedProjects, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);
    connect(startedProjects, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);
    connect(finishlineProjects, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);
    connect(finishedProjects, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);

    connect(incompleteTasks, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);
    connect(inprocessTasks, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);
    connect(completeTasks, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);

    connect(notStartedProjects, &QListWidget::itemPressed, this, &MainWindow::on_listWidget_itemClicked);
    connect(startedProjects, &QListWidget::itemPressed, this, &MainWindow::on_listWidget_itemClicked);
    connect(finishlineProjects, &QListWidget::itemPressed, this, &MainWindow::on_listWidget_itemClicked);
    connect(finishedProjects, &QListWidget::itemPressed, this, &MainWindow::on_listWidget_itemClicked);

    connect(incompleteTasks, &QListWidget::itemPressed, this, &MainWindow::on_listWidget_itemClicked);
    connect(inprocessTasks, &QListWidget::itemPressed, this, &MainWindow::on_listWidget_itemClicked);
    connect(completeTasks, &QListWidget::itemPressed, this, &MainWindow::on_listWidget_itemClicked);

    connect(completeTasks, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item) { editTask(); });

    connect(incompleteTasks, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item) { editTask(); });

    connect(inprocessTasks, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item) { editTask(); });

    connect(notStartedProjects, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item) { openProject(); });
    connect(startedProjects, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item) { openProject(); });
    connect(finishlineProjects, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item) { openProject(); });
    connect(finishedProjects, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item) { openProject(); });

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
    connect(setQuoteB, &QPushButton::clicked, this, &MainWindow::setQuote);

    connect(notesList, &QTreeView::doubleClicked, this, &MainWindow::onNoteDoubleClicked);

    connect(noteEdit, &QMarkdownTextEdit::textChanged, this, &MainWindow::saveNote);

    connect(notesList, &QTreeView::clicked, this, [=](const QModelIndex &index) {
        if (index.isValid())
        {
            QDateTime lastModified = notesDirModel->data(index, Qt::UserRole + 1).toDateTime();
            if (lastModified.isValid())
            {
                QString toolTip = "Last modified: " + lastModified.toString();
                notesList->setToolTip(toolTip);
                qDebug() << toolTip;
            }
        }
    });

    connect(notesList, &QListWidget::customContextMenuRequested, this,
            [this](const QPoint &pos) { activateNotesContextMenu(pos, notesList); });
}

void MainWindow::createShortcuts()
{
    toFirstTab = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_1), this);
    toSecondTab = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_2), this);
    toThirdTab = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_3), this);
    toFourthTab = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_4), this);

    openCommandPalette = new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_P), this);

    openSettingsWindowQS = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_P), this);

    hideMenuQS = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_M), this);
}

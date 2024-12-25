#include "mainwindow.h"

void MainWindow::createTrayMenu(QMenu *menu, QString font_size)
{
    closeAppA = menu->addAction(
        changeIconColor(QPixmap(":/quit.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Exit"), this, [=]() { this->close(); });
    closeAppA = menu->addAction(
        changeIconColor(QPixmap(":/task.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Open tasks"), this, [=]() {
            tabs->setCurrentIndex(2);
            windowTitle->setText(" ~ Tasks ~ ");
            setWindowTitle(tr("Tasks"));
        });
    closeAppA = menu->addAction(
        changeIconColor(QPixmap(":/project.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Open projects"), this, [=]() {
            tabs->setCurrentIndex(3);
            windowTitle->setText(" ~ Projects ~ ");
            setWindowTitle(tr("Projects"));
        });
    closeAppA = menu->addAction(
        changeIconColor(QPixmap(":/document.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Open notes"), this, [=]() {
            tabs->setCurrentIndex(1);
            windowTitle->setText(" ~ Notes ~ ");
            setWindowTitle(tr("Notes"));
        });
}

void MainWindow::createNotesMenu(QMenu *menu, QString font_size)
{
    newNote = menu->addAction(
        changeIconColor(QPixmap(":/new.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("New Note"), this, SLOT(createNote()), QKeySequence(Qt::CTRL + Qt::Key_N));
    rmNote = menu->addAction(
        changeIconColor(QPixmap(":/delete.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Remove"), this, SLOT(removeNote()), QKeySequence(Qt::CTRL + Qt::Key_Delete));
    newFolder = menu->addAction(
        changeIconColor(QPixmap(":/new_folder.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("New folder"), this, SLOT(createFolder()), QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N));
    renameItemA = menu->addAction(
        changeIconColor(QPixmap(":/rename.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Rename"), this, SLOT(renameItem()), QKeySequence(Qt::Key_F2));

    menu->addSeparator();

    expandAllA = menu->addAction(
        changeIconColor(QPixmap(":/expand.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Expand on one stage"), [this]() { notesList->expandAll(); }, QKeySequence(Qt::CTRL + Qt::Key_E));

    menu->addSeparator();

    QMenu *editMenu = new QMenu(tr("Edit"), menu);
    editMenu->setIcon(
        changeIconColor(QPixmap(":/edit.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setH1A = editMenu->addAction(
        changeIconColor(QPixmap(":/h1.png"))
            .scaled(font_size.toInt() + 5, font_size.toInt() + 5, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set H1"), this, SLOT(setH1()));
    setH2A = editMenu->addAction(
        changeIconColor(QPixmap(":/h2.png"))
            .scaled(font_size.toInt() + 5, font_size.toInt() + 5, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set H2"), this, SLOT(setH2()));
    setH3A = editMenu->addAction(
        changeIconColor(QPixmap(":/h3.png"))
            .scaled(font_size.toInt() + 5, font_size.toInt() + 5, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set H3"), this, SLOT(setH3()));
    editMenu->addSeparator();
    setQuoteA = editMenu->addAction(
        changeIconColor(QPixmap(":/quote.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add quote"), this, SLOT(setQuote()));
    setListA = editMenu->addAction(
        changeIconColor(QPixmap(":/list.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add list item"), this, SLOT(setList()));
    setNumListA = editMenu->addAction(
        changeIconColor(QPixmap(":/numList.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add numbered list"), this, SLOT(setNumList()));
    setLinkA = editMenu->addAction(
        changeIconColor(QPixmap(":/link.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add link"), this, SLOT(setLink()));
    setTaskA = editMenu->addAction(
        changeIconColor(QPixmap(":/checkbox.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add task"), this, SLOT(setTask()));
    editMenu->addSeparator();
    setBoldA = editMenu->addAction(
        changeIconColor(QPixmap(":/bold.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set bold"), this, SLOT(setBold()));
    setItalicA = editMenu->addAction(
        changeIconColor(QPixmap(":/italic.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set italic"), this, SLOT(setItalic()));
    setStrikeA = editMenu->addAction(
        changeIconColor(QPixmap(":/strikethrough.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set strikethrough"), this, SLOT(setStrike()));
    setTableA = editMenu->addAction(
        changeIconColor(QPixmap(":/table.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add table"), this, SLOT(setTable()));

    QMenu *sortMenu = new QMenu(tr("Sort by"), menu);
    sortMenu->setIcon(
        changeIconColor(QPixmap(":/sorting.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    nameAction = sortMenu->addAction(tr("Name"), this, SLOT(setSortByName()));
    dateAction = sortMenu->addAction(tr("Date"), this, SLOT(setSortByTime()));

    menu->addMenu(editMenu);
    menu->addMenu(sortMenu);
}

void MainWindow::createNotesContextMenu(QMenu *menu, QString font_size)
{
    mRenameNoteA = menu->addAction(
        changeIconColor(QPixmap(":/edit.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Rename"), this, SLOT(renameItem()));

    mDeleteItemA = menu->addAction(
        changeIconColor(QPixmap(":/delete.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Remove"), this, SLOT(removeNote()), QKeySequence(Qt::Key_Delete));
}

void MainWindow::createProjectMenu(QMenu *menu, QString font_size)
{
    newProject = menu->addAction(
        changeIconColor(QPixmap(":/new.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("New"), this, SLOT(createProject()), QKeySequence(Qt::CTRL + Qt::Key_N));
    rmProject = menu->addAction(
        changeIconColor(QPixmap(":/delete.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Remove"), this, SLOT(removeProject()), QKeySequence(Qt::Key_Delete));

    menu->addSeparator();

    editProject = menu->addAction(
        changeIconColor(QPixmap(":/open.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Open"), this, SLOT(openProject()));
    openProjectInGit = menu->addAction(
        changeIconColor(QPixmap(":/open.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Open in git"), this, SLOT(openGitProject()));
}

void MainWindow::createTaskMenu(QMenu *menu, QString font_size)
{
    addTaskA = menu->addAction(
        changeIconColor(QPixmap(":/new.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add task"), this, SLOT(addNewTask()), QKeySequence(Qt::Key_Return));
    rmTaskA = menu->addAction(
        changeIconColor(QPixmap(":/delete.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Delete task"), this, SLOT(removeTask()), QKeySequence(Qt::Key_Delete));
    editTaskA = menu->addAction(
        changeIconColor(QPixmap(":/edit.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Edit task"), this, SLOT(editTask()));
}

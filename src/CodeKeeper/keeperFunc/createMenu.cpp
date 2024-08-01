#include "mainwindow.h"

void MainWindow::createNotesMenu(QMenu *menu, QString font_size)
{
    newNote = menu->addAction(
        QPixmap(":/new.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("New Note"), this, SLOT(createNote()), Qt::CTRL + Qt::Key_N);
    rmNote = menu->addAction(
        QPixmap(":/delete.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Remove"), this, SLOT(removeNote()), Qt::CTRL + Qt::Key_Delete);
    newFolder = menu->addAction(
        QPixmap(":/new_folder.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("New folder"), this, SLOT(createFolder()), Qt::CTRL + Qt::SHIFT + Qt::Key_N);
    renameItemA = menu->addAction(
        QPixmap(":/rename.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Rename"), this, SLOT(renameItem()), Qt::Key_F2);

    menu->addSeparator();

    expandAllA = menu->addAction(
        QPixmap(":/expand.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Expand on one stage"), [this]() { notesList->expandAll(); }, Qt::CTRL + Qt::Key_E);

    menu->addSeparator();

    QMenu *viewMenu = new QMenu(tr("View"), menu);

    viewMenu->setIcon(
        QPixmap(":/view.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    showList =
        viewMenu->addAction(tr("Show notes list"), this, SLOT(hideNotesList()), Qt::CTRL + Qt::SHIFT + Qt::Key_L);
    showList->setCheckable(true);
    showList->setChecked(isVisibleNotesList);
    showRender =
        viewMenu->addAction(tr("Show md preview"), this, SLOT(showPreview()), Qt::CTRL + Qt::SHIFT + Qt::Key_P);
    showRender->setCheckable(true);
    showRender->setChecked(isVisiblePreview);
    viewMenu->addSeparator();
    viewMode = viewMenu->addAction(
        QPixmap(":/view.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Reading mode"), this, SLOT(toViewMode()), Qt::CTRL + Qt::SHIFT + Qt::Key_V);
    viewMode->setCheckable(true);
    viewMode->setChecked(isViewMode);

    QMenu *editMenu = new QMenu(tr("Edit"), menu);
    editMenu->setIcon(
        QPixmap(":/edit.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setH1A = editMenu->addAction(
        QPixmap(":/h1.png")
            .scaled(font_size.toInt() + 5, font_size.toInt() + 5, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set H1"), this, SLOT(setH1()));
    setH2A = editMenu->addAction(
        QPixmap(":/h2.png")
            .scaled(font_size.toInt() + 5, font_size.toInt() + 5, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set H2"), this, SLOT(setH2()));
    setH3A = editMenu->addAction(
        QPixmap(":/h3.png")
            .scaled(font_size.toInt() + 5, font_size.toInt() + 5, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set H3"), this, SLOT(setH3()));
    editMenu->addSeparator();
    setQuoteA = editMenu->addAction(
        QPixmap(":/quote.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add quote"), this, SLOT(setQuote()));
    setListA = editMenu->addAction(
        QPixmap(":/list.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add list item"), this, SLOT(setList()));
    setNumListA = editMenu->addAction(
        QPixmap(":/numList.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add numbered list"), this, SLOT(setNumList()));
    setLinkA = editMenu->addAction(
        QPixmap(":/link.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add link"), this, SLOT(setLink()));
    setTaskA = editMenu->addAction(
        QPixmap(":/checkbox.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add task"), this, SLOT(setTask()));
    editMenu->addSeparator();
    setBoldA = editMenu->addAction(
        QPixmap(":/bold.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set bold"), this, SLOT(setBold()));
    setItalicA = editMenu->addAction(
        QPixmap(":/italic.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set italic"), this, SLOT(setItalic()));
    setStrikeA = editMenu->addAction(
        QPixmap(":/strikethrough.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Set strikethrough"), this, SLOT(setStrike()));
    setTableA = editMenu->addAction(
        QPixmap(":/table.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add table"), this, SLOT(setTable()));

    QMenu *sortMenu = new QMenu(tr("Sort by"), menu);
    sortMenu->setIcon(
        QPixmap(":/sorting.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    nameAction = sortMenu->addAction(tr("Name"), this, SLOT(setSortByName()));
    dateAction = sortMenu->addAction(tr("Date"), this, SLOT(setSortByTime()));

    QMenu *exportMenu = new QMenu(tr("Export as"), menu);
    exportMenu->setIcon(
        QPixmap(":/export.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    exportToHtml = exportMenu->addAction("HTML", this, SLOT(exportNoteToHtml()));
    exportToPdf = exportMenu->addAction("Pdf", this, SLOT(exportNoteToPdf()));

    menu->addMenu(editMenu);
    menu->addMenu(viewMenu);
    menu->addMenu(sortMenu);
    menu->addMenu(exportMenu);
}

void MainWindow::createProjectMenu(QMenu *menu, QString font_size)
{
    newProject = menu->addAction(
        QPixmap(":/new.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("New"), this, SLOT(createProject()), Qt::CTRL + Qt::Key_N);
    rmProject = menu->addAction(
        QPixmap(":/delete.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Remove"), this, SLOT(removeProject()), Qt::Key_Delete);
    
    menu->addSeparator();
    
    editProject = menu->addAction(
        QPixmap(":/edit.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Edit"), this, SLOT(openProject()));
    openProjectInGit = menu->addAction(
        QPixmap(":/open.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Open in git"), this, SLOT(openGitProject()));
}

void MainWindow::createTaskMenu(QMenu *menu, QString font_size)
{
    addTask = menu->addAction(
        QPixmap(":/new.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Add task"), this, SLOT(addNewTask()), Qt::Key_Return);
    rmTask = menu->addAction(
        QPixmap(":/delete.png")
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        tr("Delete task"), this, SLOT(removeTask()), Qt::Key_Delete);
}

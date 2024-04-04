#include <QDateTime>
#include <QSyntaxHighlighter>

void MainWindow::openSettingsWindow() {
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(10);
    this->setGraphicsEffect(blurEffect);

    QRect geo = this->geometry();
    int x = geo.x();
    int y = geo.y();
    int width = geo.width();
    int height = geo.height();

    settingsWindow = new SettingsWindow(this);

    QRect geo2 = settingsWindow->geometry();

    int width2 = geo2.width();
    int height2 = geo2.height();

    int new_x = x + (width - width2) / 2;
    int new_y = y + (height - height2) / 2;

    settingsWindow->show();

    settingsWindow->move(new_x, new_y);
}

void MainWindow::addNewTask() {
    QString text = taskText->text();
    if (!text.isEmpty()) {
        taskText->clear();
        incompleteTasks->addItem(text);
    } else {
        qDebug() << "Task is empty";
    }
}

void MainWindow::removeTask() {
    QListWidget *listWidgets[] = {incompleteTasks, inprocessTasks,
                                  completeTasks};

    for (QListWidget *listWidget : listWidgets) {
        QListWidgetItem *item = listWidget->currentItem();
        if (item) {
            listWidget->takeItem(listWidget->row(item));
            delete item;
            break;
        }
    }
}

void MainWindow::hideNotesList() {
    notesList->setVisible(!notesList->isVisible());
    globalSettings->setValue("isVisibleNotesList", notesList->isVisible());
}

void MainWindow::showPreview() {
    mdPreview->setVisible(!mdPreview->isVisible());
    globalSettings->setValue("isVisiblePreview", mdPreview->isVisible());

    connect(noteEdit, &QMarkdownTextEdit::textChanged, this,
            &MainWindow::updateMDPreview);
}

void MainWindow::updateMDPreview() {
    QString text = noteEdit->toPlainText();

    mdPreview->setMarkdown(text);
}

QString getCurrentDateTimeString() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTimeString = currentDateTime.toString("dd-MM-yyyy hh:mm:ss");
    return dateTimeString;
}

void MainWindow::setHeader() {
    QString text = noteEdit->toPlainText();

    QStringList lines = text.split("\n");
    QString sourceName = lines.first();

    QString noteName = sourceName.mid(0, 40) + "...";

    noteNameLabel->setText(noteName);
}

void MainWindow::openFolder() {
    QString str = QFileDialog::getExistingDirectory(0, "Select a directory");
    if (!str.isEmpty()) {
        globalSettings->setValue("path", str);
        qDebug() << str;
    }
}

void MainWindow::createProject() {
    QString newProjectTeamplate =
        "New project\nGitHub\n" + getCurrentDateTimeString();
    notStartedProjects->addItem(newProjectTeamplate);
}

void MainWindow::removeProject() {
    QListWidget *listWidgets[] = {notStartedProjects, startedProjects,
                                  finishlineProjects, finishedProjects};

    for (QListWidget *listWidget : listWidgets) {
        QListWidgetItem *item = listWidget->currentItem();
        if (item) {
            listWidget->takeItem(listWidget->row(item));
            delete item;
            break;
        }
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item) {
    QListWidget *lists[] = {notStartedProjects, startedProjects,
                            finishlineProjects, finishedProjects,
                            incompleteTasks,    inprocessTasks,
                            completeTasks};

    for (QListWidget *list : lists) {
        QListWidgetItem *selectedItem = list->currentItem();
        if (selectedItem && selectedItem != item) {
            list->setCurrentItem(nullptr);
        }
    }
}

void MainWindow::loadNotes(const QDir &dir) {
    QApplication::processEvents();
    QString pattern = "*.md";

}

void MainWindow::loadTasks() {}

void MainWindow::loadProjects() {}

void MainWindow::setFontPr1() {
    mainTitle->setFont(selectedFont);

    projectsMainLabel->setFont(selectedFont);
    projectsMainLabel->setStyleSheet("font-size: " + font_size +
                                     "pt; color: #8ebecf;");

    openSettingsBtn->setFont(selectedFont);
    openSettingsBtn->setStyleSheet("font-size: " + font_size + "pt;");

    syncDataBtn->setFont(selectedFont);
    syncDataBtn->setStyleSheet("font-size: " + font_size + "pt;");

    openFolderBtn->setFont(selectedFont);
    openFolderBtn->setStyleSheet("font-size: " + font_size + "pt;");

    notesList->setFont(selectedFont);
    notesList->setStyleSheet("font-size: " + font_size + "pt;");

    menuButton->setFont(selectedFont);
    menuButton->setStyleSheet("font-size: " + font_size + "pt;");

    noteName->setFont(selectedFont);
    noteName->setStyleSheet("font-size: " + font_size + "pt; color: #8ebecf;");

    mdPreview->setFont(selectedFont);
    mdPreview->setStyleSheet("font-size: " + font_size + "pt;");

    noteEdit->setFont(selectedFont);
    noteEdit->setStyleSheet("font-size: " + font_size + "pt;");

    timeLabel->setFont(selectedFont);
    timeLabel->setStyleSheet("font-size: " + font_size + "pt; color: #8ebecf;");

    noteNameLabel->setFont(selectedFont);
    noteNameLabel->setStyleSheet("font-size: " + font_size +
                                 "pt; color: #8ebecf;");

    incompleteTasks->setStyleSheet(
        "background-color: rgba(255, 117, 127, 180); color: #000000; "
        "border-width: 0px; border-color: rgb(255, 117, 127); "
        "font-size: " +
        font_size + "pt;");

    inprocessTasks->setStyleSheet(
        "background-color: rgba(255, 199, 119, 180); "
        "color: #000000; text-decoration: underline; "
        "border-width: 0px; "
        "font-size: " +
        font_size +
        "pt;"
        "border-color: rgb(255, 199, 119);");

    completeTasks->setStyleSheet(
        "background-color: rgba(195, 232, 141, 180); "
        "color: #000000; text-decoration: "
        "line-through; border-width: 0px; "
        "font-size: " +
        font_size +
        "pt;"
        "border-color: rgb(195, 232, 141);");

    taskText->setFont(selectedFont);
    taskText->setStyleSheet("font-size: " + font_size + "pt;");

    addTask->setFont(selectedFont);
    addTask->setStyleSheet("font-size: " + font_size + "pt;");

    rmTask->setFont(selectedFont);
    rmTask->setStyleSheet("font-size: " + font_size + "pt;");

    notStartedProjects->setStyleSheet(
        "background-color: rgba(255, 117, 127, "
        "180); color: #000000; border-width: 0px; "
        "border-color: #ff757f; "
        "font-size: " +
        font_size + "pt;");

    nsProjects->setFont(selectedFont);

    sProjects->setFont(selectedFont);

    startedProjects->setStyleSheet(
        "background-color: rgba(255, 199, 119, 180); color: #000000; "
        "border-width: 0px; border-color: #ffc777; "
        "font-size: " +
        font_size + "pt;");

    flProjects->setFont(selectedFont);

    finishlineProjects->setStyleSheet(
        "background-color: rgba(130, 170, 255, "
        "180); color: #000000; border-width: 0px; "
        "border-color: #82aaff; "
        "font-size: " +
        font_size + "pt;");

    fProjects->setFont(selectedFont);

    finishedProjects->setStyleSheet(
        "background-color: rgba(195, 232, 141, 180); color: #000000; "
        "border-width: 0px; border-color: #c3e88d; "
        "font-size: " +
        font_size + "pt;");

    projectsMainLabel->setFont(selectedFont);
    notStartedProjects->setFont(selectedFont);
    startedProjects->setFont(selectedFont);
    finishlineProjects->setFont(selectedFont);
    finishedProjects->setFont(selectedFont);

    projectsMenuButton->setFont(selectedFont);

    projectsMenu->setFont(selectedFont);

    tabs->setFont(selectedFont);
    tabs->setStyleSheet("font-size: " + font_size + "pt;");

    incompleteTasks->setFont(selectedFont);
    inprocessTasks->setFont(selectedFont);
    completeTasks->setFont(selectedFont);

    label_1->setFont(selectedFont);
    label_2->setFont(selectedFont);
    label_3->setFont(selectedFont);
}

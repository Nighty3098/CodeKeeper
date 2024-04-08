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
}

void MainWindow::showFolders() {
    // foldersList->setVisible(!foldersList->isVisible());
    // globalSettings->setValue("isVisibleFoldersList", foldersList->isVisible());
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
        "New project\nGitHub\nDocumentation: \n" + getCurrentDateTimeString();
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


void MainWindow::displayDirectoryStructure(const QDir &dir, QTreeWidget *tree) {
    QTreeWidgetItem *rootItem = new QTreeWidgetItem(tree);
    rootItem->setText(0, dir.absolutePath());
    rootItem->setIcon(0, QIcon(":/folder.png"));
    tree->addTopLevelItem(rootItem);

    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    QFileInfo fileInfo;
    QTreeWidgetItem *childItem;

    foreach (fileInfo, fileInfoList) {
        if (fileInfo.isDir()) {
            childItem = new QTreeWidgetItem(rootItem);
            childItem->setText(0, fileInfo.fileName());
            childItem->setIcon(0, QIcon(":/folder.png"));
            displayDirectoryStructure(fileInfo.filePath(), tree);
        } else {
            childItem = new QTreeWidgetItem(rootItem);
            childItem->setText(0, fileInfo.fileName());
            childItem->setIcon(0, QIcon(":/note.png"));
        }
    }
}


void MainWindow::renameItemOnDoubleClick(QListWidget *listWidget, QListWidgetItem *item) {
    if (item) {
        QDialog dialog(this);
        dialog.setWindowTitle(tr("Rename item"));
        dialog.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

        QVBoxLayout layout(&dialog);
        QLineEdit lineEdit(&dialog);
        layout.addWidget(&lineEdit);

        QPushButton okButton(tr("OK"), &dialog);
        QPushButton cancelButton(tr("Cancel"), &dialog);
        layout.addWidget(&okButton);
        layout.addWidget(&cancelButton);

        QObject::connect(&okButton, &QPushButton::clicked, [&]() {
            QString newName = lineEdit.text();
            if (!newName.isEmpty()) {
                item->setText(newName);
            }
            dialog.close();
        });

        QObject::connect(&cancelButton, &QPushButton::clicked, [&]() {
            dialog.close();
        });

        dialog.exec();
    }
}


void MainWindow::updateTasksProgress(QTabWidget *tasksTab, QListWidget *incompleteTasks, QListWidget *inprocessTasks, QListWidget *completeTasks, QProgressBar *tasksProgress) {
    if (tasksTab->currentIndex() == 2) {
        qDebug() << tasksTab->currentIndex();
        QTimer *timer2 = new QTimer(this);
        connect(timer2, &QTimer::timeout, [=]() {
            int totalTasks = incompleteTasks->count() + inprocessTasks->count() + completeTasks->count();
            int completedTasks = completeTasks->count();

            if (totalTasks == 0) {
                tasksProgress->setValue(0);
            } else {
                double percentage = static_cast<double>(completedTasks) / static_cast<double>(totalTasks) * 100.0;
                tasksProgress->setValue(percentage);
            }
        });
        timer2->start(500);
    }
    else {
        qDebug() << tasksTab->currentIndex();
    }
}

void MainWindow::loadTasks() {}

void MainWindow::loadProjects() {}

void MainWindow::createFolder() {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "Folder");
    item->setIcon(0, QIcon(":/folder.png"));
    notesList->addTopLevelItem(item);
/*
    QListWidgetItem *item = new QListWidgetItem();
    item->setText("Folder");
    item->setIcon(QIcon(":/folder.png"));
    foldersList->addItem(item);
*/
}

void MainWindow::createNote() {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "New Note");
    item->setIcon(0, QIcon(":/note.png"));
    notesList->addTopLevelItem(item);

    /*
    QListWidgetItem *item = new QListWidgetItem();
    item->setText("New Note");
    item->setIcon(QIcon(":/note.png"));
    notesList->addItem(item);
    */
}

void MainWindow::removeFolder() {
    QTreeWidgetItem *currentItem = notesList->currentItem();

    delete currentItem;
}

void MainWindow::removeNote() {
    QTreeWidgetItem *currentItem = notesList->currentItem();

    delete currentItem;
}

void MainWindow::openProject(QListWidget *listWidget, QListWidgetItem *item) {
    if (item) {
        QDialog dialog(this);
        dialog.setWindowTitle(tr("Edit project"));
        dialog.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

        QGridLayout layout(&dialog);

        QMarkdownTextEdit markdownTextEdit(&dialog);
        QTextBrowser mdPreview(&dialog);

        mdPreview.setOpenLinks(true);
        mdPreview.setOpenExternalLinks(true);

        markdownTextEdit.setFont(selectedFont);
        markdownTextEdit.setStyleSheet("font-size: " + font_size + "pt;");

        QComboBox selectDocumentation(&dialog);
        selectDocumentation.setStyleSheet("font-size: " + font_size + "pt;");

        QPushButton openButton(tr("Open"), &dialog);
        openButton.setFont(selectedFont);
        openButton.setStyleSheet("font-size: " + font_size + "pt;");

        QPushButton saveButton(tr("Save"), &dialog);
        QPushButton closeButton(tr("Cancel"), &dialog);

        saveButton.setFont(selectedFont);
        saveButton.setStyleSheet("font-size: " + font_size + "pt;");

        closeButton.setFont(selectedFont);
        closeButton.setStyleSheet("font-size: " + font_size + "pt;");

        layout.addWidget(&markdownTextEdit, 0, 0);
        layout.addWidget(&mdPreview, 0, 1);
        layout.addWidget(&selectDocumentation, 1, 0);
        layout.addWidget(&saveButton, 1, 1);
        layout.addWidget(&openButton, 2, 0);
        layout.addWidget(&closeButton, 2, 1);

        markdownTextEdit.setPlainText(formatText(item->text()));

        QString text = markdownTextEdit.toPlainText();
        mdPreview.setMarkdown(text);

        loadDocumentations(path, selectDocumentation);

        QObject::connect(&markdownTextEdit, &QMarkdownTextEdit::textChanged, [&]() {
            QString text = markdownTextEdit.toPlainText();
            mdPreview.setMarkdown(text);
        });


        QObject::connect(&saveButton, &QPushButton::clicked, [&]() {
            item->setText(unformatText(markdownTextEdit.toPlainText()));
            dialog.close();
        });

        QObject::connect(&closeButton, &QPushButton::clicked, [&]() {
            dialog.close();
        });

        dialog.exec();
    }
}

void MainWindow::loadDocumentations(QDir path, QComboBox &comboBox) {
    QFileInfoList fileInfoList = path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    foreach (const QFileInfo &fileInfo, fileInfoList) {
        if (fileInfo.suffix() == "md") {
            comboBox.addItem(fileInfo.baseName());
        }
    }

    QDir subdir;
    QFileInfoList subdirList = path.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    foreach (const QFileInfo &subdirInfo, subdirList) {
        subdir.setPath(subdirInfo.filePath());
        if (subdir.exists()) {
            loadDocumentations(subdir, comboBox);
        }
    }
}

QString MainWindow::formatText(const QString &text) {
    QStringList lines = text.split('\n');

    if (lines.length() < 4) {
        return text;
    }

    lines[0] = QString("# %1 \n\n").arg(lines[0]);
    lines[1] = QString("[Source](%1) \n\n ").arg(lines[1]);
    lines[2] = QString("%1 \n\n ").arg(lines[2]);
    lines[3] = QString("Latest modification: %1 \n\n ").arg(lines[3]);

    return lines.join("");
}

QString MainWindow::unformatText(const QString &text) {
    QStringList lines = text.split('\n');
    lines.replaceInStrings(QRegExp("^# "), "");
    lines.replaceInStrings(QRegExp("!\\[Source\\]\\(\\n"), "");
    lines.replaceInStrings(QRegExp("Latest modification: \\n"), "");
    lines.replaceInStrings(QRegExp("\\n$"), "");

    lines[0] = QString("%1").arg(lines[0]);
    lines[1] = QString("%1").arg(lines[1]);
    lines[2] = QString("%1").arg(lines[2]);
    lines[3] = QString("%1").arg(lines[3]);

    return lines.join("\n");
}




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
    notesList->setStyleSheet("font-size: " + font_size +
                             "pt; background-color: rgba(47, 51, 77, 0);");

    // foldersList->setFont(selectedFont);
    // foldersList->setStyleSheet("font-size: " + font_size +
    //                             "pt; background-color: rgba(47, 51, 77, 50);");

    menuButton->setFont(selectedFont);
    menuButton->setStyleSheet("font-size: " + font_size + "pt;");

    tasksMenuBtn->setFont(selectedFont);
    tasksMenuBtn->setStyleSheet("font-size: " + font_size + "pt;");

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

    taskText->setFont(selectedFont);
    taskText->setStyleSheet("font-size: " + font_size + "pt;");

    incompleteTasks->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: 0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(255, 117, 127, 160); color: #000000; "
        "border-width: 0px; border-color: rgba(255, 117, 127); "
        "border-radius: 5px;"
        "font-size: " +
        font_size +
        "pt;"
        "}");

    inprocessTasks->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: 0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(255, 199, 119, 160); "
        "color: #000000; text-decoration: underline; "
        "border-width: 0px; "
        "border-radius: 5px;"
        "font-size: " +
        font_size +
        "pt;"
        "}");

    completeTasks->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: 0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(195, 232, 141, 160); "
        "color: #000000;"
        "border-radius: 5px;"
        "line-through; border-width: 0px; "
        "font-size: " +
        font_size +
        "pt;"
        "}");

    notStartedProjects->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: 0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(255, 117, 127, 160);"
        "color: #000000; border-width: 0px; "
        "border-radius: 5px;"
        "border-color: #ff757f; "
        "font-size: " +
        font_size +
        "pt;"
        "}");

    startedProjects->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: 0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(255, 199, 119, 160); color: #000000; "
        "border-radius: 5px;"
        "border-width: 0px; border-color: #ffc777; "
        "font-size: " +
        font_size +
        "pt;"
        "}");

    finishlineProjects->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: 0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(130, 170, 255, "
        "160); color: #000000; border-width: 0px; "
        "border-radius: 5px;"
        "border-color: #82aaff; "
        "font-size: " +
        font_size +
        "pt;"
        "}");

    finishedProjects->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: 0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(195, 232, 141, 160); color: #000000; "
        "border-radius: 5px;"
        "border-width: 0px; border-color: #c3e88d; "
        "font-size: " +
        font_size +
        "pt;"
        "}");

    fProjects->setFont(selectedFont);
    flProjects->setFont(selectedFont);
    nsProjects->setFont(selectedFont);
    sProjects->setFont(selectedFont);

    nsProjects->setStyleSheet("font-size: 16px;");
    sProjects->setStyleSheet("font-size: 16px;");
    flProjects->setStyleSheet("font-size: 16px;");
    fProjects->setStyleSheet("font-size: 16px;");

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

    tasksMenuBtn->setStyleSheet("border-radius: 5px;");

    label_1->setFont(selectedFont);
    label_1->setStyleSheet("font-size: 16px;");
    label_2->setFont(selectedFont);
    label_2->setStyleSheet("font-size: 16px;");
    label_3->setFont(selectedFont);
    label_3->setStyleSheet("font-size: 16px;");

    tasksProgress->setFont(selectedFont);
    tasksProgress->setStyleSheet("background-color: rgb(255, 117, 127); selection-background-color: rgb(195, 232, 141); color: #222436; font-size: " + font_size + "pt;");
}

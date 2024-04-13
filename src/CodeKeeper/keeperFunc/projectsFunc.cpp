void MainWindow::createProject() {
    QString newProjectTeamplate =
        "New project\nGitHub\n" + getCurrentDateTimeString();
    qDebug() << "New project: " << newProjectTeamplate;
    notStartedProjects->addItem(newProjectTeamplate);
}

void MainWindow::removeProject() {
    QListWidget *listWidgets[] = {notStartedProjects, startedProjects,
                                  finishlineProjects, finishedProjects};

    for (QListWidget *listWidget : listWidgets) {
        QListWidgetItem *item = listWidget->currentItem();
        if (item) {
            listWidget->takeItem(listWidget->row(item));
            qDebug() << "Removed project: " << item->text();
            delete item;
            break;
        }
    }
}


void MainWindow::openProject(QListWidget *listWidget, QListWidgetItem *item) {
    if (item) {
        QDialog dialog(this);
        dialog.setFixedSize(300, 220);
        dialog.setWindowTitle(tr("Edit project"));
        dialog.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

        QGridLayout layout(&dialog);

        QLineEdit projectName(&dialog);
        projectName.setFixedSize(280, 30);
        QLineEdit gitLink(&dialog);
        gitLink.setFixedSize(280, 30);
        QComboBox documentation(&dialog);
        documentation.setFixedSize(280, 30);
        QLabel lastMod(&dialog);
        lastMod.setFixedSize(280, 30);

        projectName.setFont(selectedFont);
        projectName.setStyleSheet("font-size: " + font_size + "pt;");

        gitLink.setFont(selectedFont);
        gitLink.setStyleSheet("font-size: " + font_size + "pt;");

        documentation.setFont(selectedFont);
        documentation.setStyleSheet("font-size: " + font_size + "pt;");

        lastMod.setFont(selectedFont);
        lastMod.setStyleSheet("font-size: " + font_size + "pt;");
        lastMod.setAlignment(Qt::AlignHCenter);

        QString text1 = item->text().split('\n').at(0);
        QString text2 = item->text().split('\n').at(1);
        QString text3 = item->text().split('\n').at(2);

        projectName.setText(text1);
        gitLink.setText(text2);
        lastMod.setText("Last Mod: " + text3);

        loadDocumentations(path, documentation);

        QPushButton saveButton(&dialog);
        QPushButton closeButton(&dialog);

        saveButton.setFont(selectedFont);
        saveButton.setStyleSheet("font-size: " + font_size + "pt;");
        closeButton.setFont(selectedFont);
        closeButton.setStyleSheet("font-size: " + font_size + "pt;");

        saveButton.setFixedSize(120, 20);
        saveButton.setText("Save");
        closeButton.setFixedSize(120, 20);
        closeButton.setText("Cancel");

        layout.addWidget(&projectName, 0, 0);
        layout.addWidget(&gitLink, 1, 0);
        layout.addWidget(&documentation, 2, 0);
        layout.addWidget(&lastMod, 3, 0);
        layout.addWidget(&saveButton, 4, 0);
        layout.addWidget(&closeButton, 4, 1);

        QObject::connect(&saveButton, &QPushButton::clicked, [&]() {
            text1 = projectName.text();
            text2 = gitLink.text();
            text3 = getCurrentDateTimeString();

            QString itemText = text1 + "\n" + text2 + "\n" + text3;
            item->setText(itemText);
            qDebug() << itemText;
            dialog.close();
        });

        QObject::connect(&closeButton, &QPushButton::clicked,
                         [&]() { dialog.close(); });

        dialog.exec();
    }
}

void MainWindow::loadDocumentations(QDir path, QComboBox &comboBox) {
    QFileInfoList fileInfoList = path.entryInfoList(
        QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    foreach (const QFileInfo &fileInfo, fileInfoList) {
        if (fileInfo.suffix() == "md") {
            comboBox.addItem(fileInfo.baseName());
        }
    }

    QDir subdir;
    QFileInfoList subdirList = path.entryInfoList(
        QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    foreach (const QFileInfo &subdirInfo, subdirList) {
        subdir.setPath(subdirInfo.filePath());
        if (subdir.exists()) {
            loadDocumentations(subdir, comboBox);
        }
    }
}

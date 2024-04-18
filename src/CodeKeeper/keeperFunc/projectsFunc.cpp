void MainWindow::onMovingProjectFrom(QListWidgetItem *item, QListWidget *list) {
    qDebug() << "Moving project: " << item->text() << " from: " << list->objectName();
}

void MainWindow::onMovingProjectTo(QListWidgetItem *item, QListWidget *list) {
    qDebug() << "Moved project: " << item->text() << " to: " << list->objectName();
    QStringList data = item->text().split("\n");
    QString status = list->objectName();
    QString date = getCurrentDateTimeString();

    updateProjectStatus(&status, &date, &data[2]);
}

void MainWindow::createProject() {
    QString date = getCurrentDateTimeString();
    QString status = "NotStartedProjects";
    QString title = "Teamplate";
    QString git = "https://github.com/";
    QString newProjectTeamplate = "New project\nGitHub\n" + date;
    qDebug() << "New project: " << newProjectTeamplate;
    notStartedProjects->addItem(newProjectTeamplate);

    saveProjectToDB(&title, &git, &status, &date);
}

void MainWindow::removeProject() {
    QListWidget *listWidgets[] = {notStartedProjects, startedProjects,
                                  finishlineProjects, finishedProjects};

    for (QListWidget *listWidget : listWidgets) {
        QListWidgetItem *item = listWidget->currentItem();
        if (item) {
            QStringList data = item->text().split("\n");
            QString status = listWidget->objectName();

            listWidget->takeItem(listWidget->row(item));

            removeProjectFromDB(&data[1], &status, &data[2]);

            qDebug() << "Removed project: " << item->text();
            delete item;
            break;
        }
    }
}

void MainWindow::getTotalProjects(QTabWidget *projectsTab,
                                  QListWidget *notStartedProjects,
                                  QListWidget *startedProjects,
                                  QListWidget *finishedProjects,
                                  QListWidget *finishlineProjects) {
    if (projectsTab->currentIndex() == 3) {
        QTimer *timer3 = new QTimer(this);
        connect(timer3, &QTimer::timeout, [=]() {
            int totalProjects =
                notStartedProjects->count() + finishlineProjects->count() +
                startedProjects->count() + finishedProjects->count();

            totalProjectsL->setText(
                "Total projects: " + QString::number(totalProjects) + " ");
        });
        timer3->start(500);
    }
}

void MainWindow::openProject(QListWidget *listWidget, QListWidgetItem *item) {
    if (item) {
        QDialog dialog(this);
        dialog.setFixedSize(400, 460);
        dialog.setWindowTitle(tr("Edit project"));
        dialog.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

        QString data = item->text();
        QStringList splitData = data.split("\n");

        QStringList projectData = GetProjectData(&splitData[1], &splitData[2]);
        qDebug() << projectData;

        QGridLayout mainLayout(&dialog);

        QLineEdit *title = new QLineEdit();
        title->setPlaceholderText(" Project name: ");
        title->setStyleSheet("font-size: " + font_size + ";");
        title->setFixedSize(380, 25);
        title->setText(projectData[0]);
        title->setFont(selectedFont);

        QLineEdit *linkToGit = new QLineEdit();
        linkToGit->setPlaceholderText(" Link to GIT");
        linkToGit->setStyleSheet("font-size: " + font_size + ";");
        linkToGit->setFixedSize(380, 25);
        linkToGit->setText(projectData[1]);
        linkToGit->setFont(selectedFont);

        QComboBox *documentation = new  QComboBox();
        documentation->setFixedSize(380, 25);
        documentation->setFont(selectedFont);

        QMarkdownTextEdit *note = new QMarkdownTextEdit();
        note->setPlaceholderText(" Just start typing");
        note->setStyleSheet("font-size: " + font_size + ";");
        note->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        note->setLineNumberEnabled(true);
        note->setLineNumbersCurrentLineColor("#51afef");
        note->setLineWidth(font_size.toInt());
        note->setHighlightingEnabled(true);
        note->setFont(selectedFont);
        note->setPlainText(projectData[3]);

        QLabel *lastMod = new QLabel();
        lastMod->setText("Last mod: ");
        lastMod->setStyleSheet("font-size: " + font_size + ";");
        lastMod->setFixedSize(380, 25);
        lastMod->setAlignment(Qt::AlignCenter);
        lastMod->setText("Last mod: " + projectData[5]);
        lastMod->setFont(selectedFont);

        QPushButton *saveDataBtn = new QPushButton();
        saveDataBtn->setText("Save");
        saveDataBtn->setStyleSheet("font-size: " + font_size + ";");
        saveDataBtn->setFixedSize(180, 25);
        saveDataBtn->setIcon(QPixmap(":/save.png"));
        saveDataBtn->setIconSize(QSize(10, 10));
        saveDataBtn->setFont(selectedFont);

        QPushButton *cancelBtn = new QPushButton();
        cancelBtn->setText("Cancel");
        cancelBtn->setStyleSheet("font-size: " + font_size + ";");
        cancelBtn->setFixedSize(180, 25);
        cancelBtn->setIcon(QPixmap(":/quit.png"));
        cancelBtn->setIconSize(QSize(10, 10));
        cancelBtn->setFont(selectedFont);

        mainLayout.addWidget(title, 0, 0, 1, 2);
        mainLayout.addWidget(linkToGit, 1, 0, 1, 2);
        mainLayout.addWidget(documentation, 2, 0, 1, 2);
        mainLayout.addWidget(note, 3, 0, 1, 2);
        mainLayout.addWidget(lastMod, 4, 0, 1, 2);
        mainLayout.addWidget(saveDataBtn, 5, 0);
        mainLayout.addWidget(cancelBtn, 5, 1);


        QObject::connect(saveDataBtn, &QPushButton::clicked, [&]() {
            QString text1 = title->text();
            QString text2 = linkToGit->text();
            QString text3 = getCurrentDateTimeString();
            QString doc = documentation->currentText();
            QString noteT = note->toPlainText();

            QString itemText = text1 + "\n" + text2 + "\n" + text3;
            item->setText(itemText);
            qDebug() << itemText;

            updateProjectData(&text1, &text2, &doc, &noteT, &text3, &splitData[2]);

            dialog.close();
        });

        QObject::connect(cancelBtn, &QPushButton::clicked,
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

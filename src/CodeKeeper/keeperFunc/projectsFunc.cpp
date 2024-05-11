#include <QDir>
#include <QFileInfo>

void MainWindow::onMovingProjectFrom(QListWidgetItem *item, QListWidget *list)
{
    qDebug() << "Moving project: " << item->text() << " from: " << list->objectName();
}

void MainWindow::onMovingProjectTo(QListWidgetItem *item, QListWidget *list)
{
    qDebug() << "Moved project: " << item->text() << " to: " << list->objectName();
    QStringList data = item->text().split("\n");
    QString status = list->objectName();
    QString date = getCurrentDateTimeString();

    updateProjectStatus(&status, &date, &data[2]);
}

void loadDocumentations(QDir path, QComboBox &comboBox)
{
    QFileInfoList fileInfoList =
            path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    foreach (const QFileInfo &fileInfo, fileInfoList) {
        if (fileInfo.suffix() == "md") {
            comboBox.addItem(fileInfo.baseName());
        }
    }

    QDir subdir;
    QFileInfoList subdirList =
            path.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    foreach (const QFileInfo &subdirInfo, subdirList) {
        subdir.setPath(subdirInfo.filePath());
        if (subdir.exists()) {
            loadDocumentations(subdir, comboBox);
        }
    }
}

void MainWindow::createProject()
{
    QString date = getCurrentDateTimeString();
    QString status = "NotStartedProjects";
    QString title = "Teamplate";
    QString git = "https://github.com/";
    QString newProjectTeamplate = title + "\n" + git + "\n" + date;

    qDebug() << "New project: " << newProjectTeamplate;

    notStartedProjects->addItem(newProjectTeamplate);

    saveProjectToDB(&title, &git, &status, &date);
}

void MainWindow::removeProject()
{
    QListWidget *listWidgets[] = { notStartedProjects, startedProjects, finishlineProjects,
                                   finishedProjects };

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

void MainWindow::getTotalProjects(QTabWidget *projectsTab, QListWidget *notStartedProjects,
                                  QListWidget *startedProjects, QListWidget *finishedProjects,
                                  QListWidget *finishlineProjects)
{
    if (projectsTab->currentIndex() == 3) {
        QTimer *timer3 = new QTimer(this);
        connect(timer3, &QTimer::timeout, [=]() {
            int totalProjects = notStartedProjects->count() + finishlineProjects->count()
                    + startedProjects->count() + finishedProjects->count();

            totalProjectsL->setText("Total projects: " + QString::number(totalProjects) + " ");
        });
        timer3->start(500);
    }
}

void MainWindow::openNote(QString filePath)
{
    QFile file(filePath);

    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        noteEdit->setPlainText(stream.readAll());
        file.close();
    } else {
        qWarning() << "Error: " << file.error();
    }
}

QString findFileInDirectoryAndSubdirectories(QDir dir, const QString &fileName)
{
    return dir.absoluteFilePath(fileName);
}

void MainWindow::openDocumentation(QComboBox &comboBox)
{
    QString doc = comboBox.currentText();

    QString filePath = findFileInDirectoryAndSubdirectories(dir, doc);
    tabs->setCurrentIndex(1);
    openNote(filePath);
}

void MainWindow::openProject(QListWidget *listWidget, QListWidgetItem *item)
{
    if (item) {
        QDialog dialog(this);
        dialog.setMinimumSize(400, 400);
        dialog.setWindowTitle(tr("Edit project"));
        dialog.setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

        QString data = item->text();
        QStringList splitData = data.split("\n");

        QString PTitle = splitData[0];
        QString PGit = splitData[1];
        QString PCreatedTime = splitData[2];
        QString PStatus = listWidget->objectName();

        QStringList projectData = GetProjectData(&PTitle, &PStatus, &PGit);
        qDebug() << "Open project: " << projectData[0] << " " << projectData[1] << " "
                 << projectData[2] << " " << projectData[3] << " " << projectData[4] << " "
                 << projectData[5];

        QGridLayout mainLayout(&dialog);

        QLineEdit *title = new QLineEdit();
        title->setPlaceholderText(" Project name: ");
        title->setStyleSheet("font-size: " + font_size + "pt;");
        title->setFixedHeight(25);
        title->setFont(selectedFont);

        QLineEdit *linkToGit = new QLineEdit();
        linkToGit->setPlaceholderText(" Link to GIT");
        linkToGit->setStyleSheet("font-size: " + font_size + "pt;");
        linkToGit->setFixedHeight(25);
        linkToGit->setFont(selectedFont);

        QComboBox *documentation = new QComboBox();
        documentation->setFixedHeight(25);
        documentation->setFont(selectedFont);

        note = new QMarkdownTextEdit();
        note->setPlaceholderText(" Just start typing");
        note->setStyleSheet("font-size: " + font_size + "pt;");
        note->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        note->setLineNumberEnabled(true);
        note->setLineNumbersCurrentLineColor("#51afef");
        note->setLineWidth(font_size.toInt());
        note->setHighlightingEnabled(true);
        note->setFont(selectedFont);

        QLabel *lastMod = new QLabel();
        lastMod->setText("Last mod: ");
        lastMod->setStyleSheet("font-size: " + font_size + "pt;");
        lastMod->setFixedHeight(25);
        lastMod->setAlignment(Qt::AlignCenter);
        lastMod->setFont(selectedFont);

        QPushButton *saveDataBtn = new QPushButton();
        saveDataBtn->setText("Save");
        saveDataBtn->setStyleSheet("font-size: " + font_size + "pt;");
        saveDataBtn->setFixedHeight(30);
        saveDataBtn->setIcon(QPixmap(":/save.png"));
        saveDataBtn->setIconSize(QSize(10, 10));
        saveDataBtn->setFont(selectedFont);

        QPushButton *cancelBtn = new QPushButton();
        cancelBtn->setText("Cancel");
        cancelBtn->setStyleSheet("font-size: " + font_size + "pt;");
        cancelBtn->setFixedHeight(30);
        cancelBtn->setIcon(QPixmap(":/quit.png"));
        cancelBtn->setIconSize(QSize(10, 10));
        cancelBtn->setFont(selectedFont);

        title->setText(projectData[0]);
        linkToGit->setText(projectData[1]);
        note->setPlainText(projectData[3]);
        lastMod->setText("Last mod: " + projectData[5]);

        loadDocumentations(dir, *documentation);
        documentation->setCurrentText(projectData[2]);

        mainLayout.addWidget(title, 0, 0, 1, 2);
        mainLayout.addWidget(linkToGit, 1, 0, 1, 2);
        mainLayout.addWidget(documentation, 2, 0, 1, 2);
        mainLayout.addWidget(note, 3, 0, 1, 2);
        mainLayout.addWidget(lastMod, 5, 0, 1, 2);
        mainLayout.addWidget(saveDataBtn, 4, 0);
        mainLayout.addWidget(cancelBtn, 4, 1);

        openDocumentation(*documentation);

        QObject::connect(saveDataBtn, &QPushButton::clicked, [&]() {
            QString projectTitle = title->text();
            QString projectLink = linkToGit->text();
            QString projectCreatedTime = getCurrentDateTimeString();
            QString projectDocumentation = documentation->currentText();
            QString noteT = note->toPlainText();

            QString itemText = projectTitle + "\n" + projectLink + "\n" + projectCreatedTime;
            item->setText(itemText);
            qDebug() << itemText;

            updateProjectData(&projectTitle, &projectLink, &projectDocumentation, &noteT,
                              &projectCreatedTime, &PCreatedTime, &PGit);

            dialog.close();
        });

        QObject::connect(cancelBtn, &QPushButton::clicked, [&]() { dialog.close(); });

        QObject::connect(
                documentation, &QComboBox::currentTextChanged, this,
                [this, documentation](const QString &text) { openDocumentation(*documentation); });

        dialog.exec();
    } else {
        qWarning() << "Error";
    }
}

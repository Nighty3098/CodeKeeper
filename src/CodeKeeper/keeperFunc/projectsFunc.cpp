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
}

QString findFileInDirectoryAndSubdirectories(QDir dir, const QString &fileName)
{
    QFileInfo fileInfo(dir, fileName);

    QString filePath = fileInfo.absoluteFilePath() + ".md";
    qDebug() << "File: " << filePath;
    return filePath;
}

void MainWindow::openDoc(QComboBox *comboBox, QDir dir)
{
    QString doc = comboBox->currentText();

    QString filePath = findFileInDirectoryAndSubdirectories(dir, doc);
    tabs->setCurrentIndex(1);
    openNote(filePath);
}

void MainWindow::openProject(QListWidget *listWidget, QListWidgetItem *item)
{
    if (item) {
        QDialog dialog(this);
        dialog.setFixedSize(400, 460);
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
        title->setFixedSize(380, 25);
        title->setFont(selectedFont);

        QLineEdit *linkToGit = new QLineEdit();
        linkToGit->setPlaceholderText(" Link to GIT");
        linkToGit->setStyleSheet("font-size: " + font_size + "pt;");
        linkToGit->setFixedSize(380, 25);
        linkToGit->setFont(selectedFont);

        QComboBox *documentation = new QComboBox();
        documentation->setFixedSize(380, 25);
        documentation->setFont(selectedFont);

        QMarkdownTextEdit *note = new QMarkdownTextEdit();
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
        lastMod->setFixedSize(380, 25);
        lastMod->setAlignment(Qt::AlignCenter);
        lastMod->setFont(selectedFont);

        QPushButton *saveDataBtn = new QPushButton();
        saveDataBtn->setText("Save");
        saveDataBtn->setStyleSheet("font-size: " + font_size + "pt;");
        saveDataBtn->setFixedSize(180, 25);
        saveDataBtn->setIcon(QPixmap(":/save.png"));
        saveDataBtn->setIconSize(QSize(10, 10));
        saveDataBtn->setFont(selectedFont);

        QPushButton *openDocBtn = new QPushButton();
        openDocBtn->setText("Open");
        openDocBtn->setStyleSheet("font-size: " + font_size + "pt;");
        openDocBtn->setIcon(QPixmap(":/read.png"));
        openDocBtn->setFixedSize(180, 25);
        openDocBtn->setIconSize(QSize(10, 10));
        openDocBtn->setFont(selectedFont);

        QPushButton *cancelBtn = new QPushButton();
        cancelBtn->setText("Cancel");
        cancelBtn->setStyleSheet("font-size: " + font_size + "pt;");
        cancelBtn->setFixedSize(180, 25);
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
        mainLayout.addWidget(documentation, 2, 0);
        mainLayout.addWidget(openDocBtn, 2, 1);
        mainLayout.addWidget(note, 3, 0, 1, 2);
        mainLayout.addWidget(lastMod, 4, 0, 1, 2);
        mainLayout.addWidget(saveDataBtn, 5, 0);
        mainLayout.addWidget(cancelBtn, 5, 1);

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

        QObject::connect(openDocBtn, &QPushButton::clicked, [&]() {
            openDoc(documentation, dir);
            dialog.close();
        });

        dialog.exec();
    } else {
        qWarning() << "Error";
    }
}

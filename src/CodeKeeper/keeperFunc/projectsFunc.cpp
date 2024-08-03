#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmap>
#include <QTableWidget>
#include <QUrl>
#include <QWebEngineView>

#include "getProjectInfo.cpp"

void MainWindow::activateProjectContextMenu(const QPoint &pos, QListWidget *listWidget)
{
    QPoint item = listWidget->mapToGlobal(pos);
    QMenu *submenu = new QMenu;

    // ! Trash - need fixed
    if (isCustomTheme)
    {
        submenu->setStyleSheet("QMenu {"
                               "    background-color: #2b3d4c;"
                               "    color: #fff;"
                               "    border: 1px solid #fff;"
                               "    border-radius: 10px;"
                               "}"
                               "QMenu::separator {"
                               "    height: 3px;"
                               "    border-radius: 1px;"
                               "    background-color: #fff;"
                               "}"
                               "QMenu::item {"
                               "    border-radius: 0px;"
                               "    color: #fff;"
                               "    margin: 5px 10px;"
                               "}"
                               "QMenu::item:selected {"
                               "    border-radius: 10px;"
                               "    color: #78b3ba;"
                               "    text-decoration: none;"
                               "}");
    }
    else
    {
    }

    createProjectMenu(submenu, font_size);

    QAction *rightClickItem = submenu->exec(item);
}

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
    QFileInfoList fileInfoList = path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    foreach (const QFileInfo &fileInfo, fileInfoList)
    {
        if (fileInfo.suffix() == "md")
        {
            comboBox.addItem(fileInfo.baseName());
        }
    }

    QDir subdir;
    QFileInfoList subdirList = path.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    foreach (const QFileInfo &subdirInfo, subdirList)
    {
        subdir.setPath(subdirInfo.filePath());
        if (subdir.exists())
        {
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

    QListWidgetItem *item = new QListWidgetItem(newProjectTeamplate);
    item->setTextAlignment(Qt::AlignCenter);

    notStartedProjects->addItem(item);

    saveProjectToDB(&title, &git, &status, &date);
}

void MainWindow::removeProject()
{
    QListWidget *listWidgets[] = {notStartedProjects, startedProjects, finishlineProjects, finishedProjects};

    for (QListWidget *listWidget : listWidgets)
    {
        QListWidgetItem *item = listWidget->currentItem();
        if (item)
        {
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
    QThread *totalProjectsThread = new QThread;
    QObject::connect(totalProjectsThread, &QThread::started, this,
                     [this, projectsTab, notStartedProjects, startedProjects, finishedProjects, finishlineProjects]() {
                         if (projectsTab->currentIndex() == 3)
                         {
                             QTimer *timer3 = new QTimer(this);
                             connect(timer3, &QTimer::timeout, [=]() {
                                 int totalProjects = notStartedProjects->count() + finishlineProjects->count() +
                                                     startedProjects->count() + finishedProjects->count();

                                 totalProjectsL->setText(tr("Total projects: ") + QString::number(totalProjects) + " ");
                             });
                             timer3->start(500);
                         }
                     });
    totalProjectsThread->start();
}

void MainWindow::openDocumentation(QString fileName)
{
    QString name = fileName + ".md";
    qDebug() << name;
    tabs->setCurrentIndex(1);

    selectFileInQTreeView(notesList, name);
}

void MainWindow::selectFileInQTreeView(QTreeView *treeView, const QString &fileName)
{
}

void MainWindow::openGitProject()
{
    QListWidget *listWidgets[] = {notStartedProjects, startedProjects, finishlineProjects, finishedProjects};

    for (QListWidget *listWidget : listWidgets)
    {
        QListWidgetItem *item = listWidget->currentItem();
        if (item)
        {
            QStringList data = item->text().split("\n");

            QString git_url = data[1];
            qDebug() << git_url;
            QUrl url(git_url);
            QDesktopServices::openUrl(url);

            break;
        }
    }
}

void MainWindow::openProject()
{
    QListWidget *listWidgets[] = {notStartedProjects, startedProjects, finishlineProjects, finishedProjects};

    for (QListWidget *listWidget : listWidgets)
    {
        QListWidgetItem *item = listWidget->currentItem();

        if (item)
        {
            QDialog dialog(this);
            QSizeGrip *sizeGrip = new QSizeGrip(this);

            dialog.setFixedWidth(600);
            dialog.setMinimumHeight(500);
            dialog.setWindowTitle(tr("Project"));
            dialog.setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

            QPushButton *saveDataBtn = new QPushButton();
            saveDataBtn->setText(tr("Save"));
            saveDataBtn->setStyleSheet("font-size: " + font_size + "pt;");
            saveDataBtn->setFixedSize(100, 25);
            saveDataBtn->setIcon(QPixmap(":/save.png"));
            saveDataBtn->setIconSize(QSize(10, 10));
            saveDataBtn->setFont(selectedFont);

            QPushButton *cancelBtn = new QPushButton("");
            cancelBtn->setFixedSize(15, 15);
            cancelBtn->setStyleSheet("QPushButton {"
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

            QVBoxLayout *centralLayout = new QVBoxLayout(&dialog);

            QHBoxLayout *controlButtons = new QHBoxLayout();

            QSpacerItem *spacer = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

            controlButtons->addWidget(cancelBtn);
            controlButtons->addItem(spacer);
            controlButtons->addWidget(saveDataBtn);

            centralLayout->addLayout(controlButtons);

            QTabWidget *tabs = new QTabWidget();
            tabs->setMovable(true);
            tabs->setTabPosition(QTabWidget::South);

            QWidget *projectTab = new QWidget();
            QGridLayout mainLayout(projectTab);

            QString data = item->text();
            QStringList splitData = data.split("\n");

            QString PTitle = splitData[0];
            QString PGit = splitData[1];
            QString PCreatedTime = splitData[2];
            QString PStatus = listWidget->objectName();

            QStringList projectData = GetProjectData(&PTitle, &PStatus, &PGit);
            qDebug() << "Open project: " << projectData[0] << " " << projectData[1] << " " << projectData[2] << " "
                     << projectData[3] << " " << projectData[4];

            QLineEdit *title = new QLineEdit();
            title->setAlignment(Qt::AlignCenter);
            title->setPlaceholderText(tr(" Project name: "));
            title->setStyleSheet("font-size: " + font_size + "pt;");
            title->setFixedHeight(25);
            title->setFont(selectedFont);

            QLineEdit *linkToGit = new QLineEdit();
            linkToGit->setAlignment(Qt::AlignCenter);
            linkToGit->setPlaceholderText(tr(" Link to GIT"));
            linkToGit->setStyleSheet("font-size: " + font_size + "pt;");
            linkToGit->setFixedHeight(25);
            linkToGit->setFont(selectedFont);

            QComboBox *documentation = new QComboBox();
            documentation->setMinimumSize(170, 20);
            documentation->setFont(selectedFont);

            QLabel *lastMod = new QLabel();
            lastMod->setText(tr("Last mod: "));
            lastMod->setStyleSheet("font-size: " + font_size + "pt;");
            lastMod->setFixedHeight(25);
            lastMod->setAlignment(Qt::AlignCenter);
            lastMod->setFont(selectedFont);

            QTableWidget *git_stats = new QTableWidget();
            git_stats->setFont(selectedFont);
            git_stats->setStyleSheet("QTableWidget{font-size:" + font_size + "pt;}");

            git_stats->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
            git_stats->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
            git_stats->setContentsMargins(0, 0, 0, 0);
            git_stats->setAlternatingRowColors(true);

            QLabel *descriptionL = new QLabel();
            descriptionL->setFixedHeight(30);
            descriptionL->setAlignment(Qt::AlignCenter);
            descriptionL->setFont(selectedFont);
            descriptionL->setStyleSheet("font-size: " + font_size + "pt;");

            QHBoxLayout *statsLayout = new QHBoxLayout();

            QSpacerItem *leftSpacer = new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
            QSpacerItem *rightSpacer = new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

            // statsLayout->addItem(leftSpacer);
            statsLayout->addWidget(git_stats);
            // statsLayout->addItem(rightSpacer);

            QPushButton *openButton = new QPushButton();
            openButton->setText(tr("Open"));
            openButton->setStyleSheet("font-size: " + font_size + "pt;");
            openButton->setFixedHeight(25);
            openButton->setIcon(QPixmap(":/read.png")
                                    .scaled(font_size.toInt() + 3, font_size.toInt() + 3, Qt::KeepAspectRatio,
                                            Qt::SmoothTransformation));
            openButton->setIconSize(QSize(10, 10));
            openButton->setFont(selectedFont);

            title->setText(projectData[0]);
            linkToGit->setText(projectData[1]);
            lastMod->setText(tr("Last mod: ") + projectData[4]);

            loadDocumentations(dir, *documentation);
            documentation->setCurrentText(projectData[2]);

            mainLayout.addWidget(title, 0, 0, 1, 2);
            mainLayout.addWidget(linkToGit, 1, 0, 1, 2);
            // mainLayout.addWidget(documentation, 2, 0);
            // mainLayout.addWidget(openButton, 2, 1);
            // mainLayout.addWidget(descriptionL, 3, 0, 1, 2);
            mainLayout.addLayout(statsLayout, 5, 0, 5, 2);
            mainLayout.addWidget(lastMod, 10, 0, 1, 2, Qt::AlignCenter);

            QWidget *issuesTab = new QWidget();
            QVBoxLayout issuesLayout(issuesTab);

            QTextBrowser *issuesLabel = new QTextBrowser();
            issuesLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
            issuesLabel->setText(tr("Issues"));
            issuesLabel->setOpenExternalLinks(true);
            issuesLabel->setFont(selectedFont);
            issuesLabel->setStyleSheet("font-size: " + font_size + "pt;");
            issuesLabel->setAlignment(Qt::AlignCenter);
            issuesLayout.addWidget(issuesLabel);

            tabs->addTab(projectTab, tr("Project"));
            tabs->addTab(issuesTab, tr("Issues"));

            centralLayout->addWidget(descriptionL);
            centralLayout->addWidget(tabs);

            QThread *thread = new QThread;
            QObject::connect(thread, &QThread::started, this,
                             [this, projectData, git_stats, issuesLabel, descriptionL]() {
                                 getRepositoryData(projectData[1], git_stats, descriptionL);
                                 issuesLabel->setHtml(getProjectIssues(projectData[1]));
                             });
            thread->start();

            QObject::connect(saveDataBtn, &QPushButton::clicked, [&]() {
                QString projectTitle = title->text();
                QString projectLink = linkToGit->text();
                QString projectCreatedTime = getCurrentDateTimeString();
                QString projectDocumentation = documentation->currentText();

                QString itemText = projectTitle + "\n" + projectLink + "\n" + projectCreatedTime;
                item->setText(itemText);
                qDebug() << itemText;

                updateProjectData(&projectTitle, &projectLink, &projectDocumentation, &projectCreatedTime,
                                  &PCreatedTime, &PGit);
            });

            QObject::connect(cancelBtn, &QPushButton::clicked, [&]() { dialog.close(); });

            QObject::connect(openButton, &QPushButton::clicked, [&]() {
                dialog.close();
                QString doc = documentation->currentText();
                openDocumentation(doc);
            });

            QObject::connect(linkToGit, &QLineEdit::textChanged, [&]() {
                QString prefix = "https://github.com/";
                QString projectLink = linkToGit->text();
                QString repo = projectLink.replace(prefix, "");

                QThread *thread = new QThread;
                QObject::connect(thread, &QThread::started, this,
                                 [this, projectData, repo, git_stats, issuesLabel, descriptionL]() {
                                     getRepositoryData(repo, git_stats, descriptionL);
                                     issuesLabel->setHtml(getProjectIssues(repo));
                                 });
                thread->start();
            });

            dialog.exec();

            break;
        }
        else
        {
            qWarning() << "Error";
        }
    }
}

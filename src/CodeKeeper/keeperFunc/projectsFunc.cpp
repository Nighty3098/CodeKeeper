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

#include "getProjectInfo.cpp"
#include "mainwindow.h"

void MainWindow::activateProjectContextMenu(const QPoint &pos, QListWidget *listWidget)
{
    if (!listWidget || listWidget->count() == 0)
    {
        return;
    }

    QPoint globalPos = listWidget->mapToGlobal(pos);
    QMenu *submenu = new QMenu(this);

    if (isCustomTheme)
    {
        submenu->setStyleSheet("QMenu {"
                               "    background-color: #505a6a;"
                               "    color: #fff;"
                               "    border: 0px solid #fff;"
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

    createProjectMenu(submenu, font_size);

    QAction *rightClickItem = submenu->exec(globalPos);
}

void MainWindow::onMovingProjectFrom(QListWidgetItem *item, QListWidget *list)
{
    if (item && list)
    {
        qDebug() << "Moving project: " << item->text() << " from: " << list->objectName();
    }
}

void MainWindow::onMovingProjectTo(QListWidgetItem *item, QListWidget *list)
{
    if (item && list)
    {
        qDebug() << "Moved project: " << item->text() << " to: " << list->objectName();

        // Разбиваем текст элемента на строки
        QStringList data = item->text().split("\n");

        // Проверяем, что у нас достаточно данных
        if (data.size() >= 3)
        {
            QString status = list->objectName();       // Получаем статус из имени списка
            QString date = getCurrentDateTimeString(); // Получаем текущую дату и время

            // Обновляем статус проекта
            updateProjectStatus(&status, &date, &data[2]); // Передаем данные в функцию обновления статуса

            // Перемещаем элемент в новый список
            QListWidget *currentList = item->listWidget();
            if (currentList)
            {
                currentList->takeItem(currentList->row(item)); // Удаляем элемент из текущего списка
            }
            list->addItem(new QListWidgetItem(item->text())); // Добавляем элемент в новый список

            // Удаляем оригинальный элемент, так как он был перемещен
            delete item;
        }
        else
        {
            qWarning() << "Invalid project data format"; // Логируем предупреждение, если данные некорректны
        }
    }
}

void MainWindow::createProject()
{
    QString date = getCurrentDateTimeString();
    QString status = "NotStartedProjects";
    QString title = "New project";
    QString git = "https://github.com/";

    QString newProjectTemplate = QString("%1\n%2\n%3").arg(title).arg(git).arg(date);

    qDebug() << "New project: " << newProjectTemplate;

    QListWidgetItem *item = new QListWidgetItem(newProjectTemplate);
    notStartedProjects->addItem(item);

    saveProjectToDB(&title, &git, &status, &date);
}

void MainWindow::removeProject()
{
    QList<QListWidget *> listWidgets = {notStartedProjects, startedProjects, finishlineProjects, finishedProjects};

    for (QListWidget *listWidget : listWidgets)
    {
        QListWidgetItem *item = listWidget->currentItem();
        if (item)
        {
            QStringList data = item->text().split("\n");
            QString status = listWidget->objectName();

            int row = listWidget->row(item);
            listWidget->takeItem(row);

            removeProjectFromDB(&data[1], &status, &data[2]);

            qDebug() << "Removed project: " << item->text();
            break;
        }
    }
}
void MainWindow::getTotalProjects(QTabWidget *projectsTab, QListWidget *notStartedProjects,
                                  QListWidget *startedProjects, QListWidget *finishedProjects,
                                  QListWidget *finishlineProjects)
{
    static QTimer *timer3 = new QTimer(this);

    connect(timer3, &QTimer::timeout, this,
            [this, notStartedProjects, finishlineProjects, startedProjects, finishedProjects]() {
                int totalProjects = notStartedProjects->count() + finishlineProjects->count() +
                                    startedProjects->count() + finishedProjects->count();

                totalProjectsL->setText(tr("Total projects: ") + QString::number(totalProjects) + " ");
            });

    if (projectsTab->currentIndex() == 3)
    {
        if (!timer3->isActive())
        {
            timer3->start(500);
        }
    }
    else
    {
        if (timer3->isActive())
        {
            timer3->stop();
        }
    }

    int totalProjects = notStartedProjects->count() + finishlineProjects->count() + startedProjects->count() +
                        finishedProjects->count();
    totalProjectsL->setText(tr("Total projects: ") + QString::number(totalProjects) + " ");
}

void MainWindow::selectFileInQTreeView(QTreeView *treeView, const QString &fileName)
{
}

void MainWindow::openGitProject()
{
    QVector<QListWidget *> listWidgets = {notStartedProjects, startedProjects, finishlineProjects, finishedProjects};

    QString git_url;

    for (QListWidget *listWidget : listWidgets)
    {
        QListWidgetItem *item = listWidget->currentItem();
        if (item)
        {
            QStringList lines = item->text().split('\n');
            if (lines.size() > 1)
            {
                git_url = lines[1].trimmed();
                qDebug() << "Opening URL:" << git_url;

                QUrl url(git_url);
                if (url.isValid() && (url.scheme() == "http" || url.scheme() == "https"))
                {
                    QDesktopServices::openUrl(url);
                    return;
                }
                else
                {
                    QMessageBox::warning(this, "Invalid URL", "The URL is not valid.");
                    return;
                }
            }
            else
            {
                QMessageBox::warning(this, "Invalid Item", "The selected item does not contain a valid URL.");
                return;
            }
        }
    }

    QMessageBox::information(this, "No Selection", "Please select a project to open.");
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
            QSizeGrip *dialogSizeGrip = new QSizeGrip(this);

            dialog.setFixedWidth(570);
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
            cancelBtn->setFixedSize(13, 13);
            cancelBtn->setStyleSheet("QPushButton {"
                                     "    border-radius: 6px;"
                                     "    border-color: rgba(0, 0, 0, 0);"
                                     "    background-color: #e08581;"
                                     "    background-repeat: no-repeat;"
                                     "    background-attachment: fixed;"
                                     "}"

                                     "QPushButton:hover {"
                                     "    border-radius: 6px;"
                                     "    border-color: rgba(0, 0, 0, 0);"
                                     "    background-repeat: no-repeat;"
                                     "    background-color: #e06a65;"
                                     "    background-attachment: fixed;"
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
            descriptionL->setFixedHeight(25);
            descriptionL->setAlignment(Qt::AlignCenter);
            descriptionL->setFont(selectedFont);
            descriptionL->setStyleSheet("font-size: " + font_size + "pt;");

            QHBoxLayout *statsLayout = new QHBoxLayout();

            QSpacerItem *leftSpacer = new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
            QSpacerItem *rightSpacer = new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

            statsLayout->addWidget(git_stats);

            title->setText(projectData[0]);
            linkToGit->setText(projectData[1]);
            lastMod->setText(tr("Last mod: ") + projectData[4]);

            mainLayout.addWidget(title, 0, 0, 1, 2);
            mainLayout.addWidget(linkToGit, 1, 0, 1, 2);
            mainLayout.addWidget(descriptionL, 3, 0, 1, 2);
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

                QString itemText = projectTitle + "\n" + projectLink + "\n" + projectCreatedTime;
                item->setText(itemText);
                qDebug() << itemText;

                QString projectDocumentation = "";

                updateProjectData(&projectTitle, &projectLink, &projectDocumentation, &projectCreatedTime,
                                  &PCreatedTime, &PGit);
            });

            QObject::connect(cancelBtn, &QPushButton::clicked, [&]() { dialog.close(); });

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

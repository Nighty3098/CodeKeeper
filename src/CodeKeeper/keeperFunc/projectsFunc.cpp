#include <QDir>
#include <QFileInfo>
#include <QWebEngineView>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QTableWidget>

void MainWindow::onMovingProjectFrom(QListWidgetItem *item, QListWidget *list)
{
    qDebug() << "Moving project: " << item->text()
             << " from: " << list->objectName();
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
    QThread *totalProjectsThread = new QThread;
    QObject::connect(totalProjectsThread, &QThread::started, this,
                     [this, projectsTab, notStartedProjects, startedProjects, finishedProjects,
                      finishlineProjects]() {
                         if (projectsTab->currentIndex() == 3) {
                             QTimer *timer3 = new QTimer(this);
                             connect(timer3, &QTimer::timeout, [=]() {
                                 int totalProjects = notStartedProjects->count()
                                         + finishlineProjects->count() + startedProjects->count()
                                         + finishedProjects->count();

                                 totalProjectsL->setText(
                                         "Total projects: " + QString::number(totalProjects) + " ");
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

void MainWindow::selectFileInQTreeView(QTreeView *treeView, const QString &fileName) { }

QString formatFileSize(qint64 bytes)
{
    static const char *suffixes[] = { "KB", "MB", "GB", "TB", "PB", "..." };
    int index = 0;
    double size = bytes;

    while (size >= 1024 && index < 5) {
        size /= 1024;
        index++;
    }

    return QString::number(size, 'f', 2) + " " + suffixes[index];
}

QString MainWindow::getRepositoryData(QString git_url, QTableWidget *table)
{
    QString prefix = "https://github.com/";
    QString repo = git_url.replace(prefix, "");
    QString repoData; // Declare repoData as a non-const QString

    QString name, createdAt, openIssues, forks, lang, stars, repoSize, license, totalDownloads,
            release, releaseDate, lastCommitS;

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QUrl url("https://api.github.com/repos/" + repo);

    QUrlQuery query;
    query.addQueryItem("login", git_user);
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    request.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    request.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *reply = manager->get(request);
    QEventLoop loop; // Create a QEventLoop
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec(); // Block until the lambda function has finished

    if (reply->error()) {
        qWarning() << "Error:" << reply->errorString();
        reply->deleteLater();
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = doc.object();
    qDebug() << doc;

    name = obj["name"].toString();

    if (isCreated) {
        createdAt = obj["created_at"].toString();
        QDateTime createdDate = QDateTime::fromString(createdAt, Qt::ISODate);
        createdAt = createdDate.toString("dd MMM yyyy hh:mm");
    }
    if (isIssue) {
        openIssues = QString::number(obj["open_issues"].toInt());
    }
    // repoData += " \n Watchers: " + QString::number(obj["watchers"].toInt()) + " ";
    if (isForks) {
        forks = QString::number(obj["forks"].toInt());
    }
    if (isLang) {
        lang = obj["language"].toString();
    }
    if (isStars) {
        stars = QString::number(obj["stargazers_count"].toInt());
    }
    if (isRepoSize) {
        qint64 size = obj["size"].toDouble();

        repoSize = formatFileSize(size);
    }

    if (obj.contains("license")) {
        QJsonObject licenseObj = obj["license"].toObject();
        if (licenseObj.contains("name")) {
            if (isLicense) {
                license = licenseObj["name"].toString() + " ";
            }
        } else {
            if (isLicense) {
                qDebug() << "License not found";
            }
        }
    } else {
        if (isLicense) {
            qDebug() << "License not found";
        }
    }

    QUrl commitUrl("https://api.github.com/repos/" + repo + "/commits");
    QNetworkReply *commitReply = manager->get(QNetworkRequest(commitUrl));
    QObject::connect(commitReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (commitReply->error()) {
        qWarning() << "Error:" << commitReply->errorString();
        commitReply->deleteLater();
    }

    QJsonDocument commitDoc = QJsonDocument::fromJson(commitReply->readAll());
    QJsonObject commitObj = commitDoc.object();
    QJsonArray commits = commitDoc.array();
    qDebug() << commitDoc;

    if (commits.isEmpty()) {
        if (isLastCommit) {
            qDebug() << "No commits found";
        }
    }

    QJsonObject lastCommit = commits.first().toObject();
    QString dateStr = lastCommit["commit"].toObject()["author"].toObject()["date"].toString();

    QDateTime lastCommitDate = QDateTime::fromString(dateStr, Qt::ISODate);

    if (isLastCommit) {
        QString lastCommitS = lastCommitDate.toString("dd MMM yyyy hh:mm");
    }

    QUrl releaseUrl("https://api.github.com/repos/" + repo + "/releases");
    QNetworkReply *releaseReply = manager->get(QNetworkRequest(releaseUrl));
    QObject::connect(releaseReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (releaseReply->error()) {
        qWarning() << "Error:" << releaseReply->errorString();
        releaseReply->deleteLater();
    }

    QJsonDocument releaseDoc = QJsonDocument::fromJson(releaseReply->readAll());
    QJsonArray releases = releaseDoc.array();
    qDebug() << releaseDoc;

    int iTotalDownloads = 0;
    for (const QJsonValue &release : releases) {
        QJsonObject releaseObj = release.toObject();
        int downloads = releaseObj["assets"].toArray().at(0).toObject()["download_count"].toInt();
        iTotalDownloads += downloads;
    }

    if (isDownloads) {
        totalDownloads = QString::number(iTotalDownloads);
    }

    // Release info
    QUrl releasesUrl("https://api.github.com/repos/" + repo + "/releases/latest");
    QNetworkReply *releasesReply = manager->get(QNetworkRequest(releasesUrl));
    QObject::connect(releasesReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec(); // Block until the lambda function has finished

    if (releasesReply->error()) {
        qWarning() << "Error:" << releasesReply->errorString();
        releasesReply->deleteLater();
    }

    QJsonDocument releasesDoc = QJsonDocument::fromJson(releasesReply->readAll());
    QJsonObject releasesObj = releasesDoc.object();
    qDebug() << releasesDoc;

    if (isRelease) {
        release = releasesObj["name"].toString();
    }

    if (isReleaseDate) {
        QString dateStr = releasesObj["published_at"].toString();

        QDateTime releaseDateT = QDateTime::fromString(dateStr, Qt::ISODate);
        releaseDate = releaseDateT.toString("dd MMM yyyy hh:mm");
    }

    releasesReply->deleteLater();
    reply->deleteLater();

    table->setRowCount(12);
    table->setColumnCount(2);
    table->setShowGrid(false);

    table->setColumnWidth(0, 190);
    table->setColumnWidth(1, 190);

    table->setRowHeight(0, 25);
    table->setRowHeight(1, 25);
    table->setRowHeight(3, 25);
    table->setRowHeight(4, 25);
    table->setRowHeight(5, 25);
    table->setRowHeight(6, 25);
    table->setRowHeight(7, 25);
    table->setRowHeight(8, 25);
    table->setRowHeight(9, 25);
    table->setRowHeight(10, 25);
    table->setRowHeight(11, 25);

    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();

    table->setItem(0, 0, new QTableWidgetItem("Repo"));
    table->setItem(0, 1, new QTableWidgetItem(name));

    table->setItem(1, 0, new QTableWidgetItem("Created at"));
    table->setItem(1, 1, new QTableWidgetItem(createdAt));

    table->setItem(2, 0, new QTableWidgetItem("Open issues"));
    table->setItem(2, 1, new QTableWidgetItem(openIssues));

    table->setItem(3, 0, new QTableWidgetItem("Forks"));
    table->setItem(3, 1, new QTableWidgetItem(forks));

    table->setItem(4, 0, new QTableWidgetItem("Lang"));
    table->setItem(4, 1, new QTableWidgetItem(lang));

    table->setItem(5, 0, new QTableWidgetItem("Stars"));
    table->setItem(5, 1, new QTableWidgetItem(stars));

    table->setItem(6, 0, new QTableWidgetItem("Repo size"));
    table->setItem(6, 1, new QTableWidgetItem(repoSize));

    table->setItem(7, 0, new QTableWidgetItem("License"));
    table->setItem(7, 1, new QTableWidgetItem(license));

    table->setItem(8, 0, new QTableWidgetItem("Last commit"));
    table->setItem(8, 1, new QTableWidgetItem(lastCommitS));

    table->setItem(9, 0, new QTableWidgetItem("Downloads"));
    table->setItem(9, 1, new QTableWidgetItem(totalDownloads));

    table->setItem(10, 0, new QTableWidgetItem("Release"));
    table->setItem(10, 1, new QTableWidgetItem(release));

    table->setItem(11, 0, new QTableWidgetItem("Release at"));
    table->setItem(11, 1, new QTableWidgetItem(releaseDate));

    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem *item = table->item(row, col);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }

    return repoData;
}

void MainWindow::createGitBadges(QString git_url, QWebEngineView *page)
{
    QString prefix = "https://github.com/";
    QString repo = git_url.replace(prefix, "");

    QString html = "<style>"
                   ".badge {"
                   "    height: 20px;"
                   "    margin: 1% 1%;"
                   "    border: 0px;"
                   "    border-radius: 5px;"
                   "}"
                   "</style>"
                   "<html>"
                   "    <body>"
                   "        <div style='align-items: center; justify-content: center; display: "
                   "flex; vertical-align: middle; flex-direction: column;'>";

    if (isCreated) {
        html += "            <img class='badge' src='https://img.shields.io/github/created-at/"
                + repo + "?style=for-the-badge&color=7dc4e4&logoColor=D9E0EE&labelColor=1c1c29' />";
    }
    if (isReleaseDate) {
        html += "            <img class='badge' src='https://img.shields.io/github/release-date/"
                + repo + "?style=for-the-badge&color=e0ea9d&logoColor=D9E0EE&labelColor=171b22' />";
    }
    if (isLastCommit) {
        html += "            <img class='badge' src='https://img.shields.io/github/last-commit/"
                + repo + "?style=for-the-badge&color=7dc4e4&logoColor=D9E0EE&labelColor=1c1c29'/>";
    }
    if (isPullReq) {
        html += "            <img class='badge' src='https://img.shields.io/github/issues-pr/"
                + repo + "?style=for-the-badge&color=ef9f9c&logoColor=85e185&labelColor=1c1c29' />";
    }
    if (isLicense) {
        html += "            <img class='badge' src='https://img.shields.io/github/license/" + repo
                + "?style=for-the-badge&color=a6e0b8&logoColor=ffffff&labelColor=1c1c29' />";
    }
    if (isRelease) {
        html += "            <img class='badge' src='https://img.shields.io/github/release/" + repo
                + "?style=for-the-badge&color=7589d5&logoColor=ffffff&labelColor=1c1c29'/>";
    }
    if (isIssue) {
        html += "            <img class='badge' src='https://img.shields.io/github/issues/" + repo
                + "?style=for-the-badge&color=dbb6ed&logoColor=ffffff&labelColor=1c1c29' />";
    }
    if (isDownloads) {
        html += "            <img class='badge' src='https://img.shields.io/github/downloads/"
                + repo
                + "/total?style=for-the-badge&color=e0ea9d&logoColor=D9E0EE&labelColor=1c1c29' />";
    }
    if (isCommit) {
        html += "            <img class='badge' "
                "src='https://img.shields.io/github/commit-activity/t/"
                + repo + "?style=for-the-badge&color=a6e0b8&logoColor=D9E0EE&labelColor=1c1c29' />";
    }
    if (isLang) {
        html += "            <img class='badge' src='https://img.shields.io/github/languages/count/"
                + repo + "?style=for-the-badge&color=ea9de7&logoColor=D9E0EE&labelColor=1c1c29' />";
    }
    if (isStars) {
        html += "            <img class='badge' src='https://img.shields.io/github/stars/" + repo
                + "?style=for-the-badge&color=eed49f&logoColor=D9E0EE&labelColor=1c1c29' />";
    }
    if (isForks) {
        html += "            <img class='badge' src='https://img.shields.io/github/forks/" + repo
                + "?style=for-the-badge&color=9dc3ea&logoColor=D9E0EE&labelColor=1c1c29' />";
    }
    if (isRepoSize) {
        html += "            <img class='badge' src='https://img.shields.io/github/repo-size/"
                + repo + "?style=for-the-badge&color=ea9de7&logoColor=D9E0EE&labelColor=171b22'/>";
    }

    html += "        </div>"
            "    </body>"
            "</html>";

    page->setHtml(html);
}

void MainWindow::openProject(QListWidget *listWidget, QListWidgetItem *item)
{
    if (item) {
        QDialog dialog(this);
        dialog.setFixedSize(400, 650);
        dialog.setWindowTitle(tr("Edit project"));
        dialog.setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

        QString data = item->text();
        QStringList splitData = data.split("\n");

        QString PTitle = splitData[0];
        QString PGit = splitData[1];
        QString PCreatedTime = splitData[2];
        QString PStatus = listWidget->objectName();

        QStringList projectData = GetProjectData(&PTitle, &PStatus, &PGit);
        qDebug() << "Open project: " << projectData[0] << " " << projectData[1]
                 << " " << projectData[2] << " " << projectData[3] << " " << projectData[4];

        QGridLayout mainLayout(&dialog);

        QLineEdit *title = new QLineEdit();
        title->setAlignment(Qt::AlignCenter);
        title->setPlaceholderText(" Project name: ");
        title->setStyleSheet("font-size: " + font_size + "pt;");
        title->setFixedHeight(25);
        title->setFont(selectedFont);

        QLineEdit *linkToGit = new QLineEdit();
        linkToGit->setAlignment(Qt::AlignCenter);
        linkToGit->setPlaceholderText(" Link to GIT");
        linkToGit->setStyleSheet("font-size: " + font_size + "pt;");
        linkToGit->setFixedHeight(25);
        linkToGit->setFont(selectedFont);

        QComboBox *documentation = new QComboBox();
        documentation->setFixedSize(190, 20);
        documentation->setFont(selectedFont);

        QLabel *lastMod = new QLabel();
        lastMod->setText("Last mod: ");
        lastMod->setStyleSheet("font-size: " + font_size + "pt;");
        lastMod->setFixedHeight(25);
        lastMod->setAlignment(Qt::AlignCenter);
        lastMod->setFont(selectedFont);

        QTableWidget *git_stats = new QTableWidget();
        git_stats->setFont(selectedFont);
        git_stats->setStyleSheet(
                "QTableWidget{ background-color: #0d1117; alternate-background-color: #171b22; "
                "selection-background-color: #336fc9; show-decoration-selected: 1; font-size: "
                + font_size + "pt; }");

        /*QWebEngineView *git_stats = new QWebEngineView();
        git_stats->page()->setBackgroundColor(Qt::transparent);
        createGitBadges(projectData[1], git_stats);*/

        QPushButton *saveDataBtn = new QPushButton();
        saveDataBtn->setText("Save");
        saveDataBtn->setStyleSheet("font-size: " + font_size + "pt;");
        saveDataBtn->setFixedSize(100, 25);
        saveDataBtn->setIcon(QPixmap(":/save.png"));
        saveDataBtn->setIconSize(QSize(10, 10));
        saveDataBtn->setFont(selectedFont);

        QPushButton *cancelBtn = new QPushButton();
        cancelBtn->setText("Cancel");
        cancelBtn->setStyleSheet("font-size: " + font_size + "pt;");
        cancelBtn->setFixedSize(100, 25);
        cancelBtn->setIcon(QPixmap(":/quit.png")
                                   .scaled(font_size.toInt() + 3, font_size.toInt() + 3,
                                           Qt::KeepAspectRatio, Qt::SmoothTransformation));
        cancelBtn->setIconSize(QSize(10, 10));
        cancelBtn->setFont(selectedFont);

        QPushButton *openButton = new QPushButton();
        openButton->setText("Open");
        openButton->setStyleSheet("font-size: " + font_size + "pt;");
        openButton->setFixedHeight(25);
        openButton->setIcon(QPixmap(":/read.png")
                                    .scaled(font_size.toInt() + 3, font_size.toInt() + 3,
                                            Qt::KeepAspectRatio, Qt::SmoothTransformation));
        openButton->setIconSize(QSize(10, 10));
        openButton->setFont(selectedFont);

        title->setText(projectData[0]);
        linkToGit->setText(projectData[1]);
        lastMod->setText("Last mod: " + projectData[4]);

        loadDocumentations(dir, *documentation);
        documentation->setCurrentText(projectData[2]);

        mainLayout.addWidget(title, 0, 0, 1, 2);
        mainLayout.addWidget(linkToGit, 1, 0, 1, 2);
        mainLayout.addWidget(documentation, 2, 0);
        mainLayout.addWidget(openButton, 2, 1);
        mainLayout.addWidget(git_stats, 4, 0, 1, 2);
        mainLayout.addWidget(lastMod, 7, 0, 1, 2);
        mainLayout.addWidget(saveDataBtn, 5, 0, 1, 2, Qt::AlignCenter);
        mainLayout.addWidget(cancelBtn, 6, 0, 1, 2, Qt::AlignCenter);

        QThread *thread = new QThread;
        QObject::connect(thread, &QThread::started, this, [this, projectData, git_stats]() {
            getRepositoryData(projectData[1], git_stats);
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

            updateProjectData(&projectTitle, &projectLink, &projectDocumentation,
                              &projectCreatedTime, &PCreatedTime, &PGit);

            dialog.close();
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

            // createGitBadges(repo, git_stats);

            QThread *thread = new QThread;
            QObject::connect(
                    thread, &QThread::started, this,
                    [this, projectData, repo, git_stats]() { getRepositoryData(repo, git_stats); });
            thread->start();
        });

        dialog.exec();
    } else {
        qWarning() << "Error";
    }
}

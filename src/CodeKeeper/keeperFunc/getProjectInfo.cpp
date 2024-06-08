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

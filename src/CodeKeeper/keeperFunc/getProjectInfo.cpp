QString formatFileSize(qint64 bytes)
{
    static const char *suffixes[] = {"KB", "MB", "GB", "TB", "PB", "..."};
    int index = 0;
    double size = bytes;

    while (size >= 1024 && index < 5)
    {
        size /= 1024;
        index++;
    }

    return QString::number(size, 'f', 2) + " " + suffixes[index];
}

QString MainWindow::getRepositoryData(QString git_url, QTableWidget *table, QLabel *label)
{
    QString prefix = "https://github.com/";
    QString repo = git_url.replace(prefix, "");
    QString repoData;

    QString name, description, createdAt, openIssues, forks, lang, stars, repoSize, license, totalDownloads, release,
        releaseDate, lastCommitS;

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
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error())
    {
        qWarning() << "Error:" << reply->errorString();
        reply->deleteLater();
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = doc.object();
    qDebug() << doc;

    name = obj["name"].toString();

    description = obj["description"].toString();

    createdAt = obj["created_at"].toString();
    QDateTime createdDate = QDateTime::fromString(createdAt, Qt::ISODate);
    createdAt = createdDate.toString("dd MMM yyyy hh:mm");

    openIssues = QString::number(obj["open_issues"].toInt());

    forks = QString::number(obj["forks"].toInt());

    stars = QString::number(obj["stargazers_count"].toInt());

    qint64 size = obj["size"].toDouble();
    repoSize = formatFileSize(size);

    if (obj.contains("license"))
    {
        QJsonObject licenseObj = obj["license"].toObject();
        if (licenseObj.contains("name"))
        {
            license = licenseObj["name"].toString() + " ";
        }
        else
        {
            qDebug() << "License not found";
        }
    }
    else
    {
        qDebug() << "License not found";
    }

    QUrl commitUrl("https://api.github.com/repos/" + repo + "/commits");
    commitUrl.setQuery(query);

    QNetworkRequest commitUrlRequest(commitUrl);
    commitUrlRequest.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    commitUrlRequest.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    commitUrlRequest.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    commitUrlRequest.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *commitReply = manager->get(commitUrlRequest);
    QObject::connect(commitReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (commitReply->error())
    {
        qWarning() << "Error:" << commitReply->errorString();
        commitReply->deleteLater();
    }

    QJsonDocument commitDoc = QJsonDocument::fromJson(commitReply->readAll());
    QJsonObject commitObj = commitDoc.object();
    QJsonArray commits = commitDoc.array();
    qDebug() << commitDoc;

    if (commits.isEmpty())
    {
        qDebug() << "No commits found";
    }

    QJsonObject lastCommit = commits.first().toObject();
    QString dateStr = lastCommit["commit"].toObject()["author"].toObject()["date"].toString();

    QDateTime lastCommitDate = QDateTime::fromString(dateStr, Qt::ISODate);

    lastCommitS = lastCommitDate.toString("dd MMM yyyy hh:mm");

    QUrl releaseUrl("https://api.github.com/repos/" + repo + "/releases");
    releaseUrl.setQuery(query);

    QNetworkRequest releaseUrlRequest(releaseUrl);
    releaseUrlRequest.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    releaseUrlRequest.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    releaseUrlRequest.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    releaseUrlRequest.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *releaseReply = manager->get(releaseUrlRequest);
    QObject::connect(releaseReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (releaseReply->error())
    {
        qWarning() << "Error:" << releaseReply->errorString();
        releaseReply->deleteLater();
    }

    QJsonDocument releaseDoc = QJsonDocument::fromJson(releaseReply->readAll());
    QJsonArray releases = releaseDoc.array();
    qDebug() << releaseDoc;

    int iTotalDownloads = 0;
    for (const QJsonValue &release : releases)
    {
        QJsonObject releaseObj = release.toObject();
        int downloads = releaseObj["assets"].toArray().at(0).toObject()["download_count"].toInt();
        iTotalDownloads += downloads;
    }

    totalDownloads = QString::number(iTotalDownloads);

    // Release info
    QUrl releasesUrl("https://api.github.com/repos/" + repo + "/releases/latest");
    releasesUrl.setQuery(query);

    QNetworkRequest releasesRequest(releasesUrl);
    releasesRequest.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    releasesRequest.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    releasesRequest.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    releasesRequest.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *releasesReply = manager->get(releasesRequest);
    QObject::connect(releasesReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (releasesReply->error())
    {
        qWarning() << "Error:" << releasesReply->errorString();
        releasesReply->deleteLater();
    }

    QJsonDocument releasesDoc = QJsonDocument::fromJson(releasesReply->readAll());
    QJsonObject releasesObj = releasesDoc.object();
    qDebug() << releasesDoc;

    release = releasesObj["name"].toString();

    dateStr = releasesObj["published_at"].toString();

    QDateTime releaseDateT = QDateTime::fromString(dateStr, Qt::ISODate);
    releaseDate = releaseDateT.toString("dd MMM yyyy hh:mm");

    releasesReply->deleteLater();
    reply->deleteLater();

    // get repo langs
    QUrl langUrl("https://api.github.com/repos/" + repo + "/languages");
    langUrl.setQuery(query);

    QNetworkRequest langRequest(langUrl);
    langRequest.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    langRequest.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    langRequest.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    langRequest.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *langReply = manager->get(langRequest);
    QObject::connect(langReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (langReply->error())
    {
        qWarning() << "Error:" << langReply->errorString();
        langReply->deleteLater();
    }

    QJsonDocument langDoc = QJsonDocument::fromJson(langReply->readAll());
    QJsonObject langObj = langDoc.object();
    qDebug() << langDoc;

    QString languages;
    for (const QString &lang : langObj.keys())
    {
        if (!languages.isEmpty())
        {
            languages += ", ";
        }
        languages += lang;
    }
    // working on table

    table->setRowCount(12);
    table->setColumnCount(2);
    table->setShowGrid(false);

    table->setColumnWidth(0, 255);
    table->setColumnWidth(1, 255);

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
    table->item(0, 0)->setTextAlignment(Qt::AlignCenter);
    table->item(0, 1)->setTextAlignment(Qt::AlignCenter);

    QStringList dataList, textList;

    dataList << name;
    textList << tr("Repo");

    if (isCreated)
    {
        textList << tr("Created at");
        dataList << createdAt;
    }

    if (isIssue)
    {
        dataList << openIssues;
        textList << tr("Open issues");
    }

    if (isForks)
    {
        dataList << forks;
        textList << tr("Forks");
    }

    if (isLang)
    {
        dataList << languages;
        textList << tr("Lang");
    }

    if (isStars)
    {
        dataList << stars;
        textList << tr("Stars");
    }

    if (isRepoSize)
    {
        dataList << repoSize;
        textList << tr("Repo size");
    }

    if (isLicense)
    {
        dataList << license;
        textList << tr("License");
    }

    if (isLastCommit)
    {
        dataList << lastCommitS;
        textList << tr("Last commit");
    }

    if (isDownloads)
    {
        dataList << totalDownloads;
        textList << tr("Downloads");
    }

    if (isRelease)
    {
        dataList << release;
        textList << tr("Release");
    }

    if (isReleaseDate)
    {
        dataList << releaseDate;
        textList << tr("Release at");
    }

    description = description.left(30) + "...";
    label->setText(name + " - " + description);

    for (int i = 0; i < dataList.count(); i++)
    {
        table->setItem(i, 0, new QTableWidgetItem(textList[i]));
        table->setItem(i, 1, new QTableWidgetItem(dataList[i]));
        table->item(i, 0)->setTextAlignment(Qt::AlignCenter);
    }

    for (int row = 0; row < table->rowCount(); ++row)
    {
        for (int col = 0; col < table->columnCount(); ++col)
        {
            QTableWidgetItem *item = table->item(row, col);
            if (item)
            {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }

    return repoData;
}

QString MainWindow::getProjectIssues(QString git_url)
{
    int maxLength = 150;
    QString prefix = "https://github.com/";
    QString repo = git_url.replace(prefix, "");
    QString issuesData = "<html style='display: flex; align-items: center; "
                         "flex-direction: column; "
                         "vertical-align: middle; justify-content: center;'>";

    QUrl url("https://api.github.com/repos/" + repo + "/issues");
    QNetworkRequest request(url);

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);

    request.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    request.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    request.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(data);
        QJsonArray issues = json.array();

        qDebug() << json;

        foreach (const QJsonValue &issue, issues)
        {
            QJsonObject issueObject = issue.toObject();
            QString title = issueObject["title"].toString();
            QString body = issueObject["body"].toString();
            QString creator = issueObject["user"].toObject()["login"].toString();
            QString creatorUrl = issueObject["user"].toObject()["html_url"].toString();
            QString shortBody = body.left(maxLength);
            QString link = issueObject["html_url"].toString();

            QString dateStr = issueObject["created_at"].toString();
            QDateTime createDate = QDateTime::fromString(dateStr, Qt::ISODate);
            QString date = createDate.toString("dd MMM yyyy hh:mm");

            issuesData += "<div align='center' style='content'><h2 "
                          "align='center'> - "
                          "</h2><h2>" +
                          title +
                          "</h2><br><a style='color: #84a0bf; "
                          "text-decoration: "
                          "none;' href=\"" +
                          creatorUrl + "\">Created by " + creator + " </a>at " + date + "<br><br>" + shortBody +
                          "<br><br><a style='color: #84a0bf; "
                          "text-decoration: none;' "
                          "href=\"" +
                          link + "\">Open</a><br></div>";
        }
    }
    else
    {
        qWarning() << "Error: " << reply->errorString();
    }
    reply->deleteLater();

    issuesData += "</html>";

    qDebug() << issuesData;
    return issuesData;
}

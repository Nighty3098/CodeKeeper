#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QLabel>

#include "mainwindow.h"

void AccountWindow::setImageFromUrl(const QString &url, QLabel *label)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error()) {
            qWarning() << "Error:" << reply->errorString();
            reply->deleteLater();
            return;
        }

        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());

        label->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        label->setStyleSheet("border-radius: 150px;");

        reply->deleteLater();
    });
}

void AccountWindow::closeWindowSlot()
{
    this->close();
}

void AccountWindow::getSettingsData()
{
    selectedFont = globalSettings->value("font").value<QFont>();
    font_size = globalSettings->value("fontSize").value<QString>();
    theme = globalSettings->value("theme").value<QString>();
    path = globalSettings->value("path").value<QString>();

    git_repo = globalSettings->value("git_repo").value<QString>();
    git_user = globalSettings->value("git_user").value<QString>();
    git_token = globalSettings->value("git_token").value<QString>();

    isAutoSyncB = globalSettings->value("isAutoSync").value<bool>();
}

void AccountWindow::setFontStyle()
{
    userName->setFont(selectedFont);

    profilePicture->setFont(selectedFont);
    profilePicture->setStyleSheet("font-size: " + font_size + "pt;");

    openRepo->setFont(selectedFont);
    openRepo->setStyleSheet("font-size: " + font_size + "pt;");

    codeKeeperStats->setFont(selectedFont);
    codeKeeperStats->setStyleSheet("font-size: " + font_size + "pt;");

    profileInfo->setFont(selectedFont);
    profileInfo->setStyleSheet("font-size: " + font_size + "pt;");

    closeWindow->setStyleSheet("QPushButton {"
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
}

int AccountWindow::getStarsCount(const QString &username)
{
    QNetworkAccessManager manager;
    QUrl url("https://api.github.com/users/" + username + "/repos");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    request.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    request.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error()) {
        qDebug() << "Error:" << reply->errorString();
        return 0;
    }

    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray repos = json.array();

    int totalStars = 0;
    for (const QJsonValue &repo : repos) {
        QJsonObject repoObject = repo.toObject();
        QString repoUrl = repoObject["url"].toString();

        QNetworkRequest repoRequest(repoUrl);
        repoRequest.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
        repoRequest.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
        repoRequest.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
        repoRequest.setRawHeader("Accept", "application/vnd.github.v3+json");
        ;

        QNetworkReply *repoReply = manager.get(repoRequest);
        QEventLoop repoLoop;
        QObject::connect(repoReply, &QNetworkReply::finished, &repoLoop, &QEventLoop::quit);
        repoLoop.exec();

        if (repoReply->error()) {
            qDebug() << "Error:" << repoReply->errorString();
            continue;
        }

        QJsonDocument repoJson = QJsonDocument::fromJson(repoReply->readAll());
        QJsonObject repoJsonObject = repoJson.object();
        int stars = repoJsonObject["stargazers_count"].toInt();

        totalStars += stars;
    }

    return totalStars;
}

void AccountWindow::setUserData(const QString &username, QLabel *label)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://api.github.com/users/" + git_user);

    QUrlQuery query;
    query.addQueryItem("login", username);
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    request.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    request.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error()) {
            qWarning() << "Error:" << reply->errorString();
            reply->deleteLater();
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();

        // do something with the user data
        qDebug() << "Name:" << obj["name"].toString();
        qDebug() << "Location:" << obj["location"].toString();
        qDebug() << "Avatar_url:" << obj["avatar_url"].toString();
        qDebug() << "Html_url:" << obj["html_url"].toString();
        qDebug() << "Created_at:" << obj["created_at"].toString();
        qDebug() << "Updated_at:" << obj["updated_at"].toString();
        qDebug() << "Following:" << obj["following"].toInt();
        qDebug() << "Followers:" << obj["followers"].toInt();
        qDebug() << "Public_repos:" << obj["public_repos"].toInt();
        qDebug() << "Bio:" << obj["bio"].toString();
        qDebug() << "Company:" << obj["company"].toString();
        qDebug() << "Login:" << obj["login"].toString();

        qDebug() << "" << doc;

        profileInfo->setText("\n\n" + obj["bio"].toString() + "\nPublic repos: "
                             + QString::number(obj["public_repos"].toInt()) + "\n\nFollowing: "
                             + QString::number(obj["following"].toInt()) + "\n\nFollowers: "
                             + QString::number(obj["followers"].toInt()) + "\n\nStars: "
                             + QString::number(getStarsCount(git_user)) + "\n");

        setImageFromUrl(obj["avatar_url"].toString(), profilePicture);
        reply->deleteLater();
    });
}

void AccountWindow::onOpenRepoClicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/" + git_user + "/"));
}

void AccountWindow::setTasksProgress() {
    MainWindow *mainWindow = qobject_cast<MainWindow *>(this->parent());
    QString stats = mainWindow->getKeeperStats();

    int incompleteTasksCount = mainWindow->incompleteTasks->count();
    int completeTasksCount = mainWindow->completeTasks->count();
    int inprocessTasksCount = mainWindow->inprocessTasks->count();

    int totalTasks = incompleteTasksCount + completeTasksCount + inprocessTasksCount;

    double percentage = static_cast<double>(completeTasksCount) / static_cast<double>(totalTasks) * 100.0;

    qDebug() << completeTasksCount << "/" << totalTasks;

    tasksStatsProgress->setMaximum(100);
    tasksStatsProgress->setValue(percentage);
    tasksStatsProgress->setFormat("Completed tasks: " + QString::number(completeTasksCount) + "/" + QString::number(totalTasks));
}
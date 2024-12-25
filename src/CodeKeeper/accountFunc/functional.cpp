#include <QEventLoop>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPainter>
#include <QPixmap>
#include <QStringList>
#include <algorithm>

#include "custom/ColorValueDisplay/ColorValueDisplay.h"
#include "custom/circleChart/CircleChart.h"
#include "custom/circleProgressbar/ProgressCircle.h"

#include "accountwindow.h"
#include "mainwindow.h"

QStringList AccountWindow::getAllGitReposUrls(const QString &username)
{
    QStringList repoUrls;

    QNetworkAccessManager manager;

    QString reposUrl = QString("https://api.github.com/users/%1/repos").arg(username);
    QString eventsUrl = QString("https://api.github.com/users/%1/events").arg(username);

    auto fetchUrls = [&](const QString &url) {
        QNetworkRequest request;
        request.setUrl(QUrl(url));

        request.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
        request.setRawHeader("Accept", "application/vnd.github.v3+json");

        QUrlQuery query;
        query.addQueryItem("login", git_user);
        request.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());

        QNetworkReply *reply = manager.get(request);
        QEventLoop eventLoop;
        QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
        eventLoop.exec();

        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (jsonDoc.isArray())
            {
                QJsonArray jsonArray = jsonDoc.array();
                for (const QJsonValue &value : jsonArray)
                {
                    QString repoUrl;
                    if (url == reposUrl)
                    {
                        repoUrl = value.toObject().value("html_url").toString();
                    }
                    else
                    {
                        QJsonObject repoObject = value.toObject().value("repo").toObject();
                        repoUrl = repoObject.value("html_url").toString();
                    }
                    if (!repoUrl.isEmpty() && !repoUrls.contains(repoUrl))
                    {
                        repoUrls.append(repoUrl);
                    }
                }
            }
        }
        else
        {
            qWarning() << "Error fetching data:" << reply->errorString();
        }

        reply->deleteLater();
    };

    fetchUrls(reposUrl);
    fetchUrls(eventsUrl);

    qDebug() << "User repos: " << repoUrls;

    return repoUrls;
}

float AccountWindow::calculatePercentage(int count, int total)
{
    return total > 0 ? static_cast<float>(count) / total * 100.0f : 0.0f;
}

void AccountWindow::setImageFromUrl(const QString &url, QLabel *label)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error())
        {
            qWarning() << "Error:" << reply->errorString();
            reply->deleteLater();
            return;
        }

        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());

        QImage image = pixmap.toImage();
        QImage roundedImage(image.size(), QImage::Format_ARGB32);
        roundedImage.fill(Qt::transparent);

        QPainter painter(&roundedImage);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(image));
        painter.setPen(Qt::NoPen);

        int radius = qMin(roundedImage.width(), roundedImage.height());
        painter.drawRoundedRect(0, 0, roundedImage.width(), roundedImage.height(), radius * 0.5, radius * 0.5);

        label->setPixmap(
            QPixmap::fromImage(roundedImage.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

        reply->deleteLater();
    });
}

void AccountWindow::get_image_url(const QString &username, QLabel *label)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://api.github.com/users/" + username);

    QUrlQuery query;
    query.addQueryItem("login", username);
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    request.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    request.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError error) {
        qWarning() << "Network error occurred:" << error;
        qWarning() << "Error string:" << reply->errorString();
        reply->deleteLater();
    });

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error())
        {
            qWarning() << "Error:" << reply->errorString();
            reply->deleteLater();
            return;
        }

        if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200)
        {
            qWarning() << "HTTP error:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            reply->deleteLater();
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();

        qDebug() << "Avatar URL:" << obj["avatar_url"].toString();

        setImageFromUrl(obj["avatar_url"].toString(), label);

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
    theme = globalSettings->value("theme").value<int>();
    path = globalSettings->value("path").value<QString>();

    git_repo = globalSettings->value("git_repo").value<QString>();
    git_user = globalSettings->value("git_user").value<QString>();
    git_token = globalSettings->value("git_token").value<QString>();

    isAutoSyncB = globalSettings->value("isAutoSync").value<bool>();
    isCustomTheme = globalSettings->value("isCustomTheme").value<bool>();
}

int AccountWindow::getStarsCount(const QString &username, const QString &token)
{
    QNetworkAccessManager manager;
    QUrl url("https://api.github.com/users/" + username + "/repos");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    int totalStars = 0;
    if (!reply->error())
    {
        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
        QJsonArray repos = json.array();

        for (const QJsonValue &repo : repos)
        {
            QJsonObject repoObject = repo.toObject();
            totalStars += repoObject["stargazers_count"].toInt();
        }
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }

    reply->deleteLater();
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
        if (reply->error())
        {
            qWarning() << "Error:" << reply->errorString();
            reply->deleteLater();
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();

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

        label->setText(tr("\n\nPublic repos: ") + QString::number(obj["public_repos"].toInt()) +
                       tr("  |  Following: ") + QString::number(obj["following"].toInt()) + tr("  |  Followers: ") +
                       QString::number(obj["followers"].toInt()) + tr("  |  Stars: ") +
                       QString::number(getStarsCount(git_user, git_token)) + "");

        reply->deleteLater();
    });
}

void AccountWindow::onOpenRepoClicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/" + git_user + "/"));
}

void AccountWindow::setTasksProgress()
{
    MainWindow *mainWindow = qobject_cast<MainWindow *>(this->parent());

    int incompleteTasksCount = mainWindow->incompleteTasks->count();
    int completeTasksCount = mainWindow->completeTasks->count();
    int inprocessTasksCount = mainWindow->inprocessTasks->count();

    int totalTasks = incompleteTasksCount + completeTasksCount + inprocessTasksCount;

    if (totalTasks <= 0)
    {
        tasksStatsProgress->hide();
        tasksStatsProgress->setFixedSize(0, 0);
        tasksTitle->setText(tr("No tasks found"));
        return;
    }

    double percentage = calculatePercentage(completeTasksCount, totalTasks);
    qDebug() << completeTasksCount << "/" << totalTasks;

    tasksStatsProgress->setValue(percentage);
    tasksStatsProgress->setMaxValue(100);

    double percentages[] = {calculatePercentage(completeTasksCount, totalTasks),
                            calculatePercentage(inprocessTasksCount, totalTasks),
                            calculatePercentage(incompleteTasksCount, totalTasks)};

    QString labels[] = {tr("Completed"), tr("Started"), tr("Not Started")};
    QColor colors[] = {QColor("#85b9b3"), QColor("#a9bf85"), QColor("#e08581")};

    for (int i = 0; i < 3; ++i)
    {
        tasksChartValuesDisplay->addValue(labels[i], percentages[i], colors[i], selectedFont);
    }

    QColor progressColor;
    if (percentage < 26)
    {
        progressColor = QColor("#e08581");
    }
    else if (percentage < 51)
    {
        progressColor = QColor("#d8bd85");
    }
    else
    {
        progressColor = QColor("#85b9b3");
    }
    tasksStatsProgress->setProgressColor(progressColor);
}

void AccountWindow::setProjectsStats()
{
    MainWindow *mainWindow = qobject_cast<MainWindow *>(this->parent());

    int notStartedProjectsCount = mainWindow->notStartedProjects->count();
    int startedProjectsCount = mainWindow->startedProjects->count();
    int finishlineProjectsCount = mainWindow->finishedProjects->count();
    int finishedProjectsCount = mainWindow->finishlineProjects->count();

    int totalProjects =
        notStartedProjectsCount + startedProjectsCount + finishlineProjectsCount + finishedProjectsCount;

    if (totalProjects == 0)
    {
        projectsChart->hide();
        projectsChart->setFixedSize(0, 0);
        projectTitle->setText("\n\nNo projects found");
        return;
    }

    float ns_p = calculatePercentage(notStartedProjectsCount, totalProjects);
    float s_p = calculatePercentage(startedProjectsCount, totalProjects);
    float fl_p = calculatePercentage(finishlineProjectsCount, totalProjects);
    float f_p = calculatePercentage(finishedProjectsCount, totalProjects);

    qDebug() << "Projects: " << ns_p << " " << s_p << " " << fl_p << " " << f_p << " " << totalProjects;

    projectsChart->setMaximumValue(100);

    float values[] = {ns_p, s_p, fl_p, f_p};
    QString labels[] = {tr("Not started"), tr("In Dev"), tr("On Review"), tr("Finished")};
    QColor colors[] = {QColor("#e08581"), QColor("#d8bd85"), QColor("#a9bf85"), QColor("#85b9b3")};

    for (int i = 0; i < 4; ++i)
    {
        projectsChart->addValue(values[i], colors[i]);
        chartValuesDisplay->addValue(labels[i], values[i], colors[i], selectedFont);
    }
}

void AccountWindow::setFontStyle()
{
    userName->setFont(selectedFont);

    chartValuesDisplay->setFont(selectedFont);
    chartValuesDisplay->setStyleSheet("font-size: " + font_size + "px;");

    tasksChartValuesDisplay->setFont(selectedFont);
    tasksChartValuesDisplay->setStyleSheet("font-size: " + font_size + "px;");

    tasksTitle->setFont(selectedFont);
    tasksTitle->setStyleSheet("background: transparent; font-size: " + font_size + "px;");

    projectTitle->setFont(selectedFont);
    projectTitle->setStyleSheet("background: transparent; font-size: " + font_size + "px;");

    userName->setStyleSheet("font-size: 36pt;");

    profilePicture->setFont(selectedFont);
    profilePicture->setStyleSheet("font-size: " + font_size + "px;");

    openRepo->setFont(selectedFont);
    openRepo->setStyleSheet("font-size: " + font_size + "px;");

    profileInfo->setFont(selectedFont);
    profileInfo->setStyleSheet("font-size: " + font_size + "px;");

    tasksStatsProgress->setFont(selectedFont);
    tasksStatsProgress->setStyleSheet("font-size: " + font_size + "px;");
}

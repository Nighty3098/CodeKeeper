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

#include "mainwindow.h"

QString AccountWindow::getLangByRepo(const QStringList &repoUrls)
{
    QMap<QString, int> languageCounts; // Хранит количество байт для каждого языка
    int totalBytes = 0;                // Общее количество байт

    QNetworkAccessManager manager;

    for (const QString &repoUrl : repoUrls)
    {
        // Удаляем префикс "https://github.com/"
        QString apiUrl = repoUrl;
        apiUrl.remove("https://github.com/");            // Удаляем префикс
        apiUrl.prepend("https://api.github.com/repos/"); // Добавляем префикс для API

        apiUrl += "/languages";                // Формируем URL для API
        QNetworkRequest request{QUrl(apiUrl)}; // Создаем запрос

        // Устанавливаем заголовки
        request.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
        request.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
        request.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
        request.setRawHeader("Accept", "application/vnd.github.v3+json");

        QNetworkReply *reply = manager.get(request);

        // Ожидаем завершения запроса
        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray response = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response);
            QJsonObject obj = doc.object();

            // Подсчитываем языки и их объем
            for (const QString &lang : obj.keys())
            {
                if (lang != "documentation_url" && lang != "message" && lang != "url")
                { // Игнорируем ненужные ключи
                    int bytes = obj.value(lang).toInt();
                    languageCounts[lang] += bytes;
                    totalBytes += bytes;
                }
            }
        }
        else
        {
            qDebug() << "Ошибка при запросе:" << reply->errorString();
        }
        reply->deleteLater();
    }

    // Формируем вектор для сортировки
    QVector<QPair<QString, double>> languagePercentages;
    for (const QString &lang : languageCounts.keys())
    {
        double percentage = (static_cast<double>(languageCounts[lang]) / totalBytes) * 100;
        languagePercentages.append(qMakePair(lang, percentage));
    }

    // Сортируем по процентам в порядке убывания
    std::sort(languagePercentages.begin(), languagePercentages.end(),
              [](const QPair<QString, double> &a, const QPair<QString, double> &b) {
                  return a.second > b.second; // Сортировка по убыванию
              });

    // Формируем строку с первыми 5 языками
    QString result;
    for (int i = 0; i < std::min(4, languagePercentages.size()); ++i)
    {
        result += QString("%1 %2 ")
                      .arg(languagePercentages[i].first)
                      .arg(QString::number(languagePercentages[i].second, 'f', 2));
    }

    return result.trimmed(); // Убираем лишние пробелы и символы новой строки
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

        qDebug() << obj["avatar_url"].toString();

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

    chartValuesDisplay->setFont(selectedFont);
    chartValuesDisplay->setStyleSheet("font-size: " + font_size + "pt;");

    tasksChartValuesDisplay->setFont(selectedFont);
    tasksChartValuesDisplay->setStyleSheet("font-size: " + font_size + "pt;");

    langsValuesDisplay->setFont(selectedFont);
    langsValuesDisplay->setStyleSheet("font-size: " + font_size + "pt;");

    langsTitle->setFont(selectedFont);
    langsTitle->setStyleSheet("background: transparent; font-size: " + font_size + "px;");

    tasksTitle->setFont(selectedFont);
    tasksTitle->setStyleSheet("background: transparent; font-size: " + font_size + "px;");

    projectTitle->setFont(selectedFont);
    projectTitle->setStyleSheet("background: transparent; font-size: " + font_size + "px;");

    userName->setStyleSheet("font-size: 36pt;");

    profilePicture->setFont(selectedFont);
    profilePicture->setStyleSheet("font-size: " + font_size + "pt;");

    openRepo->setFont(selectedFont);
    openRepo->setStyleSheet("font-size: " + font_size + "pt;");

    profileInfo->setFont(selectedFont);
    profileInfo->setStyleSheet("font-size: " + font_size + "pt;");

    tasksStatsProgress->setFont(selectedFont);
    tasksStatsProgress->setStyleSheet("font-size: " + font_size + "pt;");

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

        label->setText("\n\n" + obj["bio"].toString() + tr("\nPublic repos: ") +
                       QString::number(obj["public_repos"].toInt()) + tr("\n\nFollowing: ") +
                       QString::number(obj["following"].toInt()) + tr("\n\nFollowers: ") +
                       QString::number(obj["followers"].toInt()) + tr("\n\nStars: ") +
                       QString::number(getStarsCount(git_user, git_token)) + "\n");

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

    double percentage = static_cast<double>(completeTasksCount) / static_cast<double>(totalTasks) * 100.0;

    double complete_percentage = static_cast<double>(completeTasksCount) / static_cast<double>(totalTasks) * 100.0;
    double started_percentage = static_cast<double>(inprocessTasksCount) / static_cast<double>(totalTasks) * 100.0;
    double ns_percentage = static_cast<double>(incompleteTasksCount) / static_cast<double>(totalTasks) * 100.0;

    qDebug() << completeTasksCount << "/" << totalTasks;

    tasksStatsProgress->setValue(percentage);
    tasksStatsProgress->setMaxValue(100);

    tasksChartValuesDisplay->addValue(tr("Completed"), complete_percentage, QColor("#78b3ba"), selectedFont);
    tasksChartValuesDisplay->addValue(tr("Started"), started_percentage, QColor("#b1e032"), selectedFont);
    tasksChartValuesDisplay->addValue(tr("Not Started"), ns_percentage, QColor("#c75d5e"), selectedFont);

    if (percentage < 101)
    {
        tasksStatsProgress->setProgressColor(QColor("#78b3ba"));
    }

    if (percentage < 51)
    {
        tasksStatsProgress->setProgressColor(QColor("#e09132"));
    }

    if (percentage < 26)
    {
        tasksStatsProgress->setProgressColor(QColor("#c75d5e"));
    }
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

    float ns_p = static_cast<double>(notStartedProjectsCount) / static_cast<double>(totalProjects) * 100.0;
    float s_p = static_cast<double>(startedProjectsCount) / static_cast<double>(totalProjects) * 100.0;
    float fl_p = static_cast<double>(finishlineProjectsCount) / static_cast<double>(totalProjects) * 100.0;
    float f_p = static_cast<double>(finishedProjectsCount) / static_cast<double>(totalProjects) * 100.0;

    projectsChart->setMaximumValue(100);

    projectsChart->addValue(ns_p, QColor("#c75d5e"));
    projectsChart->addValue(s_p, QColor("#e09132"));
    projectsChart->addValue(fl_p, QColor("#b1e032"));
    projectsChart->addValue(f_p, QColor("#78b3ba"));

    chartValuesDisplay->addValue(tr("Not started"), ns_p, QColor("#c75d5e"), selectedFont);
    chartValuesDisplay->addValue(tr("In Dev"), s_p, QColor("#e09132"), selectedFont);
    chartValuesDisplay->addValue(tr("On Review"), fl_p, QColor("#b1e032"), selectedFont);
    chartValuesDisplay->addValue(tr("Finished"), f_p, QColor("#78b3ba"), selectedFont);
}

void AccountWindow::setLangsStats(const QString langsData)
{
    QStringList langsColors;
    langsColors << "#c75d5e" << "#e09132" << "#b1e032" << "#78b3ba"
                << "#5dc7c3" << "#c75da9" << "#c7c25d" << "#875dc7";

    QStringList result = langsData.split(' ');
    int count = result.size() / 2;
    qDebug() << count;

    langsChart->setMaximumValue(100);
    double other = 100;

    for (int i = 0; i < count; i++)
    {
        int value = static_cast<int>(std::round(result[i * 2 + 1].toDouble()));
        other = other - value;

        qDebug() << result[i * 2] << " " << value;
        langsChart->addValue(result[i * 2 + 1].toDouble(), langsColors[i]);
        langsValuesDisplay->addValue(result[i * 2], value, langsColors[i], selectedFont);
    }

    langsChart->addValue(other, QColor("#333333"));
    langsValuesDisplay->addValue("Other", other, "#333333", selectedFont);
}

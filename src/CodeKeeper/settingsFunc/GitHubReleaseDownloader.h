#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QTimer>

void downloadFileFromLatestRelease(const QString &owner, const QString &repo,
                                   const QString &fileName, QLabel *label, QString git_user,
                                   QString git_token)
{
    QString savePath = QCoreApplication::applicationDirPath() + "/CodeKeeper";
    QString browserDownloadUrl;

    QString oldFilePath = QCoreApplication::applicationDirPath() + "/CodeKeeper";
    QString newFilePath = QCoreApplication::applicationDirPath() + "/CodeKeeper.old";

    if (QFile::exists(oldFilePath)) {
        if (QFile::rename(oldFilePath, newFilePath)) {
            qDebug() << "File renamed successfully";
        } else {
            qDebug() << "Error when renaming a file";
        }
    } else {
        qDebug() << "The file doesn't exist";
    }

    qDebug() << savePath;

    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.github.com/repos/Nighty3098/CodeKeeper/releases/latest"));
    request.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    request.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    request.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        label->setText("Error fetching release information:" + reply->errorString());
        qDebug() << "Error fetching release information:" << reply->errorString();
        delete reply;
    }

    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObject = json.object();

    QJsonArray assets = jsonObject["assets"].toArray();
    foreach (const QJsonValue &asset, assets) {
        QJsonObject assetObject = asset.toObject();
        browserDownloadUrl = assetObject["browser_download_url"].toString();
        // Use the browser_download_url here
        label->setText("Browser download URL:" + browserDownloadUrl);
        qDebug() << "Browser download URL:" << browserDownloadUrl;
    }

    delete reply;

    QNetworkRequest downloadRequest;
    downloadRequest.setUrl(QUrl(browserDownloadUrl));

    QNetworkReply *downloadReply = manager.get(downloadRequest);

    QObject::connect(downloadReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (downloadReply->error() != QNetworkReply::NoError) {
        label->setText("File download error:" + downloadReply->errorString());
        qDebug() << "File download error:" << downloadReply->errorString();
        delete downloadReply;
    }

    QFile file(savePath);
    if (!file.open(QFile::WriteOnly)) {
        label->setText("Error opening a file for writing:" + file.errorString());
        qDebug() << "Error opening a file for writing:" << file.errorString();
        delete downloadReply;
    }

    file.write(downloadReply->readAll());
    file.close();

    delete downloadReply;
    label->setText("The file has been downloaded and saved to: " + savePath);
    qDebug() << "The file has been downloaded and saved to: " << savePath;
}
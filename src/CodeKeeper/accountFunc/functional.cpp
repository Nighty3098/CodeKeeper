#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QLabel>

void AccountWindow::setImageFromUrl(const QString& url, QLabel* label) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
            reply->deleteLater();
            return;
        }

        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());

        label->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));

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

    profilePicture->setFont(selectedFont);
    profilePicture->setStyleSheet("font-size: " + font_size + "pt;");

    profileName->setFont(selectedFont);
    profileName->setStyleSheet("font-size: " + font_size + "pt;");
}

void AccountWindow::setUserData(const QString& username, QLabel* label) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://api.github.com/users/" + git_user);

    QUrlQuery query;
    query.addQueryItem("login", username);
    url.setQuery(query);

    QNetworkReply *reply = manager->get(QNetworkRequest(url));
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
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
        qDebug() << "Following:" << obj["following"].toString();
        qDebug() << "Followers:" << obj["followers"].toString();
        qDebug() << "Public_repos:" << obj["public_repos"].toString();
        qDebug() << "Bio:" << obj["bio"].toString();
        qDebug() << "Company:" << obj["company"].toString();
        qDebug() << "Login:" << obj["login"].toString();

        profileName->setText(obj["name"].toString() + "\n\n" + obj["company"].toString() + "\n\n" + obj["bio"].toString());

        setImageFromUrl(obj["avatar_url"].toString(), profilePicture);
        reply->deleteLater();
    });
}
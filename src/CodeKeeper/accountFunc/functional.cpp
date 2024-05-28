#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QLabel>

void AccountWindow::closeWindowSlot() {
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

void AccountWindow::setFontStyle() {

    profilePicture->setFont(selectedFont);
    profilePicture->setStyleSheet("font-size: " + font_size + "pt;");
    
    profileName->setFont(selectedFont);
    profileName->setStyleSheet("font-size: " + font_size + "pt;");
}

void AccountWindow::setGithubAvatar(const QString &username, QLabel *label) {
    
}
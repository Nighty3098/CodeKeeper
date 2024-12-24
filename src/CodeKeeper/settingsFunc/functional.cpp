#include <QNetworkAccessManager>

#include "mainwindow.h"
#include "settingsFunc/GitHubReleaseDownloader.h"
#include "settingswindow.h"
#include <QPixmap>
#include <QColor>

QPixmap SettingsWindow::changeIconColor(QPixmap pixmap) {
    QColor color;

    if (isCustomTheme) {
        if (theme == 0) { // custom dark
            color = QColor("#c3e88d");
        } else if (theme == 1) { // solarized
            color = QColor("#728905");
        } else if (theme == 2) { // mac dark
            color = QColor("#ffffff");
        }
    } else {
        color = QColor("#ffffff");
    }

    QPixmap coloredPixmap = pixmap; 
    QPainter painter(&coloredPixmap);

    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(coloredPixmap.rect(), color);
    painter.end();
    
    return coloredPixmap;
}


void SettingsWindow::QuitW()
{
    this->close();
}

QString SettingsWindow::fetchSecondLastRelease()
{
    QString version;

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://api.github.com/repos/Nighty3098/CodeKeeper/releases");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "CodeKeeper");
    request.setRawHeader("Authorization", ("Bearer " + git_token).toUtf8());
    request.setRawHeader("X-GitHub-Api-Version", "2022-11-28");
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, &version]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonArray releases = jsonDoc.array();

            if (releases.size() >= 2)
            {
                QJsonObject secondLastRelease = releases[1].toObject();
                version = secondLastRelease["tag_name"].toString();
                qDebug() << "Penultimate release:" << version;
            }
            else
            {
                qDebug() << "Not enough releases to get the "
                            "penultimate one.";
            }
        }
        else
        {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });

    return version;
}

void SettingsWindow::closeEvent(QCloseEvent *event)
{
    MainWindow *mainWindow = static_cast<MainWindow *>(parent());
    mainWindow->setGraphicsEffect(nullptr);
    QMainWindow::closeEvent(event);
    saveData();
}

void SettingsWindow::checkUpdates()
{
    QString secondLastRelease = fetchSecondLastRelease();

    QDialog dialog(this);
    dialog.setFixedSize(400, 400);
    dialog.setWindowTitle(tr("Edit project"));
    dialog.setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    QString newAppVersion = getNewAppVersion();
    QString currentAppVersion = versionInfo->text();

    QGridLayout *layout = new QGridLayout(&dialog);

    QPushButton *closeWindow = new QPushButton("");
    closeWindow->setFixedSize(13, 13);
    closeWindow->setObjectName("closeBtn");

    QLabel *iconLabel = new QLabel();
    iconLabel->setPixmap(changeIconColor(QPixmap(":/refresh.png")).scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel *updateInfoLabel = new QLabel();
    updateInfoLabel->setStyleSheet("font-size: " + font_size + "px;");
    updateInfoLabel->setFont(selectedFont);
    updateInfoLabel->setAlignment(Qt::AlignCenter);

    QLabel *verInfoLabel = new QLabel();
    verInfoLabel->setStyleSheet("font-size: " + font_size + "px;");
    verInfoLabel->setFont(selectedFont);
    verInfoLabel->setAlignment(Qt::AlignCenter);

    QPushButton *downloadUpdate = new QPushButton(
        changeIconColor(QPixmap(":/download.png"))
            .scaled(font_size.toInt() + 1, font_size.toInt() + 1, Qt::KeepAspectRatio, Qt::SmoothTransformation),
        " Update");
    downloadUpdate->setFixedSize(100, 25);

    QPushButton *whatsNewButton = new QPushButton(tr("What's new"));
    whatsNewButton->setFixedSize(100, 25);
    whatsNewButton->setFont(selectedFont);
    whatsNewButton->setStyleSheet("font-size: " + font_size +
                                  "px; border: none; background-color: transparent; color: #55b27d;");

    qDebug() << newAppVersion << "  " << currentAppVersion;

    whatsNewButton->hide();

    QStringList currentParts = currentAppVersion.split('.');
    QStringList newParts = newAppVersion.split('.');

    bool isDevVersion = false;

    for (int i = 0; i < qMin(currentParts.size(), newParts.size()); ++i)
    {
        int currentPart = currentParts[i].toInt();
        int newPart = newParts[i].toInt();

        if (currentPart > newPart)
        {
            isDevVersion = true;
            break;
        }
        else if (currentPart < newPart)
        {
            break;
        }
    }

    if (isDevVersion)
    {
        updateInfoLabel->setText(tr("You are using the developer version. It's not stable"));
    }
    else
    {
        iconLabel->setPixmap(changeIconColor(QPixmap(":/refresh.png")).scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        updateInfoLabel->setText(tr("A new version of the application is available."));
        verInfoLabel->setText(tr("Current version: ") + currentAppVersion + "\n" + tr("New version: ") + newAppVersion);
        layout->addWidget(downloadUpdate, 6, 0, 1, 2, Qt::AlignCenter);
    }

    layout->addWidget(closeWindow, 0, 0, 1, 2, Qt::AlignLeft);
    layout->addWidget(iconLabel, 1, 0, 3, 2, Qt::AlignCenter);
    layout->addWidget(updateInfoLabel, 4, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(verInfoLabel, 5, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(whatsNewButton, 7, 0, 1, 2, Qt::AlignCenter);

    connect(closeWindow, &QPushButton::clicked, [&]() { dialog.close(); });

    connect(downloadUpdate, &QPushButton::clicked,
            [&]() { QDesktopServices::openUrl(QUrl("https://github.com/Nighty3098/CodeKeeper/releases/latest")); });

    connect(whatsNewButton, &QPushButton::clicked, [&]() {
        QDesktopServices::openUrl(QUrl("https://github.com/Nighty3098/CodeKeeper/compare/" + secondLastRelease + "..." +
                                       currentAppVersion + ""));
    });

    dialog.exec();
}

void SettingsWindow::checkRepo()
{
    QString repo = "https://github.com/" + gitUser->text() + "/" + gitRepo->text();

    QNetworkAccessManager nam;
    QNetworkReply *reply = nam.get(QNetworkRequest(QUrl(repo)));
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        repoAvailability->setText(tr("Repository is available"));
    }
    else
    {
        qDebug() << repo;
        qWarning() << "The repository isn't available";
        repoAvailability->setText(tr("The repository isn't available"));
    }

    reply->deleteLater();
}

void SettingsWindow::fopenFolder()
{
    QString str = QFileDialog::getExistingDirectory(this, tr("Select Folder"));
    if (!str.isEmpty())
    {
        qDebug() << str;
        globalSettings->setValue("path", str);

        pathToFolder->setText(str);

        QMessageBox *messageBox = new QMessageBox();

        messageBox->setIcon(QMessageBox::Information);
        messageBox->setWindowTitle("CodeKeeper - Settings");
        messageBox->setText(tr("To apply the settings, restart the application."));

        messageBox->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
        messageBox->exec();
        MainWindow *mainWindow = static_cast<MainWindow *>(parent());
        mainWindow->loadNotes();
    }
}

QString SettingsWindow::getNewAppVersion()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://api.github.com/repos/Nighty3098/CodeKeeper/releases/latest");

    QUrlQuery query;
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

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = doc.object();

    QString version = obj["tag_name"].toString();
    qDebug() << version;

    reply->deleteLater();

    return version;
}

void SettingsWindow::saveData()
{
    qDebug() << "Saving data";

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    QMessageBox *messageBox = new QMessageBox();

    QFont selectedFont = fontSelector->currentFont();
    globalSettings->setValue("font", selectedFont);

    int font_size = fontSize->value();
    globalSettings->setValue("fontSize", font_size);

    int theme = themeSelector->currentIndex();
    globalSettings->setValue("theme", theme);

    QString dir = pathToFolder->text();
    globalSettings->setValue("path", dir);

    QString git_tokenS = gitToken->text();
    globalSettings->setValue("git_token", git_tokenS);

    QString git_userS = gitUser->text();
    globalSettings->setValue("git_user", git_userS);

    QString git_repoS = gitRepo->text();
    globalSettings->setValue("git_repo", git_repoS);

    isDateB = isDate->isChecked();
    globalSettings->setValue("isDate", isDateB);

    isHostB = isHost->isChecked();
    globalSettings->setValue("isHost", isHostB);

    isTimeB = isTime->isChecked();
    globalSettings->setValue("isTime", isTimeB);

    isAutoSyncB = isSync->isChecked();
    globalSettings->setValue("isAutoSync", isAutoSyncB);

    isCustomTitlebar = customTitleBar->isChecked();
    globalSettings->setValue("isCustomTitlebar", isCustomTitlebar);

    isCustomTheme = customTheme->isChecked();
    globalSettings->setValue("isCustomTheme", isCustomTheme);

    isCreated = CisCreated->isChecked();
    globalSettings->setValue("isCreated", isCreated);
    isReleaseDate = CisReleaseDate->isChecked();
    globalSettings->setValue("isReleaseDate", isReleaseDate);
    isLastCommit = CisLastCommit->isChecked();
    globalSettings->setValue("isLastCommit", isLastCommit);
    isPullReq = CisPullReq->isChecked();
    globalSettings->setValue("isPullReq", isPullReq);
    isLicense = CisLicense->isChecked();
    globalSettings->setValue("isLicense", isLicense);
    isRelease = CisRelease->isChecked();
    globalSettings->setValue("isRelease", isRelease);
    isIssue = CisIssue->isChecked();
    globalSettings->setValue("isIssue", isIssue);
    isDownloads = CisDownloads->isChecked();
    globalSettings->setValue("isDownloads", isDownloads);
    isCommit = CisCommit->isChecked();
    globalSettings->setValue("isCommit", isCommit);
    isLang = CisLang->isChecked();
    globalSettings->setValue("isLang", isLang);
    isStars = CisStars->isChecked();
    globalSettings->setValue("isStars", isStars);
    isForks = CisForks->isChecked();
    globalSettings->setValue("isForks", isForks);
    isRepoSize = CisRepoSize->isChecked();
    globalSettings->setValue("isRepoSize", isRepoSize);

    isAutoCheckUpdates = autoUpdates->isChecked();
    globalSettings->setValue("isAutoCheckUpdates", isAutoCheckUpdates);

    appLang = langSelector->currentIndex();
    qDebug() << "===============================";
    qDebug() << appLang;
    qDebug() << "===============================";
    globalSettings->setValue("lang", appLang);

    MainWindow *mainWindow = static_cast<MainWindow *>(parent());
    setStyle2(&selectedFont, &font_size);
    mainWindow->setStyle(&selectedFont, &font_size);
    mainWindow->getSettingsData();

    mainWindow->setConnectionStatus();
    mainWindow->createConnection(dir);
    mainWindow->loadNotes();
    mainWindow->loadTasks();
    mainWindow->loadProjects();
    mainWindow->loadStyleSheetFile();

    SyncWindow *syncWindow = static_cast<SyncWindow *>(parent());

    AccountWindow *accountWindow = static_cast<AccountWindow *>(parent());
}

void SettingsWindow::setStyle2(QFont *selectedFont, int *font_size_int)
{
    qDebug() << "Applying preferences";

    QString font_size = QString::number(*font_size_int);
    QString font_size_2 = QString::number((*font_size_int) * 3);

    // set font
    tabs->setFont(*selectedFont);
    tabs->setStyleSheet("QTabBar::tab { font-size: " + font_size +
                        "px;} QTabBar::tab:selected {font-size: " + font_size + "px;}");

    saveBtn->setFont(*selectedFont);
    saveBtn->setStyleSheet("QPushButton {border: none; background-color: "
                           "transparent; font-size: " +
                           font_size +
                           "px;} QPushButton:hover {border: none; "
                           "background-color: transparent; font-size: " +
                           font_size + "px;}");

    appName->setFont(*selectedFont);

    urlToRepo->setFont(*selectedFont);
    urlToRepo->setStyleSheet("font-size: " + font_size + "px;");

    versionInfo->setFont(*selectedFont);
    versionInfo->setStyleSheet("font-size: " + font_size + "px;");

    checkUpdatesBtn->setFont(*selectedFont);
    checkUpdatesBtn->setStyleSheet("font-size: " + font_size + "px;");

    fontSize->setFont(*selectedFont);
    fontSize->setStyleSheet("font-size: " + font_size + "px;");

    fontSelector->setFont(*selectedFont);
    fontSelector->setStyleSheet("font-size: " + font_size + "px;");

    themeSelector->setFont(*selectedFont);
    themeSelector->setStyleSheet("font-size: " + font_size + "px;");

    gitLabel->setFont(*selectedFont);
    gitLabel->setStyleSheet("font-size: " + font_size_2 + "px;");

    gitLabel2->setFont(*selectedFont);
    gitLabel2->setStyleSheet("font-size: " + font_size_2 + "px;");

    gitToken->setFont(*selectedFont);
    gitToken->setStyleSheet("font-size: " + font_size + "px;");

    autoUpdates->setFont(*selectedFont);
    autoUpdates->setStyleSheet("font-size: " + font_size + "px;");

    gitUser->setFont(*selectedFont);
    gitUser->setStyleSheet("font-size: " + font_size + "px;");

    gitRepo->setFont(*selectedFont);
    gitRepo->setStyleSheet("font-size: " + font_size + "px;");

    langLabel->setFont(*selectedFont);
    langLabel->setStyleSheet("font-size: " + font_size + "px;");

    langSelector->setFont(*selectedFont);
    langSelector->setStyleSheet("font-size: " + font_size + "px;");

    autoSyncAfterStart->setFont(*selectedFont);
    autoSyncAfterStart->setStyleSheet("font-size: " + font_size + "px;");

    isDate->setFont(*selectedFont);
    isDate->setStyleSheet("font-size: " + font_size + "px;");

    isTime->setFont(*selectedFont);
    isTime->setStyleSheet("font-size: " + font_size + "px;");

    isHost->setFont(*selectedFont);
    isHost->setStyleSheet("font-size: " + font_size + "px;");

    mainTitle->setFont(*selectedFont);
    mainTitle->setStyleSheet("font-size: " + font_size_2 + "px;");

    fontLabel->setFont(*selectedFont);
    fontSizeLabel->setFont(*selectedFont);

    fontSizeLabel->setFont(*selectedFont);
    fontSizeLabel->setStyleSheet("font-size: " + font_size + "px;");

    warningLabel->setFont(*selectedFont);
    warningLabel->setStyleSheet("font-size: " + font_size + "px;");

    themeLabel->setFont(*selectedFont);
    themeLabel->setStyleSheet("font-size: " + font_size + "px;");

    storageLabel->setFont(*selectedFont);

    pathToFolder->setFont(*selectedFont);
    pathToFolder->setStyleSheet("font-size: " + font_size + "px;");

    openFolder->setFont(*selectedFont);
    openFolder->setStyleSheet("font-size: " + font_size + "px;");

    customTitleBar->setFont(*selectedFont);
    customTitleBar->setStyleSheet("font-size: " + font_size + "px;");

    customTheme->setFont(*selectedFont);
    customTheme->setStyleSheet("font-size: " + font_size + "px;");

    repoAvailability->setFont(*selectedFont);
    repoAvailability->setStyleSheet("font-size: " + font_size + "px;");

    projectsContentLabel->setFont(*selectedFont);

    CisCreated->setFont(*selectedFont);
    CisReleaseDate->setFont(*selectedFont);
    CisLastCommit->setFont(*selectedFont);
    CisPullReq->setFont(*selectedFont);
    CisLicense->setFont(*selectedFont);
    CisRelease->setFont(*selectedFont);
    CisIssue->setFont(*selectedFont);
    CisDownloads->setFont(*selectedFont);
    CisCommit->setFont(*selectedFont);
    CisLang->setFont(*selectedFont);
    CisStars->setFont(*selectedFont);
    CisForks->setFont(*selectedFont);

    CisCreated->setStyleSheet("font-size: " + font_size + "px;");
    CisReleaseDate->setStyleSheet("font-size: " + font_size + "px;");
    CisLastCommit->setStyleSheet("font-size: " + font_size + "px;");
    CisPullReq->setStyleSheet("font-size: " + font_size + "px;");
    CisLicense->setStyleSheet("font-size: " + font_size + "px;");
    CisRelease->setStyleSheet("font-size: " + font_size + "px;");
    CisIssue->setStyleSheet("font-size: " + font_size + "px;");
    CisDownloads->setStyleSheet("font-size: " + font_size + "px;");
    CisCommit->setStyleSheet("font-size: " + font_size + "px;");
    CisLang->setStyleSheet("font-size: " + font_size + "px;");
    CisStars->setStyleSheet("font-size: " + font_size + "px;");
    CisForks->setStyleSheet("font-size: " + font_size + "px;");

    fontSelector->setCurrentFont(*selectedFont);
    fontSize->setValue(font_size.toInt());
}

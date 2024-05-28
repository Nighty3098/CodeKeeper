#include <QDateTime>
#include <QSyntaxHighlighter>
#include <QGraphicsOpacityEffect>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>
#include <QSqlDatabase>
#include <QSqlError>
#include <QThread>

bool MainWindow::createConnection(QString path)
{
    qDebug() << "🔸DB path: " << (path) + QStringLiteral("/data.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName((path) + QStringLiteral("/data.db"));

    db.setUserName("admin");
    db.setHostName("localhost");
    db.setPassword("password");

    if (!db.open()) {
        qCritical() << "🔴 " << db.lastError();
        return false;
    }

    return true;
}

QString MainWindow::getCurrentDateTimeString()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTimeString = currentDateTime.toString("dd-MM-yyyy hh:mm:ss");
    return dateTimeString;
}

void MainWindow::getSettingsData()
{
    dir = globalSettings->value("path").value<QString>();
    selectedFont = globalSettings->value("font").value<QFont>();
    font_size = globalSettings->value("fontSize").value<QString>();
    theme = globalSettings->value("theme").value<QString>();
    isCustomTitlebar = globalSettings->value("isCustomTitlebar").value<bool>();
    sortNotesRole = globalSettings->value("sortRole", Qt::DisplayRole).value<int>();
    isAutoSyncing = globalSettings->value("isAutoSync").value<bool>();
    isVisibleNotesList = globalSettings->value("isVisibleNotesList", true).toBool();
    isVisibleFolders = globalSettings->value("isVisibleFolders", true).toBool();
    isVisiblePreview = globalSettings->value("isVisiblePreview", false).toBool();
    isViewMode = globalSettings->value("isViewMode", false).toBool();
    git_repo = globalSettings->value("git_repo").value<QString>();
    git_user = globalSettings->value("git_user").value<QString>();
    git_token = globalSettings->value("git_token").value<QString>();
    isAutoSyncB = globalSettings->value("isAutoSync").value<bool>();

    isCreated = globalSettings->value("isCreated").value<bool>();
    isReleaseDate = globalSettings->value("isReleaseDate").value<bool>();
    isLastCommit = globalSettings->value("isLastCommit").value<bool>();
    isPullReq = globalSettings->value("isPullReq").value<bool>();
    isLicense = globalSettings->value("isLicense").value<bool>();
    isRelease = globalSettings->value("isRelease").value<bool>();
    isIssue = globalSettings->value("isIssue").value<bool>();
    isDownloads = globalSettings->value("isDownloads").value<bool>();
    isCommit = globalSettings->value("isCommit").value<bool>();
    isLang = globalSettings->value("isLang").value<bool>();
    isStars = globalSettings->value("isStars").value<bool>();
    isForks = globalSettings->value("isForks").value<bool>();
    isRepoSize = globalSettings->value("isRepoSize").value<bool>();

    qDebug() << "🔸 " << dir << selectedFont << font_size << theme << isCustomTitlebar
             << sortNotesRole << isAutoSyncing << isVisibleNotesList << isVisibleFolders
             << isVisiblePreview << isViewMode << git_repo << git_user << git_token << isAutoSyncB;
}

void MainWindow::setConnectionStatus()
{
    if (checkConnection()) {
        isConnected->setIcon(QPixmap(":/connected.png")
                                     .scaled(font_size.toInt() + 1, font_size.toInt() + 1,
                                             Qt::KeepAspectRatio, Qt::SmoothTransformation));
        isConnected->setToolTip("<p style='color: #dCD7BA;'>Connected</p>");
        sizeGrip2->setStyleSheet("background-color: #37d442; border-radius: 5px;");
    } else {
        isConnected->setIcon(QPixmap(":/disconnected.png")
                                     .scaled(font_size.toInt() + 1, font_size.toInt() + 1,
                                             Qt::KeepAspectRatio, Qt::SmoothTransformation));
        isConnected->setToolTip("<p style='color: #dCD7BA;'>Disconnected</p>");
    }

    if (isAutoSyncing) {
        isAutoSync->setIcon(QPixmap(":/auto_sync_on.png")
                                    .scaled(font_size.toInt() + 1, font_size.toInt() + 1,
                                            Qt::KeepAspectRatio, Qt::SmoothTransformation));
        isAutoSync->setToolTip("<p style='color: #dCD7BA;'>Auto sync on</p>");
        sizeGrip2->setStyleSheet("background-color: #37d442; border-radius: 5px;");
    } else {
        isAutoSync->setIcon(QPixmap(":/auto_sync_off.png")
                                    .scaled(font_size.toInt() + 1, font_size.toInt() + 1,
                                            Qt::KeepAspectRatio, Qt::SmoothTransformation));
        isAutoSync->setToolTip("<p style='color: #dCD7BA;'>Auto sync off</p>");
    }
}

void MainWindow::createCustomTitlebar()
{
    QSpacerItem *headerSp = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *headerSp2 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    closeBtn->setFixedSize(15, 15);
    minimizeBtn->setFixedSize(15, 15);
    maximizeBtn->setFixedSize(15, 15);

    QLabel *windowTitle = new QLabel();
    windowTitle->setAlignment(Qt::AlignCenter);
    windowTitle->setText("CodeKeeper");
    windowTitle->setStyleSheet("font-size: " + font_size + "pt;");
    windowTitle->setFont(selectedFont);

    closeBtn->setStyleSheet("QPushButton {"
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

    minimizeBtn->setStyleSheet("QPushButton {"
                               "    border-color: rgba(0, 0, 0, 0);"
                               "    background-color: rgba(0, 0, 0, 0);"
                               "    background-image: url(':/yellow.png');"
                               "    background-repeat: no-repeat;"
                               "}"

                               "QPushButton:hover {"
                               "    border-color: rgba(0, 0, 0, 0);"
                               "    background-image: url(':/yellowHovered.png');"
                               "    background-repeat: no-repeat;"
                               "    background-color: rgba(0, 0, 0, 0);"
                               "}");

    maximizeBtn->setStyleSheet("QPushButton {"
                               "    border-color: rgba(0, 0, 0, 0);"
                               "    background-color: rgba(0, 0, 0, 0);"
                               "    background-image: url(':/green.png');"
                               "    background-repeat: no-repeat;"
                               "}"

                               "QPushButton:hover {"
                               "    border-color: rgba(0, 0, 0, 0);"
                               "    background-image: url(':/greenHovered.png');"
                               "    background-color: rgba(0, 0, 0, 0);"
                               "    background-repeat: no-repeat;"
                               "}");

    openAccountWindow->setStyleSheet(
            "QPushButton {background-color: transparent; color: #ffffff;} "
            "QPushButton:hover{text-decoration: none; background-color: transparent; color: #37d442;}");

    if (isCustomTitlebar) {
        this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

        winControlL->addWidget(closeBtn);
        winControlL->addWidget(minimizeBtn);
        winControlL->addWidget(maximizeBtn);
        winControlL->addItem(headerSp);
        // winControlL->addWidget(windowTitle);
        winControlL->addItem(headerSp2);
        winControlL->addWidget(openAccountWindow);
    }
}

void MainWindow::fOpenAccountWindow()
{
    QRect geo = this->geometry();
    int x = geo.x();
    int y = geo.y();
    int width = geo.width();
    int height = geo.height();

    accountWindow = new AccountWindow(this);

    QRect geo2 = accountWindow->geometry();

    int width2 = geo2.width();
    int height2 = geo2.height();

    int new_x = x + (width - width2) / 2;
    int new_y = y + (height - height2) / 2;

    accountWindow->show();

    accountWindow->move(new_x, new_y);
}

void MainWindow::openSettingsWindow()
{
    QRect geo = this->geometry();
    int x = geo.x();
    int y = geo.y();
    int width = geo.width();
    int height = geo.height();

    settingsWindow = new SettingsWindow(this);

    QRect geo2 = settingsWindow->geometry();

    int width2 = geo2.width();
    int height2 = geo2.height();

    int new_x = x + (width - width2) / 2;
    int new_y = y + (height - height2) / 2;

    settingsWindow->show();

    settingsWindow->move(new_x, new_y);
}

void MainWindow::setSettingsData() { }

bool MainWindow::checkConnection()
{
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("https://google.com/"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    QObject::connect(&nam, SIGNAL(finished(QNetworkReply *)), &loop, SLOT(quit()));

    if (!reply->isFinished()) {
        loop.exec();
        if (reply->error() == QNetworkReply::NoError) {
            // qDebug() << "You are connected to the internet :)";
            return true;
        } else {
            qWarning() << "🔴 You have an net error:" << reply->errorString();
            return false;
        }
    }
}

void MainWindow::openSyncWindow()
{
    QRect geo = this->geometry();
    int x = geo.x();
    int y = geo.y();
    int width = geo.width();
    int height = geo.height();

    syncWindow = new SyncWindow(this);

    QRect geo2 = syncWindow->geometry();

    int width2 = geo2.width();
    int height2 = geo2.height();

    int new_x = x + (width - width2) / 2;
    int new_y = y + (height - height2) / 2;

    syncWindow->show();
    syncWindow->move(new_x, new_y);
}

void MainWindow::openFolder()
{
    QString str = QFileDialog::getExistingDirectory(0, "Select a directory");
    if (!str.isEmpty()) {
        globalSettings->setValue("path", str);
        qDebug() << "🟢 " << str;
    }
}

void MainWindow::updateWindowTitle() { }

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QListWidget *lists[] = { notStartedProjects, startedProjects, finishlineProjects,
                             finishedProjects,   incompleteTasks, inprocessTasks,
                             completeTasks };

    for (QListWidget *list : lists) {
        QListWidgetItem *selectedItem = list->currentItem();
        if (selectedItem && selectedItem != item) {
            list->setCurrentItem(nullptr);
        }
    }
}

void MainWindow::setFontPr1(QFont *selectedFont, int *font_size_int)
{
    qDebug() << "🟢 Applying preferences";

    QString font_size = QString::number(*font_size_int);

    projectsMainLabel->setFont(*selectedFont);
    projectsMainLabel->setStyleSheet("font-size: " + font_size + "pt; color: #8ebecf;");

    openSettingsBtn->setFont(*selectedFont);
    openSettingsBtn->setStyleSheet("font-size: " + font_size + "pt;");

    syncDataBtn->setFont(*selectedFont);
    syncDataBtn->setStyleSheet("font-size: " + font_size + "pt;");

    notesList->setFont(*selectedFont);
    notesList->setStyleSheet("font-size: " + font_size
                             + "pt; background-color: rgba(47, 51, 77, 0);");

    menuButton->setFont(*selectedFont);

    tasksMenuBtn->setFont(*selectedFont);

    mdPreview->setFont(*selectedFont);

    noteEdit->setFont(*selectedFont);
    noteEdit->setStyleSheet("font-size: " + font_size + "pt;");

    noteNameLabel->setFont(*selectedFont);
    noteNameLabel->setStyleSheet("font-size: " + font_size + "pt; color: #8ebecf;");

    taskText->setFont(*selectedFont);
    taskText->setStyleSheet("font-size: " + font_size + "pt;");

    incompleteTasks->setStyleSheet("QListWidget {"
                                   "font-size: "
                                   + font_size
                                   + "pt;"
                                     "}"
                                     "QListWidget::item:selected {"
                                     "background-color: rgba(211, 102, 107, 75);"
                                     "}"
                                     "QListWidget::Item {"
                                     "margin: 0px;"
                                     "background-color: rgb(211, 102, 107); color: #000000; "
                                     "border-width: 0px; border-color: rgb(211, 102, 107); "
                                     "border-radius: 5px;"
                                     "font-size: "
                                   + font_size
                                   + "pt;"
                                     "}");

    inprocessTasks->setStyleSheet("QListWidget {"
                                  "font-size: "
                                  + font_size
                                  + "pt;"
                                    "}"
                                    "QListWidget::item:selected {"
                                    "background-color: rgba(231, 232, 141, 75);"
                                    "}"
                                    "QListWidget::Item {"
                                    "margin: 0px;"
                                    "background-color: rgb(231, 232, 141); "
                                    "color: #000000; text-decoration: underline; "
                                    "border-width: 0px; "
                                    "border-radius: 5px;"
                                    "font-size: "
                                  + font_size
                                  + "pt;"
                                    "}");

    completeTasks->setStyleSheet("QListWidget {"
                                 "font-size: "
                                 + font_size
                                 + "pt;"
                                   "}"
                                   "QListWidget::item:selected {"
                                   "background-color: rgba(195, 232, 141, 75);"
                                   "}"
                                   "QListWidget::Item {"
                                   "margin: 0px;"
                                   "background-color: rgb(195, 232, 141); "
                                   "color: #000000;"
                                   "border-radius: 5px;"
                                   "line-through; border-width: 0px; "
                                   "font-size: "
                                 + font_size
                                 + "pt;"
                                   "}");

    notStartedProjects->setStyleSheet("QListWidget {"
                                      "font-size: "
                                      + font_size
                                      + "pt;"
                                        "}"
                                        "QListWidget::item:selected {"
                                        "background-color: rgba(211, 102, 107, 75);"
                                        "}"
                                        "QListWidget::Item {"
                                        "margin: 0px;"
                                        "background-color: rgb(211, 102, 107);"
                                        "color: #000000; border-width: 0px; "
                                        "border-radius: 5px;"
                                        "border-color: #ff757f; "
                                        "font-size: "
                                      + font_size
                                      + "pt;"
                                        "}");

    startedProjects->setStyleSheet("QListWidget {"
                                   "font-size: "
                                   + font_size
                                   + "pt;"
                                     "}"
                                     "QListWidget::item:selected {"
                                     "background-color: rgba(231, 232, 141, 75);"
                                     "}"
                                     "QListWidget::Item {"
                                     "margin: 0px;"
                                     "background-color: rgb(231, 232, 141); color: #000000; "
                                     "border-radius: 5px;"
                                     "border-width: 0px; border-color: #ffc777; "
                                     "font-size: "
                                   + font_size
                                   + "pt;"
                                     "}");

    finishlineProjects->setStyleSheet("QListWidget {"
                                      "font-size: "
                                      + font_size
                                      + "pt;"
                                        "}"
                                        "QListWidget::item:selected {"
                                        "background-color: rgba(126, 156, 216, 75)"
                                        "}"
                                        "QListWidget::Item {"
                                        "margin: 0px;"
                                        "background-color: rgb(126, 156, 216 "
                                        "); color: #000000; border-width: 0px; "
                                        "border-radius: 5px;"
                                        "border-color: #82aaff; "
                                        "font-size: "
                                      + font_size
                                      + "pt;"
                                        "}");

    finishedProjects->setStyleSheet("QListWidget {"
                                    "font-size: "
                                    + font_size
                                    + "pt;"
                                      "}"
                                      "QListWidget::item:selected {"
                                      "background-color: rgba(195, 232, 141, 75);"
                                      "}"
                                      "QListWidget::Item {"
                                      "margin: 0px;"
                                      "background-color: rgb(195, 232, 141); color: #000000; "
                                      "border-radius: 5px;"
                                      "border-width: 0px; border-color: #c3e88d; "
                                      "font-size: "
                                    + font_size
                                    + "pt;"
                                      "}");

    fProjects->setFont(*selectedFont);
    flProjects->setFont(*selectedFont);
    nsProjects->setFont(*selectedFont);
    sProjects->setFont(*selectedFont);

    nsProjects->setStyleSheet("font-size: " + font_size + "pt;");
    sProjects->setStyleSheet("font-size: " + font_size + "pt;");
    flProjects->setStyleSheet("font-size: " + font_size + "pt;");
    fProjects->setStyleSheet("font-size: " + font_size + "pt;");

    projectsMainLabel->setFont(*selectedFont);
    notStartedProjects->setFont(*selectedFont);
    startedProjects->setFont(*selectedFont);
    finishlineProjects->setFont(*selectedFont);
    finishedProjects->setFont(*selectedFont);

    projectsMenu->setFont(*selectedFont);

    tabs->setFont(*selectedFont);
    tabs->setStyleSheet("QTabBar::tab { font-size: " + font_size
                        + "pt;} QTabBar::tab:selected {font-size: " + font_size + "pt;}");

    totalProjectsL->setFont(*selectedFont);
    totalProjectsL->setStyleSheet("font-size: " + font_size + "pt;");

    incompleteTasks->setFont(*selectedFont);
    inprocessTasks->setFont(*selectedFont);
    completeTasks->setFont(*selectedFont);

    label_1->setFont(*selectedFont);
    label_1->setStyleSheet("font-size: " + font_size + "pt;");
    label_2->setFont(*selectedFont);
    label_2->setStyleSheet("font-size: " + font_size + "pt;");
    label_3->setFont(*selectedFont);
    label_3->setStyleSheet("font-size: " + font_size + "pt;");

    tasksProgress->setFont(*selectedFont);
    tasksProgress->setStyleSheet(
            "background-color: rgb(211, 102, 107); selection-background-color: "
            "rgb(118, 148, 106); color: #222436; font-size: "
            + font_size + "pt;");

    menu->setStyleSheet("font-size: " + font_size + "pt;");
    menu->setFont(*selectedFont);

    tasksMenu->setFont(*selectedFont);
    tasksMenu->setStyleSheet("font-size: " + font_size + "pt;");

    projectsMenu->setFont(*selectedFont);
    projectsMenu->setStyleSheet("font-size: " + font_size + "pt;");

    openAccountWindow->setFont(*selectedFont);
    openAccountWindow->setStyleSheet(
            "QPushButton {background-color: transparent; color: #ffffff; font-size: " + font_size + "pt;} "
            "QPushButton:hover{text-decoration: none; background-color: transparent; color: #37d442; font-size: " + font_size + "pt;}");
}

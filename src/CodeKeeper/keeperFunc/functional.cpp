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
    qDebug() << path;
    qDebug() << "DB path: " << (path) + QStringLiteral("/data.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName((path) + QStringLiteral("/data.db"));

    db.setUserName("admin");
    db.setHostName("localhost");
    db.setPassword("password");

    if (!db.open()) {
        qDebug() << db.lastError();
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

    qDebug() << dir << selectedFont << font_size << theme << isCustomTitlebar << sortNotesRole
             << isAutoSyncing << isVisibleNotesList << isVisibleFolders << isVisiblePreview
             << isViewMode << git_repo << git_user << git_token << isAutoSyncB;
}

void MainWindow::setConnectionStatus()
{
    if (checkConnection()) {
        isConnected->setIcon(QIcon(":/connected.png"));
        isConnected->setToolTip("<p style='color: #ffffff;'>Connected</p>");
        sizeGrip2->setStyleSheet("background-color: #37d442; border-radius: 5px;");
    } else {
        isConnected->setIcon(QIcon(":/disconnected.png"));
        isConnected->setToolTip("<p style='color: #ffffff;'>Disconnected</p>");
    }

    if (isAutoSyncing) {
        isAutoSync->setIcon(QIcon(":/auto_sync_on.png"));
        isAutoSync->setToolTip("<p style='color: #ffffff;'>Auto sync on</p>");
        sizeGrip2->setStyleSheet("background-color: #37d442; border-radius: 5px;");
    } else {
        isAutoSync->setIcon(QIcon(":/auto_sync_off.png"));
        isAutoSync->setToolTip("<p style='color: #ffffff;'>Auto sync off</p>");
    }
}

void MainWindow::createCustomTitlebar()
{
    QSpacerItem *headerSp = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    closeBtn->setFixedSize(15, 15);
    minimizeBtn->setFixedSize(15, 15);
    maximizeBtn->setFixedSize(15, 15);

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

    if (isCustomTitlebar) {
        this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

        winControlL->addWidget(closeBtn);
        winControlL->addWidget(minimizeBtn);
        winControlL->addWidget(maximizeBtn);
        winControlL->addItem(headerSp);
    }
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
            // qDebug() << "You have an net error:" << reply->errorString();
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
        qDebug() << str;
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
    QString font_size = QString::number(*font_size_int);

    mainTitle->setFont(*selectedFont);

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

    incompleteTasks->setStyleSheet(
            "QListWidget {background-color: rgba(211, 102, 107, 0);  border-width: "
            "0px; "
            "border-color: #838383;}"
            "QListWidget::item:selected {"
            "color: #FFFFFF;"
            "}"
            "QListWidget::Item {"
            "margin: 0px;"
            "background-color: rgb(211, 102, 107); color: #000000; "
            "padding: 2px;"
            "border-width: 0px; border-color: rgb(211, 102, 107); "
            "border-radius: 5px;"
            "font-size: "
            + font_size
            + "pt;"
              "}");

    inprocessTasks->setStyleSheet(
            "QListWidget {background-color: rgba(211, 102, 107, 0);  border-width: "
            "0px; "
            "border-color: #838383;}"
            "QListWidget::item:selected {"
            "color: #FFFFFF;"
            "}"
            "QListWidget::Item {"
            "margin: 0px;"
            "background-color: rgb(192, 163, 110); "
            "color: #000000; text-decoration: underline; "
            "border-width: 0px; "
            "padding: 2px;"
            "border-radius: 5px;"
            "font-size: "
            + font_size
            + "pt;"
              "}");

    completeTasks->setStyleSheet(
            "QListWidget {background-color: rgba(211, 102, 107, 0);  border-width: "
            "0px; "
            "border-color: #838383;}"
            "QListWidget::item:selected {"
            "color: #FFFFFF;"
            "}"
            "QListWidget::Item {"
            "margin: 0px;"
            "background-color: rgb(118, 148, 106); "
            "color: #000000;"
            "padding: 2px;"
            "border-radius: 5px;"
            "line-through; border-width: 0px; "
            "font-size: "
            + font_size
            + "pt;"
              "}");

    notStartedProjects->setStyleSheet(
            "QListWidget {background-color: rgba(211, 102, 107, 0);  border-width: "
            "0px; "
            "border-color: #838383;}"
            "QListWidget::item:selected {"
            "color: #FFFFFF;"
            "}"
            "QListWidget::Item {"
            "margin: 0px;"
            "padding: 2px;"
            "background-color: rgb(211, 102, 107);"
            "color: #000000; border-width: 0px; "
            "border-radius: 5px;"
            "border-color: #ff757f; "
            "font-size: "
            + font_size
            + "pt;"
              "}");

    startedProjects->setStyleSheet(
            "QListWidget {background-color: rgba(211, 102, 107, 0);  border-width: "
            "0px; "
            "border-color: #838383;}"
            "QListWidget::item:selected {"
            "color: #FFFFFF;"
            "}"
            "QListWidget::Item {"
            "margin: 0px;"
            "background-color: rgb(192, 163, 110); color: #000000; "
            "border-radius: 5px;"
            "padding: 2px;"
            "border-width: 0px; border-color: #ffc777; "
            "font-size: "
            + font_size
            + "pt;"
              "}");

    finishlineProjects->setStyleSheet(
            "QListWidget {background-color: rgba(211, 102, 107, 0);  border-width: "
            "0px; "
            "border-color: #838383;}"
            "QListWidget::item:selected {"
            "color: #FFFFFF;"
            "}"
            "QListWidget::Item {"
            "margin: 0px;"
            "background-color: rgb(126, 156, 216 "
            "); color: #000000; border-width: 0px; "
            "border-radius: 5px;"
            "padding: 2px;"
            "border-color: #82aaff; "
            "font-size: "
            + font_size
            + "pt;"
              "}");

    finishedProjects->setStyleSheet(
            "QListWidget {background-color: rgba(211, 102, 107, 0);  border-width: "
            "0px; "
            "border-color: #838383;}"
            "QListWidget::item:selected {"
            "color: #FFFFFF;"
            "}"
            "QListWidget::Item {"
            "margin: 0px;"
            "background-color: rgb(118, 148, 106); color: #000000; "
            "border-radius: 5px;"
            "padding: 2px;"
            "border-width: 0px; border-color: #c3e88d; "
            "font-size: "
            + font_size
            + "pt;"
              "}");

    fProjects->setFont(*selectedFont);
    flProjects->setFont(*selectedFont);
    nsProjects->setFont(*selectedFont);
    sProjects->setFont(*selectedFont);

    nsProjects->setStyleSheet("font-size: 16px;");
    sProjects->setStyleSheet("font-size: 16px;");
    flProjects->setStyleSheet("font-size: 16px;");
    fProjects->setStyleSheet("font-size: 16px;");

    projectsMainLabel->setFont(*selectedFont);
    notStartedProjects->setFont(*selectedFont);
    startedProjects->setFont(*selectedFont);
    finishlineProjects->setFont(*selectedFont);
    finishedProjects->setFont(*selectedFont);

    projectsMenu->setFont(*selectedFont);

    tabs->setFont(*selectedFont);
    tabs->setStyleSheet("font-size: " + font_size + "pt;");

    totalProjectsL->setFont(*selectedFont);
    totalProjectsL->setStyleSheet("font-size: " + font_size + "pt;");

    incompleteTasks->setFont(*selectedFont);
    inprocessTasks->setFont(*selectedFont);
    completeTasks->setFont(*selectedFont);

    label_1->setFont(*selectedFont);
    label_1->setStyleSheet("font-size: 16px;");
    label_2->setFont(*selectedFont);
    label_2->setStyleSheet("font-size: 16px;");
    label_3->setFont(*selectedFont);
    label_3->setStyleSheet("font-size: 16px;");

    tasksProgress->setFont(*selectedFont);
    tasksProgress->setStyleSheet(
            "background-color: rgb(211, 102, 107); selection-background-color: "
            "rgb(118, 148, 106); color: #222436; font-size: "
            + font_size + "pt;");
}

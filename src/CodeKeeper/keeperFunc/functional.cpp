#include <QCoreApplication>
#include <QDateTime>
#include <QFontDatabase>
#include <QGraphicsOpacityEffect>
#include <QNetworkAccessManager>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSyntaxHighlighter>
#include <QThread>

#include "mainwindow.h"

void MainWindow::updateButtonStyles(QPushButton *activeButton)
{
    QString activeStyle =
        "QPushButton { margin: 7px; border-width: 2px; border-color: #a9bf85; background-color: transparent;} "
        "QPushButton::hover {border-color: #a9bf85; background-color: transparent;}";
    QString inactiveStyle =
        "QPushButton { margin: 7px; border-width: 2px; border-color: transparent; background-color: transparent;} "
        "QPushButton::hover {border-color: #a9bf85; background-color: transparent;}";

    QList<QPushButton *> buttons = {mainTabButton, tasksTabButton, notesTabButton, projectsTabButton};

    for (QPushButton *button : buttons)
    {
        if (button == activeButton)
        {
            button->setStyleSheet(activeStyle);
        }
        else
        {
            button->setStyleSheet(inactiveStyle);
        }
    }
}

void MainWindow::setupAdaptiveUI()
{
    int current_width = this->width();

    if (current_width < 1400)
    {
        tasksSplitter->setOrientation(Qt::Vertical);
        decorationLabel->setPixmap(QPixmap(":/tea.svg").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        timeLabel->setStyleSheet("font-size: 100px; color: #a9bf85;");
    }
    else if (current_width > 1500)
    {
        timeLabel->setStyleSheet("font-size: 150px; color: #a9bf85;");
        decorationLabel->setPixmap(QPixmap(":/tea.svg").scaled(350, 350, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else
    {
        tasksSplitter->setOrientation(Qt::Horizontal);

        incompleteWidget->setMaximumHeight(1000000);
        inprocessWidget->setMaximumHeight(10000000);
        completeWidget->setMaximumHeight(10000000);

        inprocessTasks->setVisible(true);
        completeTasks->setVisible(true);
        incompleteTasks->setVisible(true);
    }
}

void MainWindow::showWelcomeMessage()
{
    QVBoxLayout *layout = new QVBoxLayout();
    QDialog *dialogW = new QDialog();
    dialogW->setModal(true);
    dialogW->setMinimumWidth(700);
    dialogW->setWindowFlags(Qt::FramelessWindowHint);
    dialogW->setStyleSheet("outline: none; background-color: #1e1e1e; color: #ffffff;");

    dialogW->setLayout(layout);

    QLabel *label = new QLabel(tr(
        "\n\nThank you for downloading our program.\nAs this is the first run, please configure the "
        "program and select the folder to save the data in the settings\n\nPlease refer to the product license\n\n"));
    label->setStyleSheet("font-size: 11px;");
    label->setAlignment(Qt::AlignCenter);
    label->setWordWrap(true);

    QFile file(":/license.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open license.txt for reading.";
        return;
    }

    QPlainTextEdit *licenseText = new QPlainTextEdit();
    licenseText->setReadOnly(true);
    licenseText->setMinimumHeight(300);
    licenseText->setMinimumWidth(600);
    licenseText->setMaximumWidth(1600);
    licenseText->setStyleSheet(
        "padding: 20px; background-color: #2b2d2e; color: #ffffff; border:none; border-radius: 15px;");

    QTextStream in(&file);
    QString fileContent = in.readAll();
    licenseText->setPlainText(fileContent);
    file.close();

    QPushButton *okButton = new QPushButton(tr("   I agree to the terms and conditions   "));
    QObject::connect(okButton, &QPushButton::clicked, dialogW, &QDialog::accept);
    okButton->setFixedHeight(30);
    okButton->setStyleSheet(
        "outline: none; background-color: #3e8de6; color: #ffffff; border-radius: 7px; font-size: 11px;");

    QPushButton *cancelButton = new QPushButton(tr("   Cancel   "));
    QObject::connect(cancelButton, &QPushButton::clicked, dialogW, &QDialog::reject);
    this->close();
    cancelButton->setFixedHeight(30);
    cancelButton->setStyleSheet(
        "outline: none; background-color: #e06a65; color: #ffffff; border-radius: 7px; font-size: 11px;");
    QObject::connect(cancelButton, &QPushButton::clicked, dialogW, &QDialog::reject);
    QObject::connect(cancelButton, &QPushButton::clicked, this, &MainWindow::close);

    layout->addWidget(label, 0, Qt::AlignCenter);
    layout->addWidget(licenseText, 1, Qt::AlignCenter);
    layout->addWidget(okButton, 2, Qt::AlignCenter);
    layout->addWidget(cancelButton, 3, Qt::AlignCenter);

    dialogW->show();

    globalSettings->setValue("firstRun", false);
}

void MainWindow::hideMenu()
{
    if (isHideMenu)
    {
        tabButtonsWidget->show();
        winControlW->show();

        isHideMenu = false;
    }
    else
    {
        tabButtonsWidget->hide();
        winControlW->hide();

        isHideMenu = true;
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        this->show();
        break;
    default:
        break;
    }
}

bool MainWindow::createConnection(QString path)
{
    qDebug() << "DB path: " << (path) + QStringLiteral("/data.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName((path) + QStringLiteral("/data.db"));

    if (!db.open())
    {
        qCritical() << "" << db.lastError();
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

void MainWindow::updateTime()
{
    QString currentTime = QTime::currentTime().toString("hh:mm");
    QString currentDate = QDate::currentDate().toString("   dd.MM.yyyy");

    timeLabel->setText(currentTime);
    dateLabel->setText(currentDate);
}

void MainWindow::getSettingsData()
{
    dir = globalSettings->value("path").value<QString>();
    selectedFont = globalSettings->value("font").value<QFont>();
    font_size = globalSettings->value("fontSize").value<QString>();
    theme = globalSettings->value("theme").value<int>();
    isCustomTitlebar = globalSettings->value("isCustomTitlebar").value<bool>();
    isCustomTheme = globalSettings->value("isCustomTheme").value<bool>();
    sortNotesRole = globalSettings->value("sortRole", Qt::DisplayRole).value<int>();
    isAutoSyncing = globalSettings->value("isAutoSync").value<bool>();
    isVisibleNotesList = globalSettings->value("isVisibleNotesList", true).toBool();
    isVisibleFolders = globalSettings->value("isVisibleFolders", true).toBool();
    isViewMode = globalSettings->value("isViewMode", false).toBool();
    git_repo = globalSettings->value("git_repo").value<QString>();
    git_user = globalSettings->value("git_user").value<QString>();
    git_token = globalSettings->value("git_token").value<QString>();
    isAutoSyncB = globalSettings->value("isAutoSync").value<bool>();

    firstRun = globalSettings->value("firstRun", true).value<bool>();

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
    isAutoCheckUpdates = globalSettings->value("isAutoCheckUpdates").value<bool>();
    appLang = globalSettings->value("lang").value<int>();

    qDebug() << " " << dir << selectedFont << font_size << theme << isCustomTitlebar << sortNotesRole << isAutoSyncing
             << isVisibleNotesList << isVisibleFolders << isViewMode << git_repo << git_user << git_token << isAutoSyncB
             << isCustomTheme << isAutoCheckUpdates;
    qDebug() << "App Language: " << appLang;
}

void MainWindow::setConnectionStatus()
{
    if (checkConnection())
    {
        isConnected->setIcon(QPixmap(":/connected.png").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        isConnected->setToolTip(tr("Connected"));
        sizeGrip->setStyleSheet("background-color: #a9bf85; border-radius: 6px;");
    }
    else
    {
        isConnected->setIcon(
            QPixmap(":/disconnected.png").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        isConnected->setToolTip(tr("Disconnected"));
    }

    if (isAutoSyncing)
    {
        isAutoSync->setIcon(
            QPixmap(":/auto_sync_on.png").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        isAutoSync->setToolTip(tr("Auto sync on"));
        sizeGrip->setStyleSheet("background-color: #a9bf85; border-radius: 6px;");
    }
    else
    {
        isAutoSync->setIcon(
            QPixmap(":/auto_sync_off.png").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        isAutoSync->setToolTip(tr("Auto sync off"));
    }
}

void MainWindow::createCustomTitlebar()
{
    closeBtn->setFixedSize(13, 13);
    minimizeBtn->setFixedSize(13, 13);
    maximizeBtn->setFixedSize(13, 13);

    closeBtn->setStyleSheet("QPushButton {"
                            "    border-radius: 6px;"
                            "    border-color: rgba(0, 0, 0, 0);"
                            "    background-color: #e08581;"
                            "    background-repeat: no-repeat;"
                            "    background-attachment: fixed;"
                            "}"

                            "QPushButton:hover {"
                            "    border-radius: 6px;"
                            "    border-color: rgba(0, 0, 0, 0);"
                            "    background-repeat: no-repeat;"
                            "    background-color: #e06a65;"
                            "    background-attachment: fixed;"
                            "}");

    minimizeBtn->setStyleSheet("QPushButton {"
                               "    border-radius: 6px;"
                               "    border-color: rgba(0, 0, 0, 0);"
                               "    background-color: #d8bd85;"
                               "    background-repeat: no-repeat;"
                               "    background-attachment: fixed;"
                               "}"

                               "QPushButton:hover {"
                               "    border-radius: 6px;"
                               "    border-color: rgba(0, 0, 0, 0);"
                               "    background-repeat: no-repeat;"
                               "    background-color: #d8b772;"
                               "    background-attachment: fixed;"
                               "}");

    maximizeBtn->setStyleSheet("QPushButton {"
                               "    border-radius: 6px;"
                               "    border-color: rgba(0, 0, 0, 0);"
                               "    background-color: #a9bf85;"
                               "    background-repeat: no-repeat;"
                               "    background-attachment: fixed;"
                               "}"

                               "QPushButton:hover {"
                               "    border-radius: 6px;"
                               "    border-color: rgba(0, 0, 0, 0);"
                               "    background-color: #9bbf60;"
                               "    background-repeat: no-repeat;"
                               "    background-attachment: fixed;"
                               "}");

    if (isCustomTitlebar)
    {
        this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Window);

        winControlL->addWidget(closeBtn);
        winControlL->addWidget(minimizeBtn);
        winControlL->addWidget(maximizeBtn);
    }
}

void MainWindow::deleteAllData()
{
    QMessageBox reply;
    reply.setWindowFlags(Qt::FramelessWindowHint);
    reply.setText(tr("Do you really want to delete all the data?"));
    reply.setWindowTitle(tr("CodeKeeper"));
    reply.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    reply.setDefaultButton(QMessageBox::No);

    if (reply.exec() == QMessageBox::Yes)
    {
        if (QFile::exists(dir))
        {
            if (QFile::remove(dir))
            {
                qDebug() << "File" << dir << "deleted";
            }
            else
            {
                qDebug() << "Error: " << dir;
            }
        }
        else
        {
            qDebug() << "File" << dir << "not found.";
        }

        globalSettings->clear();
        qDebug() << "Data deleted";
    }
    else
    {
        qDebug() << "Data deletion cancelled by user.";
    }
}

void MainWindow::fOpenAccountWindow()
{
    QThread *accountWindowThread = new QThread;
    QObject::connect(accountWindowThread, &QThread::started, this, [this]() {
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

        qDebug() << "accountWindowThread started";
    });
    accountWindowThread->start();
}

void MainWindow::openSettingsWindow()
{
    QThread *settingsWindowThread = new QThread;
    QObject::connect(settingsWindowThread, &QThread::started, this, [this]() {
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

        qDebug() << "settingsWindowThread started";
    });
    settingsWindowThread->start();
}

void MainWindow::setSettingsData()
{
}

bool MainWindow::checkConnection()
{
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("https://github.com/"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    QObject::connect(&nam, SIGNAL(finished(QNetworkReply *)), &loop, SLOT(quit()));

    if (!reply->isFinished())
    {
        loop.exec();
        if (reply->error() == QNetworkReply::NoError)
        {
            // qDebug() << "You are connected to the internet :)";
            return true;
        }
        else
        {
            qWarning() << "You have an net error:" << reply->errorString();
            return false;
        }
    }
}

void MainWindow::openSyncWindow()
{
    QThread *syncWindowThread = new QThread;
    QObject::connect(syncWindowThread, &QThread::started, this, [this]() {
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

        qDebug() << "syncWindowThread started";
    });
    syncWindowThread->start();
}

void MainWindow::openFolder()
{
    QString str = QFileDialog::getExistingDirectory(0, tr("Select a directory"));
    if (!str.isEmpty())
    {
        globalSettings->setValue("path", str);
        qDebug() << "" << str;
    }
}

void MainWindow::updateWindowTitle()
{
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QListWidget *lists[] = {notStartedProjects, startedProjects, finishlineProjects, finishedProjects,
                            incompleteTasks,    inprocessTasks,  completeTasks};

    for (QListWidget *list : lists)
    {
        QListWidgetItem *selectedItem = list->currentItem();
        if (selectedItem && selectedItem != item)
        {
            list->setCurrentItem(nullptr);
        }
    }
}

void MainWindow::setStyle(QFont *selectedFont, int *font_size_int)
{
    qDebug() << "Applying preferences";

    int fontId = QFontDatabase::addApplicationFont(":/CustomFont.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    if (fontFamilies.isEmpty())
    {
        qWarning("Failed to load font.");
    }

    QString font_size = QString::number(*font_size_int);
    QString font_size_clock = QString::number(*font_size_int * 11);
    QString font_size_date = QString::number(*font_size_int * 1.6);
    QString font_size_hello = QString::number(*font_size_int * 1.4);

    timeLabel->setFont(custom_font);
    timeLabel->setStyleSheet("background: transparent; font-size: " + font_size_clock + "pt; color: #a9bf85;");

    dateLabel->setFont(custom_font);
    dateLabel->setStyleSheet("background: transparent; font-size: " + font_size_date + "pt; color: #a9bf85;");

    helloLabel->setFont(custom_font);
    helloLabel->setStyleSheet("background: transparent; font-size: " + font_size_hello + "pt; color: #a9bf85;");

    projectsMainLabel->setFont(*selectedFont);
    projectsMainLabel->setStyleSheet("font-size: " + font_size + "px;");

    notesList->setFont(*selectedFont);
    notesList->setStyleSheet("font-size: " + font_size + "px; background-color: rgba(47, 51, 77, 0);");

    menuButton->setFont(*selectedFont);

    tasksMenuBtn->setFont(*selectedFont);

    projectsList->setFont(*selectedFont);
    projectsList->setStyleSheet("font-size: " + font_size + "px;");

    noteEdit->setFont(*selectedFont);
    noteEdit->setStyleSheet("font-size: " + font_size + "px;");

    noteNameLabel->setFont(*selectedFont);
    noteNameLabel->setStyleSheet("font-size: " + font_size + "px; color: #8ebecf;");

    taskText->setFont(*selectedFont);
    taskText->setStyleSheet("font-size: " + font_size + "px;");

    incompleteTasks->setStyleSheet("QListWidget {"
                                   "font-size: " +
                                   font_size +
                                   "pt;"
                                   "padding: 0px;"
                                   "border-radius: 15px;"
                                   "}"
                                   "QListWidget::item:selected {"
                                   "background-color: rgba(211, 102, 107, 100); color: #000000;"
                                   "}"
                                   "QListWidget::Item {"
                                   "margin: 0px; color: #000000;"
                                   "background-color: #e08581;"
                                   "border-radius: 5px;"
                                   "font-size: " +
                                   font_size +
                                   "pt;"
                                   "}");

    inprocessTasks->setStyleSheet("QListWidget {"
                                  "font-size: " +
                                  font_size +
                                  "pt;"
                                  "padding: 0px;"
                                  "border-radius: 15px;"
                                  "}"
                                  "QListWidget::item:selected {"
                                  "background-color: rgba(231, 232, 141, 75);"
                                  "}"
                                  "QListWidget::Item {"
                                  "margin: 0px;"
                                  "background-color: #d8bd85; "
                                  "color: #000000; text-decoration: underline; "
                                  "border-radius: 5px;"
                                  "font-size: " +
                                  font_size +
                                  "pt;"
                                  "}");

    completeTasks->setStyleSheet("QListWidget {"
                                 "font-size: " +
                                 font_size +
                                 "pt;"
                                 "padding: 0px;"
                                 "border-radius: 15px;"
                                 "}"
                                 "QListWidget::item:selected {"
                                 "background-color: rgba(195, 232, 141, 75);"
                                 "border-width: 2px; border-color: #a9bf85;"
                                 "}"
                                 "QListWidget::Item {"
                                 "margin: 0px;"
                                 "background-color: #a9bf85; "
                                 "color: #000000;"
                                 "border-radius: 5px;"
                                 "font-size: " +
                                 font_size +
                                 "pt;"
                                 "}");

    notStartedProjects->setStyleSheet("QListWidget {"
                                      "font-size: " +
                                      font_size +
                                      "pt;"
                                      "padding: 0px;"
                                      "border-radius: 15px;"
                                      "}"
                                      "QListWidget::item:selected {"
                                      "border-width: 2px; border-color: #a9bf85;"
                                      "background-color: rgba(211, 102, 107, 75);"
                                      "}"
                                      "QListWidget::Item {"
                                      "margin: 0px;"
                                      "background-color: #e08581;"
                                      "color: #000000; "
                                      "border-radius: 5px;"
                                      "border-color: #ff757f; "
                                      "font-size: " +
                                      font_size +
                                      "pt;"
                                      "}");

    startedProjects->setStyleSheet("QListWidget {"
                                   "font-size: " +
                                   font_size +
                                   "pt;"
                                   "padding: 0px;"
                                   "border-radius: 15px;"
                                   "}"
                                   "QListWidget::item:selected {"
                                   "border-width: 2px; border-color: #a9bf85;"
                                   "background-color: rgba(231, 232, 141, 75);"
                                   "}"
                                   "QListWidget::Item {"
                                   "margin: 0px;"
                                   "background-color: #d8bd85; color: #000000; "
                                   "border-radius: 5px;"
                                   "font-size: " +
                                   font_size +
                                   "pt;"
                                   "}");

    finishlineProjects->setStyleSheet("QListWidget {"
                                      "font-size: " +
                                      font_size +
                                      "pt;"
                                      "padding: 0px;"
                                      "border-radius: 15px;"
                                      "}"
                                      "QListWidget::item:selected {"
                                      "border-width: 2px; border-color: #a9bf85;"
                                      "background-color: rgba(126, 156, 216, 75)"
                                      "}"
                                      "QListWidget::Item {"
                                      "margin: 0px;"
                                      "background-color: #85b9b3; "
                                      "color: #000000;"
                                      "border-radius: 5px;"
                                      "font-size: " +
                                      font_size +
                                      "pt;"
                                      "}");

    finishedProjects->setStyleSheet("QListWidget {"
                                    "font-size: " +
                                    font_size +
                                    "pt;"
                                    "border-radius: 15px;"
                                    "padding: 0px;"
                                    "}"
                                    "QListWidget::item:selected {"
                                    "border-width: 2px; border-color: #a9bf85;"
                                    "background-color: rgba(195, 232, 141, 75);"
                                    "}"
                                    "QListWidget::Item {"
                                    "margin: 0px;"
                                    "background-color: #a9bf85; color: #000000; "
                                    "border-radius: 5px;"
                                    "font-size: " +
                                    font_size +
                                    "pt;"
                                    "}");

    fProjects->setFont(*selectedFont);
    flProjects->setFont(*selectedFont);
    nsProjects->setFont(*selectedFont);
    sProjects->setFont(*selectedFont);

    nsProjects->setStyleSheet("font-size: " + font_size + "px;");
    sProjects->setStyleSheet("font-size: " + font_size + "px;");
    flProjects->setStyleSheet("font-size: " + font_size + "px;");
    fProjects->setStyleSheet("font-size: " + font_size + "px;");

    projectsMainLabel->setFont(*selectedFont);
    notStartedProjects->setFont(*selectedFont);
    startedProjects->setFont(*selectedFont);
    finishlineProjects->setFont(*selectedFont);
    finishedProjects->setFont(*selectedFont);

    projectsMenu->setFont(*selectedFont);

    tabs->setFont(*selectedFont);
    tabs->setStyleSheet("QTabBar::tab { font-size: " + font_size +
                        "pt;} QTabBar::tab:selected {font-size: " + font_size + "px;}");

    totalProjectsL->setFont(*selectedFont);
    totalProjectsL->setStyleSheet("font-size: " + font_size + "px;");

    incompleteTasks->setFont(*selectedFont);
    inprocessTasks->setFont(*selectedFont);
    completeTasks->setFont(*selectedFont);

    label_1->setFont(*selectedFont);
    label_1->setPixmapSize(*font_size_int);
    label_1->setCustomStyleSheet("font-size: " + font_size + "px; color: #a9bf85;");
    label_2->setFont(*selectedFont);
    label_2->setPixmapSize(*font_size_int);
    label_2->setCustomStyleSheet("font-size: " + font_size + "px; color: #a9bf85;");
    label_3->setFont(*selectedFont);
    label_3->setPixmapSize(*font_size_int);
    label_3->setCustomStyleSheet("font-size: " + font_size + "px; color: #a9bf85;");

    windowTitle->setFont(*selectedFont);
    windowTitle->setStyleSheet("font-size: " + font_size + "px;");

    tasksProgress->setFont(*selectedFont);
    tasksProgress->setStyleSheet("background-color: #e08581; selection-background-color: "
                                 "#a9bf85; color: #222436; font-size: " +
                                 font_size + "pt;");

    openSettingsBtn->setFont(*selectedFont);
    openSettingsBtn->setStyleSheet(
        "QPushButton {background-color: transparent; border: none; margin: 7px; font-size: " + font_size + "px;} ");

    syncDataBtn->setFont(*selectedFont);
    syncDataBtn->setStyleSheet("QPushButton {background-color: transparent; margin: 7px; "
                               "border: none; color: #ffffff; font-size: " +
                               font_size + "pt;}");

    menu->setStyleSheet("font-size: " + font_size + "px;");
    menu->setFont(*selectedFont);

    verLabel->setStyleSheet("font-size: " + font_size + "px; color: #e08581;");
    verLabel->setFont(custom_font);

    tasksMenu->setFont(*selectedFont);
    tasksMenu->setStyleSheet("font-size: " + font_size + "px;");

    projectsMenu->setFont(*selectedFont);
    projectsMenu->setStyleSheet("font-size: " + font_size + "px;");

    openAccountWindow->setFont(*selectedFont);
    openAccountWindow->setStyleSheet(
        "QPushButton {background-color: transparent; border: none; margin: 7px; font-size: " + font_size + "px;} ");

    mainTabButton->setStyleSheet(
        "QPushButton { margin: 7px; border-width: 2px; border-color: #a9bf85; background-color: transparent;} "
        "QPushButton:hover {border-color: #a9bf85; background-color: transparent;}");
    tasksTabButton->setStyleSheet(
        "QPushButton { margin: 7px; border-width: 2px; border-color: transparent; background-color: transparent;} "
        "QPushButton::hover {border-color: #a9bf85; background-color: transparent;}");
    notesTabButton->setStyleSheet(
        "QPushButton { margin: 7px; border-width: 2px; border-color: transparent; background-color: transparent;} "
        "QPushButton::hover {border-color: #a9bf85; background-color: transparent;}");
    projectsTabButton->setStyleSheet(
        "QPushButton { margin: 7px; border-width: 2px; border-color: transparent; background-color: transparent;} "
        "QPushButton::hover {border-color: #a9bf85; background-color: transparent;}");

    setH1B->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setH2B->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setH3B->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setListB->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setLinkB->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setBoldB->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setItalicB->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setStrikeB->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setTaskB->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setNumListB->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setTableB->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");
    setQuoteB->setStyleSheet("background-color: transparent; border: none; margin-left: 4px;");

    setH1B->setToolTip(tr("Set heading 1"));
    setH2B->setToolTip(tr("Set heading 2"));
    setH3B->setToolTip(tr("Set heading 3"));
    setListB->setToolTip(tr("List"));
    setLinkB->setToolTip(tr("Link"));
    setBoldB->setToolTip(tr("Bold text"));
    setItalicB->setToolTip(tr("Italic text"));
    setStrikeB->setToolTip(tr("Strikethrough text"));
    setTaskB->setToolTip(tr("Task"));
    setNumListB->setToolTip(tr("Numbered list"));
    setTableB->setToolTip(tr("Insert table"));
    setQuoteB->setToolTip(tr("Set quote"));

    menuButton->setStyleSheet("border: 5px; border-radius: 10px;");
    tasksMenuBtn->setStyleSheet("border: 5px; border-radius: 10px;");
    projectsMenuButton->setStyleSheet("border: 5px; border-radius: 10px;");

    isAutoSync->setStyleSheet("border: 0px; background-color: transparent;");
    isConnected->setStyleSheet("border: 0px; background-color: transparent;");

    fProjects->setStyleSheet("font-size: " + font_size + "px;");
    flProjects->setStyleSheet("font-size: " + font_size + "px;");
    sProjects->setStyleSheet("font-size: " + font_size + "px;");
    nsProjects->setStyleSheet("font-size: " + font_size + "px;");
}

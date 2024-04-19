#include "mainwindow.h"

void SettingsWindow::QuitW()
{
    this->close();
}

void SettingsWindow::closeEvent(QCloseEvent *event)
{
    MainWindow *mainWindow = static_cast<MainWindow *>(parent());
    mainWindow->setGraphicsEffect(nullptr);
    QMainWindow::closeEvent(event);
}

void SettingsWindow::checkUpdates() { }

void SettingsWindow::saveData()
{
    qDebug() << "saveData";

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    QMessageBox *messageBox = new QMessageBox();

    QFont selectedFont = fontSelector->currentFont();
    globalSettings->setValue("font", selectedFont);

    int font_size = fontSize->value();
    globalSettings->setValue("fontSize", font_size);

    QString theme = themeSelector->currentText();
    globalSettings->setValue("theme", theme);


    QString path = pathToFolder->text();
    globalSettings->setValue("path", QVariant(path));

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

    messageBox->setIcon(QMessageBox::Information);
    messageBox->setWindowTitle("CodeKeeper - Settings");
    messageBox->setText("To apply the settings, restart the application.");

    messageBox->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    // messageBox->exec();

    MainWindow *mainWindow = static_cast<MainWindow *>(parent());
    setFontPr2(&selectedFont, &font_size);
    mainWindow->setFontPr1(&selectedFont, &font_size);
}

void SettingsWindow::fopenFolder()
{
    QString str = QFileDialog::getExistingDirectory(0, "Select a directory");
    if (!str.isEmpty()) {
        QDir path = str;
        globalSettings->setValue("path", QVariant(str));
        qDebug() << path;
        pathToFolder->setText(str);

        QMessageBox *messageBox = new QMessageBox();

        messageBox->setIcon(QMessageBox::Information);
        messageBox->setWindowTitle("CodeKeeper - Settings");
        messageBox->setText("To apply the settings, restart the application.");

        messageBox->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
        messageBox->exec();
    }
}

void SettingsWindow::setFontPr2(QFont *selectedFont, int *font_size_int)
{
    QString font_size = QString::number(*font_size_int);

    // set font
    tabs->setFont(*selectedFont);
    tabs->setStyleSheet("font-size: " + font_size + "pt;");

    saveBtn->setFont(*selectedFont);
    saveBtn->setStyleSheet("font-size: " + font_size + "pt;");

    quitBtn->setFont(*selectedFont);
    quitBtn->setStyleSheet("font-size: " + font_size + "pt;");

    appName->setFont(*selectedFont);

    urlToRepo->setFont(*selectedFont);
    urlToRepo->setStyleSheet("font-size: " + font_size + "pt;");

    versionInfo->setFont(*selectedFont);
    versionInfo->setStyleSheet("font-size: " + font_size + "pt;");

    checkUpdatesBtn->setFont(*selectedFont);
    checkUpdatesBtn->setStyleSheet("font-size: " + font_size + "pt;");

    fontSize->setFont(*selectedFont);
    fontSize->setStyleSheet("font-size: " + font_size + "pt;");

    fontSelector->setFont(*selectedFont);
    fontSelector->setStyleSheet("font-size: " + font_size + "pt;");

    themeSelector->setFont(*selectedFont);
    themeSelector->setStyleSheet("font-size: " + font_size + "pt;");

    gitLabel->setFont(*selectedFont);

    gitLabel2->setFont(*selectedFont);

    gitToken->setFont(*selectedFont);
    gitToken->setStyleSheet("font-size: " + font_size + "pt;");

    gitUser->setFont(*selectedFont);
    gitUser->setStyleSheet("font-size: " + font_size + "pt;");

    gitRepo->setFont(*selectedFont);
    gitRepo->setStyleSheet("font-size: " + font_size + "pt;");

    autoSyncAfterStart->setFont(*selectedFont);
    autoSyncAfterStart->setStyleSheet("font-size: " + font_size + "pt;");

    isDate->setFont(*selectedFont);
    isDate->setStyleSheet("font-size: " + font_size + "pt;");

    isTime->setFont(*selectedFont);
    isTime->setStyleSheet("font-size: " + font_size + "pt;");

    isHost->setFont(*selectedFont);
    isHost->setStyleSheet("font-size: " + font_size + "pt;");

    mainTitle->setFont(*selectedFont);

    fontLabel->setFont(*selectedFont);
    fontSizeLabel->setFont(*selectedFont);

    fontSizeLabel->setFont(*selectedFont);
    fontSizeLabel->setStyleSheet("font-size: " + font_size + "pt;");

    themeLabel->setFont(*selectedFont);
    themeLabel->setStyleSheet("font-size: " + font_size + "pt;");

    storageLabel->setFont(*selectedFont);

    pathToFolder->setFont(*selectedFont);
    pathToFolder->setStyleSheet("font-size: " + font_size + "pt;");

    openFolder->setFont(*selectedFont);
    openFolder->setStyleSheet("font-size: " + font_size + "pt;");

    customTitleBar->setFont(*selectedFont);
    customTitleBar->setStyleSheet("font-size: " + font_size + "pt;");

    // set Data
    fontSelector->setCurrentFont(*selectedFont);
    fontSize->setValue(font_size.toInt());
    themeSelector->setCurrentText(theme);
}

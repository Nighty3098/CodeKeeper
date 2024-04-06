#include "mainwindow.h"

void SettingsWindow::QuitW() { this->close(); }

void SettingsWindow::closeEvent(QCloseEvent *event) {
    MainWindow *mainWindow = static_cast<MainWindow *>(parent());
    mainWindow->setGraphicsEffect(nullptr);
    QMainWindow::closeEvent(event);
}

void SettingsWindow::checkUpdates() {}

void SettingsWindow::saveData() {
    qDebug() << "saveData";

    globalSettings = new QSettings("CodeKeeper", "CodeKeeper");
    QMessageBox *messageBox = new QMessageBox();

    QFont selectedFont = fontSelector->currentFont();
    globalSettings->setValue("font", selectedFont);

    int font_size = fontSize->value();
    globalSettings->setValue("fontSize", font_size);

    QString theme = themeSelector->currentText();
    globalSettings->setValue("theme", theme);

    messageBox->setIcon(QMessageBox::Information);
    messageBox->setWindowTitle("CodeKeeper - Settings");
    messageBox->setText("To apply the settings, restart the application.");
    
    messageBox->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    messageBox->exec();
    
    setFontPr2();
}

void SettingsWindow::fopenFolder() {
    QString str = QFileDialog::getExistingDirectory(0, "Select a directory");
    if(!str.isEmpty()) {
        globalSettings->setValue("path", str);
        qDebug() << str;
        pathToFolder->setText(str);
    }
}

void SettingsWindow::setFontPr2() {

    // set font 
    tabs->setFont(selectedFont);
    tabs->setStyleSheet("font-size: " + font_size + "pt;");

    saveBtn->setFont(selectedFont);
    saveBtn->setStyleSheet("font-size: " + font_size + "pt;");

    quitBtn->setFont(selectedFont);
    quitBtn->setStyleSheet("font-size: " + font_size + "pt;");

    appName->setFont(selectedFont);

    urlToRepo->setFont(selectedFont);
    urlToRepo->setStyleSheet("font-size: " + font_size + "pt;");

    versionInfo->setFont(selectedFont);
    versionInfo->setStyleSheet("font-size: " + font_size + "pt;");

    checkUpdatesBtn->setFont(selectedFont);
    checkUpdatesBtn->setStyleSheet("font-size: " + font_size + "pt;");

    fontSize->setFont(selectedFont);
    fontSize->setStyleSheet("font-size: " + font_size + "pt;");

    fontSelector->setFont(selectedFont);
    fontSelector->setStyleSheet("font-size: " + font_size + "pt;");

    themeSelector->setFont(selectedFont);
    themeSelector->setStyleSheet("font-size: " + font_size + "pt;");

    gitLabel->setFont(selectedFont);

    gitLabel2->setFont(selectedFont);

    gitToken->setFont(selectedFont);
    gitToken->setStyleSheet("font-size: " + font_size + "pt;");

    gitUser->setFont(selectedFont);
    gitUser->setStyleSheet("font-size: " + font_size + "pt;");

    gitRepo->setFont(selectedFont);
    gitRepo->setStyleSheet("font-size: " + font_size + "pt;");

    autoSyncAfterStart->setFont(selectedFont);
    autoSyncAfterStart->setStyleSheet("font-size: " + font_size + "pt;");

    isDate->setFont(selectedFont);
    isDate->setStyleSheet("font-size: " + font_size + "pt;");

    isTime->setFont(selectedFont);
    isTime->setStyleSheet("font-size: " + font_size + "pt;");

    isHost->setFont(selectedFont);
    isHost->setStyleSheet("font-size: " + font_size + "pt;");

    mainTitle->setFont(selectedFont);

    fontLabel->setFont(selectedFont);
    fontSizeLabel->setFont(selectedFont);

    fontSizeLabel->setFont(selectedFont);
    fontSizeLabel->setStyleSheet("font-size: " + font_size + "pt;");

    themeLabel->setFont(selectedFont);
    themeLabel->setStyleSheet("font-size: " + font_size + "pt;");

    storageLabel->setFont(selectedFont);

    pathToFolder->setFont(selectedFont);
    pathToFolder->setStyleSheet("font-size: " + font_size + "pt;");

    openFolder->setFont(selectedFont);
    openFolder->setStyleSheet("font-size: " + font_size + "pt;");

    // set Data
    fontSelector->setCurrentFont(selectedFont);
    fontSize->setValue(font_size.toInt());
    themeSelector->setCurrentText(theme);

    
}

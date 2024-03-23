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
}

void SettingsWindow::fopenFolder() {
    QString str = QFileDialog::getExistingDirectory(0, "Select a directory");
    if(!str.isEmpty()) {
        globalSettings->setValue("path", str);
        qDebug() << str;
        pathToFolder->setText(str);
    }
}

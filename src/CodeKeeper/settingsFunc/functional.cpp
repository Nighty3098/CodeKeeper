void SettingsWindow::SaveData() {
    this->close();
}

void SettingsWindow::QuitW() {
    this->close();
}


void SettingsWindow::closeEvent(QCloseEvent *event) {
    MainWindow *mainWindow = static_cast<MainWindow*>(parent());
    mainWindow->setGraphicsEffect(nullptr);
    QMainWindow::closeEvent(event);
}




void SettingsWindow::checkUpdates() {
}
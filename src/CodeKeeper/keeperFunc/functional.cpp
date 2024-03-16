void MainWindow::openSettingsWindow() {
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(10);
    this->setGraphicsEffect(blurEffect);

    settingsWindow = new SettingsWindow(this);

    settingsWindow->show();
}

void MainWindow::addNewTask() {
    QString text = taskText->text();
    taskText->clear();
    incompleteTasks->addItem(text);
}
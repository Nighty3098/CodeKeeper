#include <QDateTime>

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

void MainWindow::hideNotesList() {

}

QString getCurrentDateTimeString() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    return dateTimeString;
}

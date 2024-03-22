#include <QDateTime>
#include <QSyntaxHighlighter>

void MainWindow::openSettingsWindow() {
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(10);
    this->setGraphicsEffect(blurEffect);

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

void MainWindow::addNewTask() {
    QString text = taskText->text();
    if (!text.isEmpty()) {
        taskText->clear();
        incompleteTasks->addItem(text);
    } else {
        qDebug() << "Task is empty";
    }
}

void MainWindow::removeTask() {}

void MainWindow::hideNotesList() {
    notesList->setVisible(!notesList->isVisible());
    globalSettings->setValue("isVisibleNotesList", notesList->isVisible());
}

void MainWindow::showPreview() {
    // QSyntaxHighlighter *highlighter = new QSyntaxHighlighter(QTextDocument);
    // highlighter->setDocument(mdPreview->document());

    mdPreview->setVisible(!mdPreview->isVisible());
    globalSettings->setValue("isVisiblePreview", mdPreview->isVisible());

    connect(noteEdit, &QMarkdownTextEdit::textChanged, this,
            &MainWindow::updateMDPreview);
}

void MainWindow::updateMDPreview() {
    QString text = noteEdit->toPlainText();

    mdPreview->setMarkdown(text);
}

QString getCurrentDateTimeString() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    return dateTimeString;
}

void MainWindow::setHeader() {
    QString text = noteEdit->toPlainText();

    QStringList lines = text.split("\n");
    QString sourceName = lines.first();

    QString noteName = sourceName.mid(0, 40) + "...";

    noteNameLabel->setText(noteName);
}

void MainWindow::openNotesFolder(QString& path, QString folderName) {

}

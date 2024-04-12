QModelIndex indexFromItem(QTreeWidgetItem *item, int column) {}

bool createFile(const QString &path) {
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "Just start typing...";
        file.close();
        qDebug() << "File created successfully at" << path;
        return true;
    } else {
        qDebug() << "Failed to create file at" << path << ": "
                 << file.errorString();
        return false;
    }
}

void MainWindow::updateMDPreview() {
    QString text = noteEdit->toPlainText();

    mdPreview->setMarkdown(text);
}

void MainWindow::saveNote() {
    QModelIndex index = notesList->currentIndex();
    if (index.isValid() && notesDirModel->fileInfo(index).isFile()) {
        QString filePath = notesDirModel->filePath(index);
        QString text = noteEdit->toPlainText();

        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            stream << text;
            file.close();
            // qDebug() << "Success", "Text written to file successfully.";
        } else {
            qDebug() << "Error", "Failed to open file for writing.";
        }
    } else {
        qDebug() << "Error", "Please select a valid file.";
    }
}

void MainWindow::onNoteDoubleClicked() {
    QModelIndex index = notesList->currentIndex();
    QString path_to_note = notesDirModel->filePath(index);

    QFile file(path_to_note);

    QRegularExpression re("(\\.md|\\.html|\\.txt)$");
    if(notesDirModel->fileInfo(index).isFile()) {
        if (re.match(path_to_note).hasMatch()) {
            if (file.open(QIODevice::ReadWrite)) {
                qDebug() << path_to_note;
                QTextStream stream(&file);
                noteEdit->setPlainText(stream.readAll());
                file.close();
            }
        }
    }
}

void MainWindow::hideNotesList() {
    notesList->setVisible(!notesList->isVisible());
    globalSettings->setValue("isVisibleNotesList", notesList->isVisible());
}

void MainWindow::showPreview() {
    mdPreview->setVisible(!mdPreview->isVisible());
    globalSettings->setValue("isVisiblePreview", mdPreview->isVisible());
}

void MainWindow::setHeader() {
    QString text = noteEdit->toPlainText();

    QStringList lines = text.split("\n");
    QString sourceName = lines.first();

    QString noteName = sourceName.mid(0, 40) + "...";

    noteNameLabel->setText(noteName);
}

void MainWindow::toViewMode() {
    bool isView = noteEdit->isVisible();

    setH1B->setVisible(!isView);
    setH2B->setVisible(!isView);
    setH3B->setVisible(!isView);
    setListB->setVisible(!isView);
    setLinkB->setVisible(!isView);
    setBoldB->setVisible(!isView);
    setItalicB->setVisible(!isView);
    setStrikeB->setVisible(!isView);
    setTaskB->setVisible(!isView);

    notesList->setVisible(!isView);
    noteEdit->setVisible(!isView);

    showList->setChecked(!isView);

    showRender->setChecked(isView);
    mdPreview->setVisible(isView);
}

void MainWindow::createFolder() {
    QModelIndex index = notesList->currentIndex();

    if (index.isValid()) {
        QString name = QInputDialog::getText(this, "Name", "Folder name");
        if (!name.isEmpty()) {
            notesDirModel->mkdir(index, name);
        }
    }
}

void MainWindow::createNote() {
    QModelIndex index = notesList->currentIndex();

    if (index.isValid()) {
        QString name = QInputDialog::getText(this, "Name", "Note name");
        if (!name.isEmpty()) {
            name = name + ".md";
            QString path_to_note = notesDirModel->filePath(index) + "/" + name;

            createFile(path_to_note);
        }
    }
}

void MainWindow::removeNote() {
    QModelIndex index = notesList->currentIndex();
    if (index.isValid()) {
        if (notesDirModel->fileInfo(index).isDir()) {
            notesDirModel->rmdir(index);
        } else {
            notesDirModel->remove(index);
        }
    }
}

void MainWindow::setH1() {
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("# ");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setH2() {
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("## ");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setH3() {
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("### ");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setList() {
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText(" - ");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setLink() {
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("[Link](");

    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    cursor.insertText(")");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setBold() {
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("**");

    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    cursor.insertText("**");

    noteEdit->setTextCursor(cursor);
}

void MainWindow::setItalic() {
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("*");

    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    cursor.insertText("*");

    noteEdit->setTextCursor(cursor);
}

void MainWindow::setStrike() {
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("~");

    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    cursor.insertText("~");

    noteEdit->setTextCursor(cursor);
}

void MainWindow::setTask() {
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText(" - [ ] - ");

    noteEdit->setTextCursor(cursor);
}

QModelIndex indexFromItem(QTreeWidgetItem *item, int column) {
}

void MainWindow::updateMDPreview() {
    QString text = noteEdit->toPlainText();

    mdPreview->setMarkdown(text);
}

void MainWindow::onNoteDoubleClicked(QTreeWidgetItem *item) {
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
    bool isView =  noteEdit->isVisible();

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

    if(index.isValid()) {
        QString name = QInputDialog::getText(this, "Name", "Folder name");
        if(!name.isEmpty()) {
            notesDirModel->mkdir(index, name);
        }
    }
}

void MainWindow::createNote() {
    QModelIndex index = notesList->currentIndex();

    if(index.isValid()) {
        QString name = QInputDialog::getText(this, "Name", "Note name");
        if(!name.isEmpty()) {
            QString fileName = name + ".md";
            notesDirModel->mkdir(index, fileName);
        }
    }
}

void MainWindow::removeNote() {
    QModelIndex index = notesList->currentIndex();
    if(index.isValid()) {
        if(notesDirModel->fileInfo(index).isDir()) {
            notesDirModel->rmdir(index);
        }
        else {
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

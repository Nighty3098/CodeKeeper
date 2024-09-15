#include <QFile>

QModelIndex indexFromItem(QTreeWidgetItem *item, int column)
{
}

bool createFile(const QString &path)
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << "Just start typing...";
        file.close();
        qDebug() << "File created successfully at " << path;
        return true;
    }
    else
    {
        qWarning() << "Failed to create file at " << path << " : " << file.errorString();
        return false;
    }
}

void MainWindow::loadNotes()
{
    dir = globalSettings->value("path").value<QString>();
    notesDirModel->setRootPath(dir);

    notesList->setAnimated(true);
    notesList->setWordWrap(true);
    notesList->setDragDropMode(QAbstractItemView::DragDrop);
    notesList->setDefaultDropAction(Qt::MoveAction);
    notesList->setDragEnabled(true);
    notesList->setMinimumWidth(100);
    notesList->setHeaderHidden(true);
    notesList->setColumnHidden(1, true);
    notesList->setSortingEnabled(true);
    notesList->setModel(notesDirModel);
    notesList->setRootIndex(notesDirModel->index(dir));

    notesList->setColumnWidth(0, 297);
    notesList->setColumnHidden(1, true);
    notesList->setColumnHidden(2, true);
    notesList->setColumnHidden(3, true);
    notesList->setColumnHidden(4, true);
}

void MainWindow::setSortByTime()
{
    notesList->sortByColumn(3, Qt::SortOrder());
}

void MainWindow::setSortByName()
{
    notesList->sortByColumn(0, Qt::SortOrder());
}

void MainWindow::saveNote()
{
    QModelIndex index = notesList->currentIndex();
    if (index.isValid() && notesDirModel->fileInfo(index).isFile())
    {
        QString filePath = notesDirModel->filePath(index);
        QString text = noteEdit->toPlainText();

        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << text;
            file.close();
            // ! qDebug() << "Success, Text written to file
            // successfully.";
        }
        else
        {
            qWarning() << "Error, Failed to open file for writing.";
        }
    }
    else
    {
        qWarning() << "Error,  Please select a valid file.";
    }
}

void MainWindow::onNoteDoubleClicked()
{
    QModelIndex index = notesList->currentIndex();
    QString path_to_note = notesDirModel->filePath(index);

    QFile file(path_to_note);

    QRegularExpression re("(\\.md|\\.html|\\.txt)$");
    if (notesDirModel->fileInfo(index).isFile())
    {
        if (re.match(path_to_note).hasMatch())
        {
            if (file.open(QIODevice::ReadWrite))
            {
                qDebug() << path_to_note;
                QTextStream stream(&file);
                noteEdit->setPlainText(stream.readAll());
                file.close();
            }
        }
        else
        {
            noteEdit->setPlainText(tr("### File format not supported."));
            qWarning() << "File format not supported";
        }
    }
}

void MainWindow::hideNotesList()
{
    notesList->setVisible(!notesList->isVisible());
    globalSettings->setValue("isVisibleNotesList", notesList->isVisible());
}

void MainWindow::setHeader()
{
    QString text = noteEdit->toPlainText();

    QStringList lines = text.split("\n");
    QString sourceName = lines.first();

    QString noteName = sourceName.mid(0, 40) + "...";

    noteNameLabel->setText(noteName);
}

void MainWindow::toViewMode()
{
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
    setNumListB->setVisible(!isView);
    setTableB->setVisible(!isView);
    setQuoteB->setVisible(!isView);

    notesList->setVisible(!isView);
    noteEdit->setVisible(!isView);

    showList->setChecked(!isView);
    tabs->setTabBarAutoHide(!isView);
}

void MainWindow::createFolder()
{
    QModelIndex index = notesList->currentIndex();

    if (index.isValid())
    {
        QString name = QInputDialog::getText(this, tr("Name"), tr("Folder name"));
        if (!name.isEmpty())
        {
            qDebug() << "🔸 Folder name:" << name;
            notesDirModel->mkdir(index, name);
        }
    }
}

void MainWindow::createNote()
{
    QModelIndex index = notesList->currentIndex();

    if (index.isValid())
    {
        QString name = QInputDialog::getText(this, tr("Name"), tr("Note name"));
        if (!name.isEmpty())
        {
            name = name + ".md";
            QString path_to_note = notesDirModel->filePath(index) + "/" + name;
            qDebug() << "Note name:" << name;
            createFile(path_to_note);
        }
    }
}

void MainWindow::removeNote()
{
    QModelIndex index = notesList->currentIndex();
    if (index.isValid())
    {
        if (notesDirModel->fileInfo(index).isDir())
        {
            qDebug() << "Folder deleted successfully ";
            notesDirModel->rmdir(index);
        }
        else
        {
            qDebug() << "Note deleted successfully ";
            notesDirModel->remove(index);
        }
    }
}

void MainWindow::renameItem()
{
    QItemSelectionModel *selectionModel = notesList->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();

    if (indexes.isEmpty())
    {
        // No items are selected
        return;
    }

    QModelIndex index = indexes.first();
    QFileInfo fileInfo = notesDirModel->fileInfo(index);

    // Prompt the user to enter a new name
    bool ok;
    QString newName = QInputDialog::getText(notesList, tr("Rename File or Folder"), tr("Enter the new name:"),
                                            QLineEdit::Normal, fileInfo.baseName(), &ok);

    if (ok && !newName.isEmpty())
    {
        // Get the new file path
        QString newFilePath = fileInfo.absoluteDir().absoluteFilePath(newName);

        // Rename the file or folder
        if (fileInfo.isFile())
        {
            QFile file(fileInfo.absoluteFilePath());
            if (file.rename(newFilePath))
            {
            }
        }
        else if (fileInfo.isDir())
        {
            QDir dir(fileInfo.absoluteFilePath());
            if (dir.rename(fileInfo.absoluteFilePath(), newFilePath))
            {
            }
        }
    }
}

void MainWindow::setH1()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("# ");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setH2()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("## ");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setH3()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("### ");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setList()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText(" - ");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setNumList()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText(" 1) ");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setLink()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("[Link](");

    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.insertText(")");

    noteEdit->setTextCursor(cursor);
};

void MainWindow::setBold()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("**");

    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.insertText("**");

    noteEdit->setTextCursor(cursor);
}

void MainWindow::setItalic()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("*");

    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.insertText("*");

    noteEdit->setTextCursor(cursor);
}

void MainWindow::setStrike()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("~");

    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.insertText("~");

    noteEdit->setTextCursor(cursor);
}

void MainWindow::setTask()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText(" - [ ] - ");

    noteEdit->setTextCursor(cursor);
}

void MainWindow::setQuote()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText(" > ");

    noteEdit->setTextCursor(cursor);
}

void MainWindow::setTable()
{
    QTextCursor cursor = noteEdit->textCursor();
    int lineNumber = cursor.blockNumber();
    QTextBlock block = noteEdit->document()->findBlockByNumber(lineNumber);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("<table>\n"
                      "<tr>\n"
                      "    <td>Column 1</td>\n"
                      "    <td>Column 2</td>\n"
                      "</tr>\n\n"
                      "<tr>\n"
                      "    <td>Item 1</td>\n"
                      "    <td>Item 2</td>\n"
                      "</tr>\n"
                      "</table>\n\n");

    noteEdit->setTextCursor(cursor);
}

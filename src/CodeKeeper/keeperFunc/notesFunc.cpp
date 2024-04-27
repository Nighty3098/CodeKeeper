#include <md4.h>
#include <md4c-html.h>
#include <QWebEngineScript>

QModelIndex indexFromItem(QTreeWidgetItem *item, int column) { }

bool createFile(const QString &path)
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "Just start typing...";
        file.close();
        qDebug() << "File created successfully at" << path;
        return true;
    } else {
        qDebug() << "Failed to create file at" << path << ": " << file.errorString();
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

void MainWindow::updateMDPreview()
{
    QString md = noteEdit->toPlainText();

    /*
    QString html;
    md_html(
            md.toUtf8().constData(), md.length(),
            [](const MD_CHAR *html, MD_SIZE html_size, void *userdata) {
                QString *htmlPtr = static_cast<QString *>(userdata);
                QString htmlStr(QString::fromUtf8(reinterpret_cast<const char *>(html), html_size));
                *htmlPtr += htmlStr;
            },
            &html, 0, 0);
    html += "</body></html>";
    */

    QString html_result =
            "<script src='https://polyfill.io/v3/polyfill.min.js?features=es6'></script>"
            "<script id='MathJax-script' async "
            "src='https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js'></script>"
            "<script type='module'>"
            "    import mermaid from "
            "'https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs';"
            "    mermaid.initialize({ startOnLoad: true });"
            "</script>"
            "<style>"
            "body {"
            "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    line-height: 1.5;"
              "}"
              "h1, h2, h3, h4, h5, h6 {"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-weight: normal;"
              "    margin-top: 20px;"
              "    margin-bottom: 10px;"
              "    color: #c3ceec;"
              "}"
              "hr {"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    color: #ecbe7b;"
              "}"
              "p{"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    font-weight: normal;"
              "    margin-top: 20px;"
              "    margin-bottom: 10px;"
              "    color: #c3ceec;"
              "}"
              "ul{"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    font-weight: normal;"
              "    margin-top: 20px;"
              "    margin-bottom: 10px;"
              "    color: #c3ceec;"
              "}"
              "li{"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    font-weight: normal;"
              "    margin-top: 20px;"
              "    margin-bottom: 10px;"
              "    color: #c3ceec;"
              "}"
              "italic{"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    font-weight: normal;"
              "    margin-top: 20px;"
              "    margin-bottom: 10px;"
              "    color: #ecbe7b;"
              "}"
              "bold{"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    font-weight: normal;"
              "    margin-top: 20px;"
              "    margin-bottom: 10px;"
              "    color: #ecbe7b;"
              "}"
              "a{"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    font-weight: normal;"
              "    margin-top: 20px;"
              "    margin-bottom: 10px;"
              "    color: #ecbe7b;"
              "}"
              "blockquote {"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    color: #222436;"
              "    background-color: #7e6c9c;"
              "    padding: 2px 5px;"
              "    border-radius: 6px;"
              "}"
              "code {"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    background-color: #7e6c9c;"
              "    padding: 2px 5px;"
              "    border-radius: 6px;"
              "}"
              "quote {"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    background-color: #7e6c9c;"
              "    padding: 2px 5px;"
              "    border-radius: 6px;"
              "}"
              "body::-webkit-scrollbar {"
              "    width: 6px;"
              "}"
              "body::-webkit-scrollbar-track {"
              "    background: transparent;"
              "}"
              "body::-webkit-scrollbar-thumb {"
              "    background-color: transparent;"
              "    border-radius: 20px;"
              "    border: 4px solid #666c72;"
              "}"
              "table {"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    border-collapse: collapse;"
              "    width: 100%;"
              "    color: #c3ceec;"
              "}"
              "th, td {"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    border: 1px solid #dddddd;"
              "    padding: 8px;"
              "    text-align: left;"
              "    color: #c3ceec;"
              "}"
              "th {"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    background-color: #2f334d;"
              "    color: #c3ceec;"
              "    font-weight: bold;"
              "    color: #c3ceec;"
              "}"
              "tr:nth-child(even) {"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    background-color: #2f334d;"
              "    color: #c3ceec;"
              "}"
              "tr:hover {"
              "    font-family: "
            + selectedFont.toString()
            + ";"
              "    font-size: "
            + font_size
            + ";"
              "    background-color: #2f334d;"
              "    color: #c3ceec;"
              "}"
              "</style>"
              "<html>"
              "<body>"
              "  <div id='content'></div>"
              "  <script src='https://cdn.jsdelivr.net/npm/marked/marked.min.js'></script>"
              "  <script>"
              "    document.getElementById('content').innerHTML ="
              "       marked.parse('"
            + md
            + "');"
              "  </script>"
              "</body>"
              "</html>";

              mdPreview->setHtml(html_result);
}

void MainWindow::saveNote()
{
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

void MainWindow::onNoteDoubleClicked()
{
    QModelIndex index = notesList->currentIndex();
    QString path_to_note = notesDirModel->filePath(index);

    QFile file(path_to_note);

    QRegularExpression re("(\\.md|\\.html|\\.txt)$");
    if (notesDirModel->fileInfo(index).isFile()) {
        if (re.match(path_to_note).hasMatch()) {
            if (file.open(QIODevice::ReadWrite)) {
                qDebug() << path_to_note;
                QTextStream stream(&file);
                noteEdit->setPlainText(stream.readAll());
                file.close();
            }
        } else {
            noteEdit->setPlainText("### File format not supported.");
        }
    }
}

void MainWindow::hideNotesList()
{
    notesList->setVisible(!notesList->isVisible());
    globalSettings->setValue("isVisibleNotesList", notesList->isVisible());
}

void MainWindow::showPreview()
{
    mdPreview->setVisible(!mdPreview->isVisible());
    globalSettings->setValue("isVisiblePreview", mdPreview->isVisible());
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

    showRender->setChecked(isView);
    mdPreview->setVisible(isView);
}

void MainWindow::createFolder()
{
    QModelIndex index = notesList->currentIndex();

    if (index.isValid()) {
        QString name = QInputDialog::getText(this, "Name", "Folder name");
        if (!name.isEmpty()) {
            qDebug() << "Folder name:" << name;
            notesDirModel->mkdir(index, name);
        }
    }
}

void MainWindow::createNote()
{
    QModelIndex index = notesList->currentIndex();

    if (index.isValid()) {
        QString name = QInputDialog::getText(this, "Name", "Note name");
        if (!name.isEmpty()) {
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
    if (index.isValid()) {
        if (notesDirModel->fileInfo(index).isDir()) {
            qDebug() << "Folder deleted successfully";
            notesDirModel->rmdir(index);
        } else {
            qDebug() << "Note deleted successfully";
            notesDirModel->remove(index);
        }
    }
}

void MainWindow::renameItem()
{
    QItemSelectionModel *selectionModel = notesList->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();

    if (indexes.isEmpty()) {
        // No items are selected
        return;
    }

    QModelIndex index = indexes.first();
    QFileInfo fileInfo = notesDirModel->fileInfo(index);

    // Prompt the user to enter a new name
    bool ok;
    QString newName =
            QInputDialog::getText(notesList, tr("Rename File or Folder"), tr("Enter the new name:"),
                                  QLineEdit::Normal, fileInfo.baseName(), &ok);

    if (ok && !newName.isEmpty()) {
        // Get the new file path
        QString newFilePath = fileInfo.absoluteDir().absoluteFilePath(newName);

        // Rename the file or folder
        if (fileInfo.isFile()) {
            QFile file(fileInfo.absoluteFilePath());
            if (file.rename(newFilePath)) { }
        } else if (fileInfo.isDir()) {
            QDir dir(fileInfo.absoluteFilePath());
            if (dir.rename(fileInfo.absoluteFilePath(), newFilePath)) { }
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

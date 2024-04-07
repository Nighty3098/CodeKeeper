void MainWindow::openProject(QListWidget *listWidget, QListWidgetItem *item) {
    if (item) {
        QDialog dialog(this);
        dialog.setWindowTitle(tr("Edit project"));
        dialog.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

        QGridLayout layout(&dialog);

        QMarkdownTextEdit markdownTextEdit(&dialog);
        QTextBrowser mdPreview(&dialog);

        mdPreview.setOpenLinks(true);
        mdPreview.setOpenExternalLinks(true);

        markdownTextEdit.setFont(selectedFont);
        markdownTextEdit.setStyleSheet("font-size: " + font_size + "pt;");

        QPushButton saveButton(tr("Save"), &dialog);
        QPushButton closeButton(tr("Cancel"), &dialog);

        saveButton.setFont(selectedFont);
        saveButton.setStyleSheet("font-size: " + font_size + "pt;");

        closeButton.setFont(selectedFont);
        closeButton.setStyleSheet("font-size: " + font_size + "pt;");

        layout.addWidget(&markdownTextEdit, 1, 0);
        layout.addWidget(&mdPreview, 1, 1);
        layout.addWidget(&saveButton, 2, 0);
        layout.addWidget(&closeButton, 2, 1);

        markdownTextEdit.setPlainText(formatText(item->text()));

        QString text = markdownTextEdit.toPlainText();
        mdPreview.setMarkdown(text);

        
        QObject::connect(&markdownTextEdit, &QMarkdownTextEdit::textChanged, [&]() {
            QString text = markdownTextEdit.toPlainText();
            mdPreview.setMarkdown(text);
        });
        

        QObject::connect(&saveButton, &QPushButton::clicked, [&]() {
            item->setText(unformatText(markdownTextEdit.toPlainText()));
            dialog.close();
        });

        QObject::connect(&closeButton, &QPushButton::clicked, [&]() {
            dialog.close();
        });

        dialog.exec();
    }
}

QString MainWindow::formatText(const QString &text) {
    QStringList lines = text.split('\n');

    if (lines.length() < 4) {
        return text;
    }

    lines[0] = QString("# %1 \n\n").arg(lines[0]);
    lines[1] = QString("[Source](%1) \n\n ").arg(lines[1]);
    lines[2] = QString("%1 \n\n ").arg(lines[2]);
    lines[3] = QString("Latest modification: %1 \n\n ").arg(lines[3]);

    return lines.join("");
}

QString MainWindow::unformatText(const QString &text) {
    QStringList lines = text.split('\n');
    lines.replaceInStrings(QRegExp("^# "), "");
    lines.replaceInStrings(QRegExp("!\\[Source\\]\\(\\n"), "");
    lines.replaceInStrings(QRegExp("Latest modification: \\n"), "");
    lines.replaceInStrings(QRegExp("\\n$"), "");

    lines[0] = QString("%1").arg(lines[0]);
    lines[1] = QString("%1").arg(lines[1]);
    lines[2] = QString("%1").arg(lines[2]);
    lines[3] = QString("%1").arg(lines[3]);

    return lines.join("\n");
}


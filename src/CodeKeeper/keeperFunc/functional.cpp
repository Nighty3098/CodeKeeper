#include <QDateTime>
#include <QSyntaxHighlighter>

QString MainWindow::getCurrentDateTimeString() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTimeString = currentDateTime.toString("dd-MM-yyyy hh:mm:ss");
    return dateTimeString;
}

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

void MainWindow::openFolder() {
    QString str = QFileDialog::getExistingDirectory(0, "Select a directory");
    if (!str.isEmpty()) {
        globalSettings->setValue("path", str);
        qDebug() << str;
    }
}

void MainWindow::updateWindowTitle() {

}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item) {
    QListWidget *lists[] = {notStartedProjects, startedProjects,
                            finishlineProjects, finishedProjects,
                            incompleteTasks,    inprocessTasks,
                            completeTasks};

    for (QListWidget *list : lists) {
        QListWidgetItem *selectedItem = list->currentItem();
        if (selectedItem && selectedItem != item) {
            list->setCurrentItem(nullptr);
        }
    }
}


void MainWindow::setFontPr1() {
    mainTitle->setFont(selectedFont);

    projectsMainLabel->setFont(selectedFont);
    projectsMainLabel->setStyleSheet("font-size: " + font_size +
                                     "pt; color: #8ebecf;");

    openSettingsBtn->setFont(selectedFont);
    openSettingsBtn->setStyleSheet("font-size: " + font_size + "pt;");

    syncDataBtn->setFont(selectedFont);
    syncDataBtn->setStyleSheet("font-size: " + font_size + "pt;");
    
    notesList->setFont(selectedFont);
    notesList->setStyleSheet("font-size: " + font_size +
                             "pt; background-color: rgba(47, 51, 77, 0);");

    menuButton->setFont(selectedFont);

    tasksMenuBtn->setFont(selectedFont);
    
    noteName->setStyleSheet("font-size: " + font_size + "pt; color: #8ebecf;");

    mdPreview->setFont(selectedFont);

    noteEdit->setFont(selectedFont);
    noteEdit->setStyleSheet("font-size: " + font_size + "pt;");

    noteNameLabel->setFont(selectedFont);
    noteNameLabel->setStyleSheet("font-size: " + font_size +
                                 "pt; color: #8ebecf;");

    taskText->setFont(selectedFont);
    taskText->setStyleSheet("font-size: " + font_size + "pt;");

    incompleteTasks->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: "
        "0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(255, 117, 127, 160); color: #000000; "
        "border-width: 0px; border-color: rgba(255, 117, 127); "
        "border-radius: 5px;"
        "font-size: " +
        font_size +
        "pt;"
        "}");

    inprocessTasks->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: "
        "0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(255, 199, 119, 160); "
        "color: #000000; text-decoration: underline; "
        "border-width: 0px; "
        "border-radius: 5px;"
        "font-size: " +
        font_size +
        "pt;"
        "}");

    completeTasks->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: "
        "0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(195, 232, 141, 160); "
        "color: #000000;"
        "border-radius: 5px;"
        "line-through; border-width: 0px; "
        "font-size: " +
        font_size +
        "pt;"
        "}");

    notStartedProjects->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: "
        "0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(255, 117, 127, 160);"
        "color: #000000; border-width: 0px; "
        "border-radius: 5px;"
        "border-color: #ff757f; "
        "font-size: " +
        font_size +
        "pt;"
        "}");

    startedProjects->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: "
        "0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(255, 199, 119, 160); color: #000000; "
        "border-radius: 5px;"
        "border-width: 0px; border-color: #ffc777; "
        "font-size: " +
        font_size +
        "pt;"
        "}");

    finishlineProjects->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: "
        "0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(130, 170, 255, "
        "160); color: #000000; border-width: 0px; "
        "border-radius: 5px;"
        "border-color: #82aaff; "
        "font-size: " +
        font_size +
        "pt;"
        "}");

    finishedProjects->setStyleSheet(
        "QListWidget {background-color: rgba(255, 117, 127, 0);  border-width: "
        "0px; "
        "border-color: #838383;}"
        "QListWidget::item:selected {"
        "color: #FFFFFF;"
        "}"
        "QListWidget::Item {"
        "background-color: rgba(195, 232, 141, 160); color: #000000; "
        "border-radius: 5px;"
        "border-width: 0px; border-color: #c3e88d; "
        "font-size: " +
        font_size +
        "pt;"
        "}");

    fProjects->setFont(selectedFont);
    flProjects->setFont(selectedFont);
    nsProjects->setFont(selectedFont);
    sProjects->setFont(selectedFont);

    nsProjects->setStyleSheet("font-size: 16px;");
    sProjects->setStyleSheet("font-size: 16px;");
    flProjects->setStyleSheet("font-size: 16px;");
    fProjects->setStyleSheet("font-size: 16px;");

    projectsMainLabel->setFont(selectedFont);
    notStartedProjects->setFont(selectedFont);
    startedProjects->setFont(selectedFont);
    finishlineProjects->setFont(selectedFont);
    finishedProjects->setFont(selectedFont);

    // projectsMenuButton->setFont(selectedFont);

    projectsMenu->setFont(selectedFont);

    tabs->setFont(selectedFont);
    tabs->setStyleSheet("font-size: " + font_size + "pt;");

    totalProjectsL->setFont(selectedFont);
    totalProjectsL->setStyleSheet("font-size: " + font_size + "pt;");

    incompleteTasks->setFont(selectedFont);
    inprocessTasks->setFont(selectedFont);
    completeTasks->setFont(selectedFont);


    label_1->setFont(selectedFont);
    label_1->setStyleSheet("font-size: 16px;");
    label_2->setFont(selectedFont);
    label_2->setStyleSheet("font-size: 16px;");
    label_3->setFont(selectedFont);
    label_3->setStyleSheet("font-size: 16px;");

    tasksProgress->setFont(selectedFont);
    tasksProgress->setStyleSheet(
        "background-color: rgb(255, 117, 127); selection-background-color: "
        "rgb(195, 232, 141); color: #222436; font-size: " +
        font_size + "pt;");
}

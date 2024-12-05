#include "mainwindow.h"

void MainWindow::activateTasksContextMenu(const QPoint &pos, QListWidget *listWidget)
{
    QPoint item = listWidget->mapToGlobal(pos);
    QMenu *submenu = new QMenu;

    // ! Need fixed
    if (isCustomTheme)
    {
        submenu->setStyleSheet("QMenu {"
                               "    background-color: #2b3d4c;"
                               "    color: #fff;"
                               "    border: 1px solid #fff;"
                               "    border-radius: 10px;"
                               "}"
                               "QMenu::separator {"
                               "    height: 3px;"
                               "    border-radius: 1px;"
                               "    background-color: #fff;"
                               "}"
                               "QMenu::item {"
                               "    border-radius: 0px;"
                               "    color: #fff;"
                               "    margin: 5px 10px;"
                               "}"
                               "QMenu::item:selected {"
                               "    border-radius: 10px;"
                               "    color: #78b3ba;"
                               "    text-decoration: none;"
                               "}");
    }
    else
    {
    }
    createTaskMenu(submenu, font_size);
    QAction *rightClickItem = submenu->exec(item);
}

void MainWindow::onMovingTaskFrom(QListWidgetItem *item, QListWidget *list)
{
    if (item && list)
    {
        qDebug() << "Moving task: " << item->text() << " from: " << list->objectName();
    }
}

void MainWindow::onMovingTaskTo(QListWidgetItem *item, QListWidget *list)
{
    if (item && list)
    {
        qDebug() << "Moved task: " << item->text() << " to: " << list->objectName();

        QStringList data = item->text().split("\n――――――――――――――\n");
        if (data.size() >= 2)
        {
            QString status = list->objectName();
            QString cT = data[1];

            updateTaskStatus(&data[0], &status, &cT);
        }
        else
        {
            qWarning() << "Invalid task data format";
        }
    }
}

void MainWindow::addNewTask()
{
    QString text = taskText->text();
    if (!text.isEmpty())
    {
        taskText->clear();
        QString task = text + "\n――――――――――――――\n" + getCurrentDateTimeString();
        qDebug() << "Added new task: " << task;
        incompleteTasks->addItem(task);
        QString status = incompleteTasks->objectName();
        QString projectLink = projectsList->currentText();
        if (projectLink.isEmpty())
        {
            projectLink = "NULL";
        }
        if (projectLink == "ALL")
        {
            projectLink = "NULL";
        }

        saveTaskToDB(&task, &status, &projectLink);
    }
    else
    {
        qWarning() << "Task is empty";
    }

    filterTasksByProject(projectsList);
}

void MainWindow::removeTask()
{
    QList<QListWidget *> listWidgets = {incompleteTasks, inprocessTasks, completeTasks};

    for (QListWidget *listWidget : listWidgets)
    {
        QListWidgetItem *item = listWidget->currentItem();
        if (item)
        {
            QString task = item->text();
            QString status = listWidget->objectName();

            listWidget->takeItem(listWidget->row(item));
            qDebug() << "Removed task: " << task;

            removeTaskFromDB(&task, &status);
            delete item;
            break;
        }
    }

    filterTasksByProject(projectList);
}

void MainWindow::getTotalTasks(QTabWidget *tasksTab, QListWidget *incompleteTasks, QListWidget *inprocessTasks,
                               QListWidget *completeTasks)
{
    if (tasksTab->currentIndex() == 2)
    {
        QTimer *timer3 = new QTimer(this);
        connect(timer3, &QTimer::timeout, [=]() {
            int totalTasks = incompleteTasks->count() + inprocessTasks->count() + completeTasks->count();

            tasksProgress->setFormat("Total tasks: " + QString::number(totalTasks) + " ");
        });
        timer3->start(500);
    }
}

void MainWindow::updateTasksProgress(QTabWidget *tasksTab, QListWidget *incompleteTasks, QListWidget *inprocessTasks,
                                     QListWidget *completeTasks, QProgressBar *tasksProgress)
{
    if (tasksTab->currentIndex() == 2)
    {
        QTimer *timer2 = new QTimer(this);
        connect(timer2, &QTimer::timeout, [=]() {
            int totalTasks = incompleteTasks->count() + inprocessTasks->count() + completeTasks->count();
            int completedTasks = completeTasks->count();

            if (totalTasks == 0)
            {
                tasksProgress->setValue(0);
            }
            else
            {
                double percentage = static_cast<double>(completedTasks) / static_cast<double>(totalTasks) * 100.0;
                tasksProgress->setValue(percentage);
            }
        });
        timer2->start(500);
    }
}

void MainWindow::editTask()
{
    QListWidget *listWidgets[] = {incompleteTasks, inprocessTasks, completeTasks};

    for (QListWidget *listWidget : listWidgets)
    {
        QListWidgetItem *item = listWidget->currentItem();
        if (item)
        {
            qDebug() << font_size;

            QString oldText = item->text();
            QStringList oldData = oldText.split("\n――――――――――――――\n");

            QDialog dialog(this);
            dialog.setMinimumSize(220, 250);
            dialog.setWindowTitle(tr("Edit task"));
            dialog.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

            QVBoxLayout layout(&dialog);
            QPlainTextEdit taskEdit(&dialog);
            taskEdit.setFont(selectedFont);
            taskEdit.setStyleSheet("font-size: " + font_size + "px;");
            taskEdit.setMinimumSize(200, 100);
            taskEdit.setPlainText(oldData[0]);

            QComboBox *projectList = new QComboBox();
            projectList->setPlaceholderText("Select project ...");
            projectList->setFont(selectedFont);
            projectList->setStyleSheet("font-size: " + font_size + "px;");
            projectList->setMinimumSize(200, 25);

            loadProjectsList(projectList);

            QString c_status = listWidget->objectName();
            QString c_task = oldData[0];
            qDebug() << "Checking" << c_task << " - " << c_status;
            QString projectLink = getProjectByTask(&c_task, &c_status);

            qDebug() << "Count: " << projectList->count();

            if (!projectLink.isEmpty() && projectLink != "NULL")
            {
                qDebug() << "Found Project link: " << projectLink;

                for (int i = 0; i < projectList->count(); ++i)
                {

                    QString itemText = projectList->itemText(i);
                    qDebug() << "Index:" << i << "Text:" << itemText;

                    if (itemText == projectLink)
                    {
                        projectList->setCurrentIndex(i);
                        qDebug() << "Selected project: " << projectList->currentText();
                    }
                }
            }

            QPushButton okButton(tr("Save"), &dialog);
            okButton.setFont(selectedFont);
            okButton.setStyleSheet("font-size: " + font_size + "px;");
            okButton.setMinimumSize(200, 25);
            QPushButton cancelButton(tr("Cancel"), &dialog);
            cancelButton.setFont(selectedFont);
            cancelButton.setMinimumSize(200, 25);
            cancelButton.setStyleSheet("font-size: " + font_size + "px;");

            layout.addWidget(projectList);
            layout.addWidget(&taskEdit);
            layout.addWidget(&okButton);
            layout.addWidget(&cancelButton);

            QObject::connect(&okButton, &QPushButton::clicked, [&]() {
                QString newText = taskEdit.toPlainText();
                if (!newText.isEmpty())
                {
                    QString newTask = newText + "\n――――――――――――――\n" + getCurrentDateTimeString();
                    QString status = listWidget->objectName();
                    QString cT = oldData[1];
                    QString newProjectLink = projectList->currentText();
                    qDebug() << "New project link: " << newProjectLink;

                    item->setText(newTask);

                    updateTaskData(&newTask, &status, &cT, &newProjectLink);
                }
                dialog.close();
            });

            QObject::connect(&cancelButton, &QPushButton::clicked, [&]() { dialog.close(); });

            dialog.exec();
            break;
        }
    }
}
void MainWindow::loadProjectsList(QComboBox *projectList)
{
    qDebug() << "Load projects list";

    projectList->clear();
    QStringList projectsStringList = getProjectsList();
    for (const QString &project : projectsStringList)
    {
        projectList->addItem(project);
    }

    projectList->addItem("All");
}

void MainWindow::filterTasksByProject(QComboBox *projectList)
{
    qDebug() << "Activated: " << projectList->currentText();
    QString selectedProject = projectList->currentText();

    for (int i = 0; i < incompleteTasks->count(); ++i)
    {
        QListWidgetItem *item = incompleteTasks->item(i);
        QStringList task = item->text().split("\n――――――――――――――\n");
        QString status = incompleteTasks->objectName();
        QString projectLink = getProjectByTask(&task[0], &status);

        item->setHidden(selectedProject != "All" && projectLink != selectedProject);
    }

    for (int i = 0; i < inprocessTasks->count(); ++i)
    {
        QListWidgetItem *item = inprocessTasks->item(i);
        QStringList task = item->text().split("\n――――――――――――――\n");
        QString status = inprocessTasks->objectName();
        QString projectLink = getProjectByTask(&task[0], &status);

        item->setHidden(selectedProject != "All" && projectLink != selectedProject);
    }

    for (int i = 0; i < completeTasks->count(); ++i)
    {
        QListWidgetItem *item = completeTasks->item(i);
        QStringList task = item->text().split("\n――――――――――――――\n");
        QString status = completeTasks->objectName();
        QString projectLink = getProjectByTask(&task[0], &status);

        item->setHidden(selectedProject != "All" && projectLink != selectedProject);
    }
}

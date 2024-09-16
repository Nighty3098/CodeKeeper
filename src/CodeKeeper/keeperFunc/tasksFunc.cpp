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

        QStringList data = item->text().split("\n");
        if (data.size() >= 2) // Check if data has at least 2 elements
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
        QString task = text + "\n" + getCurrentDateTimeString();
        qDebug() << "Added new task: " << task;
        incompleteTasks->addItem(task);
        QString status = incompleteTasks->objectName();
        saveTaskToDB(&task, &status);
    }
    else
    {
        qWarning() << "Task is empty";
    }
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
            QStringList oldData = oldText.split("\n");

            QDialog dialog(this);
            dialog.setFixedSize(220, 200);
            dialog.setWindowTitle(tr("Edit task"));
            dialog.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

            QVBoxLayout layout(&dialog);
            QLineEdit lineEdit(&dialog);
            lineEdit.setFont(selectedFont);
            lineEdit.setFixedSize(200, 100);
            lineEdit.setAlignment(Qt::AlignCenter);

            layout.addWidget(&lineEdit);

            lineEdit.setText(oldData[0]);

            QPushButton okButton(tr("Save"), &dialog);
            okButton.setFont(selectedFont);
            okButton.setFixedSize(200, 25);
            QPushButton cancelButton(tr("Cancel"), &dialog);
            cancelButton.setFont(selectedFont);
            cancelButton.setFixedSize(200, 25);
            layout.addWidget(&okButton);
            layout.addWidget(&cancelButton);

            QObject::connect(&okButton, &QPushButton::clicked, [&]() {
                QString newText = lineEdit.text();
                if (!newText.isEmpty())
                {
                    QString newTask = newText + "\n" + getCurrentDateTimeString();
                    QString status = listWidget->objectName();
                    QString cT = oldData[1];

                    item->setText(newTask);

                    updateTaskData(&newTask, &status, &cT);
                }
                dialog.close();
            });

            QObject::connect(&cancelButton, &QPushButton::clicked, [&]() { dialog.close(); });

            dialog.exec();
            break;
        }
    }
}

void MainWindow::onMovingTaskFrom(QListWidgetItem *item, QListWidget *list)
{
    qDebug() << "Moving task: " << item->text() << " from: " << list->objectName();

    QString task = item->text();
    QString status = list->objectName();
}

void MainWindow::onMovingTaskTo(QListWidgetItem *item, QListWidget *list)
{
    qDebug() << "Moved task: " << item->text() << " to: " << list->objectName();

    QString task = item->text();
    QString status = list->objectName();
    QStringList data = task.split("\n");
    QString cT = data[1];

    updateTaskStatus(&task, &status, &cT);
}

void MainWindow::addNewTask()
{
    QString text = taskText->text();
    if (!text.isEmpty()) {
        taskText->clear();
        QString task = text + "\n" + getCurrentDateTimeString();
        qDebug() << "Added new task: " << task;
        incompleteTasks->addItem(task);
        QString status = incompleteTasks->objectName();
        saveTaskToDB(&task, &status);
    } else {
        qDebug() << "Task is empty";
    }
}

void MainWindow::removeTask()
{
    QListWidget *listWidgets[] = { incompleteTasks, inprocessTasks, completeTasks };

    for (QListWidget *listWidget : listWidgets) {
        QListWidgetItem *item = listWidget->currentItem();
        if (item) {
            listWidget->takeItem(listWidget->row(item));
            qDebug() << "Removed task: " << item->text();

            QString task = item->text();
            QString status = listWidget->objectName();

            removeTaskFromDB(&task, &status);

            delete item;
            break;
        }
    }
}

void MainWindow::getTotalTasks(QTabWidget *tasksTab, QListWidget *incompleteTasks,
                               QListWidget *inprocessTasks, QListWidget *completeTasks)
{
    if (tasksTab->currentIndex() == 2) {
        QTimer *timer3 = new QTimer(this);
        connect(timer3, &QTimer::timeout, [=]() {
            int totalTasks =
                    incompleteTasks->count() + inprocessTasks->count() + completeTasks->count();

            tasksProgress->setFormat("Total tasks: " + QString::number(totalTasks) + " ");
        });
        timer3->start(500);
    }
}

void MainWindow::updateTasksProgress(QTabWidget *tasksTab, QListWidget *incompleteTasks,
                                     QListWidget *inprocessTasks, QListWidget *completeTasks,
                                     QProgressBar *tasksProgress)
{
    if (tasksTab->currentIndex() == 2) {
        QTimer *timer2 = new QTimer(this);
        connect(timer2, &QTimer::timeout, [=]() {
            int totalTasks =
                    incompleteTasks->count() + inprocessTasks->count() + completeTasks->count();
            int completedTasks = completeTasks->count();

            if (totalTasks == 0) {
                tasksProgress->setValue(0);
            } else {
                double percentage = static_cast<double>(completedTasks)
                        / static_cast<double>(totalTasks) * 100.0;
                tasksProgress->setValue(percentage);
            }
        });
        timer2->start(500);
    }
}

void MainWindow::renameItemOnDoubleClick(QListWidget *listWidget, QListWidgetItem *item)
{
    if (item) {
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
        lineEdit.setStyleSheet("background-color: #2D4F67; border-color: #2D4F67; font-size: "
                               + font_size + "pt; border-radius: 10px;");

        layout.addWidget(&lineEdit);

        lineEdit.setText(oldData[0]);

        QPushButton okButton(tr("OK"), &dialog);
        okButton.setFont(selectedFont);
        okButton.setFixedSize(200, 25);
        okButton.setStyleSheet("background-color: #2D4F67; border-color: #2D4F67; font-size: "
                               + font_size + "pt; border-radius: 10px;");
        QPushButton cancelButton(tr("Cancel"), &dialog);
        cancelButton.setFont(selectedFont);
        cancelButton.setFixedSize(200, 25);
        cancelButton.setStyleSheet("background-color: #2D4F67; border-color: #2D4F67; font-size: "
                                   + font_size + "pt; border-radius: 10px;");
        layout.addWidget(&okButton);
        layout.addWidget(&cancelButton);

        QObject::connect(&okButton, &QPushButton::clicked, [&]() {
            QString newText = lineEdit.text();
            if (!newText.isEmpty()) {
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
    }
}

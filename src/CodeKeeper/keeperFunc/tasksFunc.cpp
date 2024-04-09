
void MainWindow::addNewTask() {
    QString text = taskText->text();
    if (!text.isEmpty()) {
        taskText->clear();
        incompleteTasks->addItem(text);
    } else {
        qDebug() << "Task is empty";
    }
}

void MainWindow::removeTask() {
    QListWidget *listWidgets[] = {incompleteTasks, inprocessTasks,
                                  completeTasks};

    for (QListWidget *listWidget : listWidgets) {
        QListWidgetItem *item = listWidget->currentItem();
        if (item) {
            listWidget->takeItem(listWidget->row(item));
            delete item;
            break;
        }
    }
}

void MainWindow::updateTasksProgress(QTabWidget *tasksTab,
                                     QListWidget *incompleteTasks,
                                     QListWidget *inprocessTasks,
                                     QListWidget *completeTasks,
                                     QProgressBar *tasksProgress) {
    if (tasksTab->currentIndex() == 2) {
        qDebug() << tasksTab->currentIndex();
        QTimer *timer2 = new QTimer(this);
        connect(timer2, &QTimer::timeout, [=]() {
            int totalTasks = incompleteTasks->count() +
                             inprocessTasks->count() + completeTasks->count();
            int completedTasks = completeTasks->count();

            if (totalTasks == 0) {
                tasksProgress->setValue(0);
            } else {
                double percentage = static_cast<double>(completedTasks) /
                                    static_cast<double>(totalTasks) * 100.0;
                tasksProgress->setValue(percentage);
            }
        });
        timer2->start(500);
    } else {
        qDebug() << tasksTab->currentIndex();
    }
}

void MainWindow::loadTasks() {}
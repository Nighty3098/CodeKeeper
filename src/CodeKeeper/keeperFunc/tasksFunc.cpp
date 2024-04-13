
void MainWindow::addNewTask() {
    QString text = taskText->text();
    if (!text.isEmpty()) {
        taskText->clear();
        QString task = text + "\n" + getCurrentDateTimeString();
        qDebug() << "Added new task: " << task;
        incompleteTasks->addItem(task);
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
            qDebug() << "Removed task: " << item->text();
            delete item;
            break;
        }
    }
}

void MainWindow::getTotalTasks(QTabWidget *tasksTab, QListWidget *incompleteTasks, QListWidget *inprocessTasks, QListWidget *completeTasks) {
    if (tasksTab->currentIndex() == 2) {
        QTimer *timer3 = new QTimer(this);
        connect(timer3, &QTimer::timeout, [=]() {
            int totalTasks = incompleteTasks->count() +
                             inprocessTasks->count() + completeTasks->count();

            totalTasksL->setText("Total tasks: " + QString::number(totalTasks) + " ");
        });
        timer3->start(500);
    }
}

void MainWindow::updateTasksProgress(QTabWidget *tasksTab,
                                     QListWidget *incompleteTasks,
                                     QListWidget *inprocessTasks,
                                     QListWidget *completeTasks,
                                     QProgressBar *tasksProgress) {
    if (tasksTab->currentIndex() == 2) {
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
    }
}


void MainWindow::renameItemOnDoubleClick(QListWidget *listWidget,
                                         QListWidgetItem *item) {
    if (item) {
        QDialog dialog(this);
        dialog.setWindowTitle(tr("Edit task"));
        dialog.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

        QVBoxLayout layout(&dialog);
        QLineEdit lineEdit(&dialog);
        layout.addWidget(&lineEdit);

        QPushButton okButton(tr("OK"), &dialog);
        QPushButton cancelButton(tr("Cancel"), &dialog);
        layout.addWidget(&okButton);
        layout.addWidget(&cancelButton);

        QObject::connect(&okButton, &QPushButton::clicked, [&]() {
            QString newText = lineEdit.text();
            if (!newText.isEmpty()) {
                QString newTask = newText + "\n" + getCurrentDateTimeString();
                item->setText(newTask);
            }
            dialog.close();
        });

        QObject::connect(&cancelButton, &QPushButton::clicked,
                         [&]() { dialog.close(); });

        dialog.exec();
    }
}


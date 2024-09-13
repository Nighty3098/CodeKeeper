#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

void MainWindow::create_tasks_connection()
{
    QSqlQuery query;

    QString str = "CREATE TABLE tasks ( "
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "task TEXT,"
                  "status VARCHAR(50),"
                  "createdTime VARCHAR(50)"
                  ");";

    if (!query.exec(str))
    {
        qDebug() << "" << query.lastError();
    }
    else
    {
        qDebug() << "Tasks db was created";
    }
}

void MainWindow::updateTaskData(QString *task, QString *status, QString *cT)
{
    QSqlQuery query;

    QStringList taskText = task->split("\n");

    query.prepare("UPDATE tasks SET task = :task WHERE createdTime = :cT AND status = :status");
    query.bindValue(":task", taskText[0]);
    query.bindValue(":cT", *cT);
    query.bindValue(":status", *status);

    if (!query.exec())
    {
        qDebug() << "" << query.lastError();
    }
}

void MainWindow::updateTaskStatus(QString *task, QString *status, QString *cT)
{
    QSqlQuery query;

    QStringList taskText = task->split("\n");

    query.prepare("UPDATE tasks SET status = :status WHERE createdTime = :cT AND task = :task");
    query.bindValue(":status", *status);
    query.bindValue(":cT", *cT);
    query.bindValue(":task", taskText[0]);

    if (!query.exec())
    {
        qDebug() << "" << query.lastError();
    }
}

void MainWindow::saveTaskToDB(QString *task, QString *status)
{
    QSqlQuery query;

    QStringList taskText = task->split("\n");

    query.prepare("INSERT INTO tasks (task, status, createdTime) VALUES(:task, :status, :createdTime)");
    query.bindValue(":task", taskText[0]);
    query.bindValue(":status", *status);
    query.bindValue(":createdTime", taskText[1]);

    if (!query.exec())
    {
        qDebug() << "" << query.lastError();
    }
    else
    {
        qDebug() << "" << taskText[0] << " was saved";
    }
}

void MainWindow::removeTaskFromDB(QString *task, QString *status)
{
    QSqlQuery query;

    QStringList taskText = task->split("\n");

    query.prepare("DELETE FROM tasks WHERE task = :task AND status = :status AND createdTime = :createdTime");
    query.bindValue(":task", taskText[0]);
    query.bindValue(":status", *status);
    query.bindValue(":createdTime", taskText[1]);

    if (!query.exec())
    {
        qDebug() << "" << query.lastError();
    }
    else
    {
        qDebug() << "Successfully removed";
    }
}

void MainWindow::loadTasks()
{
    incompleteTasks->clear();
    inprocessTasks->clear();
    completeTasks->clear();

    QSqlQuery query;

    query.exec("SELECT * FROM tasks");
    while (query.next())
    {
        int id = query.value("id").toInt();
        QString task = query.value("task").toString();
        QString status = query.value("status").toString();
        QString createdTime = query.value("createdTime").toString();

        QString text = task + "\n" + createdTime;

        QListWidgetItem *item = new QListWidgetItem(text);

        item->setData(Qt::UserRole, id);

        if (status == "IncompleteTasks")
        {
            incompleteTasks->addItem(item);
        }
        if (status == "InprocessTasks")
        {
            inprocessTasks->addItem(item);
        }
        if (status == "CompleteTasks")
        {
            completeTasks->addItem(item);
        }
        else
        {
            qDebug() << "Unknown status: " << status;
        }
    }

    qDebug() << "Tasks loaded";
}

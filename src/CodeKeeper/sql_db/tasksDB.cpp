#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include "mainwindow.h"

void MainWindow::create_tasks_connection()
{
    QSqlQuery query;

    QString str = "CREATE TABLE tasks ( "
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "task TEXT,"
                  "status VARCHAR(50),"
                  "createdTime VARCHAR(50),"
                  "projectLink TEXT);";

    if (!query.exec(str))
    {
        qDebug() << "" << query.lastError();
    }
    else
    {
        qDebug() << "Tasks db was created";
    }
}

void MainWindow::updateTaskData(QString *task, QString *status, QString *cT, QString *projectLink)
{
    QSqlQuery query;

    QStringList taskText = task->split("\n――――――――――――――\n");
    QString task_s = taskText[0];

    query.prepare(
        "UPDATE tasks SET task = :task, projectLink = :projectLink WHERE createdTime = :cT AND status = :status");
    query.bindValue(":task", task_s);
    query.bindValue(":cT", *cT);
    query.bindValue(":status", *status);
    query.bindValue(":projectLink", *projectLink);

    if (!query.exec())
    {
        qDebug() << "" << query.lastError();
    }

    qDebug() << task_s << *status << *cT << *projectLink;
}

void MainWindow::updateTaskStatus(QString *task, QString *status, QString *cT)
{
    QSqlQuery query;

    QStringList taskText = task->split("\n――――――――――――――\n");

    query.prepare("UPDATE tasks SET status = :status WHERE createdTime = :cT AND task = :task");
    query.bindValue(":status", *status);
    query.bindValue(":cT", *cT);
    query.bindValue(":task", taskText[0]);

    if (!query.exec())
    {
        qDebug() << "" << query.lastError();
    }
}

void MainWindow::saveTaskToDB(QString *task, QString *status, QString *projectLink)
{
    QSqlQuery query;

    QStringList taskText = task->split("\n――――――――――――――\n");

    query.prepare("INSERT INTO tasks (task, status, createdTime, projectLink) VALUES(:task, :status, :createdTime, "
                  ":projectLink)");
    query.bindValue(":task", taskText[0]);
    query.bindValue(":status", *status);
    query.bindValue(":createdTime", taskText[1]);
    query.bindValue(":projectLink", *projectLink);

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

    QStringList taskText = task->split("\n――――――――――――――\n");

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

    query.exec("SELECT * FROM tasks ORDER BY createdTime DESC");
    while (query.next())
    {
        int id = query.value("id").toInt();
        QString task = query.value("task").toString();
        QString status = query.value("status").toString();
        QString createdTime = query.value("createdTime").toString();

        QString text = task + "\n――――――――――――――\n" + createdTime;

        QListWidgetItem *item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, id);

        if (status == "IncompleteTasks")
        {
            incompleteTasks->addItem(item);
        }
        else if (status == "InprocessTasks")
        {
            inprocessTasks->addItem(item);
        }
        else if (status == "CompleteTasks")
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

QString MainWindow::getProjectByTask(QString *task, QString *status)
{
    if (task == nullptr || status == nullptr)
    {
        qWarning() << "Null pointer passed to getProjectByTask";
        return "";
    }

    QSqlQuery query;
    query.prepare(
        "SELECT projectLink FROM tasks WHERE task = :task AND status = :status ORDER BY createdTime DESC LIMIT 1");

    query.bindValue(":task", *task);
    query.bindValue(":status", *status);

    QString projectLink = "";
    if (query.exec())
    {
        if (query.next())
        {
            projectLink = query.value("projectLink").toString();
            return projectLink;
        }
    }
    else
    {
        qWarning() << "Error querying projects database:" << query.lastError();
        return "";
    }
}

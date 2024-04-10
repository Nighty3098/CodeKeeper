#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

void MainWindow::create_tasks_connection () {
    QSqlQuery query;

    QString str =
        "CREATE TABLE tasks ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "task TEXT,"
        "status VARCHAR(50),"
        "createdTime VARCHAR(50)"
        ");";

    if (!query.exec(str)) {
        qDebug() << query.lastError();
    } else {
        qDebug() << "Tasks db was created";
    }
}

void MainWindow::loadTasks() {}
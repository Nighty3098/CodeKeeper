#include <QtSql/QSqlDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


void createNotesTable() {
    QSqlQuery query;

    QString str =
        "CREATE TABLE notes ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name VARCHAR(100),"
        "text VARCHAR(999999999),"
        "createdTime VARCHAR(50),"
        "lastModifiedTime VARCHAR(50)"
        ");";

    if (!query.exec(str)) {
        qDebug() << query.lastError();
    } else {
        qDebug() << "Notes table was created";
    }
}


void createTasksTable() {
    QSqlQuery query;

    QString str2 =
        "CREATE TABLE tasks ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "text VARCHAR(100),"
        "createdTime VARCHAR(50),"
        "category VARCHAR(1000)"
        ");";

    if (!query.exec(str2)) {
        qDebug() << query.lastError();
    } else {
        qDebug() << "Table tasks was created";
    }
}


void createProjectsTable() {
    QSqlQuery query;

    QString str3 =
        "CREATE TABLE projects ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name VARCHAR(100),"
        "text VARCHAR(999999999),"
        "category VARCHAR(1000),"
        "createdTime VARCHAR(50),"
        "lastModifiedTime VARCHAR(50),"
        "git VARCHAR(100)"
        ");";

    if (!query.exec(str3)) {
        qDebug() << query.lastError();
    } else {
        qDebug() << "Tabs projects was created";
    }
}

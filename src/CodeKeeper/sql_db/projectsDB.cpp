#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

void MainWindow::create_projects_connection () {
    QSqlQuery query;

    QString str =
        "CREATE TABLE projects ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "project TEXT,"
        "projectDoc TEXT,"
        "status VARCHAR(50),"
        "createdTime VARCHAR(50)"
        ");";

    if (!query.exec(str)) {
        qDebug() << query.lastError();
    } else {
        qDebug() << "Projects db was created";
    }
}

void MainWindow::saveProjectToDB() {

}

void MainWindow::loadProjects() {

}

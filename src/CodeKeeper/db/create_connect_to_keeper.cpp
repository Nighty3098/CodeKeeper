#include <QtSql/QSqlDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

static bool createConnectionToKeeper() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("CodeKeeper.db");

    db.setUserName("admin");
    db.setHostName("localhost");
    db.setPassword("password");

    if (!db.open()) {
        qDebug() << db.lastError();
        return false;
    }

    qDebug() << "Connection created";
    return true;
}

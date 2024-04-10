#include <QSqlQuery>
#include <QSqlError>

static bool createConnection () {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");

    db.setUserName("admin");
    db.setHostName("localhost");
    db.setPassword("password");

    if (!db.open()) {
        qDebug() << db.lastError();
        return false;
    }

    return true;
}
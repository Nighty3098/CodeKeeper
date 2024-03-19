static bool createConnectionToSettings() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("settings.db");

    db.setUserName("admin");
    db.setHostName("localhost");
    db.setPassword("password");

    if (!db.open()) {
        qDebug() << db.lastError();
        return false;
    }

    return true;
}

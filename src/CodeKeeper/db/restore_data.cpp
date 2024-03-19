#include <QtSql/QSqlDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

void restore_notes() {
    QSqlQuery query;

    query.exec("SELECT * FROM notes");
    while (query.next()) {
        QString name = query.value("name").toString();
        QString createdTime = query.value("createdTime").toString();

        QString itemText = name + "\n" + createdTime;

        QListWidgetItem *item = new QListWidgetItem(itemText);
        notesList->addItem(item);

        qDebug() << name << " was loaded";
    }
}

void restore_tasks() {
    QSqlQuery query;

    query.exec("SELECT * FROM tasks");
    while (query.next()) {
        QString task = query.value("text").toString();
        QString createdTime = query.value("createdTime").toString();
        QString category = query.value("category").toString();

        QString itemText = task + "\n" + createdTime;

        if(category == "Incomplete") {
            QListWidgetItem *item = new QListWidgetItem(itemText);
            incompleteTasks->addItem(item);
        }
        if(category == "Inprocess") {
            QListWidgetItem *item = new QListWidgetItem(itemText);
            inprocessTasks->addItem(item);
        }
        if(category == "Complete") {
            QListWidgetItem *item = new QListWidgetItem(itemText);
            completeTasks->addItem(item);
        }
        else {
            qDebug() << "Unknown category";
        }
    }
}

void restore_projects() {
    QSqlQuery query;

    query.exec("SELECT * FROM projects");
    while (query.next()) {
        QString name = query.value("name").toString();
        QString createdTime = query.value("createdTime").toString();
        QString category = query.value("category").toString();
        QString git = query.value("git").toString();

        QString itemText = name + "\n" + git + "\n" + createdTime;

        if(category == "Notstarted") {
            QListWidgetItem *item = new QListWidgetItem(itemText);
            notStartedProjects->addItem(item);
        }

        if(category == "Started") {
            QListWidgetItem *item = new QListWidgetItem(itemText);
            startedProjects->addItem(item);
        }

        if(category == "Finishline") {
            QListWidgetItem *item = new QListWidgetItem(itemText);
            finishlineProjects->addItem(item);
        }

        if(category == "Finished") {
            QListWidgetItem *item = new QListWidgetItem(itemText);
            finishedProjects->addItem(item);
        }
    }
}

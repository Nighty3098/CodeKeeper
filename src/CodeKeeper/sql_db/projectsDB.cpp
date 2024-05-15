#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

void MainWindow::create_projects_connection()
{
    QSqlQuery query;

    QString str = "CREATE TABLE projects ( "
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "title TEXT,"
                  "git_url TEXT,"
                  "projectDoc TEXT,"
                  "note TEXT,"
                  "status VARCHAR(50),"
                  "createdTime VARCHAR(50)"
                  ");";

    if (!query.exec(str)) {
        qWarning() << query.lastError();
    } else {
        qDebug() << "🟢 Projects db was created";
    }
}

QStringList MainWindow::GetProjectData(QString *title, QString *status, QString *git_url)
{
    QStringList projectData;
    QSqlQuery query;

    if (query.exec("SELECT * FROM projects WHERE status = '" + *status + "' AND title = '" + *title
                   + "' AND git_url = '" + *git_url + "'")) {
        if (query.next()) {
            projectData << query.value("title").toString();
            projectData << query.value("git_url").toString();
            projectData << query.value("projectDoc").toString();
            projectData << query.value("note").toString();
            projectData << query.value("status").toString();
            projectData << query.value("createdTime").toString();
            qDebug() << "🟢 Load project: " << projectData;
        }
    } else {
        qWarning() << "🔴 Error querying projects database:" << query.lastError();
    }
    return projectData;
}

void MainWindow::updateProjectData(QString *title, QString *git_url, QString *doc, QString *note,
                                   QString *createdTime, QString *oldTime, QString *oldGit)
{
    QSqlQuery query;

    if (!query.exec("UPDATE projects SET title = '" + *title + "', git_url = '" + *git_url
                    + "', projectDoc = '" + *doc + "', note = '" + *note + "', createdTime = '"
                    + *createdTime + "' WHERE createdTime = '" + *oldTime + "' AND git_url = '"
                    + oldGit + "'")) {
        qWarning() << "🔴 " << query.lastError();
    } else {
        qDebug() << "🟢 Sucsessfull updated";
    }
}

void MainWindow::saveProjectToDB(QString *title, QString *git_url, QString *status,
                                 QString *createdTime)
{
    QSqlQuery query;

    if (!query.exec("INSERT INTO projects (title, git_url, projectDoc, note, status, createdTime) "
                    "VALUES('"
                    + *title + "', '" + *git_url + "', ' ', '# New project', '" + *status + "', '"
                    + *createdTime + "')")) {
        qWarning() << "🔴 " << query.lastError();
    } else {
        qDebug() << "🟢 Sucsessfull saved";
    }
}

void MainWindow::updateProjectStatus(QString *status, QString *createdTime, QString *oldTime)
{
    QSqlQuery query;

    if (!query.exec("UPDATE projects SET status = '" + *status + "' WHERE createdTime = '"
                    + *oldTime + "'")) {
        qWarning() << "🔴 " << query.lastError();
    } else {
        qDebug() << "🟢 Sucsessfull updated";
    }
}

void MainWindow::removeProjectFromDB(QString *git_url, QString *status, QString *createdTime)
{
    QSqlQuery query;

    if (!query.exec("DELETE FROM projects WHERE git_url = '" + *git_url + "'")) {
        qWarning() << "🔴 " << query.lastError();
    } else {
        qDebug() << "🟢 Sucsessfull removed";
    }
}

void MainWindow::loadProjects()
{
    notStartedProjects->clear();
    startedProjects->clear();
    finishlineProjects->clear();
    finishedProjects->clear();

    QSqlQuery query;

    query.exec("SELECT * FROM projects");
    while (query.next()) {
        int id = query.value("id").toInt();
        QString title = query.value("title").toString();
        QString git_url = query.value("git_url").toString();
        QString createdTime = query.value("createdTime").toString();
        QString status = query.value("status").toString();

        QString data = title + "\n" + git_url + "\n" + createdTime;

        QListWidgetItem *item = new QListWidgetItem(data);

        item->setData(Qt::UserRole, id);

        if (status == "NotStartedProjects") {
            notStartedProjects->addItem(item);
        }
        if (status == "StartedProjects") {
            startedProjects->addItem(item);
        }
        if (status == "FinishlineProjects") {
            finishlineProjects->addItem(item);
        }
        if (status == "FinishedProjects") {
            finishedProjects->addItem(item);
        } else {
            qWarning() << "🟠 Unknown status: " << status;
        }
    }
    qDebug() << "🟢 Projects was loaded";
}

#include <QApplication>
#include <QFile>
#include <QSplashScreen>

#include "mainwindow.h"
#include "sql_db/connectionDB.cpp"

void loadModules(QSplashScreen* psplash) {
    QTime time;
    time.start();

    for (int i = 0; i < 100;) {
        if (time.elapsed() > 1) {
            time.start();
            ++i;
        }
        psplash->showMessage("Loading data: " + QString::number(i) + "%",
                             Qt::AlignCenter | Qt::AlignBottom, Qt::white);

        qApp->processEvents();
    }
}

int main(int argc, char* argv[]) {
    QFile file(":/stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);

    QApplication a(argc, argv);

    if (createConnection() == false) {
        return -1;
    }
    else {
        qDebug() << "Connected";
    }

    MainWindow w;

    a.setStyleSheet(file.readAll());

    w.setWindowIcon(QIcon(":/resources/icon.png"));

    // QSplashScreen splash(QPixmap(":/icon.png"));
    // splash.show();
    // loadModules(&splash);
    // splash.finish(&w);

    w.show();
    return a.exec();
}

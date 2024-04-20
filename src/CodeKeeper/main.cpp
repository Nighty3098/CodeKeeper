#include <QApplication>
#include <QFile>
#include <QSplashScreen>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QFile file(":/stylesheet/stylesheet.qss");
    file.open(QFile::ReadOnly);

    QApplication a(argc, argv);

    MainWindow w;

    a.setStyleSheet(file.readAll());

    w.setWindowIcon(QIcon(":/icon.png"));
    w.setStyleSheet("QMainWindow { border-radius: 10px; }");

    QPainter pain;
    w.setAttribute(Qt::WA_TranslucentBackground);
    pain.setRenderHint(QPainter::Antialiasing);
    pain.setPen(Qt::NoPen);
    pain.drawRoundedRect(QRect(), 10, 10, Qt::AbsoluteSize);

    w.show();
    return a.exec();
}

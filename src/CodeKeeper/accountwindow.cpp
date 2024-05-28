#include "accountwindow.h"
#include <QtWidgets>

AccountWindow::AccountWindow(QWidget *parent) : QMainWindow{ parent }
{
    QFile file(":/stylesheet/stylesheet_setting_window.qss");
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QGridLayout(centralWidget);
    setFixedSize(400, 600);
}

AccountWindow::~AccountWindow(){};
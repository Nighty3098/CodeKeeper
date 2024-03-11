#include "syncwindow.h"
#include "ui_syncwindow.h"
#include <QSettings>
#include "mainwindow.h"

SyncWindow::SyncWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SyncWindow)
{
    GlobalSettings = new QSettings("Settings", "Settings");
    QFont selectedFont = GlobalSettings->value("font").value<QFont>();

    ui->setupUi(this);
}

SyncWindow::~SyncWindow()
{
    delete ui;
}

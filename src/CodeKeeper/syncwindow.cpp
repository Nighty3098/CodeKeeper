#include "syncwindow.h"
#include "ui_syncwindow.h"

SyncWindow::SyncWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SyncWindow)
{
    ui->setupUi(this);
}

SyncWindow::~SyncWindow()
{
    delete ui;
}

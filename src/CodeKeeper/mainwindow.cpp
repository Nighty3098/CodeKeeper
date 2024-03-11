#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_syncBtn_clicked()
{
    syncWindow = new SyncWindow();
    syncWindow->show();
}


void MainWindow::on_settingsBtn_clicked()
{
    settingsWindow = new SettingsWindow();
    settingsWindow->show();
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QCloseEvent>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QSettings settings("CodeKeeper", "CodeKeeper");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());

    GlobalSettings = new QSettings("Settings", "Settings");
    QFont selectedFont = GlobalSettings->value("font").value<QFont>();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    QSettings settings("CodeKeeper", "CodeKeeper");
    settings.setValue("myWidget/geometry", saveGeometry());
    settings.setValue("myWidget/windowState", saveState());

    delete ui;
}


void MainWindow::on_settingsBtn_clicked()
{
    settingsWindow = new SettingsWindow();
    settingsWindow->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("CodeKeeper", "CodeKeeper");
    settings.setValue("myWidget/geometry", saveGeometry());
    settings.setValue("myWidget/windowState", saveState());

    event->accept();
}

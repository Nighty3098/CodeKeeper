#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QCloseEvent>
#include <QFont>
#include "qmarkdowntextedit/qmarkdowntextedit.h"

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
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());

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
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());

    event->accept();
}

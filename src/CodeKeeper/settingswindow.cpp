#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QMessageBox>
#include "syncwindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingsWindow)
{
    GlobalSettings = new QSettings("Settings", "Settings");
    QFont selectedFont = GlobalSettings->value("font").value<QFont>();

    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_setupSyncBtn_clicked()
{
    syncWindow = new SyncWindow();
    syncWindow->show();
}


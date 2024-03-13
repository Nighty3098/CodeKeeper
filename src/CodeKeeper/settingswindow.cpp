#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QMessageBox>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingsWindow)
{
    GlobalSettings = new QSettings("Settings", "Settings");
    QFont selectedFont = GlobalSettings->value("font").value<QFont>();

    // setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

#include "settingswindow.h"
#include "syncwindow.h"
#include "ui_settingswindow.h"
#include <QSettings>
#include <QMessageBox>
#include "mainwindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWindow)
{
    GlobalSettings = new QSettings("Settings", "Settings");
    QFont selectedFont = GlobalSettings->value("font").value<QFont>();

/*
    ui->comboBox->setFont(QFont(selectedFont));
    ui->fontComboBox->setFont(QFont(selectedFont));
    ui->label_1->setFont(QFont(selectedFont));
    ui->label_2->setFont(QFont(selectedFont));
    ui->label_3->setFont(QFont(selectedFont));
    ui->spinBox->setFont(QFont(selectedFont));
    ui->saveBtn->setFont(QFont(selectedFont));
    ui->clearDataBtn->setFont(QFont(selectedFont));
    ui->title->setFont(QFont(selectedFont));
    ui->setupSyncBtn->setFont(QFont(selectedFont));
*/

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

void SettingsWindow::on_saveBtn_clicked()
{
    GlobalSettings = new QSettings("Settings", "Settings");
    QFont selectedFont = ui->fontComboBox->currentFont();
    GlobalSettings->setValue("font", selectedFont);
    ui->title->setFont(QFont(selectedFont));

    QMessageBox::information(this, "Restart Required", "Please restart the program to apply changes.");
}


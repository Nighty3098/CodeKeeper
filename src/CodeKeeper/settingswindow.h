#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include "syncwindow.h"
#include <QSettings>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSettings *GlobalSettings;
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

private slots:
    void on_setupSyncBtn_clicked();

private:
    Ui::SettingsWindow *ui;
    SyncWindow *syncWindow;
};

#endif // SETTINGSWINDOW_H

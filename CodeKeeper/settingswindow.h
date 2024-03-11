#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "syncwindow.h"
#include <QWidget>
#include <QSettings>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

    QSettings *GlobalSettings;
    Ui::SettingsWindow *ui;

private:
    SyncWindow *syncWindow;

private slots:
    void on_setupSyncBtn_clicked();
    void on_saveBtn_clicked();
};

#endif // SETTINGSWINDOW_H

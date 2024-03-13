#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
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

private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H

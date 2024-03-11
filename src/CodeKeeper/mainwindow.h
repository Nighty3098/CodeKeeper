#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingswindow.h"
#include "syncwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_syncBtn_clicked();

    void on_settingsBtn_clicked();

private:
    Ui::MainWindow *ui;
    SettingsWindow *settingsWindow;
    SyncWindow *syncWindow;
};
#endif // MAINWINDOW_H

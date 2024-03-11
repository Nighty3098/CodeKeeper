#ifndef SYNCWINDOW_H
#define SYNCWINDOW_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class SyncWindow;
}

class SyncWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SyncWindow(QWidget *parent = nullptr);
    ~SyncWindow();

    QSettings *GlobalSettings;
    Ui::SyncWindow *ui;

private:

};

#endif // SYNCWINDOW_H

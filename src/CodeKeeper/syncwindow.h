#ifndef SYNCWINDOW_H
#define SYNCWINDOW_H

#include <QWidget>

namespace Ui {
class SyncWindow;
}

class SyncWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SyncWindow(QWidget *parent = nullptr);
    ~SyncWindow();
    Ui::SyncWindow *ui;

private:

};

#endif // SYNCWINDOW_H

#ifndef ACCOUNTWINDOW_H
#define ACCOUNTWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QGridLayout>
#include <QtWidgets>

class AccountWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AccountWindow(QWidget *parent = nullptr);
    ~AccountWindow();

    QSettings *globalSettings;

    QFont selectedFont;
    QString font_size;
    QString theme;
    QString git_repo;
    QString git_user;
    QString git_token;
    QString path;

private:
    QWidget *centralWidget;
    QGridLayout *mainLayout;
};

#endif // ACCOUNTWINDOW_H

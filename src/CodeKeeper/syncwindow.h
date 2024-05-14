#ifndef SYNCWINDOW_H
#define SYNCWINDOW_H

#include "syncFunc/functional.cpp"
#include <QtWidgets>
#include <QSettings>
#include <QGridLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class SyncWindow : public QMainWindow
{
    Q_OBJECT;

public:
    QSettings *globalSettings;

    SyncWindow(QWidget *parent = nullptr);
    ~SyncWindow();

    QString dir;
    QFont selectedFont;
    QString font_size;
    QString theme;
    QString git_repo;
    QString git_user;
    QString git_token;

private slots:
    bool checkConnection();
    void setFontStyle();

protected:
private:
    QWidget *centralWidget;
    QGridLayout *mainLayout;

    QLabel *mainTitle;
};

#endif // MAINWINDOW_H
#ifndef SYNCWINDOW_H
#define SYNCWINDOW_H

#include <QtWidgets>
#include <QSettings>
#include <QGridLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>


class SyncWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSettings *globalSettings;
    
    SyncWindow(QWidget *parent = nullptr);
    ~SyncWindow();

    QFont selectedFont;
    QString font_size;
    QString dir;

private slots:
    void checkConnection();

protected:
private:
    QWidget *centralWidget;
    QGridLayout *mainLayout;

    QLabel *mainTitle;
    QLabel *checkConnectionL;

    QNetworkAccessManager* manager;
    QNetworkReply* reply;

};

#endif // MAINWINDOW_H

#ifndef SYNCWINDOW_H
#define SYNCWINDOW_H

#include <QGridLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include <QtWidgets>

class SyncWindow : public QMainWindow
{
    Q_OBJECT;

  public:
    void setFontStyle();

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
    void startSyncingFunc();
    void cancelSyncingFunc();

  protected:
  private:
    QWidget *centralWidget;
    QGridLayout *mainLayout;

    QLabel *appIcon;
    QLabel *appName;
    QLabel *infoLabel;

    QProgressBar *syncingProgress;

    QPushButton *startSyncing;
    QPushButton *stopSyncing;
};

#endif // SYNCWINDOW_H

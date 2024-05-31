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

    void setFontStyle();

    QSettings *globalSettings;

    QFont selectedFont;
    QString font_size;
    QString theme;
    QString path;
    
    QString git_repo;
    QString git_user;
    QString git_token;

    bool isAutoSyncB;

private:
    QWidget *centralWidget;
    QGridLayout *mainLayout;

    QLabel *profilePicture;
    QLabel *userName;
    QLabel *profileInfo;
    QLabel *codeKeeperStats;

    QPushButton *closeWindow;
    QPushButton *openRepo;

private slots:
    void setUserData(const QString& username, QLabel* label);
    void closeWindowSlot();
    void getSettingsData();
    void setImageFromUrl(const QString& url, QLabel* label);
    void onOpenRepoClicked();
};

#endif // ACCOUNTWINDOW_H

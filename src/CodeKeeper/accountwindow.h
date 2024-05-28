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
    QString path;
    
    QString git_repo;
    QString git_user;
    QString git_token;

    bool isAutoSyncB;

private:
    QWidget *centralWidget;
    QGridLayout *mainLayout;

    QLabel *profilePicture;
    QLabel *profileName;

    QPushButton *closeWindow;

private slots:
    void closeWindowSlot();
    void getSettingsData();
    void setFontStyle();
    void setGithubAvatar(const QString &username, QLabel *label);
};

#endif // ACCOUNTWINDOW_H

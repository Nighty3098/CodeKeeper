#ifndef ACCOUNTWINDOW_H
#define ACCOUNTWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QGridLayout>
#include <QtWidgets>
#include "custom/circleProgressbar/ProgressCircle.h"
#include "custom/circleChart/CircleChart.h"
#include "custom/ColorValueDisplay/ColorValueDisplay.h"
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
    QLabel *tasksStats;

    QLabel *tasksTitle;
    QLabel *projectTitle;

    QPushButton *closeWindow;
    QPushButton *openRepo;

    CircleProgressBar *tasksStatsProgress;
    ColorValueDisplay *tasksChartValuesDisplay;

    CircleChart *projectsChart;
    ColorValueDisplay *chartValuesDisplay;

private slots:
    void setUserData(const QString &username, QLabel *label);
    void closeWindowSlot();
    void getSettingsData();
    void setImageFromUrl(const QString &url, QLabel *label);
    void onOpenRepoClicked();
    int getStarsCount(const QString& username, const QString& token);
    void setTasksProgress();
    void setProjectsStats();
    void get_image_url(const QString& username, QLabel *label);
};

#endif // ACCOUNTWINDOW_H

#ifndef ACCOUNTWINDOW_H
#define ACCOUNTWINDOW_H

#include "custom/ColorValueDisplay/ColorValueDisplay.h"
#include "custom/circleChart/CircleChart.h"
#include "custom/circleProgressbar/ProgressCircle.h"
#include <QGridLayout>
#include <QMainWindow>
#include <QObject>
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
    int theme;
    QString path;

    QString git_repo;
    QString git_user;
    QString git_token;

    bool isAutoSyncB;
    bool isCustomTheme;

  private:
    QWidget *centralWidget;
    QGridLayout *mainLayout;

    QLabel *profilePicture;
    QLabel *userName;
    QLabel *profileInfo;
    QLabel *tasksStats;

    QLabel *tasksTitle;
    QLabel *projectTitle;
    QLabel *langsTitle;

    QPushButton *closeWindow;
    QPushButton *openRepo;

    CircleProgressBar *tasksStatsProgress;
    ColorValueDisplay *tasksChartValuesDisplay;

    CircleChart *projectsChart;
    ColorValueDisplay *chartValuesDisplay;

    CircleChart *langsChart;
    ColorValueDisplay *langsValuesDisplay;

    QWidget *statsWidget;

  private slots:
    void setUserData(const QString &username, QLabel *label);
    void closeWindowSlot();
    void getSettingsData();
    void setImageFromUrl(const QString &url, QLabel *label);
    void onOpenRepoClicked();
    int getStarsCount(const QString &username, const QString &token);
    void setTasksProgress();
    void setProjectsStats();
    void setLangsStats(const QString langsData);
    void get_image_url(const QString &username, QLabel *label);
    QString getLangByRepo(const QStringList &repositories);
    float calculatePercentage(int count, int total);
};

#endif // ACCOUNTWINDOW_H

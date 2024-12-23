#ifndef ACCOUNTWINDOW_H
#define ACCOUNTWINDOW_H

#include "custom/ColorValueDisplay/ColorValueDisplay.h"
#include "custom/circleChart/CircleChart.h"
#include "custom/circleProgressbar/ProgressCircle.h"
#include <QGridLayout>
#include <QMainWindow>
#include <QObject>
#include <QtWidgets>

#include <QCache>
#include <QSettings>
#include <QDateTime>

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

    QCache<QString, QPixmap> imageCache;

  private:
    QHBoxLayout *langsStatsLayout;
    QHBoxLayout *GitLangsStatsLayout;

    QHBoxLayout *tasksStatsLayout;
    QHBoxLayout *projectsStatsLayout;

    QWidget *centralWidget;
    QGridLayout *mainLayout;

    QLabel *profilePicture;
    QLabel *userName;
    QLabel *profileInfo;
    QLabel *tasksStats;

    QLabel *tasksTitle;
    QLabel *projectTitle;

    QPushButton *closeWindow;
    QPushButton *openRepo;

    CircleProgressBar *tasksStatsProgress;
    ColorValueDisplay *tasksChartValuesDisplay;

    CircleChart *projectsChart;
    ColorValueDisplay *chartValuesDisplay;

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
    void get_image_url(const QString &username, QLabel *label);
    QStringList getAllGitReposUrls(const QString &username);
    float calculatePercentage(int count, int total);
};

#endif // ACCOUNTWINDOW_H

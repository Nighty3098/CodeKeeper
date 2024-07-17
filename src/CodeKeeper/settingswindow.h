#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSettings>

class SettingsWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    QSettings *globalSettings;

    QFont selectedFont;
    QString font_size;
    QString theme;
    QString git_repo;
    QString git_user;
    QString git_token;
    QString path;

    bool isTimeB;
    bool isDateB;
    bool isHostB;
    bool isAutoSyncB;
    bool isCustomTitlebar;
    bool isCustomTheme;

    bool isCreated;
    bool isReleaseDate;
    bool isLastCommit;
    bool isPullReq;
    bool isLicense;
    bool isRelease;
    bool isIssue;
    bool isDownloads;
    bool isCommit;
    bool isLang;
    bool isStars;
    bool isForks;
    bool isRepoSize;

private slots:
    void closeEvent(QCloseEvent *event);
    void QuitW();
    void checkUpdates();
    void saveData();
    void fopenFolder();

    void setFontPr2(QFont *selectedFont, int *font_size_int);
    void checkRepo();
    QString getNewAppVersion();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QTabWidget *tabs;

    QPushButton *saveBtn;
    QPushButton *quitBtn;

    // main tab
    QLabel *appName;
    QLabel *urlToRepo;
    QLabel *versionInfo;

    QPushButton *checkUpdatesBtn;

    // sync settings
    QLabel *repoAvailability;
    QLabel *gitLabel;
    QLabel *gitLabel2;

    QLineEdit *gitToken;
    QLineEdit *gitUser;
    QLineEdit *gitRepo;

    QCheckBox *autoSyncAfterStart;

    QCheckBox *isDate;
    QCheckBox *isTime;
    QCheckBox *isHost;
    QCheckBox *isSync;

    // appereance
    QLabel *mainTitle;

    QLabel *fontLabel;
    QLabel *fontSizeLabel;
    QLabel *themeLabel;

    QSpinBox *fontSize;
    QFontComboBox *fontSelector;
    QComboBox *themeSelector;

    QCheckBox *customTheme;
    QCheckBox *customTitleBar;

    // storage
    QLabel *storageLabel;
    QLineEdit *pathToFolder;
    QPushButton *openFolder;

    // projects content
    QLabel *projectsContentLabel;

    QCheckBox *CisCreated;
    QCheckBox *CisReleaseDate;
    QCheckBox *CisLastCommit;
    QCheckBox *CisPullReq;
    QCheckBox *CisLicense;
    QCheckBox *CisRelease;
    QCheckBox *CisIssue;
    QCheckBox *CisDownloads;
    QCheckBox *CisCommit;
    QCheckBox *CisLang;
    QCheckBox *CisStars;
    QCheckBox *CisForks;
    QCheckBox *CisRepoSize;
};

#endif // SETTINGSWINDOW_H

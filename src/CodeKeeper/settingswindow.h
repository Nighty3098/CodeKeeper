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

    void checkUpdates();
    QString getNewAppVersion();

    QLabel *versionInfo;

    QFont selectedFont;
    QString font_size;
    QString theme;
    QString git_repo;
    QString git_user;
    QString git_token;
    QString path;

    int appLang;

    bool isTimeB;
    bool isDateB;
    bool isHostB;
    bool isAutoSyncB;
    bool isCustomTitlebar;
    bool isCustomTheme;
    bool isAutoCheckUpdates;

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

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        } else {
            QMainWindow::mousePressEvent(event);
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        } else {
            QMainWindow::mouseMoveEvent(event);
        }
    }

private slots:
    void closeEvent(QCloseEvent *event);
    void QuitW();
    void saveData();
    void fopenFolder();

    QString fetchSecondLastRelease();

    void setStyle2(QFont *selectedFont, int *font_size_int);
    void checkRepo();

private:
    QPoint m_dragPosition;

    QSizeGrip *sizeGrip;

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QTabWidget *tabs;

    QPushButton *saveBtn;
    QPushButton *quitBtn;

    // main tab
    QLabel *appName;
    QLabel *urlToRepo;

    QPushButton *checkUpdatesBtn;
    QCheckBox *autoUpdates;

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
    QLabel *langLabel;

    QSpinBox *fontSize;
    QFontComboBox *fontSelector;
    QComboBox *themeSelector;

    QComboBox *langSelector;

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

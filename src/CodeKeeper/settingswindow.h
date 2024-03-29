#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSettings>

class SettingsWindow : public QMainWindow {
    Q_OBJECT
   public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    QSettings *globalSettings;

   private slots:
    void closeEvent(QCloseEvent *event);
    void QuitW();
    void checkUpdates();
    void saveData();
    void fopenFolder();

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

    // QLabel *languageLabel;

    QSpinBox *fontSize;
    QFontComboBox *fontSelector;
    QComboBox *themeSelector;

    // sync settings

    QLabel *gitLabel;
    QLabel *gitLabel2;

    QLineEdit *gitToken;
    QLineEdit *gitUser;
    QLineEdit *gitRepo;

    QCheckBox *autoSyncAfterStart;

    QCheckBox *isDate;
    QCheckBox *isTime;
    QCheckBox *isHost;

    // appereance
    QLabel *mainTitle;

    QLabel *fontLabel;
    QLabel *fontSizeLabel;
    QLabel *themeLabel;

    // storage
    QLabel *storageLabel;
    QLineEdit *pathToFolder;
    QPushButton *openFolder;
};

#endif  // SETTINGSWINDOW_H

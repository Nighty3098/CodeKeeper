#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "settingswindow.h"
#include "qmarkdowntextedit/qmarkdowntextedit.h"
#include <QSettings>
#include <QTextBrowser>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSettings *globalSettings;
    bool isVisibleNotesList;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addNewTask();
    void openSettingsWindow();
    void hideNotesList();
    void showPreview();
    void updateMDPreview();
    void setHeader();
    void removeTask();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QTabWidget *tabs;

    // ========================================================
    // main tab

    QLabel *mainTitle;
    QPushButton *openFolderBtn;
    QPushButton *syncDataBtn;
    QPushButton *openSettingsBtn;

    // ========================================================
    // notes tab

    QTreeWidget *notesList;
    QMarkdownTextEdit *noteEdit;
    QTextBrowser *mdPreview;
    QLineEdit *noteName;
    QToolButton *menuButton;
    QLabel *timeLabel;
    QLabel *noteNameLabel;

    // ========================================================
    // tasks tab

    QListWidget *incompleteTasks;
    QListWidget *inprocessTasks;
    QListWidget *completeTasks;

    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;

    QLineEdit *taskText;
    QPushButton *addTask;
    QPushButton *rmTask;

    // ========================================================
    // projects tab
    
    QLabel *projectsMainLabel;

    QListWidget *notStartedProjects;
    QListWidget *startedProjects;
    QListWidget *finishedProjects;
    QListWidget *finishlineProjects;
    
    QToolButton *projectsMenuButton;
    
    SettingsWindow *settingsWindow;

};
#endif // MAINWINDOW_H

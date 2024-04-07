#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTextBrowser>
#include <QtWidgets>

#include "qmarkdowntextedit/qmarkdowntextedit.h"
#include "settingswindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    QSettings *globalSettings;
    bool isVisibleNotesList;

    QFont selectedFont;
    QString font_size;
    QString theme;
    QString path;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void openSettingsWindow();
    void openFolder();

    void hideNotesList();
    void showPreview();
    void showFolders();

    void updateMDPreview();
    void setHeader();

    void addNewTask();
    void removeTask();

    void createNote();
    void removeNote();
    void removeFolder();
    void createFolder();

    void updateTasksProgress(QTabWidget *tasksTab, QListWidget *incompleteTasks, QListWidget *inprocessTasks, QListWidget *completeTasks, QProgressBar *tasksProgress);
    void createProject();
    void removeProject();

    QString formatText(const QString &text);
    QString unformatText(const QString &text);
    void openProject(QListWidget *listWidget, QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void renameItemOnDoubleClick(QListWidget *listWidget, QListWidgetItem *item);

    // load data from folder
    void loadNotes(const QDir &dir);
    void loadTasks();
    void loadProjects();

    void setFontPr1();

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

    QListWidget *foldersList;
    QListWidget *notesList;
    QMarkdownTextEdit *noteEdit;
    MarkdownHighlighter *highlighter;
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

    QProgressBar *tasksProgress;
    QToolButton *tasksMenuBtn;

    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;

    QLineEdit *taskText;


    // ========================================================
    // projects tab

    QLabel *projectsMainLabel;
    QToolButton *projectsMenuButton;
    QMenu *projectsMenu;

    QLabel *fProjects;
    QLabel *flProjects;
    QLabel *sProjects;
    QLabel *nsProjects;

    QListWidget *notStartedProjects;
    QListWidget *startedProjects;
    QListWidget *finishedProjects;
    QListWidget *finishlineProjects;

    SettingsWindow *settingsWindow;
};
#endif  // MAINWINDOW_H

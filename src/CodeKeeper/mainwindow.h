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
    QDir path;

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
    void loadDocumentations(QDir path, QComboBox &comboBox);
    void openProject(QListWidget *listWidget, QListWidgetItem *item);
    
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void renameItemOnDoubleClick(QListWidget *listWidget, QListWidgetItem *item);
    void onNoteDoubleClicked(QTreeWidgetItem *item, QMarkdownTextEdit *edit, int column);

    // load data from folder
    void displayDirectoryStructure(const QDir &dir, QTreeWidget *tree);
    void loadTasks();
    void loadProjects();
    void setFontPr1();

    void setH1();
    void setH2();
    void setH3();
    void setList();
    void setLink();
    void setBold();
    void setItalic();
    void setStrike();
    void setTask();

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
    // QListWidget *foldersList;
    // QListWidget *notesList;
    QMarkdownTextEdit *noteEdit;
    MarkdownHighlighter *highlighter;
    QTextBrowser *mdPreview;
    QLineEdit *noteName;
    QToolButton *menuButton;
    QLabel *timeLabel;
    QLabel *noteNameLabel;

    QPushButton *setH1B;
    QPushButton *setH2B;
    QPushButton *setH3B;
    QPushButton *setListB;
    QPushButton *setLinkB;
    QPushButton *setBoldB;
    QPushButton *setItalicB;
    QPushButton *setStrikeB;
    QPushButton *setTaskB;

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

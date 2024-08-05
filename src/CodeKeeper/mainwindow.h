#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFile>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QMainWindow>
#include <QMimeData>
#include <QSettings>
#include <QTabBar>
#include <QTextBrowser>
#include <QTextStream>
#include <QThread>
#include <QWebEngineView>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets>

#include "3rdParty/qmarkdowntextedit/qmarkdowntextedit.h"
#include "accountwindow.h"
#include "settingswindow.h"
#include "syncwindow.h"

class CustomIconProvider : public QFileIconProvider
{
  public:
    QIcon icon(IconType type) const override
    {
        switch (type)
        {
        case QFileIconProvider::IconType::Computer:
            return QIcon(":/home_dir.png");
        case QFileIconProvider::IconType::Trashcan:
            return QIcon(":/trash.png");
        case QFileIconProvider::IconType::File:
            return QIcon(":/document.png");
        case QFileIconProvider::IconType::Folder:
            return QIcon(":/folder.png");
        default:
            return QFileIconProvider::icon(type);
        }
    }
};

class notesTree : public QTreeView
{
  protected:
};

class NoteEditor : public QMarkdownTextEdit
{
  protected:
    // ! Bug with cursor - need fixed

    void dropEvent(QDropEvent *event)
    {
        QString filePath = event->mimeData()->text();
        QFileInfo fileInfo(filePath);
        QString fileSuffix = fileInfo.suffix();

        qDebug() << "[Dropped file]:" << filePath;

        if (fileSuffix == "txt" || fileSuffix == "html" || fileSuffix == "md")
        {
            QString newLine = "[Dropped document](" + filePath + ")";

            QTextCursor cursor = this->textCursor();
            int lineNumber = cursor.blockNumber();
            QTextBlock block = this->document()->findBlockByNumber(lineNumber);
            cursor.movePosition(QTextCursor::EndOfLine);
            cursor.insertText(newLine);
            this->setTextCursor(cursor);
        }
        else
        {
            QString newLine = "![Dropped file](" + filePath + ")";

            QTextCursor cursor = this->textCursor();
            int lineNumber = cursor.blockNumber();
            QTextBlock block = this->document()->findBlockByNumber(lineNumber);
            cursor.movePosition(QTextCursor::EndOfLine);
            cursor.insertText(newLine);
            this->setTextCursor(cursor);
        }
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    QSettings *globalSettings;

    NoteEditor *noteEdit;
    notesTree *notesList;

    QFileSystemModel *notesDirModel;
    QFileSystemModel *noteFileModel;

    QTabWidget *tabs;

    void setSettingsData();
    void getSettingsData();

    void createCustomTitlebar();
    void setConnectionStatus();

    void setStyle(QFont *selectedFont, int *font_size_int);
    void loadNotes();
    void loadProjects();
    void loadTasks();

    bool createConnection(QString path);
    void createConnects();
    void createShortcuts();

    void activateProjectContextMenu(const QPoint &pos, QListWidget *listWidget);
    void activateTasksContextMenu(const QPoint &pos, QListWidget *listWidget);

    QStringList getAllReposUrl();

    QMarkdownTextEdit *note;

    QListWidget *incompleteTasks;
    QListWidget *inprocessTasks;
    QListWidget *completeTasks;

    QListWidget *notStartedProjects;
    QListWidget *startedProjects;
    QListWidget *finishedProjects;
    QListWidget *finishlineProjects;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isVisibleNotesList;
    bool isViewMode;
    bool isVisiblePreview;
    bool isVisibleFolders;
    bool isAutoSyncB;
    bool isCustomTitlebar;
    int sortNotesRole;
    bool isAutoSyncing;
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
    bool isAutoCheckUpdates;

    QString git_repo;
    QString git_user;
    QString git_token;

    QString dir;
    QFont selectedFont;
    QString font_size;
    QString theme;

    int appLang;

  private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    QString getRepositoryData(QString git_url, QTableWidget *table, QLabel *label);
    QString getProjectIssues(QString git_url);

    void openSettingsWindow();
    void fOpenAccountWindow();

    void openSyncWindow();
    void openFolder();

    void selectFileInQTreeView(QTreeView *treeView, const QString &fileName);

    void hideNotesList();
    void showPreview();
    void updateMDPreview();
    void setHeader();
    void createNote();
    void removeNote();
    void saveNote();
    void toViewMode();
    void createFolder();
    void renameItem();

    void removeTaskFromDB(QString *task, QString *status);
    void saveTaskToDB(QString *task, QString *status);
    void addNewTask();
    void removeTask();

    void on_listWidget_itemClicked(QListWidgetItem *item);
    void editTask();
    void onNoteDoubleClicked();
    void updateTasksProgress(QTabWidget *tasksTab, QListWidget *incompleteTasks, QListWidget *inprocessTasks,
                             QListWidget *completeTasks, QProgressBar *tasksProgress);

    void getTotalTasks(QTabWidget *tasksTab, QListWidget *incompleteTasks, QListWidget *inprocessTasks,
                       QListWidget *completeTasks);

    void getTotalProjects(QTabWidget *tasksTab, QListWidget *notStartedProjects, QListWidget *startedProjects,
                          QListWidget *finishedProjects, QListWidget *finishlineProjects);

    void openProject();
    void openGitProject();

    void createProject();
    void removeProject();

    void setH1();
    void setH2();
    void setH3();
    void setList();
    void setLink();
    void setNumList();
    void setBold();
    void setItalic();
    void setStrike();
    void setTask();
    void setTable();
    void setQuote();

    void setSortByTime();
    void setSortByName();

    void updateWindowTitle();

    QString getCurrentDateTimeString();

    void create_tasks_connection();
    void create_projects_connection();

    void toPdf(const QString &html, const QString &outputFile);
    void exportNoteToPdf();
    void exportNoteToHtml();

    void updateTaskStatus(QString *task, QString *status, QString *cT);
    void updateTaskData(QString *task, QString *status, QString *cT);
    void onMovingTaskFrom(QListWidgetItem *item, QListWidget *list);
    void onMovingTaskTo(QListWidgetItem *item, QListWidget *list);

    QStringList GetProjectData(QString *title, QString *status, QString *git_url);
    void updateProjectStatus(QString *status, QString *createdTime, QString *oldTime);
    void removeProjectFromDB(QString *git_url, QString *status, QString *createdTime);
    void saveProjectToDB(QString *title, QString *git_url, QString *status, QString *createdTime);
    void updateProjectData(QString *title, QString *git_url, QString *doc, QString *createdTime, QString *oldTime,
                           QString *oldGit);
    void onMovingProjectFrom(QListWidgetItem *item, QListWidget *list);
    void onMovingProjectTo(QListWidgetItem *item, QListWidget *list);

    bool checkConnection();
    void updateTime();

    void createNotesMenu(QMenu *menu, QString font_size);
    void createProjectMenu(QMenu *menu, QString font_size);
    void createTaskMenu(QMenu *menu, QString font_size);
    void createTrayMenu(QMenu *menu, QString font_size);

  protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
        else
        {
            QMainWindow::mousePressEvent(event);
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (event->buttons() & Qt::LeftButton)
        {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        }
        else
        {
            QMainWindow::mouseMoveEvent(event);
        }
    }

  private:
    QSystemTrayIcon *trayIcon;

    // shortcuts
    QShortcut *toFirstTab;
    QShortcut *toSecondTab;
    QShortcut *toThirdTab;
    QShortcut *toFourthTab;
    QShortcut *openSettingsWindowQS;

    // other
    QLabel *windowTitle;
    QWidget *centralWidget;
    QGridLayout *mainLayout;
    QHBoxLayout *winControlL;

    QSizeGrip *sizeGrip;
    QSizeGrip *sizeGrip2;
    QSizeGrip *sizeGrip3;
    QSizeGrip *sizeGrip4;

    QLabel *timeLabel;
    QLabel *dateLabel;
    QLabel *helloLabel;
    QLabel *decorationLabel;

    QPushButton *maximizeBtn;
    QPushButton *closeBtn;
    QPushButton *minimizeBtn;

    QPushButton *isAutoSync;
    QPushButton *isConnected;

    bool isFullScreen;
    QPoint m_dragPosition;

    // ========================================================
    // main tab
    QPushButton *syncDataBtn;
    QPushButton *openSettingsBtn;
    QPushButton *openAccountWindow;

    // ========================================================
    // notes tab
    CustomIconProvider *iconProvider;
    MarkdownHighlighter *highlighter;
    QToolButton *menuButton;
    QLabel *noteNameLabel;

    QWebEngineView *mdPreview;

    QPushButton *setH1B;
    QPushButton *setH2B;
    QPushButton *setH3B;
    QPushButton *setListB;
    QPushButton *setLinkB;
    QPushButton *setBoldB;
    QPushButton *setItalicB;
    QPushButton *setStrikeB;
    QPushButton *setTaskB;
    QPushButton *setNumListB;
    QPushButton *setTableB;
    QPushButton *setQuoteB;

    // ========================================================
    // tasks tab

    QProgressBar *tasksProgress;
    QToolButton *tasksMenuBtn;

    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;

    QLineEdit *taskText;

    // ========================================================

    QPushButton *mainTabButton;
    QPushButton *tasksTabButton;
    QPushButton *notesTabButton;
    QPushButton *projectsTabButton;

    // ========================================================
    // projects tab
    QLabel *projectsMainLabel;
    QToolButton *projectsMenuButton;

    QLabel *totalProjectsL;
    QLabel *fProjects;
    QLabel *flProjects;
    QLabel *sProjects;
    QLabel *nsProjects;

    QAction *newNote;
    QAction *rmNote;
    QAction *expandAllA;
    QAction *renameItemA;
    QAction *newFolder;
    QAction *showList;
    QAction *showRender;

    QAction *exportToPdf;
    QAction *exportToHtml;

    QAction *viewMode;
    QAction *nameAction;
    QAction *dateAction;

    QAction *addTaskA;
    QAction *rmTaskA;
    QAction *editTaskA;
    
    QAction *newProject;
    QAction *openProjectInGit;
    QAction *rmProject;
    QAction *editProject;

    QAction *setH1A;
    QAction *setH2A;
    QAction *setH3A;
    QAction *setListA;
    QAction *setLinkA;
    QAction *setTaskA;
    QAction *setBoldA;
    QAction *setItalicA;
    QAction *setStrikeA;
    QAction *setNumListA;
    QAction *setTableA;
    QAction *setQuoteA;

    QAction *closeAppA;
    QAction *openNotesA;
    QAction *openProjectsA;
    QAction *openTasksA;

    QMenu *menu;
    QMenu *tasksMenu;
    QMenu *projectsMenu;

    AccountWindow *accountWindow;
    SettingsWindow *settingsWindow;
    SyncWindow *syncWindow;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "settingswindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addNewTask();
    void on_item_double_clicked(QListWidgetItem *item);

    void openSettingsWindow();

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
    QPlainTextEdit *noteEdit;
    QLineEdit *noteName;
    QToolButton *menuButton;

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
    SettingsWindow *settingsWindow;

};
#endif // MAINWINDOW_H

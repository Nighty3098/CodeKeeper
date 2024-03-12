/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabs;
    QWidget *homeTab;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *title;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QHBoxLayout *syncL;
    QPushButton *syncBtn;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *settingsL;
    QPushButton *settingsBtn;
    QWidget *notesTab;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *noteL2;
    QHBoxLayout *noteL;
    QTreeWidget *notesTree;
    QTextEdit *noteEdit;
    QWidget *tasksTab;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *incompleteTasks;
    QLabel *title_1;
    QListWidget *incompleteList;
    QVBoxLayout *inprocessTasks;
    QLabel *title_2;
    QListWidget *inprocessList;
    QVBoxLayout *completeTasks;
    QLabel *title_3;
    QListWidget *completeList;
    QWidget *projectsTab;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(776, 555);
        MainWindow->setMinimumSize(QSize(400, 300));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("applications-development")));
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("QTabWidget::tab-bar { alignment: center; }"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabs = new QTabWidget(centralwidget);
        tabs->setObjectName(QString::fromUtf8("tabs"));
        homeTab = new QWidget();
        homeTab->setObjectName(QString::fromUtf8("homeTab"));
        verticalLayout = new QVBoxLayout(homeTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        title = new QLabel(homeTab);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setPointSize(40);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(title);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton = new QPushButton(homeTab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(200, 30));
        pushButton->setMaximumSize(QSize(200, 30));

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_4);

        syncL = new QHBoxLayout();
        syncL->setObjectName(QString::fromUtf8("syncL"));
        syncBtn = new QPushButton(homeTab);
        syncBtn->setObjectName(QString::fromUtf8("syncBtn"));
        syncBtn->setMinimumSize(QSize(200, 30));
        syncBtn->setMaximumSize(QSize(200, 30));

        syncL->addWidget(syncBtn);


        verticalLayout->addLayout(syncL);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        settingsL = new QHBoxLayout();
        settingsL->setObjectName(QString::fromUtf8("settingsL"));
        settingsBtn = new QPushButton(homeTab);
        settingsBtn->setObjectName(QString::fromUtf8("settingsBtn"));
        settingsBtn->setMinimumSize(QSize(200, 30));
        settingsBtn->setMaximumSize(QSize(200, 30));

        settingsL->addWidget(settingsBtn);


        verticalLayout->addLayout(settingsL);

        tabs->addTab(homeTab, QString());
        notesTab = new QWidget();
        notesTab->setObjectName(QString::fromUtf8("notesTab"));
        horizontalLayout_2 = new QHBoxLayout(notesTab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        noteL2 = new QVBoxLayout();
        noteL2->setObjectName(QString::fromUtf8("noteL2"));
        noteL = new QHBoxLayout();
        noteL->setObjectName(QString::fromUtf8("noteL"));
        notesTree = new QTreeWidget(notesTab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(notesTree);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(notesTree);
        new QTreeWidgetItem(__qtreewidgetitem1);
        notesTree->setObjectName(QString::fromUtf8("notesTree"));
        notesTree->setMinimumSize(QSize(100, 0));
        notesTree->setMaximumSize(QSize(150, 16777215));

        noteL->addWidget(notesTree);

        noteEdit = new QTextEdit(notesTab);
        noteEdit->setObjectName(QString::fromUtf8("noteEdit"));

        noteL->addWidget(noteEdit);


        noteL2->addLayout(noteL);


        horizontalLayout_2->addLayout(noteL2);

        tabs->addTab(notesTab, QString());
        tasksTab = new QWidget();
        tasksTab->setObjectName(QString::fromUtf8("tasksTab"));
        horizontalLayout_3 = new QHBoxLayout(tasksTab);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        incompleteTasks = new QVBoxLayout();
        incompleteTasks->setObjectName(QString::fromUtf8("incompleteTasks"));
        title_1 = new QLabel(tasksTab);
        title_1->setObjectName(QString::fromUtf8("title_1"));
        title_1->setMinimumSize(QSize(0, 20));
        title_1->setAlignment(Qt::AlignCenter);

        incompleteTasks->addWidget(title_1);

        incompleteList = new QListWidget(tasksTab);
        incompleteList->setObjectName(QString::fromUtf8("incompleteList"));

        incompleteTasks->addWidget(incompleteList);


        horizontalLayout_3->addLayout(incompleteTasks);

        inprocessTasks = new QVBoxLayout();
        inprocessTasks->setObjectName(QString::fromUtf8("inprocessTasks"));
        title_2 = new QLabel(tasksTab);
        title_2->setObjectName(QString::fromUtf8("title_2"));
        title_2->setMinimumSize(QSize(0, 20));
        title_2->setAlignment(Qt::AlignCenter);

        inprocessTasks->addWidget(title_2);

        inprocessList = new QListWidget(tasksTab);
        inprocessList->setObjectName(QString::fromUtf8("inprocessList"));

        inprocessTasks->addWidget(inprocessList);


        horizontalLayout_3->addLayout(inprocessTasks);

        completeTasks = new QVBoxLayout();
        completeTasks->setObjectName(QString::fromUtf8("completeTasks"));
        title_3 = new QLabel(tasksTab);
        title_3->setObjectName(QString::fromUtf8("title_3"));
        title_3->setMinimumSize(QSize(0, 20));
        title_3->setMaximumSize(QSize(16777215, 50));
        title_3->setAlignment(Qt::AlignCenter);

        completeTasks->addWidget(title_3);

        completeList = new QListWidget(tasksTab);
        completeList->setObjectName(QString::fromUtf8("completeList"));

        completeTasks->addWidget(completeList);


        horizontalLayout_3->addLayout(completeTasks);

        tabs->addTab(tasksTab, QString());
        projectsTab = new QWidget();
        projectsTab->setObjectName(QString::fromUtf8("projectsTab"));
        tabs->addTab(projectsTab, QString());

        horizontalLayout->addWidget(tabs);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CodeKeeper", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "CodeKeeper", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Open folder", nullptr));
        syncBtn->setText(QCoreApplication::translate("MainWindow", "Sync data", nullptr));
        settingsBtn->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        tabs->setTabText(tabs->indexOf(homeTab), QCoreApplication::translate("MainWindow", "Homepage", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = notesTree->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Notes", nullptr));

        const bool __sortingEnabled = notesTree->isSortingEnabled();
        notesTree->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = notesTree->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("MainWindow", "Dev", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("MainWindow", "\320\236\320\236\320\237", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("MainWindow", "Qt c++", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = notesTree->topLevelItem(1);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("MainWindow", "School", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("MainWindow", "math", nullptr));
        notesTree->setSortingEnabled(__sortingEnabled);

        tabs->setTabText(tabs->indexOf(notesTab), QCoreApplication::translate("MainWindow", "Notes", nullptr));
        title_1->setText(QCoreApplication::translate("MainWindow", "Incomplete tasks", nullptr));
        title_2->setText(QCoreApplication::translate("MainWindow", "Inprocess Tasks", nullptr));
        title_3->setText(QCoreApplication::translate("MainWindow", "Complete Tasks", nullptr));
        tabs->setTabText(tabs->indexOf(tasksTab), QCoreApplication::translate("MainWindow", "Tasks", nullptr));
        tabs->setTabText(tabs->indexOf(projectsTab), QCoreApplication::translate("MainWindow", "Projects", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

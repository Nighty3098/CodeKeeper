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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
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
    QLabel *label;
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
    QPlainTextEdit *plainTextEdit;
    QWidget *tasksTab;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
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
        MainWindow->resize(722, 624);
        MainWindow->setMinimumSize(QSize(560, 400));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("applications-development")));
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("QTabWidget::tab-bar { alignment: center; }"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabs = new QTabWidget(centralwidget);
        tabs->setObjectName(QString::fromUtf8("tabs"));
        tabs->setMovable(true);
        tabs->setTabBarAutoHide(false);
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

        label = new QLabel(homeTab);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Myanmar Text"));
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton = new QPushButton(homeTab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(200, 25));
        pushButton->setMaximumSize(QSize(200, 25));
        QFont font2;
        font2.setPointSize(10);
        pushButton->setFont(font2);

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_4);

        syncL = new QHBoxLayout();
        syncL->setObjectName(QString::fromUtf8("syncL"));
        syncBtn = new QPushButton(homeTab);
        syncBtn->setObjectName(QString::fromUtf8("syncBtn"));
        syncBtn->setMinimumSize(QSize(200, 25));
        syncBtn->setMaximumSize(QSize(200, 25));
        syncBtn->setFont(font2);

        syncL->addWidget(syncBtn);


        verticalLayout->addLayout(syncL);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        settingsL = new QHBoxLayout();
        settingsL->setObjectName(QString::fromUtf8("settingsL"));
        settingsBtn = new QPushButton(homeTab);
        settingsBtn->setObjectName(QString::fromUtf8("settingsBtn"));
        settingsBtn->setMinimumSize(QSize(200, 25));
        settingsBtn->setMaximumSize(QSize(200, 25));
        settingsBtn->setFont(font2);

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
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(notesTree);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        notesTree->setObjectName(QString::fromUtf8("notesTree"));
        notesTree->setMinimumSize(QSize(100, 0));
        notesTree->setMaximumSize(QSize(150, 16777215));
        QFont font3;
        font3.setPointSize(10);
        font3.setItalic(true);
        notesTree->setFont(font3);
        notesTree->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        notesTree->setTabKeyNavigation(true);
        notesTree->setDragEnabled(true);
        notesTree->setDragDropMode(QAbstractItemView::DragDrop);
        notesTree->setDefaultDropAction(Qt::MoveAction);
        notesTree->setSelectionBehavior(QAbstractItemView::SelectItems);
        notesTree->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        notesTree->setAutoExpandDelay(-2);
        notesTree->setIndentation(15);
        notesTree->setUniformRowHeights(false);
        notesTree->setSortingEnabled(false);
        notesTree->setAnimated(true);
        notesTree->setWordWrap(true);
        notesTree->setColumnCount(1);
        notesTree->header()->setVisible(false);
        notesTree->header()->setProperty("showSortIndicator", QVariant(false));

        noteL->addWidget(notesTree);

        plainTextEdit = new QPlainTextEdit(notesTab);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setFont(font2);
        plainTextEdit->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse|Qt::TextBrowserInteraction|Qt::TextEditable|Qt::TextEditorInteraction|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        noteL->addWidget(plainTextEdit);


        noteL2->addLayout(noteL);


        horizontalLayout_2->addLayout(noteL2);

        tabs->addTab(notesTab, QString());
        tasksTab = new QWidget();
        tasksTab->setObjectName(QString::fromUtf8("tasksTab"));
        horizontalLayout_3 = new QHBoxLayout(tasksTab);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, -1, -1);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, -1, -1, -1);
        incompleteTasks = new QVBoxLayout();
        incompleteTasks->setObjectName(QString::fromUtf8("incompleteTasks"));
        title_1 = new QLabel(tasksTab);
        title_1->setObjectName(QString::fromUtf8("title_1"));
        title_1->setMinimumSize(QSize(0, 20));
        title_1->setFont(font2);
        title_1->setAlignment(Qt::AlignCenter);

        incompleteTasks->addWidget(title_1);

        incompleteList = new QListWidget(tasksTab);
        new QListWidgetItem(incompleteList);
        new QListWidgetItem(incompleteList);
        new QListWidgetItem(incompleteList);
        new QListWidgetItem(incompleteList);
        incompleteList->setObjectName(QString::fromUtf8("incompleteList"));
        incompleteList->setFont(font2);
        incompleteList->setLineWidth(2);
        incompleteList->setMidLineWidth(2);
        incompleteList->setDragEnabled(true);
        incompleteList->setDragDropOverwriteMode(false);
        incompleteList->setDragDropMode(QAbstractItemView::DragDrop);
        incompleteList->setDefaultDropAction(Qt::MoveAction);
        incompleteList->setAlternatingRowColors(false);
        incompleteList->setSpacing(3);
        incompleteList->setWordWrap(true);

        incompleteTasks->addWidget(incompleteList);


        horizontalLayout_5->addLayout(incompleteTasks);

        inprocessTasks = new QVBoxLayout();
        inprocessTasks->setObjectName(QString::fromUtf8("inprocessTasks"));
        title_2 = new QLabel(tasksTab);
        title_2->setObjectName(QString::fromUtf8("title_2"));
        title_2->setMinimumSize(QSize(0, 20));
        title_2->setFont(font2);
        title_2->setAlignment(Qt::AlignCenter);

        inprocessTasks->addWidget(title_2);

        inprocessList = new QListWidget(tasksTab);
        inprocessList->setObjectName(QString::fromUtf8("inprocessList"));
        inprocessList->setFont(font3);
        inprocessList->setLineWidth(2);
        inprocessList->setMidLineWidth(2);
        inprocessList->setDragEnabled(true);
        inprocessList->setDragDropOverwriteMode(false);
        inprocessList->setDragDropMode(QAbstractItemView::DragDrop);
        inprocessList->setDefaultDropAction(Qt::MoveAction);
        inprocessList->setAlternatingRowColors(false);
        inprocessList->setSpacing(3);
        inprocessList->setWordWrap(true);

        inprocessTasks->addWidget(inprocessList);


        horizontalLayout_5->addLayout(inprocessTasks);

        completeTasks = new QVBoxLayout();
        completeTasks->setObjectName(QString::fromUtf8("completeTasks"));
        title_3 = new QLabel(tasksTab);
        title_3->setObjectName(QString::fromUtf8("title_3"));
        title_3->setMinimumSize(QSize(0, 20));
        title_3->setMaximumSize(QSize(16777215, 50));
        title_3->setFont(font2);
        title_3->setAlignment(Qt::AlignCenter);

        completeTasks->addWidget(title_3);

        completeList = new QListWidget(tasksTab);
        completeList->setObjectName(QString::fromUtf8("completeList"));
        QFont font4;
        font4.setPointSize(10);
        font4.setStrikeOut(true);
        completeList->setFont(font4);
        completeList->setLineWidth(2);
        completeList->setMidLineWidth(2);
        completeList->setDragEnabled(true);
        completeList->setDragDropOverwriteMode(false);
        completeList->setDragDropMode(QAbstractItemView::DragDrop);
        completeList->setDefaultDropAction(Qt::MoveAction);
        completeList->setAlternatingRowColors(false);
        completeList->setSpacing(3);
        completeList->setWordWrap(true);

        completeTasks->addWidget(completeList);


        horizontalLayout_5->addLayout(completeTasks);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_3->addLayout(verticalLayout_2);

        tabs->addTab(tasksTab, QString());
        projectsTab = new QWidget();
        projectsTab->setObjectName(QString::fromUtf8("projectsTab"));
        tabs->addTab(projectsTab, QString());

        horizontalLayout->addWidget(tabs);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabs->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CodeKeeper", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "CodeKeeper", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "https://github.com/Nighty3098", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Open folder", nullptr));
        syncBtn->setText(QCoreApplication::translate("MainWindow", "Sync data", nullptr));
        settingsBtn->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        tabs->setTabText(tabs->indexOf(homeTab), QCoreApplication::translate("MainWindow", "Homepage", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = notesTree->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Notes", nullptr));

        const bool __sortingEnabled = notesTree->isSortingEnabled();
        notesTree->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = notesTree->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("MainWindow", "School", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("MainWindow", "math", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = notesTree->topLevelItem(1);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("MainWindow", "Dev", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem3->child(0);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("MainWindow", "\320\236\320\236\320\237", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem3->child(1);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("MainWindow", "Qt c++", nullptr));
        notesTree->setSortingEnabled(__sortingEnabled);

        plainTextEdit->setDocumentTitle(QString());
        tabs->setTabText(tabs->indexOf(notesTab), QCoreApplication::translate("MainWindow", "Notes", nullptr));
        title_1->setText(QCoreApplication::translate("MainWindow", "Incomplete tasks", nullptr));

        const bool __sortingEnabled1 = incompleteList->isSortingEnabled();
        incompleteList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = incompleteList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "gfdshgfdhfg", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = incompleteList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "dfhdjshgf ljhgds las dhjfk gsdhjlkf gajkhghjfgd gaklsdfghj gldasjfhgasd fasd gf", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = incompleteList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MainWindow", "dsgfglsdfgjksd", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = incompleteList->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("MainWindow", "sdgfsgserfm.gert", nullptr));
        incompleteList->setSortingEnabled(__sortingEnabled1);

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

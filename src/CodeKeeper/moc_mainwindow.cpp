/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[105];
    char stringdata0[1376];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "iconActivated"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(4, 60, 6), // "reason"
QT_MOC_LITERAL(5, 67, 17), // "getRepositoryData"
QT_MOC_LITERAL(6, 85, 7), // "git_url"
QT_MOC_LITERAL(7, 93, 13), // "QTableWidget*"
QT_MOC_LITERAL(8, 107, 5), // "table"
QT_MOC_LITERAL(9, 113, 7), // "QLabel*"
QT_MOC_LITERAL(10, 121, 5), // "label"
QT_MOC_LITERAL(11, 127, 16), // "getProjectIssues"
QT_MOC_LITERAL(12, 144, 18), // "openSettingsWindow"
QT_MOC_LITERAL(13, 163, 18), // "fOpenAccountWindow"
QT_MOC_LITERAL(14, 182, 14), // "openSyncWindow"
QT_MOC_LITERAL(15, 197, 10), // "openFolder"
QT_MOC_LITERAL(16, 208, 21), // "selectFileInQTreeView"
QT_MOC_LITERAL(17, 230, 10), // "QTreeView*"
QT_MOC_LITERAL(18, 241, 8), // "treeView"
QT_MOC_LITERAL(19, 250, 8), // "fileName"
QT_MOC_LITERAL(20, 259, 13), // "hideNotesList"
QT_MOC_LITERAL(21, 273, 9), // "setHeader"
QT_MOC_LITERAL(22, 283, 10), // "createNote"
QT_MOC_LITERAL(23, 294, 10), // "removeNote"
QT_MOC_LITERAL(24, 305, 8), // "saveNote"
QT_MOC_LITERAL(25, 314, 10), // "toViewMode"
QT_MOC_LITERAL(26, 325, 12), // "createFolder"
QT_MOC_LITERAL(27, 338, 10), // "renameItem"
QT_MOC_LITERAL(28, 349, 16), // "removeTaskFromDB"
QT_MOC_LITERAL(29, 366, 8), // "QString*"
QT_MOC_LITERAL(30, 375, 4), // "task"
QT_MOC_LITERAL(31, 380, 6), // "status"
QT_MOC_LITERAL(32, 387, 12), // "saveTaskToDB"
QT_MOC_LITERAL(33, 400, 10), // "addNewTask"
QT_MOC_LITERAL(34, 411, 10), // "removeTask"
QT_MOC_LITERAL(35, 422, 25), // "on_listWidget_itemClicked"
QT_MOC_LITERAL(36, 448, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(37, 465, 4), // "item"
QT_MOC_LITERAL(38, 470, 8), // "editTask"
QT_MOC_LITERAL(39, 479, 19), // "onNoteDoubleClicked"
QT_MOC_LITERAL(40, 499, 19), // "updateTasksProgress"
QT_MOC_LITERAL(41, 519, 11), // "QTabWidget*"
QT_MOC_LITERAL(42, 531, 8), // "tasksTab"
QT_MOC_LITERAL(43, 540, 12), // "QListWidget*"
QT_MOC_LITERAL(44, 553, 15), // "incompleteTasks"
QT_MOC_LITERAL(45, 569, 14), // "inprocessTasks"
QT_MOC_LITERAL(46, 584, 13), // "completeTasks"
QT_MOC_LITERAL(47, 598, 13), // "QProgressBar*"
QT_MOC_LITERAL(48, 612, 13), // "tasksProgress"
QT_MOC_LITERAL(49, 626, 13), // "getTotalTasks"
QT_MOC_LITERAL(50, 640, 16), // "getTotalProjects"
QT_MOC_LITERAL(51, 657, 18), // "notStartedProjects"
QT_MOC_LITERAL(52, 676, 15), // "startedProjects"
QT_MOC_LITERAL(53, 692, 16), // "finishedProjects"
QT_MOC_LITERAL(54, 709, 18), // "finishlineProjects"
QT_MOC_LITERAL(55, 728, 11), // "openProject"
QT_MOC_LITERAL(56, 740, 14), // "openGitProject"
QT_MOC_LITERAL(57, 755, 13), // "createProject"
QT_MOC_LITERAL(58, 769, 13), // "removeProject"
QT_MOC_LITERAL(59, 783, 5), // "setH1"
QT_MOC_LITERAL(60, 789, 5), // "setH2"
QT_MOC_LITERAL(61, 795, 5), // "setH3"
QT_MOC_LITERAL(62, 801, 7), // "setList"
QT_MOC_LITERAL(63, 809, 7), // "setLink"
QT_MOC_LITERAL(64, 817, 10), // "setNumList"
QT_MOC_LITERAL(65, 828, 7), // "setBold"
QT_MOC_LITERAL(66, 836, 9), // "setItalic"
QT_MOC_LITERAL(67, 846, 9), // "setStrike"
QT_MOC_LITERAL(68, 856, 7), // "setTask"
QT_MOC_LITERAL(69, 864, 8), // "setTable"
QT_MOC_LITERAL(70, 873, 8), // "setQuote"
QT_MOC_LITERAL(71, 882, 13), // "setSortByTime"
QT_MOC_LITERAL(72, 896, 13), // "setSortByName"
QT_MOC_LITERAL(73, 910, 17), // "updateWindowTitle"
QT_MOC_LITERAL(74, 928, 24), // "getCurrentDateTimeString"
QT_MOC_LITERAL(75, 953, 23), // "create_tasks_connection"
QT_MOC_LITERAL(76, 977, 26), // "create_projects_connection"
QT_MOC_LITERAL(77, 1004, 16), // "updateTaskStatus"
QT_MOC_LITERAL(78, 1021, 2), // "cT"
QT_MOC_LITERAL(79, 1024, 14), // "updateTaskData"
QT_MOC_LITERAL(80, 1039, 16), // "onMovingTaskFrom"
QT_MOC_LITERAL(81, 1056, 4), // "list"
QT_MOC_LITERAL(82, 1061, 14), // "onMovingTaskTo"
QT_MOC_LITERAL(83, 1076, 14), // "GetProjectData"
QT_MOC_LITERAL(84, 1091, 5), // "title"
QT_MOC_LITERAL(85, 1097, 19), // "updateProjectStatus"
QT_MOC_LITERAL(86, 1117, 11), // "createdTime"
QT_MOC_LITERAL(87, 1129, 7), // "oldTime"
QT_MOC_LITERAL(88, 1137, 19), // "removeProjectFromDB"
QT_MOC_LITERAL(89, 1157, 15), // "saveProjectToDB"
QT_MOC_LITERAL(90, 1173, 17), // "updateProjectData"
QT_MOC_LITERAL(91, 1191, 3), // "doc"
QT_MOC_LITERAL(92, 1195, 6), // "oldGit"
QT_MOC_LITERAL(93, 1202, 19), // "onMovingProjectFrom"
QT_MOC_LITERAL(94, 1222, 17), // "onMovingProjectTo"
QT_MOC_LITERAL(95, 1240, 15), // "checkConnection"
QT_MOC_LITERAL(96, 1256, 10), // "updateTime"
QT_MOC_LITERAL(97, 1267, 15), // "createNotesMenu"
QT_MOC_LITERAL(98, 1283, 6), // "QMenu*"
QT_MOC_LITERAL(99, 1290, 4), // "menu"
QT_MOC_LITERAL(100, 1295, 9), // "font_size"
QT_MOC_LITERAL(101, 1305, 17), // "createProjectMenu"
QT_MOC_LITERAL(102, 1323, 14), // "createTaskMenu"
QT_MOC_LITERAL(103, 1338, 14), // "createTrayMenu"
QT_MOC_LITERAL(104, 1353, 22) // "createNotesContextMenu"

    },
    "MainWindow\0iconActivated\0\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0getRepositoryData\0git_url\0"
    "QTableWidget*\0table\0QLabel*\0label\0"
    "getProjectIssues\0openSettingsWindow\0"
    "fOpenAccountWindow\0openSyncWindow\0"
    "openFolder\0selectFileInQTreeView\0"
    "QTreeView*\0treeView\0fileName\0hideNotesList\0"
    "setHeader\0createNote\0removeNote\0"
    "saveNote\0toViewMode\0createFolder\0"
    "renameItem\0removeTaskFromDB\0QString*\0"
    "task\0status\0saveTaskToDB\0addNewTask\0"
    "removeTask\0on_listWidget_itemClicked\0"
    "QListWidgetItem*\0item\0editTask\0"
    "onNoteDoubleClicked\0updateTasksProgress\0"
    "QTabWidget*\0tasksTab\0QListWidget*\0"
    "incompleteTasks\0inprocessTasks\0"
    "completeTasks\0QProgressBar*\0tasksProgress\0"
    "getTotalTasks\0getTotalProjects\0"
    "notStartedProjects\0startedProjects\0"
    "finishedProjects\0finishlineProjects\0"
    "openProject\0openGitProject\0createProject\0"
    "removeProject\0setH1\0setH2\0setH3\0setList\0"
    "setLink\0setNumList\0setBold\0setItalic\0"
    "setStrike\0setTask\0setTable\0setQuote\0"
    "setSortByTime\0setSortByName\0"
    "updateWindowTitle\0getCurrentDateTimeString\0"
    "create_tasks_connection\0"
    "create_projects_connection\0updateTaskStatus\0"
    "cT\0updateTaskData\0onMovingTaskFrom\0"
    "list\0onMovingTaskTo\0GetProjectData\0"
    "title\0updateProjectStatus\0createdTime\0"
    "oldTime\0removeProjectFromDB\0saveProjectToDB\0"
    "updateProjectData\0doc\0oldGit\0"
    "onMovingProjectFrom\0onMovingProjectTo\0"
    "checkConnection\0updateTime\0createNotesMenu\0"
    "QMenu*\0menu\0font_size\0createProjectMenu\0"
    "createTaskMenu\0createTrayMenu\0"
    "createNotesContextMenu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      66,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  344,    2, 0x08 /* Private */,
       5,    3,  347,    2, 0x08 /* Private */,
      11,    1,  354,    2, 0x08 /* Private */,
      12,    0,  357,    2, 0x08 /* Private */,
      13,    0,  358,    2, 0x08 /* Private */,
      14,    0,  359,    2, 0x08 /* Private */,
      15,    0,  360,    2, 0x08 /* Private */,
      16,    2,  361,    2, 0x08 /* Private */,
      20,    0,  366,    2, 0x08 /* Private */,
      21,    0,  367,    2, 0x08 /* Private */,
      22,    0,  368,    2, 0x08 /* Private */,
      23,    0,  369,    2, 0x08 /* Private */,
      24,    0,  370,    2, 0x08 /* Private */,
      25,    0,  371,    2, 0x08 /* Private */,
      26,    0,  372,    2, 0x08 /* Private */,
      27,    0,  373,    2, 0x08 /* Private */,
      28,    2,  374,    2, 0x08 /* Private */,
      32,    2,  379,    2, 0x08 /* Private */,
      33,    0,  384,    2, 0x08 /* Private */,
      34,    0,  385,    2, 0x08 /* Private */,
      35,    1,  386,    2, 0x08 /* Private */,
      38,    0,  389,    2, 0x08 /* Private */,
      39,    0,  390,    2, 0x08 /* Private */,
      40,    5,  391,    2, 0x08 /* Private */,
      49,    4,  402,    2, 0x08 /* Private */,
      50,    5,  411,    2, 0x08 /* Private */,
      55,    0,  422,    2, 0x08 /* Private */,
      56,    0,  423,    2, 0x08 /* Private */,
      57,    0,  424,    2, 0x08 /* Private */,
      58,    0,  425,    2, 0x08 /* Private */,
      59,    0,  426,    2, 0x08 /* Private */,
      60,    0,  427,    2, 0x08 /* Private */,
      61,    0,  428,    2, 0x08 /* Private */,
      62,    0,  429,    2, 0x08 /* Private */,
      63,    0,  430,    2, 0x08 /* Private */,
      64,    0,  431,    2, 0x08 /* Private */,
      65,    0,  432,    2, 0x08 /* Private */,
      66,    0,  433,    2, 0x08 /* Private */,
      67,    0,  434,    2, 0x08 /* Private */,
      68,    0,  435,    2, 0x08 /* Private */,
      69,    0,  436,    2, 0x08 /* Private */,
      70,    0,  437,    2, 0x08 /* Private */,
      71,    0,  438,    2, 0x08 /* Private */,
      72,    0,  439,    2, 0x08 /* Private */,
      73,    0,  440,    2, 0x08 /* Private */,
      74,    0,  441,    2, 0x08 /* Private */,
      75,    0,  442,    2, 0x08 /* Private */,
      76,    0,  443,    2, 0x08 /* Private */,
      77,    3,  444,    2, 0x08 /* Private */,
      79,    3,  451,    2, 0x08 /* Private */,
      80,    2,  458,    2, 0x08 /* Private */,
      82,    2,  463,    2, 0x08 /* Private */,
      83,    3,  468,    2, 0x08 /* Private */,
      85,    3,  475,    2, 0x08 /* Private */,
      88,    3,  482,    2, 0x08 /* Private */,
      89,    4,  489,    2, 0x08 /* Private */,
      90,    6,  498,    2, 0x08 /* Private */,
      93,    2,  511,    2, 0x08 /* Private */,
      94,    2,  516,    2, 0x08 /* Private */,
      95,    0,  521,    2, 0x08 /* Private */,
      96,    0,  522,    2, 0x08 /* Private */,
      97,    2,  523,    2, 0x08 /* Private */,
     101,    2,  528,    2, 0x08 /* Private */,
     102,    2,  533,    2, 0x08 /* Private */,
     103,    2,  538,    2, 0x08 /* Private */,
     104,    2,  543,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::QString, QMetaType::QString, 0x80000000 | 7, 0x80000000 | 9,    6,    8,   10,
    QMetaType::QString, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QString,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 29,   30,   31,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 29,   30,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 36,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 41, 0x80000000 | 43, 0x80000000 | 43, 0x80000000 | 43, 0x80000000 | 47,   42,   44,   45,   46,   48,
    QMetaType::Void, 0x80000000 | 41, 0x80000000 | 43, 0x80000000 | 43, 0x80000000 | 43,   42,   44,   45,   46,
    QMetaType::Void, 0x80000000 | 41, 0x80000000 | 43, 0x80000000 | 43, 0x80000000 | 43, 0x80000000 | 43,   42,   51,   52,   53,   54,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29,   30,   31,   78,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29,   30,   31,   78,
    QMetaType::Void, 0x80000000 | 36, 0x80000000 | 43,   37,   81,
    QMetaType::Void, 0x80000000 | 36, 0x80000000 | 43,   37,   81,
    QMetaType::QStringList, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29,   84,   31,    6,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29,   31,   86,   87,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29,    6,   31,   86,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29,   84,    6,   31,   86,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 29,   84,    6,   91,   86,   87,   92,
    QMetaType::Void, 0x80000000 | 36, 0x80000000 | 43,   37,   81,
    QMetaType::Void, 0x80000000 | 36, 0x80000000 | 43,   37,   81,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 98, QMetaType::QString,   99,  100,
    QMetaType::Void, 0x80000000 | 98, QMetaType::QString,   99,  100,
    QMetaType::Void, 0x80000000 | 98, QMetaType::QString,   99,  100,
    QMetaType::Void, 0x80000000 | 98, QMetaType::QString,   99,  100,
    QMetaType::Void, 0x80000000 | 98, QMetaType::QString,   99,  100,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 1: { QString _r = _t->getRepositoryData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QTableWidget*(*)>(_a[2])),(*reinterpret_cast< QLabel*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 2: { QString _r = _t->getProjectIssues((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->openSettingsWindow(); break;
        case 4: _t->fOpenAccountWindow(); break;
        case 5: _t->openSyncWindow(); break;
        case 6: _t->openFolder(); break;
        case 7: _t->selectFileInQTreeView((*reinterpret_cast< QTreeView*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->hideNotesList(); break;
        case 9: _t->setHeader(); break;
        case 10: _t->createNote(); break;
        case 11: _t->removeNote(); break;
        case 12: _t->saveNote(); break;
        case 13: _t->toViewMode(); break;
        case 14: _t->createFolder(); break;
        case 15: _t->renameItem(); break;
        case 16: _t->removeTaskFromDB((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2]))); break;
        case 17: _t->saveTaskToDB((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2]))); break;
        case 18: _t->addNewTask(); break;
        case 19: _t->removeTask(); break;
        case 20: _t->on_listWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 21: _t->editTask(); break;
        case 22: _t->onNoteDoubleClicked(); break;
        case 23: _t->updateTasksProgress((*reinterpret_cast< QTabWidget*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2])),(*reinterpret_cast< QListWidget*(*)>(_a[3])),(*reinterpret_cast< QListWidget*(*)>(_a[4])),(*reinterpret_cast< QProgressBar*(*)>(_a[5]))); break;
        case 24: _t->getTotalTasks((*reinterpret_cast< QTabWidget*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2])),(*reinterpret_cast< QListWidget*(*)>(_a[3])),(*reinterpret_cast< QListWidget*(*)>(_a[4]))); break;
        case 25: _t->getTotalProjects((*reinterpret_cast< QTabWidget*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2])),(*reinterpret_cast< QListWidget*(*)>(_a[3])),(*reinterpret_cast< QListWidget*(*)>(_a[4])),(*reinterpret_cast< QListWidget*(*)>(_a[5]))); break;
        case 26: _t->openProject(); break;
        case 27: _t->openGitProject(); break;
        case 28: _t->createProject(); break;
        case 29: _t->removeProject(); break;
        case 30: _t->setH1(); break;
        case 31: _t->setH2(); break;
        case 32: _t->setH3(); break;
        case 33: _t->setList(); break;
        case 34: _t->setLink(); break;
        case 35: _t->setNumList(); break;
        case 36: _t->setBold(); break;
        case 37: _t->setItalic(); break;
        case 38: _t->setStrike(); break;
        case 39: _t->setTask(); break;
        case 40: _t->setTable(); break;
        case 41: _t->setQuote(); break;
        case 42: _t->setSortByTime(); break;
        case 43: _t->setSortByName(); break;
        case 44: _t->updateWindowTitle(); break;
        case 45: { QString _r = _t->getCurrentDateTimeString();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 46: _t->create_tasks_connection(); break;
        case 47: _t->create_projects_connection(); break;
        case 48: _t->updateTaskStatus((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3]))); break;
        case 49: _t->updateTaskData((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3]))); break;
        case 50: _t->onMovingTaskFrom((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2]))); break;
        case 51: _t->onMovingTaskTo((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2]))); break;
        case 52: { QStringList _r = _t->GetProjectData((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 53: _t->updateProjectStatus((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3]))); break;
        case 54: _t->removeProjectFromDB((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3]))); break;
        case 55: _t->saveProjectToDB((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3])),(*reinterpret_cast< QString*(*)>(_a[4]))); break;
        case 56: _t->updateProjectData((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3])),(*reinterpret_cast< QString*(*)>(_a[4])),(*reinterpret_cast< QString*(*)>(_a[5])),(*reinterpret_cast< QString*(*)>(_a[6]))); break;
        case 57: _t->onMovingProjectFrom((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2]))); break;
        case 58: _t->onMovingProjectTo((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2]))); break;
        case 59: { bool _r = _t->checkConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 60: _t->updateTime(); break;
        case 61: _t->createNotesMenu((*reinterpret_cast< QMenu*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 62: _t->createProjectMenu((*reinterpret_cast< QMenu*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 63: _t->createTaskMenu((*reinterpret_cast< QMenu*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 64: _t->createTrayMenu((*reinterpret_cast< QMenu*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 65: _t->createNotesContextMenu((*reinterpret_cast< QMenu*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLabel* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTableWidget* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTreeView* >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            case 4:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QProgressBar* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTabWidget* >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTabWidget* >(); break;
            }
            break;
        case 25:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 4:
            case 3:
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTabWidget* >(); break;
            }
            break;
        case 50:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            }
            break;
        case 51:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            }
            break;
        case 57:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            }
            break;
        case 58:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            }
            break;
        case 61:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMenu* >(); break;
            }
            break;
        case 62:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMenu* >(); break;
            }
            break;
        case 63:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMenu* >(); break;
            }
            break;
        case 64:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMenu* >(); break;
            }
            break;
        case 65:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMenu* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 66)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 66;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 66)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 66;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

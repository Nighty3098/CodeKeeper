/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CodeKeeper/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[76];
    char stringdata0[987];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "openSettingsWindow"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "openFolder"
QT_MOC_LITERAL(4, 42, 13), // "hideNotesList"
QT_MOC_LITERAL(5, 56, 11), // "showPreview"
QT_MOC_LITERAL(6, 68, 15), // "updateMDPreview"
QT_MOC_LITERAL(7, 84, 9), // "setHeader"
QT_MOC_LITERAL(8, 94, 10), // "createNote"
QT_MOC_LITERAL(9, 105, 10), // "removeNote"
QT_MOC_LITERAL(10, 116, 8), // "saveNote"
QT_MOC_LITERAL(11, 125, 10), // "toViewMode"
QT_MOC_LITERAL(12, 136, 12), // "createFolder"
QT_MOC_LITERAL(13, 149, 9), // "loadTasks"
QT_MOC_LITERAL(14, 159, 16), // "removeTaskFromDB"
QT_MOC_LITERAL(15, 176, 8), // "QString*"
QT_MOC_LITERAL(16, 185, 4), // "task"
QT_MOC_LITERAL(17, 190, 6), // "status"
QT_MOC_LITERAL(18, 197, 12), // "saveTaskToDB"
QT_MOC_LITERAL(19, 210, 10), // "addNewTask"
QT_MOC_LITERAL(20, 221, 10), // "removeTask"
QT_MOC_LITERAL(21, 232, 25), // "on_listWidget_itemClicked"
QT_MOC_LITERAL(22, 258, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(23, 275, 4), // "item"
QT_MOC_LITERAL(24, 280, 23), // "renameItemOnDoubleClick"
QT_MOC_LITERAL(25, 304, 12), // "QListWidget*"
QT_MOC_LITERAL(26, 317, 10), // "listWidget"
QT_MOC_LITERAL(27, 328, 19), // "onNoteDoubleClicked"
QT_MOC_LITERAL(28, 348, 19), // "updateTasksProgress"
QT_MOC_LITERAL(29, 368, 11), // "QTabWidget*"
QT_MOC_LITERAL(30, 380, 8), // "tasksTab"
QT_MOC_LITERAL(31, 389, 15), // "incompleteTasks"
QT_MOC_LITERAL(32, 405, 14), // "inprocessTasks"
QT_MOC_LITERAL(33, 420, 13), // "completeTasks"
QT_MOC_LITERAL(34, 434, 13), // "QProgressBar*"
QT_MOC_LITERAL(35, 448, 13), // "tasksProgress"
QT_MOC_LITERAL(36, 462, 13), // "getTotalTasks"
QT_MOC_LITERAL(37, 476, 16), // "getTotalProjects"
QT_MOC_LITERAL(38, 493, 18), // "notStartedProjects"
QT_MOC_LITERAL(39, 512, 15), // "startedProjects"
QT_MOC_LITERAL(40, 528, 16), // "finishedProjects"
QT_MOC_LITERAL(41, 545, 18), // "finishlineProjects"
QT_MOC_LITERAL(42, 564, 18), // "loadDocumentations"
QT_MOC_LITERAL(43, 583, 4), // "QDir"
QT_MOC_LITERAL(44, 588, 4), // "path"
QT_MOC_LITERAL(45, 593, 10), // "QComboBox&"
QT_MOC_LITERAL(46, 604, 8), // "comboBox"
QT_MOC_LITERAL(47, 613, 11), // "openProject"
QT_MOC_LITERAL(48, 625, 13), // "createProject"
QT_MOC_LITERAL(49, 639, 15), // "saveProjectToDB"
QT_MOC_LITERAL(50, 655, 13), // "removeProject"
QT_MOC_LITERAL(51, 669, 12), // "loadProjects"
QT_MOC_LITERAL(52, 682, 5), // "setH1"
QT_MOC_LITERAL(53, 688, 5), // "setH2"
QT_MOC_LITERAL(54, 694, 5), // "setH3"
QT_MOC_LITERAL(55, 700, 7), // "setList"
QT_MOC_LITERAL(56, 708, 7), // "setLink"
QT_MOC_LITERAL(57, 716, 10), // "setNumList"
QT_MOC_LITERAL(58, 727, 7), // "setBold"
QT_MOC_LITERAL(59, 735, 9), // "setItalic"
QT_MOC_LITERAL(60, 745, 9), // "setStrike"
QT_MOC_LITERAL(61, 755, 7), // "setTask"
QT_MOC_LITERAL(62, 763, 8), // "setTable"
QT_MOC_LITERAL(63, 772, 17), // "updateWindowTitle"
QT_MOC_LITERAL(64, 790, 10), // "setFontPr1"
QT_MOC_LITERAL(65, 801, 24), // "getCurrentDateTimeString"
QT_MOC_LITERAL(66, 826, 23), // "create_tasks_connection"
QT_MOC_LITERAL(67, 850, 26), // "create_projects_connection"
QT_MOC_LITERAL(68, 877, 16), // "updateTaskStatus"
QT_MOC_LITERAL(69, 894, 2), // "cT"
QT_MOC_LITERAL(70, 897, 14), // "updateTaskData"
QT_MOC_LITERAL(71, 912, 16), // "onMovingTaskFrom"
QT_MOC_LITERAL(72, 929, 4), // "list"
QT_MOC_LITERAL(73, 934, 14), // "onMovingTaskTo"
QT_MOC_LITERAL(74, 949, 19), // "onMovingProjectFrom"
QT_MOC_LITERAL(75, 969, 17) // "onMovingProjectTo"

    },
    "MainWindow\0openSettingsWindow\0\0"
    "openFolder\0hideNotesList\0showPreview\0"
    "updateMDPreview\0setHeader\0createNote\0"
    "removeNote\0saveNote\0toViewMode\0"
    "createFolder\0loadTasks\0removeTaskFromDB\0"
    "QString*\0task\0status\0saveTaskToDB\0"
    "addNewTask\0removeTask\0on_listWidget_itemClicked\0"
    "QListWidgetItem*\0item\0renameItemOnDoubleClick\0"
    "QListWidget*\0listWidget\0onNoteDoubleClicked\0"
    "updateTasksProgress\0QTabWidget*\0"
    "tasksTab\0incompleteTasks\0inprocessTasks\0"
    "completeTasks\0QProgressBar*\0tasksProgress\0"
    "getTotalTasks\0getTotalProjects\0"
    "notStartedProjects\0startedProjects\0"
    "finishedProjects\0finishlineProjects\0"
    "loadDocumentations\0QDir\0path\0QComboBox&\0"
    "comboBox\0openProject\0createProject\0"
    "saveProjectToDB\0removeProject\0"
    "loadProjects\0setH1\0setH2\0setH3\0setList\0"
    "setLink\0setNumList\0setBold\0setItalic\0"
    "setStrike\0setTask\0setTable\0updateWindowTitle\0"
    "setFontPr1\0getCurrentDateTimeString\0"
    "create_tasks_connection\0"
    "create_projects_connection\0updateTaskStatus\0"
    "cT\0updateTaskData\0onMovingTaskFrom\0"
    "list\0onMovingTaskTo\0onMovingProjectFrom\0"
    "onMovingProjectTo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      50,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  264,    2, 0x08 /* Private */,
       3,    0,  265,    2, 0x08 /* Private */,
       4,    0,  266,    2, 0x08 /* Private */,
       5,    0,  267,    2, 0x08 /* Private */,
       6,    0,  268,    2, 0x08 /* Private */,
       7,    0,  269,    2, 0x08 /* Private */,
       8,    0,  270,    2, 0x08 /* Private */,
       9,    0,  271,    2, 0x08 /* Private */,
      10,    0,  272,    2, 0x08 /* Private */,
      11,    0,  273,    2, 0x08 /* Private */,
      12,    0,  274,    2, 0x08 /* Private */,
      13,    0,  275,    2, 0x08 /* Private */,
      14,    2,  276,    2, 0x08 /* Private */,
      18,    2,  281,    2, 0x08 /* Private */,
      19,    0,  286,    2, 0x08 /* Private */,
      20,    0,  287,    2, 0x08 /* Private */,
      21,    1,  288,    2, 0x08 /* Private */,
      24,    2,  291,    2, 0x08 /* Private */,
      27,    0,  296,    2, 0x08 /* Private */,
      28,    5,  297,    2, 0x08 /* Private */,
      36,    4,  308,    2, 0x08 /* Private */,
      37,    5,  317,    2, 0x08 /* Private */,
      42,    2,  328,    2, 0x08 /* Private */,
      47,    2,  333,    2, 0x08 /* Private */,
      48,    0,  338,    2, 0x08 /* Private */,
      49,    0,  339,    2, 0x08 /* Private */,
      50,    0,  340,    2, 0x08 /* Private */,
      51,    0,  341,    2, 0x08 /* Private */,
      52,    0,  342,    2, 0x08 /* Private */,
      53,    0,  343,    2, 0x08 /* Private */,
      54,    0,  344,    2, 0x08 /* Private */,
      55,    0,  345,    2, 0x08 /* Private */,
      56,    0,  346,    2, 0x08 /* Private */,
      57,    0,  347,    2, 0x08 /* Private */,
      58,    0,  348,    2, 0x08 /* Private */,
      59,    0,  349,    2, 0x08 /* Private */,
      60,    0,  350,    2, 0x08 /* Private */,
      61,    0,  351,    2, 0x08 /* Private */,
      62,    0,  352,    2, 0x08 /* Private */,
      63,    0,  353,    2, 0x08 /* Private */,
      64,    0,  354,    2, 0x08 /* Private */,
      65,    0,  355,    2, 0x08 /* Private */,
      66,    0,  356,    2, 0x08 /* Private */,
      67,    0,  357,    2, 0x08 /* Private */,
      68,    3,  358,    2, 0x08 /* Private */,
      70,    3,  365,    2, 0x08 /* Private */,
      71,    2,  372,    2, 0x08 /* Private */,
      73,    2,  377,    2, 0x08 /* Private */,
      74,    2,  382,    2, 0x08 /* Private */,
      75,    2,  387,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15,   16,   17,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15,   16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 25, 0x80000000 | 22,   26,   23,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 25, 0x80000000 | 25, 0x80000000 | 25, 0x80000000 | 34,   30,   31,   32,   33,   35,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 25, 0x80000000 | 25, 0x80000000 | 25,   30,   31,   32,   33,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 25, 0x80000000 | 25, 0x80000000 | 25, 0x80000000 | 25,   30,   38,   39,   40,   41,
    QMetaType::Void, 0x80000000 | 43, 0x80000000 | 45,   44,   46,
    QMetaType::Void, 0x80000000 | 25, 0x80000000 | 22,   26,   23,
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
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15, 0x80000000 | 15,   16,   17,   69,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15, 0x80000000 | 15,   16,   17,   69,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 25,   23,   72,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 25,   23,   72,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 25,   23,   72,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 25,   23,   72,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openSettingsWindow(); break;
        case 1: _t->openFolder(); break;
        case 2: _t->hideNotesList(); break;
        case 3: _t->showPreview(); break;
        case 4: _t->updateMDPreview(); break;
        case 5: _t->setHeader(); break;
        case 6: _t->createNote(); break;
        case 7: _t->removeNote(); break;
        case 8: _t->saveNote(); break;
        case 9: _t->toViewMode(); break;
        case 10: _t->createFolder(); break;
        case 11: _t->loadTasks(); break;
        case 12: _t->removeTaskFromDB((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2]))); break;
        case 13: _t->saveTaskToDB((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2]))); break;
        case 14: _t->addNewTask(); break;
        case 15: _t->removeTask(); break;
        case 16: _t->on_listWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 17: _t->renameItemOnDoubleClick((*reinterpret_cast< QListWidget*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 18: _t->onNoteDoubleClicked(); break;
        case 19: _t->updateTasksProgress((*reinterpret_cast< QTabWidget*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2])),(*reinterpret_cast< QListWidget*(*)>(_a[3])),(*reinterpret_cast< QListWidget*(*)>(_a[4])),(*reinterpret_cast< QProgressBar*(*)>(_a[5]))); break;
        case 20: _t->getTotalTasks((*reinterpret_cast< QTabWidget*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2])),(*reinterpret_cast< QListWidget*(*)>(_a[3])),(*reinterpret_cast< QListWidget*(*)>(_a[4]))); break;
        case 21: _t->getTotalProjects((*reinterpret_cast< QTabWidget*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2])),(*reinterpret_cast< QListWidget*(*)>(_a[3])),(*reinterpret_cast< QListWidget*(*)>(_a[4])),(*reinterpret_cast< QListWidget*(*)>(_a[5]))); break;
        case 22: _t->loadDocumentations((*reinterpret_cast< QDir(*)>(_a[1])),(*reinterpret_cast< QComboBox(*)>(_a[2]))); break;
        case 23: _t->openProject((*reinterpret_cast< QListWidget*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 24: _t->createProject(); break;
        case 25: _t->saveProjectToDB(); break;
        case 26: _t->removeProject(); break;
        case 27: _t->loadProjects(); break;
        case 28: _t->setH1(); break;
        case 29: _t->setH2(); break;
        case 30: _t->setH3(); break;
        case 31: _t->setList(); break;
        case 32: _t->setLink(); break;
        case 33: _t->setNumList(); break;
        case 34: _t->setBold(); break;
        case 35: _t->setItalic(); break;
        case 36: _t->setStrike(); break;
        case 37: _t->setTask(); break;
        case 38: _t->setTable(); break;
        case 39: _t->updateWindowTitle(); break;
        case 40: _t->setFontPr1(); break;
        case 41: { QString _r = _t->getCurrentDateTimeString();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 42: _t->create_tasks_connection(); break;
        case 43: _t->create_projects_connection(); break;
        case 44: _t->updateTaskStatus((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3]))); break;
        case 45: _t->updateTaskData((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3]))); break;
        case 46: _t->onMovingTaskFrom((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2]))); break;
        case 47: _t->onMovingTaskTo((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2]))); break;
        case 48: _t->onMovingProjectFrom((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2]))); break;
        case 49: _t->onMovingProjectTo((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidget*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            }
            break;
        case 19:
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
        case 20:
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
        case 21:
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
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            }
            break;
        case 46:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            }
            break;
        case 47:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            }
            break;
        case 48:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
            }
            break;
        case 49:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListWidget* >(); break;
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
        if (_id < 50)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 50;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 50)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 50;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

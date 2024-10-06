/****************************************************************************
** Meta object code from reading C++ file 'accountwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "accountwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'accountwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AccountWindow_t {
    QByteArrayData data[28];
    char stringdata0[352];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AccountWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AccountWindow_t qt_meta_stringdata_AccountWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "AccountWindow"
QT_MOC_LITERAL(1, 14, 11), // "setUserData"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "username"
QT_MOC_LITERAL(4, 36, 7), // "QLabel*"
QT_MOC_LITERAL(5, 44, 5), // "label"
QT_MOC_LITERAL(6, 50, 15), // "closeWindowSlot"
QT_MOC_LITERAL(7, 66, 15), // "getSettingsData"
QT_MOC_LITERAL(8, 82, 15), // "setImageFromUrl"
QT_MOC_LITERAL(9, 98, 3), // "url"
QT_MOC_LITERAL(10, 102, 17), // "onOpenRepoClicked"
QT_MOC_LITERAL(11, 120, 13), // "getStarsCount"
QT_MOC_LITERAL(12, 134, 5), // "token"
QT_MOC_LITERAL(13, 140, 16), // "setTasksProgress"
QT_MOC_LITERAL(14, 157, 16), // "setProjectsStats"
QT_MOC_LITERAL(15, 174, 13), // "setLangsStats"
QT_MOC_LITERAL(16, 188, 9), // "langsData"
QT_MOC_LITERAL(17, 198, 12), // "CircleChart*"
QT_MOC_LITERAL(18, 211, 10), // "langsChart"
QT_MOC_LITERAL(19, 222, 18), // "ColorValueDisplay*"
QT_MOC_LITERAL(20, 241, 18), // "langsValuesDisplay"
QT_MOC_LITERAL(21, 260, 13), // "get_image_url"
QT_MOC_LITERAL(22, 274, 18), // "getAllGitReposUrls"
QT_MOC_LITERAL(23, 293, 13), // "getLangByRepo"
QT_MOC_LITERAL(24, 307, 12), // "repositories"
QT_MOC_LITERAL(25, 320, 19), // "calculatePercentage"
QT_MOC_LITERAL(26, 340, 5), // "count"
QT_MOC_LITERAL(27, 346, 5) // "total"

    },
    "AccountWindow\0setUserData\0\0username\0"
    "QLabel*\0label\0closeWindowSlot\0"
    "getSettingsData\0setImageFromUrl\0url\0"
    "onOpenRepoClicked\0getStarsCount\0token\0"
    "setTasksProgress\0setProjectsStats\0"
    "setLangsStats\0langsData\0CircleChart*\0"
    "langsChart\0ColorValueDisplay*\0"
    "langsValuesDisplay\0get_image_url\0"
    "getAllGitReposUrls\0getLangByRepo\0"
    "repositories\0calculatePercentage\0count\0"
    "total"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AccountWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x08 /* Private */,
       6,    0,   84,    2, 0x08 /* Private */,
       7,    0,   85,    2, 0x08 /* Private */,
       8,    2,   86,    2, 0x08 /* Private */,
      10,    0,   91,    2, 0x08 /* Private */,
      11,    2,   92,    2, 0x08 /* Private */,
      13,    0,   97,    2, 0x08 /* Private */,
      14,    0,   98,    2, 0x08 /* Private */,
      15,    3,   99,    2, 0x08 /* Private */,
      21,    2,  106,    2, 0x08 /* Private */,
      22,    1,  111,    2, 0x08 /* Private */,
      23,    1,  114,    2, 0x08 /* Private */,
      25,    2,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    9,    5,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,    3,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 17, 0x80000000 | 19,   16,   18,   20,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::QStringList, QMetaType::QString,    3,
    QMetaType::QString, QMetaType::QStringList,   24,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   26,   27,

       0        // eod
};

void AccountWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AccountWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setUserData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QLabel*(*)>(_a[2]))); break;
        case 1: _t->closeWindowSlot(); break;
        case 2: _t->getSettingsData(); break;
        case 3: _t->setImageFromUrl((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QLabel*(*)>(_a[2]))); break;
        case 4: _t->onOpenRepoClicked(); break;
        case 5: { int _r = _t->getStarsCount((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->setTasksProgress(); break;
        case 7: _t->setProjectsStats(); break;
        case 8: _t->setLangsStats((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< CircleChart*(*)>(_a[2])),(*reinterpret_cast< ColorValueDisplay*(*)>(_a[3]))); break;
        case 9: _t->get_image_url((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QLabel*(*)>(_a[2]))); break;
        case 10: { QStringList _r = _t->getAllGitReposUrls((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->getLangByRepo((*reinterpret_cast< const QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { float _r = _t->calculatePercentage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLabel* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLabel* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CircleChart* >(); break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ColorValueDisplay* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLabel* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AccountWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_AccountWindow.data,
    qt_meta_data_AccountWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AccountWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AccountWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AccountWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int AccountWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

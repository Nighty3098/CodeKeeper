/****************************************************************************
** Meta object code from reading C++ file 'qmarkdowntextedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CodeKeeper/qmarkdowntextedit/qmarkdowntextedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmarkdowntextedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMarkdownTextEdit_t {
    QByteArrayData data[22];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QMarkdownTextEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QMarkdownTextEdit_t qt_meta_stringdata_QMarkdownTextEdit = {
    {
QT_MOC_LITERAL(0, 0, 17), // "QMarkdownTextEdit"
QT_MOC_LITERAL(1, 18, 10), // "urlClicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "url"
QT_MOC_LITERAL(4, 34, 6), // "zoomIn"
QT_MOC_LITERAL(5, 41, 7), // "zoomOut"
QT_MOC_LITERAL(6, 49, 13), // "duplicateText"
QT_MOC_LITERAL(7, 63, 7), // "setText"
QT_MOC_LITERAL(8, 71, 4), // "text"
QT_MOC_LITERAL(9, 76, 12), // "setPlainText"
QT_MOC_LITERAL(10, 89, 17), // "adjustRightMargin"
QT_MOC_LITERAL(11, 107, 4), // "hide"
QT_MOC_LITERAL(12, 112, 24), // "openLinkAtCursorPosition"
QT_MOC_LITERAL(13, 137, 22), // "handleBackspaceEntered"
QT_MOC_LITERAL(14, 160, 15), // "centerTheCursor"
QT_MOC_LITERAL(15, 176, 4), // "undo"
QT_MOC_LITERAL(16, 181, 14), // "moveTextUpDown"
QT_MOC_LITERAL(17, 196, 2), // "up"
QT_MOC_LITERAL(18, 199, 20), // "setLineNumberEnabled"
QT_MOC_LITERAL(19, 220, 7), // "enabled"
QT_MOC_LITERAL(20, 228, 25), // "updateLineNumberAreaWidth"
QT_MOC_LITERAL(21, 254, 12) // "highlighting"

    },
    "QMarkdownTextEdit\0urlClicked\0\0url\0"
    "zoomIn\0zoomOut\0duplicateText\0setText\0"
    "text\0setPlainText\0adjustRightMargin\0"
    "hide\0openLinkAtCursorPosition\0"
    "handleBackspaceEntered\0centerTheCursor\0"
    "undo\0moveTextUpDown\0up\0setLineNumberEnabled\0"
    "enabled\0updateLineNumberAreaWidth\0"
    "highlighting"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMarkdownTextEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       1,  116, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    0,   92,    2, 0x06 /* Public */,
       5,    0,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   94,    2, 0x0a /* Public */,
       7,    1,   95,    2, 0x0a /* Public */,
       9,    1,   98,    2, 0x0a /* Public */,
      10,    0,  101,    2, 0x0a /* Public */,
      11,    0,  102,    2, 0x0a /* Public */,
      12,    0,  103,    2, 0x0a /* Public */,
      13,    0,  104,    2, 0x0a /* Public */,
      14,    0,  105,    2, 0x0a /* Public */,
      15,    0,  106,    2, 0x0a /* Public */,
      16,    1,  107,    2, 0x0a /* Public */,
      18,    1,  110,    2, 0x0a /* Public */,
      20,    1,  113,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Int,    2,

 // properties: name, type, flags
      21, QMetaType::Bool, 0x00095003,

       0        // eod
};

void QMarkdownTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QMarkdownTextEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->urlClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->zoomIn(); break;
        case 2: _t->zoomOut(); break;
        case 3: _t->duplicateText(); break;
        case 4: _t->setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setPlainText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->adjustRightMargin(); break;
        case 7: _t->hide(); break;
        case 8: { bool _r = _t->openLinkAtCursorPosition();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->handleBackspaceEntered();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->centerTheCursor(); break;
        case 11: _t->undo(); break;
        case 12: _t->moveTextUpDown((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->setLineNumberEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->updateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QMarkdownTextEdit::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMarkdownTextEdit::urlClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QMarkdownTextEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMarkdownTextEdit::zoomIn)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QMarkdownTextEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMarkdownTextEdit::zoomOut)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QMarkdownTextEdit *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->highlightingEnabled(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QMarkdownTextEdit *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setHighlightingEnabled(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject QMarkdownTextEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QPlainTextEdit::staticMetaObject>(),
    qt_meta_stringdata_QMarkdownTextEdit.data,
    qt_meta_data_QMarkdownTextEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QMarkdownTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMarkdownTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QMarkdownTextEdit.stringdata0))
        return static_cast<void*>(this);
    return QPlainTextEdit::qt_metacast(_clname);
}

int QMarkdownTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QMarkdownTextEdit::urlClicked(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QMarkdownTextEdit::zoomIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QMarkdownTextEdit::zoomOut()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

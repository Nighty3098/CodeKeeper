/****************************************************************************
** Meta object code from reading C++ file 'markdownhighlighter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../CodeKeeper/qmarkdowntextedit/markdownhighlighter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'markdownhighlighter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MarkdownHighlighter_t {
    QByteArrayData data[85];
    char stringdata0[978];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MarkdownHighlighter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MarkdownHighlighter_t qt_meta_stringdata_MarkdownHighlighter = {
    {
QT_MOC_LITERAL(0, 0, 19), // "MarkdownHighlighter"
QT_MOC_LITERAL(1, 20, 20), // "highlightingFinished"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 9), // "timerTick"
QT_MOC_LITERAL(4, 52, 16), // "HighlighterState"
QT_MOC_LITERAL(5, 69, 7), // "NoState"
QT_MOC_LITERAL(6, 77, 4), // "Link"
QT_MOC_LITERAL(7, 82, 5), // "Image"
QT_MOC_LITERAL(8, 88, 9), // "CodeBlock"
QT_MOC_LITERAL(9, 98, 16), // "CodeBlockComment"
QT_MOC_LITERAL(10, 115, 6), // "Italic"
QT_MOC_LITERAL(11, 122, 4), // "Bold"
QT_MOC_LITERAL(12, 127, 4), // "List"
QT_MOC_LITERAL(13, 132, 7), // "Comment"
QT_MOC_LITERAL(14, 140, 2), // "H1"
QT_MOC_LITERAL(15, 143, 2), // "H2"
QT_MOC_LITERAL(16, 146, 2), // "H3"
QT_MOC_LITERAL(17, 149, 2), // "H4"
QT_MOC_LITERAL(18, 152, 2), // "H5"
QT_MOC_LITERAL(19, 155, 2), // "H6"
QT_MOC_LITERAL(20, 158, 10), // "BlockQuote"
QT_MOC_LITERAL(21, 169, 15), // "HorizontalRuler"
QT_MOC_LITERAL(22, 185, 5), // "Table"
QT_MOC_LITERAL(23, 191, 15), // "InlineCodeBlock"
QT_MOC_LITERAL(24, 207, 12), // "MaskedSyntax"
QT_MOC_LITERAL(25, 220, 26), // "CurrentLineBackgroundColor"
QT_MOC_LITERAL(26, 247, 10), // "BrokenLink"
QT_MOC_LITERAL(27, 258, 16), // "FrontmatterBlock"
QT_MOC_LITERAL(28, 275, 13), // "TrailingSpace"
QT_MOC_LITERAL(29, 289, 17), // "CheckBoxUnChecked"
QT_MOC_LITERAL(30, 307, 15), // "CheckBoxChecked"
QT_MOC_LITERAL(31, 323, 11), // "StUnderline"
QT_MOC_LITERAL(32, 335, 11), // "CodeKeyWord"
QT_MOC_LITERAL(33, 347, 10), // "CodeString"
QT_MOC_LITERAL(34, 358, 11), // "CodeComment"
QT_MOC_LITERAL(35, 370, 8), // "CodeType"
QT_MOC_LITERAL(36, 379, 9), // "CodeOther"
QT_MOC_LITERAL(37, 389, 14), // "CodeNumLiteral"
QT_MOC_LITERAL(38, 404, 11), // "CodeBuiltIn"
QT_MOC_LITERAL(39, 416, 17), // "CodeBlockIndented"
QT_MOC_LITERAL(40, 434, 17), // "CodeBlockTildeEnd"
QT_MOC_LITERAL(41, 452, 14), // "CodeBlockTilde"
QT_MOC_LITERAL(42, 467, 21), // "CodeBlockTildeComment"
QT_MOC_LITERAL(43, 489, 12), // "CodeBlockEnd"
QT_MOC_LITERAL(44, 502, 11), // "HeadlineEnd"
QT_MOC_LITERAL(45, 514, 19), // "FrontmatterBlockEnd"
QT_MOC_LITERAL(46, 534, 7), // "CodeCpp"
QT_MOC_LITERAL(47, 542, 14), // "CodeCppComment"
QT_MOC_LITERAL(48, 557, 6), // "CodeJs"
QT_MOC_LITERAL(49, 564, 13), // "CodeJsComment"
QT_MOC_LITERAL(50, 578, 5), // "CodeC"
QT_MOC_LITERAL(51, 584, 12), // "CodeCComment"
QT_MOC_LITERAL(52, 597, 8), // "CodeBash"
QT_MOC_LITERAL(53, 606, 7), // "CodePHP"
QT_MOC_LITERAL(54, 614, 14), // "CodePHPComment"
QT_MOC_LITERAL(55, 629, 7), // "CodeQML"
QT_MOC_LITERAL(56, 637, 14), // "CodeQMLComment"
QT_MOC_LITERAL(57, 652, 10), // "CodePython"
QT_MOC_LITERAL(58, 663, 8), // "CodeRust"
QT_MOC_LITERAL(59, 672, 15), // "CodeRustComment"
QT_MOC_LITERAL(60, 688, 8), // "CodeJava"
QT_MOC_LITERAL(61, 697, 15), // "CodeJavaComment"
QT_MOC_LITERAL(62, 713, 10), // "CodeCSharp"
QT_MOC_LITERAL(63, 724, 17), // "CodeCSharpComment"
QT_MOC_LITERAL(64, 742, 6), // "CodeGo"
QT_MOC_LITERAL(65, 749, 13), // "CodeGoComment"
QT_MOC_LITERAL(66, 763, 5), // "CodeV"
QT_MOC_LITERAL(67, 769, 12), // "CodeVComment"
QT_MOC_LITERAL(68, 782, 7), // "CodeSQL"
QT_MOC_LITERAL(69, 790, 8), // "CodeJSON"
QT_MOC_LITERAL(70, 799, 7), // "CodeXML"
QT_MOC_LITERAL(71, 807, 7), // "CodeCSS"
QT_MOC_LITERAL(72, 815, 14), // "CodeCSSComment"
QT_MOC_LITERAL(73, 830, 14), // "CodeTypeScript"
QT_MOC_LITERAL(74, 845, 21), // "CodeTypeScriptComment"
QT_MOC_LITERAL(75, 867, 8), // "CodeYAML"
QT_MOC_LITERAL(76, 876, 7), // "CodeINI"
QT_MOC_LITERAL(77, 884, 16), // "CodeTaggerScript"
QT_MOC_LITERAL(78, 901, 7), // "CodeVex"
QT_MOC_LITERAL(79, 909, 14), // "CodeVexComment"
QT_MOC_LITERAL(80, 924, 9), // "CodeCMake"
QT_MOC_LITERAL(81, 934, 8), // "CodeMake"
QT_MOC_LITERAL(82, 943, 7), // "CodeNix"
QT_MOC_LITERAL(83, 951, 9), // "CodeForth"
QT_MOC_LITERAL(84, 961, 16) // "CodeForthComment"

    },
    "MarkdownHighlighter\0highlightingFinished\0"
    "\0timerTick\0HighlighterState\0NoState\0"
    "Link\0Image\0CodeBlock\0CodeBlockComment\0"
    "Italic\0Bold\0List\0Comment\0H1\0H2\0H3\0H4\0"
    "H5\0H6\0BlockQuote\0HorizontalRuler\0Table\0"
    "InlineCodeBlock\0MaskedSyntax\0"
    "CurrentLineBackgroundColor\0BrokenLink\0"
    "FrontmatterBlock\0TrailingSpace\0"
    "CheckBoxUnChecked\0CheckBoxChecked\0"
    "StUnderline\0CodeKeyWord\0CodeString\0"
    "CodeComment\0CodeType\0CodeOther\0"
    "CodeNumLiteral\0CodeBuiltIn\0CodeBlockIndented\0"
    "CodeBlockTildeEnd\0CodeBlockTilde\0"
    "CodeBlockTildeComment\0CodeBlockEnd\0"
    "HeadlineEnd\0FrontmatterBlockEnd\0CodeCpp\0"
    "CodeCppComment\0CodeJs\0CodeJsComment\0"
    "CodeC\0CodeCComment\0CodeBash\0CodePHP\0"
    "CodePHPComment\0CodeQML\0CodeQMLComment\0"
    "CodePython\0CodeRust\0CodeRustComment\0"
    "CodeJava\0CodeJavaComment\0CodeCSharp\0"
    "CodeCSharpComment\0CodeGo\0CodeGoComment\0"
    "CodeV\0CodeVComment\0CodeSQL\0CodeJSON\0"
    "CodeXML\0CodeCSS\0CodeCSSComment\0"
    "CodeTypeScript\0CodeTypeScriptComment\0"
    "CodeYAML\0CodeINI\0CodeTaggerScript\0"
    "CodeVex\0CodeVexComment\0CodeCMake\0"
    "CodeMake\0CodeNix\0CodeForth\0CodeForthComment"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MarkdownHighlighter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       1,   26, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

 // enums: name, alias, flags, count, data
       4,    4, 0x0,   80,   31,

 // enum data: key, value
       5, uint(MarkdownHighlighter::NoState),
       6, uint(MarkdownHighlighter::Link),
       7, uint(MarkdownHighlighter::Image),
       8, uint(MarkdownHighlighter::CodeBlock),
       9, uint(MarkdownHighlighter::CodeBlockComment),
      10, uint(MarkdownHighlighter::Italic),
      11, uint(MarkdownHighlighter::Bold),
      12, uint(MarkdownHighlighter::List),
      13, uint(MarkdownHighlighter::Comment),
      14, uint(MarkdownHighlighter::H1),
      15, uint(MarkdownHighlighter::H2),
      16, uint(MarkdownHighlighter::H3),
      17, uint(MarkdownHighlighter::H4),
      18, uint(MarkdownHighlighter::H5),
      19, uint(MarkdownHighlighter::H6),
      20, uint(MarkdownHighlighter::BlockQuote),
      21, uint(MarkdownHighlighter::HorizontalRuler),
      22, uint(MarkdownHighlighter::Table),
      23, uint(MarkdownHighlighter::InlineCodeBlock),
      24, uint(MarkdownHighlighter::MaskedSyntax),
      25, uint(MarkdownHighlighter::CurrentLineBackgroundColor),
      26, uint(MarkdownHighlighter::BrokenLink),
      27, uint(MarkdownHighlighter::FrontmatterBlock),
      28, uint(MarkdownHighlighter::TrailingSpace),
      29, uint(MarkdownHighlighter::CheckBoxUnChecked),
      30, uint(MarkdownHighlighter::CheckBoxChecked),
      31, uint(MarkdownHighlighter::StUnderline),
      32, uint(MarkdownHighlighter::CodeKeyWord),
      33, uint(MarkdownHighlighter::CodeString),
      34, uint(MarkdownHighlighter::CodeComment),
      35, uint(MarkdownHighlighter::CodeType),
      36, uint(MarkdownHighlighter::CodeOther),
      37, uint(MarkdownHighlighter::CodeNumLiteral),
      38, uint(MarkdownHighlighter::CodeBuiltIn),
      39, uint(MarkdownHighlighter::CodeBlockIndented),
      40, uint(MarkdownHighlighter::CodeBlockTildeEnd),
      41, uint(MarkdownHighlighter::CodeBlockTilde),
      42, uint(MarkdownHighlighter::CodeBlockTildeComment),
      43, uint(MarkdownHighlighter::CodeBlockEnd),
      44, uint(MarkdownHighlighter::HeadlineEnd),
      45, uint(MarkdownHighlighter::FrontmatterBlockEnd),
      46, uint(MarkdownHighlighter::CodeCpp),
      47, uint(MarkdownHighlighter::CodeCppComment),
      48, uint(MarkdownHighlighter::CodeJs),
      49, uint(MarkdownHighlighter::CodeJsComment),
      50, uint(MarkdownHighlighter::CodeC),
      51, uint(MarkdownHighlighter::CodeCComment),
      52, uint(MarkdownHighlighter::CodeBash),
      53, uint(MarkdownHighlighter::CodePHP),
      54, uint(MarkdownHighlighter::CodePHPComment),
      55, uint(MarkdownHighlighter::CodeQML),
      56, uint(MarkdownHighlighter::CodeQMLComment),
      57, uint(MarkdownHighlighter::CodePython),
      58, uint(MarkdownHighlighter::CodeRust),
      59, uint(MarkdownHighlighter::CodeRustComment),
      60, uint(MarkdownHighlighter::CodeJava),
      61, uint(MarkdownHighlighter::CodeJavaComment),
      62, uint(MarkdownHighlighter::CodeCSharp),
      63, uint(MarkdownHighlighter::CodeCSharpComment),
      64, uint(MarkdownHighlighter::CodeGo),
      65, uint(MarkdownHighlighter::CodeGoComment),
      66, uint(MarkdownHighlighter::CodeV),
      67, uint(MarkdownHighlighter::CodeVComment),
      68, uint(MarkdownHighlighter::CodeSQL),
      69, uint(MarkdownHighlighter::CodeJSON),
      70, uint(MarkdownHighlighter::CodeXML),
      71, uint(MarkdownHighlighter::CodeCSS),
      72, uint(MarkdownHighlighter::CodeCSSComment),
      73, uint(MarkdownHighlighter::CodeTypeScript),
      74, uint(MarkdownHighlighter::CodeTypeScriptComment),
      75, uint(MarkdownHighlighter::CodeYAML),
      76, uint(MarkdownHighlighter::CodeINI),
      77, uint(MarkdownHighlighter::CodeTaggerScript),
      78, uint(MarkdownHighlighter::CodeVex),
      79, uint(MarkdownHighlighter::CodeVexComment),
      80, uint(MarkdownHighlighter::CodeCMake),
      81, uint(MarkdownHighlighter::CodeMake),
      82, uint(MarkdownHighlighter::CodeNix),
      83, uint(MarkdownHighlighter::CodeForth),
      84, uint(MarkdownHighlighter::CodeForthComment),

       0        // eod
};

void MarkdownHighlighter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MarkdownHighlighter *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->highlightingFinished(); break;
        case 1: _t->timerTick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MarkdownHighlighter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MarkdownHighlighter::highlightingFinished)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject MarkdownHighlighter::staticMetaObject = { {
    QMetaObject::SuperData::link<QSyntaxHighlighter::staticMetaObject>(),
    qt_meta_stringdata_MarkdownHighlighter.data,
    qt_meta_data_MarkdownHighlighter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MarkdownHighlighter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MarkdownHighlighter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MarkdownHighlighter.stringdata0))
        return static_cast<void*>(this);
    return QSyntaxHighlighter::qt_metacast(_clname);
}

int MarkdownHighlighter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSyntaxHighlighter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MarkdownHighlighter::highlightingFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

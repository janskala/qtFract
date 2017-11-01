/****************************************************************************
** Meta object code from reading C++ file 'fractGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fractGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fractGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FractGUI_t {
    QByteArrayData data[20];
    char stringdata[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FractGUI_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FractGUI_t qt_meta_stringdata_FractGUI = {
    {
QT_MOC_LITERAL(0, 0, 8), // "FractGUI"
QT_MOC_LITERAL(1, 9, 10), // "selectZoom"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 9), // "resetZoom"
QT_MOC_LITERAL(4, 31, 7), // "setZoom"
QT_MOC_LITERAL(5, 39, 15), // "showChangeResol"
QT_MOC_LITERAL(6, 55, 12), // "showEquation"
QT_MOC_LITERAL(7, 68, 13), // "showPrecision"
QT_MOC_LITERAL(8, 82, 10), // "showColors"
QT_MOC_LITERAL(9, 93, 11), // "showControl"
QT_MOC_LITERAL(10, 105, 9), // "showVideo"
QT_MOC_LITERAL(11, 115, 9), // "makeVideo"
QT_MOC_LITERAL(12, 125, 9), // "showAbout"
QT_MOC_LITERAL(13, 135, 10), // "keepAspRat"
QT_MOC_LITERAL(14, 146, 10), // "saveToFile"
QT_MOC_LITERAL(15, 157, 12), // "loadFromFile"
QT_MOC_LITERAL(16, 170, 11), // "saveVToFile"
QT_MOC_LITERAL(17, 182, 13), // "loadVFromFile"
QT_MOC_LITERAL(18, 196, 9), // "saveImage"
QT_MOC_LITERAL(19, 206, 9) // "showAngle"

    },
    "FractGUI\0selectZoom\0\0resetZoom\0setZoom\0"
    "showChangeResol\0showEquation\0showPrecision\0"
    "showColors\0showControl\0showVideo\0"
    "makeVideo\0showAbout\0keepAspRat\0"
    "saveToFile\0loadFromFile\0saveVToFile\0"
    "loadVFromFile\0saveImage\0showAngle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FractGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08 /* Private */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    1,  106,    2, 0x08 /* Private */,
       5,    0,  109,    2, 0x08 /* Private */,
       6,    0,  110,    2, 0x08 /* Private */,
       7,    0,  111,    2, 0x08 /* Private */,
       8,    0,  112,    2, 0x08 /* Private */,
       9,    0,  113,    2, 0x08 /* Private */,
      10,    0,  114,    2, 0x08 /* Private */,
      11,    0,  115,    2, 0x08 /* Private */,
      12,    0,  116,    2, 0x08 /* Private */,
      13,    0,  117,    2, 0x08 /* Private */,
      14,    0,  118,    2, 0x08 /* Private */,
      15,    0,  119,    2, 0x08 /* Private */,
      16,    0,  120,    2, 0x08 /* Private */,
      17,    0,  121,    2, 0x08 /* Private */,
      18,    0,  122,    2, 0x08 /* Private */,
      19,    0,  123,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
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

       0        // eod
};

void FractGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FractGUI *_t = static_cast<FractGUI *>(_o);
        switch (_id) {
        case 0: _t->selectZoom(); break;
        case 1: _t->resetZoom(); break;
        case 2: _t->setZoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->showChangeResol(); break;
        case 4: _t->showEquation(); break;
        case 5: _t->showPrecision(); break;
        case 6: _t->showColors(); break;
        case 7: _t->showControl(); break;
        case 8: _t->showVideo(); break;
        case 9: _t->makeVideo(); break;
        case 10: _t->showAbout(); break;
        case 11: _t->keepAspRat(); break;
        case 12: _t->saveToFile(); break;
        case 13: _t->loadFromFile(); break;
        case 14: _t->saveVToFile(); break;
        case 15: _t->loadVFromFile(); break;
        case 16: _t->saveImage(); break;
        case 17: _t->showAngle(); break;
        default: ;
        }
    }
}

const QMetaObject FractGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FractGUI.data,
      qt_meta_data_FractGUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FractGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FractGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FractGUI.stringdata))
        return static_cast<void*>(const_cast< FractGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FractGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
struct qt_meta_stringdata_equation_t {
    QByteArrayData data[4];
    char stringdata[25];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_equation_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_equation_t qt_meta_stringdata_equation = {
    {
QT_MOC_LITERAL(0, 0, 8), // "equation"
QT_MOC_LITERAL(1, 9, 7), // "checkEq"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 6) // "cancel"

    },
    "equation\0checkEq\0\0cancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_equation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void equation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        equation *_t = static_cast<equation *>(_o);
        switch (_id) {
        case 0: _t->checkEq(); break;
        case 1: _t->cancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject equation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_equation.data,
      qt_meta_data_equation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *equation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *equation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_equation.stringdata))
        return static_cast<void*>(const_cast< equation*>(this));
    return QDialog::qt_metacast(_clname);
}

int equation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_customZoom_t {
    QByteArrayData data[1];
    char stringdata[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_customZoom_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_customZoom_t qt_meta_stringdata_customZoom = {
    {
QT_MOC_LITERAL(0, 0, 10) // "customZoom"

    },
    "customZoom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_customZoom[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void customZoom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject customZoom::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_customZoom.data,
      qt_meta_data_customZoom,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *customZoom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *customZoom::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_customZoom.stringdata))
        return static_cast<void*>(const_cast< customZoom*>(this));
    return QDialog::qt_metacast(_clname);
}

int customZoom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_precision_t {
    QByteArrayData data[1];
    char stringdata[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_precision_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_precision_t qt_meta_stringdata_precision = {
    {
QT_MOC_LITERAL(0, 0, 9) // "precision"

    },
    "precision"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_precision[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void precision::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject precision::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_precision.data,
      qt_meta_data_precision,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *precision::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *precision::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_precision.stringdata))
        return static_cast<void*>(const_cast< precision*>(this));
    return QDialog::qt_metacast(_clname);
}

int precision::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_changeResol_t {
    QByteArrayData data[3];
    char stringdata[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_changeResol_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_changeResol_t qt_meta_stringdata_changeResol = {
    {
QT_MOC_LITERAL(0, 0, 11), // "changeResol"
QT_MOC_LITERAL(1, 12, 22), // "handleSelectionChanged"
QT_MOC_LITERAL(2, 35, 0) // ""

    },
    "changeResol\0handleSelectionChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_changeResol[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void changeResol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        changeResol *_t = static_cast<changeResol *>(_o);
        switch (_id) {
        case 0: _t->handleSelectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject changeResol::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_changeResol.data,
      qt_meta_data_changeResol,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *changeResol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *changeResol::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_changeResol.stringdata))
        return static_cast<void*>(const_cast< changeResol*>(this));
    return QDialog::qt_metacast(_clname);
}

int changeResol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_colors_t {
    QByteArrayData data[4];
    char stringdata[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_colors_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_colors_t qt_meta_stringdata_colors = {
    {
QT_MOC_LITERAL(0, 0, 6), // "colors"
QT_MOC_LITERAL(1, 7, 7), // "checkEq"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 6) // "cancel"

    },
    "colors\0checkEq\0\0cancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_colors[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void colors::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        colors *_t = static_cast<colors *>(_o);
        switch (_id) {
        case 0: _t->checkEq(); break;
        case 1: _t->cancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject colors::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_colors.data,
      qt_meta_data_colors,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *colors::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *colors::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_colors.stringdata))
        return static_cast<void*>(const_cast< colors*>(this));
    return QDialog::qt_metacast(_clname);
}

int colors::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_angle_t {
    QByteArrayData data[3];
    char stringdata[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_angle_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_angle_t qt_meta_stringdata_angle = {
    {
QT_MOC_LITERAL(0, 0, 5), // "angle"
QT_MOC_LITERAL(1, 6, 7), // "setAngl"
QT_MOC_LITERAL(2, 14, 0) // ""

    },
    "angle\0setAngl\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_angle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void angle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        angle *_t = static_cast<angle *>(_o);
        switch (_id) {
        case 0: _t->setAngl((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject angle::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_angle.data,
      qt_meta_data_angle,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *angle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *angle::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_angle.stringdata))
        return static_cast<void*>(const_cast< angle*>(this));
    return QDialog::qt_metacast(_clname);
}

int angle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_videoPoints_t {
    QByteArrayData data[12];
    char stringdata[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_videoPoints_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_videoPoints_t qt_meta_stringdata_videoPoints = {
    {
QT_MOC_LITERAL(0, 0, 11), // "videoPoints"
QT_MOC_LITERAL(1, 12, 6), // "addRow"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 9), // "showSlide"
QT_MOC_LITERAL(4, 30, 7), // "okClick"
QT_MOC_LITERAL(5, 38, 4), // "load"
QT_MOC_LITERAL(6, 43, 4), // "save"
QT_MOC_LITERAL(7, 48, 10), // "clearTable"
QT_MOC_LITERAL(8, 59, 6), // "insRow"
QT_MOC_LITERAL(9, 66, 6), // "delRow"
QT_MOC_LITERAL(10, 73, 14), // "randomizeMoves"
QT_MOC_LITERAL(11, 88, 3) // "Rnd"

    },
    "videoPoints\0addRow\0\0showSlide\0okClick\0"
    "load\0save\0clearTable\0insRow\0delRow\0"
    "randomizeMoves\0Rnd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_videoPoints[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

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
    QMetaType::Double,

       0        // eod
};

void videoPoints::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        videoPoints *_t = static_cast<videoPoints *>(_o);
        switch (_id) {
        case 0: _t->addRow(); break;
        case 1: _t->showSlide(); break;
        case 2: _t->okClick(); break;
        case 3: _t->load(); break;
        case 4: _t->save(); break;
        case 5: _t->clearTable(); break;
        case 6: _t->insRow(); break;
        case 7: _t->delRow(); break;
        case 8: _t->randomizeMoves(); break;
        case 9: { double _r = _t->Rnd();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject videoPoints::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_videoPoints.data,
      qt_meta_data_videoPoints,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *videoPoints::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *videoPoints::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_videoPoints.stringdata))
        return static_cast<void*>(const_cast< videoPoints*>(this));
    return QDialog::qt_metacast(_clname);
}

int videoPoints::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'projet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ProjetLO21/projet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Debut_t {
    QByteArrayData data[5];
    char stringdata[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Debut_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Debut_t qt_meta_stringdata_Debut = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 5),
QT_MOC_LITERAL(2, 12, 0),
QT_MOC_LITERAL(3, 13, 11),
QT_MOC_LITERAL(4, 25, 5)
    },
    "Debut\0ajout\0\0suppression\0modif\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Debut[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a,
       3,    0,   30,    2, 0x0a,
       4,    0,   31,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Debut::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Debut *_t = static_cast<Debut *>(_o);
        switch (_id) {
        case 0: _t->ajout(); break;
        case 1: _t->suppression(); break;
        case 2: _t->modif(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Debut::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Debut.data,
      qt_meta_data_Debut,  qt_static_metacall, 0, 0}
};


const QMetaObject *Debut::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Debut::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Debut.stringdata))
        return static_cast<void*>(const_cast< Debut*>(this));
    return QWidget::qt_metacast(_clname);
}

int Debut::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_UVSuppression_t {
    QByteArrayData data[3];
    char stringdata[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UVSuppression_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UVSuppression_t qt_meta_stringdata_UVSuppression = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 7),
QT_MOC_LITERAL(2, 22, 0)
    },
    "UVSuppression\0supprUV\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UVSuppression[] = {

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
       1,    0,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void UVSuppression::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UVSuppression *_t = static_cast<UVSuppression *>(_o);
        switch (_id) {
        case 0: _t->supprUV(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UVSuppression::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UVSuppression.data,
      qt_meta_data_UVSuppression,  qt_static_metacall, 0, 0}
};


const QMetaObject *UVSuppression::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UVSuppression::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UVSuppression.stringdata))
        return static_cast<void*>(const_cast< UVSuppression*>(this));
    return QWidget::qt_metacast(_clname);
}

int UVSuppression::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_UVModif_t {
    QByteArrayData data[3];
    char stringdata[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UVModif_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UVModif_t qt_meta_stringdata_UVModif = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 7),
QT_MOC_LITERAL(2, 16, 0)
    },
    "UVModif\0modifUV\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UVModif[] = {

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
       1,    0,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void UVModif::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UVModif *_t = static_cast<UVModif *>(_o);
        switch (_id) {
        case 0: _t->modifUV(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UVModif::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UVModif.data,
      qt_meta_data_UVModif,  qt_static_metacall, 0, 0}
};


const QMetaObject *UVModif::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UVModif::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UVModif.stringdata))
        return static_cast<void*>(const_cast< UVModif*>(this));
    return QWidget::qt_metacast(_clname);
}

int UVModif::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_UVAjout_t {
    QByteArrayData data[3];
    char stringdata[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UVAjout_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UVAjout_t qt_meta_stringdata_UVAjout = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 12),
QT_MOC_LITERAL(2, 21, 0)
    },
    "UVAjout\0slot_ajoutUV\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UVAjout[] = {

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
       1,    0,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void UVAjout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UVAjout *_t = static_cast<UVAjout *>(_o);
        switch (_id) {
        case 0: _t->slot_ajoutUV(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UVAjout::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UVAjout.data,
      qt_meta_data_UVAjout,  qt_static_metacall, 0, 0}
};


const QMetaObject *UVAjout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UVAjout::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UVAjout.stringdata))
        return static_cast<void*>(const_cast< UVAjout*>(this));
    return QWidget::qt_metacast(_clname);
}

int UVAjout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_UVEditeur_t {
    QByteArrayData data[3];
    char stringdata[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UVEditeur_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UVEditeur_t qt_meta_stringdata_UVEditeur = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 8),
QT_MOC_LITERAL(2, 19, 0)
    },
    "UVEditeur\0sauverUV\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UVEditeur[] = {

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
       1,    0,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void UVEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UVEditeur *_t = static_cast<UVEditeur *>(_o);
        switch (_id) {
        case 0: _t->sauverUV(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UVEditeur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UVEditeur.data,
      qt_meta_data_UVEditeur,  qt_static_metacall, 0, 0}
};


const QMetaObject *UVEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UVEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UVEditeur.stringdata))
        return static_cast<void*>(const_cast< UVEditeur*>(this));
    return QWidget::qt_metacast(_clname);
}

int UVEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE

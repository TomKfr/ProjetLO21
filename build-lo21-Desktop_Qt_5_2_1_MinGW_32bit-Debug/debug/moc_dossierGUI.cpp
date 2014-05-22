/****************************************************************************
** Meta object code from reading C++ file 'dossierGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ProjetLO21/dossierGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dossierGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DebutDossier_t {
    QByteArrayData data[3];
    char stringdata[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_DebutDossier_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_DebutDossier_t qt_meta_stringdata_DebutDossier = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 5),
QT_MOC_LITERAL(2, 19, 0)
    },
    "DebutDossier\0ajout\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DebutDossier[] = {

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

void DebutDossier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DebutDossier *_t = static_cast<DebutDossier *>(_o);
        switch (_id) {
        case 0: _t->ajout(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DebutDossier::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DebutDossier.data,
      qt_meta_data_DebutDossier,  qt_static_metacall, 0, 0}
};


const QMetaObject *DebutDossier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DebutDossier::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DebutDossier.stringdata))
        return static_cast<void*>(const_cast< DebutDossier*>(this));
    return QWidget::qt_metacast(_clname);
}

int DebutDossier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_DossierAjout_t {
    QByteArrayData data[5];
    char stringdata[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_DossierAjout_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_DossierAjout_t qt_meta_stringdata_DossierAjout = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 17),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 13),
QT_MOC_LITERAL(4, 46, 6)
    },
    "DossierAjout\0slot_ajoutDossier\0\0"
    "slot_selectUV\0update\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DossierAjout[] = {

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

void DossierAjout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DossierAjout *_t = static_cast<DossierAjout *>(_o);
        switch (_id) {
        case 0: _t->slot_ajoutDossier(); break;
        case 1: _t->slot_selectUV(); break;
        case 2: _t->update(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DossierAjout::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DossierAjout.data,
      qt_meta_data_DossierAjout,  qt_static_metacall, 0, 0}
};


const QMetaObject *DossierAjout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DossierAjout::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DossierAjout.stringdata))
        return static_cast<void*>(const_cast< DossierAjout*>(this));
    return QWidget::qt_metacast(_clname);
}

int DossierAjout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_AjoutUV_t {
    QByteArrayData data[5];
    char stringdata[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AjoutUV_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AjoutUV_t qt_meta_stringdata_AjoutUV = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 11),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 15),
QT_MOC_LITERAL(4, 37, 6)
    },
    "AjoutUV\0end_listeUV\0\0ajout_UVDossier\0"
    "update\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AjoutUV[] = {

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

void AjoutUV::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AjoutUV *_t = static_cast<AjoutUV *>(_o);
        switch (_id) {
        case 0: _t->end_listeUV(); break;
        case 1: _t->ajout_UVDossier(); break;
        case 2: _t->update(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AjoutUV::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AjoutUV.data,
      qt_meta_data_AjoutUV,  qt_static_metacall, 0, 0}
};


const QMetaObject *AjoutUV::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AjoutUV::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AjoutUV.stringdata))
        return static_cast<void*>(const_cast< AjoutUV*>(this));
    return QWidget::qt_metacast(_clname);
}

int AjoutUV::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE

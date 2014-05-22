/****************************************************************************
** Meta object code from reading C++ file 'dossierGUI2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ProjetLO21/dossierGUI2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dossierGUI2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MenuDossier_t {
    QByteArrayData data[11];
    char stringdata[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MenuDossier_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MenuDossier_t qt_meta_stringdata_MenuDossier = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 5),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 11),
QT_MOC_LITERAL(4, 31, 10),
QT_MOC_LITERAL(5, 42, 3),
QT_MOC_LITERAL(6, 46, 15),
QT_MOC_LITERAL(7, 62, 2),
QT_MOC_LITERAL(8, 65, 5),
QT_MOC_LITERAL(9, 71, 3),
QT_MOC_LITERAL(10, 75, 11)
    },
    "MenuDossier\0ajout\0\0suppression\0"
    "supDossier\0num\0DossierManager&\0dm\0"
    "modif\0fin\0sauvegarder\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuDossier[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a,
       3,    0,   45,    2, 0x0a,
       4,    2,   46,    2, 0x0a,
       8,    0,   51,    2, 0x0a,
       9,    0,   52,    2, 0x0a,
      10,    0,   53,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 6,    5,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MenuDossier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MenuDossier *_t = static_cast<MenuDossier *>(_o);
        switch (_id) {
        case 0: _t->ajout(); break;
        case 1: _t->suppression(); break;
        case 2: _t->supDossier((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< DossierManager(*)>(_a[2]))); break;
        case 3: _t->modif(); break;
        case 4: _t->fin(); break;
        case 5: _t->sauvegarder(); break;
        default: ;
        }
    }
}

const QMetaObject MenuDossier::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MenuDossier.data,
      qt_meta_data_MenuDossier,  qt_static_metacall, 0, 0}
};


const QMetaObject *MenuDossier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuDossier::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MenuDossier.stringdata))
        return static_cast<void*>(const_cast< MenuDossier*>(this));
    return QWidget::qt_metacast(_clname);
}

int MenuDossier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
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
struct qt_meta_stringdata_ModifierDossier_t {
    QByteArrayData data[5];
    char stringdata[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ModifierDossier_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ModifierDossier_t qt_meta_stringdata_ModifierDossier = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 19),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 12),
QT_MOC_LITERAL(4, 50, 20)
    },
    "ModifierDossier\0slot_modifFormation\0"
    "\0slot_modifUV\0slot_finModifDossier\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModifierDossier[] = {

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

void ModifierDossier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModifierDossier *_t = static_cast<ModifierDossier *>(_o);
        switch (_id) {
        case 0: _t->slot_modifFormation(); break;
        case 1: _t->slot_modifUV(); break;
        case 2: _t->slot_finModifDossier(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ModifierDossier::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ModifierDossier.data,
      qt_meta_data_ModifierDossier,  qt_static_metacall, 0, 0}
};


const QMetaObject *ModifierDossier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModifierDossier::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModifierDossier.stringdata))
        return static_cast<void*>(const_cast< ModifierDossier*>(this));
    return QWidget::qt_metacast(_clname);
}

int ModifierDossier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_ModifFormation_t {
    QByteArrayData data[4];
    char stringdata[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ModifFormation_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ModifFormation_t qt_meta_stringdata_ModifFormation = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 21),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 6)
    },
    "ModifFormation\0enregistrer_formation\0"
    "\0update\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModifFormation[] = {

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
       1,    0,   24,    2, 0x0a,
       3,    0,   25,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ModifFormation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModifFormation *_t = static_cast<ModifFormation *>(_o);
        switch (_id) {
        case 0: _t->enregistrer_formation(); break;
        case 1: _t->update(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ModifFormation::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ModifFormation.data,
      qt_meta_data_ModifFormation,  qt_static_metacall, 0, 0}
};


const QMetaObject *ModifFormation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModifFormation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModifFormation.stringdata))
        return static_cast<void*>(const_cast< ModifFormation*>(this));
    return QWidget::qt_metacast(_clname);
}

int ModifFormation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_ModifUV_t {
    QByteArrayData data[5];
    char stringdata[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ModifUV_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ModifUV_t qt_meta_stringdata_ModifUV = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 9),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 11),
QT_MOC_LITERAL(4, 31, 5)
    },
    "ModifUV\0ajouterUV\0\0supprimerUV\0finUV\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModifUV[] = {

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

void ModifUV::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModifUV *_t = static_cast<ModifUV *>(_o);
        switch (_id) {
        case 0: _t->ajouterUV(); break;
        case 1: _t->supprimerUV(); break;
        case 2: _t->finUV(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ModifUV::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ModifUV.data,
      qt_meta_data_ModifUV,  qt_static_metacall, 0, 0}
};


const QMetaObject *ModifUV::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModifUV::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModifUV.stringdata))
        return static_cast<void*>(const_cast< ModifUV*>(this));
    return QWidget::qt_metacast(_clname);
}

int ModifUV::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_SuppressionUV_t {
    QByteArrayData data[4];
    char stringdata[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SuppressionUV_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SuppressionUV_t qt_meta_stringdata_SuppressionUV = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 18),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 14)
    },
    "SuppressionUV\0suppression_une_uv\0\0"
    "finSuppression\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SuppressionUV[] = {

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
       1,    0,   24,    2, 0x0a,
       3,    0,   25,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SuppressionUV::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SuppressionUV *_t = static_cast<SuppressionUV *>(_o);
        switch (_id) {
        case 0: _t->suppression_une_uv(); break;
        case 1: _t->finSuppression(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SuppressionUV::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SuppressionUV.data,
      qt_meta_data_SuppressionUV,  qt_static_metacall, 0, 0}
};


const QMetaObject *SuppressionUV::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SuppressionUV::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SuppressionUV.stringdata))
        return static_cast<void*>(const_cast< SuppressionUV*>(this));
    return QWidget::qt_metacast(_clname);
}

int SuppressionUV::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE

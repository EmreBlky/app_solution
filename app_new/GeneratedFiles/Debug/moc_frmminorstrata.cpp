/****************************************************************************
** Meta object code from reading C++ file 'frmminorstrata.h'
**
** Created: Thu 7. Apr 13:38:59 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmminorstrata.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmminorstrata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DateTimeDelegate[] = {

 // content:
       4,       // revision
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

static const char qt_meta_stringdata_DateTimeDelegate[] = {
    "DateTimeDelegate\0"
};

const QMetaObject DateTimeDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_DateTimeDelegate,
      qt_meta_data_DateTimeDelegate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DateTimeDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DateTimeDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DateTimeDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DateTimeDelegate))
        return static_cast<void*>(const_cast< DateTimeDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int DateTimeDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_FrmMinorStrata[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      30,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmMinorStrata[] = {
    "FrmMinorStrata\0\0showDetails()\0"
    "viewRecord()\0"
};

const QMetaObject FrmMinorStrata::staticMetaObject = {
    { &GenericTab::staticMetaObject, qt_meta_stringdata_FrmMinorStrata,
      qt_meta_data_FrmMinorStrata, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmMinorStrata::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmMinorStrata::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmMinorStrata::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmMinorStrata))
        return static_cast<void*>(const_cast< FrmMinorStrata*>(this));
    if (!strcmp(_clname, "Ui::frmminorstrata"))
        return static_cast< Ui::frmminorstrata*>(const_cast< FrmMinorStrata*>(this));
    return GenericTab::qt_metacast(_clname);
}

int FrmMinorStrata::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GenericTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showDetails(); break;
        case 1: viewRecord(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

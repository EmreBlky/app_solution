/****************************************************************************
** Meta object code from reading C++ file 'frmreports.h'
**
** Created: Thu 23. Jun 11:56:08 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmreports.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmreports.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmReports[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      33,   29,   11,   11, 0x05,
      69,   53,   11,   11, 0x05,
      93,   29,   11,   11, 0x25,

 // slots: signature, parameters, type, tag, flags
     117,  112,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmReports[] = {
    "FrmReports\0\0hideFrmReports()\0str\0"
    "showStatus(QString)\0str,bShowMsgBox\0"
    "showError(QString,bool)\0showError(QString)\0"
    "item\0previewItem(QListWidgetItem*)\0"
};

const QMetaObject FrmReports::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FrmReports,
      qt_meta_data_FrmReports, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmReports::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmReports::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmReports::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmReports))
        return static_cast<void*>(const_cast< FrmReports*>(this));
    if (!strcmp(_clname, "Ui::frmreports"))
        return static_cast< Ui::frmreports*>(const_cast< FrmReports*>(this));
    return QWidget::qt_metacast(_clname);
}

int FrmReports::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: hideFrmReports(); break;
        case 1: showStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: showError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 3: showError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: previewItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FrmReports::hideFrmReports()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FrmReports::showStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FrmReports::showError(QString _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
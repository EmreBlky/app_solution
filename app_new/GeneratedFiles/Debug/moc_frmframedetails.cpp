/****************************************************************************
** Meta object code from reading C++ file 'frmframedetails.h'
**
** Created: Wed 13. Apr 17:16:26 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../frmframedetails.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmframedetails.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrmFrameDetails[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      40,   36,   16,   16, 0x05,
      76,   60,   16,   16, 0x05,
     100,   36,   16,   16, 0x25,

 // slots: signature, parameters, type, tag, flags
     119,   16,   16,   16, 0x08,
     126,   16,   16,   16, 0x08,
     131,   16,   16,   16, 0x08,
     140,   16,   16,   16, 0x08,
     148,   16,   16,   16, 0x08,
     157,   16,   16,   16, 0x08,
     164,   36,   16,   16, 0x08,
     199,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrmFrameDetails[] = {
    "FrmFrameDetails\0\0hideFrameDetails()\0"
    "str\0showStatus(QString)\0str,bShowMsgBox\0"
    "showError(QString,bool)\0showError(QString)\0"
    "back()\0ok()\0cancel()\0apply()\0verify()\0"
    "undo()\0isClonedFromPreviousFrame(QString)\0"
    "enableVerify()\0"
};

const QMetaObject FrmFrameDetails::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FrmFrameDetails,
      qt_meta_data_FrmFrameDetails, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrmFrameDetails::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrmFrameDetails::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrmFrameDetails::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrmFrameDetails))
        return static_cast<void*>(const_cast< FrmFrameDetails*>(this));
    if (!strcmp(_clname, "Ui::frmframedetails"))
        return static_cast< Ui::frmframedetails*>(const_cast< FrmFrameDetails*>(this));
    return QWidget::qt_metacast(_clname);
}

int FrmFrameDetails::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: hideFrameDetails(); break;
        case 1: showStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: showError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 3: showError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: back(); break;
        case 5: ok(); break;
        case 6: cancel(); break;
        case 7: apply(); break;
        case 8: verify(); break;
        case 9: undo(); break;
        case 10: isClonedFromPreviousFrame((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: enableVerify(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void FrmFrameDetails::hideFrameDetails()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FrmFrameDetails::showStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FrmFrameDetails::showError(QString _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

#include <QTest>
#include "generictab.h"

GenericTab::GenericTab(const int index, Sample* inSample, DateModel* inTDateTime, const QString inStrTitle, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags),m_index(index), m_tDateTime(inTDateTime), m_sample(inSample), m_title(inStrTitle), m_ruleCheckerPtr(ruleCheckerPtr) {

    nullDellegate=0;

    connect(this, SIGNAL(lockControls(bool,QList<QWidget*>&)), this,
    SLOT(onLockControls(bool,QList<QWidget*>&)));

    connect(this, SIGNAL(forward(QString)), this,
    SLOT(goForward()));

}

GenericTab::~GenericTab()
{
    if (nullDellegate!=0) delete nullDellegate;
}

bool GenericTab::initBinder(MapperRuleBinder* mapperBinderPtr)
{
    // initialize rule binder and *connect* signals!! (on init())
    //m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, mapper);
    mapperBinderPtr->init();

    //! This is are the signals of the rule binder we need to connect to:
    // addRecord, first stage record added and second stage record added (run and finish running post-triggers)
    // the pre triggers signals are connected in the binder classes; then we just need the stuff to show messages...
/*
    QDataWidgetMapper **data = mapperBinderPtr->getArMapper().data();
    for (size_t j=0; j < mapperBinderPtr->getArMapper().count(); ++j){

        if ( qobject_cast<QSqlTableModel*>(mapperBinderPtr->getArMapper()[j]->model())==0) return false;
        QSqlTableModel* tModel=qobject_cast<QSqlTableModel*>(mapperBinderPtr->getArMapper()[j]->model());*/

        // Default Rules
        connect(this, SIGNAL(addRecord(const QString)), mapperBinderPtr,
            SIGNAL(addRecord(const QString)));

        // Pre Submit Rules
        connect(this, SIGNAL(submit(const QString)), mapperBinderPtr,
            SIGNAL(submitRecord(const QString)));

        connect(mapperBinderPtr, SIGNAL(finishedPreSubmit(const bool)), this,
            SLOT(onPreSubmit(const bool)));

        // Post Trigger Rules
        connect(this, SIGNAL(recordAdded(const QString)), mapperBinderPtr,
            SIGNAL(recordAdded(const QString)));

        //connect(mapperBinderPtr, SIGNAL(finishedPostTrigger(bool)), this,
            //SLOT(onRecordAdded(bool)));

        // Messages
        connect(mapperBinderPtr, SIGNAL(showError(QString, const bool)), this,
        SIGNAL(showError(QString, const bool)));

        connect(mapperBinderPtr, SIGNAL(showStatus(QString)), this,
            SIGNAL(showStatus(QString)));

    //}

    return true;
}

bool GenericTab::onPreSubmit(const bool bSubmit)
{
    //TODO: make this virtual and abstract
    return true;
}

void GenericTab::setLbHead(QLabel* inLbHeader)
{
    lbHead=inLbHeader;
}

bool GenericTab::getDtId(const int mapIdx, int& id)
{
    QModelIndex idx= m_tDateTime->index(mapIdx,0,QModelIndex());
    if (!idx.isValid()) return false;

    id=m_tDateTime->data(idx).toInt();
    return true;
}

void GenericTab::goBack()
{
    emit navigate(false,m_index);
}

void GenericTab::goForward()
{
    emit navigate(true,m_index);
}

void GenericTab::onLockControls(bool bLock,QList<QWidget*>& lWidgets)
{
    for (int i=0; i < lWidgets.size();++i)
        lWidgets.at(i)->setDisabled(bLock);
}

void GenericTab::resizeToVisibleColumns ( QTableView* table )
{
    int ct=0;
    for (int i=0; i < table->model()->columnCount(); ++i)
        if (!table->isColumnHidden(i)) ++ ct;

    for (int i=0; i < table->model()->columnCount(); ++i)
        if (!table->isColumnHidden(i))
            table->setColumnWidth(i,table->width()/ct);

}

///////////////////////////////////////////////

NullRelationalDelegate::NullRelationalDelegate(QList<int> colsOthers, QList<int> colsText, QObject *parent):
                        QSqlRelationalDelegate(parent),m_colsText(colsText), m_colsOthers(colsOthers)
{

}
void NullRelationalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (m_colsOthers.contains(index.column())){
        QSqlRelationalDelegate::setModelData(editor,model,index);
    }else{
        if (m_colsText.contains(index.column())){//textEdits
            model->setData(index, editor->property("plainText") == tr("") ?
                QVariant() :
            editor->property("plainText"));
        }else {
            model->setData(index, editor->property("text") == tr("") ?
            QVariant() :
            editor->property("text"));
        }
    }
}

void NullRelationalDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (m_colsOthers.contains(index.column())){//others
        QSqlRelationalDelegate::setEditorData(editor,index);
    }else{
        if (m_colsText.contains(index.column())){//text edits
            editor->setProperty("plainText", index.data());
        }else {
            editor->setProperty("text", index.data());
        }
    }
}

////////////////////////////////////////// static

void filterTable(QSqlTableModel* table)
{
    table->setFilter(QObject::tr("Name<>'") + qApp->translate("null_replacements", strNa)
            + QObject::tr("' AND Name<>'") + qApp->translate("bin", strOutside)
            + QObject::tr("' AND Name<>'") + qApp->translate("null_replacements", strMissing)
            + QObject::tr("' AND Name<>'") + qApp->translate("null_replacements", strOther)
            + QObject::tr("' AND Name<>'") + qApp->translate("null_replacements", strUnknown)
            + QObject::tr("'"));
}
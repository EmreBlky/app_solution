#include <QTest>
#include "generictab.h"

GenericTab::GenericTab(const int index, QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags),m_index(index){

    connect(this, SIGNAL(lockControls(bool,QList<QWidget*>&)), this,
    SLOT(onLockControls(bool,QList<QWidget*>&)));
}

GenericTab::~GenericTab()
{
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
#include <QTest>
#include "globaldefs.h"
#include "frmminorstrata.h"

FrmMinorStrata::FrmMinorStrata(DateModel* inTDateTime, QWidget *parent, Qt::WFlags flags):
GenericTab(1,inTDateTime,parent, flags){

    setupUi(this);

    viewMinorStrata=0;
    tRefMinorStrata=0;
    buttonGroup=0;
    nullDellegate=0;
    mapper1=0;
    mapperStartDt=0;
    mapperEndDt=0;

    connect(pushNext, SIGNAL(clicked()), this,
    SLOT(goForward()));

    connect(pushPrevious, SIGNAL(clicked()), this,
    SLOT(goBack()));

    initModels();
    initUI();
    initMappers();
}

FrmMinorStrata::~FrmMinorStrata()
{
    if (tRefMinorStrata!=0) delete tRefMinorStrata;
    if (buttonGroup!=0) delete buttonGroup;
    if (nullDellegate!=0) delete nullDellegate;
    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;
    if (viewMinorStrata!=0) delete viewMinorStrata;
}

void FrmMinorStrata::next()
{
    //TODO: retrieve the selection model properly

    if (!m_selectedIdx.isValid()){
        emit showError(tr("You must select only one Minor Strata!"));
        return;
    }

    QModelIndex idx1=m_selectedIdx;
    QModelIndex idx2=viewMinorStrata->index(idx1.row(),1);//name of selected index
    QModelIndex idx3=viewMinorStrata->index(idx1.row(),0);//id of selected index

    if (!idx1.isValid() || !idx2.isValid() || !idx3.isValid())
    {
        emit showError(tr("Unable to retrieve information about selected index!"));
        return;
    }

    emit forward(lbHeader->text() + tr("-> ") + idx2.data().toString(),idx3.data());
}
void FrmMinorStrata::setReadOnly(const bool bRO)
{
    lineNew->setEnabled(!bRO);
    label_3->setEnabled(!bRO);
    cmbGLS->setEnabled(!bRO);
    groupActivity->setEnabled(!bRO);
    radioActive->setEnabled(!bRO);
    horizontalLayout->setEnabled(!bRO);
    radioInactive->setEnabled(!bRO);
    cmbReasons->setEnabled(!bRO);
    label_4->setEnabled(!bRO);
    textComments->setEnabled(!bRO);
    label->setEnabled(!bRO);
    label_2->setEnabled(!bRO);
    customDtStart->setEnabled(!bRO);
    customDtEnd->setEnabled(!bRO);

    if (bRO){
        buttonBox->button(QDialogButtonBox::Apply)->hide();
    }else{
        buttonBox->button(QDialogButtonBox::Apply)->show();
    }

}

void FrmMinorStrata::disableReasonCombo()
{
    if (static_cast<QRadioButton*>(QObject::sender())==0) return;
    cmbReasons->setEnabled(static_cast<QRadioButton*>(QObject::sender())!=radioActive);
}

void FrmMinorStrata::setActiveReason(bool bActive)
{
    if (bActive){
        int index=cmbReasons->findText(qApp->translate("null_replacements", strNa ));
        cmbReasons->setCurrentIndex(index);
    }
}

void FrmMinorStrata::previewRow(QModelIndex index)
{
    m_selectedIdx=index;//stores the index

    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    setReadOnly(true);

    QModelIndex idx=viewMinorStrata->index(index.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this minor strata!"));
        return;
    }

    QString id=idx.data().toString();

    tRefMinorStrata->setFilter(tr("Ref_Minor_Strata.ID=")+id);
    if (tRefMinorStrata->rowCount()!=1)
        return;

    mapper1->toLast();

    //Now fix the dates
    idx=tRefMinorStrata->index(0,1);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this minor strata!"));
        return;
    }
    QString strStartDt=idx.data().toString();
    idx=tRefMinorStrata->index(0,2);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this minor strata!"));
        return;
    }
    QString strEndDt=idx.data().toString();

    m_tDateTime->setFilter(tr("ID=") + strStartDt + tr(" OR ID=") + strEndDt);

    if (m_tDateTime->rowCount()!=2)
        return;

    mapperEndDt->toLast();
    mapperStartDt->setCurrentIndex(mapperEndDt->currentIndex()-1);
}

void FrmMinorStrata::onShowForm()
{
    //Make sure all models are up to date, and without filters
    tRefMinorStrata->select();
    m_tDateTime->select();
    setMinorStrataQuery();

    if (tRefMinorStrata==0) return ;
    if (!tRefMinorStrata->filter().isEmpty()) tRefMinorStrata->setFilter(tr(""));

    if (m_tDateTime==0) return ;
    if (!m_tDateTime->filter().isEmpty()) m_tDateTime->setFilter(tr(""));

    //filter the relational model from GLS
    filterGLS();
}

void FrmMinorStrata::uI4NewRecord()
{
    if (!this->groupDetails->isVisible())
        this->groupDetails->setVisible(true);

    setReadOnly(false);

    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);

    lineNew->clear();
    radioActive->click();
    textComments->clear();
}

void FrmMinorStrata::filterGLS()
{
    QString strQuery=
    tr("SELECT     dbo.FR_F2GLS.id_gls ") +
    tr("FROM         dbo.FR_Sub_Frame INNER JOIN") +
    tr("                 dbo.FR_F2GLS ON dbo.FR_Sub_Frame.ID = dbo.FR_F2GLS.id_sub_frame INNER JOIN") +
    tr("                  dbo.FR_Frame INNER JOIN") +
    tr("                  dbo.FR_Time ON dbo.FR_Frame.ID = dbo.FR_Time.id_frame ON dbo.FR_Sub_Frame.id_frame = dbo.FR_Frame.ID ") +
    tr("WHERE     (dbo.FR_Time.ID = :id) AND (dbo.FR_Sub_Frame.Type =") +
    tr("                      (SELECT     ID") +
    tr("                        FROM          dbo.Ref_Frame") +
    tr("                        WHERE      (Name = :root)) )");

    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(0,m_varData);
    query.bindValue(1,qApp->translate("frame", strRoot));

    if (!query.exec()){
        emit showError(tr("Could not obtain filter for Group of Landing Sites!"));
        return;
    }

    QString strFilter(tr(""));
     while (query.next()) {
        strFilter.append(tr("ID=") + query.value(0).toString());
        strFilter.append(tr(" OR "));
     }
     if (!strFilter.isEmpty())
         strFilter=strFilter.remove(strFilter.size()-tr(" OR ").length(),tr(" OR ").length());

    tRefMinorStrata->relationModel(4)->setFilter(strFilter);
}

void FrmMinorStrata::createRecord()
{
    //removing filters
    if (tRefMinorStrata==0) return ;
    if (!tRefMinorStrata->filter().isEmpty()) tRefMinorStrata->setFilter(tr(""));

    if (m_tDateTime==0) return ;
    if (!m_tDateTime->filter().isEmpty()) m_tDateTime->setFilter(tr(""));

    while(tRefMinorStrata->canFetchMore())
        tRefMinorStrata->fetchMore();

    //Check for uncomitted changes
    QModelIndex idx=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,0);
    if (!idx.isValid()) return;

    if (tRefMinorStrata->isDirty(idx))
        tRefMinorStrata->revertAll();

    tRefMinorStrata->insertRow(tRefMinorStrata->rowCount());

    mapper1->toLast();

    //TODO: put dates from the frame as default

    if(!m_tDateTime) return;
    m_tDateTime->select();

    bool bDate, bTime;
    customDtStart->getIsDateTime(bDate,bTime);
    if (!m_tDateTime->insertNewRecord(customDtStart->getIsAuto(),bDate,bTime)){
        emit showError(tr("Could not insert start date!"));
        return;
    }
    customDtEnd->getIsDateTime(bDate,bTime);
    if (!m_tDateTime->insertNewRecord(customDtStart->getIsAuto(),bDate,bTime)){
        emit showError(tr("Could not insert start date!"));
        return;
    }

    mapperStartDt->setCurrentIndex(m_tDateTime->rowCount()-2);
    mapperEndDt->setCurrentIndex(m_tDateTime->rowCount()-1);

    idx=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,3);
    tRefMinorStrata->setData(idx,m_varData);//id_sub_frame

    uI4NewRecord();//init UI
}

void FrmMinorStrata::onButtonClick(QAbstractButton* button)
{
    if ( buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        this->groupDetails->hide();
        this->tRefMinorStrata->revertAll();

    } else if (buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole){

        bool bError=false;
        //First insert the dates...
        if (!mapperStartDt->submit() 
            || !mapperEndDt->submit()){
            if (m_tDateTime->lastError().type()!=QSqlError::NoError)
                emit showError(m_tDateTime->lastError().text());
            else
                emit showError(tr("Could not submit mapper!"));
            bError=true;
        }
        else{
            if (!m_tDateTime->submitAll()){
                if (m_tDateTime->lastError().type()!=QSqlError::NoError)
                    emit showError(m_tDateTime->lastError().text());
                else
                    emit showError(tr("Could not write DateTime in the database!"));

                bError=true;
            }
        }

        while(m_tDateTime->canFetchMore())
            m_tDateTime->fetchMore();

        int startIdx=m_tDateTime->rowCount()-2;
        int endIdx=m_tDateTime->rowCount()-1;

        mapperStartDt->setCurrentIndex(startIdx);
        mapperEndDt->setCurrentIndex(endIdx);

        if (bError) {
            emit showError(tr("Could not create dates in the database!"));
        }else{

            int idStart;
            if (getDtId(startIdx,idStart)){
                QModelIndex idxStart=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,1);
                if (idxStart.isValid()){
                    tRefMinorStrata->setData(idxStart,idStart);
                }else bError=true;
            }else bError=true;

            int idEnd;
            if (getDtId(endIdx,idEnd)){
                QModelIndex idxEnd=tRefMinorStrata->index(tRefMinorStrata->rowCount()-1,2);
                if (idxEnd.isValid()){
                    tRefMinorStrata->setData(idxEnd,idEnd);
                }else bError=true;
            }else bError=true;

            if (!bError){
                if (mapper1->submit()){
                    bError=!
                        tRefMinorStrata->submitAll();
                    if (bError){
                        if (tRefMinorStrata->lastError().type()!=QSqlError::NoError)
                            emit showError(tRefMinorStrata->lastError().text());
                        else
                            emit showError(tr("Could not write Minor Strata in the database!"));
                    }mapper1->toLast();
                }else bError=true;
            }
        }
        button->setEnabled(bError);
        setReadOnly(!bError);
        if (!bError){
            setMinorStrataQuery();
            tableView->selectRow(0);
            tRefMinorStrata->select();
        }
    }
}
void FrmMinorStrata::initUI()
{
    setHeader();
    this->groupDetails->setVisible(false);

    customDtStart->setIsDateTime(true,false,false);
    customDtStart->setIsUTC(false);
    customDtStart->setIsAuto(false);

    customDtEnd->setIsDateTime(true,false,false);
    customDtEnd->setIsUTC(false);
    customDtEnd->setIsAuto(false);

    buttonGroup=new ButtonGroup(this);
    buttonGroup->addButton(radioActive,0);
    buttonGroup->addButton(radioInactive,1);

    tableView->setModel(viewMinorStrata);
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->verticalHeader()->hide();
    tableView->setSelectionMode(
        QAbstractItemView::SingleSelection);
    tableView->horizontalHeader()->setClickable(false);
    tableView->horizontalHeader()->setFrameStyle(QFrame::NoFrame);
}

void FrmMinorStrata::resizeEvent ( QResizeEvent * event )
{
    resizeToVisibleColumns(tableView);
}

void FrmMinorStrata::resizeToVisibleColumns ( QTableView* table )
{
    int ct=0;
    for (int i=0; i < table->model()->columnCount(); ++i)
        if (!table->isColumnHidden(i)) ++ ct;

    for (int i=0; i < table->model()->columnCount(); ++i)
        if (!table->isColumnHidden(i))
            table->setColumnWidth(i,table->width()/ct);

}

void FrmMinorStrata::setMinorStrataQuery()
{
    viewMinorStrata->setQuery(
    tr("SELECT     dbo.Ref_Minor_Strata.ID, dbo.Ref_Minor_Strata.Name, F1.Date_Local AS [Start Date], F2.Date_Local AS [End Date], ") +
    tr("CASE WHEN dbo.Ref_Minor_Strata.IsClosed=0 THEN 'false' ELSE 'true' END Closed ") +
    tr(" FROM         dbo.Ref_Minor_Strata INNER JOIN") +
    tr("                      dbo.GL_Dates AS F1 ON dbo.Ref_Minor_Strata.id_start_dt = F1.ID INNER JOIN") +
    tr("                      dbo.GL_Dates AS F2 ON dbo.Ref_Minor_Strata.id_end_dt = F2.ID") +
    tr("                      WHERE     (dbo.Ref_Minor_Strata.id_frame_time = ") + this->m_varData.toString() + tr(")") +
    tr("                      ORDER BY dbo.Ref_Minor_Strata.ID DESC")
    );

    tableView->hideColumn(0);
    resizeToVisibleColumns(tableView);
}

void FrmMinorStrata::initModels()
{
    //Minor Strata
    tRefMinorStrata=new QSqlRelationalTableModel();
    tRefMinorStrata->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Ref_Minor_Strata"),
        QSqlDriver::TableName));
    tRefMinorStrata->setRelation(4, QSqlRelation(tr("Ref_Group_of_LandingSites"), tr("ID"), tr("Name")));
    tRefMinorStrata->setRelation(6, QSqlRelation(tr("Ref_No_Recording_Activities"), tr("ID"), tr("Name")));
    tRefMinorStrata->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tRefMinorStrata->select();

    viewMinorStrata = new QSqlQueryModel;
    viewMinorStrata->setHeaderData(0, Qt::Horizontal, tr("Name"));
    viewMinorStrata->setHeaderData(1, Qt::Horizontal, tr("Start"));
    viewMinorStrata->setHeaderData(2, Qt::Horizontal, tr("End"));
    viewMinorStrata->setHeaderData(3, Qt::Horizontal, tr("Closed"));
}

bool FrmMinorStrata::getDateModel(const int dtField, QSqlQueryModel& model)
{
    QModelIndex dtID=tRefMinorStrata->index(mapper1->currentIndex(),dtField);
    if (!dtID.isValid()) return false;
    QString strId=dtID.data().toString();
    model.setQuery(tr("SELECT Date_Local FROM GL_DATES WHERE ID=") + strId);

    return true;
}

void FrmMinorStrata::initMappers()
{
    if (mapper1!=0) delete mapper1;

    mapper1= new QDataWidgetMapper(this);
    mapper1->setModel(tRefMinorStrata);
    mapper1->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    if (nullDellegate!=0) delete nullDellegate;
    QList<int> lCmb;
    lCmb << 4 << 5 << 6;
    QList<int> lText;
    lText << 7;
    nullDellegate=new NullRelationalDelegate(lCmb,lText);
    mapper1->setItemDelegate(nullDellegate);

    cmbGLS->setModel(tRefMinorStrata->relationModel(4));
    cmbGLS->setModelColumn(
        tRefMinorStrata->relationModel(4)->fieldIndex(tr("Name")));

    cmbReasons->setModel(tRefMinorStrata->relationModel(6));
    cmbReasons->setModelColumn(
        tRefMinorStrata->relationModel(6)->fieldIndex(tr("Name")));

    mapper1->addMapping(lineNew, 8);
    mapper1->addMapping(cmbGLS, 4);
    mapper1->addMapping(cmbReasons, 6);
    mapper1->addMapping(buttonGroup,5);
    mapper1->addMapping(textComments,7);

    if (mapperStartDt!=0) delete mapperStartDt;
    if (mapperEndDt!=0) delete mapperEndDt;

    mapperStartDt= new QDataWidgetMapper(this);
    mapperStartDt->setModel(m_tDateTime);
    mapperStartDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperStartDt->setItemDelegate(new QItemDelegate(this));
    mapperStartDt->addMapping(customDtStart,3,tr("dateTime").toAscii());

    mapperEndDt= new QDataWidgetMapper(this);
    mapperEndDt->setModel(m_tDateTime);
    mapperEndDt->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapperEndDt->setItemDelegate(new QItemDelegate(this));
    mapperEndDt->addMapping(customDtEnd,3,tr("dateTime").toAscii());
}

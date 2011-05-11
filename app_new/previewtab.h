#include <QtGui>
#include <QtSql>
#include "customtimectrl.h"
#include "generictab.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////////
#ifndef PREVIEWTAB_H
#define PREVIEWTAB_H

//! Preview Tab Class
/*!
This class extends the Generic Tab to a more particular form, with a preview for inserted records;
*/

class PreviewTab : public GenericTab
{
    Q_OBJECT

    public:
        PreviewTab(const int index, Sample* inSample, DateModel* inTDateTime, const QString inStrTitle, 
            QWidget *parent = 0, Qt::WFlags flags = 0);
        ~PreviewTab();

        void                                  insertRecordIntoModel(QSqlTableModel* m);

    protected:
    //! A pure virtual member.
    /*! In this function we set the query that displays the records on the preview container;
      \sa setPreviewTable(QTableView* aTable), filterModel4Combo(), setReadOnly(const bool bRO), uI4NewRecord(), genericCreateRecord()
    */
        void                                  setPreviewModel(QSqlRelationalTableModel* aModel){m_model=aModel;}
    //! A pure virtual member.
    /*! In this function we set the table that displays the records;
      \sa setPreviewModel(QSqlRelationalTableModel* aModel), filterModel4Combo(), setReadOnly(const bool bRO), uI4NewRecord(), genericCreateRecord()
    */
        void                                  setPreviewTable(QTableView* aTable){m_table=aTable;}
    //! A pure virtual member.
    /*! In this function we set the query that displays the records on the preview container;
      \sa setPreviewTable(QTableView* aTable), setPreviewModel(QSqlRelationalTableModel* aModel), filterModel4Combo(), setReadOnly(const bool bRO), uI4NewRecord(), genericCreateRecord()
    */
        virtual void                          setPreviewQuery()=0;
    //! A pure virtual member.
    /*! In this function we set the query that filters the combobox for the selected top-level id;
      \sa setPreviewTable(QTableView* aTable), setPreviewModel(QSqlRelationalTableModel* aModel), setPreviewQuery(), setReadOnly(const bool bRO), uI4NewRecord(), genericCreateRecord()
    */
        virtual void                          filterModel4Combo()=0;
    //! A pure virtual member.
    /*! In this function we initialize the UI values for a new record;
      \sa setPreviewTable(QTableView* aTable), setPreviewModel(QSqlRelationalTableModel* aModel), setPreviewQuery(), setReadOnly(const bool bRO), filterModel4Combo(), genericCreateRecord()
    */
        virtual void                          uI4NewRecord()=0;
    //! A pure virtual member.
    /*! In this function we initialize some values (UI, models, etc) that need to be set before calling the onShowForm;
      \sa onShowForm()
    */
        virtual void                          beforeShow()=0;
    /*! generic create record;
      \sa setPreviewTable(QTableView* aTable), setPreviewModel(QSqlRelationalTableModel* aModel), setPreviewQuery(), setReadOnly(const bool bRO), filterModel4Combo(), uI4NewRecord()
    */
        void                                  genericCreateRecord();
        void                                  resizeEvent ( QResizeEvent * event );
        bool                                  afterApply();
        QList<QWidget*>                       m_lWidgets;
        QModelIndex                           m_selectedIdx;

    signals:

    public slots:
        void                                  onShowForm();

    private slots:
        bool                                  next();
        //! A pure virtual member.
        /*! Slot that inititializes a new record
          \sa previewRow(QModelIndex index), onButtonClick(QAbstractButton * button)
        */
        virtual void                          createRecord()=0;
        //! A pure virtual member.
        /*! Slot that previews a selected row
          \sa createRecord(), onButtonClick(QAbstractButton * button)
        */
        virtual void                          previewRow(QModelIndex index)=0;
        //! A pure virtual member.
        /*! Slot that implements the two buttons on the preview/edit dialog: close and apply
          \sa createRecord(), previewRow(QModelIndex index)
        */
        virtual bool                          onButtonClick(QAbstractButton * button)=0;

    private:
        //! A pure virtual member.
        /*! Helper function for the next slot, that updates the sample structure
          \sa getNextLabel(QString& strLabel)
        */
        virtual bool                          updateSample()=0;
        //! A pure virtual member.
        /*! Helper function for the next slot, that gets the title label of the next form
          \sa updateSample()
        */
        virtual bool                          getNextLabel(QString& strLabel)=0;
        QSqlRelationalTableModel*             m_model;/**< pointer for the main model in this form */
        QTableView*                           m_table;/**< pointer for the table in this form */
};
#endif //PREVIEWTAB_H
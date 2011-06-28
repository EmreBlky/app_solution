#ifndef SQL_H
#define SQL_H

//#include <QSqlDatabase>
//#include <QSqlError>
//#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QtSql>
#include <boost/shared_ptr.hpp>

using namespace boost;

#define MSQL_MAX 2147483647
#define MAX_SIZE 4000
/*!
    This file defines helper functions and constants for sql queries and XML
*/
static const char *COLLATE = 
     QT_TRANSLATE_NOOP("db", "COLLATE SQL_Latin1_General_CP1_CI_AS");//TODO: GET THIS FROM THE DB OR THE UI?

static const char *DEFAULTSCHEMA = 
     QT_TRANSLATE_NOOP("db", "dbo");

static const char *URI = 
     QT_TRANSLATE_NOOP("xml", "http://tempuri.org/");

static const char *SCHEMA = 
     QT_TRANSLATE_NOOP("xml", "http://www.w3.org/2001/XMLSchema");

static const char *TMPCHAR = 
     QT_TRANSLATE_NOOP("db", "_");

static QString bottomLevelTable=QObject::tr("Ref_Minor_Strata");//This is the default table for the bottom level, but we can change it within the regions UI

//! FK struct
/*! This structure represents a Foreign Key, with parent, child and respective keys
*/
struct FK {
    //! Constructor.
        /*!
          This is the constructor for a foreign key, that initializes all the member variables.
          \param parent parent table name
          \param child child table name
          \param parent key field on the parent
          \param child key field on the child
          \sa cell()
        */
    FK(const QString parent, const QString child, const QString parentkey, const QString childkey):
    m_parent(parent), m_child(child), m_parentkey(parentkey), m_childkey(childkey)
    {}
    //! Constructor.
        /*!
          Overriden empty constructor 
          \sa FK(const QString parent, const QString child, const QString parentkey const QString childkey)
        */
    FK()
    {}
   QString             m_parent;//!< parent table name
   QString             m_child;//!< child table name
   QString             m_parentkey;//!< parent key field
   QString             m_childkey;//!< child key field
};
//////////////////////////////////////////////////////////////////////////////
typedef QMultiMap<QString,FK>                   MapFK;//!< typedef for mapping foreign keys (with a name)

//! NodeRef struct
/*! This structure references a node (table, field) from an imported adjacency model,
that we want to convert to a nested set;
*/
struct NodeRef {
    //! Constructor.
        /*!
          This is the constructor for a NodeRef, that initializes all the member variables.
          \param table table name
          \param field field name
        */
    NodeRef(const QString table, const QString field):m_strTable(table),
        m_strField(field)
    {}
   QString             m_strTable;//!< table name
   QString             m_strField;//!< field name
};

typedef shared_ptr<NodeRef>                     nodeRefPtr;//!< typedef for a smart pointer containing a Node Reference Structure
typedef QHash<int,nodeRefPtr>                   HashNodeRef;//!< typedef for mapping Node References (key=level,value=NodeRef(table,field)

static bool getImportedName(const QString inName, QString& outName, bool& bExists)
{
    //! Get Imported Table Name
    /*!
    This function allows a rename of imported tables on the database, as long as they are
    in a certain list
    \param inName original table name, as string
    \param outName out: imported table name, as string
    \param bExists out: boolean to write if it found the table or not, in the list of imported tables
    \return boolean as success or failure
    */

    //if (inName.isEmpty()) return false;

    QSqlQuery query;
    QString strQuery=QObject::tr("SELECT original_name, imported_name FROM Info_Tables_Import WHERE original_name=:table");
    if (!query.prepare(strQuery)) return false;
    query.bindValue(QObject::tr(":table"),inName);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.first();
    if (query.numRowsAffected()>0)
        outName=query.record().value(QObject::tr("imported_name")).toString();
    else
        outName=inName;

    bExists=query.numRowsAffected()>0;
    return true;
}

static bool escapeSqlString(QString& inStr)
{
    //! Escape SQL string
    /*!
    This function escapes all necessary sql "non-friendly characters"!
    We are being very "economical" here, so we pass an input string address and
    change it within this function =:->.
    \param inStr in and out: address of a string containing the information that we want to correct
    \return boolean as success or failure
    */

    int found=inStr.indexOf(QObject::tr("'"));
    if (found!=-1)
        inStr.replace(QObject::tr("'"),QObject::tr("''"));
    return true;
}

static bool castBoolean(const QString inBool, QString& outBool)
{
    //! Cast Boolean to Bit
    /*!
    Sql Server does not have a boolean type, so we have to cast true and false
    to bit (0 or 1)
    \param inBool input boolean, as string
    \param outBool output boolean, as string
    \return boolean as success or failure
    */

    if (inBool.compare(QObject::tr("true"),Qt::CaseInsensitive)==0 ||
        inBool.compare(QObject::tr("1"))==0)
        outBool=QObject::tr("1");
    else if (inBool.compare(QObject::tr("false"),Qt::CaseInsensitive)==0 ||
        inBool.compare(QObject::tr("0"))==0)
        outBool=QObject::tr("0");
    else return false;

    return true;
}

static bool castDate(QString inDate, QString& outDate)
{
    //! Truncate datetimeoffset
    /*!
    This function truncates a Dateoffset string, and it transforms it into
    a datetime conform string; if the string is not a datetimeoffset, it does nothing with it!
    \param inDate in: original date string
    \param outDate out: address of a string to put the amended date
    \return boolean as success or failure
    */

    int found=inDate.indexOf(QObject::tr("+"));
    if (found!=-1) inDate.remove(found,inDate.length()-found);

    QString strQuery=QObject::tr("SELECT CAST('") + inDate + QObject::tr("' AS datetime)");
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()!=1) return false;
    query.first();
    outDate=query.value(0).toString();
    return true;
}

static bool getTypeInfo(const QString strTableName, const QString strFieldName, QSqlRecord& rec)
{
    QSqlQuery query;
    QString strQuery(QObject::tr("SELECT data_type 'datatype', numeric_precision, numeric_scale FROM information_schema.columns WHERE") +
        QObject::tr(" (table_name =:table AND column_name=:column)"));
    if (!query.prepare(strQuery)) return false;
    query.bindValue(QObject::tr(":table"),strTableName);
    query.bindValue(QObject::tr(":column"),strFieldName);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.first();

    rec=query.record();
    return true;
}

static bool getFieldPrecision(const QString strTableName, const QString strFieldName, QString& strPrecision, QString& strScale)
{
    QSqlRecord rec;
    if (!getTypeInfo(strTableName,strFieldName,rec)) return false;
    strPrecision=rec.value(rec.indexOf(QObject::tr("numeric_precision"))).toString();
    strScale=rec.value(rec.indexOf(QObject::tr("numeric_scale"))).toString();
    return true;
}

static bool getFieldType(const QString strTableName, const QString strFieldName, QString& strType)
{
    //! Get Field Type
    /*!
    This function executes a query to retrieve the sql type of a field
    \param strTableName binded parameter table name
    \param strFieldName binded parameter field name
    \param strType address of a string, to put the result (type)
    \return boolean as success or failure
    */

    QSqlRecord rec;
    if (!getTypeInfo(strTableName,strFieldName,rec)) return false;
    strType=rec.value(rec.indexOf(QObject::tr("datatype"))).toString();
    return true;
}

static bool dropConstraint(const QString strConstraint, const QString strTable)
{
    //! Drop Constraint
    /*!
    This function provides the removal of a named constraint, given a certain table
    name and constraint identifier (as string);
    \param strConstraint constraint name
    \param strTable table name
    \return boolean as success or failure
    */

    QSqlQuery query;
    QString strQuery(QObject::tr(
        "ALTER TABLE ") + strTable + QObject::tr(" DROP CONSTRAINT ") + strConstraint);
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    return query.exec();
}

static bool nullifyField(const QString strTable, const QString strField, const QString strType, bool bNullify=false)
{
    //! Set Field to Null (or not)
    /*!
    This function alters a table, to set a field to NULL (or not null);
    its mainly use for primary keys, as we cannot have primary keys on fields that allow nulls...
    \param strTable table name as string
    \param strField field name as string
    \param strType field data type (to put on the query)
    \param bNullify if set to false (default), it will make the field nullable; otherwise, it will make it non nullable!
    \return boolean as success or failure
    */

    QSqlQuery query;
    QString strQuery=QObject::tr("ALTER TABLE ") + strTable + QObject::tr(" ALTER COLUMN ") + strField +
        QObject::tr(" ") + strType +
        (!bNullify? QObject::tr(" NOT"): QObject::tr("")) + QObject::tr(" NULL");
    query.prepare(strQuery);
    query.setForwardOnly(true);
    return query.exec();
}

static bool fixStringMaximumLength(const QString strIn, QString &strOut, const bool bRead, const bool bRestrict=true)
{
    //! Fix the maximum length of a string
    /*!
    Sql server does not allow strings to exceed a 8000 maximum size.
    In case we must exceed this value we have to use "MAX"identifier: but do we really want to?
    \param strIn input maximum size (as string)
    \param strOut amended maximum size (as string)
    \param bRestrict if set to true, it will restrict the maximum size to a define value; otherwise, it will use MAX
    \param bRead if it is reading an XML it uses the SQL MAX identifier to insert it in the database; if it is writing, it writes SQL max size as we are using an int schema type
    \return boolean as success or failure
    */

    bool bOk;
    int num=QVariant(strIn).toInt(&bOk);
    if (!bOk) return false;
    if (num>=MAX_SIZE)
    {
        if (bRestrict) strOut=QVariant(MAX_SIZE).toString();
        else
            strOut=!bRead?QVariant(MSQL_MAX).toString(): QObject::tr("MAX");
    }
    else strOut=strIn;
    return true;
}

static bool dropTableIfExists(const QString strTableName)
{
    //! Drop Table if Exists
    /*!
    This function drops a table, in case it exists
    \param strTable table name
    \return bool as success or failure of the two operations
    */

    QString strQuery=QObject::tr(
        "IF EXISTS(SELECT name FROM sys.tables WHERE name LIKE '")
        + strTableName + QObject::tr("') BEGIN DROP TABLE ") + strTableName + 
        QObject::tr(" END");

    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    return query.exec();
}

static bool getObjects(QSqlQuery& query, const QString strTable=QString())
{
    //! Get Object Ids
    /*!
    This function queries system table sys.columns
    and grabs tablenames, column names and object ids (so that we can use it later on queries);
    \param query address if a query object
    \param strTable optional parameter, if we want to use this query to verify the existence of a certain table
    \return bool as success or failure of the two operations
    */

    QString strQuery;
    if (strTable.isEmpty()){
        strQuery=QObject::tr(
        "SELECT OBJECT_NAME(object_id) AS TableName, object_id, name, is_identity FROM sys.columns");
    }
    else
        strQuery=QObject::tr(
        "SELECT OBJECT_NAME(object_id) AS TableName, object_id, name, is_identity FROM sys.columns")
        +QObject::tr(" WHERE     (OBJECT_NAME(object_id) = '") + strTable + QObject::tr("')");

    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    return (strTable.isEmpty()?query.numRowsAffected()>0:true);
}

static bool getAutoIncrementInfo(const int objectID, QSqlQuery& query)
{
    //! Get Seed and Increment Step
    /*!
    This function is used to retrieve more information
    about identity columns; it retrieves the auto increment seed and auto increment step.
    n.b.: the values have to be casted to *integers* since they are SQL variants and will 
    come has byte arrays!!
    \param objectID object id
    \param query address if a query object
    \return bool as success or failure of the two operations
    */

    QString strQuery(QObject::tr(
        "SELECT CAST(seed_value AS decimal), CAST(increment_value AS decimal) FROM sys.identity_columns WHERE (object_id =:id)"
        ));
    if (!query.prepare(strQuery)) return false;
    query.bindValue(QObject::tr(":id"),objectID);
    query.setForwardOnly(true);
    return query.exec();
}

static bool getIsNullableAndDefault(const QString strTable, const QString strField,
                                    QSqlQuery& query)
{
    //! Get Info about Column
    /*!
    This function uses a query to find out if the column is nullable and 
    its default value (in case it has one!!)
    \param strTable table name
    \param strField field name
    \param query address if a query object
    \return bool as success or failure of the two operations
    */

    QString strQuery=QObject::tr(
    "SELECT     TABLE_NAME, COLUMN_NAME, COLUMN_DEFAULT, IS_NULLABLE, DATA_TYPE, CHARACTER_MAXIMUM_LENGTH"
    " FROM         INFORMATION_SCHEMA.COLUMNS"
    " WHERE     (TABLE_NAME LIKE :table) AND (COLUMN_NAME like :column)");

    if (!query.prepare(strQuery)) return false;

    query.bindValue(QObject::tr(":table"), strTable);
    query.bindValue(QObject::tr(":column"), strField);
    query.setForwardOnly(true);
    return query.exec();
}

static bool tableHasIdentity(const QString strTableName, bool& bIdentity)
{
    //! Identify Identity Column
    /*!
    This is a convenience function to identify if a table has identity column
    \param strTableName table name
    \param bIdentity address of a bool to put the result
    \sa identityName(const QString strTableName, QString& strField)
    */

    QSqlQuery query;
    QString strQuery=QObject::tr("SELECT OBJECTPROPERTY(object_id('") + 
        strTableName + QObject::tr("'), 'TableHasIdentity')");
    query.prepare(strQuery);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.first();
    bIdentity=query.value(0).toBool();
    return true;
}

static bool identityName(const QString strTableName, QString& strField)
{
    //! Identify Identity Column
    /*!
    This is a useful query to retrieve the identity column, of a given table
    (in case it has one); n.b.: use this together with tableHasIdentity(const QString strTableName, bool& bIdentity),
    once we don't support the results for tables with *no* identity column!
    \param strTableName table name
    \param strField address of a string, to put the identity table name
    \return bool as success or failure of the two operations
    \sa tableHasIdentity(const QString strTableName, bool& bIdentity)
    */
    QSqlQuery query;
    QString strQuery(QObject::tr(
    "select object_name(object_id),name from sys.identity_columns where objectproperty(object_id,'isusertable')=1 AND object_name(object_id)='")
    + strTableName + QObject::tr("'"));
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.first();
    strField=query.value(query.record().indexOf(QObject::tr("name"))).toString();
    return true;
}

static bool clearDBTable(const QString strTableName, bool bReseed=true)
{
    //! Delete Rows from Table
    /*!
    This function uses sql queries to clear a table from all rows, and reseed the identity column (or not)
    n.b.: queries do not support the binding of table names!
    \param strTableName table name
    \param bool reset the identity column
    \return bool as success or failure of the two operations
    */

    QSqlQuery query;
    QString strQuery=QObject::tr("DELETE FROM ");
    strQuery.append(strTableName);
    query.prepare(strQuery);
    query.setForwardOnly(true);

    bool bOk=query.exec();

    if (bReseed){
        //Reseed columns
        bool bIdentity;
        //Check if we have an identity column, first!
        if (!tableHasIdentity(strTableName,bIdentity)) return false;
        if (bIdentity){
            strQuery=QObject::tr("DBCC CHECKIDENT (");
            strQuery.append(strTableName);

            //We must check the starting seed before reseeding!
            QString strField;
            //Check identity field
            if (!identityName(strTableName,strField)) return false;

            //Grabbing the object id
            QSqlQuery idQuery;
            if (!getObjects(idQuery)) return false;

            int objectID=-1;
             while (idQuery.next()) {
                 if (idQuery.value(idQuery.record().indexOf(QObject::tr("TableName"))).toString()==strTableName
                     && idQuery.value(idQuery.record().indexOf(QObject::tr("name"))).toString()==strField){
                        objectID=idQuery.value(idQuery.record().indexOf(QObject::tr("object_id"))).toInt();
                        break;
                 }
             }
             if (objectID==-1) return false;

            //Get autoincrementinfo
             QSqlQuery seedQuery;
             if (!getAutoIncrementInfo(objectID, seedQuery)) return false;
             if (seedQuery.numRowsAffected()!=1) return false;
             seedQuery.first();
             int seed=seedQuery.value(0).toInt();//Casted seed value

             //We must pass the current value to the reseeder (seed-1)
             strQuery.append(QObject::tr(" , RESEED, ") + QVariant(seed-1).toString()
                 + QObject::tr(")"));
            query.prepare(strQuery);
            query.setForwardOnly(true);
            query.exec();
        }
    }

    return bOk;
}

static QString selectAllRecordsFromTable(const QString strTable)
{
    return QObject::tr("SELECT * FROM ") + strTable;
}

static QString identifyConstraint()
{
    //! identify Constraints
    /*!
    This query returns the constraint name, given a certain id (binded parameter)
      \return QString SQL query text as string
    */
    return QObject::tr(
    "SELECT sys.sysobjects.name as NAME, sys.sysobjects.xtype FROM sys.sysobjects INNER JOIN sys.sysforeignkeys ON sys.sysobjects.id = sys.sysforeignkeys.constid WHERE (sys.sysobjects.id = ?)"
);

}

static QString selectPKConstraints(const QString strTable=QString())
{
    //! Select PK Constraints
    /*!
    This query returns the FK constraints from a certain table
    \param strTable if this parameter is empty will return all constraints from the database
     \return QString SQL query text as string
    */
    if (!strTable.isEmpty() && !strTable.isNull())
        return QObject::tr(
"SELECT Col.COLUMN_NAME, Tab.CONSTRAINT_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS Tab INNER JOIN INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE AS Col ON Tab.CONSTRAINT_NAME = Col.CONSTRAINT_NAME AND Tab.TABLE_NAME = Col.TABLE_NAME WHERE (Tab.CONSTRAINT_TYPE = 'PRIMARY KEY ') AND (Col.TABLE_NAME = '")
+ strTable + QObject::tr("')");
    else
        return QObject::tr(
    "SELECT Col.COLUMN_NAME, Tab.CONSTRAINT_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS Tab INNER JOIN INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE AS Col ON Tab.CONSTRAINT_NAME = Col.CONSTRAINT_NAME AND Tab.TABLE_NAME = Col.TABLE_NAME WHERE (Tab.CONSTRAINT_TYPE = 'PRIMARY KEY ')"
    );
}

static QString selectFKConstraints(const QString strTable=QString(), bool bFK=true)
{
    //! Select Constraints
    /*!
    This query returns the FK constraints related to a certain table; having the table has
    primary or foreign is controlled by the bool bFK parameter (which defaults to true, so the table is Foreign).
    \param strTable if this parameter is empty will return all constraints from the database
    \param FK this parameter only makes sense when the query is refering to a certain table, and it controls
    whether we want to have it as foreign, or primary table;
     \return QString SQL query text as string
    */
    if (!strTable.isEmpty() && !strTable.isNull())
        return QObject::tr(
"SELECT FK.TABLE_NAME AS FK_Table, CU.COLUMN_NAME AS FK_Column, PK.TABLE_NAME AS PK_Table, PT.COLUMN_NAME AS PK_Column, C.CONSTRAINT_NAME AS Constraint_Name FROM INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS AS C INNER JOIN INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS FK ON C.CONSTRAINT_NAME = FK.CONSTRAINT_NAME INNER JOIN INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS PK ON C.UNIQUE_CONSTRAINT_NAME = PK.CONSTRAINT_NAME INNER JOIN INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS CU ON C.CONSTRAINT_NAME = CU.CONSTRAINT_NAME INNER JOIN (SELECT i1.TABLE_NAME, i2.COLUMN_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS i1 INNER JOIN INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS i2 ON i1.CONSTRAINT_NAME = i2.CONSTRAINT_NAME WHERE (i1.CONSTRAINT_TYPE = 'PRIMARY KEY')) AS PT ON PT.TABLE_NAME = PK.TABLE_NAME WHERE ")
 + (bFK?QObject::tr("FK.TABLE_NAME='"):QObject::tr("PK.TABLE_NAME='")) + strTable + QObject::tr("'");
    else
        return QObject::tr(
        "SELECT FK.TABLE_NAME AS FK_Table, CU.COLUMN_NAME AS FK_Column, PK.TABLE_NAME AS PK_Table, PT.COLUMN_NAME AS PK_Column, C.CONSTRAINT_NAME AS Constraint_Name FROM INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS AS C INNER JOIN INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS FK ON C.CONSTRAINT_NAME = FK.CONSTRAINT_NAME INNER JOIN INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS PK ON C.UNIQUE_CONSTRAINT_NAME = PK.CONSTRAINT_NAME INNER JOIN INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS CU ON C.CONSTRAINT_NAME = CU.CONSTRAINT_NAME INNER JOIN (SELECT i1.TABLE_NAME, i2.COLUMN_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS i1 INNER JOIN INFORMATION_SCHEMA.KEY_COLUMN_USAGE AS i2 ON i1.CONSTRAINT_NAME = i2.CONSTRAINT_NAME WHERE (i1.CONSTRAINT_TYPE = 'PRIMARY KEY')) AS PT ON PT.TABLE_NAME = PK.TABLE_NAME"
        );
}

static QString selectAllConstraints()
{
        return QObject::tr(
    "SELECT OBJECT_NAME(object_id) AS NameofConstraint, SCHEMA_NAME(schema_id) AS SchemaName, OBJECT_NAME(parent_object_id) AS TableName, type_desc AS ConstraintType FROM sys.objects WHERE (type_desc LIKE '%CONSTRAINT')"
    );
}

static bool createFKConstraint(const MapFK mapFK)
{
    QSqlQuery query;
    QString strSql;
     MapFK::const_iterator i;
     for (i = mapFK.constBegin(); i != mapFK.constEnd(); ++i){

         MapFK::iterator j = mapFK.find(i.key());
         QString strChildKeys, strParentKeys, strChild, strParent;
         strChild=(*j).m_child;
         strParent=(*j).m_parent;
         strSql=( QObject::tr("ALTER TABLE ")+ strChild +
             QObject::tr(" WITH CHECK ADD CONSTRAINT ") + i.key() + 
            QObject::tr(" FOREIGN KEY(") );

         while (j != mapFK.end() && j.key() == i.key()) {
             strChildKeys.append(j.value().m_childkey);
             strChildKeys.append(QObject::tr(","));
             strParentKeys.append(j.value().m_parentkey);
             strParentKeys.append(QObject::tr(","));
             ++j;
         }
         strParentKeys.remove(strParentKeys.length()-1,1);//remove last comma
         strChildKeys.remove(strChildKeys.length()-1,1);//remove last comma

        strSql.append(strChildKeys + QObject::tr(") REFERENCES ") + (strParent) + 
        QObject::tr(" (") + strParentKeys + QObject::tr(")") );

        query.prepare(strSql);
        query.setForwardOnly(true);
        if (!query.exec()){
            return false;
        }

     }
     return true;
}

static bool storeFKConstraints(const QString strTableName, const bool bFK, MapFK& mapFK)
{
    //TODO: add a description here later!

    //If there are any FK referencing this table, we *must* delete them first!
    QSqlQueryModel model;
    model.setQuery(selectFKConstraints(strTableName,bFK));

    //N.b.: always do this to force retrieving the column count, as the SQL server driver
    // has a limit of 256 rows!!!!
    while (model.canFetchMore())
    {
        model.fetchMore();
    }

    for (size_t i=0; i < (size_t)model.rowCount();++i){
        QSqlRecord rec=model.record(i);

        QString fkName=rec.value(QObject::tr("CONSTRAINT_NAME")).toString();
        mapFK.insert(fkName,FK(rec.value(QObject::tr("PK_Table")).toString(),
            rec.value(QObject::tr("FK_Table")).toString(),rec.value(QObject::tr("PK_Column")).toString(),
            rec.value(QObject::tr("FK_Column")).toString()));
    }

    return true;
}

static bool dropFKConstraints(const QString strTableName, const bool bFK)
{
    //TODO: add a description here later!

    //If there are any FK referencing this table, we *must* delete them first!
    QSqlQueryModel model;
    model.setQuery(selectFKConstraints(strTableName,bFK));

    //N.b.: always do this to force retrieving the column count, as the SQL server driver
    // has a limit of 256 rows!!!!
    while (model.canFetchMore())
    {
        model.fetchMore();
    }

    for (size_t i=0; i < (size_t)model.rowCount();++i){
        QSqlRecord rec=model.record(i);

        QString fkName=rec.value(QObject::tr("CONSTRAINT_NAME")).toString();
        if (!dropConstraint(fkName, rec.value(QObject::tr("FK_Table")).toString())) return false;
    }

    return true;
}

static bool verifyConstraintName(const QString inStr, QString& outStr)
{
    //! Amend Constraint Name
    /*!
    This function checks if this constraint name is already in use in the db, and it case
    it is, it renames it by appending an underscore; then it loops again, to see if the new name
    is also in use;
    \param inStr original constraint name
    \param outStr address of a string to put the new constraint name
    \return bool as success or failure
    */

    QSqlQueryModel model;
    model.setQuery(selectAllConstraints());

    //N.b.: always do this to force retrieving the column count, as the SQL server driver
    // has a limit of 256 rows!!!!
    while (model.canFetchMore())
    {
        model.fetchMore();
    }

    QString strFkName=inStr;
    size_t j=0;
    while (j < (size_t)model.rowCount()){
        QSqlRecord rec=model.record(j);
        if (rec.value(QObject::tr("NameofConstraint")).toString()==(strFkName)){
            strFkName.append(QObject::tr("_"));
            j=-1;//Search again from beginning
        }
        ++j;
    }
    outStr=strFkName;
    return true;
}

static bool getSchemaType(const QVariant type, const QMap<QString,QString>& mapQt2Xs, QString& strType)
{
    //! Return schema type from a Qt Type
    /*!
    This function maps the Qt data types into xml schema types
    n.b.: do not use tinyint types in the database, as they come converted as uint and will
    be mixed with booleans by qt! (maybe in the future we need to take the translation layer of
    types from Qt's "shoulders" and use a more precise method (for instance, query the database!)
    \param type in: QVariant type
    \par mapQt2Xs in: reference of a map, containing the conversion from Qt to Schema types
    \param strType out: string with a xs type
    \return bool as success or failure
    */

    QMap<QString, QString>::const_iterator it = mapQt2Xs.find(type.typeName());
    if (it == mapQt2Xs.end()) return false;//first check point
    strType=it.value();
    return !strType.isEmpty() && !strType.isNull();//second check point
}

static QString listCASImportTables(const QString strTable=QString())
{
    //! List CAS Tables
    /*!
    This function retrieves a query to list the original name of all the tables
    from CAS that we want to import
    \param strTable optional table name to filter query
    \return query string
    */

    return QObject::tr("SELECT original_name, imported_name FROM Info_Tables_Import") + 
        (strTable.isEmpty()?QObject::tr(""): QObject::tr(" WHERE original_name='")
        +strTable + QObject::tr("'"));
}

static bool getNullForType(const QString strType, const QString strInternalName, QString& outStrNull)
{
    //! Get Nulls Replacement
    /*!
    This function gets the designated value to replace a null in the database;
     Designated values are on table [Null_Replacements], referenced by an internal name and description
     to fit a variety of situations. Since null replacements take the data type of the field, we need 
     a range of null replacements to support many data types; at this moment supported types are:
     different flavours of char and int, float, decimal, datetime and bit (boolean).
     ; the desired internal_name of the null is given and it is calculated a 
     TODO: add time stamp!
    \param strType field type (to calculate appropriated name)
    \param strInternalName internal name of the null (on table [Null_Replacements]
    \param outStrNull out: string variable to put the null replacement in
    \return bool as success or failure;
    */
    QSqlQuery query;
    QString strQuery, strPar;

    if (strType.contains(QObject::tr("nvarchar")) || strType.contains(QObject::tr("varchar"))){
        strPar=QObject::tr("varchar");
    }
    else if (strType.compare(QObject::tr("nchar(3)"))==0 || strType.compare(QObject::tr("char(3)"))==0){
        strPar=QObject::tr("char3");
    }
    else if (strType.compare(QObject::tr("nchar(3)"))==0 || strType.compare(QObject::tr("char(3)"))==0){
        strPar=QObject::tr("char3");
    }
    else if (/*strType.compare(QObject::tr("smallint"))==0 || */strType.compare(QObject::tr("bigint"))==0
        || strType.compare(QObject::tr("int"))==0){
        strPar=QObject::tr("int");
    }
    else if (strType.compare(QObject::tr("smallint"))==0){
            strPar=QObject::tr("smallint");
    }
    else if (strType.compare(QObject::tr("datetime"))==0){
        strPar=QObject::tr("datetime");
    }
    else if (strType.compare(QObject::tr("bit"))==0 || strType.compare(QObject::tr("tinyint"))==0){
        strPar=QObject::tr("bit");
    }
    else if (strType.compare(QObject::tr("decimal"))==0/* || strType.compare(QObject::tr("float"))==0*/){
        strPar=QObject::tr("float");
    }
    else if ( strType.compare(QObject::tr("float"))==0 ){//we currently *DO NOT* support floats: only decimals!!!!
        return false;
    }
    else return false;

    strQuery=QObject::tr("SELECT ") + strPar + QObject::tr(" FROM GL_Null_Replacements WHERE internal_name='")
    + strInternalName + QObject::tr("'");
    query.prepare(strQuery);

    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()<1) return false;
    query.first();
    outStrNull=query.record().value(0).toString();
    return true;
}

static bool replaceNulls(const QString strTable, const QString strField, const QString strType, const QString strInternalName)
{
    //! Replace Nulls
    /*!
    This function performs an update on a certain table, and a certain field, in order to replace nulls
     for a value from table [Null_Replacements]; the desired internal_name of the null is given and it is calculated a 
     value, based on its type;
     Supported types are: nvarchar,varchar,nchar(3),char(3),int,smallint,decimal,bit,datetime.
     TODO: add time stamp!
    \param strTable table name
    \param strType field type (to calculate appropriated name)
    \param strInternalName internal name of the null (on table [Null_Replacements]
    \return bool as success or failure;
    */

    QString val;
    if (!getNullForType(strType,strInternalName,val)) return false;
    QString strQuery=QObject::tr("UPDATE ") + strTable + QObject::tr(" SET ") +
        strField + QObject::tr("='") + val + QObject::tr("' WHERE ") + strField + 
        QObject::tr(" IS NULL");

    QSqlQuery query;
    query.prepare(strQuery);

    query.setForwardOnly(true);
    if (!query.exec()) return false;

    return true;
}

static bool getFields(const QString strTable, QMap<QString,QString>& mapTypes, QMap<QString,int>& mapSizes)
{
    //TODO: Describe this!

    QSqlQuery query;
    QString strQuery=QObject::tr("select column_name,DATA_TYPE,CHARACTER_MAXIMUM_LENGTH from information_schema.columns where table_name = :table");
    if (!query.prepare(strQuery)) return false;
    query.bindValue(QObject::tr(":table"),strTable);
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    while (query.next()){
        mapTypes.insert(query.value(0).toString(),query.value(1).toString());
        mapSizes.insert(query.value(0).toString(),(size_t)query.value(2).toInt());
    }
    return true;
}

static bool getImportedFieldsDescription(const QString strTable, QMap<QString,QString>& mapTypes, QMap<QString,int>& mapSizes)
{
    //TODO: Describe this!
    QSqlQuery query;
    QString strQuery=QObject::tr("select field_name,original_type,original_size FROM Info_Fields where table_name = :table");
    if (!query.prepare(strQuery)) return false;
    query.bindValue(QObject::tr(":table"),strTable);
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    while (query.next()){
        mapTypes.insert(query.value(0).toString(),query.value(1).toString());
        mapSizes.insert(query.value(0).toString(),(size_t)query.value(2).toInt());
    }
    return true;
}

static QString alterNull(const QString strTable, const QString strField,
                         const QString strType, bool bNull=true){

    return QObject::tr("ALTER TABLE ") + strTable + QObject::tr(" ALTER COLUMN ") + strField +
        QObject::tr(" ")+
        strType + (!bNull? QObject::tr(" NOT "):QObject::tr(" ")) + QObject::tr("NULL");
}

static bool prepareAdjacencyTable(HashNodeRef& mapTablesFields)
{
    //Supported table structure to import: ID (nvarchar) field, Name, NameENG, Description

    //n.b.: respect this order!
    if (!dropTableIfExists(QObject::tr("##List_Conversion"))) return false;

    MapFK mapFK;
    if (!storeFKConstraints(QObject::tr("Tree"),false,mapFK)) return false;//We must store existing FK referencing this table, since we are going to remove them!
    if (!dropFKConstraints(QObject::tr("Tree"),false)) return false;

    if (!clearDBTable(QObject::tr("Tree"))) return false;
    if (!clearDBTable(QObject::tr("Node_Description"))) return false;

    QSqlQuery query, query2;
    QString strQuery;
    //Initialize Root on Node_description
    if (!query.prepare(QObject::tr("INSERT INTO Node_Description (name,name_eng) VALUES('Root','Root')"))) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    //Create TMP table and fill with the mapping between old codes and new codes
    if (!query.prepare(QObject::tr("CREATE TABLE ##List_Conversion( [id] [int] IDENTITY(1,1) NOT NULL, [table_name] [nvarchar](50) COLLATE SQL_Latin1_General_CP1_CI_AS NULL, [code] [int] NULL, CONSTRAINT [PK_List_Conversion] PRIMARY KEY CLUSTERED ( [id] ASC )WITH (PAD_INDEX = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY] ) ON [PRIMARY]"))) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (!query.prepare(QObject::tr("INSERT INTO ##List_Conversion (table_name,code) VALUES('Root',0)"))) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;

     HashNodeRef::const_iterator i = mapTablesFields.constBegin();
     while (i != mapTablesFields.constEnd()) {
         strQuery=QObject::tr("SELECT * FROM ") + i.value()->m_strTable;
        if (!query.prepare(strQuery)) return false;
        query.setForwardOnly(true);
        if (!query.exec()) return false;
        while (query.next()){
            strQuery=QObject::tr("INSERT INTO ##List_Conversion (table_name,code) VALUES('") + 
             i.value()->m_strTable + QObject::tr("',CAST(") + query.record().value(QObject::tr("id")).toString()+
             QObject::tr(" AS INT))");
            if (!query2.prepare(strQuery)) return false;
            query2.setForwardOnly(true);
            if (!query2.exec()) return false;
        }
        ++i;
     }

    query.prepare(QObject::tr("SELECT int FROM Null_Replacements WHERE internal_name='Missing'"));
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    query.first();
    QString strNull=query.value(0).toString();

    //Initialize Root on Tree
    if (!query.prepare(QObject::tr("INSERT INTO Tree (parent,lft,rgt,depth) VALUES(-1,") + strNull +
        QObject::tr(",") + strNull + QObject::tr(",") + strNull + QObject::tr(")"))) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    //First check nulls
    QString strType;
    //Turn off null clause
    QStringList treeFields;
    treeFields << QObject::tr("lft") << QObject::tr("rgt") << QObject::tr("depth");

    QStringList::const_iterator constIterator;
    for (constIterator = treeFields.constBegin(); constIterator != treeFields.constEnd();
        ++constIterator){
        if (!getFieldType(QObject::tr("Tree"),*constIterator,strType)) return false;
        strQuery=alterNull(QObject::tr("Tree"),*constIterator,strType,true);
        if (!query.prepare(strQuery)) return false;
        query.setForwardOnly(true);
        if (!query.exec()) return false;
    }

    //Fill node_description
    i = mapTablesFields.constBegin();
    while (i != mapTablesFields.constEnd()) {
             strQuery=
             QObject::tr("INSERT INTO node_description (name,name_eng,description,OLD_CODE) ")+
             QObject::tr("SELECT Name,NameENG,Description,ID FROM ") +
            i.value()->m_strTable;
             if (!query.prepare(strQuery)) return false;
             query.setForwardOnly(true);
             if (!query.exec()) return false;
             ++i;
    }

    //Fill Tree
    size_t ct=0;
    i = mapTablesFields.constBegin();
    while (i != mapTablesFields.constEnd()) {
                strQuery=QObject::tr("SELECT ") + i.value()->m_strField + QObject::tr(
                    " FROM ") + i.value()->m_strTable;
                if (!query.prepare(strQuery)) return false;
                query.setForwardOnly(true);
                if (!query.exec()) return false;
                while (query.next()){
                    if (ct>0){
                        HashNodeRef::const_iterator ii = i;
                        ii--;
                        strQuery=QObject::tr("INSERT INTO Tree (parent) SELECT id FROM ##List_Conversion WHERE CODE=")+
                            query.record().value(i.value()->m_strField).toString() + QObject::tr(" AND table_name like '") +
                            ii.value()->m_strTable + QObject::tr("'");
                    }else{
                        strQuery=QObject::tr("INSERT INTO Tree (parent) VALUES(1)");
                    }
                    if (!query2.prepare(strQuery)) return false;
                    query2.setForwardOnly(true);
                    if (!query2.exec()) return false;
                }

            ct++;
            ++i;
    }

     //Put nulls back, but first update...
    for (constIterator = treeFields.constBegin(); constIterator != treeFields.constEnd();
        ++constIterator){

            strQuery=QObject::tr("UPDATE Tree set ") + *constIterator + QObject::tr("='") + strNull + QObject::tr("' WHERE ") + *constIterator 
            + QObject::tr(" IS NULL");
        if (!query.prepare(strQuery)) return false;
        query.setForwardOnly(true);
        if (!query.exec()) return false;

        if (!getFieldType(QObject::tr("Tree"),*constIterator,strType)) return false;
        strQuery=alterNull(QObject::tr("Tree"),*constIterator,strType,false);
        if (!query.prepare(strQuery)) return false;
        query.setForwardOnly(true);
        if (!query.exec()) return false;
    }

    //Don't forget to remove the Temp Table!
    strQuery=QObject::tr("DROP TABLE ##List_Conversion");
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    //Don't forget to put the constraints back
    if (!createFKConstraint(mapFK)) return false;
    return true;
}

static bool convert2List(HashNodeRef mapTablesFields)
{
    if (!prepareAdjacencyTable(mapTablesFields)) return false;
    return true;
}

static bool updateDepth(const int id)
{
    //! Update Depth
    /*!
    This function fills the depth field, which reflects the indentation of the node on the hierarchy.
    It is stored in the db for information purposes 
    N.b: This function affects one record *only*!
    \par id id of the node.
    \return booleans as success or failure
    */

    QSqlQuery query;
    //Query for Depth
    QString strQuery=QObject::tr("SELECT COUNT(t2.id)-1 as depth, T1.id from Tree as T1, Tree as T2 WHERE ( (T1.lft BETWEEN t2.lft AND T2.rgt) AND T1.id=? ) GROUP BY T1.lft, T1.id");
    query.prepare(strQuery);
    query.addBindValue(id);
    query.setForwardOnly(true);
    query.exec();

    if (query.numRowsAffected()<1) return false;
    query.first();
    int result=query.value(query.record().indexOf(QObject::tr("depth"))).toInt();

    //Update
    strQuery=QObject::tr("UPDATE Tree Set depth=? WHERE id=?");
    query.prepare(strQuery);
    query.addBindValue(result);
    query.addBindValue(id);
    query.setForwardOnly(true);
    query.exec();

    return query.numRowsAffected()==1;
}

static bool list2Nested()
{
    QSqlQuery query;
    if (!query.prepare("list2Nested")) return false;
    if (!query.exec()) return false;

    //update depth
    if (!query.prepare(QObject::tr("SELECT id from TREE"))) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()<1) return false;
    while (query.next())
    {
        if (!updateDepth(query.record().value(QObject::tr("id")).toInt())) return false;
    }
    return true;
}

static bool getFieldDescriptionFromDB(const QString strTable, const QString strField, QSqlQuery& query)
{
    //! Get Field Description
    /*!
    This function selects one record on Info_Fields, providing the information to import a certain field
    into the DB;
    N.b: This function affects one record *only*!
    \par strTable table name
    \par strField field name
    \par query address of a query to put the result
    \return booleans as success or failure
    */

    QString strQuery=QObject::tr("SELECT * FROM Info_Fields WHERE table_name LIKE :table and field_name LIKE :field");
    if (!query.prepare(strQuery)) return false;
    query.bindValue(QObject::tr(":table"),strTable);
    query.bindValue(QObject::tr(":field"),strField);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    return query.numRowsAffected()==1;
}

static bool findNullReplacementFields(const QString strTable,
                        QHash<QString,QString>& nullValues)
{
    //TODO: add description
    QSqlQuery query;
    QString strSql=QObject::tr("SELECT field_name,NullValue from Info_Fields WHERE table_name=:table AND replaceNulls=1");
    if (!query.prepare(strSql)) return false;
    query.bindValue(QObject::tr(":table"),strTable);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()>0)
    {
        while (query.next()){
            nullValues.insert(query.record().value(0).toString(),query.record().value(1).toString());
        }
    }

    return true;
}

static bool selectValue(const QString strFieldOut, const QString strTable, const QHash<QString,QString>& mapFieldValue,
                        QSqlRecord& rec, bool bAppendQuotes=true){
    //! Select Value
    /*!
    This is an utility function that will provide the result of a simple SELECT+WHERE query;
    Its receives as parameters a field that will be returned on the result, a table name, and an hash that can
    contain multiple fields/values to build the query condition.
    \par strFieldOut field returned on the result
    \par strTable table name
    \par mapFieldValue hash containing WHERE parameteres (field,value) pairs
    \par rec out: record with the result
    \return booleans boolean indicating whether this table contains or not a "converted" ID field.
    */

    QSqlQuery query;
    QString strWHERE;
    QHash<QString, QString>::const_iterator i = mapFieldValue.constBegin();
    size_t ct=0;
    while (i != mapFieldValue.constEnd()) {
        if (ct) strWHERE.append(QObject::tr(" AND "));
        strWHERE.append(i.key() + QObject::tr("=") + (bAppendQuotes?QObject::tr("'"):QObject::tr("")) + i.value() +
            (bAppendQuotes?QObject::tr("'"):QObject::tr("")));
     ++i;
     ++ct;
    }

    QString strQuery=QObject::tr("SELECT ") + strFieldOut + QObject::tr(" FROM ") + strTable +
        QObject::tr(" WHERE ") + strWHERE;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()) return false;

    if (query.numRowsAffected()>0)
    {
        query.first();
        rec=query.record();
        return true;
    }
    return false;
}

static bool convert2PK(const QString strTable)
{
    //! Convert to Primary Key
    /*!
    This is a simple convenience function that indicates whether this table has a "converted" ID field;
    that is: a created autoincrement, identity field that will replace a now obsolete PK.
    n.b.: this function will return false, also if it cannot find the giventable in the list of imported tables...
    \par strTable table name
    \return booleans boolean indicating whether this table contains or not a "converted" ID field.
    */

    QString strQuery=QObject::tr("SELECT convertPK2Int FROM Info_Tables_Import WHERE imported_name=:table");
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.bindValue(QObject::tr(":table"),strTable);
    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()>0)
    {
        query.first();
        return query.record().value(0).toBool();
    }
    return false;
}

static bool renameColumn(const QString strTable, const QString strField, const QString strNewName)
{
    QString strQuery=QObject::tr("EXEC sp_rename '") + strTable + QObject::tr(".") + strField +
        QObject::tr("', '") + strNewName + QObject::tr("', 'COLUMN'");
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << strQuery << endl;
        return false;
    }
    return true;
}

static QString getDefaultCstrt(const QString strTable, const QString strField)
{
    return 
        QObject::tr("select t.name, c.name, d.name as constraint_name, d.definition from sys.tables t join sys.default_constraints d on d.parent_object_id = t.object_id join sys.columns c on c.object_id = t.object_id and c.column_id = d.parent_column_id where t.name = '") 
        + strTable + QObject::tr("' and c.name = '") + strField + QObject::tr("'");
}

static bool dropColumn(const QString strTable, const QString strField)
{
    QString strQuery=QObject::tr("ALTER TABLE ") + strTable + QObject::tr(" DROP COLUMN ") + strField;
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << strQuery << endl;
        return false;
    }
    return true;
}

static bool renameTable(const QString oldTableName, const QString newTableName)
{
    QString strQuery=QObject::tr("EXEC sp_rename '") + oldTableName + QObject::tr("', '") + newTableName
        + QObject::tr("'");
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << strQuery << endl;
        return false;
    }
    return true;
}

static bool copyTable(const QString strTableFrom, const QString strTableTo, bool bExists)
{
    QString strQuery;
    if (!bExists){
        strQuery=QObject::tr("SELECT * INTO ") + strTableTo +  QObject::tr(" FROM ") + strTableFrom;
    }
    else{
        QMap<QString,QString> mapTypes;
        QMap<QString,int> mapSizes;
        if (!getFields(strTableFrom,mapTypes,mapSizes)) return false;
        QString strFields;

        //In case the table has an identity column, we must identify it and exclude it from the inserts!
        QString strIdentity;
        bool bIdentity=false;
        if (!tableHasIdentity(strTableFrom,bIdentity)) return false;
        if (bIdentity){
            if (!identityName(strTableFrom,strIdentity)) return false;
        }

        QMap<QString, QString>::const_iterator i = mapTypes.constBegin();
        while (i != mapTypes.constEnd()) {
            if (i.key().compare(strIdentity)!=0){
                strFields.append(i.key());
                strFields.append(QObject::tr(","));
            }
             ++i;
        }
        strFields.remove(strFields.lastIndexOf(QObject::tr(",")),1);

        strQuery=QObject::tr("INSERT INTO ") + strTableTo + QObject::tr(" (") + strFields +
            QObject::tr(") SELECT ") + strFields + QObject::tr(" FROM ") + strTableFrom;
    }

    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << strQuery << endl;
        return false;
    }
    return true;
}

static bool generateTMPTableName(const QString instrTableName, QString& outStrTableName, bool bVerify=false)
{
    QSqlQuery query;
    outStrTableName=TMPCHAR + instrTableName;

    if (bVerify){
        //Create TMP table name, but first make sure it does not exist yet...
        if (!getObjects(query,outStrTableName)) return false;
        while (query.numRowsAffected()>0){
            outStrTableName=TMPCHAR + outStrTableName;
            if (!getObjects(query,outStrTableName)) return false;
        }
    }

    return true;
}

static bool fixQueryValue(const QString strType, QString& strVal)
{
    if ( strType==QObject::tr("nvarchar") || strType==QObject::tr("varchar") || strType==QObject::tr("char")
        || strType==QObject::tr("nchar")){
            if (!escapeSqlString(strVal)) return false;

                strVal.prepend(QObject::tr("'"));
                strVal.append(QObject::tr("'"));
        }
    else if (strType==QObject::tr("datetime")){
            QString strOut;
            if (!castDate(strVal,strOut))
                return false;
            strVal=strOut;
            strVal.prepend(QObject::tr("'"));
            strVal.append(QObject::tr("'"));
        }
    else if (strType==QObject::tr("bit")){
            QString strOut;
            if (!castBoolean(strVal,strOut))
                return false;
            strVal=strOut;
        }

    return true;
}

static bool getMappedTMPName(const QString inStrName, const QMap<QString,QString>& mapTMPNames, QString& outStrName)
{
    QMap<QString,QString>::iterator it=mapTMPNames.find(inStrName);
    if (it==mapTMPNames.end()) return false;
    outStrName=it.value();

    return true;
}

static bool getNullReplacements(QStringList& list){

    QString strQuery=QObject::tr("Select internal_name from GL_Null_Replacements WHERE internal_name <> 'misc'");
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << strQuery << endl;
        return false;
    }
    if (query.numRowsAffected()< 1) return false;
    while (query.next())
        list << query.record().value(0).toString();

    return true;
}

static bool GetCurentLocation(int& locationID)
{
    QString strQuery=
        QObject::tr("Select ID FROM Location WHERE IsCurrent=1");
    QSqlQuery query;
    if (!query.prepare(strQuery)) return false;
    query.setForwardOnly(true);
    if (!query.exec()){
        qDebug() << strQuery << endl;
        return false;
    }

    //We only allow one current location at a time
    if (query.numRowsAffected()!= 1) return false;
    query.first();
    locationID=query.record().value(QObject::tr("ID")).toInt();

    return true;
}

static bool getIdForValue(const QString strTable, const QString strIdField,
                                    const QString strPar, QString& strId)
{//!< This is a convenience function to retrieve the id of a given value!

    QSqlQuery query;
    if (!query.prepare(
        QObject::tr("SELECT ") + strIdField + QObject::tr(" FROM ") + strTable + QObject::tr(" WHERE (Name LIKE :par)"))) return false;
    query.bindValue(QObject::tr(":par"),strPar);

    query.setForwardOnly(true);
    if (!query.exec()|| query.numRowsAffected()!=1){
        return false;
    }

    query.first();//! Not to mention this is *very* important!!!
    strId=query.value(query.record().indexOf(strIdField)).toString();

    return true;
}

static QString countOcurrenciesForThisPort()
{
    return QObject::tr(
    "SELECT count(Ref_PSU.Name) FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID WHERE Ref_PSU.Name=:par"
    );
}

static QString checkActiveFromLastRecord()
{
    return QObject::tr(
"SELECT Top(1) ActiveVessels,TempRemoved FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID WHERE Ref_PSU.Name=:par ORDER by id_activity DESC"
    );
}

static QString checkIfPortHasVessels1(const QString strPsu)//OBSOLETE
{
    //N.b.: *the use of this function was descontinued, because we want to use binded queries instead!!!*

    //! Check if Port has Vessels -- first test
    /* This function was designed to test a given PSU, to find out whether it has already
    a record in CAS_Activity, and in case it has if it contains active vessels;
    if it contains active vessels it returns 1, otherwise it returns false;
    if there is no record in CAS_Activity, it also returns true;
    n.b.: unfortunately is impossible to have this query as cached...!
    \param strPsu Name of the samping unit
    \return QString as query string;
    */

    QString str= QObject::tr(

"declare @cnt int, @act int, @tempRem int, @sum int "
"set @cnt=(SELECT count(Ref_PSU.Name) FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID WHERE Ref_PSU.Name=:par) "
"if (@cnt>0) "
"Begin "
"    set @act=(SELECT Top(1) ActiveVessels FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID WHERE Ref_PSU.Name=:par ORDER by id_activity DESC) "
"    set @tempRem=(SELECT Top(1) TempRemoved FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID WHERE Ref_PSU.Name=:par ORDER by id_activity DESC) "
"    set @sum=@act + @tempRem "
"    if (@sum=0) select(0) else select(1) "
"End "
"else select (1)"

//"IF :par IN (SELECT distinct Ref_PSU.Name FROM Reg_Vessels INNER JOIN Ref_PSU ON HomePort=ID) BEGIN select (1) END ELSE BEGIN select (0) END"
//"IF :par IN (SELECT Name FROM CAS_Activity INNER JOIN Ref_PSU ON id_psu=ID) BEGIN select (1) END ELSE BEGIN select (0) END"
);

    str.replace(QObject::tr(":par"),QObject::tr("'") + strPsu + QObject::tr("'"));
    return str;
}

static QString checkIfPortHasVessels2()
{
    //! Check if Port has Vessels -- second test
    /* This function was designed find out if there are any vessels registered for this port;
    if it has any vessels it returns 1, otherwise it returns false;
    \return QString as query string;
    */

    return QObject::tr(
        "IF :par IN (SELECT distinct Ref_PSU.Name FROM Reg_Vessels INNER JOIN Ref_PSU ON HomePort=ID) select(1) else select(0) "
);
}

static bool getYearLimits(int& start, int&end)
{
    //We retrieve the last inserted limits that are active (in case there are more than 1)!
    QSqlQuery query;
    if (!query.prepare(
        QObject::tr("select Top(1) start_year,end_year from Ref_Year_Limits WHERE active=1 ORDER BY ID DESC"))) return false;

    query.setForwardOnly(true);
    if (!query.exec()|| query.numRowsAffected()!=1){
        return false;
    }

    query.first();//! Not to mention this is *very* important!!!
    start=query.value(0).toInt();
    end=query.value(1).toInt();

    return true;
}

static bool getLastIdActivity(QString& strId)
{
    //! Get Last id_activity
    /* This function find the last id_activity/last record on CAS_activity;
    \par strId address of a string, to put the result on;
    \return boolean as sucess or failure
    */

    QSqlQuery query;
    if (!query.prepare(
        QObject::tr("select Top(1) id_activity from CAS_Activity ORDER BY id_activity DESC"))) return false;

    query.setForwardOnly(true);
    if (!query.exec()|| query.numRowsAffected()!=1){
        return false;
    }

    query.first();//! Not to mention this is *very* important!!!
    strId=query.value(0).toString();

    return true;
}

static bool getLastRecordFromTable(const QString strId, const QString strTable, QSqlRecord & rec)
{
    //! Get Last record of a Given Table
    /* This function finds the last record of a given table, given an order ID (to apply the ORDER BY to)
    \par strId name of the id field
    \par strTable table name
    \par rec address if an QsqlRecord to put the result on
    \return boolean as sucess or failure
    */

    QSqlQuery query;
    if (!query.prepare(
        QObject::tr("select Top(1) * from ") + strTable + QObject::tr(" ORDER BY ") + 
        strId + QObject::tr(" DESC")
        )) return false;

    query.setForwardOnly(true);
    if (!query.exec()|| query.numRowsAffected()!=1){
        return false;
    }

    query.first();//! Not to mention this is *very* important!!!
    rec=query.record();

    return true;
}

static bool getNaRuleID(size_t& id)
{
    //! Get the ID of the 'n/a' rule
    /* This is a convenience function to grabb the ID of the rule that contains 'n/a';
    This rule is used to mark dummy trigger ptrs, that only store references to controls:
    in this way they can also be stored in the reference map.
    \par id size_t address, to put the id of the rule
    \return boolean as sucess or failure
    */

    QSqlQuery query;
    if (!query.prepare(
        QObject::tr("select id_rules from UI_Rules WHERE [rule] like 'n/a'"))) return false;

    query.setForwardOnly(true);
    if (!query.exec()|| query.numRowsAffected()!=1){
        return false;
    }

    query.first();//! Not to mention this is *very* important!!!
    id=(size_t)query.value(0).toInt();

    return true;
}

static QString selectPortsFromDifferentPsu(const QString idPsu)
{
    //! Select Ports from a different psu
    /* This is a query to look for ports that belong do a different Psu, and
    at the same time are being sampled by the logbook approach;
    This function was made obsolete in the current app since we retrieve this query
    from a view in the db.
    \par idPsu current psu
    \return QString query string
    */

        QString strQuery=QObject::tr(
        "SELECT     DISTINCT "
        "             A.HomePort, B.id_psu, B.name "
        "FROM         dbo.Reg_Vessels A INNER JOIN "
        "              dbo.Ref_Source ON A.VesselID = dbo.Ref_Source.VesselID "
        "                    INNER JOIN Ref_Ports B on A.HomePort=B.ID "
        " WHERE     (dbo.Ref_Source.IsLogBook = 1)  AND ((SELECT count(ID) from Ref_Ports WHEre B.id_psu<>PAR)>0)"
        );

        strQuery.replace(QObject::tr("PAR"),idPsu);
    return strQuery;
}

static QString viewVesselsFromAnotherPort(const QString idPsu)
{
    //! Select Other Ports
    /* This is a query to look for other ports that belong to the same Psu, and
    at the same time are being sampled by the logbook approach;
    This function was made obsolete in the current app since we retrieve this query
    from a view in the db.
    \par idPsu current psu
    \return QString query string
    */

    return QObject::tr(
        "SELECT     dbo.Ref_Source.VesselID, dbo.Reg_Vessels.UniqueRegistrationNumber, dbo.Reg_Vessels.Name, dbo.Reg_Vessels.MainGearType, "
        "                      dbo.Reg_Vessels.Flag, dbo.Reg_Vessels.HomePort, dbo.Reg_Vessels.Length, dbo.Reg_Vessels.EnginePower, dbo.Reg_Vessels.GT, "
        "                      dbo.Reg_Vessels.VesselType "
        "FROM         dbo.Reg_Vessels INNER JOIN "
        "                      dbo.Ref_Source ON dbo.Reg_Vessels.VesselID = dbo.Ref_Source.VesselID "
        "WHERE     (dbo.Reg_Vessels.HomePort NOT IN "
        "                          (SELECT     ID"
        "                            FROM          dbo.Ref_Ports"
        "                            WHERE      (id_psu = ") + idPsu + 
        QObject::tr(" ))) AND (dbo.Ref_Source.IsLogBook = 1)        ")
        ;
}

static QString updateMonthlyFrameWithAddedVessel()
{
    //! Add New Vessel to the Monthly Frame
    /* This is a query to update the monthly frame with a new vessel;
    The vessel is set up as permanently added (default), with an 'uknown' reason;
    you can amend this later, through the UI.
    n.b.: this is a binded query, to you need to bind a :par later, with the vesselID
    and also with Added and tempAdded ids!
    \return QString query string
    */

        return QObject::tr(
    "DECLARE @par int, @id_activity int, @added INT, @tempAdded INT; "
    "SET @par=:par "
    "SET @id_activity=(SELECT Top(1) id_activity from CAS_Activity ORDER BY id_activity DESC) "
    "IF(SELECT IsLogBook FROM Ref_Source WHERE VesselID=@par)=0 SET @added=1 "
    "ELSE SET @added=2;"
    "INSERT INTO CAS_MonthlyFrame (VesselID,id_activity,id_gear,id_operational_status,id_temp_removed,id_removed,id_secondary_gear,id_added,id_temp_added) "
    "SELECT @par,@id_activity,MainGearType,1,11,11,SecondaryGearType,@added,5 from Reg_Vessels WHERE VesselID=@par "
    );

}

static QString rebuildIndexesSql()
{
    return QObject::tr(
        "EXEC sp_MSforeachtable @command1=\"print '?' DBCC DBREINDEX ('?', ' ', 80)\""
        );
}

#endif


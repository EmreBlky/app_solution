#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

/*!
    This file defines a helper function to open a *default* connection to the Database.
    New connections must have a name!
*/

static bool createConnection(const QString strHost, const QString strData, const QString strUser,
                                            const QString strPass, const QString strAlias, const QString strDriver)
{
       QSqlDatabase db = QSqlDatabase::addDatabase( 
        /*QT_TR_NOOP("QODBC")*/strDriver);
        //db.setConnectOptions(QT_TR_NOOP("SQL_ATTR_ODBC_VERSION=SQL_OV_ODBC3"));
        db.setConnectOptions(QT_TR_NOOP("SQL_ATTR_LOGIN_TIMEOUT=1000,SQL_COPT_SS_MARS_ENABLED,SQL_MARS_ENABLED_YES,Mars_Connection=yes"));
        db.setHostName(strHost);
        QString strData2="DRIVER={SQL SERVER};SERVER="+ strHost + ";DATABASE=albania;UID=" + strUser + ";PWD=" + strPass;
        db.setDatabaseName(strData2);
        db.setUserName(strUser);
        db.setPassword(strPass);
        //Open the Database
        if  (!db.open()){
            QString error;
            error = db.lastError().text();
            qDebug() <<  error ;
            return false;
        }
    return true;
}

#endif

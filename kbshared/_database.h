/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#ifndef _database_H
#define _database_H


#include "../kbshared/typedef.h"


class _database 

{ 
public:

  
    static t_boolean METHOD_Exists(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port);
      
    static t_boolean METHOD_SetCurrentDatabase(QString Name);

    static QString METHOD_CurrentDatabase();

    static t_boolean METHOD_OpenSQLite(QString Name);

    static t_boolean METHOD_Open(QString Driver, QString Name, QString User, QString Password);

    static t_boolean METHOD_Open(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port);

    static t_boolean METHOD_Close(QString Name);

    static t_boolean METHOD_IsOpen(QString Name);

    static t_boolean METHOD_Create(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port);

    static QString METHOD_TestConnection(QString Driver, QString User, QString Password, QString Host, QString Options, QString Port);
    
    static t_boolean METHOD_Clear(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port);

    static t_boolean METHOD_Drop(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port);

    static t_boolean METHOD_Copy(QString Source, QString Destination);

    static QString METHOD_LastSQLError(QString Name);

    static QString METHOD_LastSQLCommands(QString Name);

    static QString METHOD_LastSQLCommandFailed(QString Name);

    //static QString METHOD_LastErrorText(QString Name);

    static t_boolean METHOD_IsTransactionSupported(QString Name);
    static t_boolean METHOD_Transaction(QString Name);
    static t_boolean METHOD_Commit(QString Name);
    static t_boolean METHOD_Rollback(QString Name);

    static _strings *METHOD_Tables(QString Name);

    static _strings *METHOD_Drivers();

    static QString METHOD_MySQL(){ return "QMYSQL"; }
    static QString METHOD_PostgreSQL(){ return "QPSQL"; }
    static QString METHOD_SQLite(){ return "QSQLITE"; }
    static QString METHOD_ODBC(){ return "QODBC"; }
    static QString METHOD_LocalHost(){ return "localhost"; }
    static QString METHOD_DefaultPort(){ return ""; }
    static QString METHOD_DefaultOptions(){ return ""; }


private:


};




#endif
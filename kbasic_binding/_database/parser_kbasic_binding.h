
new_class(pcode___database, 0, 0); 


    new_param("Driver", pcode__QSTRING, false);
    new_param("Name", pcode__QSTRING, false);
    new_param("User", pcode__QSTRING, false);
    new_param("Password", pcode__QSTRING, false);
    new_param("Host", pcode__QSTRING, true, "localhost");
    new_param("Port", pcode__QSTRING, true, "");
    new_param("Options", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_Exists, pcode__BOOLEAN);

    new_param("Name", pcode__QSTRING, false);
new_staticmethod(true, pcode___database, pcode___database__METHOD_SetCurrentDatabase, pcode__BOOLEAN);

new_staticmethod(true, pcode___database, pcode___database__METHOD_CurrentDatabase, pcode__QSTRING);

    new_param("Name", pcode__QSTRING, false);
new_staticmethod(true, pcode___database, pcode___database__METHOD_OpenSQLite, pcode__BOOLEAN);

    new_param("Driver", pcode__QSTRING, false);
    new_param("Name", pcode__QSTRING, false);
    new_param("User", pcode__QSTRING, false);
    new_param("Password", pcode__QSTRING, false);
new_staticmethod(true, pcode___database, pcode___database__METHOD_Open, pcode__BOOLEAN);

    new_param("Driver", pcode__QSTRING, false);
    new_param("Name", pcode__QSTRING, false);
    new_param("User", pcode__QSTRING, false);
    new_param("Password", pcode__QSTRING, false);
    new_param("Host", pcode__QSTRING, true, "localhost");
    new_param("Options", pcode__QSTRING, true, "");
    new_param("Port", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_Open1, pcode__BOOLEAN);

    new_param("Name", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_Close, pcode__BOOLEAN);

    new_param("Name", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_IsOpen, pcode__BOOLEAN);

    new_param("Driver", pcode__QSTRING, false);
    new_param("User", pcode__QSTRING, false);
    new_param("Password", pcode__QSTRING, false);
    new_param("Host", pcode__QSTRING, true, "localhost");
    new_param("Options", pcode__QSTRING, true, "");
    new_param("Port", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_TestConnection, pcode__QSTRING);

    new_param("Driver", pcode__QSTRING, false);
    new_param("Name", pcode__QSTRING, false);
    new_param("User", pcode__QSTRING, false);
    new_param("Password", pcode__QSTRING, false);
    new_param("Host", pcode__QSTRING, true, "localhost");
    new_param("Options", pcode__QSTRING, true, "");
    new_param("Port", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_Create, pcode__BOOLEAN);

    new_param("Driver", pcode__QSTRING, false);
    new_param("Name", pcode__QSTRING, false);
    new_param("User", pcode__QSTRING, false);
    new_param("Password", pcode__QSTRING, false);
    new_param("Host", pcode__QSTRING, true, "localhost");
    new_param("Options", pcode__QSTRING, true, "");
    new_param("Port", pcode__QSTRING, true, "");
    new_staticmethod(true, pcode___database, pcode___database__METHOD_Clear, pcode__BOOLEAN);

    new_param("Driver", pcode__QSTRING, false);
    new_param("Name", pcode__QSTRING, false);
    new_param("User", pcode__QSTRING, false);
    new_param("Password", pcode__QSTRING, false);
    new_param("Host", pcode__QSTRING, true, "localhost");
    new_param("Options", pcode__QSTRING, true, "");
    new_param("Port", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_Drop, pcode__BOOLEAN);

/*
    new_param("Source", pcode__QSTRING, false);
    new_param("Destination", pcode__QSTRING, false);
new_staticmethod(true, pcode___database, pcode___database__METHOD_Copy, pcode__BOOLEAN);
*/

    new_param("Name", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_LastSQLError, pcode__QSTRING);
    new_param("Name", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_LastSQLCommands, pcode__QSTRING);
    new_param("Name", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_LastSQLCommandFailed, pcode__QSTRING);
    //new_param("Name", pcode__QSTRING, false);
//new_staticmethod(true, pcode___database, pcode___database__METHOD_LastErrorText, pcode__QSTRING);

    new_param("Name", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_IsTransactionSupported, pcode__BOOLEAN);
    new_param("Name", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_Transaction, pcode__BOOLEAN);
    new_param("Name", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_Commit, pcode__BOOLEAN);
    new_param("Name", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_Rollback, pcode__BOOLEAN);

    new_param("Name", pcode__QSTRING, true, "");
new_staticmethod(true, pcode___database, pcode___database__METHOD_Tables, pcode___strings);
new_staticmethod(true, pcode___database, pcode___database__METHOD_Drivers, pcode___strings);

new_staticmethod(true, pcode___database, pcode___database__METHOD_MySQL, pcode__QSTRING);
new_staticmethod(true, pcode___database, pcode___database__METHOD_PostgreSQL, pcode__QSTRING);
new_staticmethod(true, pcode___database, pcode___database__METHOD_SQLite, pcode__QSTRING);
new_staticmethod(true, pcode___database, pcode___database__METHOD_ODBC, pcode__QSTRING);
new_staticmethod(true, pcode___database, pcode___database__METHOD_LocalHost, pcode__QSTRING);
new_staticmethod(true, pcode___database, pcode___database__METHOD_DefaultPort, pcode__QSTRING);
new_staticmethod(true, pcode___database, pcode___database__METHOD_DefaultOptions, pcode__QSTRING);

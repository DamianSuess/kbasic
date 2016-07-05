
new_class(pcode___record, 0, 0); 


    new_param("Database", pcode__QSTRING, false);
    new_param("TableOrSql", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Open, pcode__QSTRING);

    new_param("Database", pcode__QSTRING, false);
    new_param("Table", pcode__QSTRING, false);
    new_param("Where", pcode___array, false);
    new_param("OrderBy", pcode___array, true, 0);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Open1, pcode__QSTRING);
/*
    new_param("Database", pcode__QSTRING, false);
    new_param("Tables", pcode___strings, false);
    new_param("Where", pcode___array, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Open2, pcode__QSTRING);

*/
    new_param("TableOrSql", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Open3, pcode__QSTRING);

    new_param("Table", pcode__QSTRING, false);
    new_param("Where", pcode___array, false);
    new_param("OrderBy", pcode___array, true, 0);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Open4, pcode__QSTRING);
/*
    new_param("Tables", pcode___strings, false);
    new_param("Where", pcode___array, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Open5, pcode__QSTRING);
*/
    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Close, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Requery, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_First, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Next, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Previous, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Last, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
    new_param("Position", pcode__INTEGER, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_GoTo, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Length, pcode__INTEGER);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Position, pcode__INTEGER);
/*
    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_AddNew, pcode__BOOLEAN);
*/
    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Insert, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Update, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Delete, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Clear, pcode__BOOLEAN);

    new_param("QueryId", pcode__QSTRING, false);
    new_param("Field", pcode__QSTRING, false);
    new_param("Value", pcode__VARIANT, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Set, pcode__VOID);

    new_param("QueryId", pcode__QSTRING, false);
    new_param("Field", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Get, pcode__VARIANT);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_Fields, pcode___strings);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_PrimaryKeyName, pcode__QSTRING);

    new_param("QueryId", pcode__QSTRING, false);
new_staticmethod(true, pcode___record, pcode___record__METHOD_PrimaryKey, pcode__INTEGER);

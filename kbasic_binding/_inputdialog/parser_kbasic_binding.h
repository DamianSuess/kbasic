
new_class(pcode___inputdialog, 0, 0); 


    new_param("Caption", pcode__QString, false);
    new_param("Text", pcode__QString, true, "");
    new_param("Value", pcode__DOUBLE, true, 0);
    new_param("Minimum", pcode__DOUBLE, true, -2147483647);
    new_param("Maximum", pcode__DOUBLE, true, 2147483647);
    new_param("Decimals", pcode__INTEGER, true, 1);
new_staticmethod(true, pcode___inputdialog, pcode___inputdialog__METHOD_GetDouble, pcode__DOUBLE);

    new_param("Caption", pcode__QString, false);
    new_param("Text", pcode__QString, true, "");
    new_param("Value", pcode__INTEGER, true, 0);
    new_param("Minimum", pcode__INTEGER, true, -2147483647);
    new_param("Maximum", pcode__INTEGER, true, 2147483647);
    new_param("Step", pcode__INTEGER, true, 1);
new_staticmethod(true, pcode___inputdialog, pcode___inputdialog__METHOD_GetInteger, pcode__INTEGER);

/*
    new_param("Caption", pcode__QString, false);
    new_param("LabelCaption", pcode__QString, true, "");
    new_param("Strings", pcode___strings, false, 0);
    new_param("Current", pcode__INTEGER, true, 1);
    new_param("Editable", pcode__BOOLEAN, true, false);
new_staticmethod(true, pcode___inputdialog, pcode___inputdialog__METHOD_GetItem, pcode__QString);
*/

    new_param("Caption", pcode__QString, false);
    new_param("Text", pcode__QString, true, "");
    new_param("Value", pcode__QString, true, "");
    new_param("EchoMode", pcode__QString, true, "Normal");
new_staticmethod(true, pcode___inputdialog, pcode___inputdialog__METHOD_GetString, pcode__QString);

new_staticmethod(true, pcode___inputdialog, pcode___inputdialog__METHOD_Ok, pcode__BOOLEAN);

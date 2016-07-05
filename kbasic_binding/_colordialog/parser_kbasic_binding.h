
new_class(pcode___colordialog, 0, 0); 


new_staticmethod(true, pcode___colordialog, pcode___colordialog__METHOD_GetColor, pcode__BOOLEAN);
/*
    new_param("Color", pcode__QString, false);
new_staticmethod(true, pcode___colordialog, pcode___colordialog__METHOD_GetColor1, pcode__QString);
*/

    new_param("Red", pcode__INTEGER, false);
    new_param("Green", pcode__INTEGER, false);
    new_param("Blue", pcode__INTEGER, false);
    new_param("Alpha", pcode__INTEGER, false);
new_staticmethod(true, pcode___colordialog, pcode___colordialog__METHOD_GetColor1, pcode__BOOLEAN);

new_staticmethod(true, pcode___colordialog, pcode___colordialog__METHOD_Red, pcode__INTEGER);
new_staticmethod(true, pcode___colordialog, pcode___colordialog__METHOD_Green, pcode__INTEGER);
new_staticmethod(true, pcode___colordialog, pcode___colordialog__METHOD_Blue, pcode__INTEGER);
new_staticmethod(true, pcode___colordialog, pcode___colordialog__METHOD_Alpha, pcode__INTEGER);

/*
new_staticmethod(true, pcode___colordialog, pcode___colordialog__METHOD_CustomCount, pcode__INTEGER);

    new_param("Number", pcode__INTEGER, false);
    new_param("Color", pcode__QString, false);
new_staticmethod(true, pcode___colordialog, pcode___colordialog__METHOD_SetCustomColor, pcode__VOID);

    new_param("Number", pcode__INTEGER, false);
    new_param("Color", pcode__QString, false);
new_staticmethod(true, pcode___colordialog, pcode___colordialog__METHOD_SetStandardColor, pcode__VOID);

*/
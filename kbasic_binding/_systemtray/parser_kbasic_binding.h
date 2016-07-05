
new_class(pcode___systemtray, 0, 0); 


new_staticmethod(true, pcode___systemtray, pcode___systemtray__METHOD_IsSystemTrayAvailable, pcode__BOOLEAN);
new_staticmethod(true, pcode___systemtray, pcode___systemtray__METHOD_IsPrintSupported, pcode__BOOLEAN);



   new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___systemtray, pcode___systemtray__METHOD_Print, pcode__VOID);


   new_param("Text", pcode__QString, false);
   new_param("Title", pcode__QString, false);
new_staticmethod(true, pcode___systemtray, pcode___systemtray__METHOD_Print1, pcode__VOID);


   new_param("Text", pcode__QString, false);
   new_param("Title", pcode__QString, false);
   new_param("PrintIcon", pcode__QString, false);
new_staticmethod(true, pcode___systemtray, pcode___systemtray__METHOD_Print2, pcode__VOID);


   new_param("Text", pcode__QString, false);
   new_param("Title", pcode__QString, false);
   new_param("PrintIcon", pcode__QString, false);
   new_param("TimeOut", pcode__INTEGER, false);
new_staticmethod(true, pcode___systemtray, pcode___systemtray__METHOD_Print3, pcode__VOID);

new_staticmethod(true, pcode___systemtray, pcode___systemtray__METHOD_Show, pcode__VOID);
new_staticmethod(true, pcode___systemtray, pcode___systemtray__METHOD_Hide, pcode__VOID);
new_staticmethod(true, pcode___systemtray, pcode___systemtray__METHOD_ToggleVisible, pcode__VOID);


	 new_param("MenuBarItemName", pcode__QString, false);
new_staticproperty_set(pcode___systemtray, pcode___systemtray__PROPERTYSET_ContextMenu, pcode__VOID);
new_staticproperty_get(pcode___systemtray, pcode___systemtray__PROPERTYGET_ContextMenu, pcode__QString);


	 new_param("FileName", pcode__QString, false);
new_staticproperty_set(pcode___systemtray, pcode___systemtray__PROPERTYSET_Icon, pcode__VOID);
new_staticproperty_get(pcode___systemtray, pcode___systemtray__PROPERTYGET_Icon, pcode__QString);

	 new_param("Text", pcode__QString, false);
new_staticproperty_set(pcode___systemtray, pcode___systemtray__PROPERTYSET_ToolTip, pcode__VOID);
new_staticproperty_get(pcode___systemtray, pcode___systemtray__PROPERTYGET_ToolTip, pcode__QString);

	 new_param("YesNo", pcode__BOOLEAN, false);
new_staticproperty_set(pcode___systemtray, pcode___systemtray__PROPERTYSET_Visible, pcode__VOID);
new_staticproperty_get(pcode___systemtray, pcode___systemtray__PROPERTYGET_Visible, pcode__BOOLEAN);


	// new_param("X", pcode__INTEGER, false);
//new_staticproperty_set(pcode___systemtray, pcode___systemtray__PROPERTYSET_GlobalX, pcode__VOID);
new_staticproperty_get(pcode___systemtray, pcode___systemtray__PROPERTYGET_GlobalX, pcode__INTEGER);
	 //new_param("Y", pcode__INTEGER, false);
//new_staticproperty_set(pcode___systemtray, pcode___systemtray__PROPERTYSET_GlobalY, pcode__VOID);
new_staticproperty_get(pcode___systemtray, pcode___systemtray__PROPERTYGET_GlobalY, pcode__INTEGER);
	 //new_param("Width", pcode__INTEGER, false);
//new_staticproperty_set(pcode___systemtray, pcode___systemtray__PROPERTYSET_Width, pcode__VOID);
new_staticproperty_get(pcode___systemtray, pcode___systemtray__PROPERTYGET_Width, pcode__INTEGER);
	 //new_param("Height", pcode__INTEGER, false);
//new_staticproperty_set(pcode___systemtray, pcode___systemtray__PROPERTYSET_Height, pcode__VOID);
new_staticproperty_get(pcode___systemtray, pcode___systemtray__PROPERTYGET_Height, pcode__INTEGER);



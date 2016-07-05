
new_class(pcode___mainwindow, 0, 0); 

     new_param("Visible", pcode__BOOLEAN, false);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_SetVisible, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_IsVisible, pcode__BOOLEAN);

     new_param("X", pcode__INTEGER, false);
     new_param("Y", pcode__INTEGER, false);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_Move, pcode__VOID);

     new_param("Width", pcode__INTEGER, false);
     new_param("Height", pcode__INTEGER, false);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_Resize, pcode__VOID);



new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_SetFocusNextForm, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_SetFocusPreviousForm, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_Cascade, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_Close, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_CloseActiveForm, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_CloseAllapplication, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_Tile, pcode__VOID);
   new_param("B", pcode__BOOLEAN, false);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_SetScrollBarsEnabled, pcode__VOID);

   new_param("ViewMode", pcode__QString, false);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_SetViewMode, pcode__VOID);

new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_ViewMode, pcode__QString);


   new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_SetCaption, pcode__VOID);

   new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_SetIcon, pcode__VOID);

	 new_param("X", pcode__INTEGER, false);
new_staticproperty_set(pcode___mainwindow, pcode___mainwindow__PROPERTYSET_X, pcode__VOID);
new_staticproperty_get(pcode___mainwindow, pcode___mainwindow__PROPERTYGET_X, pcode__INTEGER);
	 new_param("Y", pcode__INTEGER, false);
new_staticproperty_set(pcode___mainwindow, pcode___mainwindow__PROPERTYSET_Y, pcode__VOID);
new_staticproperty_get(pcode___mainwindow, pcode___mainwindow__PROPERTYGET_Y, pcode__INTEGER);
	 new_param("Width", pcode__INTEGER, false);
new_staticproperty_set(pcode___mainwindow, pcode___mainwindow__PROPERTYSET_Width, pcode__VOID);
new_staticproperty_get(pcode___mainwindow, pcode___mainwindow__PROPERTYGET_Width, pcode__INTEGER);
	 new_param("Height", pcode__INTEGER, false);
new_staticproperty_set(pcode___mainwindow, pcode___mainwindow__PROPERTYSET_Height, pcode__VOID);
new_staticproperty_get(pcode___mainwindow, pcode___mainwindow__PROPERTYGET_Height, pcode__INTEGER);

new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_ShowFullScreen, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_ShowMaximized, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_ShowMinimized, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_ShowNormal, pcode__VOID);
new_staticmethod(true, pcode___mainwindow, pcode___mainwindow__METHOD_IsScrollBarsEnabled, pcode__BOOLEAN);


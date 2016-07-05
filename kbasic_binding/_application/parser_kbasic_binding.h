
new_class(pcode___application, 0, 0); 

   new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_PlaySound, pcode__VOID);

   new_param("FileName", pcode__QString, false);
   new_param("KeyAndMouseCanCancel", pcode__BOOLEAN, true, true);
new_staticmethod(true, pcode___application, pcode___application__METHOD_PlayMovie, pcode__VOID);

new_staticmethod(true, pcode___application, pcode___application__METHOD_AvailableLanguages, pcode___strings);

   new_param("Language", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetLanguage, pcode__VOID);

   new_param("MimeType", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_IsMimeTypeAvailable, pcode__BOOLEAN);

new_staticmethod(true, pcode___application, pcode___application__METHOD_AvailableMimeTypes , pcode___strings);

   new_param("Filename", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_LoadProjectFileAsString, pcode__QString);

   new_param("Filename", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_LoadProjectFileAsBinary, pcode__QString);

   new_param("Filename", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_LoadFileAsString, pcode__QString);

   new_param("Filename", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_LoadURLAsBinary, pcode__QString);

     new_param("X", pcode__INTEGER, false);
     new_param("Y", pcode__INTEGER, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_Move, pcode__VOID);

     new_param("Width", pcode__INTEGER, false);
     new_param("Height", pcode__INTEGER, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_Resize, pcode__VOID);

new_staticmethod(true, pcode___application, pcode___application__METHOD_Close, pcode__VOID);

new_staticmethod(true, pcode___application, pcode___application__METHOD_QtVersion, pcode__QString);

new_staticmethod(true, pcode___application, pcode___application__METHOD_OperatingSystemName, pcode__QString);

   new_param("Filename", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetDefaultIcon, pcode__VOID);

   new_param("Filename", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_ExternalOpenFile, pcode__VOID);

new_staticmethod(true, pcode___application, pcode___application__METHOD_CloseAllWindows, pcode__VOID);

new_staticmethod(true, pcode___application, pcode___application__METHOD_IsLayoutDirection, pcode__BOOLEAN);

new_staticmethod(true, pcode___application, pcode___application__METHOD_CurrentForm, pcode___form);

new_staticmethod(true, pcode___application, pcode___application__METHOD_FocusControl, pcode___control);

   new_param("Style", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetStyle, pcode__VOID);




new_staticmethod(true, pcode___application, pcode___application__METHOD_SetFocusNextForm, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetFocusPreviousForm, pcode__VOID);

new_staticmethod(true, pcode___application, pcode___application__METHOD_Cascade, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_CloseActiveForm, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_CloseAllapplication, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_Tile, pcode__VOID);
   new_param("B", pcode__BOOLEAN, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetScrollBarsEnabled, pcode__VOID);

   new_param("ViewMode", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetViewMode, pcode__VOID);

new_staticmethod(true, pcode___application, pcode___application__METHOD_ViewMode, pcode__QString);


	 new_param("X", pcode__INTEGER, false);
new_staticproperty_set(pcode___application, pcode___application__PROPERTYSET_X, pcode__VOID);
new_staticproperty_get(pcode___application, pcode___application__PROPERTYGET_X, pcode__INTEGER);
	 new_param("Y", pcode__INTEGER, false);
new_staticproperty_set(pcode___application, pcode___application__PROPERTYSET_Y, pcode__VOID);
new_staticproperty_get(pcode___application, pcode___application__PROPERTYGET_Y, pcode__INTEGER);
	 new_param("Width", pcode__INTEGER, false);
new_staticproperty_set(pcode___application, pcode___application__PROPERTYSET_Width, pcode__VOID);
new_staticproperty_get(pcode___application, pcode___application__PROPERTYGET_Width, pcode__INTEGER);
	 new_param("Height", pcode__INTEGER, false);
new_staticproperty_set(pcode___application, pcode___application__PROPERTYSET_Height, pcode__VOID);
new_staticproperty_get(pcode___application, pcode___application__PROPERTYGET_Height, pcode__INTEGER);

new_staticmethod(true, pcode___application, pcode___application__METHOD_ShowFullScreen, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_ShowMaximized, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_ShowMinimized, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_ShowNormal, pcode__VOID);

	 new_param("Title", pcode__QString, false);
	 new_param("Caption", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_MsgBox, pcode__VOID);
	 new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetCaption, pcode__VOID);
	 new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetIcon, pcode__VOID);
	 new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetClipboardText, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_ClipboardText, pcode__QString);
new_staticmethod(true, pcode___application, pcode___application__METHOD_Path, pcode__QString);
new_staticmethod(true, pcode___application, pcode___application__METHOD_DirectoryName, pcode__QString);
new_staticmethod(true, pcode___application, pcode___application__METHOD_FileName, pcode__QString);
new_staticmethod(true, pcode___application, pcode___application__METHOD_ArgumentsAsString, pcode__QString);


new_staticmethod(true, pcode___application, pcode___application__METHOD_Arguments, pcode___strings);
new_staticmethod(true, pcode___application, pcode___application__METHOD_IsScrollBarsEnabled, pcode__BOOLEAN);

new_staticmethod(true, pcode___application, pcode___application__METHOD_Run, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_Stop, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetWaitCursor, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_UnsetWaitCursor, pcode__VOID);
	 new_param("k", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_AddLanguageTranslatorFile, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_DoEvents, pcode__VOID);
	 new_param("k", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetLanguage, pcode__VOID);
	 new_param("k", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetCountry, pcode__VOID);
	 new_param("k", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetStyleSheet, pcode__VOID);
	 new_param("k", pcode__t_boolean, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_SetLayoutDirection, pcode__VOID);
new_staticmethod(true, pcode___application, pcode___application__METHOD_ScreenWidth, pcode__t_integer);
new_staticmethod(true, pcode___application, pcode___application__METHOD_ScreenHeight, pcode__t_integer);
	 new_param("k", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_LoadExternalBrowserWithHTML, pcode__VOID);



new_staticmethod(true, pcode___application, pcode___application__METHOD_TakeScreenShot, pcode__QString);

	 new_param("Name", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_StandardIcon, pcode__QString);

new_staticmethod(true, pcode___application, pcode___application__METHOD_AvailableFontNames, pcode___strings);
new_staticmethod(true, pcode___application, pcode___application__METHOD_ProcessId, pcode__LONG);

	 new_param("Html", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_PrintHtml, pcode__VOID);

	 new_param("Html", pcode__QString, false);
	 new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___application, pcode___application__METHOD_PrintHtmlAsPdf, pcode__VOID);

new_staticmethod(true, pcode___application, pcode___application__METHOD_QtException, pcode__QString);
new_staticmethod(true, pcode___application, pcode___application__METHOD_ClearQtException, pcode__VOID);

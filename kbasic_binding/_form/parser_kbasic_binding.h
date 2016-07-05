
new_class(pcode___form, pcode___control, 0); 

new_method(true, pcode___form, pcode___form___form, pcode___form);

 
new_method(true, pcode___form, pcode___form__METHOD_Hwnd, pcode__t_long);

   new_param("ControlName", pcode__QString, false);
   new_param("ControlType", pcode__QString, false);
   new_param("ControlGroup", pcode__QString, false);
   new_param("X", pcode__INTEGER, false);
   new_param("Y", pcode__INTEGER, false);
   new_param("Width", pcode__INTEGER, false);
   new_param("Height", pcode__INTEGER, false);
   new_param("Visible", pcode__BOOLEAN, false);
new_method(true, pcode___form, pcode___form__METHOD_Append, pcode__t_boolean);


   new_param("ControlName", pcode__QString, false);
   new_param("ControlType", pcode__QString, false);
   new_param("ControlGroup", pcode__QString, false);
   new_param("X", pcode__INTEGER, false);
   new_param("Y", pcode__INTEGER, false);
   new_param("Width", pcode__INTEGER, false);
   new_param("Height", pcode__INTEGER, false);
   new_param("Visible", pcode__BOOLEAN, false);
new_method(true, pcode___form, pcode___form__METHOD_Insert1, pcode__t_boolean);

   new_param("ControlName", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_Remove, pcode__t_boolean);

   new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MouseTracking, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MouseTracking, pcode__t_boolean);

 
   new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MoveOnMouseDrag, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MoveOnMouseDrag, pcode__t_boolean);


new_method(true, pcode___form, pcode___form__EVENT_OnDockMove, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnDockShow, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnDockHide, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnDockFloating, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnDockNotFloating, pcode__VOID, false, false, false, true);

 /*
new_method(true, pcode___form, pcode___form__METHOD_DockIsLeft, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_DockIsRight, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_DockIsTop, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_DockIsBottom, pcode__t_boolean);


new_method(true, pcode___form, pcode___form__METHOD_DockSetLeft, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_DockSetRight, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_DockSetTop, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_DockSetBottom, pcode__VOID);
*/

   new_param("FormName", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DockTabify, pcode__VOID);

   new_param("FormName", pcode__QString, false);
   new_param("Direction", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DockSplit, pcode__VOID);

   new_param("FormName", pcode__t_boolean, false);
new_method(true, pcode___form, pcode___form__METHOD_DockSetFloating, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_DockIsFloating, pcode__t_boolean);

   new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_DockSplit, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_DockSplit, pcode__QString);

 
new_method(true, pcode___form, pcode___form__METHOD_OpenMaximized, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_OpenMinimized, pcode__VOID);
/*
new_method(true, pcode___form, pcode___form__METHOD_OpenCenteredOnlyOnce, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_OpenOnlyOnce, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_OpenHiddenOnlyOnce, pcode__VOID);
*/

new_method(true, pcode___form, pcode___form__METHOD_ControlFocus, pcode___control);
new_method(true, pcode___form, pcode___form__METHOD_ControlFocusNext, pcode___control);
new_method(true, pcode___form, pcode___form__METHOD_ControlSetFocusNext, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_ControlSetFocusPrevious, pcode__t_boolean);
//new_method(true, pcode___form, pcode___form__METHOD_IsShownCentered, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_IsOpen, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_ShowCentered, pcode__VOID);

new_method(true, pcode___form, pcode___form__METHOD_EventSource, pcode___control);
//new_method(true, pcode___form, pcode___form__METHOD_FormState, pcode__QString);

 
   new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ResizableSmaller, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ResizableSmaller, pcode__t_boolean);

   new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ResizableBigger, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ResizableBigger, pcode__t_boolean);


   new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ShowMode, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ShowMode, pcode__QString);



   new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FormFileName, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FormFileName, pcode__QString);

   new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FormModified, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FormModified, pcode__t_boolean);

//   new_param("n", pcode__t_integer, false);
//new_property_set(pcode___form, pcode___form__SETPROPERTY_FormX, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FormX, pcode__t_integer);


//   new_param("n", pcode__t_integer, false);
//new_property_set(pcode___form, pcode___form__SETPROPERTY_FormY, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FormY, pcode__t_integer);


//   new_param("n", pcode__t_integer, false);
//new_property_set(pcode___form, pcode___form__SETPROPERTY_FormWidth, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FormWidth, pcode__t_integer);


//   new_param("n", pcode__t_integer, false);
//new_property_set(pcode___form, pcode___form__SETPROPERTY_FormHeight, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FormHeight, pcode__t_integer);








new_method(true, pcode___form, pcode___form__EVENT_OnSingleShot, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnEnabled, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnDisabled, pcode__VOID, false, false, false, true);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_CursorAnimation, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_CursorAnimation, pcode__QString);

new_method(true, pcode___form, pcode___form__METHOD_DataIds, pcode___strings);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DataRemove, pcode__VOID);
	 
new_method(true, pcode___form, pcode___form__METHOD_DataRemoveAll, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__BOOLEAN, false);
new_method(true, pcode___form, pcode___form__METHOD_DataSetBoolean, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__INTEGER, false);
new_method(true, pcode___form, pcode___form__METHOD_DataSetInteger, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DataSetString, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__DOUBLE, false);
new_method(true, pcode___form, pcode___form__METHOD_DataSetDouble, pcode__VOID);


	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__LONG, false);
new_method(true, pcode___form, pcode___form__METHOD_DataSetLong, pcode__VOID);
	 
   new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__CURRENCY, false);
new_method(true, pcode___form, pcode___form__METHOD_DataSetDecimal, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__DATE, false);
new_method(true, pcode___form, pcode___form__METHOD_DataSetDateTime, pcode__VOID);
		 

	 new_param("Id", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DataBoolean, pcode__BOOLEAN);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DataInteger, pcode__INTEGER);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DataString, pcode__QString);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DataDouble, pcode__DOUBLE);
	 	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DataLong, pcode__LONG);

	 new_param("Id", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DataDecimal, pcode__CURRENCY);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_DataDateTime, pcode__DATE);
	 

new_method(true, pcode___form, pcode___form__METHOD_ClearFocus, pcode__VOID);

new_method(true, pcode___form, pcode___form__METHOD_ToggleVisible, pcode__VOID);

	 new_param("Milliseconds", pcode__INTEGER, false);
new_method(true, pcode___form, pcode___form__METHOD_SingleShot, pcode__VOID);
	 
new_method(true, pcode___form, pcode___form__METHOD_StartTimer, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_StopTimer, pcode__VOID);
	 
	 new_param("LocalX", pcode__INTEGER, false);
new_method(true, pcode___form, pcode___form__METHOD_GlobalX, pcode__INTEGER);
	 
	 new_param("LocalY", pcode__INTEGER, false);
new_method(true, pcode___form, pcode___form__METHOD_GlobalY, pcode__INTEGER);	 

	 new_param("GlobalX", pcode__INTEGER, false);
new_method(true, pcode___form, pcode___form__METHOD_LocalX, pcode__INTEGER);
	 
	 new_param("GlobalY", pcode__INTEGER, false);
new_method(true, pcode___form, pcode___form__METHOD_LocalY, pcode__INTEGER);
	 
new_method(true, pcode___form, pcode___form__METHOD_UnderMouse, pcode__BOOLEAN);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Mask, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Mask, pcode__QString);

   new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_SoundOnEvent, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_SoundOnEvent, pcode__QString);

   new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Left, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Left, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Top, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Top, pcode__t_integer);

   new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_LocalX, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_LocalX, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_LocalY, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_LocalY, pcode__t_integer);

	 new_param("n", pcode__BOOLEAN, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_DrawOnPaint, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_DrawOnPaint, pcode__BOOLEAN);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Palette, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Palette, pcode__QString);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_BackgroundStyle, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_BackgroundStyle, pcode__QString);



	 new_param("Tag", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__t_boolean, false);
new_method(true, pcode___form, pcode___form__METHOD_SetWithTag, pcode__VOID);

	 new_param("Tag", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__METHOD_SetWithTag1, pcode__VOID);

	 new_param("Tag", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_SetWithTag2, pcode__VOID);

	 new_param("Tag", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__DOUBLE, false);
new_method(true, pcode___form, pcode___form__METHOD_SetWithTag3, pcode__VOID);


	 new_param("Group", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__t_boolean, false);
new_method(true, pcode___form, pcode___form__METHOD_SetWithGroup, pcode__VOID);

	 new_param("Group", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__METHOD_SetWithGroup1, pcode__VOID);

	 new_param("Group", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_SetWithGroup2, pcode__VOID);

	 new_param("Group", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__DOUBLE, false);
new_method(true, pcode___form, pcode___form__METHOD_SetWithGroup3, pcode__VOID);



new_method(true, pcode___form, pcode___form__METHOD_IsShownFullScreen, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_IsShownMaximized, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_IsShownMinimized, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_IsShownNormal, pcode__t_boolean);

	 new_param("s", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_Load, pcode__t_boolean);

	 new_param("s", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__METHOD_ShowMultiPage, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_ShowNextMultiPage, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_ShowPreviousMultiPage, pcode__VOID);

new_method(true, pcode___form, pcode___form__EVENT_OnScroll, pcode__VOID, false, false, false, true);

	 new_param("Page", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__EVENT_OnMultiPageShow, pcode__VOID, false, false, false, true);

	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Resizable, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Resizable, pcode__t_boolean);


new_method(true, pcode___form, pcode___form__METHOD_OpenPrintDialog, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_OpenPrint, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_OpenPrintPreview, pcode__VOID);

new_method(true, pcode___form, pcode___form__METHOD_Finish, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_FocusControl, pcode__QString);
new_method(true, pcode___form, pcode___form__METHOD_ControlFirst, pcode__QString);
new_method(true, pcode___form, pcode___form__METHOD_ControlNext, pcode__QString);
	 new_param("s", pcode__t_string, false);
new_method(true, pcode___form, pcode___form__METHOD_Tr, pcode__QString);
new_method(true, pcode___form, pcode___form__METHOD_ShowFullScreen, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_ShowMaximized, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_ShowMinimized, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_ShowNormal, pcode__VOID);
	 new_param("s", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_Control, pcode___control);
new_method(true, pcode___form, pcode___form__EVENT_OnLoad, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnDirty, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnAddNew, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnGoTo, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnGoTo2, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnQuery, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnDirty, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnAfterInsert, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnAfterUpdate, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnAfterDelete, pcode__VOID, false, false, false, true);
	 new_param("Cancel", pcode__BOOLEAN_POINTER, false);
new_method(true, pcode___form, pcode___form__EVENT_OnBeforeInsert, pcode__VOID, false, false, false, true);
	 new_param("Cancel", pcode__BOOLEAN_POINTER, false);
new_method(true, pcode___form, pcode___form__EVENT_OnBeforeUpdate, pcode__VOID, false, false, false, true);
	 new_param("Cancel", pcode__BOOLEAN_POINTER, false);
new_method(true, pcode___form, pcode___form__EVENT_OnBeforeDelete, pcode__VOID, false, false, false, true);

/*

	 new_param("FieldName", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_Record, pcode__t_variant);

   new_param("FieldName", pcode__QString, false);
	 new_param("Value", pcode__t_variant, false);
new_method(true, pcode___form, pcode___form__METHOD_SetRecord, pcode__VOID);
*/


//new_method(true, pcode___form, pcode___form__METHOD_Record1, pcode___record);
	 new_param("SQLStatement", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_Query, pcode___query);

new_method(true, pcode___form, pcode___form__METHOD_IsFilterActive, pcode__t_boolean);

new_method(true, pcode___form, pcode___form__METHOD_Cut, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_Copy, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_Paste, pcode__t_boolean);

new_method(true, pcode___form, pcode___form__METHOD_First, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_Next, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_Previous, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_Last, pcode__t_boolean);
	 new_param("l", pcode__t_long, false);
new_method(true, pcode___form, pcode___form__METHOD_GoTo, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_Insert, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_Update, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_Delete, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_AddNew, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_Len, pcode__t_long);
new_method(true, pcode___form, pcode___form__METHOD_Pos, pcode__t_long);
new_method(true, pcode___form, pcode___form__METHOD_IsDirty, pcode__t_boolean);
new_method(true, pcode___form, pcode___form__METHOD_Affected, pcode__t_long);
	 new_param("SQLStatement", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_Cmd, pcode__t_boolean);

   new_param("Filter1", pcode__QString, true, "");
   new_param("Filter2", pcode__QString, true, "");
   new_param("Filter3", pcode__QString, true, "");
   new_param("Filter4", pcode__QString, true, "");
   new_param("Filter5", pcode__QString, true, "");
   new_param("Filter6", pcode__QString, true, "");
new_method(true, pcode___form, pcode___form__METHOD_Seek, pcode__t_boolean);

new_method(true, pcode___form, pcode___form__METHOD_ClearFilter, pcode__VOID);
	 new_param("Filter", pcode__QString, true, "");
new_method(true, pcode___form, pcode___form__METHOD_AddFilter, pcode__VOID);
	 new_param("Filter", pcode__QString, true, "");
new_method(true, pcode___form, pcode___form__METHOD_SetFilter, pcode__VOID);
	 new_param("Field", pcode__QString, true, "");
new_method(true, pcode___form, pcode___form__METHOD_SortAsc, pcode__VOID);
	 new_param("Field", pcode__QString, true, "");
new_method(true, pcode___form, pcode___form__METHOD_SortDesc, pcode__VOID);

	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Mask, pcode__VOID);
new_property_get(pcode___form, pcode___form__SETPROPERTY_Mask, pcode__QString);

	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Dock, pcode__VOID);
new_property_get(pcode___form, pcode___form__SETPROPERTY_Dock, pcode__QString);

	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ScrollBar, pcode__VOID);
new_property_get(pcode___form, pcode___form__SETPROPERTY_ScrollBar, pcode__QString);



	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_StopOnClose, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_StopOnClose, pcode__t_boolean);

	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_OpenAtStartup, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_OpenAtStartup, pcode__t_boolean);

	 
new_method(true, pcode___form, pcode___form__METHOD_kbrecordid, pcode__t_integer);
   new_param("FormView", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_kbrecordid1, pcode__t_integer);

new_method(true, pcode___form, pcode___form__METHOD_PrimaryKey, pcode__t_integer);
   new_param("FormView", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_PrimaryKey1, pcode__t_integer);

new_method(true, pcode___form, pcode___form__METHOD_PrimaryKeyName, pcode__QString);
   new_param("FormView", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_PrimaryKeyName1, pcode__QString);


new_method(true, pcode___form, pcode___form__METHOD_LastSQLError, pcode__QString);
/*
	 new_param("SearchFor", pcode__QString, false);
	 new_param("InTableDotField", pcode__QString, false);
	 new_param("ReturnFieldName", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_Find, pcode___record);
*/
	 new_param("SearchFor", pcode__QString, false);
	 new_param("InTableDotField", pcode__QString, false);
	 new_param("ReturnFieldName", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_Find1, pcode__t_variant);
	 new_param("SQL", pcode__QString, false);
new_method(true, pcode___form, pcode___form__METHOD_Get, pcode__t_variant);
new_method(true, pcode___form, pcode___form__METHOD_Requery, pcode__VOID);


	 new_param("n", pcode__BOOLEAN, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_DockTitleVisible, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_DockTitleVisible, pcode__BOOLEAN);

	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_DockOrder, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_DockOrder, pcode__QString);

	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_DockWidth, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_DockWidth, pcode__t_integer);

	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_DockHeight, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_DockHeight, pcode__t_integer);


	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ScrollX, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ScrollX, pcode__t_integer);

	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ScrollY, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ScrollY, pcode__t_integer);

	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ScrollWidth, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ScrollWidth, pcode__t_integer);

	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ScrollHeight, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ScrollHeight, pcode__t_integer);



	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MultiPageHeight, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MultiPageHeight, pcode__t_integer);


	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MultiPageBorderLeft, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MultiPageBorderLeft, pcode__t_integer);

	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MultiPageBorderRight, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MultiPageBorderRight, pcode__t_integer);

	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MultiPageBorderTop, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MultiPageBorderTop, pcode__t_integer);

	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MultiPageBorderBottom, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MultiPageBorderBottom, pcode__t_integer);



	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_BorderTop, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_BorderTop, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_BorderBottom, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_BorderBottom, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_BorderLeft, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_BorderLeft, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_BorderRight, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_BorderRight, pcode__t_integer);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_TableView, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_TableView, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Flag, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Flag, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Icon, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Icon, pcode__QString);

	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Caption, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Caption, pcode__QString);

	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Value, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Value, pcode__QString);

	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Text, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Text, pcode__QString);

  new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Modal, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Modal, pcode__t_boolean);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__METHOD_Move, pcode__VOID);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__METHOD_Resize, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_Show, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_Hide, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_RepaintAlways, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_Repaint, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_Raise, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_Lower, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_Close, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_Open, pcode__VOID);

	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__METHOD_Open1, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__METHOD_Open2, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_OpenFullScreen, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_OpenCentered, pcode__VOID);

new_method(true, pcode___form, pcode___form__METHOD_OpenHidden, pcode__VOID);
new_method(true, pcode___form, pcode___form__METHOD_SetFocus, pcode__VOID);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Name, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Name, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Group, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Group, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Background, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Background, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_X, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_X, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Y, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Y, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Width, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Width, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Height, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Height, pcode__t_integer);
new_property_get(pcode___form, pcode___form__GETPROPERTY_GlobalX, pcode__t_integer);
new_property_get(pcode___form, pcode___form__GETPROPERTY_GlobalY, pcode__t_integer);
new_property_get(pcode___form, pcode___form__GETPROPERTY_OldX, pcode__t_integer);
new_property_get(pcode___form, pcode___form__GETPROPERTY_OldY, pcode__t_integer);
new_property_get(pcode___form, pcode___form__GETPROPERTY_OldWidth, pcode__t_integer);
new_property_get(pcode___form, pcode___form__GETPROPERTY_OldHeight, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MinimumWidth, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MinimumWidth, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MinimumHeight, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MinimumHeight, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MaximumWidth, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MaximumWidth, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_MaximumHeight, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_MaximumHeight, pcode__t_integer);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Tag, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Tag, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_CSV, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_CSV, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ParentForm, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ParentForm, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ParentControl, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ParentControl, pcode__QString);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_DragDrop, pcode__VOID);
new_method(true, pcode___form, pcode___form__GETPROPERTY_ParentControl1, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ControlType, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ControlType, pcode__QString);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Focus, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Focus, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FocusPolicy, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FocusPolicy, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FocusProxy, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FocusProxy, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FocusOrder, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FocusOrder, pcode__t_integer);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Cursor, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Cursor, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FontName, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FontName, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FontSize, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FontSize, pcode__t_integer);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FontItalic, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FontItalic, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FontBold, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FontBold, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FontUnderline, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FontUnderline, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_FontColor, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_FontColor, pcode__QString);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Enabled, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Enabled, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Visible, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Visible, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_StatusTip, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_StatusTip, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ToolTip, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ToolTip, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_StyleSheet, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_StyleSheet, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_WhatsThis, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_WhatsThis, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_TimerInterval, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_TimerInterval, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_Opacity, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_Opacity, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_BoxIndex, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_BoxIndex, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_SplitIndex, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_SplitIndex, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_TabIndex, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_TabIndex, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_BoxX, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_BoxX, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_BoxY, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_BoxY, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_ParentIndex, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_ParentIndex, pcode__t_integer);
	 new_param("n", pcode__QString, false);
new_method(true, pcode___form, pcode___form__SETPROPERTY_ControlType1, pcode__VOID);
new_method(true, pcode___form, pcode___form__GETPROPERTY_ControlType1, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_SQLName, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_SQLName, pcode__QString);
	 
   new_param("n", pcode__QString, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_SQLControls, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_SQLControls, pcode__QString);


	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_SQLInsert, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_SQLInsert, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_SQLUpdate, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_SQLUpdate, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___form, pcode___form__SETPROPERTY_SQLDelete, pcode__VOID);
new_property_get(pcode___form, pcode___form__GETPROPERTY_SQLDelete, pcode__t_boolean);

new_method(true, pcode___form, pcode___form__EVENT_OnOpen, pcode__VOID, false, false, false, true);
	 new_param("Cancel", pcode__BOOLEAN_POINTER, false);
new_method(true, pcode___form, pcode___form__EVENT_OnClose, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__EVENT_OnContextMenu, pcode__BOOLEAN, false, false, false, true);
	 new_param("Cancel", pcode__t_boolean, false);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__EVENT_OnDragEnter, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnDragExit, pcode__VOID, false, false, false, true);
	 new_param("Cancel", pcode__t_boolean, false);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__EVENT_OnDragMove, pcode__VOID, false, false, false, true);
	 new_param("Cancel", pcode__t_boolean, false);
	 new_param("MimeData", pcode__QString, false);
new_method(true, pcode___form, pcode___form__EVENT_OnDrop, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnEnter, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnGotFocus, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnLostFocus, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnHide, pcode__VOID, false, false, false, true);
	 new_param("Key", pcode__t_integer, false);
	 new_param("Shift", pcode__t_boolean, false);
	 new_param("Control", pcode__t_boolean, false);
	 new_param("Alt", pcode__t_boolean, false);
new_method(true, pcode___form, pcode___form__EVENT_OnKeyDown, pcode__VOID, false, false, false, true);
	 new_param("Key", pcode__t_integer, false);
	 new_param("Shift", pcode__t_boolean, false);
	 new_param("Control", pcode__t_boolean, false);
	 new_param("Alt", pcode__t_boolean, false);
new_method(true, pcode___form, pcode___form__EVENT_OnKeyUp, pcode__VOID, false, false, false, true);
	 new_param("Key", pcode__t_integer, false);
	 new_param("Shift", pcode__t_boolean, false);
	 new_param("Control", pcode__t_boolean, false);
	 new_param("Alt", pcode__t_boolean, false);
new_method(true, pcode___form, pcode___form__EVENT_OnKeyPress, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnExit, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___form, pcode___form__EVENT_OnDblClick, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___form, pcode___form__EVENT_OnClick, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__EVENT_OnMouseMove, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___form, pcode___form__EVENT_OnMouseDown, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___form, pcode___form__EVENT_OnMouseUp, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("OldX", pcode__t_integer, false);
	 new_param("OldY", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__EVENT_OnMove, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__EVENT_OnPaint, pcode__VOID, false, false, false, true);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("OldWidth", pcode__t_integer, false);
	 new_param("OldHeight", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__EVENT_OnResize, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnShow, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
new_method(true, pcode___form, pcode___form__EVENT_OnMouseWheel, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnTimer, pcode__VOID, false, false, false, true);
new_method(true, pcode___form, pcode___form__EVENT_OnPrint, pcode__VOID, false, false, false, true);
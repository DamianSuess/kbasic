
new_class(pcode___movie, pcode___control, 0); 

new_method(true, pcode___movie, pcode___movie___movie1, pcode___movie);


	 new_param("YesNo", pcode__BOOLEAN, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_MouseTracking, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_MouseTracking, pcode__BOOLEAN);



new_method(true, pcode___movie, pcode___movie__EVENT_OnSingleShot, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnEnabled, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnDisabled, pcode__VOID, false, false, false, true);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_CursorAnimation, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_CursorAnimation, pcode__QString);

new_method(true, pcode___movie, pcode___movie__METHOD_DataIds, pcode___strings);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataRemove, pcode__VOID);
	 
new_method(true, pcode___movie, pcode___movie__METHOD_DataRemoveAll, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__BOOLEAN, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataSetBoolean, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__INTEGER, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataSetInteger, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataSetString, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__DOUBLE, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataSetDouble, pcode__VOID);


	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__LONG, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataSetLong, pcode__VOID);
	 
   new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__CURRENCY, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataSetDecimal, pcode__VOID);
	 
	 new_param("Id", pcode__QString, false);
	 new_param("Value", pcode__DATE, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataSetDateTime, pcode__VOID);


	 new_param("Id", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataBoolean, pcode__BOOLEAN);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataInteger, pcode__INTEGER);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataString, pcode__QString);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataDouble, pcode__DOUBLE);
 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataLong, pcode__LONG);

	 new_param("Id", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataDecimal, pcode__CURRENCY);
	 
	 new_param("Id", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_DataDateTime, pcode__DATE);


new_method(true, pcode___movie, pcode___movie__METHOD_ClearFocus, pcode__VOID);

new_method(true, pcode___movie, pcode___movie__METHOD_ToggleVisible, pcode__VOID);

	 new_param("Milliseconds", pcode__INTEGER, false);
new_method(true, pcode___movie, pcode___movie__METHOD_SingleShot, pcode__VOID);
	 
new_method(true, pcode___movie, pcode___movie__METHOD_StartTimer, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_StopTimer, pcode__VOID);
	 
	 new_param("LocalX", pcode__INTEGER, false);
new_method(true, pcode___movie, pcode___movie__METHOD_GlobalX, pcode__INTEGER);
	 
	 new_param("LocalY", pcode__INTEGER, false);
new_method(true, pcode___movie, pcode___movie__METHOD_GlobalY, pcode__INTEGER);	 

	 new_param("GlobalX", pcode__INTEGER, false);
new_method(true, pcode___movie, pcode___movie__METHOD_LocalX, pcode__INTEGER);
	 
	 new_param("GlobalY", pcode__INTEGER, false);
new_method(true, pcode___movie, pcode___movie__METHOD_LocalY, pcode__INTEGER);
	 
new_method(true, pcode___movie, pcode___movie__METHOD_UnderMouse, pcode__BOOLEAN);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Mask, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Mask, pcode__QString);

   new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_SoundOnEvent, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_SoundOnEvent, pcode__QString);

   new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Left, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Left, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Top, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Top, pcode__t_integer);

   new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_LocalX, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_LocalX, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_LocalY, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_LocalY, pcode__t_integer);

	 new_param("n", pcode__BOOLEAN, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_DrawOnPaint, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_DrawOnPaint, pcode__BOOLEAN);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Palette, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Palette, pcode__QString);


	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_BackgroundStyle, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_BackgroundStyle, pcode__QString);



	 new_param("Percent", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Brightness, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Brightness, pcode__t_integer);

	 new_param("Percent", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Contrast, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Contrast, pcode__t_integer);

	 new_param("Percent", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Hue, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Hue, pcode__t_integer);

	 new_param("Saturation", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Saturation, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Saturation, pcode__t_integer);

	 new_param("ScaleMode", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_ScaleMode, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_ScaleMode, pcode__QString);

	 new_param("AspectRatio", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_AspectRatio, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_AspectRatio, pcode__QString);


new_method(true, pcode___movie, pcode___movie__METHOD_State, pcode__QString);
new_method(true, pcode___movie, pcode___movie__METHOD_ErrorType, pcode__QString);
new_method(true, pcode___movie, pcode___movie__METHOD_ErrorString, pcode__QString);
new_method(true, pcode___movie, pcode___movie__METHOD_CurrentTime, pcode__t_long);
new_method(true, pcode___movie, pcode___movie__METHOD_TotalTime, pcode__t_long);
new_method(true, pcode___movie, pcode___movie__METHOD_IsPlaying, pcode__t_boolean);
new_method(true, pcode___movie, pcode___movie__METHOD_IsPaused, pcode__t_boolean);
new_method(true, pcode___movie, pcode___movie__METHOD_IsMuted, pcode__t_boolean);
new_method(true, pcode___movie, pcode___movie__METHOD_IsSeekable, pcode__t_boolean);
new_method(true, pcode___movie, pcode___movie__METHOD_Play, pcode__VOID);
	 

     new_param("FileName", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_Play1, pcode__VOID);

     new_param("FileName", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_Load, pcode__VOID);

     new_param("FileName", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__METHOD_PlayInQueue, pcode__VOID);

new_method(true, pcode___movie, pcode___movie__METHOD_Pause, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_Stop, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_ClearQueue, pcode__VOID);

     new_param("Position", pcode__t_long, false);
new_method(true, pcode___movie, pcode___movie__METHOD_Seek, pcode__VOID);



    new_param("FileName", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_StringValue, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_StringValue, pcode__QString);

    new_param("MSec", pcode__t_long, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_TransitionTime, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_TransitionTime, pcode__t_long);

    new_param("OnOff", pcode__t_boolean, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Muted, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Muted, pcode__t_boolean);

    new_param("Percent", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Volume, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Volume, pcode__t_integer);

    new_param("MSec", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_PrefinishMark, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_PrefinishMark, pcode__t_integer);

    new_param("MSec", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Tick, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Tick, pcode__t_integer);


new_method(true, pcode___movie, pcode___movie__EVENT_OnEvent, pcode__VOID, false, false, false, true);

    new_param("MSec", pcode__t_long, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnTick, pcode__VOID, false, false, false, true);

    new_param("NewState", pcode__QString, false);
    new_param("OldState", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnStateChanged, pcode__VOID, false, false, false, true);

new_method(true, pcode___movie, pcode___movie__EVENT_OnAboutToFinish, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnFinished, pcode__VOID, false, false, false, true);
    new_param("OnOff", pcode__t_boolean, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnMutedChanged, pcode__VOID, false, false, false, true);
    new_param("Percent", pcode__t_integer, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnVolumeChanged, pcode__VOID, false, false, false, true);
    new_param("FileName", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnPlayingTitleChanged, pcode__VOID, false, false, false, true);
    new_param("Percent", pcode__t_integer, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnBufferStatus, pcode__VOID, false, false, false, true);

    new_param("MSec", pcode__t_long, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnTotalTimeChanged, pcode__VOID, false, false, false, true);



	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
new_method(true, pcode___movie, pcode___movie__METHOD_Move, pcode__VOID);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___movie, pcode___movie__METHOD_Resize, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_Show, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_Hide, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_RepaintAlways, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_Repaint, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_Raise, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_Lower, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_Close, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_Open, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__METHOD_SetFocus, pcode__VOID);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Name, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Name, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Group, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Group, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Background, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Background, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_X, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_X, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Y, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Y, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Width, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Width, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Height, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Height, pcode__t_integer);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_GlobalX, pcode__t_integer);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_GlobalY, pcode__t_integer);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_OldX, pcode__t_integer);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_OldY, pcode__t_integer);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_OldWidth, pcode__t_integer);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_OldHeight, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_MinimumWidth, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_MinimumWidth, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_MinimumHeight, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_MinimumHeight, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_MaximumWidth, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_MaximumWidth, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_MaximumHeight, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_MaximumHeight, pcode__t_integer);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Tag, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Tag, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_CSV, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_CSV, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_ParentForm, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_ParentForm, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_ParentControl, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_ParentControl, pcode__QString);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_DragDrop, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__GETPROPERTY_ParentControl1, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_ControlType, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_ControlType, pcode__QString);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Focus, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Focus, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_FocusPolicy, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_FocusPolicy, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_FocusProxy, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_FocusProxy, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_FocusOrder, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_FocusOrder, pcode__t_integer);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Cursor, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Cursor, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_FontName, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_FontName, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_FontSize, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_FontSize, pcode__t_integer);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_FontItalic, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_FontItalic, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_FontBold, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_FontBold, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_FontUnderline, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_FontUnderline, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_FontColor, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_FontColor, pcode__QString);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Enabled, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Enabled, pcode__t_boolean);
	 new_param("n", pcode__t_boolean, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Visible, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Visible, pcode__t_boolean);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_StatusTip, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_StatusTip, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_ToolTip, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_ToolTip, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_StyleSheet, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_StyleSheet, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_WhatsThis, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_WhatsThis, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_movieInterval, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_movieInterval, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_Opacity, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_Opacity, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_BoxIndex, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_BoxIndex, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_SplitIndex, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_SplitIndex, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_TabIndex, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_TabIndex, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_BoxX, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_BoxX, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_BoxY, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_BoxY, pcode__t_integer);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_ParentIndex, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_ParentIndex, pcode__t_integer);
	 new_param("n", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__SETPROPERTY_ControlType1, pcode__VOID);
new_method(true, pcode___movie, pcode___movie__GETPROPERTY_ControlType1, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_SQLName, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_SQLName, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_SQLType, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_SQLType, pcode__QString);
	 new_param("n", pcode__QString, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_SQLCaption, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_SQLCaption, pcode__QString);
	 new_param("n", pcode__t_integer, false);
new_property_set(pcode___movie, pcode___movie__SETPROPERTY_SQLWidth, pcode__VOID);
new_property_get(pcode___movie, pcode___movie__GETPROPERTY_SQLWidth, pcode__t_integer);
new_method(true, pcode___movie, pcode___movie__EVENT_OnOpen, pcode__VOID, false, false, false, true);
	 new_param("Cancel", pcode__BOOLEAN_POINTER, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnClose, pcode__VOID, false, false, false, true);

	 new_param("Cancel", pcode__t_boolean, false);
	 new_param("MimeData", pcode__QString, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnDrop, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnEnter, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnGotFocus, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnLostFocus, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnHide, pcode__VOID, false, false, false, true);
	 new_param("Key", pcode__t_integer, false);
	 new_param("Shift", pcode__t_boolean, false);
	 new_param("Control", pcode__t_boolean, false);
	 new_param("Alt", pcode__t_boolean, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnKeyDown, pcode__VOID, false, false, false, true);
	 new_param("Key", pcode__t_integer, false);
	 new_param("Shift", pcode__t_boolean, false);
	 new_param("Control", pcode__t_boolean, false);
	 new_param("Alt", pcode__t_boolean, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnKeyUp, pcode__VOID, false, false, false, true);
	 new_param("Key", pcode__t_integer, false);
	 new_param("Shift", pcode__t_boolean, false);
	 new_param("Control", pcode__t_boolean, false);
	 new_param("Alt", pcode__t_boolean, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnKeyPress, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnExit, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnDblClick, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnClick, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnMouseMove, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnMouseDown, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
	 new_param("Left", pcode__t_boolean, false);
	 new_param("Right", pcode__t_boolean, false);
	 new_param("Mid", pcode__t_boolean, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnMouseUp, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("OldX", pcode__t_integer, false);
	 new_param("OldY", pcode__t_integer, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnMove, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnPaint, pcode__VOID, false, false, false, true);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("OldWidth", pcode__t_integer, false);
	 new_param("OldHeight", pcode__t_integer, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnResize, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnShow, pcode__VOID, false, false, false, true);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("GlobalX", pcode__t_integer, false);
	 new_param("GlobalY", pcode__t_integer, false);
new_method(true, pcode___movie, pcode___movie__EVENT_OnMouseWheel, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnTimer, pcode__VOID, false, false, false, true);
new_method(true, pcode___movie, pcode___movie__EVENT_OnPrint, pcode__VOID, false, false, false, true);


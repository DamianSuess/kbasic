
static const int pcode___movie___movie = pcode___movie * SPACE;
static const int pcode___movie___movie1 = pcode___movie___movie + 1;


static const int pcode___movie__SETPROPERTY_MouseTracking = pcode___movie___movie1 + 1;
static const int pcode___movie__GETPROPERTY_MouseTracking = pcode___movie__SETPROPERTY_MouseTracking + 1; 




static const int pcode___movie__EVENT_OnSingleShot = pcode___movie__GETPROPERTY_MouseTracking + 1;
static const int pcode___movie__EVENT_OnEnabled = pcode___movie__EVENT_OnSingleShot + 1;
static const int pcode___movie__EVENT_OnDisabled = pcode___movie__EVENT_OnEnabled + 1;

static const int pcode___movie__SETPROPERTY_CursorAnimation = pcode___movie__EVENT_OnDisabled + 1;
static const int pcode___movie__GETPROPERTY_CursorAnimation = pcode___movie__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___movie__METHOD_DataIds = pcode___movie__GETPROPERTY_CursorAnimation + 1;

static const int pcode___movie__METHOD_DataRemove = pcode___movie__METHOD_DataIds + 1;
static const int pcode___movie__METHOD_DataRemoveAll = pcode___movie__METHOD_DataRemove + 1;
static const int pcode___movie__METHOD_DataSetBoolean = pcode___movie__METHOD_DataRemoveAll + 1;
static const int pcode___movie__METHOD_DataSetInteger = pcode___movie__METHOD_DataSetBoolean + 1;
static const int pcode___movie__METHOD_DataSetString = pcode___movie__METHOD_DataSetInteger + 1;
static const int pcode___movie__METHOD_DataSetDouble = pcode___movie__METHOD_DataSetString + 1;
static const int pcode___movie__METHOD_DataSetLong = pcode___movie__METHOD_DataSetDouble + 1;
static const int pcode___movie__METHOD_DataSetDecimal = pcode___movie__METHOD_DataSetLong + 1;
static const int pcode___movie__METHOD_DataSetDateTime = pcode___movie__METHOD_DataSetDecimal + 1;


static const int pcode___movie__METHOD_DataBoolean = pcode___movie__METHOD_DataSetDateTime + 1;
static const int pcode___movie__METHOD_DataInteger = pcode___movie__METHOD_DataBoolean + 1;
static const int pcode___movie__METHOD_DataString = pcode___movie__METHOD_DataInteger + 1;
static const int pcode___movie__METHOD_DataDouble = pcode___movie__METHOD_DataString + 1;
static const int pcode___movie__METHOD_DataLong = pcode___movie__METHOD_DataDouble + 1;
static const int pcode___movie__METHOD_DataDecimal = pcode___movie__METHOD_DataLong + 1;
static const int pcode___movie__METHOD_DataDateTime = pcode___movie__METHOD_DataDecimal + 1;

static const int pcode___movie__METHOD_ClearFocus = pcode___movie__METHOD_DataDateTime + 1;
static const int pcode___movie__METHOD_ToggleVisible = pcode___movie__METHOD_ClearFocus + 1;

static const int pcode___movie__METHOD_SingleShot = pcode___movie__METHOD_ToggleVisible + 1;
static const int pcode___movie__METHOD_StartTimer = pcode___movie__METHOD_SingleShot + 1;
static const int pcode___movie__METHOD_StopTimer = pcode___movie__METHOD_StartTimer + 1;

//static const int pcode___movie__METHOD_EventSender = pcode___movie__METHOD_StopTimer + 1;

static const int pcode___movie__METHOD_GlobalX = pcode___movie__METHOD_StopTimer + 1;
static const int pcode___movie__METHOD_GlobalY = pcode___movie__METHOD_GlobalX + 1;
static const int pcode___movie__METHOD_LocalX = pcode___movie__METHOD_GlobalY + 1;
static const int pcode___movie__METHOD_LocalY = pcode___movie__METHOD_LocalX + 1;

static const int pcode___movie__METHOD_UnderMouse = pcode___movie__METHOD_LocalY + 1;

static const int pcode___movie__SETPROPERTY_Mask = pcode___movie__METHOD_UnderMouse + 1;
static const int pcode___movie__GETPROPERTY_Mask = pcode___movie__SETPROPERTY_Mask + 1;

static const int pcode___movie__SETPROPERTY_SoundOnEvent = pcode___movie__GETPROPERTY_Mask + 1;
static const int pcode___movie__GETPROPERTY_SoundOnEvent = pcode___movie__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___movie__SETPROPERTY_Left = pcode___movie__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___movie__GETPROPERTY_Left = pcode___movie__SETPROPERTY_Left + 1;
static const int pcode___movie__SETPROPERTY_Top = pcode___movie__GETPROPERTY_Left + 1;
static const int pcode___movie__GETPROPERTY_Top = pcode___movie__SETPROPERTY_Top + 1;

static const int pcode___movie__SETPROPERTY_LocalX = pcode___movie__GETPROPERTY_Top + 1;
static const int pcode___movie__GETPROPERTY_LocalX = pcode___movie__SETPROPERTY_LocalX + 1;
static const int pcode___movie__SETPROPERTY_LocalY = pcode___movie__GETPROPERTY_LocalX + 1;
static const int pcode___movie__GETPROPERTY_LocalY = pcode___movie__SETPROPERTY_LocalY + 1;

static const int pcode___movie__SETPROPERTY_DrawOnPaint = pcode___movie__GETPROPERTY_LocalY + 1;
static const int pcode___movie__GETPROPERTY_DrawOnPaint = pcode___movie__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___movie__SETPROPERTY_Palette = pcode___movie__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___movie__GETPROPERTY_Palette = pcode___movie__SETPROPERTY_Palette + 1;


static const int pcode___movie__SETPROPERTY_BackgroundStyle = pcode___movie__GETPROPERTY_Palette + 1;
static const int pcode___movie__GETPROPERTY_BackgroundStyle = pcode___movie__SETPROPERTY_BackgroundStyle + 1;


static const int pcode___movie__SETPROPERTY_Brightness = pcode___movie__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___movie__GETPROPERTY_Brightness = pcode___movie__SETPROPERTY_Brightness + 1;

static const int pcode___movie__SETPROPERTY_Contrast = pcode___movie__GETPROPERTY_Brightness + 1;
static const int pcode___movie__GETPROPERTY_Contrast = pcode___movie__SETPROPERTY_Contrast + 1;

static const int pcode___movie__SETPROPERTY_Hue = pcode___movie__GETPROPERTY_Contrast + 1;
static const int pcode___movie__GETPROPERTY_Hue = pcode___movie__SETPROPERTY_Hue + 1;

static const int pcode___movie__SETPROPERTY_Saturation = pcode___movie__GETPROPERTY_Hue + 1;
static const int pcode___movie__GETPROPERTY_Saturation = pcode___movie__SETPROPERTY_Saturation + 1;

static const int pcode___movie__SETPROPERTY_ScaleMode = pcode___movie__GETPROPERTY_Saturation + 1;
static const int pcode___movie__GETPROPERTY_ScaleMode = pcode___movie__SETPROPERTY_ScaleMode + 1;

static const int pcode___movie__SETPROPERTY_AspectRatio = pcode___movie__GETPROPERTY_ScaleMode + 1;
static const int pcode___movie__GETPROPERTY_AspectRatio = pcode___movie__SETPROPERTY_AspectRatio + 1;

static const int pcode___movie__METHOD_State = pcode___movie__GETPROPERTY_AspectRatio + 1;
static const int pcode___movie__METHOD_ErrorType = pcode___movie__METHOD_State + 1;
static const int pcode___movie__METHOD_ErrorString = pcode___movie__METHOD_ErrorType + 1;
static const int pcode___movie__METHOD_CurrentTime = pcode___movie__METHOD_ErrorString + 1;
static const int pcode___movie__METHOD_TotalTime = pcode___movie__METHOD_CurrentTime + 1;
static const int pcode___movie__METHOD_IsPlaying = pcode___movie__METHOD_TotalTime + 1;
static const int pcode___movie__METHOD_IsPaused = pcode___movie__METHOD_IsPlaying + 1;
static const int pcode___movie__METHOD_IsMuted = pcode___movie__METHOD_IsPaused + 1;
static const int pcode___movie__METHOD_IsSeekable = pcode___movie__METHOD_IsMuted + 1;
static const int pcode___movie__METHOD_Play = pcode___movie__METHOD_IsSeekable + 1;
static const int pcode___movie__METHOD_Play1 = pcode___movie__METHOD_Play + 1;
static const int pcode___movie__METHOD_Load = pcode___movie__METHOD_Play1 + 1;
static const int pcode___movie__METHOD_PlayInQueue = pcode___movie__METHOD_Load + 1;
static const int pcode___movie__METHOD_Pause = pcode___movie__METHOD_PlayInQueue + 1;
static const int pcode___movie__METHOD_Stop = pcode___movie__METHOD_Pause + 1;
static const int pcode___movie__METHOD_ClearQueue = pcode___movie__METHOD_Stop + 1;
static const int pcode___movie__METHOD_Seek = pcode___movie__METHOD_ClearQueue + 1;

static const int pcode___movie__SETPROPERTY_StringValue = pcode___movie__METHOD_Seek + 1;
static const int pcode___movie__GETPROPERTY_StringValue = pcode___movie__SETPROPERTY_StringValue + 1;

static const int pcode___movie__SETPROPERTY_TransitionTime = pcode___movie__GETPROPERTY_StringValue + 1;
static const int pcode___movie__GETPROPERTY_TransitionTime = pcode___movie__SETPROPERTY_TransitionTime + 1;

static const int pcode___movie__SETPROPERTY_Muted = pcode___movie__GETPROPERTY_TransitionTime + 1;
static const int pcode___movie__GETPROPERTY_Muted = pcode___movie__SETPROPERTY_Muted + 1;

static const int pcode___movie__SETPROPERTY_Volume = pcode___movie__GETPROPERTY_Muted + 1;
static const int pcode___movie__GETPROPERTY_Volume = pcode___movie__SETPROPERTY_Volume + 1;

static const int pcode___movie__SETPROPERTY_PrefinishMark = pcode___movie__GETPROPERTY_Volume + 1;
static const int pcode___movie__GETPROPERTY_PrefinishMark = pcode___movie__SETPROPERTY_PrefinishMark + 1;

static const int pcode___movie__SETPROPERTY_Tick = pcode___movie__GETPROPERTY_PrefinishMark + 1;
static const int pcode___movie__GETPROPERTY_Tick = pcode___movie__SETPROPERTY_Tick + 1;

static const int pcode___movie__EVENT_OnEvent = pcode___movie__GETPROPERTY_Tick + 1;
static const int pcode___movie__EVENT_OnTick = pcode___movie__EVENT_OnEvent + 1;
static const int pcode___movie__EVENT_OnStateChanged = pcode___movie__EVENT_OnTick + 1;
static const int pcode___movie__EVENT_OnAboutToFinish = pcode___movie__EVENT_OnStateChanged + 1;
static const int pcode___movie__EVENT_OnFinished = pcode___movie__EVENT_OnAboutToFinish + 1;
static const int pcode___movie__EVENT_OnMutedChanged = pcode___movie__EVENT_OnFinished + 1;
static const int pcode___movie__EVENT_OnVolumeChanged = pcode___movie__EVENT_OnMutedChanged + 1;
static const int pcode___movie__EVENT_OnPlayingTitleChanged = pcode___movie__EVENT_OnVolumeChanged + 1;
static const int pcode___movie__EVENT_OnBufferStatus = pcode___movie__EVENT_OnPlayingTitleChanged + 1;
static const int pcode___movie__EVENT_OnTotalTimeChanged = pcode___movie__EVENT_OnBufferStatus + 1;



static const int pcode___movie__SETPROPERTY_Layout = pcode___movie__EVENT_OnTotalTimeChanged + 1;
static const int pcode___movie__GETPROPERTY_Layout = pcode___movie__SETPROPERTY_Layout + 1;
static const int pcode___movie__METHOD_Move = pcode___movie__GETPROPERTY_Layout + 1;
static const int pcode___movie__METHOD_Resize = pcode___movie__METHOD_Move + 1;
static const int pcode___movie__METHOD_Show = pcode___movie__METHOD_Resize + 1;
static const int pcode___movie__METHOD_Hide = pcode___movie__METHOD_Show + 1;
static const int pcode___movie__METHOD_RepaintAlways = pcode___movie__METHOD_Hide + 1;
static const int pcode___movie__METHOD_Repaint = pcode___movie__METHOD_RepaintAlways + 1;
static const int pcode___movie__METHOD_Raise = pcode___movie__METHOD_Repaint + 1;
static const int pcode___movie__METHOD_Lower = pcode___movie__METHOD_Raise + 1;
static const int pcode___movie__METHOD_Close = pcode___movie__METHOD_Lower + 1;
static const int pcode___movie__METHOD_Open = pcode___movie__METHOD_Close + 1;
static const int pcode___movie__METHOD_SetFocus = pcode___movie__METHOD_Open + 1;
static const int pcode___movie__SETPROPERTY_Name = pcode___movie__METHOD_SetFocus + 1;
static const int pcode___movie__GETPROPERTY_Name = pcode___movie__SETPROPERTY_Name + 1;
static const int pcode___movie__SETPROPERTY_Group = pcode___movie__GETPROPERTY_Name + 1;
static const int pcode___movie__GETPROPERTY_Group = pcode___movie__SETPROPERTY_Group + 1;
static const int pcode___movie__SETPROPERTY_Background = pcode___movie__GETPROPERTY_Group + 1;
static const int pcode___movie__GETPROPERTY_Background = pcode___movie__SETPROPERTY_Background + 1;
static const int pcode___movie__SETPROPERTY_X = pcode___movie__GETPROPERTY_Background + 1;
static const int pcode___movie__GETPROPERTY_X = pcode___movie__SETPROPERTY_X + 1;
static const int pcode___movie__SETPROPERTY_Y = pcode___movie__GETPROPERTY_X + 1;
static const int pcode___movie__GETPROPERTY_Y = pcode___movie__SETPROPERTY_Y + 1;
static const int pcode___movie__SETPROPERTY_Width = pcode___movie__GETPROPERTY_Y + 1;
static const int pcode___movie__GETPROPERTY_Width = pcode___movie__SETPROPERTY_Width + 1;
static const int pcode___movie__SETPROPERTY_Height = pcode___movie__GETPROPERTY_Width + 1;
static const int pcode___movie__GETPROPERTY_Height = pcode___movie__SETPROPERTY_Height + 1;
static const int pcode___movie__GETPROPERTY_GlobalX = pcode___movie__GETPROPERTY_Height + 1;
static const int pcode___movie__GETPROPERTY_GlobalY = pcode___movie__GETPROPERTY_GlobalX + 1;
static const int pcode___movie__GETPROPERTY_OldX = pcode___movie__GETPROPERTY_GlobalY + 1;
static const int pcode___movie__GETPROPERTY_OldY = pcode___movie__GETPROPERTY_OldX + 1;
static const int pcode___movie__GETPROPERTY_OldWidth = pcode___movie__GETPROPERTY_OldY + 1;
static const int pcode___movie__GETPROPERTY_OldHeight = pcode___movie__GETPROPERTY_OldWidth + 1;
static const int pcode___movie__SETPROPERTY_MinimumWidth = pcode___movie__GETPROPERTY_OldHeight + 1;
static const int pcode___movie__GETPROPERTY_MinimumWidth = pcode___movie__SETPROPERTY_MinimumWidth + 1;
static const int pcode___movie__SETPROPERTY_MinimumHeight = pcode___movie__GETPROPERTY_MinimumWidth + 1;
static const int pcode___movie__GETPROPERTY_MinimumHeight = pcode___movie__SETPROPERTY_MinimumHeight + 1;
static const int pcode___movie__SETPROPERTY_MaximumWidth = pcode___movie__GETPROPERTY_MinimumHeight + 1;
static const int pcode___movie__GETPROPERTY_MaximumWidth = pcode___movie__SETPROPERTY_MaximumWidth + 1;
static const int pcode___movie__SETPROPERTY_MaximumHeight = pcode___movie__GETPROPERTY_MaximumWidth + 1;
static const int pcode___movie__GETPROPERTY_MaximumHeight = pcode___movie__SETPROPERTY_MaximumHeight + 1;
static const int pcode___movie__SETPROPERTY_Tag = pcode___movie__GETPROPERTY_MaximumHeight + 1;
static const int pcode___movie__GETPROPERTY_Tag = pcode___movie__SETPROPERTY_Tag + 1;
static const int pcode___movie__SETPROPERTY_CSV = pcode___movie__GETPROPERTY_Tag + 1;
static const int pcode___movie__GETPROPERTY_CSV = pcode___movie__SETPROPERTY_CSV + 1;
static const int pcode___movie__SETPROPERTY_ParentForm = pcode___movie__GETPROPERTY_CSV + 1;
static const int pcode___movie__GETPROPERTY_ParentForm = pcode___movie__SETPROPERTY_ParentForm + 1;
static const int pcode___movie__SETPROPERTY_ParentControl = pcode___movie__GETPROPERTY_ParentForm + 1;
static const int pcode___movie__GETPROPERTY_ParentControl = pcode___movie__SETPROPERTY_ParentControl + 1;
static const int pcode___movie__SETPROPERTY_DragDrop = pcode___movie__GETPROPERTY_ParentControl + 1;
static const int pcode___movie__GETPROPERTY_ParentControl1 = pcode___movie__SETPROPERTY_DragDrop + 1;
static const int pcode___movie__SETPROPERTY_ControlType = pcode___movie__GETPROPERTY_ParentControl1 + 1;
static const int pcode___movie__GETPROPERTY_ControlType = pcode___movie__SETPROPERTY_ControlType + 1;
static const int pcode___movie__SETPROPERTY_Focus = pcode___movie__GETPROPERTY_ControlType + 1;
static const int pcode___movie__GETPROPERTY_Focus = pcode___movie__SETPROPERTY_Focus + 1;
static const int pcode___movie__SETPROPERTY_FocusPolicy = pcode___movie__GETPROPERTY_Focus + 1;
static const int pcode___movie__GETPROPERTY_FocusPolicy = pcode___movie__SETPROPERTY_FocusPolicy + 1;
static const int pcode___movie__SETPROPERTY_FocusProxy = pcode___movie__GETPROPERTY_FocusPolicy + 1;
static const int pcode___movie__GETPROPERTY_FocusProxy = pcode___movie__SETPROPERTY_FocusProxy + 1;
static const int pcode___movie__SETPROPERTY_FocusOrder = pcode___movie__GETPROPERTY_FocusProxy + 1;
static const int pcode___movie__GETPROPERTY_FocusOrder = pcode___movie__SETPROPERTY_FocusOrder + 1;
static const int pcode___movie__SETPROPERTY_Cursor = pcode___movie__GETPROPERTY_FocusOrder + 1;
static const int pcode___movie__GETPROPERTY_Cursor = pcode___movie__SETPROPERTY_Cursor + 1;
static const int pcode___movie__SETPROPERTY_FontName = pcode___movie__GETPROPERTY_Cursor + 1;
static const int pcode___movie__GETPROPERTY_FontName = pcode___movie__SETPROPERTY_FontName + 1;
static const int pcode___movie__SETPROPERTY_FontSize = pcode___movie__GETPROPERTY_FontName + 1;
static const int pcode___movie__GETPROPERTY_FontSize = pcode___movie__SETPROPERTY_FontSize + 1;
static const int pcode___movie__SETPROPERTY_FontItalic = pcode___movie__GETPROPERTY_FontSize + 1;
static const int pcode___movie__GETPROPERTY_FontItalic = pcode___movie__SETPROPERTY_FontItalic + 1;
static const int pcode___movie__SETPROPERTY_FontBold = pcode___movie__GETPROPERTY_FontItalic + 1;
static const int pcode___movie__GETPROPERTY_FontBold = pcode___movie__SETPROPERTY_FontBold + 1;
static const int pcode___movie__SETPROPERTY_FontUnderline = pcode___movie__GETPROPERTY_FontBold + 1;
static const int pcode___movie__GETPROPERTY_FontUnderline = pcode___movie__SETPROPERTY_FontUnderline + 1;
static const int pcode___movie__SETPROPERTY_FontColor = pcode___movie__GETPROPERTY_FontUnderline + 1;
static const int pcode___movie__GETPROPERTY_FontColor = pcode___movie__SETPROPERTY_FontColor + 1;
static const int pcode___movie__SETPROPERTY_Enabled = pcode___movie__GETPROPERTY_FontColor + 1;
static const int pcode___movie__GETPROPERTY_Enabled = pcode___movie__SETPROPERTY_Enabled + 1;
static const int pcode___movie__SETPROPERTY_Visible = pcode___movie__GETPROPERTY_Enabled + 1;
static const int pcode___movie__GETPROPERTY_Visible = pcode___movie__SETPROPERTY_Visible + 1;
static const int pcode___movie__SETPROPERTY_StatusTip = pcode___movie__GETPROPERTY_Visible + 1;
static const int pcode___movie__GETPROPERTY_StatusTip = pcode___movie__SETPROPERTY_StatusTip + 1;
static const int pcode___movie__SETPROPERTY_ToolTip = pcode___movie__GETPROPERTY_StatusTip + 1;
static const int pcode___movie__GETPROPERTY_ToolTip = pcode___movie__SETPROPERTY_ToolTip + 1;
static const int pcode___movie__SETPROPERTY_StyleSheet = pcode___movie__GETPROPERTY_ToolTip + 1;
static const int pcode___movie__GETPROPERTY_StyleSheet = pcode___movie__SETPROPERTY_StyleSheet + 1;
static const int pcode___movie__SETPROPERTY_WhatsThis = pcode___movie__GETPROPERTY_StyleSheet + 1;
static const int pcode___movie__GETPROPERTY_WhatsThis = pcode___movie__SETPROPERTY_WhatsThis + 1;
static const int pcode___movie__SETPROPERTY_movieInterval = pcode___movie__GETPROPERTY_WhatsThis + 1;
static const int pcode___movie__GETPROPERTY_movieInterval = pcode___movie__SETPROPERTY_movieInterval + 1;
static const int pcode___movie__SETPROPERTY_Opacity = pcode___movie__GETPROPERTY_movieInterval + 1;
static const int pcode___movie__GETPROPERTY_Opacity = pcode___movie__SETPROPERTY_Opacity + 1;
static const int pcode___movie__SETPROPERTY_BoxIndex = pcode___movie__GETPROPERTY_Opacity + 1;
static const int pcode___movie__GETPROPERTY_BoxIndex = pcode___movie__SETPROPERTY_BoxIndex + 1;
static const int pcode___movie__SETPROPERTY_SplitIndex = pcode___movie__GETPROPERTY_BoxIndex + 1;
static const int pcode___movie__GETPROPERTY_SplitIndex = pcode___movie__SETPROPERTY_SplitIndex + 1;
static const int pcode___movie__SETPROPERTY_TabIndex = pcode___movie__GETPROPERTY_SplitIndex + 1;
static const int pcode___movie__GETPROPERTY_TabIndex = pcode___movie__SETPROPERTY_TabIndex + 1;
static const int pcode___movie__SETPROPERTY_BoxX = pcode___movie__GETPROPERTY_TabIndex + 1;
static const int pcode___movie__GETPROPERTY_BoxX = pcode___movie__SETPROPERTY_BoxX + 1;
static const int pcode___movie__SETPROPERTY_BoxY = pcode___movie__GETPROPERTY_BoxX + 1;
static const int pcode___movie__GETPROPERTY_BoxY = pcode___movie__SETPROPERTY_BoxY + 1;
static const int pcode___movie__SETPROPERTY_ParentIndex = pcode___movie__GETPROPERTY_BoxY + 1;
static const int pcode___movie__GETPROPERTY_ParentIndex = pcode___movie__SETPROPERTY_ParentIndex + 1;
static const int pcode___movie__SETPROPERTY_ControlType1 = pcode___movie__GETPROPERTY_ParentIndex + 1;
static const int pcode___movie__GETPROPERTY_ControlType1 = pcode___movie__SETPROPERTY_ControlType1 + 1;
static const int pcode___movie__SETPROPERTY_SQLName = pcode___movie__GETPROPERTY_ControlType1 + 1;
static const int pcode___movie__GETPROPERTY_SQLName = pcode___movie__SETPROPERTY_SQLName + 1;
static const int pcode___movie__SETPROPERTY_SQLType = pcode___movie__GETPROPERTY_SQLName + 1;
static const int pcode___movie__GETPROPERTY_SQLType = pcode___movie__SETPROPERTY_SQLType + 1;
static const int pcode___movie__SETPROPERTY_SQLCaption = pcode___movie__GETPROPERTY_SQLType + 1;
static const int pcode___movie__GETPROPERTY_SQLCaption = pcode___movie__SETPROPERTY_SQLCaption + 1;
static const int pcode___movie__SETPROPERTY_SQLWidth = pcode___movie__GETPROPERTY_SQLCaption + 1;
static const int pcode___movie__GETPROPERTY_SQLWidth = pcode___movie__SETPROPERTY_SQLWidth + 1;
static const int pcode___movie__EVENT_OnOpen = pcode___movie__GETPROPERTY_SQLWidth + 1;
static const int pcode___movie__EVENT_OnClose = pcode___movie__EVENT_OnOpen + 1;
static const int pcode___movie__EVENT_OnContextMenu = pcode___movie__EVENT_OnClose + 1;
static const int pcode___movie__EVENT_OnDragEnter = pcode___movie__EVENT_OnContextMenu + 1;
static const int pcode___movie__EVENT_OnDragExit = pcode___movie__EVENT_OnDragEnter + 1;
static const int pcode___movie__EVENT_OnDragMove = pcode___movie__EVENT_OnDragExit + 1;
static const int pcode___movie__EVENT_OnDrop = pcode___movie__EVENT_OnDragMove + 1;
static const int pcode___movie__EVENT_OnEnter = pcode___movie__EVENT_OnDrop + 1;
static const int pcode___movie__EVENT_OnGotFocus = pcode___movie__EVENT_OnEnter + 1;
static const int pcode___movie__EVENT_OnLostFocus = pcode___movie__EVENT_OnGotFocus + 1;
static const int pcode___movie__EVENT_OnHide = pcode___movie__EVENT_OnLostFocus + 1;
static const int pcode___movie__EVENT_OnKeyDown = pcode___movie__EVENT_OnHide + 1;
static const int pcode___movie__EVENT_OnKeyUp = pcode___movie__EVENT_OnKeyDown + 1;
static const int pcode___movie__EVENT_OnKeyPress = pcode___movie__EVENT_OnKeyUp + 1;
static const int pcode___movie__EVENT_OnExit = pcode___movie__EVENT_OnKeyPress + 1;
static const int pcode___movie__EVENT_OnDblClick = pcode___movie__EVENT_OnExit + 1;
static const int pcode___movie__EVENT_OnClick = pcode___movie__EVENT_OnDblClick + 1;
static const int pcode___movie__EVENT_OnMouseMove = pcode___movie__EVENT_OnClick + 1;
static const int pcode___movie__EVENT_OnMouseDown = pcode___movie__EVENT_OnMouseMove + 1;
static const int pcode___movie__EVENT_OnMouseUp = pcode___movie__EVENT_OnMouseDown + 1;
static const int pcode___movie__EVENT_OnMove = pcode___movie__EVENT_OnMouseUp + 1;
static const int pcode___movie__EVENT_OnPaint = pcode___movie__EVENT_OnMove + 1;
static const int pcode___movie__EVENT_OnResize = pcode___movie__EVENT_OnPaint + 1;
static const int pcode___movie__EVENT_OnShow = pcode___movie__EVENT_OnResize + 1;
static const int pcode___movie__EVENT_OnMouseWheel = pcode___movie__EVENT_OnShow + 1;
static const int pcode___movie__EVENT_OnTimer = pcode___movie__EVENT_OnMouseWheel + 1;
static const int pcode___movie__EVENT_OnPrint = pcode___movie__EVENT_OnTimer + 1;

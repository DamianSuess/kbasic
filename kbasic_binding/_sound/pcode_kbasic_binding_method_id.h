
static const int pcode___sound___sound = pcode___sound * SPACE;
static const int pcode___sound___sound1 = pcode___sound___sound + 1;



static const int pcode___sound__SETPROPERTY_MouseTracking = pcode___sound___sound1 + 1;
static const int pcode___sound__GETPROPERTY_MouseTracking = pcode___sound__SETPROPERTY_MouseTracking + 1; 


static const int pcode___sound__EVENT_OnSingleShot = pcode___sound__GETPROPERTY_MouseTracking + 1;
static const int pcode___sound__EVENT_OnEnabled = pcode___sound__EVENT_OnSingleShot + 1;
static const int pcode___sound__EVENT_OnDisabled = pcode___sound__EVENT_OnEnabled + 1;

static const int pcode___sound__SETPROPERTY_CursorAnimation = pcode___sound__EVENT_OnDisabled + 1;
static const int pcode___sound__GETPROPERTY_CursorAnimation = pcode___sound__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___sound__METHOD_DataIds = pcode___sound__GETPROPERTY_CursorAnimation + 1;

static const int pcode___sound__METHOD_DataRemove = pcode___sound__METHOD_DataIds + 1;
static const int pcode___sound__METHOD_DataRemoveAll = pcode___sound__METHOD_DataRemove + 1;
static const int pcode___sound__METHOD_DataSetBoolean = pcode___sound__METHOD_DataRemoveAll + 1;
static const int pcode___sound__METHOD_DataSetInteger = pcode___sound__METHOD_DataSetBoolean + 1;
static const int pcode___sound__METHOD_DataSetString = pcode___sound__METHOD_DataSetInteger + 1;
static const int pcode___sound__METHOD_DataSetDouble = pcode___sound__METHOD_DataSetString + 1;
static const int pcode___sound__METHOD_DataSetLong = pcode___sound__METHOD_DataSetDouble + 1;
static const int pcode___sound__METHOD_DataSetDecimal = pcode___sound__METHOD_DataSetLong + 1;
static const int pcode___sound__METHOD_DataSetDateTime = pcode___sound__METHOD_DataSetDecimal + 1;


static const int pcode___sound__METHOD_DataBoolean = pcode___sound__METHOD_DataSetDateTime + 1;
static const int pcode___sound__METHOD_DataInteger = pcode___sound__METHOD_DataBoolean + 1;
static const int pcode___sound__METHOD_DataString = pcode___sound__METHOD_DataInteger + 1;
static const int pcode___sound__METHOD_DataDouble = pcode___sound__METHOD_DataString + 1;
static const int pcode___sound__METHOD_DataLong = pcode___sound__METHOD_DataDouble + 1;
static const int pcode___sound__METHOD_DataDecimal = pcode___sound__METHOD_DataLong + 1;
static const int pcode___sound__METHOD_DataDateTime = pcode___sound__METHOD_DataDecimal + 1;

static const int pcode___sound__METHOD_ClearFocus = pcode___sound__METHOD_DataDateTime + 1;
static const int pcode___sound__METHOD_ToggleVisible = pcode___sound__METHOD_ClearFocus + 1;

static const int pcode___sound__METHOD_SingleShot = pcode___sound__METHOD_ToggleVisible + 1;
static const int pcode___sound__METHOD_StartTimer = pcode___sound__METHOD_SingleShot + 1;
static const int pcode___sound__METHOD_StopTimer = pcode___sound__METHOD_StartTimer + 1;


static const int pcode___sound__METHOD_GlobalX = pcode___sound__METHOD_StopTimer + 1;
static const int pcode___sound__METHOD_GlobalY = pcode___sound__METHOD_GlobalX + 1;
static const int pcode___sound__METHOD_LocalX = pcode___sound__METHOD_GlobalY + 1;
static const int pcode___sound__METHOD_LocalY = pcode___sound__METHOD_LocalX + 1;

static const int pcode___sound__METHOD_UnderMouse = pcode___sound__METHOD_LocalY + 1;

static const int pcode___sound__SETPROPERTY_Mask = pcode___sound__METHOD_UnderMouse + 1;
static const int pcode___sound__GETPROPERTY_Mask = pcode___sound__SETPROPERTY_Mask + 1;

static const int pcode___sound__SETPROPERTY_SoundOnEvent = pcode___sound__GETPROPERTY_Mask + 1;
static const int pcode___sound__GETPROPERTY_SoundOnEvent = pcode___sound__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___sound__SETPROPERTY_Left = pcode___sound__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___sound__GETPROPERTY_Left = pcode___sound__SETPROPERTY_Left + 1;
static const int pcode___sound__SETPROPERTY_Top = pcode___sound__GETPROPERTY_Left + 1;
static const int pcode___sound__GETPROPERTY_Top = pcode___sound__SETPROPERTY_Top + 1;

static const int pcode___sound__SETPROPERTY_LocalX = pcode___sound__GETPROPERTY_Top + 1;
static const int pcode___sound__GETPROPERTY_LocalX = pcode___sound__SETPROPERTY_LocalX + 1;
static const int pcode___sound__SETPROPERTY_LocalY = pcode___sound__GETPROPERTY_LocalX + 1;
static const int pcode___sound__GETPROPERTY_LocalY = pcode___sound__SETPROPERTY_LocalY + 1;

static const int pcode___sound__SETPROPERTY_DrawOnPaint = pcode___sound__GETPROPERTY_LocalY + 1;
static const int pcode___sound__GETPROPERTY_DrawOnPaint = pcode___sound__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___sound__SETPROPERTY_Palette = pcode___sound__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___sound__GETPROPERTY_Palette = pcode___sound__SETPROPERTY_Palette + 1;


static const int pcode___sound__SETPROPERTY_BackgroundStyle = pcode___sound__GETPROPERTY_Palette + 1;
static const int pcode___sound__GETPROPERTY_BackgroundStyle = pcode___sound__SETPROPERTY_BackgroundStyle + 1;


static const int pcode___sound__METHOD_State = pcode___sound__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___sound__METHOD_ErrorType = pcode___sound__METHOD_State + 1;
static const int pcode___sound__METHOD_ErrorString = pcode___sound__METHOD_ErrorType + 1;
static const int pcode___sound__METHOD_CurrentTime = pcode___sound__METHOD_ErrorString + 1;
static const int pcode___sound__METHOD_TotalTime = pcode___sound__METHOD_CurrentTime + 1;
static const int pcode___sound__METHOD_IsPlaying = pcode___sound__METHOD_TotalTime + 1;
static const int pcode___sound__METHOD_IsPaused = pcode___sound__METHOD_IsPlaying + 1;
static const int pcode___sound__METHOD_IsMuted = pcode___sound__METHOD_IsPaused + 1;
static const int pcode___sound__METHOD_IsSeekable = pcode___sound__METHOD_IsMuted + 1;
static const int pcode___sound__METHOD_Play = pcode___sound__METHOD_IsSeekable + 1;
static const int pcode___sound__METHOD_Play1 = pcode___sound__METHOD_Play + 1;
static const int pcode___sound__METHOD_Load = pcode___sound__METHOD_Play1 + 1;
static const int pcode___sound__METHOD_PlayInQueue = pcode___sound__METHOD_Load + 1;
static const int pcode___sound__METHOD_Pause = pcode___sound__METHOD_PlayInQueue + 1;
static const int pcode___sound__METHOD_Stop = pcode___sound__METHOD_Pause + 1;
static const int pcode___sound__METHOD_ClearQueue = pcode___sound__METHOD_Stop + 1;
static const int pcode___sound__METHOD_Seek = pcode___sound__METHOD_ClearQueue + 1;

static const int pcode___sound__SETPROPERTY_StringValue = pcode___sound__METHOD_Seek + 1;
static const int pcode___sound__GETPROPERTY_StringValue = pcode___sound__SETPROPERTY_StringValue + 1;

static const int pcode___sound__SETPROPERTY_TransitionTime = pcode___sound__GETPROPERTY_StringValue + 1;
static const int pcode___sound__GETPROPERTY_TransitionTime = pcode___sound__SETPROPERTY_TransitionTime + 1;

static const int pcode___sound__SETPROPERTY_Muted = pcode___sound__GETPROPERTY_TransitionTime + 1;
static const int pcode___sound__GETPROPERTY_Muted = pcode___sound__SETPROPERTY_Muted + 1;

static const int pcode___sound__SETPROPERTY_Volume = pcode___sound__GETPROPERTY_Muted + 1;
static const int pcode___sound__GETPROPERTY_Volume = pcode___sound__SETPROPERTY_Volume + 1;

static const int pcode___sound__SETPROPERTY_PrefinishMark = pcode___sound__GETPROPERTY_Volume + 1;
static const int pcode___sound__GETPROPERTY_PrefinishMark = pcode___sound__SETPROPERTY_PrefinishMark + 1;

static const int pcode___sound__SETPROPERTY_Tick = pcode___sound__GETPROPERTY_PrefinishMark + 1;
static const int pcode___sound__GETPROPERTY_Tick = pcode___sound__SETPROPERTY_Tick + 1;

static const int pcode___sound__EVENT_OnEvent = pcode___sound__GETPROPERTY_Tick + 1;
static const int pcode___sound__EVENT_OnTick = pcode___sound__EVENT_OnEvent + 1;
static const int pcode___sound__EVENT_OnStateChanged = pcode___sound__EVENT_OnTick + 1;
static const int pcode___sound__EVENT_OnAboutToFinish = pcode___sound__EVENT_OnStateChanged + 1;
static const int pcode___sound__EVENT_OnFinished = pcode___sound__EVENT_OnAboutToFinish + 1;
static const int pcode___sound__EVENT_OnMutedChanged = pcode___sound__EVENT_OnFinished + 1;
static const int pcode___sound__EVENT_OnVolumeChanged = pcode___sound__EVENT_OnMutedChanged + 1;
static const int pcode___sound__EVENT_OnPlayingTitleChanged = pcode___sound__EVENT_OnVolumeChanged + 1;
static const int pcode___sound__EVENT_OnBufferStatus = pcode___sound__EVENT_OnPlayingTitleChanged + 1;
static const int pcode___sound__EVENT_OnTotalTimeChanged = pcode___sound__EVENT_OnBufferStatus + 1;



static const int pcode___sound__SETPROPERTY_Layout = pcode___sound__EVENT_OnTotalTimeChanged + 1;
static const int pcode___sound__GETPROPERTY_Layout = pcode___sound__SETPROPERTY_Layout + 1;
static const int pcode___sound__METHOD_Move = pcode___sound__GETPROPERTY_Layout + 1;
static const int pcode___sound__METHOD_Resize = pcode___sound__METHOD_Move + 1;
static const int pcode___sound__METHOD_Show = pcode___sound__METHOD_Resize + 1;
static const int pcode___sound__METHOD_Hide = pcode___sound__METHOD_Show + 1;
static const int pcode___sound__METHOD_RepaintAlways = pcode___sound__METHOD_Hide + 1;
static const int pcode___sound__METHOD_Repaint = pcode___sound__METHOD_RepaintAlways + 1;
static const int pcode___sound__METHOD_Raise = pcode___sound__METHOD_Repaint + 1;
static const int pcode___sound__METHOD_Lower = pcode___sound__METHOD_Raise + 1;
static const int pcode___sound__METHOD_Close = pcode___sound__METHOD_Lower + 1;
static const int pcode___sound__METHOD_Open = pcode___sound__METHOD_Close + 1;
static const int pcode___sound__METHOD_SetFocus = pcode___sound__METHOD_Open + 1;
static const int pcode___sound__SETPROPERTY_Name = pcode___sound__METHOD_SetFocus + 1;
static const int pcode___sound__GETPROPERTY_Name = pcode___sound__SETPROPERTY_Name + 1;
static const int pcode___sound__SETPROPERTY_Group = pcode___sound__GETPROPERTY_Name + 1;
static const int pcode___sound__GETPROPERTY_Group = pcode___sound__SETPROPERTY_Group + 1;
static const int pcode___sound__SETPROPERTY_Background = pcode___sound__GETPROPERTY_Group + 1;
static const int pcode___sound__GETPROPERTY_Background = pcode___sound__SETPROPERTY_Background + 1;
static const int pcode___sound__SETPROPERTY_X = pcode___sound__GETPROPERTY_Background + 1;
static const int pcode___sound__GETPROPERTY_X = pcode___sound__SETPROPERTY_X + 1;
static const int pcode___sound__SETPROPERTY_Y = pcode___sound__GETPROPERTY_X + 1;
static const int pcode___sound__GETPROPERTY_Y = pcode___sound__SETPROPERTY_Y + 1;
static const int pcode___sound__SETPROPERTY_Width = pcode___sound__GETPROPERTY_Y + 1;
static const int pcode___sound__GETPROPERTY_Width = pcode___sound__SETPROPERTY_Width + 1;
static const int pcode___sound__SETPROPERTY_Height = pcode___sound__GETPROPERTY_Width + 1;
static const int pcode___sound__GETPROPERTY_Height = pcode___sound__SETPROPERTY_Height + 1;
static const int pcode___sound__GETPROPERTY_GlobalX = pcode___sound__GETPROPERTY_Height + 1;
static const int pcode___sound__GETPROPERTY_GlobalY = pcode___sound__GETPROPERTY_GlobalX + 1;
static const int pcode___sound__GETPROPERTY_OldX = pcode___sound__GETPROPERTY_GlobalY + 1;
static const int pcode___sound__GETPROPERTY_OldY = pcode___sound__GETPROPERTY_OldX + 1;
static const int pcode___sound__GETPROPERTY_OldWidth = pcode___sound__GETPROPERTY_OldY + 1;
static const int pcode___sound__GETPROPERTY_OldHeight = pcode___sound__GETPROPERTY_OldWidth + 1;
static const int pcode___sound__SETPROPERTY_MinimumWidth = pcode___sound__GETPROPERTY_OldHeight + 1;
static const int pcode___sound__GETPROPERTY_MinimumWidth = pcode___sound__SETPROPERTY_MinimumWidth + 1;
static const int pcode___sound__SETPROPERTY_MinimumHeight = pcode___sound__GETPROPERTY_MinimumWidth + 1;
static const int pcode___sound__GETPROPERTY_MinimumHeight = pcode___sound__SETPROPERTY_MinimumHeight + 1;
static const int pcode___sound__SETPROPERTY_MaximumWidth = pcode___sound__GETPROPERTY_MinimumHeight + 1;
static const int pcode___sound__GETPROPERTY_MaximumWidth = pcode___sound__SETPROPERTY_MaximumWidth + 1;
static const int pcode___sound__SETPROPERTY_MaximumHeight = pcode___sound__GETPROPERTY_MaximumWidth + 1;
static const int pcode___sound__GETPROPERTY_MaximumHeight = pcode___sound__SETPROPERTY_MaximumHeight + 1;
static const int pcode___sound__SETPROPERTY_Tag = pcode___sound__GETPROPERTY_MaximumHeight + 1;
static const int pcode___sound__GETPROPERTY_Tag = pcode___sound__SETPROPERTY_Tag + 1;
static const int pcode___sound__SETPROPERTY_CSV = pcode___sound__GETPROPERTY_Tag + 1;
static const int pcode___sound__GETPROPERTY_CSV = pcode___sound__SETPROPERTY_CSV + 1;
static const int pcode___sound__SETPROPERTY_ParentForm = pcode___sound__GETPROPERTY_CSV + 1;
static const int pcode___sound__GETPROPERTY_ParentForm = pcode___sound__SETPROPERTY_ParentForm + 1;
static const int pcode___sound__SETPROPERTY_ParentControl = pcode___sound__GETPROPERTY_ParentForm + 1;
static const int pcode___sound__GETPROPERTY_ParentControl = pcode___sound__SETPROPERTY_ParentControl + 1;
static const int pcode___sound__SETPROPERTY_DragDrop = pcode___sound__GETPROPERTY_ParentControl + 1;
static const int pcode___sound__GETPROPERTY_ParentControl1 = pcode___sound__SETPROPERTY_DragDrop + 1;
static const int pcode___sound__SETPROPERTY_ControlType = pcode___sound__GETPROPERTY_ParentControl1 + 1;
static const int pcode___sound__GETPROPERTY_ControlType = pcode___sound__SETPROPERTY_ControlType + 1;
static const int pcode___sound__SETPROPERTY_Focus = pcode___sound__GETPROPERTY_ControlType + 1;
static const int pcode___sound__GETPROPERTY_Focus = pcode___sound__SETPROPERTY_Focus + 1;
static const int pcode___sound__SETPROPERTY_FocusPolicy = pcode___sound__GETPROPERTY_Focus + 1;
static const int pcode___sound__GETPROPERTY_FocusPolicy = pcode___sound__SETPROPERTY_FocusPolicy + 1;
static const int pcode___sound__SETPROPERTY_FocusProxy = pcode___sound__GETPROPERTY_FocusPolicy + 1;
static const int pcode___sound__GETPROPERTY_FocusProxy = pcode___sound__SETPROPERTY_FocusProxy + 1;
static const int pcode___sound__SETPROPERTY_FocusOrder = pcode___sound__GETPROPERTY_FocusProxy + 1;
static const int pcode___sound__GETPROPERTY_FocusOrder = pcode___sound__SETPROPERTY_FocusOrder + 1;
static const int pcode___sound__SETPROPERTY_Cursor = pcode___sound__GETPROPERTY_FocusOrder + 1;
static const int pcode___sound__GETPROPERTY_Cursor = pcode___sound__SETPROPERTY_Cursor + 1;
static const int pcode___sound__SETPROPERTY_FontName = pcode___sound__GETPROPERTY_Cursor + 1;
static const int pcode___sound__GETPROPERTY_FontName = pcode___sound__SETPROPERTY_FontName + 1;
static const int pcode___sound__SETPROPERTY_FontSize = pcode___sound__GETPROPERTY_FontName + 1;
static const int pcode___sound__GETPROPERTY_FontSize = pcode___sound__SETPROPERTY_FontSize + 1;
static const int pcode___sound__SETPROPERTY_FontItalic = pcode___sound__GETPROPERTY_FontSize + 1;
static const int pcode___sound__GETPROPERTY_FontItalic = pcode___sound__SETPROPERTY_FontItalic + 1;
static const int pcode___sound__SETPROPERTY_FontBold = pcode___sound__GETPROPERTY_FontItalic + 1;
static const int pcode___sound__GETPROPERTY_FontBold = pcode___sound__SETPROPERTY_FontBold + 1;
static const int pcode___sound__SETPROPERTY_FontUnderline = pcode___sound__GETPROPERTY_FontBold + 1;
static const int pcode___sound__GETPROPERTY_FontUnderline = pcode___sound__SETPROPERTY_FontUnderline + 1;
static const int pcode___sound__SETPROPERTY_FontColor = pcode___sound__GETPROPERTY_FontUnderline + 1;
static const int pcode___sound__GETPROPERTY_FontColor = pcode___sound__SETPROPERTY_FontColor + 1;
static const int pcode___sound__SETPROPERTY_Enabled = pcode___sound__GETPROPERTY_FontColor + 1;
static const int pcode___sound__GETPROPERTY_Enabled = pcode___sound__SETPROPERTY_Enabled + 1;
static const int pcode___sound__SETPROPERTY_Visible = pcode___sound__GETPROPERTY_Enabled + 1;
static const int pcode___sound__GETPROPERTY_Visible = pcode___sound__SETPROPERTY_Visible + 1;
static const int pcode___sound__SETPROPERTY_StatusTip = pcode___sound__GETPROPERTY_Visible + 1;
static const int pcode___sound__GETPROPERTY_StatusTip = pcode___sound__SETPROPERTY_StatusTip + 1;
static const int pcode___sound__SETPROPERTY_ToolTip = pcode___sound__GETPROPERTY_StatusTip + 1;
static const int pcode___sound__GETPROPERTY_ToolTip = pcode___sound__SETPROPERTY_ToolTip + 1;
static const int pcode___sound__SETPROPERTY_StyleSheet = pcode___sound__GETPROPERTY_ToolTip + 1;
static const int pcode___sound__GETPROPERTY_StyleSheet = pcode___sound__SETPROPERTY_StyleSheet + 1;
static const int pcode___sound__SETPROPERTY_WhatsThis = pcode___sound__GETPROPERTY_StyleSheet + 1;
static const int pcode___sound__GETPROPERTY_WhatsThis = pcode___sound__SETPROPERTY_WhatsThis + 1;
static const int pcode___sound__SETPROPERTY_soundInterval = pcode___sound__GETPROPERTY_WhatsThis + 1;
static const int pcode___sound__GETPROPERTY_soundInterval = pcode___sound__SETPROPERTY_soundInterval + 1;
static const int pcode___sound__SETPROPERTY_Opacity = pcode___sound__GETPROPERTY_soundInterval + 1;
static const int pcode___sound__GETPROPERTY_Opacity = pcode___sound__SETPROPERTY_Opacity + 1;
static const int pcode___sound__SETPROPERTY_BoxIndex = pcode___sound__GETPROPERTY_Opacity + 1;
static const int pcode___sound__GETPROPERTY_BoxIndex = pcode___sound__SETPROPERTY_BoxIndex + 1;
static const int pcode___sound__SETPROPERTY_SplitIndex = pcode___sound__GETPROPERTY_BoxIndex + 1;
static const int pcode___sound__GETPROPERTY_SplitIndex = pcode___sound__SETPROPERTY_SplitIndex + 1;
static const int pcode___sound__SETPROPERTY_TabIndex = pcode___sound__GETPROPERTY_SplitIndex + 1;
static const int pcode___sound__GETPROPERTY_TabIndex = pcode___sound__SETPROPERTY_TabIndex + 1;
static const int pcode___sound__SETPROPERTY_BoxX = pcode___sound__GETPROPERTY_TabIndex + 1;
static const int pcode___sound__GETPROPERTY_BoxX = pcode___sound__SETPROPERTY_BoxX + 1;
static const int pcode___sound__SETPROPERTY_BoxY = pcode___sound__GETPROPERTY_BoxX + 1;
static const int pcode___sound__GETPROPERTY_BoxY = pcode___sound__SETPROPERTY_BoxY + 1;
static const int pcode___sound__SETPROPERTY_ParentIndex = pcode___sound__GETPROPERTY_BoxY + 1;
static const int pcode___sound__GETPROPERTY_ParentIndex = pcode___sound__SETPROPERTY_ParentIndex + 1;
static const int pcode___sound__SETPROPERTY_ControlType1 = pcode___sound__GETPROPERTY_ParentIndex + 1;
static const int pcode___sound__GETPROPERTY_ControlType1 = pcode___sound__SETPROPERTY_ControlType1 + 1;
static const int pcode___sound__SETPROPERTY_SQLName = pcode___sound__GETPROPERTY_ControlType1 + 1;
static const int pcode___sound__GETPROPERTY_SQLName = pcode___sound__SETPROPERTY_SQLName + 1;
static const int pcode___sound__SETPROPERTY_SQLType = pcode___sound__GETPROPERTY_SQLName + 1;
static const int pcode___sound__GETPROPERTY_SQLType = pcode___sound__SETPROPERTY_SQLType + 1;
static const int pcode___sound__SETPROPERTY_SQLCaption = pcode___sound__GETPROPERTY_SQLType + 1;
static const int pcode___sound__GETPROPERTY_SQLCaption = pcode___sound__SETPROPERTY_SQLCaption + 1;
static const int pcode___sound__SETPROPERTY_SQLWidth = pcode___sound__GETPROPERTY_SQLCaption + 1;
static const int pcode___sound__GETPROPERTY_SQLWidth = pcode___sound__SETPROPERTY_SQLWidth + 1;
static const int pcode___sound__EVENT_OnOpen = pcode___sound__GETPROPERTY_SQLWidth + 1;
static const int pcode___sound__EVENT_OnClose = pcode___sound__EVENT_OnOpen + 1;
static const int pcode___sound__EVENT_OnContextMenu = pcode___sound__EVENT_OnClose + 1;
static const int pcode___sound__EVENT_OnDragEnter = pcode___sound__EVENT_OnContextMenu + 1;
static const int pcode___sound__EVENT_OnDragExit = pcode___sound__EVENT_OnDragEnter + 1;
static const int pcode___sound__EVENT_OnDragMove = pcode___sound__EVENT_OnDragExit + 1;
static const int pcode___sound__EVENT_OnDrop = pcode___sound__EVENT_OnDragMove + 1;
static const int pcode___sound__EVENT_OnEnter = pcode___sound__EVENT_OnDrop + 1;
static const int pcode___sound__EVENT_OnGotFocus = pcode___sound__EVENT_OnEnter + 1;
static const int pcode___sound__EVENT_OnLostFocus = pcode___sound__EVENT_OnGotFocus + 1;
static const int pcode___sound__EVENT_OnHide = pcode___sound__EVENT_OnLostFocus + 1;
static const int pcode___sound__EVENT_OnKeyDown = pcode___sound__EVENT_OnHide + 1;
static const int pcode___sound__EVENT_OnKeyUp = pcode___sound__EVENT_OnKeyDown + 1;
static const int pcode___sound__EVENT_OnKeyPress = pcode___sound__EVENT_OnKeyUp + 1;
static const int pcode___sound__EVENT_OnExit = pcode___sound__EVENT_OnKeyPress + 1;
static const int pcode___sound__EVENT_OnDblClick = pcode___sound__EVENT_OnExit + 1;
static const int pcode___sound__EVENT_OnClick = pcode___sound__EVENT_OnDblClick + 1;
static const int pcode___sound__EVENT_OnMouseMove = pcode___sound__EVENT_OnClick + 1;
static const int pcode___sound__EVENT_OnMouseDown = pcode___sound__EVENT_OnMouseMove + 1;
static const int pcode___sound__EVENT_OnMouseUp = pcode___sound__EVENT_OnMouseDown + 1;
static const int pcode___sound__EVENT_OnMove = pcode___sound__EVENT_OnMouseUp + 1;
static const int pcode___sound__EVENT_OnPaint = pcode___sound__EVENT_OnMove + 1;
static const int pcode___sound__EVENT_OnResize = pcode___sound__EVENT_OnPaint + 1;
static const int pcode___sound__EVENT_OnShow = pcode___sound__EVENT_OnResize + 1;
static const int pcode___sound__EVENT_OnMouseWheel = pcode___sound__EVENT_OnShow + 1;
static const int pcode___sound__EVENT_OnTimer = pcode___sound__EVENT_OnMouseWheel + 1;
static const int pcode___sound__EVENT_OnPrint = pcode___sound__EVENT_OnTimer + 1;

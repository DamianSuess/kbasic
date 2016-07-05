static const int pcode___timer___timer = pcode___timer * SPACE;
static const int pcode___timer___timer1 = pcode___timer___timer + 1;


static const int pcode___timer__SETPROPERTY_MouseTracking = pcode___timer___timer1 + 1;
static const int pcode___timer__GETPROPERTY_MouseTracking = pcode___timer__SETPROPERTY_MouseTracking + 1; 


static const int pcode___timer__EVENT_OnSingleShot = pcode___timer__GETPROPERTY_MouseTracking + 1;
static const int pcode___timer__EVENT_OnEnabled = pcode___timer__EVENT_OnSingleShot + 1;
static const int pcode___timer__EVENT_OnDisabled = pcode___timer__EVENT_OnEnabled + 1;

static const int pcode___timer__SETPROPERTY_CursorAnimation = pcode___timer__EVENT_OnDisabled + 1;
static const int pcode___timer__GETPROPERTY_CursorAnimation = pcode___timer__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___timer__METHOD_DataIds = pcode___timer__GETPROPERTY_CursorAnimation + 1;

static const int pcode___timer__METHOD_DataRemove = pcode___timer__METHOD_DataIds + 1;
static const int pcode___timer__METHOD_DataRemoveAll = pcode___timer__METHOD_DataRemove + 1;
static const int pcode___timer__METHOD_DataSetBoolean = pcode___timer__METHOD_DataRemoveAll + 1;
static const int pcode___timer__METHOD_DataSetInteger = pcode___timer__METHOD_DataSetBoolean + 1;
static const int pcode___timer__METHOD_DataSetString = pcode___timer__METHOD_DataSetInteger + 1;
static const int pcode___timer__METHOD_DataSetDouble = pcode___timer__METHOD_DataSetString + 1;
static const int pcode___timer__METHOD_DataSetLong = pcode___timer__METHOD_DataSetDouble + 1;
static const int pcode___timer__METHOD_DataSetDecimal = pcode___timer__METHOD_DataSetLong + 1;
static const int pcode___timer__METHOD_DataSetDateTime = pcode___timer__METHOD_DataSetDecimal + 1;


static const int pcode___timer__METHOD_DataBoolean = pcode___timer__METHOD_DataSetDateTime + 1;
static const int pcode___timer__METHOD_DataInteger = pcode___timer__METHOD_DataBoolean + 1;
static const int pcode___timer__METHOD_DataString = pcode___timer__METHOD_DataInteger + 1;
static const int pcode___timer__METHOD_DataDouble = pcode___timer__METHOD_DataString + 1;
static const int pcode___timer__METHOD_DataLong = pcode___timer__METHOD_DataDouble + 1;
static const int pcode___timer__METHOD_DataDecimal = pcode___timer__METHOD_DataLong + 1;
static const int pcode___timer__METHOD_DataDateTime = pcode___timer__METHOD_DataDecimal + 1;

static const int pcode___timer__METHOD_ClearFocus = pcode___timer__METHOD_DataDateTime + 1;
static const int pcode___timer__METHOD_ToggleVisible = pcode___timer__METHOD_ClearFocus + 1;

static const int pcode___timer__METHOD_SingleShot = pcode___timer__METHOD_ToggleVisible + 1;
static const int pcode___timer__METHOD_StartTimer = pcode___timer__METHOD_SingleShot + 1;
static const int pcode___timer__METHOD_StopTimer = pcode___timer__METHOD_StartTimer + 1;

//static const int pcode___timer__METHOD_EventSender = pcode___timer__METHOD_StopTimer + 1;

static const int pcode___timer__METHOD_GlobalX = pcode___timer__METHOD_StopTimer + 1;
static const int pcode___timer__METHOD_GlobalY = pcode___timer__METHOD_GlobalX + 1;
static const int pcode___timer__METHOD_LocalX = pcode___timer__METHOD_GlobalY + 1;
static const int pcode___timer__METHOD_LocalY = pcode___timer__METHOD_LocalX + 1;

static const int pcode___timer__METHOD_UnderMouse = pcode___timer__METHOD_LocalY + 1;

static const int pcode___timer__SETPROPERTY_Mask = pcode___timer__METHOD_UnderMouse + 1;
static const int pcode___timer__GETPROPERTY_Mask = pcode___timer__SETPROPERTY_Mask + 1;

static const int pcode___timer__SETPROPERTY_SoundOnEvent = pcode___timer__GETPROPERTY_Mask + 1;
static const int pcode___timer__GETPROPERTY_SoundOnEvent = pcode___timer__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___timer__SETPROPERTY_Left = pcode___timer__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___timer__GETPROPERTY_Left = pcode___timer__SETPROPERTY_Left + 1;
static const int pcode___timer__SETPROPERTY_Top = pcode___timer__GETPROPERTY_Left + 1;
static const int pcode___timer__GETPROPERTY_Top = pcode___timer__SETPROPERTY_Top + 1;

static const int pcode___timer__SETPROPERTY_LocalX = pcode___timer__GETPROPERTY_Top + 1;
static const int pcode___timer__GETPROPERTY_LocalX = pcode___timer__SETPROPERTY_LocalX + 1;
static const int pcode___timer__SETPROPERTY_LocalY = pcode___timer__GETPROPERTY_LocalX + 1;
static const int pcode___timer__GETPROPERTY_LocalY = pcode___timer__SETPROPERTY_LocalY + 1;

static const int pcode___timer__SETPROPERTY_DrawOnPaint = pcode___timer__GETPROPERTY_LocalY + 1;
static const int pcode___timer__GETPROPERTY_DrawOnPaint = pcode___timer__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___timer__SETPROPERTY_Palette = pcode___timer__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___timer__GETPROPERTY_Palette = pcode___timer__SETPROPERTY_Palette + 1;


static const int pcode___timer__SETPROPERTY_BackgroundStyle = pcode___timer__GETPROPERTY_Palette + 1;
static const int pcode___timer__GETPROPERTY_BackgroundStyle = pcode___timer__SETPROPERTY_BackgroundStyle + 1;


static const int pcode___timer__SETPROPERTY_Layout = pcode___timer__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___timer__GETPROPERTY_Layout = pcode___timer__SETPROPERTY_Layout + 1;
static const int pcode___timer__SETPROPERTY_Interval = pcode___timer__GETPROPERTY_Layout + 1;
static const int pcode___timer__GETPROPERTY_Interval = pcode___timer__SETPROPERTY_Interval + 1;

static const int pcode___timer__SETPROPERTY_EventOnOpen = pcode___timer__GETPROPERTY_Interval + 1;
static const int pcode___timer__GETPROPERTY_EventOnOpen = pcode___timer__SETPROPERTY_EventOnOpen + 1;

static const int pcode___timer__METHOD_IsRunning = pcode___timer__GETPROPERTY_EventOnOpen + 1;
static const int pcode___timer__METHOD_Start = pcode___timer__METHOD_IsRunning + 1;
static const int pcode___timer__METHOD_Stop = pcode___timer__METHOD_Start + 1;
static const int pcode___timer__EVENT_OnEvent = pcode___timer__METHOD_Stop + 1;



static const int pcode___timer__METHOD_Move = pcode___timer__EVENT_OnEvent + 1;
static const int pcode___timer__METHOD_Resize = pcode___timer__METHOD_Move + 1;
static const int pcode___timer__METHOD_Show = pcode___timer__METHOD_Resize + 1;
static const int pcode___timer__METHOD_Hide = pcode___timer__METHOD_Show + 1;
static const int pcode___timer__METHOD_RepaintAlways = pcode___timer__METHOD_Hide + 1;
static const int pcode___timer__METHOD_Repaint = pcode___timer__METHOD_RepaintAlways + 1;
static const int pcode___timer__METHOD_Raise = pcode___timer__METHOD_Repaint + 1;
static const int pcode___timer__METHOD_Lower = pcode___timer__METHOD_Raise + 1;
static const int pcode___timer__METHOD_Close = pcode___timer__METHOD_Lower + 1;
static const int pcode___timer__METHOD_Open = pcode___timer__METHOD_Close + 1;
static const int pcode___timer__METHOD_SetFocus = pcode___timer__METHOD_Open + 1;
static const int pcode___timer__SETPROPERTY_Name = pcode___timer__METHOD_SetFocus + 1;
static const int pcode___timer__GETPROPERTY_Name = pcode___timer__SETPROPERTY_Name + 1;
static const int pcode___timer__SETPROPERTY_Group = pcode___timer__GETPROPERTY_Name + 1;
static const int pcode___timer__GETPROPERTY_Group = pcode___timer__SETPROPERTY_Group + 1;
static const int pcode___timer__SETPROPERTY_Background = pcode___timer__GETPROPERTY_Group + 1;
static const int pcode___timer__GETPROPERTY_Background = pcode___timer__SETPROPERTY_Background + 1;
static const int pcode___timer__SETPROPERTY_X = pcode___timer__GETPROPERTY_Background + 1;
static const int pcode___timer__GETPROPERTY_X = pcode___timer__SETPROPERTY_X + 1;
static const int pcode___timer__SETPROPERTY_Y = pcode___timer__GETPROPERTY_X + 1;
static const int pcode___timer__GETPROPERTY_Y = pcode___timer__SETPROPERTY_Y + 1;
static const int pcode___timer__SETPROPERTY_Width = pcode___timer__GETPROPERTY_Y + 1;
static const int pcode___timer__GETPROPERTY_Width = pcode___timer__SETPROPERTY_Width + 1;
static const int pcode___timer__SETPROPERTY_Height = pcode___timer__GETPROPERTY_Width + 1;
static const int pcode___timer__GETPROPERTY_Height = pcode___timer__SETPROPERTY_Height + 1;
static const int pcode___timer__GETPROPERTY_GlobalX = pcode___timer__GETPROPERTY_Height + 1;
static const int pcode___timer__GETPROPERTY_GlobalY = pcode___timer__GETPROPERTY_GlobalX + 1;
static const int pcode___timer__GETPROPERTY_OldX = pcode___timer__GETPROPERTY_GlobalY + 1;
static const int pcode___timer__GETPROPERTY_OldY = pcode___timer__GETPROPERTY_OldX + 1;
static const int pcode___timer__GETPROPERTY_OldWidth = pcode___timer__GETPROPERTY_OldY + 1;
static const int pcode___timer__GETPROPERTY_OldHeight = pcode___timer__GETPROPERTY_OldWidth + 1;
static const int pcode___timer__SETPROPERTY_MinimumWidth = pcode___timer__GETPROPERTY_OldHeight + 1;
static const int pcode___timer__GETPROPERTY_MinimumWidth = pcode___timer__SETPROPERTY_MinimumWidth + 1;
static const int pcode___timer__SETPROPERTY_MinimumHeight = pcode___timer__GETPROPERTY_MinimumWidth + 1;
static const int pcode___timer__GETPROPERTY_MinimumHeight = pcode___timer__SETPROPERTY_MinimumHeight + 1;
static const int pcode___timer__SETPROPERTY_MaximumWidth = pcode___timer__GETPROPERTY_MinimumHeight + 1;
static const int pcode___timer__GETPROPERTY_MaximumWidth = pcode___timer__SETPROPERTY_MaximumWidth + 1;
static const int pcode___timer__SETPROPERTY_MaximumHeight = pcode___timer__GETPROPERTY_MaximumWidth + 1;
static const int pcode___timer__GETPROPERTY_MaximumHeight = pcode___timer__SETPROPERTY_MaximumHeight + 1;
static const int pcode___timer__SETPROPERTY_Tag = pcode___timer__GETPROPERTY_MaximumHeight + 1;
static const int pcode___timer__GETPROPERTY_Tag = pcode___timer__SETPROPERTY_Tag + 1;
static const int pcode___timer__SETPROPERTY_CSV = pcode___timer__GETPROPERTY_Tag + 1;
static const int pcode___timer__GETPROPERTY_CSV = pcode___timer__SETPROPERTY_CSV + 1;
static const int pcode___timer__SETPROPERTY_ParentForm = pcode___timer__GETPROPERTY_CSV + 1;
static const int pcode___timer__GETPROPERTY_ParentForm = pcode___timer__SETPROPERTY_ParentForm + 1;
static const int pcode___timer__SETPROPERTY_ParentControl = pcode___timer__GETPROPERTY_ParentForm + 1;
static const int pcode___timer__GETPROPERTY_ParentControl = pcode___timer__SETPROPERTY_ParentControl + 1;
static const int pcode___timer__SETPROPERTY_DragDrop = pcode___timer__GETPROPERTY_ParentControl + 1;
static const int pcode___timer__GETPROPERTY_ParentControl1 = pcode___timer__SETPROPERTY_DragDrop + 1;
static const int pcode___timer__SETPROPERTY_ControlType = pcode___timer__GETPROPERTY_ParentControl1 + 1;
static const int pcode___timer__GETPROPERTY_ControlType = pcode___timer__SETPROPERTY_ControlType + 1;
static const int pcode___timer__SETPROPERTY_Focus = pcode___timer__GETPROPERTY_ControlType + 1;
static const int pcode___timer__GETPROPERTY_Focus = pcode___timer__SETPROPERTY_Focus + 1;
static const int pcode___timer__SETPROPERTY_FocusPolicy = pcode___timer__GETPROPERTY_Focus + 1;
static const int pcode___timer__GETPROPERTY_FocusPolicy = pcode___timer__SETPROPERTY_FocusPolicy + 1;
static const int pcode___timer__SETPROPERTY_FocusProxy = pcode___timer__GETPROPERTY_FocusPolicy + 1;
static const int pcode___timer__GETPROPERTY_FocusProxy = pcode___timer__SETPROPERTY_FocusProxy + 1;
static const int pcode___timer__SETPROPERTY_FocusOrder = pcode___timer__GETPROPERTY_FocusProxy + 1;
static const int pcode___timer__GETPROPERTY_FocusOrder = pcode___timer__SETPROPERTY_FocusOrder + 1;
static const int pcode___timer__SETPROPERTY_Cursor = pcode___timer__GETPROPERTY_FocusOrder + 1;
static const int pcode___timer__GETPROPERTY_Cursor = pcode___timer__SETPROPERTY_Cursor + 1;
static const int pcode___timer__SETPROPERTY_FontName = pcode___timer__GETPROPERTY_Cursor + 1;
static const int pcode___timer__GETPROPERTY_FontName = pcode___timer__SETPROPERTY_FontName + 1;
static const int pcode___timer__SETPROPERTY_FontSize = pcode___timer__GETPROPERTY_FontName + 1;
static const int pcode___timer__GETPROPERTY_FontSize = pcode___timer__SETPROPERTY_FontSize + 1;
static const int pcode___timer__SETPROPERTY_FontItalic = pcode___timer__GETPROPERTY_FontSize + 1;
static const int pcode___timer__GETPROPERTY_FontItalic = pcode___timer__SETPROPERTY_FontItalic + 1;
static const int pcode___timer__SETPROPERTY_FontBold = pcode___timer__GETPROPERTY_FontItalic + 1;
static const int pcode___timer__GETPROPERTY_FontBold = pcode___timer__SETPROPERTY_FontBold + 1;
static const int pcode___timer__SETPROPERTY_FontUnderline = pcode___timer__GETPROPERTY_FontBold + 1;
static const int pcode___timer__GETPROPERTY_FontUnderline = pcode___timer__SETPROPERTY_FontUnderline + 1;
static const int pcode___timer__SETPROPERTY_FontColor = pcode___timer__GETPROPERTY_FontUnderline + 1;
static const int pcode___timer__GETPROPERTY_FontColor = pcode___timer__SETPROPERTY_FontColor + 1;
static const int pcode___timer__SETPROPERTY_Enabled = pcode___timer__GETPROPERTY_FontColor + 1;
static const int pcode___timer__GETPROPERTY_Enabled = pcode___timer__SETPROPERTY_Enabled + 1;
static const int pcode___timer__SETPROPERTY_Visible = pcode___timer__GETPROPERTY_Enabled + 1;
static const int pcode___timer__GETPROPERTY_Visible = pcode___timer__SETPROPERTY_Visible + 1;
static const int pcode___timer__SETPROPERTY_StatusTip = pcode___timer__GETPROPERTY_Visible + 1;
static const int pcode___timer__GETPROPERTY_StatusTip = pcode___timer__SETPROPERTY_StatusTip + 1;
static const int pcode___timer__SETPROPERTY_ToolTip = pcode___timer__GETPROPERTY_StatusTip + 1;
static const int pcode___timer__GETPROPERTY_ToolTip = pcode___timer__SETPROPERTY_ToolTip + 1;
static const int pcode___timer__SETPROPERTY_StyleSheet = pcode___timer__GETPROPERTY_ToolTip + 1;
static const int pcode___timer__GETPROPERTY_StyleSheet = pcode___timer__SETPROPERTY_StyleSheet + 1;
static const int pcode___timer__SETPROPERTY_WhatsThis = pcode___timer__GETPROPERTY_StyleSheet + 1;
static const int pcode___timer__GETPROPERTY_WhatsThis = pcode___timer__SETPROPERTY_WhatsThis + 1;
static const int pcode___timer__SETPROPERTY_TimerInterval = pcode___timer__GETPROPERTY_WhatsThis + 1;
static const int pcode___timer__GETPROPERTY_TimerInterval = pcode___timer__SETPROPERTY_TimerInterval + 1;
static const int pcode___timer__SETPROPERTY_Opacity = pcode___timer__GETPROPERTY_TimerInterval + 1;
static const int pcode___timer__GETPROPERTY_Opacity = pcode___timer__SETPROPERTY_Opacity + 1;
static const int pcode___timer__SETPROPERTY_BoxIndex = pcode___timer__GETPROPERTY_Opacity + 1;
static const int pcode___timer__GETPROPERTY_BoxIndex = pcode___timer__SETPROPERTY_BoxIndex + 1;
static const int pcode___timer__SETPROPERTY_SplitIndex = pcode___timer__GETPROPERTY_BoxIndex + 1;
static const int pcode___timer__GETPROPERTY_SplitIndex = pcode___timer__SETPROPERTY_SplitIndex + 1;
static const int pcode___timer__SETPROPERTY_TabIndex = pcode___timer__GETPROPERTY_SplitIndex + 1;
static const int pcode___timer__GETPROPERTY_TabIndex = pcode___timer__SETPROPERTY_TabIndex + 1;
static const int pcode___timer__SETPROPERTY_BoxX = pcode___timer__GETPROPERTY_TabIndex + 1;
static const int pcode___timer__GETPROPERTY_BoxX = pcode___timer__SETPROPERTY_BoxX + 1;
static const int pcode___timer__SETPROPERTY_BoxY = pcode___timer__GETPROPERTY_BoxX + 1;
static const int pcode___timer__GETPROPERTY_BoxY = pcode___timer__SETPROPERTY_BoxY + 1;
static const int pcode___timer__SETPROPERTY_ParentIndex = pcode___timer__GETPROPERTY_BoxY + 1;
static const int pcode___timer__GETPROPERTY_ParentIndex = pcode___timer__SETPROPERTY_ParentIndex + 1;
static const int pcode___timer__SETPROPERTY_ControlType1 = pcode___timer__GETPROPERTY_ParentIndex + 1;
static const int pcode___timer__GETPROPERTY_ControlType1 = pcode___timer__SETPROPERTY_ControlType1 + 1;
static const int pcode___timer__SETPROPERTY_SQLName = pcode___timer__GETPROPERTY_ControlType1 + 1;
static const int pcode___timer__GETPROPERTY_SQLName = pcode___timer__SETPROPERTY_SQLName + 1;
static const int pcode___timer__SETPROPERTY_SQLType = pcode___timer__GETPROPERTY_SQLName + 1;
static const int pcode___timer__GETPROPERTY_SQLType = pcode___timer__SETPROPERTY_SQLType + 1;
static const int pcode___timer__SETPROPERTY_SQLCaption = pcode___timer__GETPROPERTY_SQLType + 1;
static const int pcode___timer__GETPROPERTY_SQLCaption = pcode___timer__SETPROPERTY_SQLCaption + 1;
static const int pcode___timer__SETPROPERTY_SQLWidth = pcode___timer__GETPROPERTY_SQLCaption + 1;
static const int pcode___timer__GETPROPERTY_SQLWidth = pcode___timer__SETPROPERTY_SQLWidth + 1;
static const int pcode___timer__EVENT_OnOpen = pcode___timer__GETPROPERTY_SQLWidth + 1;
static const int pcode___timer__EVENT_OnClose = pcode___timer__EVENT_OnOpen + 1;
static const int pcode___timer__EVENT_OnContextMenu = pcode___timer__EVENT_OnClose + 1;
static const int pcode___timer__EVENT_OnDragEnter = pcode___timer__EVENT_OnContextMenu + 1;
static const int pcode___timer__EVENT_OnDragExit = pcode___timer__EVENT_OnDragEnter + 1;
static const int pcode___timer__EVENT_OnDragMove = pcode___timer__EVENT_OnDragExit + 1;
static const int pcode___timer__EVENT_OnDrop = pcode___timer__EVENT_OnDragMove + 1;
static const int pcode___timer__EVENT_OnEnter = pcode___timer__EVENT_OnDrop + 1;
static const int pcode___timer__EVENT_OnGotFocus = pcode___timer__EVENT_OnEnter + 1;
static const int pcode___timer__EVENT_OnLostFocus = pcode___timer__EVENT_OnGotFocus + 1;
static const int pcode___timer__EVENT_OnHide = pcode___timer__EVENT_OnLostFocus + 1;
static const int pcode___timer__EVENT_OnKeyDown = pcode___timer__EVENT_OnHide + 1;
static const int pcode___timer__EVENT_OnKeyUp = pcode___timer__EVENT_OnKeyDown + 1;
static const int pcode___timer__EVENT_OnKeyPress = pcode___timer__EVENT_OnKeyUp + 1;
static const int pcode___timer__EVENT_OnExit = pcode___timer__EVENT_OnKeyPress + 1;
static const int pcode___timer__EVENT_OnDblClick = pcode___timer__EVENT_OnExit + 1;
static const int pcode___timer__EVENT_OnClick = pcode___timer__EVENT_OnDblClick + 1;
static const int pcode___timer__EVENT_OnMouseMove = pcode___timer__EVENT_OnClick + 1;
static const int pcode___timer__EVENT_OnMouseDown = pcode___timer__EVENT_OnMouseMove + 1;
static const int pcode___timer__EVENT_OnMouseUp = pcode___timer__EVENT_OnMouseDown + 1;
static const int pcode___timer__EVENT_OnMove = pcode___timer__EVENT_OnMouseUp + 1;
static const int pcode___timer__EVENT_OnPaint = pcode___timer__EVENT_OnMove + 1;
static const int pcode___timer__EVENT_OnResize = pcode___timer__EVENT_OnPaint + 1;
static const int pcode___timer__EVENT_OnShow = pcode___timer__EVENT_OnResize + 1;
static const int pcode___timer__EVENT_OnMouseWheel = pcode___timer__EVENT_OnShow + 1;
static const int pcode___timer__EVENT_OnTimer = pcode___timer__EVENT_OnMouseWheel + 1;
static const int pcode___timer__EVENT_OnPrint = pcode___timer__EVENT_OnTimer + 1;
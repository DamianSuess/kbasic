static const int pcode___udpsocket___udpsocket = pcode___udpsocket * SPACE;
static const int pcode___udpsocket___udpsocket1 = pcode___udpsocket___udpsocket + 1;


static const int pcode___udpsocket__SETPROPERTY_MouseTracking = pcode___udpsocket___udpsocket1 + 1;
static const int pcode___udpsocket__GETPROPERTY_MouseTracking = pcode___udpsocket__SETPROPERTY_MouseTracking + 1; 

static const int pcode___udpsocket__EVENT_OnSingleShot = pcode___udpsocket__GETPROPERTY_MouseTracking + 1;
static const int pcode___udpsocket__EVENT_OnEnabled = pcode___udpsocket__EVENT_OnSingleShot + 1;
static const int pcode___udpsocket__EVENT_OnDisabled = pcode___udpsocket__EVENT_OnEnabled + 1;

static const int pcode___udpsocket__SETPROPERTY_CursorAnimation = pcode___udpsocket__EVENT_OnDisabled + 1;
static const int pcode___udpsocket__GETPROPERTY_CursorAnimation = pcode___udpsocket__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___udpsocket__METHOD_DataIds = pcode___udpsocket__GETPROPERTY_CursorAnimation + 1;

static const int pcode___udpsocket__METHOD_DataRemove = pcode___udpsocket__METHOD_DataIds + 1;
static const int pcode___udpsocket__METHOD_DataRemoveAll = pcode___udpsocket__METHOD_DataRemove + 1;
static const int pcode___udpsocket__METHOD_DataSetBoolean = pcode___udpsocket__METHOD_DataRemoveAll + 1;
static const int pcode___udpsocket__METHOD_DataSetInteger = pcode___udpsocket__METHOD_DataSetBoolean + 1;
static const int pcode___udpsocket__METHOD_DataSetString = pcode___udpsocket__METHOD_DataSetInteger + 1;
static const int pcode___udpsocket__METHOD_DataSetDouble = pcode___udpsocket__METHOD_DataSetString + 1;
static const int pcode___udpsocket__METHOD_DataSetLong = pcode___udpsocket__METHOD_DataSetDouble + 1;
static const int pcode___udpsocket__METHOD_DataSetDecimal = pcode___udpsocket__METHOD_DataSetLong + 1;
static const int pcode___udpsocket__METHOD_DataSetDateTime = pcode___udpsocket__METHOD_DataSetDecimal + 1;


static const int pcode___udpsocket__METHOD_DataBoolean = pcode___udpsocket__METHOD_DataSetDateTime + 1;
static const int pcode___udpsocket__METHOD_DataInteger = pcode___udpsocket__METHOD_DataBoolean + 1;
static const int pcode___udpsocket__METHOD_DataString = pcode___udpsocket__METHOD_DataInteger + 1;
static const int pcode___udpsocket__METHOD_DataDouble = pcode___udpsocket__METHOD_DataString + 1;
static const int pcode___udpsocket__METHOD_DataLong = pcode___udpsocket__METHOD_DataDouble + 1;
static const int pcode___udpsocket__METHOD_DataDecimal = pcode___udpsocket__METHOD_DataLong + 1;
static const int pcode___udpsocket__METHOD_DataDateTime = pcode___udpsocket__METHOD_DataDecimal + 1;

static const int pcode___udpsocket__METHOD_ClearFocus = pcode___udpsocket__METHOD_DataDateTime + 1;
static const int pcode___udpsocket__METHOD_ToggleVisible = pcode___udpsocket__METHOD_ClearFocus + 1;

static const int pcode___udpsocket__METHOD_SingleShot = pcode___udpsocket__METHOD_ToggleVisible + 1;
static const int pcode___udpsocket__METHOD_StartTimer = pcode___udpsocket__METHOD_SingleShot + 1;
static const int pcode___udpsocket__METHOD_StopTimer = pcode___udpsocket__METHOD_StartTimer + 1;

static const int pcode___udpsocket__METHOD_GlobalX = pcode___udpsocket__METHOD_StopTimer + 1;
static const int pcode___udpsocket__METHOD_GlobalY = pcode___udpsocket__METHOD_GlobalX + 1;
static const int pcode___udpsocket__METHOD_LocalX = pcode___udpsocket__METHOD_GlobalY + 1;
static const int pcode___udpsocket__METHOD_LocalY = pcode___udpsocket__METHOD_LocalX + 1;

static const int pcode___udpsocket__METHOD_UnderMouse = pcode___udpsocket__METHOD_LocalY + 1;

static const int pcode___udpsocket__SETPROPERTY_Mask = pcode___udpsocket__METHOD_UnderMouse + 1;
static const int pcode___udpsocket__GETPROPERTY_Mask = pcode___udpsocket__SETPROPERTY_Mask + 1;

static const int pcode___udpsocket__SETPROPERTY_SoundOnEvent = pcode___udpsocket__GETPROPERTY_Mask + 1;
static const int pcode___udpsocket__GETPROPERTY_SoundOnEvent = pcode___udpsocket__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___udpsocket__SETPROPERTY_Left = pcode___udpsocket__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___udpsocket__GETPROPERTY_Left = pcode___udpsocket__SETPROPERTY_Left + 1;
static const int pcode___udpsocket__SETPROPERTY_Top = pcode___udpsocket__GETPROPERTY_Left + 1;
static const int pcode___udpsocket__GETPROPERTY_Top = pcode___udpsocket__SETPROPERTY_Top + 1;

static const int pcode___udpsocket__SETPROPERTY_LocalX = pcode___udpsocket__GETPROPERTY_Top + 1;
static const int pcode___udpsocket__GETPROPERTY_LocalX = pcode___udpsocket__SETPROPERTY_LocalX + 1;
static const int pcode___udpsocket__SETPROPERTY_LocalY = pcode___udpsocket__GETPROPERTY_LocalX + 1;
static const int pcode___udpsocket__GETPROPERTY_LocalY = pcode___udpsocket__SETPROPERTY_LocalY + 1;

static const int pcode___udpsocket__SETPROPERTY_DrawOnPaint = pcode___udpsocket__GETPROPERTY_LocalY + 1;
static const int pcode___udpsocket__GETPROPERTY_DrawOnPaint = pcode___udpsocket__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___udpsocket__SETPROPERTY_Palette = pcode___udpsocket__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___udpsocket__GETPROPERTY_Palette = pcode___udpsocket__SETPROPERTY_Palette + 1;


static const int pcode___udpsocket__SETPROPERTY_BackgroundStyle = pcode___udpsocket__GETPROPERTY_Palette + 1;
static const int pcode___udpsocket__GETPROPERTY_BackgroundStyle = pcode___udpsocket__SETPROPERTY_BackgroundStyle + 1;


//static const int pcode___udpsocket__METHOD_Open = pcode___udpsocket___udpsocket + 1;
//static const int pcode___udpsocket__METHOD_Close = pcode___udpsocket__METHOD_IsWritable + 1;

static const int pcode___udpsocket__METHOD_Bind = pcode___udpsocket__GETPROPERTY_BackgroundStyle + 1;

static const int pcode___udpsocket__METHOD_ReadData = pcode___udpsocket__METHOD_Bind + 1;
static const int pcode___udpsocket__METHOD_WriteData = pcode___udpsocket__METHOD_ReadData + 1;
static const int pcode___udpsocket__METHOD_LastError = pcode___udpsocket__METHOD_WriteData + 1;
static const int pcode___udpsocket__METHOD_LastErrorText = pcode___udpsocket__METHOD_LastError + 1;

static const int pcode___udpsocket__SETPROPERTY_HostAddress = pcode___udpsocket__METHOD_LastErrorText + 1;
static const int pcode___udpsocket__GETPROPERTY_HostAddress = pcode___udpsocket__SETPROPERTY_HostAddress + 1;
static const int pcode___udpsocket__SETPROPERTY_Port = pcode___udpsocket__GETPROPERTY_HostAddress + 1;
static const int pcode___udpsocket__GETPROPERTY_Port = pcode___udpsocket__SETPROPERTY_Port + 1;


static const int pcode___udpsocket__EVENT_OnEvent = pcode___udpsocket__GETPROPERTY_Port + 1;

static const int pcode___udpsocket__SETPROPERTY_Layout = pcode___udpsocket__EVENT_OnEvent + 1;
static const int pcode___udpsocket__GETPROPERTY_Layout = pcode___udpsocket__SETPROPERTY_Layout + 1;
static const int pcode___udpsocket__METHOD_Move = pcode___udpsocket__GETPROPERTY_Layout + 1;
static const int pcode___udpsocket__METHOD_Resize = pcode___udpsocket__METHOD_Move + 1;
static const int pcode___udpsocket__METHOD_Show = pcode___udpsocket__METHOD_Resize + 1;
static const int pcode___udpsocket__METHOD_Hide = pcode___udpsocket__METHOD_Show + 1;
static const int pcode___udpsocket__METHOD_RepaintAlways = pcode___udpsocket__METHOD_Hide + 1;
static const int pcode___udpsocket__METHOD_Repaint = pcode___udpsocket__METHOD_RepaintAlways + 1;
static const int pcode___udpsocket__METHOD_Raise = pcode___udpsocket__METHOD_Repaint + 1;
static const int pcode___udpsocket__METHOD_Lower = pcode___udpsocket__METHOD_Raise + 1;
static const int pcode___udpsocket__METHOD_Close = pcode___udpsocket__METHOD_Lower + 1;
static const int pcode___udpsocket__METHOD_Open = pcode___udpsocket__METHOD_Close + 1;
static const int pcode___udpsocket__METHOD_SetFocus = pcode___udpsocket__METHOD_Open + 1;
static const int pcode___udpsocket__SETPROPERTY_Name = pcode___udpsocket__METHOD_SetFocus + 1;
static const int pcode___udpsocket__GETPROPERTY_Name = pcode___udpsocket__SETPROPERTY_Name + 1;
static const int pcode___udpsocket__SETPROPERTY_Group = pcode___udpsocket__GETPROPERTY_Name + 1;
static const int pcode___udpsocket__GETPROPERTY_Group = pcode___udpsocket__SETPROPERTY_Group + 1;
static const int pcode___udpsocket__SETPROPERTY_Background = pcode___udpsocket__GETPROPERTY_Group + 1;
static const int pcode___udpsocket__GETPROPERTY_Background = pcode___udpsocket__SETPROPERTY_Background + 1;
static const int pcode___udpsocket__SETPROPERTY_X = pcode___udpsocket__GETPROPERTY_Background + 1;
static const int pcode___udpsocket__GETPROPERTY_X = pcode___udpsocket__SETPROPERTY_X + 1;
static const int pcode___udpsocket__SETPROPERTY_Y = pcode___udpsocket__GETPROPERTY_X + 1;
static const int pcode___udpsocket__GETPROPERTY_Y = pcode___udpsocket__SETPROPERTY_Y + 1;
static const int pcode___udpsocket__SETPROPERTY_Width = pcode___udpsocket__GETPROPERTY_Y + 1;
static const int pcode___udpsocket__GETPROPERTY_Width = pcode___udpsocket__SETPROPERTY_Width + 1;
static const int pcode___udpsocket__SETPROPERTY_Height = pcode___udpsocket__GETPROPERTY_Width + 1;
static const int pcode___udpsocket__GETPROPERTY_Height = pcode___udpsocket__SETPROPERTY_Height + 1;
static const int pcode___udpsocket__GETPROPERTY_GlobalX = pcode___udpsocket__GETPROPERTY_Height + 1;
static const int pcode___udpsocket__GETPROPERTY_GlobalY = pcode___udpsocket__GETPROPERTY_GlobalX + 1;
static const int pcode___udpsocket__GETPROPERTY_OldX = pcode___udpsocket__GETPROPERTY_GlobalY + 1;
static const int pcode___udpsocket__GETPROPERTY_OldY = pcode___udpsocket__GETPROPERTY_OldX + 1;
static const int pcode___udpsocket__GETPROPERTY_OldWidth = pcode___udpsocket__GETPROPERTY_OldY + 1;
static const int pcode___udpsocket__GETPROPERTY_OldHeight = pcode___udpsocket__GETPROPERTY_OldWidth + 1;
static const int pcode___udpsocket__SETPROPERTY_MinimumWidth = pcode___udpsocket__GETPROPERTY_OldHeight + 1;
static const int pcode___udpsocket__GETPROPERTY_MinimumWidth = pcode___udpsocket__SETPROPERTY_MinimumWidth + 1;
static const int pcode___udpsocket__SETPROPERTY_MinimumHeight = pcode___udpsocket__GETPROPERTY_MinimumWidth + 1;
static const int pcode___udpsocket__GETPROPERTY_MinimumHeight = pcode___udpsocket__SETPROPERTY_MinimumHeight + 1;
static const int pcode___udpsocket__SETPROPERTY_MaximumWidth = pcode___udpsocket__GETPROPERTY_MinimumHeight + 1;
static const int pcode___udpsocket__GETPROPERTY_MaximumWidth = pcode___udpsocket__SETPROPERTY_MaximumWidth + 1;
static const int pcode___udpsocket__SETPROPERTY_MaximumHeight = pcode___udpsocket__GETPROPERTY_MaximumWidth + 1;
static const int pcode___udpsocket__GETPROPERTY_MaximumHeight = pcode___udpsocket__SETPROPERTY_MaximumHeight + 1;
static const int pcode___udpsocket__SETPROPERTY_Tag = pcode___udpsocket__GETPROPERTY_MaximumHeight + 1;
static const int pcode___udpsocket__GETPROPERTY_Tag = pcode___udpsocket__SETPROPERTY_Tag + 1;
static const int pcode___udpsocket__SETPROPERTY_CSV = pcode___udpsocket__GETPROPERTY_Tag + 1;
static const int pcode___udpsocket__GETPROPERTY_CSV = pcode___udpsocket__SETPROPERTY_CSV + 1;
static const int pcode___udpsocket__SETPROPERTY_ParentForm = pcode___udpsocket__GETPROPERTY_CSV + 1;
static const int pcode___udpsocket__GETPROPERTY_ParentForm = pcode___udpsocket__SETPROPERTY_ParentForm + 1;
static const int pcode___udpsocket__SETPROPERTY_ParentControl = pcode___udpsocket__GETPROPERTY_ParentForm + 1;
static const int pcode___udpsocket__GETPROPERTY_ParentControl = pcode___udpsocket__SETPROPERTY_ParentControl + 1;
static const int pcode___udpsocket__SETPROPERTY_DragDrop = pcode___udpsocket__GETPROPERTY_ParentControl + 1;
static const int pcode___udpsocket__GETPROPERTY_ParentControl1 = pcode___udpsocket__SETPROPERTY_DragDrop + 1;
static const int pcode___udpsocket__SETPROPERTY_ControlType = pcode___udpsocket__GETPROPERTY_ParentControl1 + 1;
static const int pcode___udpsocket__GETPROPERTY_ControlType = pcode___udpsocket__SETPROPERTY_ControlType + 1;
static const int pcode___udpsocket__SETPROPERTY_Focus = pcode___udpsocket__GETPROPERTY_ControlType + 1;
static const int pcode___udpsocket__GETPROPERTY_Focus = pcode___udpsocket__SETPROPERTY_Focus + 1;
static const int pcode___udpsocket__SETPROPERTY_FocusPolicy = pcode___udpsocket__GETPROPERTY_Focus + 1;
static const int pcode___udpsocket__GETPROPERTY_FocusPolicy = pcode___udpsocket__SETPROPERTY_FocusPolicy + 1;
static const int pcode___udpsocket__SETPROPERTY_FocusProxy = pcode___udpsocket__GETPROPERTY_FocusPolicy + 1;
static const int pcode___udpsocket__GETPROPERTY_FocusProxy = pcode___udpsocket__SETPROPERTY_FocusProxy + 1;
static const int pcode___udpsocket__SETPROPERTY_FocusOrder = pcode___udpsocket__GETPROPERTY_FocusProxy + 1;
static const int pcode___udpsocket__GETPROPERTY_FocusOrder = pcode___udpsocket__SETPROPERTY_FocusOrder + 1;
static const int pcode___udpsocket__SETPROPERTY_Cursor = pcode___udpsocket__GETPROPERTY_FocusOrder + 1;
static const int pcode___udpsocket__GETPROPERTY_Cursor = pcode___udpsocket__SETPROPERTY_Cursor + 1;
static const int pcode___udpsocket__SETPROPERTY_FontName = pcode___udpsocket__GETPROPERTY_Cursor + 1;
static const int pcode___udpsocket__GETPROPERTY_FontName = pcode___udpsocket__SETPROPERTY_FontName + 1;
static const int pcode___udpsocket__SETPROPERTY_FontSize = pcode___udpsocket__GETPROPERTY_FontName + 1;
static const int pcode___udpsocket__GETPROPERTY_FontSize = pcode___udpsocket__SETPROPERTY_FontSize + 1;
static const int pcode___udpsocket__SETPROPERTY_FontItalic = pcode___udpsocket__GETPROPERTY_FontSize + 1;
static const int pcode___udpsocket__GETPROPERTY_FontItalic = pcode___udpsocket__SETPROPERTY_FontItalic + 1;
static const int pcode___udpsocket__SETPROPERTY_FontBold = pcode___udpsocket__GETPROPERTY_FontItalic + 1;
static const int pcode___udpsocket__GETPROPERTY_FontBold = pcode___udpsocket__SETPROPERTY_FontBold + 1;
static const int pcode___udpsocket__SETPROPERTY_FontUnderline = pcode___udpsocket__GETPROPERTY_FontBold + 1;
static const int pcode___udpsocket__GETPROPERTY_FontUnderline = pcode___udpsocket__SETPROPERTY_FontUnderline + 1;
static const int pcode___udpsocket__SETPROPERTY_FontColor = pcode___udpsocket__GETPROPERTY_FontUnderline + 1;
static const int pcode___udpsocket__GETPROPERTY_FontColor = pcode___udpsocket__SETPROPERTY_FontColor + 1;
static const int pcode___udpsocket__SETPROPERTY_Enabled = pcode___udpsocket__GETPROPERTY_FontColor + 1;
static const int pcode___udpsocket__GETPROPERTY_Enabled = pcode___udpsocket__SETPROPERTY_Enabled + 1;
static const int pcode___udpsocket__SETPROPERTY_Visible = pcode___udpsocket__GETPROPERTY_Enabled + 1;
static const int pcode___udpsocket__GETPROPERTY_Visible = pcode___udpsocket__SETPROPERTY_Visible + 1;
static const int pcode___udpsocket__SETPROPERTY_StatusTip = pcode___udpsocket__GETPROPERTY_Visible + 1;
static const int pcode___udpsocket__GETPROPERTY_StatusTip = pcode___udpsocket__SETPROPERTY_StatusTip + 1;
static const int pcode___udpsocket__SETPROPERTY_ToolTip = pcode___udpsocket__GETPROPERTY_StatusTip + 1;
static const int pcode___udpsocket__GETPROPERTY_ToolTip = pcode___udpsocket__SETPROPERTY_ToolTip + 1;
static const int pcode___udpsocket__SETPROPERTY_StyleSheet = pcode___udpsocket__GETPROPERTY_ToolTip + 1;
static const int pcode___udpsocket__GETPROPERTY_StyleSheet = pcode___udpsocket__SETPROPERTY_StyleSheet + 1;
static const int pcode___udpsocket__SETPROPERTY_WhatsThis = pcode___udpsocket__GETPROPERTY_StyleSheet + 1;
static const int pcode___udpsocket__GETPROPERTY_WhatsThis = pcode___udpsocket__SETPROPERTY_WhatsThis + 1;
static const int pcode___udpsocket__SETPROPERTY_TimerInterval = pcode___udpsocket__GETPROPERTY_WhatsThis + 1;
static const int pcode___udpsocket__GETPROPERTY_TimerInterval = pcode___udpsocket__SETPROPERTY_TimerInterval + 1;
static const int pcode___udpsocket__SETPROPERTY_Opacity = pcode___udpsocket__GETPROPERTY_TimerInterval + 1;
static const int pcode___udpsocket__GETPROPERTY_Opacity = pcode___udpsocket__SETPROPERTY_Opacity + 1;
static const int pcode___udpsocket__SETPROPERTY_BoxIndex = pcode___udpsocket__GETPROPERTY_Opacity + 1;
static const int pcode___udpsocket__GETPROPERTY_BoxIndex = pcode___udpsocket__SETPROPERTY_BoxIndex + 1;
static const int pcode___udpsocket__SETPROPERTY_SplitIndex = pcode___udpsocket__GETPROPERTY_BoxIndex + 1;
static const int pcode___udpsocket__GETPROPERTY_SplitIndex = pcode___udpsocket__SETPROPERTY_SplitIndex + 1;
static const int pcode___udpsocket__SETPROPERTY_TabIndex = pcode___udpsocket__GETPROPERTY_SplitIndex + 1;
static const int pcode___udpsocket__GETPROPERTY_TabIndex = pcode___udpsocket__SETPROPERTY_TabIndex + 1;
static const int pcode___udpsocket__SETPROPERTY_BoxX = pcode___udpsocket__GETPROPERTY_TabIndex + 1;
static const int pcode___udpsocket__GETPROPERTY_BoxX = pcode___udpsocket__SETPROPERTY_BoxX + 1;
static const int pcode___udpsocket__SETPROPERTY_BoxY = pcode___udpsocket__GETPROPERTY_BoxX + 1;
static const int pcode___udpsocket__GETPROPERTY_BoxY = pcode___udpsocket__SETPROPERTY_BoxY + 1;
static const int pcode___udpsocket__SETPROPERTY_ParentIndex = pcode___udpsocket__GETPROPERTY_BoxY + 1;
static const int pcode___udpsocket__GETPROPERTY_ParentIndex = pcode___udpsocket__SETPROPERTY_ParentIndex + 1;
static const int pcode___udpsocket__SETPROPERTY_ControlType1 = pcode___udpsocket__GETPROPERTY_ParentIndex + 1;
static const int pcode___udpsocket__GETPROPERTY_ControlType1 = pcode___udpsocket__SETPROPERTY_ControlType1 + 1;
static const int pcode___udpsocket__SETPROPERTY_SQLName = pcode___udpsocket__GETPROPERTY_ControlType1 + 1;
static const int pcode___udpsocket__GETPROPERTY_SQLName = pcode___udpsocket__SETPROPERTY_SQLName + 1;
static const int pcode___udpsocket__SETPROPERTY_SQLType = pcode___udpsocket__GETPROPERTY_SQLName + 1;
static const int pcode___udpsocket__GETPROPERTY_SQLType = pcode___udpsocket__SETPROPERTY_SQLType + 1;
static const int pcode___udpsocket__SETPROPERTY_SQLCaption = pcode___udpsocket__GETPROPERTY_SQLType + 1;
static const int pcode___udpsocket__GETPROPERTY_SQLCaption = pcode___udpsocket__SETPROPERTY_SQLCaption + 1;
static const int pcode___udpsocket__SETPROPERTY_SQLWidth = pcode___udpsocket__GETPROPERTY_SQLCaption + 1;
static const int pcode___udpsocket__GETPROPERTY_SQLWidth = pcode___udpsocket__SETPROPERTY_SQLWidth + 1;
static const int pcode___udpsocket__EVENT_OnOpen = pcode___udpsocket__GETPROPERTY_SQLWidth + 1;
static const int pcode___udpsocket__EVENT_OnClose = pcode___udpsocket__EVENT_OnOpen + 1;
static const int pcode___udpsocket__EVENT_OnContextMenu = pcode___udpsocket__EVENT_OnClose + 1;
static const int pcode___udpsocket__EVENT_OnDragEnter = pcode___udpsocket__EVENT_OnContextMenu + 1;
static const int pcode___udpsocket__EVENT_OnDragExit = pcode___udpsocket__EVENT_OnDragEnter + 1;
static const int pcode___udpsocket__EVENT_OnDragMove = pcode___udpsocket__EVENT_OnDragExit + 1;
static const int pcode___udpsocket__EVENT_OnDrop = pcode___udpsocket__EVENT_OnDragMove + 1;
static const int pcode___udpsocket__EVENT_OnEnter = pcode___udpsocket__EVENT_OnDrop + 1;
static const int pcode___udpsocket__EVENT_OnGotFocus = pcode___udpsocket__EVENT_OnEnter + 1;
static const int pcode___udpsocket__EVENT_OnLostFocus = pcode___udpsocket__EVENT_OnGotFocus + 1;
static const int pcode___udpsocket__EVENT_OnHide = pcode___udpsocket__EVENT_OnLostFocus + 1;
static const int pcode___udpsocket__EVENT_OnKeyDown = pcode___udpsocket__EVENT_OnHide + 1;
static const int pcode___udpsocket__EVENT_OnKeyUp = pcode___udpsocket__EVENT_OnKeyDown + 1;
static const int pcode___udpsocket__EVENT_OnKeyPress = pcode___udpsocket__EVENT_OnKeyUp + 1;
static const int pcode___udpsocket__EVENT_OnExit = pcode___udpsocket__EVENT_OnKeyPress + 1;
static const int pcode___udpsocket__EVENT_OnDblClick = pcode___udpsocket__EVENT_OnExit + 1;
static const int pcode___udpsocket__EVENT_OnClick = pcode___udpsocket__EVENT_OnDblClick + 1;
static const int pcode___udpsocket__EVENT_OnMouseMove = pcode___udpsocket__EVENT_OnClick + 1;
static const int pcode___udpsocket__EVENT_OnMouseDown = pcode___udpsocket__EVENT_OnMouseMove + 1;
static const int pcode___udpsocket__EVENT_OnMouseUp = pcode___udpsocket__EVENT_OnMouseDown + 1;
static const int pcode___udpsocket__EVENT_OnMove = pcode___udpsocket__EVENT_OnMouseUp + 1;
static const int pcode___udpsocket__EVENT_OnPaint = pcode___udpsocket__EVENT_OnMove + 1;
static const int pcode___udpsocket__EVENT_OnResize = pcode___udpsocket__EVENT_OnPaint + 1;
static const int pcode___udpsocket__EVENT_OnShow = pcode___udpsocket__EVENT_OnResize + 1;
static const int pcode___udpsocket__EVENT_OnMouseWheel = pcode___udpsocket__EVENT_OnShow + 1;
static const int pcode___udpsocket__EVENT_Onudpsocket = pcode___udpsocket__EVENT_OnMouseWheel + 1;
static const int pcode___udpsocket__EVENT_OnPrint = pcode___udpsocket__EVENT_Onudpsocket + 1;

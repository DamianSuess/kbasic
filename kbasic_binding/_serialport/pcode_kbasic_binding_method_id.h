static const int pcode___serialport___serialport = pcode___serialport * SPACE;
static const int pcode___serialport___serialport1 = pcode___serialport___serialport + 1;


static const int pcode___serialport__SETPROPERTY_MouseTracking = pcode___serialport___serialport1 + 1;
static const int pcode___serialport__GETPROPERTY_MouseTracking = pcode___serialport__SETPROPERTY_MouseTracking + 1; 

static const int pcode___serialport__EVENT_OnSingleShot = pcode___serialport__GETPROPERTY_MouseTracking + 1;
static const int pcode___serialport__EVENT_OnEnabled = pcode___serialport__EVENT_OnSingleShot + 1;
static const int pcode___serialport__EVENT_OnDisabled = pcode___serialport__EVENT_OnEnabled + 1;

static const int pcode___serialport__SETPROPERTY_CursorAnimation = pcode___serialport__EVENT_OnDisabled + 1;
static const int pcode___serialport__GETPROPERTY_CursorAnimation = pcode___serialport__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___serialport__METHOD_DataIds = pcode___serialport__GETPROPERTY_CursorAnimation + 1;

static const int pcode___serialport__METHOD_DataRemove = pcode___serialport__METHOD_DataIds + 1;
static const int pcode___serialport__METHOD_DataRemoveAll = pcode___serialport__METHOD_DataRemove + 1;
static const int pcode___serialport__METHOD_DataSetBoolean = pcode___serialport__METHOD_DataRemoveAll + 1;
static const int pcode___serialport__METHOD_DataSetInteger = pcode___serialport__METHOD_DataSetBoolean + 1;
static const int pcode___serialport__METHOD_DataSetString = pcode___serialport__METHOD_DataSetInteger + 1;
static const int pcode___serialport__METHOD_DataSetDouble = pcode___serialport__METHOD_DataSetString + 1;
static const int pcode___serialport__METHOD_DataSetLong = pcode___serialport__METHOD_DataSetDouble + 1;
static const int pcode___serialport__METHOD_DataSetDecimal = pcode___serialport__METHOD_DataSetLong + 1;
static const int pcode___serialport__METHOD_DataSetDateTime = pcode___serialport__METHOD_DataSetDecimal + 1;


static const int pcode___serialport__METHOD_DataBoolean = pcode___serialport__METHOD_DataSetDateTime + 1;
static const int pcode___serialport__METHOD_DataInteger = pcode___serialport__METHOD_DataBoolean + 1;
static const int pcode___serialport__METHOD_DataString = pcode___serialport__METHOD_DataInteger + 1;
static const int pcode___serialport__METHOD_DataDouble = pcode___serialport__METHOD_DataString + 1;
static const int pcode___serialport__METHOD_DataLong = pcode___serialport__METHOD_DataDouble + 1;
static const int pcode___serialport__METHOD_DataDecimal = pcode___serialport__METHOD_DataLong + 1;
static const int pcode___serialport__METHOD_DataDateTime = pcode___serialport__METHOD_DataDecimal + 1;

static const int pcode___serialport__METHOD_ClearFocus = pcode___serialport__METHOD_DataDateTime + 1;
static const int pcode___serialport__METHOD_ToggleVisible = pcode___serialport__METHOD_ClearFocus + 1;

static const int pcode___serialport__METHOD_SingleShot = pcode___serialport__METHOD_ToggleVisible + 1;
static const int pcode___serialport__METHOD_StartTimer = pcode___serialport__METHOD_SingleShot + 1;
static const int pcode___serialport__METHOD_StopTimer = pcode___serialport__METHOD_StartTimer + 1;

static const int pcode___serialport__METHOD_GlobalX = pcode___serialport__METHOD_StopTimer + 1;
static const int pcode___serialport__METHOD_GlobalY = pcode___serialport__METHOD_GlobalX + 1;
static const int pcode___serialport__METHOD_LocalX = pcode___serialport__METHOD_GlobalY + 1;
static const int pcode___serialport__METHOD_LocalY = pcode___serialport__METHOD_LocalX + 1;

static const int pcode___serialport__METHOD_UnderMouse = pcode___serialport__METHOD_LocalY + 1;

static const int pcode___serialport__SETPROPERTY_Mask = pcode___serialport__METHOD_UnderMouse + 1;
static const int pcode___serialport__GETPROPERTY_Mask = pcode___serialport__SETPROPERTY_Mask + 1;

static const int pcode___serialport__SETPROPERTY_SoundOnEvent = pcode___serialport__GETPROPERTY_Mask + 1;
static const int pcode___serialport__GETPROPERTY_SoundOnEvent = pcode___serialport__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___serialport__SETPROPERTY_Left = pcode___serialport__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___serialport__GETPROPERTY_Left = pcode___serialport__SETPROPERTY_Left + 1;
static const int pcode___serialport__SETPROPERTY_Top = pcode___serialport__GETPROPERTY_Left + 1;
static const int pcode___serialport__GETPROPERTY_Top = pcode___serialport__SETPROPERTY_Top + 1;

static const int pcode___serialport__SETPROPERTY_LocalX = pcode___serialport__GETPROPERTY_Top + 1;
static const int pcode___serialport__GETPROPERTY_LocalX = pcode___serialport__SETPROPERTY_LocalX + 1;
static const int pcode___serialport__SETPROPERTY_LocalY = pcode___serialport__GETPROPERTY_LocalX + 1;
static const int pcode___serialport__GETPROPERTY_LocalY = pcode___serialport__SETPROPERTY_LocalY + 1;

static const int pcode___serialport__SETPROPERTY_DrawOnPaint = pcode___serialport__GETPROPERTY_LocalY + 1;
static const int pcode___serialport__GETPROPERTY_DrawOnPaint = pcode___serialport__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___serialport__SETPROPERTY_Palette = pcode___serialport__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___serialport__GETPROPERTY_Palette = pcode___serialport__SETPROPERTY_Palette + 1;


static const int pcode___serialport__SETPROPERTY_BackgroundStyle = pcode___serialport__GETPROPERTY_Palette + 1;
static const int pcode___serialport__GETPROPERTY_BackgroundStyle = pcode___serialport__SETPROPERTY_BackgroundStyle + 1;



//static const int pcode___serialport__METHOD_Open = pcode___serialport___serialport + 1;
static const int pcode___serialport__METHOD_IsOpen = pcode___serialport__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___serialport__METHOD_IsReadable = pcode___serialport__METHOD_IsOpen + 1;
static const int pcode___serialport__METHOD_IsWritable = pcode___serialport__METHOD_IsReadable + 1;
//static const int pcode___serialport__METHOD_Close = pcode___serialport__METHOD_IsWritable + 1;
static const int pcode___serialport__METHOD_Flush = pcode___serialport__METHOD_IsWritable + 1;

static const int pcode___serialport__METHOD_BytesRead = pcode___serialport__METHOD_Flush + 1;
static const int pcode___serialport__METHOD_BytesWritten = pcode___serialport__METHOD_BytesRead + 1;

static const int pcode___serialport__METHOD_IsCTS = pcode___serialport__METHOD_BytesWritten + 1;
static const int pcode___serialport__METHOD_IsDSR = pcode___serialport__METHOD_IsCTS + 1;
static const int pcode___serialport__METHOD_IsDCD = pcode___serialport__METHOD_IsDSR + 1;
static const int pcode___serialport__METHOD_IsRI = pcode___serialport__METHOD_IsDCD + 1;

static const int pcode___serialport__METHOD_BytesAvailable = pcode___serialport__METHOD_IsRI + 1;
static const int pcode___serialport__METHOD_ReadData = pcode___serialport__METHOD_BytesAvailable + 1;
static const int pcode___serialport__METHOD_WriteData = pcode___serialport__METHOD_ReadData + 1;
static const int pcode___serialport__METHOD_ReadLine = pcode___serialport__METHOD_WriteData + 1;
static const int pcode___serialport__METHOD_WriteLine = pcode___serialport__METHOD_ReadLine + 1;
static const int pcode___serialport__METHOD_SetDtr = pcode___serialport__METHOD_WriteLine + 1;
static const int pcode___serialport__METHOD_SetRts = pcode___serialport__METHOD_SetDtr + 1;
static const int pcode___serialport__METHOD_AtEnd = pcode___serialport__METHOD_SetRts + 1;
static const int pcode___serialport__METHOD_LineStatus = pcode___serialport__METHOD_AtEnd + 1;
static const int pcode___serialport__METHOD_LastError = pcode___serialport__METHOD_LineStatus + 1;
static const int pcode___serialport__METHOD_LastErrorText = pcode___serialport__METHOD_LastError + 1;

static const int pcode___serialport__SETPROPERTY_PortName = pcode___serialport__METHOD_LastErrorText + 1;
static const int pcode___serialport__GETPROPERTY_PortName = pcode___serialport__SETPROPERTY_PortName + 1;

static const int pcode___serialport__SETPROPERTY_BaudRate = pcode___serialport__GETPROPERTY_PortName + 1;
static const int pcode___serialport__GETPROPERTY_BaudRate = pcode___serialport__SETPROPERTY_BaudRate + 1;

static const int pcode___serialport__SETPROPERTY_DataBits = pcode___serialport__GETPROPERTY_BaudRate + 1;
static const int pcode___serialport__GETPROPERTY_DataBits = pcode___serialport__SETPROPERTY_DataBits + 1;

static const int pcode___serialport__SETPROPERTY_FlowControl = pcode___serialport__GETPROPERTY_DataBits + 1;
static const int pcode___serialport__GETPROPERTY_FlowControl = pcode___serialport__SETPROPERTY_FlowControl + 1;

static const int pcode___serialport__SETPROPERTY_Parity = pcode___serialport__GETPROPERTY_FlowControl + 1;
static const int pcode___serialport__GETPROPERTY_Parity = pcode___serialport__SETPROPERTY_Parity + 1;

static const int pcode___serialport__SETPROPERTY_StopBits = pcode___serialport__GETPROPERTY_Parity + 1;
static const int pcode___serialport__GETPROPERTY_StopBits = pcode___serialport__SETPROPERTY_StopBits + 1;

static const int pcode___serialport__SETPROPERTY_TimeOutMillisec = pcode___serialport__GETPROPERTY_StopBits + 1;
static const int pcode___serialport__GETPROPERTY_TimeOutMillisec = pcode___serialport__SETPROPERTY_TimeOutMillisec + 1;

static const int pcode___serialport__SETPROPERTY_PollingInterval = pcode___serialport__GETPROPERTY_TimeOutMillisec + 1;
static const int pcode___serialport__GETPROPERTY_PollingInterval = pcode___serialport__SETPROPERTY_PollingInterval + 1;
static const int pcode___serialport__EVENT_OnEvent = pcode___serialport__GETPROPERTY_PollingInterval + 1;

static const int pcode___serialport__SETPROPERTY_Layout = pcode___serialport__EVENT_OnEvent + 1;
static const int pcode___serialport__GETPROPERTY_Layout = pcode___serialport__SETPROPERTY_Layout + 1;
static const int pcode___serialport__METHOD_Move = pcode___serialport__GETPROPERTY_Layout + 1;
static const int pcode___serialport__METHOD_Resize = pcode___serialport__METHOD_Move + 1;
static const int pcode___serialport__METHOD_Show = pcode___serialport__METHOD_Resize + 1;
static const int pcode___serialport__METHOD_Hide = pcode___serialport__METHOD_Show + 1;
static const int pcode___serialport__METHOD_RepaintAlways = pcode___serialport__METHOD_Hide + 1;
static const int pcode___serialport__METHOD_Repaint = pcode___serialport__METHOD_RepaintAlways + 1;
static const int pcode___serialport__METHOD_Raise = pcode___serialport__METHOD_Repaint + 1;
static const int pcode___serialport__METHOD_Lower = pcode___serialport__METHOD_Raise + 1;
static const int pcode___serialport__METHOD_Close = pcode___serialport__METHOD_Lower + 1;
static const int pcode___serialport__METHOD_Open = pcode___serialport__METHOD_Close + 1;
static const int pcode___serialport__METHOD_SetFocus = pcode___serialport__METHOD_Open + 1;
static const int pcode___serialport__SETPROPERTY_Name = pcode___serialport__METHOD_SetFocus + 1;
static const int pcode___serialport__GETPROPERTY_Name = pcode___serialport__SETPROPERTY_Name + 1;
static const int pcode___serialport__SETPROPERTY_Group = pcode___serialport__GETPROPERTY_Name + 1;
static const int pcode___serialport__GETPROPERTY_Group = pcode___serialport__SETPROPERTY_Group + 1;
static const int pcode___serialport__SETPROPERTY_Background = pcode___serialport__GETPROPERTY_Group + 1;
static const int pcode___serialport__GETPROPERTY_Background = pcode___serialport__SETPROPERTY_Background + 1;
static const int pcode___serialport__SETPROPERTY_X = pcode___serialport__GETPROPERTY_Background + 1;
static const int pcode___serialport__GETPROPERTY_X = pcode___serialport__SETPROPERTY_X + 1;
static const int pcode___serialport__SETPROPERTY_Y = pcode___serialport__GETPROPERTY_X + 1;
static const int pcode___serialport__GETPROPERTY_Y = pcode___serialport__SETPROPERTY_Y + 1;
static const int pcode___serialport__SETPROPERTY_Width = pcode___serialport__GETPROPERTY_Y + 1;
static const int pcode___serialport__GETPROPERTY_Width = pcode___serialport__SETPROPERTY_Width + 1;
static const int pcode___serialport__SETPROPERTY_Height = pcode___serialport__GETPROPERTY_Width + 1;
static const int pcode___serialport__GETPROPERTY_Height = pcode___serialport__SETPROPERTY_Height + 1;
static const int pcode___serialport__GETPROPERTY_GlobalX = pcode___serialport__GETPROPERTY_Height + 1;
static const int pcode___serialport__GETPROPERTY_GlobalY = pcode___serialport__GETPROPERTY_GlobalX + 1;
static const int pcode___serialport__GETPROPERTY_OldX = pcode___serialport__GETPROPERTY_GlobalY + 1;
static const int pcode___serialport__GETPROPERTY_OldY = pcode___serialport__GETPROPERTY_OldX + 1;
static const int pcode___serialport__GETPROPERTY_OldWidth = pcode___serialport__GETPROPERTY_OldY + 1;
static const int pcode___serialport__GETPROPERTY_OldHeight = pcode___serialport__GETPROPERTY_OldWidth + 1;
static const int pcode___serialport__SETPROPERTY_MinimumWidth = pcode___serialport__GETPROPERTY_OldHeight + 1;
static const int pcode___serialport__GETPROPERTY_MinimumWidth = pcode___serialport__SETPROPERTY_MinimumWidth + 1;
static const int pcode___serialport__SETPROPERTY_MinimumHeight = pcode___serialport__GETPROPERTY_MinimumWidth + 1;
static const int pcode___serialport__GETPROPERTY_MinimumHeight = pcode___serialport__SETPROPERTY_MinimumHeight + 1;
static const int pcode___serialport__SETPROPERTY_MaximumWidth = pcode___serialport__GETPROPERTY_MinimumHeight + 1;
static const int pcode___serialport__GETPROPERTY_MaximumWidth = pcode___serialport__SETPROPERTY_MaximumWidth + 1;
static const int pcode___serialport__SETPROPERTY_MaximumHeight = pcode___serialport__GETPROPERTY_MaximumWidth + 1;
static const int pcode___serialport__GETPROPERTY_MaximumHeight = pcode___serialport__SETPROPERTY_MaximumHeight + 1;
static const int pcode___serialport__SETPROPERTY_Tag = pcode___serialport__GETPROPERTY_MaximumHeight + 1;
static const int pcode___serialport__GETPROPERTY_Tag = pcode___serialport__SETPROPERTY_Tag + 1;
static const int pcode___serialport__SETPROPERTY_CSV = pcode___serialport__GETPROPERTY_Tag + 1;
static const int pcode___serialport__GETPROPERTY_CSV = pcode___serialport__SETPROPERTY_CSV + 1;
static const int pcode___serialport__SETPROPERTY_ParentForm = pcode___serialport__GETPROPERTY_CSV + 1;
static const int pcode___serialport__GETPROPERTY_ParentForm = pcode___serialport__SETPROPERTY_ParentForm + 1;
static const int pcode___serialport__SETPROPERTY_ParentControl = pcode___serialport__GETPROPERTY_ParentForm + 1;
static const int pcode___serialport__GETPROPERTY_ParentControl = pcode___serialport__SETPROPERTY_ParentControl + 1;
static const int pcode___serialport__SETPROPERTY_DragDrop = pcode___serialport__GETPROPERTY_ParentControl + 1;
static const int pcode___serialport__GETPROPERTY_ParentControl1 = pcode___serialport__SETPROPERTY_DragDrop + 1;
static const int pcode___serialport__SETPROPERTY_ControlType = pcode___serialport__GETPROPERTY_ParentControl1 + 1;
static const int pcode___serialport__GETPROPERTY_ControlType = pcode___serialport__SETPROPERTY_ControlType + 1;
static const int pcode___serialport__SETPROPERTY_Focus = pcode___serialport__GETPROPERTY_ControlType + 1;
static const int pcode___serialport__GETPROPERTY_Focus = pcode___serialport__SETPROPERTY_Focus + 1;
static const int pcode___serialport__SETPROPERTY_FocusPolicy = pcode___serialport__GETPROPERTY_Focus + 1;
static const int pcode___serialport__GETPROPERTY_FocusPolicy = pcode___serialport__SETPROPERTY_FocusPolicy + 1;
static const int pcode___serialport__SETPROPERTY_FocusProxy = pcode___serialport__GETPROPERTY_FocusPolicy + 1;
static const int pcode___serialport__GETPROPERTY_FocusProxy = pcode___serialport__SETPROPERTY_FocusProxy + 1;
static const int pcode___serialport__SETPROPERTY_FocusOrder = pcode___serialport__GETPROPERTY_FocusProxy + 1;
static const int pcode___serialport__GETPROPERTY_FocusOrder = pcode___serialport__SETPROPERTY_FocusOrder + 1;
static const int pcode___serialport__SETPROPERTY_Cursor = pcode___serialport__GETPROPERTY_FocusOrder + 1;
static const int pcode___serialport__GETPROPERTY_Cursor = pcode___serialport__SETPROPERTY_Cursor + 1;
static const int pcode___serialport__SETPROPERTY_FontName = pcode___serialport__GETPROPERTY_Cursor + 1;
static const int pcode___serialport__GETPROPERTY_FontName = pcode___serialport__SETPROPERTY_FontName + 1;
static const int pcode___serialport__SETPROPERTY_FontSize = pcode___serialport__GETPROPERTY_FontName + 1;
static const int pcode___serialport__GETPROPERTY_FontSize = pcode___serialport__SETPROPERTY_FontSize + 1;
static const int pcode___serialport__SETPROPERTY_FontItalic = pcode___serialport__GETPROPERTY_FontSize + 1;
static const int pcode___serialport__GETPROPERTY_FontItalic = pcode___serialport__SETPROPERTY_FontItalic + 1;
static const int pcode___serialport__SETPROPERTY_FontBold = pcode___serialport__GETPROPERTY_FontItalic + 1;
static const int pcode___serialport__GETPROPERTY_FontBold = pcode___serialport__SETPROPERTY_FontBold + 1;
static const int pcode___serialport__SETPROPERTY_FontUnderline = pcode___serialport__GETPROPERTY_FontBold + 1;
static const int pcode___serialport__GETPROPERTY_FontUnderline = pcode___serialport__SETPROPERTY_FontUnderline + 1;
static const int pcode___serialport__SETPROPERTY_FontColor = pcode___serialport__GETPROPERTY_FontUnderline + 1;
static const int pcode___serialport__GETPROPERTY_FontColor = pcode___serialport__SETPROPERTY_FontColor + 1;
static const int pcode___serialport__SETPROPERTY_Enabled = pcode___serialport__GETPROPERTY_FontColor + 1;
static const int pcode___serialport__GETPROPERTY_Enabled = pcode___serialport__SETPROPERTY_Enabled + 1;
static const int pcode___serialport__SETPROPERTY_Visible = pcode___serialport__GETPROPERTY_Enabled + 1;
static const int pcode___serialport__GETPROPERTY_Visible = pcode___serialport__SETPROPERTY_Visible + 1;
static const int pcode___serialport__SETPROPERTY_StatusTip = pcode___serialport__GETPROPERTY_Visible + 1;
static const int pcode___serialport__GETPROPERTY_StatusTip = pcode___serialport__SETPROPERTY_StatusTip + 1;
static const int pcode___serialport__SETPROPERTY_ToolTip = pcode___serialport__GETPROPERTY_StatusTip + 1;
static const int pcode___serialport__GETPROPERTY_ToolTip = pcode___serialport__SETPROPERTY_ToolTip + 1;
static const int pcode___serialport__SETPROPERTY_StyleSheet = pcode___serialport__GETPROPERTY_ToolTip + 1;
static const int pcode___serialport__GETPROPERTY_StyleSheet = pcode___serialport__SETPROPERTY_StyleSheet + 1;
static const int pcode___serialport__SETPROPERTY_WhatsThis = pcode___serialport__GETPROPERTY_StyleSheet + 1;
static const int pcode___serialport__GETPROPERTY_WhatsThis = pcode___serialport__SETPROPERTY_WhatsThis + 1;
static const int pcode___serialport__SETPROPERTY_TimerInterval = pcode___serialport__GETPROPERTY_WhatsThis + 1;
static const int pcode___serialport__GETPROPERTY_TimerInterval = pcode___serialport__SETPROPERTY_TimerInterval + 1;
static const int pcode___serialport__SETPROPERTY_Opacity = pcode___serialport__GETPROPERTY_TimerInterval + 1;
static const int pcode___serialport__GETPROPERTY_Opacity = pcode___serialport__SETPROPERTY_Opacity + 1;
static const int pcode___serialport__SETPROPERTY_BoxIndex = pcode___serialport__GETPROPERTY_Opacity + 1;
static const int pcode___serialport__GETPROPERTY_BoxIndex = pcode___serialport__SETPROPERTY_BoxIndex + 1;
static const int pcode___serialport__SETPROPERTY_SplitIndex = pcode___serialport__GETPROPERTY_BoxIndex + 1;
static const int pcode___serialport__GETPROPERTY_SplitIndex = pcode___serialport__SETPROPERTY_SplitIndex + 1;
static const int pcode___serialport__SETPROPERTY_TabIndex = pcode___serialport__GETPROPERTY_SplitIndex + 1;
static const int pcode___serialport__GETPROPERTY_TabIndex = pcode___serialport__SETPROPERTY_TabIndex + 1;
static const int pcode___serialport__SETPROPERTY_BoxX = pcode___serialport__GETPROPERTY_TabIndex + 1;
static const int pcode___serialport__GETPROPERTY_BoxX = pcode___serialport__SETPROPERTY_BoxX + 1;
static const int pcode___serialport__SETPROPERTY_BoxY = pcode___serialport__GETPROPERTY_BoxX + 1;
static const int pcode___serialport__GETPROPERTY_BoxY = pcode___serialport__SETPROPERTY_BoxY + 1;
static const int pcode___serialport__SETPROPERTY_ParentIndex = pcode___serialport__GETPROPERTY_BoxY + 1;
static const int pcode___serialport__GETPROPERTY_ParentIndex = pcode___serialport__SETPROPERTY_ParentIndex + 1;
static const int pcode___serialport__SETPROPERTY_ControlType1 = pcode___serialport__GETPROPERTY_ParentIndex + 1;
static const int pcode___serialport__GETPROPERTY_ControlType1 = pcode___serialport__SETPROPERTY_ControlType1 + 1;
static const int pcode___serialport__SETPROPERTY_SQLName = pcode___serialport__GETPROPERTY_ControlType1 + 1;
static const int pcode___serialport__GETPROPERTY_SQLName = pcode___serialport__SETPROPERTY_SQLName + 1;
static const int pcode___serialport__SETPROPERTY_SQLType = pcode___serialport__GETPROPERTY_SQLName + 1;
static const int pcode___serialport__GETPROPERTY_SQLType = pcode___serialport__SETPROPERTY_SQLType + 1;
static const int pcode___serialport__SETPROPERTY_SQLCaption = pcode___serialport__GETPROPERTY_SQLType + 1;
static const int pcode___serialport__GETPROPERTY_SQLCaption = pcode___serialport__SETPROPERTY_SQLCaption + 1;
static const int pcode___serialport__SETPROPERTY_SQLWidth = pcode___serialport__GETPROPERTY_SQLCaption + 1;
static const int pcode___serialport__GETPROPERTY_SQLWidth = pcode___serialport__SETPROPERTY_SQLWidth + 1;
static const int pcode___serialport__EVENT_OnOpen = pcode___serialport__GETPROPERTY_SQLWidth + 1;
static const int pcode___serialport__EVENT_OnClose = pcode___serialport__EVENT_OnOpen + 1;
static const int pcode___serialport__EVENT_OnContextMenu = pcode___serialport__EVENT_OnClose + 1;
static const int pcode___serialport__EVENT_OnDragEnter = pcode___serialport__EVENT_OnContextMenu + 1;
static const int pcode___serialport__EVENT_OnDragExit = pcode___serialport__EVENT_OnDragEnter + 1;
static const int pcode___serialport__EVENT_OnDragMove = pcode___serialport__EVENT_OnDragExit + 1;
static const int pcode___serialport__EVENT_OnDrop = pcode___serialport__EVENT_OnDragMove + 1;
static const int pcode___serialport__EVENT_OnEnter = pcode___serialport__EVENT_OnDrop + 1;
static const int pcode___serialport__EVENT_OnGotFocus = pcode___serialport__EVENT_OnEnter + 1;
static const int pcode___serialport__EVENT_OnLostFocus = pcode___serialport__EVENT_OnGotFocus + 1;
static const int pcode___serialport__EVENT_OnHide = pcode___serialport__EVENT_OnLostFocus + 1;
static const int pcode___serialport__EVENT_OnKeyDown = pcode___serialport__EVENT_OnHide + 1;
static const int pcode___serialport__EVENT_OnKeyUp = pcode___serialport__EVENT_OnKeyDown + 1;
static const int pcode___serialport__EVENT_OnKeyPress = pcode___serialport__EVENT_OnKeyUp + 1;
static const int pcode___serialport__EVENT_OnExit = pcode___serialport__EVENT_OnKeyPress + 1;
static const int pcode___serialport__EVENT_OnDblClick = pcode___serialport__EVENT_OnExit + 1;
static const int pcode___serialport__EVENT_OnClick = pcode___serialport__EVENT_OnDblClick + 1;
static const int pcode___serialport__EVENT_OnMouseMove = pcode___serialport__EVENT_OnClick + 1;
static const int pcode___serialport__EVENT_OnMouseDown = pcode___serialport__EVENT_OnMouseMove + 1;
static const int pcode___serialport__EVENT_OnMouseUp = pcode___serialport__EVENT_OnMouseDown + 1;
static const int pcode___serialport__EVENT_OnMove = pcode___serialport__EVENT_OnMouseUp + 1;
static const int pcode___serialport__EVENT_OnPaint = pcode___serialport__EVENT_OnMove + 1;
static const int pcode___serialport__EVENT_OnResize = pcode___serialport__EVENT_OnPaint + 1;
static const int pcode___serialport__EVENT_OnShow = pcode___serialport__EVENT_OnResize + 1;
static const int pcode___serialport__EVENT_OnMouseWheel = pcode___serialport__EVENT_OnShow + 1;
static const int pcode___serialport__EVENT_Onserialport = pcode___serialport__EVENT_OnMouseWheel + 1;
static const int pcode___serialport__EVENT_OnPrint = pcode___serialport__EVENT_Onserialport + 1;

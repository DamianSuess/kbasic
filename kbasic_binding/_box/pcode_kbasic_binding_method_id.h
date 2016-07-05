static const int pcode___box___box = pcode___box * SPACE;

static const int pcode___box___box1 = pcode___box___box + 1;

static const int pcode___box__SETPROPERTY_MouseTracking = pcode___box___box1 + 1;
static const int pcode___box__GETPROPERTY_MouseTracking = pcode___box__SETPROPERTY_MouseTracking + 1; 


static const int pcode___box__EVENT_OnSingleShot = pcode___box__GETPROPERTY_MouseTracking + 1;
static const int pcode___box__EVENT_OnEnabled = pcode___box__EVENT_OnSingleShot + 1;
static const int pcode___box__EVENT_OnDisabled = pcode___box__EVENT_OnEnabled + 1;

static const int pcode___box__SETPROPERTY_CursorAnimation = pcode___box__EVENT_OnDisabled + 1;
static const int pcode___box__GETPROPERTY_CursorAnimation = pcode___box__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___box__METHOD_DataIds = pcode___box__GETPROPERTY_CursorAnimation + 1;

static const int pcode___box__METHOD_DataRemove = pcode___box__METHOD_DataIds + 1;
static const int pcode___box__METHOD_DataRemoveAll = pcode___box__METHOD_DataRemove + 1;
static const int pcode___box__METHOD_DataSetBoolean = pcode___box__METHOD_DataRemoveAll + 1;
static const int pcode___box__METHOD_DataSetInteger = pcode___box__METHOD_DataSetBoolean + 1;
static const int pcode___box__METHOD_DataSetString = pcode___box__METHOD_DataSetInteger + 1;
static const int pcode___box__METHOD_DataSetDouble = pcode___box__METHOD_DataSetString + 1;
static const int pcode___box__METHOD_DataSetLong = pcode___box__METHOD_DataSetDouble + 1;
static const int pcode___box__METHOD_DataSetDecimal = pcode___box__METHOD_DataSetLong + 1;
static const int pcode___box__METHOD_DataSetDateTime = pcode___box__METHOD_DataSetDecimal + 1;


static const int pcode___box__METHOD_DataBoolean = pcode___box__METHOD_DataSetDateTime + 1;
static const int pcode___box__METHOD_DataInteger = pcode___box__METHOD_DataBoolean + 1;
static const int pcode___box__METHOD_DataString = pcode___box__METHOD_DataInteger + 1;
static const int pcode___box__METHOD_DataDouble = pcode___box__METHOD_DataString + 1;
static const int pcode___box__METHOD_DataLong = pcode___box__METHOD_DataDouble + 1;
static const int pcode___box__METHOD_DataDecimal = pcode___box__METHOD_DataLong + 1;
static const int pcode___box__METHOD_DataDateTime = pcode___box__METHOD_DataDecimal + 1;

static const int pcode___box__METHOD_ClearFocus = pcode___box__METHOD_DataDateTime + 1;
static const int pcode___box__METHOD_ToggleVisible = pcode___box__METHOD_ClearFocus + 1;

static const int pcode___box__METHOD_SingleShot = pcode___box__METHOD_ToggleVisible + 1;
static const int pcode___box__METHOD_StartTimer = pcode___box__METHOD_SingleShot + 1;
static const int pcode___box__METHOD_StopTimer = pcode___box__METHOD_StartTimer + 1;

//static const int pcode___box__METHOD_EventSender = pcode___box__METHOD_StopTimer + 1;

static const int pcode___box__METHOD_GlobalX = pcode___box__METHOD_StopTimer + 1;
static const int pcode___box__METHOD_GlobalY = pcode___box__METHOD_GlobalX + 1;
static const int pcode___box__METHOD_LocalX = pcode___box__METHOD_GlobalY + 1;
static const int pcode___box__METHOD_LocalY = pcode___box__METHOD_LocalX + 1;

static const int pcode___box__METHOD_UnderMouse = pcode___box__METHOD_LocalY + 1;

static const int pcode___box__SETPROPERTY_Mask = pcode___box__METHOD_UnderMouse + 1;
static const int pcode___box__GETPROPERTY_Mask = pcode___box__SETPROPERTY_Mask + 1;

static const int pcode___box__SETPROPERTY_SoundOnEvent = pcode___box__GETPROPERTY_Mask + 1;
static const int pcode___box__GETPROPERTY_SoundOnEvent = pcode___box__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___box__SETPROPERTY_Left = pcode___box__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___box__GETPROPERTY_Left = pcode___box__SETPROPERTY_Left + 1;
static const int pcode___box__SETPROPERTY_Top = pcode___box__GETPROPERTY_Left + 1;
static const int pcode___box__GETPROPERTY_Top = pcode___box__SETPROPERTY_Top + 1;

static const int pcode___box__SETPROPERTY_LocalX = pcode___box__GETPROPERTY_Top + 1;
static const int pcode___box__GETPROPERTY_LocalX = pcode___box__SETPROPERTY_LocalX + 1;
static const int pcode___box__SETPROPERTY_LocalY = pcode___box__GETPROPERTY_LocalX + 1;
static const int pcode___box__GETPROPERTY_LocalY = pcode___box__SETPROPERTY_LocalY + 1;

static const int pcode___box__SETPROPERTY_DrawOnPaint = pcode___box__GETPROPERTY_LocalY + 1;
static const int pcode___box__GETPROPERTY_DrawOnPaint = pcode___box__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___box__SETPROPERTY_Palette = pcode___box__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___box__GETPROPERTY_Palette = pcode___box__SETPROPERTY_Palette + 1;


static const int pcode___box__SETPROPERTY_BackgroundStyle = pcode___box__GETPROPERTY_Palette + 1;
static const int pcode___box__GETPROPERTY_BackgroundStyle = pcode___box__SETPROPERTY_BackgroundStyle + 1;


static const int pcode___box__SETPROPERTY_Layout = pcode___box__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___box__GETPROPERTY_Layout = pcode___box__SETPROPERTY_Layout + 1;
static const int pcode___box__SETPROPERTY_Value = pcode___box__GETPROPERTY_Layout + 1;
static const int pcode___box__GETPROPERTY_Value = pcode___box__SETPROPERTY_Value + 1;
static const int pcode___box__GETPROPERTY_OldValue = pcode___box__GETPROPERTY_Value + 1;
static const int pcode___box__SETPROPERTY_Maximum = pcode___box__GETPROPERTY_OldValue + 1;
static const int pcode___box__GETPROPERTY_Maximum = pcode___box__SETPROPERTY_Maximum + 1;
static const int pcode___box__SETPROPERTY_Minimum = pcode___box__GETPROPERTY_Maximum + 1;
static const int pcode___box__GETPROPERTY_Minimum = pcode___box__SETPROPERTY_Minimum + 1;
static const int pcode___box__SETPROPERTY_Format = pcode___box__GETPROPERTY_Minimum + 1;
static const int pcode___box__GETPROPERTY_Format = pcode___box__SETPROPERTY_Format + 1;
static const int pcode___box__SETPROPERTY_PopUp = pcode___box__GETPROPERTY_Format + 1;
static const int pcode___box__GETPROPERTY_PopUp = pcode___box__SETPROPERTY_PopUp + 1;
static const int pcode___box__METHOD_SetDateTime = pcode___box__GETPROPERTY_PopUp + 1;
static const int pcode___box__METHOD_AsDateTime = pcode___box__METHOD_SetDateTime + 1;
static const int pcode___box__EVENT_OnEvent = pcode___box__METHOD_AsDateTime + 1;
static const int pcode___box__METHOD_Move = pcode___box__EVENT_OnEvent + 1;
static const int pcode___box__METHOD_Resize = pcode___box__METHOD_Move + 1;
static const int pcode___box__METHOD_Show = pcode___box__METHOD_Resize + 1;
static const int pcode___box__METHOD_Hide = pcode___box__METHOD_Show + 1;
static const int pcode___box__METHOD_RepaintAlways = pcode___box__METHOD_Hide + 1;
static const int pcode___box__METHOD_Repaint = pcode___box__METHOD_RepaintAlways + 1;
static const int pcode___box__METHOD_Raise = pcode___box__METHOD_Repaint + 1;
static const int pcode___box__METHOD_Lower = pcode___box__METHOD_Raise + 1;
static const int pcode___box__METHOD_Close = pcode___box__METHOD_Lower + 1;
static const int pcode___box__METHOD_Open = pcode___box__METHOD_Close + 1;
static const int pcode___box__METHOD_SetFocus = pcode___box__METHOD_Open + 1;
static const int pcode___box__SETPROPERTY_Name = pcode___box__METHOD_SetFocus + 1;
static const int pcode___box__GETPROPERTY_Name = pcode___box__SETPROPERTY_Name + 1;
static const int pcode___box__SETPROPERTY_Group = pcode___box__GETPROPERTY_Name + 1;
static const int pcode___box__GETPROPERTY_Group = pcode___box__SETPROPERTY_Group + 1;
static const int pcode___box__SETPROPERTY_Background = pcode___box__GETPROPERTY_Group + 1;
static const int pcode___box__GETPROPERTY_Background = pcode___box__SETPROPERTY_Background + 1;
static const int pcode___box__SETPROPERTY_X = pcode___box__GETPROPERTY_Background + 1;
static const int pcode___box__GETPROPERTY_X = pcode___box__SETPROPERTY_X + 1;
static const int pcode___box__SETPROPERTY_Y = pcode___box__GETPROPERTY_X + 1;
static const int pcode___box__GETPROPERTY_Y = pcode___box__SETPROPERTY_Y + 1;
static const int pcode___box__SETPROPERTY_Width = pcode___box__GETPROPERTY_Y + 1;
static const int pcode___box__GETPROPERTY_Width = pcode___box__SETPROPERTY_Width + 1;
static const int pcode___box__SETPROPERTY_Height = pcode___box__GETPROPERTY_Width + 1;
static const int pcode___box__GETPROPERTY_Height = pcode___box__SETPROPERTY_Height + 1;
static const int pcode___box__GETPROPERTY_GlobalX = pcode___box__GETPROPERTY_Height + 1;
static const int pcode___box__GETPROPERTY_GlobalY = pcode___box__GETPROPERTY_GlobalX + 1;
static const int pcode___box__GETPROPERTY_OldX = pcode___box__GETPROPERTY_GlobalY + 1;
static const int pcode___box__GETPROPERTY_OldY = pcode___box__GETPROPERTY_OldX + 1;
static const int pcode___box__GETPROPERTY_OldWidth = pcode___box__GETPROPERTY_OldY + 1;
static const int pcode___box__GETPROPERTY_OldHeight = pcode___box__GETPROPERTY_OldWidth + 1;
static const int pcode___box__SETPROPERTY_MinimumWidth = pcode___box__GETPROPERTY_OldHeight + 1;
static const int pcode___box__GETPROPERTY_MinimumWidth = pcode___box__SETPROPERTY_MinimumWidth + 1;
static const int pcode___box__SETPROPERTY_MinimumHeight = pcode___box__GETPROPERTY_MinimumWidth + 1;
static const int pcode___box__GETPROPERTY_MinimumHeight = pcode___box__SETPROPERTY_MinimumHeight + 1;
static const int pcode___box__SETPROPERTY_MaximumWidth = pcode___box__GETPROPERTY_MinimumHeight + 1;
static const int pcode___box__GETPROPERTY_MaximumWidth = pcode___box__SETPROPERTY_MaximumWidth + 1;
static const int pcode___box__SETPROPERTY_MaximumHeight = pcode___box__GETPROPERTY_MaximumWidth + 1;
static const int pcode___box__GETPROPERTY_MaximumHeight = pcode___box__SETPROPERTY_MaximumHeight + 1;
static const int pcode___box__SETPROPERTY_Tag = pcode___box__GETPROPERTY_MaximumHeight + 1;
static const int pcode___box__GETPROPERTY_Tag = pcode___box__SETPROPERTY_Tag + 1;
static const int pcode___box__SETPROPERTY_CSV = pcode___box__GETPROPERTY_Tag + 1;
static const int pcode___box__GETPROPERTY_CSV = pcode___box__SETPROPERTY_CSV + 1;
static const int pcode___box__SETPROPERTY_ParentForm = pcode___box__GETPROPERTY_CSV + 1;
static const int pcode___box__GETPROPERTY_ParentForm = pcode___box__SETPROPERTY_ParentForm + 1;
static const int pcode___box__SETPROPERTY_ParentControl = pcode___box__GETPROPERTY_ParentForm + 1;
static const int pcode___box__GETPROPERTY_ParentControl = pcode___box__SETPROPERTY_ParentControl + 1;
static const int pcode___box__SETPROPERTY_DragDrop = pcode___box__GETPROPERTY_ParentControl + 1;
static const int pcode___box__GETPROPERTY_ParentControl1 = pcode___box__SETPROPERTY_DragDrop + 1;
static const int pcode___box__SETPROPERTY_ControlType = pcode___box__GETPROPERTY_ParentControl1 + 1;
static const int pcode___box__GETPROPERTY_ControlType = pcode___box__SETPROPERTY_ControlType + 1;
static const int pcode___box__SETPROPERTY_Focus = pcode___box__GETPROPERTY_ControlType + 1;
static const int pcode___box__GETPROPERTY_Focus = pcode___box__SETPROPERTY_Focus + 1;
static const int pcode___box__SETPROPERTY_FocusPolicy = pcode___box__GETPROPERTY_Focus + 1;
static const int pcode___box__GETPROPERTY_FocusPolicy = pcode___box__SETPROPERTY_FocusPolicy + 1;
static const int pcode___box__SETPROPERTY_FocusProxy = pcode___box__GETPROPERTY_FocusPolicy + 1;
static const int pcode___box__GETPROPERTY_FocusProxy = pcode___box__SETPROPERTY_FocusProxy + 1;
static const int pcode___box__SETPROPERTY_FocusOrder = pcode___box__GETPROPERTY_FocusProxy + 1;
static const int pcode___box__GETPROPERTY_FocusOrder = pcode___box__SETPROPERTY_FocusOrder + 1;
static const int pcode___box__SETPROPERTY_Cursor = pcode___box__GETPROPERTY_FocusOrder + 1;
static const int pcode___box__GETPROPERTY_Cursor = pcode___box__SETPROPERTY_Cursor + 1;
static const int pcode___box__SETPROPERTY_FontName = pcode___box__GETPROPERTY_Cursor + 1;
static const int pcode___box__GETPROPERTY_FontName = pcode___box__SETPROPERTY_FontName + 1;
static const int pcode___box__SETPROPERTY_FontSize = pcode___box__GETPROPERTY_FontName + 1;
static const int pcode___box__GETPROPERTY_FontSize = pcode___box__SETPROPERTY_FontSize + 1;
static const int pcode___box__SETPROPERTY_FontItalic = pcode___box__GETPROPERTY_FontSize + 1;
static const int pcode___box__GETPROPERTY_FontItalic = pcode___box__SETPROPERTY_FontItalic + 1;
static const int pcode___box__SETPROPERTY_FontBold = pcode___box__GETPROPERTY_FontItalic + 1;
static const int pcode___box__GETPROPERTY_FontBold = pcode___box__SETPROPERTY_FontBold + 1;
static const int pcode___box__SETPROPERTY_FontUnderline = pcode___box__GETPROPERTY_FontBold + 1;
static const int pcode___box__GETPROPERTY_FontUnderline = pcode___box__SETPROPERTY_FontUnderline + 1;
static const int pcode___box__SETPROPERTY_FontColor = pcode___box__GETPROPERTY_FontUnderline + 1;
static const int pcode___box__GETPROPERTY_FontColor = pcode___box__SETPROPERTY_FontColor + 1;
static const int pcode___box__SETPROPERTY_Enabled = pcode___box__GETPROPERTY_FontColor + 1;
static const int pcode___box__GETPROPERTY_Enabled = pcode___box__SETPROPERTY_Enabled + 1;
static const int pcode___box__SETPROPERTY_Visible = pcode___box__GETPROPERTY_Enabled + 1;
static const int pcode___box__GETPROPERTY_Visible = pcode___box__SETPROPERTY_Visible + 1;
static const int pcode___box__SETPROPERTY_StatusTip = pcode___box__GETPROPERTY_Visible + 1;
static const int pcode___box__GETPROPERTY_StatusTip = pcode___box__SETPROPERTY_StatusTip + 1;
static const int pcode___box__SETPROPERTY_ToolTip = pcode___box__GETPROPERTY_StatusTip + 1;
static const int pcode___box__GETPROPERTY_ToolTip = pcode___box__SETPROPERTY_ToolTip + 1;
static const int pcode___box__SETPROPERTY_StyleSheet = pcode___box__GETPROPERTY_ToolTip + 1;
static const int pcode___box__GETPROPERTY_StyleSheet = pcode___box__SETPROPERTY_StyleSheet + 1;
static const int pcode___box__SETPROPERTY_WhatsThis = pcode___box__GETPROPERTY_StyleSheet + 1;
static const int pcode___box__GETPROPERTY_WhatsThis = pcode___box__SETPROPERTY_WhatsThis + 1;
static const int pcode___box__SETPROPERTY_TimerInterval = pcode___box__GETPROPERTY_WhatsThis + 1;
static const int pcode___box__GETPROPERTY_TimerInterval = pcode___box__SETPROPERTY_TimerInterval + 1;
static const int pcode___box__SETPROPERTY_Opacity = pcode___box__GETPROPERTY_TimerInterval + 1;
static const int pcode___box__GETPROPERTY_Opacity = pcode___box__SETPROPERTY_Opacity + 1;
static const int pcode___box__SETPROPERTY_BoxIndex = pcode___box__GETPROPERTY_Opacity + 1;
static const int pcode___box__GETPROPERTY_BoxIndex = pcode___box__SETPROPERTY_BoxIndex + 1;
static const int pcode___box__SETPROPERTY_SplitIndex = pcode___box__GETPROPERTY_BoxIndex + 1;
static const int pcode___box__GETPROPERTY_SplitIndex = pcode___box__SETPROPERTY_SplitIndex + 1;
static const int pcode___box__SETPROPERTY_TabIndex = pcode___box__GETPROPERTY_SplitIndex + 1;
static const int pcode___box__GETPROPERTY_TabIndex = pcode___box__SETPROPERTY_TabIndex + 1;
static const int pcode___box__SETPROPERTY_BoxX = pcode___box__GETPROPERTY_TabIndex + 1;
static const int pcode___box__GETPROPERTY_BoxX = pcode___box__SETPROPERTY_BoxX + 1;
static const int pcode___box__SETPROPERTY_BoxY = pcode___box__GETPROPERTY_BoxX + 1;
static const int pcode___box__GETPROPERTY_BoxY = pcode___box__SETPROPERTY_BoxY + 1;
static const int pcode___box__SETPROPERTY_ParentIndex = pcode___box__GETPROPERTY_BoxY + 1;
static const int pcode___box__GETPROPERTY_ParentIndex = pcode___box__SETPROPERTY_ParentIndex + 1;
static const int pcode___box__SETPROPERTY_ControlType1 = pcode___box__GETPROPERTY_ParentIndex + 1;
static const int pcode___box__GETPROPERTY_ControlType1 = pcode___box__SETPROPERTY_ControlType1 + 1;
static const int pcode___box__SETPROPERTY_SQLName = pcode___box__GETPROPERTY_ControlType1 + 1;
static const int pcode___box__GETPROPERTY_SQLName = pcode___box__SETPROPERTY_SQLName + 1;
static const int pcode___box__SETPROPERTY_SQLType = pcode___box__GETPROPERTY_SQLName + 1;
static const int pcode___box__GETPROPERTY_SQLType = pcode___box__SETPROPERTY_SQLType + 1;
static const int pcode___box__SETPROPERTY_SQLCaption = pcode___box__GETPROPERTY_SQLType + 1;
static const int pcode___box__GETPROPERTY_SQLCaption = pcode___box__SETPROPERTY_SQLCaption + 1;
static const int pcode___box__SETPROPERTY_SQLWidth = pcode___box__GETPROPERTY_SQLCaption + 1;
static const int pcode___box__GETPROPERTY_SQLWidth = pcode___box__SETPROPERTY_SQLWidth + 1;
static const int pcode___box__EVENT_OnOpen = pcode___box__GETPROPERTY_SQLWidth + 1;
static const int pcode___box__EVENT_OnClose = pcode___box__EVENT_OnOpen + 1;
static const int pcode___box__EVENT_OnContextMenu = pcode___box__EVENT_OnClose + 1;
static const int pcode___box__EVENT_OnDragEnter = pcode___box__EVENT_OnContextMenu + 1;
static const int pcode___box__EVENT_OnDragExit = pcode___box__EVENT_OnDragEnter + 1;
static const int pcode___box__EVENT_OnDragMove = pcode___box__EVENT_OnDragExit + 1;
static const int pcode___box__EVENT_OnDrop = pcode___box__EVENT_OnDragMove + 1;
static const int pcode___box__EVENT_OnEnter = pcode___box__EVENT_OnDrop + 1;
static const int pcode___box__EVENT_OnGotFocus = pcode___box__EVENT_OnEnter + 1;
static const int pcode___box__EVENT_OnLostFocus = pcode___box__EVENT_OnGotFocus + 1;
static const int pcode___box__EVENT_OnHide = pcode___box__EVENT_OnLostFocus + 1;
static const int pcode___box__EVENT_OnKeyDown = pcode___box__EVENT_OnHide + 1;
static const int pcode___box__EVENT_OnKeyUp = pcode___box__EVENT_OnKeyDown + 1;
static const int pcode___box__EVENT_OnKeyPress = pcode___box__EVENT_OnKeyUp + 1;
static const int pcode___box__EVENT_OnExit = pcode___box__EVENT_OnKeyPress + 1;
static const int pcode___box__EVENT_OnDblClick = pcode___box__EVENT_OnExit + 1;
static const int pcode___box__EVENT_OnClick = pcode___box__EVENT_OnDblClick + 1;
static const int pcode___box__EVENT_OnMouseMove = pcode___box__EVENT_OnClick + 1;
static const int pcode___box__EVENT_OnMouseDown = pcode___box__EVENT_OnMouseMove + 1;
static const int pcode___box__EVENT_OnMouseUp = pcode___box__EVENT_OnMouseDown + 1;
static const int pcode___box__EVENT_OnMove = pcode___box__EVENT_OnMouseUp + 1;
static const int pcode___box__EVENT_OnPaint = pcode___box__EVENT_OnMove + 1;
static const int pcode___box__EVENT_OnResize = pcode___box__EVENT_OnPaint + 1;
static const int pcode___box__EVENT_OnShow = pcode___box__EVENT_OnResize + 1;
static const int pcode___box__EVENT_OnMouseWheel = pcode___box__EVENT_OnShow + 1;
static const int pcode___box__EVENT_OnTimer = pcode___box__EVENT_OnMouseWheel + 1;
static const int pcode___box__EVENT_OnPrint = pcode___box__EVENT_OnTimer + 1;
static const int pcode___line___line = pcode___line * SPACE;
static const int pcode___line___line1 = pcode___line___line + 1;


static const int pcode___line__CONST_Vertical = pcode___line___line1 + 1;
static const int pcode___line__CONST_Horizontal = pcode___line__CONST_Vertical + 1;

static const int pcode___line__SETPROPERTY_MouseTracking = pcode___line__CONST_Horizontal + 1;
static const int pcode___line__GETPROPERTY_MouseTracking = pcode___line__SETPROPERTY_MouseTracking + 1; 


static const int pcode___line__EVENT_OnSingleShot = pcode___line__GETPROPERTY_MouseTracking + 1;
static const int pcode___line__EVENT_OnEnabled = pcode___line__EVENT_OnSingleShot + 1;
static const int pcode___line__EVENT_OnDisabled = pcode___line__EVENT_OnEnabled + 1;

static const int pcode___line__SETPROPERTY_CursorAnimation = pcode___line__EVENT_OnDisabled + 1;
static const int pcode___line__GETPROPERTY_CursorAnimation = pcode___line__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___line__METHOD_DataIds = pcode___line__GETPROPERTY_CursorAnimation + 1;

static const int pcode___line__METHOD_DataRemove = pcode___line__METHOD_DataIds + 1;
static const int pcode___line__METHOD_DataRemoveAll = pcode___line__METHOD_DataRemove + 1;
static const int pcode___line__METHOD_DataSetBoolean = pcode___line__METHOD_DataRemoveAll + 1;
static const int pcode___line__METHOD_DataSetInteger = pcode___line__METHOD_DataSetBoolean + 1;
static const int pcode___line__METHOD_DataSetString = pcode___line__METHOD_DataSetInteger + 1;
static const int pcode___line__METHOD_DataSetDouble = pcode___line__METHOD_DataSetString + 1;
static const int pcode___line__METHOD_DataSetLong = pcode___line__METHOD_DataSetDouble + 1;
static const int pcode___line__METHOD_DataSetDecimal = pcode___line__METHOD_DataSetLong + 1;
static const int pcode___line__METHOD_DataSetDateTime = pcode___line__METHOD_DataSetDecimal + 1;


static const int pcode___line__METHOD_DataBoolean = pcode___line__METHOD_DataSetDateTime + 1;
static const int pcode___line__METHOD_DataInteger = pcode___line__METHOD_DataBoolean + 1;
static const int pcode___line__METHOD_DataString = pcode___line__METHOD_DataInteger + 1;
static const int pcode___line__METHOD_DataDouble = pcode___line__METHOD_DataString + 1;
static const int pcode___line__METHOD_DataLong = pcode___line__METHOD_DataDouble + 1;
static const int pcode___line__METHOD_DataDecimal = pcode___line__METHOD_DataLong + 1;
static const int pcode___line__METHOD_DataDateTime = pcode___line__METHOD_DataDecimal + 1;

static const int pcode___line__METHOD_ClearFocus = pcode___line__METHOD_DataDateTime + 1;
static const int pcode___line__METHOD_ToggleVisible = pcode___line__METHOD_ClearFocus + 1;

static const int pcode___line__METHOD_SingleShot = pcode___line__METHOD_ToggleVisible + 1;
static const int pcode___line__METHOD_StartTimer = pcode___line__METHOD_SingleShot + 1;
static const int pcode___line__METHOD_StopTimer = pcode___line__METHOD_StartTimer + 1;

//static const int pcode___line__METHOD_EventSender = pcode___line__METHOD_StopTimer + 1;

static const int pcode___line__METHOD_GlobalX = pcode___line__METHOD_StopTimer + 1;
static const int pcode___line__METHOD_GlobalY = pcode___line__METHOD_GlobalX + 1;
static const int pcode___line__METHOD_LocalX = pcode___line__METHOD_GlobalY + 1;
static const int pcode___line__METHOD_LocalY = pcode___line__METHOD_LocalX + 1;

static const int pcode___line__METHOD_UnderMouse = pcode___line__METHOD_LocalY + 1;

static const int pcode___line__SETPROPERTY_Mask = pcode___line__METHOD_UnderMouse + 1;
static const int pcode___line__GETPROPERTY_Mask = pcode___line__SETPROPERTY_Mask + 1;

static const int pcode___line__SETPROPERTY_SoundOnEvent = pcode___line__GETPROPERTY_Mask + 1;
static const int pcode___line__GETPROPERTY_SoundOnEvent = pcode___line__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___line__SETPROPERTY_Left = pcode___line__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___line__GETPROPERTY_Left = pcode___line__SETPROPERTY_Left + 1;
static const int pcode___line__SETPROPERTY_Top = pcode___line__GETPROPERTY_Left + 1;
static const int pcode___line__GETPROPERTY_Top = pcode___line__SETPROPERTY_Top + 1;

static const int pcode___line__SETPROPERTY_LocalX = pcode___line__GETPROPERTY_Top + 1;
static const int pcode___line__GETPROPERTY_LocalX = pcode___line__SETPROPERTY_LocalX + 1;
static const int pcode___line__SETPROPERTY_LocalY = pcode___line__GETPROPERTY_LocalX + 1;
static const int pcode___line__GETPROPERTY_LocalY = pcode___line__SETPROPERTY_LocalY + 1;

static const int pcode___line__SETPROPERTY_DrawOnPaint = pcode___line__GETPROPERTY_LocalY + 1;
static const int pcode___line__GETPROPERTY_DrawOnPaint = pcode___line__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___line__SETPROPERTY_Palette = pcode___line__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___line__GETPROPERTY_Palette = pcode___line__SETPROPERTY_Palette + 1;


static const int pcode___line__SETPROPERTY_BackgroundStyle = pcode___line__GETPROPERTY_Palette + 1;
static const int pcode___line__GETPROPERTY_BackgroundStyle = pcode___line__SETPROPERTY_BackgroundStyle + 1;



static const int pcode___line__SETPROPERTY_Layout = pcode___line__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___line__GETPROPERTY_Layout = pcode___line__SETPROPERTY_Layout + 1;

static const int pcode___line__SETPROPERTY_Flip = pcode___line__GETPROPERTY_Layout + 1;
static const int pcode___line__GETPROPERTY_Flip = pcode___line__SETPROPERTY_Flip + 1;
static const int pcode___line__SETPROPERTY_Flat = pcode___line__GETPROPERTY_Flip + 1;
static const int pcode___line__GETPROPERTY_Flat = pcode___line__SETPROPERTY_Flat + 1;
static const int pcode___line__SETPROPERTY_Orientation = pcode___line__GETPROPERTY_Flat + 1;
static const int pcode___line__GETPROPERTY_Orientation = pcode___line__SETPROPERTY_Orientation + 1;

static const int pcode___line__METHOD_Move = pcode___line__GETPROPERTY_Orientation + 1;
static const int pcode___line__METHOD_Resize = pcode___line__METHOD_Move + 1;
static const int pcode___line__METHOD_Show = pcode___line__METHOD_Resize + 1;
static const int pcode___line__METHOD_Hide = pcode___line__METHOD_Show + 1;
static const int pcode___line__METHOD_RepaintAlways = pcode___line__METHOD_Hide + 1;
static const int pcode___line__METHOD_Repaint = pcode___line__METHOD_RepaintAlways + 1;
static const int pcode___line__METHOD_Raise = pcode___line__METHOD_Repaint + 1;
static const int pcode___line__METHOD_Lower = pcode___line__METHOD_Raise + 1;
static const int pcode___line__METHOD_Close = pcode___line__METHOD_Lower + 1;
static const int pcode___line__METHOD_Open = pcode___line__METHOD_Close + 1;
static const int pcode___line__METHOD_SetFocus = pcode___line__METHOD_Open + 1;
static const int pcode___line__SETPROPERTY_Name = pcode___line__METHOD_SetFocus + 1;
static const int pcode___line__GETPROPERTY_Name = pcode___line__SETPROPERTY_Name + 1;
static const int pcode___line__SETPROPERTY_Group = pcode___line__GETPROPERTY_Name + 1;
static const int pcode___line__GETPROPERTY_Group = pcode___line__SETPROPERTY_Group + 1;
static const int pcode___line__SETPROPERTY_Background = pcode___line__GETPROPERTY_Group + 1;
static const int pcode___line__GETPROPERTY_Background = pcode___line__SETPROPERTY_Background + 1;
static const int pcode___line__SETPROPERTY_X = pcode___line__GETPROPERTY_Background + 1;
static const int pcode___line__GETPROPERTY_X = pcode___line__SETPROPERTY_X + 1;
static const int pcode___line__SETPROPERTY_Y = pcode___line__GETPROPERTY_X + 1;
static const int pcode___line__GETPROPERTY_Y = pcode___line__SETPROPERTY_Y + 1;
static const int pcode___line__SETPROPERTY_Width = pcode___line__GETPROPERTY_Y + 1;
static const int pcode___line__GETPROPERTY_Width = pcode___line__SETPROPERTY_Width + 1;
static const int pcode___line__SETPROPERTY_Height = pcode___line__GETPROPERTY_Width + 1;
static const int pcode___line__GETPROPERTY_Height = pcode___line__SETPROPERTY_Height + 1;
static const int pcode___line__GETPROPERTY_GlobalX = pcode___line__GETPROPERTY_Height + 1;
static const int pcode___line__GETPROPERTY_GlobalY = pcode___line__GETPROPERTY_GlobalX + 1;
static const int pcode___line__GETPROPERTY_OldX = pcode___line__GETPROPERTY_GlobalY + 1;
static const int pcode___line__GETPROPERTY_OldY = pcode___line__GETPROPERTY_OldX + 1;
static const int pcode___line__GETPROPERTY_OldWidth = pcode___line__GETPROPERTY_OldY + 1;
static const int pcode___line__GETPROPERTY_OldHeight = pcode___line__GETPROPERTY_OldWidth + 1;
static const int pcode___line__SETPROPERTY_MinimumWidth = pcode___line__GETPROPERTY_OldHeight + 1;
static const int pcode___line__GETPROPERTY_MinimumWidth = pcode___line__SETPROPERTY_MinimumWidth + 1;
static const int pcode___line__SETPROPERTY_MinimumHeight = pcode___line__GETPROPERTY_MinimumWidth + 1;
static const int pcode___line__GETPROPERTY_MinimumHeight = pcode___line__SETPROPERTY_MinimumHeight + 1;
static const int pcode___line__SETPROPERTY_MaximumWidth = pcode___line__GETPROPERTY_MinimumHeight + 1;
static const int pcode___line__GETPROPERTY_MaximumWidth = pcode___line__SETPROPERTY_MaximumWidth + 1;
static const int pcode___line__SETPROPERTY_MaximumHeight = pcode___line__GETPROPERTY_MaximumWidth + 1;
static const int pcode___line__GETPROPERTY_MaximumHeight = pcode___line__SETPROPERTY_MaximumHeight + 1;
static const int pcode___line__SETPROPERTY_Tag = pcode___line__GETPROPERTY_MaximumHeight + 1;
static const int pcode___line__GETPROPERTY_Tag = pcode___line__SETPROPERTY_Tag + 1;
static const int pcode___line__SETPROPERTY_CSV = pcode___line__GETPROPERTY_Tag + 1;
static const int pcode___line__GETPROPERTY_CSV = pcode___line__SETPROPERTY_CSV + 1;
static const int pcode___line__SETPROPERTY_ParentForm = pcode___line__GETPROPERTY_CSV + 1;
static const int pcode___line__GETPROPERTY_ParentForm = pcode___line__SETPROPERTY_ParentForm + 1;
static const int pcode___line__SETPROPERTY_ParentControl = pcode___line__GETPROPERTY_ParentForm + 1;
static const int pcode___line__GETPROPERTY_ParentControl = pcode___line__SETPROPERTY_ParentControl + 1;
static const int pcode___line__SETPROPERTY_DragDrop = pcode___line__GETPROPERTY_ParentControl + 1;
static const int pcode___line__GETPROPERTY_ParentControl1 = pcode___line__SETPROPERTY_DragDrop + 1;
static const int pcode___line__SETPROPERTY_ControlType = pcode___line__GETPROPERTY_ParentControl1 + 1;
static const int pcode___line__GETPROPERTY_ControlType = pcode___line__SETPROPERTY_ControlType + 1;
static const int pcode___line__SETPROPERTY_Focus = pcode___line__GETPROPERTY_ControlType + 1;
static const int pcode___line__GETPROPERTY_Focus = pcode___line__SETPROPERTY_Focus + 1;
static const int pcode___line__SETPROPERTY_FocusPolicy = pcode___line__GETPROPERTY_Focus + 1;
static const int pcode___line__GETPROPERTY_FocusPolicy = pcode___line__SETPROPERTY_FocusPolicy + 1;
static const int pcode___line__SETPROPERTY_FocusProxy = pcode___line__GETPROPERTY_FocusPolicy + 1;
static const int pcode___line__GETPROPERTY_FocusProxy = pcode___line__SETPROPERTY_FocusProxy + 1;
static const int pcode___line__SETPROPERTY_FocusOrder = pcode___line__GETPROPERTY_FocusProxy + 1;
static const int pcode___line__GETPROPERTY_FocusOrder = pcode___line__SETPROPERTY_FocusOrder + 1;
static const int pcode___line__SETPROPERTY_Cursor = pcode___line__GETPROPERTY_FocusOrder + 1;
static const int pcode___line__GETPROPERTY_Cursor = pcode___line__SETPROPERTY_Cursor + 1;
static const int pcode___line__SETPROPERTY_FontName = pcode___line__GETPROPERTY_Cursor + 1;
static const int pcode___line__GETPROPERTY_FontName = pcode___line__SETPROPERTY_FontName + 1;
static const int pcode___line__SETPROPERTY_FontSize = pcode___line__GETPROPERTY_FontName + 1;
static const int pcode___line__GETPROPERTY_FontSize = pcode___line__SETPROPERTY_FontSize + 1;
static const int pcode___line__SETPROPERTY_FontItalic = pcode___line__GETPROPERTY_FontSize + 1;
static const int pcode___line__GETPROPERTY_FontItalic = pcode___line__SETPROPERTY_FontItalic + 1;
static const int pcode___line__SETPROPERTY_FontBold = pcode___line__GETPROPERTY_FontItalic + 1;
static const int pcode___line__GETPROPERTY_FontBold = pcode___line__SETPROPERTY_FontBold + 1;
static const int pcode___line__SETPROPERTY_FontUnderline = pcode___line__GETPROPERTY_FontBold + 1;
static const int pcode___line__GETPROPERTY_FontUnderline = pcode___line__SETPROPERTY_FontUnderline + 1;
static const int pcode___line__SETPROPERTY_FontColor = pcode___line__GETPROPERTY_FontUnderline + 1;
static const int pcode___line__GETPROPERTY_FontColor = pcode___line__SETPROPERTY_FontColor + 1;
static const int pcode___line__SETPROPERTY_Enabled = pcode___line__GETPROPERTY_FontColor + 1;
static const int pcode___line__GETPROPERTY_Enabled = pcode___line__SETPROPERTY_Enabled + 1;
static const int pcode___line__SETPROPERTY_Visible = pcode___line__GETPROPERTY_Enabled + 1;
static const int pcode___line__GETPROPERTY_Visible = pcode___line__SETPROPERTY_Visible + 1;
static const int pcode___line__SETPROPERTY_StatusTip = pcode___line__GETPROPERTY_Visible + 1;
static const int pcode___line__GETPROPERTY_StatusTip = pcode___line__SETPROPERTY_StatusTip + 1;
static const int pcode___line__SETPROPERTY_ToolTip = pcode___line__GETPROPERTY_StatusTip + 1;
static const int pcode___line__GETPROPERTY_ToolTip = pcode___line__SETPROPERTY_ToolTip + 1;
static const int pcode___line__SETPROPERTY_StyleSheet = pcode___line__GETPROPERTY_ToolTip + 1;
static const int pcode___line__GETPROPERTY_StyleSheet = pcode___line__SETPROPERTY_StyleSheet + 1;
static const int pcode___line__SETPROPERTY_WhatsThis = pcode___line__GETPROPERTY_StyleSheet + 1;
static const int pcode___line__GETPROPERTY_WhatsThis = pcode___line__SETPROPERTY_WhatsThis + 1;
static const int pcode___line__SETPROPERTY_TimerInterval = pcode___line__GETPROPERTY_WhatsThis + 1;
static const int pcode___line__GETPROPERTY_TimerInterval = pcode___line__SETPROPERTY_TimerInterval + 1;
static const int pcode___line__SETPROPERTY_Opacity = pcode___line__GETPROPERTY_TimerInterval + 1;
static const int pcode___line__GETPROPERTY_Opacity = pcode___line__SETPROPERTY_Opacity + 1;
static const int pcode___line__SETPROPERTY_BoxIndex = pcode___line__GETPROPERTY_Opacity + 1;
static const int pcode___line__GETPROPERTY_BoxIndex = pcode___line__SETPROPERTY_BoxIndex + 1;
static const int pcode___line__SETPROPERTY_SplitIndex = pcode___line__GETPROPERTY_BoxIndex + 1;
static const int pcode___line__GETPROPERTY_SplitIndex = pcode___line__SETPROPERTY_SplitIndex + 1;
static const int pcode___line__SETPROPERTY_TabIndex = pcode___line__GETPROPERTY_SplitIndex + 1;
static const int pcode___line__GETPROPERTY_TabIndex = pcode___line__SETPROPERTY_TabIndex + 1;
static const int pcode___line__SETPROPERTY_BoxX = pcode___line__GETPROPERTY_TabIndex + 1;
static const int pcode___line__GETPROPERTY_BoxX = pcode___line__SETPROPERTY_BoxX + 1;
static const int pcode___line__SETPROPERTY_BoxY = pcode___line__GETPROPERTY_BoxX + 1;
static const int pcode___line__GETPROPERTY_BoxY = pcode___line__SETPROPERTY_BoxY + 1;
static const int pcode___line__SETPROPERTY_ParentIndex = pcode___line__GETPROPERTY_BoxY + 1;
static const int pcode___line__GETPROPERTY_ParentIndex = pcode___line__SETPROPERTY_ParentIndex + 1;
static const int pcode___line__SETPROPERTY_ControlType1 = pcode___line__GETPROPERTY_ParentIndex + 1;
static const int pcode___line__GETPROPERTY_ControlType1 = pcode___line__SETPROPERTY_ControlType1 + 1;
static const int pcode___line__SETPROPERTY_SQLName = pcode___line__GETPROPERTY_ControlType1 + 1;
static const int pcode___line__GETPROPERTY_SQLName = pcode___line__SETPROPERTY_SQLName + 1;
static const int pcode___line__SETPROPERTY_SQLType = pcode___line__GETPROPERTY_SQLName + 1;
static const int pcode___line__GETPROPERTY_SQLType = pcode___line__SETPROPERTY_SQLType + 1;
static const int pcode___line__SETPROPERTY_SQLCaption = pcode___line__GETPROPERTY_SQLType + 1;
static const int pcode___line__GETPROPERTY_SQLCaption = pcode___line__SETPROPERTY_SQLCaption + 1;
static const int pcode___line__SETPROPERTY_SQLWidth = pcode___line__GETPROPERTY_SQLCaption + 1;
static const int pcode___line__GETPROPERTY_SQLWidth = pcode___line__SETPROPERTY_SQLWidth + 1;
static const int pcode___line__EVENT_OnOpen = pcode___line__GETPROPERTY_SQLWidth + 1;
static const int pcode___line__EVENT_OnClose = pcode___line__EVENT_OnOpen + 1;
static const int pcode___line__EVENT_OnContextMenu = pcode___line__EVENT_OnClose + 1;
static const int pcode___line__EVENT_OnDragEnter = pcode___line__EVENT_OnContextMenu + 1;
static const int pcode___line__EVENT_OnDragExit = pcode___line__EVENT_OnDragEnter + 1;
static const int pcode___line__EVENT_OnDragMove = pcode___line__EVENT_OnDragExit + 1;
static const int pcode___line__EVENT_OnDrop = pcode___line__EVENT_OnDragMove + 1;
static const int pcode___line__EVENT_OnEnter = pcode___line__EVENT_OnDrop + 1;
static const int pcode___line__EVENT_OnGotFocus = pcode___line__EVENT_OnEnter + 1;
static const int pcode___line__EVENT_OnLostFocus = pcode___line__EVENT_OnGotFocus + 1;
static const int pcode___line__EVENT_OnHide = pcode___line__EVENT_OnLostFocus + 1;
static const int pcode___line__EVENT_OnKeyDown = pcode___line__EVENT_OnHide + 1;
static const int pcode___line__EVENT_OnKeyUp = pcode___line__EVENT_OnKeyDown + 1;
static const int pcode___line__EVENT_OnKeyPress = pcode___line__EVENT_OnKeyUp + 1;
static const int pcode___line__EVENT_OnExit = pcode___line__EVENT_OnKeyPress + 1;
static const int pcode___line__EVENT_OnDblClick = pcode___line__EVENT_OnExit + 1;
static const int pcode___line__EVENT_OnClick = pcode___line__EVENT_OnDblClick + 1;
static const int pcode___line__EVENT_OnMouseMove = pcode___line__EVENT_OnClick + 1;
static const int pcode___line__EVENT_OnMouseDown = pcode___line__EVENT_OnMouseMove + 1;
static const int pcode___line__EVENT_OnMouseUp = pcode___line__EVENT_OnMouseDown + 1;
static const int pcode___line__EVENT_OnMove = pcode___line__EVENT_OnMouseUp + 1;
static const int pcode___line__EVENT_OnPaint = pcode___line__EVENT_OnMove + 1;
static const int pcode___line__EVENT_OnResize = pcode___line__EVENT_OnPaint + 1;
static const int pcode___line__EVENT_OnShow = pcode___line__EVENT_OnResize + 1;
static const int pcode___line__EVENT_OnMouseWheel = pcode___line__EVENT_OnShow + 1;
static const int pcode___line__EVENT_OnTimer = pcode___line__EVENT_OnMouseWheel + 1;
static const int pcode___line__EVENT_OnPrint = pcode___line__EVENT_OnTimer + 1;
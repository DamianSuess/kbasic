static const int pcode___frame___frame = pcode___frame * SPACE;
static const int pcode___frame___frame1 = pcode___frame___frame + 1;

static const int pcode___frame__SETPROPERTY_MouseTracking = pcode___frame___frame1 + 1;
static const int pcode___frame__GETPROPERTY_MouseTracking = pcode___frame__SETPROPERTY_MouseTracking + 1; 


static const int pcode___frame__EVENT_OnSingleShot = pcode___frame__GETPROPERTY_MouseTracking + 1;
static const int pcode___frame__EVENT_OnEnabled = pcode___frame__EVENT_OnSingleShot + 1;
static const int pcode___frame__EVENT_OnDisabled = pcode___frame__EVENT_OnEnabled + 1;

static const int pcode___frame__SETPROPERTY_CursorAnimation = pcode___frame__EVENT_OnDisabled + 1;
static const int pcode___frame__GETPROPERTY_CursorAnimation = pcode___frame__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___frame__METHOD_DataIds = pcode___frame__GETPROPERTY_CursorAnimation + 1;

static const int pcode___frame__METHOD_DataRemove = pcode___frame__METHOD_DataIds + 1;
static const int pcode___frame__METHOD_DataRemoveAll = pcode___frame__METHOD_DataRemove + 1;
static const int pcode___frame__METHOD_DataSetBoolean = pcode___frame__METHOD_DataRemoveAll + 1;
static const int pcode___frame__METHOD_DataSetInteger = pcode___frame__METHOD_DataSetBoolean + 1;
static const int pcode___frame__METHOD_DataSetString = pcode___frame__METHOD_DataSetInteger + 1;
static const int pcode___frame__METHOD_DataSetDouble = pcode___frame__METHOD_DataSetString + 1;
static const int pcode___frame__METHOD_DataSetLong = pcode___frame__METHOD_DataSetDouble + 1;
static const int pcode___frame__METHOD_DataSetDecimal = pcode___frame__METHOD_DataSetLong + 1;
static const int pcode___frame__METHOD_DataSetDateTime = pcode___frame__METHOD_DataSetDecimal + 1;


static const int pcode___frame__METHOD_DataBoolean = pcode___frame__METHOD_DataSetDateTime + 1;
static const int pcode___frame__METHOD_DataInteger = pcode___frame__METHOD_DataBoolean + 1;
static const int pcode___frame__METHOD_DataString = pcode___frame__METHOD_DataInteger + 1;
static const int pcode___frame__METHOD_DataDouble = pcode___frame__METHOD_DataString + 1;
static const int pcode___frame__METHOD_DataLong = pcode___frame__METHOD_DataDouble + 1;
static const int pcode___frame__METHOD_DataDecimal = pcode___frame__METHOD_DataLong + 1;
static const int pcode___frame__METHOD_DataDateTime = pcode___frame__METHOD_DataDecimal + 1;

static const int pcode___frame__METHOD_ClearFocus = pcode___frame__METHOD_DataDateTime + 1;
static const int pcode___frame__METHOD_ToggleVisible = pcode___frame__METHOD_ClearFocus + 1;

static const int pcode___frame__METHOD_SingleShot = pcode___frame__METHOD_ToggleVisible + 1;
static const int pcode___frame__METHOD_StartTimer = pcode___frame__METHOD_SingleShot + 1;
static const int pcode___frame__METHOD_StopTimer = pcode___frame__METHOD_StartTimer + 1;

static const int pcode___frame__METHOD_GlobalX = pcode___frame__METHOD_StopTimer + 1;
static const int pcode___frame__METHOD_GlobalY = pcode___frame__METHOD_GlobalX + 1;
static const int pcode___frame__METHOD_LocalX = pcode___frame__METHOD_GlobalY + 1;
static const int pcode___frame__METHOD_LocalY = pcode___frame__METHOD_LocalX + 1;

static const int pcode___frame__METHOD_UnderMouse = pcode___frame__METHOD_LocalY + 1;

static const int pcode___frame__SETPROPERTY_Mask = pcode___frame__METHOD_UnderMouse + 1;
static const int pcode___frame__GETPROPERTY_Mask = pcode___frame__SETPROPERTY_Mask + 1;

static const int pcode___frame__SETPROPERTY_SoundOnEvent = pcode___frame__GETPROPERTY_Mask + 1;
static const int pcode___frame__GETPROPERTY_SoundOnEvent = pcode___frame__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___frame__SETPROPERTY_Left = pcode___frame__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___frame__GETPROPERTY_Left = pcode___frame__SETPROPERTY_Left + 1;
static const int pcode___frame__SETPROPERTY_Top = pcode___frame__GETPROPERTY_Left + 1;
static const int pcode___frame__GETPROPERTY_Top = pcode___frame__SETPROPERTY_Top + 1;

static const int pcode___frame__SETPROPERTY_LocalX = pcode___frame__GETPROPERTY_Top + 1;
static const int pcode___frame__GETPROPERTY_LocalX = pcode___frame__SETPROPERTY_LocalX + 1;
static const int pcode___frame__SETPROPERTY_LocalY = pcode___frame__GETPROPERTY_LocalX + 1;
static const int pcode___frame__GETPROPERTY_LocalY = pcode___frame__SETPROPERTY_LocalY + 1;

static const int pcode___frame__SETPROPERTY_DrawOnPaint = pcode___frame__GETPROPERTY_LocalY + 1;
static const int pcode___frame__GETPROPERTY_DrawOnPaint = pcode___frame__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___frame__SETPROPERTY_Palette = pcode___frame__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___frame__GETPROPERTY_Palette = pcode___frame__SETPROPERTY_Palette + 1;


static const int pcode___frame__SETPROPERTY_BackgroundStyle = pcode___frame__GETPROPERTY_Palette + 1;
static const int pcode___frame__GETPROPERTY_BackgroundStyle = pcode___frame__SETPROPERTY_BackgroundStyle + 1;



static const int pcode___frame__SETPROPERTY_Layout = pcode___frame__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___frame__GETPROPERTY_Layout = pcode___frame__SETPROPERTY_Layout + 1;

static const int pcode___frame__SETPROPERTY_Caption = pcode___frame__GETPROPERTY_Layout + 1;
static const int pcode___frame__GETPROPERTY_Caption = pcode___frame__SETPROPERTY_Caption + 1;
static const int pcode___frame__SETPROPERTY_Text = pcode___frame__GETPROPERTY_Caption + 1;
static const int pcode___frame__GETPROPERTY_Text = pcode___frame__SETPROPERTY_Text + 1;

static const int pcode___frame__METHOD_Move = pcode___frame__GETPROPERTY_Text + 1;
static const int pcode___frame__METHOD_Resize = pcode___frame__METHOD_Move + 1;
static const int pcode___frame__METHOD_Show = pcode___frame__METHOD_Resize + 1;
static const int pcode___frame__METHOD_Hide = pcode___frame__METHOD_Show + 1;
static const int pcode___frame__METHOD_RepaintAlways = pcode___frame__METHOD_Hide + 1;
static const int pcode___frame__METHOD_Repaint = pcode___frame__METHOD_RepaintAlways + 1;
static const int pcode___frame__METHOD_Raise = pcode___frame__METHOD_Repaint + 1;
static const int pcode___frame__METHOD_Lower = pcode___frame__METHOD_Raise + 1;
static const int pcode___frame__METHOD_Close = pcode___frame__METHOD_Lower + 1;
static const int pcode___frame__METHOD_Open = pcode___frame__METHOD_Close + 1;
static const int pcode___frame__METHOD_SetFocus = pcode___frame__METHOD_Open + 1;
static const int pcode___frame__SETPROPERTY_Name = pcode___frame__METHOD_SetFocus + 1;
static const int pcode___frame__GETPROPERTY_Name = pcode___frame__SETPROPERTY_Name + 1;
static const int pcode___frame__SETPROPERTY_Group = pcode___frame__GETPROPERTY_Name + 1;
static const int pcode___frame__GETPROPERTY_Group = pcode___frame__SETPROPERTY_Group + 1;
static const int pcode___frame__SETPROPERTY_Background = pcode___frame__GETPROPERTY_Group + 1;
static const int pcode___frame__GETPROPERTY_Background = pcode___frame__SETPROPERTY_Background + 1;
static const int pcode___frame__SETPROPERTY_X = pcode___frame__GETPROPERTY_Background + 1;
static const int pcode___frame__GETPROPERTY_X = pcode___frame__SETPROPERTY_X + 1;
static const int pcode___frame__SETPROPERTY_Y = pcode___frame__GETPROPERTY_X + 1;
static const int pcode___frame__GETPROPERTY_Y = pcode___frame__SETPROPERTY_Y + 1;
static const int pcode___frame__SETPROPERTY_Width = pcode___frame__GETPROPERTY_Y + 1;
static const int pcode___frame__GETPROPERTY_Width = pcode___frame__SETPROPERTY_Width + 1;
static const int pcode___frame__SETPROPERTY_Height = pcode___frame__GETPROPERTY_Width + 1;
static const int pcode___frame__GETPROPERTY_Height = pcode___frame__SETPROPERTY_Height + 1;
static const int pcode___frame__GETPROPERTY_GlobalX = pcode___frame__GETPROPERTY_Height + 1;
static const int pcode___frame__GETPROPERTY_GlobalY = pcode___frame__GETPROPERTY_GlobalX + 1;
static const int pcode___frame__GETPROPERTY_OldX = pcode___frame__GETPROPERTY_GlobalY + 1;
static const int pcode___frame__GETPROPERTY_OldY = pcode___frame__GETPROPERTY_OldX + 1;
static const int pcode___frame__GETPROPERTY_OldWidth = pcode___frame__GETPROPERTY_OldY + 1;
static const int pcode___frame__GETPROPERTY_OldHeight = pcode___frame__GETPROPERTY_OldWidth + 1;
static const int pcode___frame__SETPROPERTY_MinimumWidth = pcode___frame__GETPROPERTY_OldHeight + 1;
static const int pcode___frame__GETPROPERTY_MinimumWidth = pcode___frame__SETPROPERTY_MinimumWidth + 1;
static const int pcode___frame__SETPROPERTY_MinimumHeight = pcode___frame__GETPROPERTY_MinimumWidth + 1;
static const int pcode___frame__GETPROPERTY_MinimumHeight = pcode___frame__SETPROPERTY_MinimumHeight + 1;
static const int pcode___frame__SETPROPERTY_MaximumWidth = pcode___frame__GETPROPERTY_MinimumHeight + 1;
static const int pcode___frame__GETPROPERTY_MaximumWidth = pcode___frame__SETPROPERTY_MaximumWidth + 1;
static const int pcode___frame__SETPROPERTY_MaximumHeight = pcode___frame__GETPROPERTY_MaximumWidth + 1;
static const int pcode___frame__GETPROPERTY_MaximumHeight = pcode___frame__SETPROPERTY_MaximumHeight + 1;
static const int pcode___frame__SETPROPERTY_Tag = pcode___frame__GETPROPERTY_MaximumHeight + 1;
static const int pcode___frame__GETPROPERTY_Tag = pcode___frame__SETPROPERTY_Tag + 1;
static const int pcode___frame__SETPROPERTY_CSV = pcode___frame__GETPROPERTY_Tag + 1;
static const int pcode___frame__GETPROPERTY_CSV = pcode___frame__SETPROPERTY_CSV + 1;
static const int pcode___frame__SETPROPERTY_ParentForm = pcode___frame__GETPROPERTY_CSV + 1;
static const int pcode___frame__GETPROPERTY_ParentForm = pcode___frame__SETPROPERTY_ParentForm + 1;
static const int pcode___frame__SETPROPERTY_ParentControl = pcode___frame__GETPROPERTY_ParentForm + 1;
static const int pcode___frame__GETPROPERTY_ParentControl = pcode___frame__SETPROPERTY_ParentControl + 1;
static const int pcode___frame__SETPROPERTY_DragDrop = pcode___frame__GETPROPERTY_ParentControl + 1;
static const int pcode___frame__GETPROPERTY_ParentControl1 = pcode___frame__SETPROPERTY_DragDrop + 1;
static const int pcode___frame__SETPROPERTY_ControlType = pcode___frame__GETPROPERTY_ParentControl1 + 1;
static const int pcode___frame__GETPROPERTY_ControlType = pcode___frame__SETPROPERTY_ControlType + 1;
static const int pcode___frame__SETPROPERTY_Focus = pcode___frame__GETPROPERTY_ControlType + 1;
static const int pcode___frame__GETPROPERTY_Focus = pcode___frame__SETPROPERTY_Focus + 1;
static const int pcode___frame__SETPROPERTY_FocusPolicy = pcode___frame__GETPROPERTY_Focus + 1;
static const int pcode___frame__GETPROPERTY_FocusPolicy = pcode___frame__SETPROPERTY_FocusPolicy + 1;
static const int pcode___frame__SETPROPERTY_FocusProxy = pcode___frame__GETPROPERTY_FocusPolicy + 1;
static const int pcode___frame__GETPROPERTY_FocusProxy = pcode___frame__SETPROPERTY_FocusProxy + 1;
static const int pcode___frame__SETPROPERTY_FocusOrder = pcode___frame__GETPROPERTY_FocusProxy + 1;
static const int pcode___frame__GETPROPERTY_FocusOrder = pcode___frame__SETPROPERTY_FocusOrder + 1;
static const int pcode___frame__SETPROPERTY_Cursor = pcode___frame__GETPROPERTY_FocusOrder + 1;
static const int pcode___frame__GETPROPERTY_Cursor = pcode___frame__SETPROPERTY_Cursor + 1;
static const int pcode___frame__SETPROPERTY_FontName = pcode___frame__GETPROPERTY_Cursor + 1;
static const int pcode___frame__GETPROPERTY_FontName = pcode___frame__SETPROPERTY_FontName + 1;
static const int pcode___frame__SETPROPERTY_FontSize = pcode___frame__GETPROPERTY_FontName + 1;
static const int pcode___frame__GETPROPERTY_FontSize = pcode___frame__SETPROPERTY_FontSize + 1;
static const int pcode___frame__SETPROPERTY_FontItalic = pcode___frame__GETPROPERTY_FontSize + 1;
static const int pcode___frame__GETPROPERTY_FontItalic = pcode___frame__SETPROPERTY_FontItalic + 1;
static const int pcode___frame__SETPROPERTY_FontBold = pcode___frame__GETPROPERTY_FontItalic + 1;
static const int pcode___frame__GETPROPERTY_FontBold = pcode___frame__SETPROPERTY_FontBold + 1;
static const int pcode___frame__SETPROPERTY_FontUnderline = pcode___frame__GETPROPERTY_FontBold + 1;
static const int pcode___frame__GETPROPERTY_FontUnderline = pcode___frame__SETPROPERTY_FontUnderline + 1;
static const int pcode___frame__SETPROPERTY_FontColor = pcode___frame__GETPROPERTY_FontUnderline + 1;
static const int pcode___frame__GETPROPERTY_FontColor = pcode___frame__SETPROPERTY_FontColor + 1;
static const int pcode___frame__SETPROPERTY_Enabled = pcode___frame__GETPROPERTY_FontColor + 1;
static const int pcode___frame__GETPROPERTY_Enabled = pcode___frame__SETPROPERTY_Enabled + 1;
static const int pcode___frame__SETPROPERTY_Visible = pcode___frame__GETPROPERTY_Enabled + 1;
static const int pcode___frame__GETPROPERTY_Visible = pcode___frame__SETPROPERTY_Visible + 1;
static const int pcode___frame__SETPROPERTY_StatusTip = pcode___frame__GETPROPERTY_Visible + 1;
static const int pcode___frame__GETPROPERTY_StatusTip = pcode___frame__SETPROPERTY_StatusTip + 1;
static const int pcode___frame__SETPROPERTY_ToolTip = pcode___frame__GETPROPERTY_StatusTip + 1;
static const int pcode___frame__GETPROPERTY_ToolTip = pcode___frame__SETPROPERTY_ToolTip + 1;
static const int pcode___frame__SETPROPERTY_StyleSheet = pcode___frame__GETPROPERTY_ToolTip + 1;
static const int pcode___frame__GETPROPERTY_StyleSheet = pcode___frame__SETPROPERTY_StyleSheet + 1;
static const int pcode___frame__SETPROPERTY_WhatsThis = pcode___frame__GETPROPERTY_StyleSheet + 1;
static const int pcode___frame__GETPROPERTY_WhatsThis = pcode___frame__SETPROPERTY_WhatsThis + 1;
static const int pcode___frame__SETPROPERTY_TimerInterval = pcode___frame__GETPROPERTY_WhatsThis + 1;
static const int pcode___frame__GETPROPERTY_TimerInterval = pcode___frame__SETPROPERTY_TimerInterval + 1;
static const int pcode___frame__SETPROPERTY_Opacity = pcode___frame__GETPROPERTY_TimerInterval + 1;
static const int pcode___frame__GETPROPERTY_Opacity = pcode___frame__SETPROPERTY_Opacity + 1;
static const int pcode___frame__SETPROPERTY_BoxIndex = pcode___frame__GETPROPERTY_Opacity + 1;
static const int pcode___frame__GETPROPERTY_BoxIndex = pcode___frame__SETPROPERTY_BoxIndex + 1;
static const int pcode___frame__SETPROPERTY_SplitIndex = pcode___frame__GETPROPERTY_BoxIndex + 1;
static const int pcode___frame__GETPROPERTY_SplitIndex = pcode___frame__SETPROPERTY_SplitIndex + 1;
static const int pcode___frame__SETPROPERTY_TabIndex = pcode___frame__GETPROPERTY_SplitIndex + 1;
static const int pcode___frame__GETPROPERTY_TabIndex = pcode___frame__SETPROPERTY_TabIndex + 1;
static const int pcode___frame__SETPROPERTY_BoxX = pcode___frame__GETPROPERTY_TabIndex + 1;
static const int pcode___frame__GETPROPERTY_BoxX = pcode___frame__SETPROPERTY_BoxX + 1;
static const int pcode___frame__SETPROPERTY_BoxY = pcode___frame__GETPROPERTY_BoxX + 1;
static const int pcode___frame__GETPROPERTY_BoxY = pcode___frame__SETPROPERTY_BoxY + 1;
static const int pcode___frame__SETPROPERTY_ParentIndex = pcode___frame__GETPROPERTY_BoxY + 1;
static const int pcode___frame__GETPROPERTY_ParentIndex = pcode___frame__SETPROPERTY_ParentIndex + 1;
static const int pcode___frame__SETPROPERTY_ControlType1 = pcode___frame__GETPROPERTY_ParentIndex + 1;
static const int pcode___frame__GETPROPERTY_ControlType1 = pcode___frame__SETPROPERTY_ControlType1 + 1;
static const int pcode___frame__SETPROPERTY_SQLName = pcode___frame__GETPROPERTY_ControlType1 + 1;
static const int pcode___frame__GETPROPERTY_SQLName = pcode___frame__SETPROPERTY_SQLName + 1;
static const int pcode___frame__SETPROPERTY_SQLType = pcode___frame__GETPROPERTY_SQLName + 1;
static const int pcode___frame__GETPROPERTY_SQLType = pcode___frame__SETPROPERTY_SQLType + 1;
static const int pcode___frame__SETPROPERTY_SQLCaption = pcode___frame__GETPROPERTY_SQLType + 1;
static const int pcode___frame__GETPROPERTY_SQLCaption = pcode___frame__SETPROPERTY_SQLCaption + 1;
static const int pcode___frame__SETPROPERTY_SQLWidth = pcode___frame__GETPROPERTY_SQLCaption + 1;
static const int pcode___frame__GETPROPERTY_SQLWidth = pcode___frame__SETPROPERTY_SQLWidth + 1;
static const int pcode___frame__EVENT_OnOpen = pcode___frame__GETPROPERTY_SQLWidth + 1;
static const int pcode___frame__EVENT_OnClose = pcode___frame__EVENT_OnOpen + 1;
static const int pcode___frame__EVENT_OnContextMenu = pcode___frame__EVENT_OnClose + 1;
static const int pcode___frame__EVENT_OnDragEnter = pcode___frame__EVENT_OnContextMenu + 1;
static const int pcode___frame__EVENT_OnDragExit = pcode___frame__EVENT_OnDragEnter + 1;
static const int pcode___frame__EVENT_OnDragMove = pcode___frame__EVENT_OnDragExit + 1;
static const int pcode___frame__EVENT_OnDrop = pcode___frame__EVENT_OnDragMove + 1;
static const int pcode___frame__EVENT_OnEnter = pcode___frame__EVENT_OnDrop + 1;
static const int pcode___frame__EVENT_OnGotFocus = pcode___frame__EVENT_OnEnter + 1;
static const int pcode___frame__EVENT_OnLostFocus = pcode___frame__EVENT_OnGotFocus + 1;
static const int pcode___frame__EVENT_OnHide = pcode___frame__EVENT_OnLostFocus + 1;
static const int pcode___frame__EVENT_OnKeyDown = pcode___frame__EVENT_OnHide + 1;
static const int pcode___frame__EVENT_OnKeyUp = pcode___frame__EVENT_OnKeyDown + 1;
static const int pcode___frame__EVENT_OnKeyPress = pcode___frame__EVENT_OnKeyUp + 1;
static const int pcode___frame__EVENT_OnExit = pcode___frame__EVENT_OnKeyPress + 1;
static const int pcode___frame__EVENT_OnDblClick = pcode___frame__EVENT_OnExit + 1;
static const int pcode___frame__EVENT_OnClick = pcode___frame__EVENT_OnDblClick + 1;
static const int pcode___frame__EVENT_OnMouseMove = pcode___frame__EVENT_OnClick + 1;
static const int pcode___frame__EVENT_OnMouseDown = pcode___frame__EVENT_OnMouseMove + 1;
static const int pcode___frame__EVENT_OnMouseUp = pcode___frame__EVENT_OnMouseDown + 1;
static const int pcode___frame__EVENT_OnMove = pcode___frame__EVENT_OnMouseUp + 1;
static const int pcode___frame__EVENT_OnPaint = pcode___frame__EVENT_OnMove + 1;
static const int pcode___frame__EVENT_OnResize = pcode___frame__EVENT_OnPaint + 1;
static const int pcode___frame__EVENT_OnShow = pcode___frame__EVENT_OnResize + 1;
static const int pcode___frame__EVENT_OnMouseWheel = pcode___frame__EVENT_OnShow + 1;
static const int pcode___frame__EVENT_OnTimer = pcode___frame__EVENT_OnMouseWheel + 1;
static const int pcode___frame__EVENT_OnPrint = pcode___frame__EVENT_OnTimer + 1;
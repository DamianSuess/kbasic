static const int pcode___image___image = pcode___image * SPACE;
static const int pcode___image___image1 = pcode___image___image + 1;

static const int pcode___image__SETPROPERTY_MouseTracking = pcode___image___image1 + 1;
static const int pcode___image__GETPROPERTY_MouseTracking = pcode___image__SETPROPERTY_MouseTracking + 1; 

static const int pcode___image__EVENT_OnSingleShot = pcode___image__GETPROPERTY_MouseTracking + 1;
static const int pcode___image__EVENT_OnEnabled = pcode___image__EVENT_OnSingleShot + 1;
static const int pcode___image__EVENT_OnDisabled = pcode___image__EVENT_OnEnabled + 1;

static const int pcode___image__SETPROPERTY_CursorAnimation = pcode___image__EVENT_OnDisabled + 1;
static const int pcode___image__GETPROPERTY_CursorAnimation = pcode___image__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___image__METHOD_DataIds = pcode___image__GETPROPERTY_CursorAnimation + 1;

static const int pcode___image__METHOD_DataRemove = pcode___image__METHOD_DataIds + 1;
static const int pcode___image__METHOD_DataRemoveAll = pcode___image__METHOD_DataRemove + 1;
static const int pcode___image__METHOD_DataSetBoolean = pcode___image__METHOD_DataRemoveAll + 1;
static const int pcode___image__METHOD_DataSetInteger = pcode___image__METHOD_DataSetBoolean + 1;
static const int pcode___image__METHOD_DataSetString = pcode___image__METHOD_DataSetInteger + 1;
static const int pcode___image__METHOD_DataSetDouble = pcode___image__METHOD_DataSetString + 1;
static const int pcode___image__METHOD_DataSetLong = pcode___image__METHOD_DataSetDouble + 1;
static const int pcode___image__METHOD_DataSetDecimal = pcode___image__METHOD_DataSetLong + 1;
static const int pcode___image__METHOD_DataSetDateTime = pcode___image__METHOD_DataSetDecimal + 1;


static const int pcode___image__METHOD_DataBoolean = pcode___image__METHOD_DataSetDateTime + 1;
static const int pcode___image__METHOD_DataInteger = pcode___image__METHOD_DataBoolean + 1;
static const int pcode___image__METHOD_DataString = pcode___image__METHOD_DataInteger + 1;
static const int pcode___image__METHOD_DataDouble = pcode___image__METHOD_DataString + 1;
static const int pcode___image__METHOD_DataLong = pcode___image__METHOD_DataDouble + 1;
static const int pcode___image__METHOD_DataDecimal = pcode___image__METHOD_DataLong + 1;
static const int pcode___image__METHOD_DataDateTime = pcode___image__METHOD_DataDecimal + 1;

static const int pcode___image__METHOD_ClearFocus = pcode___image__METHOD_DataDateTime + 1;
static const int pcode___image__METHOD_ToggleVisible = pcode___image__METHOD_ClearFocus + 1;

static const int pcode___image__METHOD_SingleShot = pcode___image__METHOD_ToggleVisible + 1;
static const int pcode___image__METHOD_StartTimer = pcode___image__METHOD_SingleShot + 1;
static const int pcode___image__METHOD_StopTimer = pcode___image__METHOD_StartTimer + 1;

static const int pcode___image__METHOD_GlobalX = pcode___image__METHOD_StopTimer + 1;
static const int pcode___image__METHOD_GlobalY = pcode___image__METHOD_GlobalX + 1;
static const int pcode___image__METHOD_LocalX = pcode___image__METHOD_GlobalY + 1;
static const int pcode___image__METHOD_LocalY = pcode___image__METHOD_LocalX + 1;

static const int pcode___image__METHOD_UnderMouse = pcode___image__METHOD_LocalY + 1;

static const int pcode___image__SETPROPERTY_Mask = pcode___image__METHOD_UnderMouse + 1;
static const int pcode___image__GETPROPERTY_Mask = pcode___image__SETPROPERTY_Mask + 1;

static const int pcode___image__SETPROPERTY_SoundOnEvent = pcode___image__GETPROPERTY_Mask + 1;
static const int pcode___image__GETPROPERTY_SoundOnEvent = pcode___image__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___image__SETPROPERTY_Left = pcode___image__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___image__GETPROPERTY_Left = pcode___image__SETPROPERTY_Left + 1;
static const int pcode___image__SETPROPERTY_Top = pcode___image__GETPROPERTY_Left + 1;
static const int pcode___image__GETPROPERTY_Top = pcode___image__SETPROPERTY_Top + 1;

static const int pcode___image__SETPROPERTY_LocalX = pcode___image__GETPROPERTY_Top + 1;
static const int pcode___image__GETPROPERTY_LocalX = pcode___image__SETPROPERTY_LocalX + 1;
static const int pcode___image__SETPROPERTY_LocalY = pcode___image__GETPROPERTY_LocalX + 1;
static const int pcode___image__GETPROPERTY_LocalY = pcode___image__SETPROPERTY_LocalY + 1;

static const int pcode___image__SETPROPERTY_DrawOnPaint = pcode___image__GETPROPERTY_LocalY + 1;
static const int pcode___image__GETPROPERTY_DrawOnPaint = pcode___image__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___image__SETPROPERTY_Palette = pcode___image__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___image__GETPROPERTY_Palette = pcode___image__SETPROPERTY_Palette + 1;


static const int pcode___image__SETPROPERTY_BackgroundStyle = pcode___image__GETPROPERTY_Palette + 1;
static const int pcode___image__GETPROPERTY_BackgroundStyle = pcode___image__SETPROPERTY_BackgroundStyle + 1;


static const int pcode___image__SETPROPERTY_Layout = pcode___image__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___image__GETPROPERTY_Layout = pcode___image__SETPROPERTY_Layout + 1;

static const int pcode___image__SETPROPERTY_Value = pcode___image__GETPROPERTY_Layout + 1;
static const int pcode___image__GETPROPERTY_Value = pcode___image__SETPROPERTY_Value + 1;
static const int pcode___image__GETPROPERTY_OldValue = pcode___image__GETPROPERTY_Value + 1;
static const int pcode___image__SETPROPERTY_Text = pcode___image__GETPROPERTY_OldValue + 1;
static const int pcode___image__GETPROPERTY_Text = pcode___image__SETPROPERTY_Text + 1;

static const int pcode___image__METHOD_Move = pcode___image__GETPROPERTY_Text + 1;
static const int pcode___image__METHOD_Resize = pcode___image__METHOD_Move + 1;
static const int pcode___image__METHOD_Show = pcode___image__METHOD_Resize + 1;
static const int pcode___image__METHOD_Hide = pcode___image__METHOD_Show + 1;
static const int pcode___image__METHOD_RepaintAlways = pcode___image__METHOD_Hide + 1;
static const int pcode___image__METHOD_Repaint = pcode___image__METHOD_RepaintAlways + 1;
static const int pcode___image__METHOD_Raise = pcode___image__METHOD_Repaint + 1;
static const int pcode___image__METHOD_Lower = pcode___image__METHOD_Raise + 1;
static const int pcode___image__METHOD_Close = pcode___image__METHOD_Lower + 1;
static const int pcode___image__METHOD_Open = pcode___image__METHOD_Close + 1;
static const int pcode___image__METHOD_SetFocus = pcode___image__METHOD_Open + 1;
static const int pcode___image__SETPROPERTY_Name = pcode___image__METHOD_SetFocus + 1;
static const int pcode___image__GETPROPERTY_Name = pcode___image__SETPROPERTY_Name + 1;
static const int pcode___image__SETPROPERTY_Group = pcode___image__GETPROPERTY_Name + 1;
static const int pcode___image__GETPROPERTY_Group = pcode___image__SETPROPERTY_Group + 1;
static const int pcode___image__SETPROPERTY_Background = pcode___image__GETPROPERTY_Group + 1;
static const int pcode___image__GETPROPERTY_Background = pcode___image__SETPROPERTY_Background + 1;
static const int pcode___image__SETPROPERTY_X = pcode___image__GETPROPERTY_Background + 1;
static const int pcode___image__GETPROPERTY_X = pcode___image__SETPROPERTY_X + 1;
static const int pcode___image__SETPROPERTY_Y = pcode___image__GETPROPERTY_X + 1;
static const int pcode___image__GETPROPERTY_Y = pcode___image__SETPROPERTY_Y + 1;
static const int pcode___image__SETPROPERTY_Width = pcode___image__GETPROPERTY_Y + 1;
static const int pcode___image__GETPROPERTY_Width = pcode___image__SETPROPERTY_Width + 1;
static const int pcode___image__SETPROPERTY_Height = pcode___image__GETPROPERTY_Width + 1;
static const int pcode___image__GETPROPERTY_Height = pcode___image__SETPROPERTY_Height + 1;
static const int pcode___image__GETPROPERTY_GlobalX = pcode___image__GETPROPERTY_Height + 1;
static const int pcode___image__GETPROPERTY_GlobalY = pcode___image__GETPROPERTY_GlobalX + 1;
static const int pcode___image__GETPROPERTY_OldX = pcode___image__GETPROPERTY_GlobalY + 1;
static const int pcode___image__GETPROPERTY_OldY = pcode___image__GETPROPERTY_OldX + 1;
static const int pcode___image__GETPROPERTY_OldWidth = pcode___image__GETPROPERTY_OldY + 1;
static const int pcode___image__GETPROPERTY_OldHeight = pcode___image__GETPROPERTY_OldWidth + 1;
static const int pcode___image__SETPROPERTY_MinimumWidth = pcode___image__GETPROPERTY_OldHeight + 1;
static const int pcode___image__GETPROPERTY_MinimumWidth = pcode___image__SETPROPERTY_MinimumWidth + 1;
static const int pcode___image__SETPROPERTY_MinimumHeight = pcode___image__GETPROPERTY_MinimumWidth + 1;
static const int pcode___image__GETPROPERTY_MinimumHeight = pcode___image__SETPROPERTY_MinimumHeight + 1;
static const int pcode___image__SETPROPERTY_MaximumWidth = pcode___image__GETPROPERTY_MinimumHeight + 1;
static const int pcode___image__GETPROPERTY_MaximumWidth = pcode___image__SETPROPERTY_MaximumWidth + 1;
static const int pcode___image__SETPROPERTY_MaximumHeight = pcode___image__GETPROPERTY_MaximumWidth + 1;
static const int pcode___image__GETPROPERTY_MaximumHeight = pcode___image__SETPROPERTY_MaximumHeight + 1;
static const int pcode___image__SETPROPERTY_Tag = pcode___image__GETPROPERTY_MaximumHeight + 1;
static const int pcode___image__GETPROPERTY_Tag = pcode___image__SETPROPERTY_Tag + 1;
static const int pcode___image__SETPROPERTY_CSV = pcode___image__GETPROPERTY_Tag + 1;
static const int pcode___image__GETPROPERTY_CSV = pcode___image__SETPROPERTY_CSV + 1;
static const int pcode___image__SETPROPERTY_ParentForm = pcode___image__GETPROPERTY_CSV + 1;
static const int pcode___image__GETPROPERTY_ParentForm = pcode___image__SETPROPERTY_ParentForm + 1;
static const int pcode___image__SETPROPERTY_ParentControl = pcode___image__GETPROPERTY_ParentForm + 1;
static const int pcode___image__GETPROPERTY_ParentControl = pcode___image__SETPROPERTY_ParentControl + 1;
static const int pcode___image__SETPROPERTY_DragDrop = pcode___image__GETPROPERTY_ParentControl + 1;
static const int pcode___image__GETPROPERTY_ParentControl1 = pcode___image__SETPROPERTY_DragDrop + 1;
static const int pcode___image__SETPROPERTY_ControlType = pcode___image__GETPROPERTY_ParentControl1 + 1;
static const int pcode___image__GETPROPERTY_ControlType = pcode___image__SETPROPERTY_ControlType + 1;
static const int pcode___image__SETPROPERTY_Focus = pcode___image__GETPROPERTY_ControlType + 1;
static const int pcode___image__GETPROPERTY_Focus = pcode___image__SETPROPERTY_Focus + 1;
static const int pcode___image__SETPROPERTY_FocusPolicy = pcode___image__GETPROPERTY_Focus + 1;
static const int pcode___image__GETPROPERTY_FocusPolicy = pcode___image__SETPROPERTY_FocusPolicy + 1;
static const int pcode___image__SETPROPERTY_FocusProxy = pcode___image__GETPROPERTY_FocusPolicy + 1;
static const int pcode___image__GETPROPERTY_FocusProxy = pcode___image__SETPROPERTY_FocusProxy + 1;
static const int pcode___image__SETPROPERTY_FocusOrder = pcode___image__GETPROPERTY_FocusProxy + 1;
static const int pcode___image__GETPROPERTY_FocusOrder = pcode___image__SETPROPERTY_FocusOrder + 1;
static const int pcode___image__SETPROPERTY_Cursor = pcode___image__GETPROPERTY_FocusOrder + 1;
static const int pcode___image__GETPROPERTY_Cursor = pcode___image__SETPROPERTY_Cursor + 1;
static const int pcode___image__SETPROPERTY_FontName = pcode___image__GETPROPERTY_Cursor + 1;
static const int pcode___image__GETPROPERTY_FontName = pcode___image__SETPROPERTY_FontName + 1;
static const int pcode___image__SETPROPERTY_FontSize = pcode___image__GETPROPERTY_FontName + 1;
static const int pcode___image__GETPROPERTY_FontSize = pcode___image__SETPROPERTY_FontSize + 1;
static const int pcode___image__SETPROPERTY_FontItalic = pcode___image__GETPROPERTY_FontSize + 1;
static const int pcode___image__GETPROPERTY_FontItalic = pcode___image__SETPROPERTY_FontItalic + 1;
static const int pcode___image__SETPROPERTY_FontBold = pcode___image__GETPROPERTY_FontItalic + 1;
static const int pcode___image__GETPROPERTY_FontBold = pcode___image__SETPROPERTY_FontBold + 1;
static const int pcode___image__SETPROPERTY_FontUnderline = pcode___image__GETPROPERTY_FontBold + 1;
static const int pcode___image__GETPROPERTY_FontUnderline = pcode___image__SETPROPERTY_FontUnderline + 1;
static const int pcode___image__SETPROPERTY_FontColor = pcode___image__GETPROPERTY_FontUnderline + 1;
static const int pcode___image__GETPROPERTY_FontColor = pcode___image__SETPROPERTY_FontColor + 1;
static const int pcode___image__SETPROPERTY_Enabled = pcode___image__GETPROPERTY_FontColor + 1;
static const int pcode___image__GETPROPERTY_Enabled = pcode___image__SETPROPERTY_Enabled + 1;
static const int pcode___image__SETPROPERTY_Visible = pcode___image__GETPROPERTY_Enabled + 1;
static const int pcode___image__GETPROPERTY_Visible = pcode___image__SETPROPERTY_Visible + 1;
static const int pcode___image__SETPROPERTY_StatusTip = pcode___image__GETPROPERTY_Visible + 1;
static const int pcode___image__GETPROPERTY_StatusTip = pcode___image__SETPROPERTY_StatusTip + 1;
static const int pcode___image__SETPROPERTY_ToolTip = pcode___image__GETPROPERTY_StatusTip + 1;
static const int pcode___image__GETPROPERTY_ToolTip = pcode___image__SETPROPERTY_ToolTip + 1;
static const int pcode___image__SETPROPERTY_StyleSheet = pcode___image__GETPROPERTY_ToolTip + 1;
static const int pcode___image__GETPROPERTY_StyleSheet = pcode___image__SETPROPERTY_StyleSheet + 1;
static const int pcode___image__SETPROPERTY_WhatsThis = pcode___image__GETPROPERTY_StyleSheet + 1;
static const int pcode___image__GETPROPERTY_WhatsThis = pcode___image__SETPROPERTY_WhatsThis + 1;
static const int pcode___image__SETPROPERTY_TimerInterval = pcode___image__GETPROPERTY_WhatsThis + 1;
static const int pcode___image__GETPROPERTY_TimerInterval = pcode___image__SETPROPERTY_TimerInterval + 1;
static const int pcode___image__SETPROPERTY_Opacity = pcode___image__GETPROPERTY_TimerInterval + 1;
static const int pcode___image__GETPROPERTY_Opacity = pcode___image__SETPROPERTY_Opacity + 1;
static const int pcode___image__SETPROPERTY_BoxIndex = pcode___image__GETPROPERTY_Opacity + 1;
static const int pcode___image__GETPROPERTY_BoxIndex = pcode___image__SETPROPERTY_BoxIndex + 1;
static const int pcode___image__SETPROPERTY_SplitIndex = pcode___image__GETPROPERTY_BoxIndex + 1;
static const int pcode___image__GETPROPERTY_SplitIndex = pcode___image__SETPROPERTY_SplitIndex + 1;
static const int pcode___image__SETPROPERTY_TabIndex = pcode___image__GETPROPERTY_SplitIndex + 1;
static const int pcode___image__GETPROPERTY_TabIndex = pcode___image__SETPROPERTY_TabIndex + 1;
static const int pcode___image__SETPROPERTY_BoxX = pcode___image__GETPROPERTY_TabIndex + 1;
static const int pcode___image__GETPROPERTY_BoxX = pcode___image__SETPROPERTY_BoxX + 1;
static const int pcode___image__SETPROPERTY_BoxY = pcode___image__GETPROPERTY_BoxX + 1;
static const int pcode___image__GETPROPERTY_BoxY = pcode___image__SETPROPERTY_BoxY + 1;
static const int pcode___image__SETPROPERTY_ParentIndex = pcode___image__GETPROPERTY_BoxY + 1;
static const int pcode___image__GETPROPERTY_ParentIndex = pcode___image__SETPROPERTY_ParentIndex + 1;
static const int pcode___image__SETPROPERTY_ControlType1 = pcode___image__GETPROPERTY_ParentIndex + 1;
static const int pcode___image__GETPROPERTY_ControlType1 = pcode___image__SETPROPERTY_ControlType1 + 1;
static const int pcode___image__SETPROPERTY_SQLName = pcode___image__GETPROPERTY_ControlType1 + 1;
static const int pcode___image__GETPROPERTY_SQLName = pcode___image__SETPROPERTY_SQLName + 1;
static const int pcode___image__SETPROPERTY_SQLType = pcode___image__GETPROPERTY_SQLName + 1;
static const int pcode___image__GETPROPERTY_SQLType = pcode___image__SETPROPERTY_SQLType + 1;
static const int pcode___image__SETPROPERTY_SQLCaption = pcode___image__GETPROPERTY_SQLType + 1;
static const int pcode___image__GETPROPERTY_SQLCaption = pcode___image__SETPROPERTY_SQLCaption + 1;
static const int pcode___image__SETPROPERTY_SQLWidth = pcode___image__GETPROPERTY_SQLCaption + 1;
static const int pcode___image__GETPROPERTY_SQLWidth = pcode___image__SETPROPERTY_SQLWidth + 1;
static const int pcode___image__EVENT_OnOpen = pcode___image__GETPROPERTY_SQLWidth + 1;
static const int pcode___image__EVENT_OnClose = pcode___image__EVENT_OnOpen + 1;
static const int pcode___image__EVENT_OnContextMenu = pcode___image__EVENT_OnClose + 1;
static const int pcode___image__EVENT_OnDragEnter = pcode___image__EVENT_OnContextMenu + 1;
static const int pcode___image__EVENT_OnDragExit = pcode___image__EVENT_OnDragEnter + 1;
static const int pcode___image__EVENT_OnDragMove = pcode___image__EVENT_OnDragExit + 1;
static const int pcode___image__EVENT_OnDrop = pcode___image__EVENT_OnDragMove + 1;
static const int pcode___image__EVENT_OnEnter = pcode___image__EVENT_OnDrop + 1;
static const int pcode___image__EVENT_OnGotFocus = pcode___image__EVENT_OnEnter + 1;
static const int pcode___image__EVENT_OnLostFocus = pcode___image__EVENT_OnGotFocus + 1;
static const int pcode___image__EVENT_OnHide = pcode___image__EVENT_OnLostFocus + 1;
static const int pcode___image__EVENT_OnKeyDown = pcode___image__EVENT_OnHide + 1;
static const int pcode___image__EVENT_OnKeyUp = pcode___image__EVENT_OnKeyDown + 1;
static const int pcode___image__EVENT_OnKeyPress = pcode___image__EVENT_OnKeyUp + 1;
static const int pcode___image__EVENT_OnExit = pcode___image__EVENT_OnKeyPress + 1;
static const int pcode___image__EVENT_OnDblClick = pcode___image__EVENT_OnExit + 1;
static const int pcode___image__EVENT_OnClick = pcode___image__EVENT_OnDblClick + 1;
static const int pcode___image__EVENT_OnMouseMove = pcode___image__EVENT_OnClick + 1;
static const int pcode___image__EVENT_OnMouseDown = pcode___image__EVENT_OnMouseMove + 1;
static const int pcode___image__EVENT_OnMouseUp = pcode___image__EVENT_OnMouseDown + 1;
static const int pcode___image__EVENT_OnMove = pcode___image__EVENT_OnMouseUp + 1;
static const int pcode___image__EVENT_OnPaint = pcode___image__EVENT_OnMove + 1;
static const int pcode___image__EVENT_OnResize = pcode___image__EVENT_OnPaint + 1;
static const int pcode___image__EVENT_OnShow = pcode___image__EVENT_OnResize + 1;
static const int pcode___image__EVENT_OnMouseWheel = pcode___image__EVENT_OnShow + 1;
static const int pcode___image__EVENT_OnTimer = pcode___image__EVENT_OnMouseWheel + 1;
static const int pcode___image__EVENT_OnPrint = pcode___image__EVENT_OnTimer + 1;
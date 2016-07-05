static const int pcode___tab___tab = pcode___tab * SPACE;
static const int pcode___tab___tab1 = pcode___tab___tab + 1;



static const int pcode___tab__SETPROPERTY_MouseTracking = pcode___tab___tab1 + 1;
static const int pcode___tab__GETPROPERTY_MouseTracking = pcode___tab__SETPROPERTY_MouseTracking + 1; 


static const int pcode___tab__EVENT_OnSingleShot = pcode___tab__GETPROPERTY_MouseTracking + 1;
static const int pcode___tab__EVENT_OnEnabled = pcode___tab__EVENT_OnSingleShot + 1;
static const int pcode___tab__EVENT_OnDisabled = pcode___tab__EVENT_OnEnabled + 1;

static const int pcode___tab__SETPROPERTY_CursorAnimation = pcode___tab__EVENT_OnDisabled + 1;
static const int pcode___tab__GETPROPERTY_CursorAnimation = pcode___tab__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___tab__METHOD_DataIds = pcode___tab__GETPROPERTY_CursorAnimation + 1;

static const int pcode___tab__METHOD_DataRemove = pcode___tab__METHOD_DataIds + 1;
static const int pcode___tab__METHOD_DataRemoveAll = pcode___tab__METHOD_DataRemove + 1;
static const int pcode___tab__METHOD_DataSetBoolean = pcode___tab__METHOD_DataRemoveAll + 1;
static const int pcode___tab__METHOD_DataSetInteger = pcode___tab__METHOD_DataSetBoolean + 1;
static const int pcode___tab__METHOD_DataSetString = pcode___tab__METHOD_DataSetInteger + 1;
static const int pcode___tab__METHOD_DataSetDouble = pcode___tab__METHOD_DataSetString + 1;
static const int pcode___tab__METHOD_DataSetLong = pcode___tab__METHOD_DataSetDouble + 1;
static const int pcode___tab__METHOD_DataSetDecimal = pcode___tab__METHOD_DataSetLong + 1;
static const int pcode___tab__METHOD_DataSetDateTime = pcode___tab__METHOD_DataSetDecimal + 1;


static const int pcode___tab__METHOD_DataBoolean = pcode___tab__METHOD_DataSetDateTime + 1;
static const int pcode___tab__METHOD_DataInteger = pcode___tab__METHOD_DataBoolean + 1;
static const int pcode___tab__METHOD_DataString = pcode___tab__METHOD_DataInteger + 1;
static const int pcode___tab__METHOD_DataDouble = pcode___tab__METHOD_DataString + 1;
static const int pcode___tab__METHOD_DataLong = pcode___tab__METHOD_DataDouble + 1;
static const int pcode___tab__METHOD_DataDecimal = pcode___tab__METHOD_DataLong + 1;
static const int pcode___tab__METHOD_DataDateTime = pcode___tab__METHOD_DataDecimal + 1;

static const int pcode___tab__METHOD_ClearFocus = pcode___tab__METHOD_DataDateTime + 1;
static const int pcode___tab__METHOD_ToggleVisible = pcode___tab__METHOD_ClearFocus + 1;

static const int pcode___tab__METHOD_SingleShot = pcode___tab__METHOD_ToggleVisible + 1;
static const int pcode___tab__METHOD_StartTimer = pcode___tab__METHOD_SingleShot + 1;
static const int pcode___tab__METHOD_StopTimer = pcode___tab__METHOD_StartTimer + 1;

static const int pcode___tab__METHOD_GlobalX = pcode___tab__METHOD_StopTimer + 1;
static const int pcode___tab__METHOD_GlobalY = pcode___tab__METHOD_GlobalX + 1;
static const int pcode___tab__METHOD_LocalX = pcode___tab__METHOD_GlobalY + 1;
static const int pcode___tab__METHOD_LocalY = pcode___tab__METHOD_LocalX + 1;

static const int pcode___tab__METHOD_UnderMouse = pcode___tab__METHOD_LocalY + 1;

static const int pcode___tab__SETPROPERTY_Mask = pcode___tab__METHOD_UnderMouse + 1;
static const int pcode___tab__GETPROPERTY_Mask = pcode___tab__SETPROPERTY_Mask + 1;

static const int pcode___tab__SETPROPERTY_SoundOnEvent = pcode___tab__GETPROPERTY_Mask + 1;
static const int pcode___tab__GETPROPERTY_SoundOnEvent = pcode___tab__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___tab__SETPROPERTY_Left = pcode___tab__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___tab__GETPROPERTY_Left = pcode___tab__SETPROPERTY_Left + 1;
static const int pcode___tab__SETPROPERTY_Top = pcode___tab__GETPROPERTY_Left + 1;
static const int pcode___tab__GETPROPERTY_Top = pcode___tab__SETPROPERTY_Top + 1;

static const int pcode___tab__SETPROPERTY_LocalX = pcode___tab__GETPROPERTY_Top + 1;
static const int pcode___tab__GETPROPERTY_LocalX = pcode___tab__SETPROPERTY_LocalX + 1;
static const int pcode___tab__SETPROPERTY_LocalY = pcode___tab__GETPROPERTY_LocalX + 1;
static const int pcode___tab__GETPROPERTY_LocalY = pcode___tab__SETPROPERTY_LocalY + 1;

static const int pcode___tab__SETPROPERTY_DrawOnPaint = pcode___tab__GETPROPERTY_LocalY + 1;
static const int pcode___tab__GETPROPERTY_DrawOnPaint = pcode___tab__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___tab__SETPROPERTY_Palette = pcode___tab__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___tab__GETPROPERTY_Palette = pcode___tab__SETPROPERTY_Palette + 1;


static const int pcode___tab__SETPROPERTY_BackgroundStyle = pcode___tab__GETPROPERTY_Palette + 1;
static const int pcode___tab__GETPROPERTY_BackgroundStyle = pcode___tab__SETPROPERTY_BackgroundStyle + 1;


static const int pcode___tab__SETPROPERTY_Layout = pcode___tab__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___tab__GETPROPERTY_Layout = pcode___tab__SETPROPERTY_Layout + 1;
static const int pcode___tab__EVENT_OnEvent = pcode___tab__GETPROPERTY_Layout + 1;
static const int pcode___tab__METHOD_AppendTab = pcode___tab__EVENT_OnEvent + 1;
static const int pcode___tab__METHOD_InsertTab = pcode___tab__METHOD_AppendTab + 1;
static const int pcode___tab__METHOD_RemoveTab = pcode___tab__METHOD_InsertTab + 1;
static const int pcode___tab__METHOD_Len = pcode___tab__METHOD_RemoveTab + 1;
static const int pcode___tab__METHOD_SetTabEnabled = pcode___tab__METHOD_Len + 1;
static const int pcode___tab__METHOD_IsTabEnabled = pcode___tab__METHOD_SetTabEnabled + 1;
static const int pcode___tab__METHOD_Select = pcode___tab__METHOD_IsTabEnabled + 1;
static const int pcode___tab__METHOD_Selected = pcode___tab__METHOD_Select + 1;
static const int pcode___tab__METHOD_SetToolTip = pcode___tab__METHOD_Selected + 1;
static const int pcode___tab__METHOD_ToolTip = pcode___tab__METHOD_SetToolTip + 1;
static const int pcode___tab__METHOD_SetWhatsThis = pcode___tab__METHOD_ToolTip + 1;
static const int pcode___tab__METHOD_WhatsThis = pcode___tab__METHOD_SetWhatsThis + 1;
static const int pcode___tab__METHOD_SetCaption = pcode___tab__METHOD_WhatsThis + 1;
static const int pcode___tab__METHOD_Caption = pcode___tab__METHOD_SetCaption + 1;
static const int pcode___tab__METHOD_SetIcon = pcode___tab__METHOD_Caption + 1;
static const int pcode___tab__METHOD_Move = pcode___tab__METHOD_SetIcon + 1;
static const int pcode___tab__METHOD_Resize = pcode___tab__METHOD_Move + 1;
static const int pcode___tab__METHOD_Show = pcode___tab__METHOD_Resize + 1;
static const int pcode___tab__METHOD_Hide = pcode___tab__METHOD_Show + 1;
static const int pcode___tab__METHOD_RepaintAlways = pcode___tab__METHOD_Hide + 1;
static const int pcode___tab__METHOD_Repaint = pcode___tab__METHOD_RepaintAlways + 1;
static const int pcode___tab__METHOD_Raise = pcode___tab__METHOD_Repaint + 1;
static const int pcode___tab__METHOD_Lower = pcode___tab__METHOD_Raise + 1;
static const int pcode___tab__METHOD_Close = pcode___tab__METHOD_Lower + 1;
static const int pcode___tab__METHOD_Open = pcode___tab__METHOD_Close + 1;
static const int pcode___tab__METHOD_SetFocus = pcode___tab__METHOD_Open + 1;
static const int pcode___tab__SETPROPERTY_Name = pcode___tab__METHOD_SetFocus + 1;
static const int pcode___tab__GETPROPERTY_Name = pcode___tab__SETPROPERTY_Name + 1;
static const int pcode___tab__SETPROPERTY_Group = pcode___tab__GETPROPERTY_Name + 1;
static const int pcode___tab__GETPROPERTY_Group = pcode___tab__SETPROPERTY_Group + 1;
static const int pcode___tab__SETPROPERTY_Background = pcode___tab__GETPROPERTY_Group + 1;
static const int pcode___tab__GETPROPERTY_Background = pcode___tab__SETPROPERTY_Background + 1;
static const int pcode___tab__SETPROPERTY_X = pcode___tab__GETPROPERTY_Background + 1;
static const int pcode___tab__GETPROPERTY_X = pcode___tab__SETPROPERTY_X + 1;
static const int pcode___tab__SETPROPERTY_Y = pcode___tab__GETPROPERTY_X + 1;
static const int pcode___tab__GETPROPERTY_Y = pcode___tab__SETPROPERTY_Y + 1;
static const int pcode___tab__SETPROPERTY_Width = pcode___tab__GETPROPERTY_Y + 1;
static const int pcode___tab__GETPROPERTY_Width = pcode___tab__SETPROPERTY_Width + 1;
static const int pcode___tab__SETPROPERTY_Height = pcode___tab__GETPROPERTY_Width + 1;
static const int pcode___tab__GETPROPERTY_Height = pcode___tab__SETPROPERTY_Height + 1;
static const int pcode___tab__GETPROPERTY_GlobalX = pcode___tab__GETPROPERTY_Height + 1;
static const int pcode___tab__GETPROPERTY_GlobalY = pcode___tab__GETPROPERTY_GlobalX + 1;
static const int pcode___tab__GETPROPERTY_OldX = pcode___tab__GETPROPERTY_GlobalY + 1;
static const int pcode___tab__GETPROPERTY_OldY = pcode___tab__GETPROPERTY_OldX + 1;
static const int pcode___tab__GETPROPERTY_OldWidth = pcode___tab__GETPROPERTY_OldY + 1;
static const int pcode___tab__GETPROPERTY_OldHeight = pcode___tab__GETPROPERTY_OldWidth + 1;
static const int pcode___tab__SETPROPERTY_MinimumWidth = pcode___tab__GETPROPERTY_OldHeight + 1;
static const int pcode___tab__GETPROPERTY_MinimumWidth = pcode___tab__SETPROPERTY_MinimumWidth + 1;
static const int pcode___tab__SETPROPERTY_MinimumHeight = pcode___tab__GETPROPERTY_MinimumWidth + 1;
static const int pcode___tab__GETPROPERTY_MinimumHeight = pcode___tab__SETPROPERTY_MinimumHeight + 1;
static const int pcode___tab__SETPROPERTY_MaximumWidth = pcode___tab__GETPROPERTY_MinimumHeight + 1;
static const int pcode___tab__GETPROPERTY_MaximumWidth = pcode___tab__SETPROPERTY_MaximumWidth + 1;
static const int pcode___tab__SETPROPERTY_MaximumHeight = pcode___tab__GETPROPERTY_MaximumWidth + 1;
static const int pcode___tab__GETPROPERTY_MaximumHeight = pcode___tab__SETPROPERTY_MaximumHeight + 1;
static const int pcode___tab__SETPROPERTY_Tag = pcode___tab__GETPROPERTY_MaximumHeight + 1;
static const int pcode___tab__GETPROPERTY_Tag = pcode___tab__SETPROPERTY_Tag + 1;
static const int pcode___tab__SETPROPERTY_CSV = pcode___tab__GETPROPERTY_Tag + 1;
static const int pcode___tab__GETPROPERTY_CSV = pcode___tab__SETPROPERTY_CSV + 1;
static const int pcode___tab__SETPROPERTY_ParentForm = pcode___tab__GETPROPERTY_CSV + 1;
static const int pcode___tab__GETPROPERTY_ParentForm = pcode___tab__SETPROPERTY_ParentForm + 1;
static const int pcode___tab__SETPROPERTY_ParentControl = pcode___tab__GETPROPERTY_ParentForm + 1;
static const int pcode___tab__GETPROPERTY_ParentControl = pcode___tab__SETPROPERTY_ParentControl + 1;
static const int pcode___tab__SETPROPERTY_DragDrop = pcode___tab__GETPROPERTY_ParentControl + 1;
static const int pcode___tab__GETPROPERTY_ParentControl1 = pcode___tab__SETPROPERTY_DragDrop + 1;
static const int pcode___tab__SETPROPERTY_ControlType = pcode___tab__GETPROPERTY_ParentControl1 + 1;
static const int pcode___tab__GETPROPERTY_ControlType = pcode___tab__SETPROPERTY_ControlType + 1;
static const int pcode___tab__SETPROPERTY_Focus = pcode___tab__GETPROPERTY_ControlType + 1;
static const int pcode___tab__GETPROPERTY_Focus = pcode___tab__SETPROPERTY_Focus + 1;
static const int pcode___tab__SETPROPERTY_FocusPolicy = pcode___tab__GETPROPERTY_Focus + 1;
static const int pcode___tab__GETPROPERTY_FocusPolicy = pcode___tab__SETPROPERTY_FocusPolicy + 1;
static const int pcode___tab__SETPROPERTY_FocusProxy = pcode___tab__GETPROPERTY_FocusPolicy + 1;
static const int pcode___tab__GETPROPERTY_FocusProxy = pcode___tab__SETPROPERTY_FocusProxy + 1;
static const int pcode___tab__SETPROPERTY_FocusOrder = pcode___tab__GETPROPERTY_FocusProxy + 1;
static const int pcode___tab__GETPROPERTY_FocusOrder = pcode___tab__SETPROPERTY_FocusOrder + 1;
static const int pcode___tab__SETPROPERTY_Cursor = pcode___tab__GETPROPERTY_FocusOrder + 1;
static const int pcode___tab__GETPROPERTY_Cursor = pcode___tab__SETPROPERTY_Cursor + 1;
static const int pcode___tab__SETPROPERTY_FontName = pcode___tab__GETPROPERTY_Cursor + 1;
static const int pcode___tab__GETPROPERTY_FontName = pcode___tab__SETPROPERTY_FontName + 1;
static const int pcode___tab__SETPROPERTY_FontSize = pcode___tab__GETPROPERTY_FontName + 1;
static const int pcode___tab__GETPROPERTY_FontSize = pcode___tab__SETPROPERTY_FontSize + 1;
static const int pcode___tab__SETPROPERTY_FontItalic = pcode___tab__GETPROPERTY_FontSize + 1;
static const int pcode___tab__GETPROPERTY_FontItalic = pcode___tab__SETPROPERTY_FontItalic + 1;
static const int pcode___tab__SETPROPERTY_FontBold = pcode___tab__GETPROPERTY_FontItalic + 1;
static const int pcode___tab__GETPROPERTY_FontBold = pcode___tab__SETPROPERTY_FontBold + 1;
static const int pcode___tab__SETPROPERTY_FontUnderline = pcode___tab__GETPROPERTY_FontBold + 1;
static const int pcode___tab__GETPROPERTY_FontUnderline = pcode___tab__SETPROPERTY_FontUnderline + 1;
static const int pcode___tab__SETPROPERTY_FontColor = pcode___tab__GETPROPERTY_FontUnderline + 1;
static const int pcode___tab__GETPROPERTY_FontColor = pcode___tab__SETPROPERTY_FontColor + 1;
static const int pcode___tab__SETPROPERTY_Enabled = pcode___tab__GETPROPERTY_FontColor + 1;
static const int pcode___tab__GETPROPERTY_Enabled = pcode___tab__SETPROPERTY_Enabled + 1;
static const int pcode___tab__SETPROPERTY_Visible = pcode___tab__GETPROPERTY_Enabled + 1;
static const int pcode___tab__GETPROPERTY_Visible = pcode___tab__SETPROPERTY_Visible + 1;
static const int pcode___tab__SETPROPERTY_StatusTip = pcode___tab__GETPROPERTY_Visible + 1;
static const int pcode___tab__GETPROPERTY_StatusTip = pcode___tab__SETPROPERTY_StatusTip + 1;
static const int pcode___tab__SETPROPERTY_ToolTip = pcode___tab__GETPROPERTY_StatusTip + 1;
static const int pcode___tab__GETPROPERTY_ToolTip = pcode___tab__SETPROPERTY_ToolTip + 1;
static const int pcode___tab__SETPROPERTY_StyleSheet = pcode___tab__GETPROPERTY_ToolTip + 1;
static const int pcode___tab__GETPROPERTY_StyleSheet = pcode___tab__SETPROPERTY_StyleSheet + 1;
static const int pcode___tab__SETPROPERTY_WhatsThis = pcode___tab__GETPROPERTY_StyleSheet + 1;
static const int pcode___tab__GETPROPERTY_WhatsThis = pcode___tab__SETPROPERTY_WhatsThis + 1;
static const int pcode___tab__SETPROPERTY_TimerInterval = pcode___tab__GETPROPERTY_WhatsThis + 1;
static const int pcode___tab__GETPROPERTY_TimerInterval = pcode___tab__SETPROPERTY_TimerInterval + 1;
static const int pcode___tab__SETPROPERTY_Opacity = pcode___tab__GETPROPERTY_TimerInterval + 1;
static const int pcode___tab__GETPROPERTY_Opacity = pcode___tab__SETPROPERTY_Opacity + 1;
static const int pcode___tab__SETPROPERTY_BoxIndex = pcode___tab__GETPROPERTY_Opacity + 1;
static const int pcode___tab__GETPROPERTY_BoxIndex = pcode___tab__SETPROPERTY_BoxIndex + 1;
static const int pcode___tab__SETPROPERTY_SplitIndex = pcode___tab__GETPROPERTY_BoxIndex + 1;
static const int pcode___tab__GETPROPERTY_SplitIndex = pcode___tab__SETPROPERTY_SplitIndex + 1;
static const int pcode___tab__SETPROPERTY_TabIndex = pcode___tab__GETPROPERTY_SplitIndex + 1;
static const int pcode___tab__GETPROPERTY_TabIndex = pcode___tab__SETPROPERTY_TabIndex + 1;
static const int pcode___tab__SETPROPERTY_BoxX = pcode___tab__GETPROPERTY_TabIndex + 1;
static const int pcode___tab__GETPROPERTY_BoxX = pcode___tab__SETPROPERTY_BoxX + 1;
static const int pcode___tab__SETPROPERTY_BoxY = pcode___tab__GETPROPERTY_BoxX + 1;
static const int pcode___tab__GETPROPERTY_BoxY = pcode___tab__SETPROPERTY_BoxY + 1;
static const int pcode___tab__SETPROPERTY_ParentIndex = pcode___tab__GETPROPERTY_BoxY + 1;
static const int pcode___tab__GETPROPERTY_ParentIndex = pcode___tab__SETPROPERTY_ParentIndex + 1;
static const int pcode___tab__SETPROPERTY_ControlType1 = pcode___tab__GETPROPERTY_ParentIndex + 1;
static const int pcode___tab__GETPROPERTY_ControlType1 = pcode___tab__SETPROPERTY_ControlType1 + 1;
static const int pcode___tab__SETPROPERTY_SQLName = pcode___tab__GETPROPERTY_ControlType1 + 1;
static const int pcode___tab__GETPROPERTY_SQLName = pcode___tab__SETPROPERTY_SQLName + 1;
static const int pcode___tab__SETPROPERTY_SQLType = pcode___tab__GETPROPERTY_SQLName + 1;
static const int pcode___tab__GETPROPERTY_SQLType = pcode___tab__SETPROPERTY_SQLType + 1;
static const int pcode___tab__SETPROPERTY_SQLCaption = pcode___tab__GETPROPERTY_SQLType + 1;
static const int pcode___tab__GETPROPERTY_SQLCaption = pcode___tab__SETPROPERTY_SQLCaption + 1;
static const int pcode___tab__SETPROPERTY_SQLWidth = pcode___tab__GETPROPERTY_SQLCaption + 1;
static const int pcode___tab__GETPROPERTY_SQLWidth = pcode___tab__SETPROPERTY_SQLWidth + 1;
static const int pcode___tab__EVENT_OnOpen = pcode___tab__GETPROPERTY_SQLWidth + 1;
static const int pcode___tab__EVENT_OnClose = pcode___tab__EVENT_OnOpen + 1;
static const int pcode___tab__EVENT_OnContextMenu = pcode___tab__EVENT_OnClose + 1;
static const int pcode___tab__EVENT_OnDragEnter = pcode___tab__EVENT_OnContextMenu + 1;
static const int pcode___tab__EVENT_OnDragExit = pcode___tab__EVENT_OnDragEnter + 1;
static const int pcode___tab__EVENT_OnDragMove = pcode___tab__EVENT_OnDragExit + 1;
static const int pcode___tab__EVENT_OnDrop = pcode___tab__EVENT_OnDragMove + 1;
static const int pcode___tab__EVENT_OnEnter = pcode___tab__EVENT_OnDrop + 1;
static const int pcode___tab__EVENT_OnGotFocus = pcode___tab__EVENT_OnEnter + 1;
static const int pcode___tab__EVENT_OnLostFocus = pcode___tab__EVENT_OnGotFocus + 1;
static const int pcode___tab__EVENT_OnHide = pcode___tab__EVENT_OnLostFocus + 1;
static const int pcode___tab__EVENT_OnKeyDown = pcode___tab__EVENT_OnHide + 1;
static const int pcode___tab__EVENT_OnKeyUp = pcode___tab__EVENT_OnKeyDown + 1;
static const int pcode___tab__EVENT_OnKeyPress = pcode___tab__EVENT_OnKeyUp + 1;
static const int pcode___tab__EVENT_OnExit = pcode___tab__EVENT_OnKeyPress + 1;
static const int pcode___tab__EVENT_OnDblClick = pcode___tab__EVENT_OnExit + 1;
static const int pcode___tab__EVENT_OnClick = pcode___tab__EVENT_OnDblClick + 1;
static const int pcode___tab__EVENT_OnMouseMove = pcode___tab__EVENT_OnClick + 1;
static const int pcode___tab__EVENT_OnMouseDown = pcode___tab__EVENT_OnMouseMove + 1;
static const int pcode___tab__EVENT_OnMouseUp = pcode___tab__EVENT_OnMouseDown + 1;
static const int pcode___tab__EVENT_OnMove = pcode___tab__EVENT_OnMouseUp + 1;
static const int pcode___tab__EVENT_OnPaint = pcode___tab__EVENT_OnMove + 1;
static const int pcode___tab__EVENT_OnResize = pcode___tab__EVENT_OnPaint + 1;
static const int pcode___tab__EVENT_OnShow = pcode___tab__EVENT_OnResize + 1;
static const int pcode___tab__EVENT_OnMouseWheel = pcode___tab__EVENT_OnShow + 1;
static const int pcode___tab__EVENT_OnTimer = pcode___tab__EVENT_OnMouseWheel + 1;
static const int pcode___tab__EVENT_OnPrint = pcode___tab__EVENT_OnTimer + 1;

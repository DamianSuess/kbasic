static const int pcode___control___control = pcode___control * SPACE;


static const int pcode___control__SETPROPERTY_MouseTracking = pcode___control___control + 1;
static const int pcode___control__GETPROPERTY_MouseTracking = pcode___control__SETPROPERTY_MouseTracking + 1; 


static const int pcode___control__EVENT_OnSingleShot = pcode___control__GETPROPERTY_MouseTracking + 1;
static const int pcode___control__EVENT_OnEnabled = pcode___control__EVENT_OnSingleShot + 1;
static const int pcode___control__EVENT_OnDisabled = pcode___control__EVENT_OnEnabled + 1;

static const int pcode___control__SETPROPERTY_CursorAnimation = pcode___control__EVENT_OnDisabled + 1;
static const int pcode___control__GETPROPERTY_CursorAnimation = pcode___control__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___control__METHOD_DataIds = pcode___control__GETPROPERTY_CursorAnimation + 1;

static const int pcode___control__METHOD_DataRemove = pcode___control__METHOD_DataIds + 1;
static const int pcode___control__METHOD_DataRemoveAll = pcode___control__METHOD_DataRemove + 1;
static const int pcode___control__METHOD_DataSetBoolean = pcode___control__METHOD_DataRemoveAll + 1;
static const int pcode___control__METHOD_DataSetInteger = pcode___control__METHOD_DataSetBoolean + 1;
static const int pcode___control__METHOD_DataSetString = pcode___control__METHOD_DataSetInteger + 1;
static const int pcode___control__METHOD_DataSetDouble = pcode___control__METHOD_DataSetString + 1;
static const int pcode___control__METHOD_DataSetLong = pcode___control__METHOD_DataSetDouble + 1;
static const int pcode___control__METHOD_DataSetDecimal = pcode___control__METHOD_DataSetLong + 1;
static const int pcode___control__METHOD_DataSetDateTime = pcode___control__METHOD_DataSetDecimal + 1;


static const int pcode___control__METHOD_DataBoolean = pcode___control__METHOD_DataSetDateTime + 1;
static const int pcode___control__METHOD_DataInteger = pcode___control__METHOD_DataBoolean + 1;
static const int pcode___control__METHOD_DataString = pcode___control__METHOD_DataInteger + 1;
static const int pcode___control__METHOD_DataDouble = pcode___control__METHOD_DataString + 1;
static const int pcode___control__METHOD_DataLong = pcode___control__METHOD_DataDouble + 1;
static const int pcode___control__METHOD_DataDecimal = pcode___control__METHOD_DataLong + 1;
static const int pcode___control__METHOD_DataDateTime = pcode___control__METHOD_DataDecimal + 1;

static const int pcode___control__METHOD_ClearFocus = pcode___control__METHOD_DataDateTime + 1;
static const int pcode___control__METHOD_ToggleVisible = pcode___control__METHOD_ClearFocus + 1;

static const int pcode___control__METHOD_SingleShot = pcode___control__METHOD_ToggleVisible + 1;
static const int pcode___control__METHOD_StartTimer = pcode___control__METHOD_SingleShot + 1;
static const int pcode___control__METHOD_StopTimer = pcode___control__METHOD_StartTimer + 1;

static const int pcode___control__METHOD_GlobalX = pcode___control__METHOD_StopTimer + 1;
static const int pcode___control__METHOD_GlobalY = pcode___control__METHOD_GlobalX + 1;
static const int pcode___control__METHOD_LocalX = pcode___control__METHOD_GlobalY + 1;
static const int pcode___control__METHOD_LocalY = pcode___control__METHOD_LocalX + 1;

static const int pcode___control__METHOD_UnderMouse = pcode___control__METHOD_LocalY + 1;

static const int pcode___control__SETPROPERTY_Mask = pcode___control__METHOD_UnderMouse + 1;
static const int pcode___control__GETPROPERTY_Mask = pcode___control__SETPROPERTY_Mask + 1;

static const int pcode___control__SETPROPERTY_SoundOnEvent = pcode___control__GETPROPERTY_Mask + 1;
static const int pcode___control__GETPROPERTY_SoundOnEvent = pcode___control__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___control__SETPROPERTY_Left = pcode___control__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___control__GETPROPERTY_Left = pcode___control__SETPROPERTY_Left + 1;
static const int pcode___control__SETPROPERTY_Top = pcode___control__GETPROPERTY_Left + 1;
static const int pcode___control__GETPROPERTY_Top = pcode___control__SETPROPERTY_Top + 1;

static const int pcode___control__SETPROPERTY_LocalX = pcode___control__GETPROPERTY_Top + 1;
static const int pcode___control__GETPROPERTY_LocalX = pcode___control__SETPROPERTY_LocalX + 1;
static const int pcode___control__SETPROPERTY_LocalY = pcode___control__GETPROPERTY_LocalX + 1;
static const int pcode___control__GETPROPERTY_LocalY = pcode___control__SETPROPERTY_LocalY + 1;

static const int pcode___control__SETPROPERTY_DrawOnPaint = pcode___control__GETPROPERTY_LocalY + 1;
static const int pcode___control__GETPROPERTY_DrawOnPaint = pcode___control__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___control__SETPROPERTY_Palette = pcode___control__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___control__GETPROPERTY_Palette = pcode___control__SETPROPERTY_Palette + 1;


static const int pcode___control__SETPROPERTY_BackgroundStyle = pcode___control__GETPROPERTY_Palette + 1;
static const int pcode___control__GETPROPERTY_BackgroundStyle = pcode___control__SETPROPERTY_BackgroundStyle + 1;



static const int pcode___control__SETPROPERTY_Layout = pcode___control__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___control__GETPROPERTY_Layout = pcode___control__SETPROPERTY_Layout + 1;
static const int pcode___control__SETPROPERTY_Value = pcode___control__GETPROPERTY_Layout + 1;
static const int pcode___control__GETPROPERTY_Value = pcode___control__SETPROPERTY_Value + 1;
static const int pcode___control__GETPROPERTY_OldValue = pcode___control__GETPROPERTY_Value + 1;
static const int pcode___control__SETPROPERTY_Maximum = pcode___control__GETPROPERTY_OldValue + 1;
static const int pcode___control__GETPROPERTY_Maximum = pcode___control__SETPROPERTY_Maximum + 1;
static const int pcode___control__SETPROPERTY_Minimum = pcode___control__GETPROPERTY_Maximum + 1;
static const int pcode___control__GETPROPERTY_Minimum = pcode___control__SETPROPERTY_Minimum + 1;
static const int pcode___control__SETPROPERTY_Format = pcode___control__GETPROPERTY_Minimum + 1;
static const int pcode___control__GETPROPERTY_Format = pcode___control__SETPROPERTY_Format + 1;
static const int pcode___control__SETPROPERTY_PopUp = pcode___control__GETPROPERTY_Format + 1;
static const int pcode___control__GETPROPERTY_PopUp = pcode___control__SETPROPERTY_PopUp + 1;
static const int pcode___control__METHOD_SetDateTime = pcode___control__GETPROPERTY_PopUp + 1;
static const int pcode___control__METHOD_AsDateTime = pcode___control__METHOD_SetDateTime + 1;
static const int pcode___control__EVENT_OnEvent = pcode___control__METHOD_AsDateTime + 1;
static const int pcode___control__METHOD_Move = pcode___control__EVENT_OnEvent + 1;
static const int pcode___control__METHOD_Resize = pcode___control__METHOD_Move + 1;
static const int pcode___control__METHOD_Show = pcode___control__METHOD_Resize + 1;
static const int pcode___control__METHOD_Hide = pcode___control__METHOD_Show + 1;
static const int pcode___control__METHOD_RepaintAlways = pcode___control__METHOD_Hide + 1;
static const int pcode___control__METHOD_Repaint = pcode___control__METHOD_RepaintAlways + 1;
static const int pcode___control__METHOD_Raise = pcode___control__METHOD_Repaint + 1;
static const int pcode___control__METHOD_Lower = pcode___control__METHOD_Raise + 1;
static const int pcode___control__METHOD_Close = pcode___control__METHOD_Lower + 1;
static const int pcode___control__METHOD_Open = pcode___control__METHOD_Close + 1;
static const int pcode___control__METHOD_OpenHidden = pcode___control__METHOD_Open + 1;
static const int pcode___control__METHOD_SetFocus = pcode___control__METHOD_OpenHidden + 1;
static const int pcode___control__SETPROPERTY_Name = pcode___control__METHOD_SetFocus + 1;
static const int pcode___control__GETPROPERTY_Name = pcode___control__SETPROPERTY_Name + 1;
static const int pcode___control__SETPROPERTY_Group = pcode___control__GETPROPERTY_Name + 1;
static const int pcode___control__GETPROPERTY_Group = pcode___control__SETPROPERTY_Group + 1;
static const int pcode___control__SETPROPERTY_Background = pcode___control__GETPROPERTY_Group + 1;
static const int pcode___control__GETPROPERTY_Background = pcode___control__SETPROPERTY_Background + 1;
static const int pcode___control__SETPROPERTY_X = pcode___control__GETPROPERTY_Background + 1;
static const int pcode___control__GETPROPERTY_X = pcode___control__SETPROPERTY_X + 1;
static const int pcode___control__SETPROPERTY_Y = pcode___control__GETPROPERTY_X + 1;
static const int pcode___control__GETPROPERTY_Y = pcode___control__SETPROPERTY_Y + 1;
static const int pcode___control__SETPROPERTY_Width = pcode___control__GETPROPERTY_Y + 1;
static const int pcode___control__GETPROPERTY_Width = pcode___control__SETPROPERTY_Width + 1;
static const int pcode___control__SETPROPERTY_Height = pcode___control__GETPROPERTY_Width + 1;
static const int pcode___control__GETPROPERTY_Height = pcode___control__SETPROPERTY_Height + 1;
static const int pcode___control__GETPROPERTY_GlobalX = pcode___control__GETPROPERTY_Height + 1;
static const int pcode___control__GETPROPERTY_GlobalY = pcode___control__GETPROPERTY_GlobalX + 1;
static const int pcode___control__GETPROPERTY_OldX = pcode___control__GETPROPERTY_GlobalY + 1;
static const int pcode___control__GETPROPERTY_OldY = pcode___control__GETPROPERTY_OldX + 1;
static const int pcode___control__GETPROPERTY_OldWidth = pcode___control__GETPROPERTY_OldY + 1;
static const int pcode___control__GETPROPERTY_OldHeight = pcode___control__GETPROPERTY_OldWidth + 1;
static const int pcode___control__SETPROPERTY_MinimumWidth = pcode___control__GETPROPERTY_OldHeight + 1;
static const int pcode___control__GETPROPERTY_MinimumWidth = pcode___control__SETPROPERTY_MinimumWidth + 1;
static const int pcode___control__SETPROPERTY_MinimumHeight = pcode___control__GETPROPERTY_MinimumWidth + 1;
static const int pcode___control__GETPROPERTY_MinimumHeight = pcode___control__SETPROPERTY_MinimumHeight + 1;
static const int pcode___control__SETPROPERTY_MaximumWidth = pcode___control__GETPROPERTY_MinimumHeight + 1;
static const int pcode___control__GETPROPERTY_MaximumWidth = pcode___control__SETPROPERTY_MaximumWidth + 1;
static const int pcode___control__SETPROPERTY_MaximumHeight = pcode___control__GETPROPERTY_MaximumWidth + 1;
static const int pcode___control__GETPROPERTY_MaximumHeight = pcode___control__SETPROPERTY_MaximumHeight + 1;
static const int pcode___control__SETPROPERTY_Tag = pcode___control__GETPROPERTY_MaximumHeight + 1;
static const int pcode___control__GETPROPERTY_Tag = pcode___control__SETPROPERTY_Tag + 1;
static const int pcode___control__SETPROPERTY_CSV = pcode___control__GETPROPERTY_Tag + 1;
static const int pcode___control__GETPROPERTY_CSV = pcode___control__SETPROPERTY_CSV + 1;
static const int pcode___control__SETPROPERTY_ParentForm = pcode___control__GETPROPERTY_CSV + 1;
static const int pcode___control__GETPROPERTY_ParentForm = pcode___control__SETPROPERTY_ParentForm + 1;
static const int pcode___control__SETPROPERTY_ParentControl = pcode___control__GETPROPERTY_ParentForm + 1;
static const int pcode___control__GETPROPERTY_ParentControl = pcode___control__SETPROPERTY_ParentControl + 1;
static const int pcode___control__SETPROPERTY_DragDrop = pcode___control__GETPROPERTY_ParentControl + 1;
static const int pcode___control__GETPROPERTY_ParentControl1 = pcode___control__SETPROPERTY_DragDrop + 1;
static const int pcode___control__SETPROPERTY_ControlType = pcode___control__GETPROPERTY_ParentControl1 + 1;
static const int pcode___control__GETPROPERTY_ControlType = pcode___control__SETPROPERTY_ControlType + 1;
static const int pcode___control__SETPROPERTY_Focus = pcode___control__GETPROPERTY_ControlType + 1;
static const int pcode___control__GETPROPERTY_Focus = pcode___control__SETPROPERTY_Focus + 1;
static const int pcode___control__SETPROPERTY_FocusPolicy = pcode___control__GETPROPERTY_Focus + 1;
static const int pcode___control__GETPROPERTY_FocusPolicy = pcode___control__SETPROPERTY_FocusPolicy + 1;
static const int pcode___control__SETPROPERTY_FocusProxy = pcode___control__GETPROPERTY_FocusPolicy + 1;
static const int pcode___control__GETPROPERTY_FocusProxy = pcode___control__SETPROPERTY_FocusProxy + 1;
static const int pcode___control__SETPROPERTY_FocusOrder = pcode___control__GETPROPERTY_FocusProxy + 1;
static const int pcode___control__GETPROPERTY_FocusOrder = pcode___control__SETPROPERTY_FocusOrder + 1;
static const int pcode___control__SETPROPERTY_Cursor = pcode___control__GETPROPERTY_FocusOrder + 1;
static const int pcode___control__GETPROPERTY_Cursor = pcode___control__SETPROPERTY_Cursor + 1;
static const int pcode___control__SETPROPERTY_FontName = pcode___control__GETPROPERTY_Cursor + 1;
static const int pcode___control__GETPROPERTY_FontName = pcode___control__SETPROPERTY_FontName + 1;
static const int pcode___control__SETPROPERTY_FontSize = pcode___control__GETPROPERTY_FontName + 1;
static const int pcode___control__GETPROPERTY_FontSize = pcode___control__SETPROPERTY_FontSize + 1;
static const int pcode___control__SETPROPERTY_FontItalic = pcode___control__GETPROPERTY_FontSize + 1;
static const int pcode___control__GETPROPERTY_FontItalic = pcode___control__SETPROPERTY_FontItalic + 1;
static const int pcode___control__SETPROPERTY_FontBold = pcode___control__GETPROPERTY_FontItalic + 1;
static const int pcode___control__GETPROPERTY_FontBold = pcode___control__SETPROPERTY_FontBold + 1;
static const int pcode___control__SETPROPERTY_FontUnderline = pcode___control__GETPROPERTY_FontBold + 1;
static const int pcode___control__GETPROPERTY_FontUnderline = pcode___control__SETPROPERTY_FontUnderline + 1;
static const int pcode___control__SETPROPERTY_FontColor = pcode___control__GETPROPERTY_FontUnderline + 1;
static const int pcode___control__GETPROPERTY_FontColor = pcode___control__SETPROPERTY_FontColor + 1;
static const int pcode___control__SETPROPERTY_Enabled = pcode___control__GETPROPERTY_FontColor + 1;
static const int pcode___control__GETPROPERTY_Enabled = pcode___control__SETPROPERTY_Enabled + 1;
static const int pcode___control__SETPROPERTY_Visible = pcode___control__GETPROPERTY_Enabled + 1;
static const int pcode___control__GETPROPERTY_Visible = pcode___control__SETPROPERTY_Visible + 1;
static const int pcode___control__SETPROPERTY_StatusTip = pcode___control__GETPROPERTY_Visible + 1;
static const int pcode___control__GETPROPERTY_StatusTip = pcode___control__SETPROPERTY_StatusTip + 1;
static const int pcode___control__SETPROPERTY_ToolTip = pcode___control__GETPROPERTY_StatusTip + 1;
static const int pcode___control__GETPROPERTY_ToolTip = pcode___control__SETPROPERTY_ToolTip + 1;
static const int pcode___control__SETPROPERTY_StyleSheet = pcode___control__GETPROPERTY_ToolTip + 1;
static const int pcode___control__GETPROPERTY_StyleSheet = pcode___control__SETPROPERTY_StyleSheet + 1;
static const int pcode___control__SETPROPERTY_WhatsThis = pcode___control__GETPROPERTY_StyleSheet + 1;
static const int pcode___control__GETPROPERTY_WhatsThis = pcode___control__SETPROPERTY_WhatsThis + 1;
static const int pcode___control__SETPROPERTY_TimerInterval = pcode___control__GETPROPERTY_WhatsThis + 1;
static const int pcode___control__GETPROPERTY_TimerInterval = pcode___control__SETPROPERTY_TimerInterval + 1;
static const int pcode___control__SETPROPERTY_Opacity = pcode___control__GETPROPERTY_TimerInterval + 1;
static const int pcode___control__GETPROPERTY_Opacity = pcode___control__SETPROPERTY_Opacity + 1;
static const int pcode___control__SETPROPERTY_BoxIndex = pcode___control__GETPROPERTY_Opacity + 1;
static const int pcode___control__GETPROPERTY_BoxIndex = pcode___control__SETPROPERTY_BoxIndex + 1;
static const int pcode___control__SETPROPERTY_SplitIndex = pcode___control__GETPROPERTY_BoxIndex + 1;
static const int pcode___control__GETPROPERTY_SplitIndex = pcode___control__SETPROPERTY_SplitIndex + 1;
static const int pcode___control__SETPROPERTY_TabIndex = pcode___control__GETPROPERTY_SplitIndex + 1;
static const int pcode___control__GETPROPERTY_TabIndex = pcode___control__SETPROPERTY_TabIndex + 1;
static const int pcode___control__SETPROPERTY_BoxX = pcode___control__GETPROPERTY_TabIndex + 1;
static const int pcode___control__GETPROPERTY_BoxX = pcode___control__SETPROPERTY_BoxX + 1;
static const int pcode___control__SETPROPERTY_BoxY = pcode___control__GETPROPERTY_BoxX + 1;
static const int pcode___control__GETPROPERTY_BoxY = pcode___control__SETPROPERTY_BoxY + 1;
static const int pcode___control__SETPROPERTY_ParentIndex = pcode___control__GETPROPERTY_BoxY + 1;
static const int pcode___control__GETPROPERTY_ParentIndex = pcode___control__SETPROPERTY_ParentIndex + 1;
static const int pcode___control__SETPROPERTY_ControlType1 = pcode___control__GETPROPERTY_ParentIndex + 1;
static const int pcode___control__GETPROPERTY_ControlType1 = pcode___control__SETPROPERTY_ControlType1 + 1;

static const int pcode___control__SETPROPERTY_SQL = pcode___control__GETPROPERTY_ControlType1 + 1;
static const int pcode___control__GETPROPERTY_SQL = pcode___control__SETPROPERTY_SQL + 1;

static const int pcode___control__SETPROPERTY_SQLName = pcode___control__GETPROPERTY_SQL + 1;
static const int pcode___control__GETPROPERTY_SQLName = pcode___control__SETPROPERTY_SQLName + 1;
static const int pcode___control__SETPROPERTY_SQLRelation = pcode___control__GETPROPERTY_SQLName + 1;
static const int pcode___control__GETPROPERTY_SQLRelation = pcode___control__SETPROPERTY_SQLRelation + 1;
static const int pcode___control__SETPROPERTY_TableViewCaption = pcode___control__GETPROPERTY_SQLRelation + 1;
static const int pcode___control__GETPROPERTY_TableViewCaption = pcode___control__SETPROPERTY_TableViewCaption + 1;
static const int pcode___control__SETPROPERTY_TableViewSort = pcode___control__GETPROPERTY_TableViewCaption + 1;
static const int pcode___control__GETPROPERTY_TableViewSort = pcode___control__SETPROPERTY_TableViewSort + 1;
static const int pcode___control__SETPROPERTY_TableViewFilter = pcode___control__GETPROPERTY_TableViewSort + 1;
static const int pcode___control__GETPROPERTY_TableViewFilter = pcode___control__SETPROPERTY_TableViewFilter + 1;
static const int pcode___control__SETPROPERTY_TableViewWidth = pcode___control__GETPROPERTY_TableViewFilter + 1;
static const int pcode___control__GETPROPERTY_TableViewWidth = pcode___control__SETPROPERTY_TableViewWidth + 1;
static const int pcode___control__SETPROPERTY_TableViewVisible = pcode___control__GETPROPERTY_TableViewWidth + 1;
static const int pcode___control__GETPROPERTY_TableViewVisible = pcode___control__SETPROPERTY_TableViewVisible + 1;
static const int pcode___control__SETPROPERTY_TableViewOrder = pcode___control__GETPROPERTY_TableViewVisible + 1;
static const int pcode___control__GETPROPERTY_TableViewOrder = pcode___control__SETPROPERTY_TableViewOrder + 1;

static const int pcode___control__EVENT_OnOpen = pcode___control__GETPROPERTY_TableViewOrder + 1;
static const int pcode___control__EVENT_OnClose = pcode___control__EVENT_OnOpen + 1;
static const int pcode___control__EVENT_OnContextMenu = pcode___control__EVENT_OnClose + 1;
static const int pcode___control__EVENT_OnDragEnter = pcode___control__EVENT_OnContextMenu + 1;
static const int pcode___control__EVENT_OnDragExit = pcode___control__EVENT_OnDragEnter + 1;
static const int pcode___control__EVENT_OnDragMove = pcode___control__EVENT_OnDragExit + 1;
static const int pcode___control__EVENT_OnDrop = pcode___control__EVENT_OnDragMove + 1;
static const int pcode___control__EVENT_OnEnter = pcode___control__EVENT_OnDrop + 1;
static const int pcode___control__EVENT_OnGotFocus = pcode___control__EVENT_OnEnter + 1;
static const int pcode___control__EVENT_OnLostFocus = pcode___control__EVENT_OnGotFocus + 1;
static const int pcode___control__EVENT_OnHide = pcode___control__EVENT_OnLostFocus + 1;
static const int pcode___control__EVENT_OnKeyDown = pcode___control__EVENT_OnHide + 1;
static const int pcode___control__EVENT_OnKeyUp = pcode___control__EVENT_OnKeyDown + 1;
static const int pcode___control__EVENT_OnKeyPress = pcode___control__EVENT_OnKeyUp + 1;
static const int pcode___control__EVENT_OnExit = pcode___control__EVENT_OnKeyPress + 1;
static const int pcode___control__EVENT_OnDblClick = pcode___control__EVENT_OnExit + 1;
static const int pcode___control__EVENT_OnClick = pcode___control__EVENT_OnDblClick + 1;
static const int pcode___control__EVENT_OnMouseMove = pcode___control__EVENT_OnClick + 1;
static const int pcode___control__EVENT_OnMouseDown = pcode___control__EVENT_OnMouseMove + 1;
static const int pcode___control__EVENT_OnMouseUp = pcode___control__EVENT_OnMouseDown + 1;
static const int pcode___control__EVENT_OnMove = pcode___control__EVENT_OnMouseUp + 1;
static const int pcode___control__EVENT_OnPaint = pcode___control__EVENT_OnMove + 1;
static const int pcode___control__EVENT_OnResize = pcode___control__EVENT_OnPaint + 1;
static const int pcode___control__EVENT_OnShow = pcode___control__EVENT_OnResize + 1;
static const int pcode___control__EVENT_OnMouseWheel = pcode___control__EVENT_OnShow + 1;
static const int pcode___control__EVENT_OnTimer = pcode___control__EVENT_OnMouseWheel + 1;
static const int pcode___control__EVENT_OnPrint = pcode___control__EVENT_OnTimer + 1;
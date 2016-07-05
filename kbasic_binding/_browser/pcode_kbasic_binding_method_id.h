static const int pcode___browser___browser = pcode___browser * SPACE;
static const int pcode___browser___browser1 = pcode___browser___browser + 1;

static const int pcode___browser__SETPROPERTY_MouseTracking = pcode___browser___browser1 + 1;
static const int pcode___browser__GETPROPERTY_MouseTracking = pcode___browser__SETPROPERTY_MouseTracking + 1; 


static const int pcode___browser__EVENT_OnSingleShot = pcode___browser__GETPROPERTY_MouseTracking + 1;
static const int pcode___browser__EVENT_OnEnabled = pcode___browser__EVENT_OnSingleShot + 1;
static const int pcode___browser__EVENT_OnDisabled = pcode___browser__EVENT_OnEnabled + 1;

static const int pcode___browser__SETPROPERTY_CursorAnimation = pcode___browser__EVENT_OnDisabled + 1;
static const int pcode___browser__GETPROPERTY_CursorAnimation = pcode___browser__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___browser__METHOD_DataIds = pcode___browser__GETPROPERTY_CursorAnimation + 1;

static const int pcode___browser__METHOD_DataRemove = pcode___browser__METHOD_DataIds + 1;
static const int pcode___browser__METHOD_DataRemoveAll = pcode___browser__METHOD_DataRemove + 1;
static const int pcode___browser__METHOD_DataSetBoolean = pcode___browser__METHOD_DataRemoveAll + 1;
static const int pcode___browser__METHOD_DataSetInteger = pcode___browser__METHOD_DataSetBoolean + 1;
static const int pcode___browser__METHOD_DataSetString = pcode___browser__METHOD_DataSetInteger + 1;
static const int pcode___browser__METHOD_DataSetDouble = pcode___browser__METHOD_DataSetString + 1;
static const int pcode___browser__METHOD_DataSetLong = pcode___browser__METHOD_DataSetDouble + 1;
static const int pcode___browser__METHOD_DataSetDecimal = pcode___browser__METHOD_DataSetLong + 1;
static const int pcode___browser__METHOD_DataSetDateTime = pcode___browser__METHOD_DataSetDecimal + 1;


static const int pcode___browser__METHOD_DataBoolean = pcode___browser__METHOD_DataSetDateTime + 1;
static const int pcode___browser__METHOD_DataInteger = pcode___browser__METHOD_DataBoolean + 1;
static const int pcode___browser__METHOD_DataString = pcode___browser__METHOD_DataInteger + 1;
static const int pcode___browser__METHOD_DataDouble = pcode___browser__METHOD_DataString + 1;
static const int pcode___browser__METHOD_DataLong = pcode___browser__METHOD_DataDouble + 1;
static const int pcode___browser__METHOD_DataDecimal = pcode___browser__METHOD_DataLong + 1;
static const int pcode___browser__METHOD_DataDateTime = pcode___browser__METHOD_DataDecimal + 1;

static const int pcode___browser__METHOD_ClearFocus = pcode___browser__METHOD_DataDateTime + 1;
static const int pcode___browser__METHOD_ToggleVisible = pcode___browser__METHOD_ClearFocus + 1;

static const int pcode___browser__METHOD_SingleShot = pcode___browser__METHOD_ToggleVisible + 1;
static const int pcode___browser__METHOD_StartTimer = pcode___browser__METHOD_SingleShot + 1;
static const int pcode___browser__METHOD_StopTimer = pcode___browser__METHOD_StartTimer + 1;

//static const int pcode___browser__METHOD_EventSender = pcode___browser__METHOD_StopTimer + 1;

static const int pcode___browser__METHOD_GlobalX = pcode___browser__METHOD_StopTimer + 1;
static const int pcode___browser__METHOD_GlobalY = pcode___browser__METHOD_GlobalX + 1;
static const int pcode___browser__METHOD_LocalX = pcode___browser__METHOD_GlobalY + 1;
static const int pcode___browser__METHOD_LocalY = pcode___browser__METHOD_LocalX + 1;

static const int pcode___browser__METHOD_UnderMouse = pcode___browser__METHOD_LocalY + 1;

static const int pcode___browser__SETPROPERTY_Mask = pcode___browser__METHOD_UnderMouse + 1;
static const int pcode___browser__GETPROPERTY_Mask = pcode___browser__SETPROPERTY_Mask + 1;

static const int pcode___browser__SETPROPERTY_SoundOnEvent = pcode___browser__GETPROPERTY_Mask + 1;
static const int pcode___browser__GETPROPERTY_SoundOnEvent = pcode___browser__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___browser__SETPROPERTY_Left = pcode___browser__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___browser__GETPROPERTY_Left = pcode___browser__SETPROPERTY_Left + 1;
static const int pcode___browser__SETPROPERTY_Top = pcode___browser__GETPROPERTY_Left + 1;
static const int pcode___browser__GETPROPERTY_Top = pcode___browser__SETPROPERTY_Top + 1;

static const int pcode___browser__SETPROPERTY_LocalX = pcode___browser__GETPROPERTY_Top + 1;
static const int pcode___browser__GETPROPERTY_LocalX = pcode___browser__SETPROPERTY_LocalX + 1;
static const int pcode___browser__SETPROPERTY_LocalY = pcode___browser__GETPROPERTY_LocalX + 1;
static const int pcode___browser__GETPROPERTY_LocalY = pcode___browser__SETPROPERTY_LocalY + 1;

static const int pcode___browser__SETPROPERTY_DrawOnPaint = pcode___browser__GETPROPERTY_LocalY + 1;
static const int pcode___browser__GETPROPERTY_DrawOnPaint = pcode___browser__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___browser__SETPROPERTY_Palette = pcode___browser__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___browser__GETPROPERTY_Palette = pcode___browser__SETPROPERTY_Palette + 1;


static const int pcode___browser__SETPROPERTY_BackgroundStyle = pcode___browser__GETPROPERTY_Palette + 1;
static const int pcode___browser__GETPROPERTY_BackgroundStyle = pcode___browser__SETPROPERTY_BackgroundStyle + 1;



static const int pcode___browser__SETPROPERTY_Layout = pcode___browser__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___browser__GETPROPERTY_Layout = pcode___browser__SETPROPERTY_Layout + 1;

static const int pcode___browser__SETPROPERTY_Value = pcode___browser__GETPROPERTY_Layout + 1;
static const int pcode___browser__GETPROPERTY_Value = pcode___browser__SETPROPERTY_Value + 1;
static const int pcode___browser__GETPROPERTY_OldValue = pcode___browser__GETPROPERTY_Value + 1;
static const int pcode___browser__SETPROPERTY_Text = pcode___browser__GETPROPERTY_OldValue + 1;
static const int pcode___browser__GETPROPERTY_Text = pcode___browser__SETPROPERTY_Text + 1;

static const int pcode___browser__SETPROPERTY_HomeURL = pcode___browser__GETPROPERTY_Text + 1;
static const int pcode___browser__GETPROPERTY_HomeURL = pcode___browser__SETPROPERTY_HomeURL + 1;
static const int pcode___browser__SETPROPERTY_OpenLinks = pcode___browser__GETPROPERTY_HomeURL + 1;
static const int pcode___browser__GETPROPERTY_OpenLinks = pcode___browser__SETPROPERTY_OpenLinks + 1;
static const int pcode___browser__METHOD_BackwardAvailable = pcode___browser__GETPROPERTY_OpenLinks + 1;
static const int pcode___browser__METHOD_ForwardAvailable = pcode___browser__METHOD_BackwardAvailable + 1;
static const int pcode___browser__METHOD_Backward = pcode___browser__METHOD_ForwardAvailable + 1;
static const int pcode___browser__METHOD_Forward = pcode___browser__METHOD_Backward + 1;
static const int pcode___browser__METHOD_Reload = pcode___browser__METHOD_Forward + 1;
static const int pcode___browser__EVENT_OnEvent = pcode___browser__METHOD_Reload + 1;
static const int pcode___browser__METHOD_Move = pcode___browser__EVENT_OnEvent + 1;
static const int pcode___browser__METHOD_Resize = pcode___browser__METHOD_Move + 1;
static const int pcode___browser__METHOD_Show = pcode___browser__METHOD_Resize + 1;
static const int pcode___browser__METHOD_Hide = pcode___browser__METHOD_Show + 1;
static const int pcode___browser__METHOD_RepaintAlways = pcode___browser__METHOD_Hide + 1;
static const int pcode___browser__METHOD_Repaint = pcode___browser__METHOD_RepaintAlways + 1;
static const int pcode___browser__METHOD_Raise = pcode___browser__METHOD_Repaint + 1;
static const int pcode___browser__METHOD_Lower = pcode___browser__METHOD_Raise + 1;
static const int pcode___browser__METHOD_Close = pcode___browser__METHOD_Lower + 1;
static const int pcode___browser__METHOD_Open = pcode___browser__METHOD_Close + 1;
static const int pcode___browser__METHOD_SetFocus = pcode___browser__METHOD_Open + 1;
static const int pcode___browser__SETPROPERTY_Name = pcode___browser__METHOD_SetFocus + 1;
static const int pcode___browser__GETPROPERTY_Name = pcode___browser__SETPROPERTY_Name + 1;
static const int pcode___browser__SETPROPERTY_Group = pcode___browser__GETPROPERTY_Name + 1;
static const int pcode___browser__GETPROPERTY_Group = pcode___browser__SETPROPERTY_Group + 1;
static const int pcode___browser__SETPROPERTY_Background = pcode___browser__GETPROPERTY_Group + 1;
static const int pcode___browser__GETPROPERTY_Background = pcode___browser__SETPROPERTY_Background + 1;
static const int pcode___browser__SETPROPERTY_X = pcode___browser__GETPROPERTY_Background + 1;
static const int pcode___browser__GETPROPERTY_X = pcode___browser__SETPROPERTY_X + 1;
static const int pcode___browser__SETPROPERTY_Y = pcode___browser__GETPROPERTY_X + 1;
static const int pcode___browser__GETPROPERTY_Y = pcode___browser__SETPROPERTY_Y + 1;
static const int pcode___browser__SETPROPERTY_Width = pcode___browser__GETPROPERTY_Y + 1;
static const int pcode___browser__GETPROPERTY_Width = pcode___browser__SETPROPERTY_Width + 1;
static const int pcode___browser__SETPROPERTY_Height = pcode___browser__GETPROPERTY_Width + 1;
static const int pcode___browser__GETPROPERTY_Height = pcode___browser__SETPROPERTY_Height + 1;
static const int pcode___browser__GETPROPERTY_GlobalX = pcode___browser__GETPROPERTY_Height + 1;
static const int pcode___browser__GETPROPERTY_GlobalY = pcode___browser__GETPROPERTY_GlobalX + 1;
static const int pcode___browser__GETPROPERTY_OldX = pcode___browser__GETPROPERTY_GlobalY + 1;
static const int pcode___browser__GETPROPERTY_OldY = pcode___browser__GETPROPERTY_OldX + 1;
static const int pcode___browser__GETPROPERTY_OldWidth = pcode___browser__GETPROPERTY_OldY + 1;
static const int pcode___browser__GETPROPERTY_OldHeight = pcode___browser__GETPROPERTY_OldWidth + 1;
static const int pcode___browser__SETPROPERTY_MinimumWidth = pcode___browser__GETPROPERTY_OldHeight + 1;
static const int pcode___browser__GETPROPERTY_MinimumWidth = pcode___browser__SETPROPERTY_MinimumWidth + 1;
static const int pcode___browser__SETPROPERTY_MinimumHeight = pcode___browser__GETPROPERTY_MinimumWidth + 1;
static const int pcode___browser__GETPROPERTY_MinimumHeight = pcode___browser__SETPROPERTY_MinimumHeight + 1;
static const int pcode___browser__SETPROPERTY_MaximumWidth = pcode___browser__GETPROPERTY_MinimumHeight + 1;
static const int pcode___browser__GETPROPERTY_MaximumWidth = pcode___browser__SETPROPERTY_MaximumWidth + 1;
static const int pcode___browser__SETPROPERTY_MaximumHeight = pcode___browser__GETPROPERTY_MaximumWidth + 1;
static const int pcode___browser__GETPROPERTY_MaximumHeight = pcode___browser__SETPROPERTY_MaximumHeight + 1;
static const int pcode___browser__SETPROPERTY_Tag = pcode___browser__GETPROPERTY_MaximumHeight + 1;
static const int pcode___browser__GETPROPERTY_Tag = pcode___browser__SETPROPERTY_Tag + 1;
static const int pcode___browser__SETPROPERTY_CSV = pcode___browser__GETPROPERTY_Tag + 1;
static const int pcode___browser__GETPROPERTY_CSV = pcode___browser__SETPROPERTY_CSV + 1;
static const int pcode___browser__SETPROPERTY_ParentForm = pcode___browser__GETPROPERTY_CSV + 1;
static const int pcode___browser__GETPROPERTY_ParentForm = pcode___browser__SETPROPERTY_ParentForm + 1;
static const int pcode___browser__SETPROPERTY_ParentControl = pcode___browser__GETPROPERTY_ParentForm + 1;
static const int pcode___browser__GETPROPERTY_ParentControl = pcode___browser__SETPROPERTY_ParentControl + 1;
static const int pcode___browser__SETPROPERTY_DragDrop = pcode___browser__GETPROPERTY_ParentControl + 1;
static const int pcode___browser__GETPROPERTY_ParentControl1 = pcode___browser__SETPROPERTY_DragDrop + 1;
static const int pcode___browser__SETPROPERTY_ControlType = pcode___browser__GETPROPERTY_ParentControl1 + 1;
static const int pcode___browser__GETPROPERTY_ControlType = pcode___browser__SETPROPERTY_ControlType + 1;
static const int pcode___browser__SETPROPERTY_Focus = pcode___browser__GETPROPERTY_ControlType + 1;
static const int pcode___browser__GETPROPERTY_Focus = pcode___browser__SETPROPERTY_Focus + 1;
static const int pcode___browser__SETPROPERTY_FocusPolicy = pcode___browser__GETPROPERTY_Focus + 1;
static const int pcode___browser__GETPROPERTY_FocusPolicy = pcode___browser__SETPROPERTY_FocusPolicy + 1;
static const int pcode___browser__SETPROPERTY_FocusProxy = pcode___browser__GETPROPERTY_FocusPolicy + 1;
static const int pcode___browser__GETPROPERTY_FocusProxy = pcode___browser__SETPROPERTY_FocusProxy + 1;
static const int pcode___browser__SETPROPERTY_FocusOrder = pcode___browser__GETPROPERTY_FocusProxy + 1;
static const int pcode___browser__GETPROPERTY_FocusOrder = pcode___browser__SETPROPERTY_FocusOrder + 1;
static const int pcode___browser__SETPROPERTY_Cursor = pcode___browser__GETPROPERTY_FocusOrder + 1;
static const int pcode___browser__GETPROPERTY_Cursor = pcode___browser__SETPROPERTY_Cursor + 1;
static const int pcode___browser__SETPROPERTY_FontName = pcode___browser__GETPROPERTY_Cursor + 1;
static const int pcode___browser__GETPROPERTY_FontName = pcode___browser__SETPROPERTY_FontName + 1;
static const int pcode___browser__SETPROPERTY_FontSize = pcode___browser__GETPROPERTY_FontName + 1;
static const int pcode___browser__GETPROPERTY_FontSize = pcode___browser__SETPROPERTY_FontSize + 1;
static const int pcode___browser__SETPROPERTY_FontItalic = pcode___browser__GETPROPERTY_FontSize + 1;
static const int pcode___browser__GETPROPERTY_FontItalic = pcode___browser__SETPROPERTY_FontItalic + 1;
static const int pcode___browser__SETPROPERTY_FontBold = pcode___browser__GETPROPERTY_FontItalic + 1;
static const int pcode___browser__GETPROPERTY_FontBold = pcode___browser__SETPROPERTY_FontBold + 1;
static const int pcode___browser__SETPROPERTY_FontUnderline = pcode___browser__GETPROPERTY_FontBold + 1;
static const int pcode___browser__GETPROPERTY_FontUnderline = pcode___browser__SETPROPERTY_FontUnderline + 1;
static const int pcode___browser__SETPROPERTY_FontColor = pcode___browser__GETPROPERTY_FontUnderline + 1;
static const int pcode___browser__GETPROPERTY_FontColor = pcode___browser__SETPROPERTY_FontColor + 1;
static const int pcode___browser__SETPROPERTY_Enabled = pcode___browser__GETPROPERTY_FontColor + 1;
static const int pcode___browser__GETPROPERTY_Enabled = pcode___browser__SETPROPERTY_Enabled + 1;
static const int pcode___browser__SETPROPERTY_Visible = pcode___browser__GETPROPERTY_Enabled + 1;
static const int pcode___browser__GETPROPERTY_Visible = pcode___browser__SETPROPERTY_Visible + 1;
static const int pcode___browser__SETPROPERTY_StatusTip = pcode___browser__GETPROPERTY_Visible + 1;
static const int pcode___browser__GETPROPERTY_StatusTip = pcode___browser__SETPROPERTY_StatusTip + 1;
static const int pcode___browser__SETPROPERTY_ToolTip = pcode___browser__GETPROPERTY_StatusTip + 1;
static const int pcode___browser__GETPROPERTY_ToolTip = pcode___browser__SETPROPERTY_ToolTip + 1;
static const int pcode___browser__SETPROPERTY_StyleSheet = pcode___browser__GETPROPERTY_ToolTip + 1;
static const int pcode___browser__GETPROPERTY_StyleSheet = pcode___browser__SETPROPERTY_StyleSheet + 1;
static const int pcode___browser__SETPROPERTY_WhatsThis = pcode___browser__GETPROPERTY_StyleSheet + 1;
static const int pcode___browser__GETPROPERTY_WhatsThis = pcode___browser__SETPROPERTY_WhatsThis + 1;
static const int pcode___browser__SETPROPERTY_TimerInterval = pcode___browser__GETPROPERTY_WhatsThis + 1;
static const int pcode___browser__GETPROPERTY_TimerInterval = pcode___browser__SETPROPERTY_TimerInterval + 1;
static const int pcode___browser__SETPROPERTY_Opacity = pcode___browser__GETPROPERTY_TimerInterval + 1;
static const int pcode___browser__GETPROPERTY_Opacity = pcode___browser__SETPROPERTY_Opacity + 1;
static const int pcode___browser__SETPROPERTY_BoxIndex = pcode___browser__GETPROPERTY_Opacity + 1;
static const int pcode___browser__GETPROPERTY_BoxIndex = pcode___browser__SETPROPERTY_BoxIndex + 1;
static const int pcode___browser__SETPROPERTY_SplitIndex = pcode___browser__GETPROPERTY_BoxIndex + 1;
static const int pcode___browser__GETPROPERTY_SplitIndex = pcode___browser__SETPROPERTY_SplitIndex + 1;
static const int pcode___browser__SETPROPERTY_TabIndex = pcode___browser__GETPROPERTY_SplitIndex + 1;
static const int pcode___browser__GETPROPERTY_TabIndex = pcode___browser__SETPROPERTY_TabIndex + 1;
static const int pcode___browser__SETPROPERTY_BoxX = pcode___browser__GETPROPERTY_TabIndex + 1;
static const int pcode___browser__GETPROPERTY_BoxX = pcode___browser__SETPROPERTY_BoxX + 1;
static const int pcode___browser__SETPROPERTY_BoxY = pcode___browser__GETPROPERTY_BoxX + 1;
static const int pcode___browser__GETPROPERTY_BoxY = pcode___browser__SETPROPERTY_BoxY + 1;
static const int pcode___browser__SETPROPERTY_ParentIndex = pcode___browser__GETPROPERTY_BoxY + 1;
static const int pcode___browser__GETPROPERTY_ParentIndex = pcode___browser__SETPROPERTY_ParentIndex + 1;
static const int pcode___browser__SETPROPERTY_ControlType1 = pcode___browser__GETPROPERTY_ParentIndex + 1;
static const int pcode___browser__GETPROPERTY_ControlType1 = pcode___browser__SETPROPERTY_ControlType1 + 1;

static const int pcode___browser__SETPROPERTY_SQLName = pcode___browser__GETPROPERTY_ControlType1 + 1;
static const int pcode___browser__GETPROPERTY_SQLName = pcode___browser__SETPROPERTY_SQLName + 1;
static const int pcode___browser__SETPROPERTY_SQLRelation = pcode___browser__GETPROPERTY_SQLName + 1;
static const int pcode___browser__GETPROPERTY_SQLRelation = pcode___browser__SETPROPERTY_SQLRelation + 1;
static const int pcode___browser__SETPROPERTY_TableViewCaption = pcode___browser__GETPROPERTY_SQLRelation + 1;
static const int pcode___browser__GETPROPERTY_TableViewCaption = pcode___browser__SETPROPERTY_TableViewCaption + 1;
static const int pcode___browser__SETPROPERTY_TableViewSort = pcode___browser__GETPROPERTY_TableViewCaption + 1;
static const int pcode___browser__GETPROPERTY_TableViewSort = pcode___browser__SETPROPERTY_TableViewSort + 1;
static const int pcode___browser__SETPROPERTY_TableViewFilter = pcode___browser__GETPROPERTY_TableViewSort + 1;
static const int pcode___browser__GETPROPERTY_TableViewFilter = pcode___browser__SETPROPERTY_TableViewFilter + 1;
static const int pcode___browser__SETPROPERTY_TableViewWidth = pcode___browser__GETPROPERTY_TableViewFilter + 1;
static const int pcode___browser__GETPROPERTY_TableViewWidth = pcode___browser__SETPROPERTY_TableViewWidth + 1;
static const int pcode___browser__SETPROPERTY_TableViewVisible = pcode___browser__GETPROPERTY_TableViewWidth + 1;
static const int pcode___browser__GETPROPERTY_TableViewVisible = pcode___browser__SETPROPERTY_TableViewVisible + 1;
static const int pcode___browser__SETPROPERTY_TableViewOrder = pcode___browser__GETPROPERTY_TableViewVisible + 1;
static const int pcode___browser__GETPROPERTY_TableViewOrder = pcode___browser__SETPROPERTY_TableViewOrder + 1;

static const int pcode___browser__EVENT_OnOpen = pcode___browser__GETPROPERTY_TableViewOrder + 1;
static const int pcode___browser__EVENT_OnClose = pcode___browser__EVENT_OnOpen + 1;
static const int pcode___browser__EVENT_OnContextMenu = pcode___browser__EVENT_OnClose + 1;
static const int pcode___browser__EVENT_OnDragEnter = pcode___browser__EVENT_OnContextMenu + 1;
static const int pcode___browser__EVENT_OnDragExit = pcode___browser__EVENT_OnDragEnter + 1;
static const int pcode___browser__EVENT_OnDragMove = pcode___browser__EVENT_OnDragExit + 1;
static const int pcode___browser__EVENT_OnDrop = pcode___browser__EVENT_OnDragMove + 1;
static const int pcode___browser__EVENT_OnEnter = pcode___browser__EVENT_OnDrop + 1;
static const int pcode___browser__EVENT_OnGotFocus = pcode___browser__EVENT_OnEnter + 1;
static const int pcode___browser__EVENT_OnLostFocus = pcode___browser__EVENT_OnGotFocus + 1;
static const int pcode___browser__EVENT_OnHide = pcode___browser__EVENT_OnLostFocus + 1;
static const int pcode___browser__EVENT_OnKeyDown = pcode___browser__EVENT_OnHide + 1;
static const int pcode___browser__EVENT_OnKeyUp = pcode___browser__EVENT_OnKeyDown + 1;
static const int pcode___browser__EVENT_OnKeyPress = pcode___browser__EVENT_OnKeyUp + 1;
static const int pcode___browser__EVENT_OnExit = pcode___browser__EVENT_OnKeyPress + 1;
static const int pcode___browser__EVENT_OnDblClick = pcode___browser__EVENT_OnExit + 1;
static const int pcode___browser__EVENT_OnClick = pcode___browser__EVENT_OnDblClick + 1;
static const int pcode___browser__EVENT_OnMouseMove = pcode___browser__EVENT_OnClick + 1;
static const int pcode___browser__EVENT_OnMouseDown = pcode___browser__EVENT_OnMouseMove + 1;
static const int pcode___browser__EVENT_OnMouseUp = pcode___browser__EVENT_OnMouseDown + 1;
static const int pcode___browser__EVENT_OnMove = pcode___browser__EVENT_OnMouseUp + 1;
static const int pcode___browser__EVENT_OnPaint = pcode___browser__EVENT_OnMove + 1;
static const int pcode___browser__EVENT_OnResize = pcode___browser__EVENT_OnPaint + 1;
static const int pcode___browser__EVENT_OnShow = pcode___browser__EVENT_OnResize + 1;
static const int pcode___browser__EVENT_OnMouseWheel = pcode___browser__EVENT_OnShow + 1;
static const int pcode___browser__EVENT_OnTimer = pcode___browser__EVENT_OnMouseWheel + 1;
static const int pcode___browser__EVENT_OnPrint = pcode___browser__EVENT_OnTimer + 1;
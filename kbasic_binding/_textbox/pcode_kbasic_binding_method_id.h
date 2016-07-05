static const int pcode___textbox___textbox = pcode___textbox * SPACE;
static const int pcode___textbox___textbox1 = pcode___textbox___textbox + 1;

static const int pcode___textbox__SETPROPERTY_MouseTracking = pcode___textbox___textbox1 + 1;
static const int pcode___textbox__GETPROPERTY_MouseTracking = pcode___textbox__SETPROPERTY_MouseTracking + 1; 


static const int pcode___textbox__EVENT_OnSingleShot = pcode___textbox__GETPROPERTY_MouseTracking + 1;
static const int pcode___textbox__EVENT_OnEnabled = pcode___textbox__EVENT_OnSingleShot + 1;
static const int pcode___textbox__EVENT_OnDisabled = pcode___textbox__EVENT_OnEnabled + 1;

static const int pcode___textbox__SETPROPERTY_CursorAnimation = pcode___textbox__EVENT_OnDisabled + 1;
static const int pcode___textbox__GETPROPERTY_CursorAnimation = pcode___textbox__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___textbox__METHOD_DataIds = pcode___textbox__GETPROPERTY_CursorAnimation + 1;

static const int pcode___textbox__METHOD_DataRemove = pcode___textbox__METHOD_DataIds + 1;
static const int pcode___textbox__METHOD_DataRemoveAll = pcode___textbox__METHOD_DataRemove + 1;
static const int pcode___textbox__METHOD_DataSetBoolean = pcode___textbox__METHOD_DataRemoveAll + 1;
static const int pcode___textbox__METHOD_DataSetInteger = pcode___textbox__METHOD_DataSetBoolean + 1;
static const int pcode___textbox__METHOD_DataSetString = pcode___textbox__METHOD_DataSetInteger + 1;
static const int pcode___textbox__METHOD_DataSetDouble = pcode___textbox__METHOD_DataSetString + 1;
static const int pcode___textbox__METHOD_DataSetLong = pcode___textbox__METHOD_DataSetDouble + 1;
static const int pcode___textbox__METHOD_DataSetDecimal = pcode___textbox__METHOD_DataSetLong + 1;
static const int pcode___textbox__METHOD_DataSetDateTime = pcode___textbox__METHOD_DataSetDecimal + 1;


static const int pcode___textbox__METHOD_DataBoolean = pcode___textbox__METHOD_DataSetDateTime + 1;
static const int pcode___textbox__METHOD_DataInteger = pcode___textbox__METHOD_DataBoolean + 1;
static const int pcode___textbox__METHOD_DataString = pcode___textbox__METHOD_DataInteger + 1;
static const int pcode___textbox__METHOD_DataDouble = pcode___textbox__METHOD_DataString + 1;
static const int pcode___textbox__METHOD_DataLong = pcode___textbox__METHOD_DataDouble + 1;
static const int pcode___textbox__METHOD_DataDecimal = pcode___textbox__METHOD_DataLong + 1;
static const int pcode___textbox__METHOD_DataDateTime = pcode___textbox__METHOD_DataDecimal + 1;

static const int pcode___textbox__METHOD_ClearFocus = pcode___textbox__METHOD_DataDateTime + 1;
static const int pcode___textbox__METHOD_ToggleVisible = pcode___textbox__METHOD_ClearFocus + 1;

static const int pcode___textbox__METHOD_SingleShot = pcode___textbox__METHOD_ToggleVisible + 1;
static const int pcode___textbox__METHOD_StartTimer = pcode___textbox__METHOD_SingleShot + 1;
static const int pcode___textbox__METHOD_StopTimer = pcode___textbox__METHOD_StartTimer + 1;

//static const int pcode___textbox__METHOD_EventSender = pcode___textbox__METHOD_StopTimer + 1;

static const int pcode___textbox__METHOD_GlobalX = pcode___textbox__METHOD_StopTimer + 1;
static const int pcode___textbox__METHOD_GlobalY = pcode___textbox__METHOD_GlobalX + 1;
static const int pcode___textbox__METHOD_LocalX = pcode___textbox__METHOD_GlobalY + 1;
static const int pcode___textbox__METHOD_LocalY = pcode___textbox__METHOD_LocalX + 1;

static const int pcode___textbox__METHOD_UnderMouse = pcode___textbox__METHOD_LocalY + 1;

static const int pcode___textbox__SETPROPERTY_Mask = pcode___textbox__METHOD_UnderMouse + 1;
static const int pcode___textbox__GETPROPERTY_Mask = pcode___textbox__SETPROPERTY_Mask + 1;

static const int pcode___textbox__SETPROPERTY_SoundOnEvent = pcode___textbox__GETPROPERTY_Mask + 1;
static const int pcode___textbox__GETPROPERTY_SoundOnEvent = pcode___textbox__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___textbox__SETPROPERTY_Left = pcode___textbox__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___textbox__GETPROPERTY_Left = pcode___textbox__SETPROPERTY_Left + 1;
static const int pcode___textbox__SETPROPERTY_Top = pcode___textbox__GETPROPERTY_Left + 1;
static const int pcode___textbox__GETPROPERTY_Top = pcode___textbox__SETPROPERTY_Top + 1;

static const int pcode___textbox__SETPROPERTY_LocalX = pcode___textbox__GETPROPERTY_Top + 1;
static const int pcode___textbox__GETPROPERTY_LocalX = pcode___textbox__SETPROPERTY_LocalX + 1;
static const int pcode___textbox__SETPROPERTY_LocalY = pcode___textbox__GETPROPERTY_LocalX + 1;
static const int pcode___textbox__GETPROPERTY_LocalY = pcode___textbox__SETPROPERTY_LocalY + 1;

static const int pcode___textbox__SETPROPERTY_DrawOnPaint = pcode___textbox__GETPROPERTY_LocalY + 1;
static const int pcode___textbox__GETPROPERTY_DrawOnPaint = pcode___textbox__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___textbox__SETPROPERTY_Palette = pcode___textbox__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___textbox__GETPROPERTY_Palette = pcode___textbox__SETPROPERTY_Palette + 1;


static const int pcode___textbox__SETPROPERTY_BackgroundStyle = pcode___textbox__GETPROPERTY_Palette + 1;
static const int pcode___textbox__GETPROPERTY_BackgroundStyle = pcode___textbox__SETPROPERTY_BackgroundStyle + 1;


static const int pcode___textbox__SETPROPERTY_Layout = pcode___textbox__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___textbox__GETPROPERTY_Layout = pcode___textbox__SETPROPERTY_Layout + 1;
static const int pcode___textbox__METHOD_IsValid = pcode___textbox__GETPROPERTY_Layout + 1;
static const int pcode___textbox__METHOD_SelectAll = pcode___textbox__METHOD_IsValid + 1;
static const int pcode___textbox__SETPROPERTY_Alignment = pcode___textbox__METHOD_SelectAll + 1;
static const int pcode___textbox__GETPROPERTY_Alignment = pcode___textbox__SETPROPERTY_Alignment + 1;

static const int pcode___textbox__SETPROPERTY_StringValue = pcode___textbox__GETPROPERTY_Alignment + 1;
static const int pcode___textbox__GETPROPERTY_StringValue = pcode___textbox__SETPROPERTY_StringValue + 1;
static const int pcode___textbox__GETPROPERTY_OldStringValue = pcode___textbox__GETPROPERTY_StringValue + 1;
static const int pcode___textbox__SETPROPERTY_Text = pcode___textbox__GETPROPERTY_OldStringValue + 1;
static const int pcode___textbox__GETPROPERTY_Text = pcode___textbox__SETPROPERTY_Text + 1;

static const int pcode___textbox__SETPROPERTY_EchoMode = pcode___textbox__GETPROPERTY_Text + 1;
static const int pcode___textbox__GETPROPERTY_EchoMode = pcode___textbox__SETPROPERTY_EchoMode + 1;

static const int pcode___textbox__SETPROPERTY_InputMask = pcode___textbox__GETPROPERTY_EchoMode + 1;
static const int pcode___textbox__GETPROPERTY_InputMask = pcode___textbox__SETPROPERTY_InputMask + 1;
static const int pcode___textbox__SETPROPERTY_ReadOnly = pcode___textbox__GETPROPERTY_InputMask + 1;
static const int pcode___textbox__GETPROPERTY_ReadOnly = pcode___textbox__SETPROPERTY_ReadOnly + 1;
static const int pcode___textbox__SETPROPERTY_ValidatorDouble = pcode___textbox__GETPROPERTY_ReadOnly + 1;
static const int pcode___textbox__GETPROPERTY_ValidatorDouble = pcode___textbox__SETPROPERTY_ValidatorDouble + 1;
static const int pcode___textbox__SETPROPERTY_ValidatorInteger = pcode___textbox__GETPROPERTY_ValidatorDouble + 1;
static const int pcode___textbox__GETPROPERTY_ValidatorInteger = pcode___textbox__SETPROPERTY_ValidatorInteger + 1;
static const int pcode___textbox__SETPROPERTY_ValidatorRegEx = pcode___textbox__GETPROPERTY_ValidatorInteger + 1;
static const int pcode___textbox__GETPROPERTY_ValidatorRegEx = pcode___textbox__SETPROPERTY_ValidatorRegEx + 1;
static const int pcode___textbox__SETPROPERTY_ValidatorRegEx2 = pcode___textbox__GETPROPERTY_ValidatorRegEx + 1;
static const int pcode___textbox__GETPROPERTY_ValidatorRegEx2 = pcode___textbox__SETPROPERTY_ValidatorRegEx2 + 1;
static const int pcode___textbox__SETPROPERTY_IntegerMaximum = pcode___textbox__GETPROPERTY_ValidatorRegEx2 + 1;
static const int pcode___textbox__GETPROPERTY_IntegerMaximum = pcode___textbox__SETPROPERTY_IntegerMaximum + 1;
static const int pcode___textbox__SETPROPERTY_Completer = pcode___textbox__GETPROPERTY_IntegerMaximum + 1;
static const int pcode___textbox__GETPROPERTY_Completer = pcode___textbox__SETPROPERTY_Completer + 1;
static const int pcode___textbox__EVENT_OnEvent = pcode___textbox__GETPROPERTY_Completer + 1;


static const int pcode___textbox__EVENT_OnCursorPositionChanged = pcode___textbox__EVENT_OnEvent + 1;
static const int pcode___textbox__EVENT_OnEditingFinished = pcode___textbox__EVENT_OnCursorPositionChanged + 1;
static const int pcode___textbox__EVENT_OnReturnPressed = pcode___textbox__EVENT_OnEditingFinished + 1;
static const int pcode___textbox__EVENT_OnSelectionChanged = pcode___textbox__EVENT_OnReturnPressed + 1;
static const int pcode___textbox__EVENT_OnTextChanged = pcode___textbox__EVENT_OnSelectionChanged + 1;
static const int pcode___textbox__EVENT_OnTextEdited = pcode___textbox__EVENT_OnTextChanged + 1;


static const int pcode___textbox__METHOD_Move = pcode___textbox__EVENT_OnTextEdited + 1;
static const int pcode___textbox__METHOD_Resize = pcode___textbox__METHOD_Move + 1;
static const int pcode___textbox__METHOD_Show = pcode___textbox__METHOD_Resize + 1;
static const int pcode___textbox__METHOD_Hide = pcode___textbox__METHOD_Show + 1;
static const int pcode___textbox__METHOD_RepaintAlways = pcode___textbox__METHOD_Hide + 1;
static const int pcode___textbox__METHOD_Repaint = pcode___textbox__METHOD_RepaintAlways + 1;
static const int pcode___textbox__METHOD_Raise = pcode___textbox__METHOD_Repaint + 1;
static const int pcode___textbox__METHOD_Lower = pcode___textbox__METHOD_Raise + 1;
static const int pcode___textbox__METHOD_Close = pcode___textbox__METHOD_Lower + 1;
static const int pcode___textbox__METHOD_Open = pcode___textbox__METHOD_Close + 1;
static const int pcode___textbox__METHOD_SetFocus = pcode___textbox__METHOD_Open + 1;
static const int pcode___textbox__SETPROPERTY_Name = pcode___textbox__METHOD_SetFocus + 1;
static const int pcode___textbox__GETPROPERTY_Name = pcode___textbox__SETPROPERTY_Name + 1;
static const int pcode___textbox__SETPROPERTY_Group = pcode___textbox__GETPROPERTY_Name + 1;
static const int pcode___textbox__GETPROPERTY_Group = pcode___textbox__SETPROPERTY_Group + 1;
static const int pcode___textbox__SETPROPERTY_Background = pcode___textbox__GETPROPERTY_Group + 1;
static const int pcode___textbox__GETPROPERTY_Background = pcode___textbox__SETPROPERTY_Background + 1;
static const int pcode___textbox__SETPROPERTY_X = pcode___textbox__GETPROPERTY_Background + 1;
static const int pcode___textbox__GETPROPERTY_X = pcode___textbox__SETPROPERTY_X + 1;
static const int pcode___textbox__SETPROPERTY_Y = pcode___textbox__GETPROPERTY_X + 1;
static const int pcode___textbox__GETPROPERTY_Y = pcode___textbox__SETPROPERTY_Y + 1;
static const int pcode___textbox__SETPROPERTY_Width = pcode___textbox__GETPROPERTY_Y + 1;
static const int pcode___textbox__GETPROPERTY_Width = pcode___textbox__SETPROPERTY_Width + 1;
static const int pcode___textbox__SETPROPERTY_Height = pcode___textbox__GETPROPERTY_Width + 1;
static const int pcode___textbox__GETPROPERTY_Height = pcode___textbox__SETPROPERTY_Height + 1;
static const int pcode___textbox__GETPROPERTY_GlobalX = pcode___textbox__GETPROPERTY_Height + 1;
static const int pcode___textbox__GETPROPERTY_GlobalY = pcode___textbox__GETPROPERTY_GlobalX + 1;
static const int pcode___textbox__GETPROPERTY_OldX = pcode___textbox__GETPROPERTY_GlobalY + 1;
static const int pcode___textbox__GETPROPERTY_OldY = pcode___textbox__GETPROPERTY_OldX + 1;
static const int pcode___textbox__GETPROPERTY_OldWidth = pcode___textbox__GETPROPERTY_OldY + 1;
static const int pcode___textbox__GETPROPERTY_OldHeight = pcode___textbox__GETPROPERTY_OldWidth + 1;
static const int pcode___textbox__SETPROPERTY_MinimumWidth = pcode___textbox__GETPROPERTY_OldHeight + 1;
static const int pcode___textbox__GETPROPERTY_MinimumWidth = pcode___textbox__SETPROPERTY_MinimumWidth + 1;
static const int pcode___textbox__SETPROPERTY_MinimumHeight = pcode___textbox__GETPROPERTY_MinimumWidth + 1;
static const int pcode___textbox__GETPROPERTY_MinimumHeight = pcode___textbox__SETPROPERTY_MinimumHeight + 1;
static const int pcode___textbox__SETPROPERTY_MaximumWidth = pcode___textbox__GETPROPERTY_MinimumHeight + 1;
static const int pcode___textbox__GETPROPERTY_MaximumWidth = pcode___textbox__SETPROPERTY_MaximumWidth + 1;
static const int pcode___textbox__SETPROPERTY_MaximumHeight = pcode___textbox__GETPROPERTY_MaximumWidth + 1;
static const int pcode___textbox__GETPROPERTY_MaximumHeight = pcode___textbox__SETPROPERTY_MaximumHeight + 1;
static const int pcode___textbox__SETPROPERTY_Tag = pcode___textbox__GETPROPERTY_MaximumHeight + 1;
static const int pcode___textbox__GETPROPERTY_Tag = pcode___textbox__SETPROPERTY_Tag + 1;
static const int pcode___textbox__SETPROPERTY_CSV = pcode___textbox__GETPROPERTY_Tag + 1;
static const int pcode___textbox__GETPROPERTY_CSV = pcode___textbox__SETPROPERTY_CSV + 1;
static const int pcode___textbox__SETPROPERTY_ParentForm = pcode___textbox__GETPROPERTY_CSV + 1;
static const int pcode___textbox__GETPROPERTY_ParentForm = pcode___textbox__SETPROPERTY_ParentForm + 1;
static const int pcode___textbox__SETPROPERTY_ParentControl = pcode___textbox__GETPROPERTY_ParentForm + 1;
static const int pcode___textbox__GETPROPERTY_ParentControl = pcode___textbox__SETPROPERTY_ParentControl + 1;
static const int pcode___textbox__SETPROPERTY_DragDrop = pcode___textbox__GETPROPERTY_ParentControl + 1;
static const int pcode___textbox__GETPROPERTY_ParentControl1 = pcode___textbox__SETPROPERTY_DragDrop + 1;
static const int pcode___textbox__SETPROPERTY_ControlType = pcode___textbox__GETPROPERTY_ParentControl1 + 1;
static const int pcode___textbox__GETPROPERTY_ControlType = pcode___textbox__SETPROPERTY_ControlType + 1;
static const int pcode___textbox__SETPROPERTY_Focus = pcode___textbox__GETPROPERTY_ControlType + 1;
static const int pcode___textbox__GETPROPERTY_Focus = pcode___textbox__SETPROPERTY_Focus + 1;
static const int pcode___textbox__SETPROPERTY_FocusPolicy = pcode___textbox__GETPROPERTY_Focus + 1;
static const int pcode___textbox__GETPROPERTY_FocusPolicy = pcode___textbox__SETPROPERTY_FocusPolicy + 1;
static const int pcode___textbox__SETPROPERTY_FocusProxy = pcode___textbox__GETPROPERTY_FocusPolicy + 1;
static const int pcode___textbox__GETPROPERTY_FocusProxy = pcode___textbox__SETPROPERTY_FocusProxy + 1;
static const int pcode___textbox__SETPROPERTY_FocusOrder = pcode___textbox__GETPROPERTY_FocusProxy + 1;
static const int pcode___textbox__GETPROPERTY_FocusOrder = pcode___textbox__SETPROPERTY_FocusOrder + 1;
static const int pcode___textbox__SETPROPERTY_Cursor = pcode___textbox__GETPROPERTY_FocusOrder + 1;
static const int pcode___textbox__GETPROPERTY_Cursor = pcode___textbox__SETPROPERTY_Cursor + 1;
static const int pcode___textbox__SETPROPERTY_FontName = pcode___textbox__GETPROPERTY_Cursor + 1;
static const int pcode___textbox__GETPROPERTY_FontName = pcode___textbox__SETPROPERTY_FontName + 1;
static const int pcode___textbox__SETPROPERTY_FontSize = pcode___textbox__GETPROPERTY_FontName + 1;
static const int pcode___textbox__GETPROPERTY_FontSize = pcode___textbox__SETPROPERTY_FontSize + 1;
static const int pcode___textbox__SETPROPERTY_FontItalic = pcode___textbox__GETPROPERTY_FontSize + 1;
static const int pcode___textbox__GETPROPERTY_FontItalic = pcode___textbox__SETPROPERTY_FontItalic + 1;
static const int pcode___textbox__SETPROPERTY_FontBold = pcode___textbox__GETPROPERTY_FontItalic + 1;
static const int pcode___textbox__GETPROPERTY_FontBold = pcode___textbox__SETPROPERTY_FontBold + 1;
static const int pcode___textbox__SETPROPERTY_FontUnderline = pcode___textbox__GETPROPERTY_FontBold + 1;
static const int pcode___textbox__GETPROPERTY_FontUnderline = pcode___textbox__SETPROPERTY_FontUnderline + 1;
static const int pcode___textbox__SETPROPERTY_FontColor = pcode___textbox__GETPROPERTY_FontUnderline + 1;
static const int pcode___textbox__GETPROPERTY_FontColor = pcode___textbox__SETPROPERTY_FontColor + 1;
static const int pcode___textbox__SETPROPERTY_Enabled = pcode___textbox__GETPROPERTY_FontColor + 1;
static const int pcode___textbox__GETPROPERTY_Enabled = pcode___textbox__SETPROPERTY_Enabled + 1;
static const int pcode___textbox__SETPROPERTY_Visible = pcode___textbox__GETPROPERTY_Enabled + 1;
static const int pcode___textbox__GETPROPERTY_Visible = pcode___textbox__SETPROPERTY_Visible + 1;
static const int pcode___textbox__SETPROPERTY_StatusTip = pcode___textbox__GETPROPERTY_Visible + 1;
static const int pcode___textbox__GETPROPERTY_StatusTip = pcode___textbox__SETPROPERTY_StatusTip + 1;
static const int pcode___textbox__SETPROPERTY_ToolTip = pcode___textbox__GETPROPERTY_StatusTip + 1;
static const int pcode___textbox__GETPROPERTY_ToolTip = pcode___textbox__SETPROPERTY_ToolTip + 1;
static const int pcode___textbox__SETPROPERTY_StyleSheet = pcode___textbox__GETPROPERTY_ToolTip + 1;
static const int pcode___textbox__GETPROPERTY_StyleSheet = pcode___textbox__SETPROPERTY_StyleSheet + 1;
static const int pcode___textbox__SETPROPERTY_WhatsThis = pcode___textbox__GETPROPERTY_StyleSheet + 1;
static const int pcode___textbox__GETPROPERTY_WhatsThis = pcode___textbox__SETPROPERTY_WhatsThis + 1;
static const int pcode___textbox__SETPROPERTY_TimerInterval = pcode___textbox__GETPROPERTY_WhatsThis + 1;
static const int pcode___textbox__GETPROPERTY_TimerInterval = pcode___textbox__SETPROPERTY_TimerInterval + 1;
static const int pcode___textbox__SETPROPERTY_Opacity = pcode___textbox__GETPROPERTY_TimerInterval + 1;
static const int pcode___textbox__GETPROPERTY_Opacity = pcode___textbox__SETPROPERTY_Opacity + 1;
static const int pcode___textbox__SETPROPERTY_BoxIndex = pcode___textbox__GETPROPERTY_Opacity + 1;
static const int pcode___textbox__GETPROPERTY_BoxIndex = pcode___textbox__SETPROPERTY_BoxIndex + 1;
static const int pcode___textbox__SETPROPERTY_SplitIndex = pcode___textbox__GETPROPERTY_BoxIndex + 1;
static const int pcode___textbox__GETPROPERTY_SplitIndex = pcode___textbox__SETPROPERTY_SplitIndex + 1;
static const int pcode___textbox__SETPROPERTY_TabIndex = pcode___textbox__GETPROPERTY_SplitIndex + 1;
static const int pcode___textbox__GETPROPERTY_TabIndex = pcode___textbox__SETPROPERTY_TabIndex + 1;
static const int pcode___textbox__SETPROPERTY_BoxX = pcode___textbox__GETPROPERTY_TabIndex + 1;
static const int pcode___textbox__GETPROPERTY_BoxX = pcode___textbox__SETPROPERTY_BoxX + 1;
static const int pcode___textbox__SETPROPERTY_BoxY = pcode___textbox__GETPROPERTY_BoxX + 1;
static const int pcode___textbox__GETPROPERTY_BoxY = pcode___textbox__SETPROPERTY_BoxY + 1;
static const int pcode___textbox__SETPROPERTY_ParentIndex = pcode___textbox__GETPROPERTY_BoxY + 1;
static const int pcode___textbox__GETPROPERTY_ParentIndex = pcode___textbox__SETPROPERTY_ParentIndex + 1;
static const int pcode___textbox__SETPROPERTY_ControlType1 = pcode___textbox__GETPROPERTY_ParentIndex + 1;
static const int pcode___textbox__GETPROPERTY_ControlType1 = pcode___textbox__SETPROPERTY_ControlType1 + 1;

static const int pcode___textbox__SETPROPERTY_SQL = pcode___textbox__GETPROPERTY_ControlType1 + 1;
static const int pcode___textbox__GETPROPERTY_SQL = pcode___textbox__SETPROPERTY_SQL + 1;

static const int pcode___textbox__SETPROPERTY_SQLName = pcode___textbox__GETPROPERTY_SQL + 1;
static const int pcode___textbox__GETPROPERTY_SQLName = pcode___textbox__SETPROPERTY_SQLName + 1;
static const int pcode___textbox__SETPROPERTY_SQLRelation = pcode___textbox__GETPROPERTY_SQLName + 1;
static const int pcode___textbox__GETPROPERTY_SQLRelation = pcode___textbox__SETPROPERTY_SQLRelation + 1;
static const int pcode___textbox__SETPROPERTY_TableViewCaption = pcode___textbox__GETPROPERTY_SQLRelation + 1;
static const int pcode___textbox__GETPROPERTY_TableViewCaption = pcode___textbox__SETPROPERTY_TableViewCaption + 1;
static const int pcode___textbox__SETPROPERTY_TableViewSort = pcode___textbox__GETPROPERTY_TableViewCaption + 1;
static const int pcode___textbox__GETPROPERTY_TableViewSort = pcode___textbox__SETPROPERTY_TableViewSort + 1;
static const int pcode___textbox__SETPROPERTY_TableViewFilter = pcode___textbox__GETPROPERTY_TableViewSort + 1;
static const int pcode___textbox__GETPROPERTY_TableViewFilter = pcode___textbox__SETPROPERTY_TableViewFilter + 1;
static const int pcode___textbox__SETPROPERTY_TableViewWidth = pcode___textbox__GETPROPERTY_TableViewFilter + 1;
static const int pcode___textbox__GETPROPERTY_TableViewWidth = pcode___textbox__SETPROPERTY_TableViewWidth + 1;
static const int pcode___textbox__SETPROPERTY_TableViewVisible = pcode___textbox__GETPROPERTY_TableViewWidth + 1;
static const int pcode___textbox__GETPROPERTY_TableViewVisible = pcode___textbox__SETPROPERTY_TableViewVisible + 1;
static const int pcode___textbox__SETPROPERTY_TableViewOrder = pcode___textbox__GETPROPERTY_TableViewVisible + 1;
static const int pcode___textbox__GETPROPERTY_TableViewOrder = pcode___textbox__SETPROPERTY_TableViewOrder + 1;

static const int pcode___textbox__EVENT_OnOpen = pcode___textbox__GETPROPERTY_TableViewOrder + 1;
static const int pcode___textbox__EVENT_OnClose = pcode___textbox__EVENT_OnOpen + 1;
static const int pcode___textbox__EVENT_OnContextMenu = pcode___textbox__EVENT_OnClose + 1;
static const int pcode___textbox__EVENT_OnDragEnter = pcode___textbox__EVENT_OnContextMenu + 1;
static const int pcode___textbox__EVENT_OnDragExit = pcode___textbox__EVENT_OnDragEnter + 1;
static const int pcode___textbox__EVENT_OnDragMove = pcode___textbox__EVENT_OnDragExit + 1;
static const int pcode___textbox__EVENT_OnDrop = pcode___textbox__EVENT_OnDragMove + 1;
static const int pcode___textbox__EVENT_OnEnter = pcode___textbox__EVENT_OnDrop + 1;
static const int pcode___textbox__EVENT_OnGotFocus = pcode___textbox__EVENT_OnEnter + 1;
static const int pcode___textbox__EVENT_OnLostFocus = pcode___textbox__EVENT_OnGotFocus + 1;
static const int pcode___textbox__EVENT_OnHide = pcode___textbox__EVENT_OnLostFocus + 1;
static const int pcode___textbox__EVENT_OnKeyDown = pcode___textbox__EVENT_OnHide + 1;
static const int pcode___textbox__EVENT_OnKeyUp = pcode___textbox__EVENT_OnKeyDown + 1;
static const int pcode___textbox__EVENT_OnKeyPress = pcode___textbox__EVENT_OnKeyUp + 1;
static const int pcode___textbox__EVENT_OnExit = pcode___textbox__EVENT_OnKeyPress + 1;
static const int pcode___textbox__EVENT_OnDblClick = pcode___textbox__EVENT_OnExit + 1;
static const int pcode___textbox__EVENT_OnClick = pcode___textbox__EVENT_OnDblClick + 1;
static const int pcode___textbox__EVENT_OnMouseMove = pcode___textbox__EVENT_OnClick + 1;
static const int pcode___textbox__EVENT_OnMouseDown = pcode___textbox__EVENT_OnMouseMove + 1;
static const int pcode___textbox__EVENT_OnMouseUp = pcode___textbox__EVENT_OnMouseDown + 1;
static const int pcode___textbox__EVENT_OnMove = pcode___textbox__EVENT_OnMouseUp + 1;
static const int pcode___textbox__EVENT_OnPaint = pcode___textbox__EVENT_OnMove + 1;
static const int pcode___textbox__EVENT_OnResize = pcode___textbox__EVENT_OnPaint + 1;
static const int pcode___textbox__EVENT_OnShow = pcode___textbox__EVENT_OnResize + 1;
static const int pcode___textbox__EVENT_OnMouseWheel = pcode___textbox__EVENT_OnShow + 1;
static const int pcode___textbox__EVENT_OnTimer = pcode___textbox__EVENT_OnMouseWheel + 1;
static const int pcode___textbox__EVENT_OnPrint = pcode___textbox__EVENT_OnTimer + 1;
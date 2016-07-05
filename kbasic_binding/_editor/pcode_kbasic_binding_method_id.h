static const int pcode___editor___editor = pcode___editor * SPACE;
static const int pcode___editor___editor1 = pcode___editor___editor + 1;

static const int pcode___editor__SETPROPERTY_MouseTracking = pcode___editor___editor1 + 1;
static const int pcode___editor__GETPROPERTY_MouseTracking = pcode___editor__SETPROPERTY_MouseTracking + 1; 


static const int pcode___editor__EVENT_OnSingleShot = pcode___editor__GETPROPERTY_MouseTracking + 1;
static const int pcode___editor__EVENT_OnEnabled = pcode___editor__EVENT_OnSingleShot + 1;
static const int pcode___editor__EVENT_OnDisabled = pcode___editor__EVENT_OnEnabled + 1;

static const int pcode___editor__SETPROPERTY_CursorAnimation = pcode___editor__EVENT_OnDisabled + 1;
static const int pcode___editor__GETPROPERTY_CursorAnimation = pcode___editor__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___editor__METHOD_DataIds = pcode___editor__GETPROPERTY_CursorAnimation + 1;

static const int pcode___editor__METHOD_DataRemove = pcode___editor__METHOD_DataIds + 1;
static const int pcode___editor__METHOD_DataRemoveAll = pcode___editor__METHOD_DataRemove + 1;
static const int pcode___editor__METHOD_DataSetBoolean = pcode___editor__METHOD_DataRemoveAll + 1;
static const int pcode___editor__METHOD_DataSetInteger = pcode___editor__METHOD_DataSetBoolean + 1;
static const int pcode___editor__METHOD_DataSetString = pcode___editor__METHOD_DataSetInteger + 1;
static const int pcode___editor__METHOD_DataSetDouble = pcode___editor__METHOD_DataSetString + 1;
static const int pcode___editor__METHOD_DataSetLong = pcode___editor__METHOD_DataSetDouble + 1;
static const int pcode___editor__METHOD_DataSetDecimal = pcode___editor__METHOD_DataSetLong + 1;
static const int pcode___editor__METHOD_DataSetDateTime = pcode___editor__METHOD_DataSetDecimal + 1;


static const int pcode___editor__METHOD_DataBoolean = pcode___editor__METHOD_DataSetDateTime + 1;
static const int pcode___editor__METHOD_DataInteger = pcode___editor__METHOD_DataBoolean + 1;
static const int pcode___editor__METHOD_DataString = pcode___editor__METHOD_DataInteger + 1;
static const int pcode___editor__METHOD_DataDouble = pcode___editor__METHOD_DataString + 1;
static const int pcode___editor__METHOD_DataLong = pcode___editor__METHOD_DataDouble + 1;
static const int pcode___editor__METHOD_DataDecimal = pcode___editor__METHOD_DataLong + 1;
static const int pcode___editor__METHOD_DataDateTime = pcode___editor__METHOD_DataDecimal + 1;

static const int pcode___editor__METHOD_ClearFocus = pcode___editor__METHOD_DataDateTime + 1;
static const int pcode___editor__METHOD_ToggleVisible = pcode___editor__METHOD_ClearFocus + 1;

static const int pcode___editor__METHOD_SingleShot = pcode___editor__METHOD_ToggleVisible + 1;
static const int pcode___editor__METHOD_StartTimer = pcode___editor__METHOD_SingleShot + 1;
static const int pcode___editor__METHOD_StopTimer = pcode___editor__METHOD_StartTimer + 1;

//static const int pcode___editor__METHOD_EventSender = pcode___editor__METHOD_StopTimer + 1;

static const int pcode___editor__METHOD_GlobalX = pcode___editor__METHOD_StopTimer + 1;
static const int pcode___editor__METHOD_GlobalY = pcode___editor__METHOD_GlobalX + 1;
static const int pcode___editor__METHOD_LocalX = pcode___editor__METHOD_GlobalY + 1;
static const int pcode___editor__METHOD_LocalY = pcode___editor__METHOD_LocalX + 1;

static const int pcode___editor__METHOD_UnderMouse = pcode___editor__METHOD_LocalY + 1;

static const int pcode___editor__SETPROPERTY_Mask = pcode___editor__METHOD_UnderMouse + 1;
static const int pcode___editor__GETPROPERTY_Mask = pcode___editor__SETPROPERTY_Mask + 1;

static const int pcode___editor__SETPROPERTY_SoundOnEvent = pcode___editor__GETPROPERTY_Mask + 1;
static const int pcode___editor__GETPROPERTY_SoundOnEvent = pcode___editor__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___editor__SETPROPERTY_Left = pcode___editor__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___editor__GETPROPERTY_Left = pcode___editor__SETPROPERTY_Left + 1;
static const int pcode___editor__SETPROPERTY_Top = pcode___editor__GETPROPERTY_Left + 1;
static const int pcode___editor__GETPROPERTY_Top = pcode___editor__SETPROPERTY_Top + 1;

static const int pcode___editor__SETPROPERTY_LocalX = pcode___editor__GETPROPERTY_Top + 1;
static const int pcode___editor__GETPROPERTY_LocalX = pcode___editor__SETPROPERTY_LocalX + 1;
static const int pcode___editor__SETPROPERTY_LocalY = pcode___editor__GETPROPERTY_LocalX + 1;
static const int pcode___editor__GETPROPERTY_LocalY = pcode___editor__SETPROPERTY_LocalY + 1;

static const int pcode___editor__SETPROPERTY_DrawOnPaint = pcode___editor__GETPROPERTY_LocalY + 1;
static const int pcode___editor__GETPROPERTY_DrawOnPaint = pcode___editor__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___editor__SETPROPERTY_Palette = pcode___editor__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___editor__GETPROPERTY_Palette = pcode___editor__SETPROPERTY_Palette + 1;


static const int pcode___editor__SETPROPERTY_BackgroundStyle = pcode___editor__GETPROPERTY_Palette + 1;
static const int pcode___editor__GETPROPERTY_BackgroundStyle = pcode___editor__SETPROPERTY_BackgroundStyle + 1;



static const int pcode___editor__SETPROPERTY_Layout = pcode___editor__GETPROPERTY_BackgroundStyle + 1;
static const int pcode___editor__GETPROPERTY_Layout = pcode___editor__SETPROPERTY_Layout + 1;

static const int pcode___editor__SETPROPERTY_Value = pcode___editor__GETPROPERTY_Layout + 1;
static const int pcode___editor__GETPROPERTY_Value = pcode___editor__SETPROPERTY_Value + 1;
static const int pcode___editor__GETPROPERTY_OldValue = pcode___editor__GETPROPERTY_Value + 1;
static const int pcode___editor__SETPROPERTY_Text = pcode___editor__GETPROPERTY_OldValue + 1;
static const int pcode___editor__GETPROPERTY_Text = pcode___editor__SETPROPERTY_Text + 1;

static const int pcode___editor__SETPROPERTY_AcceptRichText = pcode___editor__GETPROPERTY_Text + 1;
static const int pcode___editor__GETPROPERTY_AcceptRichText = pcode___editor__SETPROPERTY_AcceptRichText + 1;
static const int pcode___editor__SETPROPERTY_Alignment = pcode___editor__GETPROPERTY_AcceptRichText + 1;
static const int pcode___editor__GETPROPERTY_Alignment = pcode___editor__SETPROPERTY_Alignment + 1;

static const int pcode___editor__SETPROPERTY_ReadOnly = pcode___editor__GETPROPERTY_Alignment + 1;
static const int pcode___editor__GETPROPERTY_ReadOnly = pcode___editor__SETPROPERTY_ReadOnly + 1;
static const int pcode___editor__SETPROPERTY_WordWrap = pcode___editor__GETPROPERTY_ReadOnly + 1;
static const int pcode___editor__GETPROPERTY_WordWrap = pcode___editor__SETPROPERTY_WordWrap + 1;
static const int pcode___editor__SETPROPERTY_Comment1Begin = pcode___editor__GETPROPERTY_WordWrap + 1;
static const int pcode___editor__GETPROPERTY_Comment1Begin = pcode___editor__SETPROPERTY_Comment1Begin + 1;
static const int pcode___editor__SETPROPERTY_Comment2Begin = pcode___editor__GETPROPERTY_Comment1Begin + 1;
static const int pcode___editor__GETPROPERTY_Comment2Begin = pcode___editor__SETPROPERTY_Comment2Begin + 1;
static const int pcode___editor__SETPROPERTY_Comment1End = pcode___editor__GETPROPERTY_Comment2Begin + 1;
static const int pcode___editor__GETPROPERTY_Comment1End = pcode___editor__SETPROPERTY_Comment1End + 1;
static const int pcode___editor__SETPROPERTY_Comment2End = pcode___editor__GETPROPERTY_Comment1End + 1;
static const int pcode___editor__GETPROPERTY_Comment2End = pcode___editor__SETPROPERTY_Comment2End + 1;
static const int pcode___editor__SETPROPERTY_Keywords = pcode___editor__GETPROPERTY_Comment2End + 1;
static const int pcode___editor__GETPROPERTY_Keywords = pcode___editor__SETPROPERTY_Keywords + 1;
static const int pcode___editor__SETPROPERTY_Commands = pcode___editor__GETPROPERTY_Keywords + 1;
static const int pcode___editor__GETPROPERTY_Commands = pcode___editor__SETPROPERTY_Commands + 1;
static const int pcode___editor__SETPROPERTY_CommentColor = pcode___editor__GETPROPERTY_Commands + 1;
static const int pcode___editor__GETPROPERTY_CommentColor = pcode___editor__SETPROPERTY_CommentColor + 1;
static const int pcode___editor__SETPROPERTY_KeywordColor = pcode___editor__GETPROPERTY_CommentColor + 1;
static const int pcode___editor__GETPROPERTY_KeywordColor = pcode___editor__SETPROPERTY_KeywordColor + 1;
static const int pcode___editor__SETPROPERTY_CommandColor = pcode___editor__GETPROPERTY_KeywordColor + 1;
static const int pcode___editor__GETPROPERTY_CommandColor = pcode___editor__SETPROPERTY_CommandColor + 1;
static const int pcode___editor__EVENT_OnEvent = pcode___editor__GETPROPERTY_CommandColor + 1;
static const int pcode___editor__EVENT_OnEvent1 = pcode___editor__EVENT_OnEvent + 1;
static const int pcode___editor__EVENT_OnCursorPositionChanged = pcode___editor__EVENT_OnEvent1 + 1;

static const int pcode___editor__METHOD_HTML = pcode___editor__EVENT_OnCursorPositionChanged + 1;
static const int pcode___editor__METHOD_PlainText = pcode___editor__METHOD_HTML + 1;
static const int pcode___editor__METHOD_IsModified = pcode___editor__METHOD_PlainText + 1;
static const int pcode___editor__METHOD_SetModified = pcode___editor__METHOD_IsModified + 1;
static const int pcode___editor__METHOD_SetFontColor = pcode___editor__METHOD_SetModified + 1;
static const int pcode___editor__METHOD_SetFontColor1 = pcode___editor__METHOD_SetFontColor + 1;

static const int pcode___editor__METHOD_SetFontPointSize = pcode___editor__METHOD_SetFontColor1 + 1;
static const int pcode___editor__METHOD_SetFontFamily = pcode___editor__METHOD_SetFontPointSize + 1;
static const int pcode___editor__METHOD_SetFontBold = pcode___editor__METHOD_SetFontFamily + 1;
static const int pcode___editor__METHOD_SetFontItalic = pcode___editor__METHOD_SetFontBold + 1;
static const int pcode___editor__METHOD_SetFontUnderline = pcode___editor__METHOD_SetFontItalic + 1;
static const int pcode___editor__METHOD_Line = pcode___editor__METHOD_SetFontUnderline + 1;
static const int pcode___editor__METHOD_Column = pcode___editor__METHOD_Line + 1;
static const int pcode___editor__METHOD_Selected = pcode___editor__METHOD_Column + 1;
static const int pcode___editor__METHOD_Undo = pcode___editor__METHOD_Selected + 1;
static const int pcode___editor__METHOD_Redo = pcode___editor__METHOD_Undo + 1;
static const int pcode___editor__METHOD_SetTabChangesFocus = pcode___editor__METHOD_Redo + 1;
static const int pcode___editor__METHOD_RemoveAll = pcode___editor__METHOD_SetTabChangesFocus + 1;
static const int pcode___editor__METHOD_Copy = pcode___editor__METHOD_RemoveAll + 1;
static const int pcode___editor__METHOD_Paste = pcode___editor__METHOD_Copy + 1;
static const int pcode___editor__METHOD_Cut = pcode___editor__METHOD_Paste + 1;
static const int pcode___editor__METHOD_SelectAll = pcode___editor__METHOD_Cut + 1;
static const int pcode___editor__METHOD_SetHtml = pcode___editor__METHOD_SelectAll + 1;
static const int pcode___editor__METHOD_SetPlainText = pcode___editor__METHOD_SetHtml + 1;
static const int pcode___editor__METHOD_InsertHtml = pcode___editor__METHOD_SetPlainText + 1;
static const int pcode___editor__METHOD_InsertPlainText = pcode___editor__METHOD_InsertHtml + 1;
static const int pcode___editor__METHOD_Append = pcode___editor__METHOD_InsertPlainText + 1;
static const int pcode___editor__METHOD_Move = pcode___editor__METHOD_Append + 1;
static const int pcode___editor__METHOD_Resize = pcode___editor__METHOD_Move + 1;
static const int pcode___editor__METHOD_Show = pcode___editor__METHOD_Resize + 1;
static const int pcode___editor__METHOD_Hide = pcode___editor__METHOD_Show + 1;
static const int pcode___editor__METHOD_RepaintAlways = pcode___editor__METHOD_Hide + 1;
static const int pcode___editor__METHOD_Repaint = pcode___editor__METHOD_RepaintAlways + 1;
static const int pcode___editor__METHOD_Raise = pcode___editor__METHOD_Repaint + 1;
static const int pcode___editor__METHOD_Lower = pcode___editor__METHOD_Raise + 1;
static const int pcode___editor__METHOD_Close = pcode___editor__METHOD_Lower + 1;
static const int pcode___editor__METHOD_Open = pcode___editor__METHOD_Close + 1;
static const int pcode___editor__METHOD_SetFocus = pcode___editor__METHOD_Open + 1;
static const int pcode___editor__SETPROPERTY_Name = pcode___editor__METHOD_SetFocus + 1;
static const int pcode___editor__GETPROPERTY_Name = pcode___editor__SETPROPERTY_Name + 1;
static const int pcode___editor__SETPROPERTY_Group = pcode___editor__GETPROPERTY_Name + 1;
static const int pcode___editor__GETPROPERTY_Group = pcode___editor__SETPROPERTY_Group + 1;
static const int pcode___editor__SETPROPERTY_Background = pcode___editor__GETPROPERTY_Group + 1;
static const int pcode___editor__GETPROPERTY_Background = pcode___editor__SETPROPERTY_Background + 1;
static const int pcode___editor__SETPROPERTY_X = pcode___editor__GETPROPERTY_Background + 1;
static const int pcode___editor__GETPROPERTY_X = pcode___editor__SETPROPERTY_X + 1;
static const int pcode___editor__SETPROPERTY_Y = pcode___editor__GETPROPERTY_X + 1;
static const int pcode___editor__GETPROPERTY_Y = pcode___editor__SETPROPERTY_Y + 1;
static const int pcode___editor__SETPROPERTY_Width = pcode___editor__GETPROPERTY_Y + 1;
static const int pcode___editor__GETPROPERTY_Width = pcode___editor__SETPROPERTY_Width + 1;
static const int pcode___editor__SETPROPERTY_Height = pcode___editor__GETPROPERTY_Width + 1;
static const int pcode___editor__GETPROPERTY_Height = pcode___editor__SETPROPERTY_Height + 1;
static const int pcode___editor__GETPROPERTY_GlobalX = pcode___editor__GETPROPERTY_Height + 1;
static const int pcode___editor__GETPROPERTY_GlobalY = pcode___editor__GETPROPERTY_GlobalX + 1;
static const int pcode___editor__GETPROPERTY_OldX = pcode___editor__GETPROPERTY_GlobalY + 1;
static const int pcode___editor__GETPROPERTY_OldY = pcode___editor__GETPROPERTY_OldX + 1;
static const int pcode___editor__GETPROPERTY_OldWidth = pcode___editor__GETPROPERTY_OldY + 1;
static const int pcode___editor__GETPROPERTY_OldHeight = pcode___editor__GETPROPERTY_OldWidth + 1;
static const int pcode___editor__SETPROPERTY_MinimumWidth = pcode___editor__GETPROPERTY_OldHeight + 1;
static const int pcode___editor__GETPROPERTY_MinimumWidth = pcode___editor__SETPROPERTY_MinimumWidth + 1;
static const int pcode___editor__SETPROPERTY_MinimumHeight = pcode___editor__GETPROPERTY_MinimumWidth + 1;
static const int pcode___editor__GETPROPERTY_MinimumHeight = pcode___editor__SETPROPERTY_MinimumHeight + 1;
static const int pcode___editor__SETPROPERTY_MaximumWidth = pcode___editor__GETPROPERTY_MinimumHeight + 1;
static const int pcode___editor__GETPROPERTY_MaximumWidth = pcode___editor__SETPROPERTY_MaximumWidth + 1;
static const int pcode___editor__SETPROPERTY_MaximumHeight = pcode___editor__GETPROPERTY_MaximumWidth + 1;
static const int pcode___editor__GETPROPERTY_MaximumHeight = pcode___editor__SETPROPERTY_MaximumHeight + 1;
static const int pcode___editor__SETPROPERTY_Tag = pcode___editor__GETPROPERTY_MaximumHeight + 1;
static const int pcode___editor__GETPROPERTY_Tag = pcode___editor__SETPROPERTY_Tag + 1;
static const int pcode___editor__SETPROPERTY_CSV = pcode___editor__GETPROPERTY_Tag + 1;
static const int pcode___editor__GETPROPERTY_CSV = pcode___editor__SETPROPERTY_CSV + 1;
static const int pcode___editor__SETPROPERTY_ParentForm = pcode___editor__GETPROPERTY_CSV + 1;
static const int pcode___editor__GETPROPERTY_ParentForm = pcode___editor__SETPROPERTY_ParentForm + 1;
static const int pcode___editor__SETPROPERTY_ParentControl = pcode___editor__GETPROPERTY_ParentForm + 1;
static const int pcode___editor__GETPROPERTY_ParentControl = pcode___editor__SETPROPERTY_ParentControl + 1;
static const int pcode___editor__SETPROPERTY_DragDrop = pcode___editor__GETPROPERTY_ParentControl + 1;
static const int pcode___editor__GETPROPERTY_ParentControl1 = pcode___editor__SETPROPERTY_DragDrop + 1;
static const int pcode___editor__SETPROPERTY_ControlType = pcode___editor__GETPROPERTY_ParentControl1 + 1;
static const int pcode___editor__GETPROPERTY_ControlType = pcode___editor__SETPROPERTY_ControlType + 1;
static const int pcode___editor__SETPROPERTY_Focus = pcode___editor__GETPROPERTY_ControlType + 1;
static const int pcode___editor__GETPROPERTY_Focus = pcode___editor__SETPROPERTY_Focus + 1;
static const int pcode___editor__SETPROPERTY_FocusPolicy = pcode___editor__GETPROPERTY_Focus + 1;
static const int pcode___editor__GETPROPERTY_FocusPolicy = pcode___editor__SETPROPERTY_FocusPolicy + 1;
static const int pcode___editor__SETPROPERTY_FocusProxy = pcode___editor__GETPROPERTY_FocusPolicy + 1;
static const int pcode___editor__GETPROPERTY_FocusProxy = pcode___editor__SETPROPERTY_FocusProxy + 1;
static const int pcode___editor__SETPROPERTY_FocusOrder = pcode___editor__GETPROPERTY_FocusProxy + 1;
static const int pcode___editor__GETPROPERTY_FocusOrder = pcode___editor__SETPROPERTY_FocusOrder + 1;
static const int pcode___editor__SETPROPERTY_Cursor = pcode___editor__GETPROPERTY_FocusOrder + 1;
static const int pcode___editor__GETPROPERTY_Cursor = pcode___editor__SETPROPERTY_Cursor + 1;
static const int pcode___editor__SETPROPERTY_FontName = pcode___editor__GETPROPERTY_Cursor + 1;
static const int pcode___editor__GETPROPERTY_FontName = pcode___editor__SETPROPERTY_FontName + 1;
static const int pcode___editor__SETPROPERTY_FontSize = pcode___editor__GETPROPERTY_FontName + 1;
static const int pcode___editor__GETPROPERTY_FontSize = pcode___editor__SETPROPERTY_FontSize + 1;
static const int pcode___editor__SETPROPERTY_FontItalic = pcode___editor__GETPROPERTY_FontSize + 1;
static const int pcode___editor__GETPROPERTY_FontItalic = pcode___editor__SETPROPERTY_FontItalic + 1;
static const int pcode___editor__SETPROPERTY_FontBold = pcode___editor__GETPROPERTY_FontItalic + 1;
static const int pcode___editor__GETPROPERTY_FontBold = pcode___editor__SETPROPERTY_FontBold + 1;
static const int pcode___editor__SETPROPERTY_FontUnderline = pcode___editor__GETPROPERTY_FontBold + 1;
static const int pcode___editor__GETPROPERTY_FontUnderline = pcode___editor__SETPROPERTY_FontUnderline + 1;
static const int pcode___editor__SETPROPERTY_FontColor = pcode___editor__GETPROPERTY_FontUnderline + 1;
static const int pcode___editor__GETPROPERTY_FontColor = pcode___editor__SETPROPERTY_FontColor + 1;
static const int pcode___editor__SETPROPERTY_Enabled = pcode___editor__GETPROPERTY_FontColor + 1;
static const int pcode___editor__GETPROPERTY_Enabled = pcode___editor__SETPROPERTY_Enabled + 1;
static const int pcode___editor__SETPROPERTY_Visible = pcode___editor__GETPROPERTY_Enabled + 1;
static const int pcode___editor__GETPROPERTY_Visible = pcode___editor__SETPROPERTY_Visible + 1;
static const int pcode___editor__SETPROPERTY_StatusTip = pcode___editor__GETPROPERTY_Visible + 1;
static const int pcode___editor__GETPROPERTY_StatusTip = pcode___editor__SETPROPERTY_StatusTip + 1;
static const int pcode___editor__SETPROPERTY_ToolTip = pcode___editor__GETPROPERTY_StatusTip + 1;
static const int pcode___editor__GETPROPERTY_ToolTip = pcode___editor__SETPROPERTY_ToolTip + 1;
static const int pcode___editor__SETPROPERTY_StyleSheet = pcode___editor__GETPROPERTY_ToolTip + 1;
static const int pcode___editor__GETPROPERTY_StyleSheet = pcode___editor__SETPROPERTY_StyleSheet + 1;
static const int pcode___editor__SETPROPERTY_WhatsThis = pcode___editor__GETPROPERTY_StyleSheet + 1;
static const int pcode___editor__GETPROPERTY_WhatsThis = pcode___editor__SETPROPERTY_WhatsThis + 1;
static const int pcode___editor__SETPROPERTY_TimerInterval = pcode___editor__GETPROPERTY_WhatsThis + 1;
static const int pcode___editor__GETPROPERTY_TimerInterval = pcode___editor__SETPROPERTY_TimerInterval + 1;
static const int pcode___editor__SETPROPERTY_Opacity = pcode___editor__GETPROPERTY_TimerInterval + 1;
static const int pcode___editor__GETPROPERTY_Opacity = pcode___editor__SETPROPERTY_Opacity + 1;
static const int pcode___editor__SETPROPERTY_BoxIndex = pcode___editor__GETPROPERTY_Opacity + 1;
static const int pcode___editor__GETPROPERTY_BoxIndex = pcode___editor__SETPROPERTY_BoxIndex + 1;
static const int pcode___editor__SETPROPERTY_SplitIndex = pcode___editor__GETPROPERTY_BoxIndex + 1;
static const int pcode___editor__GETPROPERTY_SplitIndex = pcode___editor__SETPROPERTY_SplitIndex + 1;
static const int pcode___editor__SETPROPERTY_TabIndex = pcode___editor__GETPROPERTY_SplitIndex + 1;
static const int pcode___editor__GETPROPERTY_TabIndex = pcode___editor__SETPROPERTY_TabIndex + 1;
static const int pcode___editor__SETPROPERTY_BoxX = pcode___editor__GETPROPERTY_TabIndex + 1;
static const int pcode___editor__GETPROPERTY_BoxX = pcode___editor__SETPROPERTY_BoxX + 1;
static const int pcode___editor__SETPROPERTY_BoxY = pcode___editor__GETPROPERTY_BoxX + 1;
static const int pcode___editor__GETPROPERTY_BoxY = pcode___editor__SETPROPERTY_BoxY + 1;
static const int pcode___editor__SETPROPERTY_ParentIndex = pcode___editor__GETPROPERTY_BoxY + 1;
static const int pcode___editor__GETPROPERTY_ParentIndex = pcode___editor__SETPROPERTY_ParentIndex + 1;
static const int pcode___editor__SETPROPERTY_ControlType1 = pcode___editor__GETPROPERTY_ParentIndex + 1;
static const int pcode___editor__GETPROPERTY_ControlType1 = pcode___editor__SETPROPERTY_ControlType1 + 1;

static const int pcode___editor__SETPROPERTY_SQLName = pcode___editor__GETPROPERTY_ControlType1 + 1;
static const int pcode___editor__GETPROPERTY_SQLName = pcode___editor__SETPROPERTY_SQLName + 1;
static const int pcode___editor__SETPROPERTY_SQLRelation = pcode___editor__GETPROPERTY_SQLName + 1;
static const int pcode___editor__GETPROPERTY_SQLRelation = pcode___editor__SETPROPERTY_SQLRelation + 1;
static const int pcode___editor__SETPROPERTY_TableViewCaption = pcode___editor__GETPROPERTY_SQLRelation + 1;
static const int pcode___editor__GETPROPERTY_TableViewCaption = pcode___editor__SETPROPERTY_TableViewCaption + 1;
static const int pcode___editor__SETPROPERTY_TableViewSort = pcode___editor__GETPROPERTY_TableViewCaption + 1;
static const int pcode___editor__GETPROPERTY_TableViewSort = pcode___editor__SETPROPERTY_TableViewSort + 1;
static const int pcode___editor__SETPROPERTY_TableViewFilter = pcode___editor__GETPROPERTY_TableViewSort + 1;
static const int pcode___editor__GETPROPERTY_TableViewFilter = pcode___editor__SETPROPERTY_TableViewFilter + 1;
static const int pcode___editor__SETPROPERTY_TableViewWidth = pcode___editor__GETPROPERTY_TableViewFilter + 1;
static const int pcode___editor__GETPROPERTY_TableViewWidth = pcode___editor__SETPROPERTY_TableViewWidth + 1;
static const int pcode___editor__SETPROPERTY_TableViewVisible = pcode___editor__GETPROPERTY_TableViewWidth + 1;
static const int pcode___editor__GETPROPERTY_TableViewVisible = pcode___editor__SETPROPERTY_TableViewVisible + 1;
static const int pcode___editor__SETPROPERTY_TableViewOrder = pcode___editor__GETPROPERTY_TableViewVisible + 1;
static const int pcode___editor__GETPROPERTY_TableViewOrder = pcode___editor__SETPROPERTY_TableViewOrder + 1;

static const int pcode___editor__EVENT_OnOpen = pcode___editor__GETPROPERTY_TableViewOrder + 1;
static const int pcode___editor__EVENT_OnClose = pcode___editor__EVENT_OnOpen + 1;
static const int pcode___editor__EVENT_OnContextMenu = pcode___editor__EVENT_OnClose + 1;
static const int pcode___editor__EVENT_OnDragEnter = pcode___editor__EVENT_OnContextMenu + 1;
static const int pcode___editor__EVENT_OnDragExit = pcode___editor__EVENT_OnDragEnter + 1;
static const int pcode___editor__EVENT_OnDragMove = pcode___editor__EVENT_OnDragExit + 1;
static const int pcode___editor__EVENT_OnDrop = pcode___editor__EVENT_OnDragMove + 1;
static const int pcode___editor__EVENT_OnEnter = pcode___editor__EVENT_OnDrop + 1;
static const int pcode___editor__EVENT_OnGotFocus = pcode___editor__EVENT_OnEnter + 1;
static const int pcode___editor__EVENT_OnLostFocus = pcode___editor__EVENT_OnGotFocus + 1;
static const int pcode___editor__EVENT_OnHide = pcode___editor__EVENT_OnLostFocus + 1;
static const int pcode___editor__EVENT_OnKeyDown = pcode___editor__EVENT_OnHide + 1;
static const int pcode___editor__EVENT_OnKeyUp = pcode___editor__EVENT_OnKeyDown + 1;
static const int pcode___editor__EVENT_OnKeyPress = pcode___editor__EVENT_OnKeyUp + 1;
static const int pcode___editor__EVENT_OnExit = pcode___editor__EVENT_OnKeyPress + 1;
static const int pcode___editor__EVENT_OnDblClick = pcode___editor__EVENT_OnExit + 1;
static const int pcode___editor__EVENT_OnClick = pcode___editor__EVENT_OnDblClick + 1;
static const int pcode___editor__EVENT_OnMouseMove = pcode___editor__EVENT_OnClick + 1;
static const int pcode___editor__EVENT_OnMouseDown = pcode___editor__EVENT_OnMouseMove + 1;
static const int pcode___editor__EVENT_OnMouseUp = pcode___editor__EVENT_OnMouseDown + 1;
static const int pcode___editor__EVENT_OnMove = pcode___editor__EVENT_OnMouseUp + 1;
static const int pcode___editor__EVENT_OnPaint = pcode___editor__EVENT_OnMove + 1;
static const int pcode___editor__EVENT_OnResize = pcode___editor__EVENT_OnPaint + 1;
static const int pcode___editor__EVENT_OnShow = pcode___editor__EVENT_OnResize + 1;
static const int pcode___editor__EVENT_OnMouseWheel = pcode___editor__EVENT_OnShow + 1;
static const int pcode___editor__EVENT_OnTimer = pcode___editor__EVENT_OnMouseWheel + 1;
static const int pcode___editor__EVENT_OnPrint = pcode___editor__EVENT_OnTimer + 1;
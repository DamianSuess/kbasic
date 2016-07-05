static const int pcode___form___form = pcode___form * SPACE;

static const int pcode___form__METHOD_Hwnd = pcode___form___form + 1;

static const int pcode___form__METHOD_IsFilterActive = pcode___form__METHOD_Hwnd + 1;

static const int pcode___form__METHOD_Append = pcode___form__METHOD_IsFilterActive + 1;
static const int pcode___form__METHOD_Insert1 = pcode___form__METHOD_Append + 1;
static const int pcode___form__METHOD_Remove = pcode___form__METHOD_Insert1 + 1;
static const int pcode___form__SETPROPERTY_MouseTracking = pcode___form__METHOD_Remove + 1;
static const int pcode___form__GETPROPERTY_MouseTracking = pcode___form__SETPROPERTY_MouseTracking + 1;
static const int pcode___form__SETPROPERTY_MoveOnMouseDrag = pcode___form__GETPROPERTY_MouseTracking + 1;
static const int pcode___form__GETPROPERTY_MoveOnMouseDrag = pcode___form__SETPROPERTY_MoveOnMouseDrag + 1;


static const int pcode___form__EVENT_OnDockMove = pcode___form__GETPROPERTY_MoveOnMouseDrag + 1;
static const int pcode___form__EVENT_OnDockShow = pcode___form__EVENT_OnDockMove + 1;
static const int pcode___form__EVENT_OnDockHide = pcode___form__EVENT_OnDockShow + 1;
static const int pcode___form__EVENT_OnDockFloating = pcode___form__EVENT_OnDockHide + 1;
static const int pcode___form__EVENT_OnDockNotFloating = pcode___form__EVENT_OnDockFloating + 1;


static const int pcode___form__METHOD_DockIsLeft = pcode___form__EVENT_OnDockNotFloating + 1;
static const int pcode___form__METHOD_DockIsRight = pcode___form__METHOD_DockIsLeft + 1;
static const int pcode___form__METHOD_DockIsTop = pcode___form__METHOD_DockIsRight + 1;
static const int pcode___form__METHOD_DockIsBottom = pcode___form__METHOD_DockIsTop + 1;

static const int pcode___form__METHOD_DockSetLeft = pcode___form__METHOD_DockIsBottom + 1;
static const int pcode___form__METHOD_DockSetRight = pcode___form__METHOD_DockSetLeft + 1;
static const int pcode___form__METHOD_DockSetTop = pcode___form__METHOD_DockSetRight + 1;
static const int pcode___form__METHOD_DockSetBottom = pcode___form__METHOD_DockSetTop + 1;

static const int pcode___form__METHOD_DockTabify = pcode___form__METHOD_DockSetBottom + 1;
static const int pcode___form__METHOD_DockSplit = pcode___form__METHOD_DockTabify + 1;

static const int pcode___form__METHOD_DockSetFloating = pcode___form__METHOD_DockSplit + 1;
static const int pcode___form__METHOD_DockIsFloating = pcode___form__METHOD_DockSetFloating + 1;

static const int pcode___form__SETPROPERTY_DockSplit = pcode___form__METHOD_DockIsFloating + 1;
static const int pcode___form__GETPROPERTY_DockSplit = pcode___form__SETPROPERTY_DockSplit + 1;

static const int pcode___form__METHOD_ControlFocus = pcode___form__GETPROPERTY_DockSplit + 1;
static const int pcode___form__METHOD_ControlFocusNext = pcode___form__METHOD_ControlFocus + 1;
static const int pcode___form__METHOD_ControlSetFocusNext = pcode___form__METHOD_ControlFocusNext+ 1;
static const int pcode___form__METHOD_ControlSetFocusPrevious = pcode___form__METHOD_ControlSetFocusNext+ 1;
static const int pcode___form__METHOD_IsShownCentered = pcode___form__METHOD_ControlSetFocusPrevious + 1;
static const int pcode___form__METHOD_IsOpen = pcode___form__METHOD_IsShownCentered + 1;

static const int pcode___form__METHOD_ShowCentered = pcode___form__METHOD_IsOpen + 1;
static const int pcode___form__METHOD_OpenMaximized = pcode___form__METHOD_ShowCentered + 1;
static const int pcode___form__METHOD_OpenMinimized = pcode___form__METHOD_OpenMaximized + 1;
static const int pcode___form__METHOD_EventSource = pcode___form__METHOD_OpenMinimized + 1;

static const int pcode___form__METHOD_FormState = pcode___form__METHOD_EventSource + 1;
static const int pcode___form__METHOD_OpenCenteredOnlyOnce = pcode___form__METHOD_FormState + 1;
static const int pcode___form__METHOD_OpenOnlyOnce = pcode___form__METHOD_OpenCenteredOnlyOnce + 1;
static const int pcode___form__METHOD_OpenHiddenOnlyOnce = pcode___form__METHOD_OpenOnlyOnce + 1;

static const int pcode___form__SETPROPERTY_ResizableSmaller = pcode___form__METHOD_OpenHiddenOnlyOnce + 1;
static const int pcode___form__GETPROPERTY_ResizableSmaller = pcode___form__SETPROPERTY_ResizableSmaller + 1;
static const int pcode___form__SETPROPERTY_ResizableBigger = pcode___form__GETPROPERTY_ResizableSmaller + 1;
static const int pcode___form__GETPROPERTY_ResizableBigger = pcode___form__SETPROPERTY_ResizableBigger + 1;
static const int pcode___form__SETPROPERTY_ShowMode = pcode___form__GETPROPERTY_ResizableBigger + 1;
static const int pcode___form__GETPROPERTY_ShowMode = pcode___form__SETPROPERTY_ShowMode + 1;
static const int pcode___form__SETPROPERTY_FormFileName = pcode___form__GETPROPERTY_ShowMode + 1;
static const int pcode___form__GETPROPERTY_FormFileName = pcode___form__SETPROPERTY_FormFileName + 1;
static const int pcode___form__SETPROPERTY_FormModified = pcode___form__GETPROPERTY_FormFileName + 1;
static const int pcode___form__GETPROPERTY_FormModified = pcode___form__SETPROPERTY_FormModified + 1;
static const int pcode___form__SETPROPERTY_FormX = pcode___form__GETPROPERTY_FormModified + 1;
static const int pcode___form__GETPROPERTY_FormX = pcode___form__SETPROPERTY_FormX + 1;
static const int pcode___form__SETPROPERTY_FormY = pcode___form__GETPROPERTY_FormX + 1;
static const int pcode___form__GETPROPERTY_FormY = pcode___form__SETPROPERTY_FormY + 1;
static const int pcode___form__SETPROPERTY_FormWidth = pcode___form__GETPROPERTY_FormY + 1;
static const int pcode___form__GETPROPERTY_FormWidth = pcode___form__SETPROPERTY_FormWidth + 1;
static const int pcode___form__SETPROPERTY_FormHeight = pcode___form__GETPROPERTY_FormWidth + 1;
static const int pcode___form__GETPROPERTY_FormHeight = pcode___form__SETPROPERTY_FormHeight + 1;



static const int pcode___form__EVENT_OnSingleShot = pcode___form__GETPROPERTY_FormHeight + 1;
static const int pcode___form__EVENT_OnEnabled = pcode___form__EVENT_OnSingleShot + 1;
static const int pcode___form__EVENT_OnDisabled = pcode___form__EVENT_OnEnabled + 1;

static const int pcode___form__SETPROPERTY_CursorAnimation = pcode___form__EVENT_OnDisabled + 1;
static const int pcode___form__GETPROPERTY_CursorAnimation = pcode___form__SETPROPERTY_CursorAnimation + 1; 

static const int pcode___form__METHOD_DataIds = pcode___form__GETPROPERTY_CursorAnimation + 1;

static const int pcode___form__METHOD_DataRemove = pcode___form__METHOD_DataIds + 1;
static const int pcode___form__METHOD_DataRemoveAll = pcode___form__METHOD_DataRemove + 1;
static const int pcode___form__METHOD_DataSetBoolean = pcode___form__METHOD_DataRemoveAll + 1;
static const int pcode___form__METHOD_DataSetInteger = pcode___form__METHOD_DataSetBoolean + 1;
static const int pcode___form__METHOD_DataSetString = pcode___form__METHOD_DataSetInteger + 1;
static const int pcode___form__METHOD_DataSetDouble = pcode___form__METHOD_DataSetString + 1;
static const int pcode___form__METHOD_DataSetLong = pcode___form__METHOD_DataSetDouble + 1;
static const int pcode___form__METHOD_DataSetDecimal = pcode___form__METHOD_DataSetLong + 1;
static const int pcode___form__METHOD_DataSetDateTime = pcode___form__METHOD_DataSetDecimal + 1;


static const int pcode___form__METHOD_DataBoolean = pcode___form__METHOD_DataSetDateTime + 1;
static const int pcode___form__METHOD_DataInteger = pcode___form__METHOD_DataBoolean + 1;
static const int pcode___form__METHOD_DataString = pcode___form__METHOD_DataInteger + 1;
static const int pcode___form__METHOD_DataDouble = pcode___form__METHOD_DataString + 1;
static const int pcode___form__METHOD_DataLong = pcode___form__METHOD_DataDouble + 1;
static const int pcode___form__METHOD_DataDecimal = pcode___form__METHOD_DataLong + 1;
static const int pcode___form__METHOD_DataDateTime = pcode___form__METHOD_DataDecimal + 1;

static const int pcode___form__METHOD_ClearFocus = pcode___form__METHOD_DataDateTime + 1;
static const int pcode___form__METHOD_ToggleVisible = pcode___form__METHOD_ClearFocus + 1;

static const int pcode___form__METHOD_SingleShot = pcode___form__METHOD_ToggleVisible + 1;
static const int pcode___form__METHOD_StartTimer = pcode___form__METHOD_SingleShot + 1;
static const int pcode___form__METHOD_StopTimer = pcode___form__METHOD_StartTimer + 1;

//static const int pcode___form__METHOD_EventSender = pcode___form__METHOD_StopTimer + 1;

static const int pcode___form__METHOD_GlobalX = pcode___form__METHOD_StopTimer + 1;
static const int pcode___form__METHOD_GlobalY = pcode___form__METHOD_GlobalX + 1;
static const int pcode___form__METHOD_LocalX = pcode___form__METHOD_GlobalY + 1;
static const int pcode___form__METHOD_LocalY = pcode___form__METHOD_LocalX + 1;

static const int pcode___form__METHOD_UnderMouse = pcode___form__METHOD_LocalY + 1;

static const int pcode___form__SETPROPERTY_Mask = pcode___form__METHOD_UnderMouse + 1;
static const int pcode___form__GETPROPERTY_Mask = pcode___form__SETPROPERTY_Mask + 1;

static const int pcode___form__SETPROPERTY_SoundOnEvent = pcode___form__GETPROPERTY_Mask + 1;
static const int pcode___form__GETPROPERTY_SoundOnEvent = pcode___form__SETPROPERTY_SoundOnEvent + 1;

static const int pcode___form__SETPROPERTY_Left = pcode___form__GETPROPERTY_SoundOnEvent + 1;
static const int pcode___form__GETPROPERTY_Left = pcode___form__SETPROPERTY_Left + 1;
static const int pcode___form__SETPROPERTY_Top = pcode___form__GETPROPERTY_Left + 1;
static const int pcode___form__GETPROPERTY_Top = pcode___form__SETPROPERTY_Top + 1;

static const int pcode___form__SETPROPERTY_LocalX = pcode___form__GETPROPERTY_Top + 1;
static const int pcode___form__GETPROPERTY_LocalX = pcode___form__SETPROPERTY_LocalX + 1;
static const int pcode___form__SETPROPERTY_LocalY = pcode___form__GETPROPERTY_LocalX + 1;
static const int pcode___form__GETPROPERTY_LocalY = pcode___form__SETPROPERTY_LocalY + 1;

static const int pcode___form__SETPROPERTY_DrawOnPaint = pcode___form__GETPROPERTY_LocalY + 1;
static const int pcode___form__GETPROPERTY_DrawOnPaint = pcode___form__SETPROPERTY_DrawOnPaint + 1;

static const int pcode___form__SETPROPERTY_Palette = pcode___form__GETPROPERTY_DrawOnPaint + 1;
static const int pcode___form__GETPROPERTY_Palette = pcode___form__SETPROPERTY_Palette + 1;


static const int pcode___form__SETPROPERTY_BackgroundStyle = pcode___form__GETPROPERTY_Palette + 1;
static const int pcode___form__GETPROPERTY_BackgroundStyle = pcode___form__SETPROPERTY_BackgroundStyle + 1;



static const int pcode___form__METHOD_Load = pcode___form__GETPROPERTY_BackgroundStyle + 1;

static const int pcode___form__METHOD_IsShownFullScreen =pcode___form__METHOD_Load+ 1;
static const int pcode___form__METHOD_IsShownMaximized =pcode___form__METHOD_IsShownFullScreen + 1;
static const int pcode___form__METHOD_IsShownMinimized =pcode___form__METHOD_IsShownMaximized + 1;
static const int pcode___form__METHOD_IsShownNormal =pcode___form__METHOD_IsShownMinimized + 1;



static const int pcode___form__METHOD_SetWithTag =pcode___form__METHOD_IsShownNormal + 1;
static const int pcode___form__METHOD_SetWithTag1 = pcode___form__METHOD_SetWithTag + 1;
static const int pcode___form__METHOD_SetWithTag2 = pcode___form__METHOD_SetWithTag1 + 1;
static const int pcode___form__METHOD_SetWithTag3 = pcode___form__METHOD_SetWithTag2 + 1;

static const int pcode___form__METHOD_SetWithGroup = pcode___form__METHOD_SetWithTag3 + 1;
static const int pcode___form__METHOD_SetWithGroup1 = pcode___form__METHOD_SetWithGroup + 1;
static const int pcode___form__METHOD_SetWithGroup2 = pcode___form__METHOD_SetWithGroup1 + 1;
static const int pcode___form__METHOD_SetWithGroup3 = pcode___form__METHOD_SetWithGroup2 + 1;



static const int pcode___form__METHOD_ShowMultiPage =pcode___form__METHOD_SetWithGroup3 + 1;
static const int pcode___form__METHOD_ShowNextMultiPage = pcode___form__METHOD_ShowMultiPage + 1;
static const int pcode___form__METHOD_ShowPreviousMultiPage = pcode___form__METHOD_ShowNextMultiPage + 1;

static const int pcode___form__METHOD_OpenPrintDialog = pcode___form__METHOD_ShowPreviousMultiPage + 1;
static const int pcode___form__METHOD_OpenPrint = pcode___form__METHOD_OpenPrintDialog + 1;
static const int pcode___form__METHOD_OpenPrintPreview = pcode___form__METHOD_OpenPrint + 1;



static const int pcode___form__SETPROPERTY_Resizable = pcode___form__METHOD_OpenPrintPreview + 1;
static const int pcode___form__GETPROPERTY_Resizable = pcode___form__SETPROPERTY_Resizable + 1;

static const int pcode___form__EVENT_OnScroll = pcode___form__GETPROPERTY_Resizable + 1;

static const int pcode___form__EVENT_OnMultiPageShow = pcode___form__EVENT_OnScroll + 1;

static const int pcode___form__METHOD_Finish = pcode___form__EVENT_OnMultiPageShow + 1;
static const int pcode___form__METHOD_FocusControl = pcode___form__METHOD_Finish + 1;
static const int pcode___form__METHOD_ControlFirst = pcode___form__METHOD_FocusControl + 1;
static const int pcode___form__METHOD_ControlNext = pcode___form__METHOD_ControlFirst + 1;
static const int pcode___form__METHOD_Tr = pcode___form__METHOD_ControlNext + 1;
static const int pcode___form__METHOD_ShowFullScreen = pcode___form__METHOD_Tr + 1;
static const int pcode___form__METHOD_ShowMaximized = pcode___form__METHOD_ShowFullScreen + 1;
static const int pcode___form__METHOD_ShowMinimized = pcode___form__METHOD_ShowMaximized + 1;
static const int pcode___form__METHOD_ShowNormal = pcode___form__METHOD_ShowMinimized + 1;
static const int pcode___form__METHOD_Control = pcode___form__METHOD_ShowNormal + 1;
static const int pcode___form__EVENT_OnAddNew = pcode___form__METHOD_Control + 1;
static const int pcode___form__EVENT_OnLoad = pcode___form__EVENT_OnAddNew + 1;
static const int pcode___form__EVENT_OnGoTo = pcode___form__EVENT_OnLoad + 1;
static const int pcode___form__EVENT_OnGoTo2 = pcode___form__EVENT_OnGoTo + 1;
static const int pcode___form__EVENT_OnQuery = pcode___form__EVENT_OnGoTo2 + 1;
static const int pcode___form__EVENT_OnDirty = pcode___form__EVENT_OnQuery + 1;
static const int pcode___form__EVENT_OnBeforeInsert = pcode___form__EVENT_OnDirty + 1;
static const int pcode___form__EVENT_OnBeforeUpdate = pcode___form__EVENT_OnBeforeInsert + 1;
static const int pcode___form__EVENT_OnBeforeDelete = pcode___form__EVENT_OnBeforeUpdate + 1;
static const int pcode___form__EVENT_OnAfterInsert = pcode___form__EVENT_OnBeforeDelete + 1;
static const int pcode___form__EVENT_OnAfterUpdate = pcode___form__EVENT_OnAfterInsert + 1;
static const int pcode___form__EVENT_OnAfterDelete = pcode___form__EVENT_OnAfterUpdate + 1;
static const int pcode___form__METHOD_Record = pcode___form__EVENT_OnAfterDelete + 1;
static const int pcode___form__METHOD_Record1 = pcode___form__METHOD_Record + 1;
static const int pcode___form__METHOD_SetRecord = pcode___form__METHOD_Record1 + 1;
static const int pcode___form__METHOD_Query = pcode___form__METHOD_SetRecord + 1;

static const int pcode___form__METHOD_Cut = pcode___form__METHOD_Query + 1;
static const int pcode___form__METHOD_Copy = pcode___form__METHOD_Cut + 1;
static const int pcode___form__METHOD_Paste = pcode___form__METHOD_Copy + 1;

static const int pcode___form__METHOD_First = pcode___form__METHOD_Paste + 1;
static const int pcode___form__METHOD_Next = pcode___form__METHOD_First + 1;
static const int pcode___form__METHOD_Previous = pcode___form__METHOD_Next + 1;
static const int pcode___form__METHOD_Last = pcode___form__METHOD_Previous + 1;
static const int pcode___form__METHOD_GoTo = pcode___form__METHOD_Last + 1;
static const int pcode___form__METHOD_Insert = pcode___form__METHOD_GoTo + 1;
static const int pcode___form__METHOD_Update = pcode___form__METHOD_Insert + 1;
static const int pcode___form__METHOD_Delete = pcode___form__METHOD_Update + 1;
static const int pcode___form__METHOD_AddNew = pcode___form__METHOD_Delete + 1;
static const int pcode___form__METHOD_Len = pcode___form__METHOD_AddNew + 1;
static const int pcode___form__METHOD_Pos = pcode___form__METHOD_Len + 1;
static const int pcode___form__METHOD_IsDirty = pcode___form__METHOD_Pos + 1;
static const int pcode___form__METHOD_Affected = pcode___form__METHOD_IsDirty + 1;
static const int pcode___form__METHOD_Cmd = pcode___form__METHOD_Affected + 1;
static const int pcode___form__METHOD_LastSQLError = pcode___form__METHOD_Cmd + 1;
static const int pcode___form__METHOD_Find = pcode___form__METHOD_LastSQLError + 1;
static const int pcode___form__METHOD_Find1 = pcode___form__METHOD_Find + 1;
static const int pcode___form__METHOD_Get = pcode___form__METHOD_Find1 + 1;
static const int pcode___form__METHOD_Requery = pcode___form__METHOD_Get + 1;
static const int pcode___form__METHOD_Seek = pcode___form__METHOD_Requery + 1;

static const int pcode___form__METHOD_kbrecordid = pcode___form__METHOD_Seek + 1;
static const int pcode___form__METHOD_kbrecordid1 = pcode___form__METHOD_kbrecordid + 1;

static const int pcode___form__METHOD_PrimaryKey = pcode___form__METHOD_kbrecordid1 + 1;
static const int pcode___form__METHOD_PrimaryKey1 = pcode___form__METHOD_PrimaryKey + 1;
static const int pcode___form__METHOD_PrimaryKeyName = pcode___form__METHOD_PrimaryKey1 + 1;
static const int pcode___form__METHOD_PrimaryKeyName1 = pcode___form__METHOD_PrimaryKeyName + 1;

static const int pcode___form__METHOD_ClearFilter = pcode___form__METHOD_PrimaryKeyName1 + 1;
static const int pcode___form__METHOD_SetFilter = pcode___form__METHOD_ClearFilter + 1;
static const int pcode___form__METHOD_AddFilter = pcode___form__METHOD_SetFilter + 1;
static const int pcode___form__METHOD_SortAsc = pcode___form__METHOD_AddFilter + 1;
static const int pcode___form__METHOD_SortDesc = pcode___form__METHOD_SortAsc + 1;

static const int pcode___form__SETPROPERTY_ScrollX = pcode___form__METHOD_SortDesc + 1;
static const int pcode___form__GETPROPERTY_ScrollX = pcode___form__SETPROPERTY_ScrollX + 1;

static const int pcode___form__SETPROPERTY_ScrollY = pcode___form__GETPROPERTY_ScrollX + 1;
static const int pcode___form__GETPROPERTY_ScrollY = pcode___form__SETPROPERTY_ScrollY + 1;

static const int pcode___form__SETPROPERTY_ScrollWidth = pcode___form__GETPROPERTY_ScrollY + 1;
static const int pcode___form__GETPROPERTY_ScrollWidth = pcode___form__SETPROPERTY_ScrollWidth + 1;

static const int pcode___form__SETPROPERTY_ScrollHeight = pcode___form__GETPROPERTY_ScrollWidth + 1;
static const int pcode___form__GETPROPERTY_ScrollHeight = pcode___form__SETPROPERTY_ScrollHeight + 1;



static const int pcode___form__SETPROPERTY_MultiPageHeight = pcode___form__GETPROPERTY_ScrollHeight + 1;
static const int pcode___form__GETPROPERTY_MultiPageHeight = pcode___form__SETPROPERTY_MultiPageHeight + 1;
static const int pcode___form__SETPROPERTY_MultiPageBorderLeft = pcode___form__GETPROPERTY_MultiPageHeight + 1;
static const int pcode___form__GETPROPERTY_MultiPageBorderLeft = pcode___form__SETPROPERTY_MultiPageBorderLeft + 1;
static const int pcode___form__SETPROPERTY_MultiPageBorderRight = pcode___form__GETPROPERTY_MultiPageBorderLeft + 1;
static const int pcode___form__GETPROPERTY_MultiPageBorderRight = pcode___form__SETPROPERTY_MultiPageBorderRight + 1;
static const int pcode___form__SETPROPERTY_MultiPageBorderTop = pcode___form__GETPROPERTY_MultiPageBorderRight + 1;
static const int pcode___form__GETPROPERTY_MultiPageBorderTop = pcode___form__SETPROPERTY_MultiPageBorderTop + 1;
static const int pcode___form__SETPROPERTY_MultiPageBorderBottom = pcode___form__GETPROPERTY_MultiPageBorderTop + 1;
static const int pcode___form__GETPROPERTY_MultiPageBorderBottom = pcode___form__SETPROPERTY_MultiPageBorderBottom + 1;



static const int pcode___form__SETPROPERTY_ScrollBar = pcode___form__GETPROPERTY_MultiPageBorderBottom + 1;
static const int pcode___form__GETPROPERTY_ScrollBar = pcode___form__SETPROPERTY_ScrollBar + 1;

static const int pcode___form__SETPROPERTY_Dock = pcode___form__GETPROPERTY_ScrollBar + 1;
static const int pcode___form__GETPROPERTY_Dock = pcode___form__SETPROPERTY_Dock + 1;

static const int pcode___form__SETPROPERTY_StopOnClose = pcode___form__GETPROPERTY_Dock + 1;
static const int pcode___form__GETPROPERTY_StopOnClose = pcode___form__SETPROPERTY_StopOnClose + 1;

static const int pcode___form__SETPROPERTY_OpenAtStartup = pcode___form__GETPROPERTY_StopOnClose + 1;
static const int pcode___form__GETPROPERTY_OpenAtStartup = pcode___form__SETPROPERTY_OpenAtStartup + 1;



static const int pcode___form__SETPROPERTY_DockTitleVisible = pcode___form__GETPROPERTY_OpenAtStartup + 1;
static const int pcode___form__GETPROPERTY_DockTitleVisible = pcode___form__SETPROPERTY_DockTitleVisible + 1;
static const int pcode___form__SETPROPERTY_DockOrder = pcode___form__GETPROPERTY_DockTitleVisible + 1;
static const int pcode___form__GETPROPERTY_DockOrder = pcode___form__SETPROPERTY_DockOrder + 1;
static const int pcode___form__SETPROPERTY_DockWidth = pcode___form__GETPROPERTY_DockOrder + 1;
static const int pcode___form__GETPROPERTY_DockWidth = pcode___form__SETPROPERTY_DockWidth + 1;
static const int pcode___form__SETPROPERTY_DockHeight = pcode___form__GETPROPERTY_DockWidth + 1;
static const int pcode___form__GETPROPERTY_DockHeight = pcode___form__SETPROPERTY_DockHeight + 1;

static const int pcode___form__SETPROPERTY_BorderTop = pcode___form__GETPROPERTY_DockHeight + 1;
static const int pcode___form__GETPROPERTY_BorderTop = pcode___form__SETPROPERTY_BorderTop + 1;
static const int pcode___form__SETPROPERTY_BorderBottom = pcode___form__GETPROPERTY_BorderTop + 1;
static const int pcode___form__GETPROPERTY_BorderBottom = pcode___form__SETPROPERTY_BorderBottom + 1;
static const int pcode___form__SETPROPERTY_BorderLeft = pcode___form__GETPROPERTY_BorderBottom + 1;
static const int pcode___form__GETPROPERTY_BorderLeft = pcode___form__SETPROPERTY_BorderLeft + 1;
static const int pcode___form__SETPROPERTY_BorderRight = pcode___form__GETPROPERTY_BorderLeft + 1;
static const int pcode___form__GETPROPERTY_BorderRight = pcode___form__SETPROPERTY_BorderRight + 1;

static const int pcode___form__SETPROPERTY_TableView = pcode___form__GETPROPERTY_BorderRight + 1;
static const int pcode___form__GETPROPERTY_TableView = pcode___form__SETPROPERTY_TableView + 1;
static const int pcode___form__SETPROPERTY_Flag = pcode___form__GETPROPERTY_TableView + 1;
static const int pcode___form__GETPROPERTY_Flag = pcode___form__SETPROPERTY_Flag + 1;
static const int pcode___form__SETPROPERTY_Icon = pcode___form__GETPROPERTY_Flag + 1;
static const int pcode___form__GETPROPERTY_Icon = pcode___form__SETPROPERTY_Icon + 1;
static const int pcode___form__SETPROPERTY_IconCaption = pcode___form__GETPROPERTY_Icon + 1;
static const int pcode___form__GETPROPERTY_IconCaption = pcode___form__SETPROPERTY_IconCaption + 1;

static const int pcode___form__SETPROPERTY_Caption = pcode___form__GETPROPERTY_IconCaption + 1;
static const int pcode___form__GETPROPERTY_Caption = pcode___form__SETPROPERTY_Caption + 1;

static const int pcode___form__SETPROPERTY_Value = pcode___form__GETPROPERTY_Caption + 1;
static const int pcode___form__GETPROPERTY_Value = pcode___form__SETPROPERTY_Value + 1;

static const int pcode___form__SETPROPERTY_OldValue = pcode___form__GETPROPERTY_Value + 1;
static const int pcode___form__GETPROPERTY_OldValue = pcode___form__SETPROPERTY_OldValue + 1;

static const int pcode___form__SETPROPERTY_Text = pcode___form__GETPROPERTY_OldValue + 1;
static const int pcode___form__GETPROPERTY_Text = pcode___form__SETPROPERTY_Text + 1;

static const int pcode___form__SETPROPERTY_Modal = pcode___form__GETPROPERTY_Text + 1;
static const int pcode___form__GETPROPERTY_Modal = pcode___form__SETPROPERTY_Modal + 1;
static const int pcode___form__METHOD_Move = pcode___form__GETPROPERTY_Modal + 1;
static const int pcode___form__METHOD_Resize = pcode___form__METHOD_Move + 1;
static const int pcode___form__METHOD_Show = pcode___form__METHOD_Resize + 1;
static const int pcode___form__METHOD_Hide = pcode___form__METHOD_Show + 1;
static const int pcode___form__METHOD_RepaintAlways = pcode___form__METHOD_Hide + 1;
static const int pcode___form__METHOD_Repaint = pcode___form__METHOD_RepaintAlways + 1;
static const int pcode___form__METHOD_Raise = pcode___form__METHOD_Repaint + 1;
static const int pcode___form__METHOD_Lower = pcode___form__METHOD_Raise + 1;
static const int pcode___form__METHOD_Close = pcode___form__METHOD_Lower + 1;
static const int pcode___form__METHOD_Open = pcode___form__METHOD_Close + 1;

static const int pcode___form__METHOD_Open1 = pcode___form__METHOD_Open + 1;
static const int pcode___form__METHOD_Open2 = pcode___form__METHOD_Open1 + 1;
static const int pcode___form__METHOD_OpenFullScreen = pcode___form__METHOD_Open2 + 1;
static const int pcode___form__METHOD_OpenCentered = pcode___form__METHOD_OpenFullScreen + 1;



static const int pcode___form__METHOD_OpenHidden = pcode___form__METHOD_OpenCentered + 1;
static const int pcode___form__METHOD_SetFocus = pcode___form__METHOD_OpenHidden + 1;
static const int pcode___form__SETPROPERTY_Name = pcode___form__METHOD_SetFocus + 1;
static const int pcode___form__GETPROPERTY_Name = pcode___form__SETPROPERTY_Name + 1;
static const int pcode___form__SETPROPERTY_Group = pcode___form__GETPROPERTY_Name + 1;
static const int pcode___form__GETPROPERTY_Group = pcode___form__SETPROPERTY_Group + 1;
static const int pcode___form__SETPROPERTY_Background = pcode___form__GETPROPERTY_Group + 1;
static const int pcode___form__GETPROPERTY_Background = pcode___form__SETPROPERTY_Background + 1;
static const int pcode___form__SETPROPERTY_X = pcode___form__GETPROPERTY_Background + 1;
static const int pcode___form__GETPROPERTY_X = pcode___form__SETPROPERTY_X + 1;
static const int pcode___form__SETPROPERTY_Y = pcode___form__GETPROPERTY_X + 1;
static const int pcode___form__GETPROPERTY_Y = pcode___form__SETPROPERTY_Y + 1;
static const int pcode___form__SETPROPERTY_Width = pcode___form__GETPROPERTY_Y + 1;
static const int pcode___form__GETPROPERTY_Width = pcode___form__SETPROPERTY_Width + 1;
static const int pcode___form__SETPROPERTY_Height = pcode___form__GETPROPERTY_Width + 1;
static const int pcode___form__GETPROPERTY_Height = pcode___form__SETPROPERTY_Height + 1;
static const int pcode___form__GETPROPERTY_GlobalX = pcode___form__GETPROPERTY_Height + 1;
static const int pcode___form__GETPROPERTY_GlobalY = pcode___form__GETPROPERTY_GlobalX + 1;
static const int pcode___form__GETPROPERTY_OldX = pcode___form__GETPROPERTY_GlobalY + 1;
static const int pcode___form__GETPROPERTY_OldY = pcode___form__GETPROPERTY_OldX + 1;
static const int pcode___form__GETPROPERTY_OldWidth = pcode___form__GETPROPERTY_OldY + 1;
static const int pcode___form__GETPROPERTY_OldHeight = pcode___form__GETPROPERTY_OldWidth + 1;
static const int pcode___form__SETPROPERTY_MinimumWidth = pcode___form__GETPROPERTY_OldHeight + 1;
static const int pcode___form__GETPROPERTY_MinimumWidth = pcode___form__SETPROPERTY_MinimumWidth + 1;
static const int pcode___form__SETPROPERTY_MinimumHeight = pcode___form__GETPROPERTY_MinimumWidth + 1;
static const int pcode___form__GETPROPERTY_MinimumHeight = pcode___form__SETPROPERTY_MinimumHeight + 1;
static const int pcode___form__SETPROPERTY_MaximumWidth = pcode___form__GETPROPERTY_MinimumHeight + 1;
static const int pcode___form__GETPROPERTY_MaximumWidth = pcode___form__SETPROPERTY_MaximumWidth + 1;
static const int pcode___form__SETPROPERTY_MaximumHeight = pcode___form__GETPROPERTY_MaximumWidth + 1;
static const int pcode___form__GETPROPERTY_MaximumHeight = pcode___form__SETPROPERTY_MaximumHeight + 1;
static const int pcode___form__SETPROPERTY_Tag = pcode___form__GETPROPERTY_MaximumHeight + 1;
static const int pcode___form__GETPROPERTY_Tag = pcode___form__SETPROPERTY_Tag + 1;
static const int pcode___form__SETPROPERTY_CSV = pcode___form__GETPROPERTY_Tag + 1;
static const int pcode___form__GETPROPERTY_CSV = pcode___form__SETPROPERTY_CSV + 1;
static const int pcode___form__SETPROPERTY_ParentForm = pcode___form__GETPROPERTY_CSV + 1;
static const int pcode___form__GETPROPERTY_ParentForm = pcode___form__SETPROPERTY_ParentForm + 1;
static const int pcode___form__SETPROPERTY_ParentControl = pcode___form__GETPROPERTY_ParentForm + 1;
static const int pcode___form__GETPROPERTY_ParentControl = pcode___form__SETPROPERTY_ParentControl + 1;
static const int pcode___form__SETPROPERTY_DragDrop = pcode___form__GETPROPERTY_ParentControl + 1;
static const int pcode___form__GETPROPERTY_ParentControl1 = pcode___form__SETPROPERTY_DragDrop + 1;
static const int pcode___form__SETPROPERTY_ControlType = pcode___form__GETPROPERTY_ParentControl1 + 1;
static const int pcode___form__GETPROPERTY_ControlType = pcode___form__SETPROPERTY_ControlType + 1;
static const int pcode___form__SETPROPERTY_Focus = pcode___form__GETPROPERTY_ControlType + 1;
static const int pcode___form__GETPROPERTY_Focus = pcode___form__SETPROPERTY_Focus + 1;
static const int pcode___form__SETPROPERTY_FocusPolicy = pcode___form__GETPROPERTY_Focus + 1;
static const int pcode___form__GETPROPERTY_FocusPolicy = pcode___form__SETPROPERTY_FocusPolicy + 1;
static const int pcode___form__SETPROPERTY_FocusProxy = pcode___form__GETPROPERTY_FocusPolicy + 1;
static const int pcode___form__GETPROPERTY_FocusProxy = pcode___form__SETPROPERTY_FocusProxy + 1;
static const int pcode___form__SETPROPERTY_FocusOrder = pcode___form__GETPROPERTY_FocusProxy + 1;
static const int pcode___form__GETPROPERTY_FocusOrder = pcode___form__SETPROPERTY_FocusOrder + 1;
static const int pcode___form__SETPROPERTY_Cursor = pcode___form__GETPROPERTY_FocusOrder + 1;
static const int pcode___form__GETPROPERTY_Cursor = pcode___form__SETPROPERTY_Cursor + 1;
static const int pcode___form__SETPROPERTY_FontName = pcode___form__GETPROPERTY_Cursor + 1;
static const int pcode___form__GETPROPERTY_FontName = pcode___form__SETPROPERTY_FontName + 1;
static const int pcode___form__SETPROPERTY_FontSize = pcode___form__GETPROPERTY_FontName + 1;
static const int pcode___form__GETPROPERTY_FontSize = pcode___form__SETPROPERTY_FontSize + 1;
static const int pcode___form__SETPROPERTY_FontItalic = pcode___form__GETPROPERTY_FontSize + 1;
static const int pcode___form__GETPROPERTY_FontItalic = pcode___form__SETPROPERTY_FontItalic + 1;
static const int pcode___form__SETPROPERTY_FontBold = pcode___form__GETPROPERTY_FontItalic + 1;
static const int pcode___form__GETPROPERTY_FontBold = pcode___form__SETPROPERTY_FontBold + 1;
static const int pcode___form__SETPROPERTY_FontUnderline = pcode___form__GETPROPERTY_FontBold + 1;
static const int pcode___form__GETPROPERTY_FontUnderline = pcode___form__SETPROPERTY_FontUnderline + 1;
static const int pcode___form__SETPROPERTY_FontColor = pcode___form__GETPROPERTY_FontUnderline + 1;
static const int pcode___form__GETPROPERTY_FontColor = pcode___form__SETPROPERTY_FontColor + 1;
static const int pcode___form__SETPROPERTY_Enabled = pcode___form__GETPROPERTY_FontColor + 1;
static const int pcode___form__GETPROPERTY_Enabled = pcode___form__SETPROPERTY_Enabled + 1;
static const int pcode___form__SETPROPERTY_Visible = pcode___form__GETPROPERTY_Enabled + 1;
static const int pcode___form__GETPROPERTY_Visible = pcode___form__SETPROPERTY_Visible + 1;
static const int pcode___form__SETPROPERTY_StatusTip = pcode___form__GETPROPERTY_Visible + 1;
static const int pcode___form__GETPROPERTY_StatusTip = pcode___form__SETPROPERTY_StatusTip + 1;
static const int pcode___form__SETPROPERTY_ToolTip = pcode___form__GETPROPERTY_StatusTip + 1;
static const int pcode___form__GETPROPERTY_ToolTip = pcode___form__SETPROPERTY_ToolTip + 1;
static const int pcode___form__SETPROPERTY_StyleSheet = pcode___form__GETPROPERTY_ToolTip + 1;
static const int pcode___form__GETPROPERTY_StyleSheet = pcode___form__SETPROPERTY_StyleSheet + 1;
static const int pcode___form__SETPROPERTY_WhatsThis = pcode___form__GETPROPERTY_StyleSheet + 1;
static const int pcode___form__GETPROPERTY_WhatsThis = pcode___form__SETPROPERTY_WhatsThis + 1;
static const int pcode___form__SETPROPERTY_TimerInterval = pcode___form__GETPROPERTY_WhatsThis + 1;
static const int pcode___form__GETPROPERTY_TimerInterval = pcode___form__SETPROPERTY_TimerInterval + 1;
static const int pcode___form__SETPROPERTY_Opacity = pcode___form__GETPROPERTY_TimerInterval + 1;
static const int pcode___form__GETPROPERTY_Opacity = pcode___form__SETPROPERTY_Opacity + 1;
static const int pcode___form__SETPROPERTY_BoxIndex = pcode___form__GETPROPERTY_Opacity + 1;
static const int pcode___form__GETPROPERTY_BoxIndex = pcode___form__SETPROPERTY_BoxIndex + 1;
static const int pcode___form__SETPROPERTY_SplitIndex = pcode___form__GETPROPERTY_BoxIndex + 1;
static const int pcode___form__GETPROPERTY_SplitIndex = pcode___form__SETPROPERTY_SplitIndex + 1;
static const int pcode___form__SETPROPERTY_TabIndex = pcode___form__GETPROPERTY_SplitIndex + 1;
static const int pcode___form__GETPROPERTY_TabIndex = pcode___form__SETPROPERTY_TabIndex + 1;
static const int pcode___form__SETPROPERTY_BoxX = pcode___form__GETPROPERTY_TabIndex + 1;
static const int pcode___form__GETPROPERTY_BoxX = pcode___form__SETPROPERTY_BoxX + 1;
static const int pcode___form__SETPROPERTY_BoxY = pcode___form__GETPROPERTY_BoxX + 1;
static const int pcode___form__GETPROPERTY_BoxY = pcode___form__SETPROPERTY_BoxY + 1;
static const int pcode___form__SETPROPERTY_ParentIndex = pcode___form__GETPROPERTY_BoxY + 1;
static const int pcode___form__GETPROPERTY_ParentIndex = pcode___form__SETPROPERTY_ParentIndex + 1;
static const int pcode___form__SETPROPERTY_ControlType1 = pcode___form__GETPROPERTY_ParentIndex + 1;
static const int pcode___form__GETPROPERTY_ControlType1 = pcode___form__SETPROPERTY_ControlType1 + 1;
static const int pcode___form__SETPROPERTY_SQLName = pcode___form__GETPROPERTY_ControlType1 + 1;
static const int pcode___form__GETPROPERTY_SQLName = pcode___form__SETPROPERTY_SQLName + 1;
static const int pcode___form__SETPROPERTY_SQLControls = pcode___form__GETPROPERTY_SQLName + 1;
static const int pcode___form__GETPROPERTY_SQLControls = pcode___form__SETPROPERTY_SQLControls + 1;
static const int pcode___form__SETPROPERTY_SQLInsert = pcode___form__GETPROPERTY_SQLControls + 1;
static const int pcode___form__GETPROPERTY_SQLInsert = pcode___form__SETPROPERTY_SQLInsert + 1;
static const int pcode___form__SETPROPERTY_SQLUpdate = pcode___form__GETPROPERTY_SQLInsert + 1;
static const int pcode___form__GETPROPERTY_SQLUpdate = pcode___form__SETPROPERTY_SQLUpdate + 1;
static const int pcode___form__SETPROPERTY_SQLDelete = pcode___form__GETPROPERTY_SQLUpdate + 1;
static const int pcode___form__GETPROPERTY_SQLDelete = pcode___form__SETPROPERTY_SQLDelete + 1;
static const int pcode___form__EVENT_OnOpen = pcode___form__GETPROPERTY_SQLDelete + 1;
static const int pcode___form__EVENT_OnClose = pcode___form__EVENT_OnOpen + 1;
static const int pcode___form__EVENT_OnContextMenu = pcode___form__EVENT_OnClose + 1;
static const int pcode___form__EVENT_OnDragEnter = pcode___form__EVENT_OnContextMenu + 1;
static const int pcode___form__EVENT_OnDragExit = pcode___form__EVENT_OnDragEnter + 1;
static const int pcode___form__EVENT_OnDragMove = pcode___form__EVENT_OnDragExit + 1;
static const int pcode___form__EVENT_OnDrop = pcode___form__EVENT_OnDragMove + 1;
static const int pcode___form__EVENT_OnEnter = pcode___form__EVENT_OnDrop + 1;
static const int pcode___form__EVENT_OnGotFocus = pcode___form__EVENT_OnEnter + 1;
static const int pcode___form__EVENT_OnLostFocus = pcode___form__EVENT_OnGotFocus + 1;
static const int pcode___form__EVENT_OnHide = pcode___form__EVENT_OnLostFocus + 1;
static const int pcode___form__EVENT_OnKeyDown = pcode___form__EVENT_OnHide + 1;
static const int pcode___form__EVENT_OnKeyUp = pcode___form__EVENT_OnKeyDown + 1;
static const int pcode___form__EVENT_OnKeyPress = pcode___form__EVENT_OnKeyUp + 1;
static const int pcode___form__EVENT_OnExit = pcode___form__EVENT_OnKeyPress + 1;
static const int pcode___form__EVENT_OnDblClick = pcode___form__EVENT_OnExit + 1;
static const int pcode___form__EVENT_OnClick = pcode___form__EVENT_OnDblClick + 1;
static const int pcode___form__EVENT_OnMouseMove = pcode___form__EVENT_OnClick + 1;
static const int pcode___form__EVENT_OnMouseDown = pcode___form__EVENT_OnMouseMove + 1;
static const int pcode___form__EVENT_OnMouseUp = pcode___form__EVENT_OnMouseDown + 1;
static const int pcode___form__EVENT_OnMove = pcode___form__EVENT_OnMouseUp + 1;
static const int pcode___form__EVENT_OnPaint = pcode___form__EVENT_OnMove + 1;
static const int pcode___form__EVENT_OnResize = pcode___form__EVENT_OnPaint + 1;
static const int pcode___form__EVENT_OnShow = pcode___form__EVENT_OnResize + 1;
static const int pcode___form__EVENT_OnMouseWheel = pcode___form__EVENT_OnShow + 1;
static const int pcode___form__EVENT_OnTimer = pcode___form__EVENT_OnMouseWheel + 1;
static const int pcode___form__EVENT_OnPrint = pcode___form__EVENT_OnTimer + 1;
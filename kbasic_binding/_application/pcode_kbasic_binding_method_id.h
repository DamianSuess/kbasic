static const int pcode___application___application = pcode___application * SPACE;

static const int pcode___application__METHOD_PlaySound = pcode___application___application + 1;
static const int pcode___application__METHOD_PlayMovie = pcode___application__METHOD_PlaySound + 1;
static const int pcode___application__METHOD_LoadURLAsBinary = pcode___application__METHOD_PlayMovie + 1;

static const int pcode___application__METHOD_AvailableLanguages = pcode___application__METHOD_LoadURLAsBinary + 1;
static const int pcode___application__METHOD_SetLanguage = pcode___application__METHOD_AvailableLanguages + 1;
static const int pcode___application__METHOD_SetCountry = pcode___application__METHOD_SetLanguage + 1;

static const int pcode___application__METHOD_SetViewMode = pcode___application__METHOD_SetCountry + 1;
static const int pcode___application__METHOD_ViewMode = pcode___application__METHOD_SetViewMode + 1;

static const int pcode___application__PROPERTYSET_X = pcode___application__METHOD_ViewMode + 1;
static const int pcode___application__PROPERTYGET_X = pcode___application__PROPERTYSET_X + 1;
static const int pcode___application__PROPERTYSET_Y = pcode___application__PROPERTYGET_X + 1;
static const int pcode___application__PROPERTYGET_Y = pcode___application__PROPERTYSET_Y + 1;
static const int pcode___application__PROPERTYSET_Width = pcode___application__PROPERTYGET_Y + 1;
static const int pcode___application__PROPERTYGET_Width = pcode___application__PROPERTYSET_Width + 1;
static const int pcode___application__PROPERTYSET_Height = pcode___application__PROPERTYGET_Width + 1;
static const int pcode___application__PROPERTYGET_Height = pcode___application__PROPERTYSET_Height + 1;

static const int pcode___application__METHOD_IsMimeTypeAvailable = pcode___application__PROPERTYGET_Height + 1;
static const int pcode___application__METHOD_AvailableMimeTypes = pcode___application__METHOD_IsMimeTypeAvailable + 1;

static const int pcode___application__METHOD_Arguments = pcode___application__METHOD_AvailableMimeTypes + 1;
static const int pcode___application__METHOD_IsScrollBarsEnabled = pcode___application__METHOD_Arguments + 1;

static const int pcode___application__METHOD_LoadProjectFileAsString = pcode___application__METHOD_IsScrollBarsEnabled + 1;
static const int pcode___application__METHOD_LoadProjectFileAsBinary = pcode___application__METHOD_LoadProjectFileAsString + 1;
static const int pcode___application__METHOD_LoadFileAsString = pcode___application__METHOD_LoadProjectFileAsBinary + 1;
static const int pcode___application__METHOD_Move = pcode___application__METHOD_LoadFileAsString + 1;
static const int pcode___application__METHOD_Resize = pcode___application__METHOD_Move + 1;
static const int pcode___application__METHOD_Close = pcode___application__METHOD_Resize + 1;
static const int pcode___application__METHOD_QtVersion = pcode___application__METHOD_Close + 1;
static const int pcode___application__METHOD_OperatingSystemName = pcode___application__METHOD_QtVersion + 1;
static const int pcode___application__METHOD_SetDefaultIcon = pcode___application__METHOD_OperatingSystemName + 1;
static const int pcode___application__METHOD_ExternalOpenFile = pcode___application__METHOD_SetDefaultIcon + 1;
static const int pcode___application__METHOD_CloseAllWindows = pcode___application__METHOD_ExternalOpenFile + 1;
static const int pcode___application__METHOD_IsLayoutDirection = pcode___application__METHOD_CloseAllWindows + 1;
static const int pcode___application__METHOD_CurrentForm = pcode___application__METHOD_IsLayoutDirection + 1;
static const int pcode___application__METHOD_FocusControl = pcode___application__METHOD_CurrentForm + 1;
static const int pcode___application__METHOD_SetStyle = pcode___application__METHOD_FocusControl + 1;

static const int pcode___application__METHOD_ShowFullScreen = pcode___application__METHOD_SetStyle + 1;
static const int pcode___application__METHOD_ShowMaximized = pcode___application__METHOD_ShowFullScreen + 1;
static const int pcode___application__METHOD_ShowMinimized = pcode___application__METHOD_ShowMaximized + 1;
static const int pcode___application__METHOD_ShowNormal = pcode___application__METHOD_ShowMinimized + 1;
static const int pcode___application__METHOD_SetSQLDriver = pcode___application__METHOD_ShowNormal + 1;
static const int pcode___application__METHOD_SetSQLHost = pcode___application__METHOD_SetSQLDriver + 1;
static const int pcode___application__METHOD_SetSQLDatabase = pcode___application__METHOD_SetSQLHost + 1;
static const int pcode___application__METHOD_SetSQLUser = pcode___application__METHOD_SetSQLDatabase + 1;
static const int pcode___application__METHOD_SetSQLPassword = pcode___application__METHOD_SetSQLUser + 1;
static const int pcode___application__METHOD_MsgBox = pcode___application__METHOD_SetSQLPassword + 1;
static const int pcode___application__METHOD_SetCaption = pcode___application__METHOD_MsgBox + 1;
static const int pcode___application__METHOD_SetIcon = pcode___application__METHOD_SetCaption + 1;
static const int pcode___application__METHOD_SetClipboardText = pcode___application__METHOD_SetIcon + 1;
static const int pcode___application__METHOD_ClipboardText = pcode___application__METHOD_SetClipboardText + 1;
static const int pcode___application__METHOD_Path = pcode___application__METHOD_ClipboardText + 1;
static const int pcode___application__METHOD_DirectoryName = pcode___application__METHOD_Path + 1;
static const int pcode___application__METHOD_FileName = pcode___application__METHOD_DirectoryName + 1;
static const int pcode___application__METHOD_ArgumentsAsString = pcode___application__METHOD_FileName + 1;
static const int pcode___application__METHOD_Run = pcode___application__METHOD_ArgumentsAsString + 1;
static const int pcode___application__METHOD_Stop = pcode___application__METHOD_Run + 1;
static const int pcode___application__METHOD_SetWaitCursor = pcode___application__METHOD_Stop + 1;
static const int pcode___application__METHOD_UnsetWaitCursor = pcode___application__METHOD_SetWaitCursor + 1;
static const int pcode___application__METHOD_AddLanguageTranslatorFile = pcode___application__METHOD_UnsetWaitCursor + 1;
static const int pcode___application__METHOD_DoEvents = pcode___application__METHOD_AddLanguageTranslatorFile + 1;
static const int pcode___application__METHOD_SetStyleSheet = pcode___application__METHOD_DoEvents + 1;
static const int pcode___application__METHOD_SetLayoutDirection = pcode___application__METHOD_SetStyleSheet + 1;
static const int pcode___application__METHOD_ScreenWidth = pcode___application__METHOD_SetLayoutDirection + 1;
static const int pcode___application__METHOD_ScreenHeight = pcode___application__METHOD_ScreenWidth + 1;
static const int pcode___application__METHOD_IsSoundAvailable = pcode___application__METHOD_ScreenHeight + 1;
static const int pcode___application__METHOD_LoadExternalBrowserWithHTML = pcode___application__METHOD_IsSoundAvailable + 1;

static const int pcode___application__METHOD_SetFocusNextForm = pcode___application__METHOD_LoadExternalBrowserWithHTML + 1;
static const int pcode___application__METHOD_SetFocusPreviousForm = pcode___application__METHOD_SetFocusNextForm + 1;
static const int pcode___application__METHOD_ArrangeIcons = pcode___application__METHOD_SetFocusPreviousForm + 1;
static const int pcode___application__METHOD_Cascade = pcode___application__METHOD_ArrangeIcons + 1;
static const int pcode___application__METHOD_CloseActiveForm = pcode___application__METHOD_Cascade + 1;
static const int pcode___application__METHOD_CloseAllapplication = pcode___application__METHOD_CloseActiveForm + 1;
static const int pcode___application__METHOD_Tile = pcode___application__METHOD_CloseAllapplication + 1;
static const int pcode___application__METHOD_SetScrollBarsEnabled = pcode___application__METHOD_Tile + 1;
static const int pcode___application__METHOD_TakeScreenShot = pcode___application__METHOD_SetScrollBarsEnabled + 1;
static const int pcode___application__METHOD_StandardIcon = pcode___application__METHOD_TakeScreenShot + 1;
static const int pcode___application__METHOD_AvailableFontNames = pcode___application__METHOD_StandardIcon + 1;
static const int pcode___application__METHOD_ProcessId = pcode___application__METHOD_AvailableFontNames + 1;
static const int pcode___application__METHOD_PrintHtml = pcode___application__METHOD_ProcessId + 1;
static const int pcode___application__METHOD_PrintHtmlAsPdf = pcode___application__METHOD_PrintHtml + 1;

static const int pcode___application__METHOD_QtException = pcode___application__METHOD_PrintHtmlAsPdf + 1;
static const int pcode___application__METHOD_ClearQtException = pcode___application__METHOD_QtException + 1;

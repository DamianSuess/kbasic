static const int pcode___mainwindow___mainwindow = pcode___mainwindow * SPACE;

static const int pcode___mainwindow__METHOD_SetVisible = pcode___mainwindow___mainwindow + 1;
static const int pcode___mainwindow__METHOD_IsVisible = pcode___mainwindow__METHOD_SetVisible + 1;

static const int pcode___mainwindow__METHOD_SetViewMode = pcode___mainwindow__METHOD_IsVisible + 1;
static const int pcode___mainwindow__METHOD_ViewMode = pcode___mainwindow__METHOD_SetViewMode + 1;

static const int pcode___mainwindow__PROPERTYSET_X = pcode___mainwindow__METHOD_ViewMode + 1;
static const int pcode___mainwindow__PROPERTYGET_X = pcode___mainwindow__PROPERTYSET_X + 1;
static const int pcode___mainwindow__PROPERTYSET_Y = pcode___mainwindow__PROPERTYGET_X + 1;
static const int pcode___mainwindow__PROPERTYGET_Y = pcode___mainwindow__PROPERTYSET_Y + 1;
static const int pcode___mainwindow__PROPERTYSET_Width = pcode___mainwindow__PROPERTYGET_Y + 1;
static const int pcode___mainwindow__PROPERTYGET_Width = pcode___mainwindow__PROPERTYSET_Width + 1;
static const int pcode___mainwindow__PROPERTYSET_Height = pcode___mainwindow__PROPERTYGET_Width + 1;
static const int pcode___mainwindow__PROPERTYGET_Height = pcode___mainwindow__PROPERTYSET_Height + 1;

static const int pcode___mainwindow__METHOD_IsScrollBarsEnabled = pcode___mainwindow__PROPERTYGET_Height + 1;

static const int pcode___mainwindow__METHOD_Move = pcode___mainwindow__METHOD_IsScrollBarsEnabled + 1;
static const int pcode___mainwindow__METHOD_Resize = pcode___mainwindow__METHOD_Move + 1;
static const int pcode___mainwindow__METHOD_Close = pcode___mainwindow__METHOD_Resize + 1;
static const int pcode___mainwindow__METHOD_CloseAllWindows = pcode___mainwindow__METHOD_Close + 1;

static const int pcode___mainwindow__METHOD_ShowFullScreen = pcode___mainwindow__METHOD_CloseAllWindows + 1;
static const int pcode___mainwindow__METHOD_ShowMaximized = pcode___mainwindow__METHOD_ShowFullScreen + 1;
static const int pcode___mainwindow__METHOD_ShowMinimized = pcode___mainwindow__METHOD_ShowMaximized + 1;
static const int pcode___mainwindow__METHOD_ShowNormal = pcode___mainwindow__METHOD_ShowMinimized + 1;

static const int pcode___mainwindow__METHOD_SetFocusNextForm = pcode___mainwindow__METHOD_ShowNormal + 1;
static const int pcode___mainwindow__METHOD_SetFocusPreviousForm = pcode___mainwindow__METHOD_SetFocusNextForm + 1;
static const int pcode___mainwindow__METHOD_Cascade = pcode___mainwindow__METHOD_SetFocusPreviousForm + 1;
static const int pcode___mainwindow__METHOD_CloseActiveForm = pcode___mainwindow__METHOD_Cascade + 1;
static const int pcode___mainwindow__METHOD_CloseAllapplication = pcode___mainwindow__METHOD_CloseActiveForm + 1;
static const int pcode___mainwindow__METHOD_Tile = pcode___mainwindow__METHOD_CloseAllapplication + 1;
static const int pcode___mainwindow__METHOD_SetScrollBarsEnabled = pcode___mainwindow__METHOD_Tile + 1;
static const int pcode___mainwindow__METHOD_SetCaption = pcode___mainwindow__METHOD_SetScrollBarsEnabled + 1;
static const int pcode___mainwindow__METHOD_SetIcon = pcode___mainwindow__METHOD_SetCaption + 1;

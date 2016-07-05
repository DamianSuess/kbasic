


int nTimerId;

void constructor(_form *f, QWidget *parent)
{
  constructor(f, parent, true, 0);
}

void constructor2(_form *f, QWidget *parent)
{
  constructor(f, parent, false, 4);
}

void destructor()
{
  if (movie) delete movie; if (moviea) delete moviea; if (movieb) delete movieb;
  if (cursoranimation_movie) delete cursoranimation_movie; if (cursoranimation_moviea) delete cursoranimation_moviea; if (cursoranimation_movieb) delete cursoranimation_movieb;
}

void constructor(_form *f, QWidget *parent, bool bResize, int nWidth)
{
  
  bBackgroundStyle = false;

  my_form = f;

  nTimerId = 0;
  movie = 0; moviea = 0; movieb = 0;
  cursoranimation_movie = 0; cursoranimation_moviea = 0; cursoranimation_movieb = 0;  

  nSingleShot = 0;

  bForm = my_form ? my_form_isForm(my_form) : true;
  
#ifdef _MENUBARITEM
#else
  #ifdef _TOOLBARITEM
  #else
  setHidden(true);
  #endif
#endif  

  addProperty("Name", pt_qstring);
  addProperty("Layout", pt_qstring);
  addProperty("ControlType", pt_qstring);

  addProperty("X", pt_integer);
  addProperty("Y", pt_integer);
  addProperty("Width", pt_integer);
  addProperty("Height", pt_integer);

  addProperty("LoadedX", pt_integer);
  addProperty("LoadedY", pt_integer);
  addProperty("LoadedWidth", pt_integer);
  addProperty("LoadedHeight", pt_integer);
  addProperty("MultiPage", pt_integer);


  addProperty("OldX", pt_integer);
  addProperty("GlobalX", pt_integer);
  addProperty("OldY", pt_integer);
  addProperty("GlobalY", pt_integer);
  addProperty("OldWidth", pt_integer);
  addProperty("OldHeight", pt_integer);
#ifdef _FORM
  addProperty("Opacity", pt_integer);
#endif

#if defined(_CHILDCONTROL)
#elif defined(_VSPLIT)
#elif defined(_HSPLIT)
#elif defined(_VHBOX)
#elif defined(_VBOX)
#elif defined(_HBOX)
#elif defined(_TAB)
    addProperty("DrawOnPaint", pt_boolean);
    SETPROPERTY_DrawOnPaint(true);
#elif defined(_HIDDEN)
#elif defined(_TIMER)
    addProperty("DrawOnPaint", pt_boolean);
    SETPROPERTY_DrawOnPaint(true);
#elif defined(_UDPSOCKET)
    addProperty("DrawOnPaint", pt_boolean);
    SETPROPERTY_DrawOnPaint(true);
#elif defined(_SERIALPORT)
    addProperty("DrawOnPaint", pt_boolean);
    SETPROPERTY_DrawOnPaint(true);
#elif defined(_SOUND)
    addProperty("DrawOnPaint", pt_boolean);
    SETPROPERTY_DrawOnPaint(true);
#elif defined(_HEADER)
#elif defined(_FOOTER)
#else
  if (bForm){
    addProperty("Group", pt_qstring);  
    addProperty("Palette", pt_qstring);
    addProperty("Mask", pt_qstring);  
    addProperty("MouseTracking", pt_boolean);    
    addProperty("DrawOnPaint", pt_boolean);
    SETPROPERTY_DrawOnPaint(true);
  }

#endif

#if defined(_CHILDCONTROL)
#elif defined(_HIDDEN)
#elif defined(_TIMER)
#elif defined(_UDPSOCKET)
#elif defined(_SERIALPORT)
#elif defined(_SOUND)
#elif defined(_HEADER)
#elif defined(_FOOTER)
#else
  addProperty("Background", pt_qstring);
  addProperty("BackgroundStyle", pt_qstring);
#endif  


#if defined(_HIDDEN)
#elif defined(_TIMER)
#elif defined(_UDPSOCKET)
#elif defined(_SERIALPORT)
#elif defined(_HEADER)
#elif defined(_FOOTER)
#else
  if (bForm){
    addProperty("MinimumWidth", pt_integer);
    addProperty("MinimumHeight", pt_integer);
    addProperty("MaximumWidth", pt_integer);
    addProperty("MaximumHeight", pt_integer);
  }
#endif
  addProperty("Tag", pt_qstring);
/*
#if defined(_CHILDCONTROL)
#elif defined(_CUSTOMCONTROL)
#elif defined(_HIDDEN)
#elif defined(_SCROLLBOX)
#elif defined(_TAB)
#elif defined(_VSPLIT)
#elif defined(_HSPLIT)
#elif defined(_VHBOX)
#elif defined(_VBOX)
#elif defined(_HBOX)
#elif defined(_BOX)
#elif defined(_HIDDEN)
#elif defined(_TIMER)
#else
  addProperty("SQL", pt_qstring);
#endif
*/
#ifdef _FRAME
#elif defined(_HIDDEN)
#elif defined(_CHILDCONTROL)
#elif defined(_VSPLIT)
#elif defined(_HSPLIT)
#elif defined(_VHBOX)
#elif defined(_VBOX)
#elif defined(_HBOX)
#elif defined(_BOX)
#elif defined(_RESIZEBOX)
#elif defined(_SCROLLBOX)
#elif defined(_TIMER)
#elif defined(_UDPSOCKET)
#elif defined(_SERIALPORT)
#elif defined(_HEADER)
#elif defined(_FOOTER)
#else
  if (bForm){
    addProperty("DragDrop", pt_boolean);
    addProperty("FocusPolicy", pt_qstring);
    addProperty("FocusProxy", pt_qstring);
    addProperty("FocusOrder", pt_integer);
  }
#endif  

#if defined(_MENUBARITEM)
#elif defined(_TOOLBARITEM)
#else
  addProperty("TimerInterval", pt_integer);
#endif 

#if defined(_HIDDEN)
#elif defined(_HEADER)
#elif defined(_FOOTER)
#elif defined(_CHILDCONTROL)
#elif defined(_VSPLIT)
#elif defined(_HSPLIT)
#elif defined(_VHBOX)
#elif defined(_VBOX)
#elif defined(_HBOX)
//#elif defined(_SCROLLBOX)
//  addProperty("Visible", pt_boolean);
#elif defined(_BOX)
  addProperty("Visible", pt_boolean);
  if (bForm) addProperty("Cursor", pt_qstring);
  if (bForm) addProperty("CursorAnimation", pt_qstring);
#elif defined(_RESIZEBOX)
  addProperty("Visible", pt_boolean);
  if (bForm) addProperty("Cursor", pt_qstring);
  if (bForm) addProperty("CursorAnimation", pt_qstring);
#elif defined(_TIMER)
  addProperty("Enabled", pt_boolean);
#elif defined(_UDPSOCKET)
  addProperty("Enabled", pt_boolean);
#elif defined(_SERIALPORT)
  addProperty("Enabled", pt_boolean);
#else

  if (bForm) addProperty("Cursor", pt_qstring);
  if (bForm) addProperty("CursorAnimation", pt_qstring);
  #if defined(_IMAGE)
  #elif defined(_BOX)
  #elif defined(_RESIZEBOX)
  #else
  addProperty("FontName", pt_qstring);
  addProperty("FontSize", pt_integer);
  addProperty("FontItalic", pt_boolean);
  addProperty("FontBold", pt_boolean);
  addProperty("FontUnderline", pt_boolean);
  addProperty("FontColor", pt_qstring);
  #endif
  /*
  #if defined(_FORM)
  #elif defined(_REPORT)
  #else*/
  if (bForm) addProperty("Enabled", pt_boolean);
 // #endif

  addProperty("Visible", pt_boolean);
#endif
  addProperty("ParentForm", pt_qstring);
  addProperty("ParentControl", pt_qstring);

  addProperty("BoxIndex", pt_integer);
  addProperty("BoxX", pt_integer);
  addProperty("BoxY", pt_integer);
  addProperty("SplitIndex", pt_integer);
  addProperty("TabIndex", pt_integer);
  addProperty("ParentIndex", pt_integer);

#ifdef _LABEL
  if (bForm) addProperty("Scale", pt_boolean);
#endif

#if defined(_HIDDEN)
#elif defined(_CHILDCONTROL)
#elif defined(_VSPLIT)
#elif defined(_HSPLIT)
#elif defined(_VHBOX)
#elif defined(_VBOX)
#elif defined(_HBOX)
#elif defined(_TIMER)
  // CONTROL
#elif defined(_UDPSOCKET)
#elif defined(_SERIALPORT)
#elif defined(_HEADER)
#elif defined(_FOOTER)
#else
  if (bForm){
    addProperty("StatusTip", pt_qstring);
    addProperty("ToolTip", pt_qstring);
    addProperty("StyleSheet", pt_qstring);
    addProperty("WhatsThis", pt_qstring);
  }
#endif

#if defined(_LISTBOX) || defined(_COMBOBOX) || defined(_TREEVIEW)
  addProperty("CSV", pt_qstring);
#endif


   
#if defined(_LABEL) || defined(_SOUND) || defined(_IMAGE) || defined(_MOVIE) || defined(_BROWSER) || defined(_WEB) || defined(_TEXTBOX) || defined(_COMBOBOX) || defined(_LISTBOX) || defined(_CHECKBOX) || defined(_DATEBOX) || defined(_TIMEBOX)/* || defined(_DATETIMEBOX)*/ || defined(_EDITOR)
  addProperty("SQLName", pt_qstring);
#ifdef _FORM
#else
  addProperty("SQLRelation", pt_qstring);
  addProperty("TableViewCaption", pt_qstring);
  addProperty("TableViewSort", pt_qstring);
  addProperty("TableViewFilter", pt_qstring);
  addProperty("TableViewWidth", pt_integer);
  addProperty("TableViewVisible", pt_boolean);

  SETPROPERTY_TableViewVisible(true);

  addProperty("TableViewOrder", pt_integer);
#endif
//  addProperty("Print", pt_event);
#endif
/*
#if defined(_FORM)
	addProperty("SQLName", pt_qstring);
	addProperty("SQLRelation", pt_qstring);
	addProperty("SQLWhere", pt_qstring);
	addProperty("SQLOrderBy", pt_qstring);
	addProperty("SQLInsert", pt_boolean);
	addProperty("SQLUpdate", pt_boolean);
	addProperty("SQLDelete", pt_boolean);

    addProperty("TableView", pt_boolean);
    addProperty("TimerInterval", pt_integer);
    addProperty("Flag", pt_qstring);
    addProperty("Icon", pt_qstring);
    addProperty("IconCaption", pt_qstring);
    addProperty("Modal", pt_boolean);
    addProperty("Opacity", pt_integer);

    // events  
    addProperty("Open", pt_event);
    addProperty("Close", pt_event);
    addProperty("GoTo", pt_event);
    addProperty("BeforeInsert", pt_event);
    addProperty("BeforeDelete", pt_event);
    addProperty("BeforeUpdate", pt_event);
    addProperty("Timer", pt_event);
#endif  */

#if defined(_TIMER)
#elif defined(_UDPSOCKET)
  addProperty("OnOpen", pt_event);
  addProperty("OnClose", pt_event);
#elif defined(_SERIALPORT)
#elif defined(_VBOX)
#elif defined(_HBOX)
#elif defined(_VHBOX)
#elif defined(_VSPLIT)
#elif defined(_HSPLIT)
#elif defined(_CHILDCONTROL)
#elif defined(_HEADER)
#elif defined(_FOOTER)
#elif defined(_SCROLLBOX)
  addProperty("OnShow", pt_event);
  addProperty("OnHide", pt_event);
  addProperty("OnMove", pt_event);
  addProperty("OnResize", pt_event);
#elif defined(_HIDDEN)
  addProperty("OnClick", pt_event);
  addProperty("OnDblClick", pt_event);
  addProperty("OnMouseDown", pt_event);
  addProperty("OnMouseUp", pt_event);
  addProperty("OnMouseMove", pt_event);
  addProperty("OnEnter", pt_event);
  addProperty("OnExit", pt_event);
  addProperty("OnContextMenu", pt_event);
  addProperty("OnMouseWheel", pt_event);
#elif defined(_IMAGE) || defined(_FRAME) || defined(_LABEL) || defined(_TAB) || defined(_PROGRESSBAR) || defined(_BOX)
  if (bForm){
    addProperty("OnShow", pt_event);
    addProperty("OnHide", pt_event);
    addProperty("OnPaint", pt_event);
    addProperty("OnMove", pt_event);
    addProperty("OnResize", pt_event);
  } else {
#ifdef _BOX
    addProperty("OnPaint", pt_event);
#endif
  }
#else
  if (bForm){
    addProperty("OnClick", pt_event);
    addProperty("OnDblClick", pt_event);
    addProperty("OnMouseDown", pt_event);
    addProperty("OnMouseUp", pt_event);
    addProperty("OnMouseMove", pt_event);
    addProperty("OnGotFocus", pt_event);
    addProperty("OnLostFocus", pt_event);
    addProperty("OnEnter", pt_event);
    addProperty("OnExit", pt_event);
    addProperty("OnKeyDown", pt_event);
    addProperty("OnKeyUp", pt_event);
    addProperty("OnKeyPress", pt_event);
    addProperty("OnDragEnter", pt_event);
    addProperty("OnDragMove", pt_event);
    addProperty("OnDragExit", pt_event);
    addProperty("OnDrop", pt_event);
    addProperty("OnContextMenu", pt_event);
    addProperty("OnMouseWheel", pt_event);
    addProperty("OnShow", pt_event);
    addProperty("OnHide", pt_event);
    //addProperty("OnPaint", pt_event);
    addProperty("OnMove", pt_event);
    addProperty("OnResize", pt_event);
    addProperty("OnSingleShot", pt_event);
    addProperty("OnEnabled", pt_event);
    addProperty("OnDisabled", pt_event);
  }
#endif

#if defined(_CHILDCONTROL)
#elif defined(_UDPSOCKET)
#elif defined(_SERIALPORT)
#else
  if (bForm){
    addProperty("OnEnabled", pt_event);
    addProperty("OnDisabled", pt_event);
    addProperty("OnSingleShot", pt_event);
  } else {
  }
#endif


#if defined(_MENUBARITEM)
#elif defined(_TOOLBARITEM)
#else

#ifdef IDE

  _selectPanels[0] = new _selectPanel(LeftTop, (QWidget *) this, bResize, nWidth);
  _selectPanels[1] = new _selectPanel(MidTop, (QWidget *) this, bResize, nWidth);

  _selectPanels[2] = new _selectPanel(RightTop, (QWidget *) this, bResize, nWidth);
  _selectPanels[3] = new _selectPanel(LeftMid, (QWidget *) this, bResize, nWidth);

  _selectPanels[4] = new _selectPanel(RightMid, (QWidget *) this, bResize, nWidth);
  _selectPanels[5] = new _selectPanel(LeftBottom, (QWidget *) this, bResize, nWidth);

  _selectPanels[6] = new _selectPanel(MidBottom, (QWidget *) this, bResize, nWidth);
  _selectPanels[7] = new _selectPanel(RightBottom, (QWidget *) this, bResize, nWidth);

  setFocusPolicy(Qt::NoFocus);
  
#endif

#endif

} 

QString getProjectPath()
{
  return my_form_getProjectPath(my_form);
}


QPixmap &createPixmap(_form *f, QString fn){ return my_form_createPixmap(f, fn); }


#ifdef IDE
void showSelectPanels()
{
  _selectPanels[0]->show();
  _selectPanels[1]->show();
  _selectPanels[2]->show();
  _selectPanels[3]->show();
  _selectPanels[4]->show();
  _selectPanels[5]->show();
  _selectPanels[6]->show();
  _selectPanels[7]->show();
}

void hideSelectPanels()
{
  _selectPanels[0]->hide();
  _selectPanels[1]->hide();
  _selectPanels[2]->hide();
  _selectPanels[3]->hide();
  _selectPanels[4]->hide();
  _selectPanels[5]->hide();
  _selectPanels[6]->hide();
  _selectPanels[7]->hide();
}
#endif

#if defined(_MENUBARITEM)
#elif defined(_TOOLBARITEM)
#else
void contextMenuEvent(QContextMenuEvent *e)
{
 
#ifdef IDE

    QMenu contextMenu(this);

    contextMenu.addAction(kbasicIcon(kbasicPath("ide/EDIT_CUT.png")), tr("Cut"), (QWidget *) my_form, SLOT(_event_EDIT_CUT()), QKeySequence("CTRL+X"));

    contextMenu.addAction(kbasicIcon(kbasicPath("ide/EDIT_COPY.png")), tr("Copy"), (QWidget *) my_form, SLOT(_event_EDIT_COPY()), QKeySequence("CTRL+C"));
    contextMenu.addAction(kbasicIcon(kbasicPath("ide/EDIT_PASTE.png")), tr("Paste"), (QWidget *) my_form, SLOT(_event_EDIT_PASTE()), QKeySequence("CTRL+V"));
    
    contextMenu.addAction(tr("Delete"), (QWidget *) my_form, SLOT(_event_EDIT_DELETE()));    
    contextMenu.addSeparator();
    contextMenu.addAction(tr("Select All"), (QWidget *) my_form, SLOT(performSelectAll()));    
    contextMenu.addSeparator();
    contextMenu.addAction(kbasicIcon(kbasicPath("ide/EDIT_APPLY.png")), tr("Apply Properties"), (QWidget *) my_form, SLOT(_event_EDIT_APPLY()));

    contextMenu.addSeparator();
    contextMenu.addAction(kbasicIcon(kbasicPath("ide/FORMAT_MOVE_TO_FRONT.png")), tr("ZOrder: Move To Front"), (QWidget *) my_form, SLOT(_event_FORMAT_MOVE_TO_FRONT()));
    contextMenu.addAction(kbasicIcon(kbasicPath("ide/FORMAT_MOVE_TO_BACK.png")), tr("ZOrder: Move To Back"), (QWidget *) my_form, SLOT(_event_FORMAT_MOVE_TO_BACK()));

    
#ifdef _TAB
    contextMenu.addSeparator();
    contextMenu.addAction(tr("Add New Page"), (QWidget *) my_form, SLOT(_event_ADDPAGE()));
    contextMenu.addAction(tr("Remove Current Page"), (QWidget *) my_form, SLOT(_event_REMOVEPAGE()));
    contextMenu.addAction(tr("Rename Current Page"), (QWidget *) my_form, SLOT(_event_RENAMEPAGE()));
#endif

    contextMenu.exec(QCursor::pos());
    
#elif defined(RUN)

#ifdef SUPERCLASS
    
   if (EVENT_OnContextMenu(e->x(), e->y(), e->globalX(), e->globalY()) == false) SUPERCLASS::contextMenuEvent(e);
        
#endif

#endif
  
}
#endif

void show()
{
#ifdef IDE
    showSelectPanels();
#endif
#ifdef SUPERCLASS
  SUPERCLASS::show();
#endif
}



#ifdef IDE
/*
void cloneProperties(t_properties *p2, t_properties *p)
{
  t_properties::Iterator it;
  t_properties::Iterator it2;

  for ( it = p2->begin(); it != p2->end(); ++it ){
    QString k = it.key();
    t_property *d = *it;
    //t_property *d2 = new t_property();
    //memcpy(d, d2, sizeof(d));

    it2 = p->insert(k, d);
  }

  for ( it = p->begin(); it != p->end(); ++it ){

    t_property *d = *it;
    QString ss = it.key();

    if (ss == "Name"){
      //SETPROPERTY_Name(d->v_qstring);
    } else if (ss == "ControlType"){
      SETPROPERTY_ControlType(d->v_qstring);
    } else if (ss == "X"){
       SETPROPERTY_X(d->v_integer);
    } else if (ss == "Y"){
      SETPROPERTY_Y(d->v_integer);
    } else if (ss == "Width"){
      SETPROPERTY_Width(d->v_integer);
    } else if (ss == "Height"){
      SETPROPERTY_Height(d->v_integer);
    } else if (ss == "Caption"){
      SETPROPERTY_Caption(d->v_qstring);
    } else if (ss == "IntegerValue"){
      //_property::
      SETPROPERTY_IntegerValue(d->v_integer);


    } else if (ss == "Group"){ SETPROPERTY_Group(d->v_qstring);
    } else if (ss == "Background"){ SETPROPERTY_Background(d->v_qstring);
    } else if (ss == "BackgroundStyle"){ SETPROPERTY_BackgroundStyle(d->v_qstring);
    } else if (ss == "Palette"){ SETPROPERTY_Palette(d->v_qstring);    
    } else if (ss == "MinimumWidth"){ SETPROPERTY_MinimumWidth(d->v_integer);
    } else if (ss == "MinimumHeight"){ SETPROPERTY_MinimumHeight(d->v_integer);
    } else if (ss == "MaximumWidth"){ SETPROPERTY_MaximumWidth(d->v_integer);
    } else if (ss == "MaximumHeight"){ SETPROPERTY_MaximumHeight(d->v_integer);
    } else if (ss == "StopOnClose"){ SETPROPERTY_StopOnClose(d->v_boolean);

    } else if (ss == "BorderTop"){ SETPROPERTY_BorderTop(d->v_integer);
    } else if (ss == "BorderBottom"){ SETPROPERTY_BorderBottom(d->v_integer);
    } else if (ss == "BorderLeft"){ SETPROPERTY_BorderLeft(d->v_integer);
    } else if (ss == "BorderRight"){ SETPROPERTY_BorderRight(d->v_integer);
    } else if (ss == "CSV"){ SETPROPERTY_CSV(d->v_qstring);
    } else if (ss == "Tag"){ SETPROPERTY_Tag(d->v_qstring);
    } else if (ss == "TableView"){ SETPROPERTY_TableView(d->v_boolean);
    
    } else if (ss == "BoxIndex"){ SETPROPERTY_BoxIndex(d->v_integer);
    } else if (ss == "BoxX"){ SETPROPERTY_BoxX(d->v_integer);
    } else if (ss == "BoxY"){ SETPROPERTY_BoxY(d->v_integer);
    } else if (ss == "SplitIndex"){ SETPROPERTY_SplitIndex(d->v_integer);

    } else if (ss == "Scale"){ SETPROPERTY_Scale(d->v_boolean);
    } else if (ss == "DragDrop"){ SETPROPERTY_DragDrop(d->v_boolean);
    
    } else if (ss == "FocusPolicy"){ SETPROPERTY_FocusPolicy(d->v_qstring);
    } else if (ss == "FocusProxy"){ SETPROPERTY_FocusProxy(d->v_qstring);
    } else if (ss == "FocusOrder"){ SETPROPERTY_FocusOrder(d->v_integer);

    } else if (ss == "FontName"){ SETPROPERTY_FontName(d->v_qstring);
    } else if (ss == "FontSize"){ SETPROPERTY_FontSize(d->v_integer);

    } else if (ss == "FontBold"){ SETPROPERTY_FontBold(d->v_boolean);
    } else if (ss == "FontItalic"){ SETPROPERTY_FontItalic(d->v_boolean);
    } else if (ss == "FontUnderline"){ SETPROPERTY_FontUnderline(d->v_boolean);

    } else if (ss == "FontColor"){ SETPROPERTY_FontColor(d->v_qstring);

    } else if (ss == "StatusTip"){ SETPROPERTY_StatusTip(d->v_qstring);
    } else if (ss == "ToolTip"){ SETPROPERTY_ToolTip(d->v_qstring);
    } else if (ss == "StyleSheet"){ SETPROPERTY_StyleSheet(d->v_qstring);

    } else if (ss == "Flag"){ SETPROPERTY_Flag(d->v_qstring);
    } else if (ss == "Layout"){ SETPROPERTY_Layout(d->v_qstring);
    } else if (ss == "SQLControls"){ SETPROPERTY_SQLControls(d->v_qstring);
    } else if (ss == "Icon"){ SETPROPERTY_Icon(d->v_qstring);
    //} else if (ss == "IconCaption"){ SETPROPERTY_IconCaption(d->v_qstring);
    } else if (ss == "Caption"){ SETPROPERTY_Caption(d->v_qstring);

    } else if (ss == "Modal"){ SETPROPERTY_Modal(d->v_boolean);
    } else if (ss == "Opacity"){ SETPROPERTY_Opacity(d->v_integer);
    } else if (ss == "TimerInterval"){ SETPROPERTY_TimerInterval(d->v_integer);

    } else if (ss == "Shadow"){ SETPROPERTY_Shadow(d->v_boolean);
    } else if (ss == "Shape"){ SETPROPERTY_Shape(d->v_boolean);
    } else if (ss == "OpenLinks"){ SETPROPERTY_OpenLinks(d->v_boolean);

    } else if (ss == "Icon"){ SETPROPERTY_Icon(d->v_qstring);
    } else if (ss == "InputControl"){ SETPROPERTY_InputControl(d->v_qstring);
    
    } else if (ss == "Space"){ SETPROPERTY_Space(d->v_integer);
    } else if (ss == "Border"){ SETPROPERTY_Border(d->v_integer);

    } else if (ss == "Flat"){ SETPROPERTY_Flat(d->v_boolean);

    } else if (ss == "Key"){ SETPROPERTY_Key(d->v_qstring);
        
    } else if (ss == "IntegerMaximum"){ SETPROPERTY_IntegerMaximum(d->v_integer);
    } else if (ss == "IntegerMinimum"){ SETPROPERTY_IntegerMinimum(d->v_integer);
    } else if (ss == "Completer"){ SETPROPERTY_Completer(d->v_qstring);

    } else if (ss == "ValidatorDouble"){ SETPROPERTY_ValidatorDouble(d->v_boolean);
    } else if (ss == "ValidatorInteger"){ SETPROPERTY_ValidatorInteger(d->v_boolean);

    } else if (ss == "ValidatorRegEx"){ SETPROPERTY_ValidatorRegEx(d->v_qstring);
    } else if (ss == "ValidatorRegEx2"){ SETPROPERTY_ValidatorRegEx2(d->v_qstring);
    } else if (ss == "DoubleEntry"){ SETPROPERTY_DoubleEntry(d->v_boolean);

    } else if (ss == "InsertPolicy"){ SETPROPERTY_InsertPolicy(d->v_qstring);
    } else if (ss == "Editable"){ SETPROPERTY_Editable(d->v_boolean);
    } else if (ss == "MaximumVisible"){ SETPROPERTY_MaximumVisible(d->v_integer);
    } else if (ss == "Sorted"){ SETPROPERTY_Sorted(d->v_boolean);
    } else if (ss == "RootIsDecorated"){ SETPROPERTY_RootIsDecorated(d->v_boolean);

    } else if (ss == "StringMaximum"){ SETPROPERTY_StringMaximum(d->v_qstring);
    } else if (ss == "StringMinimum"){ SETPROPERTY_StringMinimum(d->v_qstring);
    } else if (ss == "Format"){ SETPROPERTY_Format(d->v_qstring);

    } else if (ss == "PopUp"){ SETPROPERTY_PopUp(d->v_boolean);
    } else if (ss == "ScrollBar"){ SETPROPERTY_ScrollBar(d->v_qstring);

    } else if (ss == "MouseDownImage"){ SETPROPERTY_MouseDownImage(d->v_qstring);
    } else if (ss == "MouseUpImage"){ SETPROPERTY_MouseUpImage(d->v_qstring);
    } else if (ss == "EnabledImage"){ SETPROPERTY_EnabledImage(d->v_qstring);
    } else if (ss == "MouseDownSound"){ SETPROPERTY_MouseDownSound(d->v_qstring);
    } else if (ss == "MouseUpSound"){ SETPROPERTY_MouseUpSound(d->v_qstring);
    } else if (ss == "HomeURL"){ SETPROPERTY_HomeURL(d->v_qstring);

    } else if (ss == "Enabled"){
      SETPROPERTY_Enabled(d->v_boolean);
    } else if (ss == "Cursor"){
      SETPROPERTY_Cursor(d->v_qstring);
    } else if (ss == "TabIndex"){
      SETPROPERTY_TabIndex(d->v_integer);
    } else if (ss == "ParentIndex"){
      SETPROPERTY_ParentIndex(d->v_integer);
    } else if (ss == "Tag"){
      SETPROPERTY_Tag(d->v_qstring);
    } else if (ss == "Visible"){
      SETPROPERTY_Visible(d->v_boolean);
    } else if (ss == "Resizable"){
      SETPROPERTY_Resizable(d->v_boolean);

    } else if (ss == "ResizableSmaller"){
      SETPROPERTY_ResizableSmaller(d->v_boolean);
    } else if (ss == "ResizableBigger"){
      SETPROPERTY_ResizableBigger(d->v_boolean);

    } else if (ss == "WordWrap"){
      SETPROPERTY_WordWrap(d->v_boolean);
    } else if (ss == "ReadOnly"){
      SETPROPERTY_ReadOnly(d->v_boolean);
    } else if (ss == "Alignment"){
      SETPROPERTY_Alignment(d->v_qstring);
    } else if (ss == "EchoMode"){
      SETPROPERTY_EchoMode(d->v_qstring);
    } else if (ss == "Feature"){
      SETPROPERTY_Feature(d->v_qstring);
    } else if (ss == "Orientation"){
      SETPROPERTY_Orientation(d->v_qstring);
    }

    

    // PROPERTY
    if (ss == "Dock"){ SETPROPERTY_Dock(d->v_qstring);
    } else if (ss == "Prefix"){ SETPROPERTY_Prefix(d->v_qstring);
    } else if (ss == "Suffix"){ SETPROPERTY_Suffix(d->v_qstring);

    } else if (ss == "Description"){ SETPROPERTY_Description(d->v_qstring);
    } else if (ss == "ViewMode"){ SETPROPERTY_ViewMode(d->v_qstring);

    } else if (ss == "TickPosition"){ SETPROPERTY_TickPosition(d->v_qstring);
    } else if (ss == "InvertedAppearance"){ SETPROPERTY_InvertedAppearance(d->v_boolean);
    } else if (ss == "InvertedControls"){ SETPROPERTY_InvertedControls(d->v_boolean);
    } else if (ss == "Tracking"){ SETPROPERTY_Tracking(d->v_boolean);
    } else if (ss == "TickInterval"){ SETPROPERTY_TickInterval(d->v_integer);
    } else if (ss == "PageStep"){ SETPROPERTY_PageStep(d->v_integer);
    } else if (ss == "SingleStep"){ SETPROPERTY_SingleStep(d->v_integer);

    } else if (ss == "MoveOnMouseDrag"){ SETPROPERTY_MoveOnMouseDrag(d->v_boolean);
    } else if (ss == "MouseTracking"){ SETPROPERTY_MouseTracking(d->v_boolean);
    } else if (ss == "DrawOnPaint"){ SETPROPERTY_DrawOnPaint(d->v_boolean);
    } else if (ss == "SoundOnEvent"){ SETPROPERTY_SoundOnEvent(d->v_qstring);
    } else if (ss == "ActionId"){ SETPROPERTY_ActionId(d->v_qstring);

    
    } else if (ss == "CursorAnimation"){ SETPROPERTY_CursorAnimation(d->v_qstring);
    

    } else if (ss == "ScrollX"){ SETPROPERTY_ScrollX(d->v_integer);
    } else if (ss == "ScrollY"){ SETPROPERTY_ScrollY(d->v_integer);
    } else if (ss == "ScrollWidth"){ SETPROPERTY_ScrollWidth(d->v_integer);
    } else if (ss == "ScrollHeight"){ SETPROPERTY_ScrollHeight(d->v_integer);

    } else if (ss == "MultiPageHeight"){ SETPROPERTY_MultiPageHeight(d->v_integer);
    } else if (ss == "MultiPageBorderTop"){ SETPROPERTY_MultiPageBorderTop(d->v_integer);
    } else if (ss == "MultiPageBorderBottom"){ SETPROPERTY_MultiPageBorderBottom(d->v_integer);
    } else if (ss == "MultiPageBorderLeft"){ SETPROPERTY_MultiPageBorderLeft(d->v_integer);
    } else if (ss == "MultiPageBorderRight"){ SETPROPERTY_MultiPageBorderRight(d->v_integer);

    } else if (ss == "PortName"){ SETPROPERTY_PortName(d->v_qstring);
    } else if (ss == "BaudRate"){ SETPROPERTY_BaudRate(d->v_qstring);
    } else if (ss == "DataBits"){ SETPROPERTY_DataBits(d->v_qstring);
    } else if (ss == "Parity"){ SETPROPERTY_Parity(d->v_qstring);
    } else if (ss == "FlowControl"){ SETPROPERTY_FlowControl(d->v_qstring);    
    } else if (ss == "StopBits"){ SETPROPERTY_StopBits(d->v_qstring);
    } else if (ss == "TimeOutMillisec"){ SETPROPERTY_TimeOutMillisec(d->v_integer);
    } else if (ss == "PollingInterval"){ SETPROPERTY_PollingInterval(d->v_integer);

    } else if (ss == "SelectionMode"){ SETPROPERTY_SelectionMode(d->v_qstring);
    } else if (ss == "AlternatingRowColors"){ SETPROPERTY_AlternatingRowColors(d->v_boolean);
    } else if (ss == "Checked"){ SETPROPERTY_Checked(d->v_boolean);
    //} else if (ss == "Null"){ SETPROPERTY_Null(d->v_boolean);
    } else if (ss == "Index"){ SETPROPERTY_Index(d->v_boolean);



    } else if (ss == "Comment1Begin"){ SETPROPERTY_Comment1Begin(d->v_qstring);
    } else if (ss == "Comment1End"){ SETPROPERTY_Comment1End(d->v_qstring);
    } else if (ss == "Comment2Begin"){ SETPROPERTY_Comment2Begin(d->v_qstring);
    //} else if (ss == "Comment2End"){ SETPROPERTY_Comment2End(d->v_qstring);
    } else if (ss == "Keywords"){ SETPROPERTY_Keywords(d->v_qstring);
    } else if (ss == "Commands"){ SETPROPERTY_Commands(d->v_qstring);
    } else if (ss == "CommentColor"){ SETPROPERTY_CommentColor(d->v_qstring);
    } else if (ss == "KeywordColor"){ SETPROPERTY_KeywordColor(d->v_qstring);
    } else if (ss == "CommandColor"){ SETPROPERTY_CommandColor(d->v_qstring);
      

    } else if (ss == "SQL"){ SETPROPERTY_SQL(d->v_qstring);
    }

    if (ss == "SQLName"){ SETPROPERTY_SQLName(d->v_qstring);
    } else if (ss == "SQLRelation"){ SETPROPERTY_SQLRelation(d->v_qstring);
    } else if (ss == "SQLInsert"){ SETPROPERTY_SQLInsert(d->v_boolean);
    } else if (ss == "SQLUpdate"){ SETPROPERTY_SQLUpdate(d->v_boolean);
    } else if (ss == "SQLDelete"){ SETPROPERTY_SQLDelete(d->v_boolean);


    } else if (ss == "TableViewCaption"){ SETPROPERTY_TableViewCaption(d->v_qstring);
    } else if (ss == "TableViewSort"){ SETPROPERTY_TableViewSort(d->v_qstring);
    } else if (ss == "TableViewFilter"){ SETPROPERTY_TableViewFilter(d->v_qstring);
    } else if (ss == "TableViewWidth"){ SETPROPERTY_TableViewWidth(d->v_integer);
    } else if (ss == "TableViewVisible"){ SETPROPERTY_TableViewVisible(d->v_boolean);
    } else if (ss == "TableViewOrder"){ SETPROPERTY_TableViewOrder(d->v_integer);
      
    } else if (ss == "Pages"){ SETPROPERTY_Pages(d->v_qstring);
    } else if (ss == "ParentForm"){ SETPROPERTY_ParentForm(d->v_qstring);
    } else if (ss == "ParentControl"){ SETPROPERTY_ParentControl(d->v_qstring);
    } else if (ss == "TabIndex"){ SETPROPERTY_TabIndex(d->v_integer);
    } else if (ss == "ParentIndex"){ SETPROPERTY_ParentIndex(d->v_integer);

    } //else 

    if (ss == "EnterImage"){
      SETPROPERTY_EnterImage(d->v_qstring);

    } else if (ss == "ExitImage"){
      SETPROPERTY_ExitImage(d->v_qstring);

    } else if (ss == "DisabledImage"){
      SETPROPERTY_DisabledImage(d->v_qstring);

    } else if (ss == "EnterSound"){
      SETPROPERTY_EnterSound(d->v_qstring);

    } else if (ss == "ExitSound"){
      SETPROPERTY_ExitSound(d->v_qstring);

    } else if (ss == "StringValue"){
      SETPROPERTY_StringValue(d->v_qstring); 

    } else if (ss == "InputMask"){
      SETPROPERTY_InputMask(d->v_qstring);
      
    } else if (ss == "Mask"){
      SETPROPERTY_Mask(d->v_qstring);
      
    } else if (ss == "Menu"){
      SETPROPERTY_Menu(d->v_boolean);

    } else if (ss == "Interval"){
      SETPROPERTY_Interval(d->v_integer);     

    } else if (ss == "Brightness"){ SETPROPERTY_Brightness(d->v_integer);
    } else if (ss == "Contrast"){ SETPROPERTY_Contrast(d->v_integer);
    } else if (ss == "Hue"){ SETPROPERTY_Hue(d->v_integer);
    } else if (ss == "Saturation"){ SETPROPERTY_Saturation(d->v_integer);
    } else if (ss == "ScaleMode"){ SETPROPERTY_ScaleMode(d->v_qstring);
    } else if (ss == "AspectRatio"){ SETPROPERTY_AspectRatio(d->v_qstring);
      
    } else if (ss == "TransitionTime"){ SETPROPERTY_TransitionTime(d->v_integer);
    } else if (ss == "Muted"){ SETPROPERTY_Muted(d->v_boolean);
    } else if (ss == "Volume"){ SETPROPERTY_Volume(d->v_integer);
    } else if (ss == "PrefinishMark"){ SETPROPERTY_PrefinishMark(d->v_integer);
    } else if (ss == "Tick"){ SETPROPERTY_Tick(d->v_integer);

    } else if (ss == "OnTick"){ SETPROPERTY_OnTick(d->v_event);
    } else if (ss == "OnStateChanged"){ SETPROPERTY_OnStateChanged(d->v_event);
    } else if (ss == "OnAboutToFinish"){ SETPROPERTY_OnAboutToFinish(d->v_event);
    } else if (ss == "OnFinished"){ SETPROPERTY_OnFinished(d->v_event);
    } else if (ss == "OnMutedChanged"){ SETPROPERTY_OnMutedChanged(d->v_event);
    } else if (ss == "OnVolumeChanged"){ SETPROPERTY_OnVolumeChanged(d->v_event);
    } else if (ss == "OnPlayedTitleChanged"){ SETPROPERTY_OnPlayingTitleChanged(d->v_event);
    } else if (ss == "OnBufferStatus"){ SETPROPERTY_OnBufferStatus(d->v_event);
    } else if (ss == "OnTotalTimeChanged"){ SETPROPERTY_OnTotalTimeChanged(d->v_event);

    } else if (ss == "OpenOnRun"){
      SETPROPERTY_OpenAtStartup(d->v_boolean);
    } else if (ss == "AutoDefault"){
      SETPROPERTY_AutoDefault(d->v_boolean);
     
    } else if (ss == "Checkable"){
      SETPROPERTY_Checkable(d->v_boolean);
    } else if (ss == "Default"){
      SETPROPERTY_Default(d->v_boolean);
    } else if (ss == "Separator"){
      SETPROPERTY_Separator(d->v_boolean);

    
      
    } else if (ss == "BooleanValue"){
      SETPROPERTY_BooleanValue(d->v_boolean);

    // EVENT
    } else if (ss == "OnPage"){ SETPROPERTY_OnPage(d->v_event);
    } else if (ss == "OnLinkHovered"){ SETPROPERTY_OnLinkHovered(d->v_event);
    } else if (ss == "OnLoadFinished"){ SETPROPERTY_OnLoadFinished(d->v_event);
    } else if (ss == "OnLoadProgress"){ SETPROPERTY_OnLoadProgress(d->v_event);
    } else if (ss == "OnLoadStarted"){ SETPROPERTY_OnLoadStarted(d->v_event);
    } else if (ss == "OnWindowCloseRequested"){ SETPROPERTY_OnWindowCloseRequested(d->v_event);

    } else if (ss == "OnSingleShot"){ SETPROPERTY_OnSingleShot(d->v_event);
    } else if (ss == "OnPrint"){ SETPROPERTY_OnPrint(d->v_event);

    } else if (ss == "OnCurrentItemChanged"){ SETPROPERTY_OnCurrentItemChanged(d->v_event);
    } else if (ss == "OnItemActivated"){ SETPROPERTY_OnItemActivated(d->v_event);
    } else if (ss == "OnItemChanged"){ SETPROPERTY_OnItemChanged(d->v_event);
    } else if (ss == "OnItemClicked"){ SETPROPERTY_OnItemClicked(d->v_event);
    } else if (ss == "OnItemCollapsed"){ SETPROPERTY_OnItemCollapsed(d->v_event);
    } else if (ss == "OnItemDoubleClicked"){ SETPROPERTY_OnItemDoubleClicked(d->v_event);
    } else if (ss == "OnItemEntered"){ SETPROPERTY_OnItemEntered(d->v_event);
    } else if (ss == "OnItemExpanded"){ SETPROPERTY_OnItemExpanded(d->v_event);
    } else if (ss == "OnItemPressed"){ SETPROPERTY_OnItemPressed(d->v_event);
    } else if (ss == "OnItemSelectionChanged"){ SETPROPERTY_OnItemSelectionChanged(d->v_event);

    } else if (ss == "OnDockMove"){ SETPROPERTY_OnDockMove(d->v_event);
    } else if (ss == "OnDockShow"){ SETPROPERTY_OnDockShow(d->v_event);
    } else if (ss == "OnDockHide"){ SETPROPERTY_OnDockHide(d->v_event);
    } else if (ss == "OnDockFloating"){ SETPROPERTY_OnDockFloating(d->v_event);
    } else if (ss == "OnDockNotFloating"){ SETPROPERTY_OnDockNotFloating(d->v_event);

    } else if (ss == "OnEvent"){ SETPROPERTY_OnEvent(d->v_event);
    } else if (ss == "OnOpen"){ SETPROPERTY_OnOpen(d->v_event);
    } else if (ss == "OnClose"){ SETPROPERTY_OnClose(d->v_event);
    } else if (ss == "OnGoTo"){ SETPROPERTY_OnGoTo(d->v_event);
    } else if (ss == "OnBeforeInsert"){ SETPROPERTY_OnBeforeInsert(d->v_event);
    } else if (ss == "OnBeforeDelete"){ SETPROPERTY_OnBeforeDelete(d->v_event);
    } else if (ss == "OnDragExit"){ SETPROPERTY_OnDragExit(d->v_event);
    } else if (ss == "OnPaint"){ SETPROPERTY_OnPaint(d->v_event);

    } else if (ss == "OnDirty"){ SETPROPERTY_OnDirty(d->v_event);
    } else if (ss == "OnAddNew"){ SETPROPERTY_OnAddNew(d->v_event);
    } else if (ss == "OnQuery"){ SETPROPERTY_OnQuery(d->v_event);

    } else if (ss == "OnTimer"){
      SETPROPERTY_OnTimer(d->v_event);

    } else if (ss == "OnClick"){
      SETPROPERTY_OnClick(d->v_event);

    } else if (ss == "OnDblClick"){
      SETPROPERTY_OnDblClick(d->v_event);

    } else if (ss == "OnMouseDown"){
      SETPROPERTY_OnMouseDown(d->v_event);

    } else if (ss == "OnMouseUp"){
      SETPROPERTY_OnMouseUp(d->v_event);

    } else if (ss == "OnMouseMove"){
      SETPROPERTY_OnMouseMove(d->v_event);

    } else if (ss == "OnGotFocus"){
      SETPROPERTY_OnGotFocus(d->v_event);

    } else if (ss == "OnLostFocus"){
      SETPROPERTY_OnLostFocus(d->v_event);

    } else if (ss == "OnEnter"){
      SETPROPERTY_OnEnter(d->v_event);

    } else if (ss == "OnExit"){
      SETPROPERTY_OnExit(d->v_event);

    } else if (ss == "OnKeyDown"){
      SETPROPERTY_OnKeyDown(d->v_event);

    } else if (ss == "OnKeyUp"){
      SETPROPERTY_OnKeyUp(d->v_event);

    } else if (ss == "OnKeyPress"){
      SETPROPERTY_OnKeyPress(d->v_event);

    } else if (ss == "OnBeforeUpdate"){
      SETPROPERTY_OnBeforeUpdate(d->v_event);

    } else if (ss == "OnResize"){
      SETPROPERTY_OnResize(d->v_event);

    } else if (ss == "OnDragEnter"){ SETPROPERTY_OnDragEnter(d->v_event);
    } else if (ss == "OnDragMove"){ SETPROPERTY_OnDragMove(d->v_event);
    } else if (ss == "OnDrop"){ SETPROPERTY_OnDrop(d->v_event);
    } else if (ss == "OnContextMenu"){ SETPROPERTY_OnContextMenu(d->v_event);
    } else if (ss == "OnMouseWheel"){ SETPROPERTY_OnMouseWheel(d->v_event);
    } else if (ss == "OnMultiPageShow"){ SETPROPERTY_OnMultiPageShow(d->v_event);
    } else if (ss == "OnScroll"){ SETPROPERTY_OnScroll(d->v_event);
    
    } else if (ss == "OnShow"){ SETPROPERTY_OnShow(d->v_event);
    } else if (ss == "OnHide"){ SETPROPERTY_OnHide(d->v_event);
    } else if (ss == "OnMove"){ SETPROPERTY_OnMove(d->v_event);
    } else if (ss == "OnEnabled"){ SETPROPERTY_OnEnabled(d->v_event);
    } else if (ss == "OnDisabled"){ SETPROPERTY_OnDisabled(d->v_event);

    }
  }
}
*/
#endif

void mouseDoubleClickEvent ( QMouseEvent * e )
{
#ifdef IDE 

#if defined(_COMMANDBUTTON) || defined(_COMMANDLINKBUTTON) || defined(_TOOLBUTTON) || defined(_CHECKBOX) || defined(_RADIOBUTTON) || defined(_TEXTBOX) || defined(_DATEBOX) || defined(_TIMEBOX) || defined(_DATETIMEBOX) || defined(_TIMER) || defined(_IMAGEBUTTON) || defined(_EDITOR) || defined(_SLIDER)
    my_form_newEvent (my_form, GETPROPERTY_Name(), "OnEvent", "");
    e->accept();
#endif
#if defined(_COMBOBOX) || defined(_LISTBOX)
    my_form_newEvent (my_form, GETPROPERTY_Name(), "OnEvent", "Index As Integer, Caption As String");
    e->accept();
#endif
#if defined(_TAB)
    my_form_newEvent (my_form, GETPROPERTY_Name(), "OnEvent", "Index As Integer");
    e->accept();
#endif
#if defined(_CHILDCONTROL)
    my_form_newEvent (my_form, "FormView", GETPROPERTY_StringValue(), "");
    e->accept();
#endif
#if defined(_TOOLBARVIEW)
    my_form_newEvent (my_form, "ToolBarView", GETPROPERTY_StringValue(), "");
    e->accept();
#endif
#if defined(_BROWSER)
    my_form_newEvent (my_form, GETPROPERTY_Name(), "OnEvent", "BackwardAvailable As Boolean, ForwardAvailable As Boolean, NewURL As String");
    e->accept();
#endif
    //e->ignore();

#elif defined(RUN)
#ifdef SUPERCLASS
    SUPERCLASS::mouseDoubleClickEvent(e);
    { 
      Qt::MouseButton bu = e->button();
      EVENT_OnDblClick(e->x(), e->y(), e->globalX(), e->globalY(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);
    }
#endif
#endif
}

void mousePressEvent ( QMouseEvent * e )
{
  #ifdef IDE 

    e->ignore();

  #elif defined(RUN)
#ifdef _IMAGEBUTTON
    
  if (GETPROPERTY_Enabled()){
    QString s = GETPROPERTY_MouseDownSound();
    if (!s.isEmpty()){
      EXTERN_my_sounds->playOnce(s);
    }
  }

  //if (sClickImage != GETPROPERTY_MouseDownImage()){


    QString fn;
    if (GETPROPERTY_Enabled()){
      if (GETPROPERTY_Checked()){
        fn = GETPROPERTY_CheckMouseDownImage(); 
      } else {
        fn = GETPROPERTY_MouseDownImage(); 
      }
    }    
    if (fn.length()){

       if (fn.length() > 200){ // QString contains binary data         

          QPixmap pi;
          if (fn.left(200).contains("<svg ", Qt::CaseInsensitive)){
            fn = fn.trimmed();
            QSvgWidget w(0);
            w.resize(width(), height());
            QSvgRenderer *r = w.renderer();
            if (r->load(fn.toLatin1())){
              QPixmap p(width(), height());
              QPainter painter(&p);
              r->render(&painter);
              pi = p;
            }
          } else {
             pi.loadFromData(fn.toLatin1());
          }       

          if (GETPROPERTY_Scale() && !pi.isNull()){            
            pi = pi.scaled(width(), height());
          }

         setAutoFillBackground(true);
         QBrush b(pi);
         QPalette p = palette();
         p.setBrush(QPalette::Window, b);  
         setPalette(p);

       } else {

        QPixmap pi = loadPixmap(fn.contains(".") ? fn : fn + ".png");
        if (GETPROPERTY_Scale() && !pi.isNull()){
          pi = pi.scaled(width(), height());
        }

         setAutoFillBackground(true);
         QBrush b(pi);
         QPalette p = palette();
         p.setBrush(QPalette::Window, b);  
         setPalette(p);

       }
    }
/*
    if (fn.length()){

      if (!(fn.contains("/") || fn.contains("\\"))){
        clickImage = my_form_loadProjectImage(my_form, fn.toAscii());
//       oldImage = backgroundPixmap();
      // setBackgroundPixmap( clickImage );
      }
      if (QFile::exists( fn )){
       QImage img( fn );
      // clickImage.convertFromImage( img );        

      // oldImage = backgroundPixmap();

      // setBackgroundPixmap( clickImage );
      }
    }*/
//  } else {
//    oldImage = backgroundPixmap();

   // setBackgroundPixmap( clickImage );
  //}
  
#endif
#ifdef _MOVIE
  if (bKeyAndMouseCanCancel) this->METHOD_Stop();
#endif

#ifdef SUPERCLASS
    SUPERCLASS::mousePressEvent(e);
    {
      bEventClick = true;
      Qt::MouseButton bu = e->button();
      EVENT_OnMouseDown(e->x(), e->y(), e->globalX(), e->globalY(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);
    }
#endif
  #endif
}

void mouseReleaseEvent ( QMouseEvent * e ) 
{
  #ifdef IDE 

    e->ignore();

  #elif defined(RUN)
#ifdef _IMAGEBUTTON

  if (GETPROPERTY_Enabled()){
    QString s = GETPROPERTY_MouseUpSound();
    if (!s.isEmpty()){
      EXTERN_my_sounds->playOnce(s);
    }
  }

  //if (sClickImage != GETPROPERTY_MouseUpImage()){


    QString fn;
    if (GETPROPERTY_Enabled()){
      if (GETPROPERTY_Checked()){
        fn = GETPROPERTY_CheckMouseUpImage(); 
        if (!fn.length()) fn = GETPROPERTY_CheckEnterImage(); 
      } else {
        fn = GETPROPERTY_MouseUpImage(); 
        if (!fn.length()) fn = GETPROPERTY_EnterImage(); 
      }
     
    }    
    if (fn.length()){

       if (fn.length() > 200){ // QString contains binary data         


          QPixmap pi;
          if (fn.left(200).contains("<svg ", Qt::CaseInsensitive)){
            fn = fn.trimmed();
            QSvgWidget w(0);
            w.resize(width(), height());
            QSvgRenderer *r = w.renderer();
            if (r->load(fn.toLatin1())){
              QPixmap p(width(), height());
              QPainter painter(&p);
              r->render(&painter);
              pi = p;
            }
          } else {
             pi.loadFromData(fn.toLatin1());
          }       

        if (GETPROPERTY_Scale() && !pi.isNull()){
          pi = pi.scaled(width(), height());
        }
         setAutoFillBackground(true);
         QBrush b(pi);
         QPalette p = palette();
         p.setBrush(QPalette::Window, b);  
         setPalette(p);

       } else {


        QPixmap pi = loadPixmap(fn.contains(".") ? fn : fn + ".png");
        if (GETPROPERTY_Scale() && !pi.isNull()){
          pi = pi.scaled(width(), height());
        }

         setAutoFillBackground(true);
         QBrush b(pi);
         QPalette p = palette();
         p.setBrush(QPalette::Window, b);  
         setPalette(p);

       }
    }

#endif
#ifdef SUPERCLASS
    SUPERCLASS::mouseReleaseEvent(e);
    //SENDER = this;
    {
      Qt::MouseButton bu = e->button();
      int x = e->x();
      int y = e->y();
      int gx = e->globalX();
      int gy = e->globalY();
      if (bEventClick){
        bEventClick = false;      
        EVENT_OnClick(x, y, gx, gy, bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);
#ifdef _IMAGEBUTTON
        if (GETPROPERTY_Enabled()){
          if (GETPROPERTY_Checkable()){
            SETPROPERTY_Checked(!GETPROPERTY_Checked());
          }
  
          SoundOnEvent();
          setFocus(); 
          EVENT_OnEvent();
        }
#endif
      }
      EVENT_OnMouseUp(x, y, gx, gy, bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);
    }

#endif
  #endif
}

void mouseMoveEvent ( QMouseEvent * e )
{
  #ifdef IDE 

    e->ignore();

#elif defined(RUN)

#ifdef SUPERCLASS
    SUPERCLASS::mouseMoveEvent(e);
    {
      EVENT_OnMouseMove(e->x(), e->y(), e->globalX(), e->globalY());
    }
#endif
#endif
}

void keyPressEvent ( QKeyEvent * e ) 
{
  #ifdef IDE 

    e->ignore();
  #elif defined(RUN)
#ifdef _MOVIE
  if (bKeyAndMouseCanCancel) this->METHOD_Stop();
#endif
#ifdef SUPERCLASS
    SUPERCLASS::keyPressEvent(e);
    { 
      bEventKeyPress = true;
      Qt::KeyboardModifiers m = e->modifiers();
      EVENT_OnKeyDown(e->key(), m & Qt::ShiftModifier, m & Qt::ControlModifier, m & Qt::AltModifier); 
    }
#endif
#endif  
}

void keyReleaseEvent ( QKeyEvent * e )
{  
  #ifdef IDE  

    //e->ignore();
  #elif defined(RUN)
#ifdef SUPERCLASS
    SUPERCLASS::keyReleaseEvent(e);
    { 
      Qt::KeyboardModifiers m = e->modifiers();
      if (bEventKeyPress){
         bEventKeyPress = false;
         EVENT_OnKeyPress(e->key(), m & Qt::ShiftModifier, m & Qt::ControlModifier, m & Qt::AltModifier); 
      }
      EVENT_OnKeyUp(e->key(), m & Qt::ShiftModifier, m & Qt::ControlModifier, m & Qt::AltModifier); 
    }
#endif
  #endif
}

void dragEnterEvent ( QDragEnterEvent * e)
{
  #ifdef IDE 

    e->ignore();
  #elif defined(RUN)
#ifdef SUPERCLASS
    SUPERCLASS::dragEnterEvent(e);
    
    { 
      t_boolean Cancel = false;
      QRect r = e->answerRect();
      QPoint g = mapToGlobal(QPoint(r.x(), r.y()));
      Qt::MouseButtons bu = e->mouseButtons();
      Qt::KeyboardModifiers m = e->keyboardModifiers();
      EVENT_OnDragEnter(&Cancel, r.x(), r.y(), g.x(), g.y(), r.width(), r.height(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton, m & Qt::ShiftModifier, m & Qt::ControlModifier, m & Qt::AltModifier); 
      if (Cancel){
        e->ignore();
      } else {         
        if (e->mimeData()->hasText() || e->mimeData()->hasHtml() || e->mimeData()->hasUrls()){
           e->accept();
        }
/*

        QStringList l = e->mimeData()->formats();
        foreach(QString s, l){
          QMessageBox::information(0,"", s);   
        }*/
        /*
        if (e->mimeData()->hasFormat("text/plain")){
           e->acceptProposedAction();
        }
        */

      }
    }    
#endif
 #endif
}

void dragMoveEvent ( QDragMoveEvent * e)
{
  #ifdef IDE 

    e->ignore();
  #elif defined(RUN)
#ifdef SUPERCLASS    
  SUPERCLASS::dragMoveEvent(e);
    { 
      t_boolean Cancel = false;
      QRect r = e->answerRect();
      QPoint g = mapToGlobal(QPoint(r.x(), r.y()));
      Qt::MouseButtons bu = e->mouseButtons();
      Qt::KeyboardModifiers m = e->keyboardModifiers();      
      EVENT_OnDragMove(&Cancel, r.x(), r.y(), g.x(), g.y(), r.width(), r.height(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton, m & Qt::ShiftModifier, m & Qt::ControlModifier, m & Qt::AltModifier); 
      if (Cancel){
        e->ignore(); 
      } else {
        
        e->accept();
      }
    }    
#endif
 #endif
}

void dragLeaveEvent ( QDragLeaveEvent * e)
{
  #ifdef IDE

  //  e->ignore();
#elif defined(RUN)
#ifdef SUPERCLASS
    SUPERCLASS::dragLeaveEvent(e);
    { 
      EVENT_OnDragExit(); 
    }    
#endif
#endif
}

void dropEvent( QDropEvent *e)
{
  #ifdef IDE

    e->ignore();
  #elif defined(RUN)
#ifdef SUPERCLASS   
   SUPERCLASS::dropEvent(e);
    { 
      t_boolean Cancel = false;
     // const QMimeData *d = e->mimeData;
      QString s = e->mimeData()->text();
      if (s.isEmpty()) s = e->mimeData()->html();
      if (s.isEmpty()){
        QList<QUrl> l = e->mimeData()->urls();
        bool bFirst = true;
        foreach(QUrl u, l){
          if (bFirst == false) s += ";";
          bFirst = false;
          s += u.toString();          
        }
      }

      QPoint g = mapToGlobal(QPoint(e->pos().x(), e->pos().y()));
      Qt::MouseButtons bu = e->mouseButtons();
      Qt::KeyboardModifiers m = e->keyboardModifiers();
      EVENT_OnDrop(&Cancel, s, e->pos().x(), e->pos().y(), g.x(), g.y(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton, m & Qt::ShiftModifier, m & Qt::ControlModifier, m & Qt::AltModifier); 
      if (Cancel){
        e->ignore(); 
      } else {        
        e->acceptProposedAction();
      }
    }    
#endif
#endif
}

void timerEvent (QTimerEvent *e) 
{
#ifdef SUPERCLASS
    SUPERCLASS::timerEvent(e);
    #ifdef RUN 

    if (e->timerId() == nSingleShot){
      EVENT_OnSingleShot(); 
      killTimer(nSingleShot);
      nSingleShot = 0;
    } else {
      /*
#ifdef _SERIALPORT
      if (e->timerId() == nSerialPort && sp.bytesAvailable()) EVENT_OnEvent();
#endif
      */
      EVENT_OnTimer(); 
    }
    
    #endif        
#endif  
}

void moveEvent ( QMoveEvent * e)
{
#ifdef SUPERCLASS
    SUPERCLASS::moveEvent(e);
    #ifdef RUN 
      EVENT_OnMove(e->pos().x(), e->pos().y(), e->oldPos().x(), e->oldPos().y()); 
    #endif        
#endif  
}
void closeEvent(QCloseEvent * e)
{
  
#ifdef SUPERCLASS
  /*
    #ifdef RUN 
      t_boolean b = true;
      EVENT_OnClose(&b); 
      if (b) SUPERCLASS::closeEvent(e);
    #else*/
      SUPERCLASS::closeEvent(e);
    //#endif        
#endif  
}


void wheelEvent ( QWheelEvent * e )
{
  #ifdef IDE

    e->ignore();
  #elif defined(RUN)
#ifdef SUPERCLASS
    SUPERCLASS::wheelEvent(e);
    { 
      EVENT_OnMouseWheel(e->x(), e->y(), e->globalX(), e->globalY()/*, e->delta()*/);
    }
#endif
 #endif
}


void focusInEvent ( QFocusEvent * e)
{
  #ifdef IDE

//  e->ignore();
  #elif defined(RUN)

#ifdef _EDITOR
  if (bCanPaste != canPaste()){
    bCanPaste = canPaste();
    EVENT_OnEvent1(bTextSelected, bCanPaste, bUndoAvailable, bRedoAvailable);
  }
#endif

#ifdef _IMAGEBUTTON
  if (e->reason() == Qt::TabFocusReason || e->reason() == Qt::BacktabFocusReason){
    qfocusframe = new QFocusFrame((QWidget *) my_form);
    qfocusframe->setWidget(this);
    qfocusframe->show();
  }
#endif

#ifdef SUPERCLASS
    SUPERCLASS::focusInEvent(e);
    { 
      if (my_form) my_form_EVENT_OnGotFocus(my_form);
      EVENT_OnGotFocus();
    }
#endif
#endif
}

void focusOutEvent ( QFocusEvent * e)
{
  #ifdef IDE

//  e->ignore();
  #elif defined(RUN)

#ifdef _IMAGEBUTTON
  if (qfocusframe){
    delete qfocusframe;
    qfocusframe = 0;
  }
#endif

#ifdef SUPERCLASS
    SUPERCLASS::focusOutEvent(e);
    { 
     // static QWidget *w = 0; 
      ControlFocusPrevious = this;
      //w = this;
      if (my_form) my_form_EVENT_OnLostFocus(my_form);
      EVENT_OnLostFocus();
    }
#endif
#endif
}

void enterEvent ( QEvent * e)
{
  #ifdef IDE

  //e->ignore();
  #elif defined(RUN)
#ifdef _IMAGEBUTTON

  {
    QString s = GETPROPERTY_EnterSound();
    if (!s.isEmpty()){
      EXTERN_my_sounds->playOnce(s);
    }
  }

    QString fn;
    if (GETPROPERTY_Enabled()){
      if (GETPROPERTY_Checked()){
        fn = GETPROPERTY_CheckEnterImage(); 
      } else {
        fn = GETPROPERTY_EnterImage(); 
      }
    }
    if (fn.length()){

       if (fn.length() > 200){ // QString contains binary data         

          QPixmap pi;
          if (fn.left(200).contains("<svg ", Qt::CaseInsensitive)){
            fn = fn.trimmed();
            QSvgWidget w(0);
            w.resize(width(), height());
            QSvgRenderer *r = w.renderer();
            if (r->load(fn.toLatin1())){
              QPixmap p(width(), height());
              QPainter painter(&p);
              r->render(&painter);
              pi = p;
            }
          } else {
             pi.loadFromData(fn.toLatin1());
          }       

        if (GETPROPERTY_Scale() && !pi.isNull()){
          pi = pi.scaled(width(), height());
        }
         setAutoFillBackground(true);
         QBrush b(pi);
         QPalette p = palette();
         p.setBrush(QPalette::Window, b);  
         setPalette(p);

       } else {

        QPixmap pi = loadPixmap(fn.contains(".") ? fn : fn + ".png");
        if (GETPROPERTY_Scale() && !pi.isNull()){
          pi = pi.scaled(width(), height());
        }

         setAutoFillBackground(true);
         QBrush b(pi);
         QPalette p = palette();
         p.setBrush(QPalette::Window, b);  
         setPalette(p);

       }
    }
/*
  if (sClickImage != GETPROPERTY_EnterImage()){

    QString fn = GETPROPERTY_EnterImage(); 
    if (fn.length()){

      if (!(fn.contains("/") || fn.contains("\\"))){
        enterImage = my_form_loadProjectImage(my_form, fn.toAscii());
        //oldImage = backgroundPixmap();
        //setBackgroundPixmap( enterImage );
      } else {

        if (QFile::exists( fn )){
          QImage img( fn );

          //enterImage.convertFromImage( img );        
          //oldImage = backgroundPixmap();
          //setBackgroundPixmap( enterImage );
        }
      }
    }
  } else {
    //oldImage = backgroundPixmap();

    //setBackgroundPixmap( enterImage );
  }
  */
#endif   
#ifdef SUPERCLASS
    SUPERCLASS::enterEvent(e);
    { 
      EVENT_OnEnter();
    }
#endif
 #endif
}

void leaveEvent ( QEvent * e)
{
  #ifdef IDE

  //e->ignore();
  #elif defined(RUN)
#ifdef _IMAGEBUTTON

  {
    QString s = GETPROPERTY_ExitSound();
    if (!s.isEmpty()){
      EXTERN_my_sounds->playOnce(s);
    }
  }

    QString fn;
    if (GETPROPERTY_Enabled()){
      if (GETPROPERTY_Checked()){
        fn = GETPROPERTY_CheckExitImage(); 
        if (!fn.length()) fn = GETPROPERTY_CheckEnabledImage(); 
      } else {
        fn = GETPROPERTY_ExitImage(); 
        if (!fn.length()) fn = GETPROPERTY_EnabledImage(); 
      }
    }    
    if (fn.length()){

       if (fn.length() > 200){ // QString contains binary data         

          QPixmap pi;
          if (fn.left(200).contains("<svg ", Qt::CaseInsensitive)){
            fn = fn.trimmed();
            QSvgWidget w(0);
            w.resize(width(), height());
            QSvgRenderer *r = w.renderer();
            if (r->load(fn.toLatin1())){
              QPixmap p(width(), height());
              QPainter painter(&p);
              r->render(&painter);
              pi = p;
            }
          } else {
             pi.loadFromData(fn.toLatin1());
          }       


        if (GETPROPERTY_Scale() && !pi.isNull()){
          pi = pi.scaled(width(), height());
        }

         setAutoFillBackground(true);
         QBrush b(pi);
         QPalette p = palette();
         p.setBrush(QPalette::Window, b);  
         setPalette(p);

       } else {

        QPixmap pi = loadPixmap(fn.contains(".") ? fn : fn + ".png");
        if (GETPROPERTY_Scale() && !pi.isNull()){
          pi = pi.scaled(width(), height());
        }

         setAutoFillBackground(true);
         QBrush b(pi);
         QPalette p = palette();
         p.setBrush(QPalette::Window, b);  
         setPalette(p);

       }
    }

//  if (oldImage){
//     setBackgroundPixmap( oldImage2 );
 // }
#endif
#ifdef SUPERCLASS
    { 
      EVENT_OnExit();
    }    
    SUPERCLASS::leaveEvent(e);
#endif
 #endif
}

#ifdef IDE
void updateControls (int x, int y, int w, int h);
#endif

#if defined(_MENUBARITEM)
#elif defined(_TOOLBARITEM)
#elif defined(_TAB)
void resizeEvent ( QResizeEvent *e);
#else
void resizeEvent ( QResizeEvent *e)
{  
//  if (autoMask()) updateMask();
    
/*#ifdef RUN
#ifdef _TIMER
  hide();
  
  QBitmap bm(size());         
  QColor color0(255, 255, 255);  
  bm.fill(color0);  
  setMask(bm.mask());
  
#endif
#endif*/

#ifdef IDE


    //setUpdatesEnabled(false);

    for (int i = 0; i < 8; i++){
      _selectPanels[i]->reorder();
    }

  #ifdef _FRAME
    QString s = title();
    setTitle(s + " "); // WORK AROUND
    setTitle(s);
  #endif

  #ifdef _LISTBOX
    setFlow(width() > height() ? QListView::LeftToRight : QListView::TopToBottom);
  #endif
/*
  #ifdef _LISTBOX
//    triggerUpdate(true); // WORK AROUND
  #endif

  #ifdef _TEXTAREA
    zoomIn(); // WORK AROUND
    zoomOut(); // WORK AROUND
  #endif
*/

SUPERCLASS::resizeEvent(e);

#ifdef _IMAGEBUTTON
  if (GETPROPERTY_Scale()){            
     setAutoFillBackground(true);
     QPalette p = palette();
     QPixmap pi = p.brush(QPalette::Window).texture();  
     if (!pi.isNull()){
       pi = pi.scaled(width(), height());
       QBrush b(pi);
       p.setBrush(QPalette::Window, b);  
       setPalette(p);
     }
 }
#endif

#ifdef RUN

#ifdef _TOOLBARVIEW
  setOrientation(width() > height() ? Qt::Horizontal : Qt::Vertical);
#endif
#ifdef _LISTBOX
  setFlow(width() > height() ? QListView::LeftToRight : QListView::TopToBottom);
#endif

#endif

 

#ifdef _LABEL
  if (movie) movie->setScaledSize(e->size());
#endif

    //setUpdatesEnabled(true);

#elif defined(RUN)
#ifdef SUPERCLASS
    SUPERCLASS::resizeEvent(e);
#ifdef _LABEL
    if (movie) movie->setScaledSize(e->size());
#endif

#ifdef _IMAGEBUTTON
  if (GETPROPERTY_Scale()){            
     setAutoFillBackground(true);
     QPalette p = palette();
     QPixmap pi = p.brush(QPalette::Window).texture();  
     if (!pi.isNull()){
       pi = pi.scaled(width(), height());
       QBrush b(pi);
       p.setBrush(QPalette::Window, b);  
       setPalette(p);
     }
  }
#endif

    { 
      EVENT_OnResize(e->size().width(), e->size().height(), e->oldSize().width(), e->oldSize().height()); 
    }    
#endif
 #endif

}
#endif

#if defined(_MENUBARITEM)
#elif defined(_TOOLBARITEM)
#else

void paintEvent ( QPaintEvent * e)
{
  //if (bForm) MYLOG("paintEvent");

  if (!bForm || GETPROPERTY_DrawOnPaint()){
    if (bBackgroundStyle){
      QPainter p( this );

      int w = width();
      int h = height();
      int h2 = h / 2;
      //int w3 = w - w2;

      QColor c = cBackground;

      for (int y = 0; y < h2; y++){
        p.setPen(c);
        p.drawLine(0, y, w, y);
        c = c.darker(102);
      }

      c = c.darker(125);
      for (int y = h2; y < h; y++){      
        p.setPen(c);
        p.drawLine(0, y, w, y);
        c = c.lighter(102);
      }

    }
  #ifdef SUPERCLASS  
    SUPERCLASS::paintEvent(e);
  #endif
#ifdef _IMAGEBUTTON
  QString s = GETPROPERTY_Caption();
  QString s2 = GETPROPERTY_Icon();
  if (!s.isEmpty() && !s2.isEmpty()){
    QPainter p(this);
    p.setPen(palette().color(QPalette::ButtonText));
    p.setFont(font());
    p.drawText(0, 0, width(), height(), Qt::AlignCenter, s);
    int x = (width() / 4) - qpixmap.width() * 2;
    if (x - 5 < 0) x = 5;
    p.drawPixmap(x, (height() / 2) - (qpixmap.height() / 2), qpixmap);
  } else if (!s.isEmpty()){
    QPainter p(this);
    p.setPen(palette().color(QPalette::ButtonText));
    p.setFont(font());
    p.drawText(0, 0, width(), height(), Qt::AlignCenter, s);
  } else if (!s2.isEmpty()){
    QPainter p(this);
    p.drawPixmap((width() / 2) - (qpixmap.width() / 2), (height() / 2) - (qpixmap.height() / 2), qpixmap);
  }
#endif
  }
#ifdef IDE

    //setUpdatesEnabled(false);

    if (acceptDrops()){ // missused as selected flag
      for (int i = 0; i < 8; i++){
       _selectPanels[i]->show();
      }
    } else {
      for (int i = 0; i < 8; i++){
       _selectPanels[i]->hide();
      }
    }

    //setUpdatesEnabled(true);
#endif

#ifdef IDE
  #ifdef _VHBOX  
    QPainter p( this );

    QGridLayout *l = (QGridLayout *) layout();

    int cc = l->columnCount();
    int rc = l->rowCount();

    int w = width();
    int h = height();

    int w2 = width() / (cc + 1);
    int h2 = height() / (rc + 1);

    for (int yy = 0; yy < rc; yy++){
      if (yy % 2){
        p.setPen(Qt::white);
      } else {
        p.setPen(Qt::black);
      }
      p.drawLine(0, (yy + 1) * h2, w, (yy + 1) * h2);
    }

    for (int xx = 0; xx < cc; xx++){
      if (xx % 2){
        p.setPen(Qt::white);
      } else {
        p.setPen(Qt::black);
      }
      p.drawLine((xx + 1) * w2, 0, (xx + 1) * w2, h);
    }

  #endif
#endif
#ifdef RUN
#ifdef _CHILDCONTROL
#else
    QRect r = e->rect();
    EVENT_OnPaint(r.x(), r.y(), r.width(), r.height()); 
#endif
#endif
}


void changeEvent( QEvent * e)
{
#ifdef SUPERCLASS  
  SUPERCLASS::changeEvent(e);
#endif
  #ifdef RUN
    if (e->type() == QEvent::EnabledChange){
      if (isEnabled()){
        EVENT_OnEnabled(); 
      } else {
        EVENT_OnDisabled(); 
      }
    }    
  #endif   
}

void showEvent ( QShowEvent * e)
{
#ifdef SUPERCLASS  
  SUPERCLASS::showEvent(e);
#endif
  #ifdef RUN
    EVENT_OnShow(); 
  #endif   
}

void hideEvent ( QHideEvent * e)
{
#ifdef SUPERCLASS  
  SUPERCLASS::hideEvent(e);
#endif
  #ifdef RUN
    EVENT_OnHide(); 
  #endif 
}

/*
void SETPROPERTY_X(int n)
{   
  if (GETPROPERTY_X() != n){   

#ifdef RUN
    _SETPROPERTY_X(my_form, this, n);
#endif
    //move(m + n, y());
    
    _property::SETPROPERTY_X(n);
  }
}

void SETPROPERTY_Y(int n)
{ 
  if (GETPROPERTY_Y() != n){

#ifdef RUN
    _SETPROPERTY_Y(my_form, this, n);
#endif
    //move(x(), n);
    _property::SETPROPERTY_Y(n);
  }

}*/

void SETPROPERTY_Width(int n)
{ 
#ifdef _TAB
    setFixedSize(n, height());
    _property::SETPROPERTY_Width(n);
#else
  if (GETPROPERTY_Width() != n){
    resize(n, height());
    _property::SETPROPERTY_Width(n);
  }
#endif
}

void SETPROPERTY_Height(int n)
{ 
#ifdef _TAB
    setFixedSize(width(), n);
    _property::SETPROPERTY_Height(n);
#else
  if (GETPROPERTY_Height() != n){    
    resize(width(), n);
    _property::SETPROPERTY_Height(n);
  }
#endif
}

void setGeo(int x, int y, int w, int h)
{
  setGeometry(x, y, w, h);
  /*
  SETPROPERTY_X(x);
  SETPROPERTY_Y(y);
  SETPROPERTY_Width(w);
  SETPROPERTY_Height(h);*/
}


void setXYWidthHeight(int x, int y, int w, int h)
{
  SETPROPERTY_X(x);
  SETPROPERTY_Y(y);
  SETPROPERTY_Width(w);
  SETPROPERTY_Height(h);
}

void incX(int n)
{
  //SETPROPERTY_X(x() + n);
  move(x() + n, y());

  //int mx = my_form_XScrollBar_value(my_form);
  //if (mx)
  {
    SETPROPERTY_X(GETPROPERTY_X() + n);
  }
  
}

void incY(int n)
{
  //SETPROPERTY_Y(y() + n);
  move(x(), y() + n);
  SETPROPERTY_Y(GETPROPERTY_Y() + n);

}

void decX(int n)
{
  //SETPROPERTY_X(x() - n);
  move(x() - n, y());

  //int mx = my_form_XScrollBar_value(my_form);
 // if (mx)
  {
    SETPROPERTY_X(GETPROPERTY_X() - n);
  }
  
}

void decY(int n)
{
  //SETPROPERTY_Y(y() - n);
  move(x(), y() - n);
  SETPROPERTY_Y(GETPROPERTY_Y() - n);
}

void incWidth(int n)
{
  SETPROPERTY_Width(width() + n);
  resize(width() + n, height());
}

void incHeight(int n)
{
  SETPROPERTY_Height(height() + n);
  resize(width(), height() + n);
}

void decWidth(int n)
{
  SETPROPERTY_Width(width() - n);
  resize(width() - n, height());
}

void decHeight(int n)
{
  SETPROPERTY_Height(height() - n);
  resize(width(), height() - n);
}
#endif

//bool selected;


protected:
QString sName;
QString sGroup;

const char *acName;
const char *acGroup;
QByteArray a;
QByteArray b;

public:
_form *my_form;
private:
QObject *SENDER;

//QWidget *PROPERTY_parent;

#ifdef IDE
_selectPanel *_selectPanels[8];
#endif




bool bEventClick;
bool bEventKeyPress;


const QPixmap &loadPixmap(QString fn)
{
  static QPixmap p;

  p = QPixmap();
  if (!(fn.contains("/") || fn.contains("\\"))){
/*
    if (!p.isValid()){
      fn = qApp->applicationDirPath() + "/" + fn; // try a file in the directory, where the exe is
      goto re;
    }
*/
#ifdef RUN
      p = my_form_loadProjectImage(my_form, fn);
#elif defined (IDE)

      #ifdef _FORM
        fn = getPath() + "/" + fn;
      #else
        fn = getProjectPath() + "/" + fn;
      #endif

      if (QFile::exists(fn)){
        p = QPixmap(fn);
      }

#endif
    
  } else {
//re:
    if (QFile::exists(fn)){
      p = QPixmap(fn);
    }
    
  }

  return p;
  
}

private:
  QMovie *movie; QByteArray *moviea; QBuffer *movieb;
  QMovie *cursoranimation_movie; QByteArray *cursoranimation_moviea; QBuffer *cursoranimation_movieb;

  bool bForm;

public slots:
void frameChanged(int)
{
#if defined(_COMMANDBUTTON) || defined(_COMMANDLINKBUTTON) || defined(_TOOLBUTTON) || defined(_CHECKBOX) || defined(_RADIOBUTTON)
    setIcon(movie->currentPixmap());
#elif defined(_FORM)
    setWindowIcon(movie->currentPixmap());
#elif defined(_MENUBARITEM)
  #ifdef RUN
    if (my_qaction) my_qaction->setIcon(movie->currentPixmap());
  #endif
#elif defined(_TOOLBARITEM)
  #ifdef RUN
    if (my_qaction) my_qaction->setIcon(movie->currentPixmap());
  #endif
#endif
}

void cursoranimation_frameChanged(int)
{
  setCursor(QCursor(cursoranimation_movie->currentPixmap()));
}

private:

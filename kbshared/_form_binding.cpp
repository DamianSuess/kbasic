/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).
***************************************************************************
*/

#include <QtGui>

#include "_form.h"
#include "_report.h"



#ifdef IDE
#include <QtSql>
extern QSqlDatabase CurrentDatabase;

extern QWidget *cInsertControl;

#include "../kbide/_help.h"
#include "../kbide/_qbe_tables.h"

#include "../kbide/_projectwindow.h"
#include "../kbide/_parserwindow.h"
#include "../kbide/_sourcecodeeditor.h"
#include "../kbide/_toolboxwindow_form.h"
#include "../kbide/_toolboxwindow_vista.h"
#include "../kbide/_helpwindow_shortcut.h"

extern QDockWidget *EXTERN_ToolboxForm;
extern QDockWidget *EXTERN_ToolboxReport;
extern QDockWidget *EXTERN_ToolboxMenuBar;
extern QDockWidget *EXTERN_ToolboxToolBar;
extern QDockWidget *EXTERN_Helpwindow_shortcut;

extern int nInsert_Width;
extern int nInsert_Height;

extern _parserwindow *EXTERN_my_parserwindow;


extern _propertywindow *EXTERN_my_propertywindow;
extern _toolboxwindow_form *EXTERN_my_toolboxwindow_form;
extern _toolboxwindow_vista *EXTERN_my_toolboxwindow_vista;
extern const QIcon &kbasicIcon(QString s);

extern QMdiArea *forms_workspace;


extern int nPropertyWindowForWhat;
#endif


extern _form *EXTERN_my_form;



#ifdef IDE


extern QString sInsertTypeOption;

extern QList<QWidget *>cCut;
extern QList<QWidget *>cPasted;
extern QList<t_properties *>apply_properties;


extern int nCutMinX;
extern int nCutMinY;

extern bool bApply;
extern bool bCopy;
extern bool bCut;
extern _form *cutForm;
extern QDockWidget *EXTERN_PropertyWindow;

extern _report *EXTERN_my_report;
extern QString idePath(QString s);
extern _projectwindow *EXTERN_my_projectwindow;

#endif



#ifdef RUN



extern bool bSDI;

#include "_application.h"

#include "../kbshared/_log.h"

extern bool bBlock_qApp_processEvents;

extern QMap<QString,QString>trs;


extern _log *my_log;

extern QMap<QString,int>forms2;
extern int nCurrentFormId;

extern bool bOpenonrun_forms;

extern QMainWindow *forms_mainwindow;
extern _menubar *EXTERN_my_menubar;
extern bool bLogin;

extern QWidget *ControlFocusPrevious;

#endif

extern QWidget *min;





bool _form::loadControl(QString *s, _controlType ct, QString sName, QWidget *c)
{ 
  bool bWebView = c != 0;

  if (ct == t_notype){
    ct = t_editor;
  }

 
  if (bWebView == false){
#ifdef IDE
  #define SWITCH4 (this);
#endif
#ifdef RUN
  #define SWITCH4 (this, main, sName);
#endif
  #define SWITCH3 c
  #include "_form_property_switch.h" 
  #undef SWITCH3
  #undef SWITCH4
  }

  if (bWebView == false){
    c->setHidden(true);
    METHOD_insertControl(c, ct, -1, -1, false, sName, false);
  }


#ifdef RUN
  /*
    if (ct == t_hidden){
//      c->setAutoMask(true);
    }
    if (ct == t_timer){
     // c->setAutoMask(true);
    }
    */
 
#endif
  int nTabIndex = 0;
  int X = 0;
  int Y = 0;
  int W = 0;
  int H = 0;

  QString sToolBarView = "";
  QWidget *ToolBarView = 0;

  QString sChildControl = "";
  QWidget *ChildControl = 0;
  QString sPages = "";
  QString sChildControlName = "";  

  do {

    const char *sss = (*s).toAscii();

    *s = (*s).trimmed();

    QString sKey;    

    bool bb;
    QString ss;
    int nn;
    double dd;

    #define SWITCH loadProperty(s, &sKey, &bb, &ss, &nn);
    #include "_form_property_switch.h"    

  if (sKey == "X"){      

    X = nn;

  } else if (sKey == "Y"){      

    Y = nn;

  } else if (sKey == "Width"){ 
    W = nn;

  } else if (sKey == "Height"){      
    H = nn;

  } else if (sKey == "Pages"){      
    sPages = ss;

  } else if (sKey == "TabIndex"){
    nTabIndex = nn;

    #define SWITCH SETPROPERTY_TabIndex(nn);
    #include "_form_property_switch.h"     

  } else if (sKey == "StringValue"){      
    #define SWITCH SETPROPERTY_StringValue(ss);
    #include "_form_property_switch.h"     

#ifdef RUN
    if (controlType(c) == t_childcontrol){
      sChildControl = ss;
      ChildControl = c;        
    } else if (controlType(c) == t_toolbarview){
      sToolBarView = ss;
      ToolBarView = c;        
    }
#endif

  } else if (sKey == "Layout"){ 
    #define SWITCH SETPROPERTY_Layout(ss);
    #include "_form_property_switch.h"      

  } else {
    applyProperty(c, sKey, bb, ss, nn, dd);
  }

  } while ( !((*s).length() <= 0 || (*s).startsWith("End")) );

  *s = (*s).mid(3); // eat 'End'

  c->setGeometry(X, Y, W, H);

  #define SWITCH SETPROPERTY_X(X); 
  #include "_form_property_switch.h"   

  #define SWITCH SETPROPERTY_Y(Y); 
  #include "_form_property_switch.h"   

  #define SWITCH SETPROPERTY_Height(H); 
  #include "_form_property_switch.h"   

  #define SWITCH SETPROPERTY_Width(W); 
  #include "_form_property_switch.h"   

  #define SWITCH SETPROPERTY_LoadedX(X); 
  #include "_form_property_switch.h"   

  #define SWITCH SETPROPERTY_LoadedY(Y); 
  #include "_form_property_switch.h"   

  #define SWITCH SETPROPERTY_LoadedHeight(H); 
  #include "_form_property_switch.h"   

  #define SWITCH SETPROPERTY_LoadedWidth(W); 
  #include "_form_property_switch.h"   

  if (!sPages.isEmpty()){
    #define SWITCH SETPROPERTY_Pages(sPages);
    #include "_form_property_switch.h"     
  }

#ifdef RUN
  if (!sChildControl.isEmpty()){
    _childcontrol *cc = ((_childcontrol *) ChildControl);
    nCurrentFormId = forms2[sChildControl];

    cc->ParentForm = interpreter::openForm(sChildControl, (kb_form *) this/*, X, Y, H, W*/);

    layout_childcontrols[(_form *) cc->ParentForm] = (_childcontrol *) ChildControl;//sChildControlLayout;
  }
  if (!sToolBarView.isEmpty()){

    ((_toolbarview *) ToolBarView)->loadToolbar(sToolBarView);
    
    QWidget *w = (QWidget *) new QWidget(this); // needed to expand the toolbarview to the right size
    w->setMinimumSize(10000, 20);
    ((_toolbarview *) ToolBarView)->addWidget(w);
    
    ToolBarView->show();

  }
#endif

  return true;
}

void _form::applyProperty(QWidget *c, QString sKey, bool bb, QString &ss, int nn, double dd)
{ 

  if (sKey == "Caption"){      
    #define SWITCH SETPROPERTY_Caption(ss);
    #include "_form_property_switch.h"       

  } else if (sKey == "SQL"){ 
    sKey = sKey;
    #define SWITCH SETPROPERTY_SQL(ss);
    #include "_form_property_switch.h"        


  } else if (sKey == "StringValue"){      
    #define SWITCH SETPROPERTY_StringValue(ss);
    #include "_form_property_switch.h"     


  } else if (sKey == "Interval"){      
    #define SWITCH SETPROPERTY_Interval(nn);
    #include "_form_property_switch.h"     

  } else if (sKey == "IntegerValue"){      
    #define SWITCH SETPROPERTY_IntegerValue(nn);
    #include "_form_property_switch.h"   


  } else if (sKey == "Shape"){      
    #define SWITCH SETPROPERTY_Shape(bb);
    #include "_form_property_switch.h"   

  } else if (sKey == "Enabled"){      
    #define SWITCH SETPROPERTY_Enabled(bb);
    #include "_form_property_switch.h"   

  } else if (sKey == "Flip"){      
    #define SWITCH SETPROPERTY_Flip(bb);
    #include "_form_property_switch.h"   

  } else if (sKey == "Cursor"){      
    #define SWITCH SETPROPERTY_Cursor(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "TabIndex"){      
    #define SWITCH SETPROPERTY_TabIndex(nn);
    #include "_form_property_switch.h"     

  } else if (sKey == "ParentIndex"){      
    #define SWITCH SETPROPERTY_ParentIndex(nn);
    #include "_form_property_switch.h"     

  }
  
  if (sKey == "Tag"){      
    #define SWITCH SETPROPERTY_Tag(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "Visible"){      
    #define SWITCH SETPROPERTY_Visible(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "Resizable"){      
    #define SWITCH SETPROPERTY_Resizable(bb);
    #include "_form_property_switch.h"          

  } else if (sKey == "ResizableSmaller"){      
    #define SWITCH SETPROPERTY_ResizableSmaller(bb);
    #include "_form_property_switch.h"          

  } else if (sKey == "ResizableBigger"){      
    #define SWITCH SETPROPERTY_ResizableBigger(bb);
    #include "_form_property_switch.h"          

  } else if (sKey == "WordWrap"){      
    #define SWITCH SETPROPERTY_WordWrap(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "ReadOnly"){      
    #define SWITCH SETPROPERTY_ReadOnly(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "Alignment"){      
    #define SWITCH SETPROPERTY_Alignment(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "EchoMode"){      
    #define SWITCH SETPROPERTY_EchoMode(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "Feature"){      
    #define SWITCH SETPROPERTY_Feature(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "Orientation"){      
    #define SWITCH SETPROPERTY_Orientation(ss);
    #include "_form_property_switch.h"     


  } else if (sKey == "Group"){ 
    #define SWITCH SETPROPERTY_Group(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "Background"){ 
    #define SWITCH SETPROPERTY_Background(ss);
    #include "_form_property_switch.h"      
  
  } else if (sKey == "BackgroundStyle"){ 
    #define SWITCH SETPROPERTY_BackgroundStyle(ss);
    #include "_form_property_switch.h"      
  
  } else if (sKey == "Palette"){ 
    #define SWITCH SETPROPERTY_Palette(ss);
    #include "_form_property_switch.h"      
  
  } 
  
  if (sKey == "MinimumWidth"){ 
    #define SWITCH SETPROPERTY_MinimumWidth(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "MinimumHeight"){ 
    #define SWITCH SETPROPERTY_MinimumHeight(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "MaximumWidth"){ 
    #define SWITCH SETPROPERTY_MaximumWidth(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "MaximumHeight"){ 
    #define SWITCH SETPROPERTY_MaximumHeight(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "CSV"){
    #define SWITCH SETPROPERTY_CSV(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "Tag"){
    #define SWITCH SETPROPERTY_Tag(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "TableView"){ 
    #define SWITCH SETPROPERTY_TableView(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "BoxIndex"){ 
    #define SWITCH SETPROPERTY_BoxIndex(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "BoxX"){ 
    #define SWITCH SETPROPERTY_BoxX(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "BoxY"){ 
    #define SWITCH SETPROPERTY_BoxY(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "SplitIndex"){ 
    #define SWITCH SETPROPERTY_SplitIndex(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "Scale"){ 
    #define SWITCH SETPROPERTY_Scale(bb);
    #include "_form_property_switch.h"      
/*
  } else if (sKey == "FormCentered"){
    #define SWITCH SETPROPERTY_FormCentered(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "FormScaled"){
    #define SWITCH SETPROPERTY_FormScaled(bb);
    #include "_form_property_switch.h"      
*/
  } else if (sKey == "DragDrop"){ 
    #define SWITCH SETPROPERTY_DragDrop(bb);
    #include "_form_property_switch.h"      
  
  } else if (sKey == "FocusPolicy"){ 
    #define SWITCH SETPROPERTY_FocusPolicy(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "FocusProxy"){ 
    #define SWITCH SETPROPERTY_FocusProxy(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "FocusOrder"){ 
    #define SWITCH SETPROPERTY_FocusOrder(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "FontName"){
    #define SWITCH SETPROPERTY_FontName(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "FontSize"){ 
    #define SWITCH SETPROPERTY_FontSize(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "FontBold"){ 
    #define SWITCH SETPROPERTY_FontBold(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "FontItalic"){ 
    #define SWITCH SETPROPERTY_FontItalic(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "FontUnderline"){ 
    #define SWITCH SETPROPERTY_FontUnderline(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "FontColor"){
    
    #define SWITCH SETPROPERTY_FontColor(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "StatusTip"){ 
    #define SWITCH SETPROPERTY_StatusTip(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "ToolTip"){ 
    #define SWITCH SETPROPERTY_ToolTip(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "StyleSheet"){ 
    #define SWITCH SETPROPERTY_StyleSheet(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "WhatsThis"){ 
    #define SWITCH SETPROPERTY_WhatsThis(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "Flag"){ 
    #define SWITCH SETPROPERTY_Flag(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "Icon"){ 
    #define SWITCH SETPROPERTY_Icon(ss);
    #include "_form_property_switch.h"      
/*
  } else if (sKey == "IconCaption"){
    #define SWITCH SETPROPERTY_IconCaption(ss);
    #include "_form_property_switch.h"      
*/
  } else if (sKey == "Caption"){ 
    #define SWITCH SETPROPERTY_Caption(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "Modal"){
    #define SWITCH SETPROPERTY_Modal(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "Opacity"){ 
    #define SWITCH SETPROPERTY_Modal(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "TimerInterval"){
    #define SWITCH SETPROPERTY_TimerInterval(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "Shadow"){ 
    #define SWITCH SETPROPERTY_Shadow(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "Shape"){
    #define SWITCH SETPROPERTY_Shape(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "OpenLinks"){ 
    #define SWITCH SETPROPERTY_OpenLinks(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "Icon"){
    #define SWITCH SETPROPERTY_Icon(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "InputControl"){
    #define SWITCH SETPROPERTY_InputControl(ss);
    #include "_form_property_switch.h"      
  
  } else if (sKey == "Space"){ 
    #define SWITCH SETPROPERTY_Space(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "Border"){ 
    #define SWITCH SETPROPERTY_Border(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "Flat"){
    #define SWITCH SETPROPERTY_Flat(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "Key"){ SETPROPERTY_Key(ss);
    #define SWITCH SETPROPERTY_Key(ss);
    #include "_form_property_switch.h"      
      
  } else if (sKey == "IntegerMaximum"){ 
    #define SWITCH SETPROPERTY_IntegerMaximum(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "IntegerMinimum"){ 
    #define SWITCH SETPROPERTY_IntegerMinimum(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "Completer"){ 
    #define SWITCH SETPROPERTY_Completer(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "ValidatorDouble"){ 
    #define SWITCH SETPROPERTY_ValidatorDouble(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "ValidatorInteger"){
    #define SWITCH SETPROPERTY_ValidatorInteger(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "ValidatorRegEx"){
    #define SWITCH SETPROPERTY_ValidatorRegEx(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "ValidatorRegEx2"){ 
    #define SWITCH SETPROPERTY_ValidatorRegEx2(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "DoubleEntry"){
    #define SWITCH SETPROPERTY_DoubleEntry(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "InsertPolicy"){
    #define SWITCH SETPROPERTY_InsertPolicy(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "Editable"){ 
    #define SWITCH SETPROPERTY_Editable(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "MaximumVisible"){
    #define SWITCH SETPROPERTY_MaximumVisible(nn);
    #include "_form_property_switch.h"      

  }// else 
    
  if (sKey == "Sorted"){ 
    #define SWITCH SETPROPERTY_Sorted(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "StringMaximum"){
    #define SWITCH SETPROPERTY_StringMaximum(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "StringMinimum"){ 
    #define SWITCH SETPROPERTY_StringMinimum(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "Format"){ 
    #define SWITCH SETPROPERTY_Format(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "PopUp"){
    #define SWITCH SETPROPERTY_PopUp(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "ScrollBar"){ 
    #define SWITCH SETPROPERTY_ScrollBar(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "MouseDownImage"){
    #define SWITCH SETPROPERTY_MouseDownImage(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "MouseUpImage"){ 
    #define SWITCH SETPROPERTY_MouseUpImage(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "EnabledImage"){ 
    #define SWITCH SETPROPERTY_EnabledImage(ss);
    #include "_form_property_switch.h"   

  } else if (sKey == "EnterImage"){ 
    #define SWITCH SETPROPERTY_EnterImage(ss);
    #include "_form_property_switch.h"   

  } else if (sKey == "CheckMouseDownImage"){
    #define SWITCH SETPROPERTY_CheckMouseDownImage(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "CheckMouseUpImage"){ 
    #define SWITCH SETPROPERTY_CheckMouseUpImage(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "CheckEnabledImage"){ 
    #define SWITCH SETPROPERTY_CheckEnabledImage(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "MouseDownSound"){
    #define SWITCH SETPROPERTY_MouseDownSound(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "MouseUpSound"){
    #define SWITCH SETPROPERTY_MouseUpSound(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "HomeURL"){ 
    #define SWITCH SETPROPERTY_HomeURL(ss);
    #include "_form_property_switch.h"      


  } else if (sKey == "Brightness"){ 
    #define SWITCH SETPROPERTY_Brightness(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "Contrast"){ 
    #define SWITCH SETPROPERTY_Contrast(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "Hue"){ 
    #define SWITCH SETPROPERTY_Hue(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "Saturation"){ 
    #define SWITCH SETPROPERTY_Saturation(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "ScaleMode"){ 
    #define SWITCH SETPROPERTY_ScaleMode(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "AspectRatio"){ 
    #define SWITCH SETPROPERTY_AspectRatio(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "TransitionTime"){ 
    #define SWITCH SETPROPERTY_TransitionTime(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "Muted"){ 
    #define SWITCH SETPROPERTY_Muted(bb);
    #include "_form_property_switch.h"      

  } else if (sKey == "Volume"){ 
    #define SWITCH SETPROPERTY_Volume(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "PrefinishMark"){ 
    #define SWITCH SETPROPERTY_PrefinishMark(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "Tick"){ 
    #define SWITCH SETPROPERTY_Tick(nn);
    #include "_form_property_switch.h"      

  } else if (sKey == "OnTick"){ 
    #define SWITCH SETPROPERTY_OnTick(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnStateChanged"){ 
    #define SWITCH SETPROPERTY_OnStateChanged(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnAboutToFinish"){ 
    #define SWITCH SETPROPERTY_OnAboutToFinish(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnFinished"){ 
    #define SWITCH SETPROPERTY_OnFinished(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnMutedChanged"){ 
    #define SWITCH SETPROPERTY_OnMutedChanged(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnVolumeChanged"){ 
    #define SWITCH SETPROPERTY_OnVolumeChanged(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnPlayedTitleChanged"){ 
    #define SWITCH SETPROPERTY_OnPlayingTitleChanged(bb);
    #include "_form_property_switch.h"  

  } else if (sKey == "OnBufferStatus"){ 
    #define SWITCH SETPROPERTY_OnBufferStatus(bb);
    #include "_form_property_switch.h" 

  } else if (sKey == "OnTotalTimeChanged"){ 
    #define SWITCH SETPROPERTY_OnTotalTimeChanged(bb);
    #include "_form_property_switch.h"     


  // PROPERTY      

  } else if (sKey == "Prefix"){ 
    #define SWITCH SETPROPERTY_Prefix(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "Suffix"){ 
    #define SWITCH SETPROPERTY_Suffix(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "TickPosition"){ 
    #define SWITCH SETPROPERTY_TickPosition(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "InvertedAppearance"){ 
    #define SWITCH SETPROPERTY_InvertedAppearance(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "InvertedControls"){ 
    #define SWITCH SETPROPERTY_InvertedControls(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "Tracking"){ 
    #define SWITCH SETPROPERTY_Tracking(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "TickInterval"){ 
    #define SWITCH SETPROPERTY_TickInterval(nn);
    #include "_form_property_switch.h"    

  } else if (sKey == "PageStep"){ 
    #define SWITCH SETPROPERTY_PageStep(nn);
    #include "_form_property_switch.h"    

  } else if (sKey == "SingleStep"){ 
    #define SWITCH SETPROPERTY_SingleStep(nn);
    #include "_form_property_switch.h"    

  } else if (sKey == "ViewMode"){ 
    #define SWITCH SETPROPERTY_ViewMode(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "Description"){ 
    #define SWITCH SETPROPERTY_Description(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "MoveOnMouseDrag"){ 
    #define SWITCH SETPROPERTY_MoveOnMouseDrag(bb);
    #include "_form_property_switch.h"    


  } else if (sKey == "MouseTracking"){ 
    #define SWITCH SETPROPERTY_MouseTracking(bb);
    #include "_form_property_switch.h"    


  } else if (sKey == "DrawOnPaint"){ 
    #define SWITCH SETPROPERTY_DrawOnPaint(bb);
    #include "_form_property_switch.h"    

    

  } else if (sKey == "ActionId"){ 
    #define SWITCH SETPROPERTY_ActionId(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "SoundOnEvent"){ 
    #define SWITCH SETPROPERTY_SoundOnEvent(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "CursorAnimation"){ 
    #define SWITCH SETPROPERTY_CursorAnimation(ss);
    #include "_form_property_switch.h"    

    


  } else if (sKey == "RootIsDecorated"){ 
    #define SWITCH SETPROPERTY_RootIsDecorated(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "Checked"){ 
    #define SWITCH SETPROPERTY_Checked(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "CheckableExclusive"){ 
    #define SWITCH SETPROPERTY_CheckableExclusive(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "ContextMenu"){ 
    #define SWITCH SETPROPERTY_ContextMenu(ss);
    #include "_form_property_switch.h"   

  } else if (sKey == "PortName"){ 
    #define SWITCH SETPROPERTY_PortName(ss);
    #include "_form_property_switch.h"   

  } else if (sKey == "BaudRate"){ 
    #define SWITCH SETPROPERTY_BaudRate(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "DataBits"){ 
    #define SWITCH SETPROPERTY_DataBits(ss);
    #include "_form_property_switch.h" 

  } else if (sKey == "Parity"){ 
    #define SWITCH SETPROPERTY_Parity(ss);
    #include "_form_property_switch.h"  

  } else if (sKey == "FlowControl"){ 
    #define SWITCH SETPROPERTY_FlowControl(ss);
    #include "_form_property_switch.h"  

  } else if (sKey == "StopBits"){ 
    #define SWITCH SETPROPERTY_StopBits(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "TimeOutMillisec"){ 
    #define SWITCH SETPROPERTY_TimeOutMillisec(nn);
    #include "_form_property_switch.h"  

  } else if (sKey == "PollingInterval"){ 
    #define SWITCH SETPROPERTY_PollingInterval(nn);
    #include "_form_property_switch.h"  



  } else if (sKey == "Comment1Begin"){ 
    #define SWITCH SETPROPERTY_Comment1Begin(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "Comment1End"){ 
    #define SWITCH SETPROPERTY_Comment1End(ss);
    #include "_form_property_switch.h"      

  } else if (sKey == "Comment2Begin"){ 
    #define SWITCH SETPROPERTY_Comment2Begin(ss);
    #include "_form_property_switch.h"      
/*
  } else if (sKey == "Comment2End"){ 
    #define SWITCH SETPROPERTY_Comment2End(ss);
    #include "_form_property_switch.h"     
*/
  } else if (sKey == "Keywords"){ 
    #define SWITCH SETPROPERTY_Keywords(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "Commands"){ 
    #define SWITCH SETPROPERTY_Commands(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "CommentColor"){ 
    #define SWITCH SETPROPERTY_CommentColor(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "KeywordColor"){ 
    #define SWITCH SETPROPERTY_KeywordColor(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "CommandColor"){ 
    #define SWITCH SETPROPERTY_CommandColor(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "OnPrint"){ 
    #define SWITCH SETPROPERTY_OnPrint(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "OnCurrentItemChanged"){ 
    #define SWITCH SETPROPERTY_OnCurrentItemChanged(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "OnItemActivated"){ 
    #define SWITCH SETPROPERTY_OnItemActivated(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "OnItemChanged"){ 
    #define SWITCH SETPROPERTY_OnItemChanged(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "OnItemClicked"){ 
    #define SWITCH SETPROPERTY_OnItemClicked(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "OnItemCollapsed"){ 
    #define SWITCH SETPROPERTY_OnItemCollapsed(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "OnItemDoubleClicked"){ 
    #define SWITCH SETPROPERTY_OnItemDoubleClicked(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnItemEntered"){ 
    #define SWITCH SETPROPERTY_OnItemEntered(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnItemExpanded"){ 
    #define SWITCH SETPROPERTY_OnItemExpanded(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnItemPressed"){ 
    #define SWITCH SETPROPERTY_OnItemPressed(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnItemSelectionChanged"){ 
    #define SWITCH SETPROPERTY_OnItemSelectionChanged(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDockMove"){ 
    #define SWITCH SETPROPERTY_OnDockMove(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDockShow"){ 
    #define SWITCH SETPROPERTY_OnDockShow(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDockHide"){ 
    #define SWITCH SETPROPERTY_OnDockHide(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDockFloating"){ 
    #define SWITCH SETPROPERTY_OnDockFloating(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDockNotFloating"){ 
    #define SWITCH SETPROPERTY_OnDockNotFloating(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "Dock"){ 
    #define SWITCH SETPROPERTY_Dock(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "SelectionMode"){ 
    #define SWITCH SETPROPERTY_SelectionMode(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "AlternatingRowColors"){ 
    #define SWITCH SETPROPERTY_AlternatingRowColors(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "SQLName"){ 
    #define SWITCH SETPROPERTY_SQLName(ss);
    #include "_form_property_switch.h"        


  } else if (sKey == "SQLRelation"){ 
    #define SWITCH SETPROPERTY_SQLRelation(ss);
    #include "_form_property_switch.h"    
/*
  } else if (sKey == "SQLInsert"){ 
    #define SWITCH SETPROPERTY_SQLInsert(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "SQLUpdate"){ 
    #define SWITCH SETPROPERTY_SQLUpdate(bb);
    #include "_form_property_switch.h"   

  } else if (sKey == "SQLDelete"){ 
    #define SWITCH SETPROPERTY_SQLDelete(bb);
    #include "_form_property_switch.h"   
*/
  } else if (sKey == "TableViewCaption"){ 
    #define SWITCH SETPROPERTY_TableViewCaption(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "TableViewSort"){ 
    #define SWITCH SETPROPERTY_TableViewSort(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "TableViewFilter"){ 
    #define SWITCH SETPROPERTY_TableViewFilter(ss);
    #include "_form_property_switch.h"    

  } else if (sKey == "TableViewWidth"){ 
    #define SWITCH SETPROPERTY_TableViewWidth(nn);
    #include "_form_property_switch.h"    

  } else if (sKey == "TableViewVisible"){ 
    #define SWITCH SETPROPERTY_TableViewVisible(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "TableViewOrder"){ 
    #define SWITCH SETPROPERTY_TableViewOrder(nn);
    #include "_form_property_switch.h"    

  } else if (sKey == "ParentForm"){     
    #define SWITCH SETPROPERTY_ParentForm(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "ParentControl"){   
 
    #define SWITCH SETPROPERTY_ParentControl(ss);
    #include "_form_property_switch.h"     
    /*
  } else if (sKey == "TabIndex"){
    nTabIndex = nn;

    #define SWITCH SETPROPERTY_TabIndex(nn);
    #include "_form_property_switch.h"     
*/

  } else if (sKey == "ExitImage"){      
    #define SWITCH SETPROPERTY_ExitImage(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "CheckDisabledImage"){      
    #define SWITCH SETPROPERTY_CheckDisabledImage(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "CheckExitImage"){      
    #define SWITCH SETPROPERTY_CheckExitImage(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "CheckEnterImage"){      
    #define SWITCH SETPROPERTY_CheckEnterImage(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "DisabledImage"){      
    #define SWITCH SETPROPERTY_DisabledImage(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "CheckExitImage"){      
    #define SWITCH SETPROPERTY_ExitImage(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "CheckDisabledImage"){      
    #define SWITCH SETPROPERTY_DisabledImage(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "EnterSound"){      
    #define SWITCH SETPROPERTY_EnterSound(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "ExitSound"){      
    #define SWITCH SETPROPERTY_ExitSound(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "Group"){      
    #define SWITCH SETPROPERTY_Group(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "Menu"){      
    #define SWITCH SETPROPERTY_Menu(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "InputMask"){      
    #define SWITCH SETPROPERTY_InputMask(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "Mask"){      
    #define SWITCH SETPROPERTY_Mask(ss);
    #include "_form_property_switch.h"     

  } else if (sKey == "Default"){      
    #define SWITCH SETPROPERTY_Default(bb);
    #include "_form_property_switch.h"    

  } else if (sKey == "Checkable"){      
    #define SWITCH SETPROPERTY_Checkable(bb);
    #include "_form_property_switch.h"          

  } else if (sKey == "EventOnOpen"){      
    #define SWITCH SETPROPERTY_EventOnOpen(bb);
    #include "_form_property_switch.h"           

  } else if (sKey == "AcceptRichText"){      
    #define SWITCH SETPROPERTY_AcceptRichText(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "AutoDefault"){      
    #define SWITCH SETPROPERTY_AutoDefault(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "Separator"){      
    #define SWITCH SETPROPERTY_Separator(bb);
    #include "_form_property_switch.h"     



  } //else 
    
  if (sKey == "BooleanValue"){      
    #define SWITCH SETPROPERTY_BooleanValue(bb);
    #include "_form_property_switch.h"     

  // OBJECT

  // EVENT

/*
  } else if (sKey == "OnCursorPositionChanged"){
    #define SWITCH SETPROPERTY_OnCursorPositionChanged(bb);
    #include "_form_property_switch.h"     
*/
  } else if (sKey == "OnEditingFinished"){
    #define SWITCH SETPROPERTY_OnEditingFinished(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnReturnPressed"){
    #define SWITCH SETPROPERTY_OnReturnPressed(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnSelectionChanged"){
    #define SWITCH SETPROPERTY_OnSelectionChanged(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnTextChanged"){
    #define SWITCH SETPROPERTY_OnTextChanged(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnTextEdited"){
    #define SWITCH SETPROPERTY_OnTextEdited(bb);
    #include "_form_property_switch.h"     


  } else if (sKey == "OnPage"){
    #define SWITCH SETPROPERTY_OnPage(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnLinkHovered"){
    #define SWITCH SETPROPERTY_OnLinkHovered(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnLoadFinished"){
    #define SWITCH SETPROPERTY_OnLoadFinished(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnLoadProgress"){
    #define SWITCH SETPROPERTY_OnLoadProgress(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnLoadStarted"){
    #define SWITCH SETPROPERTY_OnLoadStarted(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnWindowCloseRequested"){
    #define SWITCH SETPROPERTY_OnWindowCloseRequested(bb);
    #include "_form_property_switch.h"     


  } else if (sKey == "OnSingleShot"){
    #define SWITCH SETPROPERTY_OnSingleShot(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnEvent"){
    #define SWITCH SETPROPERTY_OnEvent(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnAction"){
    #define SWITCH SETPROPERTY_OnAction(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnCursorPositionChanged"){
    #define SWITCH SETPROPERTY_OnCursorPositionChanged(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnOpen"){
    #define SWITCH SETPROPERTY_OnOpen(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnGoTo"){
    #define SWITCH SETPROPERTY_OnGoTo(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnBeforeInsert"){
    #define SWITCH SETPROPERTY_OnBeforeInsert(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnBeforeDelete"){
    #define SWITCH SETPROPERTY_OnBeforeDelete(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDragExit"){
    #define SWITCH SETPROPERTY_OnDragExit(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnPaint"){
    #define SWITCH SETPROPERTY_OnPaint(bb);
    #include "_form_property_switch.h"     


  } else if (sKey == "OnClick"){      
    #define SWITCH SETPROPERTY_OnClick(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnTimer"){      
    #define SWITCH SETPROPERTY_OnTimer(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDblClick"){      
    #define SWITCH SETPROPERTY_OnDblClick(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnMouseDown"){      
    #define SWITCH SETPROPERTY_OnMouseDown(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnMouseUp"){      
    #define SWITCH SETPROPERTY_OnMouseUp(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnMouseMove"){      
    #define SWITCH SETPROPERTY_OnMouseMove(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnGotFocus"){      
    #define SWITCH SETPROPERTY_OnGotFocus(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnLostFocus"){      
    #define SWITCH SETPROPERTY_OnLostFocus(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnEnter"){      
    #define SWITCH SETPROPERTY_OnEnter(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnExit"){      
    #define SWITCH SETPROPERTY_OnExit(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnKeyDown"){      
    #define SWITCH SETPROPERTY_OnKeyDown(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnKeyUp"){      
    #define SWITCH SETPROPERTY_OnKeyUp(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnKeyPress"){      
    #define SWITCH SETPROPERTY_OnKeyPress(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnBeforeUpdate"){   
    #define SWITCH SETPROPERTY_OnBeforeUpdate(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnOpen"){   
    #define SWITCH SETPROPERTY_OnOpen(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnResize"){   
    #define SWITCH SETPROPERTY_OnResize(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnClose"){   
    #define SWITCH SETPROPERTY_OnClose(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDragEnter"){   
    #define SWITCH SETPROPERTY_OnDragEnter(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDragMove"){   
    #define SWITCH SETPROPERTY_OnDragMove(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDrop"){   
    #define SWITCH SETPROPERTY_OnDrop(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnContextMenu"){   
    #define SWITCH SETPROPERTY_OnContextMenu(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnMouseWheel"){   
    #define SWITCH SETPROPERTY_OnMouseWheel(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnScroll"){   
    #define SWITCH SETPROPERTY_OnScroll(bb);
    #include "_form_property_switch.h"     

    
  } else if (sKey == "OnMultiPageShow"){   
    #define SWITCH SETPROPERTY_OnMultiPageShow(bb);
    #include "_form_property_switch.h"     

    
  } else if (sKey == "OnEnabled"){   
    #define SWITCH SETPROPERTY_OnEnabled(bb);
    #include "_form_property_switch.h"     
    
  } else if (sKey == "OnDisabled"){   
    #define SWITCH SETPROPERTY_OnDisabled(bb);
    #include "_form_property_switch.h"     
    
  } else if (sKey == "OnShow"){   
    #define SWITCH SETPROPERTY_OnShow(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnHide"){   
    #define SWITCH SETPROPERTY_OnHide(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnMove"){   
    #define SWITCH SETPROPERTY_OnMove(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnEnabled"){   
    #define SWITCH SETPROPERTY_OnEnabled(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnDisabled"){   
    #define SWITCH SETPROPERTY_OnDisabled(bb);
    #include "_form_property_switch.h"     

  } else if (sKey == "OnSingleShot"){   
    #define SWITCH SETPROPERTY_OnSingleShot(bb);
    #include "_form_property_switch.h"     

  }

  // ***

}


void _form::keyPressEvent ( QKeyEvent * e )
{
#ifdef IDE
  {

    QWidget *c;
    bool bDefault = false;

    switch(e->key()){
      case Qt::Key_Control:
        bCTRL = true;
        break;
      case Qt::Key_Shift:
        bSHIFT = true;
        break;
    }

    bool bFirst = true;

     switch(e->key()){
       case Qt::Key_Delete:             
         METHOD_deleteControl(bFirst);
         bFirst = false;
         break;
       case Qt::Key_Insert:
         if (bCTRL){               
           _event_EDIT_PASTE(bFirst);             
         }
         bFirst = false;
         break;
     }


    if (bFirst && firstControl(&c)){

      do {

       if (c->acceptDrops()){ // missused as selected flag

         int X;

         #define SWITCH GETPROPERTY_X();      
         #define SWITCH3 X
         #include "_form_property_switch.h"   
         #undef SWITCH3

         int Y;

         #define SWITCH GETPROPERTY_Y();      
         #define SWITCH3 Y
         #include "_form_property_switch.h"   
         #undef SWITCH3

         switch(e->key()){

           case Qt::Key_Left:
             {
             bool b = c->x() - 1 < 50;
             switch(e->modifiers()){
               case Qt::ShiftModifier:                    
                 if ((!XScrollBar && c->x() + c->width() - 1 < 0) || (XScrollBar && X + c->width() - 1 < 0)){
                 } else {
                   if (bFirst) newUndoRedo();
                   b = false;
                   decWidth(c, 1);
                 }
                 break;
               case Qt::ControlModifier:
                 if ((!XScrollBar && c->x() - 10 < 0) || (XScrollBar && X - 10 < 0)){
                   if (bFirst) newUndoRedo();
                   my_move(c, 0, c->y());
                 } else {
                   if (bFirst) newUndoRedo();
                   decX(c, 10);
                 }
                 break;
               default:
                 if ((!XScrollBar && c->x() - 1 < 0) || (XScrollBar && X - 1 < 0)){
                   if (bFirst) newUndoRedo();
                   my_move(c, 0, c->y());
                 } else {
                   if (bFirst) newUndoRedo();
                   decX(c, 1);
                 }
                 break;
             }
              if (XScrollBar && b){
                XScrollBar->setValue(XScrollBar->value() - 50);
              }
             }
             break;
           case Qt::Key_Right:
             {
              bool b = c->x() + c->width() + 50 > frameW();
              switch(e->modifiers()){
                case Qt::ShiftModifier:              
                  if ((!XScrollBar && c->x() + c->width() + 1 > frameW()) || (XScrollBar && X + c->width() + 1 > XScrollBar->value() + frameW())){
                  } else {
                    if (bFirst) newUndoRedo();
                    b = false;
                    incWidth(c, 1);
                  }
                  break;
                case Qt::ControlModifier:
                  if ((!XScrollBar && c->x() + c->width() + 10 > frameW()) || (XScrollBar && X + c->width() + 10 > XScrollBar->value() + frameW())){
                    if (bFirst) newUndoRedo();
                    my_move(c, frameW() - c->width(), c->y());
                  } else {
                    if (bFirst) newUndoRedo();
                    incX(c, 10);
                  }
                  break;
                default:
                  if ((!XScrollBar && c->x() + c->width() + 1 > frameW()) || (XScrollBar && X + c->width() + 1 > XScrollBar->value() + frameW())){
                    if (bFirst) newUndoRedo();
                    my_move(c, frameW() - c->width(), c->y());
                  } else {
                    if (bFirst) newUndoRedo();
                    incX(c, 1);
                  }
                  break;
              }
              if (XScrollBar && b){
                XScrollBar->setValue(XScrollBar->value() + 50);
              }
             }
             break;
           case Qt::Key_Up:
             {
              bool b = c->y() - 1 < 50;
              switch(e->modifiers()){
                case Qt::ShiftModifier:              
                  if ((!YScrollBar && c->y() + c->height() - 1 < 0) || (YScrollBar && Y + c->height() - 1 < 0)){
                  } else {
                    if (bFirst) newUndoRedo();
                    b = false;
                    decHeight(c, 1);
                  }
                  break;
                case Qt::ControlModifier:
                  if ((!YScrollBar && c->y() - 10 < 0) || (YScrollBar && Y + c->height() - 1 < 0)){
                    if (bFirst) newUndoRedo();
                    my_move(c, c->x(), 0);
                  } else {
                    if (bFirst) newUndoRedo();
                    decY(c, 10);
                  }
                  break;
                default:
                  if ((!YScrollBar && c->y() - 1 < 0) || (YScrollBar && Y - 1 < 0)){
                    if (bFirst) newUndoRedo();
                    my_move(c, c->x(), 0);
                  } else {
                    if (bFirst) newUndoRedo();
                    decY(c, 1);
                  }
                  break;
              }
              if (YScrollBar && b){
                YScrollBar->setValue(YScrollBar->value() - 50);
              }
             }
             break;
           case Qt::Key_Down:
             {
               bool b = c->y() + c->height() + 50 > frameH();

                switch(e->modifiers()){
                  case Qt::ShiftModifier:              
                    if ((!YScrollBar && c->y() + c->height() + 1 > frameH()) || (YScrollBar && Y + c->height() + 1 > YScrollBar->value() + frameH())){
                    } else {
                      if (bFirst) newUndoRedo();
                      b = false;
                      incHeight(c, 1);
                    }
                    break;
                  case Qt::ControlModifier:
                    if ((!YScrollBar && c->y() + c->height() + 10 > frameH()) || (YScrollBar && Y + c->height() + 10 > YScrollBar->value() + frameH())){
                      if (bFirst) newUndoRedo();
                      my_move(c, c->x(), frameH() - c->height());
                    } else {
                      if (bFirst) newUndoRedo();
                      incY(c, 10);
                    }
                    break;
                  default:
                    if ((!YScrollBar && c->y() + c->height() + 1 > frameH()) || (YScrollBar && Y + c->height() + 1 > YScrollBar->value() + frameH())){
                      if (bFirst) newUndoRedo();
                      my_move(c, c->x(), frameH() - c->height());
                    } else {
                      if (bFirst) newUndoRedo();
                      incY(c, 1);
                    }
                    break;
                }
              if (YScrollBar && b){
                YScrollBar->setValue(YScrollBar->value() + 50);
              }
             }
             break;
           default:
             bDefault = true;
             goto stepout;
             break;
         }

         if (bFirst){
           bFirst = false;
         }

       }


      } while (nextControl(&c));

      
    }

  stepout:

    if (bDefault == false){      
      checkFrameMinSize();
    }  

    if (bDefault == false){
      updatePropertyWindowGeo();
 

    }  
  } 
  
    QWidget::keyPressEvent(e);
#endif
    
    bEventKeyPress = true;
#ifdef RUN
    QWidget::keyPressEvent(e);

    Qt::KeyboardModifiers m = e->modifiers();

    QWidget *c;
    if (firstControl(&c)){

      if (e->key() != 0){

        bool bSpace = e->key() == Qt::Key_Space;
       // bool bPrevious = e->key() == Qt::Key_Left || e->key() == Qt::Key_Up;
       // bool bNext = e->key() == Qt::Key_Right || e->key() == Qt::Key_Down;

        int m = e->key();
        m = e->key() | (m & Qt::ShiftModifier ? Qt::SHIFT : 0) | (m & Qt::ControlModifier ? Qt::CTRL : 0) | (m & Qt::AltModifier ? Qt::ALT : 0) | (m & Qt::MetaModifier ? Qt::META : 0);
        QKeySequence kk(m);

        do {

          QString sControlType = "";

          #define SWITCH GETPROPERTY_ControlType();      
          #define SWITCH3 sControlType
          #include "_form_property_switch.h"   
          #undef SWITCH3

          if (sControlType == "ImageButton"){      

            if (bSpace && ((kb_imagebutton *) c)->hasFocus()){
              ((kb_imagebutton *) c)->setFocus(); 
              ((kb_imagebutton *) c)->EVENT_OnEvent(); 
              break;
              /*
            } else if (bPrevious){
              c->nextInFocusChain()->setFocus(); 
              break;
            } else if (bNext){
              c->nextInFocusChain()->setFocus(); 
              break;*/
            }

            QString sKey = "";

            #define SWITCH GETPROPERTY_Key();      
            #define SWITCH3 sKey
            #include "_form_property_switch.h"   
            #undef SWITCH3

            if (sKey.isEmpty() || ((kb_imagebutton *) c)->GETPROPERTY_Enabled() == false) continue;

            if (QKeySequence(sKey) == kk){
              ((kb_imagebutton *) c)->setFocus(); 
              ((kb_imagebutton *) c)->EVENT_OnEvent(); 
            }
          }
            
        } while (nextControl(&c));
      }
    }

    EVENT_OnKeyDown(e->key(), m & Qt::ShiftModifier, m & Qt::ControlModifier, m & Qt::AltModifier); 
#endif
  
}

void _form::keyReleaseEvent ( QKeyEvent * e )
{  
#ifdef IDE
  {

    switch(e->key()){
      case Qt::Key_Control:
       bCTRL = false;
       break;
      case Qt::Key_Shift:
       bSHIFT = false;
       break;
    }
  } 

  
  if (isReport()){
    QWidget *c;

    if (firstControl(&c)){

      do {

       if (c->acceptDrops()){ // missused as selected flag

         
            _controlType tt = controlType(c);
            if (tt != t_header && tt != t_footer){        

                _header *t = (_header *) insideHeader(c->x(), c->y(), 1, 1);
                if (t){
                  c->move(c->x(), t->y() + t->height());
                } else {
                  _header *t = (_header *) insideHeader(c->x(), c->y() + c->height(), 1, 1);
                  if (t){
                    c->move(c->x(), t->y() + t->height());
                  }
                }

                {
                  _footer *t = (_footer *) insideFooter(c->x(), c->y(), 1, 1);
                  if (t){
                    c->move(c->x(), t->y() + t->height());
                  } else {
                    _footer *t = (_footer *) insideFooter(c->x(), c->y() + c->height(), 1, 1);
                    if (t){
                      c->move(c->x(), t->y() + t->height());
                    }
                  }
                }
            }
         

       }
      } while (nextControl(&c));
     }
  }

  
  QWidget::keyReleaseEvent(e);
#endif
#ifdef RUN
    QWidget::keyReleaseEvent(e);
#endif
    Qt::KeyboardModifiers m = e->modifiers();
    if (bEventKeyPress){
        bEventKeyPress = false;
#ifdef RUN
        EVENT_OnKeyPress(e->key(), m & Qt::ShiftModifier, m & Qt::ControlModifier, m & Qt::AltModifier); 
#endif
    }
#ifdef RUN
    EVENT_OnKeyUp(e->key(), m & Qt::ShiftModifier, m & Qt::ControlModifier, m & Qt::AltModifier); 
#endif
  
}

QString _form::getPath()
{ 
#ifdef RUN
  return qApp->applicationDirPath();
#else
  QString s = sFilename;
  int i = s.lastIndexOf('/');
  if (i == -1) i = s.lastIndexOf('\\');
  s = s.left(i);
  return s; 
#endif
}


bool _form::loadFormProperty(QString *s, QString sName)
{ 
     //  QMessageBox::information(0,"loadFormProperty", "sTypeName");   

  SETPROPERTY_Name(sName);

  int nScrollWidth = 0;
  int nScrollHeight = 0;

  do {

    const char *sss = (*s).toAscii();

    *s = (*s).trimmed();

    QString sKey;

    bool bb;
    QString ss;
    int nn;

    loadProperty(s, &sKey, &bb, &ss, &nn);

    if (sKey.isEmpty() || sKey.isNull()) break;

      // QMessageBox::information(0,sKey, "sTypeName");   

    //if (bLoadFormClassSourceCodeOnly) continue;
     
    if (sKey == "Caption"){      
      SETPROPERTY_Caption(ss);

    } else if (sKey == "X"){      
      SETPROPERTY_X(nn, false);
      SETPROPERTY_LoadedX(nn);

    } else if (sKey == "Y"){      
      SETPROPERTY_Y(nn, false);
      SETPROPERTY_LoadedY(nn);
    
    } else if (sKey == "Width"){ 
      SETPROPERTY_Width(nn); 
      SETPROPERTY_LoadedWidth(nn);

    } else if (sKey == "Height"){      
      SETPROPERTY_Height(nn);
      SETPROPERTY_LoadedHeight(nn);

    } else if (sKey == "Cursor"){      
      SETPROPERTY_Cursor(ss);

    } else if (sKey == "Tag"){      
      SETPROPERTY_Tag(ss);
/*
    } else if (sKey == "MenuItemKeyCode"){      
      SETPROPERTY_MENUBARITEMKeyCode(ss);
*/

      /*
    } else if (sKey == "CheckEnterImage"){      
      SETPROPERTY_CheckEnterImage(ss);

    } else if (sKey == "EnterImage"){      
      SETPROPERTY_EnterImage(ss);

    } else if (sKey == "ExitImage"){      
      SETPROPERTY_ExitImage(ss);

    } else if (sKey == "DisabledImage"){      
      SETPROPERTY_DisabledImage(ss);

    } else if (sKey == "EnterSound"){      
      SETPROPERTY_EnterSound(ss);

    } else if (sKey == "ExitSound"){      
      SETPROPERTY_ExitSound(ss);
*/

    } else if (sKey == "Group"){ SETPROPERTY_Group(ss);
    } else if (sKey == "Background"){ SETPROPERTY_Background(ss);
    } else if (sKey == "BackgroundStyle"){ SETPROPERTY_BackgroundStyle(ss);
    } else if (sKey == "Palette"){ SETPROPERTY_Palette(ss);
    
    } else if (sKey == "MinimumWidth"){ SETPROPERTY_MinimumWidth(nn);
    } else if (sKey == "MinimumHeight"){ SETPROPERTY_MinimumHeight(nn);
    } else if (sKey == "MaximumWidth"){ SETPROPERTY_MaximumWidth(nn);
    } else if (sKey == "MaximumHeight"){ SETPROPERTY_MaximumHeight(nn);
    } else if (sKey == "StopOnClose"){ SETPROPERTY_StopOnClose(bb);

    } else if (sKey == "DockTitleVisible"){ SETPROPERTY_DockTitleVisible(bb);
    } else if (sKey == "DockParent"){ SETPROPERTY_DockOrder(ss);

    } else if (sKey == "DockSplit"){ SETPROPERTY_DockSplit(ss);
#ifdef IDE
    } else if (sKey == "ShowMode"){ SETPROPERTY_ShowMode(ss);
#else
    } else if (sKey == "ShowMode"){ SETPROPERTY_ShowMode(ss, true);
#endif
    } else if (sKey == "FormFileName"){ SETPROPERTY_FormFileName(ss);
    } else if (sKey == "FormModified"){ SETPROPERTY_FormModified(bb);
    
    } else if (sKey == "FormX"){ SETPROPERTY_FormX(bb);
    } else if (sKey == "FormY"){ SETPROPERTY_FormY(bb);
    } else if (sKey == "FormWidth"){ SETPROPERTY_FormWidth(bb);
    } else if (sKey == "FormHeight"){ SETPROPERTY_FormHeight(bb);
    

    } else if (sKey == "DockWidth"){ SETPROPERTY_DockWidth(nn);
    } else if (sKey == "DockHeight"){ SETPROPERTY_DockHeight(nn);

    } else if (sKey == "ScrollX"){ SETPROPERTY_ScrollX(nn);
    } else if (sKey == "ScrollY"){ SETPROPERTY_ScrollY(nn);
    } else if (sKey == "ScrollWidth"){ nScrollWidth = nn; 
    } else if (sKey == "ScrollHeight"){ nScrollHeight = nn; 

    } else if (sKey == "MultiPageHeight"){ SETPROPERTY_MultiPageHeight(nn);
    } else if (sKey == "MultiPageBorderTop"){ SETPROPERTY_MultiPageBorderTop(nn);
    } else if (sKey == "MultiPageBorderBottom"){ SETPROPERTY_MultiPageBorderBottom(nn);
    } else if (sKey == "MultiPageBorderLeft"){ SETPROPERTY_MultiPageBorderLeft(nn);
    } else if (sKey == "MultiPageBorderRight"){ SETPROPERTY_MultiPageBorderRight(nn);

    } else if (sKey == "BorderTop"){ SETPROPERTY_BorderTop(nn);
    } else if (sKey == "BorderBottom"){ SETPROPERTY_BorderBottom(nn);
    } else if (sKey == "BorderLeft"){ SETPROPERTY_BorderLeft(nn);
    } else if (sKey == "BorderRight"){ SETPROPERTY_BorderRight(nn);
    } else if (sKey == "CSV"){ SETPROPERTY_CSV(ss);
    } else if (sKey == "Tag"){ SETPROPERTY_Tag(ss);
    } else if (sKey == "TableView"){ SETPROPERTY_TableView(bb);
#ifdef RUN
    bTableView = bb;
/*
    connect(this, SIGNAL(beforeInsert(QSqlRecord &)), this, SLOT(EVENT_On2BeforeInsert(QSqlRecord &)));
    connect(this, SIGNAL(beforeUpdate(int, QSqlRecord &)), this, SLOT(EVENT_On2BeforeUpdate(int, QSqlRecord &)));
    connect(this, SIGNAL(beforeDelete(int)), this, SLOT(EVENT_On2BeforeDelete(int)));
*/
    if (bTableView) sqlv = new QTableView(this);

#endif
    }
    
    if (sKey == "BoxIndex"){ SETPROPERTY_BoxIndex(nn);
    } else if (sKey == "BoxX"){ SETPROPERTY_BoxX(nn);
    } else if (sKey == "BoxY"){ SETPROPERTY_BoxY(nn);
    } else if (sKey == "SplitIndex"){ SETPROPERTY_SplitIndex(nn);

    } else if (sKey == "Scale"){ SETPROPERTY_Scale(bb);
    //} else if (sKey == "FormCentered"){ SETPROPERTY_FormCentered(bb);
    //} else if (sKey == "FormScaled"){ SETPROPERTY_FormScaled(bb);
    } else if (sKey == "DragDrop"){ SETPROPERTY_DragDrop(bb);
    
    } else if (sKey == "FocusPolicy"){ SETPROPERTY_FocusPolicy(ss);
    } else if (sKey == "FocusProxy"){ SETPROPERTY_FocusProxy(ss);
    } else if (sKey == "FocusOrder"){ SETPROPERTY_FocusOrder(nn);

    } else if (sKey == "FontName"){ SETPROPERTY_FontName(ss);
    } else if (sKey == "FontSize"){ SETPROPERTY_FontSize(nn);

    } else if (sKey == "FontBold"){ SETPROPERTY_FontBold(bb);
    } else if (sKey == "FontItalic"){ SETPROPERTY_FontItalic(bb);
    } else if (sKey == "FontUnderline"){ SETPROPERTY_FontUnderline(bb);

    } else if (sKey == "FontColor"){ SETPROPERTY_FontColor(ss);

    } else if (sKey == "StatusTip"){ SETPROPERTY_StatusTip(ss);
    } else if (sKey == "ToolTip"){ SETPROPERTY_ToolTip(ss);
    } else if (sKey == "StyleSheet"){ SETPROPERTY_StyleSheet(ss);
    } else if (sKey == "WhatsThis"){ SETPROPERTY_WhatsThis(ss);

    } else if (sKey == "Flag"){ 
      SETPROPERTY_Flag(ss);
    } else if (sKey == "SQLControls"){ SETPROPERTY_SQLControls(ss);

    } else if (sKey == "Icon"){ SETPROPERTY_Icon(ss);
    //} else if (sKey == "IconCaption"){ SETPROPERTY_IconCaption(ss);
    } else if (sKey == "Caption"){ SETPROPERTY_Caption(ss);

    } else if (sKey == "Modal"){ SETPROPERTY_Modal(bb);
#ifdef IDE
    } else if (sKey == "Opacity"){ SETPROPERTY_Opacity(nn);
#endif
#ifdef RUN
    } else if (sKey == "Opacity"){ SETPROPERTY_Opacity(nn, false);
#endif
    } else if (sKey == "TimerInterval"){ SETPROPERTY_TimerInterval(nn);

    } else if (sKey == "Shadow"){ SETPROPERTY_Shadow(bb);
    } else if (sKey == "Shape"){ SETPROPERTY_Shape(bb);
    } else if (sKey == "OpenLinks"){ SETPROPERTY_OpenLinks(bb);

    } else if (sKey == "InputControl"){ SETPROPERTY_InputControl(ss);
   
    } else if (sKey == "Space"){ SETPROPERTY_Space(nn);
    } else if (sKey == "Border"){ SETPROPERTY_Border(nn);

    } else if (sKey == "Flat"){ SETPROPERTY_Flat(bb);

    } else if (sKey == "Key"){ SETPROPERTY_Key(ss);
        
    } else if (sKey == "IntegerMaximum"){ SETPROPERTY_IntegerMaximum(nn);
    } else if (sKey == "IntegerMinimum"){ SETPROPERTY_IntegerMinimum(nn);
    } else if (sKey == "Completer"){ SETPROPERTY_Completer(ss);

    } else if (sKey == "ValidatorDouble"){ SETPROPERTY_ValidatorDouble(bb);
    } else if (sKey == "ValidatorInteger"){ SETPROPERTY_ValidatorInteger(bb);

    } else if (sKey == "ValidatorRegEx"){ SETPROPERTY_ValidatorRegEx(ss);
    } else if (sKey == "ValidatorRegEx2"){ SETPROPERTY_ValidatorRegEx2(ss);
    } else if (sKey == "DoubleEntry"){ SETPROPERTY_DoubleEntry(bb);

    } else if (sKey == "InsertPolicy"){ SETPROPERTY_InsertPolicy(ss);
    } else if (sKey == "Editable"){ SETPROPERTY_Editable(bb);
    } else if (sKey == "MaximumVisible"){ SETPROPERTY_MaximumVisible(nn);
    } else if (sKey == "Sorted"){ SETPROPERTY_Sorted(bb);

    } else if (sKey == "StringMaximum"){ SETPROPERTY_StringMaximum(ss);
    } else if (sKey == "StringMinimum"){ SETPROPERTY_StringMinimum(ss);
    } else if (sKey == "Format"){ SETPROPERTY_Format(ss);

    } else if (sKey == "PopUp"){ SETPROPERTY_PopUp(bb);
    } else if (sKey == "ScrollBar"){ SETPROPERTY_ScrollBar(ss);

    /*
    } else if (sKey == "MouseDownImage"){ SETPROPERTY_MouseDownImage(ss);
    } else if (sKey == "MouseUpImage"){ SETPROPERTY_MouseUpImage(ss);
    } else if (sKey == "EnabledImage"){ SETPROPERTY_EnabledImage(ss);

    } else if (sKey == "CheckMouseDownImage"){ SETPROPERTY_MouseDownImage(ss);
    } else if (sKey == "CheckMouseUpImage"){ SETPROPERTY_MouseUpImage(ss);
    } else if (sKey == "CheckEnabledImage"){ SETPROPERTY_EnabledImage(ss);

    } else if (sKey == "MouseDownSound"){ SETPROPERTY_MouseDownSound(ss);
    } else if (sKey == "MouseUpSound"){ SETPROPERTY_MouseUpSound(ss);
*/
    } else if (sKey == "HomeURL"){ SETPROPERTY_HomeURL(ss);



/*
    } else if (sKey == "Menu"){      
      SETPROPERTY_Menu(bb);
*/
    } else if (sKey == "Interval"){      
      SETPROPERTY_Interval(nn);

    // PROPERTY of form only

    } else if (sKey == "MoveOnMouseDrag"){ SETPROPERTY_MoveOnMouseDrag(bb);
    } else if (sKey == "MouseTracking"){ SETPROPERTY_MouseTracking(bb);
    } else if (sKey == "DrawOnPaint"){ SETPROPERTY_DrawOnPaint(bb);
    } else if (sKey == "SoundOnEvent"){ SETPROPERTY_SoundOnEvent(ss);
    } else if (sKey == "CursorAnimation"){ SETPROPERTY_CursorAnimation(ss);
    
    } else if (sKey == "Dock"){ SETPROPERTY_Dock(ss);
    } else if (sKey == "Mask"){ SETPROPERTY_Mask(ss);
    } else if (sKey == "OpenOnRun"){ SETPROPERTY_OpenAtStartup(bb);
    
    } else if (sKey == "SelectionMode"){ SETPROPERTY_SelectionMode(ss);
    } else if (sKey == "AlternatingRowColors"){ SETPROPERTY_AlternatingRowColors(bb);

    } else if (sKey == "SQLName"){ SETPROPERTY_SQLName(ss);
    //} else if (sKey == "SQLType"){ SETPROPERTY_SQLType(ss);
    } else if (sKey == "SQLRelation"){ SETPROPERTY_SQLRelation(ss);
    //} else if (sKey == "SQLWhere"){ SETPROPERTY_SQLWhere(ss);
    //} else if (sKey == "SQLOrderBy"){ SETPROPERTY_SQLOrderBy(ss);
    } else if (sKey == "SQLInsert"){ SETPROPERTY_SQLInsert(bb);
    } else if (sKey == "SQLUpdate"){ SETPROPERTY_SQLUpdate(bb);
    } else if (sKey == "SQLDelete"){ SETPROPERTY_SQLDelete(bb);
    } else if (sKey == "Resizable"){ SETPROPERTY_Resizable(bb);
    } else if (sKey == "ResizableSmaller"){ SETPROPERTY_ResizableSmaller(bb);
    } else if (sKey == "ResizableBigger"){ SETPROPERTY_ResizableBigger(bb);

    //} else if (sKey == "SQLCaption"){ SETPROPERTY_SQLCaption(ss);
    //} else if (sKey == "SQLWidth"){ SETPROPERTY_SQLWidth(nn);


    } else if (sKey == "Pages"){ SETPROPERTY_Pages(ss);
    } else if (sKey == "ParentForm"){ SETPROPERTY_ParentForm(ss);
    } else if (sKey == "ParentControl"){ SETPROPERTY_ParentControl(ss);
    } else if (sKey == "TabIndex"){ SETPROPERTY_TabIndex(nn);
	}

    // EVENT

    if (sKey == "OnEvent"){ SETPROPERTY_OnEvent(bb);


    //} else if (sKey == "OnCursorPositionChanged"){ SETPROPERTY_OnCursorPositionChanged(bb);
    } else if (sKey == "OnEditingFinished"){ SETPROPERTY_OnEditingFinished(bb);
    } else if (sKey == "OnReturnPressed"){ SETPROPERTY_OnReturnPressed(bb);
    } else if (sKey == "OnSelectionChanged"){ SETPROPERTY_OnSelectionChanged(bb);
    } else if (sKey == "OnTextChanged"){ SETPROPERTY_OnTextChanged(bb);
    } else if (sKey == "OnTextEdited"){ SETPROPERTY_OnTextEdited(bb);

    } else if (sKey == "OnPage"){ SETPROPERTY_OnPage(bb);
    } else if (sKey == "OnLinkHovered"){ SETPROPERTY_OnLinkHovered(bb);
    } else if (sKey == "OnLoadFinished"){ SETPROPERTY_OnLoadFinished(bb);
    } else if (sKey == "OnLoadProgress"){ SETPROPERTY_OnLoadProgress(bb);
    } else if (sKey == "OnLoadStarted"){ SETPROPERTY_OnLoadStarted(bb);
    } else if (sKey == "OnWindowCloseRequested"){ SETPROPERTY_OnWindowCloseRequested(bb);

    } else if (sKey == "OnSingleShot"){ SETPROPERTY_OnSingleShot(bb);
    } else if (sKey == "OnAction"){ SETPROPERTY_OnAction(bb);
    } else if (sKey == "OnCursorPositionChanged"){ SETPROPERTY_OnCursorPositionChanged(bb);
    } else if (sKey == "OnOpen"){ SETPROPERTY_OnOpen(bb);
    } else if (sKey == "OnClose"){ SETPROPERTY_OnClose(bb);
    } else if (sKey == "OnGoTo"){ SETPROPERTY_OnGoTo(bb);
    } else if (sKey == "OnBeforeInsert"){ SETPROPERTY_OnBeforeInsert(bb);
    } else if (sKey == "OnBeforeDelete"){ SETPROPERTY_OnBeforeDelete(bb);
    } else if (sKey == "OnDragExit"){ SETPROPERTY_OnDragExit(bb);
    } else if (sKey == "OnPaint"){ SETPROPERTY_OnPaint(bb);

    } else if (sKey == "OnDirty"){ SETPROPERTY_OnDirty(bb);
    } else if (sKey == "OnAddNew"){ SETPROPERTY_OnAddNew(bb);
    } else if (sKey == "OnQuery"){ SETPROPERTY_OnQuery(bb);

    } else if (sKey == "OnTimer"){      
      SETPROPERTY_OnTimer(bb);

    } else if (sKey == "OnClick"){      
      SETPROPERTY_OnClick(bb);

    } else if (sKey == "OnDblClick"){      
      SETPROPERTY_OnDblClick(bb);

    } else if (sKey == "OnMouseDown"){      
      SETPROPERTY_OnMouseDown(bb);  

    } else if (sKey == "OnMouseUp"){      
      SETPROPERTY_OnMouseUp(bb);

    } else if (sKey == "OnMouseMove"){      
      SETPROPERTY_OnMouseMove(bb);

    } else if (sKey == "OnGotFocus"){      
      SETPROPERTY_OnGotFocus(bb);

    } else if (sKey == "OnLostFocus"){      
      SETPROPERTY_OnLostFocus(bb);

    } else if (sKey == "OnEnter"){      
      SETPROPERTY_OnEnter(bb);

    } else if (sKey == "OnExit"){      
      SETPROPERTY_OnExit(bb);

    } else if (sKey == "OnKeyDown"){      
      SETPROPERTY_OnKeyDown(bb);

    } else if (sKey == "OnKeyUp"){      
      SETPROPERTY_OnKeyUp(bb);

    } else if (sKey == "OnKeyPress"){      
      SETPROPERTY_OnKeyPress(bb);

    } else if (sKey == "OnBeforeUpdate"){      
      SETPROPERTY_OnBeforeUpdate(bb);

    } else if (sKey == "OnOpen"){      
      SETPROPERTY_OnOpen(bb);

    } else if (sKey == "OnResize"){      
      SETPROPERTY_OnResize(bb);

    } else if (sKey == "OnClose"){      
      SETPROPERTY_OnClose(bb);

    } else if (sKey == "OnDragEnter"){ SETPROPERTY_OnDragEnter(bb);
    } else if (sKey == "OnDragMove"){ SETPROPERTY_OnDragMove(bb);
    } else if (sKey == "OnDrop"){ SETPROPERTY_OnDrop(bb);
    } else if (sKey == "OnContextMenu"){ SETPROPERTY_OnContextMenu(bb);
    } else if (sKey == "OnMouseWheel"){ SETPROPERTY_OnMouseWheel(bb);
    } else if (sKey == "OnMultiPageShow"){ SETPROPERTY_OnMultiPageShow(bb);
    } else if (sKey == "OnScroll"){ SETPROPERTY_OnScroll(bb);
    
    } else if (sKey == "OnShow"){ SETPROPERTY_OnShow(bb);
    } else if (sKey == "OnEnabled"){ SETPROPERTY_OnEnabled(bb);
    } else if (sKey == "OnDisabled"){ SETPROPERTY_OnDisabled(bb);
    } else if (sKey == "OnHide"){ SETPROPERTY_OnHide(bb);
    } else if (sKey == "OnMove"){ SETPROPERTY_OnMove(bb);



    }    

    // ***

  } while ( !((*s).length() <= 0 || (*s).startsWith("Begin")) );

#ifdef RUN
  if (GETPROPERTY_MultiPageHeight()){
    int n = GETPROPERTY_MultiPageHeight();
    SETPROPERTY_Height(n);
    SETPROPERTY_LoadedHeight(n);
  }
  
  SETPROPERTY_ScrollWidth(nScrollWidth);
  SETPROPERTY_ScrollHeight(nScrollHeight);

#endif
  //QMessageBox::information(0,"METHOD_Load", "2");     

  // load controls
  loadControls(s);


#ifdef RUN

  min = 0;
 
 // focus order is set at once after reading all controls
  QWidget *c = 0;
  QWidget *max = 0;
  /*
  if (firstControl(&c)){
     do {
       int n = 0;
                    
       #define SWITCH GETPROPERTY_FocusOrder();      
       #define SWITCH3 n
       #include "_form_property_switch.h"   
       #undef SWITCH3
       if (n == 1){
         min = c;
         break;
       }

     } while (nextControl(&c));
  }
  */
  min = this;

  int n2 = 0;

  QString sFocusProxy;
  int nMax = 0;
  if (firstControl(&c)){
     do {
       int n = 0;
                    
       #define SWITCH GETPROPERTY_FocusOrder();      
       #define SWITCH3 n
       #include "_form_property_switch.h"   
       #undef SWITCH3
       if (n > n2){
         n2 = n;
         max = c;
         nMax = n;
       }

       #define SWITCH GETPROPERTY_FocusProxy();      
       #define SWITCH3 sFocusProxy
       #include "_form_property_switch.h"   
       #undef SWITCH3

       if (!sFocusProxy.isEmpty()){

        QWidget *c2 = 0;
        if (firstControl(&c2, 11)){
          do {            
            if (c->objectName() == sFocusProxy){
              c->setFocusProxy(c2);
              break;
            }
          } while (nextControl(&c2, 11));
        }
         
       }
        

     } while (nextControl(&c));
  }


  { // form has proxy?
    sFocusProxy = this->GETPROPERTY_FocusProxy();      

    if (!sFocusProxy.isEmpty()){

      QWidget *c2 = 0;
      if (firstControl(&c2, 11)){
        do {            
          if (c2->objectName() == sFocusProxy){
            setFocusProxy(c2);
            min = c2;
            break;
          }
        } while (nextControl(&c2, 11));
      }         
    }
  }

  n2 = 0;
  QWidget *c2 = 0;


  while (n2 < nMax){
    if (firstControl(&c)){
      do {
        int n = 0;
                      
        #define SWITCH GETPROPERTY_FocusOrder();      
        #define SWITCH3 n
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if (n2 + 1 == n){
          if (n2 + 1 == 2){
            QWidget::setTabOrder(min, c); 
          } else if (c2){
            QWidget::setTabOrder(c2, c);
          }
          c2 = c;
          break;
        }

      } while (nextControl(&c));
    }
    n2++;
  }
  if (max != min) QWidget::setTabOrder(max, min);  

  {
    int nMultiPageHeight = GETPROPERTY_MultiPageHeight();
    int nMultiPageBorderTop = GETPROPERTY_MultiPageBorderTop();
    int nMultiPageBorderBottom = GETPROPERTY_MultiPageBorderBottom();
    int nMultiPageBorderLeft = GETPROPERTY_MultiPageBorderLeft();
    int nMultiPageBorderRight = GETPROPERTY_MultiPageBorderRight();

    // * running timer controls

    int w = GETPROPERTY_Width();
    int h = GETPROPERTY_Height();

    if (firstControl(&c)){
      do {
        
        if (controlType(c) == t_timer){
          /*kb*/_timer *t = qobject_cast</*kb*/_timer *>(c);

          if (t && t->GETPROPERTY_Enabled()){
            ((kb_timer* ) t)->METHOD_Start();
          }

        }

        else if (controlType(c) == t_movie){
          /*kb*/_movie *t = qobject_cast</*kb*/_movie *>(c);

          if (t && t->GETPROPERTY_Enabled()){
            ((kb_movie* ) t)->METHOD_Play();
          }

        }

        else if (controlType(c) == t_sound){
          /*kb*/_sound *t = qobject_cast</*kb*/_sound *>(c);

          if (t && t->GETPROPERTY_Enabled()){
            ((kb_sound* ) t)->METHOD_Play();
          }

        }

        // is a control on a MultiPage?
        if (nMultiPageHeight){
          int x = c->x();
          int y = c->y();
          if (x > nMultiPageBorderLeft && x < w - nMultiPageBorderRight &&
            ((y > nMultiPageBorderTop && y < h - nMultiPageBorderBottom) || y > nMultiPageHeight))
          {

             #define SWITCH SETPROPERTY_MultiPage(y / nMultiPageHeight + 1);
             #include "_form_property_switch.h"            

          }
        }
                
      } while (nextControl(&c));
    }
  }

  // *

#endif

#ifdef IDE
  // eat 'End Form'
  *s = (*s).mid(8); 

  // load source code of form
  loadFormClass(s);

  checkFrameMinSize();
#endif
  
#ifdef RUN
  *s = "";
  bOpened = true;
#endif

  return true;
}

#ifdef RUN

_form *EXTERN_my_form_test = 0;

t_boolean _form::METHOD_Load(QString s)
{  

  bLoading = true;

 

     //QMessageBox::information(0,"METHOD_Load", "1");     

  

  if (loadForm(s)){
#ifdef RUN
   // SETPROPERTY_Width(GETPROPERTY_Width());
    int w = GETPROPERTY_ScrollWidth();
    if (w == 0 || w < GETPROPERTY_Width()) w = GETPROPERTY_Width();
    int h = GETPROPERTY_ScrollHeight();
    if (h == 0 || h < GETPROPERTY_Height()) h = GETPROPERTY_Height();
    if (GETPROPERTY_ScrollWidth() || GETPROPERTY_ScrollHeight()){
      main->setFixedSize(w, h);    
    } else {
      main->resize(w, h);    
    }
    this->setUpdatesEnabled(false);
    if (GETPROPERTY_ScrollWidth() || GETPROPERTY_ScrollHeight()) this->setMaximumSize(w, h);
    this->setWidget(0);
    this->setWidget(main);
    int w2 = w - this->width();
    this->horizontalScrollBar()->setMaximum(w2);
    int h2 = h - this->height();
    this->verticalScrollBar()->setMaximum(h2);
    this->setUpdatesEnabled(true);
    /*
    horizontalScrollBar()->setPageStep(width());
    verticalScrollBar()->setPageStep(height());
    horizontalScrollBar()->setMaximum(GETPROPERTY_ScrollWidth() - width());
    verticalScrollBar()->setMaximum(GETPROPERTY_ScrollHeight()- height());
    */
        
    /*
    // set focus proxy for form
    if (!GETPROPERTY_FocusProxy().isEmpty()){
      QWidget *c = 0;
      if (firstControl(&c)){
        do {
          QString sControlType = "";
          #define SWITCH GETPROPERTY_Name();      
          #define SWITCH3 sControlName
          #include "_form_property_switch.h"   
          #undef SWITCH3

          if (sControlName == GETPROPERTY_FocusProxy()){
            QWidget *cc = getControl(sControlName);
            if (cc) setFocusProxy(cc);
          }

        } while (nextControl(&c));
      }
    }*/
      

#endif
         //QMessageBox::information(0,"METHOD_Load", "2");     

  EXTERN_my_form_test = this;
#ifdef RUN
    if (ParentForm) SETPROPERTY_ParentForm(((_form *) ParentForm)->GETPROPERTY_Name());
#endif
    //EVENT_OnLoad();
    return true;
  }
  return false;
}



void _form::METHOD_Finish()
{  
  /*
  sName = GETPROPERTY_Name();
  sGroup = GETPROPERTY_Group();

  a = sName.toAscii();
  acName = a.data();
  b = sGroup.toAscii();
  acGroup = b.data();*/

  acName = "Form"; // always form making reusing form codes easier
  acGroup = "";

  bLoading = false;
}

void _form::setSQL()
{
#ifdef RUN
  if (!q.isValid()) return;

  //recordbuffer.clear();

  bool bbDirty = bDirty;
  setSQL2(q.record());
  
  setDirty(bbDirty);
  if (!bTableView){
    EVENT_OnGoTo3();
    EVENT_OnGoTo2();
    EVENT_OnGoTo();
  }
  bDirty = bbDirty;

#endif
}

t_variant _form::METHOD_Record(QString sFieldName)
{ 
#ifdef RUN  
  if (!bTableView){
  //  return rd_Record(q.record(), sFieldName);
  } else {
  }
#endif
  return 0;
}


void _form::METHOD_SetRecord(QString FieldName, t_variant Value)
{ 
#ifdef RUN
  if (!bTableView){
    //bDirty = true;
    //recordbuffer[FieldName] = Value;
  } else {
  }
#endif
}

t_boolean _form::updateFromControls()
{ 
#ifdef RUN

#endif
  return false;
}

t_boolean _form::stopByQuestion(bool bQuestion)
{ 
#ifdef RUN
  if (!bTableView){
    if (bDirty){
      if (bAddNew){

        QString kk = "New Record"; if (trs.contains(kk)) kk = trs[kk];
        QString qq = "Would you like to save this new record (else changes will be lost)?"; if (trs.contains(qq)) qq = trs[qq];

        if (bQuestion && QMessageBox::question(this, kk, qq, QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
          setDirty(false);
          setAddNew(false);
          return false;
        }

        QString sTable = getSQLTableName();
        QString sKBRecordId = getPrimary(sTable);
        
        QString fields = "";     
        QString values = "";     

        QSqlRecord r = q.record();

        qulonglong kbrecordid = 0;

        QWidget *c;
        bool b = true;
        if (firstControl(&c)){
          do {

            QString sSQLName = "";                    
            #define SWITCH GETPROPERTY_SQLName();      
            #define SWITCH3 sSQLName
            #include "_form_property_switch.h"   
            #undef SWITCH3
    
            QString sSQLRelation = "";                    
            #define SWITCH GETPROPERTY_SQLRelation();      
            #define SWITCH3 sSQLRelation
            #include "_form_property_switch.h"   
            #undef SWITCH3

            if (!sSQLName.isEmpty()){

              QString sControlType = "";
              #define SWITCH GETPROPERTY_ControlType();      
              #define SWITCH3 sControlType
              #include "_form_property_switch.h"   
              #undef SWITCH3

              if (!b) fields += ", ";
              fields += sSQLName; 

              if (!b) values += ", ";
              QString value = "";

              if (b) b = false;

              if (sControlType == "Label") value += ((_label *) c)->GETPROPERTY_Caption();
              else if (sControlType == "TextBox") value += ((_textbox *) c)->GETPROPERTY_StringValue();
              /*
              else if (sControlType == "Sound"){
                value += ((_sound *) c)->GETPROPERTY_StringValue();
              }*/
              else if (sControlType == "ComboBox"){
                if (!sSQLRelation.isEmpty()){
                  int n = ((_combobox *) c)->currentIndex();
                  if (n >= 0) value += ((_combobox *) c)->itemData(n).toString();                      
                } else {
                  value += ((_combobox *) c)->GETPROPERTY_StringValue();            
                }
              }
              else if (sControlType == "ListBox"){
                if (!sSQLRelation.isEmpty()){
                  QListWidgetItem *it = ((_listbox *) c)->currentItem();
                  if (it) value += it->data(Qt::UserRole).toString(); 
                } else {
                  value += ((_listbox *) c)->GETPROPERTY_StringValue();            
                }              
              }
              else if (sControlType == "CheckBox") value += ((_checkbox *) c)->GETPROPERTY_BooleanValue() ? "True" : "False";
              else if (sControlType == "DateBox"){
                  value += ((_datebox *) c)->GETPROPERTY_StringValue();
              }
              else if (sControlType == "TimeBox"){
                  value += ((_timebox *) c)->GETPROPERTY_StringValue();
              }
              else if (sControlType == "RichTextBox") value += ((_editor *) c)->GETPROPERTY_StringValue();

             int n = r.indexOf(sSQLName);
             QSqlField f = r.field(n);
             
             if (sSQLName == sKBRecordId&& value.isEmpty()){
                QSqlQuery rr(CurrentDatabase);
                QString s = "SELECT " + sKBRecordId + " FROM " + sTable + " ORDER BY " + sKBRecordId + " DESC";
                if (rr.exec(s)){
                  //my_log->METHOD_PrintSql(s);                  
                 // addLog(s);

                  if (rr.first()){
                    QSqlRecord r = rr.record();
                    int n = r.indexOf(sKBRecordId);
                    kbrecordid = rr.value(n).toLongLong();
                    values += QString("%1").arg(++kbrecordid);
                  } else {
                    values += "1";
                  }
                } else {
                  values += "1";
                }                
              } else {

                switch(f.type()){
                  case QVariant::Bool:
                    values += value.isEmpty() ? "NULL" : value;
                    break;
                  case QVariant::Date: 
                    values += value.isEmpty() ? "NULL" : "'" + value + "'";
                    break;
                  case QVariant::Time: 
                    values += value.isEmpty() ? "NULL" : "'" + value + "'";
                    break;
                  case QVariant::Double:
                    values += value.isEmpty() ? "0" : value;
                    break;
                  case QVariant::UInt:
                  case QVariant::ULongLong:
                  case QVariant::LongLong:
                  case QVariant::Int:
                    values += value.isEmpty() ? "0" : value;
                    break;
                  case QVariant::String: 
                    value = value.replace("'", "''");

                    values += "'";
                    values += value;
                    values += "'";
                    break;
                  default:

                    if (value.isEmpty()){
                      values += "NULL";
                    } else {
                      value = value.replace("'", "''");

                      values += "'";
                      values += value;
                      values += "'";
                    }

                    //values += value.isEmpty() ? "0" : value;
                    break;
                }
              }
            
            
            }
            

          } while (nextControl(&c));
        } 


        QString sql = "INSERT INTO " + sTable + "(" + fields + ") VALUES (" + values + ")";

        QSqlQuery rr(CurrentDatabase);
        if (rr.exec(sql)){
          //my_log->METHOD_PrintSql(sql);
         // addProtocol(tr("1 record added"));
         // addLog(sql);
          setAddNew(false);
          setDirty(false);
          EVENT_OnQuery();
          METHOD_ClearFilter();
          nQuerySize = 0;
          QString k = q.executedQuery();
          if (!q.exec(k)) QMessageBox::information(this, MYAPP, q.lastError().text());
          //my_log->METHOD_PrintSql(k);
          setQuerySize();

         // addLog(q.executedQuery());
          QString sKBRecordId = getPrimary(sTable);
          if (q.first()){
            do {
              QSqlRecord a = q.record();
              int n = a.indexOf(sKBRecordId);
              if (n >= 0){
                QVariant v = a.value(n);
                if (v.toLongLong() == kbrecordid){
                  METHOD_GoTo(q.at() + 1, false);
                  break;
                }                
              }
            } while (q.next());
          }
        } else {
          QMessageBox::information(this, MYAPP, rr.lastError().text());
        }

      } else {

        QString kk = "Current Record Changed"; if (trs.contains(kk)) kk = trs[kk];
        QString qq = "Would you like to save the changes?"; if (trs.contains(qq)) qq = trs[qq];

        if (bQuestion && QMessageBox::question(this, kk, qq, QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
          setDirty(false);
          return false;
        }

        QString sTable = getSQLTableName();   
        QString sKBRecordId = getPrimary(sTable);

        QString fields = "";     
        //QString values = "";     

        QSqlRecord r = q.record();

        QWidget *c;
        bool b = true;
        qulonglong kbrecordid = 0;

        if (firstControl(&c)){
          do {

            QString sSQLName = "";                    
            #define SWITCH GETPROPERTY_SQLName();      
            #define SWITCH3 sSQLName
            #include "_form_property_switch.h"   
            #undef SWITCH3
    
            QString sSQLRelation = "";                    
            #define SWITCH GETPROPERTY_SQLRelation();      
            #define SWITCH3 sSQLRelation
            #include "_form_property_switch.h"   
            #undef SWITCH3

            if (!sSQLName.isEmpty()){

              QString sControlType = "";
              #define SWITCH GETPROPERTY_ControlType();      
              #define SWITCH3 sControlType
              #include "_form_property_switch.h"   
              #undef SWITCH3

              if (sControlType == "Sound"){
                continue;
              } if (sControlType == "MovieBox"){
                continue;
              } if (sControlType == "ImageBox"){
                continue;
              } if (sControlType == "HtmlView"){
                continue;
              } if (sControlType == "WebView"){
                continue;
              } if (sControlType == "RichTextBox"){
                continue;
              }

              if (sSQLName != sKBRecordId){
                if (!b) fields += ", ";
                fields += sSQLName; 
                fields += " = "; 
                if (b) b = false;
              }
              
              
              QString value = "";

              if (sControlType == "Label") value += ((_label *) c)->GETPROPERTY_Caption();
              else if (sControlType == "TextBox") value += ((_textbox *) c)->GETPROPERTY_StringValue();
              else if (sControlType == "ComboBox"){
                if (!sSQLRelation.isEmpty()){
                  int n = ((_combobox *) c)->currentIndex();
                  if (n >= 0) value += ((_combobox *) c)->itemData(n).toString();                      
                } else {
                  value += ((_combobox *) c)->GETPROPERTY_StringValue();            
                }
              }
              else if (sControlType == "ListBox"){
                if (!sSQLRelation.isEmpty()){
                  QListWidgetItem *it = ((_listbox *) c)->currentItem();
                  if (it) value += it->data(Qt::UserRole).toString(); 
                } else {
                  value += ((_listbox *) c)->GETPROPERTY_StringValue();            
                }              }
              else if (sControlType == "CheckBox") value += ((_checkbox *) c)->GETPROPERTY_BooleanValue() ? "True" : "False";
              else if (sControlType == "DateBox"){
                  QDate d = ((_datebox *) c)->date();
                  value += d.toString("yyyy-MM-dd");
                  //value += ((_datebox *) c)->GETPROPERTY_StringValue();
              }
              else if (sControlType == "TimeBox"){
                  QTime d = ((_timebox *) c)->time();
                  value += d.toString("hh:mm:ss");
//                  value += ((_timebox *) c)->GETPROPERTY_StringValue();
              }
              else if (sControlType == "RichTextBox"){
                value += ((_editor *) c)->GETPROPERTY_StringValue();
              }

             int n = r.indexOf(sSQLName);
             QSqlField f = r.field(n);

              if (sSQLName == sKBRecordId){
                kbrecordid = value.toLongLong();
              } else {

                switch(f.type()){
                  case QVariant::Bool:
                    fields += value.isEmpty() ? "NULL" : value;
                    break;
                  case QVariant::Date: 
                    fields += value.isEmpty() ? "NULL" : "'" + value + "'";
                    break;
                  case QVariant::Time: 
                    fields += value.isEmpty() ? "NULL" : "'" + value + "'";
                    break;
                  case QVariant::Double:
                    fields += value.isEmpty() ? "0" : value;
                    break;
                  case QVariant::UInt:
                  case QVariant::ULongLong:
                  case QVariant::LongLong:
                  case QVariant::Int:
                    fields += value.isEmpty() ? "0" : value;
                    break;
                  case QVariant::String: 
                    value = value.replace("'", "''");
                    fields += value.isEmpty() ? "NULL" : "'" + value + "'";
                    break;
                  default:
                    value = value.replace("'", "''");
                    fields += value.isEmpty() ? "NULL" : ("'" + value + "'");
                    break;
                }
              }

            
            }            

          } while (nextControl(&c));
        } 


        QString sql = "UPDATE " + sTable + " SET " + fields + " WHERE " + sKBRecordId + " = " + QString("%1").arg(kbrecordid);
       /* QTextEdit *t = new QTextEdit(sql);
        t->showMaximized();*/

        QSqlQuery rr(CurrentDatabase);
        if (rr.exec(sql)){

          if (firstControl(&c)){
            do {

              QString sSQLName = "";                    
              #define SWITCH GETPROPERTY_SQLName();      
              #define SWITCH3 sSQLName
              #include "_form_property_switch.h"   
              #undef SWITCH3
      
              QString sSQLRelation = "";                    
              #define SWITCH GETPROPERTY_SQLRelation();      
              #define SWITCH3 sSQLRelation
              #include "_form_property_switch.h"   
              #undef SWITCH3

              if (!sSQLName.isEmpty()){

                QString sControlType = "";
                #define SWITCH GETPROPERTY_ControlType();      
                #define SWITCH3 sControlType
                #include "_form_property_switch.h"   
                #undef SWITCH3

                QString k = "";
                if (sControlType == "Sound"){
                  k = ((_sound *) c)->GETPROPERTY_StringValue();                 
                } else if (sControlType == "MovieBox"){
                  k = ((_movie *) c)->GETPROPERTY_StringValue();                 
                } else if (sControlType == "ImageBox"){
                  k = ((_image *) c)->GETPROPERTY_StringValue();                 
                } else if (sControlType == "HtmlView"){
                  k = ((_browser *) c)->GETPROPERTY_StringValue();                 
                } else if (sControlType == "WebView"){
                  k = ((_web *) c)->GETPROPERTY_StringValue();                 
                } else if (sControlType == "RichTextBox"){
                  k = ((_editor *) c)->GETPROPERTY_StringValue();                 
                } else {
                  continue;
                }

                //if (!k.isEmpty())
                {
                  k = k.replace(QChar(0), "ZERO_kbasic");
                  k = k.replace(QChar('\''), "SINGLEQUOTE_kbasic");
                  k = k.replace(QChar('\\'), "BACKSLASH_kbasic");
                  
                  k = k.replace(QChar('\x00'), "x00_kbasic");
                  k = k.replace(QChar('\x1a'), "x1a_kbasic");

                  k = k.replace(QChar('\n'), "n_kbasic");
                  k = k.replace(QChar('\t'), "t_kbasic");
                  k = k.replace(QChar('\f'), "f_kbasic");
                  k = k.replace(QChar('\r'), "r_kbasic");
                  k = k.replace(QChar('\v'), "v_kbasic");

               //   QString kkk;

                //  kkk = kkk.fill(QChar('z'), 500000);

                  QSqlQuery query2(CurrentDatabase);
                  query2.prepare("UPDATE " + sTable + " SET " + sSQLName + "=:" + sSQLName + " WHERE " + sKBRecordId + " = " + QString("%1").arg(kbrecordid));
                  query2.bindValue(":" + sSQLName, k, QSql::In/* | QSql::Binary*/);
                  bool b = query2.exec();
                  if (!b) QMessageBox::information(this, MYAPP, query2.lastError().text());                  
                }
              }

            } while (nextControl(&c));
          } 

          //my_log->METHOD_PrintSql(sql);
         // addProtocol(tr("1 record changed"));
         // addLog(sql);
          setDirty(false);
          
          EVENT_OnQuery();          
          //METHOD_ClearFilter();
          QString ss = q.executedQuery();
          nQuerySize = 0;
          if (!q.exec(ss)) QMessageBox::information(this, MYAPP, q.lastError().text());
          //my_log->METHOD_PrintSql(ss);
          setQuerySize();
         // addLog(ss);
          
          if (q.first()){
            do {                
              QSqlRecord a = q.record();
              int n = a.indexOf(sKBRecordId);
              if (n >= 0){
                QVariant v = a.value(n);
                QString mm = v.toString();
                qulonglong m = v.toLongLong();
                
                if (m == kbrecordid){
                  METHOD_GoTo(q.at() + 1, false);
                  return false;
                }         
              }
            } while (q.next());
          }
                   
        } else {
          QMessageBox::information(this, MYAPP, rr.lastError().text());
        }

      }
      
      return false;
    }
  } else {
    if (bAddNew){

      QString kk = "New Record"; if (trs.contains(kk)) kk = trs[kk];
      QString qq = "Would you like to save this new record (else changes will be lost)?"; if (trs.contains(qq)) qq = trs[qq];

      if (bQuestion && QMessageBox::question(this, kk, qq, QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
        setAddNew(false);
        return false;
      }

      qulonglong kbrecordid = 0;

      QString sKBRecordId = getPrimary(getSQLTableName());

      QSqlQuery rr(CurrentDatabase);
      QString s = "SELECT " + sKBRecordId + " FROM " + getSQLTableName() + " ORDER BY " + sKBRecordId + " DESC";
      if (rr.exec(s)){
        //my_log->METHOD_PrintSql(s);
       // addLog(s);
        if (rr.first()){
          QSqlRecord r = rr.record();
          int n = r.indexOf(sKBRecordId);


          kbrecordid = rr.value(n).toLongLong() + 1;

          int p = sqlm.rowCount() - 1;
          r = sqlm.record(p);
          n = r.indexOf(sKBRecordId);
          r.setValue(n, QVariant(kbrecordid));
          bool b = sqlm.setRecord(p, r);
          setAddNew(false);
          sqlm.submitAll();
          //sqlm.insertRecord(-1, r);
        }
      }     
    
    } else {

      QString kk = "Current Record Changed"; if (trs.contains(kk)) kk = trs[kk];
      QString qq = "Would you like to save the changes?"; if (trs.contains(qq)) qq = trs[qq];

      if (bQuestion && QMessageBox::question(this, kk, qq, QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
        sqlm.revertAll();
        return false;
      } else {
        sqlm.submitAll();
      }

    }
  
  }
#endif
  return false;
}



t_boolean _form::METHOD_Insert()
{ 
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return false;
  if (GETPROPERTY_SQLInsert()){
    t_boolean b = false;
    EVENT_OnBeforeInsert(&b);
    if (!b){
      if (!bTableView){
        METHOD_Update();
      } else {
        METHOD_Update();
      }
    }
  }
#endif
  return false;
}

t_boolean _form::METHOD_Update()
{ 
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return false;
  if (GETPROPERTY_SQLUpdate()){
    t_boolean b = false;
    EVENT_OnBeforeUpdate(&b);
    if (!b){

      if (!bTableView){
        //if (q.isValid() && METHOD_Len()){
        return stopByQuestion(false);
          
        //}
      } else {
        //*sqlm.submit();
        //updateFromControls();
        return true;
      }
    }
  }
#endif
  return false;
}

t_boolean _form::METHOD_Cut()
{
  return false;
}

t_boolean _form::METHOD_Copy()
{
  return false;
}

t_boolean _form::METHOD_Paste()
{
  return false;
}

t_boolean _form::METHOD_Delete()
{ 
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return false;
  if (GETPROPERTY_SQLDelete()){
    t_boolean b = false;
    EVENT_OnBeforeDelete(&b);
    if (!b){

      if (!bTableView){

        QString kk = "Delete Current Record"; if (trs.contains(kk)) kk = trs[kk];
        QString qq = "Would you like to delete the current record?"; if (trs.contains(qq)) qq = trs[qq];

        if (QMessageBox::question(this, kk, qq, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){

          QString sTable = getSQLTableName();    
          QString sKBRecordId = getPrimary(sTable);

          QString fields = "";     
          QString values = "";     

          QSqlRecord r = q.record();

          QWidget *c;
          if (firstControl(&c)){
            do {

              QString sSQLName = "";                    
              #define SWITCH GETPROPERTY_SQLName();      
              #define SWITCH3 sSQLName
              #include "_form_property_switch.h"   
              #undef SWITCH3
      
              if (!sSQLName.isEmpty()){

                QString sControlType = "";
                #define SWITCH GETPROPERTY_ControlType();      
                #define SWITCH3 sControlType
                #include "_form_property_switch.h"   
                #undef SWITCH3

                QString value = "";

                if (sControlType == "Label") value += ((_label *) c)->GETPROPERTY_Caption();
                //else if (sControlType == "Sound") value += ((_sound *) c)->GETPROPERTY_StringValue();
                else if (sControlType == "TextBox") value += ((_textbox *) c)->GETPROPERTY_StringValue();
                else if (sControlType == "ComboBox") value += ((_combobox *) c)->GETPROPERTY_StringValue();            
                else if (sControlType == "ListBox") value += ((_listbox *) c)->GETPROPERTY_StringValue();
                /*
                else if (sControlType == "CheckBox") value += ((_checkbox *) c)->GETPROPERTY_BooleanValue() ? "True" : "False";
                else if (sControlType == "DateBox"){
                    value += ((_datebox *) c)->GETPROPERTY_StringValue();
                }
                else if (sControlType == "TimeBox"){
                    value += ((_timebox *) c)->GETPROPERTY_StringValue();
                }
                else if (sControlType == "RichTextBox") value += ((_editor *) c)->GETPROPERTY_StringValue();
*/
             // int n = r.indexOf(sSQLName);
           //   QSqlField f = r.field(n);

                if (sSQLName == sKBRecordId){                  

                  QSqlQuery rr(CurrentDatabase);
                  QString s = "DELETE FROM " + sTable + " WHERE " + sKBRecordId + " = " + value;
                  if (rr.exec(s)){
                    //my_log->METHOD_PrintSql(s);
                   // addLog(s);
                    setDirty(false);
                    METHOD_Requery();

                   // addProtocol(tr("1 record deleted"));

                    return true;

                    /*
                    if (!METHOD_Next()) if (!METHOD_First()) value = "";

                    qulonglong kbrecordid = value.toLongLong();

                    bDirty = false;
                    METHOD_Requery();

                    if (q.first()){
                      do {
                        QSqlRecord a = q.record();
                        int n = a.indexOf(sKBRecordId);
                        if (n >= 0){
                          QVariant v = a.value(n);
                          if (v.toLongLong() == recordid){
                            METHOD_GoTo(q.at() + 1, false);
                            break;
                          }                
                        }
                      } while (q.next());

                    }
                    */
                  } else {
                    QMessageBox::information(this, MYAPP, rr.lastError().text());
                  }          
                  break;
                }
              }          
            } while (nextControl(&c));
          } 
        }
      } else {

        QString kk = "Delete Record"; if (trs.contains(kk)) kk = trs[kk];
        QString qq = "Would you like to delete the current record?"; if (trs.contains(qq)) qq = trs[qq];

        if (QMessageBox::question(this, kk, qq, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
          QHeaderView *m = sqlv->horizontalHeader();

          sqlm.removeRows(m->currentIndex().row(), 1);
          METHOD_First(false);

          return true;

          /*
          QItemSelectionModel *l = m->selectionModel();
          for (int i = 0; i < sqlm.rowCount(); i++){
            if (l->isRowSelected(i + 1, QModelIndex())){
              sqlm.removeRows(i + 1, 1);
            }
          }*/
            /*
          int n = m->currentIndex().row();
          QItemSelectionModel *l = m->selectionModel();
          QModelIndexList k = l->selectedRows();
          int nn = k.count();
          bool b = sqlm.removeRows(n, nn);
          b = b;
          
          }*/
        }
      }
    }
  }
#endif
  return false;
}

t_boolean _form::METHOD_AddNew()
{ 
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return false;
  if (GETPROPERTY_SQLInsert()){
    if (!bTableView && stopByQuestion()) return false;

    bLoading = true;

    if (!bTableView){      
      q.last();
      q.next();
      setAddNew(true);

      QWidget *c;
      if (firstControl(&c)){
        do {

          QString sControlName = c->objectName();                    
          /*
          #define SWITCH GETPROPERTY_Name();      
          #define SWITCH3 sControlName
          #include "_form_property_switch.h"   
          #undef SWITCH3*/

          QString sSQLName = "";                    
          #define SWITCH GETPROPERTY_SQLName();      
          #define SWITCH3 sSQLName
          #include "_form_property_switch.h"   
          #undef SWITCH3
  /*
          QString sSQLType = "";                    
          #define SWITCH GETPROPERTY_SQLType();      
          #define SWITCH3 sSQLType
          #include "_form_property_switch.h"   
          #undef SWITCH3
  */
          if (!sSQLName.isEmpty()){
            // int n = a.indexOf(sSQLName);
              //if (n >= 0)
              {
              // QVariant v = q.value(n);

                QString sControlType = "";
                #define SWITCH GETPROPERTY_ControlType();      
                #define SWITCH3 sControlType
                #include "_form_property_switch.h"   
                #undef SWITCH3

                if (sControlType == "Label") ((_label *) c)->SETPROPERTY_Caption("");
                //else if (sControlType == "Sound") ((_sound *) c)->SETPROPERTY_StringValue("");
                else if (sControlType == "TextBox") ((_textbox *) c)->SETPROPERTY_StringValue("");
                else if (sControlType == "ComboBox") ((_combobox *) c)->METHOD_Select("");            
                else if (sControlType == "ListBox") ((_listbox *) c)->METHOD_Select("");
                else if (sControlType == "CheckBox") ((_checkbox *) c)->SETPROPERTY_BooleanValue(false);
                else if (sControlType == "DateBox"){
  //                QString s = v.toString();
                    ((_datebox *) c)->setDate(QDate(/*1979, 1, 1*/));                 
                    //((_datebox *) c)->setCurrentSection(QDateTimeEdit::DaySection); ((_datebox *) c)->clear();
                    //((_datebox *) c)->setCurrentSection(QDateTimeEdit::MonthSection); ((_datebox *) c)->clear();
                    ((_datebox *) c)->setCurrentSection(QDateTimeEdit::YearSection); ((_datebox *) c)->clear();                   
                }
                else if (sControlType == "TimeBox"){
            //     QString s = v.toString();
                    ((_timebox *) c)->setTime(QTime(/*1979, 1, 1*/));                 
                    ((_timebox *) c)->setCurrentSection(QDateTimeEdit::HourSection); ((_timebox *) c)->clear();

                }
                //else if (sControlType == "DateTimeBox") ((_datetimebox *) c)->SETPROPERTY_StringValue(v.toString());
                else if (sControlType == "RichTextBox") ((_editor *) c)->SETPROPERTY_StringValue("");

              }
          }

        } while (nextControl(&c));
      } 
    } else {
      
      QSqlRecord r = CurrentDatabase.record(getSQLTableName());
      sqlm.insertRecord(-1, r);
      METHOD_Last();
      //setAddNew(true); // must be after set position of current record
      
      bLoading = false;
      return true;
    }
  bLoading = false;
  

  EVENT_OnAddNew();

  setDirty(true);
#endif

  return true;

  }

  return false;
}

t_boolean _form::METHOD_Last(bool bInvokedByUser)
{ 
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return false;
  if (!bTableView){     
    if (q.at() + 1 == METHOD_Len()) return true;
    if (stopByQuestion()) return false;
    if (q.last()){
      if (bInvokedByUser)// addProtocol("");
      bLoading = true; setSQL(); bLoading = false;
      return true;
    }
  } else {
    QHeaderView *m = sqlv->horizontalHeader();
    t_long x = sqlm.rowCount() - 1;
    sqlv->setFocus();
    if (x < 0) return true;
    //if (x + 1 == sqlm.rowCount()) return true;
    //x = sqlm.rowCount();

    int nn = m->currentIndex().row();
    if (nn == -1){
      m->setCurrentIndex(m->model()->index(x, 0));    
    } else {
      m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
    }

    //m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
    if (m->currentIndex().row() == x){
      sqlv->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
/*
      EVENT_OnGoTo2();
      EVENT_OnGoTo();*/
      return true;
    }
  }
  return false;
#endif
}

t_boolean _form::METHOD_Previous(bool bInvokedByUser)
{ 
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return false;
  if (!bTableView){     
    if (q.at() == 0) return true;
    if (stopByQuestion()) return false;
    if (q.previous()){
      if (bInvokedByUser)// addProtocol("");
      bLoading = true; setSQL(); bLoading = false;
      return true;
    }
  } else {
    QHeaderView *m = sqlv->horizontalHeader();
    t_long x = m->currentIndex().row() - 1;
    sqlv->setFocus();
    if (x < 0) return true;
//    m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    

    int nn = m->currentIndex().row();
    if (nn == -1){
      m->setCurrentIndex(m->model()->index(x, 0));    
    } else {
      m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
    }

    if (m->currentIndex().row() == x){
      sqlv->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
/*
      EVENT_OnGoTo2();
      EVENT_OnGoTo();*/
      return true;
    }
  }
  return false;
#endif
}

t_boolean _form::METHOD_First(bool bInvokedByUser)
{ 
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return false;
  if (!bTableView){    
    if (q.at() == 0) return true;
    if (stopByQuestion()) return false;
    if (q.first()){
      if (bInvokedByUser)// addProtocol("");
      bLoading = true; setSQL(); bLoading = false;
      return true;
    }
  } else {
    QHeaderView *m = sqlv->horizontalHeader();
    //m->selectionModel()->setCurrentIndex(m->currentIndex().sibling(0, m->currentIndex().column()), QItemSelectionModel::SelectCurrent);
//    m->setCurrentIndex(m->currentIndex().sibling(0, m->currentIndex().column()));
    sqlv->setFocus();

    int x = 0;
    int nn = m->currentIndex().row();
    if (nn == -1){
      nn = x;
      m->setCurrentIndex(m->model()->index(x, 0));    
    } else {
      m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
    }
    //if (nn == x)
    {
      sqlv->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
    }

    if (m->currentIndex().row() == 0){
      /*
      EVENT_OnGoTo2();
      EVENT_OnGoTo();*/
      return true;
    } 
  }
  return false;
#endif
}


t_boolean _form::METHOD_Next(bool bInvokedByUser)
{ 
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return false;
  if (!bTableView){    
    if (q.at() + 1 == METHOD_Len()) return true;
    if (stopByQuestion()) return false;
    if (q.next()){
      if (bInvokedByUser)// addProtocol("");
      bLoading = true; setSQL(); bLoading = false;
      return true;
    }
  } else {
    QHeaderView *m = sqlv->horizontalHeader();
    t_long x = m->currentIndex().row() + 1;
    sqlv->setFocus();
    if (x + 1 > sqlm.rowCount()) return true;
    //m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
  
    int nn = m->currentIndex().row();
    if (nn == -1){
      m->setCurrentIndex(m->model()->index(x, 0));    
    } else {
      m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
    }
    sqlv->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);

    if (m->currentIndex().row() == x){
      /*
      EVENT_OnGoTo2();
      EVENT_OnGoTo();*/
      return true;
    }
  }
  return false;
#endif
}

t_boolean _form::METHOD_GoTo(t_long l, bool bInvokedByUser)
{ 
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return false;
  if (!bTableView){    
    if (!(l > 0 && l <= METHOD_Len())) return false;
    if (stopByQuestion()) return false;
    if (q.seek(l - 1)){
      if (bInvokedByUser)// addProtocol("");
      bLoading = true; setSQL(); bLoading = false;
      return true;
    }
  } else {
    QHeaderView *m = sqlv->horizontalHeader();
    t_long x = l - 1;
    sqlv->setFocus();
    if (x < 0) return true;
    if (x + 1 > sqlm.rowCount()) return true;
//    m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    

    int nn = m->currentIndex().row();
    if (nn == -1){
      m->setCurrentIndex(m->model()->index(x, 0));    
    } else {
      m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
    }

    if (m->currentIndex().row() == x){

      sqlv->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
      /*
      EVENT_OnGoTo2();
      EVENT_OnGoTo();*/
      return true;
    }
  }
  return false;
#endif
}

#endif


#ifdef RUN

void _form::METHOD_OpenMaximized()
{  
  METHOD_Open(false, false, false, false, -1, -1, -1, -1, true);

  

}

void _form::METHOD_OpenMinimized()
{  
  METHOD_Open(false, false, false, false, -1, -1, -1, -1, false, true);
}

void _form::METHOD_OpenCenteredOnlyOnce()
{  
  METHOD_Open();
}

void _form::METHOD_OpenOnlyOnce()
{  
  METHOD_Open();
}

void _form::METHOD_OpenHiddenOnlyOnce()
{  
  METHOD_Open();
}


void _form::METHOD_OpenHidden()
{  
  METHOD_Open(true);
}

void _form::METHOD_OpenFullScreen()
{  
  METHOD_Open(false, false, true);
}

void _form::METHOD_OpenCentered()
{  
  METHOD_Open(false, false, false, true);
}

void _form::METHOD_Open(int X, int Y)
{  
  METHOD_Open(false, false, false, false, X, Y);
}

void _form::METHOD_Open(int X, int Y, int Width, int Height)
{  
  METHOD_Open(false, false, false, false, X, Y, Width, Height);
}

void _form::setQuerySize()
{
  if (!bQuerySize){ 
    nQuerySize = 0;
    if (q.first()){
      do {
        nQuerySize++;
      } while (q.next());
    }            
  }
}

void _form::METHOD_Open(bool bHidden, bool bRequeryOnly, bool bFullScreen, bool bCentered, int X, int Y, int Width, int Height, bool bOpenMaximized, bool bOpenMinimized, bool bOpenCenteredOnlyOnce, bool bOpenOnlyOnc, bool bOpenHiddenOnlyOnce)
{  
  static bool bLock = false;

#ifdef RUN

  // QMessageBox::information(0, "0", isVisible() ? "YES" : "NO");     


  if (!bRequeryOnly && bMETHOD_Open_Opened){
   // showNormal();
    if (Width >= 0 || Height >= 0){
      setGeometry(X, Y, Width, Height);
    } else if (X >= 0 || Y >= 0){
      setGeometry(X, Y, width(), height());
    }
    if (bFullScreen){
      METHOD_ShowFullScreen();
    } else if (bOpenMaximized){
      METHOD_ShowMaximized();
    } else if (bOpenMinimized){
      METHOD_ShowMinimized();
    } else if (bOpenMinimized){
      METHOD_ShowMinimized();
    } else if (bCentered || bOpenCenteredOnlyOnce){
      setGeometry(QApplication::desktop()->width() / 2 - width() / 2, QApplication::desktop()->height() / 2 - height() / 2, width(), height());
      show();
    } else if (bHidden || bOpenHiddenOnlyOnce){
    } else {
      if (isMinimized()){
        showNormal();
      } else {
        show();
      }
    }

    qApp->setActiveWindow(this);
    setFocus();
/*
  bDialogRunning = true;
  if (bDialog && bDialogRunning){
    bBlockOnceOpenModal = true;
    while(EXTERN_myInterpreter->bNoError && EXTERN_myInterpreter->bRunPcode && bDialogRunning){
      qApp->processEvents(QEventLoop::WaitForMoreEvents);
    }
  }
  bDialogRunning = false;
*/
    return;
  }

    // QMessageBox::information(0, "0b", isVisible() ? "YES" : "NO");     


  bool bGETPROPERTY_Visible = isVisible();//GETPROPERTY_Visible();
  if (!bHidden || bGETPROPERTY_Visible == false) QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));    

  
  if (bOpenonrun_forms && bLock == false && bLogin == false){
    bLock = true;
    bOpenonrun_forms = false;
    foreach(QString s, openonrun_forms){
      QString k = s.left(s.indexOf("."));
      int SAVE = nCurrentFormId;
      nCurrentFormId = forms2[k];
      kb_form *f = interpreter::openForm(k);
      //qApp->processEvents();
      /*
      memory_variable2 *v = EXTERN_myInterpreter->getVar(global);

      v->setObject(nId, f, 0);

      nCurrentFormId = SAVE;*/


    }
    bLock = false;
  }


      

  if (CurrentDatabase.isOpen()){
    q = QSqlQuery(CurrentDatabase);
    bQuerySize = CurrentDatabase.driver()->hasFeature(QSqlDriver::QuerySize);
  }

   //QMessageBox::information(0,"METHOD_Open", "1");     

  QString sCaption = this->GETPROPERTY_Caption();
  if (sCaption == ""){
    sCaption = this->getFilenameWithoutPathAndExtension();
    setWindowTitle(sCaption);
    this->SETPROPERTY_Caption(sCaption);
  } else {
    setWindowTitle(sCaption);
  }


  QString sShowMode = _property::GETPROPERTY_ShowMode();

  QString ss = "";
  bool bSpecialWindow = false;
  bool bDialog = false;  

  ss = this->GETPROPERTY_SQLName();
  QString sKBRecordId = getPrimary(ss);


  if (!CurrentDatabase.isOpen() && !ss.isEmpty() && !bTableView){
    bLoading = true;  setSQL2(q.record()); bLoading = false;
  }

  int nWindowFlag = 0;
  if (!bRequeryOnly && ParentForm == 0){
    QString ss = this->GETPROPERTY_Flag();
    



    if (!ss.isEmpty()){
      int i = 0;
      
      if (ss.contains("Tool", Qt::CaseInsensitive)){
        i |= Qt::Tool; bSpecialWindow = true;
        if (forms_mainwindow) setParent(forms_mainwindow);

        setProperty("ToolWindow", (int) this);

      }
      
      if (ss.contains("Dialog", Qt::CaseInsensitive)){ 
        i |= Qt::Dialog; bSpecialWindow = true; 
        setWindowModality(Qt::ApplicationModal);
        bDialog = true;
      }

      if (ss.contains("Sheet", Qt::CaseInsensitive)){ i |= Qt::Sheet; bSpecialWindow = true; }
      if (ss.contains("Drawer", Qt::CaseInsensitive)){ i |= Qt::Drawer; bSpecialWindow = true; }
      if (ss.contains("SystemMenu", Qt::CaseInsensitive)){ i |= Qt::WindowSystemMenuHint; }
      if (ss.contains("MinimizeButton", Qt::CaseInsensitive)){ i |= Qt::WindowMinimizeButtonHint; }
      if (ss.contains("MaximizeButton", Qt::CaseInsensitive)){ i |= Qt::WindowMaximizeButtonHint; }
#ifndef LINUX
      if (ss.contains("CloseButton", Qt::CaseInsensitive)){ i |= Qt::WindowCloseButtonHint; }
#endif
      if (ss.contains("ContextHelp", Qt::CaseInsensitive)){ i |= Qt::WindowContextHelpButtonHint; }
      if (ss.contains("WindowStaysOnTopHint", Qt::CaseInsensitive)){ i |= Qt::WindowStaysOnTopHint; bSpecialWindow = true; }
      if (ss.contains("Frameless", Qt::CaseInsensitive)){ i |= Qt::FramelessWindowHint; bSpecialWindow = true; }
      
      i |= Qt::CustomizeWindowHint;

      nWindowFlag = i;

      setWindowFlags((Qt::WindowFlags) i);

    }


    if (this->GETPROPERTY_Modal()){
      setWindowModality(Qt::ApplicationModal);
    }

    if (bSDI && !bSpecialWindow && forms_mainwindow && GETPROPERTY_Dock().isEmpty()){
      if (forms_mainwindow->centralWidget() && windowFlags() && Qt::Sheet == false && windowFlags() && Qt::Drawer == false && bFullScreen == false && !sShowMode.contains("FullScreen", Qt::CaseInsensitive)){
        //forms_mainwindow->centralWidget()->hide();
      }
      forms_mainwindow->setCentralWidget(this); // setting SDI
    }

  }

  // QMessageBox::information(0, "1", isVisible() ? "YES" : "NO");     

  if (!bRequeryOnly){

    QString sFontColor = this->GETPROPERTY_FontColor();

    if (!sFontColor.isEmpty()){
      
      if (!bTableView){
        QObjectList it = children(); // iterate over the children
        QObject *o;
        for (int q = 0; q < it.size(); q++){
          o = it.at(q);

          QString sControlName = o->objectName();    

          if (sControlName == "SQLRecordset" && o->parent() == this){
            ((_label *) o)->SETPROPERTY_FontColor(sFontColor);        
          }
          else if (sControlName == "SQLGoTo" && o->parent() == this){
            ((_textbox *) o)->SETPROPERTY_FontColor(sFontColor);    
          }
          else if (sControlName == "SQLInfo" && o->parent() == this){
            ((_label *) o)->SETPROPERTY_FontColor(sFontColor);            
          }

        }

      }
    }
  }

//sMNIDFilter = "";

  if (CurrentDatabase.isOpen() && !ss.isEmpty()){
    if (!bTableView){
      if (!bRequeryOnly){
        if (!ss.contains(" ")){
          ss = "SELECT * FROM " + ss;
        }
        QString sss = ss;
        sss = sss.left(sss.indexOf(" FROM ", Qt::CaseInsensitive));
        
        if (!sss.contains(sKBRecordId, Qt::CaseInsensitive) && !sss.contains("SELECT *", Qt::CaseInsensitive)){
          int k = ss.indexOf("SELECT ", Qt::CaseInsensitive);
          if (k >= 0){
            k += 7;
            ss = ss.insert(k, sKBRecordId + ", ");
          }
        }
        if (!ss.contains(" ORDER BY ", Qt::CaseInsensitive)){
          ss += " ORDER BY " + sKBRecordId + " asc";
        }
        SETPROPERTY_SQLName(ss);
      }
      
      if (CurrentDatabase.isOpen()){
        EVENT_OnQuery();
        nQuerySize = 0;
        if ((!ParentForm || bRequeryOnly) && !q.exec(ss)){
          QSqlError e = q.lastError();
          QMessageBox::information(0, tr("Error in SQLName = ") + ss,  e.text());  
        } else {
          //my_log->METHOD_PrintSql(ss);
          setQuerySize();
          if ((!ParentForm || bRequeryOnly))// addLog(ss);
          if (q.first()){
            bLoading = true; setSQL(); bLoading = false;
           // addProtocol(tr("Records loaded"));
          } else { // no results
            bLoading = true;  setSQL2(q.record()); bLoading = false;            
          }
        }
      }
      setDirty(false);
    } else {

      if (!bRequeryOnly){

        if (ss.contains("SELECT *", Qt::CaseInsensitive)){
          QString k = "";

          QWidget *c = 0;
          if (firstControl(&c)){
            do {                       
              
              QString s = "";

              #define SWITCH GETPROPERTY_SQLName();      
              #define SWITCH3 s
              #include "_form_property_switch.h"   
              #undef SWITCH3

              if (!s.isEmpty()){
                if (!k.isEmpty()) k += ", ";
                k += s;
              }

            } while (nextControl(&c));
          }

          k = "SELECT " + k;
          ss = ss.replace("SELECT *", k, Qt::CaseInsensitive);
  /*
          if (!ss.contains(sKBRecordId, Qt::CaseInsensitive)){
            int k = ss.indexOf("SELECT ", Qt::CaseInsensitive);
            if (k >= 0){
              k += 7;
              ss = ss.insert(k, sKBRecordId + ", ");
            }
          }*/

          SETPROPERTY_SQLName(ss);
        }
      }
      

      if (CurrentDatabase.isOpen()){

        QString sSAVE = this->GETPROPERTY_SQLName();

        setDirty(false);

        if (bRequeryOnly && ParentForm){

          QString s = this->GETPROPERTY_SQLName();

          int k = 0;
          while ((k = s.indexOf("$")) >= 0){
                      
            QString sField = s.mid(k + 1);
            int nn = sField.indexOf(" ");
            if (nn >= 0){
              sField = sField.left(nn);
            }
            sField = sField.replace(")", "");
            sField = sField.replace("'", "");

            QSqlRecord ri = ((_form *) ParentForm)->q.record();

            QString sValue = "";
            int n = ri.indexOf(sField);
            if (n >= 0){
              sValue = ((_form *) ParentForm)->q.value(n).toString();
              sValue = sValue.replace("'", "''");
            }  
            s = s.replace("$" + sField, sValue);    

          }

          this->SETPROPERTY_SQLName(s);
                   
        }

        if (!bRequeryOnly){
          sqlm.setEditStrategy(QSqlTableModel::OnFieldChange);
          sqlm.setTable(getSQLTableName());
        }
        QString sFilter = "";
        if (bRequeryOnly && ParentForm) sFilter = getSQLFilter();
/*
        if (!sFilter.isEmpty()){
          sFilter = "(" + sFilter + ") AND recordid<>0";
        } else {
          sFilter += sKBRecordId + "<>0";
        }*/
        sTableFilter = sFilter;

        QString sIDs = "";

        if (bRequeryOnly && ParentForm){
          QSqlQuery rr(CurrentDatabase);

          QString s = this->GETPROPERTY_SQLRelation();

          int k = s.lastIndexOf("$");
          QString sField = s.mid(k + 1);
          s = s.left(k);


          QSqlRecord ri = ((_form *) ParentForm)->q.record();

          int n = ri.indexOf(sField);
          if (n >= 0){
            sField = ((_form *) ParentForm)->q.value(n).toString();
          } else sField = "";
          s += sField;    

          if (rr.exec(s)){
            //my_log->METHOD_PrintSql(s);
            if (rr.first()){
              do {
                if (!sIDs.isEmpty()) sIDs += " OR ";
                sIDs += sKBRecordId + " = ";
                sIDs += rr.value(0).toString();
              } while (rr.next());
            } else sIDs += sKBRecordId + " = 0";
          }
                   
        }
        if (!sFilter.isEmpty() && !sIDs.isEmpty()){
          sFilter += " AND (";
          sFilter += sIDs;
          sFilter += ")";
        } else {
          sFilter += sIDs;
        }

        if (ParentForm && !bRequeryOnly){
          if (!sFilter.isEmpty()) sFilter += " AND (" + sKBRecordId + " = 0)";
          else sFilter += sKBRecordId + " = 0";
        }

        if (!sFilter.isEmpty()){
          sqlm.setFilter(sFilter);
        }

        QStringList so = getSQLSort();
        QStringList fi = getSQLFields();

        foreach(QString s, so){
          int n = -1;
          bool b = s.contains(" DESC", Qt::CaseInsensitive);
          if (s.contains(" ")){
            s = s.left(s.indexOf(" "));
          }

          QString ss = fi.at(0);
          if (ss == "*"){
            QMessageBox::information(0, tr("Error in SQLName"),  
              tr("You must not use * for selecting fields, \n"
              "if you use TableView mode. Write something like\n"
              "'SELECT field1, field2, field3 FROM myTable'.\n")
              );  
          
          }

          for (int i = 0; i < sqlm.record().count(); ++i){
            if (sqlm.fieldIndex(s) == i){
              n = i;
              break;
            }          
          }        
          if (n >= 0) sqlm.setSort(n, b ? Qt::DescendingOrder : Qt::AscendingOrder);
        }
        if (!sqlm.select()){
          QSqlError e = sqlm.lastError();
          QMessageBox::information(0, tr("Error in SQLName = ") + ss,  e.text());  
        } else {

          if (!ss.isEmpty() && !bRequeryOnly){
            sqlv = new TableView(this);

            QString sFontColor = this->GETPROPERTY_FontColor();

            if (!sFontColor.isEmpty()){

                QPalette p = palette();          
                p.setColor(QPalette::ButtonText, _property::getColor(sFontColor));  
                p.setColor(QPalette::WindowText, _property::getColor(sFontColor));  
                p.setColor(QPalette::Text, _property::getColor(sFontColor));          
                sqlv->setPalette(p);
            }

            sqlv->setSelectionMode(QAbstractItemView::SingleSelection);
            if (!GETPROPERTY_SQLUpdate()) sqlv->setEditTriggers(QAbstractItemView::NoEditTriggers);
          
#ifdef MAC
            sqlv->setAlternatingRowColors(true); // HIDE
#endif
          
            int x = GETPROPERTY_BorderLeft();
            int y = GETPROPERTY_BorderTop();
            int w = GETPROPERTY_Width() - GETPROPERTY_BorderRight() - GETPROPERTY_BorderLeft();
            int h = GETPROPERTY_Height() - GETPROPERTY_BorderBottom() - GETPROPERTY_BorderTop() - 25;
            sqlv->setGeometry(x, y, w, h);
            QHeaderView *hh = sqlv->horizontalHeader();
            QHeaderView *vv = sqlv->verticalHeader();
            hh->setMovable(true);
            sqlv->setItemDelegate(new TableViewDelegate(this));          

            //vv->setDefaultSectionSize(250);
            //vv->setCascadingSectionResizes(true);

            sqlv->setModel(&sqlm);

            for (int i = 0; i < hh->count(); i++){
              hh->setSectionHidden(i, true);
            }

            QString sss = GETPROPERTY_SQLName();

            QWidget *c = 0;
            if (firstControl(&c)){
              do {                       
                
                QString s = "";

                #define SWITCH GETPROPERTY_SQLName();      
                #define SWITCH3 s
                #include "_form_property_switch.h"   
                #undef SWITCH3

                if (!s.isEmpty()){

                  c->setHidden(true); // the actual control is hidden, only used for editing one table view cell

                  bool b = false;

                  #define SWITCH GETPROPERTY_TableViewVisible();      
                  #define SWITCH3 b
                  #include "_form_property_switch.h"   
                  #undef SWITCH3

                  if (!sss.contains(" " + s + ",", Qt::CaseInsensitive) && !sss.contains(" " + s + " ", Qt::CaseInsensitive)) b = false;

                  if (b){
                    int n = sqlm.fieldIndex(s);
                    if (n >= 0) hh->setSectionHidden(n, false);
                  } else {
                    int n = sqlm.fieldIndex(s);
                    if (n >= 0) hh->setSectionHidden(n, true);
                  }

                  int k = 0;

                  #define SWITCH GETPROPERTY_TableViewWidth();      
                  #define SWITCH3 k
                  #include "_form_property_switch.h"   
                  #undef SWITCH3

                  if (k > 0){
                    int n = sqlm.fieldIndex(s);
                    if (n >= 0) hh->resizeSection(n, k);
                  }

                  QString ss = "";

                  #define SWITCH GETPROPERTY_TableViewCaption();      
                  #define SWITCH3 ss
                  #include "_form_property_switch.h"   
                  #undef SWITCH3

                  if (!ss.isEmpty()){
                    int n = sqlm.fieldIndex(s);
                    if (n >= 0) sqlm.setHeaderData(n, Qt::Horizontal, ss);
                  }

                }
                
              } while (nextControl(&c));
            }
            /*
            EVENT_OnGoTo2();
            EVENT_OnGoTo();*/
          }

          METHOD_First(false);
          sqlv->show();

        }
        
        this->SETPROPERTY_SQLName(sSAVE);

      }
    }
    
  }


  if (!bHidden || bGETPROPERTY_Visible == false) QApplication::restoreOverrideCursor();

 //                    qApp->exec();

  // start timer, if needed
  int mn = GETPROPERTY_TimerInterval();  
  if (mn > 0 || mn == -1) SETPROPERTY_TimerInterval(GETPROPERTY_TimerInterval());

  // QMessageBox::information(0, "2", isVisible() ? "YES" : "NO");     

  /*
  int nMultiPageHeight = GETPROPERTY_MultiPageHeight();
  int nMultiPageBorderTop = GETPROPERTY_MultiPageBorderTop();
  int nMultiPageBorderBottom = GETPROPERTY_MultiPageBorderBottom();
  int nMultiPageBorderLeft = GETPROPERTY_MultiPageBorderLeft();
  int nMultiPageBorderRight = GETPROPERTY_MultiPageBorderRight();
        */
  // * running timer EventOnOpen
  {
    QWidget *c = 0;
    if (firstControl(&c)){
      do {
        
        if (controlType(c) == t_timer){
          /*kb*/_timer *t = qobject_cast</*kb*/_timer *>(c);

          if (t && t->GETPROPERTY_EventOnOpen()){
            ((kb_timer *) t)->EVENT_OnEvent();
          }

        }
/*
        if (nMultiPageHeight){
          int nMultiPage = 0;
          #define SWITCH GETPROPERTY_MultiPage();      
          #define SWITCH3 nMultiPage
          #include "_form_property_switch.h"   
          #undef SWITCH3

          if (nMultiPage && nMultiPage != nCurrentMultiPage){
            
          }

        }
*/
                
      } while (nextControl(&c));
    }
  }

  // *

  
  if (ParentForm == 0){    

    QString s = GETPROPERTY_Dock();

    if (forms_mainwindow && !s.isEmpty()){
      int i = 0;

      QString k = s;

      k = k.replace("AllF", "");
      k = k.replace("NoF", "");
      k = k.replace("SetL", "");
      k = k.replace("SetR", "");
      k = k.replace("SetT", "");
      k = k.replace("SetB", "");

      if (k.contains("Left")) i |= Qt::LeftDockWidgetArea;
      if (k.contains("Right")) i |= Qt::RightDockWidgetArea;
      if (k.contains("Top")) i |= Qt::TopDockWidgetArea;
      if (k.contains("Bottom")) i |= Qt::BottomDockWidgetArea;
      if (k.contains("All")) i |= Qt::AllDockWidgetAreas;
      if (k.contains("No")) i |= Qt::NoDockWidgetArea;

      dock = new QDockWidget(sCaption, forms_mainwindow);
      dock->setAllowedAreas(((Qt::DockWidgetAreas) i));    
      dock->setObjectName(GETPROPERTY_Name());
      /*
      {
        QString n = this->GETPROPERTY_Icon();
        dock->setWindowIcon(loadPixmap(n.contains(".") ? n : n + ".png"));
      }*/
      if (GETPROPERTY_DockTitleVisible() == false) dock->setTitleBarWidget(new QWidget());

      connect(dock, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(dockLocationChanged(Qt::DockWidgetArea)));
      connect(dock, SIGNAL(topLevelChanged(bool)), this, SLOT(topLevelChanged(bool)));
      connect(dock, SIGNAL(visibilityChanged(bool)), this, SLOT(visibilityChanged(bool)));
      
      //dock->setFloating(true);

      i = 0;

      if (s.contains("Closable")) i |= QDockWidget::DockWidgetClosable;
      if (s.contains("VerticalTitleBar")) i |= QDockWidget::DockWidgetVerticalTitleBar;
      if (s.contains("Movable")) i |= QDockWidget::DockWidgetMovable;
      if (s.contains("Floatable")) i |= QDockWidget::DockWidgetFloatable;
      if (s.contains("AllFeatures")) i |= QDockWidget::AllDockWidgetFeatures;
      if (s.contains("NoFeatures")) i |= QDockWidget::NoDockWidgetFeatures;

      dock->setFeatures((QDockWidget::DockWidgetFeature) i);

      i = Qt::LeftDockWidgetArea;


      if (s.contains("SetLeft")) i = Qt::LeftDockWidgetArea;
      else if (s.contains("SetRight")) i = Qt::RightDockWidgetArea;
      else if (s.contains("SetTop")) i = Qt::TopDockWidgetArea;
      else if (s.contains("SetBottom")) i = Qt::BottomDockWidgetArea;
        
      dock->setWidget(this);
      setProperty("DockWidget", (int) dock);
      /*
      QVariant v = property("DockWidget");
      bool b = v.isValid();
      int m = v.toInt();*/

      forms_mainwindow->addDockWidget((Qt::DockWidgetArea) i, dock);

      connect(dock, SIGNAL(topLevelChanged(bool)), this, SLOT(form_topLevelChanged(bool)));
      
      if (GETPROPERTY_Opacity()) SETPROPERTY_Opacity(GETPROPERTY_Opacity());
      if (!bHidden && !bGETPROPERTY_Visible) dock->show();
      
    } else {      
      {
        if (forms_workspace && !bSpecialWindow){
         // setGeometry(GETPROPERTY_X(), GETPROPERTY_Y(), GETPROPERTY_Width(), GETPROPERTY_Height());
          if (nWindowFlag){
            QMdiSubWindow *ww = new QMdiSubWindow();
            ww->setWidget(this);            
            setProperty("MdiSubWindow", (int) ww);           
            forms_workspace->addSubWindow(ww, Qt::Window | Qt::CustomizeWindowHint | (Qt::WindowFlags) nWindowFlag); 
            this->SETPROPERTY_Width(GETPROPERTY_Width(), false); // needed for correct sizes            
            ww->installEventFilter(this);
          } else {
            QMdiSubWindow *ww = new QMdiSubWindow();
            ww->setWidget(this);
            setProperty("MdiSubWindow", (int) ww);
            forms_workspace->addSubWindow(ww); 
            this->SETPROPERTY_Width(GETPROPERTY_Width(), false); // needed for correct sizes
            ww->installEventFilter(this);
          }
        } else if (forms_mainwindow){
         // setParent((QWidget *) forms_mainwindow);
        }

        QRect r;
        QWidget *w = this->parentWidget();
        if (w && qobject_cast<QMdiSubWindow *>(w)){
          r = w->layout()->contentsRect();      
        }

        if (Width >= 0 || Height >= 0){
          setGeometry(X, Y, Width + r.left() * 2, Height + r.top());
        } else if (X >= 0 || Y >= 0){
          setGeometry(X, Y, width() + r.left() * 2, height() + r.top());
        }

        QMapIterator<_form *, _childcontrol *>i(layout_childcontrols);
        while (i.hasNext()){
            i.next();

            _form *c = (_form *) i.key();
            _childcontrol *cc = i.value();

            c->SETPROPERTY_X(cc->GETPROPERTY_X());
            c->SETPROPERTY_Y(cc->GETPROPERTY_Y());
            c->SETPROPERTY_Width(cc->GETPROPERTY_Width(), false);
            c->SETPROPERTY_Height(cc->GETPROPERTY_Height(), false);

        }

        if (GETPROPERTY_Opacity()) SETPROPERTY_Opacity(GETPROPERTY_Opacity());
      
        {
          if (bFullScreen){
            METHOD_ShowFullScreen();
            sShowMode = "";
          } else if (bCentered || bOpenCenteredOnlyOnce){      
            if (forms_workspace && parentWidget() && (qobject_cast<QMdiSubWindow *>(parentWidget()))){
              QWidget *w = parentWidget()->parentWidget();
              QWidget *ww = parentWidget();
              ww->setGeometry(w->width() / 2 - ww->width() / 2, w->height() / 2 - ww->height() / 2, ww->width(), ww->height());
              if (!bHidden && !bGETPROPERTY_Visible) show();
            } else {
              setGeometry(QApplication::desktop()->width() / 2 - width() / 2, QApplication::desktop()->height() / 2 - height() / 2, width(), height());
              if (!bHidden && !bGETPROPERTY_Visible) show();
            }    
            sShowMode = "";

          } else if (bOpenMaximized){   
            //SETPROPERTY_Width(GETPROPERTY_Width(), false);
            if (!bHidden && !bGETPROPERTY_Visible) METHOD_ShowMaximized();
            sShowMode = "";

          } else if (bOpenMinimized){    
            //SETPROPERTY_Width(GETPROPERTY_Width(), false);
            if (!bHidden && !bGETPROPERTY_Visible) METHOD_ShowMinimized();
            sShowMode = "";

          } else if (bOpenHiddenOnlyOnce){      
            //SETPROPERTY_Width(GETPROPERTY_Width(), false);
            sShowMode = "";

          // bOpenOnlyOnce and default
          } else if (sShowMode.isEmpty() || sShowMode.contains("Normal", Qt::CaseInsensitive)){
         //   SETPROPERTY_Width(GETPROPERTY_Width(), false);
            if (!bHidden && !bGETPROPERTY_Visible) show();

          }
        }
        

      }
    }
  } else {
    setParent((QWidget *) ParentForm);
 //   this->SETPROPERTY_Width(Width, false);
 //   this->SETPROPERTY_Height(Height, false);
    if (GETPROPERTY_Opacity()) SETPROPERTY_Opacity(GETPROPERTY_Opacity());
  }

  // QMessageBox::information(0, "3", isVisible() ? "YES" : "NO");     

  if (!GETPROPERTY_Resizable()){

    QWidget *w = this->parentWidget();
    if (w && qobject_cast<QMdiSubWindow *>(w)){
      QRect r = w->layout()->contentsRect();         
      int hh =  w->height() - r.height();

      w->setMinimumSize(w->size().width(), size().height() + hh);
      w->setMaximumSize(w->size().width(), size().height() + hh);
     // w->setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    } else {
      setMinimumSize(size());
      setMaximumSize(size());
     // setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    }
  } 


  if (GETPROPERTY_ResizableBigger() == true){

    QWidget *w = this->parentWidget();
    if (w && qobject_cast<QMdiSubWindow *>(w)){

      QRect r = w->layout()->contentsRect();         
      int hh =  w->height() - r.height();

      w->setMinimumSize(w->size().width(), size().height() + hh);

    } else {
      setMinimumSize(size());
    }
  } 

  if (GETPROPERTY_ResizableSmaller() == true){

    QWidget *w = this->parentWidget();
    if (w && qobject_cast<QMdiSubWindow *>(w)){

      QRect r = w->layout()->contentsRect();         
      int hh =  w->height() - r.height();

      w->setMaximumSize(w->size().width(), size().height() + hh);
    } else {
      setMaximumSize(size());
    }
  } 

  if (!sShowMode.isEmpty() && sShowMode.contains("Normal", Qt::CaseInsensitive) == false){
    if (sShowMode.contains("Maximized", Qt::CaseInsensitive)){
      if (!bHidden && !bGETPROPERTY_Visible) showMaximized();
    } else if (sShowMode.contains("Minimized", Qt::CaseInsensitive)){
      if (!bHidden && !bGETPROPERTY_Visible) showMinimized();
    } else if (sShowMode.contains("Normal", Qt::CaseInsensitive)){
      if (!bHidden && !bGETPROPERTY_Visible) show();
    } else if (sShowMode.contains("Centered", Qt::CaseInsensitive)){

      if (forms_workspace && parentWidget() && (qobject_cast<QMdiSubWindow *>(parentWidget()))){
        QWidget *w = parentWidget()->parentWidget();
        QWidget *ww = parentWidget();
        ww->setGeometry(w->width() / 2 - ww->width() / 2, w->height() / 2 - ww->height() / 2, ww->width(), ww->height());
        if (!bHidden && !bGETPROPERTY_Visible) show();
      } else {
        setGeometry(QApplication::desktop()->width() / 2 - width() / 2, QApplication::desktop()->height() / 2 - height() / 2, width(), height());
        if (!bHidden && !bGETPROPERTY_Visible) show();
      }
      
    } else if (sShowMode.contains("FullScreen", Qt::CaseInsensitive)){
      if (!bHidden && !bGETPROPERTY_Visible){
        show(); // needed to have working fullscreen
        METHOD_ShowFullScreen();
      }
    }
  }


  // do the context menus of buttons etc.
  QMapIterator<QWidget*, QString> i(menusForButtons);
  while (i.hasNext()){
    i.next();

    _qmenu *my_qmenu = 0;

    _menubaritem *c;

    if (EXTERN_my_menubar->firstControl(&c)){
     
      do {

        if (c->GETPROPERTY_Name().compare(i.value(), Qt::CaseInsensitive) == 0){
          my_qmenu = c->my_qmenu;
          break;
        }

      } while (EXTERN_my_menubar->nextControl(&c)); 
    }

    if (my_qmenu != 0){
      QPushButton *o = qobject_cast<QPushButton *>(i.key());
      if (o){
        o->setMenu(my_qmenu);
      }
    }
  }

  EVENT_OnOpen();


  bMETHOD_Open_Opened = true;

  bDialogRunning = true;
  if (bDialog && bDialogRunning){
    bBlockOnceOpenModal = true;
    while(EXTERN_myInterpreter->bNoError && EXTERN_myInterpreter->bRunPcode && bDialogRunning){
      qApp->processEvents(QEventLoop::WaitForMoreEvents);
    }
  }
  //bDialogRunning = false;


#endif
}
#endif

#ifdef RUN
t_long _form::METHOD_Pos()
{ 
  if (!CurrentDatabase.isOpen()) return 0;
  if (!bTableView){
    return q.at() + 1;
  } else {
     int n = sqlv->horizontalHeader()->currentIndex().row();
     if (n >= 0) n++;
     return n;
    /*
    QModelIndexList l = sqlv->horizontalHeader()->selectionModel()->selectedColumns();
    int n = l.first().column();
    return n;*/

  }
  return 0;
}
#endif

#ifdef RUN
t_boolean _form::METHOD_IsDirty()
{ 
  if (!CurrentDatabase.isOpen()) return false;
  if (!bTableView){
    return bDirty;
  } else {
    QHeaderView *m = sqlv->horizontalHeader();
    int y = m->currentIndex().row();
    int xmax = sqlm.columnCount(m->currentIndex());

    for (int x = 0; x < xmax; x++){
      if (sqlm.isDirty(sqlm.index(y, x))) return true;
    }
  }
  return false;
}
#endif

#ifdef RUN
 

t_variant _form::METHOD_Read(QString SearchFor, QString InTableDotField, QString ReturnFieldName)
{
  //t_variant v;
  if (!CurrentDatabase.isOpen()) return t_variant(&kbNullQString);
  QString sTable = "";
  QString sField = "";
  if (InTableDotField != "*" && !InTableDotField.contains(".")){    
    return t_variant(&kbNullQString);
  }

  int n = InTableDotField.indexOf(".");
  sTable = InTableDotField.left(n);
  sField = InTableDotField.mid(n + 1);

  QString sWhere = " WHERE ";
  sWhere += "(" + sField + " = ";
  sWhere += SearchFor;
  sWhere += ")";


  static QSqlQuery rr; rr = QSqlQuery(CurrentDatabase);
  QString s = "SELECT * FROM " + sTable + sWhere;
  if (InTableDotField == "*") goto r; // use cache, speed up
  if (rr.exec(s)){
    //my_log->METHOD_PrintSql(s);
   // addLog(s);

r:
    if (rr.first()){
      QSqlRecord r = rr.record();
      int nn = r.indexOf(ReturnFieldName);

      QVariant f = rr.value(nn);

      switch(f.type()){
        case QVariant::Bool:
          return t_variant(f.toBool());
          break;
        case QVariant::Date: 
          return t_variant(&f.toString());
          break;
        case QVariant::Time: 
          return t_variant(&f.toString());
          break;
        case QVariant::Double:
          return t_variant(f.toDouble());
          break;
        case QVariant::UInt:
        case QVariant::ULongLong:
        case QVariant::LongLong:
        case QVariant::Int:
          return t_variant(f.toInt());
          break;
        case QVariant::String: 
          return t_variant(&f.toString());
          break;
        default:
          return t_variant(&f.toString());
          break;
      }
    }
  }      

  return t_variant(&kbNullQString);
}

QString _form::METHOD_PrimaryKeyName()
{
  QString sKBRecordId = getPrimary(this->GETPROPERTY_SQLName());
  return sKBRecordId;
}

t_integer _form::METHOD_PrimaryKey()
{
  return METHOD_kbrecordid(getPrimary(this->GETPROPERTY_SQLName()));
}

t_integer _form::METHOD_kbrecordid(QString sFieldName)
{
  if (!CurrentDatabase.isOpen()) return 0;
  if (!bTableView){
    QSqlRecord r = q.record();
    int n = r.indexOf(sFieldName);
    qulonglong kbrecordid = q.value(n).toLongLong();
    return kbrecordid;
  } else {
    QHeaderView *hh = sqlv->horizontalHeader();

    int n = 0;
    QSqlRecord r = sqlm.record();
    for (; n < r.count(); n++){
      if (r.fieldName(n) == sFieldName){
        n = hh->visualIndex(n);
        break;
      }
    }
    QVariant v = sqlm.data(sqlm.index(hh->currentIndex().row(), n), Qt::EditRole);
    return v.toInt();
  }
  
  return 0;
}

QString _form::METHOD_PrimaryKeyName2(QString ChildControl)
{
  if (!CurrentDatabase.isOpen()) return 0;
  if (ChildControl.isEmpty()){
    QObjectList it = children(); // iterate over the children
    _form *o;
    for (int q = 0; q < it.size(); q++){
      o = qobject_cast<_form *>(it.at(q));
      if (o){
        return o->METHOD_PrimaryKeyName();
      }
    }
  } else {
    QObjectList it = children(); // iterate over the children
    _form *o;
    for (int q = 0; q < it.size(); q++){
      o = qobject_cast<_form *>(it.at(q));
      if (o && o->GETPROPERTY_Name() == ChildControl){
        return o->METHOD_PrimaryKeyName();
      }
    }
  }

  return "kbrecordid";
}

t_integer _form::METHOD_PrimaryKey2(QString ChildControl)
{
  if (!CurrentDatabase.isOpen()) return 0;
  if (ChildControl.isEmpty()){
    QObjectList it = children(); // iterate over the children
    _form *o;
    for (int q = 0; q < it.size(); q++){
      o = qobject_cast<_form *>(it.at(q));
      if (o){
        return o->METHOD_PrimaryKey();
      }
    }
  } else {
    QObjectList it = children(); // iterate over the children
    _form *o;
    for (int q = 0; q < it.size(); q++){
      o = qobject_cast<_form *>(it.at(q));
      if (o && o->GETPROPERTY_Name() == ChildControl){
        return o->METHOD_PrimaryKey();
      }
    }
  }

  return 0;
}

t_integer _form::METHOD_kbrecordid2(QString ChildControl)
{
  if (!CurrentDatabase.isOpen()) return 0;
  if (ChildControl.isEmpty()){
    QObjectList it = children(); // iterate over the children
    _form *o;
    for (int q = 0; q < it.size(); q++){
      o = qobject_cast<_form *>(it.at(q));
      if (o){
        return o->METHOD_kbrecordid();
      }
    }
  } else {
    QObjectList it = children(); // iterate over the children
    _form *o;
    for (int q = 0; q < it.size(); q++){
      o = qobject_cast<_form *>(it.at(q));
      if (o && o->GETPROPERTY_Name() == ChildControl){
        return o->METHOD_kbrecordid();
      }
    }
  }

  return 0;
}

t_variant _form::METHOD_Get(QString SQL)
{
  //t_variant v;
  const char *ac = "";
  if (!CurrentDatabase.isOpen()) return t_variant(&kbNullQString);
  QString sTable = "";
  QString sField = "";


  static QSqlQuery rr; rr = QSqlQuery(CurrentDatabase);
  if (rr.exec(SQL)){
    //my_log->METHOD_PrintSql(SQL);
   // addLog(SQL);

    if (rr.first()){
      QSqlRecord r = rr.record();

      QVariant f = rr.value(0);
      int n = f.type();

      switch(f.type()){
        case QVariant::Bool:
          return t_variant(f.toBool());
          break;
        case QVariant::Date: 
          return t_variant(&f.toString());
          break;
        case QVariant::Time: 
          return t_variant(&f.toString());
          break;
        case QVariant::Double:
          return t_variant(f.toDouble());
          break;
        case QVariant::UInt:
        case QVariant::ULongLong:
        case QVariant::LongLong:
        case QVariant::Int:
          return t_variant(f.toInt());
          break;
        case QVariant::String: 
          return t_variant(&f.toString());
          break;
        default:
          return t_variant(&f.toString());
          break;
      }
    }
  }      

  return t_variant(&kbNullQString);
}

t_boolean _form::METHOD_Seek(QString Filter1, QString Filter2, QString Filter3, QString Filter4, QString Filter5, QString Filter6)
{
  if (!CurrentDatabase.isOpen()) return false;
  if (this->GETPROPERTY_SQLName().isEmpty()) return false;

  QString cn = "";

  if (Filter1 == ""){

    if (!bTableView){
      if (ControlFocusPrevious == 0){
        //QMessageBox::information(this, MYAPP, tr("You have to click on (select) a control first, before the seek dialog is shown."));
        return false;
      }
      cn = ControlFocusPrevious->objectName();
    } else {
      QHeaderView *hh = sqlv->horizontalHeader();
      int n = hh->logicalIndex(nTableViewCurrentX);
      QSqlRecord r = sqlm.record();
      cn = r.fieldName(n);
    }


    if (!bTableView){
      bool b = true;
      QWidget *c = 0;
      if (firstControl(&c)){
        do {
          if (c->objectName() == cn){
            b = false;
            
            QString ss = "";
            #define SWITCH GETPROPERTY_SQLName();      
            #define SWITCH3 ss
            #include "_form_property_switch.h"   
            #undef SWITCH3

            if (ss.isEmpty()) return false;

            bool bb;
            Filter1 = QInputDialog::getText(this, tr("Seek in ") + ss, tr("Enter the text you would like to find:"), QLineEdit::Normal, QString::null, &bb);
            if (!(bb && !Filter1.isEmpty())) return false;
            Filter1 = ss + " = '" + Filter1 + "'";

            break;
          }
        } while (nextControl(&c)); 
      }    
      if (b){
        //QMessageBox::information(this, MYAPP, tr("You have to click on (select) a control first, before the seek dialog is shown."));
        return false;
      }
    } else {

      bool bb;
      Filter1 = QInputDialog::getText(this, tr("Seek"), tr("Enter the text you would like to find:"), QLineEdit::Normal, QString::null, &bb);
      if (!(bb && !Filter1.isEmpty())) return false;
      Filter1 = cn + " = '" + Filter1 + "'";

    }
  }  

  QString sTable = getSQLTableName();
  QString sWhere = " WHERE ";
  sWhere += "(";
  sWhere += Filter1;
  sWhere += ")";

  if (!Filter2.isEmpty()){
    sWhere += " AND (";
    sWhere += Filter2;
    sWhere += ")";
  }

  if (!Filter3.isEmpty()){
    sWhere += " AND (";
    sWhere += Filter3;
    sWhere += ")";
  }

  if (!Filter4.isEmpty()){
    sWhere += " AND (";
    sWhere += Filter4;
    sWhere += ")";
  }

  if (!Filter5.isEmpty()){
    sWhere += " AND (";
    sWhere += Filter5;
    sWhere += ")";
  }

  if (!Filter6.isEmpty()){
    sWhere += " AND (";
    sWhere += Filter6;
    sWhere += ")";
  }

  QString sKBRecordId = getPrimary(this->GETPROPERTY_SQLName());

  QSqlQuery rr(CurrentDatabase);
  QString s = "SELECT " + sKBRecordId + " FROM " + sTable + sWhere + " ORDER BY " + sKBRecordId + " desc";
  if (rr.exec(s)){
    //my_log->METHOD_PrintSql(s);
   // addLog(s);

    if (rr.first()){
      QSqlRecord r = rr.record();
      int n = r.indexOf(sKBRecordId);
      qulonglong kbrecordid = rr.value(n).toLongLong();

      if (!bTableView){
        int nPos = q.at();

        if (q.first()){
          do {
            QSqlRecord a = q.record();
            int n = a.indexOf(sKBRecordId);

            if (n >= 0){
              QVariant v = a.value(n);
              int mm = v.toLongLong();
              if (v.toLongLong() == kbrecordid){
                METHOD_GoTo(q.at() + 1, false);
                return true;
              }                
            }
          } while (q.next());
          q.seek(nPos);
        }
      } else {

        QHeaderView *hh = sqlv->horizontalHeader();

        QSqlRecord r = sqlm.record();
        sName = r.fieldName(n);
        for (int n = 0; n < r.count(); n++){
          if (r.fieldName(n) == sKBRecordId){
            n = hh->visualIndex(n);
            break;
          }
        }

        for (int i = 0; i < sqlm.rowCount(); i++){
          QVariant v = sqlm.data(sqlm.index(i, n), Qt::EditRole);
          if (v.toLongLong() == kbrecordid){
             METHOD_GoTo(i + 1, false);
             return true;
          }                
        }


        /*
        int nPos = sqlm.at();

        if (sqlm.first()){
          do {
            QSqlRecord a = sqlm.record();
            int n = a.indexOf(sKBRecordId);
            if (n >= 0){
              QVariant v = a.value(n);
              if (v.toLongLong() == kbrecordid){
                METHOD_GoTo(sqlm.at() + 1, false);
                return true;
              }                
            }
          } while (sqlm.next());
          sqlm.seek(nPos);
        }
        */
      }
      
    }
  }      

  return false;
}

void _form::setSQL2(QSqlRecord  a)
{
#ifdef RUN

  QWidget *c;
  if (firstControl(&c)){
     do {

       QString sControlName = c->objectName();     
       /*
       #define SWITCH GETPROPERTY_Name();      
       #define SWITCH3 sControlName
       #include "_form_property_switch.h"   
       #undef SWITCH3*/

       QString sSQLName = "";                    
       #define SWITCH GETPROPERTY_SQLName();      
       #define SWITCH3 sSQLName
       #include "_form_property_switch.h"   
       #undef SWITCH3

       QString sSQLRelation = "";                    
       #define SWITCH GETPROPERTY_SQLRelation();      
       #define SWITCH3 sSQLRelation
       #include "_form_property_switch.h"   
       #undef SWITCH3

       if (!sSQLName.isEmpty()){
          int n = a.indexOf(sSQLName);
          QVariant v;
          if (n >= 0) v = a.value(n);

            int type = v.type();

            QString sControlType = "";
            #define SWITCH GETPROPERTY_ControlType();      
            #define SWITCH3 sControlType
            #include "_form_property_switch.h"   
            #undef SWITCH3

            if (sControlType == "Label") ((_label *) c)->SETPROPERTY_Caption(v.toString());
            else if (sControlType == "Sound"){
              QString k = v.toString();
              k = k.replace("ZERO_kbasic", QChar(0));
              k = k.replace("BACKSLASH_kbasic", QChar('\\'));
              k = k.replace("SINGLEQUOTE_kbasic", QChar('\''));

              k = k.replace("x00_kbasic", QChar('\x00'));
              k = k.replace("x1a_kbasic", QChar('\x1a'));

              k = k.replace("n_kbasic", QChar('\n'));
              k = k.replace("t_kbasic", QChar('\t'));
              k = k.replace("f_kbasic", QChar('\f'));
              k = k.replace("r_kbasic", QChar('\r'));
              k = k.replace("v_kbasic", QChar('\v'));


              ((_sound *) c)->SETPROPERTY_StringValue(k);
            } else if (sControlType == "MovieBox"){
              QString k = v.toString();
              k = k.replace("ZERO_kbasic", QChar(0));
              k = k.replace("BACKSLASH_kbasic", QChar('\\'));
              k = k.replace("SINGLEQUOTE_kbasic", QChar('\''));

              k = k.replace("x00_kbasic", QChar('\x00'));
              k = k.replace("x1a_kbasic", QChar('\x1a'));

              k = k.replace("n_kbasic", QChar('\n'));
              k = k.replace("t_kbasic", QChar('\t'));
              k = k.replace("f_kbasic", QChar('\f'));
              k = k.replace("r_kbasic", QChar('\r'));
              k = k.replace("v_kbasic", QChar('\v'));
              ((_movie *) c)->SETPROPERTY_StringValue(k);
            } else if (sControlType == "ImageBox"){
              QString k = v.toString();
              k = k.replace("ZERO_kbasic", QChar(0));
              k = k.replace("BACKSLASH_kbasic", QChar('\\'));
              k = k.replace("SINGLEQUOTE_kbasic", QChar('\''));

              k = k.replace("x00_kbasic", QChar('\x00'));
              k = k.replace("x1a_kbasic", QChar('\x1a'));

              k = k.replace("n_kbasic", QChar('\n'));
              k = k.replace("t_kbasic", QChar('\t'));
              k = k.replace("f_kbasic", QChar('\f'));
              k = k.replace("r_kbasic", QChar('\r'));
              k = k.replace("v_kbasic", QChar('\v'));
              ((_image *) c)->SETPROPERTY_StringValue(k);
            } else if (sControlType == "HtmlView"){
              QString k = v.toString();
              k = k.replace("ZERO_kbasic", QChar(0));
              k = k.replace("BACKSLASH_kbasic", QChar('\\'));
              k = k.replace("SINGLEQUOTE_kbasic", QChar('\''));

              k = k.replace("x00_kbasic", QChar('\x00'));
              k = k.replace("x1a_kbasic", QChar('\x1a'));

              k = k.replace("n_kbasic", QChar('\n'));
              k = k.replace("t_kbasic", QChar('\t'));
              k = k.replace("f_kbasic", QChar('\f'));
              k = k.replace("r_kbasic", QChar('\r'));
              k = k.replace("v_kbasic", QChar('\v'));
              ((_browser *) c)->SETPROPERTY_StringValue(k);
            } else if (sControlType == "WebView"){
              QString k = v.toString();
              k = k.replace("ZERO_kbasic", QChar(0));
              k = k.replace("BACKSLASH_kbasic", QChar('\\'));
              k = k.replace("SINGLEQUOTE_kbasic", QChar('\''));

              k = k.replace("x00_kbasic", QChar('\x00'));
              k = k.replace("x1a_kbasic", QChar('\x1a'));

              k = k.replace("n_kbasic", QChar('\n'));
              k = k.replace("t_kbasic", QChar('\t'));
              k = k.replace("f_kbasic", QChar('\f'));
              k = k.replace("r_kbasic", QChar('\r'));
              k = k.replace("v_kbasic", QChar('\v'));
              ((_web *) c)->SETPROPERTY_StringValue(k);

            } else if (sControlType == "RichTextBox"){
              QString k = v.toString();
              k = k.replace("ZERO_kbasic", QChar(0));
              k = k.replace("BACKSLASH_kbasic", QChar('\\'));
              k = k.replace("SINGLEQUOTE_kbasic", QChar('\''));

              k = k.replace("x00_kbasic", QChar('\x00'));
              k = k.replace("x1a_kbasic", QChar('\x1a'));

              k = k.replace("n_kbasic", QChar('\n'));
              k = k.replace("t_kbasic", QChar('\t'));
              k = k.replace("f_kbasic", QChar('\f'));
              k = k.replace("r_kbasic", QChar('\r'));
              k = k.replace("v_kbasic", QChar('\v'));
              ((_editor *) c)->SETPROPERTY_StringValue(k);
            }
            else if (sControlType == "TextBox") ((_textbox *) c)->SETPROPERTY_StringValue(v.toString());
            else if (sControlType == "ComboBox"){
              if (!sSQLRelation.isEmpty()){

                QString sKBRecordId = "kbrecordid";
                int g = sSQLRelation.indexOf(" FROM ", Qt::CaseInsensitive);
                if (g >= 0){
                  g += 6;
                  int g2 = sSQLRelation.indexOf(" ", g, Qt::CaseInsensitive);
                  if (g2 >= 0){
                    sKBRecordId = getPrimary(sSQLRelation.mid(g, g2 - g));
                  }
                }
                  
                if (!sSQLRelation.contains(sKBRecordId, Qt::CaseInsensitive)){
                  int k = sSQLRelation.indexOf("SELECT ", Qt::CaseInsensitive);
                  if (k >= 0){
                    k += 7;
                    sSQLRelation = sSQLRelation.insert(k, sKBRecordId + ", ");
                  }
                }

                if (((_combobox *) c)->count() == 0){

                  QSqlQuery rr(CurrentDatabase);
                  QString s = sSQLRelation;
                  if (rr.exec(s)){
                    //my_log->METHOD_PrintSql(s);
                   // addLog(s);
                    if (rr.first()){
                      ((_combobox *) c)->addItem("", QVariant(0));

                      do {
                        QString ss = "";
                      QSqlRecord r = rr.record();
                      for (int i = 0; i < r.count() - 1; i++){
                        ss += rr.value(i + 1).toString();
                        ss += " | ";
                      }

                      qulonglong kbrecordid = rr.value(0).toLongLong();

                      ((_combobox *) c)->addItem(ss, QVariant(kbrecordid));
                    } while (rr.next());
                  }
                }
              }
              int n = ((_combobox *) c)->findData(v);
              if (n >= 0) ((_combobox *) c)->setCurrentIndex(n); else ((_combobox *) c)->setCurrentIndex(0);
            } else {
              ((_combobox *) c)->METHOD_Select(v.toString());            
            }
          }
          else if (sControlType == "ListBox"){
            if (!sSQLRelation.isEmpty()){

              QString sKBRecordId = "kbrecordid";
              int g = sSQLRelation.indexOf(" FROM ", Qt::CaseInsensitive);
              if (g >= 0){
                g += 6;
                int g2 = sSQLRelation.indexOf(" ", g, Qt::CaseInsensitive);
                if (g2 >= 0){
                  sKBRecordId = getPrimary(sSQLRelation.mid(g, g2 - g));
                }
              }

              if (!sSQLRelation.contains(sKBRecordId, Qt::CaseInsensitive)){

                int k = sSQLRelation.indexOf("SELECT ", Qt::CaseInsensitive);
                if (k >= 0){
                  k += 7;
                  sSQLRelation = sSQLRelation.insert(k, sKBRecordId + ", ");
                }
              }

              if (((_listbox *) c)->count() == 0){

                QSqlQuery rr(CurrentDatabase);
                QString s = sSQLRelation;
                if (rr.exec(s)){
                  //my_log->METHOD_PrintSql(s);
                 // addLog(s);
                  if (rr.first()){
                    QListWidgetItem *it = new QListWidgetItem();
                    it->setText(""); it->setData(Qt::UserRole, QVariant(0));
                    ((_listbox *) c)->addItem(it);

                    do {
                      QString ss = "";
                      QSqlRecord r = rr.record();
                      for (int i = 0; i < r.count() - 1; i++){
                        ss += rr.value(i + 1).toString();
                        ss += " | ";
                      }

                      qulonglong kbrecordid = rr.value(0).toLongLong();

                      QListWidgetItem *it = new QListWidgetItem();
                      it->setText(ss); it->setData(Qt::UserRole, QVariant(kbrecordid));
                      ((_listbox *) c)->addItem(it);

                    } while (rr.next());
                  }
                }
              }
              bool b = true;
              for (int i = 0; i < ((_listbox *) c)->count(); i++){
                QListWidgetItem *it = ((_listbox *) c)->item(i);
                if (it->data(Qt::UserRole) == v){
                  ((_listbox *) c)->setCurrentRow(i); 
                  b = false;
                  break;
                }
              }
              if (b) ((_listbox *) c)->setCurrentRow(0);                
              
            } else {
              ((_listbox *) c)->METHOD_Select(v.toString());            
            }
          }
          else if (sControlType == "CheckBox") ((_checkbox *) c)->SETPROPERTY_BooleanValue(v.toBool());
          else if (sControlType == "DateBox"){

            if (v.type() == QVariant::Date){
              QDate s = v.toDate();
              if (s.isNull()){                
                ((_datebox *) c)->setDate(QDate(/*1979, 1, 1*/));                 
                //((_datebox *) c)->setCurrentSection(QDateTimeEdit::DaySection); ((_datebox *) c)->clear();
                //((_datebox *) c)->setCurrentSection(QDateTimeEdit::MonthSection); ((_datebox *) c)->clear();
                ((_datebox *) c)->setCurrentSection(QDateTimeEdit::YearSection); ((_datebox *) c)->clear();
                  
              } else {
                ((_datebox *) c)->SETPROPERTY_StringValue(s.toString("yyyy-MM-dd"));
              }
            } else {
              QString s = v.toString();
              ((_datebox *) c)->SETPROPERTY_StringValue(s);
            }
          }
          else if (sControlType == "TimeBox"){
            if (v.type() == QVariant::Time){
              QTime s = v.toTime();
              if (s.isNull()){                
                ((_timebox *) c)->setTime(QTime(/*1979, 1, 1*/));                 
                ((_timebox *) c)->setCurrentSection(QDateTimeEdit::HourSection); ((_timebox *) c)->clear();
                  
              } else {
                ((_timebox *) c)->SETPROPERTY_StringValue(s.toString("hh:mm:ss"));
              }
                  
            } else {
              QString s = v.toString();
              ((_timebox *) c)->SETPROPERTY_StringValue(s);
            }
          }
          //else if (sControlType == "DateTimeBox") ((_datetimebox *) c)->SETPROPERTY_StringValue(v.toString());
          //else if (sControlType == "RichTextBox") ((_editor *) c)->SETPROPERTY_StringValue(v.toString());

          
       }

     } while (nextControl(&c));
  }
  
#endif
}

QString _form::getSQLTableName()
{
  QString s = GETPROPERTY_SQLName();   
  if (s.contains(" ")){
    int n = s.indexOf(" FROM ");
    if (n >= 0){
      s = s.mid(n + 6);
      s = s.simplified();
      n = s.indexOf(" ");
      if (n >= 0) s = s.left(n);
    }
  }
  return s;
}
 
QString _form::getSQLFilter()
{
  QString s = GETPROPERTY_SQLName();   
  if (s.contains(" ")){
    int n = s.indexOf(" WHERE ");
    if (n >= 0){
      s = s.mid(n + 7);
      s = s.simplified();
      if (s.contains(" GROUP BY ", Qt::CaseInsensitive)){
        s = s.left(s.indexOf(" GROUP BY ", Qt::CaseInsensitive));
      } else {
        if (s.contains(" ORDER BY ", Qt::CaseInsensitive)){
          s = s.left(s.indexOf(" ORDER BY ", Qt::CaseInsensitive));
        }
      }
      return s;
    }
  }
  return "";
}

QStringList _form::getSQLSort()
{
  QString s = GETPROPERTY_SQLName();   
  if (s.contains(" ")){
    int n = s.indexOf(" ORDER BY ");
    if (n >= 0){
      s = s.mid(n + 10);
      s = s.simplified();
      s = s.replace(" ,", ",");
      s = s.replace(", ", ",");
      if (s.contains(",")) return s.split(",");
      return QStringList(s);
    }
  }
  return QStringList();
}

QStringList _form::getSQLFields()
{
  QString s = GETPROPERTY_SQLName();   
  if (s.contains(" ")){
    int n = s.indexOf("SELECT ", 0);
    if (n >= 0){
      s = s.mid(n + 7);
      int n = s.indexOf(" FROM ");
      if (n >= 0){
        s = s.left(s.indexOf(" FROM ", Qt::CaseInsensitive));
        s = s.simplified();
        s = s.replace(" ,", ",");
        s = s.replace(", ", ",");
        if (s.contains(",")) return s.split(",");
        return QStringList(s);
      }
    }
  }
  return QStringList();
}


void _form::setDirty(bool _bDirty)
{
  if (!bTableView && bLoading) return;

  bool b = bDirty;
  bDirty = _bDirty;

  if (!bTableView && bDirty && !b){
    EVENT_OnDirty();
  }

  QWidget *c;
  if (firstControl(&c, 60)){
     do {

       QString sControlName = c->objectName();    

       
       if (!bTableView){
        if (sControlName == "SQLUpdate"){

          QString sParentForm = "";    
           
          #define SWITCH GETPROPERTY_ParentForm();      
          #define SWITCH3 sParentForm
          #include "_form_property_switch.h"   

          if (sParentForm == this->GETPROPERTY_ParentForm()){
            ((_commandbutton *) c)->SETPROPERTY_Enabled(bDirty);                 
            break;
          }
        }
       } else {

        if (sControlName == "SQLUpdate"){


          QString sParentForm = "";    
           
          #define SWITCH GETPROPERTY_ParentForm();      
          #define SWITCH3 sParentForm
          #include "_form_property_switch.h"   

          if (sParentForm == this->GETPROPERTY_ParentForm()){
            ((_commandbutton *) c)->SETPROPERTY_Visible(false);                 
          }
        }
        if (sControlName == "SQLAddNew"){

          QString sParentForm = "";    
           
          #define SWITCH GETPROPERTY_ParentForm();      
          #define SWITCH3 sParentForm
          #include "_form_property_switch.h"   

          if (sParentForm == this->GETPROPERTY_ParentForm()){
            ((_commandbutton *) c)->SETPROPERTY_Visible(false);                 
          }
        }

       }
       

     } while (nextControl(&c, 60));
  }
  
}

void _form::setAddNew(bool _bAddNew)
{
  bAddNew = _bAddNew;


  QWidget *c;
  if (firstControl(&c, 60)){
     do {

       QString sControlName = c->objectName();    
       /*
       #define SWITCH GETPROPERTY_Name();      
       #define SWITCH3 sControlName
       #include "_form_property_switch.h"   */
       
       if (sControlName == "SQLAddNew"){
         ((_commandbutton *) c)->SETPROPERTY_Enabled(!bAddNew);                 
         break;
       }

     } while (nextControl(&c, 60));
  }
  
}

void _form::addProtocol(QString s)
{

  QWidget *c;
  if (firstControl(&c, 60)){
     do {

       QString sControlName = c->objectName();    
/*
       #define SWITCH GETPROPERTY_Name();      
       #define SWITCH3 sControlName
       #include "_form_property_switch.h"   */
       
       if (sControlName == "SQLProtocol"){
         ((_label *) c)->SETPROPERTY_Caption(s);                 
         break;
       }

     } while (nextControl(&c, 60));
  }
  
}

void _form::addLog(QString s)
{

  QWidget *c;
  if (firstControl(&c, 60)){
     do {

       QString sControlName = c->objectName();    
/*
       #define SWITCH GETPROPERTY_Name();      
       #define SWITCH3 sControlName
       #include "_form_property_switch.h"   */
       
       if (sControlName == "SQLLog"){
         QString ss = ((_browser *) c)->GETPROPERTY_StringValue(); 
         ((_browser *) c)->SETPROPERTY_StringValue(ss + s + "\n\n");                 
         break;
       }

     } while (nextControl(&c, 60));
  }
  
}

t_boolean _form::METHOD_Requery()
{ 
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return false;
  if (this->GETPROPERTY_SQLName().isEmpty()) return false;

  if (!bTableView){
    if (stopByQuestion()) return false;
    EVENT_OnQuery();
    nQuerySize = 0;
    QString k = q.lastQuery();
    if (q.exec(k)){
     //my_log->METHOD_PrintSql(k);
     setQuerySize();
     // addProtocol(tr("Refreshed query"));
     // addLog(q.lastQuery());
      bool b = METHOD_First(false);
      bDirty = false;
      return b;
    } else QMessageBox::information(this, MYAPP, q.lastError().text());
  } else {
    //if (stopByQuestion()) return false;
    EVENT_OnQuery();
    METHOD_Open(false, true);
    //sqlm.clear();
    //bool b = sqlm.select();
   // addProtocol(tr("Refreshed query"));
   // addLog(sqlm.query().executedQuery());
   // if (b) b = METHOD_First(false);    
    sqlv->setFocus();
    //if (b) 
    bool b = METHOD_First(false);
    return b;
  }
#endif
  return false;
}

void _form::METHOD_ClearFilter()
{  
  if (!CurrentDatabase.isOpen()) return;
  if (this->GETPROPERTY_SQLName().isEmpty()) return;

  if (!bTableView){
    if (stopByQuestion()) return;
    QString s = q.executedQuery();
    QString SAVE = s;
    QString s2 = "";
    QString s3 = q.executedQuery();
    QString s4 = "";
    if (s.contains(" WHERE ", Qt::CaseInsensitive)){      
      if (s.contains(" GROUP BY ", Qt::CaseInsensitive)){
        s2 = s.mid(s.indexOf(" GROUP BY ", Qt::CaseInsensitive));
      } else {
        if (s.contains(" ORDER BY ", Qt::CaseInsensitive)){
          s2 = s.mid(s.indexOf(" ORDER BY ", Qt::CaseInsensitive));
        }
      }
      s = s.left(s.indexOf(" WHERE ", Qt::CaseInsensitive));
    } else {
      if (s.contains(" GROUP BY ", Qt::CaseInsensitive)){
        s2 = s.mid(s.indexOf(" GROUP BY ", Qt::CaseInsensitive));
        s = s.left(s.indexOf(" GROUP BY ", Qt::CaseInsensitive));
      } else {
        if (s.contains(" ORDER BY ", Qt::CaseInsensitive)){
          s2 = s.mid(s.indexOf(" ORDER BY ", Qt::CaseInsensitive));
          s = s.left(s.indexOf(" ORDER BY ", Qt::CaseInsensitive));
        }
      }
    }

    if (s3.contains(" WHERE ", Qt::CaseInsensitive)){      
      s3 = s3.mid(s3.indexOf(" WHERE ", Qt::CaseInsensitive) + 7);
      if (s3.contains(" GROUP BY ", Qt::CaseInsensitive)){
        s4 = s3.left(s3.indexOf(" GROUP BY ", Qt::CaseInsensitive));
      } else {
        if (s3.contains(" ORDER BY ", Qt::CaseInsensitive)){
          s4 = s3.left(s3.indexOf(" ORDER BY ", Qt::CaseInsensitive));
        }
      }
    }
    if (!s4.isEmpty()) s += " WHERE ";
    if (!s4.isEmpty()) s+= "(";
    s += s4;
    if (!s4.isEmpty()) s+= ")";
    s += s2;
    EVENT_OnQuery();
    nQuerySize = 0;
    if (q.exec(s)){    
     //my_log->METHOD_PrintSql(s);
     setQuerySize();
     // addProtocol(tr("Refreshed query with no custom filter "));
     // addLog(s);
      bIsFilterActive = false;
      bool b = METHOD_First(false);
      setAddNew(false);
      setDirty(false);      
      return;
    } else {
      QMessageBox::information(this, MYAPP, q.lastError().text());

      nQuerySize = 0;
      if (q.exec(SAVE)){ // at least this sql statement will work
        //my_log->METHOD_PrintSql(SAVE);
       setQuerySize();
       // addProtocol(tr("Requeried, because new SQL statement failed"));
       // addLog(SAVE);
        bool b = METHOD_First(false);
        setAddNew(false);
        setDirty(false);
        return;
      }
    }
  } else {

    sqlm.setFilter(sTableFilter);
    if (!sqlm.select()){
      QSqlError e = sqlm.lastError();
      QMessageBox::information(0, tr("Error in = ") + sTableFilter,  e.text());  
      return;
    }
    bIsFilterActive = false;
    METHOD_First();

   // bool b = sqlm.select();
   // sqlv->setFocus();
    return;
  }
}

void _form::METHOD_SetFilter(QString ss)
{
  if (!CurrentDatabase.isOpen()) return;
  if (this->GETPROPERTY_SQLName().isEmpty()) return;

  METHOD_AddFilter(ss, false);
}

void _form::METHOD_AddFilter(QString ss, bool bAddFilter)
{
  if (!CurrentDatabase.isOpen()) return;
  if (this->GETPROPERTY_SQLName().isEmpty()) return;

  QString sOperator = "=";
  if (ss == "=" || ss == "<>" || ss == "<" || ss == ">"){
    sOperator = ss;
    ss = "";
    goto r;
  }
  if (ss == ""){
r:
    if (!bTableView){
      if (ControlFocusPrevious == 0) return;

      QString cn = ControlFocusPrevious->objectName();

      bool b = true;
      QWidget *c = 0;
      if (firstControl(&c)){
        do {
          if (c->objectName() == cn){

            #define SWITCH GETPROPERTY_SQLName();      
            #define SWITCH3 ss
            #include "_form_property_switch.h"   
            #undef SWITCH3
            
            if (ss.isEmpty()) return;

            QString sControlType = c->property("__kb1979.ControlType.kb__").toString();
            QString sss = "";

            if (sControlType == "TextBox"){

              #define SWITCH GETPROPERTY_StringValue();      
              #define SWITCH3 sss
              #include "_form_property_switch.h"   
              #undef SWITCH3         

            } else if (sControlType == "CheckBox"){

              #define SWITCH GETPROPERTY_BooleanValue();      
              #define SWITCH3 sss
              #include "_form_property_switch.h"   
              #undef SWITCH3

            } else if (sControlType == "ComboBox"){

              #define SWITCH GETPROPERTY_StringValue();      
              #define SWITCH3 sss
              #include "_form_property_switch.h"   
              #undef SWITCH3

            } else if (sControlType == "ListBox"){

              #define SWITCH GETPROPERTY_StringValue();      
              #define SWITCH3 sss
              #include "_form_property_switch.h"   
              #undef SWITCH3

            } else if (sControlType == "DateBox"){

              #define SWITCH GETPROPERTY_StringValue();      
              #define SWITCH3 sss
              #include "_form_property_switch.h"   
              #undef SWITCH3

            } else if (sControlType == "TimeBox"){

              #define SWITCH GETPROPERTY_StringValue();      
              #define SWITCH3 sss
              #include "_form_property_switch.h"   
              #undef SWITCH3

            } else if (sControlType == "RichTextBox"){

              #define SWITCH GETPROPERTY_StringValue();      
              #define SWITCH3 sss
              #include "_form_property_switch.h"   
              #undef SWITCH3

            } else {
              return;
            }


            ss += " ";
            ss += sOperator;
            ss += " ";

            QVariant v = sss;
            switch(v.type()){
              case QVariant::Bool:
                ss += sss;
                break;
              case QVariant::Date: 
                ss += "'" + sss + "'";
                break;
              case QVariant::Time: 
                ss += "'" + sss + "'";
                break;
              case QVariant::Double:
                ss += sss;
                break;
              case QVariant::UInt:
              case QVariant::ULongLong:
              case QVariant::LongLong:
              case QVariant::Int:
                ss += sss;
                break;
              case QVariant::String: 
                sss = sss.replace("'", "''");
                ss += "'" + sss + "'";
                break;
              default:
                sss = sss.replace("'", "''");
                ss += "'" + sss + "'";
                break;
            }


            b = false;
            break;
          }
        } while (nextControl(&c)); 
      }     
      if (b) return;
    } else {

      QString sss = "";


      QString sName = "";
      QString sValue = "";
      
      //sName = sqlm.headerData(nTableViewCurrentX, Qt::Horizontal).toString();

      QHeaderView *hh = sqlv->horizontalHeader();
      int n = hh->logicalIndex(nTableViewCurrentX);
      QSqlRecord r = sqlm.record();
      sName = r.fieldName(n);

      QVariant v = sqlm.data(sqlm.index(nTableViewCurrentY, nTableViewCurrentX), Qt::EditRole);

      sss = sName;

      ss += sss;

      ss += " ";
      ss += sOperator;
      ss += " ";

      sValue = v.toString();


      switch(v.type()){
        case QVariant::Bool:
          ss += sValue;
          break;
        case QVariant::Date: 
          ss += "'" + sValue + "'";
          break;
        case QVariant::Time: 
          ss += "'" + sValue + "'";
          break;
        case QVariant::Double:
          ss += sValue;
          break;
        case QVariant::UInt:
        case QVariant::ULongLong:
        case QVariant::LongLong:
        case QVariant::Int:
          ss += sValue;
          break;
        case QVariant::String: 
          sValue = sValue.replace("'", "''");
          ss += "'" + sValue + "'";
          break;
        default:
          sValue = sValue.replace("'", "''");
          ss += "'" + sValue + "'";
          break;
      }
      QString k = "";
      if (bAddFilter){
        k = sqlm.filter();
      } else {
        k = sTableFilter;
      }
      
      if (!k.isEmpty()){
        ss = "(" + k + ") AND " + ss;
      }
      sqlm.setFilter(ss);
      if (!sqlm.select()){
        QSqlError e = sqlm.lastError();
        QMessageBox::information(0, tr("Error in = ") + ss,  e.text());  
        return;
      }
      bIsFilterActive = true;
      METHOD_First();
      

      //m->currentIndex();
    }
  }
  if (!bTableView){
    if (stopByQuestion()) return;
    QString s = bAddFilter ? q.lastQuery() : q.executedQuery();
    QString SAVE = s;
    QString s2 = "";
    QString s3 = bAddFilter ? q.lastQuery() : q.executedQuery();
    QString s4 = "";
    if (s.contains(" WHERE ", Qt::CaseInsensitive)){      
      if (s.contains(" GROUP BY ", Qt::CaseInsensitive)){
        s2 = s.mid(s.indexOf(" GROUP BY ", Qt::CaseInsensitive));
      } else {
        if (s.contains(" ORDER BY ", Qt::CaseInsensitive)){
          s2 = s.mid(s.indexOf(" ORDER BY ", Qt::CaseInsensitive));
        }
      }
      s = s.left(s.indexOf(" WHERE ", Qt::CaseInsensitive));
    } else {
      if (s.contains(" GROUP BY ", Qt::CaseInsensitive)){
        s2 = s.mid(s.indexOf(" GROUP BY ", Qt::CaseInsensitive));
        s = s.left(s.indexOf(" GROUP BY ", Qt::CaseInsensitive));
      } else {
        if (s.contains(" ORDER BY ", Qt::CaseInsensitive)){
          s2 = s.mid(s.indexOf(" ORDER BY ", Qt::CaseInsensitive));
          s = s.left(s.indexOf(" ORDER BY ", Qt::CaseInsensitive));
        }
      }
    }
    s += " WHERE ";

    if (s3.contains(" WHERE ", Qt::CaseInsensitive)){      
      s3 = s3.mid(s3.indexOf(" WHERE ", Qt::CaseInsensitive) + 7);
      if (s3.contains(" GROUP BY ", Qt::CaseInsensitive)){
        s4 = s3.left(s3.indexOf(" GROUP BY ", Qt::CaseInsensitive));
      } else {
        if (s3.contains(" ORDER BY ", Qt::CaseInsensitive)){
          s4 = s3.left(s3.indexOf(" ORDER BY ", Qt::CaseInsensitive));
        }
      }
    }

    if (!s4.isEmpty()) s+= "(";
    s += s4;
    if (!s4.isEmpty()) s+= ") AND ";
    s += ss;
    s += s2;
    EVENT_OnQuery();
    nQuerySize = 0;
    if (q.exec(s)){
     //my_log->METHOD_PrintSql(s);
     setQuerySize();
     // addProtocol(tr("Refreshed query with filter ") + ss);
     // addLog(s);
      bIsFilterActive = true;
      bool b = METHOD_First(false);
      setAddNew(false);
      setDirty(false);
      
      return;
    } else {
      QMessageBox::information(this, MYAPP, q.lastError().text());

      nQuerySize = 0;
      if (q.exec(SAVE)){ // at least this sql statement will work
        //my_log->METHOD_PrintSql(SAVE);
        setQuerySize();
       // addProtocol(tr("Requeried, because new SQL statement failed"));
       // addLog(SAVE);
        bool b = METHOD_First(false);
        setAddNew(false);
        setDirty(false);        
        return;
      }
    }
  } else {
   // bool b = sqlm.select();
   // sqlv->setFocus();
    return;
  }
}

void _form::METHOD_SortAsc(QString ss)
{
#ifdef RUN
  if (!CurrentDatabase.isOpen()) return;
  if (this->GETPROPERTY_SQLName().isEmpty()) return;

  if (!bTableView){

    if (ss == ""){

      if (ControlFocusPrevious == 0) return;

      QString cn = ControlFocusPrevious->objectName();

      bool b = true;
      QWidget *c = 0;
      if (firstControl(&c)){
        do {
          if (c->objectName() == cn){
            b = false;
            
            #define SWITCH GETPROPERTY_SQLName();      
            #define SWITCH3 ss
            #include "_form_property_switch.h"   
            #undef SWITCH3

            if (ss.isEmpty()) return;

            break;
          }
        } while (nextControl(&c)); 
      }     
      if (b) return;
    }
    
    if (stopByQuestion()) return;
    QString s = q.executedQuery();
    QString SAVE = s;
    if (s.contains(" ORDER BY ", Qt::CaseInsensitive)){
      s = s.left(s.indexOf(" ORDER BY ", Qt::CaseInsensitive));
    }
    s += " ORDER BY ";
    if (!ss.contains(" ") && !ss.endsWith(" ASC", Qt::CaseInsensitive)) ss += " ASC";
    s += ss;
    EVENT_OnQuery();
    nQuerySize = 0;
    if (q.exec(s)){
      //my_log->METHOD_PrintSql(s);
     setQuerySize();
     // addProtocol(tr("Refreshed query with sort ") + ss);
     // addLog(s);
      bool b = METHOD_First(false);
      setAddNew(false);
      setDirty(false);
      return;
    } else {
      QMessageBox::information(this, MYAPP, q.lastError().text());

      nQuerySize = 0;
      if (q.exec(SAVE)){ // at least this sql statement will work
        //my_log->METHOD_PrintSql(SAVE);
       setQuerySize();
       // addProtocol(tr("Requeried, because new SQL statement failed"));
       // addLog(SAVE);
        bool b = METHOD_First(false);
        setAddNew(false);
        setDirty(false);
        return;
      }
    }
  } else {

    QString sName = "";

    QHeaderView *hh = sqlv->horizontalHeader();
    int n = hh->logicalIndex(nTableViewCurrentX);
    QSqlRecord r = sqlm.record();
    sName = r.fieldName(n);

    for (int i = 0; i < sqlm.record().count(); ++i){
      if (sqlm.fieldIndex(sName) == i){
        n = i;
        break;
      }          
    }        
    if (n >= 0) sqlm.setSort(n, Qt::AscendingOrder);
    sqlm.select();
    sqlv->setFocus();
    METHOD_First(false);
    return;
  }
#endif
}

void _form::METHOD_SortDesc(QString ss)
{
  if (!CurrentDatabase.isOpen()) return;
  if (this->GETPROPERTY_SQLName().isEmpty()) return;

  if (!bTableView){
    if (ss == ""){

      if (ControlFocusPrevious == 0) return;

      QString cn = ControlFocusPrevious->objectName();

      bool b = true;
      QWidget *c = 0;
      if (firstControl(&c)){
        do {
          if (c->objectName() == cn){
            b = false;
            
            #define SWITCH GETPROPERTY_SQLName();      
            #define SWITCH3 ss
            #include "_form_property_switch.h"   
            #undef SWITCH3

            if (ss.isEmpty()) return;

            break;
          }
        } while (nextControl(&c)); 
      }     
      if (b) return;
    }
  
    if (stopByQuestion()) return;
    QString s = q.executedQuery();
    QString SAVE = s;
    if (s.contains(" ORDER BY ", Qt::CaseInsensitive)){
      s = s.left(s.indexOf(" ORDER BY ", Qt::CaseInsensitive));
    }
    s += " ORDER BY ";
    if (!ss.contains(" ") && !ss.endsWith(" DESC", Qt::CaseInsensitive)) ss += " DESC";
    s += ss;
    EVENT_OnQuery();
    nQuerySize = 0;
    if (q.exec(s)){
      //my_log->METHOD_PrintSql(s);
     setQuerySize();
     // addProtocol(tr("Refreshed query with sort ") + ss);
     // addLog(s);
      bool b = METHOD_First(false);
      setAddNew(false);
      setDirty(false);
      return;
    } else {
      QMessageBox::information(this, MYAPP, q.lastError().text());

      nQuerySize = 0;
      if (q.exec(SAVE)){ // at least this sql statement will work
        //my_log->METHOD_PrintSql(SAVE);
       setQuerySize();
       // addProtocol(tr("Requeried, because new SQL statement failed"));
       // addLog(SAVE);
        bool b = METHOD_First(false);
        setAddNew(false);
        setDirty(false);
        return;
      }
    }
  } else {

    QString sName = "";

    QHeaderView *hh = sqlv->horizontalHeader();
    int n = hh->logicalIndex(nTableViewCurrentX);
    QSqlRecord r = sqlm.record();
    sName = r.fieldName(n);

    for (int i = 0; i < sqlm.record().count(); ++i){
      if (sqlm.fieldIndex(sName) == i){
        n = i;
        break;
      }          
    }        
    if (n >= 0) sqlm.setSort(n, Qt::DescendingOrder);

    sqlm.select();
    sqlv->setFocus();
    METHOD_First(false);
    return;
  }
}

#endif

#ifdef IDE
bool _form::saveControls(QString *s)
{

  QWidget *c;
  bool b = true;

re:
  QObjectList l = children();
  for (int i = 0; i < l.size(); i++){ // save it in stack order
    QWidget *cc = qobject_cast<QWidget *>(l.at(i));

  
    if (firstControl(&c)){

      do {

        _controlType ct = controlType(c);

        if (cc == c && ((b == true && ct == t_tab) || (b == false && ct != t_tab))){

          sControlName = "";
          #define SWITCH GETPROPERTY_Name();      
          #define SWITCH3 sControlName
          #include "_form_property_switch.h"   
          #undef SWITCH3

          *s += "\n";

          *s += "  Begin ";
          *s += controlTypeName(ct);
          *s += " ";
          *s += sControlName + "\n";

          #define SWITCH saveProperty(s);
          #include "_form_property_switch.h"    

          *s += "  End";
          *s += "\n";
        }

      } while (nextControl(&c));
      
    }
  }

  if (b){ // write all tabs first, then other controls
    b = false;
    goto re;
  }

  return true;
}

#endif

#ifdef RUN
TableViewDelegate::TableViewDelegate(_form *f, QObject *parent)
     : QItemDelegate(parent) { my_form = f; }

 QWidget *TableViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& ii,
     const QModelIndex &index) const
 {
   return 0;
   /*
     if(index.column() == 1){
         QDateTimeEdit *editor = new QDateTimeEdit(parent);
         editor->setDisplayFormat("dd/M/yyyy");
         editor->setCalendarPopup(true);
         return editor;
     }
     QLineEdit *editor = new QLineEdit(parent);
     connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
     */
//   QWidget *c = QModelIndexToWidget(index);
//   c->setParent(parent);

   QWidget *c = QModelIndexToWidget(index);
   _textbox *my_textbox = qobject_cast<_textbox *>(c);
   if (my_textbox){
     _textbox *t = new _textbox(0, parent);
     t->SETPROPERTY_InputMask(my_textbox->GETPROPERTY_InputMask());
     t->SETPROPERTY_ValidatorDouble(my_textbox->GETPROPERTY_ValidatorDouble());
     t->SETPROPERTY_ValidatorInteger(my_textbox->GETPROPERTY_ValidatorInteger());
     t->SETPROPERTY_IntegerMaximum(my_textbox->GETPROPERTY_IntegerMaximum());
     t->SETPROPERTY_Completer(my_textbox->GETPROPERTY_Completer());

     connect(t, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));     
     return t;
   }

   return TableViewDelegate::createEditor(parent, ii, index);
   
 }

 void TableViewDelegate::commitAndCloseEditor()
 {
   QObject *c = sender();

   _textbox *my_textbox = qobject_cast<_textbox *>(c);
   if (my_textbox){
     emit commitData(my_textbox);     
     emit closeEditor(my_textbox/*, QAbstractItemDelegate::EditNextItem*/);
   }
 }

void TableViewDelegate::setEditorData(QWidget *c, const QModelIndex &index) const
{
  QString sControlType = c->property("__kb1979.ControlType.kb__").toString();

  QVariant v = index.model()->data(index, Qt::EditRole);


  _textbox *my_textbox = qobject_cast<_textbox *>(QModelIndexToWidget(index));
  if (my_textbox){
    ((_textbox *) c)->SETPROPERTY_StringValue(v.toString());
  }
/*

  if (sControlType == "Label") ((_label *) c)->SETPROPERTY_Caption(v.toString());
  else if (sControlType == "TextBox") ((_textbox *) c)->SETPROPERTY_StringValue(v.toString());
  else if (sControlType == "ComboBox"){
    QString sSQLRelation = "";

    if (!sSQLRelation.isEmpty()){

      if (!sSQLRelation.contains(sKBRecordId, Qt::CaseInsensitive)){
        int k = sSQLRelation.indexOf("SELECT ", Qt::CaseInsensitive);
        if (k >= 0){
          k += 7;
          sSQLRelation = sSQLRelation.insert(k, sKBRecordId + ", ");
        }
      }

      if (((_combobox *) c)->count() == 0){

        QSqlQuery rr(CurrentDatabase);
        QString s = sSQLRelation;
        if (rr.exec(s)){
          my_form->addLog(s);

          if (rr.first()){
            ((_combobox *) c)->addItem("", QVariant(0));

            do {
              QString ss = "";
              QSqlRecord r = rr.record();
              for (int i = 0; i < r.count() - 1; i++){
                ss += rr.value(i + 1).toString();
                ss += " | ";
              }

              qulonglong kbrecordid = rr.value(0).toLongLong();

              ((_combobox *) c)->addItem(ss, QVariant(kbrecordid));
            } while (rr.next());
          }
        }
      }
      int n = ((_combobox *) c)->findData(v);
      if (n >= 0) ((_combobox *) c)->setCurrentIndex(n); else ((_combobox *) c)->setCurrentIndex(0);
    } else {
      ((_combobox *) c)->METHOD_Select(v.toString());            
    }
  }
  else if (sControlType == "ListBox"){
    QString sSQLRelation = "";

    if (!sSQLRelation.isEmpty()){

      if (!sSQLRelation.contains(sKBRecordId, Qt::CaseInsensitive)){
        int k = sSQLRelation.indexOf("SELECT ", Qt::CaseInsensitive);
        if (k >= 0){
          k += 7;
          sSQLRelation = sSQLRelation.insert(k, sKBRecordId + ", ");
        }
      }

      if (((_listbox *) c)->count() == 0){

        QSqlQuery rr(CurrentDatabase);
        QString s = sSQLRelation;
        if (rr.exec(s)){
          my_form->addLog(s);

          if (rr.first()){
            QListWidgetItem *it = new QListWidgetItem();
            it->setText(""); it->setData(Qt::UserRole, QVariant(0));
            ((_listbox *) c)->addItem(it);

            do {
              QString ss = "";
              QSqlRecord r = rr.record();
              for (int i = 0; i < r.count() - 1; i++){
                ss += rr.value(i + 1).toString();
                ss += " | ";
              }

              qulonglong kbrecordid = rr.value(0).toLongLong();

              QListWidgetItem *it = new QListWidgetItem();
              it->setText(ss); it->setData(Qt::UserRole, QVariant(kbrecordid));
              ((_listbox *) c)->addItem(it);

            } while (rr.next());
          }
        }
      }
      bool b = true;
      for (int i = 0; i < ((_listbox *) c)->count(); i++){
        QListWidgetItem *it = ((_listbox *) c)->item(i);
        if (it->data(Qt::UserRole) == v){
          ((_listbox *) c)->setCurrentRow(i); 
          b = false;
          break;
        }
      }
      if (b) ((_listbox *) c)->setCurrentRow(0);                
      
    } else {
      ((_listbox *) c)->METHOD_Select(v.toString());            
    }
  }
  else if (sControlType == "CheckBox") ((_checkbox *) c)->SETPROPERTY_BooleanValue(v.toBool());
  else if (sControlType == "DateBox"){
    QDate s = v.toDate();
    if (s.isNull()){                
      ((_datebox *) c)->setDate(QDate());                 
      //((_datebox *) c)->setCurrentSection(QDateTimeEdit::DaySection); ((_datebox *) c)->clear();
      //((_datebox *) c)->setCurrentSection(QDateTimeEdit::MonthSection); ((_datebox *) c)->clear();
      ((_datebox *) c)->setCurrentSection(QDateTimeEdit::YearSection); ((_datebox *) c)->clear();
        
    } else {
      ((_datebox *) c)->SETPROPERTY_StringValue(s.toString("yyyy-MM-dd"));
    }
  }
  else if (sControlType == "TimeBox"){
    QTime s = v.toTime();
    if (s.isNull()){                
      ((_timebox *) c)->setTime(QTime());                 
      ((_timebox *) c)->setCurrentSection(QDateTimeEdit::HourSection); ((_timebox *) c)->clear();
        
    } else {
      ((_timebox *) c)->SETPROPERTY_StringValue(s.toString("hh:mm:ss"));
    }
  }
  else if (sControlType == "RichTextBox") ((_editor *) c)->SETPROPERTY_StringValue(v.toString());

*/
   /*
     QWidget *c = QModelIndexToWidget(index);

     QLineEdit *edit = qobject_cast<QLineEdit *>(editor);
     if (edit) {
         edit->setText(index.model()->data(index, Qt::EditRole).toString());
     }
     else {
         QDateTimeEdit *dateEditor = qobject_cast<QDateTimeEdit *>(editor);
         if (dateEditor) {
             dateEditor->setDate(QDate::fromString(index.model()->data(index, Qt::EditRole).toString(), "d/M/yyyy"));
         }
     }*/

 }

 void TableViewDelegate::setModelData(QWidget *c, QAbstractItemModel *model,
     const QModelIndex &index) const
 {
  QString sControlType = c->property("__kb1979.ControlType.kb__").toString();

  QVariant v = index.model()->data(index, Qt::EditRole);

  _textbox *my_textbox = qobject_cast<_textbox *>(QModelIndexToWidget(index));
  if (my_textbox){
    my_textbox->SETPROPERTY_StringValue(v.toString());
    model->setData(index, ((_textbox *) c)->GETPROPERTY_StringValue());
  }
/*
  if (sControlType == "Label") model->setData(index, ((_label *) c)->GETPROPERTY_Caption());
  else if (sControlType == "TextBox") model->setData(index, ((_textbox *) c)->GETPROPERTY_StringValue());
  else if (sControlType == "ComboBox"){
    QString sSQLRelation = "";

    if (!sSQLRelation.isEmpty()){
    } else {
      model->setData(index, ((_listbox *) c)->METHOD_Selected());            
    }
  }
  else if (sControlType == "ListBox"){
    QString sSQLRelation = "";

    if (!sSQLRelation.isEmpty()){
    } else {
      model->setData(index, ((_listbox *) c)->METHOD_Selected());            
    }
  }
  else if (sControlType == "CheckBox") model->setData(index, ((_checkbox *) c)->GETPROPERTY_BooleanValue() ? "True" : "False");
  else if (sControlType == "DateBox"){
    model->setData(index, ((_datebox *) c)->GETPROPERTY_StringValue());
  }
  else if (sControlType == "TimeBox"){
    model->setData(index, ((_timebox *) c)->GETPROPERTY_StringValue());
  }
  else if (sControlType == "RichTextBox") model->setData(index, ((_editor *) c)->GETPROPERTY_StringValue());

*/
   /*
     QLineEdit *edit = qobject_cast<QLineEdit *>(editor);
     if (edit) {
         model->setData(index, edit->text());
     }
     else {
         QDateTimeEdit *dateEditor = qobject_cast<QDateTimeEdit *>(editor);
         if (dateEditor) {
             model->setData(index, dateEditor->date().toString("dd/M/yyyy"));
         }
     }*/
    //c->hide();
 }

 
 QWidget *TableViewDelegate::QModelIndexToWidget(const QModelIndex &index) const
 {
  int n = index.column();
  /*
  int nn = 0;

  QHeaderView *hh = my_form->sqlv->horizontalHeader();
  for (int i = 0; i < hh->count() && i < n + nn; i++){
    nn += hh->isSectionHidden(i) ? 1 : 0;
  }*/

  QString s = "";
  QStringList fi = my_form->getSQLFields();
  foreach(s, fi){
    if (my_form->sqlm.fieldIndex(s) == n){
      break;
    }
  }

  QWidget *c = 0;
  if (my_form->firstControl(&c)){
    do {

      #define SWITCH6 my_form->controlType(c)
      QString ss = "";
      #define SWITCH GETPROPERTY_SQLName();      
      #define SWITCH3 ss
      #include "_form_property_switch.h"   
      #undef SWITCH3
      #define SWITCH6 controlType(c)

      if (ss == s){
        return c;
      }
    } while (my_form->nextControl(&c)); 
  }     

  return 0;
}

 TableView::TableView(_form *f) : QTableView(f)
{
  my_form = f;
}
 
void TableView::currentChanged ( const QModelIndex & current, const QModelIndex & previous )
{
  my_form->nTableViewCurrentX = current.column();
  my_form->nTableViewCurrentY = current.row();

  if (current.row() != previous.row()){
    if (my_form->bAddNew && !my_form->stopByQuestion()){ 
      // delete addnewrecord
      int n = previous.row();
      my_form->sqlm.removeRows(n, 1);
      my_form->setAddNew(false);
    } else if (my_form->sqlm.isDirty(previous)){ 
      bool b = false;
      if (my_form->stopByQuestion()){ 
   //     my_form->sqlm.revertAll();
      } else {
   //     b = my_form->sqlm.submit();
      }
      my_form->EVENT_OnGoTo3();
      my_form->EVENT_OnGoTo2();
      my_form->EVENT_OnGoTo();
    } else {
      my_form->EVENT_OnGoTo3();
      my_form->EVENT_OnGoTo2();
      my_form->EVENT_OnGoTo();
    }

    my_form->setSQL2(my_form->sqlm.record(my_form->nTableViewCurrentY));

  }
}

#endif

#ifdef IDE
void _form::event_EDIT_BACKGROUND()
{
}

void _form::event_EDIT_FONTNAME()
{
}

void _form::event_EDIT_FONTCOLOR()
{
}

void _form::event_EDIT_BOLD()
{
}

void _form::event_EDIT_ITALIC()
{
}

void _form::event_EDIT_UNDERLINE()
{
}

void _form::event_EDIT_FONTSIZE()
{
}


#endif

#ifdef RUN
void _form::METHOD_OpenPrintDialog() // only for reports
{
  METHOD_Open(true);
  printDialog();
}

void _form::METHOD_OpenPrint() // only for reports
{
  METHOD_Open(true);
  printDialog();
}

void _form::METHOD_OpenPrintPreview() // only for reports
{
  METHOD_Open(true);
  previewReport();
}

void _form::EVENT_OnGoTo3()
{
  if (!bOnGoTo3First && !bOnGoTo3Children) return;

  if (bOnGoTo3First) bOnGoTo3First = false;

  QObjectList it = children(); // iterate over the children
  _form *o;
  for (int q = 0; q < it.size(); q++){
    o = qobject_cast<_form *>(it.at(q));
    if (o){
      bOnGoTo3Children = true;
      o->METHOD_Open(false, true);
    }
  }

}


t_long _form::METHOD_Len()
{ 

  
  if (bQuerySize){
    if (!bTableView){
      return q.size();
    } else {
      return sqlm.rowCount();
    }
  } else {
    if (!bTableView){
      return nQuerySize;
    } else {
      return sqlm.rowCount();
    }    
  }

  return 0;
}
#endif

#ifdef IDE
bool _form::saveFormClassSourceCodeOnly(QString m, QString k)
{
 // QString s = "";
  QString ss = "";

  int n = getFormClassSourceCodeFilePos(m, &ss);
//  s = ss;
  ss = ss.left(n);

  //s = ss.mid(n);

  QFile f(m);
  if (!f.open(QIODevice::WriteOnly )){
    QMessageBox::information(EXTERN_my_mainwindow, MYAPP, QString("Could not read from %1").arg(m));
  } else {
   // f.seek(n);
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << ss;
    t << k;
    f.resize(f.pos());
    f.close();
  }

  return true;
}

#endif


#ifdef RUN
void _form::METHOD_ShowMultiPage(t_integer nPage)
{
  if (nCurrentMultiPage == nPage){
    EVENT_OnMultiPageShow(nPage);
    return;
  }

  int nMultiPageHeight = GETPROPERTY_MultiPageHeight();

  bool bInc = nCurrentMultiPage < nPage;
  int y_offset = (nPage - nCurrentMultiPage) * nMultiPageHeight * (bInc ? -1 : -1);

  nCurrentMultiPage = nPage;

  int nMultiPageBorderTop = GETPROPERTY_MultiPageBorderTop();
  int nMultiPageBorderBottom = GETPROPERTY_MultiPageBorderBottom();
  int nMultiPageBorderLeft = GETPROPERTY_MultiPageBorderLeft();
  int nMultiPageBorderRight = GETPROPERTY_MultiPageBorderRight();
        

  if (nMultiPageHeight){
    QWidget *c = 0;
    if (firstControl(&c)){
      do {       
      
        int nMultiPage = 0;
        #define SWITCH GETPROPERTY_MultiPage();      
        #define SWITCH3 nMultiPage
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if (nMultiPage){
          int y = c->y();
          y += y_offset;
          c->move(c->x(), y);
        }
    
      } while (nextControl(&c));
    }
  }
  EVENT_OnMultiPageShow(nPage);
}

void _form::METHOD_ShowNextMultiPage()
{
  METHOD_ShowMultiPage(nCurrentMultiPage + 1);
}

void _form::METHOD_ShowPreviousMultiPage()
{
  METHOD_ShowMultiPage(nCurrentMultiPage - 1);
}

#endif


void _form::XScrollBar_valueChanged(int value)
{  
  static bool bLock = false;

  if (bLock) return;
  bLock = true;

  //SETPROPERTY_ScrollX(value);
#ifdef IDE
  /*
  t_property *d;

  d = pp["ScrollX"]; if (d) EXTERN_my_propertywindow->SETPROPERTY_ScrollX(d->display, d->set, value);
 */
 EXTERN_my_propertywindow->SETPROPERTY_ScrollX(true, true, value);


  static int nOldValue = 0;
  int n = nOldValue < value ? -(value - nOldValue): (nOldValue - value);
  nOldValue = value;

  QObjectList it = children(); // iterate over the children
  QObject *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    if (qobject_cast<QScrollBar *>(o)){
    } else if (o->parent() == this){
      QWidget *w = qobject_cast<QWidget *>(o);
      if (w){
        w->move(w->x() + n, w->y());
      }
    }
  }
#else 
 SETPROPERTY_ScrollX(value);
 main->repaint();
#endif

#ifdef RUN
  EVENT_OnScroll();
#endif
  bLock = false;
}

void _form::YScrollBar_valueChanged(int value)
{
  static bool bLock = false;

  if (bLock) return;
  bLock = true;

 // SETPROPERTY_ScrollY(value);
#ifdef IDE
  /*
  t_property *d;

  d = pp["ScrollY"]; if (d) EXTERN_my_propertywindow->SETPROPERTY_ScrollY(d->display, d->set, value);
*/
  EXTERN_my_propertywindow->SETPROPERTY_ScrollY(true, true, value);

  static int nOldValue = 0;
  int n = nOldValue < value ? -(value - nOldValue): (nOldValue - value);
  nOldValue = value;

  QObjectList it = children(); // iterate over the children
  QObject *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    if (qobject_cast<QScrollBar *>(o)){
    } else if (o->parent() == this){
      QWidget *w = qobject_cast<QWidget *>(o);
      if (w){
        w->move(w->x(), w->y() + n);
      }
    }
  }
#else 
 SETPROPERTY_ScrollY(value);
 main->repaint();
#endif

#ifdef RUN
  EVENT_OnScroll();
#endif
  bLock = false;
}

#ifdef IDE
void _form::updateControls(_selectPanelStyle style, int x, int y, int w, int h)
{
  QWidget *c;

  //setUpdatesEnabled(false);

  if (firstControl(&c)){

    do {

      if (c->acceptDrops()){ // missused as selected flag

        int xx = 0;
        int yy = 0;
        int ww = 0;
        int hh = 0;

        switch(style){
          case LeftTop:
            xx = c->x() - x;
            yy = c->y() - y;
            ww = c->width() + w;
            hh = c->height() + h;              

            if (xx <0){
              xx = 0;
              ww = c->width();
            }
            if (yy <0){ 
              yy = 0;
              hh = c->height();
            }
            if (xx + ww > width()) ww = width() - xx;
            if (yy + hh > height()) hh = height() - yy;

            if (ww <= 0) xx = c->x();
            if (hh <= 0) yy = c->y();

            break;
          case MidTop:
            xx = c->x();
            yy = c->y() - y;
            ww = c->width();
            hh = c->height() + h;              

            if (yy <0){ 
              yy = 0;
              hh = c->height();
            }
            if (yy + hh > height()) hh = height() - yy;

            if (ww <= 0) xx = c->x();
            if (hh <= 0) yy = c->y();

            break;
          case RightTop:
            xx = c->x();
            yy = c->y() - y;
            ww = c->width() - w;
            hh = c->height() + h;              

            if (xx <0){
              xx = 0;
              ww = c->width();
            }
            if (yy <0){ 
              yy = 0;
              hh = c->height();
            }
            if (xx + ww > width()) ww = width() - xx;
            if (yy + hh > height()) hh = height() - yy;

            if (ww <= 0) xx = c->x();
            if (hh <= 0) yy = c->y();

            break;
          case LeftMid:
            xx = c->x() - x;
            yy = c->y();
            ww = c->width() + w;
            hh = c->height();              

            if (xx < 0){
              xx = 0;
              ww = c->width();
            }
            if (yy < 0){ 
              yy = 0;
              hh = c->height();
            }

            if (xx + ww > width()) ww = width() - xx;
            if (yy + hh > height()) hh = height() - yy;
            
            if (ww <= 0) xx = c->x();
            if (hh <= 0) yy = c->y();

            break;
          case RightMid:

            xx = c->x();
            yy = c->y();
            ww = c->width() - w;
            hh = c->height();              

            if (xx <0){
              xx = 0;
              ww = c->width();
            }
            if (yy <0){ 
              yy = 0;
              hh = c->height();
            }
            if (xx + ww > width()) ww = width() - xx;
            if (yy + hh > height()) hh = height() - yy;

            if (ww <= 0) xx = c->x();
            if (hh <= 0) yy = c->y();

            break;
          case LeftBottom:

            xx = c->x() - x;
            yy = c->y();
            ww = c->width() + w;
            hh = c->height() - h;              

            if (xx <0){
              xx = 0;
              ww = c->width();
            }
            if (yy <0){ 
              yy = 0;
              hh = c->height();
            }
            if (xx + ww > width()) ww = width() - xx;
            if (yy + hh > height()) hh = height() - yy;

            if (ww <= 0) xx = c->x();
            if (hh <= 0) yy = c->y();

            break;
          case MidBottom:

            xx = c->x();
            yy = c->y();
            ww = c->width();
            hh = c->height() - h;              

            if (xx <0){
              xx = 0;
              ww = c->width();
            }
            if (yy <0){ 
              yy = 0;
              hh = c->height();
            }
            if (xx + ww > width()) ww = width() - xx;
            if (yy + hh > height()) hh = height() - yy;

            if (ww <= 0) xx = c->x();
            if (hh <= 0) yy = c->y();

            break;
          case RightBottom:
            xx = c->x();
            yy = c->y();
            ww = c->width() - w;
            hh = c->height() - h;              

            if (xx <0){
              xx = 0;
              ww = c->width();
            }
            if (yy <0){ 
              yy = 0;
              hh = c->height();
            }
            if (xx + ww > width()) ww = width() - xx;
            if (yy + hh > height()) hh = height() - yy;

            if (ww <= 0) xx = c->x();
            if (hh <= 0) yy = c->y();

            break;
          default:
            break;
        }
        setGeo(c, xx, yy, ww, hh);
      }

    } while (nextControl(&c));
    
  }

  //setUpdatesEnabled(true);
  updatePropertyWindowGeo();
  //showUpdatePropertyWindow(false);
}


#endif


#ifdef RUN


t_boolean _form::METHOD_IsShownFullScreen()
{
  return this->isFullScreen();
}

t_boolean _form::METHOD_IsShownMaximized()
{
  return this->isMaximized();
}

t_boolean _form::METHOD_IsShownMinimized()
{
  return this->isMinimized();
}

t_boolean _form::METHOD_IsShownNormal()
{
  return !this->isFullScreen() && !this->isMaximized() && !this->isMinimized();
}

void _form::SETPROPERTY_ShowMode(QString sShowMode, bool bInit)
{  
  if (sShowMode.contains("Maximized", Qt::CaseInsensitive)){
    if (bInit == false) showMaximized();
    _property::SETPROPERTY_ShowMode("Maximized");
  } else if (sShowMode.contains("Minimized", Qt::CaseInsensitive)){
    if (bInit == false) showMinimized();
    _property::SETPROPERTY_ShowMode("Minimized");
  } else if (sShowMode.contains("Normal", Qt::CaseInsensitive)){
    if (bInit == false) show();
    _property::SETPROPERTY_ShowMode("Normal");
  } else if (sShowMode.contains("Centered", Qt::CaseInsensitive)){

    if (bInit == false){
      if (forms_workspace && parentWidget() && (qobject_cast<QMdiSubWindow *>(parentWidget()))){
        QWidget *w = parentWidget()->parentWidget();
        QWidget *ww = parentWidget();
        ww->setGeometry(w->width() / 2 - ww->width() / 2, w->height() / 2 - ww->height() / 2, ww->width(), ww->height());
      } else {
        setGeometry(QApplication::desktop()->width() / 2 - width() / 2, QApplication::desktop()->height() / 2 - height() / 2, width(), height());
        show();
      }
    }
    _property::SETPROPERTY_ShowMode("Centered");
    
  } else if (sShowMode.contains("FullScreen", Qt::CaseInsensitive)){
    if (bInit == false){ 
      show(); // needed to have working fullscreen
      METHOD_ShowFullScreen();
    }
    _property::SETPROPERTY_ShowMode("FullScreen");
  }
  
}

QString _form::GETPROPERTY_ShowMode()
{
  if (isVisible()){
    if (METHOD_IsShownFullScreen()) return "FullScreen";
    if (METHOD_IsShownMaximized()) return "Maximized";
    if (METHOD_IsShownMinimized()) return "Minimized";
    if (METHOD_IsShownNormal()) return "Normal";
  } else {
    _property::GETPROPERTY_ShowMode();
  }
}

void _form::METHOD_SetWithTag(QString Tag, QString PropertyName, t_boolean bb)
{
  QWidget *c;
  //bool bb = false;
  QString ss = "";
  int nn = 0;
  t_double dd = 0;
  QString sTag;

  if (firstControl(&c)){
   
    do {

      #define SWITCH GETPROPERTY_Tag();      
      #define SWITCH3 sTag
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sTag.compare(Tag, Qt::CaseInsensitive) == 0){
        applyProperty(c, PropertyName, bb, ss, nn, dd);
      }

    } while (nextControl(&c)); 
  }
}

void _form::METHOD_SetWithTag(QString Tag, QString PropertyName, t_integer nn)
{
  QWidget *c;
  bool bb = false;
  QString ss = "";
  //int nn = 0;
  t_double dd = 0;
  QString sTag;

  if (firstControl(&c)){
   
    do {

      #define SWITCH GETPROPERTY_Tag();      
      #define SWITCH3 sTag
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sTag.compare(Tag, Qt::CaseInsensitive) == 0){
        applyProperty(c, PropertyName, bb, ss, nn, dd);
      }

    } while (nextControl(&c)); 
  }
}

void _form::METHOD_SetWithTag(QString Tag, QString PropertyName, QString ss)
{
  QWidget *c;
  bool bb = false;
  //QString ss = "";
  int nn = 0;
  t_double dd = 0;
  QString sTag;

  if (firstControl(&c)){
   
    do {

      #define SWITCH GETPROPERTY_Tag();      
      #define SWITCH3 sTag
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sTag.compare(Tag, Qt::CaseInsensitive) == 0){
        applyProperty(c, PropertyName, bb, ss, nn, dd);
      }

    } while (nextControl(&c)); 
  }
}

void _form::METHOD_SetWithTag(QString Tag, QString PropertyName, t_double dd)
{
  QWidget *c;
  bool bb = false;
  QString ss = "";
  int nn = 0;
 // t_double dd = 0;
  QString sTag;

  if (firstControl(&c)){
   
    do {

      #define SWITCH GETPROPERTY_Tag();      
      #define SWITCH3 sTag
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sTag.compare(Tag, Qt::CaseInsensitive) == 0){
        applyProperty(c, PropertyName, bb, ss, nn, dd);
      }

    } while (nextControl(&c)); 
  }
}

void _form::METHOD_SetWithGroup(QString Group, QString PropertyName, t_boolean bb)
{
  QWidget *c;
  //bool bb = false;
  QString ss = "";
  int nn = 0;
  t_double dd = 0;
  QString sGroup;
  

  if (firstControl(&c)){
   
    do {

      #define SWITCH GETPROPERTY_Group();      
      #define SWITCH3 sGroup
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sGroup.compare(Group, Qt::CaseInsensitive) == 0){
        applyProperty(c, PropertyName, bb, ss, nn, dd);
      }

    } while (nextControl(&c)); 
  }
}

void _form::METHOD_SetWithGroup(QString Group, QString PropertyName, t_integer nn)
{
  QWidget *c;
  bool bb = false;
  QString ss = "";
  //int nn = 0;
  t_double dd = 0;
  QString sGroup;

  if (firstControl(&c)){
   
    do {

      #define SWITCH GETPROPERTY_Group();      
      #define SWITCH3 sGroup
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sGroup.compare(Group, Qt::CaseInsensitive) == 0){
        applyProperty(c, PropertyName, bb, ss, nn, dd);
      }


    } while (nextControl(&c)); 
  }
}

void _form::METHOD_SetWithGroup(QString Group, QString PropertyName, QString ss)
{
  QWidget *c;
  bool bb = false;
  //QString ss = "";
  int nn = 0;
  t_double dd = 0;
  QString sGroup;

  if (firstControl(&c)){
   
    do {

      #define SWITCH GETPROPERTY_Group();      
      #define SWITCH3 sGroup
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sGroup.compare(Group, Qt::CaseInsensitive) == 0){
        applyProperty(c, PropertyName, bb, ss, nn, dd);
      }


    } while (nextControl(&c)); 
  }
}

void _form::METHOD_SetWithGroup(QString Group, QString PropertyName, t_double dd)
{
  QWidget *c;
  bool bb = false;
  QString ss = "";
  int nn = 0;
  //int dd = 0;
  QString sGroup;

  if (firstControl(&c)){
   
    do {

      #define SWITCH GETPROPERTY_Group();      
      #define SWITCH3 sGroup
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sGroup.compare(Group, Qt::CaseInsensitive) == 0){
        applyProperty(c, PropertyName, bb, ss, nn, dd);
      }


    } while (nextControl(&c)); 
  }
}

void _form::form_topLevelChanged(bool)
{
  if (GETPROPERTY_Opacity()) SETPROPERTY_Opacity(GETPROPERTY_Opacity());
}

void _form::METHOD_DockTabify(QString FormName)
{
  if (dock == 0) return;

  _form *f = (_form *) _forms::METHOD_Form(FormName);
  if (f == 0) return;

  forms_mainwindow->tabifyDockWidget(f->dock, dock);
}

void _form::METHOD_DockSplit(QString FormName, QString Direction)
{
  if (dock == 0) return;

  _form *f = (_form *) _forms::METHOD_Form(FormName);
  if (f == 0) return;

  forms_mainwindow->splitDockWidget(f->dock, dock, Direction.contains("Horizontal", Qt::CaseInsensitive) ? Qt::Horizontal : Qt::Vertical);
}


#endif

void _form::deleteControl(QWidget *c)
{
  // CONTROL
  if (qobject_cast<_udpsocket *>(c) && udpsockets.del2((_udpsocket *) c)) return;
  if (qobject_cast<_scrollbar *>(c) && scrollbars.del2((_scrollbar *) c)) return;
  if (qobject_cast<_spinbox *>(c) && spinboxes.del2((_spinbox *) c)) return;
  if (qobject_cast<_slider *>(c) && sliders.del2((_slider *) c)) return;
  if (qobject_cast<_formsview *>(c) && formsviews.del2((_formsview *) c)) return;
  if (qobject_cast<_toolbarview *>(c) && toolbarviews.del2((_toolbarview *) c)) return;
  if (qobject_cast<_svg *>(c) && svgs.del2((_svg *) c)) return;
  if (qobject_cast<_commandlinkbutton *>(c) && commandlinkbuttons.del2((_commandlinkbutton *) c)) return;
  if (qobject_cast<_resizebox *>(c) && resizeboxes.del2((_resizebox *) c)) return;
  if (qobject_cast<_toolbutton *>(c) && toolbuttons.del2((_toolbutton *) c)) return;
  if (qobject_cast<_line *>(c) && lines.del2((_line *) c)) return;
  if (qobject_cast<_movie *>(c) && movies.del2((_movie *) c)) return;
  if (qobject_cast<_sound *>(c) && sounds.del2((_sound *) c)) return;
  if (qobject_cast<_web *>(c) && webs.del2((_web *) c)) return;
  if (qobject_cast<_serialport *>(c) && serialports.del2((_serialport *) c)) return;
  if (qobject_cast<_header *>(c) && headers.del2((_header *) c)) return;
  if (qobject_cast<_footer *>(c) && footers.del2((_footer *) c)) return;
  if (qobject_cast<_label *>(c) && labels.del2((_label *) c)) return;
  if (qobject_cast<_commandbutton *>(c) && commandbuttons.del2((_commandbutton *) c)) return;
  if (qobject_cast<_checkbox *>(c) && checkboxes.del2((_checkbox *) c)) return;
  if (qobject_cast<_frame *>(c) && frames.del2((_frame *) c)) return;
  if (qobject_cast<_listbox *>(c) && listboxes.del2((_listbox *) c)) return;
  if (qobject_cast<_radiobutton *>(c) && radiobuttons.del2((_radiobutton *) c)) return;
  if (qobject_cast<_textbox *>(c) && textboxes.del2((_textbox *) c)) return;
  if (qobject_cast<_progressbar *>(c) && progressbars.del2((_progressbar *) c)) return;
  if (qobject_cast<_image *>(c) && images.del2((_image *) c)) return;
  if (qobject_cast<_timer *>(c) && timers.del2((_timer *) c)) return;
  if (qobject_cast<_treeview *>(c) && treeviews.del2((_treeview *) c)) return;
  if (qobject_cast<_combobox *>(c) && comboboxes.del2((_combobox *) c)) return;
  if (qobject_cast<_box *>(c) && boxes.del2((_box *) c)) return;
  if (qobject_cast<_childcontrol *>(c) && childcontrols.del2((_childcontrol *) c)) return;
  if (qobject_cast<_editor *>(c) && editors.del2((_editor *) c)) return;
  if (qobject_cast<_browser *>(c) && browsers.del2((_browser *) c)) return;
  if (qobject_cast<_datebox *>(c) && dateboxes.del2((_datebox *) c)) return;
  if (qobject_cast<_timebox *>(c) && timeboxes.del2((_timebox *) c)) return;
  if (qobject_cast<_datetimebox *>(c) && datetimeboxes.del2((_datetimebox *) c)) return;
  if (qobject_cast<_tab *>(c) && tabs.del2((_tab *) c)) return;
  if (qobject_cast<_imagebutton *>(c) && imagebuttons.del2((_imagebutton *) c)) return;

}

#ifdef RUN
t_boolean _form::METHOD_Append(QString ControlName, QString ControlType, QString ControlGroup, t_integer X, t_integer Y, t_integer Width, t_integer Height, t_boolean Visible)
{
  _controlType ct = getControlType(ControlType);
  if (ct == t_notype) return false;
  
  if (METHOD_Control(ControlName)) return false;

  QWidget *c = 0;

  #define SWITCH4 (this, main, ControlName);
  #define SWITCH3 c
  #include "_form_property_switch.h" 
  #undef SWITCH3
  #undef SWITCH4

  c->setHidden(true);

  METHOD_insertControl(c, ct, -1, -1, false, ControlName, false);

  EXTERN_myInterpreter->kbasic_binding_setKbId(c, EXTERN_myInterpreter->getVar(me), 0, getControlType(ct));

  #define SWITCH SETPROPERTY_Group(ControlGroup);
  #include "_form_property_switch.h"     

  #define SWITCH SETPROPERTY_X(X);
  #include "_form_property_switch.h"  

  #define SWITCH SETPROPERTY_Y(Y);
  #include "_form_property_switch.h"     

  #define SWITCH SETPROPERTY_Width(Width);
  #include "_form_property_switch.h"  

  #define SWITCH SETPROPERTY_Height(Height);
  #include "_form_property_switch.h"   

  #define SWITCH SETPROPERTY_Visible(Visible);
  #include "_form_property_switch.h"     

  return true;
}
#endif

int _form::getControlType(_controlType ct)
{
#ifdef RUN
  // CONTROL
  if (ct == t_udpsocket) return pcode___udpsocket;
  if (ct == t_scrollbar) return pcode___scrollbar;
  if (ct == t_spinbox) return pcode___spinbox;
  if (ct == t_slider) return pcode___slider;
  if (ct == t_formsview) return pcode___formsview;
  if (ct == t_toolbarview) return pcode___toolbarview;
  if (ct == t_svg) return pcode___svg;
  if (ct == t_commandlinkbutton) return pcode___commandlinkbutton;
  if (ct == t_resizebox) return pcode___resizebox;
  if (ct == t_toolbutton) return pcode___toolbutton;
  if (ct == t_label) return pcode___label;
  if (ct == t_line) return pcode___line;
  if (ct == t_movie) return pcode___movie;
  if (ct == t_sound) return pcode___sound;
  if (ct == t_web) return pcode___web;
  if (ct == t_commandbutton) return pcode___commandbutton;
  if (ct == t_checkbox) return pcode___checkbox;
  if (ct == t_frame) return pcode___frame;
  if (ct == t_listbox) return pcode___listbox;
  if (ct == t_radiobutton) return pcode___radiobutton;
  if (ct == t_tab) return pcode___tab;
  if (ct == t_textbox) return pcode___textbox;
  if (ct == t_progressbar) return pcode___progressbar;
  if (ct == t_image) return pcode___image;
  if (ct == t_timer) return pcode___timer;
  if (ct == t_serialport) return pcode___serialport;
  if (ct == t_treeview) return pcode___treeview;
  if (ct == t_combobox) return pcode___combobox;
  if (ct == t_box) return pcode___box;
  if (ct == t_childcontrol) return pcode___childcontrol;
  if (ct == t_browser) return pcode___browser;
  if (ct == t_editor) return pcode___editor;
  if (ct == t_datebox) return pcode___datebox;
  if (ct == t_timebox) return pcode___timebox;
  if (ct == t_datetimebox) return pcode___datetimebox;
  if (ct == t_header) return pcode___header;
  if (ct == t_footer) return pcode___footer;
  if (ct == t_imagebutton) return pcode___imagebutton;
#endif
  return 0;
}

void _form::readdToCollection(QWidget *c, QString old, QString s, const char *acType)
{
#ifdef RUN
  switch(getControlType2(acType)){
    // CONTROL
    case pcode___udpsocket: udpsockets.readd(udpsockets.count(), old, s, (_udpsocket *) c); return;
    case pcode___scrollbar: scrollbars.readd(scrollbars.count(), old, s, (_scrollbar *) c); return;
    case pcode___spinbox: spinboxes.readd(spinboxes.count(), old, s, (_spinbox *) c); return;
    case pcode___slider: sliders.readd(sliders.count(), old, s, (_slider *) c); return;
    case pcode___formsview: formsviews.readd(formsviews.count(), old, s, (_formsview *) c); return;
    case pcode___toolbarview: toolbarviews.readd(toolbarviews.count(), old, s, (_toolbarview *) c); return;
    case pcode___svg: svgs.readd(svgs.count(), old, s, (_svg *) c); return;
    case pcode___commandlinkbutton: commandlinkbuttons.readd(commandlinkbuttons.count(), old, s, (_commandlinkbutton *) c); return;
    case pcode___resizebox: resizeboxes.readd(resizeboxes.count(), old, s, (_resizebox *) c); return;
    case pcode___toolbutton: toolbuttons.readd(toolbuttons.count(), old, s, (_toolbutton *) c); return;
    case pcode___line: lines.readd(lines.count(), old, s, (_line *) c); return;
    case pcode___textbox: textboxes.readd(textboxes.count(), old, s, (_textbox *) c); return;
    case pcode___label: labels.readd(labels.count(), old, s, (_label *) c); return;
    case pcode___movie: movies.readd(movies.count(), old, s, (_movie *) c); return;
    case pcode___sound: sounds.readd(sounds.count(), old, s, (_sound *) c); return;
    case pcode___web: webs.readd(webs.count(), old, s, (_web *) c); return;
    case pcode___commandbutton: commandbuttons.readd(commandbuttons.count(), old, s, (_commandbutton *) c); return;
    case pcode___checkbox: checkboxes.readd(checkboxes.count(), old, s, (_checkbox *) c); return;
    case pcode___frame: frames.readd(frames.count(), old, s, (_frame *) c); return;
    case pcode___listbox: listboxes.readd(listboxes.count(), old, s, (_listbox *) c); return;
    case pcode___radiobutton: radiobuttons.readd(radiobuttons.count(), old, s, (_radiobutton *) c); return;
    case pcode___tab: tabs.readd(tabs.count(), old, s, (_tab *) c); return;
    case pcode___progressbar: progressbars.readd(progressbars.count(), old, s, (_progressbar *) c); return;
    case pcode___image: images.readd(images.count(), old, s, (_image *) c); return;
    case pcode___timer: timers.readd(timers.count(), old, s, (_timer *) c); return;
    case pcode___serialport: serialports.readd(serialports.count(), old, s, (_serialport *) c); return;
    case pcode___treeview: treeviews.readd(treeviews.count(), old, s, (_treeview *) c); return;
    case pcode___combobox: comboboxes.readd(comboboxes.count(), old, s, (_combobox *) c); return;
    case pcode___box: boxes.readd(boxes.count(), old, s, (_box *) c); return;
    case pcode___childcontrol: childcontrols.readd(childcontrols.count(), old, s, (_childcontrol *) c); return;
    case pcode___browser: browsers.readd(browsers.count(), old, s, (_browser *) c); return;
    case pcode___editor: editors.readd(editors.count(), old, s, (_editor *) c); return;
    case pcode___datebox: dateboxes.readd(dateboxes.count(), old, s, (_datebox *) c); return;
    case pcode___timebox: timeboxes.readd(timeboxes.count(), old, s, (_timebox *) c); return;
    case pcode___datetimebox: datetimeboxes.readd(datetimeboxes.count(), old, s, (_datetimebox *) c); return;
    case pcode___header: headers.readd(headers.count(), old, s, (_header *) c); return;
    case pcode___footer: footers.readd(footers.count(), old, s, (_footer *) c); return;
    case pcode___imagebutton: imagebuttons.readd(imagebuttons.count(), old, s, (_imagebutton *) c); return;
  }
#endif
}

void _form::addToCollection(QWidget *c, QString s, int nType)
{
#ifdef RUN
  switch(nType){
    // CONTROL
    case pcode___udpsocket: udpsockets.add(udpsockets.count(), s, (_udpsocket *) c); return;
    case pcode___scrollbar: scrollbars.add(scrollbars.count(), s, (_scrollbar *) c); return;
    case pcode___spinbox: spinboxes.add(spinboxes.count(), s, (_spinbox *) c); return;
    case pcode___slider: sliders.add(sliders.count(), s, (_slider *) c); return;
    case pcode___formsview: formsviews.add(formsviews.count(), s, (_formsview *) c); return;
    case pcode___toolbarview: toolbarviews.add(toolbarviews.count(), s, (_toolbarview *) c); return;
    case pcode___svg: svgs.add(svgs.count(), s, (_svg *) c); return;
    case pcode___commandlinkbutton: commandlinkbuttons.add(commandlinkbuttons.count(), s, (_commandlinkbutton *) c); return;
    case pcode___resizebox: resizeboxes.add(resizeboxes.count(), s, (_resizebox *) c); return;
    case pcode___toolbutton: toolbuttons.add(toolbuttons.count(), s, (_toolbutton *) c); return;
    case pcode___line: lines.add(lines.count(), s, (_line *) c); return;
    case pcode___textbox: textboxes.add(textboxes.count(), s, (_textbox *) c); return;
    case pcode___label: labels.add(labels.count(), s, (_label *) c); return;
    case pcode___movie: movies.add(movies.count(), s, (_movie *) c); return;
    case pcode___sound: sounds.add(sounds.count(), s, (_sound *) c); return;
    case pcode___web: webs.add(webs.count(), s, (_web *) c); return;
    case pcode___commandbutton: commandbuttons.add(commandbuttons.count(), s, (_commandbutton *) c); return;
    case pcode___checkbox: checkboxes.add(checkboxes.count(), s, (_checkbox *) c); return;
    case pcode___frame: frames.add(frames.count(), s, (_frame *) c); return;
    case pcode___listbox: listboxes.add(listboxes.count(), s, (_listbox *) c); return;
    case pcode___radiobutton: radiobuttons.add(radiobuttons.count(), s, (_radiobutton *) c); return;
    case pcode___tab: tabs.add(tabs.count(), s, (_tab *) c); return;
    case pcode___progressbar: progressbars.add(progressbars.count(), s, (_progressbar *) c); return;
    case pcode___image: images.add(images.count(), s, (_image *) c); return;
    case pcode___timer: timers.add(timers.count(), s, (_timer *) c); return;
    case pcode___serialport: serialports.add(serialports.count(), s, (_serialport *) c); return;
    case pcode___treeview: treeviews.add(treeviews.count(), s, (_treeview *) c); return;
    case pcode___combobox: comboboxes.add(comboboxes.count(), s, (_combobox *) c); return;
    case pcode___box: boxes.add(boxes.count(), s, (_box *) c); return;
    case pcode___childcontrol: childcontrols.add(childcontrols.count(), s, (_childcontrol *) c); return;
    case pcode___browser: browsers.add(browsers.count(), s, (_browser *) c); return;
    case pcode___editor: editors.add(editors.count(), s, (_editor *) c); return;
    case pcode___datebox: dateboxes.add(dateboxes.count(), s, (_datebox *) c); return;
    case pcode___timebox: timeboxes.add(timeboxes.count(), s, (_timebox *) c); return;
    case pcode___datetimebox: datetimeboxes.add(datetimeboxes.count(), s, (_datetimebox *) c); return;
    case pcode___header: headers.add(headers.count(), s, (_header *) c); return;
    case pcode___footer: footers.add(footers.count(), s, (_footer *) c); return;
    case pcode___imagebutton: imagebuttons.add(imagebuttons.count(), s, (_imagebutton *) c); return;
  }
#endif
}


#ifdef IDE
void _form::newUndoRedo(bool bIgnoreBlocking, bool bFormMoveOnly, bool bFormResizeOnly, bool bLastAppend)
{
  if (bLoading) return;
  if (bLoaded == false) return;
  
  if ((bFormMoveOnly == false && bFormResizeOnly == false) && bIgnoreBlocking == false && bPerformUndoRedo) return;

  if (bUndoRedoSaveLast == false){
    bUndoRedoSaveLast = true;
  }

  bool bAppend = true;

  QWidget *c;  

  undoRedoControls controls;

  // save form properties
  {
    t_properties2 ap2;
    t_properties2 ap3;

    if (bFormMoveOnly == false && bFormResizeOnly == false){

      t_properties *ap;

      ap = getProperties();

      t_properties::Iterator it;
      for ( it = ap->begin(); it != ap->end(); ++it){
        QString k = it.key();
        t_property *d = *it;
        t_property p = t_property(d);
        ap2.insert(k, p);
      }

      controls.append(ap2);
      controls.append(ap3);

    } else {
       t_property p;

       p.propertyType = pt_integer;
       p.display = true;
       p.used = true;
       p.set = true;

       //if (bFormMoveOnly){
         p.v_integer = GETPROPERTY_X(); ap2.insert("X", p);
         p.v_integer = GETPROPERTY_Y(); ap2.insert("Y", p);
       //} else if (bFormResizeOnly){
         p.v_integer = GETPROPERTY_Width(); ap2.insert("Width", p);
         p.v_integer = GETPROPERTY_Height(); ap2.insert("Height", p);
       //}

       p.propertyType = pt_qstring;
       p.v_qstring = GETPROPERTY_Name(); 
       ap2.insert("Name", p);

       bool bClear = (bFormMoveOnly && bUndoRedoLastNewFormMove) || (bFormResizeOnly && bUndoRedoLastNewFormResize);

       if (nUndoRedo >= 0 && bClear){ // contains only form properties
   
         controls = undoRedoStacks[nUndoRedo];


         /*
         foreach(t_properties2 ppp, controls){
           if (bFormMoveOnly){
             int nn = ppp["Width"].v_integer;
             if (ppp["Width"].v_integer != GETPROPERTY_Width() || ppp["Height"].v_integer != GETPROPERTY_Height()){
               bClear = false;
             }
           } else if (bFormResizeOnly){
             if (ppp["X"].v_integer != GETPROPERTY_X() || ppp["Y"].v_integer != GETPROPERTY_Y()){
               bClear = false;
             }
           }
         }
*/
//         if (bClear){
           controls.clear();
        // }
         controls.append(ap2);
         //controls.append(ap3);

         //if (bClear){
           bAppend = bLastAppend;
         //}
         
       } else {
         controls.append(ap2);
         //controls.append(ap3);
       }
    }

  }

  // * save control properties

  if (bFormMoveOnly == false && bFormResizeOnly == false){

    if (firstControl(&c, 11)){    

      do {
        
        t_properties *ap;

        #define SWITCH getProperties();      
        #define SWITCH3 ap
        #include "_form_property_switch.h"   
        #undef SWITCH3

        t_properties2 ap2;

        t_properties::Iterator it;
        for ( it = ap->begin(); it != ap->end(); ++it){
          QString k = it.key();
          t_property *d = *it;
          t_property p = t_property(d);

          ap2.insert(k, p);
        }
        controls.append(ap2);
        

        //c->acceptDrops(); // missused as selected flag
              
      } while (nextControl(&c, 11)); 

    }
  }

  if (bAppend){
    int nSize = undoRedoStacks.size();
    if (nUndoRedo + 1 < nSize){
      undoRedoStacks.remove(nUndoRedo + 1, nSize - (nUndoRedo + 1));
    }

    undoRedoStacks.append(controls);
    nUndoRedo++;
  }
  if (bAppend){
    EXTERN_my_mainwindow->EDIT_REDO->setEnabled(this->hasRedo());
    EXTERN_my_mainwindow->EDIT_UNDO->setEnabled(this->hasUndo());    
  }

  bUndoRedoLastNewFormMove = bFormMoveOnly;
  bUndoRedoLastNewFormResize = bFormResizeOnly;

  //EXTERN_my_mainwindow->setWindowTitle(QString("size=%1 nUndoRedo=%2").arg(undoRedoStacks.size()).arg(nUndoRedo));


}

void _form::performUndoRedo(bool bRedo)
{
QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    _controlType SAVE = insertType;    

    int nn = undoRedoStacks.size();

    bool bDec = true;
    if (bLastWasUndo && bRedo){
      nUndoRedo++;
    } else if (bLastWasUndo == false && bRedo == false){
      if (nUndoRedo > 0) nUndoRedo--;
    }
    if (bRedo){
      bDec = false;
      nUndoRedo++;
      if (nUndoRedo == 0/* && bLastWasUndo*/) nUndoRedo++;
    } else if (nUndoRedo + 1 == undoRedoStacks.size() && bLastWasUndo == false){
      if (nUndoRedo > 0) nUndoRedo--;
    }
    
    if (nUndoRedo == -1) nUndoRedo = 0;

    undoRedoControls controls = undoRedoStacks[nUndoRedo];

    int nSize = controls.size();
    if (nSize > 2){ // contains not only form properties

      QWidget *c;
  re:
      if (firstControl(&c)){
         do {              
            c->hide();
            c->setAcceptDrops(false); // missused as selected flag
            deleteControl(c);
            // delete c;     
            goto re;
         } while (nextControl(&c));
      }
    }



    foreach(t_properties2 p, controls){

      QString sControlType = p["ControlType"].v_qstring;

      // CONTROL
      if (sControlType == "TextBox") setInsertControlType(t_textbox);       
      else if (sControlType == "UdpSocket") setInsertControlType(t_udpsocket); 
      else if (sControlType == "ScrollBar") setInsertControlType(t_scrollbar); 
      else if (sControlType == "SpinBox") setInsertControlType(t_spinbox); 
      else if (sControlType == "Slider") setInsertControlType(t_slider); 
      else if (sControlType == "FormsView") setInsertControlType(t_formsview); 
      else if (sControlType == "ToolBarView") setInsertControlType(t_toolbarview); 
      else if (sControlType == "SvgBox") setInsertControlType(t_svg); 
      else if (sControlType == "CommandLinkButton") setInsertControlType(t_commandlinkbutton); 
      else if (sControlType == "ResizeBox") setInsertControlType(t_resizebox); 
      else if (sControlType == "ToolButton") setInsertControlType(t_toolbutton); 
      else if (sControlType == "Line") setInsertControlType(t_line); 
      else if (sControlType == "Label") setInsertControlType(t_label); 
      else if (sControlType == "MovieBox") setInsertControlType(t_movie); 
      else if (sControlType == "Sound") setInsertControlType(t_sound); 
      else if (sControlType == "WebView") setInsertControlType(t_web); 
      else if (sControlType == "SerialPort") setInsertControlType(t_serialport); 
      else if (sControlType == "Header") setInsertControlType(t_header); 
      else if (sControlType == "Footer") setInsertControlType(t_footer); 
      else if (sControlType == "Box") setInsertControlType(t_box); 
      else if (sControlType == "CommandButton") setInsertControlType(t_commandbutton); 
      else if (sControlType == "CheckBox") setInsertControlType(t_checkbox); 
      else if (sControlType == "Frame") setInsertControlType(t_frame); 
      else if (sControlType == "ListBox") setInsertControlType(t_listbox); 
      else if (sControlType == "RadioButton") setInsertControlType(t_radiobutton); 
      else if (sControlType == "TabView") setInsertControlType(t_tab); 
      else if (sControlType == "ProgressBar") setInsertControlType(t_progressbar); 
      else if (sControlType == "ImageBox") setInsertControlType(t_image); 
      else if (sControlType == "Timer") setInsertControlType(t_timer); 
      else if (sControlType == "TreeView") setInsertControlType(t_treeview); 
      else if (sControlType == "ComboBox") setInsertControlType(t_combobox); 
      else if (sControlType == "FormView") setInsertControlType(t_childcontrol); 
      else if (sControlType == "HtmlView") setInsertControlType(t_browser); 
      else if (sControlType == "RichTextBox") setInsertControlType(t_editor); 
      else if (sControlType == "DateBox") setInsertControlType(t_datebox); 
      else if (sControlType == "TimeBox") setInsertControlType(t_timebox); 
      else if (sControlType == "DateTimeBox") setInsertControlType(t_datetimebox); 
      else if (sControlType == "ImageButton") setInsertControlType(t_imagebutton); 
      
      QWidget *c;
      QString kk = p["Name"].v_qstring;
      if (p["Name"].v_qstring != this->GETPROPERTY_Name()){
        insertControl(p["X"].v_integer, p["Y"].v_integer, false, p["Width"].v_integer, p["Height"].v_integer);
        QWidget *c = cInsertControl;
      
        t_properties2::Iterator it;
        for ( it = p.begin(); it != p.end(); ++it ){

          QString s = it.key();

          if (s.compare("ControlType", Qt::CaseInsensitive) == 0) continue;

          t_property d1;
          d1 = *it;

          switch(d1.propertyType){
            case pt_integer:
              applyProperty(c, s, d1.v_boolean, d1.v_qstring, d1.v_integer, d1.v_double);
              break;           
            case pt_boolean:
              applyProperty(c, s, d1.v_boolean, d1.v_qstring, d1.v_integer, d1.v_double);
              break;
            case pt_qstring:
              {
              if (!d1.v_qstring.isEmpty()) applyProperty(c, s, d1.v_boolean, d1.v_qstring, d1.v_integer, d1.v_double);
              break;
              }
         }
        }
      } else {
        //if (p.contains("X")){
          this->SETPROPERTY_X(p["X"].v_integer, false);
          this->SETPROPERTY_Y(p["Y"].v_integer, false);
       // } else {
          this->SETPROPERTY_Width(p["Width"].v_integer, true);
          this->SETPROPERTY_Height(p["Height"].v_integer, true);
      //  }
      }

    }

    insertType = SAVE;
    
    unselectAllControls();
    updatePropertyWindow();
    if (bDec){
      nUndoRedo--; 
      //if (bRedo) nUndoRedo++; else nUndoRedo--; 
    }
    EXTERN_my_mainwindow->EDIT_REDO->setEnabled(this->hasRedo());
    EXTERN_my_mainwindow->EDIT_UNDO->setEnabled(this->hasUndo());    

    
	 QApplication::restoreOverrideCursor();   

    //EXTERN_my_mainwindow->setWindowTitle(QString("size=%1 nUndoRedo=%2").arg(undoRedoStacks.size()).arg(nUndoRedo));

  
}

void _form::performUndo()
{
QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  if (hasUndo()){
    bPerformUndoRedo = true;

    int nOldUndoRedo = nUndoRedo;

    undoRedoControls controls;
    if (nUndoRedo >= 0) controls = undoRedoStacks[nUndoRedo];

    bool bDec = false;
    bool bForm = true;
    
    int nSize = controls.size();
    if (controls.size() > 2){ // contains not only form properties
      bForm = false;
    }
      
      int nn = undoRedoStacks.size();

      
      if (bUndoRedoSaveLast == true && nUndoRedo + 1 == undoRedoStacks.size()){
        newUndoRedo(true, bForm, false, true);
        nUndoRedo--;
        bUndoRedoSaveLast = false;
        bDec = true;
      }
   // } else {
      
   // }

    if (bDec && bForm == false && nOldUndoRedo > 1) nUndoRedo--;

    performUndoRedo(false);    
    bLastWasUndo = nUndoRedo > 0;

    bPerformUndoRedo = false;

    if (bDec && bForm && nOldUndoRedo > 1) nUndoRedo--;
  }
   QApplication::restoreOverrideCursor();   

}

void _form::performRedo()
{
  if (hasRedo()){
    bPerformUndoRedo = true;
    performUndoRedo(true);    
    bLastWasUndo = false;
    bPerformUndoRedo = false;
  }
}

#endif


#ifdef RUN
t_boolean _form::METHOD_Remove(QString ControlName)
{
  _control *o = METHOD_Control(ControlName);
  if (o == 0) return false;

  QWidget *c = (QWidget *) o;
  //c->hide();

  _controlType ct = controlType(c);

  deleteControl(c);
/*
  ((kb_textbox *) c)->close();
  delete ((kb_textbox *) c);
*/
  
  c->close();

  #undef SWITCH6
  #define SWITCH6 ct

  #define SWITCH METHOD_Close();
  #include "_form_property_switch.h"     

  #define SWITCH6 controlType(c)


  return true;
}
#endif
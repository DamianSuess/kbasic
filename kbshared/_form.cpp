/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#include <QtGui>

#include "_form.h"
#include "_report.h"



#ifdef IDE
bool bcheckFrameMinSize = false;

#include <QtSql>
extern QSqlDatabase CurrentDatabase;

#include "../kbide/_help.h"
#include "../kbide/_qbe_tables.h"

QWidget *cInsertControl = 0;

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

int nInsert_Width = 0;
int nInsert_Height = 0;

extern _parserwindow *EXTERN_my_parserwindow;

extern _propertywindow *EXTERN_my_propertywindow;
extern _toolboxwindow_form *EXTERN_my_toolboxwindow_form;
extern _toolboxwindow_vista *EXTERN_my_toolboxwindow_vista;
extern const QIcon &kbasicIcon(QString s);

extern QMdiArea *forms_workspace;

extern int nPropertyWindowForWhat;
#endif


_form *EXTERN_my_form;
#ifdef IDE


QString sInsertTypeOption;

QList<QWidget *>cCut;
QList<QWidget *>cPasted;
QList<t_properties *>apply_properties;


int nCutMinX = 999999;
int nCutMinY = 999999;

bool bApply = false;
bool bCopy = false;
bool bCut = false;
_form *cutForm = 0;
extern QDockWidget *EXTERN_PropertyWindow;

extern _report *EXTERN_my_report;

extern QString idePath(QString s);
extern _projectwindow *EXTERN_my_projectwindow;
#else

#endif



#ifdef RUN
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

QWidget *ControlFocusPrevious = 0;

#endif

QWidget *min = 0;


_form::_form(_mainwindow *_my_mainwindow)
{
  constructor(_my_mainwindow);
}

_form::_form(_mainwindow *_my_mainwindow, QString sObjectName)
{
  constructor(_my_mainwindow, sObjectName);
}



void _form::constructor(_mainwindow *_my_mainwindow, QString _sObjectName) 
{
  setAttribute(Qt::WA_DeleteOnClose);

  
  bLoaded = false;

#ifdef IDE
  XScrollBar = 0;
  YScrollBar = 0;
  main = this;
#endif


#ifdef RUN
  nFormId = 0;

  connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(XScrollBar_valueChanged(int)));
  connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(YScrollBar_valueChanged(int)));

  main = new _main(this);

  this->setFrameShadow(QFrame::Plain);  
  this->setFrameShape(QFrame::NoFrame);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 

  this->setWidget(main);
 

  bIsFilterActive = false;
  bResizeEventFlag = true;
  dock = 0;

  nWasMaximized = 0;
  setProperty("MdiSubWindow", 0);
  setProperty("DockWidget", 0);

  bFullscreen = false;

  nSingleShot = 0;
  nOldCurrentMultiPage = 1;
  nCurrentMultiPage = 1;
  bQuerySize = false;
  nQuerySize = 0;


  bOpened = false;
  bMETHOD_Open_Opened = false;
  bBlockOnceOpenModal = false;

  ParentForm = 0;



  bOnGoTo3First = true;
  bOnGoTo3Children = false;

  sName = "";
  sGroup = "";
  acName = "Form";
  acGroup = "";

  bTableView = false;

  bFirstResize = true;
  bFirstDockResize = true;

  bDialogRunning = false;
  

#endif


#ifdef IDE
  
  bUndoRedoLastNewFormMove = false;
  bUndoRedoLastNewFormResize = false;
  bPerformUndoRedo = false;
  bLastWasUndo = true;
  bUndoRedoSaveLast = false;
  bLoading = false;

  nUndoRedo = -1;

  bObjectEditor = false;
  bShowFocusOrder = false;
  bShowSQLSettings = false;
  bShowSQLTables = false;

  


  bModified = false;
  
  
#endif

  EXTERN_my_form = this;

#ifdef IDE
  EXTERN_my_report = (_report *) EXTERN_my_form;
#endif


  nTimerId = 0;
  nTimerIdMove = 0;
  nTimerIdResize = 0;




  nOldMouseX = -1;
  nOldMouseY = -1;

#ifdef IDE
  setMouseTracking(true); // For a widget to get mouse move events when no button is depressed, it must do so
#endif


  sObjectName = _sObjectName;
  bObjectEditor = sObjectName.length() > 0 && sObjectName != "Report";

  form_parent = 0;  
#ifdef IDE
#else
  bDirty = false;
  bAddNew = false;
  my_form = this;
#endif


  bool bForm = sObjectName != "Report";

#ifdef IDE
  if (bForm){
    QString k = EXTERN_my_mainwindow->getProjectPath() + "/application.qss";
    if (QFile::exists(k)){
      QString s = "";

      QFile f(k);
      if (!f.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(k));
      } else {
        QTextStream t(&f);
        s = t.readAll();
        s = s.replace("\r", "");
        f.close();
      }

      setStyleSheet(s);
    }
  }
#endif

  {

  // PROPERTY of form only
  addProperty("Name", pt_qstring);
  addProperty("ControlType", pt_qstring);
  addProperty("X", pt_integer);
  addProperty("Y", pt_integer);
  addProperty("Width", pt_integer);
  addProperty("Height", pt_integer);

  addProperty("LoadedX", pt_integer);
  addProperty("LoadedY", pt_integer);
  addProperty("LoadedWidth", pt_integer);
  addProperty("LoadedHeight", pt_integer);

  addProperty("OldX", pt_integer);
  addProperty("GlobalX", pt_integer);
  addProperty("OldY", pt_integer);
  addProperty("GlobalY", pt_integer);
  addProperty("OldWidth", pt_integer);
  addProperty("OldHeight", pt_integer);


  addProperty("BorderTop", pt_integer);
  addProperty("BorderBottom", pt_integer);
  addProperty("BorderLeft", pt_integer);
  addProperty("BorderRight", pt_integer);

  if (bForm){

    addProperty("DockTitleVisible", pt_boolean);
    addProperty("DockParent", pt_qstring);
    addProperty("DockWidth", pt_integer);
    addProperty("DockHeight", pt_integer);

    addProperty("TimerInterval", pt_integer);

    addProperty("Mask", pt_qstring);
    addProperty("MoveOnMouseDrag", pt_boolean);

    addProperty("MouseTracking", pt_boolean);
    SETPROPERTY_MouseTracking(true);

    addProperty("DrawOnPaint", pt_boolean);
    SETPROPERTY_DrawOnPaint(true);

    addProperty("StopOnClose", pt_boolean);
    addProperty("OpenOnRun", pt_boolean);
    
    addProperty("ScrollBar", pt_qstring);
    addProperty("Dock", pt_qstring);

    addProperty("ScrollX", pt_integer);
    addProperty("ScrollY", pt_integer);
    addProperty("ScrollWidth", pt_integer);
    addProperty("ScrollHeight", pt_integer);

    addProperty("MultiPageHeight", pt_integer);
    addProperty("MultiPageBorderLeft", pt_integer);
    addProperty("MultiPageBorderRight", pt_integer);
    addProperty("MultiPageBorderTop", pt_integer);
    addProperty("MultiPageBorderBottom", pt_integer);

    addProperty("MinimumWidth", pt_integer);
    addProperty("MinimumHeight", pt_integer);
    addProperty("MaximumWidth", pt_integer);
    addProperty("MaximumHeight", pt_integer);
    addProperty("DragDrop", pt_boolean);
    addProperty("FocusPolicy", pt_qstring);
    addProperty("FocusProxy", pt_qstring);
    addProperty("FocusOrder", pt_integer);

    addProperty("Cursor", pt_qstring);
    addProperty("CursorAnimation", pt_qstring);
    
    

    addProperty("StatusTip", pt_qstring);
    addProperty("ToolTip", pt_qstring);
    addProperty("StyleSheet", pt_qstring);
    addProperty("WhatsThis", pt_qstring);

    addProperty("TableView", pt_boolean);
    addProperty("Resizable", pt_boolean);
    SETPROPERTY_Resizable(true);

    addProperty("DockSplit", pt_qstring);
    addProperty("ShowMode", pt_qstring);

    addProperty("FormFileName", pt_qstring);
    addProperty("FormModified", pt_boolean);
    addProperty("FormX", pt_integer);
    addProperty("FormY", pt_integer);
    addProperty("FormWidth", pt_integer);
    addProperty("FormHeight", pt_integer);

    addProperty("ResizableSmaller", pt_boolean);
    addProperty("ResizableBigger", pt_boolean);   

    addProperty("Flag", pt_qstring);
    addProperty("Icon", pt_qstring);

    addProperty("Caption", pt_qstring);

    addProperty("Modal", pt_boolean);
    addProperty("Opacity", pt_integer);  
    
    addProperty("Background", pt_qstring);
    addProperty("FontColor", pt_qstring);

  }

  

  addProperty("Tag", pt_qstring);
  addProperty("SQLName", pt_qstring);
  if (bForm){
    addProperty("SQLRelation", pt_qstring);
    addProperty("SQLControls", pt_qstring);
 
    addProperty("SQLInsert", pt_boolean);
    addProperty("SQLUpdate", pt_boolean);
    addProperty("SQLDelete", pt_boolean);

    SETPROPERTY_SQLInsert(true);
    SETPROPERTY_SQLUpdate(true);
    SETPROPERTY_SQLDelete(true);


    addProperty("Visible", pt_boolean);
#ifdef IDE
    SETPROPERTY_Visible(true);
#endif

    addProperty("ParentForm", pt_qstring);
    addProperty("ParentControl", pt_qstring);
  }  
  



  
  // events

  if (bForm){
    addProperty("OnOpen", pt_event);
    addProperty("OnClose", pt_event);

    addProperty("OnDragEnter", pt_event);
    addProperty("OnDragMove", pt_event);
    addProperty("OnDragExit", pt_event);
    addProperty("OnDrop", pt_event);

    addProperty("OnDockMove", pt_event);
    addProperty("OnDockShow", pt_event);
    addProperty("OnDockHide", pt_event);
    addProperty("OnDockFloating", pt_event);
    addProperty("OnDockNotFloating", pt_event);
    
    addProperty("OnScroll", pt_event);
    addProperty("OnMultiPageShow", pt_event);
    addProperty("OnDirty", pt_event);
    addProperty("OnAddNew", pt_event);
    addProperty("OnQuery", pt_event);

    addProperty("OnGoTo", pt_event);
    addProperty("OnBeforeInsert", pt_event);
    addProperty("OnBeforeDelete", pt_event);
    addProperty("OnBeforeUpdate", pt_event);
    addProperty("OnTimer", pt_event);
    

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
    addProperty("OnPaint", pt_event);
    addProperty("OnMove", pt_event);
    addProperty("OnResize", pt_event);
  }
  SETPROPERTY_DockTitleVisible(true);  

  }

  // ***

#ifdef IDE
  resize(500, 400);

  setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_FORM.png")));


  setAcceptDrops(true); // missused as flag


  selector1 = new QFrame(this); selector1->setFrameShape(QFrame::Box); selector1->setFrameShadow(QFrame::Raised);
  
  QPalette p = selector1->palette();          
  p.setColor(QPalette::Dark, QColor(0, 0, 0, 100));         
  p.setColor(QPalette::Light, QColor(255, 255, 255, 155));         
  selector1->setPalette(p);

  selector1->setLineWidth(2);


    updateCaption("");
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    if (bObjectEditor){
    
    } else {
     
    }

    
  

  #endif


#ifdef IDE
  selector1->setHidden(true);


  insertType = t_notype;
  sInsertTypeOption = "";
#endif

  bMousePressed = false;
  bMouseMove = false;
  bControlMove = false;  
  bDoubleClick = false;  

  bCTRL = false;
  bSHIFT = false;
  bSelector = false;  

  
#ifdef IDE
    setFormSelf();


#endif


       
    movie = 0; moviea = 0; movieb = 0;
    cursoranimation_movie = 0; cursoranimation_moviea = 0; cursoranimation_movieb = 0;

}


_form::~_form()
{
  if (movie) delete movie; if (moviea) delete moviea; if (movieb) delete movieb;
  if (cursoranimation_movie) delete cursoranimation_movie; if (cursoranimation_moviea) delete cursoranimation_moviea; if (cursoranimation_movieb) delete cursoranimation_movieb;
}



void  _form::paintEvent( QPaintEvent *e )
{

#ifdef IDE  

  QWidget::paintEvent(e);
  QPainter p( this );

    QRect r = e->rect();
    int nScrollX = GETPROPERTY_ScrollX();
    int nScrollY = GETPROPERTY_ScrollY();

    for (int y = 0; y < r.bottom() + 11 + nScrollY; y += 10){
      for (int x = 0; x < r.right() + 11 + nScrollX; x += 10){
       if (y % 20 && !(x % 20)){
         p.setPen(Qt::gray);
       } else {
         p.setPen(Qt::black);
       }
       p.drawPoint(x - nScrollX, y - nScrollY);
      }
    }


    {
      int nMultiPageHeight = GETPROPERTY_MultiPageHeight();
      int nMultiPageBorderTop = GETPROPERTY_MultiPageBorderTop();
      int nMultiPageBorderBottom = GETPROPERTY_MultiPageBorderBottom();
      int nMultiPageBorderLeft = GETPROPERTY_MultiPageBorderLeft();
      int nMultiPageBorderRight = GETPROPERTY_MultiPageBorderRight();

      if (nMultiPageHeight){        
        for (int y = 0; y < height() / nMultiPageHeight; y++){
          p.setPen(Qt::red);
          if (y) p.drawLine(0, y * nMultiPageHeight, width(), y * nMultiPageHeight);

          p.setPen(Qt::blue);

          {
            if (nMultiPageBorderTop) p.drawLine(0, y * nMultiPageHeight + nMultiPageBorderTop, width(), y * nMultiPageHeight + nMultiPageBorderTop);
            if (nMultiPageBorderBottom) p.drawLine(0, (y + 1) * nMultiPageHeight - nMultiPageBorderBottom, width(), (y + 1) * nMultiPageHeight - nMultiPageBorderBottom);
            if (nMultiPageBorderLeft) p.drawLine(nMultiPageBorderLeft, 0, nMultiPageBorderLeft, height());
            if (nMultiPageBorderRight) p.drawLine(width() - nMultiPageBorderRight, 0, width() - nMultiPageBorderRight, height());
          }

          p.drawText(0, y * nMultiPageHeight + 20, QString(tr("Page %1")).arg(y + 1));

        }


      }

      int nBorderTop = GETPROPERTY_BorderTop();
      int nBorderBottom = height() - GETPROPERTY_BorderBottom();
      int nBorderLeft = GETPROPERTY_BorderLeft();
      int nBorderRight = GETPROPERTY_BorderRight();

      p.setPen(Qt::white);
      if (nBorderLeft) p.drawLine(nBorderLeft + 1, nBorderTop, nBorderLeft + 1, nBorderBottom);
      if (GETPROPERTY_BorderRight()) p.drawLine(width() - nBorderRight + 1, nBorderTop, width() - nBorderRight + 1, nBorderBottom);

      p.setPen(Qt::black);
      if (nBorderTop) p.drawLine(nBorderLeft, nBorderTop, width() - nBorderRight, nBorderTop);
      if (GETPROPERTY_BorderBottom()) p.drawLine(nBorderLeft, nBorderBottom, width() - nBorderRight, nBorderBottom);

      if (this->isForm()){
        p.setPen(Qt::black);

        int k = GETPROPERTY_BorderBottom();
        if (k == 0 && !this->GETPROPERTY_SQLName().isEmpty()){
          k = height();
        }
        if (k) p.drawLine(nBorderLeft, k - 20, width() - nBorderRight, k - 20);
      }

      p.setPen(Qt::white);
      if (nBorderTop) p.drawLine(nBorderLeft, nBorderTop + 1, width() - nBorderRight, nBorderTop + 1);
      if (GETPROPERTY_BorderBottom()) p.drawLine(nBorderLeft, nBorderBottom + 1, width() - nBorderRight, nBorderBottom + 1);

      p.setPen(Qt::black);
      if (nBorderLeft) p.drawLine(nBorderLeft, nBorderTop, nBorderLeft, nBorderBottom);
      if (GETPROPERTY_BorderRight()) p.drawLine(width() - nBorderRight, nBorderTop, width() - nBorderRight, nBorderBottom);

    }
  

#elif defined(RUN)

#endif
 
}


const char *controlTypeName(_controlType ct)
{
  // CONTROL
  switch (ct){
    case t_notype:
      return "notype";

    case t_udpsocket: return "UdpSocket";
    case t_scrollbar: return "ScrollBar";
    case t_spinbox: return "SpinBox";
    case t_slider: return "Slider";
    case t_formsview: return "FormsView";
    case t_toolbarview: return "ToolBarView";
    case t_svg: return "SvgBox";
    case t_commandlinkbutton: return "CommandLinkButton";
    case t_resizebox: return "ResizeBox";
    case t_toolbutton: return "ToolButton";
    case t_line: return "Line";
    case t_movie: return "MovieBox";
    case t_sound: return "Sound";
    case t_web: return "WebView";

    case t_serialport:
      return "SerialPort";
    case t_header:
      return "Header";
    case t_footer:
      return "Footer";
    case t_label:
      return "Label";
    case t_commandbutton:
      return "CommandButton";
    case t_checkbox:
      return "CheckBox";
    case t_frame:
      return "Frame";
    case t_listbox:
      return "ListBox";
    case t_radiobutton:
      return "RadioButton";
    case t_tab:
      return "TabView";
    case t_textbox:
      return "TextBox";
    case t_progressbar:
      return "ProgressBar";

    case t_image:
      return "ImageBox";
    case t_timer:
      return "Timer";
    case t_treeview:
      return "TreeView";
    case t_combobox:
      return "ComboBox";
    case t_imagebutton:
      return "ImageButton";

    case t_hidden:
      return "Hidden";
    case t_vbox:
      return "VBox";
    case t_hbox:
      return "HBox";
    case t_vhbox:
      return "VHBox";
    case t_vsplit:
      return "VSplit";
    case t_hsplit:
      return "HSplit";

    case t_box: return "Box";
    case t_childcontrol: return "FormView";
    case t_editor: return "RichTextBox";
    case t_browser: return "HtmlView";
    case t_datebox: return "DateBox";
    case t_timebox: return "TimeBox";
    case t_datetimebox: return "DateTimeBox";

  }
  return "";
}

#ifdef IDE
void _form::addTable(QString s)
{  

  if (!CurrentDatabase.isOpen()){
    QMessageBox::information(this, MYAPP, "You are not connected to a database.");  

    return;
  }

  _controlType t = insertType;

  QSqlRecord r = CurrentDatabase.record(s);
  {
    int x = 120;
    int y = 10;

    for (int i = 0; i < r.count(); i++){

      EXTERN_my_mainwindow->processGUI();
      unselectAllControls();

      QSqlField f = r.field(i);

      QString sControlType = "";

      switch(f.type()){
        case QVariant::Bool:
          sControlType = "CheckBox";
          setInsertControlType(t_checkbox); 
          break;
        case QVariant::Date: 
          sControlType = "DateBox";
          setInsertControlType(t_datebox); 
          break;
        case QVariant::Time: 
          sControlType = "TimeBox";
          setInsertControlType(t_timebox); 
          break;
        case QVariant::Double:
          sControlType = "TextBox";
          setInsertControlType(t_textbox); 
          break;
        case QVariant::UInt:
        case QVariant::ULongLong:
        case QVariant::LongLong:
        case QVariant::Int:
          sControlType = "TextBox";
          setInsertControlType(t_textbox); 
          break;
        case QVariant::String: 
          sControlType = "TextBox";
          setInsertControlType(t_textbox); 
          break;
        default:
          sControlType = "Label";
          setInsertControlType(t_textbox); 
          break;
      }
      insertControl(x, y, false);

      QWidget *c = 0;
      if (firstControl(&c)){
        do {
          if (c->acceptDrops()){ // missused as selected flag
            break;
          }
        } while (nextControl(&c));
      }

      if (sControlType == "Label"){
        ((_label *) c)->SETPROPERTY_SQLName(f.name());
        ((_label *) c)->SETPROPERTY_FocusOrder(i + 1);
      } else if (sControlType == "TextBox"){
        ((_textbox *) c)->SETPROPERTY_SQLName(f.name());
        ((_textbox *) c)->SETPROPERTY_FocusOrder(i + 1);
      } else if (sControlType == "TimeBox"){
        ((_timebox *) c)->SETPROPERTY_SQLName(f.name());
        ((_timebox *) c)->SETPROPERTY_FocusOrder(i + 1);
      } else if (sControlType == "DateBox"){
        ((_datebox *) c)->SETPROPERTY_SQLName(f.name());
        ((_datebox *) c)->SETPROPERTY_FocusOrder(i + 1);
      } else if (sControlType == "CheckBox"){
        ((_checkbox *) c)->SETPROPERTY_SQLName(f.name());
        ((_checkbox *) c)->SETPROPERTY_FocusOrder(i + 1);
      }

      
      setInsertControlType(t_label); 
      insertControl(x - 110, y, false);
      c = 0;
      if (firstControl(&c)){
        do {
          if (c->acceptDrops()){ // missused as selected flag
            break;
          }
        } while (nextControl(&c));
      }
      ((_label *) c)->SETPROPERTY_Caption(f.name());

      y += 40;

      if (GETPROPERTY_Height() < 400 && y >= GETPROPERTY_Height()){
        SETPROPERTY_Height(500);
      } else if (y >= GETPROPERTY_Height()){
        x += 350;
        y = 10;
      }

      if (GETPROPERTY_Width() < 800 && x >= GETPROPERTY_Width()){
        SETPROPERTY_Width(GETPROPERTY_Width() + 100);
      }
    }
  }
  
  SETPROPERTY_SQLName("SELECT * FROM " + s);
  setInsertControlType(t); 
}

extern bool bWORKAROUNDShow;

bool _form::newEvent (QString sControlName, QString sEvent, QString sParameter)
{
    if (!isForm()) return false;

    QString sControlType = "";
    if (sControlName.isEmpty()){

      sControlName = GETPROPERTY_Name();
      if (sControlName == getFilenameWithoutPathAndExtension()){
        sControlName = "Form";
      }
      sControlType = GETPROPERTY_ControlType();

      QWidget *c;

      int n = 0;
      if (firstControl(&c)){

        do {

          if (c->acceptDrops()){

            n++;;
          }

        } while (nextControl(&c)); 
      }     
      
      if (firstControl(&c)){

        do {

          if (c->acceptDrops()){

            if (n > 1){
              #define SWITCH GETPROPERTY_Group();      
              #define SWITCH3 sControlName
              #include "_form_property_switch.h"   
              #undef SWITCH3
            } else {
              sControlName = c->objectName();
            

              sControlType = "";
              #define SWITCH GETPROPERTY_ControlType();      
              #define SWITCH3 sControlType
              #include "_form_property_switch.h"   
              #undef SWITCH3
            }

            break;
          }

        } while (nextControl(&c)); 
      }
      
    }

  if (sEvent == "OnEvent"){
    if (sControlType == "ComboBox" || sControlType == "ListBox"){
      sParameter = "Index As Integer, Caption As String";
    } else if (sControlType == "TreeView"){
      sParameter = "";
    } else if (sControlType == "TabView"){
      sParameter = "Index As Integer";
    } else if (sControlType == "HtmlView"){
      sParameter = "BackwardAvailable As Boolean, ForwardAvailable As Boolean, NewURL As String";
    }
  } else if (sEvent == "OnAction"){
    if (sControlType == "RichTextBox"){
      sParameter = "TextSelected As Boolean, PasteAvailable As Boolean, UndoAvailable As Boolean, RedoAvailable As Boolean";
    }
  } else if (sEvent == "OnCursorPositionChanged"){
    if (sControlType == "RichTextBox"){
      sParameter = "";
    }
  } else if (sEvent == "OnTick"){
    sParameter = "MSec As Long";
  } else if (sEvent == "OnStateChanged"){
    sParameter = "NewState As String, OldState As String";
  } else if (sEvent == "OnMutedChanged"){
    sParameter = "OnOff As Boolean";
  } else if (sEvent == "OnVolumeChanged"){
    sParameter = "Percent As Integer";
  } else if (sEvent == "OnPlayedTitleChanged"){
    sParameter = "FileName As String";
  } else if (sEvent == "OnBufferStatus"){
    sParameter = "Percent As Integer";
  } else if (sEvent == "OnTotalTimeChanged"){
    sParameter = "MSec As Long";	
  }
  

  bWORKAROUNDShow = false;

  QString q = getFilename();
  EXTERN_my_mainwindow->openFormClassSourceCode(q);
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(EXTERN_my_mainwindow->workspace->activeSubWindow() ? EXTERN_my_mainwindow->workspace->activeSubWindow()->widget() : 0);
  if (o){
    bWORKAROUNDShow = true;
    return o->newEvent (sControlName, sEvent, sParameter);
  }
  bWORKAROUNDShow = true;

  return false;

}
#endif

void _form::SETPROPERTY_X(int n, bool b)
{   
#ifdef IDE

  if (GETPROPERTY_X() != n){   
    
    _property::SETPROPERTY_X(n);
      if (!b){
        QWidget *w = this->parentWidget();
        if (w) w->move(n, GETPROPERTY_Y());
      }
      if (hasSelectedControls()) setFormSelf();
      
      updatePropertyWindow2(false, "X");
    
  }
#elif defined(RUN)

  QWidget *w = parentWidget();
  if (w){
    QMdiSubWindow *o = qobject_cast<QMdiSubWindow *>(w);
    if (o){
      o->move(n, GETPROPERTY_Y());
     //_property::SETPROPERTY_GlobalX(o->mapToGlobal(QPoint(n, 0)).x());
      return;
    }
  }

  w = this;
  w->move(n, GETPROPERTY_Y());
 
  
#endif

}


#ifdef RUN
int _form::GETPROPERTY_X()
{   
  QWidget *w = parentWidget();
  if (w){
    QMdiSubWindow *o = qobject_cast<QMdiSubWindow *>(w);
    if (o){
      return o->x();
    }
  }

  return x();
}

int _form::GETPROPERTY_Width()
{   
  if (this->bMETHOD_Open_Opened == false){
    int m = _property::GETPROPERTY_Width();
    return _property::GETPROPERTY_Width();
  }
  int k = width();
  return width();
}

int _form::GETPROPERTY_GlobalX()
{   
  QWidget *w = parentWidget();
  if (w){
    QMdiSubWindow *o = qobject_cast<QMdiSubWindow *>(w);
    if (o){
      return o->parentWidget()->mapToGlobal(QPoint(o->x(), 0)).x();
    }
  }

  return x();
}

int _form::GETPROPERTY_Y()
{   
  QWidget *w = parentWidget();
  if (w){
    QMdiSubWindow *o = qobject_cast<QMdiSubWindow *>(w);
    if (o){
      return o->y();
    }
  }

  return y();
}

int _form::GETPROPERTY_Height()
{   
  if (this->bMETHOD_Open_Opened == false) return _property::GETPROPERTY_Height();
  return height();
}

int _form::GETPROPERTY_GlobalY()
{   
  QWidget *w = parentWidget();
  if (w){
    QMdiSubWindow *o = qobject_cast<QMdiSubWindow *>(w);
    if (o){
      return o->parentWidget()->mapToGlobal(QPoint(0, o->y())).y();
    }
  }

  return y();
}
#endif


void _form::SETPROPERTY_Y(int n, bool b)
{ 
#ifdef IDE
  if (GETPROPERTY_Y() != n){
    
    _property::SETPROPERTY_Y(n);
    
      if (!b){
        QWidget *w = this->parentWidget();
        if (w) w->move(GETPROPERTY_X(), n);
      }
      if (hasSelectedControls()) setFormSelf();

      updatePropertyWindow2(false, "Y");
    
  }
#elif defined(RUN)

  QWidget *w = parentWidget();
  if (w){
    QMdiSubWindow *o = qobject_cast<QMdiSubWindow *>(w);
    if (o){
      o->move(GETPROPERTY_X(), n);
       return;
    }
  }

  w = this;
  w->move(GETPROPERTY_X(), n);
 
  
#endif
}

void _form::SETPROPERTY_Width(int n, bool b)
{   
#ifdef IDE
  if (GETPROPERTY_Width() != n){
    
    if (b){

      QWidget *w = this->parentWidget();
      if (w){
        QRect r = w->layout()->contentsRect();
        w->resize(n + r.left() * 2, GETPROPERTY_Height() + r.top());
      }
    }

    _property::SETPROPERTY_Width(n);
      if (hasSelectedControls()) setFormSelf();
      
      updatePropertyWindow2(false, "Width");
    
  }  
#elif defined(RUN)
   
  _property::SETPROPERTY_Width(n); // must be before calling resize

  QRect r;
    QWidget *w = this->parentWidget();
    if (w && qobject_cast<QMdiSubWindow *>(w)){

      w->layout()->activate(); // needed
      r = w->layout()->contentsRect();      

        w->resize(n + r.left() * 2, GETPROPERTY_Height() + w->height() - r.height());
  
    } else {
      // childform
      //QWidget::
     // this->setWidget(main);
    //  main->resize(n, GETPROPERTY_Height());
      resize(n, GETPROPERTY_Height());
    }
  
#endif


}

void _form::SETPROPERTY_Height(int n, bool b)
{   
#ifdef IDE

  if (GETPROPERTY_Height() != n){
    
    if (b){
      QWidget *w = this->parentWidget();
      if (w){
        QRect r = w->layout()->contentsRect();
        w->resize(GETPROPERTY_Width() + r.left() * 2, n + r.top()); // 31 = recordBorder->height()
      }
    }

    _property::SETPROPERTY_Height(n); // 31 = recordBorder->height()
    
      if (hasSelectedControls()) setFormSelf();
      
      updatePropertyWindow2(false, "Height");
    
  }  
#elif defined(RUN)

   _property::SETPROPERTY_Height(n); // must be before calling resize

    QRect r;
    QWidget *w = this->parentWidget();
    if (w && qobject_cast<QMdiSubWindow *>(w)){
      w->layout()->activate(); // needed
      r = w->layout()->contentsRect();      

        w->resize(GETPROPERTY_Width() + r.left() * 2, n + w->height() - r.height());

    } else {
      // childform
//      QWidget::resize(GETPROPERTY_Width(), n);
      resize(GETPROPERTY_Width(), n);
    }

    

  
#endif

}


void _form::closeEvent( QCloseEvent *e )
{
#ifdef RUN
    
    t_boolean b = false;
    if (stopByQuestion()){
      e->ignore();
      return;
    }
    EVENT_OnClose(&b);
    if (b){
      e->ignore();
      return;
    }
    if (forms_mainwindow && forms_mainwindow->centralWidget() == this){
      forms_mainwindow->setCentralWidget(0); // setting SDI
    }

    if (GETPROPERTY_StopOnClose()){
      _application::METHOD_Stop();
    }
    if (!this->GETPROPERTY_Dock().isEmpty()){
      QWidget *w = (QWidget *) this->parent();
      if (w) w->close();
    }

    memory_variable2 *v = EXTERN_myInterpreter->getVar(global);
    if (nFormId) v->setObject(nFormId, 0, 0);

    e->accept();

    QWidget::closeEvent(e);

    bDialogRunning = false;

#endif
#ifdef IDE

  
  if (isModified()){
      
	  show();
    setFocus();

	  switch( QMessageBox::question( this, tr("Save Changes"), 
	      tr("Save changes to %1?").arg( sFilename ),
	      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel )){
	    case QMessageBox::Yes:
	        {
		        save();            
		        if (!sFilename.isEmpty())
		          goto a;
		        else
		          e->ignore();
	        }
	        break;
	    case QMessageBox::No:
	        goto a;
	        break;
	    default:
	        e->ignore();
          return;
	        break;
	  }

  }

a:

  if (parentWidget()){
    QMdiSubWindow *mdis = qobject_cast<QMdiSubWindow *>(parentWidget());
    EXTERN_my_mainwindow->workspace->removeSubWindow(mdis);
  }

  e->accept();
  EXTERN_my_form = 0;
  EXTERN_my_report = 0;

  QWidget::closeEvent(e);

  EXTERN_my_parserwindow->refreshControl();

#endif
}




#ifdef IDE
QSize _form::checkFrameMinSize () 
{  
  QWidget *c;

  int nMaxX = 0;
  int nMaxY = 0;

  {

    if (firstControl(&c)){

      do {

        if (c->x() + c->width() > nMaxX){
          nMaxX = c->x() + c->width();
        }
        if (c->y() + c->height() > nMaxY){
          nMaxY = c->y() + c->height();
        }

      } while (nextControl(&c));

      int aa = this->minimumWidth();
      int bb = this->minimumHeight();
     
      if (this->minimumWidth() != nMaxX){
        bcheckFrameMinSize = true;
        this->setMinimumWidth(nMaxX/* + nBorderX + nBorderW*/);
      }
      if (this->minimumHeight() != nMaxY){
        this->setMinimumHeight(nMaxY/* + nBorderY + nBorderH*/);  
        bcheckFrameMinSize = true;
      }

    }
  }
  return QSize(nMaxX, nMaxY);
}
#endif


#ifdef RUN
void _form::moveEvent ( QMoveEvent *e)
{
  nMoveEventX = e->pos().x();
  nMoveEventY = e->pos().y();
  nMoveEventOldX = e->oldPos().x();
  nMoveEventOldY = e->oldPos().y();

  moveEvent(e, true);
}

void _form::moveEvent ( QMoveEvent *e, bool b)
{
#ifdef IDE
  if (b){
    QWidget::moveEvent(e);
  }
#endif

  if (this->bMETHOD_Open_Opened){
    bBlock_qApp_processEvents = true;
    EVENT_OnMove(nMoveEventX, nMoveEventY, nMoveEventOldX, nMoveEventOldY); 
    bBlock_qApp_processEvents = false;
  }
}
#endif

#ifdef IDE
void _form::showEvent(QShowEvent *e) 
{
  
  QWidget::showEvent(e);
}

void _form::showScrollBars()
{
  if (XScrollBar == 0 && GETPROPERTY_ScrollWidth()){ 
    XScrollBar = new QScrollBar(Qt::Horizontal, this); 
    XScrollBar->setHidden(GETPROPERTY_ScrollBar().contains("XScrollBarAlwaysOff"));
    XScrollBar->setMinimum(0);
    connect(XScrollBar, SIGNAL(valueChanged(int)), this, SLOT(XScrollBar_valueChanged(int)));
  }
  if (YScrollBar == 0 && GETPROPERTY_ScrollHeight()){ 
    YScrollBar = new QScrollBar(Qt::Vertical, this);
    YScrollBar->setHidden(GETPROPERTY_ScrollBar().contains("YScrollBarAlwaysOff"));
    YScrollBar->setMinimum(0);
    connect(YScrollBar, SIGNAL(valueChanged(int)), this, SLOT(YScrollBar_valueChanged(int)));
  }
  if (XScrollBar && YScrollBar){
    int y = height() - XScrollBar->sizeHint().height();    
    int x = width() - YScrollBar->sizeHint().width();
    XScrollBar->setPageStep(width());
    YScrollBar->setPageStep(height());
    XScrollBar->setMaximum(GETPROPERTY_ScrollWidth() - width());
    YScrollBar->setMaximum(GETPROPERTY_ScrollHeight()- height());
    XScrollBar->setGeometry(0, y, width() - (YScrollBar ? YScrollBar->sizeHint().width() : 0), XScrollBar->height());
    YScrollBar->setGeometry(x, 0, YScrollBar->width(), height() - (XScrollBar ? XScrollBar->sizeHint().height() : 0));
    XScrollBar->show();  
    YScrollBar->show();
  } else if (XScrollBar){
    int y = height() - XScrollBar->sizeHint().height();    
    XScrollBar->setPageStep(width());
    XScrollBar->setMaximum(GETPROPERTY_ScrollWidth() - width());
    XScrollBar->setGeometry(0, y, width() - (YScrollBar ? YScrollBar->sizeHint().width() : 0), XScrollBar->height());
    XScrollBar->show();  
  } else if (YScrollBar){
    int x = width() - YScrollBar->sizeHint().width();
    YScrollBar->setPageStep(height());
    YScrollBar->setMaximum(GETPROPERTY_ScrollHeight()- height());
    YScrollBar->setGeometry(x, 0, YScrollBar->width(), height() - (XScrollBar ? XScrollBar->sizeHint().height() : 0));
    YScrollBar->show();
  }
}
#endif

void _form::resizeEvent ( QResizeEvent *e)
{
#ifdef IDE
  newUndoRedo(false, false, true);

#endif

   nResizeEventWidth = e->size().width();
   nResizeEventHeight = e->size().height();
   nResizeEventOldWidth = e->oldSize().width();
   nResizeEventOldHeight = e->oldSize().height();
#ifdef RUN
   if (parentWidget() && qobject_cast<QMdiSubWindow *>(parentWidget())){
     QRect r = parentWidget()->layout()->contentsRect();

   } 
#endif
   resizeSize = QSize(nResizeEventWidth, nResizeEventHeight);
#ifdef RUN
   if (bFullscreen){
     resizeOldSize = resizeSize;
     
   } else {
     resizeOldSize = e->oldSize();
   }
  resizeEvent(e, bResizeEventFlag);

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

  if (bResizeEventFlag == false) bResizeEventFlag = true;
#else
     resizeOldSize = e->oldSize();
  resizeEvent(e, true);
#endif
  
}

void _form::resizeEvent ( QResizeEvent *e, bool b)
{
#ifdef IDE

  {

    if (bcheckFrameMinSize){
      bcheckFrameMinSize = false;
      return; // avoid curious action by resizing recursive calls
    }

  //return;

    QSize size = parentWidget()->size();
    int w = e->size().width();
    int h = e->size().height();

    int w2 = e->oldSize().width();
    int h2 = e->oldSize().height();

    checkFrameMinSize();
    


    QRect r = parentWidget()->layout()->contentsRect();

    SETPROPERTY_Width(w /*+ r.left() * 2*/, false);
    SETPROPERTY_Height(h /*+ r.top()*/, false);

    QWidget *c = 0;
    if (firstControl(&c)){
      do {

        QString sParentControl = "";

        #define SWITCH GETPROPERTY_ParentControl();      
        #define SWITCH3 sParentControl
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if (sParentControl == ""){
          
          QString sLayout = "";

          #define SWITCH GETPROPERTY_Layout();      
          #define SWITCH3 sLayout
          #include "_form_property_switch.h"   
          #undef SWITCH3

          if (sLayout.isEmpty()) continue;

          if (sLayout.contains("RelativeX", Qt::CaseInsensitive)){          
            if (w - w2 != 0){
              my_move(c, c->x() + w - w2, c->y());
            }

          } 
          
          if (sLayout.contains("RelativeWidth", Qt::CaseInsensitive)){          

            if (w - w2 != 0){
              int n = c->width() + w - w2;
              int n2 = c->minimumWidth();
              if (n < n2 && n2 > 0) n = n2;

              #define SWITCH SETPROPERTY_Width(n);         
              #include "_form_property_switch.h"     
            }

          }

          if (sLayout.contains("RelativeY", Qt::CaseInsensitive)){          

            if (h - h2 != 0){
              my_move(c, c->x(), c->y() + h - h2);
            }

          }              
            
          if (sLayout.contains("RelativeHeight", Qt::CaseInsensitive)){          

            if (h - h2 != 0){

              int n = c->height() + h - h2;
              int n2 = c->minimumHeight();
              if (n < n2 && n2 > 0) n = n2;
              //if (n > nFormHeight) n = nFormHeight;

              #define SWITCH SETPROPERTY_Height(n);
              #include "_form_property_switch.h"   
            }

          }

        }
          
      } while (nextControl(&c));
    }

  }
#endif

#ifdef IDE
  showScrollBars();
  if (b){
    QWidget::resizeEvent(e);
  }
#endif
#ifdef RUN
    

    int w = nResizeEventWidth;
    int h = nResizeEventHeight;

    
    int w2 = 0;
    int h2 = 0;
    QSize size2 = resizeOldSize;
    if (size2.isValid()){
      oldSize = size2;
      w2 = nResizeEventOldWidth;
      h2 = nResizeEventOldHeight;
    } else {
      w2 = oldSize.width();
      h2 = oldSize.height();
      oldSize = resizeSize;
    }

    QString sParent = GETPROPERTY_Name();

    QRect rr;   
    QWidget *ww = parentWidget();
    if (ww && qobject_cast<QMdiSubWindow *>(ww)){
      rr = ww->layout()->contentsRect();      
    }
    int nFormWidth = width();
    int nFormHeight = height();

    {
      nFormWidth += rr.left() * 2;
      nFormHeight += rr.top();

      w += rr.left() * 2; 
      h += rr.top();
      w2 += rr.left() * 2; 
      h2 += rr.top();
    }
 
    int nLoadedWidth = GETPROPERTY_LoadedWidth();    
    int nLoadedHeight = GETPROPERTY_LoadedHeight();   

    int nDockWidth = GETPROPERTY_DockWidth();    
    int nDockHeight = GETPROPERTY_DockHeight();   
    QWidget *p = parentWidget();

    if (bFirstDockResize && (p == 0 || !qobject_cast<_form *>(p))){
      bool bbb = true;
      if (nDockWidth == 0){
        bbb = false;
        nDockWidth = nLoadedWidth;
      }
      else if (nDockWidth == -1){
        nDockWidth = 0;
        bbb = false;
      }
      if (nDockHeight == 0){
        nDockHeight = nLoadedHeight;
      } 
      else if (nDockHeight == -1){
        nDockHeight = 0;
        bbb = false;
      }
      else bbb = true;

      if (bbb && (nDockWidth > 0 || nDockHeight > 0)){

        if (p && qobject_cast<QMdiSubWindow *>(p)){
        } else {
          setMinimumSize(nDockWidth > 0 ? nDockWidth : 0, nDockHeight > 0 ? nDockHeight : 0);      
        }
      }
        
      if (p){
        bFirstDockResize = false;
        return;
      }
      

    }

    QWidget *c = 0;
    if ((nFormWidth != nLoadedWidth || nFormHeight != nLoadedHeight || (w2 > 0 && w2 - w) || (h2 > 0 && h2 - h)) /*w2 > 0 && h2 > 0*/ && firstControl(&c)){

      bFirstResize = false;

      do {

        if (controlType(c) == t_childcontrol) continue;

        QString sControlName = "";

        #define SWITCH GETPROPERTY_Name();      
        #define SWITCH3 sControlName
        #include "_form_property_switch.h"   
        #undef SWITCH3

        QString sParentControl = "";

        #define SWITCH GETPROPERTY_ParentControl();      
        #define SWITCH3 sParentControl
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if (sParentControl == sParent || sParentControl.isEmpty()){

          QString sLayout = "";

          #define SWITCH GETPROPERTY_Layout();      
          #define SWITCH3 sLayout
          #include "_form_property_switch.h"   
          #undef SWITCH3

          if (sLayout.isEmpty()) continue;

          if (sLayout.contains("RelativeX", Qt::CaseInsensitive)){          

            if (w - w2 != 0){

              int xx;

              #define SWITCH GETPROPERTY_LoadedX();      
              #define SWITCH3 xx
              #include "_form_property_switch.h"   
              #undef SWITCH3

              int n = c->x() + w - w2;
              if (n > nFormWidth) n = nFormWidth;

              my_move(c, n, c->y());

            }

          } 
          
          if (sLayout.contains("RelativeWidth", Qt::CaseInsensitive)){          

            if (w - w2 != 0){

              int ww; 

              #define SWITCH GETPROPERTY_LoadedWidth();      
              #define SWITCH3 ww
              #include "_form_property_switch.h"   
              #undef SWITCH3
            
              int n = c->width() + w - w2;
              if (controlType(c) != t_tab){
                int n2 = c->minimumWidth();
                if (n < n2 && n2 > 0) n = n2;
              }
              if (n > nFormWidth) n = nFormWidth;

              #define SWITCH SETPROPERTY_Width(n);
              #include "_form_property_switch.h"  

            }

          }

          if (sLayout.contains("RelativeY", Qt::CaseInsensitive)){          

            if (h - h2 != 0){

              int yy;

              #define SWITCH GETPROPERTY_LoadedY();      
              #define SWITCH3 yy
              #include "_form_property_switch.h"   
              #undef SWITCH3

              int n = c->y() + h - h2;
              if (n > nFormHeight) n = nFormHeight;

              my_move(c, c->x(), n);
            }


          } 
          if (sLayout.contains("RelativeHeight", Qt::CaseInsensitive)){          

            if (h - h2 != 0){

              int hh; 

              #define SWITCH GETPROPERTY_LoadedHeight();      
              #define SWITCH3 hh
              #include "_form_property_switch.h"   
              #undef SWITCH3

              int n = c->height() + h - h2;
              if (controlType(c) != t_tab){
                int n2 = c->minimumHeight();
                if (n < n2 && n2 > 0) n = n2;
              }
              if (n > nFormHeight) n = nFormHeight;

              #define SWITCH SETPROPERTY_Height(n);
              #include "_form_property_switch.h"   
            }



          }

        }
          
      } while (nextControl(&c));
    }

    QMapIterator<_form *, _childcontrol *>i(layout_childcontrols);
    if ((nFormWidth != nLoadedWidth || nFormHeight != nLoadedHeight || (w2 > 0 && w2 - w) || (h2 > 0 && h2 - h))){
      while (i.hasNext()){
          i.next();

          _form *c = (_form *) i.key();
          _childcontrol *cc = i.value();;

          QString sLayout = cc->GETPROPERTY_Layout();//i.value();
          
          if (sLayout.isEmpty()) continue;

          if (sLayout.contains("RelativeX", Qt::CaseInsensitive)){          

            if (w - w2 != 0){
              int xx = cc->GETPROPERTY_LoadedX(); 

              int n = c->x() + w - w2;
              if (n < xx) n = xx;      
              if (n > nFormWidth) n = nFormWidth;

              c->SETPROPERTY_X(n);
            }
          }

          if (sLayout.contains("RelativeWidth", Qt::CaseInsensitive)){          

            if (w - w2 != 0){
              int ww = cc->GETPROPERTY_LoadedWidth(); 

              int n = c->width() + w - w2;
              if (n < ww) n = ww;      
              int n2 = c->minimumWidth();
              if (n < n2 && n2 > 0) n = n2;
              if (n > nFormWidth) n = nFormWidth;

              c->SETPROPERTY_Width(n);
            }

          }

          if (sLayout.contains("RelativeY", Qt::CaseInsensitive)){          

            if (h - h2 != 0){
              int yy = cc->GETPROPERTY_LoadedY(); 

              int n = c->height() + h - h2;
              if (n < yy) n = yy;              
              if (n > nFormHeight) n = nFormHeight;

              c->SETPROPERTY_Y(n);
            }

          } 

          if (sLayout.contains("RelativeHeight", Qt::CaseInsensitive)){          

            if (h - h2 != 0){

              int hh = cc->GETPROPERTY_LoadedHeight(); 

              int n = c->height() + h - h2;
              if (n < hh) n = hh;              
              int n2 = c->minimumHeight();
              if (n < n2 && n2 > 0) n = n2;
              if (n > nFormHeight) n = nFormHeight;

              c->SETPROPERTY_Height(n);
            }

          }

      }
    }
    if (this->bMETHOD_Open_Opened){
      bBlock_qApp_processEvents = true;
      EVENT_OnResize(nResizeEventWidth, nResizeEventHeight, nResizeEventOldWidth, nResizeEventOldHeight);
      bBlock_qApp_processEvents = false;
    }
#endif
  
  
}

#ifdef RUN

void _form::timerEvent(QTimerEvent* e)
{
  if (nTimerIdMove && nTimerIdMove == e->timerId()){
    killTimer(nTimerIdMove);
    nTimerIdMove = 0;
    moveEvent(0, false);
  }
  if (nTimerIdResize && nTimerIdResize == e->timerId()){
    killTimer(nTimerIdResize);
    nTimerIdResize = 0;
    resizeEvent(0, false);
  }

  QWidget::timerEvent(e);

  if (e->timerId() == nSingleShot){
    EVENT_OnSingleShot(); 
    killTimer(nSingleShot);
    nSingleShot = 0;
  } else {
    EVENT_OnTimer(); 
  }
  
}

bool _form::eventFilter( QObject *o, QEvent *e )
{
  bool b = QWidget::eventFilter(o, e);
  
  if (this->bMETHOD_Open_Opened){
     if ( e->type() == QEvent::Move ){
      
       
       nMoveEventX = ((QMoveEvent *) e)->pos().x();
       nMoveEventY = ((QMoveEvent *) e)->pos().y();
       nMoveEventOldX = ((QMoveEvent *) e)->oldPos().x();
       nMoveEventOldY = ((QMoveEvent *) e)->oldPos().y();

       moveEvent(0, false);

     } else if ( e->type() == QEvent::Resize ){

 
     }
  }

   return b;
}
#endif


void _form::focusInEvent ( QFocusEvent * e)
{  
#ifdef IDE
  if (e == 0 && !this->hasFocus()){
  } else {

    if (isForm()){
      EXTERN_ToolboxForm->show();
      EXTERN_ToolboxReport->hide();
    } else {
      EXTERN_ToolboxForm->hide();
      EXTERN_ToolboxReport->show();
    }
    EXTERN_ToolboxMenuBar->hide();
    EXTERN_ToolboxToolBar->hide();
    EXTERN_Helpwindow_shortcut->hide();

    EXTERN_my_mainwindow->workspace->setActiveSubWindow((QMdiSubWindow *) parentWidget());
  
    EXTERN_my_mainwindow->updateGeneralActions(
    false,  isForm(),  isReport(),  false, 
    false,  false,  false,  false,  false,   
    bShowFocusOrder, bShowSQLSettings, bShowSQLTables, 
    controlSelected(), bCopy || bCut, hasRedo(), hasUndo(), 
    false, "");

    if (isForm()){
      nPropertyWindowForWhat = 0;
      EXTERN_my_form = this;
      EXTERN_my_report = 0;
    } else {
      nPropertyWindowForWhat = 3;
      EXTERN_my_form = 0;
      EXTERN_my_report = (_report *) this;
    }
        
    bool b = isModified();
    EXTERN_my_parserwindow->refreshControl();
    updatePropertyWindow();
    if (!b) setNonModified();
/*
    EXTERN_my_helpwindow->setText(
"In your KBasic-application forms are not only masks for inputting and changing data, but they are the graphical interface of your application. In the eyes of the beholder, they are the application! By creating your application using forms, you control the program flow with events, which are raised in the forms.\n\n"
"Central meaning of forms: Each form in a KBasic application has got a form module with event procedures. Those event procedures react on events raised in the form. Additionally, every module can contain other non-event procedures.\n\n"
"A form module is part of every form, when you copy a form, its form module is automatically copied, too. If you delete a form, its form module is deleted as well. KBasic creates a form module automatically. So you need only to write the event procedures and other procedures.\n"
"\n\n"
"Forms keep your KBasic program together!"
);
*/
     }

  QWidget::focusInEvent(e);

#endif
#ifdef RUN
  QWidget::focusInEvent(e);
  
    EVENT_OnGotFocus();
#endif
  
}

void _form::focusOutEvent ( QFocusEvent * e)
{  
#ifdef RUN
  QWidget::focusOutEvent(e);
    EVENT_OnLostFocus();

#else
  QWidget::focusOutEvent(e);  
#endif
  
}

void _form::mousePressEvent ( QMouseEvent * e )
{
  Qt::MouseButton bu = e->button();

#ifdef IDE
  {

    if (bMouseMove == false){
      bFirstMouseMove = true;

      if (bMousePressed == false){
       nMouseOriginX = mouseX(e);
       nMouseOriginY = mouseY(e);
       //updatePropertyWindow();

      }

      bMousePressed = true;
      bRightButton = e->button() == Qt::RightButton;

      nMouseX = mouseX(e);
      nMouseY = mouseY(e); 

    }
  }   

#elif defined(RUN)
  {

    
/*
    // *** hidden control ?
    QObjectList it = children(); // iterate over the children
    QObject *o;
    for (int q = 0; q < it.size(); q++){
      o = it.at(q);
      if (qobject_cast<_hidden *>(o)){
        _hidden *k = (_hidden *) o;
        int x = k->x();
        int y = k->y();
        int x2 = e->x();
        int y2 = e->y();
        int w = k->width();
        int h = k->height();

        if (x2 >= x && x2 <= x + w && y2 >= y && y2 <= y + h){
          bEventClick = true;
          k->EVENT_OnMouseDown(e->x(), e->y(), e->globalX(), e->globalY(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);
          return;
        }        
      }
    }
    */
  }
  QWidget::mousePressEvent(e);
    // ***
#endif    
    bEventClick = true;
#ifdef RUN
    QWidget::mousePressEvent(e);
    nMoveOnMouseDragX = e->globalX();
    nMoveOnMouseDragY = e->globalY();     

    EVENT_OnMouseDown(e->x() + this->horizontalScrollBar()->value(), e->y() + this->verticalScrollBar()->value(), e->globalX(), e->globalY(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);
#endif
  
  
}

void _form::mouseReleaseEvent ( QMouseEvent * e ) 
{
#ifdef IDE
  {    

    bool bInserted = false;

    bMousePressed = false;

    if (bSelector == true){

      selector1->hide();

      QWidget *c;

      int x = nMouseOriginX;
      int y = nMouseOriginY;
      int w = nMouseX - nMouseOriginX;    
      if (w < 0){
       x = nMouseOriginX + w;
       w *= -1;
      }
      int h = nMouseY - nMouseOriginY;
      if (h < 0){
       y = nMouseOriginY + h;
       h *= -1;
      }

      x -= XSCROLLBAR;
      y -= YSCROLLBAR;

      if (bCTRL == false && bControlMove == false){
       unselectAllControls();
      }

      if (firstControl(&c)){

       do {

         if (c->isHidden()) continue;


         int x2;

         #define SWITCH GETPROPERTY_X();      
         #define SWITCH3 x2
         #include "_form_property_switch.h"   
         #undef SWITCH3

         x2 -= XSCROLLBAR;

         int y2;

         #define SWITCH GETPROPERTY_Y();      
         #define SWITCH3 y2
         #include "_form_property_switch.h"   
         #undef SWITCH3

         y2 -= YSCROLLBAR;

         int w2 = c->width();
         int h2 = c->height();

         QWidget *ww = c->parentWidget();
         if (ww != this){
           x2 += ww->x();
           y2 += ww->y();
         }

         if ( (x2 >= x && x2 <= x + w && y2 >= y && y2 <= y + h)
           || (x2 >= x && x2 <= x + w && y2 + h2 >= y && y2 + h2 <= y + h)
           || (x2 + w2 >= x && x2 + w2 <= x + w && y2 >= y && y2 <= y + h)
           || (x2 + w2 >= x && x2 + w2 <= x + w && y2 + h2 >= y && y2 + h2 <= y + h)
            
           || (x >= x2 && x <= x2 + w2 && y >= y2 && y <= y2 + h2)
           || (x + w >= x2 && x + w <= x2 + w2 && y + h >= y2 && y + h <= y2 + h2)

           || (x >= x2 && x <= x2 + w2 && x + w >= x2 && x + w <= x2 + w2 && y <= y2 && y + h >= y2 + h2)
           || (y >= y2 && y <= y2 + h2 && y + h >= y2 && y + h <= y2 + h2 && x <= x2 && x + w >= x2 + w2)
            
           )
         {
           
           selectControlAlways(c);
         }

       } while (nextControl(&c)); 

      }

      bControlMove = false;  
      bSelector = false;
    } else {

      QWidget *c;
      bool bFind = false;
      
      bSelected = false;

      if (insertType == t_notype && firstControl(&c)){

       
       int nMinX = 999999;
       int nMinY = 999999; 
       QWidget *cMin = 0;


       int x2 = mouseX(e);
       int y2 = mouseY(e);


       do {
         if (c->isHidden()) continue;

         if (isReport()){
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

         if (bControlMove) setParentControl(c, x2, y2);


         int x;

         #define SWITCH GETPROPERTY_X();      
         #define SWITCH3 x
         #include "_form_property_switch.h"   
         #undef SWITCH3

         int y;

         #define SWITCH GETPROPERTY_Y();      
         #define SWITCH3 y
         #include "_form_property_switch.h"   
         #undef SWITCH3

         int w = c->width();
         int h = c->height();

         QWidget *ww = c->parentWidget();
         if (ww != this){
           x += ww->x();
           y += ww->y();
         }

         x2 = mouseX(e);// - XSCROLLBAR;
         y2 = mouseY(e);// - YSCROLLBAR;

         if (bCTRL == false && bControlMove == false && bRightButton == false){
           unselectControl(c);
         }

         if (x2 >= x && x2 <= x + w 
         && y2 >= y && y2 <= y + h)
         {
           if (bControlMove == false && x2 - x <= nMinX && y2 - y <= nMinY){
             nMinX = x2 - x;
             nMinY = y2 - y;
             cMin = c;
           }
            
           bSelected = true;
           bFind = true;
         }


       } while (nextControl(&c));


       if (bControlMove == false && nMouseX == x2 && nMouseY == y2 && cMin != 0){

         if (bRightButton == true){
           if (cMin->acceptDrops() == false){
             unselectAllControls();
           }
         }
         if (bApply && !bCopy && ! bCut){
           
            performApply(cMin, 0);


              apply_properties.clear();// = 0;

              QApplication::restoreOverrideCursor();
              bApply = false;             
            
         }
         
         {

          if (bCTRL == false){
            selectControlAlways(cMin);
          } else {
            selectControl(cMin);
          }
         }
          
       }

       if (bFind){
         goto exit;
       }
      }

      if (e->button() == Qt::LeftButton && bControlMove == false){

       newUndoRedo();
       if (bCTRL == false){
         unselectAllControls();
       }
       insertControl(mouseX(e), mouseY(e));
       bInserted = true;
       bSelected = true;
       if (bCTRL == false){
         //setInsertControlType(t_notype);
       }

      }
    
      int w = nMouseX - nMouseOriginX;    
      int h = nMouseY - nMouseOriginY;

      if (w == 0 && h == 0 && bSelected == false && bControlMove == false){
       setFocus();
       unselectAllControls();
       insertType = t_notype;
      }
    }  
  exit:
    bSelected = false;
    bControlMove = false;  
    bMouseMove = false;
    checkFrameMinSize();

    if (bInserted == false || insertType == t_notype) updatePropertyWindow();
    
    {
      focusInEvent(0);
    }

  } 
  
  QWidget::mouseReleaseEvent(e);
#endif

#ifdef RUN
  QWidget::mouseReleaseEvent(e);
  {
    Qt::MouseButton bu = e->button();
/*
    // *** hidden control ?
    QObjectList it = children(); // iterate over the children
    QObject *o;
    for (int q = 0; q < it.size(); q++){
      o = it.at(q);
      if (qobject_cast<_hidden *>(o)){
        _hidden *k = (_hidden *) o;
        int x = k->x();
        int y = k->y();
        int x2 = e->x();
        int y2 = e->y();
        int w = k->width();
        int h = k->height();

        if (x2 >= x && x2 <= x + w && y2 >= y && y2 <= y + h){
          if (bEventClick){
            bEventClick = false;
            k->EVENT_OnClick(e->x(), e->y(), e->globalX(), e->globalY(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);
          }
          k->EVENT_OnMouseUp(e->x(), e->y(), e->globalX(), e->globalY(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);
          return;
        }        
      }
    }
    */

    // ***

    if (bEventClick){
      bEventClick = false;

      EVENT_OnClick(e->x() + this->horizontalScrollBar()->value(), e->y() + this->verticalScrollBar()->value(), e->globalX(), e->globalY(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);

    }

    EVENT_OnMouseUp(e->x() + this->horizontalScrollBar()->value(), e->y() + this->verticalScrollBar()->value(), e->globalX(), e->globalY(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);

  }
  #endif

}

void _form::mouseMoveEvent ( QMouseEvent * e ) 
{
#ifdef IDE
  {
    sCoordinate = QString("X: %1  Y: %2").arg(nMouseX).arg(nMouseY);
    this->setToolTip(sCoordinate);

    if (insertType == t_notype && bMousePressed == true){
      bMouseMove = true;

      bool bMoveControls = false;

      if (bSelector == true || (bMoveControls = moveControls(e)) == false){ // test if controls should be moved    

       if (bControlMove == false && (insertType == t_notype || bRightButton)){

         bSelector = true;
         int x = nMouseOriginX - XSCROLLBAR;
         int y = nMouseOriginY - YSCROLLBAR;
         int w = nMouseX - nMouseOriginX;
         int h = nMouseY - nMouseOriginY;

          
         selector1->raise();

         if (w < 0){
           x = x + w + 1;
           w *= -1;
         }

         if (h < 0){
           y = y + h + 1;
           h *= -1;
         }

         selector1->setGeometry(x, y, w, h);
      
         selector1->show();
         qApp->processEvents(); // needed to make selector1->show(); working

       }
      }

      if (bMoveControls){
        if (bFirstMouseMove){
          bFirstMouseMove = false;
          newUndoRedo();
        }
        
      }

      updatePropertyWindowGeo();
   
      checkFrameMinSize();
    }

    nMouseX = mouseX(e);
    nMouseY = mouseY(e);

  } 

#elif defined(RUN)
    /*
    QObjectList it = children(); // iterate over the children
    QObject *o;
    for (int q = 0; q < it.size(); q++){
      o = it.at(q);
      if (qobject_cast<_hidden *>(o)){
        _hidden *k = (_hidden *) o;
        int x = k->x();
        int y = k->y();
        int x2 = e->x();
        int y2 = e->y();
        int w = k->width();
        int h = k->height();
        bool b = false;

        if (!(nOldMouseX >= x && nOldMouseX <= x + w && nOldMouseY >= y && nOldMouseY <= y + h)){
          b = true;
          k->EVENT_OnEnter();          
        } else if (nOldMouseX >= x && nOldMouseX <= x + w && nOldMouseY >= y && nOldMouseY <= y + h){
          b = true;
          k->EVENT_OnExit();  
        }        

        if (x2 >= x && x2 <= x + w && y2 >= y && y2 <= y + h){
          k->EVENT_OnMouseMove(e->x(), e->y(), e->globalX(), e->globalY());
          return;
        }      
        if (b) return;
      }
    }
    */
QWidget::mouseMoveEvent(e);
#endif

    // ***
#ifdef RUN

    QWidget::mouseMoveEvent(e);

    EVENT_OnMouseMove(e->x() + this->horizontalScrollBar()->value(), e->y() + this->verticalScrollBar()->value(), e->globalX(), e->globalY());
#endif


    nOldMouseX = e->x();
    nOldMouseY = e->y();
  

#ifdef RUN
    Qt::MouseButtons bu = e->buttons();
    if (bu == Qt::LeftButton && GETPROPERTY_MoveOnMouseDrag() && !this->isMaximized() && !this->isFullScreen()){
      int x = nMoveOnMouseDragX - e->globalX();
      int y = nMoveOnMouseDragY - e->globalY();
      if (x != 0 || y != 0){
        if (parentWidget()){
          parentWidget()->move(parentWidget()->x() - x, parentWidget()->y() - y);
        } else {
          move(GETPROPERTY_X() - x, GETPROPERTY_Y() - y);
        }
      }

      nMoveOnMouseDragX = e->globalX();
      nMoveOnMouseDragY = e->globalY();
    }  
#endif
  
}



void _form::my_move(QWidget *c, int x, int y, int mx2, int my2)
{
  int mx = 0;
  int my = 0;

#ifdef IDE
  if (XScrollBar && mx2 == 0) mx = XScrollBar->value(); else mx = mx2;
  if (YScrollBar && my2 == 0) my = YScrollBar->value(); else my = my2;


  moveTabRelated(c, x, y);
#endif

  c->move(x, y);

  #define SWITCH SETPROPERTY_X(mx + x);
  #define SWITCH2 SETPROPERTY_Y(my + y);
  #include "_form_property_switch.h"            
}


#ifdef IDE
bool _form::eventFilter( QObject *o, QEvent *e )
{
#ifdef IDE
  if (bObjectEditor) return false;

  static int n = 0;

   if ( e->type() == QEvent::Move ){

      {

        n++;
        {

        if (!bMousePressed)
        {
          if (bPerformUndoRedo == false) newUndoRedo(false, true);

            SETPROPERTY_X(parentWidget()->x(), true);
            SETPROPERTY_Y(parentWidget()->y(), true);
        }

      }
    }


   } else if ( e->type() == QEvent::MouseButtonRelease ){   
   }
#endif

   return QObject::eventFilter(o, e);
}




void _form::moveTabRelated(QWidget *c, int x, int y)
{

  {     

    QWidget *c2 = 0;
    
    int x2 = c->x() - x;
    int y2 = c->y() - y;          

    QWidget *ww = c->parentWidget();
    if (ww != this){
      x2 += ww->x();
      y2 += ww->y();
    }

    // move the controls inside a tab
    if (controlType(c) == t_tab){        
      QWidget *currentControl = c;            
      
      QString sTab = ((_tab *) c)->GETPROPERTY_Name(); 

      if (firstControl(&c)){
        do {

          c2 = c;

          QString sParentControl = "";

          #define SWITCH GETPROPERTY_ParentControl();      
          #define SWITCH3 sParentControl
          #include "_form_property_switch.h"   
          #undef SWITCH3

          if (sParentControl == sTab && sTab.length() && c->acceptDrops() == false){ // missused as selected flag
            
            int x3 = c->x();
            int y3 = c->y();  

            QWidget *ww = c->parentWidget();
            if (ww != this){
              y3 += ww->x();
              y3 += ww->y();
            }

            // move the control
            my_move(c, x3 - x2, y3 - y2); // move the control
/*
            #define SWITCH SETPROPERTY_X(x3 - x2);
            #define SWITCH2 SETPROPERTY_Y(y3 - y2);
            #include "_form_property_switch.h"    */
          }
            
        } while (nextControl(&c));

        // seek to current control
        if (firstControl(&c)){
          do {
            if (c == currentControl) break;

          } while (nextControl(&c));
        }

      }
    }

    // update ParentControl and TabIndex
    if (c2) setParentControl(c2, x, y);

  }
    
}
#endif

void _form::updateCaption(QString s)
{
  if (s.isEmpty()){
    s = tr("unnamed document");
  } else {
    s = getFilenameWithoutPath();
  }
  
#ifdef IDE
    {
      setWindowTitle(s);      
    }
#endif

}

void _form::tabPageSelected(_tab *t, int index)
{


  QWidget *c;
  
  QString sTab = t->GETPROPERTY_Name(); 
  int nIndex = t->METHOD_Selected() - 1; 

  QWidget *currentControl = CurrentControl;

  if (firstControl(&c)){
    do {

      QString sParentControl = "";
      int nTabIndex = 0;

      #define SWITCH GETPROPERTY_ParentControl();      
      #define SWITCH3 sControlName
      #include "_form_property_switch.h"   
      #undef SWITCH3

      #define SWITCH GETPROPERTY_TabIndex();      
      #define SWITCH3 nTabIndex
      #include "_form_property_switch.h"   
      #undef SWITCH3
      
      if (sTab == sControlName){

        if (nIndex == nTabIndex){

          if (controlType(c) == t_childcontrol){
#ifdef RUN
            _form *f = (_form *) ((_childcontrol *) c)->METHOD_Form(); 
            f->show();            
#endif
          } else {
            c->show();          
          }
        } else {

          if (controlType(c) == t_childcontrol){
#ifdef RUN
            _form *f = (_form *) ((_childcontrol *) c)->METHOD_Form(); 
            f->hide();            
#endif
          } else  {
            c->hide();
          }
        }
      }
        
    } while (nextControl(&c));
  }

  // seek to current control
  if (firstControl(&c)){
    do {
      if (c == currentControl) break;

    } while (nextControl(&c));
  }
  
}

void _form::mouseDoubleClickEvent ( QMouseEvent * e )
{
#ifdef IDE
    openFormClassSourceCode();
    mouseReleaseEvent(e); // select control
#elif defined(RUN)

    Qt::MouseButton bu = e->button();

    /*
    // *** hidden control ?
    QObjectList it = children(); // iterate over the children
    QObject *o;
    for (int q = 0; q < it.size(); q++){
      o = it.at(q);
      if (qobject_cast<_hidden *>(o)){
        _hidden *k = (_hidden *) o;
        int x = k->x();
        int y = k->y();
        int x2 = e->x();
        int y2 = e->y();
        int w = k->width();
        int h = k->height();

        if (x2 >= x && x2 <= x + w && y2 >= y && y2 <= y + h){
          k->EVENT_OnDblClick(e->x(), e->y(), e->globalX(), e->globalY(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);
          return;
        }        
      }
    }
    */
    // ***    
    QWidget::mouseDoubleClickEvent(e);
#endif
    
#ifdef RUN
    QWidget::mouseDoubleClickEvent(e);

    EVENT_OnDblClick(e->x() + this->horizontalScrollBar()->value(), e->y() + this->verticalScrollBar()->value(), e->globalX(), e->globalY(), bu == Qt::LeftButton, bu == Qt::RightButton, bu == Qt::MidButton);
#endif
  
}


#ifdef IDE
void _form::updatePropertyWindowGeo()
{
   bPerformUndoRedo = true;

  QWidget *c;

  pp.clear();

  bool b = true;
  bool b2 = true;

  if (firstControl(&c)){

    do {

      if (c->acceptDrops()){ // missused as selected flag        

      #define SWITCH getProperties();
      #define SWITCH3 p2
      #include "_form_property_switch.h"    
      #undef SWITCH3

        if (b){
          b = false;

          _property::addProperties(&pp, p2);

        } else {

          if (b2){
            b2 = false;

            pp["X"]->set = false;// pp["X"]->defaultValue = false;            
            pp["Y"]->set = false;// pp["Y"]->defaultValue = false;            
            pp["Width"]->set = false;// pp["Width"]->defaultValue = false;            
            pp["Height"]->set = false;// pp["Height"]->defaultValue = false;            
          }

          _property::mergeProperties(&pp, p2);
        }


      }

    } while (nextControl(&c));
    
  }
  if (b){
    showUpdatePropertyWindow();
    bPerformUndoRedo = false;
    return;
  }

  t_property *d;

  d = pp["X"]; EXTERN_my_propertywindow->SETPROPERTY_X(d->display, d->set, d->v_integer);
  d = pp["Y"]; EXTERN_my_propertywindow->SETPROPERTY_Y(d->display, d->set, d->v_integer);
  d = pp["Width"]; EXTERN_my_propertywindow->SETPROPERTY_Width(d->display, d->set, d->v_integer); 
  d = pp["Height"]; EXTERN_my_propertywindow->SETPROPERTY_Height(d->display, d->set, d->v_integer);

   bPerformUndoRedo = false;

}

void _form::showUpdatePropertyWindow(bool b)
{
 
  updatePropertyWindow(b);

}

void _form::updatePropertyWindow2(bool bb, QString sProperty )
{

  bPerformUndoRedo = true;

  t_properties::Iterator it;
  t_properties *a;
  t_property *d =  0;
  bool b = false;
  QString ss = "";

  if (sProperty.length()){ // speed optimization
    if (!hasSelectedControls()){
      p.clear();
      a = this->getProperties();
    }

    b = true;
    d = (t_property *) 1;

         if (sProperty == "X"){ d = (*a)["X"]; if (d) goto _X; }
    else if (sProperty == "Y"){ d = (*a)["Y"]; if (d) goto _Y; }
    else if (sProperty == "Width"){ d = (*a)["Width"]; if (d) goto _Width; }
    else if (sProperty == "Height"){ d = (*a)["Height"]; if (d) goto _Height; }

    if (d == 0){
      showUpdatePropertyWindow();
      return;
    }

    b = false;
  }

  if (bb){
    EXTERN_my_propertywindow->setEnabled(false);
    EXTERN_my_propertywindow->showProperties(false);
  }

  EXTERN_my_propertywindow->setUpdatesEnabled(false);
  EXTERN_my_propertywindow->lock();
  for ( it = p.begin(); it != p.end(); ++it){

    ss = it.key();
    d = *it;

    if (ss == "Name"){

     EXTERN_my_propertywindow->SETPROPERTY_Name(d->display, d->set, d->v_qstring);

    } else if (ss == "X"){
_X:        EXTERN_my_propertywindow->SETPROPERTY_X(d->display, d->set, d->v_integer); if (b){ EXTERN_my_propertywindow->setEnabled(true); return; }
    } else if (ss == "Y"){
_Y:        EXTERN_my_propertywindow->SETPROPERTY_Y(d->display, d->set, d->v_integer); if (b){ EXTERN_my_propertywindow->setEnabled(true); return; }
    } else if (ss == "Width"){
_Width:    EXTERN_my_propertywindow->SETPROPERTY_Width(d->display, d->set, d->v_integer); if (b){ EXTERN_my_propertywindow->setEnabled(true); return; }
    } else if (ss == "Height"){
_Height:   EXTERN_my_propertywindow->SETPROPERTY_Height(d->display, d->set, d->v_integer); if (b){ EXTERN_my_propertywindow->setEnabled(true); return; }

    } else if (ss == "ControlType"){
     EXTERN_my_propertywindow->SETPROPERTY_ControlType(d->display, d->set, d->v_qstring);
    } else if (ss == "Caption"){
     EXTERN_my_propertywindow->SETPROPERTY_Caption(d->display, d->set, d->v_qstring);
    } else if (ss == "IntegerValue"){
     EXTERN_my_propertywindow->SETPROPERTY_IntegerValue(d->display, d->set, d->v_integer);
    
    } else if (ss == "Group"){ EXTERN_my_propertywindow->SETPROPERTY_Group(d->display, d->set, d->v_qstring);
    } else if (ss == "Background"){ EXTERN_my_propertywindow->SETPROPERTY_Background(d->display, d->set, d->v_qstring);
    } else if (ss == "BackgroundStyle"){ EXTERN_my_propertywindow->SETPROPERTY_BackgroundStyle(d->display, d->set, d->v_qstring);
    } else if (ss == "Palette"){ EXTERN_my_propertywindow->SETPROPERTY_Palette(d->display, d->set, d->v_qstring);
    } else if (ss == "MinimumWidth"){ EXTERN_my_propertywindow->SETPROPERTY_MinimumWidth(d->display, d->set, d->v_integer);
    } else if (ss == "MinimumHeight"){ EXTERN_my_propertywindow->SETPROPERTY_MinimumHeight(d->display, d->set, d->v_integer);
    } else if (ss == "MaximumWidth"){ EXTERN_my_propertywindow->SETPROPERTY_MaximumWidth(d->display, d->set, d->v_integer);
    } else if (ss == "MaximumHeight"){ EXTERN_my_propertywindow->SETPROPERTY_MaximumHeight(d->display, d->set, d->v_integer);
    } else if (ss == "StopOnClose"){ EXTERN_my_propertywindow->SETPROPERTY_StopOnClose(d->display, d->set, d->v_boolean);

    } else if (ss == "DockTitleVisible"){ EXTERN_my_propertywindow->SETPROPERTY_DockTitleVisible(d->display, d->set, d->v_boolean);
    } else if (ss == "DockParent"){ EXTERN_my_propertywindow->SETPROPERTY_DockOrder(d->display, d->set, d->v_qstring);

    } else if (ss == "DockSplit"){ EXTERN_my_propertywindow->SETPROPERTY_DockSplit(d->display, d->set, d->v_qstring);
    } else if (ss == "ShowMode"){ EXTERN_my_propertywindow->SETPROPERTY_ShowMode(d->display, d->set, d->v_qstring);


    } else if (ss == "DockWidth"){ EXTERN_my_propertywindow->SETPROPERTY_DockWidth(d->display, d->set, d->v_integer);
    } else if (ss == "DockHeight"){ EXTERN_my_propertywindow->SETPROPERTY_DockHeight(d->display, d->set, d->v_integer);

    } else if (ss == "BorderTop"){ EXTERN_my_propertywindow->SETPROPERTY_BorderTop(d->display, d->set, d->v_integer);
    } else if (ss == "BorderBottom"){ EXTERN_my_propertywindow->SETPROPERTY_BorderBottom(d->display, d->set, d->v_integer);
    } else if (ss == "BorderLeft"){ EXTERN_my_propertywindow->SETPROPERTY_BorderLeft(d->display, d->set, d->v_integer);
    } else if (ss == "BorderRight"){ EXTERN_my_propertywindow->SETPROPERTY_BorderRight(d->display, d->set, d->v_integer);
    } else if (ss == "CSV"){ EXTERN_my_propertywindow->SETPROPERTY_CSV(d->display, d->set, d->v_qstring);
    } else if (ss == "Tag"){ EXTERN_my_propertywindow->SETPROPERTY_Tag(d->display, d->set, d->v_qstring);

    } else if (ss == "TableView"){ EXTERN_my_propertywindow->SETPROPERTY_TableView(d->display, d->set, d->v_boolean);

    } else if (ss == "Scale"){ EXTERN_my_propertywindow->SETPROPERTY_Scale(d->display, d->set, d->v_boolean);

    } else if (ss == "DragDrop"){ EXTERN_my_propertywindow->SETPROPERTY_DragDrop(d->display, d->set, d->v_boolean);

    } else if (ss == "FocusPolicy"){ EXTERN_my_propertywindow->SETPROPERTY_FocusPolicy(d->display, d->set, d->v_qstring);
    } else if (ss == "FocusProxy"){ EXTERN_my_propertywindow->SETPROPERTY_FocusProxy(d->display, d->set, d->v_qstring);
    } else if (ss == "FocusOrder"){ EXTERN_my_propertywindow->SETPROPERTY_FocusOrder(d->display, d->set, d->v_integer);

    } else if (ss == "FontName"){ EXTERN_my_propertywindow->SETPROPERTY_FontName(d->display, d->set, d->v_qstring);
    } else if (ss == "FontSize"){ EXTERN_my_propertywindow->SETPROPERTY_FontSize(d->display, d->set, d->v_integer);

    } else if (ss == "FontBold"){ EXTERN_my_propertywindow->SETPROPERTY_FontBold(d->display, d->set, d->v_boolean);
    } else if (ss == "FontItalic"){ EXTERN_my_propertywindow->SETPROPERTY_FontItalic(d->display, d->set, d->v_boolean);
    } else if (ss == "FontUnderline"){ EXTERN_my_propertywindow->SETPROPERTY_FontUnderline(d->display, d->set, d->v_boolean);

    } else if (ss == "FontColor"){ EXTERN_my_propertywindow->SETPROPERTY_FontColor(d->display, d->set, d->v_qstring);
    } else if (ss == "StatusTip"){ EXTERN_my_propertywindow->SETPROPERTY_StatusTip(d->display, d->set, d->v_qstring);
    } else if (ss == "ToolTip"){ EXTERN_my_propertywindow->SETPROPERTY_ToolTip(d->display, d->set, d->v_qstring);
    } else if (ss == "StyleSheet"){ EXTERN_my_propertywindow->SETPROPERTY_StyleSheet(d->display, d->set, d->v_qstring);
    } else if (ss == "WhatsThis"){ EXTERN_my_propertywindow->SETPROPERTY_WhatsThis(d->display, d->set, d->v_qstring);

    } else if (ss == "Flag"){ EXTERN_my_propertywindow->SETPROPERTY_Flag(d->display, d->set, d->v_qstring);
    } else if (ss == "SQLControls"){ EXTERN_my_propertywindow->SETPROPERTY_SQLControls(d->display, d->set, d->v_qstring);
    } else if (ss == "Icon"){ EXTERN_my_propertywindow->SETPROPERTY_Icon(d->display, d->set, d->v_qstring);
    } else if (ss == "Caption"){ EXTERN_my_propertywindow->SETPROPERTY_Caption(d->display, d->set, d->v_qstring);

    } else if (ss == "Modal"){ EXTERN_my_propertywindow->SETPROPERTY_Modal(d->display, d->set, d->v_boolean);
    } else if (ss == "Opacity"){ EXTERN_my_propertywindow->SETPROPERTY_Opacity(d->display, d->set, d->v_integer);
    } else if (ss == "TimerInterval"){ EXTERN_my_propertywindow->SETPROPERTY_TimerInterval(d->display, d->set, d->v_integer);

    } else if (ss == "ScrollX"){ EXTERN_my_propertywindow->SETPROPERTY_ScrollX(d->display, d->set, d->v_integer);
    } else if (ss == "ScrollY"){ EXTERN_my_propertywindow->SETPROPERTY_ScrollY(d->display, d->set, d->v_integer);
    } else if (ss == "ScrollWidth"){ EXTERN_my_propertywindow->SETPROPERTY_ScrollWidth(d->display, d->set, d->v_integer);
    } else if (ss == "ScrollHeight"){ EXTERN_my_propertywindow->SETPROPERTY_ScrollHeight(d->display, d->set, d->v_integer);

    } else if (ss == "MultiPageHeight"){ EXTERN_my_propertywindow->SETPROPERTY_MultiPageHeight(d->display, d->set, d->v_integer);
    } else if (ss == "MultiPageBorderTop"){ EXTERN_my_propertywindow->SETPROPERTY_MultiPageBorderTop(d->display, d->set, d->v_integer);
    } else if (ss == "MultiPageBorderBottom"){ EXTERN_my_propertywindow->SETPROPERTY_MultiPageBorderBottom(d->display, d->set, d->v_integer);
    } else if (ss == "MultiPageBorderLeft"){ EXTERN_my_propertywindow->SETPROPERTY_MultiPageBorderLeft(d->display, d->set, d->v_integer);
    } else if (ss == "MultiPageBorderRight"){ EXTERN_my_propertywindow->SETPROPERTY_MultiPageBorderRight(d->display, d->set, d->v_integer);

    } else if (ss == "Shadow"){ EXTERN_my_propertywindow->SETPROPERTY_Shadow(d->display, d->set, d->v_boolean);
    } else if (ss == "Shape"){ EXTERN_my_propertywindow->SETPROPERTY_Shape(d->display, d->set, d->v_boolean);
    } else if (ss == "OpenLinks"){ EXTERN_my_propertywindow->SETPROPERTY_OpenLinks(d->display, d->set, d->v_boolean);

    } else if (ss == "Icon"){ EXTERN_my_propertywindow->SETPROPERTY_Icon(d->display, d->set, d->v_qstring);
    } else if (ss == "InputControl"){ EXTERN_my_propertywindow->SETPROPERTY_InputControl(d->display, d->set, d->v_qstring);

    } else if (ss == "Space"){ EXTERN_my_propertywindow->SETPROPERTY_Space(d->display, d->set, d->v_integer);
    } else if (ss == "Border"){ EXTERN_my_propertywindow->SETPROPERTY_Border(d->display, d->set, d->v_integer);

    } else if (ss == "Flat"){ EXTERN_my_propertywindow->SETPROPERTY_Flat(d->display, d->set, d->v_boolean);

    } else if (ss == "Key"){ EXTERN_my_propertywindow->SETPROPERTY_Key(d->display, d->set, d->v_qstring);
    } else if (ss == "IntegerMinimum"){ EXTERN_my_propertywindow->SETPROPERTY_IntegerMinimum(d->display, d->set, d->v_integer);
    } else if (ss == "IntegerMaximum"){ EXTERN_my_propertywindow->SETPROPERTY_IntegerMaximum(d->display, d->set, d->v_integer);
    } else if (ss == "Completer"){ EXTERN_my_propertywindow->SETPROPERTY_Completer(d->display, d->set, d->v_qstring);

    } else if (ss == "ValidatorDouble"){ EXTERN_my_propertywindow->SETPROPERTY_ValidatorDouble(d->display, d->set, d->v_boolean);
    } else if (ss == "ValidatorInteger"){ EXTERN_my_propertywindow->SETPROPERTY_ValidatorInteger(d->display, d->set, d->v_boolean);

    //} else if (ss == "ValidatorRegEx"){ EXTERN_my_propertywindow->SETPROPERTY_ValidatorRegEx(d->display, d->set, d->v_qstring);
    //} else if (ss == "ValidatorRegEx2"){ EXTERN_my_propertywindow->SETPROPERTY_ValidatorRegEx2(d->display, d->set, d->v_qstring);
    
    } else if (ss == "DoubleEntry"){ EXTERN_my_propertywindow->SETPROPERTY_DoubleEntry(d->display, d->set, d->v_boolean);
    } else if (ss == "InsertPolicy"){ EXTERN_my_propertywindow->SETPROPERTY_InsertPolicy(d->display, d->set, d->v_qstring);
    } else if (ss == "Editable"){ EXTERN_my_propertywindow->SETPROPERTY_Editable(d->display, d->set, d->v_boolean);
    } else if (ss == "MaximumVisible"){ EXTERN_my_propertywindow->SETPROPERTY_MaximumVisible(d->display, d->set, d->v_integer);
    } else if (ss == "Sorted"){ EXTERN_my_propertywindow->SETPROPERTY_Sorted(d->display, d->set, d->v_boolean);
    } else if (ss == "RootIsDecorated"){ EXTERN_my_propertywindow->SETPROPERTY_RootIsDecorated(d->display, d->set, d->v_boolean);

    

    } else if (ss == "StringMaximum"){ EXTERN_my_propertywindow->SETPROPERTY_StringMaximum(d->display, d->set, d->v_qstring);
    } else if (ss == "StringMinimum"){ EXTERN_my_propertywindow->SETPROPERTY_StringMinimum(d->display, d->set, d->v_qstring);
    } else if (ss == "Format"){ EXTERN_my_propertywindow->SETPROPERTY_Format(d->display, d->set, d->v_qstring);
    } else if (ss == "PopUp"){ EXTERN_my_propertywindow->SETPROPERTY_PopUp(d->display, d->set, d->v_boolean);

    } else if (ss == "ScrollBar"){ EXTERN_my_propertywindow->SETPROPERTY_ScrollBar(d->display, d->set, d->v_qstring);

    } else if (ss == "MouseDownImage"){ EXTERN_my_propertywindow->SETPROPERTY_MouseDownImage(d->display, d->set, d->v_qstring);
    } else if (ss == "MouseUpImage"){ EXTERN_my_propertywindow->SETPROPERTY_MouseUpImage(d->display, d->set, d->v_qstring);
    } else if (ss == "EnabledImage"){ EXTERN_my_propertywindow->SETPROPERTY_EnabledImage(d->display, d->set, d->v_qstring);

    } else if (ss == "CheckMouseDownImage"){ EXTERN_my_propertywindow->SETPROPERTY_CheckMouseDownImage(d->display, d->set, d->v_qstring);
    } else if (ss == "CheckMouseUpImage"){ EXTERN_my_propertywindow->SETPROPERTY_CheckMouseUpImage(d->display, d->set, d->v_qstring);
    } else if (ss == "CheckEnabledImage"){ EXTERN_my_propertywindow->SETPROPERTY_CheckEnabledImage(d->display, d->set, d->v_qstring);

    } else if (ss == "MouseDownSound"){ EXTERN_my_propertywindow->SETPROPERTY_MouseDownSound(d->display, d->set, d->v_qstring);
    } else if (ss == "MouseUpSound"){ EXTERN_my_propertywindow->SETPROPERTY_MouseUpSound(d->display, d->set, d->v_qstring);

    } else if (ss == "HomeURL"){ EXTERN_my_propertywindow->SETPROPERTY_HomeURL(d->display, d->set, d->v_qstring);

    } else if (ss == "Enabled"){
     EXTERN_my_propertywindow->SETPROPERTY_Enabled(d->display, d->set, d->v_boolean);
    } else if (ss == "Flip"){
     EXTERN_my_propertywindow->SETPROPERTY_Flip(d->display, d->set, d->v_boolean);
    } else if (ss == "Cursor"){
     EXTERN_my_propertywindow->SETPROPERTY_Cursor(d->display, d->set, d->v_qstring);
   // } else if (ss == "TabIndex"){
    // EXTERN_my_propertywindow->SETPROPERTY_TabIndex(d->display, d->set, d->v_integer);
    } else if (ss == "Tag"){
     EXTERN_my_propertywindow->SETPROPERTY_Tag(d->display, d->set, d->v_qstring);
    } else if (ss == "Visible"){
     EXTERN_my_propertywindow->SETPROPERTY_Visible(d->display, d->set, d->v_boolean);
    } else if (ss == "Resizable"){
     EXTERN_my_propertywindow->SETPROPERTY_Resizable(d->display, d->set, d->v_boolean);     

    } else if (ss == "ResizableSmaller"){
     EXTERN_my_propertywindow->SETPROPERTY_ResizableSmaller(d->display, d->set, d->v_boolean);     
    } else if (ss == "ResizableBigger"){
     EXTERN_my_propertywindow->SETPROPERTY_ResizableBigger(d->display, d->set, d->v_boolean);     

    } else if (ss == "WordWrap"){
     EXTERN_my_propertywindow->SETPROPERTY_WordWrap(d->display, d->set, d->v_boolean);
    } else if (ss == "ReadOnly"){
     EXTERN_my_propertywindow->SETPROPERTY_ReadOnly(d->display, d->set, d->v_boolean);
    } else if (ss == "Alignment"){
     EXTERN_my_propertywindow->SETPROPERTY_Alignment(d->display, d->set, d->v_qstring);
    } else if (ss == "EchoMode"){
     EXTERN_my_propertywindow->SETPROPERTY_EchoMode(d->display, d->set, d->v_qstring);
    } else if (ss == "Feature"){
     EXTERN_my_propertywindow->SETPROPERTY_Feature(d->display, d->set, d->v_qstring);
    } else if (ss == "Orientation"){
     EXTERN_my_propertywindow->SETPROPERTY_Orientation(d->display, d->set, d->v_qstring);


    

    } else if (ss == "EnterImage"){
     EXTERN_my_propertywindow->SETPROPERTY_EnterImage(d->display, d->set, d->v_qstring);

    } else if (ss == "ExitImage"){
     EXTERN_my_propertywindow->SETPROPERTY_ExitImage(d->display, d->set, d->v_qstring);

    } else if (ss == "CheckDisabledImage"){
     EXTERN_my_propertywindow->SETPROPERTY_CheckDisabledImage(d->display, d->set, d->v_qstring);

    } else if (ss == "CheckEnterImage"){
     EXTERN_my_propertywindow->SETPROPERTY_CheckEnterImage(d->display, d->set, d->v_qstring);

    } else if (ss == "CheckExitImage"){
     EXTERN_my_propertywindow->SETPROPERTY_CheckExitImage(d->display, d->set, d->v_qstring);

    } else if (ss == "DisabledImage"){
     EXTERN_my_propertywindow->SETPROPERTY_DisabledImage(d->display, d->set, d->v_qstring);

    } else if (ss == "EnterSound"){
     EXTERN_my_propertywindow->SETPROPERTY_EnterSound(d->display, d->set, d->v_qstring);

    } else if (ss == "ExitSound"){
     EXTERN_my_propertywindow->SETPROPERTY_ExitSound(d->display, d->set, d->v_qstring);

    } else if (ss == "Group"){
     EXTERN_my_propertywindow->SETPROPERTY_Group(d->display, d->set, d->v_qstring);

    } else if (ss == "Menu"){
     EXTERN_my_propertywindow->SETPROPERTY_Menu(d->display, d->set, d->v_boolean);

    } else if (ss == "Interval"){
     EXTERN_my_propertywindow->SETPROPERTY_Interval(d->display, d->set, d->v_integer);

    }

    if (ss == "Brightness"){ EXTERN_my_propertywindow->SETPROPERTY_Brightness(d->display, d->set, d->v_integer);
    } else if (ss == "Contrast"){ EXTERN_my_propertywindow->SETPROPERTY_Contrast(d->display, d->set, d->v_integer);
    } else if (ss == "Hue"){ EXTERN_my_propertywindow->SETPROPERTY_Hue(d->display, d->set, d->v_integer);
    } else if (ss == "Saturation"){ EXTERN_my_propertywindow->SETPROPERTY_Saturation(d->display, d->set, d->v_integer);
    } else if (ss == "ScaleMode"){ EXTERN_my_propertywindow->SETPROPERTY_ScaleMode(d->display, d->set, d->v_qstring);
    } else if (ss == "AspectRatio"){ EXTERN_my_propertywindow->SETPROPERTY_AspectRatio(d->display, d->set, d->v_qstring);

    } else if (ss == "TransitionTime"){ EXTERN_my_propertywindow->SETPROPERTY_TransitionTime(d->display, d->set, d->v_integer);
    } else if (ss == "Muted"){ EXTERN_my_propertywindow->SETPROPERTY_Muted(d->display, d->set, d->v_boolean);
    } else if (ss == "Volume"){ EXTERN_my_propertywindow->SETPROPERTY_Volume(d->display, d->set, d->v_integer);
    } else if (ss == "PrefinishMark"){ EXTERN_my_propertywindow->SETPROPERTY_PrefinishMark(d->display, d->set, d->v_integer);
    } else if (ss == "Tick"){ EXTERN_my_propertywindow->SETPROPERTY_Tick(d->display, d->set, d->v_integer);

    } else if (ss == "OnTick"){EXTERN_my_propertywindow->SETPROPERTY_OnTick(d->display, d->set, d->v_event);
    } else if (ss == "OnStateChanged"){EXTERN_my_propertywindow->SETPROPERTY_OnStateChanged(d->display, d->set, d->v_event);
    } else if (ss == "OnAboutToFinish"){EXTERN_my_propertywindow->SETPROPERTY_OnAboutToFinish(d->display, d->set, d->v_event);
    } else if (ss == "OnFinished"){EXTERN_my_propertywindow->SETPROPERTY_OnFinished(d->display, d->set, d->v_event);
    } else if (ss == "OnMutedChanged"){EXTERN_my_propertywindow->SETPROPERTY_OnMutedChanged(d->display, d->set, d->v_event);
    } else if (ss == "OnVolumeChanged"){EXTERN_my_propertywindow->SETPROPERTY_OnVolumeChanged(d->display, d->set, d->v_event);
    } else if (ss == "OnPlayedTitleChanged"){EXTERN_my_propertywindow->SETPROPERTY_OnPlayingTitleChanged(d->display, d->set, d->v_event);
    } else if (ss == "OnBufferStatus"){EXTERN_my_propertywindow->SETPROPERTY_OnBufferStatus(d->display, d->set, d->v_event);
    } else if (ss == "OnTotalTimeChanged"){EXTERN_my_propertywindow->SETPROPERTY_OnTotalTimeChanged(d->display, d->set, d->v_event);
	}


    // PROPERTY
     
    if (ss == "OpenOnRun"){ EXTERN_my_propertywindow->SETPROPERTY_OpenAtStartup(d->display, d->set, d->v_boolean);
    } else if (ss == "Prefix"){ EXTERN_my_propertywindow->SETPROPERTY_Prefix(d->display, d->set, d->v_qstring);
    } else if (ss == "Suffix"){ EXTERN_my_propertywindow->SETPROPERTY_Suffix(d->display, d->set, d->v_qstring);

    } else if (ss == "Description"){ EXTERN_my_propertywindow->SETPROPERTY_Description(d->display, d->set, d->v_qstring);
    } else if (ss == "ViewMode"){ EXTERN_my_propertywindow->SETPROPERTY_ViewMode(d->display, d->set, d->v_qstring);
    
    } else if (ss == "TickPosition"){ EXTERN_my_propertywindow->SETPROPERTY_TickPosition(d->display, d->set, d->v_qstring);
    } else if (ss == "InvertedAppearance"){ EXTERN_my_propertywindow->SETPROPERTY_InvertedAppearance(d->display, d->set, d->v_boolean);
    } else if (ss == "InvertedControls"){ EXTERN_my_propertywindow->SETPROPERTY_InvertedControls(d->display, d->set, d->v_boolean);
    } else if (ss == "Tracking"){ EXTERN_my_propertywindow->SETPROPERTY_Tracking(d->display, d->set, d->v_boolean);
    } else if (ss == "TickInterval"){ EXTERN_my_propertywindow->SETPROPERTY_TickInterval(d->display, d->set, d->v_integer);
    } else if (ss == "PageStep"){ EXTERN_my_propertywindow->SETPROPERTY_PageStep(d->display, d->set, d->v_integer);
    } else if (ss == "SingleStep"){ EXTERN_my_propertywindow->SETPROPERTY_SingleStep(d->display, d->set, d->v_integer);
    
    } else if (ss == "MoveOnMouseDrag"){ EXTERN_my_propertywindow->SETPROPERTY_MoveOnMouseDrag(d->display, d->set, d->v_boolean);
    } else if (ss == "MouseTracking"){ EXTERN_my_propertywindow->SETPROPERTY_MouseTracking(d->display, d->set, d->v_boolean);
    } else if (ss == "DrawOnPaint"){ EXTERN_my_propertywindow->SETPROPERTY_DrawOnPaint(d->display, d->set, d->v_boolean);
    } else if (ss == "SoundOnEvent"){ EXTERN_my_propertywindow->SETPROPERTY_SoundOnEvent(d->display, d->set, d->v_qstring);
    } else if (ss == "ActionId"){ EXTERN_my_propertywindow->SETPROPERTY_ActionId(d->display, d->set, d->v_qstring);
    
    } else if (ss == "CursorAnimation"){ EXTERN_my_propertywindow->SETPROPERTY_CursorAnimation(d->display, d->set, d->v_qstring);
    
    } else if (ss == "Mask"){ EXTERN_my_propertywindow->SETPROPERTY_Mask(d->display, d->set, d->v_qstring);
    } else if (ss == "Dock"){ EXTERN_my_propertywindow->SETPROPERTY_Dock(d->display, d->set, d->v_qstring);
    } else if (ss == "Layout"){ EXTERN_my_propertywindow->SETPROPERTY_Layout(d->display, d->set, d->v_qstring);
    } else if (ss == "SelectionMode"){ EXTERN_my_propertywindow->SETPROPERTY_SelectionMode(d->display, d->set, d->v_qstring);
    } else if (ss == "AlternatingRowColors"){ EXTERN_my_propertywindow->SETPROPERTY_AlternatingRowColors(d->display, d->set, d->v_boolean);
    } else if (ss == "Checked"){ EXTERN_my_propertywindow->SETPROPERTY_Checked(d->display, d->set, d->v_boolean);
    } else if (ss == "CheckableExclusive"){ EXTERN_my_propertywindow->SETPROPERTY_CheckableExclusive(d->display, d->set, d->v_boolean);

    } else if (ss == "ContextMenu"){ EXTERN_my_propertywindow->SETPROPERTY_ContextMenu(d->display, d->set, d->v_qstring);
    } else if (ss == "Comment1Begin"){ EXTERN_my_propertywindow->SETPROPERTY_Comment1Begin(d->display, d->set, d->v_qstring);
    } else if (ss == "Comment1End"){ EXTERN_my_propertywindow->SETPROPERTY_Comment1End(d->display, d->set, d->v_qstring);
    } else if (ss == "Comment2Begin"){ EXTERN_my_propertywindow->SETPROPERTY_Comment2Begin(d->display, d->set, d->v_qstring);
    //} else if (ss == "Comment2End"){ EXTERN_my_propertywindow->SETPROPERTY_Comment2End(d->display, d->set, d->v_qstring);
    } else if (ss == "Keywords"){ EXTERN_my_propertywindow->SETPROPERTY_Keywords(d->display, d->set, d->v_qstring);
    } else if (ss == "Commands"){ EXTERN_my_propertywindow->SETPROPERTY_Commands(d->display, d->set, d->v_qstring);
    } else if (ss == "CommentColor"){ EXTERN_my_propertywindow->SETPROPERTY_CommentColor(d->display, d->set, d->v_qstring);
    } else if (ss == "KeywordColor"){ EXTERN_my_propertywindow->SETPROPERTY_KeywordColor(d->display, d->set, d->v_qstring);
    } else if (ss == "CommandColor"){ EXTERN_my_propertywindow->SETPROPERTY_CommandColor(d->display, d->set, d->v_qstring);
    }
    
    if (ss == "PortName"){ EXTERN_my_propertywindow->SETPROPERTY_PortName(d->display, d->set, d->v_qstring);
    } else if (ss == "BaudRate"){ EXTERN_my_propertywindow->SETPROPERTY_BaudRate(d->display, d->set, d->v_qstring);
    } else if (ss == "DataBits"){ EXTERN_my_propertywindow->SETPROPERTY_DataBits(d->display, d->set, d->v_qstring);
    } else if (ss == "Parity"){ EXTERN_my_propertywindow->SETPROPERTY_Parity(d->display, d->set, d->v_qstring);
    } else if (ss == "FlowControl"){ EXTERN_my_propertywindow->SETPROPERTY_FlowControl(d->display, d->set, d->v_qstring);    
    } else if (ss == "StopBits"){ EXTERN_my_propertywindow->SETPROPERTY_StopBits(d->display, d->set, d->v_qstring);
    } else if (ss == "TimeOutMillisec"){ EXTERN_my_propertywindow->SETPROPERTY_TimeOutMillisec(d->display, d->set, d->v_integer);
    } else if (ss == "PollingInterval"){ EXTERN_my_propertywindow->SETPROPERTY_PollingInterval(d->display, d->set, d->v_integer);

    } else if (ss == "SQL"){ EXTERN_my_propertywindow->SETPROPERTY_SQL(d->display, d->set, d->v_qstring);

    } else if (ss == "SQLName"){ EXTERN_my_propertywindow->SETPROPERTY_SQLName(d->display, d->set, d->v_qstring);
    } else if (ss == "SQLRelation"){ EXTERN_my_propertywindow->SETPROPERTY_SQLRelation(d->display, d->set, d->v_qstring);
    } else if (ss == "SQLInsert"){ EXTERN_my_propertywindow->SETPROPERTY_SQLInsert(d->display, d->set, d->v_boolean);
    } else if (ss == "SQLUpdate"){ EXTERN_my_propertywindow->SETPROPERTY_SQLUpdate(d->display, d->set, d->v_boolean);
    } else if (ss == "SQLDelete"){ EXTERN_my_propertywindow->SETPROPERTY_SQLDelete(d->display, d->set, d->v_boolean);
    }

    if (ss == "TableViewCaption"){ EXTERN_my_propertywindow->SETPROPERTY_TableViewCaption(d->display, d->set, d->v_qstring);
    //} else if (ss == "TableViewSort"){ EXTERN_my_propertywindow->SETPROPERTY_TableViewSort(d->display, d->set, d->v_qstring);
    //} else if (ss == "TableViewFilter"){ EXTERN_my_propertywindow->SETPROPERTY_TableViewFilter(d->display, d->set, d->v_qstring);
    } else if (ss == "TableViewWidth"){ EXTERN_my_propertywindow->SETPROPERTY_TableViewWidth(d->display, d->set, d->v_integer);
    } else if (ss == "TableViewVisible"){ EXTERN_my_propertywindow->SETPROPERTY_TableViewVisible(d->display, d->set, d->v_boolean);
    //} else if (ss == "TableViewOrder"){ EXTERN_my_propertywindow->SETPROPERTY_TableViewOrder(d->display, d->set, d->v_integer);


    } else if (ss == "Pages"){
     EXTERN_my_propertywindow->SETPROPERTY_Pages(d->display, d->set, d->v_qstring);

     /*
    } else if (ss == "ParentForm"){
     EXTERN_my_propertywindow->SETPROPERTY_ParentForm(d->display, d->set, d->v_qstring);

    } else if (ss == "ParentControl"){
     EXTERN_my_propertywindow->SETPROPERTY_ParentControl(d->display, d->set, d->v_qstring);
*/

    } else if (ss == "StringValue"){
     EXTERN_my_propertywindow->SETPROPERTY_StringValue(d->display, d->set, d->v_qstring);

    } else if (ss == "InputMask"){
     EXTERN_my_propertywindow->SETPROPERTY_InputMask(d->display, d->set, d->v_qstring);

    } else if (ss == "Separator"){
     EXTERN_my_propertywindow->SETPROPERTY_Separator(d->display, d->set, d->v_boolean);

    } else if (ss == "EventOnOpen"){
     EXTERN_my_propertywindow->SETPROPERTY_EventOnOpen(d->display, d->set, d->v_boolean);

    } else if (ss == "AcceptRichText"){
     EXTERN_my_propertywindow->SETPROPERTY_AcceptRichText(d->display, d->set, d->v_boolean);

    } else if (ss == "AutoDefault"){
     EXTERN_my_propertywindow->SETPROPERTY_AutoDefault(d->display, d->set, d->v_boolean);

    } else if (ss == "Default"){
     EXTERN_my_propertywindow->SETPROPERTY_Default(d->display, d->set, d->v_boolean);

    } else if (ss == "Checkable"){
     EXTERN_my_propertywindow->SETPROPERTY_Checkable(d->display, d->set, d->v_boolean);     

    } else if (ss == "BooleanValue"){
     EXTERN_my_propertywindow->SETPROPERTY_BooleanValue(d->display, d->set, d->v_boolean);

    // EVENT
    } 
    
    if (ss == "OnEvent"){ EXTERN_my_propertywindow->SETPROPERTY_OnEvent(d->display, d->set, d->v_event);       

    //} else if (ss == "OnCursorPositionChanged"){ EXTERN_my_propertywindow->SETPROPERTY_OnCursorPositionChanged(d->display, d->set, d->v_event);
    } else if (ss == "OnEditingFinished"){ EXTERN_my_propertywindow->SETPROPERTY_OnEditingFinished(d->display, d->set, d->v_event);
    } else if (ss == "OnReturnPressed"){ EXTERN_my_propertywindow->SETPROPERTY_OnReturnPressed(d->display, d->set, d->v_event);
    } else if (ss == "OnSelectionChanged"){ EXTERN_my_propertywindow->SETPROPERTY_OnSelectionChanged(d->display, d->set, d->v_event);
    } else if (ss == "OnTextChanged"){ EXTERN_my_propertywindow->SETPROPERTY_OnTextChanged(d->display, d->set, d->v_event);
    } else if (ss == "OnTextEdited"){ EXTERN_my_propertywindow->SETPROPERTY_OnTextEdited(d->display, d->set, d->v_event);

    } else if (ss == "OnPage"){ EXTERN_my_propertywindow->SETPROPERTY_OnPage(d->display, d->set, d->v_event);
    } else if (ss == "OnLinkHovered"){ EXTERN_my_propertywindow->SETPROPERTY_OnLinkHovered(d->display, d->set, d->v_event);
    } else if (ss == "OnLoadFinished"){ EXTERN_my_propertywindow->SETPROPERTY_OnLoadFinished(d->display, d->set, d->v_event);
    } else if (ss == "OnLoadProgress"){ EXTERN_my_propertywindow->SETPROPERTY_OnLoadProgress(d->display, d->set, d->v_event);
    } else if (ss == "OnLoadStarted"){ EXTERN_my_propertywindow->SETPROPERTY_OnLoadStarted(d->display, d->set, d->v_event);
    } else if (ss == "OnWindowCloseRequested"){ EXTERN_my_propertywindow->SETPROPERTY_OnWindowCloseRequested(d->display, d->set, d->v_event);

    } else if (ss == "OnSingleShot"){ EXTERN_my_propertywindow->SETPROPERTY_OnSingleShot(d->display, d->set, d->v_event);
    } else if (ss == "OnAction"){ EXTERN_my_propertywindow->SETPROPERTY_OnAction(d->display, d->set, d->v_event);
    } else if (ss == "OnCursorPositionChanged"){ EXTERN_my_propertywindow->SETPROPERTY_OnCursorPositionChanged(d->display, d->set, d->v_event);

    } else if (ss == "OnOpen"){ EXTERN_my_propertywindow->SETPROPERTY_OnOpen(d->display, d->set, d->v_event);
    } else if (ss == "OnClose"){ EXTERN_my_propertywindow->SETPROPERTY_OnClose(d->display, d->set, d->v_event);
    } else if (ss == "OnGoTo"){ EXTERN_my_propertywindow->SETPROPERTY_OnGoTo(d->display, d->set, d->v_event);
    } else if (ss == "OnBeforeInsert"){ EXTERN_my_propertywindow->SETPROPERTY_OnBeforeInsert(d->display, d->set, d->v_event);
    } else if (ss == "OnBeforeDelete"){ EXTERN_my_propertywindow->SETPROPERTY_OnBeforeDelete(d->display, d->set, d->v_event);
    } else if (ss == "OnPaint"){ EXTERN_my_propertywindow->SETPROPERTY_OnPaint(d->display, d->set, d->v_event);

    } else if (ss == "OnDragEnter"){EXTERN_my_propertywindow->SETPROPERTY_OnDragEnter(d->display, d->set, d->v_event);
    } else if (ss == "OnDragExit"){EXTERN_my_propertywindow->SETPROPERTY_OnDragExit(d->display, d->set, d->v_event);
    } else if (ss == "OnDragMove"){EXTERN_my_propertywindow->SETPROPERTY_OnDragMove(d->display, d->set, d->v_event);
    } else if (ss == "OnDrop"){EXTERN_my_propertywindow->SETPROPERTY_OnDrop(d->display, d->set, d->v_event);

    //} else if (ss == "OnContextMenu"){EXTERN_my_propertywindow->SETPROPERTY_OnContextMenu(d->display, d->set, d->v_event);
    } else if (ss == "OnMouseWheel"){EXTERN_my_propertywindow->SETPROPERTY_OnMouseWheel(d->display, d->set, d->v_event);
    } else if (ss == "OnMultiPageShow"){EXTERN_my_propertywindow->SETPROPERTY_OnMultiPageShow(d->display, d->set, d->v_event);
    } else if (ss == "OnScroll"){EXTERN_my_propertywindow->SETPROPERTY_OnScroll(d->display, d->set, d->v_event);
    
    
    } else if (ss == "OnResize"){EXTERN_my_propertywindow->SETPROPERTY_OnResize(d->display, d->set, d->v_event);
    } else if (ss == "OnShow"){EXTERN_my_propertywindow->SETPROPERTY_OnShow(d->display, d->set, d->v_event);
    } else if (ss == "OnEnabled"){EXTERN_my_propertywindow->SETPROPERTY_OnEnabled(d->display, d->set, d->v_event);
    } else if (ss == "OnDisabled"){EXTERN_my_propertywindow->SETPROPERTY_OnDisabled(d->display, d->set, d->v_event);
    } else if (ss == "OnHide"){EXTERN_my_propertywindow->SETPROPERTY_OnHide(d->display, d->set, d->v_event);
    } else if (ss == "OnMove"){EXTERN_my_propertywindow->SETPROPERTY_OnMove(d->display, d->set, d->v_event);

    } else if (ss == "OnDirty"){EXTERN_my_propertywindow->SETPROPERTY_OnDirty(d->display, d->set, d->v_event);
    } else if (ss == "OnAddNew"){EXTERN_my_propertywindow->SETPROPERTY_OnAddNew(d->display, d->set, d->v_event);
    } else if (ss == "OnQuery"){EXTERN_my_propertywindow->SETPROPERTY_OnQuery(d->display, d->set, d->v_event);

    } else if (ss == "OnTimer"){EXTERN_my_propertywindow->SETPROPERTY_OnTimer(d->display, d->set, d->v_event);

    //} else if (ss == "OnPrint"){EXTERN_my_propertywindow->SETPROPERTY_OnPrint(d->display, d->set, d->v_event);

    } else if (ss == "OnCurrentItemChanged"){EXTERN_my_propertywindow->SETPROPERTY_OnCurrentItemChanged(d->display, d->set, d->v_event);
    } else if (ss == "OnItemActivated"){EXTERN_my_propertywindow->SETPROPERTY_OnItemActivated(d->display, d->set, d->v_event);
    } else if (ss == "OnItemChanged"){EXTERN_my_propertywindow->SETPROPERTY_OnItemChanged(d->display, d->set, d->v_event);
    } else if (ss == "OnItemClicked"){EXTERN_my_propertywindow->SETPROPERTY_OnItemClicked(d->display, d->set, d->v_event);
    } else if (ss == "OnItemCollapsed"){EXTERN_my_propertywindow->SETPROPERTY_OnItemCollapsed(d->display, d->set, d->v_event);
    } else if (ss == "OnItemDoubleClicked"){EXTERN_my_propertywindow->SETPROPERTY_OnItemDoubleClicked(d->display, d->set, d->v_event);
    } else if (ss == "OnItemEntered"){EXTERN_my_propertywindow->SETPROPERTY_OnItemEntered(d->display, d->set, d->v_event);
    } else if (ss == "OnItemExpanded"){EXTERN_my_propertywindow->SETPROPERTY_OnItemExpanded(d->display, d->set, d->v_event);
    } else if (ss == "OnItemPressed"){EXTERN_my_propertywindow->SETPROPERTY_OnItemPressed(d->display, d->set, d->v_event);
    } else if (ss == "OnItemSelectionChanged"){EXTERN_my_propertywindow->SETPROPERTY_OnItemSelectionChanged(d->display, d->set, d->v_event);

    } else if (ss == "OnDockMove"){EXTERN_my_propertywindow->SETPROPERTY_OnDockMove(d->display, d->set, d->v_event);
    } else if (ss == "OnDockShow"){EXTERN_my_propertywindow->SETPROPERTY_OnDockShow(d->display, d->set, d->v_event);
    } else if (ss == "OnDockHide"){EXTERN_my_propertywindow->SETPROPERTY_OnDockHide(d->display, d->set, d->v_event);
    } else if (ss == "OnDockFloating"){EXTERN_my_propertywindow->SETPROPERTY_OnDockFloating(d->display, d->set, d->v_event);
    } else if (ss == "OnDockNotFloating"){EXTERN_my_propertywindow->SETPROPERTY_OnDockNotFloating(d->display, d->set, d->v_event);


    } else if (ss == "OnClick"){
     EXTERN_my_propertywindow->SETPROPERTY_OnClick(d->display, d->set, d->v_event);

    } else if (ss == "OnDblClick"){
     EXTERN_my_propertywindow->SETPROPERTY_OnDblClick(d->display, d->set, d->v_event);

    } else if (ss == "OnMouseDown"){
     EXTERN_my_propertywindow->SETPROPERTY_OnMouseDown(d->display, d->set, d->v_event);

    } else if (ss == "OnMouseUp"){
     EXTERN_my_propertywindow->SETPROPERTY_OnMouseUp(d->display, d->set, d->v_event);

    } else if (ss == "OnMouseMove"){
     EXTERN_my_propertywindow->SETPROPERTY_OnMouseMove(d->display, d->set, d->v_event);

    } else if (ss == "OnGotFocus"){
     EXTERN_my_propertywindow->SETPROPERTY_OnGotFocus(d->display, d->set, d->v_event);

    } else if (ss == "OnLostFocus"){
     EXTERN_my_propertywindow->SETPROPERTY_OnLostFocus(d->display, d->set, d->v_event);

    } else if (ss == "OnEnter"){
     EXTERN_my_propertywindow->SETPROPERTY_OnEnter(d->display, d->set, d->v_event);

    } else if (ss == "OnExit"){
     EXTERN_my_propertywindow->SETPROPERTY_OnExit(d->display, d->set, d->v_event);

    }// else 
      
    if (ss == "OnKeyDown"){
     EXTERN_my_propertywindow->SETPROPERTY_OnKeyDown(d->display, d->set, d->v_event);

    } else if (ss == "OnKeyUp"){
     EXTERN_my_propertywindow->SETPROPERTY_OnKeyUp(d->display, d->set, d->v_event);

    } else if (ss == "OnKeyPress"){
     EXTERN_my_propertywindow->SETPROPERTY_OnKeyPress(d->display, d->set, d->v_event);

    } else if (ss == "OnBeforeUpdate"){
     EXTERN_my_propertywindow->SETPROPERTY_OnBeforeUpdate(d->display, d->set, d->v_event);


    }

    

    // ***

  }
re:
  EXTERN_my_propertywindow->unlock();
  EXTERN_my_propertywindow->setUpdatesEnabled(true);
  if (bb){
    EXTERN_my_propertywindow->setEnabled(p.count()); nPropertyWindowForWhat = isForm() ? 0 : 3;
  }


  bPerformUndoRedo = false;

}



void _form::updatePropertyWindow(bool b)
{

  QWidget *c;
  
  p.clear();


  bool bForm = true;
  bool bb = true;
  int nn = 0;

  if (firstControl(&c)){

    do {

      if (c->acceptDrops()){ // missused as selected flag        
        bForm = false;

      #define SWITCH getProperties();
      #define SWITCH3 p2
      #include "_form_property_switch.h"    
      #undef SWITCH3
        nn++;

        if (bb){
          bb = false;

          _property::addProperties(&p, p2);
          EXTERN_my_propertywindow->showControlName(" " + p["Name"]->v_qstring);

        } else {          

          _property::mergeProperties(&p, p2);
        }

      }

    } while (nextControl(&c));
    
  }
  if (bb == false && nn > 1) EXTERN_my_propertywindow->showControlName(QString(" %1 controls selected").arg(nn));
  else if (nn == 0){
    EXTERN_my_propertywindow->showControlName(" no control selected");
    EXTERN_my_propertywindow->SETPROPERTY_ControlType(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_Group(false, false, "");

  }
  EXTERN_my_propertywindow->setform->setHidden(false);
  static const QIcon &report2 = kbasicIcon(idePath("VIEW_REPORT.png"));
  static const QIcon &form2 = kbasicIcon(idePath("VIEW_FORM.png"));

  if (isReport()){
    const QIcon &icon = EXTERN_my_propertywindow->setform->icon();
    if (icon.serialNumber() != report2.serialNumber()) EXTERN_my_propertywindow->setform->setIcon(report2);
  } else {
    const QIcon &icon = EXTERN_my_propertywindow->setform->icon();
    if (icon.serialNumber() != report2.serialNumber()) EXTERN_my_propertywindow->setform->setIcon(report2);
  }

  EXTERN_my_propertywindow->setform->setIcon(isReport() ? report2 : form2);

  if (bForm){    


    _property::addProperties(&p, this->getProperties());
  }

  updatePropertyWindow2(true);  

}


void _form::performApply(QWidget *c, int nIndex)
{

  t_properties *ppp;

    #define SWITCH getProperties();      
    #define SWITCH3 ppp
    #include "_form_property_switch.h"   
    #undef SWITCH3

      t_properties::Iterator it;
      t_properties::Iterator it2;

    int nX = 0;
    int nY = 0;
    int nWidth = -1;
    int nHeight = -1;

    for ( it = apply_properties.at(nIndex)->begin(); it != apply_properties.at(nIndex)->end(); ++it ){

      QString s = it.key();


      if (!bCopy && !bCut){
        if (s == "X") continue;
        if (s == "Y") continue;
        if (s == "Width") continue;
        if (s == "Height") continue;   
      }
      if (s == "Name") continue;
      if (s == "ControlType") continue;
      if (s == "TabIndex") continue;
      if (s == "BoxIndex") continue;
      if (s == "BoxX") continue;
      if (s == "BoxY") continue;
      if (s == "ParentIndex") continue;
      if (s == "SplitIndex") continue;
      if (s == "TabIndex") continue;
      if (s == "ParentControl") continue;
      if (s == "FocusOrder") continue;

      if (!bCopy && !bCut){

        if (s == "Icon") continue;
        if (s == "Caption") continue;
        if (s == "StringValue") continue;
        if (s == "IntegerValue") continue;
        if (s == "DoubleValue") continue;
        if (s == "Text") continue;
        if (s == "StatusTip") continue;
        if (s == "ToolTip") continue;
        if (s == "WhatsThis") continue;
        if (s == "Tag") continue;
        if (s == "Group") continue;
        if (s == "SQLName") continue;
        if (s == "SQLRelation") continue;
      }


      if (ppp->contains(s) ){


      t_property *d1;

      d1 = *it;

      if (!d1->used) continue;

      switch(d1->propertyType){
        case pt_integer:
          applyProperty(c, s, d1->v_boolean, d1->v_qstring, d1->v_integer, d1->v_double);
          if (s == "Width"){
            nWidth = d1->v_integer;
          } else if (s == "Height"){
            nHeight = d1->v_integer;            
          } else if (s == "X"){
            nX = d1->v_integer;            
          } else if (s == "Y"){
            nY = d1->v_integer;            
          }
          break;           
        case pt_boolean:
          applyProperty(c, s, d1->v_boolean, d1->v_qstring, d1->v_integer, d1->v_double);
          break;
        case pt_qstring:
          {
          applyProperty(c, s, d1->v_boolean, d1->v_qstring, d1->v_integer, d1->v_double);
          break;
          }
      }       
      }
    }
    
    if (!bCopy && !bCut){
    } else {
      if (nX >= 0 || nY >= 0) c->move(nX - 0, nY - 0);
    }
    if (nWidth >= 0 && nHeight >= 0){
      #define SWITCH SETPROPERTY_Width(nWidth);
      #include "_form_property_switch.h"   

      #define SWITCH SETPROPERTY_Height(nHeight);
      #include "_form_property_switch.h"   
    }



 }

bool _form::applyApply()
{ 
  
  
  QWidget *c = 0;

  cCut.clear();

  bool b = false;

  nCutMinX = 999999;
  nCutMinY = 999999;

  // get the selected control
  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        t_properties *ap;

        #define SWITCH getProperties();      
        #define SWITCH3 ap
        #include "_form_property_switch.h"   
        #undef SWITCH3

        apply_properties.append(ap);

        if (c->x() < nCutMinX) nCutMinX = c->x();
        if (c->y() < nCutMinY) nCutMinY = c->y();

        cCut.append(c);

        b = true;
      }
        
    } while (nextControl(&c));
  }
  return b;

}


void _form::_event_EDIT_APPLY()
{ 
  cutForm = 0;
  bCut = false;
  bCopy = false;
  bApply = applyApply();
  if (bApply) qApp->setOverrideCursor(QCursor(Qt::CrossCursor));
  focusInEvent(0);
}


void _form::_event_EDIT_CUT()
{
  cutForm = this;
  apply_properties.clear();
  bCut = applyApply();
  focusInEvent(0);

}

void _form::_event_EDIT_COPY()
{
   apply_properties.clear();
   bCopy = applyApply();
   focusInEvent(0);
}

void _form::_event_EDIT_PASTE(bool bFirst)
{  
  static int nOffset = 0;
  
  if (bCopy || bCut){
    if (bFirst) newUndoRedo();

    cPasted.clear();

    _controlType SAVE = insertType;

    int nIndex = 0;
    foreach(QWidget *ww, cCut){      

      nOffset += 10;
      if (nOffset > 100) nOffset = 0;
      QString sControlType = apply_properties.at(nIndex)->value("ControlType")->v_qstring;

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
      
      if (cutForm){
        cutForm->unselectAllControls();
        if (bCut){
          cutForm->selectControlAlways(ww);
          cutForm->METHOD_deleteControl();
        }
      } else {
        unselectAllControls();
        if (bCut){
          selectControlAlways(ww);
          METHOD_deleteControl();
        }
      }
     
      {      

        insertControl(cutForm != this ? 10 + nOffset : 0, cutForm != this ? 10 + nOffset : 0, false);
        QWidget *c = cInsertControl;

        cPasted.append(c);

        performApply(c, nIndex);
        c->raise();
      }

      nIndex++;

    }

    if (bCut){
      apply_properties.clear();
      bCut = false;
      bApply = false;
      cutForm = 0;
    }

    unselectAllControls();
    foreach(QWidget *ww, cPasted){     
      selectControlAlways(ww);
    }

    insertType = SAVE;
    
    updatePropertyWindow();
  } 
  
}

void _form::_event_EDIT_DELETE()
{
  METHOD_deleteControl();
}

void _form::_event_FORMAT_MOVE_TO_FRONT()
{
  if (EXTERN_my_mainwindow) EXTERN_my_mainwindow->event_FORMAT_MOVE_TO_FRONT();
}

void _form::_event_FORMAT_MOVE_TO_BACK()
{
  if (EXTERN_my_mainwindow) EXTERN_my_mainwindow->event_FORMAT_MOVE_TO_BACK();                
}

void _form::_event_ADDPAGE()
{
  QWidget *c = 0;
  _tab *t = 0;

  // get the selected tab control
  if (firstControl(&c)){
    do {

      if (controlType(c) == t_tab && c->acceptDrops()){ // missused as selected flag
        t = (_tab *) c;
        goto t;
      }
        
    } while (nextControl(&c));

    return;

  }
t:
  bool b;
  QString k = QInputDialog::getText(this, tr("Add New Page"), tr("Enter name of the new page:"), QLineEdit::Normal, QString::null, &b);
  if (k.isEmpty()) return;

  int n = k.indexOf("|");
  QString s = k;
  QString image = "";
  if (n > 0){
    s = k.left(n);
    image = k.mid(n + 1);
  }

  t->METHOD_AppendTab(image, s);

  QString u = t->GETPROPERTY_Pages();
  if (u.endsWith(";")){
    t->SETPROPERTY_Pages(u + k);
  } else {
    t->SETPROPERTY_Pages(u + ";" + k);
  }

  updatePropertyWindow();


}

void _form::_event_REMOVEPAGE()
{


  QWidget *c = 0;
  _tab *t = 0;

  // get the selected tab control
  if (firstControl(&c)){
    do {

      if (controlType(c) == t_tab && c->acceptDrops()){ // missused as selected flag
        t = (_tab *) c;
        goto t;        
      }
        
    } while (nextControl(&c));

    return;

  }
t:

  QString sTab = "";
  c = t;
  sTab = c->objectName();

  int nIndex = t->METHOD_Selected() - 1;
  QString sPage = t->METHOD_Caption(nIndex + 1);
  t->METHOD_RemoveTab(nIndex + 1);

  // delete tab related controls of index
  if (firstControl(&c)){
    do {

      QString sParentControl = "";
      int nTabIndex = 0;

      #define SWITCH GETPROPERTY_ParentControl();      
      #define SWITCH3 sParentControl
      #include "_form_property_switch.h"   
      #undef SWITCH3

      #define SWITCH GETPROPERTY_TabIndex();      
      #define SWITCH3 nTabIndex
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sParentControl == sTab && nTabIndex == nIndex && sTab.length()){

        #define SWITCH SETPROPERTY_ParentControl("");
        #include "_form_property_switch.h"   

        #define SWITCH SETPROPERTY_TabIndex(0);
        #include "_form_property_switch.h"     
  
        c->hide();
      }
        
    } while (nextControl(&c));

    // decrement TabIndex
    if (firstControl(&c)){
      do {

        QString sParentControl = "";
        int nTabIndex = 0;

        #define SWITCH GETPROPERTY_ParentControl();      
        #define SWITCH3 sParentControl
        #include "_form_property_switch.h"   
        #undef SWITCH3

        #define SWITCH GETPROPERTY_TabIndex();      
        #define SWITCH3 nTabIndex
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if (sParentControl == sTab && sTab.length()){  

          nTabIndex -= 1;
          if (nTabIndex < 0) nTabIndex = 0;
          #define SWITCH SETPROPERTY_TabIndex(nTabIndex);
          #include "_form_property_switch.h"     
    
        }
          
      } while (nextControl(&c));
    }

    tabPageSelected(t, 0);

  }

  QString u = t->GETPROPERTY_Pages();
  QString k = u;
  int n = k.indexOf(sPage);

  if (n >= 0){
    u = k.left(n);
    n = k.indexOf(";", n + 1);
    if (n >= 0){
      u = u + k.mid(n + 1);
    }
    
  }
 
  t->SETPROPERTY_Pages(u);

  updatePropertyWindow();

}

void _form::_event_RENAMEPAGE()
{


  QWidget *c = 0;
  _tab *t = 0;

  // get the selected tab control
  if (firstControl(&c)){
    do {

      if (controlType(c) == t_tab && c->acceptDrops()){ // missused as selected flag
        t = (_tab *) c;
        goto t;
      }
        
    } while (nextControl(&c));

    return;

  }
t:

  int nIndex = t->METHOD_Selected() - 1;

  bool b;
  QString k = QInputDialog::getText(this, tr("Rename Page"), tr("Enter new name of the page:"), QLineEdit::Normal, QString::null, &b);
  if (k.isEmpty()) return;

  int n = k.indexOf("|");
  QString s = k;
  QString image = "";
  if (n > 0){
    s = k.left(n);
    image = k.mid(n + 1);
  }
  QString sOld = t->METHOD_Caption(nIndex + 1);
  t->METHOD_SetCaption(nIndex + 1, s);
  t->METHOD_SetIcon(nIndex + 1, image);


  updatePropertyWindow();


}

void _form::setParentControl(QWidget *c, int x, int y, bool bInsert)
{
  if (controlType(c) == t_tab) return;

  QString sParentControl = "";

  // ***

  int x2 = c->x();
  int y2 = c->y();
  int w2 = c->width();
  int h2 = c->height();

  QWidget *ww = c->parentWidget();
  if (ww != this){
    x2 += ww->x();
    y2 += ww->y();
    //w2 += ww->width();
    //h2 += ww->height();
  }

  {

    _tab *t = (_tab *) insideTab(x2, y2, w2, h2);

    QString sControlName = c->objectName();

    sParentControl = "";
    int nTabIndex = 0;

    if (t){
      sParentControl = t->GETPROPERTY_Name(); 
      nTabIndex = t->METHOD_Selected() - 1;

      if (sControlName == sParentControl){
        sParentControl = "";
        nTabIndex = 0;              
      }

    }

    {

      #define SWITCH SETPROPERTY_ParentControl(sParentControl);
      #include "_form_property_switch.h"   

      #define SWITCH SETPROPERTY_TabIndex(nTabIndex);
      #include "_form_property_switch.h"     
    }

  }
/*
  // ***
  {
    QString sControlName = "";

    _vbox *vb = 0;

    if (controlType(c) != t_vbox){

      if (c->acceptDrops()){ // missused as selected flag                   
        vb = (_vbox *) insideVBox(x2, y2, w2, h2);
      } else if (bInsert){
        vb = (_vbox *) insideVBox(x, y, 1, 1);
      }
      if (vb){

        #define SWITCH GETPROPERTY_Name();      
        #define SWITCH3 sControlName
        #include "_form_property_switch.h"   
        #undef SWITCH3

        sParentControl = "";
      }

    }

    if (vb){
      sParentControl = vb->GETPROPERTY_Name(); 

      if (sControlName == sParentControl){
        sParentControl = "";
      }
    }

    if (vb && c->isVisible()){

      #define SWITCH SETPROPERTY_ParentControl(sParentControl);
      #include "_form_property_switch.h"   

      if (sParentControl.length()){
        QVBoxLayout *l = (QVBoxLayout *) vb->layout();
        int n = -1;

        int i = 0;
        for (; i < l->count(); i++){
          
          QWidget *w = l->itemAt(i)->widget();
          if (w == c) continue;

          int y1 = c->y();
          int y2 = w->y() + w->parentWidget()->y();
          int y3 = w->y();
          int h2 = w->height();

          if (!bInsert){
            if ((y1 > y3 && y1 < y3 + h2) || y1 < y3){
              n = i;
              break;
            }
          } else {
            if ((y1 > y2 && y1 < y2 + h2) || y1 < y2){
              n = i;
              break;
            }
          }
        }

        if (i != l->count() || l->count() == 0){
     
          l->removeWidget(c);
          l->insertWidget(n, c);

          if (n == -1) n = l->count();

          //#define SWITCH SETPROPERTY_LayoutIndex(n);
          #include "_form_property_switch.h"     
        }

      }
      
    }
  }

  // ***
  {
    QString sControlName = "";


    _hbox *hb = 0;

    if (controlType(c) != t_hbox){

      if (c->acceptDrops()){ // missused as selected flag                   
        hb = (_hbox *) insideHBox(x2, y2, w2, h2);
      } else if (bInsert){
        hb = (_hbox *) insideHBox(x, y, 1, 1);
      }
      if (hb){

        #define SWITCH GETPROPERTY_Name();      
        #define SWITCH3 sControlName
        #include "_form_property_switch.h"   
        #undef SWITCH3

        sParentControl = "";
      }

    }

    if (hb){
      sParentControl = hb->GETPROPERTY_Name(); 

      if (sControlName == sParentControl){
        sParentControl = "";
      }
    }

    if (hb && c->isVisible()){

      #define SWITCH SETPROPERTY_ParentControl(sParentControl);
      #include "_form_property_switch.h"   

      if (sParentControl.length()){
        QHBoxLayout *l = (QHBoxLayout *) hb->layout();
        int n = -1;

        int i = 0;
        for (; i < l->count(); i++){
          n = i;
          QWidget *w = l->itemAt(i)->widget();
          if (w == c) continue;

          int x1 = c->x();
          int x2 = w->x() + w->parentWidget()->x();
          int x3 = w->x();
          int w2 = w->width();

          if (!bInsert){
            if ((x1 > x3 && x1 < x3 + w2) || x1 < x3){
              n = i;
              break;
            }
          } else {
            if ((x1 > x2 && x1 < x2 + w2) || x1 < x2){
              n = i;
              break;
            }
          }

        }
     
        if (i != l->count() || l->count() == 0){
     
          l->removeWidget(c);
          l->insertWidget(n, c);

          if (n == -1) n = l->count();

          //#define SWITCH SETPROPERTY_LayoutIndex(n);
          #include "_form_property_switch.h"     
        }

      }
      
    }
  }

  // ***
  {
    QString sControlName = "";

    _vhbox *vhb = 0;

    if (controlType(c) != t_vhbox){

      if (c->acceptDrops()){ // missused as selected flag                   
        vhb = (_vhbox *) insideVHBox(x2, y2, w2, h2);
      } else if (bInsert){
        vhb = (_vhbox *) insideVHBox(x, y, 1, 1);
      }
      if (vhb){

        #define SWITCH GETPROPERTY_Name();      
        #define SWITCH3 sControlName
        #include "_form_property_switch.h"   
        #undef SWITCH3

        sParentControl = "";
      }

    }

    if (vhb){
      sParentControl = vhb->GETPROPERTY_Name(); 

      if (sControlName == sParentControl){
        sParentControl = "";
      }
    }

    if (vhb && c->isVisible()){

      #define SWITCH SETPROPERTY_ParentControl(sParentControl);
      #include "_form_property_switch.h"   

      if (sParentControl.length()){
        QGridLayout *l = (QGridLayout *) vhb->layout();
        int xn = 0;
        int yn = 0;

        int rc = l->rowCount();
        int cc = l->columnCount();

        if (rc == 1 && cc == 1){
          if (x > vhb->x() && x < vhb->x() + vhb->width()){
            int xx = x - vhb->x();
            int ww = (vhb->width() / (cc + 1));
            xn = xx / ww;
          }
          if (xn < 0) xn = 0;

          if (y > vhb->y() && y < vhb->y() + vhb->height()){
            int yy = y - vhb->y();
            int hh = (vhb->height() / (rc + 1));
            yn = yy / hh;

          }       
          if (yn < 0) yn = 0;
        } else {
       
          for (int yy = 0; yy < l->rowCount(); yy++){
            for (int xx = 0; xx < l->columnCount(); xx++){
              xn = xx;
              yn = yy;
              QRect r = l->cellRect (yy, xx);
              
             // r.setX(r.x() + vhb->x());
             // r.setY(r.y() + vhb->y());

              int x2 = r.x();
              int y2 = r.y();
              int w2 = r.width();
              int h2 = r.height();

              if (x > x2 && y > y2 && x < x2 + w2 && y < y2 + h2){
                if (x2 - 15 < 0) xn--;
                if (y2 - 15 < 0) yn--;
                if (x + 15 > x2 + w2) xn++;
                if (y + 15 > y2 + h2) yn++;
                break;
              }

              x2 = x2;

            }
          }      
        }

        l->removeWidget(c);
        l->addWidget(c, yn, xn);
        vhb->repaint();
        

        //#define SWITCH SETPROPERTY_layoutx(n);
        #include "_form_property_switch.h"     

      }
      
    }
  }

  // ***
  {
    QString sControlName = "";

    _vsplit *v = 0;

    if (controlType(c) != t_vsplit){

      if (c->acceptDrops()){ // missused as selected flag                   
        v = (_vsplit *) insideVSplit(x2, y2, w2, h2);
      } else if (bInsert){
        v = (_vsplit *) insideVSplit(x, y, 1, 1);
      }
      if (v){

        #define SWITCH GETPROPERTY_Name();      
        #define SWITCH3 sControlName
        #include "_form_property_switch.h"   
        #undef SWITCH3

        sParentControl = "";
      }

    }

    if (v){
      sParentControl = v->GETPROPERTY_Name(); 

      if (sControlName == sParentControl){
        sParentControl = "";
      }
    }

    if (v && c->isVisible()){

      #define SWITCH SETPROPERTY_ParentControl(sParentControl);
      #include "_form_property_switch.h"   

      if (sParentControl.length()){

        v->addWidget(c);

        //#define SWITCH SETPROPERTY_layoutx(n);
        #include "_form_property_switch.h"     

      }
      
    }
  }

  // ***

  {
    QString sControlName = "";

    _hsplit *v = 0;

    if (controlType(c) != t_hsplit){

      if (c->acceptDrops()){ // missused as selected flag                   
        v = (_hsplit *) insideHSplit(x2, y2, w2, h2);
      } else if (bInsert){
        v = (_hsplit *) insideHSplit(x, y, 1, 1);
      }
      if (v){

        #define SWITCH GETPROPERTY_Name();      
        #define SWITCH3 sControlName
        #include "_form_property_switch.h"   
        #undef SWITCH3

        sParentControl = "";
      }

    }

    if (v){
      sParentControl = v->GETPROPERTY_Name(); 

      if (sControlName == sParentControl){
        sParentControl = "";
      }
    }

    if (v && c->isVisible()){

      #define SWITCH SETPROPERTY_ParentControl(sParentControl);
      #include "_form_property_switch.h"   

      if (sParentControl.length()){

        v->addWidget(c);

        //#define SWITCH SETPROPERTY_layoutx(n);
        #include "_form_property_switch.h"     

      }
      
    }
  }
  */

  // ***

//done:
  if (sParentControl == ""){
    c->show();
  }
}



bool _form::moveControls ( QMouseEvent * e ) 
{  
  QWidget *c;
  QWidget *c2;

  int nMinX = 999999;
  int nMinY = 999999; 
  QWidget *cMin = 0;

  bool b = false;
  bool b2 = true;
  bool b3 = false;

  if (bControlMove == false){

    int x2 = mouseX(e) - XSCROLLBAR;
    int y2 = mouseY(e) - YSCROLLBAR;

    if (firstControl(&c)){

      do {
        if (c->isHidden()) continue;

        int x = c->x();
        int y = c->y();
        int w = c->width();
        int h = c->height();

        QWidget *ww = c->parentWidget();
        if (ww != this){
          x += ww->x();
          y += ww->y();
          //w += ww->width();
          //h += ww->height();
        }

        if (x2 >= x && x2 <= x + w 
        && y2 >= y && y2 <= y + h)
        {
          if (bRightButton){
            bControlMove = true;
            return true;            
          }

          if (x2 - x <= nMinX && y2 - y <= nMinY){
            nMinX = x2 - x;
            nMinY = y2 - y;
            cMin = c;
          }

          bSelected = true;             
          b = true;

        }

      } while (nextControl(&c)); 

    }

    if (b && cMin != 0){

      if (bRightButton == true){
        if (cMin->acceptDrops() == false){
             unselectAllControls();
        }
      }

      if (bCTRL == false){
        if (cMin->acceptDrops() == false){
          unselectAllControls();      
        }
      }
      selectControlAlways(cMin);
    }

  }

  if ((b || bControlMove) && bRightButton){
    return true;
  }
  

  static int diffx2 = 0;
  static int diffy2 = 0;

  diffx2++;
  diffy2++;

  if (firstControl(&c)){

    do { 

      if (b || bControlMove){

        int diffx = (mouseX(e) - nMouseX);
        int diffy = (mouseY(e) - nMouseY);

        if (bCTRL){
          if (diffx < 10 && diffx > 0){ 
            if (diffx2 > 5){
              diffx = 10;
            } else diffx = 0;
          } else if (diffx > -10 && diffx < 0){
            if (diffx2 > 5){
              diffx = -10;
            } else diffx = 0;            
          }

          if (diffy < 10 && diffy > 0){
            if (diffy2 > 5){
              diffy = 10;
            } else diffy = 0;
          } else if (diffy > -10 && diffy < 0){
            if (diffy2 > 5){
              diffy = -10;
            } else diffy = 0;           
          }
        }

        int x = c->x() + diffx;
        int y = c->y() + diffy;
        int w = c->width();
        int h = c->height();

        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + w > frameW()){
          x = frameW() - w;
        }
        
        if (y + h > frameH()){
          y = frameH() - h;
        }         

        if (c->acceptDrops()){ // missused as selected flag                   

          if (XScrollBar && nMouseOriginX > mouseX(e) && c->x() - 1 < 50){
            XScrollBar->setValue(XScrollBar->value() - 50);    
          } else if (XScrollBar && nMouseOriginX < mouseX(e) && c->x() + c->width() + 50 > frameW()){
            XScrollBar->setValue(XScrollBar->value() + 50);    
          }
          if (YScrollBar && nMouseOriginY > mouseY(e) && c->y() - 1 < 50){
            YScrollBar->setValue(YScrollBar->value() - 50);    
          } else if (YScrollBar && nMouseOriginY < mouseY(e) && c->y() + c->height() + 50 > frameH()){
            YScrollBar->setValue(YScrollBar->value() + 50);    
          }

          my_move(c, x, y); // move the control

          bControlMove = true;
        }
      }

    } while (nextControl(&c));  

    if (diffx2 > 5){
      diffx2 = 0;
      diffy2 = 0;
    }
    if (diffy2 > 5){
      diffx2 = 0;
      diffy2 = 0;
    }

    if (b){
      //setUpdatesEnabled(true);
      return true;
    }

  }

  return false;
}

QWidget *_form::insideTab(int x, int y, int w, int h)
{


  QWidget *currentControl = CurrentControl;

  QWidget *c;
  QWidget *c2;
  QWidget *ret = 0;
  

  if (firstControl(&c)){
    do {

      if (controlType(c) == t_tab){

        int x2 = c->x();
        int y2 = c->y();
        int w2 = c->width();
        int h2 = c->height();

        QWidget *ww = c->parentWidget();
        if (ww != this){
          x2 += ww->x();
          y2 += ww->y();
        }

        if (x >= x2 && y >= y2 && x <= x2 + w2 && y <= y2 + h2){

          c2 = c;

          // seek to current control
          if (firstControl(&c)){
            do {
              if (c == currentControl) break;

            } while (nextControl(&c));
          }
          ret = c2;
          goto re;

        }
       
      }

    } while (nextControl(&c));
  }
re:
  // seek to current control
  if (firstControl(&c)){
    do {
      if (c == currentControl) break;

    } while (nextControl(&c));
  }

  return ret;
}

QWidget *_form::insideHeader(int x, int y, int w, int h)
{


  QWidget *currentControl = CurrentControl;

  QWidget *c;
  QWidget *c2;
  QWidget *ret = 0;
  

  if (firstControl(&c)){
    do {

      if (controlType(c) == t_header){

        int x2 = c->x();
        int y2 = c->y();
        int w2 = c->width();
        int h2 = c->height();

        QWidget *ww = c->parentWidget();
        if (ww != this){
          x2 += ww->x();
          y2 += ww->y();
        }

        if (x >= x2 && y >= y2 && x <= x2 + w2 && y <= y2 + h2){

          c2 = c;

          // seek to current control
          if (firstControl(&c)){
            do {
              if (c == currentControl) break;

            } while (nextControl(&c));
          }
          ret = c2;
          goto re;

        }
       
      }

    } while (nextControl(&c));
  }
re:
  // seek to current control
  if (firstControl(&c)){
    do {
      if (c == currentControl) break;

    } while (nextControl(&c));
  }

  return ret;
}

QWidget *_form::insideFooter(int x, int y, int w, int h)
{


  QWidget *currentControl = CurrentControl;

  QWidget *c;
  QWidget *c2;
  QWidget *ret = 0;
  

  if (firstControl(&c)){
    do {

      if (controlType(c) == t_footer){

        int x2 = c->x();
        int y2 = c->y();
        int w2 = c->width();
        int h2 = c->height();

        QWidget *ww = c->parentWidget();
        if (ww != this){
          x2 += ww->x();
          y2 += ww->y();
        }

        if (x >= x2 && y >= y2 && x <= x2 + w2 && y <= y2 + h2){

          c2 = c;

          // seek to current control
          if (firstControl(&c)){
            do {
              if (c == currentControl) break;

            } while (nextControl(&c));
          }
          ret = c2;
          goto re;

        }
       
      }

    } while (nextControl(&c));
  }
re:
  // seek to current control
  if (firstControl(&c)){
    do {
      if (c == currentControl) break;

    } while (nextControl(&c));
  }

  return ret;
}

QWidget *_form::insideVBox(int x, int y, int w, int h)
{


  QWidget *currentControl = CurrentControl;

  QWidget *c;
  QWidget *c2;
  QWidget *ret = 0;
  

  if (firstControl(&c)){
    do {

      if (controlType(c) == t_vbox){

        int x2 = c->x();
        int y2 = c->y();
        int w2 = c->width();
        int h2 = c->height();

        QWidget *ww = c->parentWidget();
        if (ww != this){
          x2 += ww->x();
          y2 += ww->y();
        }

        if (x >= x2 && y >= y2 && x <= x2 + w2 && y <= y2 + h2){

          c2 = c;

          // seek to current control
          if (firstControl(&c)){
            do {
              if (c == currentControl) break;

            } while (nextControl(&c));
          }
          ret = c2;
          goto re;

        }
       
      }

    } while (nextControl(&c));
  }
re:
  // seek to current control
  if (firstControl(&c)){
    do {
      if (c == currentControl) break;

    } while (nextControl(&c));
  }

  return ret;
}


QWidget *_form::insideHBox(int x, int y, int w, int h)
{


  QWidget *currentControl = CurrentControl;

  QWidget *c;
  QWidget *c2;
  QWidget *ret = 0;
  

  if (firstControl(&c)){
    do {

      if (controlType(c) == t_hbox){

        int x2 = c->x();
        int y2 = c->y();
        int w2 = c->width();
        int h2 = c->height();

        QWidget *ww = c->parentWidget();
        if (ww != this){
          x2 += ww->x();
          y2 += ww->y();
        }

        if (x >= x2 && y >= y2 && x <= x2 + w2 && y <= y2 + h2){

          c2 = c;

          // seek to current control
          if (firstControl(&c)){
            do {
              if (c == currentControl) break;

            } while (nextControl(&c));
          }
          ret = c2;
          goto re;

        }
       
      }

    } while (nextControl(&c));
  }
re:
  // seek to current control
  if (firstControl(&c)){
    do {
      if (c == currentControl) break;

    } while (nextControl(&c));
  }

  return ret;
}



QWidget *_form::insideVSplit(int x, int y, int w, int h)
{


  QWidget *currentControl = CurrentControl;

  QWidget *c;
  QWidget *c2;
  QWidget *ret = 0;
  

  if (firstControl(&c)){
    do {

      if (controlType(c) == t_vsplit){

        int x2 = c->x();
        int y2 = c->y();
        int w2 = c->width();
        int h2 = c->height();

        QWidget *ww = c->parentWidget();
        if (ww != this){
          x2 += ww->x();
          y2 += ww->y();
        }

        if (x >= x2 && y >= y2 && x <= x2 + w2 && y <= y2 + h2){

          c2 = c;

          // seek to current control
          if (firstControl(&c)){
            do {
              if (c == currentControl) break;

            } while (nextControl(&c));
          }
          ret = c2;
          goto re;

        }
       
      }

    } while (nextControl(&c));
  }
re:
  // seek to current control
  if (firstControl(&c)){
    do {
      if (c == currentControl) break;

    } while (nextControl(&c));
  }

  return ret;
}



QWidget *_form::insideHSplit(int x, int y, int w, int h)
{


  QWidget *currentControl = CurrentControl;

  QWidget *c;
  QWidget *c2;
  QWidget *ret = 0;
  

  if (firstControl(&c)){
    do {

      if (controlType(c) == t_hsplit){

        int x2 = c->x();
        int y2 = c->y();
        int w2 = c->width();
        int h2 = c->height();

        QWidget *ww = c->parentWidget();
        if (ww != this){
          x2 += ww->x();
          y2 += ww->y();
        }

        if (x >= x2 && y >= y2 && x <= x2 + w2 && y <= y2 + h2){

          c2 = c;

          // seek to current control
          if (firstControl(&c)){
            do {
              if (c == currentControl) break;

            } while (nextControl(&c));
          }
          ret = c2;
          goto re;

        }
       
      }

    } while (nextControl(&c));
  }
re:
  // seek to current control
  if (firstControl(&c)){
    do {
      if (c == currentControl) break;

    } while (nextControl(&c));
  }

  return ret;
}



QWidget *_form::insideVHBox(int x, int y, int w, int h)
{


  QWidget *currentControl = CurrentControl;

  QWidget *c;
  QWidget *c2;
  QWidget *ret = 0;
  

  if (firstControl(&c)){
    do {

      if (controlType(c) == t_vhbox){

        int x2 = c->x();
        int y2 = c->y();
        int w2 = c->width();
        int h2 = c->height();

        QWidget *ww = c->parentWidget();
        if (ww != this){
          x2 += ww->x();
          y2 += ww->y();
        }

        if (x >= x2 && y >= y2 && x <= x2 + w2 && y <= y2 + h2){

          c2 = c;

          // seek to current control
          if (firstControl(&c)){
            do {
              if (c == currentControl) break;

            } while (nextControl(&c));
          }
          ret = c2;
          goto re;

        }
       
      }

    } while (nextControl(&c));
  }
re:
  // seek to current control
  if (firstControl(&c)){
    do {
      if (c == currentControl) break;

    } while (nextControl(&c));
  }

  return ret;
}
#endif



void _form::show ()
{  
#ifdef RUN
  QWidget::show();
   EVENT_OnShow();
#else
  QWidget::show();
#endif
  
}

void _form::hide ()
{  
#ifdef RUN
  QWidget::hide();
  EVENT_OnHide();
#else
  QWidget::hide();
#endif
  
}

#ifdef IDE
void _form::event_FORMAT_MOVE_TO_FRONT()
{
  int nMaxX = 0;
  int nMaxY = 0;
  int nMinX = 999999;
  int nMinY = 999999;
  int nMaxWidth = 0;
  int nMaxHeight = 0;

  formatValues(&nMaxX, &nMaxY, &nMinX, &nMinY, &nMaxWidth, &nMaxHeight);

  QWidget *c;
  bool b = false;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        b = true;

        c->raise();

        if (controlType(c) == t_tab){

          QString sTab = ((_tab *) c)->GETPROPERTY_Name(); 
          QWidget *currentControl = c;            
         
          if (firstControl(&c)){
            do {
              
              QString sParentControl = "";

              #define SWITCH GETPROPERTY_ParentControl();      
              #define SWITCH3 sParentControl
              #include "_form_property_switch.h"   
              #undef SWITCH3

              if (sParentControl == sTab && sTab.length()){  

                c->raise();
          
              }
                
            } while (nextControl(&c));

            // seek to current control
            if (firstControl(&c)){
              do {
                if (c == currentControl) break;

              } while (nextControl(&c));
            }
          }
        }

      }

    } while (nextControl(&c));
  }
    if (!b){
      QMessageBox::information( this, tr(MYAPP),
        tr(
            "You have to select one control,\n"       
            "before this does any usefully function."
            )
            );
  }

  updatePropertyWindowGeo();

}       

void _form::event_FORMAT_MOVE_TO_BACK()
{
  int nMaxX = 0;
  int nMaxY = 0;
  int nMinX = 999999;
  int nMinY = 999999;
  int nMaxWidth = 0;
  int nMaxHeight = 0;

  formatValues(&nMaxX, &nMaxY, &nMinX, &nMinY, &nMaxWidth, &nMaxHeight);

  QWidget *c;
  bool b = false;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag
        c->lower();

        b = true;
       }

    } while (nextControl(&c));
  }
  if (!b){
      QMessageBox::information( this, tr(MYAPP),
        tr(
            "You have to select one control,\n"       
            "before this does any usefully function."
            )
            );
  }
   showUpdatePropertyWindow/**/();

}      

void _form::setGeo(QWidget *c, int x, int y, int w, int h)
{
  moveTabRelated(c, x, y);

  #define SWITCH setGeo(x, y, w, h);
  #include "_form_property_switch.h"    

  int mx = 0;
  int my = 0;
  if (XScrollBar) mx = XScrollBar->value();
  if (YScrollBar) my = YScrollBar->value();

  #define SWITCH setXYWidthHeight(mx + x, my + y, w, h);
  #include "_form_property_switch.h"   
}


t_boolean _form::METHOD_deleteControl(bool bFirst)
{
  if (bFirst) newUndoRedo();

  QWidget *c;
  bool b = false;

  if (firstControl(&c)){

    do {

      if (c->acceptDrops()){
        QString s = "";

        if (controlType(c) ==  t_tab){

          QWidget *currentControl = c;           
          
          QString sTab = c->objectName();  
      
          // delete tab related controls of index
          if (firstControl(&c)){
            do {              

              QString sParentControl = "";
              int nTabIndex = 0;

              #define SWITCH GETPROPERTY_ParentControl();      
              #define SWITCH3 sParentControl
              #include "_form_property_switch.h"   
              #undef SWITCH3

              #define SWITCH GETPROPERTY_TabIndex();      
              #define SWITCH3 nTabIndex
              #include "_form_property_switch.h"   
              #undef SWITCH3

              if (sParentControl == sTab){
          
                #define SWITCH GETPROPERTY_Name();
                #define SWITCH3 s
                #include "_form_property_switch.h"    
                #undef SWITCH3

                #define SWITCH5 del(s);
                #include "_form_property_switch.h"    
                #undef SWITCH5

                c->hide();
                c->setAcceptDrops(false); // missused as selected flag

                deleteControl(c);

              }
                
            } while (nextControl(&c));

          }

          // seek to current control
          if (firstControl(&c)){
            do {
              if (c == currentControl) break;

            } while (nextControl(&c));
          }
        }



        b = true;
        

        #define SWITCH GETPROPERTY_Name();
        #define SWITCH3 s
        #include "_form_property_switch.h"    
        #undef SWITCH3

        #define SWITCH5 del(s);
        #include "_form_property_switch.h"    
        #undef SWITCH5

        c->hide();
        deleteControl(c);

        if (firstControl(&c)){ 
          continue;
        } else { 
          break;
        }

      }

    } while (nextControl(&c)); 
  }
  update();

  EXTERN_my_parserwindow->refreshControl();
  checkFrameMinSize();


  return b;
}

#endif

#ifdef RUN
QString _form::loadProjectFile (QString sFile) 
{
    const char *ac = myInterpreter->loadProjectFile(sFile);
    QString s = QString::fromUtf8(ac);
    return s;
}

t_pointer _form::loadProjectFile(QString sFile, t_integer *nSize)
{
    return myInterpreter->loadProjectFile(sFile, nSize);
}

QPixmap _form::loadProjectImage(QString sFile)
{
    t_integer n = 0;
    t_pointer pp = loadProjectFile(sFile, &n);
    QPixmap p;
    bool b = p.loadFromData((const uchar *) pp, n);
    if (b == false){
      static QPixmap pp = QPixmap();
      p = pp;
    }
    return p;
}
#endif

QWidget *_form::getControl(QString s)
{
  QWidget *c;
  if (firstControl(&c)){
     do {
       QString sControlName = c->objectName();
     
       if (sControlName == s){
          return c;
       }

     } while (nextControl(&c));
  }

  return 0;
}

#ifdef IDE
bool _form::insertControl(int x, int y, bool bUpdatePropertyWindow, int nWidth, int nHeight)
{ 
  

  bool bSQLAll = false;
  if (insertType == t_SQLAll){
    bSQLAll = true;
    if (width() < 460) resize(460, height());
    y = height() - 40;
  }

  
  bool bRefreshProject = false;


  do {    

    QWidget *c = 0;
    QString sControlName = "";
    QString s = "";
    QString sIcon = "";  
    _sourcecodeeditor *o = 0;
    QString sCode = "";
    QString sPath = "";  

    if (bSQLAll){
      if (insertType == t_SQLAll){ insertType = t_SQLInsert; x = 320; y = y; }
      else if (insertType == t_SQLInsert){ insertType = t_SQLUpdate; x = 350; y = y; }
      else if (insertType == t_SQLUpdate){ insertType = t_SQLDelete; x = 410; y = y; }
      else if (insertType == t_SQLDelete){ insertType = t_SQLNext; x = 260; y = y; }
      else if (insertType == t_SQLNext){ insertType = t_SQLPrevious; x = 30; y = y; }
      else if (insertType == t_SQLPrevious){ insertType = t_SQLFirst; x = 0; y = y; }
      else if (insertType == t_SQLFirst){ insertType = t_SQLLast; x = 290; y = y; }
      else if (insertType == t_SQLLast){ insertType = t_SQLRequery; x = 380; y = y; }
      else if (insertType == t_SQLRequery){ insertType = t_SQLGoTo; x = 60; y = y; }
      else if (insertType == t_SQLGoTo){ insertType = t_SQLInfo; x = 110; y = y; }
    }

    switch(insertType){
      case t_SQLInsert: sControlName = "SQLInsert"; goto sql;
      case t_SQLUpdate: sControlName = "SQLUpdate"; goto sql;
      case t_SQLDelete: sControlName = "SQLDelete"; goto sql;
      case t_SQLNext: sControlName = "SQLNext"; goto sql;
      case t_SQLPrevious: sControlName = "SQLPrevious"; goto sql;
      case t_SQLFirst: sControlName = "SQLFirst"; goto sql;
      case t_SQLLast: sControlName = "SQLLast"; goto sql;
      case t_SQLRequery: sControlName = "SQLRequery"; goto sql;

  sql:
        if (isReport()) return false; 
        if (commandbuttons.has(sControlName)) return false; 
        c = new _commandbutton(this, main);
        s = sControlName;
        ((_commandbutton *) c)->SETPROPERTY_Name(sControlName);
        s += ".png";
        sIcon = s;
        ((_commandbutton *) c)->SETPROPERTY_Caption("");
        ((_commandbutton *) c)->SETPROPERTY_Flat(true);
        ((_commandbutton *) c)->SETPROPERTY_Background("&HFFFFFF");
        ((_commandbutton *) c)->SETPROPERTY_Icon(sIcon);

        sPath = EXTERN_my_mainwindow->getProjectPath();
        sPath += "/";
        sPath += s;

        EXTERN_my_mainwindow->copyFile(idePath(s), sPath);
        bRefreshProject = true;      
        {
          QString q = getFilename();
          EXTERN_my_mainwindow->openFormClassSourceCode(q);
        }
        o = qobject_cast<_sourcecodeeditor *>(EXTERN_my_mainwindow->workspace->activeSubWindow() ? EXTERN_my_mainwindow->workspace->activeSubWindow()->widget() : 0);
        if (o){
	        this->showNormal();  
          this->activateWindow();
          this->setFocus();

          sCode += "  Me." + sControlName.mid(3) + "()\n";
          o->newEvent (sControlName, "OnEvent", "", sCode);
        }    
        break;

      case t_SQLGoTo: sControlName = "SQLGoTo";
        if (isReport()) return false; 
        if (textboxes.has(sControlName)) return false; 
        c = new _textbox(this, main);
        s = sControlName;
        ((_textbox *) c)->SETPROPERTY_Name(sControlName);
        s += ".png";
        sIcon = s;
        ((_textbox *) c)->SETPROPERTY_StringValue("SQLGoTo");
        ((_textbox *) c)->SETPROPERTY_Flat(false);      
        ((_textbox *) c)->SETPROPERTY_Background("&HFFFFFF");
        
        {
          QString q = getFilename();
        EXTERN_my_mainwindow->openFormClassSourceCode(q);
        }
        o = qobject_cast<_sourcecodeeditor *>(EXTERN_my_mainwindow->workspace->activeSubWindow() ? EXTERN_my_mainwindow->workspace->activeSubWindow()->widget() : 0);
        if (o){
	        this->showNormal();  
          this->activateWindow();
          this->setFocus();

          sCode += "  Dim n As Integer \n";
          sCode += "  n = Val(SQLGoTo.Value)\n";
          sCode += "  If n < 1 Or n > Me.Len() Then Return\n";
          sCode += "  If Not Me.GoTo(n) Then SQLGoTo.Value = Me.Pos()\n";

          o->newEvent(sControlName, "OnEvent", "", sCode);

          o->addToEvent("Form", "OnGoTo", "", "  SQLGoTo.Value = Me.Pos()\n");        
        }    
        break;

      case t_SQLInfo: sControlName = "SQLInfo";
        if (isReport()) return false; 
        if (labels.has(sControlName)) return false; 
        c = new _label(this, main);
        s = sControlName;
        ((_label *) c)->SETPROPERTY_Name(sControlName);
        s += ".png";
        sIcon = s;
        ((_label *) c)->SETPROPERTY_Caption("SQLInfo");      
        ((_label *) c)->SETPROPERTY_Background("&HFFFFFF");
        
        {
        QString q = getFilename();
        EXTERN_my_mainwindow->openFormClassSourceCode(q);
        }
        o = qobject_cast<_sourcecodeeditor *>(EXTERN_my_mainwindow->workspace->activeSubWindow() ? EXTERN_my_mainwindow->workspace->activeSubWindow()->widget() : 0);
        if (o){
	        this->showNormal();  
          this->activateWindow();
          this->setFocus();

          o->addToEvent("Form", "OnQuery", "", "  SQLInfo.Caption = \"of \" & Me.Len() & \" record(s)\"\n");
        }    
        break;
      case t_header:  c = new _header(this, main); break;
      case t_footer:  c = new _footer(this, main); break;
      case t_label:  c = new _label(this, main); break;
      case t_serialport:  c = new _serialport(this, main); break;
      case t_movie:  c = new _movie(this, main); break;
      case t_sound:  c = new _sound(this, main); break;
      case t_web:  c = new _web(this, main); break;
      case t_line:  c = new _line(this, main); break;
      case t_toolbutton:  c = new _toolbutton(this, main); break;

        /*
      case t_vsplit: if (isReport()) return false; c = new _vsplit(this, main);  break;
      case t_hsplit:
        if (isReport()) return false; 
        c = new _hsplit(this, main);
        break;
      case t_vbox:
        if (isReport()) return false; 
        c = new _vbox(this, main);
        break;
*/

      case t_box: c = new _box(this, main); break;
      case t_childcontrol: if (isReport()) return false; 
#ifdef IDE
        c = new _childcontrol(this, main); 
#endif
#ifdef RUN
        return true;
#endif
        break;
      case t_editor: c = new _editor(this, main); break;
      case t_browser: c = new _browser(this, main); break;
      case t_datebox: c = new _datebox(this, main); break;
      case t_timebox: c = new _timebox(this, main); break;
      case t_datetimebox: c = new _datetimebox(this, main); break;
/*
      case t_vhbox:
        if (isReport()) return false; 
        c = new _vhbox(this, main);
        break;
      case t_hbox:
        if (isReport()) return false; 
        c = new _hbox(this, main);
        break;*/
      case t_commandbutton:
        if (isReport()) return false; 
        c = new _commandbutton(this, main);
        break;
      case t_checkbox:
        c = new _checkbox(this, main);
        break;
      case t_frame:
        c = new _frame(this, main);
        break;
      case t_listbox:
        if (isReport()) return false; 
        c = new _listbox(this, main);
        break;
      case t_radiobutton:
        if (isReport()) return false; 
        c = new _radiobutton(this, main);
        break;
        
      case t_tab:
        if (isReport()) return false; 
        c = new _tab(this, main);
        break;
       
      case t_textbox:
        c = new _textbox(this, main);
        break;
      case t_progressbar:
        c = new _progressbar(this, main);
        break;
        /*
      case t_scrollbar:
        c = new _scrollbar(this, main);
        break;
        */
      case t_image:
        c = new _image(this, main);
        break;
       
      case t_timer:
        if (isReport()) return false; 
        c = new _timer(this, main);
        break;
      case t_treeview:
        if (isReport()) return false; 
        c = new _treeview(this, main);
        break;
        
      case t_combobox:
        if (isReport()) return false; 
        c = new _combobox(this, main);
        break;

        // CONTROL

      case t_udpsocket:
        if (isReport()) return false; 
        c = new _udpsocket(this, main);
        break;

      case t_scrollbar:
        if (isReport()) return false; 
        c = new _scrollbar(this, main);
        break;

      case t_spinbox:
        if (isReport()) return false; 
        c = new _spinbox(this, main);
        break;

      case t_slider:
        if (isReport()) return false; 
        c = new _slider(this, main);
        break;

      case t_formsview:
        if (isReport()) return false; 
        c = new _formsview(this, (QLabel *) main);
        break;

      case t_toolbarview:
        if (isReport()) return false; 
        c = new _toolbarview(this, (QLabel *) main);
        break;

      case t_svg:
        if (isReport()) return false; 
        c = new _svg(this, main);
        break;

      case t_imagebutton:
        if (isReport()) return false; 
        c = new _imagebutton(this, main);
        break;

      case t_commandlinkbutton:
        if (isReport()) return false; 
        c = new _commandlinkbutton(this, main);
        break;

      case t_resizebox:
        if (isReport()) return false; 
        c = new _resizebox(this, main);
        break;

      //case t_line:
        //c = new _line(this, main);
        //break;
      //case t_circle:
        //c = new _circle(this, main);
        //break;
      //case t_rectangle:
        //c = new _rectangle(this, main);
        //break;
        /*
      case t_hidden:
        if (isReport()) return false; 
        c = new _hidden(this, main);
        break;

      case t_toolbutton:
      case t_imagebutton:
        if (isReport()) return false; 
        c = new _imagebutton(this, main);
        break;*/

      //case t_activex:
        //c = new _activex(this, main);
        //break;
        /*
  #elif defined(RUN)
      case t_label:  c = new kb_label(this, main); break;

      case t_movie:  c = new kb_movie(this, main); break;
      case t_sound:  c = new kb_sound(this, main); break;
      case t_web:  c = new kb_web(this, main); break;

  
      case t_vsplit: c = new kb_vsplit(this, main);  break;
      case t_hsplit:
        c = new kb_hsplit(this, main);
        break;
      case t_vbox:
        c = new kb_vbox(this, main);
        break;


      case t_box: c = new kb_box(this, main); break;
      case t_childcontrol: c = new kb_childcontrol(this, main); break;
      case t_customcontrol: c = new kb_customcontrol(this, main); break;
      case t_scrollbox: c = new kb_scrollbox(this, main); break;
      case t_editor: c = new kb_editor(this, main); break;
      case t_browser: c = new kb_browser(this, main); break;
      case t_datebox: c = new kb_datebox(this, main); break;
      case t_timebox: c = new kb_timebox(this, main); break;
      case t_datetimebox: c = new kb_datetimebox(this, main); break;

      case t_vhbox:
        c = new kb_vhbox(this, main);
        break;
      case t_hbox:
        c = new kb_hbox(this, main);
        break;
      case t_commandbutton:
        c = new kb_commandbutton(this, main);
        break;
      case t_checkbox:
        c = new kb_checkbox(this, main);
        break;
      case t_frame:
        c = new kb_frame(this, main);
        break;
      case t_listbox:
        c = new kb_listbox(this, main);
        break;
      case t_radiobutton:
        c = new kb_radiobutton(this, main);
        break;
        
      case t_tab:
        c = new kb_tab(this, main);
        break;
       
      case t_textbox:
        c = new kb_textbox(this, main);
        break;
      case t_progressbar:
        c = new kb_progressbar(this, main);
        break;

      case t_image:
        c = new kb_image(this, main);
        break;
       
      case t_timer:
        c = new kb_timer(this, main);
        break;
      case t_treeview:
        c = new kb_treeview(this, main);
        break;
        
      case t_combobox:
        c = new kb_combobox(this, main);
        break;

      //case t_line:
        //c = new kb_line(this, main);
        //break;
      //case t_circle:
        //c = new kb_circle(this, main);
        //break;
      //case t_rectangle:
        //c = new kb_rectangle(this, main);
        //break;
      case t_hidden:
        c = new kb_hidden(this, main);
        break;

      case t_imagebutton:
        c = new kb_imagebutton(this, main);
        break;

      //case t_activex:
        //c = new kb_activex(this, main);
        //break;
  #endif
  */
      default:
        return false;
        break;
    }  

    cInsertControl = c;

    if (nInsert_Width == 0 || nInsert_Height == 0){

    switch(insertType){
      
      case t_SQLInfo:   
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(150, 20);
        break;
      case t_SQLInsert:
      case t_SQLUpdate:
      case t_SQLDelete:
      case t_SQLNext:
      case t_SQLPrevious:
      case t_SQLFirst:
      case t_SQLLast:
      case t_SQLRequery:      
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(20, 20);
        break;

      case t_SQLGoTo:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(50, 20);
        break;

      case t_header:
      case t_footer:
        c->lower();
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(400, 16);
        break;
          // CONTROL

      case t_spinbox:
#ifdef MAC
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 134 : 28);
#elif defined(LINUX)
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 134 : 30);
#else
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 134 : 20);
#endif	  

        break;
      case t_scrollbar:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 134 : 20);
        break;      
      case t_slider:
#ifdef LINUX
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 134 : 30);
#else
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 134 : 20);
#endif	
        break;
      case t_formsview:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(200, isReport() ? 134 : 134);
        break;
      case t_toolbarview:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(200, isReport() ? 34 : 34);
        break;
      case t_svg:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 100 : 100);
        break;
      case t_commandbutton:
#ifdef MAC
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(140, isReport() ? 16 : 34); // HIDE
#else
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(110, isReport() ? 16 : 23);
#endif
        break;
      case t_commandlinkbutton:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(180, isReport() ? 16 : 32);
        break;
      case t_combobox:
#ifdef MAC
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, 26); // HIDE
#else
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, 30);
#endif
        break;        
      case t_label:
      case t_toolbutton:
      case t_checkbox:
      case t_radiobutton:
      case t_resizebox:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(120, 30);
        break;        
      case t_textbox:
#ifdef MAC
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, 22); // HIDE
#else
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, 30);
#endif
        break;        

      case t_imagebutton:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, 30);
        break;        

      case t_datebox:
      case t_timebox:
#ifdef MAC
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 16 : 28);
#elif defined(LINUX)
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 16 : 30);
#else
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 16 : 20);
#endif	  
        break;   
	case t_datetimebox:
#ifdef MAC
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 16 : 25);
#elif defined(LINUX)
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 16 : 30);
#else
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, isReport() ? 16 : 20);
#endif	  
        break;

      case t_line:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(50, 50);
        break;

      case t_box:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(50, 50);
        break;
      //case t_line:
      //case t_circle:
      //case t_rectangle:
        //c->resize(200, 200);
        //break;
      case t_hidden:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(150, 20);
        break;
      case t_vbox:
      case t_hbox:
      case t_vhbox:
      case t_vsplit:
      case t_hsplit:
        c->lower();
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(200, 200);
        break;

      //case t_activex:
      case t_frame:
        for(int i = 0; i < 1000; i++){
          c->lower();
        }
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(200, 200);
        break;
      case t_listbox:
      case t_image:
      case t_treeview:
      case t_movie:
      case t_web:
      case t_editor:
      case t_browser:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(200, 200);
        break;
      case t_childcontrol:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(200, 200);
        break;
      case t_tab:
        c->lower();
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(300, 300);
        break;
      case t_progressbar:
#ifdef LINUX
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, 30);
#else
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(100, 20);
#endif
        break;
  //    case t_scrollbar:
      // c->resize(20, 300);
      // break;
      case t_sound:
      case t_timer:
      case t_serialport:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(200, 20);
        break;
      case t_udpsocket:
        if (nWidth >= 0 && nHeight >= 0) c->resize(nWidth, nHeight); else c->resize(200, 20);
        break;
      default:
        return false;
        break;
    }  

    } else {
      c->resize(nInsert_Width, nInsert_Height);
      nInsert_Width = 0;
      nInsert_Height = 0;
    }

    if (x - XSCROLLBAR + c->width()> width()){
      parentWidget()->setMinimumWidth(x - XSCROLLBAR + c->width());
    }

    if (y - YSCROLLBAR + c->height() > height()){
      parentWidget()->setMinimumHeight(y - YSCROLLBAR + c->height());
    }

    METHOD_insertControl(c, insertType, x, y, true, sControlName);

    if (!bSQLAll){
      selectControl(c);
      if (bUpdatePropertyWindow) updatePropertyWindow();
      EXTERN_my_parserwindow->refreshControl();
    }
   
    if (bSQLAll && insertType == t_SQLInfo){
      insertType = t_notype;
      bSQLAll = false;
    }

  } while (bSQLAll);

  if (bRefreshProject){
    EXTERN_my_projectwindow->refresh();
  }

    return true;
}



#endif

t_boolean _form::METHOD_insertControl(QWidget *c, _controlType controlType, int x, int y, bool bMove, QString s2, bool bShow)
{
  QString s = s2; 

  switch(controlType){
    case t_commandbutton:
      //if (!s2.length()) 
      commandbuttons.uniqueName(&s);
      if (s.isEmpty()) s = s2;
      ((_commandbutton *) c)->SETPROPERTY_Name(s);
#ifdef IDE
    case t_SQLInsert:
    case t_SQLUpdate:
    case t_SQLDelete:
    case t_SQLNext:
    case t_SQLPrevious:
    case t_SQLFirst:
    case t_SQLLast:
    case t_SQLRequery:     
#endif
      commandbuttons.add(commandbuttons.count(), s, (_commandbutton *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);

        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_commandbutton *) c)->show();
      break;

    case t_commandlinkbutton:
      //if (!s2.length()) 
        commandlinkbuttons.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      commandlinkbuttons.add(commandlinkbuttons.count(), s, (_commandlinkbutton *) c);
      ((_commandlinkbutton *) c)->SETPROPERTY_Name(s);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_commandlinkbutton *) c)->show();
      break;

    case t_box:
      //if (!s2.length()) 
        boxes.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      boxes.add(boxes.count(), s, (_box *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_box *) c)->show();
      ((_box *) c)->SETPROPERTY_Name(s);
      break;
    case t_header:
      //if (!s2.length()) 
        headers.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      headers.add(headers.count(), s, (_header *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_header *) c)->show();
      ((_header *) c)->SETPROPERTY_Name(s);
      break;
    case t_footer:
     // if (!s2.length())
        footers.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      footers.add(footers.count(), s, (_footer *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_footer *) c)->show();
      ((_footer *) c)->SETPROPERTY_Name(s);
      break;

    case t_label:
      //if (!s2.length()) 
      labels.uniqueName(&s);
      if (s.isEmpty()) s = s2;
      ((_label *) c)->SETPROPERTY_Name(s);
#ifdef IDE
    case t_SQLInfo:      
#endif
      labels.add(labels.count(), s, (_label *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_label *) c)->show();      
      break;


    case t_movie:
      //if (!s2.length()) 
        movies.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_movie *) c)->SETPROPERTY_Name(s);
      movies.add(movies.count(), s, (_movie *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_movie *) c)->show();      
      break;
    case t_sound:
     // if (!s2.length())
        sounds.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_sound *) c)->SETPROPERTY_Name(s);
      sounds.add(sounds.count(), s, (_sound *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_sound *) c)->show();      
      break;
    case t_web:
    //  if (!s2.length())
        webs.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_web *) c)->SETPROPERTY_Name(s);
      webs.add(webs.count(), s, (_web *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_web *) c)->show();      
      break;

      // CONTROL

    case t_udpsocket:
     // if (!s2.length())
        udpsockets.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_udpsocket *) c)->SETPROPERTY_Name(s);
      udpsockets.add(udpsockets.count(), s, (_udpsocket *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_udpsocket *) c)->show();      
      break;

    case t_scrollbar:
     // if (!s2.length())
        scrollbars.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_scrollbar *) c)->SETPROPERTY_Name(s);
      scrollbars.add(scrollbars.count(), s, (_scrollbar *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_scrollbar *) c)->show();      
      break;


    case t_spinbox:
    //  if (!s2.length()) 
        spinboxes.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_spinbox *) c)->SETPROPERTY_Name(s);
      spinboxes.add(spinboxes.count(), s, (_spinbox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_spinbox *) c)->show();      
      break;


    case t_slider:
     // if (!s2.length()) 
        sliders.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_slider *) c)->SETPROPERTY_Name(s);
      sliders.add(sliders.count(), s, (_slider *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_slider *) c)->show();      
      break;

    case t_formsview:
     // if (!s2.length())
        formsviews.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_formsview *) c)->SETPROPERTY_Name(s);
      formsviews.add(formsviews.count(), s, (_formsview *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_formsview *) c)->show();      
      break;

    case t_toolbarview:
     // if (!s2.length())
        toolbarviews.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_toolbarview *) c)->SETPROPERTY_Name(s);
      toolbarviews.add(toolbarviews.count(), s, (_toolbarview *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_toolbarview *) c)->show();      
      break;

    case t_svg:
    //  if (!s2.length())
        svgs.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_svg *) c)->SETPROPERTY_Name(s);
      svgs.add(svgs.count(), s, (_svg *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_svg *) c)->show();      
      break;

    case t_resizebox:
     // if (!s2.length())
        resizeboxes.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_resizebox *) c)->SETPROPERTY_Name(s);
      resizeboxes.add(resizeboxes.count(), s, (_resizebox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_resizebox *) c)->show();      
      break;

    case t_toolbutton:
     // if (!s2.length())
        toolbuttons.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_toolbutton *) c)->SETPROPERTY_Name(s);
      toolbuttons.add(toolbuttons.count(), s, (_toolbutton *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_toolbutton *) c)->show();      
      break;
    case t_line:
     // if (!s2.length())
        lines.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_line *) c)->SETPROPERTY_Name(s);
      lines.add(lines.count(), s, (_line *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_line *) c)->show();      
      break;

//#ifndef FASTMODE

      /*
    case t_vsplit:
    //  if (!s2.length())
      vsplits.uniqueName(&s);
      if (s.isEmpty()) s = s2;
      vsplits.add(vsplits.count(), s, (_vsplit *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_vsplit *) c)->show();
      ((_vsplit *) c)->SETPROPERTY_Name(s);
      break;
    case t_hsplit:
      //if (!s2.length())
      hsplits.uniqueName(&s);
      if (s.isEmpty()) s = s2;
      hsplits.add(hsplits.count(), s, (_hsplit *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_hsplit *) c)->show();
      ((_hsplit *) c)->SETPROPERTY_Name(s);
      break;
    case t_vbox:
      //if (!s2.length())
      vboxes.uniqueName(&s);
      if (s.isEmpty()) s = s2;
      vboxes.add(vboxes.count(), s, (_vbox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_vbox *) c)->show();
      ((_vbox *) c)->SETPROPERTY_Name(s);
      break;
    case t_vhbox:
     // if (!s2.length()) 
      vhboxes.uniqueName(&s);
      if (s.isEmpty()) s = s2;
      vhboxes.add(vhboxes.count(), s, (_vhbox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_vhbox *) c)->show();
      ((_vhbox *) c)->SETPROPERTY_Name(s);
      break;
    case t_hbox:
   //   if (!s2.length())
      hboxes.uniqueName(&s);
      if (s.isEmpty()) s = s2;
      hboxes.add(hboxes.count(), s, (_hbox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_hbox *) c)->show();
      ((_hbox *) c)->SETPROPERTY_Name(s);
      break;*/
    case t_checkbox:
     // if (!s2.length())
        checkboxes.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      checkboxes.add(checkboxes.count(), s, (_checkbox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_checkbox *) c)->show();
      ((_checkbox *) c)->SETPROPERTY_Name(s);
      break;

    case t_frame:
     // if (!s2.length())
        frames.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      frames.add(frames.count(), s, (_frame *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_frame *) c)->show();
      ((_frame *) c)->SETPROPERTY_Name(s);
      break;
    case t_listbox:
   //   if (!s2.length())
        listboxes.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      listboxes.add(listboxes.count(), s, (_listbox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_listbox *) c)->show();
      ((_listbox *) c)->SETPROPERTY_Name(s);
      break;
   
    case t_radiobutton:
     // if (!s2.length()) 
        radiobuttons.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      radiobuttons.add(radiobuttons.count(), s, (_radiobutton *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_radiobutton *) c)->show();
      ((_radiobutton *) c)->SETPROPERTY_Name(s);
      break;
      
    case t_tab:
      //if (!s2.length())
        tabs.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      tabs.add(tabs.count(), s, (_tab *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_tab *) c)->show();
      ((_tab *) c)->SETPROPERTY_Name(s);
#ifdef IDE
      if (x != -1 || y != -1){ // if inserted while designing
        ((_tab *) c)->METHOD_InsertTab(-1, "", "Page");
//        ((_tab *) c)->SETPROPERTY_Pages("Page");      
      }
#endif

      break;
      
    case t_textbox:      
      //if (!s2.length())
        textboxes.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      ((_textbox *) c)->SETPROPERTY_Name(s);
#ifdef IDE
    case t_SQLGoTo:
#endif
      textboxes.add(textboxes.count(), s, (_textbox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_textbox *) c)->show();
      break;
    case t_progressbar:
     // if (!s2.length()) 
        progressbars.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      progressbars.add(progressbars.count(), s, (_progressbar *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_progressbar *) c)->show();
      ((_progressbar *) c)->SETPROPERTY_Name(s);
      break;
      
    case t_image:
     // if (!s2.length()) 
        images.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      images.add(images.count(), s, (_image *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_image *) c)->show();
      ((_image *) c)->SETPROPERTY_Name(s);
      break;
    case t_serialport:
      //if (!s2.length())
        serialports.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      serialports.add(serialports.count(), s, (_serialport *) c);
      
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
      //  incWidth(c, 0);
      //  incHeight(c, 0);
      }
      //if (bShow) ((_serialport *) c)->show();*/
      ((_serialport *) c)->SETPROPERTY_Name(s);
      break;      
    case t_timer:
   //   if (!s2.length())
        timers.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      timers.add(timers.count(), s, (_timer *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_timer *) c)->show();
      ((_timer *) c)->SETPROPERTY_Name(s);
      break;
    case t_treeview:
  //    if (!s2.length())
        treeviews.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      treeviews.add(treeviews.count(), s, (_treeview *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_treeview *) c)->show();
      ((_treeview *) c)->SETPROPERTY_Name(s);
      break;
      

    case t_combobox:
   //   if (!s2.length())
        comboboxes.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      comboboxes.add(comboboxes.count(), s, (_combobox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_combobox *) c)->show();
      ((_combobox *) c)->SETPROPERTY_Name(s);
      break;

/*
    case t_hidden:
    //  if (!s2.length()) 
      hiddens.uniqueName(&s);
      if (s.isEmpty()) s = s2;
      hiddens.add(hiddens.count(), s, (_hidden *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_hidden *) c)->show();
      ((_hidden *) c)->SETPROPERTY_Name(s);
      break;*/

    case t_imagebutton:
     // if (!s2.length()) 
        imagebuttons.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      imagebuttons.add(imagebuttons.count(), s, (_imagebutton *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_imagebutton *) c)->show();
      ((_imagebutton *) c)->SETPROPERTY_Name(s);
      break;

    case t_childcontrol:
     // if (!s2.length())
        childcontrols.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      childcontrols.add(childcontrols.count(), s, (_childcontrol *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_childcontrol *) c)->show();
      ((_childcontrol *) c)->SETPROPERTY_Name(s);
      
      break;
            
    case t_browser:
    //  if (!s2.length())
        browsers.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      browsers.add(browsers.count(), s, (_browser *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_browser *) c)->show();
      ((_browser *) c)->SETPROPERTY_Name(s);
      break;
      
    case t_editor:
     // if (!s2.length())
        editors.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      editors.add(editors.count(), s, (_editor *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_editor *) c)->show();
      ((_editor *) c)->SETPROPERTY_Name(s);
      break;
      
    case t_datebox:
    //  if (!s2.length()) 
        dateboxes.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      dateboxes.add(dateboxes.count(), s, (_datebox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_datebox *) c)->show();
      ((_datebox *) c)->SETPROPERTY_Name(s);
      break;
      
    case t_timebox:
     // if (!s2.length())
        timeboxes.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      timeboxes.add(timeboxes.count(), s, (_timebox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_timebox *) c)->show();
      ((_timebox *) c)->SETPROPERTY_Name(s);
      break;
      
    case t_datetimebox:
      //if (!s2.length()) 
        datetimeboxes.uniqueName(&s);
        if (s.isEmpty()) s = s2;
      datetimeboxes.add(datetimeboxes.count(), s, (_datetimebox *) c);
      if (bMove){ 
        my_move(c, x - XSCROLLBAR, y - YSCROLLBAR);
        incWidth(c, 0);
        incHeight(c, 0);
      }
      if (bShow) ((_datetimebox *) c)->show();
      ((_datetimebox *) c)->SETPROPERTY_Name(s);
      break;


  }
#ifdef IDE
  setParentControl(c, x, y, true);
  c->setAcceptDrops(false); // missused as selected flag
#endif

  return true;
}

bool _form::isModified()
{  
  QWidget *c;

  if (bModified) return true;

  if (firstControl(&c)){

    do {

      QString sControlType = c->property("__kb1979.ControlType.kb__").toString();

      // CONTROL
      if (sControlType == "TextBox"){ if (((_textbox *) c)->bModified) return true; }
      else if (sControlType == "UdpSocket"){ if (((_udpsocket *) c)->bModified) return true; }
      else if (sControlType == "ScrollBar"){ if (((_scrollbar *) c)->bModified) return true; }
      else if (sControlType == "SpinBox"){ if (((_spinbox *) c)->bModified) return true; }
      else if (sControlType == "Slider"){ if (((_slider *) c)->bModified) return true; }
      else if (sControlType == "FormsView"){ if (((_formsview *) c)->bModified) return true; }
      else if (sControlType == "ToolBarView"){ if (((_toolbarview *) c)->bModified) return true; }
      else if (sControlType == "SvgBox"){ if (((_svg *) c)->bModified) return true; }
      else if (sControlType == "CommandLinkButton"){ if (((_commandlinkbutton *) c)->bModified) return true; }
      else if (sControlType == "ResizeBox"){ if (((_resizebox *) c)->bModified) return true; }
      else if (sControlType == "ToolButton"){ if (((_toolbutton *) c)->bModified) return true; }
      else if (sControlType == "Line"){ if (((_line *) c)->bModified) return true; }
      else if (sControlType == "MovieBox"){ if (((_movie *) c)->bModified) return true; }
      else if (sControlType == "Sound"){ if (((_sound *) c)->bModified) return true; }
      else if (sControlType == "WebView"){ if (((_web *) c)->bModified) return true; }
      else if (sControlType == "Label"){ if (((_label *) c)->bModified) return true; }
      else if (sControlType == "SerialPort"){ if (((_serialport *) c)->bModified) return true; }
      else if (sControlType == "Header"){ if (((_header *) c)->bModified) return true; }
      else if (sControlType == "Footer"){ if (((_footer *) c)->bModified) return true; }
      else if (sControlType == "Box"){ if (((_box *) c)->bModified) return true; }
      else if (sControlType == "CommandButton"){ if (((_commandbutton *) c)->bModified) return true; }
      else if (sControlType == "CheckBox"){ if (((_checkbox *) c)->bModified) return true; }
      else if (sControlType == "Frame"){ if (((_frame *) c)->bModified) return true; }
      else if (sControlType == "ListBox"){ if (((_listbox *) c)->bModified) return true; }
      else if (sControlType == "RadioButton"){ if (((_radiobutton *) c)->bModified) return true; }
      else if (sControlType == "TabView"){ if (((_tab *) c)->bModified) return true; }
      else if (sControlType == "TextBox"){ if (((_textbox *) c)->bModified) return true; }
      else if (sControlType == "ProgressBar"){ if (((_progressbar *) c)->bModified) return true; }
      else if (sControlType == "ImageBox"){ if (((_image *) c)->bModified) return true; }
      else if (sControlType == "Timer"){ if (((_timer *) c)->bModified) return true; }
      else if (sControlType == "TreeView"){ if (((_treeview *) c)->bModified) return true; }
      else if (sControlType == "ComboBox"){ if (((_combobox *) c)->bModified) return true; }
      else if (sControlType == "FormView"){ if (((_childcontrol *) c)->bModified) return true; }
      else if (sControlType == "HtmlView"){ if (((_browser *) c)->bModified) return true; }
      else if (sControlType == "RichTextBox"){ if (((_editor *) c)->bModified) return true; }
      else if (sControlType == "DateBox"){ if (((_datebox *) c)->bModified) return true; }
      else if (sControlType == "TimeBox"){ if (((_timebox *) c)->bModified) return true; }
      else if (sControlType == "DateTimeBox"){ if (((_datetimebox *) c)->bModified) return true; }
      else if (sControlType == "ImageButton"){ if (((_imagebutton *) c)->bModified) return true; }

    } while (nextControl(&c)); 
  }

  return bModified;
}

void _form::setNonModified()
{  
  QWidget *c;

  if (firstControl(&c)){

    do {

      QString sControlType = c->property("__kb1979.ControlType.kb__").toString();

      // CONTROL
      if (sControlType == "TextBox"){ ((_textbox *) c)->bModified = false; }
      else if (sControlType == "UdpSocket"){ ((_udpsocket *) c)->bModified = false;    }   
      else if (sControlType == "ScrollBar"){ ((_scrollbar *) c)->bModified = false;    }   
      else if (sControlType == "SpinBox"){ ((_spinbox *) c)->bModified = false;    }   
      else if (sControlType == "Slider"){ ((_slider *) c)->bModified = false;    }   
      else if (sControlType == "FormsView"){ ((_formsview *) c)->bModified = false;    }   
      else if (sControlType == "ToolBarView"){ ((_toolbarview *) c)->bModified = false;    }   
      else if (sControlType == "SvgBox"){ ((_svg *) c)->bModified = false;    }   
      else if (sControlType == "CommandLinkButton"){ ((_commandlinkbutton *) c)->bModified = false;    }   
      else if (sControlType == "ResizeBox"){ ((_resizebox *) c)->bModified = false;    }   
      else if (sControlType == "ToolButton"){ ((_toolbutton *) c)->bModified = false;    }   
      else if (sControlType == "Line"){ ((_line *) c)->bModified = false;    }   
      else if (sControlType == "MovieBox"){ ((_movie *) c)->bModified = false;    }   
      else if (sControlType == "Sound"){ ((_sound *) c)->bModified = false;    }   
      else if (sControlType == "WebView"){ ((_web *) c)->bModified = false;    }   
      else if (sControlType == "Label"){ ((_label *) c)->bModified = false;    }   
      else if (sControlType == "SerialPort"){ ((_serialport *) c)->bModified = false;    }   
      else if (sControlType == "Header"){ ((_header *) c)->bModified = false;      } 
      else if (sControlType == "Footer"){ ((_footer *) c)->bModified = false;      } 
      else if (sControlType == "Box"){ ((_box *) c)->bModified = false;       }
      else if (sControlType == "CommandButton"){ ((_commandbutton *) c)->bModified = false;       }
      else if (sControlType == "CheckBox"){ ((_checkbox *) c)->bModified = false;       }
      else if (sControlType == "Frame"){ ((_frame *) c)->bModified = false;       }
      else if (sControlType == "ListBox"){ ((_listbox *) c)->bModified = false;       }
      else if (sControlType == "RadioButton"){ ((_radiobutton *) c)->bModified = false;      } 
      else if (sControlType == "TabView"){ ((_tab *) c)->bModified = false;       }
      else if (sControlType == "TextBox"){ ((_textbox *) c)->bModified = false;       }
      else if (sControlType == "ProgressBar"){ ((_progressbar *) c)->bModified = false;    }   
      else if (sControlType == "ImageBox"){ ((_image *) c)->bModified = false;       }
      else if (sControlType == "Timer"){ ((_timer *) c)->bModified = false;       }
      else if (sControlType == "TreeView"){ ((_treeview *) c)->bModified = false;       }
      else if (sControlType == "ComboBox"){ ((_combobox *) c)->bModified = false;       }
      else if (sControlType == "FormView"){ ((_childcontrol *) c)->bModified = false;     }  
      else if (sControlType == "HtmlView"){ ((_browser *) c)->bModified = false;       }
      else if (sControlType == "RichTextBox"){ ((_editor *) c)->bModified = false;       }
      else if (sControlType == "DateBox"){ ((_datebox *) c)->bModified = false;       }
      else if (sControlType == "TimeBox"){ ((_timebox *) c)->bModified = false;       }
      else if (sControlType == "DateTimeBox"){ ((_datetimebox *) c)->bModified = false;   }    
      else if (sControlType == "ImageButton"){ ((_imagebutton *) c)->bModified = false;   }    

    } while (nextControl(&c)); 
  }
  
  bModified = false;
}

#ifdef IDE
void _form::showFocusOrder(bool bChange)
{    
  QWidget *c;

  if (firstControl(&c)){

    static QFont f;
    f.setFamily("Arial");
    f.setPointSize(12);
    f.setBold(true);
    
    do {

      if (qobject_cast<_tab *>(c)) continue;

      if (bChange == false ||!bShowFocusOrder){

        int nFocusOrder = 0;

        #define SWITCH GETPROPERTY_FocusOrder();      
        #define SWITCH3 nFocusOrder
        #include "_form_property_switch.h"   
        #undef SWITCH3

        QString sControlType = c->property("__kb1979.ControlType.kb__").toString();
        // CONTROL
        // show focus order?
        if (sControlType == "UdpSocket") continue;
        if (sControlType == "ScrollBar") continue;
        if (sControlType == "Slider") continue;
        if (sControlType == "FormsView") continue;
        if (sControlType == "ToolBarView") continue;
        if (sControlType == "Label") continue;
        if (sControlType == "SvgBox") continue;
        if (sControlType == "ResizeBox") continue;
        if (sControlType == "Frame") continue;
        if (sControlType == "ImageBox") continue;
        if (sControlType == "Timer") continue;
        if (sControlType == "Box") continue;
        if (sControlType == "Sound") continue;
        if (sControlType == "MovieBox") continue;
        if (sControlType == "SerialPort") continue;
        if (sControlType == "Line") continue;

        QObject *o = c->findChild<QLabel *>("FocusOrder");
        
        QLabel *l = 0;
        if (o) l = (QLabel *) o;

        if (l == 0){
          l = new QLabel("", c);
          l->setObjectName("FocusOrder");

          l->setFont(f);
          QPalette p = l->palette();          
          p.setColor(QPalette::ButtonText, Qt::red);  
          p.setColor(QPalette::WindowText, Qt::red);  
          p.setColor(QPalette::Text, Qt::red);  
 
          l->setPalette(p);
          l->resize(30, 30);
        }
        l->setText(QString("%1").arg(nFocusOrder));

        l->show();
      } else {
        QObject *o = c->findChild<QLabel *>("FocusOrder");      
        QLabel *l = 0;
        if (o) l = (QLabel *) o;
        if (l) l->hide();
      }      

    } while (nextControl(&c)); 

    if (bChange) bShowFocusOrder = !bShowFocusOrder;   
    EXTERN_my_mainwindow->VIEW_FOCUSORDER->setChecked(bShowFocusOrder);


    
  }


}


void _form::showSQLSettings(bool bChange)
{    
  QWidget *c;

  if (firstControl(&c)){

    static QFont f;
    f.setFamily("Arial");
    f.setPointSize(12);
    f.setBold(true);
    
    do {

      if (qobject_cast<_tab *>(c)) continue;

      if (bChange == false ||!bShowSQLSettings){

        QString sSQLName = "";

        #define SWITCH GETPROPERTY_SQLName();      
        #define SWITCH3 sSQLName
        #include "_form_property_switch.h"   
        #undef SWITCH3

        QObject *o = c->findChild<QLabel *>("SQLName");
        
        QLabel *l = 0;
        if (o) l = (QLabel *) o;

        if (l == 0){
          l = new QLabel("", c);
          l->setIndent(10);
          l->setObjectName("SQLName");

          l->setFont(f);
          QPalette p = l->palette();          
          p.setColor(QPalette::ButtonText, Qt::blue);  
          p.setColor(QPalette::WindowText, Qt::blue);  
          p.setColor(QPalette::Text, Qt::blue);   
          l->setPalette(p);
          l->resize(100, 30);
        }
        if (!sSQLName.isEmpty()) l->setText(QString("%1").arg(sSQLName));

        l->show();
      } else {
        QObject *o = c->findChild<QLabel *>("SQLName");      
        QLabel *l = 0;
        if (o) l = (QLabel *) o;
        if (l) l->hide();
      }      

    } while (nextControl(&c)); 

    if (bChange) bShowSQLSettings = !bShowSQLSettings;   
    EXTERN_my_mainwindow->VIEW_SQLSETTINGS->setChecked(bShowSQLSettings);

    
  }


}





void _form::showSQLTables(bool bChange)
{    
}






#endif

#ifdef RUN

void  _main::paintEvent(QPaintEvent *e)
{
   QRect r = e->rect();
   f->EVENT_OnPaint(r.x(), r.y(), r.width(), r.height());
   QWidget::paintEvent(e);
}
/*
void  _main::actionEvent(QActionEvent *e){ f->actionEvent(e); }
void  _main::changeEvent(QEvent *e){ f->changeEvent(e); }
void  _main::contextMenuEvent(QContextMenuEvent *e){ f->contextMenuEvent(e); }
void  _main::dragEnterEvent(QDragEnterEvent *e){ f->dragEnterEvent(e); }
void  _main::dragLeaveEvent(QDragLeaveEvent *e){ f->dragLeaveEvent(e); }
void  _main::dragMoveEvent(QDragMoveEvent *e){ f->dragMoveEvent(e); }
void  _main::dropEvent(QDropEvent *e){ f->dropEvent(e); }
void  _main::enterEvent(QEvent *e){ f->enterEvent(e); }
void  _main::focusInEvent(QFocusEvent *e){ f->focusInEvent(e); }
void  _main::focusOutEvent(QFocusEvent *e){ f->focusOutEvent(e); }
void  _main::hideEvent(QHideEvent *e){ f->hideEvent(e); }
void  _main::inputMethodEvent(QInputMethodEvent *e){ f->inputMethodEvent(e); }
void  _main::keyPressEvent(QKeyEvent *e){ f->keyPressEvent(e); }
void  _main::keyReleaseEvent(QKeyEvent *e){ f->keyReleaseEvent(e); }
void  _main::leaveEvent(QEvent *e){ f->leaveEvent(e); }
void  _main::mouseDoubleClickEvent(QMouseEvent *e){ f->mouseDoubleClickEvent(e); }
void  _main::mouseMoveEvent(QMouseEvent *e){ f->mouseMoveEvent(e); }
void  _main::mousePressEvent(QMouseEvent *e){ f->mousePressEvent(e); }
void  _main::mouseReleaseEvent(QMouseEvent *e){ f->mouseReleaseEvent(e); }
void  _main::resizeEvent(QResizeEvent *e){ f->resizeEvent(e); }
void  _main::tabletEvent(QTabletEvent *e){ f->tabletEvent(e); }
void  _main::wheelEvent(QWheelEvent *e){ f->wheelEvent(e); }
*/

#endif
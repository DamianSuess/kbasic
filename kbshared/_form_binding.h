
//#include "__property_tableview.h"
#include "__property_flag.h"
#include "__property_icon.h"
//#include "__property_iconcaption.h"
#include "__property_caption.h"
#include "__property_modal.h"
//#include "__property_openonstartup.h"
//#include "__property_stoponclose.h"
#include "__property_scrollx.h"
#include "__property_scrolly.h"
#include "__property_scrollwidth.h"
#include "__property_scrollheight.h"
#include "__property_scrollbar.h"
//#include "__property_mousetracking.h"


// ***

/*
void timerEvent(QTimerEvent *event)  
{
  EVENT_OnTimer();
}
*/

int nCurrentMultiPage;
int nOldCurrentMultiPage;

bool bIsFilterActive;

virtual void EVENT_OnMultiPageShow(t_integer nPage)
{
  nOldCurrentMultiPage = nPage;
}


t_boolean METHOD_IsShownFullScreen(); 
t_boolean METHOD_IsShownMaximized(); 
t_boolean METHOD_IsShownMinimized(); 
t_boolean METHOD_IsShownNormal(); 



t_boolean METHOD_Append(QString ControlName, QString ControlType, QString ControlGroup, t_integer X, t_integer Y, t_integer Width, t_integer Height, t_boolean Visible);

t_boolean METHOD_Remove(QString ControlName);


#ifdef RUN
void SETPROPERTY_MoveOnMouseDrag(t_boolean b)
{  
  if (b) setMouseTracking(true);
  _property::SETPROPERTY_MoveOnMouseDrag(b);
}
#endif

/*
t_boolean GETPROPERTY_MoveOnMouseDrag()
{
  return false;
}

*/

void METHOD_SetWithTag(QString Tag, QString PropertyName, t_boolean b);
void METHOD_SetWithTag(QString Tag, QString PropertyName, t_integer n);
void METHOD_SetWithTag(QString Tag, QString PropertyName, QString s);
void METHOD_SetWithTag(QString Tag, QString PropertyName, t_double d);

void METHOD_SetWithGroup(QString Group, QString PropertyName, t_boolean b);
void METHOD_SetWithGroup(QString Group, QString PropertyName, t_integer n);
void METHOD_SetWithGroup(QString Group, QString PropertyName, QString s);
void METHOD_SetWithGroup(QString Group, QString PropertyName, t_double d);

void METHOD_ShowMultiPage(t_integer nPage); 
void METHOD_ShowNextMultiPage(); 
void METHOD_ShowPreviousMultiPage();

void METHOD_OpenPrintDialog(); // only for reports
void METHOD_OpenPrint(); // only for reports
void METHOD_OpenPrintPreview(); // only for reports

QString METHOD_FocusControl()
{
  QWidget *w = QApplication::focusWidget();

  QWidget *c;
  if (firstControl(&c)){
     do {
       if (c == w){
          QString sControlName = "";
                        
          #define SWITCH GETPROPERTY_Name();      
          #define SWITCH3 sControlName
          #include "_form_property_switch.h"   
          #undef SWITCH3

          return sControlName;
       }

     } while (nextControl(&c));
  }
  return "";

}

QString METHOD_ControlFirst()
{
  QWidget *c;

  if (firstControl(&c)){
    QString sControlName = "";
                
    #define SWITCH GETPROPERTY_Name();      
    #define SWITCH3 sControlName
    #include "_form_property_switch.h"   
    #undef SWITCH3

    return sControlName;     
  }
  return "";
}

QString METHOD_ControlNext()
{
  QWidget *c;

  if (nextControl(&c)){
    QString sControlName = "";
                
    #define SWITCH GETPROPERTY_Name();      
    #define SWITCH3 sControlName
    #include "_form_property_switch.h"   
    #undef SWITCH3

    return sControlName;     
  }
  return "";
}
/*
void METHOD_SetFocus()
{
  setActiveWindow();
}


QString METHOD_Tr(t_string s)
{
  return tr(s);
}*/


void METHOD_ShowFullScreen()
{
  if (bOpened){

    noFullScreenParent = parentWidget();
/*
    QMdiSubWindow *o = 0;
    if (noFullScreenParent && (o = qobject_cast<QMdiSubWindow *>(noFullScreenParent))){
      noFullScreenWindowFlags = windowFlags();
     // QRect r = o->layout()->contentsRect();         
      noFullScreenPos = o->pos();
      //noFullScreenOffset = QPoint(r.left(), r.top());
      noFullScreenSize = o->size();      
//      noFullScreenSize2 = QPoint(r.left() * 2, r.top());
     // o->hide();
//      forms_workspace->removeSubWindow(o);
      o->hide();
      
    } else {
      */
      noFullScreenWindowFlags = windowFlags();
      noFullScreenPos = pos();
//      noFullScreenOffset = QPoint(0, 0);
      noFullScreenSize = size();
  //  }


    setParent(0);
    bFullscreen = true;

    showFullScreen();
    //oldSize = size();
  }
}

void METHOD_ShowNormal()
{
  if (bOpened){

    if (bFullscreen){
      bFullscreen = false;

      setHidden(true);
      QMdiSubWindow *o = 0;
      if (noFullScreenParent && (o = qobject_cast<QMdiSubWindow *>(noFullScreenParent))){
        o->setHidden(true);
        setParent(noFullScreenParent, noFullScreenWindowFlags);    
        //forms_workspace->addSubWindow(o);
        //QWidget::move(noFullScreenOffset);
       // o->move(noFullScreenPos);
        o->setWidget(0); o->setWidget(this);
        //o->resize(noFullScreenSize);
        //noFullScreenSize.setWidth(noFullScreenSize.width() - noFullScreenOffset.x() * 2);
       // bResizeEventFlag = false; resize(noFullScreenSize);
        showNormal();
      } else {
        setParent(noFullScreenParent, noFullScreenWindowFlags);    
        move(noFullScreenPos);
        resize(noFullScreenSize);
        showNormal();
      }

    } else {
      showNormal();
    }
    
  }

}

void METHOD_ShowCentered()
{
  if (bOpened){

    if (bFullscreen){
      bFullscreen = false;

      setHidden(true);
      QMdiSubWindow *o = 0;
      if (noFullScreenParent && (o = qobject_cast<QMdiSubWindow *>(noFullScreenParent))){
        o->setHidden(true);
        setParent(noFullScreenParent, noFullScreenWindowFlags);    
        //forms_workspace->addSubWindow(o);
        //QWidget::move(noFullScreenOffset);
        //o->move(noFullScreenPos);
        //o->resize(noFullScreenSize);
        //resize(noFullScreenSize);

        o->setWidget(0); o->setWidget(this);

        QWidget *w = parentWidget()->parentWidget();
        QWidget *ww = parentWidget();
        ww->setGeometry(w->width() / 2 - ww->width() / 2, w->height() / 2 - ww->height() / 2, ww->width(), ww->height());
        show();

      } else {
        setParent(noFullScreenParent, noFullScreenWindowFlags);    
        //move(noFullScreenPos);
        //resize(noFullScreenSize);

        setGeometry(QApplication::desktop()->width() / 2 - width() / 2, QApplication::desktop()->height() / 2 - height() / 2, width(), height());
        show();            
      }

    } else {

      if (forms_workspace && parentWidget() && (qobject_cast<QMdiSubWindow *>(parentWidget()))){
        QWidget *w = parentWidget()->parentWidget();
        QWidget *ww = parentWidget();
        ww->setGeometry(w->width() / 2 - ww->width() / 2, w->height() / 2 - ww->height() / 2, ww->width(), ww->height());
        show();
        
        //forms_workspace->update();
      } else {
        setGeometry(QApplication::desktop()->width() / 2 - width() / 2, QApplication::desktop()->height() / 2 - height() / 2, width(), height());
        show();
      }         

    }
    
  }

}

int nWasMaximized;

void METHOD_ShowMaximized()
{
  if (bOpened){

    if (bFullscreen){
      bFullscreen = false;

      setHidden(true);
      QMdiSubWindow *o = 0;
      if (noFullScreenParent && (o = qobject_cast<QMdiSubWindow *>(noFullScreenParent))){
        o->setHidden(true);
        setParent(noFullScreenParent, noFullScreenWindowFlags);    
        //forms_workspace->addSubWindow(o);

        o->setWidget(0); o->setWidget(this);
        /*
        move(noFullScreenOffset);

        o->move(noFullScreenPos);
        o->resize(noFullScreenSize);
        resize(noFullScreenSize);
        nWasMaximized = 2;
        */

        showMaximized();
      } else {
        setParent(noFullScreenParent, noFullScreenWindowFlags);    
        move(noFullScreenPos);
        resize(noFullScreenSize);
      //  nWasMaximized = 2;
        showMaximized();
      }
    } else {
   //   nWasMaximized = 2;
      showMaximized();
    }
    
  }
}

void METHOD_ShowMinimized()
{
  if (bOpened){

    if (bFullscreen){
      bFullscreen = false;

      setHidden(true);
      QMdiSubWindow *o = 0;
      if (noFullScreenParent && (o = qobject_cast<QMdiSubWindow *>(noFullScreenParent))){
        o->setHidden(true);
        setParent(noFullScreenParent, noFullScreenWindowFlags);    

        o->setWidget(0); o->setWidget(this);
        /*
        //forms_workspace->addSubWindow(o);
        move(noFullScreenOffset);
        o->move(noFullScreenPos);
        o->resize(noFullScreenSize);
        resize(noFullScreenSize);*/
        showMinimized();
      } else {
        setParent(noFullScreenParent, noFullScreenWindowFlags);    
        move(noFullScreenPos);
        resize(noFullScreenSize);
        showMinimized();
      }

    } else {
      showMinimized();
    }
    
  }

}

_control *METHOD_Control(QString s)
{
  QWidget *c;
  if (firstControl(&c)){
     do {
       QString sControlName = "";
                    
       #define SWITCH GETPROPERTY_Name();      
       #define SWITCH3 sControlName
       #include "_form_property_switch.h"   
       #undef SWITCH3
       if (s == sControlName){
          return (_control *) c;
       }

     } while (nextControl(&c));
  }

  return 0;
}

bool bLoading;

t_boolean METHOD_Load(QString s);


void METHOD_Finish();

          _record *METHOD_Record()
          { 
          #ifdef RUN
          #endif
            return 0;
          }

        
virtual void EVENT_OnScroll()
{
}

virtual void EVENT_OnAddNew()
{
}

virtual void EVENT_OnDirty()
{
}


virtual void EVENT_OnQuery()
{
}

virtual void EVENT_OnLoad()
{
}

virtual void EVENT_OnGoTo()
{
}

virtual void EVENT_OnGoTo2()
{
}

#ifdef RUN
void EVENT_OnGoTo3();
#endif

virtual void EVENT_OnBeforeInsert(t_boolean *Cancel)
{
}

    virtual void EVENT_OnAfterInsert()
    {
    }

virtual void EVENT_OnBeforeUpdate(t_boolean *Cancel)
{
}

    virtual void EVENT_OnAfterUpdate()
    {
    }

virtual void EVENT_OnBeforeDelete(t_boolean *Cancel)
{
}

t_long METHOD_Hwnd()
{
  if (nativeParentWidget()){
    return (t_long) nativeParentWidget()->effectiveWinId();
  }
  return (t_long) effectiveWinId();
}


t_variant METHOD_Read(QString SearchFor, QString InTableDotField, QString ReturnFieldName);
t_variant METHOD_Get(QString SQL);

t_integer METHOD_kbrecordid(QString sFieldName = "kbrecordid");
t_integer METHOD_kbrecordid2(QString ChildControl);

t_integer METHOD_PrimaryKey();
t_integer METHOD_PrimaryKey2(QString ChildControl);

QString METHOD_PrimaryKeyName();
QString METHOD_PrimaryKeyName2(QString ChildControl);

t_boolean METHOD_IsFilterActive()
{
  return bIsFilterActive;
}

t_boolean METHOD_Seek(QString Filter1, QString Filter2, QString Filter3, QString Filter4, QString Filter5, QString Filter6);

    virtual void EVENT_OnAfterDelete()
    {
    }

    _record *METHOD_Find(QString SearchFor, QString InTableDotField, QString ReturnFieldName)
    { 
      return 0;
    }

    _query *METHOD_Query(QString SQLStatement)
    { 
    #ifdef RUN
    #endif
      return 0;
    }

    t_long METHOD_Affected()
    { 
    #ifdef RUN
    #endif
      return 0;//r.numRowsAffected();
    }





// ################################################################################################
// ################################################################################################
// ################################################################################################


void EVENT_On2BeforeInsert()
{ 
#ifdef RUN
  if (!bTableView){
    t_boolean Cancel = false;
    EVENT_OnBeforeInsert(&Cancel); 
    if (&Cancel) return;
    METHOD_Insert();
    //EVENT_OnAfterInsert(); 
  }
#endif
}

void EVENT_On2BeforeUpdate()
{ 
#ifdef RUN
  if (!bTableView){
    t_boolean Cancel = false;
    EVENT_OnBeforeUpdate(&Cancel); 
    if (&Cancel) return;
    METHOD_Update();
    //EVENT_OnAfterUpdate(); 
  }
#endif
}

void EVENT_On2BeforeDelete()
{ 
#ifdef RUN
  if (!bTableView){
    t_boolean Cancel = false;
    EVENT_OnBeforeDelete(&Cancel); 
    if (&Cancel) return;
    METHOD_Delete();
    //EVENT_OnAfterDelete(); 
  }
#endif
}

      t_variant rd_Record(QSqlRecord & a, QString sFieldName)
      { 
      #ifdef RUN  
        int n = a.indexOf(sFieldName);
        if (n >= 0){
          QVariant v = a.value(n);
          t_variant vv;
          static QByteArray a;
          switch(v.type()){
            case QVariant::Bool: vv = v.toBool(); return vv;
            case QVariant::Date: 
              {
                QDate d = v.toDate(); 
                QString s = d.toString("yyyy-MM-dd");
                a = s.toAscii();
                vv = a.data();
                return vv;
              }
            case QVariant::Double: vv = v.toDouble(); return vv;
            case QVariant::UInt:
            case QVariant::ULongLong:
            case QVariant::LongLong:
            case QVariant::Int: vv = v.toInt(); return vv;
            case QVariant::String: 
              {
                QString s = v.toString();
                a = s.toAscii();
                vv = a.data();
                return vv;
              }
            case QVariant::Time: 
              {
                QTime t = v.toTime(); 
                QString s = t.toString("hh:mm:ss");
                a = s.toAscii();
                vv = a.data();
                return vv;
              }
          }

        }
      #endif
        return 0;
      }


void setSQL();

t_boolean METHOD_First(bool bInvokedByUser = true);
t_boolean METHOD_Next(bool bInvokedByUser = true);
t_boolean METHOD_Previous(bool bInvokedByUser = true);
t_boolean METHOD_Last(bool bInvokedByUser = true);
t_boolean METHOD_GoTo(t_long l, bool bInvokedByUser = true);

t_long METHOD_Len();


t_long METHOD_Pos();

t_boolean METHOD_Cmd(QString SQLStatement)
{ 
#ifdef RUN
  QSqlQuery rr(CurrentDatabase);
  return rr.exec(SQLStatement);
#endif
  return false;
}

    QString METHOD_LastSQLError()
    { 
    #ifdef RUN
      static QString s = "";
      s = q.lastError().text();
      return s;
    #endif
      return "";
    }

t_boolean METHOD_Requery();



    t_variant METHOD_Record(QString sFieldName);

// ################################################################################################
// ################################################################################################
// ################################################################################################



    void METHOD_SetRecord(QString FieldName, t_variant Value);


t_boolean stopByQuestion(bool bQuestion = true);
t_boolean updateFromControls();

t_boolean METHOD_IsDirty();

t_boolean METHOD_Insert();

t_boolean METHOD_Update();

t_boolean METHOD_Delete();

t_boolean METHOD_AddNew();


t_boolean METHOD_Cut();
t_boolean METHOD_Copy();
t_boolean METHOD_Paste();

void METHOD_ClearFilter();
void METHOD_AddFilter(QString s, bool bAddFilter = true);
void METHOD_SetFilter(QString s);
void METHOD_SortAsc(QString s);
void METHOD_SortDesc(QString s);



void setSQL2(QSqlRecord a);

QString getSQLTableName();
QString getSQLFilter();
QStringList getSQLSort();
QStringList getSQLFields();

void EVENT_On2BeforeInsert(QSqlRecord & record)
{ 
#ifdef RUN
  if (!bTableView){
    if (GETPROPERTY_SQLInsert()){
      setSQL2(sqlm.record());
      t_boolean Cancel = false;
      EVENT_OnBeforeInsert(&Cancel); 
      if (&Cancel) return;
      //METHOD_Insert();
      //EVENT_OnAfterInsert(); 
    }
  }
#endif
}

void EVENT_On2BeforeUpdate(int row, QSqlRecord & record)
{ 
#ifdef RUN
  if (!bTableView){
    if (GETPROPERTY_SQLUpdate()){
      setSQL2(sqlm.record());
      t_boolean Cancel = false;
      EVENT_OnBeforeUpdate(&Cancel); 
      if (&Cancel) return;
      //METHOD_Update();
      //EVENT_OnAfterUpdate(); 
    }
  }
#endif
}

void EVENT_On2BeforeDelete(int row)
{ 
#ifdef RUN
  if (!bTableView){
    if (GETPROPERTY_SQLDelete()){
      setSQL2(sqlm.record());
      t_boolean Cancel = false;
      EVENT_OnBeforeDelete(&Cancel); 
      if (&Cancel) return;
      //METHOD_Delete();
      //EVENT_OnAfterDelete(); 
    }
  }
#endif
}

void setDirty(bool bDirty);
void setAddNew(bool bAddNew);
void addProtocol(QString s);
void addLog(QString s);

bool bDirty;
bool bAddNew;



virtual void EVENT_OnDockMove()
{
}

virtual void EVENT_OnDockShow()
{
}

virtual void EVENT_OnDockHide()
{
}

virtual void EVENT_OnDockFloating()
{
}

virtual void EVENT_OnDockNotFloating()
{
}

t_boolean METHOD_DockIsLeft()
{
  return false;
}

t_boolean METHOD_DockIsRight()
{
  return false;
}

t_boolean METHOD_DockIsTop()
{
  return false;
}

t_boolean METHOD_DockIsBottom()
{
  return false;
}

void METHOD_DockSetLeft()
{
  if (dock == 0) return;

  forms_mainwindow->removeDockWidget(dock);
  forms_mainwindow->addDockWidget(Qt::LeftDockWidgetArea, dock);
}

void METHOD_DockSetRight()
{
}

void METHOD_DockSetTop()
{
}

void METHOD_DockSetBottom()
{
}

void METHOD_DockTabify(QString FormName);


void METHOD_DockSplit(QString FormName, QString Direction);


void METHOD_DockSetFloating(t_boolean YesNo)
{
  if (dock == 0) return;
  dock->setFloating(YesNo);
}

t_boolean METHOD_DockIsFloating()
{
  if (dock == 0) return false;
  return dock->isFloating();
}

void SETPROPERTY_DockSplit(QString FormName)
{
}

QString GETPROPERTY_DockSplit()
{
  return "";
}

_control *METHOD_ControlFocus()
{
  QWidget *w = focusWidget();

  if (w){
    QString s = w->objectName();
    if (!s.isEmpty()) return METHOD_Control(s);
  }

  return 0;
}

_control *METHOD_ControlFocusNext()
{
  QWidget *w = focusWidget()->nextInFocusChain();

  if (w){
    QString s = w->objectName();
    if (!s.isEmpty()) return METHOD_Control(s);
  }

  return 0;
}

t_boolean METHOD_ControlSetFocusNext()
{  
  /*
  QWidget *w = focusWidget();
  if (w){
    return w->focusNextChild();
  }*/
  return focusNextChild();
}

t_boolean METHOD_ControlSetFocusPrevious()
{  
  /*
  QWidget *w = focusWidget();
  if (w){
    return w->focusNextChild();
  }*/
  return focusPreviousChild();
}

/*
t_boolean METHOD_IsShownCentered()
{
  return false;
}


t_boolean METHOD_IsOpen()
{
  return false;
}*/
/*

void METHOD_ShowCentered()
{
}*/

/*
void METHOD_OpenMaximized()
{
}

void METHOD_OpenMinimized()
{
}*/

_control *METHOD_EventSource()
{
  if (EventSource){
    QString s = EventSource->objectName();
    if (!s.isEmpty()) return METHOD_Control(s);
  }
  return 0;
}

/*
QString METHOD_FormState()
{
  return 0;
}*/

/*
void METHOD_OpenCenteredOnlyOnce()
{
}

void METHOD_OpenOnlyOnce()
{
}

void METHOD_OpenHiddenOnlyOnce()
{
}*/

/*
void SETPROPERTY_ResizableSmaller(t_boolean YesNo)
{
}

t_boolean GETPROPERTY_ResizableSmaller()
{
  return false;
}*/

/*
void SETPROPERTY_ResizableBigger(t_boolean YesNo)
{
}

t_boolean GETPROPERTY_ResizableBigger()
{
  return false;
}
*/

void SETPROPERTY_ShowMode(QString sShowMode, bool bInit = false);
QString GETPROPERTY_ShowMode();


void SETPROPERTY_FormFileName(QString FormName)
{
  setWindowTitle(FormName);
}

QString GETPROPERTY_FormFileName()
{
  return windowTitle();
}

void SETPROPERTY_FormModified(t_boolean YesNo)
{
  setWindowModified(YesNo);
}

t_boolean GETPROPERTY_FormModified()
{
  return isWindowModified();
}

/*
void SETPROPERTY_FormX(t_integer n)
{
}*/

t_integer GETPROPERTY_FormX()
{
  QWidget *w = parentWidget();
  if (w){
    //QMdiSubWindow *o = qobject_cast<QMdiSubWindow *>(w);
    //if (o){
      QRect r = w->layout()->contentsRect();      
      return w->x() + r.left();
    //}
  } else {
      QRect r = geometry();
      return r.left();
  }
  return x();
}

/*
void SETPROPERTY_FormY(t_integer n)
{
}*/

t_integer GETPROPERTY_FormY()
{
  QWidget *w = parentWidget();
  if (w){
    //QMdiSubWindow *o = qobject_cast<QMdiSubWindow *>(w);
    //if (o){
      QRect r = w->layout()->contentsRect();      
      return w->y() + r.top();
   // }
  } else {
      QRect r = geometry();
      return r.top();
  }
}

/*
void SETPROPERTY_FormWidth(t_integer n)
{
}
*/

t_integer GETPROPERTY_FormWidth()
{
  QWidget *w = parentWidget();
  if (w){
      QRect r = w->frameGeometry();
      return r.width();

      //QRect r = w->layout()->contentsRect();      
      //return w->width() + r.left() * 2;

  //  QMdiSubWindow *o = qobject_cast<QMdiSubWindow *>(w);
  //  if (o) return o->width();
  } else {
      QRect r = frameGeometry();
      return r.width();
  }
}

/*
void SETPROPERTY_FormHeight(t_integer n)
{
}*/

t_integer GETPROPERTY_FormHeight()
{
  QWidget *w = parentWidget();
  if (w){
      QRect r = w->frameGeometry();
      return r.height();
/*
      QRect r = w->layout()->contentsRect();    
      int t = r.top();
      int b = r.bottom();
      int h = r.height();

      return w->height() + r.top() + r.height() - r.bottom();
//    QMdiSubWindow *o = qobject_cast<QMdiSubWindow *>(w);*/
  //  if (o) return o->height();
 
  } else {
      QRect r = frameGeometry();
      return r.height();
  }
}
                 

/*
t_variant METHOD_Record(QString FieldName)
{ 
  return t_variant(false);
}*/


/*
t_variant METHOD_Record(t_string s)
{ 
  return 0;
}*/



//QSqlQuery q;



/*
_query *METHOD_Query(t_string SQLStatement)
{ 
  return 0;
}



_record *METHOD_Find(t_string SearchFor, t_string InTableDotField, t_string ReturnFieldName)
{ 
  return 0;
}*/




//#ifdef RUN
/*

*** binding class definition:

t_string  PROPERTY_Name
t_integer PROPERTY_X
t_integer PROPERTY_Y
t_integer PROPERTY_Width
t_integer PROPERTY_Height
t_string  PROPERTY_Tag
t_string  PROPERTY_DataSource
t_string  PROPERTY_Caption

void EVENT_Open()
void EVENT_Activate()
void EVENT_Deactivate()
void EVENT_Close()

void EVENT_Click(_mouse *Mouse)
void EVENT_DblClick(_mouse *Mouse)
void EVENT_MouseDown(_mouse *Mouse)
void EVENT_MouseUp(_mouse *Mouse)
void EVENT_MouseMove(_mouse *Mouse)

void EVENT_GotFocus()
void EVENT_LostFocus()
void EVENT_Enter()
void EVENT_Exit()

void EVENT_KeyDown(_key *Key)
void EVENT_KeyUp(_key *Key)
void EVENT_KeyPress(_key *Key)

void EVENT_Current()
void EVENT_AfterUpdate()
void EVENT_BeforeUpdate(t_boolean Cancel)

void METHOD_Open()
void METHOD_Activate()
void METHOD_Deactivate()
void METHOD_Close()

void METHOD_Load(const char* p)
*/
/*


void METHOD_AddControl(_control* p)

_form *GETOBJECT_Forms(const char* p)
_forms *GETOBJECT_Forms()

_control *GETOBJECT_Controls(const char* p)
_controls *GETOBJECT_Controls()

void EVENT_Resize()

void METHOD_Open(mit optinoal cstring besser als load)

***

*/

/**
[KBASIC]
NAME: FORM
PRINTNAME: Form
TASK: A form is a window with controls
DESC: 
In your KBasic-application forms are not only masks for inputting and changing data, but they are the graphical interface of your application. In the eyes of the beholder, they are the application! By creating  your application using forms, you control the program flow with events, which are raised in the forms.

Central meaning of forms:
Each form in a KBasic application has got a form module with event procedures. Those event procedures react on events raised in the form. Additionally, every module can contain other non-event procedures.

A form module is part of every form, when you copy a form, its form module is automatically copied, too. If you delete a form, its form module is deleted as well. KBasic creates a form module automatically. So you need only to write the event procedures and other procedures.

Forms hold your KBasic program together!

DESCEND: 
PROPERTY1: Name As String PROPERTYDESC:' is the name
PROPERTY2: Tag As String PROPERTYDESC:' it is your idea what you use it for<br><br>
PROPERTY3: X As Integer PROPERTYDESC:' the X-Coordinate 
PROPERTY4: Y As Integer PROPERTYDESC:' the Y-Coordinate
PROPERTY5: Width As Integer PROPERTYDESC:' the width 
PROPERTY6: Height As Integer PROPERTYDESC:' the height<br><br>
PROPERTY7: DataSource As String PROPERTYDESC:' holds the SQL query or query for the form's recordset<br><br>
PROPERTY8: BackImage As String PROPERTYDESC:' the background image<br><br>
PROPERTY9: AcceptDrops As Boolean PROPERTYDESC:' if the control can do drag and drop<br><br>
PROPERTY10: Transparent As Boolean PROPERTYDESC:' if the control has transparent background<br><br>
EVENT1: Sub Open() EVENTDESC:' when the form opens
EVENT2: Sub Close() EVENTDESC:' closing<br><br>
EVENT3: Sub Resize() EVENTDESC:'<br><br>
EVENT4: Sub Activate() EVENTDESC:' when the form is about to be shown
EVENT5: Sub Deactivate() EVENTDESC:' when the form is about to be hidden<br><br>
EVENT6: Sub Current() EVENTDESC:' when the form's recordset is updated and shown
EVENT7: Sub AfterUpdate() EVENTDESC:' after the controls changed
EVENT8: Sub BeforeUpdate(&Cancel As Boolean) EVENTDESC:' before the controls changes<br><br>
EVENT9: Sub DragEnter(m As Mouse) EVENTDESC:' is called when a drag is in progress and the mouse enters the control' <br><br>
EVENT10: Sub DragMove(m As Mouse) EVENTDESC:' is called when a drag is in progress and the mouse enters the control, and whenever it moves within the control <br><br>
EVENT11: Sub DragLeave(m As Mouse) EVENTDESC:' is called when a drag is in progress and the mouse leaves the control <br><br>
EVENT12: Sub Drop(m As Mouse) EVENTDESC:' is called when the drag is dropped on this control <br><br>
EVENT13: Sub Menu(m As Mouse) EVENTDESC:' is called when a context menu is requested <br><br>
EVENT14: Sub MouseWheel(m As Mouse) EVENTDESC:' receive wheel events <br><br>
EVENT15: Sub Show() EVENTDESC:' when the control is shown<br><br>
EVENT16: Sub Hide() EVENTDESC:' when the control is set invisible <br><br>
EVENT17: Sub Refresh() EVENTDESC:' when the control is painted on the screen <br><br>
EVENT18: Sub Move(X As Integer, Y As Integer) EVENTDESC:' when the control is moved <br><br>
EVENT19: Sub Resize(Width As Integer, Height As Integer) EVENTDESC:' when the control is resized <br><br>
METHOD1: Sub Open() METHODDESC:'
METHOD2: Sub Close() METHODDESC:'
METHOD3: Sub Resize() METHODDESC:'
METHOD4: Sub Activate() METHODDESC:'
METHOD5: Sub Deactivate() METHODDESC:'
METHOD6: Sub Load(Name As String) METHODDESC:'
METHOD7: Function Control(Name As String) As Control METHODDESC:'
EXAMPLES: form.kbasic
CATEGORY: CLASS, FORM, CONTROL, OBJECT, GUI, KBASIC
SEEALSO: APPLICATION
LOG: 04-02-2004 implemented
TIP:
*/

//#include "_control1_binding.h"

//#include "__property_open.h"
//#include "__property_resize.h"
//#include "__property_close.h"
//#include "__property_current.h"
//#include "__property_afterupdate.h"
//#include "__property_beforeupdate.h"


// KBBINDINGEVENTS
/*virtual void EVENT_Open()
{
}*/
/*
virtual void EVENT_Resize()
{
}
*/
/*
virtual void EVENT_Activate()
{
}

virtual void EVENT_Deactivate()
{
}

virtual void EVENT_Close()
{
}*/
/*
void EVENT_Click(_mouse *Mouse)
{
}

void EVENT_DblClick(_mouse *Mouse)
{
}

void EVENT_MouseDown(_mouse *Mouse)
{
}

void EVENT_MouseUp(_mouse *Mouse)
{
}

void EVENT_MouseMove(_mouse *Mouse)
{
}

void EVENT_GotFocus()
{
}

void EVENT_LostFocus()
{
}

void EVENT_Enter()
{
}

void EVENT_Exit()
{
}

void EVENT_KeyDown(_key *Key)
{
}

void EVENT_KeyUp(_key *Key)
{
}

void EVENT_KeyPress(_key *Key)
{
}
*/
/*
virtual void EVENT_Current()
{
//***  my_mainwindow->processGUI(100);
}
*/
/*
void EVENT_AfterUpdate()
{
}

void EVENT_BeforeUpdate(&Cancel As Boolean)
{
}
*/

// KBBINDINGMETHODS
/*
void METHOD_Move(int X, int Y)
{
  SETPROPERTY_X(X);
  SETPROPERTY_Y(Y);
}
*/

/*
void METHOD_Open()
{
  setFormNormalMode();
  //QMainWindow::move(10, 10);
  //SETPROPERTY_Visible(true);
  //SETPROPERTY_X(GETPROPERTY_X());
  //SETPROPERTY_Y(GETPROPERTY_Y());

  EVENT_Open();
  
  METHOD_Activate();

}

void METHOD_Close()
{
  METHOD_Deactivate();
  close();

//***  my_mainwindow->processGUI(100);
}
*/
/*
void METHOD_Activate()
{
  show();
  setFocus();
//***  setActiveWindow();
  setFocus();
  //bActivated = true;

//***  my_mainwindow->processGUI(100);

//***  if (my_mainwindow) my_mainwindow->updateAll();

  QWidget *c;
  if (firstControl(&c)){
     do {
       if (controlType(c) == t_timer){
         _timer *t = (_timer *) c;

         if (t->GETPROPERTY_Enabled()) t->startTimer(t->GETPROPERTY_Interval());
       }

     } while (nextControl(&c));
  }
}

void METHOD_Deactivate()
{
  hide();

  //bActivated = false;

  QWidget *c;
  if (firstControl(&c)){
     do {
       if (controlType(c) == t_timer){
         _timer *t = (_timer *) c;
//***         t->killTimers();
       }

     } while (nextControl(&c));
  }

//***  my_mainwindow->processGUI(100);
}

void METHOD_Load(const char *ac)
{
//  sName = ac;
  load(ac);  
  
}

t_object METHOD_Control(QString s)
{
  return getControl(s);
}
*/
//#endif
/*
First

Function First() As Boolean
Next

Function Next() As Boolean
Previous

Function Previous() As Boolean
Last

Function Last() As Boolean
GoTo

Function GoTo(Position As Integer) As Boolean
Insert

Function Insert() As Boolean
Update (SQL)

Function Update() As Boolean
Delete

Function Delete() As Boolean
AddNew

Function AddNew() As Boolean
Record

Function Record(FieldName As String) As AnyType
Len

Function Len() As Long
Pos

Function Pos() As Long
IsDirty

Function IsDirty() As Boolean
Affected

Function Affected() As Long
Query

Function Query(SQLStatement As String) As Query
LastSQLError

Function LastSQLError() As Query
Find

Function Find(SearchFor As String, InTableDotField As String, ReturnFieldName As String) As Record

Example

Dim r As Record = Find("id", "mytable.id", "name")

Requery

Sub Requery() 
*/




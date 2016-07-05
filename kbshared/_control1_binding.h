
// events and properties

//extern void MYLOG(QString s);


#ifdef IDE
class _control;
class _strings;
#endif

public:
void METHOD_Move(t_integer X, t_integer Y)
{
#ifdef _FORM
  QWidget::move(X, Y);
#else
  move(X, Y);
#endif
}

void METHOD_Resize(t_integer Width, t_integer Height)
{
#ifdef _FORM
  _property::SETPROPERTY_Width(Width); // must be before calling resize
  _property::SETPROPERTY_Height(Height); // must be before calling resize
#endif
  resize(Width, Height);
}

void METHOD_Show()
{
#ifdef _FORM
  if (bOpened){ 
    if (dock) dock->show(); 
     if (parentWidget() && qobject_cast<QMdiSubWindow *>(parentWidget())){
       parentWidget()->show(); 
     }
    show(); 
  }
#else
#ifdef SUPERCLASS 
  show();
#endif
#endif
}

void METHOD_Hide()
{
#ifdef _FORM
  if (bOpened){ 
    if (dock) dock->hide(); 
     if (parentWidget() && qobject_cast<QMdiSubWindow *>(parentWidget())){
       parentWidget()->hide(); 
     }
    hide(); 
  }
#else
#ifdef SUPERCLASS 
  hide();
#endif
#endif
}

void METHOD_RepaintAlways()
{
#ifdef _FORM
  main->repaint();
 // MYLOG("1METHOD_RepaintAlways");
  //QMessageBox::information(0, "1", "METHOD_RepaintAlways");
#else
  //QMessageBox::information(0, "2", "METHOD_RepaintAlways");
 // MYLOG("2METHOD_RepaintAlways");
#ifdef SUPERCLASS 
  repaint();
#endif
#endif
}

void METHOD_Repaint()
{
#ifdef _FORM
  main->update();
//  MYLOG("1METHOD_Repaint");
#else
#ifdef SUPERCLASS 
  //QMessageBox::information(0, "2", "METHOD_Repaint");
  update();
 // MYLOG("2METHOD_Repaint");
#endif
#endif
}

void METHOD_Raise()
{
#ifdef SUPERCLASS 
  raise();
#endif
}

void METHOD_Lower()
{
#ifdef SUPERCLASS 
  lower();
#endif
}

void METHOD_Close()
{
#ifdef _FORM
  t_boolean b = true;
  EVENT_OnClose(&b);
  if (b) close();
#else
  delete ((SUPERCLASS *) this);
#endif
}

#ifdef _FORM
  void METHOD_Open(bool bHidden = false, bool bRequeryOnly = false, 
    bool bFullScreen = false, bool bCentered = false, 
    int X = -1, int Y = -1, int Width = -1, int Height = -1
    , bool bOpenMaximized = false, bool bOpenMinimized = false, bool bOpenCenteredOnlyOnce = false
    , bool bOpenOnlyOnce = false, bool bOpenHiddenOnlyOnce = false
    );


#else
  void METHOD_Open()
  {
  #ifndef _CONTROL
  #ifdef SUPERCLASS 
    EVENT_OnOpen();
    show();
  #endif
  #endif
  }
#endif

#ifdef _FORM
  void METHOD_OpenHidden();
#else
  void METHOD_OpenHidden()
  {
  #ifndef _CONTROL
  #ifdef SUPERCLASS 
    EVENT_OnOpen();
  #endif
  #endif
  }
#endif

#ifdef _FORM
  void METHOD_OpenMaximized();
  void METHOD_OpenMinimized();
  void METHOD_OpenCenteredOnlyOnce();
  void METHOD_OpenOnlyOnce();
  void METHOD_OpenHiddenOnlyOnce();

#endif

#ifdef _FORM
  void METHOD_Open(int X, int Y);
#else
  void METHOD_Open(int X, int Y)
  {
  #ifndef _CONTROL
  #ifdef SUPERCLASS 
    EVENT_OnOpen();
  #endif
  #endif
  }
#endif

#ifdef _FORM
  void METHOD_Open(int X, int Y, int Width, int Height);
#else
  void METHOD_Open(int X, int Y, int Width, int Height)
  {
  #ifndef _CONTROL
  #ifdef SUPERCLASS 
    EVENT_OnOpen();
  #endif
  #endif
  }
#endif

#ifdef _FORM
  void METHOD_OpenFullScreen();
#else
  void METHOD_OpenFullScreen()
  {
  #ifndef _CONTROL
  #ifdef SUPERCLASS 
    EVENT_OnOpen();
  #endif
  #endif
  }
#endif

  
#ifdef _FORM
  void METHOD_OpenCentered();
#else
  void METHOD_OpenCentered()
  {
  #ifndef _CONTROL
  #ifdef SUPERCLASS 
    EVENT_OnOpen();
  #endif
  #endif
  }
#endif

void METHOD_SetFocus()
{
#ifdef _FORM
  activateWindow();
#else
  setFocus();
#endif
}


// PROPERTY

#include "__property_name.h"
#include "__property_controltype.h"
#include "__property_group.h"
//#include "__property_layout.h"

#include "__property_drawonpaint.h"
#include "__property_mousetracking.h"
#include "__property_soundonevent.h"
#include "__property_cursoranimation.h"

#include "__property_palette.h"
#include "__property_mask.h"
#include "__property_background.h"
#include "__property_backgroundstyle.h"
#include "__property_minimumwidth.h"
#include "__property_minimumheight.h"
#include "__property_maximumwidth.h"
#include "__property_maximumheight.h"
#include "__property_headerheight.h"
#include "__property_footerheight.h"
#include "__property_borderleft.h"
#include "__property_borderright.h"
//#include "__property_tag.h"
#include "__property_dragdrop.h"
#include "__property_focus.h"
#include "__property_focuspolicy.h"
#include "__property_focusproxy.h"
#include "__property_focusorder.h"
#include "__property_cursor.h"
#include "__property_fontname.h"
#include "__property_fontsize.h"
#include "__property_fontitalic.h"
#include "__property_fontbold.h"
#include "__property_fontunderline.h"
#include "__property_fontcolor.h"
//#include "__property_tableview.h"
#include "__property_enabled.h"
#include "__property_visible.h"
#include "__property_parentform.h"
#include "__property_parentcontrol.h"
//#include "__property_boxindex.h"
//#include "__property_boxx.h"
//#include "__property_boxy.h"
//#include "__property_splitindex.h"
//#include "__property_tabindex.h"
#include "__property_scale.h"
#include "__property_statustip.h"
#include "__property_tooltip.h"
#include "__property_stylesheet.h"
#include "__property_whatsthis.h"
#include "__property_csv.h"

#include "__property_timerinterval.h"

#include "__property_opacity.h"

#include "__property_sql.h"

//#include "__property_sqlname.h"
//#include "__property_sqlrelation.h"
//#include "__property_tableviewcaption.h"
//#include "__property_tableviewsort.h"
//#include "__property_tableviewfilter.h"
//#include "__property_tableviewwidth.h"
//#include "__property_tableviewvisible.h"
//#include "__property_tablevieworder.h"





// KBBINDINGEVENTS

virtual void EVENT_OnOpen()
{
}

virtual void EVENT_OnClose(t_boolean *Cancel)
{
}

virtual bool EVENT_OnContextMenu(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY)
{
  return false;
}

virtual void EVENT_OnDragEnter(t_boolean *Cancel, t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_integer Width, t_integer Height, t_boolean Left, t_boolean Right, t_boolean Mid, t_boolean Shift, t_boolean Control, t_boolean Alt)
{
}

virtual void EVENT_OnDragExit()
{
}

virtual void EVENT_OnDragMove(t_boolean *Cancel, t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_integer Width, t_integer Height, t_boolean Left, t_boolean Right, t_boolean Mid, t_boolean Shift, t_boolean Control, t_boolean Alt)
{
}

virtual void EVENT_OnDrop(t_boolean *Cancel, QString MimeData, t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_boolean Left, t_boolean Right, t_boolean Mid, t_boolean Shift, t_boolean Control, t_boolean Alt)
{
}

virtual void EVENT_OnEnter()
{
}

virtual void EVENT_OnGotFocus()
{
}

virtual void EVENT_OnLostFocus()
{
}

virtual void EVENT_OnHide()
{
}

virtual void EVENT_OnKeyDown(t_integer Key, t_boolean Shift, t_boolean Control, t_boolean Alt)
{
}

virtual void EVENT_OnKeyUp(t_integer Key, t_boolean Shift, t_boolean Control, t_boolean Alt)
{
}

virtual void EVENT_OnKeyPress(t_integer Key, t_boolean Shift, t_boolean Control, t_boolean Alt)
{
}

virtual void EVENT_OnExit()
{
}

virtual void EVENT_OnDblClick(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_boolean Left, t_boolean Right, t_boolean Mid)
{
}

virtual void EVENT_OnClick(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_boolean Left, t_boolean Right, t_boolean Mid)
{
}

virtual void EVENT_OnMouseMove(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY)
{
}

virtual void EVENT_OnMouseDown(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_boolean Left, t_boolean Right, t_boolean Mid)
{
}

virtual void EVENT_OnMouseUp(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_boolean Left, t_boolean Right, t_boolean Mid)
{
}

virtual void EVENT_OnMove(t_integer X, t_integer Y, t_integer OldX, t_integer OldY)
{
}

virtual void EVENT_OnPaint(t_integer X, t_integer Y, t_integer Width, t_integer Height)
{
}

virtual void EVENT_OnResize(t_integer Width, t_integer Height, t_integer OldWidth, t_integer OldHeight)
{
}

virtual void EVENT_OnEnabled()
{
}

virtual void EVENT_OnDisabled()
{
}

virtual void EVENT_OnShow()
{
}

virtual void EVENT_OnMouseWheel(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY)
{
}

virtual void EVENT_OnTimer()
{
}

virtual void EVENT_OnPrint()
{
}

virtual void EVENT_OnSingleShot()
{
}


#ifdef RUN
void METHOD_DataRemove(QString Id)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(QVariant::Invalid));
}

void METHOD_DataRemoveAll()
{
  QList<QByteArray> l = dynamicPropertyNames();

  foreach(QByteArray a, l)
  {
    QString s = QString::fromUtf8(a);
    if (s.compare("__kb1979.ControlType.kb__", Qt::CaseSensitive) != 0){
      setProperty(a.data(), QVariant(QVariant::Invalid));
    }
  }

}

void METHOD_DataSetBoolean(QString Id, t_boolean Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(Value));
}

void METHOD_DataSetInteger(QString Id, t_integer Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(Value));
}

void METHOD_DataSetString(QString Id, QString Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(Value));
}

void METHOD_DataSetDouble(QString Id, t_double Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(Value));
}

void METHOD_DataSetLong(QString Id, t_long Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(Value));
}

void METHOD_DataSetDecimal(QString Id, t_currency Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(*Value.toQString()));
}

void METHOD_DataSetDateTime(QString Id, t_date Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(*Value.toQString()));
}

t_currency METHOD_DataDecimal(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()){
    QString s = v.toString();
    return t_currency(&s);
  }
  return t_currency();
}

t_date METHOD_DataDateTime(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()){
    QString s = v.toString();
    return t_date(&s);
  }
  return t_date();
}

t_long METHOD_DataLong(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()) return v.toLongLong();
  return 0;
}

t_boolean METHOD_DataBoolean(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()) return v.toBool();
  return 0;
}

t_integer METHOD_DataInteger(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()) return v.toInt();
  return 0;
}

QString METHOD_DataString(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()) return v.toString();
  return "";
}

t_double METHOD_DataDouble(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()) return v.toDouble();
  return 0;
}
#endif

void METHOD_ClearFocus()
{
  clearFocus();
}

void METHOD_ToggleVisible()
{
  setHidden(isVisible());
}

void METHOD_SingleShot(t_integer Milliseconds)
{
  nSingleShot = startTimer(Milliseconds);
}

void METHOD_StartTimer()
{
  if (nTimerId != 0) killTimer(nTimerId);
  int n = GETPROPERTY_TimerInterval();
  nTimerId = startTimer(n);
}

void METHOD_StopTimer()
{
  if (nTimerId != 0) killTimer(nTimerId);
}


t_integer METHOD_LocalX(t_integer GlobalX)
{
  return mapFromGlobal(QPoint(GlobalX, 0)).x() + x(); 
}

t_integer METHOD_LocalY(t_integer GlobalY)
{
  return mapFromGlobal(QPoint(0, GlobalY)).y() + y(); 
}

t_integer METHOD_GlobalX(t_integer LocalX)
{
  return mapToGlobal(QPoint(LocalX, 0)).x() - x(); 
}

t_integer METHOD_GlobalY(t_integer LocalY)
{
  return mapToGlobal(QPoint(0, LocalY)).y() - y(); 
}

t_boolean METHOD_UnderMouse()
{
  return underMouse();
}

int nSingleShot;
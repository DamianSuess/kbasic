
#ifdef IDE


t_properties *p2;
void showUpdatePropertyWindow(bool b = true);


t_properties p;
  
void updatePropertyWindow2(bool b = true, QString sProperty = "");
void updatePropertyWindow(bool b = true);




bool newEvent(QString s, QWidget *currentControlInFormClassSourcecode = 0);

// ***

virtual void controls_SETPROPERTY_Name(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Name(n);
        #include "_form_property_switch.h"       
        b = false;
      }
    } while (nextControl(&c));
  }
  
  if (b){
    SETPROPERTY_Name(n);
  }
}

void controls_SETPROPERTY_X(t_integer n)
{
  QWidget *c; 
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        int x = n;
        if (x < 0) x = 0;
        if (x + c->width() > XSCROLLBAR + width()){
          if (XScrollBar){
            if (x + c->width() > GETPROPERTY_ScrollWidth()){
              x = GETPROPERTY_ScrollWidth() - width() - c->width() + XSCROLLBAR;
            }
            if (XScrollBar) XScrollBar->setValue(XScrollBar->maximum());
          } else {
            x = XSCROLLBAR + width() - c->width();
          }
        } else {
     //     int k = GETPROPERTY_ScrollWidth() / XScrollBar->maximum();
          if (x < width() && XSCROLLBAR > width() - 50){
            if (XScrollBar) XScrollBar->setValue(0);
          }
            
        }

        my_move(c, x - XSCROLLBAR, c->y(), XSCROLLBAR, 0);


        b = false;

      }
    } while (nextControl(&c));

  }

  if (b){
    SETPROPERTY_X(n, false);
  }
}

void controls_SETPROPERTY_Y(t_integer n)
{
  QWidget *c; 
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        int y = n;
        if (y < 0) y = 0;
        if (y + c->height() > YSCROLLBAR + height()){
          if (YScrollBar){
            if (y + c->height() > GETPROPERTY_ScrollHeight()){
              y = GETPROPERTY_ScrollHeight() - height() - c->height() + YSCROLLBAR;
            }
            if (YScrollBar) YScrollBar->setValue(YScrollBar->maximum());
          } else {
            y = YSCROLLBAR + height() - c->height();
          }
        } else {
     
          if (y < height() && YSCROLLBAR > height() - 50){
            if (YScrollBar) YScrollBar->setValue(0);
          }
            
        }

        my_move(c, c->x(), y - YSCROLLBAR, 0, YSCROLLBAR);

        b = false;

      }
    } while (nextControl(&c));
    
  }

  if (b){
    SETPROPERTY_Y(n, false);
  }
}

void controls_SETPROPERTY_Width(t_integer n)
{
  QWidget *c; 
  bool b = true;

  if (firstControl(&c)){
    do {             

      if (c->acceptDrops()){ // missused as selected flag

        int w = n;
        if (w < 0) w = 0;
        if (c->x() + w > width()){
          w = width() - c->x();
        }          
        #define SWITCH SETPROPERTY_Width(w);
        #include "_form_property_switch.h"       
        b = false;

      }
    } while (nextControl(&c));

  }

  if (b){
    SETPROPERTY_Width(n);
  }
}

void controls_SETPROPERTY_Height(t_integer n)
{
  QWidget *c; 
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        int h = n;
        if (h < 0) h = 0;
        if (c->y() + h > height()){
          h = height() - c->y();
        }    

        #define SWITCH SETPROPERTY_Height(h);
        #include "_form_property_switch.h"       
        b = false;

      }
    } while (nextControl(&c));

  }

  if (b){
    SETPROPERTY_Height(n);
  }
}

virtual void controls_SETPROPERTY_Caption(QString &n)
{
  QWidget *c;
  bool b = true;

//  if (bInitControl)bModified = true;
  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Caption(n);
        #include "_form_property_switch.h"       
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Caption(n);
  }
}

void controls_SETPROPERTY_IntegerValue(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_IntegerValue(n);
        #include "_form_property_switch.h"       
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_IntegerValue(n);
  }
}

virtual void controls_SETPROPERTY_Enabled(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Enabled(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Enabled(n);
  }
}

void controls_SETPROPERTY_Flip(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Flip(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Flip(n);
  }
}

virtual void controls_SETPROPERTY_Checked(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Checked(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Checked(n);
  }
}

virtual void controls_SETPROPERTY_CheckableExclusive(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CheckableExclusive(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_CheckableExclusive(n);
  }
}

virtual void controls_SETPROPERTY_Tag(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Tag(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Tag(n);
  }
}

void controls_SETPROPERTY_Resizable(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Resizable(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Resizable(n);
  }
}


void controls_SETPROPERTY_ResizableSmaller(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ResizableSmaller(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ResizableSmaller(n);
  }
}

void controls_SETPROPERTY_ResizableBigger(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ResizableBigger(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ResizableBigger(n);
  }
}



virtual void controls_SETPROPERTY_Visible(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Visible(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Visible(n);
  }
}

void controls_SETPROPERTY_WordWrap(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_WordWrap(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_WordWrap(n);
  }
}

void controls_SETPROPERTY_ReadOnly(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ReadOnly(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ReadOnly(n);
  }
}

void controls_SETPROPERTY_Alignment(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Alignment(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Alignment(n);
  }
}


void controls_SETPROPERTY_EchoMode(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_EchoMode(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_EchoMode(n);
  }
}




void controls_SETPROPERTY_Orientation(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Orientation(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Orientation(n);
  }
}

void controls_SETPROPERTY_Feature(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Feature(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Feature(n);
  }
}

void controls_SETPROPERTY_Cursor(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Cursor(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Cursor(n);
  }
}

void controls_SETPROPERTY_SQL(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SQL(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SQL(n);
  }
}

void controls_SETPROPERTY_SQLName(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SQLName(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SQLName(n);
  }
}

void controls_SETPROPERTY_SQLRelation(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SQLRelation(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SQLRelation(n);
  }
}

void controls_SETPROPERTY_SQLInsert(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SQLInsert(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SQLInsert(n);
  }
}

void controls_SETPROPERTY_SQLUpdate(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SQLUpdate(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SQLUpdate(n);
  }
}

void controls_SETPROPERTY_SQLDelete(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SQLDelete(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SQLDelete(n);
  }
}


void controls_SETPROPERTY_TableViewCaption(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TableViewCaption(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TableViewCaption(n);
  }
}

void controls_SETPROPERTY_TableViewSort(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TableViewSort(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TableViewSort(n);
  }
}

void controls_SETPROPERTY_TableViewFilter(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TableViewFilter(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TableViewFilter(n);
  }
}

void controls_SETPROPERTY_TableViewWidth(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TableViewWidth(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TableViewWidth(n);
  }
}

void controls_SETPROPERTY_TableViewVisible(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TableViewVisible(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TableViewVisible(n);
  }
}

void controls_SETPROPERTY_TableViewOrder(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TableViewOrder(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TableViewOrder(n);
  }
}

void controls_SETPROPERTY_DockTitleVisible(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_DockTitleVisible(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_DockTitleVisible(n);
  }
}

void controls_SETPROPERTY_DockOrder(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_DockOrder(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_DockOrder(n);
  }
}

void controls_SETPROPERTY_DockSplit(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_DockSplit(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_DockSplit(n);
  }
}

void controls_SETPROPERTY_ShowMode(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ShowMode(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ShowMode(n);
  }
}


void controls_SETPROPERTY_DockWidth(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_DockWidth(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_DockWidth(n);
  }
}

void controls_SETPROPERTY_DockHeight(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_DockHeight(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_DockHeight(n);
  }
}


void controls_SETPROPERTY_ScrollX(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ScrollX(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ScrollX(n);
    if (XScrollBar) XScrollBar->setValue(n);
  }
}

void controls_SETPROPERTY_ScrollY(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ScrollY(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ScrollY(n);
    if (YScrollBar) YScrollBar->setValue(n);
  }
}

void controls_SETPROPERTY_ScrollWidth(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ScrollWidth(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ScrollWidth(n);
  }
}

void controls_SETPROPERTY_ScrollHeight(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ScrollHeight(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ScrollHeight(n);
  }
}

void controls_SETPROPERTY_MultiPageHeight(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MultiPageHeight(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MultiPageHeight(n);
  }
}


void controls_SETPROPERTY_MultiPageBorderTop(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MultiPageBorderTop(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MultiPageBorderTop(n);
  }
}

void controls_SETPROPERTY_MultiPageBorderBottom(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MultiPageBorderBottom(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MultiPageBorderBottom(n);
  }
}

void controls_SETPROPERTY_MultiPageBorderLeft(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MultiPageBorderLeft(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MultiPageBorderLeft(n);
  }
}

void controls_SETPROPERTY_MultiPageBorderRight(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MultiPageBorderRight(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MultiPageBorderRight(n);
  }
}

void controls_SETPROPERTY_BorderTop(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BorderTop(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_BorderTop(n);
  }
}

void controls_SETPROPERTY_BorderBottom(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BorderBottom(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_BorderBottom(n);
  }
}
// PROPERTY

void controls_SETPROPERTY_Prefix(QString n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Prefix(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Prefix(n);
  }
}

void controls_SETPROPERTY_Suffix(QString n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Suffix(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Suffix(n);
  }
}

void controls_SETPROPERTY_SingleStep(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SingleStep(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SingleStep(n);
  }
}

void controls_SETPROPERTY_PageStep(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_PageStep(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_PageStep(n);
  }
}

void controls_SETPROPERTY_TickInterval(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TickInterval(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TickInterval(n);
  }
}

void controls_SETPROPERTY_Tracking(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Tracking(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Tracking(n);
  }
}

void controls_SETPROPERTY_InvertedControls(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_InvertedControls(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_InvertedControls(n);
  }
}

void controls_SETPROPERTY_InvertedAppearance(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_InvertedAppearance(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_InvertedAppearance(n);
  }
}

void controls_SETPROPERTY_TickPosition(QString n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TickPosition(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TickPosition(n);
  }
}

void controls_SETPROPERTY_ViewMode(QString n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ViewMode(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ViewMode(n);
  }
}

void controls_SETPROPERTY_Description(QString n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Description(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Description(n);
  }
}

void controls_SETPROPERTY_Brightness(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Brightness(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}



void controls_SETPROPERTY_MoveOnMouseDrag(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MoveOnMouseDrag(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MoveOnMouseDrag(n);
  }
}
void controls_SETPROPERTY_MouseTracking(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MouseTracking(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MouseTracking(n);
  }
}

void controls_SETPROPERTY_DrawOnPaint(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_DrawOnPaint(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_DrawOnPaint(n);
  }
}

void controls_SETPROPERTY_ActionId(QString n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ActionId(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ActionId(n);
  }
}

void controls_SETPROPERTY_SoundOnEvent(QString n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SoundOnEvent(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SoundOnEvent(n);
  }
}

void controls_SETPROPERTY_CursorAnimation(QString n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CursorAnimation(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_CursorAnimation(n);
  }
}


void controls_SETPROPERTY_Contrast(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Contrast(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_Hue(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Hue(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_Saturation(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Saturation(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_ScaleMode(QString & n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ScaleMode(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_AspectRatio(QString & n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_AspectRatio(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_TransitionTime(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TransitionTime(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_RootIsDecorated(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_RootIsDecorated(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_Muted(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Muted(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_Volume(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Volume(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_PrefinishMark(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_PrefinishMark(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_Tick(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Tick(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
  //  SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_OnTick(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnTick(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_OnStateChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnStateChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_OnAboutToFinish(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnAboutToFinish(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_OnFinished(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnFinished(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_OnMutedChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnMutedChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_OnVolumeChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnVolumeChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_OnPlayingTitleChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnPlayingTitleChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_OnBufferStatus(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnBufferStatus(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_(n);
  }
}

void controls_SETPROPERTY_OnTotalTimeChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnTotalTimeChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_(n);
  }
}
void controls_SETPROPERTY_BorderLeft(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BorderLeft(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_BorderLeft(n);
  }
}

void controls_SETPROPERTY_BorderRight(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BorderRight(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_BorderRight(n);
  }
}

virtual void controls_SETPROPERTY_CommandColor(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CommandColor(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_SelectionMode(n);
  }
}
virtual void controls_SETPROPERTY_KeywordColor(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_KeywordColor(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_SelectionMode(n);
  }
}
virtual void controls_SETPROPERTY_CommentColor(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CommentColor(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_SelectionMode(n);
  }
}
virtual void controls_SETPROPERTY_Commands(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Commands(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_SelectionMode(n);
  }
}
virtual void controls_SETPROPERTY_Keywords(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Keywords(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_SelectionMode(n);
  }
}

virtual void controls_SETPROPERTY_Comment1Begin(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Comment1Begin(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_SelectionMode(n);
  }
}

virtual void controls_SETPROPERTY_Comment1End(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Comment1End(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_SelectionMode(n);
  }
}

virtual void controls_SETPROPERTY_Comment2Begin(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Comment2Begin(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_SelectionMode(n);
  }
}

/*
virtual void controls_SETPROPERTY_Comment2End(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Comment2End(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_SelectionMode(n);
  }
}
*/

virtual void controls_SETPROPERTY_ContextMenu(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ContextMenu(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    //SETPROPERTY_ContextMenu(n);
  }
}

virtual void controls_SETPROPERTY_Dock(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Dock(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Dock(n);
  }
}

virtual void controls_SETPROPERTY_SelectionMode(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SelectionMode(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SelectionMode(n);
  }
}

virtual void controls_SETPROPERTY_OnPrint(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnPrint(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnPrint(n);
  }
}

virtual void controls_SETPROPERTY_AlternatingRowColors(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_AlternatingRowColors(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_AlternatingRowColors(n);
  }
}

virtual void controls_SETPROPERTY_OnCurrentItemChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnCurrentItemChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnCurrentItemChanged(n);
  }
}

virtual void controls_SETPROPERTY_OnItemActivated(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnItemActivated(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnItemActivated(n);
  }
}

virtual void controls_SETPROPERTY_OnItemChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnItemChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnItemChanged(n);
  }
}

virtual void controls_SETPROPERTY_OnItemClicked(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnItemClicked(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnItemClicked(n);
  }
}

virtual void controls_SETPROPERTY_OnItemCollapsed(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnItemCollapsed(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnItemCollapsed(n);
  }
}

virtual void controls_SETPROPERTY_OnItemDoubleClicked(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnItemDoubleClicked(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnItemDoubleClicked(n);
  }
}

virtual void controls_SETPROPERTY_OnItemEntered(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnItemEntered(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnItemEntered(n);
  }
}

virtual void controls_SETPROPERTY_OnItemExpanded(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnItemExpanded(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnItemExpanded(n);
  }
}

virtual void controls_SETPROPERTY_OnItemPressed(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnItemPressed(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnItemPressed(n);
  }
}

virtual void controls_SETPROPERTY_OnItemSelectionChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnItemSelectionChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnItemSelectionChanged(n);
  }
}


virtual void controls_SETPROPERTY_OnDockMove(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDockMove(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDockMove(n);
  }
}

virtual void controls_SETPROPERTY_OnDockShow(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDockShow(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDockShow(n);
  }
}

virtual void controls_SETPROPERTY_OnDockHide(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDockHide(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDockHide(n);
  }
}

virtual void controls_SETPROPERTY_OnDockFloating(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDockFloating(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDockFloating(n);
  }
}


virtual void controls_SETPROPERTY_OnDockNotFloating(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDockNotFloating(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDockNotFloating(n);
  }
}

virtual void controls_SETPROPERTY_Pages(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Pages(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Pages(n);
  }
}

virtual void controls_SETPROPERTY_ParentForm(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ParentForm(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ParentForm(n);
  }
}

virtual void controls_SETPROPERTY_ParentControl(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ParentControl(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ParentControl(n);
  }
}

virtual void controls_SETPROPERTY_TabIndex(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TabIndex(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TabIndex(n);
  }
}

virtual void controls_SETPROPERTY_ParentIndex(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ParentIndex(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ParentIndex(n);
  }
}

void controls_SETPROPERTY_StringValue(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_StringValue(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_StringValue(n);
  }
}

void controls_SETPROPERTY_InputMask(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_InputMask(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_InputMask(n);
  }
}

void controls_SETPROPERTY_Mask(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Mask(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Mask(n);
  }
}

void controls_SETPROPERTY_OpenAtStartup(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OpenAtStartup(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OpenAtStartup(n);
  }
}

void controls_SETPROPERTY_EventOnOpen(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_EventOnOpen(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_EventOnOpen(n);
  }
}


void controls_SETPROPERTY_AcceptRichText(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_AcceptRichText(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_AcceptRichText(n);
  }
}


void controls_SETPROPERTY_AutoDefault(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_AutoDefault(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_AutoDefault(n);
  }
}


void controls_SETPROPERTY_Default(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Default(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Default(n);
  }
}


void controls_SETPROPERTY_Checkable(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Checkable(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Checkable(n);
  }
}




virtual void controls_SETPROPERTY_Separator(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Separator(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Separator(n);
  }
}

void controls_SETPROPERTY_EnterImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_EnterImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_EnterImage(n);
  }
}

void controls_SETPROPERTY_ExitImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ExitImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ExitImage(n);
  }
}

void controls_SETPROPERTY_DisabledImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_DisabledImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_DisabledImage(n);
  }
}

void controls_SETPROPERTY_CheckEnterImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CheckEnterImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_CheckEnterImage(n);
  }
}

void controls_SETPROPERTY_CheckExitImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CheckExitImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_CheckExitImage(n);
  }
}

void controls_SETPROPERTY_CheckDisabledImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CheckDisabledImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_CheckDisabledImage(n);
  }
}

void controls_SETPROPERTY_EnterSound(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_EnterSound(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_EnterSound(n);
  }
}

void controls_SETPROPERTY_ExitSound(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ExitSound(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ExitSound(n);
  }
}

void controls_SETPROPERTY_Menu(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Menu(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Menu(n);
  }
}

void controls_SETPROPERTY_Interval(t_integer n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Interval(n);
        #include "_form_property_switch.h"       
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Interval(n);
  }
}

void controls_SETPROPERTY_BooleanValue(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BooleanValue(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_BooleanValue(n);
  }
}

// EVENT
/*
virtual void controls_SETPROPERTY_OnCursorPositionChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnCursorPositionChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnCursorPositionChanged(n);
  }
}
*/
virtual void controls_SETPROPERTY_OnEditingFinished(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnEditingFinished(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnEditingFinished(n);
  }
}

virtual void controls_SETPROPERTY_OnReturnPressed(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnReturnPressed(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnReturnPressed(n);
  }
}

virtual void controls_SETPROPERTY_OnSelectionChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnSelectionChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnSelectionChanged(n);
  }
}

virtual void controls_SETPROPERTY_OnTextChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnTextChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnTextChanged(n);
  }
}

virtual void controls_SETPROPERTY_OnTextEdited(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnTextEdited(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnTextEdited(n);
  }
}

virtual void controls_SETPROPERTY_OnPage(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnPage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnPage(n);
  }
}


virtual void controls_SETPROPERTY_OnLinkHovered(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnLinkHovered(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnLinkHovered(n);
  }
}

virtual void controls_SETPROPERTY_OnLoadFinished(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnLoadFinished(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnLoadFinished(n);
  }
}


virtual void controls_SETPROPERTY_OnLoadProgress(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnLoadProgress(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnLoadProgress(n);
  }
}

virtual void controls_SETPROPERTY_OnLoadStarted(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnLoadStarted(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnLoadStarted(n);
  }
}

virtual void controls_SETPROPERTY_OnWindowCloseRequested(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnWindowCloseRequested(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnWindowCloseRequested(n);
  }
}

virtual void controls_SETPROPERTY_OnTimer(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnTimer(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnTimer(n);
  }
}

virtual void controls_SETPROPERTY_OnSingleShot(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnSingleShot(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnSingleShot(n);
  }
}

virtual void controls_SETPROPERTY_OnQuery(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnQuery(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnQuery(n);
  }
}

virtual void controls_SETPROPERTY_OnAddNew(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnAddNew(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnAddNew(n);
  }
}

virtual void controls_SETPROPERTY_OnDirty(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDirty(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDirty(n);
  }
}

virtual void controls_SETPROPERTY_OnMove(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnMove(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnMove(n);
  }
}

virtual void controls_SETPROPERTY_OnHide(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnHide(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnHide(n);
  }
}

virtual void controls_SETPROPERTY_OnShow(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnShow(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnShow(n);
  }
}

virtual void controls_SETPROPERTY_OnEnabled(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnEnabled(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnEnabled(n);
  }
}

virtual void controls_SETPROPERTY_OnDisabled(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDisabled(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDisabled(n);
  }
}

virtual void controls_SETPROPERTY_OnContextMenu(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnContextMenu(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnContextMenu(n);
  }
}

virtual void controls_SETPROPERTY_OnScroll(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnScroll(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnScroll(n);
  }
}


virtual void controls_SETPROPERTY_OnMultiPageShow(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnMultiPageShow(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnMultiPageShow(n);
  }
}


virtual void controls_SETPROPERTY_OnMouseWheel(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnMouseWheel(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnMouseWheel(n);
  }
}


virtual void controls_SETPROPERTY_OnDrop(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDrop(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDrop(n);
  }
}

virtual void controls_SETPROPERTY_OnDragMove(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDragMove(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDragMove(n);
  }
}

virtual void controls_SETPROPERTY_OnDragEnter(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDragEnter(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDragEnter(n);
  }
}

virtual void controls_SETPROPERTY_OnClick(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnClick(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnClick(n);
  }
}

virtual void controls_SETPROPERTY_OnDblClick(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDblClick(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDblClick(n);
  }
}

virtual void controls_SETPROPERTY_OnMouseDown(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnMouseDown(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnMouseDown(n);
  }
}

virtual void controls_SETPROPERTY_OnMouseUp(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnMouseUp(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnMouseUp(n);
  }
}

virtual void controls_SETPROPERTY_OnMouseMove(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnMouseMove(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnMouseMove(n);
  }
}

virtual void controls_SETPROPERTY_OnGotFocus(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnGotFocus(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnGotFocus(n);
  }
}

virtual void controls_SETPROPERTY_OnLostFocus(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnLostFocus(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnLostFocus(n);
  }
}

virtual void controls_SETPROPERTY_OnEnter(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnEnter(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnEnter(n);
  }
}

virtual void controls_SETPROPERTY_OnExit(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnExit(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnExit(n);
  }
}

virtual void controls_SETPROPERTY_OnKeyDown(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnKeyDown(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnKeyDown(n);
  }
}

virtual void controls_SETPROPERTY_OnKeyUp(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnKeyUp(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnKeyUp(n);
  }
}

virtual void controls_SETPROPERTY_OnKeyPress(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnKeyPress(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnKeyPress(n);
  }
}

virtual void controls_SETPROPERTY_OnBeforeUpdate(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnBeforeUpdate(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnBeforeUpdate(n);
  }
}

virtual void controls_SETPROPERTY_OnOpen(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnOpen(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnOpen(n);
  }
}

virtual void controls_SETPROPERTY_OnResize(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnResize(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnResize(n);
  }
}

virtual void controls_SETPROPERTY_OnClose(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnClose(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnClose(n);
  }
}


virtual void controls_SETPROPERTY_Group(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Group(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Group(n);
  }
}

virtual void controls_SETPROPERTY_Background(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Background(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Background(n);
  }
}

virtual void controls_SETPROPERTY_BackgroundStyle(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BackgroundStyle(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_BackgroundStyle(n);
  }
}

virtual void controls_SETPROPERTY_Palette(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Palette(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Palette(n);
  }
}

virtual void controls_SETPROPERTY_MinimumWidth(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MinimumWidth(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MinimumWidth(n);
  }
}

virtual void controls_SETPROPERTY_MinimumHeight(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MinimumHeight(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MinimumHeight(n);
  }
}

virtual void controls_SETPROPERTY_MaximumWidth(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MaximumWidth(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MaximumWidth(n);
  }
}

virtual void controls_SETPROPERTY_MaximumHeight(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MaximumHeight(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MaximumHeight(n);
  }
}

virtual void controls_SETPROPERTY_CSV(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CSV(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_CSV(n);
  }
}

virtual void controls_SETPROPERTY_TableView(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TableView(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TableView(n);
  }
}

virtual void controls_SETPROPERTY_BoxIndex(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BoxIndex(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_BoxIndex(n);
  }
}

virtual void controls_SETPROPERTY_BoxX(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BoxX(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_BoxX(n);
  }
}

virtual void controls_SETPROPERTY_BoxY(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BoxY(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_BoxY(n);
  }
}

virtual void controls_SETPROPERTY_SplitIndex(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SplitIndex(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SplitIndex(n);
  }
}

virtual void controls_SETPROPERTY_StopOnClose(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_StopOnClose(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_StopOnClose(n);
  }
}

virtual void controls_SETPROPERTY_Scale(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Scale(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Scale(n);
  }
}
/*
virtual void controls_SETPROPERTY_FormCentered(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FormCentered(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FormCentered(n);
  }
}

virtual void controls_SETPROPERTY_FormScaled(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FormScaled(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FormScaled(n);
  }
}
*/
virtual void controls_SETPROPERTY_DragDrop(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_DragDrop(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_DragDrop(n);
  }
}

virtual void controls_SETPROPERTY_FocusPolicy(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FocusPolicy(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FocusPolicy(n);
  }
}

virtual void controls_SETPROPERTY_FocusProxy(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FocusProxy(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FocusProxy(n);
  }
}

virtual void controls_SETPROPERTY_FocusOrder(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FocusOrder(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FocusOrder(n);
  }
  showFocusOrder(false); // update the shown focus order labels, if needed
}

virtual void controls_SETPROPERTY_FontName(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FontName(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FontName(n);
  }
}

virtual void controls_SETPROPERTY_FontSize(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FontSize(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FontSize(n);
  }
}

virtual void controls_SETPROPERTY_FontBold(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FontBold(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FontBold(n);
  }
}

virtual void controls_SETPROPERTY_FontItalic(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FontItalic(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FontItalic(n);
  }
}

virtual void controls_SETPROPERTY_FontUnderline(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FontUnderline(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FontUnderline(n);
  }
}

virtual void controls_SETPROPERTY_FontColor(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FontColor(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FontColor(n);
  }
}

virtual void controls_SETPROPERTY_StatusTip(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_StatusTip(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_StatusTip(n);
  }
}

virtual void controls_SETPROPERTY_ToolTip(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ToolTip(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ToolTip(n);
  }
}

virtual void controls_SETPROPERTY_StyleSheet(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_StyleSheet(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_StyleSheet(n);
  }
}

virtual void controls_SETPROPERTY_WhatsThis(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_WhatsThis(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_WhatsThis(n);
  }
}

virtual void controls_SETPROPERTY_Flag(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Flag(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Flag(n);
  }
}

virtual void controls_SETPROPERTY_Layout(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Layout(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Layout(n);
  }
}
  

virtual void controls_SETPROPERTY_PortName(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_PortName(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_PortName(n);
  }
}

virtual void controls_SETPROPERTY_BaudRate(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BaudRate(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_BaudRate(n);
  }
}

virtual void controls_SETPROPERTY_DataBits(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_DataBits(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_DataBits(n);
  }
}

virtual void controls_SETPROPERTY_FlowControl(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_FlowControl(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_FlowControl(n);
  }
}

virtual void controls_SETPROPERTY_Parity(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Parity(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Parity(n);
  }
}

virtual void controls_SETPROPERTY_StopBits(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_StopBits(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_StopBits(n);
  }
}

virtual void controls_SETPROPERTY_TimeOutMillisec(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TimeOutMillisec(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TimeOutMillisec(n);
  }
}

virtual void controls_SETPROPERTY_PollingInterval(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_PollingInterval(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_PollingInterval(n);
  }
}


virtual void controls_SETPROPERTY_SQLControls(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SQLControls(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_SQLControls(n);
  }
}


/*
virtual void controls_SETPROPERTY_IconCaption(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_IconCaption(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_IconCaption(n);
  }
}

*/
virtual void controls_SETPROPERTY_Modal(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Modal(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Modal(n);
  }
}

virtual void controls_SETPROPERTY_Opacity(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Opacity(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Opacity(n);
  }
}

virtual void controls_SETPROPERTY_TimerInterval(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_TimerInterval(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_TimerInterval(n);
  }
}

virtual void controls_SETPROPERTY_Shadow(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Shadow(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Shadow(n);
  }
}

virtual void controls_SETPROPERTY_Shape(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Shape(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Shape(n);
  }
}

virtual void controls_SETPROPERTY_OpenLinks(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OpenLinks(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OpenLinks(n);
  }
}

virtual void controls_SETPROPERTY_Icon(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Icon(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Icon(n);
  }
}

virtual void controls_SETPROPERTY_InputControl(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_InputControl(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_InputControl(n);
  }
}

virtual void controls_SETPROPERTY_Space(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Space(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Space(n);
  }
}

virtual void controls_SETPROPERTY_Border(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Border(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Border(n);
  }
}

virtual void controls_SETPROPERTY_Flat(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Flat(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Flat(n);
  }
}

virtual void controls_SETPROPERTY_Key(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Key(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Key(n);
  }
}

virtual void controls_SETPROPERTY_IntegerMaximum(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_IntegerMaximum(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_IntegerMaximum(n);
  }
}

virtual void controls_SETPROPERTY_IntegerMinimum(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_IntegerMinimum(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_IntegerMinimum(n);
  }
}

virtual void controls_SETPROPERTY_Completer(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Completer(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Completer(n);
  }
}

virtual void controls_SETPROPERTY_ValidatorDouble(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ValidatorDouble(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ValidatorDouble(n);
  }
}

virtual void controls_SETPROPERTY_ValidatorInteger(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ValidatorInteger(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ValidatorInteger(n);
  }
}

virtual void controls_SETPROPERTY_ValidatorRegEx(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ValidatorRegEx(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ValidatorRegEx(n);
  }
}

virtual void controls_SETPROPERTY_ValidatorRegEx2(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ValidatorRegEx2(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ValidatorRegEx2(n);
  }
}

virtual void controls_SETPROPERTY_DoubleEntry(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_DoubleEntry(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_DoubleEntry(n);
  }
}

virtual void controls_SETPROPERTY_InsertPolicy(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_InsertPolicy(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_InsertPolicy(n);
  }
}

virtual void controls_SETPROPERTY_Editable(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Editable(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Editable(n);
  }
}

virtual void controls_SETPROPERTY_MaximumVisible(t_integer &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MaximumVisible(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MaximumVisible(n);
  }
}

virtual void controls_SETPROPERTY_Sorted(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Sorted(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Sorted(n);
  }
}

virtual void controls_SETPROPERTY_StringMaximum(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_StringMaximum(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_StringMaximum(n);
  }
}

virtual void controls_SETPROPERTY_StringMinimum(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_StringMinimum(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_StringMinimum(n);
  }
}

virtual void controls_SETPROPERTY_Format(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Format(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_Format(n);
  }
}

virtual void controls_SETPROPERTY_PopUp(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_PopUp(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_PopUp(n);
  }
}

virtual void controls_SETPROPERTY_ScrollBar(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ScrollBar(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_ScrollBar(n);
  }
}

virtual void controls_SETPROPERTY_MouseDownImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MouseDownImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MouseDownImage(n);
  }
}

virtual void controls_SETPROPERTY_MouseUpImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MouseUpImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MouseUpImage(n);
  }
}

virtual void controls_SETPROPERTY_EnabledImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_EnabledImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_EnabledImage(n);
  }
}


virtual void controls_SETPROPERTY_CheckMouseDownImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CheckMouseDownImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_CheckMouseDownImage(n);
  }
}

virtual void controls_SETPROPERTY_CheckMouseUpImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CheckMouseUpImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_CheckMouseUpImage(n);
  }
}

virtual void controls_SETPROPERTY_CheckEnabledImage(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_CheckEnabledImage(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_CheckEnabledImage(n);
  }
}

virtual void controls_SETPROPERTY_MouseDownSound(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MouseDownSound(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MouseDownSound(n);
  }
}

virtual void controls_SETPROPERTY_MouseUpSound(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MouseUpSound(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_MouseUpSound(n);
  }
}

virtual void controls_SETPROPERTY_HomeURL(QString &n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_HomeURL(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_HomeURL(n);
  }
}

virtual void controls_SETPROPERTY_OnAction(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnAction(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnAction(n);
  }
}
virtual void controls_SETPROPERTY_OnCursorPositionChanged(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnCursorPositionChanged(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnCursorPositionChanged(n);
  }
}
virtual void controls_SETPROPERTY_OnEvent(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnEvent(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnEvent(n);
  }
}
virtual void controls_SETPROPERTY_OnGoTo(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnGoTo(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnGoTo(n);
  }
}


virtual void controls_SETPROPERTY_OnBeforeInsert(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnBeforeInsert(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnBeforeInsert(n);
  }
}

virtual void controls_SETPROPERTY_OnBeforeDelete(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnBeforeDelete(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnBeforeDelete(n);
  }
}

virtual void controls_SETPROPERTY_OnDragExit(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnDragExit(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnDragExit(n);
  }
}

virtual void controls_SETPROPERTY_OnPaint(t_boolean n)
{
  QWidget *c;
  bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnPaint(n);
        #include "_form_property_switch.h"                 
        b = false;

      }
    } while (nextControl(&c));
  }

  if (b){
    SETPROPERTY_OnPaint(n);
  }
}

#endif
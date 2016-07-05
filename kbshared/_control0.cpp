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

#include "../kbshared/_control0.h"


#include "../kbshared/_form.h"
#include "../kbshared/_report.h"

extern _form *EXTERN_my_form;
extern _report *EXTERN_my_report;


#ifdef IDE

void _selectPanel::mouseMoveEvent ( QMouseEvent * e ) 
{
  if (parent->acceptDrops()){ // missused as selected flag = formDesignMode() == true

    if (bMousePressed == true){
      QWidget *c = parent;

      int diffx = e->globalX() - nMouseX;
      int diffy = e->globalY() - nMouseY;

      int x = c->x() + diffx;
      int y = c->y() + diffy;

      int width = positive(c->width() + diffx);
      int height = positive(c->height() + diffy);


      if (EXTERN_my_form){
        int xx = 0;
        xx += c->x();

        EXTERN_my_form->updateControls(style,  xx - x, /*(EXTERN_my_form->YScrollBar ? EXTERN_my_form->YScrollBar->value() : 0) +*/ c->y() - y, c->width() - width, c->height() - height);
      } else if (EXTERN_my_report){
        EXTERN_my_report->updateControls(style, c->x() - x, c->y() - y, c->width() - width, c->height() - height);
      }

      nMouseX = e->globalX();
      nMouseY = e->globalY();
    }  
  }
}

void _selectPanel::mouseReleaseEvent ( QMouseEvent * e ) 
{
  bMousePressed = false;
}

void _property::addProperties(t_properties *p, t_properties *p2)
{
  t_properties::Iterator it;
  t_properties::Iterator it2;

  for ( it = p2->begin(); it != p2->end(); ++it ){
    QString k = it.key();
    t_property *v = *it;

    it2 = p->insert(k, v);

    (*it2)->set = true;
    (*it2)->display = true;
    t_boolean b = (*it2)->v_boolean;
    b = b;
  }

}

void _property::mergeProperties(t_properties *p, t_properties *p2, bool bApplyMode)
{
  t_properties::Iterator it;
  t_properties::Iterator it2;
  t_property *d1;
  t_property *d2;

  {
    
    for ( it = p->begin(); it != p->end(); ++it ){
      d1 = *it;

      if (d1->display == true){

        QString s = it.key();

        if (p2->contains(s) ){


          it2 = p2->find(s);
          d2 = *it2;
         
          switch(d1->propertyType){
            case pt_integer:
              d1->set = d1->v_integer == d2->v_integer;
              if (d1->v_integer == d2->v_integer) d1->v_integer = d2->v_integer;
              break;           
            case pt_boolean:
              d1->set = d1->v_boolean == d2->v_boolean;          
              if (d1->v_boolean == d2->v_boolean) d1->v_boolean = d2->v_boolean;
              break;
            case pt_event:
              d1->set = d1->v_event == d2->v_event;          
              if (d1->v_event == d2->v_event) d1->v_event = d2->v_event;
              break;
            case pt_qstring:
              {
              d1->set = d1->v_qstring == d2->v_qstring;
              if (d1->v_qstring == d2->v_qstring) d1->v_qstring = d2->v_qstring;
              break;
              }
          }                 

        } else {
          d1->display = false;
        }
      }
    }
  }


}


#endif

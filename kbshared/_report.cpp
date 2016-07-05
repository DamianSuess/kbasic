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
#include <QtSql>

#include "_form.h"
#include "_report.h"

#include "_previewreport.h"

#ifdef IDE
#include "../kbide/_sourcecodeeditor.h"
#include "../kbide/_toolboxwindow_report.h"
#include "../kbide/_helpwindow_shortcut.h"

extern _helpwindow_shortcut *EXTERN_my_helpwindow_shortcut;
extern _propertywindow *EXTERN_my_propertywindow;
extern _toolboxwindow_report *EXTERN_my_toolboxwindow_report;
extern const QIcon &kbasicIcon(QString s);

extern QSqlDatabase CurrentDatabase;

#else
extern const QPixmap &interpreter_loadPixmap(QString fn);
extern QString sProjectName;
#endif

bool bStopDrawing;

_report *EXTERN_my_report;


void _form::previewReport()
{  
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  bStopDrawing = false;
#ifdef IDE
  if (!CurrentDatabase.isOpen()/* || db->isOpenError()*/){
    QApplication::restoreOverrideCursor();
    QMessageBox::information(this, MYAPP, "You are not connected to a database.");      
    return;
  }

  _previewreport *p = new _previewreport(this, this);
#else
  if (!CurrentDatabase.isOpen()/* || db->isOpenError()*/){
    QApplication::restoreOverrideCursor();
    QMessageBox::information(this, sProjectName.isNull() ? MYAPP : sProjectName, "You are not connected to a database.");      
    return;
  }

  _previewreport *p = new _previewreport(this, 0);
  p->setWindowIcon(QIcon(interpreter_loadPixmap("VIEW_REPORTPREVIEW.png")));
#endif
#ifdef IDE
  p->setWindowModality(Qt::WindowModal);
#endif
  p->setAttribute(Qt::WA_DeleteOnClose);  
  p->showMaximized();
  QApplication::restoreOverrideCursor();
}

void _form::printDialog()
{  
#ifdef RUN
  if (!CurrentDatabase.isOpen()/* || db->isOpenError()*/){
    QMessageBox::information(this, sProjectName.isNull() ? MYAPP : sProjectName, "You are not connected to a database.");      
    return;
  }

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  bStopDrawing = false;
  _previewreport *p = new _previewreport(this, 0, false, false, true);
  p->setAttribute(Qt::WA_DeleteOnClose);  
  QApplication::restoreOverrideCursor();

#endif
}

#define MAX_SECTIONS 8

QSqlQuery r[MAX_SECTIONS];
QString sSQLReport[MAX_SECTIONS];
QSqlRecord ri[MAX_SECTIONS];

int nOffsetMax;
int nPageY1;
int nPageY2;
int nNewPageAt;

int nYPageHeader;
int nYPageFooter;

QSizeF pageSize;


int nBorderLeft = 0;
int nBorderRight = 0;
int nBorderTop = 0;
int nBorderBottom = 0;


int nPageCounter = 0;
bool bNewPage = false;

int nMargin;
int nMarginTop;
int nMarginBottom;
int nMarginRight;

bool bPrintinig = false;
int nCurrentPage = 0;
int nTotalPage = 0;


QVector<_header *> header;
QVector<_footer *> footer;

struct section
{


  int header0;
  int header1;
  int header_height;
  int header_subheight;

  int footer0;
  int footer1;
  int footer_height;
  int footer_subheight;


  QVector<QWidget *> controls_header;
  QVector<QWidget *> controls_footer;
};

QVector<section*>sections;    


int nOffset;
QString sTest = "";




int _form::REPORT_drawSection(QPainter* p, int nPage, int nSection)
{  

  if (nSection >= MAX_SECTIONS || bStopDrawing) return 0;

  section *s = sections.at(nSection);

  int nExtraAddOffset = 0;

  int y = 0;


//  int nCount = 0;
  //r[nSection] = QSqlQuery();

  QString ss = sSQLReport[nSection];
  if (nSection > 0){
    if (ss.isEmpty()) return 0;

    //SELECT * FROM actor WHERE kbrecordid=SELECT actorid FROM actor_movie WHERE movieid=$kbrecordid
    int k = ss.lastIndexOf("=SELECT ");
    if (k == -1) k = ss.lastIndexOf("= SELECT ");
    if (k >= 0){ 
      QString ss2 = ss.mid(k + 1);

      ss = ss.left(k);
      int k0 = ss.lastIndexOf(" ");
      QString sField = ss.mid(k0 + 1);
      
      int k2 = ss2.lastIndexOf("$");

      QString sField2 = ss2.mid(k2 + 1);
      ss2 = ss2.left(k2);

      int n = ri[nSection - 1].indexOf(sField2);
      if (n >= 0){
        sField2 = r[nSection - 1].value(n).toString();
      } else  return 0;
      ss2 += sField2;    

      if (!r[nSection].exec(ss2)){ 
        QMessageBox::information(this, MYAPP, tr("An error occured! Could not read database table: \n\n") + ss + "\n\n" + r[nSection].lastError().text()); 
        bStopDrawing = true;
        return 0;
      }
      QString sIds = "=";

      bool bFirst = true;

      if (r[nSection].first()){
        do {
          if (bFirst == false) sIds += " OR " + sField + "=";

          sIds += r[nSection].value(0).toString();
          bFirst = false;
        } while (r[nSection].next());
      }   

      ss += sIds;

      if (!r[nSection].exec(ss)){ 
        QMessageBox::information(this, MYAPP, tr("An error occured! Could not read database table: \n\n") + ss + "\n\n" + r[nSection].lastError().text()); 
        bStopDrawing = true;
        return 0;
      }
    

    } else {
      k = ss.lastIndexOf("$");
      QString sField = ss.mid(k + 1);
      ss = ss.left(k);

      int n = ri[nSection - 1].indexOf(sField);
      if (n >= 0){
        sField = r[nSection - 1].value(n).toString();
      } else  return 0;
      ss += sField;    

      if (!r[nSection].exec(ss)){ 
        QMessageBox::information(this, MYAPP, tr("An error occured! Could not read database table: \n\n") + ss + "\n\n" + r[nSection].lastError().text()); 
        bStopDrawing = true;
        return 0;
      }
    }
  }

/*
  switch(nSection){
    case 0:
      sSQLReport[0] = this->GETPROPERTY_SQLName();

      if (!r[nSection].exec(sSQLReport[nSection])){ 
        QMessageBox::information(this, MYAPP, tr("An error occured! Could not read database table: \n\n") + sSQLReport[nSection] + "\n\n" + r[nSection].lastError().text()); 
        bStopDrawing = true;
        return 0;
      }
    //  nCount = r.rowCount();
      break;
    case 1:
    //  nCount = 5;
      break;
    default:
    //  nCount = 3;
      break;
  }*/
  // record count test for 5 rows for each section  
//  for (int z = 0; z < nCount; z++){     

  

  int nCount = r[nSection].size();
  if (nCount == -1){
    nCount = 0;
    if (r[nSection].first()){
      do {
        nCount++;
      } while (r[nSection].next());
    }           
  }
  int z = 0;
  bool bFirst = r[nSection].first();
  {
    do {
    ri[nSection] = r[nSection].record();

      //ri[nSection].clearValues();

      if (/*bNewPage && */(nPageCounter || z) && nSection == 0 && sections.size() > 1){
        //bNewPage = false;

        nPageCounter++;
        nOffset = pageSize.height() * nPageCounter;
        //nOffset -= s->header_subheight;
      }
  /*
      if (bNewPage && nSection == 0){
        nOffset += nExtraAddOffset;
        bNewPage = false;
      }
  */
      //int nPageCounterOld = nPageCounter;

      int k = s->controls_header.size();
      nOffset -= s->header_subheight;
      for (int n = 0; n < k; n++){               

        QWidget *c = s->controls_header.at(n);

        #define SWITCH GETPROPERTY_Y();      
        #define SWITCH3 y
        #include "_form_property_switch.h"   
        #undef SWITCH3
  /*
        if (bNewPage && nSection == 0 && nPageCounter && sections.size() > 1){
          nPageCounter++;
          nOffset = pageSize.height() * nPageCounter - y + nYPageHeader * 2;
          bNewPage = false;
        }*/

        if (nOffset > nNewPageAt + pageSize.height() * nPageCounter){
          nPageCounter++;
          if (nSection > 1){
            nOffset = pageSize.height() * nPageCounter - y + nYPageHeader * 2;
            nOffset -= s->header_subheight;
          } else {
            nOffset = pageSize.height() * nPageCounter - y + nYPageHeader;
          }

          for (int i = 0; nSection > 0 && i < (nSection == 0 ? nCount - z : nCount); i++){
            nOffset -= s->header_height;
          }

          if (nSection - 1 >= 0){
            section *ss = sections.at(nSection - 1);
            nOffset += ss->header_height;
          } 
          bNewPage = true;
          

          /*
          for (int i = nSection - 1; i >= 0; i--){
            section *ss = sections.at(nSection);
  //          nOffset -= ss->header_subheight;
          }*/
          //bNewPage = true;
        }
        
        if (nOffsetMax < nOffset) nOffsetMax = nOffset;
        
        if (p && nOffset + y >= nPageY1 && nOffset + y <= nPageY2){
          //sTest = QString("%1 %2").arg(z).arg(nOffset + y);
          if (bFirst) REPORT_drawControl(p, c, nSection);
        }
           
      }
  //    if (nPageCounterOld == nPageCounter) 
      nOffset += s->header_subheight;
      //nPageCounterOld = nPageCounter;
      
      if (nSection + 1 < sections.size()) nExtraAddOffset = REPORT_drawSection(p, nPage, nSection + 1);
      //if (nSection == 0) nExtraAddOffset = 0;

      if (p && nSection == 0){
        nSection = nSection;
      }

      if (p && nSection == 1){
        nSection = nSection;
      }

      if (p && nSection == 2){
        nSection = nSection;
      }

      nOffset -= s->footer_subheight;
      k = s->controls_footer.size();
      for (int n = 0; n < k; n++){               

        QWidget *c = s->controls_footer.at(n);

        #define SWITCH GETPROPERTY_Y();      
        #define SWITCH3 y
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if (nOffset > nNewPageAt + pageSize.height() * nPageCounter){
          nPageCounter++;
          nOffset = pageSize.height() * nPageCounter - y + nYPageHeader;
          nOffset -= s->footer_subheight;

          for (int i = 0; i < nCount; i++){
            nOffset -= s->footer_height;
          }

          if (nSection - 1 >= 0){
            section *ss = sections.at(nSection - 1);
            nOffset += ss->footer_height;
          } 
          bNewPage = true;

        }
        
        if (nOffsetMax < nOffset) nOffsetMax = nOffset;
        
        if (p && nOffset + y >= nPageY1 && nOffset + y <= nPageY2){
          //sTest = QString("%1 %2").arg(z).arg(nOffset + y);
          if (bFirst) REPORT_drawControl(p, c, nSection);
        }
           
      }
      //if (nPageCounterOld == nPageCounter) 
      nOffset += s->footer_subheight;
      //nPageCounterOld = nPageCounter;
      
      if (nSection == 0){
        nSection = nSection;
      }
      if (z + 1 < nCount){
        nOffset += s->header_height; // carriage return for header area
        nOffset += s->footer_height; // carriage return for footer area
        nOffset += nExtraAddOffset;
      }
      

      z++;
    } while (bFirst && r[nSection].next());
  }
    
  return s->header_height + s->footer_height; 

}

int _form::REPORT_draw(QPainter* p, int nPage)
{

  //int nPage = 1;

  if (p == 0){

    nBorderTop = this->GETPROPERTY_BorderTop();
    nBorderBottom = this->GETPROPERTY_BorderBottom();
    nBorderLeft = this->GETPROPERTY_BorderLeft();
    nBorderRight = this->GETPROPERTY_BorderRight();

    header.clear();
    footer.clear();
    sections.clear();

    for (int i = 0; i < MAX_SECTIONS; i++){
      r[i] = QSqlQuery((CurrentDatabase));
    }

  } else {
    p = p;
  }


  nOffset = 0;

  QString sControlType = "";
  int y = 0;

  int header_size = header.size();
  int footer_size = footer.size();

  QWidget *c;

  // sort header & footer in 2 lists
  if (p == 0 && firstControl(&c)){    

    do {

   //   sControlType = c->property("ControlType").toString();
        

      #define SWITCH GETPROPERTY_ControlType();      
      #define SWITCH3 sControlType
      #include "_form_property_switch.h"   
      #undef SWITCH3

      #define SWITCH GETPROPERTY_Y();      
      #define SWITCH3 y
      #include "_form_property_switch.h"   
      #undef SWITCH3
      bool b = true;

      if (sControlType == "Header"){

        header_size = header.size();
        for (int i = 0; i < header_size; i++){
          if (y < header.at(i)->GETPROPERTY_Y()){
            header.insert(i, (_header *) c);
            b = false;
            break;
          }
        }        
        if (b) header.append((_header *) c);
      } else if (sControlType == "Footer"){

        footer_size = footer.size();
        for (int i = 0; i < footer_size; i++){
          if (y < footer.at(i)->GETPROPERTY_Y()){
            footer.insert(i, (_footer *) c);
            b = false;
            break;
          }
        }        
        if (b) footer.append((_footer *) c);
      }

    } while (nextControl(&c)); 
  }

  header_size = header.size();
  footer_size = footer.size();

  nYPageHeader = header_size ? header.at(0)->GETPROPERTY_Y() : 0;
  nYPageFooter = footer_size ? footer.at(footer_size - 1)->GETPROPERTY_Y() : 0;

  if (nYPageFooter == 0 || header_size != footer_size) return 0; // if no footer at all abort printing
  
  // test for placement of header/footer pairs, abort if order is not ok
  for (int i = 0; i < header_size; i++){
    if (footer.at(header_size - i - 1)->GETPROPERTY_Y() < header.at(0)->GETPROPERTY_Y()) return 0;
  }

  int nOffset2 = 0;
  nNewPageAt = (pageSize.height() - (this->GETPROPERTY_Height() - nYPageFooter)) - nYPageFooter;

  if (firstControl(&c)){    

    do {

      #define SWITCH GETPROPERTY_ControlType();      
      #define SWITCH3 sControlType
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sControlType == "Header"){
        continue;
      } else if (sControlType == "Footer"){
        continue;
      }

      #define SWITCH GETPROPERTY_Y();      
      #define SWITCH3 y
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (p){
        //nTotalPage = REPORT_pageCount();
        nCurrentPage = nPage;
      }

      // draw header controls, which are page related
      if (p && y <= nYPageHeader){
        
        nOffset = pageSize.height() * nPage;
        //sTest = "";
        REPORT_drawControl(p, c, -1);
        
      // draw footer controls, which are page related
      } else if (p && y >= nYPageFooter){
        
        if (nYPageHeader && nYPageFooter) nOffset = - header.at(0)->GETPROPERTY_Height() - footer.at(0)->GETPROPERTY_Height();
        nOffset += pageSize.height() * nPage + nNewPageAt;
        //sTest = "";
        REPORT_drawControl(p, c, -1);

      // create section list
      } else if (p == 0 && y >= nYPageHeader && y <= nYPageFooter){
        section *s = 0;
        bool b = true;

        if (y == 457){
          y = y;
        }

        int sections_size = sections.size();
        if (sections_size){
          for (int i = sections_size - 1; i >= 0; i--){
            s = sections.at(i);
            if ((y >= s->header0 && y <= s->header1)){
              s->controls_header.append(c);
              b = false;
              break;
            } else if ((y >= s->footer0 && y <= s->footer1)){
              s->controls_footer.append(c);
              b = false;
              break;
            }
          }
        }

        if (b){
          s = new section();

          int i = 0;
          int k = -1;
          for (; i < header_size; i++){
            if (y >= header.at(i)->GETPROPERTY_Y() && y <= footer.at(header_size - i - 1)->GETPROPERTY_Y()){                
              k = i;
            } 
          }
          
          int m = 0;
          if (k == -1){
            if (sections_size){
            } else {
              s->header0 = nYPageHeader;
              s->header1 = nYPageFooter;
            }
          } else if (k + 1 >= header_size){
            _header *h = header.at(k);
            m = h->GETPROPERTY_Height();
            s->header0 = h->GETPROPERTY_Y();
            s->header1 = footer.at(header_size - k - 1)->GETPROPERTY_Y();
          } else {
            _header *h = header.at(k);
            m = h->GETPROPERTY_Height();
            s->header0 = h->GETPROPERTY_Y();
            s->header1 = header.at(k + 1)->GETPROPERTY_Y();
          }
          s->header_height = m ? s->header1 - s->header0 - m : 0;

          int kh = header_size - k;
          k = -1;
          i = 0;
          for (; i < header_size; i++){
            if (i + 1 == header_size){
            } else {
              if (y >= footer.at(i)->GETPROPERTY_Y() && y <= footer.at(i + 1)->GETPROPERTY_Y()){                
                k = i;
              } 
            }
          }

          m = 0;
          if (k == -1){            
            if (sections_size){
              if (kh - 2 >= 0 && kh < header_size){
                _footer *f = footer.at(kh - 2);
                m = f->GETPROPERTY_Height();
                s->footer0 = f->GETPROPERTY_Y();
                s->footer1 = footer.at(kh - 1)->GETPROPERTY_Y();
              } else {
                s->footer0 = 0;
                s->footer1 = 0;
              }
            } else {
              _footer *f = 0;
              if (footer.size() - 1 > 0) f = footer.at(footer.size() - 1);
              if (f){
                s->footer0 = f->GETPROPERTY_Y();
              } else {
                s->footer0 = nYPageHeader;
              }
              s->footer1 = nYPageFooter;
            }
          } else if (k + 1 >= header_size){
            _header *h = header.at(header_size - 1);
            m = h->GETPROPERTY_Height();
            s->footer0 = h->GETPROPERTY_Y();
            s->footer1 = footer.at(k)->GETPROPERTY_Y();
          } else {
            _footer *f = footer.at(k);
            m = f->GETPROPERTY_Height();
            s->footer0 = f->GETPROPERTY_Y();
            s->footer1 = footer.at(k + 1)->GETPROPERTY_Y();
          }
          s->footer_height = m ? s->footer1 - s->footer0 - m : 0;

          sections.append(s);

          if ((y >= s->header0 && y <= s->header1)){
            s->controls_header.append(c);
          } else if ((y >= s->footer0 && y <= s->footer1)){
            s->controls_footer.append(c);
          }
          
        }         

      }    

    } while (nextControl(&c));     
  }

  int sections_size = sections.size();
  if (sections_size == 0) return 0;

  // sort sections
  if (p == 0){
    QVector<section*>sec; 
re:
    int y = 0;
    int i = 0;
    int n = 0;
    sections_size = sections.size();
    for (; i < sections_size; i++){
      section *s = sections.at(i);

      if (s->header0 > y){ 
        y = s->header0;
        n = i;
      }
    }
    if (y){
      sec.prepend(sections.at(n));
      sections.remove(n);
      goto re;
    }

    sections = sec;
  }

  nOffsetMax = 0;
  nPageY1 = pageSize.height() * (nPage);
  nPageY2 = pageSize.height() * (nPage + 1);

  int gh = 0;
  int gf = 0;

  sections_size = sections.size();
  for (int i = 0; p == 0 && i < sections_size; i++){
    section *s = sections.at(i);

    gh = 0;
    gf = 0;

    for (int n = 0; n < header_size; n++){
      _header *h = header.at(n);
      if (s->header1 > h->GETPROPERTY_Y()){
        gh += h->GETPROPERTY_Height();
      } 
      if (s->footer1 > h->GETPROPERTY_Y()){
        gf += h->GETPROPERTY_Height();
      } 
      QString s = h->GETPROPERTY_Caption();
      if (!s.isEmpty()){
        sSQLReport[n] = s;
/*
        QString ss = sSQLReport[n];

        int k = ss.lastIndexOf("$");
        QString sField = ss.mid(k + 1);
        ss = ss.left(k);

        int n = ri[n - 1].indexOf(sField);
        if (n >= 0){
          sField = r[n - 1].value(n).toString();
        } else  return 0;
        ss += sField;

        sSQLReport[n] = ss;*/
      } else {
        sSQLReport[n] = "";
      }

    }    
    for (int n = 0; n < footer_size; n++){
      _footer *f = footer.at(n);
      int yy = f->GETPROPERTY_Y();
      if (s->footer1 > yy){
        gf += f->GETPROPERTY_Height();
      }// else break;
    }

    s->header_subheight = gh;
    s->footer_subheight = i + 1 == sections_size ? 0 : gf;
  }
  
  QString m = this->GETPROPERTY_SQLName();
  if (!m.isEmpty()) sSQLReport[0] = m;

  section *s = sections.at(0);
  if (p){
    nOffset = 0;
  }
  nPageCounter = 0;
  bNewPage = false;

  if (!r[0].exec(sSQLReport[0])){ 
    QMessageBox::information(this, MYAPP, tr("An error occured! Could not read database table: \n\n") + sSQLReport[0] + "\n\n" + r[0].lastError().text()); 
    bStopDrawing = true;
    return 0;
  }

  REPORT_drawSection(p, nPage, 0);

  int mm = nOffsetMax / (pageSize.height() - nBorderTop - nBorderBottom);
  return mm + 1;

}

void _form::REPORT_drawControl(QPainter* p, QWidget *c, int nSection)
{

  static QTextEdit editor;

  QString sControlType;// = "";
  int x;// = 0;
  int y;// = 0;
  int h;// = 0;
  int w;// = 0;
  QString sCaption;// = "";
  QString sStringValue;// = "";
  QString sBackground;// = "";
  QString sFontColor;// = "";
  QString sFontName;// = "";
  
  int nFontSize = 0;
  bool bFontBold = false;
  bool bFontItalic = false;
  bool bFontUnderline = false;
  bool bBooleanValue = false;
  
  
  #define SWITCH GETPROPERTY_ControlType();      
  #define SWITCH3 sControlType
  #include "_form_property_switch.h"   
  #undef SWITCH3

  #define SWITCH GETPROPERTY_X();      
  #define SWITCH3 x
  #include "_form_property_switch.h"   
  #undef SWITCH3

  x += nMargin;

  #define SWITCH GETPROPERTY_Y();      
  #define SWITCH3 y
  #include "_form_property_switch.h"   
  #undef SWITCH3

  y += nOffset + nMarginTop;
  if (bPrintinig){
    y -= pageSize.height() * nCurrentPage;
  }

  #define SWITCH GETPROPERTY_Width();      
  #define SWITCH3 w
  #include "_form_property_switch.h"   
  #undef SWITCH3

  #define SWITCH GETPROPERTY_Height();      
  #define SWITCH3 h
  #include "_form_property_switch.h"   
  #undef SWITCH3

  
  #define SWITCH GETPROPERTY_Background();      
  #define SWITCH3 sBackground
  #include "_form_property_switch.h"   
  #undef SWITCH3

  #define SWITCH GETPROPERTY_FontColor();      
  #define SWITCH3 sFontColor
  #include "_form_property_switch.h"   
  #undef SWITCH3

  #define SWITCH GETPROPERTY_FontName();      
  #define SWITCH3 sFontName
  #include "_form_property_switch.h"   
  #undef SWITCH3

  #define SWITCH GETPROPERTY_FontSize();      
  #define SWITCH3 nFontSize
  #include "_form_property_switch.h"   
  #undef SWITCH3

  #define SWITCH GETPROPERTY_FontBold();      
  #define SWITCH3 bFontBold
  #include "_form_property_switch.h"   
  #undef SWITCH3

  #define SWITCH GETPROPERTY_FontItalic();      
  #define SWITCH3 bFontItalic
  #include "_form_property_switch.h"   
  #undef SWITCH3

  #define SWITCH GETPROPERTY_FontUnderline();      
  #define SWITCH3 bFontUnderline
  #include "_form_property_switch.h"   
  #undef SWITCH3


  QFont f;

  if (!sFontName.isEmpty()) f.setFamily(sFontName);
  if (nFontSize) f.setPointSize(nFontSize);
  if (bFontBold) f.setBold(bFontBold);
  if (bFontItalic) f.setItalic(bFontItalic);
  if (bFontUnderline) f.setUnderline(bFontUnderline);
  p->setFont(f);

  if (!sBackground.isEmpty()) p->fillRect(x, y, w, h, sBackground.startsWith("&H") ? QBrush(_property::getColor(sBackground)) : QBrush(loadPixmap(sBackground)));

  QString sBinding = "";

  if (sControlType == "Label"){

    #define SWITCH GETPROPERTY_SQLName();      
    #define SWITCH3 sBinding
    #include "_form_property_switch.h"   
    #undef SWITCH3

//    int nPos = r[nSection].at();
    if (nSection >= 0){
      int n = ri[nSection].indexOf(sBinding);
      if (n >= 0){
        sCaption = r[nSection].value(n).toString();
      } else {
        sCaption = "";
      }
    } else {
      sCaption = "";
    }

    if (sBinding.isEmpty() && sStringValue.isEmpty()){
      #define SWITCH GETPROPERTY_Caption();      
      #define SWITCH3 sCaption
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sCaption == "Label") sCaption = "";
    }

    if (!sCaption.isEmpty()){
      if (!sFontColor.isEmpty()){
        p->setPen(_property::getColor(sFontColor));
      } else {
        p->setPen(Qt::black);
      }

      QString k = sCaption;
      k = k.simplified().toLower();
      if (k == "=page()"){
        sCaption = QString("%1").arg(nCurrentPage + 1);
      } else if (k == "=totalpage()"){
        sCaption = QString("%1").arg(nTotalPage);
      } else if (k == "=pages()"){
        sCaption = QString(tr("%1 / %2")).arg(nCurrentPage + 1).arg(nTotalPage);
      } else if (k == "=date()"){
        sCaption = QString("%1").arg(QDate::currentDate().toString());
      } else if (k == "=time()"){
        sCaption = QString("%1").arg(QTime::currentTime().toString());
      }

      p->drawText(QRect(x, y, w, h), /*sTest +*/ sCaption);
    }

  } else if (sControlType == "RichTextBox" || sControlType == "TextBox"){

    #define SWITCH GETPROPERTY_SQLName();      
    #define SWITCH3 sBinding
    #include "_form_property_switch.h"   
    #undef SWITCH3

    int nPos = r[nSection].at();
    if (nSection >= 0){
      int n = ri[nSection].indexOf(sBinding);
      if (n >= 0){
        sStringValue = r[nSection].value(n).toString();
      } else {
        sStringValue = "";
      }
    } else {
      sStringValue = "";
    }

    if (sStringValue.startsWith("<html><", Qt::CaseInsensitive)){
      editor.setText(sStringValue);
      sStringValue = editor.toPlainText();
    }

    if (sBinding.isEmpty() && sStringValue.isEmpty()){
      #define SWITCH GETPROPERTY_StringValue();      
      #define SWITCH3 sStringValue
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sStringValue == "TextBox" || sStringValue == "RichTextBox") sStringValue = "";
    }

    if (!sStringValue.isEmpty()){
      if (!sFontColor.isEmpty()){
        p->setPen(_property::getColor(sFontColor));
      } else {
        p->setPen(Qt::black);
      }
      p->drawText(QRect(x, y, w, h), /*sTest + */sStringValue);
    }
  } else if (sControlType == "DateTimeBox" || sControlType == "TimeBox" || sControlType == "DateBox"){
    
    #define SWITCH GETPROPERTY_SQLName();      
    #define SWITCH3 sBinding
    #include "_form_property_switch.h"   
    #undef SWITCH3

    int nPos = r[nSection].at();
    if (nSection >= 0){
      int n = ri[nSection].indexOf(sBinding);
      if (n >= 0){
        sStringValue = r[nSection].value(n).toString();
      } else {
        sStringValue = "";
      }
    } else {
      sStringValue = "";
    }

    if (sStringValue.startsWith("<html><", Qt::CaseInsensitive)){
      editor.setText(sStringValue);
      sStringValue = editor.toPlainText();
    }

    if (sBinding.isEmpty() && sStringValue.isEmpty()){
      #define SWITCH GETPROPERTY_StringValue();      
      #define SWITCH3 sStringValue
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sStringValue == "DateTimeBox" || sStringValue == "TimeBox" || sStringValue == "DateBox") sStringValue = "";
    }


/*
      } else if (sCaption.simplified().toLower() == "=date()"){
        sCaption = QString("%1").arg(QDate::currentDate());
      } else if (sCaption.simplified().toLower() == "=time()"){
        sCaption = QString("%1").arg(QTime::currentTime());
*/
/*
    if (sStringValue.isEmpty()){
      
      if (sControlType == "DateTimeBox") sStringValue = "yyyy-MM-dd hh:mm:ss";
      else if (sControlType == "DateBox") sStringValue = "yyyy-MM-dd";
      else if (sControlType == "TimeBox") sStringValue = "hh:mm:ss";
     
    } */

    if (!sStringValue.isEmpty()){
      if (!sFontColor.isEmpty()){
        p->setPen(_property::getColor(sFontColor));
      } else {
        p->setPen(Qt::black);
      }
      p->drawText(QRect(x, y, w, h), /*sTest + */sStringValue);
    }
  } else if (sControlType == "CheckBox"){
    
    #define SWITCH GETPROPERTY_SQLName();      
    #define SWITCH3 sBinding
    #include "_form_property_switch.h"   
    #undef SWITCH3

    int nPos = r[nSection].at();
    if (nSection >= 0){
      int n = ri[nSection].indexOf(sBinding);
      if (n >= 0){
        bBooleanValue = r[nSection].value(n).toBool();
      } else {
        bBooleanValue = false;
      }
    } else {
      bBooleanValue = false;
    }

    if (sBinding.isEmpty() && sStringValue.isEmpty()){
      #define SWITCH GETPROPERTY_BooleanValue();      
      #define SWITCH3 bBooleanValue
      #include "_form_property_switch.h"   
      #undef SWITCH3
    }

    #define SWITCH GETPROPERTY_Caption();      
    #define SWITCH3 sCaption
    #include "_form_property_switch.h"   
    #undef SWITCH3

    if (!sCaption.isEmpty()){
      if (!sFontColor.isEmpty()){
        p->setPen(_property::getColor(sFontColor));
      } else {
        p->setPen(Qt::black);
      }
      p->drawText(QRect(x + 15, y, w, h), /*sTest + */sCaption);
      p->fillRect(x, y + 5, 10, 10, QBrush(Qt::black));
      p->fillRect(x + 1, y + 5 + 1, 10 - 2, 10 - 2, QBrush(Qt::gray));
      p->fillRect(x + 2, y + 5 + 2, 10 - 3, 10 - 3, QBrush(Qt::white));

      if (bBooleanValue){
        p->setPen(Qt::black);
        p->drawLine(x, y + 5, x + 10, y + 15);
        p->drawLine(x + 1, y + 5, x + 9, y + 15);

        p->drawLine(x, y + 5 + 10, x + 10, y + 5);
        p->drawLine(x, y + 5 + 10 - 1, x + 10, y + 5 + 1);
      }

    }
    /*
  } else if (sControlType == "Frame"){

    #define SWITCH GETPROPERTY_Caption();      
    #define SWITCH3 sCaption
    #include "_form_property_switch.h"   
    #undef SWITCH3

    if (!sCaption.isEmpty()){
      if (!sFontColor.isEmpty()){
        p->setPen(_property::getColor(sFontColor));
      } else {
        p->setPen(Qt::black);
      }
      p->fillRect(x, y + 5, w, h, QBrush(Qt::black));
      p->fillRect(x + 1, y + 5 + 1, w - 2, h - 2, QBrush(Qt::gray));
      p->fillRect(x + 2, y + 5 + 2, w - 3, h - 3, QBrush(Qt::white));
  
      p->setPen(Qt::white);
      QString s = "";
      s = s.fill(QChar('_'), sCaption.length() + 1);
      p->drawText(x + 8, y + 4, s);
      p->drawText(x + 8, y + 5, s);
      p->drawText(x + 8, y + 6, s);
      p->drawText(x + 8, y + 7, s);
      p->drawText(x + 8, y + 8, s);
      p->setPen(Qt::black);
      p->drawText(x + 10 + 1, y + 9, sTest + sCaption);

    }*/
  } else if (sControlType == "ImageBox"){

    #define SWITCH GETPROPERTY_SQLName();      
    #define SWITCH3 sBinding
    #include "_form_property_switch.h"   
    #undef SWITCH3

    int nPos = r[nSection].at();
    if (nSection >= 0){
      int n = ri[nSection].indexOf(sBinding);
      if (n >= 0){
        sStringValue = r[nSection].value(n).toString();
      } else {
        sStringValue = "";
      }
    } else {
      sStringValue = "";
    }

    if (sBinding.isEmpty() && sStringValue.isEmpty()){
      #define SWITCH GETPROPERTY_StringValue();      
      #define SWITCH3 sStringValue
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sStringValue == "TextBox" || sStringValue == "RichTextBox") sStringValue = "";
    }

    if (!sStringValue.isEmpty() && sBackground.isEmpty()){
      static QMap<QString,QPixmap>cache;

      static QPixmap pp;
      if (cache.contains(sStringValue)){
        pp = cache[sStringValue];
      } else {
        pp = loadPixmap(sStringValue);
        cache[sStringValue] = pp;
      }
      p->drawPixmap(x, y, w, h, pp);
    }
  }        


}

void _form::REPORT_setMargin(int m)
{
   nMargin = m;
   nMarginTop = 0;//100;
   nMarginRight = 0;//100;
   nMarginBottom = 0;//100;
}

void _form::REPORT_setPageSize(QSizeF f)
{
  pageSize = f;
}

int _form::REPORT_pageCount()
{
  int n = 0;
//  if (n == 0) 
  n = REPORT_draw(0, 0);
  nTotalPage = n;
  return n;
}

QSizeF _form::REPORT_pageSize()
{
  return pageSize;
}

QSizeF _form::REPORT_docSize()
{
  int n = REPORT_pageCount();
  return QSizeF(1500, 1500 * n);
}

void _form::REPORT_print(QPrinter *p)
{
  //QPrinter printer;
  //printer.setOrientation(QPrinter::Portait);

  //QPrintDialog *dialog = new QPrintDialog(&printer, this);
  //dialog->setWindowTitle(tr("Print Preview"));
  //if (dialog->exec() != QDialog::Accepted) return;
bPrintinig = true;
  QPainter painter;
  painter.begin(p);
  int n = REPORT_pageCount();
  nTotalPage = n;
  for (int i = 0; i < n; i++){
    nCurrentPage = i;
    REPORT_draw(&painter, i);   
    if (i + 1 < n) p->newPage();
    
  }

  painter.end();

  bPrintinig = false;
}
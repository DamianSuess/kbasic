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

#include "_propertywindow.h"
#include "../kbshared/_form.h"
#include "../kbshared/_table.h"
#include "../kbshared/_report.h"
#include "../kbshared/_menubar.h"
#include "../kbshared/_toolbar.h"

extern _propertywindow *EXTERN_my_propertywindow;
extern _table *EXTERN_my_table;
extern _form *EXTERN_my_form;
extern _report *EXTERN_my_report;
extern _menubar *EXTERN_my_menubar;
extern _toolbar *EXTERN_my_toolbar;
extern _mainwindow *EXTERN_my_mainwindow;

_form *f;

#define ISFORM ((f = EXTERN_my_form) || (f = EXTERN_my_report)) && qobject_cast<_form *>(EXTERN_my_mainwindow->workspace->currentSubWindow() ? EXTERN_my_mainwindow->workspace->currentSubWindow()->widget() : 0)
#define ISMENUBAR EXTERN_my_menubar && qobject_cast<_menubar *>(EXTERN_my_mainwindow->workspace->currentSubWindow() ? EXTERN_my_mainwindow->workspace->currentSubWindow()->widget() : 0)
#define ISTOOLBAR EXTERN_my_toolbar && qobject_cast<_toolbar *>(EXTERN_my_mainwindow->workspace->currentSubWindow() ? EXTERN_my_mainwindow->workspace->currentSubWindow()->widget() : 0)
#define ISTABLE EXTERN_my_table && qobject_cast<_table *>(EXTERN_my_mainwindow->workspace->currentSubWindow() ? EXTERN_my_mainwindow->workspace->currentSubWindow()->widget() : 0)

void _propertywindow::SLOTPROPERTY_Group()
{
  if (ISFORM ){
    PROPERTY_Group->setModified(false);
    QString n = (PROPERTY_Group->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Group(n);
  }
  else if (ISMENUBAR){
    PROPERTY_Group->setModified(false);
    QString n = (PROPERTY_Group->text());
    EXTERN_my_menubar->controls_SETPROPERTY_Group(n);
  }
   else if (ISTOOLBAR){
    PROPERTY_Group->setModified(false);
    QString n = (PROPERTY_Group->text());
    EXTERN_my_toolbar->controls_SETPROPERTY_Group(n);
  }

}

void _propertywindow::SLOTPROPERTY_Background()
{
  if (ISFORM && PROPERTY_Background->isVisible()){
    QString s = PROPERTY_Background->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Background(s);
  }
}


void _propertywindow::SLOTPROPERTY_BackgroundStyle()
{
  if (ISFORM && PROPERTY_BackgroundStyle->isVisible()){
    QString s = PROPERTY_BackgroundStyle->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_BackgroundStyle(s);
  }
}


void _propertywindow::SLOTPROPERTY_DockTitleVisible()
{

  if (ISFORM && PROPERTY_DockTitleVisible->isVisible()){
    bool n = (PROPERTY_DockTitleVisible->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_DockTitleVisible(n);
  }

}


void _propertywindow::SLOTPROPERTY_DockOrder()
{

  if (ISFORM && PROPERTY_DockOrder->isVisible()){
    {
      QString n = (PROPERTY_DockOrder->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_DockOrder(n);
    }
  }

}

void _propertywindow::SLOTPROPERTY_DockSplit()
{

  if (ISFORM && PROPERTY_DockSplit->isVisible()){
    {
      QString n = (PROPERTY_DockSplit->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_DockSplit(n);
    }
  }

}



void _propertywindow::SLOTPROPERTY_DockWidth()
{
  if (ISFORM/* && PROPERTY_DockWidth->lineedit()->isModified()*/){
    PROPERTY_DockWidth->lineedit()->setModified(false);
    int n = (PROPERTY_DockWidth->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_DockWidth(n);
  }
}

void _propertywindow::SLOTPROPERTY_DockHeight()
{
  if (ISFORM/* && PROPERTY_DockHeight->lineedit()->isModified()*/){
    PROPERTY_DockHeight->lineedit()->setModified(false);
    int n = (PROPERTY_DockHeight->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_DockHeight(n);
  }
}


void _propertywindow::SLOTPROPERTY_Brightness()
{
  if (ISFORM){
    PROPERTY_Brightness->setModified(false);
    int n = (PROPERTY_Brightness->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Brightness(n);
  }
}

void _propertywindow::SLOTPROPERTY_Contrast()
{
  if (ISFORM){
    PROPERTY_Contrast->setModified(false);
    int n = (PROPERTY_Contrast->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Contrast(n);
  }
}

void _propertywindow::SLOTPROPERTY_Hue()
{
  if (ISFORM){
    PROPERTY_Hue->setModified(false);
    int n = (PROPERTY_Hue->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Hue(n);
  }
}

void _propertywindow::SLOTPROPERTY_Saturation()
{
  if (ISFORM){
    PROPERTY_Saturation->setModified(false);
    int n = (PROPERTY_Saturation->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Saturation(n);
  }
}

void _propertywindow::SLOTPROPERTY_ScaleMode()
{
  if (ISFORM && PROPERTY_ScaleMode->isVisible()){
    QString s = PROPERTY_ScaleMode->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ScaleMode(s);
  }
}


void _propertywindow::SLOTPROPERTY_AspectRatio()
{
  if (ISFORM && PROPERTY_AspectRatio->isVisible()){
    QString s = PROPERTY_AspectRatio->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_AspectRatio(s);
  }
}

void _propertywindow::SLOTPROPERTY_TransitionTime()
{
  if (ISFORM){
    PROPERTY_TransitionTime->setModified(false);
    int n = (PROPERTY_TransitionTime->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_TransitionTime(n);
  }
}

void _propertywindow::SLOTPROPERTY_Muted()
{

  if (ISFORM && PROPERTY_Muted->isVisible()){
    bool n = (PROPERTY_Muted->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Muted(n);
  }
}

void _propertywindow::SLOTPROPERTY_Volume()
{
  if (ISFORM){
    PROPERTY_Volume->setModified(false);
    int n = (PROPERTY_Volume->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Volume(n);
  }
}

void _propertywindow::SLOTPROPERTY_PrefinishMark()
{
  if (ISFORM){
    PROPERTY_PrefinishMark->setModified(false);
    int n = (PROPERTY_PrefinishMark->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_PrefinishMark(n);
  }
}

void _propertywindow::SLOTPROPERTY_Tick()
{
  if (ISFORM){
    PROPERTY_Tick->setModified(false);
    int n = (PROPERTY_Tick->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Tick(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnTick()
{
  if (ISFORM && PROPERTY_OnTick->isVisible()){
    bool n = (PROPERTY_OnTick->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnTick(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnStateChanged()
{
  if (ISFORM && PROPERTY_OnStateChanged->isVisible()){
    bool n = (PROPERTY_OnStateChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnStateChanged(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnAboutToFinish()
{
  if (ISFORM && PROPERTY_OnAboutToFinish->isVisible()){
    bool n = (PROPERTY_OnAboutToFinish->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnAboutToFinish(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnFinished()
{
  if (ISFORM && PROPERTY_OnFinished->isVisible()){
    bool n = (PROPERTY_OnFinished->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnFinished(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnMutedChanged()
{
  if (ISFORM && PROPERTY_OnMutedChanged->isVisible()){
    bool n = (PROPERTY_OnMutedChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnMutedChanged(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnVolumeChanged()
{
  if (ISFORM && PROPERTY_OnVolumeChanged->isVisible()){
    bool n = (PROPERTY_OnVolumeChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnVolumeChanged(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnPlayingTitleChanged()
{
  if (ISFORM && PROPERTY_OnPlayingTitleChanged->isVisible()){
    bool n = (PROPERTY_OnPlayingTitleChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnPlayingTitleChanged(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnBufferStatus()
{
  if (ISFORM && PROPERTY_OnBufferStatus->isVisible()){
    bool n = (PROPERTY_OnBufferStatus->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnBufferStatus(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnTotalTimeChanged()
{
  if (ISFORM && PROPERTY_OnTotalTimeChanged->isVisible()){
    bool n = (PROPERTY_OnTotalTimeChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnTotalTimeChanged(n);
  }
}

void _propertywindow::SLOTPROPERTY_ScrollX()
{
  if (ISFORM){
    PROPERTY_ScrollX->lineedit()->setModified(false);
    int n = (PROPERTY_ScrollX->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ScrollX(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_ScrollY()
{
  if (ISFORM){
    PROPERTY_ScrollY->lineedit()->setModified(false);
    int n = (PROPERTY_ScrollY->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ScrollY(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_ScrollWidth()
{
  if (ISFORM){
    PROPERTY_ScrollWidth->lineedit()->setModified(false);
    int n = (PROPERTY_ScrollWidth->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ScrollWidth(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_ScrollHeight()
{
  if (ISFORM){
    PROPERTY_ScrollHeight->lineedit()->setModified(false);
    int n = (PROPERTY_ScrollHeight->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ScrollHeight(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_MultiPageHeight()
{
  if (ISFORM){
    PROPERTY_MultiPageHeight->lineedit()->setModified(false);
    int n = (PROPERTY_MultiPageHeight->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MultiPageHeight(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_MultiPageBorderTop()
{
  if (ISFORM){
    PROPERTY_MultiPageBorderTop->lineedit()->setModified(false);
    int n = (PROPERTY_MultiPageBorderTop->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MultiPageBorderTop(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_MultiPageBorderBottom()
{
  if (ISFORM){
    PROPERTY_MultiPageBorderBottom->lineedit()->setModified(false);
    int n = (PROPERTY_MultiPageBorderBottom->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MultiPageBorderBottom(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_MultiPageBorderLeft()
{
  if (ISFORM){
    PROPERTY_MultiPageBorderLeft->lineedit()->setModified(false);
    int n = (PROPERTY_MultiPageBorderLeft->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MultiPageBorderLeft(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_MultiPageBorderRight()
{
  if (ISFORM){
    PROPERTY_MultiPageBorderRight->lineedit()->setModified(false);
    int n = (PROPERTY_MultiPageBorderRight->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MultiPageBorderRight(n);
    f->repaint();
  }
}


void _propertywindow::SLOTPROPERTY_BorderTop()
{
  if (ISFORM/* && PROPERTY_BorderTop->lineedit()->isModified()*/){
    PROPERTY_BorderTop->lineedit()->setModified(false);
    int n = (PROPERTY_BorderTop->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_BorderTop(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_BorderBottom()
{
  if (ISFORM/* && PROPERTY_BorderBottom->lineedit()->isModified()*/){
    PROPERTY_BorderBottom->lineedit()->setModified(false);
    int n = (PROPERTY_BorderBottom->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_BorderBottom(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_BorderLeft()
{
  if (ISFORM/* && PROPERTY_BorderLeft->lineedit()->isModified()*/){
    PROPERTY_BorderLeft->lineedit()->setModified(false);
    int n = (PROPERTY_BorderLeft->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_BorderLeft(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_BorderRight()
{
  if (ISFORM /*&& PROPERTY_BorderRight->lineedit()->isModified()*/){
    PROPERTY_BorderRight->lineedit()->setModified(false);
    int n = (PROPERTY_BorderRight->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_BorderRight(n);
    f->repaint();
  }
}

void _propertywindow::SLOTPROPERTY_MinimumWidth()
{
  if (ISFORM /* &&!PROPERTY_MinimumWidth->text().isEmpty() && *//*PROPERTY_MinimumWidth->isModified()*/){
    PROPERTY_MinimumWidth->setModified(false);
    int n = (PROPERTY_MinimumWidth->text()).toInt();
    if (n == 0) PROPERTY_MinimumWidth->setText("");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MinimumWidth(n);
  }
}

void _propertywindow::SLOTPROPERTY_MinimumHeight()
{
  if (ISFORM /* &&!PROPERTY_MinimumHeight->text().isEmpty() && *//*PROPERTY_MinimumHeight->isModified()*/){
    PROPERTY_MinimumHeight->setModified(false);
    int n = (PROPERTY_MinimumHeight->text()).toInt();
    if (n == 0) PROPERTY_MinimumHeight->setText("");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MinimumHeight(n);
  }
}

void _propertywindow::SLOTPROPERTY_MaximumWidth()
{
  if (ISFORM /* &&!PROPERTY_MaximumWidth->text().isEmpty() && *//*PROPERTY_MaximumWidth->isModified()*/){
    PROPERTY_MaximumWidth->setModified(false);
    int n = (PROPERTY_MaximumWidth->text()).toInt();
    if (n == 0) PROPERTY_MaximumWidth->setText("");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MaximumWidth(n);
  }
}

void _propertywindow::SLOTPROPERTY_MaximumHeight()
{
  if (ISFORM /* &&!PROPERTY_MaximumHeight->text().isEmpty() && *//*PROPERTY_MaximumHeight->isModified()*/){
    PROPERTY_MaximumHeight->setModified(false);
    int n = (PROPERTY_MaximumHeight->text()).toInt();
    if (n == 0) PROPERTY_MaximumHeight->setText("");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MaximumHeight(n);
  }
}

void _propertywindow::SLOTPROPERTY_CSV()
{
  if (ISFORM /* &&!PROPERTY_CSV->text().isEmpty() && *//*PROPERTY_CSV->isModified()*/){
    PROPERTY_CSV->setModified(false);
    QString n = (PROPERTY_CSV->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CSV(n);
  }

}

void _propertywindow::SLOTPROPERTY_Tag()
{
  if (ISFORM /* &&!PROPERTY_Tag->text().isEmpty() && *//*PROPERTY_Tag->isModified()*/){
    PROPERTY_Tag->setModified(false);
    QString n = (PROPERTY_Tag->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Tag(n);
  }

  else if (ISMENUBAR/* && !PROPERTY_Tag->text().isEmpty() && *//*PROPERTY_Tag->isModified()*/){
    PROPERTY_Tag->setModified(false);
    QString n = (PROPERTY_Tag->text());
    EXTERN_my_menubar->controls_SETPROPERTY_Tag(n);
  }

  else if (ISTOOLBAR /*&& !PROPERTY_Tag->text().isEmpty() && *//*PROPERTY_Tag->isModified()*/){
    PROPERTY_Tag->setModified(false);
    QString n = (PROPERTY_Tag->text());
    EXTERN_my_toolbar->controls_SETPROPERTY_Tag(n);
  }

}

void _propertywindow::SLOTPROPERTY_MenuBarRole()
{

   if (ISMENUBAR && PROPERTY_MenuBarRole->isVisible()){
    QString s = PROPERTY_MenuBarRole->text();
    EXTERN_my_menubar->controls_SETPROPERTY_MenuBarRole(s);
  }

}

void _propertywindow::SLOTPROPERTY_Data()
{

  if (ISMENUBAR){
    PROPERTY_Data->setModified(false);
    QString n = (PROPERTY_Data->text());
    EXTERN_my_menubar->controls_SETPROPERTY_Data(n);
  }

}

void _propertywindow::SLOTPROPERTY_TableView()
{
  if (ISFORM && PROPERTY_TableView->isVisible()){
    bool n = (PROPERTY_TableView->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_TableView(n);
  }
}

void _propertywindow::SLOTPROPERTY_BoxIndex()
{
  /*
  if (ISFORM && !PROPERTY_BoxIndex->text().isEmpty() && PROPERTY_BoxIndex->isModified()){
    PROPERTY_BoxIndex->setModified(false);
    int n = (PROPERTY_BoxIndex->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_BoxIndex(n);
  }
  */
}

void _propertywindow::SLOTPROPERTY_BoxX()
{
  if (ISFORM /* &&!PROPERTY_BoxX->text().isEmpty() && *//*PROPERTY_BoxX->isModified()*/){
    PROPERTY_BoxX->setModified(false);
    int n = (PROPERTY_BoxX->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_BoxX(n);
  }
}

void _propertywindow::SLOTPROPERTY_BoxY()
{
  if (ISFORM /* &&!PROPERTY_BoxY->text().isEmpty() && *//*PROPERTY_BoxY->isModified()*/){
    PROPERTY_BoxY->setModified(false);
    int n = (PROPERTY_BoxY->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_BoxY(n);
  }
}

void _propertywindow::SLOTPROPERTY_SplitIndex()
{
  if (ISFORM /* &&!PROPERTY_SplitIndex->text().isEmpty() && *//*PROPERTY_SplitIndex->isModified()*/){
    PROPERTY_SplitIndex->setModified(false);
    int n = (PROPERTY_SplitIndex->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_SplitIndex(n);
  }
}

void _propertywindow::SLOTPROPERTY_StopOnClose()
{
  if (ISFORM && PROPERTY_StopOnClose->isVisible()){
    bool n = (PROPERTY_StopOnClose->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_StopOnClose(n);
  }
}

void _propertywindow::SLOTPROPERTY_Scale()
{
  if (ISFORM && PROPERTY_Scale->isVisible()){
    bool n = (PROPERTY_Scale->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Scale(n);
  }
}
/*
void _propertywindow::SLOTPROPERTY_FormCentered()
{
  if (ISFORM && PROPERTY_FormCentered->isVisible()){
    bool n = (PROPERTY_FormCentered->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FormCentered(n);
  }
}

void _propertywindow::SLOTPROPERTY_FormScaled()
{
  if (ISFORM && PROPERTY_FormScaled->isVisible()){
    bool n = (PROPERTY_FormScaled->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FormScaled(n);
  }
}
*/
void _propertywindow::SLOTPROPERTY_DragDrop()
{
  if (ISFORM && PROPERTY_DragDrop->isVisible()){
    bool n = (PROPERTY_DragDrop->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_DragDrop(n);
  }
}

void _propertywindow::SLOTPROPERTY_FocusPolicy()
{
  if (ISFORM && PROPERTY_FocusPolicy->isVisible()){
    QString s = PROPERTY_FocusPolicy->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FocusPolicy(s);
  }
}

void _propertywindow::SLOTPROPERTY_FocusProxy()
{
  if (ISFORM && PROPERTY_FocusProxy->isVisible()){
    QString s = PROPERTY_FocusProxy->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FocusProxy(s);
  }
}

void _propertywindow::SLOTPROPERTY_FocusOrder()
{
  if (ISFORM && PROPERTY_FocusOrder->isModified()){
    PROPERTY_FocusOrder->setModified(false);
    int n = (PROPERTY_FocusOrder->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FocusOrder(n);
  }
}

void _propertywindow::SLOTPROPERTY_FontName()
{
  if (ISFORM && PROPERTY_FontName->isVisible()){
    QString s = PROPERTY_FontName->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FontName(s);
  }
}

void _propertywindow::SLOTPROPERTY_Opacity()
{

  if (ISFORM && PROPERTY_Opacity->isVisible()){
    QString s = PROPERTY_Opacity->currentText();
    int n = s.toInt();
    if (n == 0) PROPERTY_Opacity->setCurrentIndex(0);
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Opacity(n);
  }

}

void _propertywindow::SLOTPROPERTY_FontSize()
{

  if (ISFORM && PROPERTY_FontSize->isVisible()){
    QString s = PROPERTY_FontSize->currentText();
    int n = s.toInt();
    if (n == 0) PROPERTY_FontSize->setCurrentIndex(0);
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FontSize(n);
  }

}

void _propertywindow::SLOTPROPERTY_FontBold()
{
  if (ISFORM && PROPERTY_FontBold->isVisible()){
    bool n = (PROPERTY_FontBold->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FontBold(n);
  }
}

void _propertywindow::SLOTPROPERTY_FontItalic()
{
  if (ISFORM && PROPERTY_FontItalic->isVisible()){
    bool n = (PROPERTY_FontItalic->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FontItalic(n);
  }
}

void _propertywindow::SLOTPROPERTY_FontUnderline()
{
  if (ISFORM && PROPERTY_FontUnderline->isVisible()){
    bool n = (PROPERTY_FontUnderline->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FontUnderline(n);
  }
}

void _propertywindow::SLOTPROPERTY_FontColor()
{
  if (ISFORM && PROPERTY_FontColor->isVisible()){
    QString s = PROPERTY_FontColor->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FontColor(s);
  }
}

void _propertywindow::SLOTPROPERTY_Palette()
{
  if (ISFORM){
    PROPERTY_Palette->setModified(false);
    QString n = (PROPERTY_Palette->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Palette(n);
  }
}

void _propertywindow::SLOTPROPERTY_StatusTip()
{
  if (ISFORM /* &&!PROPERTY_StatusTip->text().isEmpty() && *//*PROPERTY_StatusTip->isModified()*/){
    PROPERTY_StatusTip->setModified(false);
    QString n = (PROPERTY_StatusTip->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_StatusTip(n);
  }

  else if (ISMENUBAR/* && !PROPERTY_StatusTip->text().isEmpty() && *//*PROPERTY_StatusTip->isModified()*/){
    PROPERTY_StatusTip->setModified(false);
    QString n = (PROPERTY_StatusTip->text());
    EXTERN_my_menubar->controls_SETPROPERTY_StatusTip(n);
  }

  else if (ISTOOLBAR /*&& !PROPERTY_StatusTip->text().isEmpty() && *//*PROPERTY_StatusTip->isModified()*/){
    PROPERTY_StatusTip->setModified(false);
    QString n = (PROPERTY_StatusTip->text());
    EXTERN_my_toolbar->controls_SETPROPERTY_StatusTip(n);
  }
}

void _propertywindow::SLOTPROPERTY_ToolTip()
{
  if (ISFORM /* &&!PROPERTY_ToolTip->text().isEmpty() && *//*PROPERTY_ToolTip->isModified()*/){
    PROPERTY_ToolTip->setModified(false);
    QString n = (PROPERTY_ToolTip->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ToolTip(n);
  }

  else if (ISTOOLBAR /*&& !PROPERTY_ToolTip->text().isEmpty() && *//*PROPERTY_ToolTip->isModified()*/){
    PROPERTY_ToolTip->setModified(false);
    QString n = (PROPERTY_ToolTip->text());
    EXTERN_my_toolbar->controls_SETPROPERTY_ToolTip(n);
  }


}

void _propertywindow::SLOTPROPERTY_StyleSheet()
{
  if (ISFORM /* &&!PROPERTY_StyleSheet->text().isEmpty() && *//*PROPERTY_StyleSheet->isModified()*/){
    PROPERTY_StyleSheet->setModified(false);
    QString n = (PROPERTY_StyleSheet->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_StyleSheet(n);
  }

}

void _propertywindow::SLOTPROPERTY_WhatsThis()
{
  if (ISFORM /* &&!PROPERTY_WhatsThis->text().isEmpty() && *//*PROPERTY_WhatsThis->isModified()*/){
    PROPERTY_WhatsThis->setModified(false);
    QString n = (PROPERTY_WhatsThis->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_WhatsThis(n);
  }

  else if (ISTOOLBAR /*&& !PROPERTY_WhatsThis->text().isEmpty() && *//*PROPERTY_WhatsThis->isModified()*/){
    PROPERTY_WhatsThis->setModified(false);
    QString n = (PROPERTY_WhatsThis->text());
    EXTERN_my_toolbar->controls_SETPROPERTY_WhatsThis(n);
  }

}

void _propertywindow::SLOTPROPERTY_Layout()
{
  if (ISFORM && PROPERTY_Layout->isVisible()){
    QString s = PROPERTY_Layout->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Layout(s);
  }
}

void _propertywindow::SLOTPROPERTY_Flag()
{
  if (ISFORM && PROPERTY_Flag->isVisible()){
    QString s = PROPERTY_Flag->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Flag(s);
  }
}

void _propertywindow::SLOTPROPERTY_ArrowType()
{
  if (ISTOOLBAR && PROPERTY_ArrowType->isVisible()){
    QString s = PROPERTY_ArrowType->text();
    EXTERN_my_toolbar->controls_SETPROPERTY_ArrowType(s);
  }
}

void _propertywindow::SLOTPROPERTY_PopupMode()
{
  if (ISTOOLBAR && PROPERTY_PopupMode->isVisible()){
    QString s = PROPERTY_PopupMode->text();
    EXTERN_my_toolbar->controls_SETPROPERTY_PopupMode(s);
  }

}

void _propertywindow::SLOTPROPERTY_ToolBarRole()
{
  if (ISTOOLBAR && PROPERTY_ToolBarRole->isVisible()){
    QString s = PROPERTY_ToolBarRole->text();
    EXTERN_my_toolbar->controls_SETPROPERTY_ToolBarRole(s);
  }
}

void _propertywindow::SLOTPROPERTY_Dock()
{
  if (ISFORM && PROPERTY_Dock->isVisible()){
    QString s = PROPERTY_Dock->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Dock(s);
  }
}

void _propertywindow::SLOTPROPERTY_ShowMode()
{
  if (ISFORM && PROPERTY_ShowMode->isVisible()){
    QString s = PROPERTY_ShowMode->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ShowMode(s);
  }
}



void _propertywindow::SLOTPROPERTY_SQLControls()
{
  if (ISFORM && PROPERTY_SQLControls->isVisible()){
    QString s = PROPERTY_SQLControls->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_SQLControls(s);
  }
}
/*
void _propertywindow::SLOTPROPERTY_IconCaption()
{
  if (ISFORM && PROPERTY_IconCaption->isModified()){
    PROPERTY_IconCaption->setModified(false);
    QString n = (PROPERTY_IconCaption->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_IconCaption(n);
  }

}
*/
void _propertywindow::SLOTPROPERTY_Modal()
{
  if (ISFORM && PROPERTY_Modal->isVisible()){
    bool n = (PROPERTY_Modal->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Modal(n);
  }
}



void _propertywindow::SLOTPROPERTY_TimerInterval()
{
  if (ISFORM /* &&!PROPERTY_TimerInterval->text().isEmpty() && *//*PROPERTY_TimerInterval->isModified()*/){
    PROPERTY_TimerInterval->setModified(false);
    int n = (PROPERTY_TimerInterval->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_TimerInterval(n);
  }
}


void _propertywindow::SLOTPROPERTY_Shadow()
{
  if (ISFORM && PROPERTY_Shadow->isVisible()){
    bool n = (PROPERTY_Shadow->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Shadow(n);
  }
}

void _propertywindow::SLOTPROPERTY_Shape()
{
  if (ISFORM && PROPERTY_Shape->isVisible()){
    bool n = (PROPERTY_Shape->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Shape(n);
  }
}

void _propertywindow::SLOTPROPERTY_OpenLinks()
{
  if (ISFORM && PROPERTY_OpenLinks->isVisible()){
    bool n = (PROPERTY_OpenLinks->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OpenLinks(n);
  }
}

void _propertywindow::SLOTPROPERTY_Icon()
{
  if (ISFORM && PROPERTY_Icon->isVisible()){
    QString s = PROPERTY_Icon->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Icon(s);
  }

  else if (ISMENUBAR && PROPERTY_Icon->isVisible()){
    QString s = PROPERTY_Icon->lineedit()->text();
    EXTERN_my_menubar->controls_SETPROPERTY_Icon(s);
  }

  else if (ISTOOLBAR && PROPERTY_Icon->isVisible()){
    QString s = PROPERTY_Icon->lineedit()->text();
    EXTERN_my_toolbar->controls_SETPROPERTY_Icon(s);
  }

}

void _propertywindow::SLOTPROPERTY_InputControl()
{
  if (ISFORM /* &&!PROPERTY_InputControl->text().isEmpty() && *//*PROPERTY_InputControl->isModified()*/){
    PROPERTY_InputControl->setModified(false);
    QString n = (PROPERTY_InputControl->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_InputControl(n);
  }

}

void _propertywindow::SLOTPROPERTY_Space()
{
  if (ISFORM /* &&!PROPERTY_Space->text().isEmpty() && *//*PROPERTY_Space->isModified()*/){
    PROPERTY_Space->setModified(false);
    int n = (PROPERTY_Space->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Space(n);
  }
}

void _propertywindow::SLOTPROPERTY_Border()
{
  if (ISFORM /* &&!PROPERTY_Border->text().isEmpty() && *//*PROPERTY_Border->isModified()*/){
    PROPERTY_Border->setModified(false);
    int n = (PROPERTY_Border->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Border(n);
  }
}

void _propertywindow::SLOTPROPERTY_Flip()
{
  if (ISFORM && PROPERTY_Flip->isVisible()){
    bool n = (PROPERTY_Flip->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Flip(n);
  }
}

void _propertywindow::SLOTPROPERTY_Flat()
{
  if (ISFORM && PROPERTY_Flat->isVisible()){
    bool n = (PROPERTY_Flat->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Flat(n);
  }
}

void _propertywindow::SLOTPROPERTY_Key()
{
  if (ISFORM && PROPERTY_Key->isVisible()){
    QString s = PROPERTY_Key->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Key(s);
  }

  else if (ISMENUBAR && PROPERTY_Key->isVisible()){
    QString s = PROPERTY_Key->text();
    EXTERN_my_menubar->controls_SETPROPERTY_Key(s);
  }
}

void _propertywindow::SLOTPROPERTY_IntegerMaximum()
{
  if (ISFORM /* &&!PROPERTY_IntegerMaximum->text().isEmpty() && *//*PROPERTY_IntegerMaximum->isModified()*/){
    PROPERTY_IntegerMaximum->setModified(false);
    int n = (PROPERTY_IntegerMaximum->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_IntegerMaximum(n);
  }
}

void _propertywindow::SLOTPROPERTY_IntegerMinimum()
{
  if (ISFORM /* &&!PROPERTY_IntegerMinimum->text().isEmpty() && *//*PROPERTY_IntegerMinimum->isModified()*/){
    PROPERTY_IntegerMinimum->setModified(false);
    int n = (PROPERTY_IntegerMinimum->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_IntegerMinimum(n);
  }
}

void _propertywindow::SLOTPROPERTY_Completer()
{
  if (ISFORM /* &&!PROPERTY_Completer->text().isEmpty() && *//*PROPERTY_Completer->isModified()*/){
    PROPERTY_Completer->setModified(false);
    QString n = (PROPERTY_Completer->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Completer(n);
  }

}

void _propertywindow::SLOTPROPERTY_ValidatorDouble()
{
  if (ISFORM && PROPERTY_ValidatorDouble->isVisible()){
    bool n = (PROPERTY_ValidatorDouble->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ValidatorDouble(n);
  }
}

void _propertywindow::SLOTPROPERTY_ValidatorInteger()
{
  if (ISFORM && PROPERTY_ValidatorInteger->isVisible()){
    bool n = (PROPERTY_ValidatorInteger->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ValidatorInteger(n);
  }
}

void _propertywindow::SLOTPROPERTY_ValidatorRegEx()
{
  if (ISFORM /* &&!PROPERTY_ValidatorRegEx->text().isEmpty() && *//*PROPERTY_ValidatorRegEx->isModified()*/){
    PROPERTY_ValidatorRegEx->setModified(false);
    QString n = (PROPERTY_ValidatorRegEx->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ValidatorRegEx(n);
  }

}

void _propertywindow::SLOTPROPERTY_ValidatorRegEx2()
{
  if (ISFORM /* &&!PROPERTY_ValidatorRegEx2->text().isEmpty() && *//*PROPERTY_ValidatorRegEx2->isModified()*/){
    PROPERTY_ValidatorRegEx2->setModified(false);
    QString n = (PROPERTY_ValidatorRegEx2->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ValidatorRegEx2(n);
  }

}

void _propertywindow::SLOTPROPERTY_DoubleEntry()
{
  if (ISFORM && PROPERTY_DoubleEntry->isVisible()){
    bool n = (PROPERTY_DoubleEntry->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_DoubleEntry(n);
  }
}

void _propertywindow::SLOTPROPERTY_InsertPolicy()
{
  if (ISFORM && PROPERTY_InsertPolicy->isVisible()){
    QString s = PROPERTY_InsertPolicy->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_InsertPolicy(s);
  }
}

void _propertywindow::SLOTPROPERTY_Editable()
{
  if (ISFORM && PROPERTY_Editable->isVisible()){
    bool n = (PROPERTY_Editable->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Editable(n);
  }
}

void _propertywindow::SLOTPROPERTY_MaximumVisible()
{
  if (ISFORM /* &&!PROPERTY_MaximumVisible->text().isEmpty() && *//*PROPERTY_MaximumVisible->isModified()*/){
    PROPERTY_MaximumVisible->setModified(false);
    int n = (PROPERTY_MaximumVisible->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MaximumVisible(n);
  }
}

void _propertywindow::SLOTPROPERTY_Sorted()
{
  if (ISFORM && PROPERTY_Sorted->isVisible()){
    bool n = (PROPERTY_Sorted->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Sorted(n);
  }
}

void _propertywindow::SLOTPROPERTY_StringMaximum()
{
  if (ISFORM /* &&!PROPERTY_StringMaximum->text().isEmpty() && *//*PROPERTY_StringMaximum->isModified()*/){
    PROPERTY_StringMaximum->setModified(false);
    QString n = (PROPERTY_StringMaximum->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_StringMaximum(n);
  }

}

void _propertywindow::SLOTPROPERTY_StringMinimum()
{
  if (ISFORM /* &&!PROPERTY_StringMinimum->text().isEmpty() && *//*PROPERTY_StringMinimum->isModified()*/){
    PROPERTY_StringMinimum->setModified(false);
    QString n = (PROPERTY_StringMinimum->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_StringMinimum(n);
  }

}

void _propertywindow::SLOTPROPERTY_Format()
{
  if (ISFORM /* &&!PROPERTY_Format->text().isEmpty() && *//*PROPERTY_Format->isModified()*/){
    PROPERTY_Format->setModified(false);
    QString n = (PROPERTY_Format->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Format(n);
  }

}

void _propertywindow::SLOTPROPERTY_PopUp()
{
  if (ISFORM && PROPERTY_PopUp->isVisible()){
    bool n = (PROPERTY_PopUp->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_PopUp(n);
  }
}

void _propertywindow::SLOTPROPERTY_ScrollBar()
{
  if (ISFORM && PROPERTY_ScrollBar->isVisible()){
    QString s = PROPERTY_ScrollBar->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ScrollBar(s);
  }
}

void _propertywindow::SLOTPROPERTY_MouseDownImage()
{
  if (ISFORM && PROPERTY_MouseDownImage->isVisible()){
    QString s = PROPERTY_MouseDownImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MouseDownImage(s);
  }
}

void _propertywindow::SLOTPROPERTY_MouseUpImage()
{
  if (ISFORM && PROPERTY_MouseUpImage->isVisible()){
    QString s = PROPERTY_MouseUpImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MouseUpImage(s);
  }
}

void _propertywindow::SLOTPROPERTY_EnabledImage()
{
  if (ISFORM && PROPERTY_EnabledImage->isVisible()){
    QString s = PROPERTY_EnabledImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_EnabledImage(s);
  }
}


void _propertywindow::SLOTPROPERTY_CheckMouseDownImage()
{
  if (ISFORM && PROPERTY_CheckMouseDownImage->isVisible()){
    QString s = PROPERTY_CheckMouseDownImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CheckMouseDownImage(s);
  }
}

void _propertywindow::SLOTPROPERTY_CheckMouseUpImage()
{
  if (ISFORM && PROPERTY_CheckMouseUpImage->isVisible()){
    QString s = PROPERTY_CheckMouseUpImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CheckMouseUpImage(s);
  }
}

void _propertywindow::SLOTPROPERTY_CheckEnabledImage()
{
  if (ISFORM && PROPERTY_CheckEnabledImage->isVisible()){
    QString s = PROPERTY_CheckEnabledImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CheckEnabledImage(s);
  }
}

void _propertywindow::SLOTPROPERTY_MouseDownSound()
{
  if (ISFORM && PROPERTY_MouseDownSound->isVisible()){
    QString s = PROPERTY_MouseDownSound->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MouseDownSound(s);
  }
}

void _propertywindow::SLOTPROPERTY_MouseUpSound()
{
  if (ISFORM && PROPERTY_MouseUpSound->isVisible()){
    QString s = PROPERTY_MouseUpSound->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MouseUpSound(s);
  }
}

void _propertywindow::SLOTPROPERTY_HomeURL()
{
  if (ISFORM && PROPERTY_HomeURL->isVisible()){
    QString s = PROPERTY_HomeURL->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_HomeURL(s);
  }
}





void _propertywindow::SLOTPROPERTY_Name()
{
  if (ISFORM && !PROPERTY_Name->text().isEmpty() /*&& PROPERTY_Name->isModified()*/){
    PROPERTY_Name->setModified(false);
    QString n = (PROPERTY_Name->text());
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Name(n);
  }

  if (ISMENUBAR && !PROPERTY_Name->text().isEmpty() /*&& PROPERTY_Name->isModified()*/){
    PROPERTY_Name->setModified(false);
    QString n = (PROPERTY_Name->text());
    EXTERN_my_menubar->controls_SETPROPERTY_Name(n);
  }

  else if (ISTOOLBAR && !PROPERTY_Name->text().isEmpty() /*&& PROPERTY_Name->isModified()*/){
    PROPERTY_Name->setModified(false);
    QString n = (PROPERTY_Name->text());
    EXTERN_my_toolbar->controls_SETPROPERTY_Name(n);
  }
}

void _propertywindow::SLOTPROPERTY_X()
{

  if (ISFORM && !PROPERTY_X->lineedit()->text().isEmpty()/* && PROPERTY_X->lineedit()->isModified()*/){
    PROPERTY_X->lineedit()->setModified(false);
    int n = (PROPERTY_X->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_X(n);
  }
/*
  else if (EXTERN_my_report && !PROPERTY_X->lineedit()->text().isEmpty() && PROPERTY_X->lineedit()->isModified()){
    PROPERTY_X->lineedit()->setModified(false);
    int n = (PROPERTY_X->lineedit()->text()).toInt();
    EXTERN_my_report->controls_SETPROPERTY_X(n);
  }*/
}

void _propertywindow::SLOTPROPERTY_Y()
{

  if (ISFORM && !PROPERTY_Y->lineedit()->text().isEmpty() /*&& PROPERTY_Y->lineedit()->isModified()*/){
    PROPERTY_Y->lineedit()->setModified(false);
    int n = (PROPERTY_Y->lineedit()->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Y(n);
  }
/*
  else if (EXTERN_my_report && !PROPERTY_Y->lineedit()->text().isEmpty() && PROPERTY_Y->lineedit()->isModified()){
    PROPERTY_Y->lineedit()->setModified(false);
    int n = (PROPERTY_Y->lineedit()->text()).toInt();
    EXTERN_my_report->controls_SETPROPERTY_Y(n);
  }*/

}

void _propertywindow::SLOTPROPERTY_Width()
{

  if (ISFORM && PROPERTY_Width->lineedit()->isVisible()){
    if (!PROPERTY_Width->lineedit()->text().isEmpty() /*&& PROPERTY_Width->lineedit()->isModified()*/){
      PROPERTY_Width->lineedit()->setModified(false);
      int n = (PROPERTY_Width->lineedit()->text()).toInt();
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_Width(n);
    }
  }
/*
  else if (EXTERN_my_report && PROPERTY_Width->lineedit()->isVisible()){
    if (!PROPERTY_Width->lineedit()->text().isEmpty() && PROPERTY_Width->lineedit()->isModified()){
      PROPERTY_Width->lineedit()->setModified(false);
      int n = (PROPERTY_Width->lineedit()->text()).toInt();
      EXTERN_my_report->controls_SETPROPERTY_Width(n);
    }
  }*/

}

void _propertywindow::SLOTPROPERTY_Height()
{  

  if (ISFORM && PROPERTY_Height->lineedit()->isVisible()){
    if (!PROPERTY_Height->lineedit()->text().isEmpty() /*&& PROPERTY_Height->lineedit()->isModified()*/){
      PROPERTY_Height->lineedit()->setModified(false);
      int n = (PROPERTY_Height->lineedit()->text()).toInt();
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_Height(n);
    }
  }
/*
  else if (EXTERN_my_report && PROPERTY_Height->lineedit()->isVisible()){
    if (!PROPERTY_Height->lineedit()->text().isEmpty() && PROPERTY_Height->lineedit()->isModified()){
      PROPERTY_Height->lineedit()->setModified(false);
      int n = (PROPERTY_Height->lineedit()->text()).toInt();
      EXTERN_my_report->controls_SETPROPERTY_Height(n);
    }
  }*/
}

void _propertywindow::SLOTPROPERTY_Caption()
{



  if (ISFORM && PROPERTY_Caption->isVisible()){
    //if (/*!PROPERTY_Caption->text().isEmpty() && *//*PROPERTY_Caption->isModified()*/)
    {
      QString n = (PROPERTY_Caption->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_Caption(n);
    }
  }

  else if (ISMENUBAR && PROPERTY_Caption->isVisible()){
    //if (/*!PROPERTY_Caption->text().isEmpty() && *//*PROPERTY_Caption->isModified()*/)
    {
      QString n = (PROPERTY_Caption->text());
      EXTERN_my_menubar->controls_SETPROPERTY_Caption(n);
    }
  }
  
  else if (ISTOOLBAR && PROPERTY_Caption->isVisible()){
    //if (/*!PROPERTY_Caption->text().isEmpty() && *//*PROPERTY_Caption->isModified()*/)
    {
      QString n = (PROPERTY_Caption->text());
      EXTERN_my_toolbar->controls_SETPROPERTY_Caption(n);
    }
  }
}
/*
void _propertywindow::SLOTPROPERTY_BackColor()
{

  if (ISFORM && PROPERTY_BackColor->isVisible()){
    if (ISFORM && PROPERTY_BackColor->SETPROPERTY()){
      QString s = PROPERTY_BackColor->lineedit()->text();
      QString n = s;
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_BackColor(n);
    }
  }

}

void _propertywindow::SLOTPROPERTY_BackImage2()
{

  SLOTPROPERTY_BackImage(true);

}

void _propertywindow::SLOTPROPERTY_BackImage(bool b)
{  

  if (ISFORM && PROPERTY_BackImage->isVisible()){
    QString s = PROPERTY_BackImage->lineedit()->text();
    QString n = s;   
    if (!b || s.length()){
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_BackImage(n);
    }
  }

}
*/


void _propertywindow::SLOTPROPERTY_IntegerValue()
{

  if (ISFORM && PROPERTY_IntegerValue->isVisible()){
    QString s = PROPERTY_IntegerValue->text();
    //QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_IntegerValue(s.toInt());
  }

}

void _propertywindow::SLOTPROPERTY_PortName()
{
  if (ISFORM && PROPERTY_PortName->isVisible()){
    QString s = PROPERTY_PortName->currentText();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_PortName(n);
  }
}

void _propertywindow::SLOTPROPERTY_BaudRate()
{
  if (ISFORM && PROPERTY_BaudRate->isVisible()){
    QString s = PROPERTY_BaudRate->currentText();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_BaudRate(n);
  }
}

void _propertywindow::SLOTPROPERTY_DataBits()
{
  if (ISFORM && PROPERTY_DataBits->isVisible()){
    QString s = PROPERTY_DataBits->currentText();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_DataBits(n);
  }
}

void _propertywindow::SLOTPROPERTY_FlowControl()
{
  if (ISFORM && PROPERTY_FlowControl->isVisible()){
    QString s = PROPERTY_FlowControl->currentText();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_FlowControl(n);
  }
}

void _propertywindow::SLOTPROPERTY_Parity()
{
  if (ISFORM && PROPERTY_Parity->isVisible()){
    QString s = PROPERTY_Parity->currentText();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Parity(n);
  }
}

void _propertywindow::SLOTPROPERTY_StopBits()
{
  if (ISFORM && PROPERTY_StopBits->isVisible()){
    QString s = PROPERTY_StopBits->currentText();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_StopBits(n);
  }
}

void _propertywindow::SLOTPROPERTY_TimeoutMillisec()
{
  if (ISFORM && PROPERTY_TimeoutMillisec->isVisible()){
    QString s = PROPERTY_TimeoutMillisec->text();
    int n = s.toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_TimeOutMillisec(n);
  }
}

void _propertywindow::SLOTPROPERTY_PollingInterval()
{
  if (ISFORM && PROPERTY_PollingInterval->isVisible()){
    QString s = PROPERTY_PollingInterval->text();
    int n = s.toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_PollingInterval(n);
  }
}

void _propertywindow::SLOTPROPERTY_Cursor()
{

  if (ISFORM && PROPERTY_Cursor->isVisible()){
    QString s = PROPERTY_Cursor->currentText();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Cursor(n);
  }

}

void _propertywindow::SLOTPROPERTY_CursorAnimation()
{

  if (ISFORM && PROPERTY_CursorAnimation->isVisible()){
    QString s = PROPERTY_CursorAnimation->currentText();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CursorAnimation(n);
  }

}



void _propertywindow::SLOTPROPERTY_Enabled()
{

  if (ISFORM && PROPERTY_Enabled->isVisible()){
    bool n = (PROPERTY_Enabled->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Enabled(n);
  }

  else if (ISMENUBAR && PROPERTY_Enabled->isVisible()){
    bool n = (PROPERTY_Enabled->currentText() == "True");
    EXTERN_my_menubar->controls_SETPROPERTY_Enabled(n);
  }

  else if (ISTOOLBAR && PROPERTY_Enabled->isVisible()){
    bool n = (PROPERTY_Enabled->currentText() == "True");
    EXTERN_my_toolbar->controls_SETPROPERTY_Enabled(n);
  }
}

void _propertywindow::SLOTPROPERTY_Checked()
{

  if (ISFORM && PROPERTY_Checked->isVisible()){
    bool n = (PROPERTY_Checked->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Checked(n);
  }

  else if (ISMENUBAR && PROPERTY_Checked->isVisible()){
    bool n = (PROPERTY_Checked->currentText() == "True");
    EXTERN_my_menubar->controls_SETPROPERTY_Checked(n);
  }

  else if (ISTOOLBAR && PROPERTY_Checked->isVisible()){
    bool n = (PROPERTY_Checked->currentText() == "True");
    EXTERN_my_toolbar->controls_SETPROPERTY_Checked(n);
  }
}

void _propertywindow::SLOTPROPERTY_CheckableExclusive()
{

  if (ISFORM && PROPERTY_CheckableExclusive->isVisible()){
    bool n = (PROPERTY_CheckableExclusive->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CheckableExclusive(n);
  }

}



void _propertywindow::SLOTPROPERTY_Visible()
{

  if (ISFORM && PROPERTY_Visible->isVisible()){
    bool n = (PROPERTY_Visible->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Visible(n);
  }

  else if (ISMENUBAR && PROPERTY_Visible->isVisible()){
    bool n = (PROPERTY_Visible->currentText() == "True");
    EXTERN_my_menubar->controls_SETPROPERTY_Visible(n);
  }

  else if (ISTOOLBAR && PROPERTY_Visible->isVisible()){
    bool n = (PROPERTY_Visible->currentText() == "True");
    EXTERN_my_toolbar->controls_SETPROPERTY_Visible(n);
  }
/*
  if (ISMENUBAR && PROPERTY_Visible->isVisible()){
    bool n = (PROPERTY_Visible->currentText() == "True");
    EXTERN_my_menubar->controls_SETPROPERTY_Visible(n);
  }*/
}

void _propertywindow::SLOTPROPERTY_Resizable()
{

  if (ISFORM && PROPERTY_Resizable->isVisible()){
    bool n = (PROPERTY_Resizable->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Resizable(n);
  }

}

void _propertywindow::SLOTPROPERTY_ResizableSmaller()
{
  if (ISFORM && PROPERTY_ResizableSmaller->isVisible()){
    bool n = (PROPERTY_ResizableSmaller->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ResizableSmaller(n);
  }
}

void _propertywindow::SLOTPROPERTY_ResizableBigger()
{
  if (ISFORM && PROPERTY_ResizableBigger->isVisible()){
    bool n = (PROPERTY_ResizableBigger->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ResizableBigger(n);
  }
}




void _propertywindow::SLOTPROPERTY_Separator()
{

  if (ISFORM && PROPERTY_Separator->isVisible()){
    bool n = (PROPERTY_Separator->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Separator(n);
  }

  else if (ISMENUBAR && PROPERTY_Separator->isVisible()){
    bool n = (PROPERTY_Separator->currentText() == "True");
    EXTERN_my_menubar->controls_SETPROPERTY_Separator(n);
  }

  else if (ISTOOLBAR && PROPERTY_Separator->isVisible()){
    bool n = (PROPERTY_Separator->currentText() == "True");
    EXTERN_my_toolbar->controls_SETPROPERTY_Separator(n);
  }
}

void _propertywindow::SLOTPROPERTY_WordWrap()
{

  if (ISFORM && PROPERTY_WordWrap->isVisible()){
    bool n = (PROPERTY_WordWrap->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_WordWrap(n);
  }

}

void _propertywindow::SLOTPROPERTY_ReadOnly()
{

  if (ISFORM && PROPERTY_ReadOnly->isVisible()){
    bool n = (PROPERTY_ReadOnly->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ReadOnly(n);
  }

}

void _propertywindow::SLOTPROPERTY_Alignment()
{

  if (ISFORM && PROPERTY_Alignment->isVisible()){
    QString s = PROPERTY_Alignment->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Alignment(s);
  }

}

void _propertywindow::SLOTPROPERTY_EchoMode()
{

  if (ISFORM && PROPERTY_EchoMode->isVisible()){
    QString s = PROPERTY_EchoMode->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_EchoMode(s);
  }

}


void _propertywindow::SLOTPROPERTY_Orientation()
{

//  ((f = EXTERN_my_form)
    
/*
  QMdiSubWindow *ww = EXTERN_my_mainwindow->workspace->currentSubWindow();
  QMdiSubWindow *ww2 = EXTERN_my_mainwindow->workspace->activeSubWindow();

  QWidget *w = ww->widget();

  _form *f = qobject_cast<_form *>(w);

    //activeSubWindow()->widget() : 0)
*/
  if (ISFORM){
    if (PROPERTY_Orientation->isVisible()){
    QString s = PROPERTY_Orientation->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Orientation(s);
  }
  }

}


void _propertywindow::SLOTPROPERTY_Feature()
{

  if (ISFORM && PROPERTY_Feature->isVisible()){
    QString s = PROPERTY_Feature->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Feature(s);
  }

}

void _propertywindow::SLOTPROPERTY_SQL()
{
  if (ISFORM && PROPERTY_SQL->isVisible()){
    //if (/*!PROPERTY_SQLName->text().isEmpty() && *//*PROPERTY_SQL->isModified()*/)
    {
      QString n = (PROPERTY_SQL->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_SQL(n);
    }
  }
}

void _propertywindow::SLOTPROPERTY_SQLName()
{
  if (ISFORM && PROPERTY_SQLName->isVisible()){
    //if (/*!PROPERTY_SQLName->text().isEmpty() && *//*PROPERTY_SQLName->isModified()*/)
    {
      QString n = (PROPERTY_SQLName->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_SQLName(n);
      f->repaint();
    }
  }
}

void _propertywindow::SLOTPROPERTY_SQLRelation()
{
  if (ISFORM && PROPERTY_SQLRelation->isVisible()){
    //if (PROPERTY_SQLRelation->isModified()*/)
    {
      QString n = (PROPERTY_SQLRelation->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_SQLRelation(n);
    }
  }
}


void _propertywindow::SLOTPROPERTY_TableViewCaption()
{
  if (ISFORM && PROPERTY_TableViewCaption->isVisible()){
    //if (PROPERTY_TableViewCaption->isModified()*/)
    {
      QString n = (PROPERTY_TableViewCaption->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_TableViewCaption(n);
    }
  }
}

void _propertywindow::SLOTPROPERTY_TableViewSort()
{
  if (ISFORM && PROPERTY_TableViewSort->isVisible()){
    //if (PROPERTY_TableViewSort->isModified()*/)
    {
      QString n = (PROPERTY_TableViewSort->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_TableViewSort(n);
    }
  }
}

void _propertywindow::SLOTPROPERTY_TableViewFilter()
{
  if (ISFORM && PROPERTY_TableViewFilter->isVisible()){
    //if (PROPERTY_TableViewFilter->isModified()*/)
    {
      QString n = (PROPERTY_TableViewFilter->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_TableViewFilter(n);
    }
  }
}

void _propertywindow::SLOTPROPERTY_TableViewWidth()
{
  if (ISFORM && PROPERTY_TableViewWidth->isVisible()){
    QString s = PROPERTY_TableViewWidth->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_TableViewWidth(s.toInt());
  }
}

void _propertywindow::SLOTPROPERTY_TableViewVisible()
{

  if (ISFORM && PROPERTY_TableViewVisible->isVisible()){
    bool n = (PROPERTY_TableViewVisible->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_TableViewVisible(n);
  }
}

void _propertywindow::SLOTPROPERTY_TableViewOrder()
{
  if (ISFORM && PROPERTY_TableViewOrder->isVisible()){
    QString s = PROPERTY_TableViewOrder->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_TableViewOrder(s.toInt());
  }
}


void _propertywindow::SLOTPROPERTY_SQLInsert()
{
  if (ISFORM && PROPERTY_SQLInsert->isVisible()){
    bool n = (PROPERTY_SQLInsert->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_SQLInsert(n);
  }
}

void _propertywindow::SLOTPROPERTY_SQLUpdate()
{
  if (ISFORM && PROPERTY_SQLUpdate->isVisible()){
    bool n = (PROPERTY_SQLUpdate->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_SQLUpdate(n);
  }
}

void _propertywindow::SLOTPROPERTY_SQLDelete()
{
  if (ISFORM && PROPERTY_SQLDelete->isVisible()){
    bool n = (PROPERTY_SQLDelete->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_SQLDelete(n);
  }
}


void _propertywindow::SLOTPROPERTY_Pages()
{

  if (ISFORM && PROPERTY_Pages->isVisible()){
    //if (/*!PROPERTY_Pages->text().isEmpty() && *//*PROPERTY_Pages->isModified()*/)
    {
      QString n = (PROPERTY_Pages->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_Pages(n);
    }
  }

}

// PROPERTY    

void _propertywindow::SLOTPROPERTY_Prefix()
{
  if (ISFORM && PROPERTY_Prefix->isVisible()){
    {
      QString n = (PROPERTY_Prefix->text());
      my_form_newUndoRedo(f); EXTERN_my_form->controls_SETPROPERTY_Prefix(n);
    }
  }
}

void _propertywindow::SLOTPROPERTY_Suffix()
{
  if (ISFORM && PROPERTY_Suffix->isVisible()){
    {
      QString n = (PROPERTY_Suffix->text());
      my_form_newUndoRedo(f); EXTERN_my_form->controls_SETPROPERTY_Suffix(n);
    }
  }
}

void _propertywindow::SLOTPROPERTY_ViewMode()
{

  if (ISFORM && PROPERTY_ViewMode->isVisible()){
    {
      QString n = (PROPERTY_ViewMode->text());
      my_form_newUndoRedo(f); EXTERN_my_form->controls_SETPROPERTY_ViewMode(n);
    }
  }
  
}

void _propertywindow::SLOTPROPERTY_TickPosition()
{
  if (ISFORM && PROPERTY_TickPosition->isVisible()){
    {
      QString n = (PROPERTY_TickPosition->text());
      my_form_newUndoRedo(f); EXTERN_my_form->controls_SETPROPERTY_TickPosition(n);
    }
  }
}

void _propertywindow::SLOTPROPERTY_InvertedAppearance()
{
  if (ISFORM && PROPERTY_InvertedAppearance->isVisible()){
    bool n = (PROPERTY_InvertedAppearance->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_InvertedAppearance(n);
  }
}

void _propertywindow::SLOTPROPERTY_InvertedControls()
{
  if (ISFORM && PROPERTY_InvertedControls->isVisible()){
    bool n = (PROPERTY_InvertedControls->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_InvertedControls(n);
  }
}

void _propertywindow::SLOTPROPERTY_Tracking()
{
  if (ISFORM && PROPERTY_Tracking->isVisible()){
    bool n = (PROPERTY_Tracking->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Tracking(n);
  }
}

void _propertywindow::SLOTPROPERTY_TickInterval()
{
  if (ISFORM){
    PROPERTY_TickInterval->setModified(false);
    int n = (PROPERTY_TickInterval->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_TickInterval(n);
  }
}

void _propertywindow::SLOTPROPERTY_PageStep()
{
  if (ISFORM){
    PROPERTY_PageStep->setModified(false);
    int n = (PROPERTY_PageStep->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_PageStep(n);
  }
}

void _propertywindow::SLOTPROPERTY_SingleStep()
{
  if (ISFORM){
    PROPERTY_SingleStep->setModified(false);
    int n = (PROPERTY_SingleStep->text()).toInt();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_SingleStep(n);
  }
}

void _propertywindow::SLOTPROPERTY_Description()
{

  if (ISFORM && PROPERTY_Description->isVisible()){
    {
      QString n = (PROPERTY_Description->text());
      my_form_newUndoRedo(f); EXTERN_my_form->controls_SETPROPERTY_Description(n);
    }
  }
  
}


void _propertywindow::SLOTPROPERTY_ContextMenu()
{

  if (ISFORM && PROPERTY_ContextMenu->isVisible()){
    {
      QString n = (PROPERTY_ContextMenu->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_ContextMenu(n);
    }
  }

  else if (ISTOOLBAR && PROPERTY_ContextMenu->isVisible()){
    {
      QString n = (PROPERTY_ContextMenu->text());
      EXTERN_my_toolbar->controls_SETPROPERTY_ContextMenu(n);
    }
  }

}



void _propertywindow::SLOTPROPERTY_ActionId()
{

  if (ISMENUBAR && PROPERTY_ActionId->isVisible()){
    {
      QString n = (PROPERTY_ActionId->text());
      EXTERN_my_menubar->controls_SETPROPERTY_ActionId(n);
    }
  }
  
  else if (ISTOOLBAR && PROPERTY_ActionId->isVisible()){
    {
      QString n = (PROPERTY_ActionId->text());
      EXTERN_my_toolbar->controls_SETPROPERTY_ActionId(n);
    }
  }
}

void _propertywindow::SLOTPROPERTY_SoundOnEvent()
{

  if (ISFORM && PROPERTY_SoundOnEvent->isVisible()){
    {
      QString n = (PROPERTY_SoundOnEvent->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_SoundOnEvent(n);
    }
  }


  else if (ISMENUBAR && PROPERTY_SoundOnEvent->isVisible()){
    {
      QString n = (PROPERTY_SoundOnEvent->text());
      EXTERN_my_menubar->controls_SETPROPERTY_SoundOnEvent(n);
    }
  }
  
  else if (ISTOOLBAR && PROPERTY_SoundOnEvent->isVisible()){
    {
      QString n = (PROPERTY_SoundOnEvent->text());
      EXTERN_my_toolbar->controls_SETPROPERTY_SoundOnEvent(n);
    }
  }
}

void _propertywindow::SLOTPROPERTY_Comment1Begin()
{

  if (ISFORM && PROPERTY_Comment1Begin->isVisible()){
    //if (/*!PROPERTY_Pages->text().isEmpty() && *//*PROPERTY_Comment1Begin->isModified()*/)
    {
      QString n = (PROPERTY_Comment1Begin->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_Comment1Begin(n);
    }
  }

}

void _propertywindow::SLOTPROPERTY_Comment1End()
{

  if (ISFORM && PROPERTY_Comment1End->isVisible()){
   // if (/*!PROPERTY_Pages->text().isEmpty() && *//*PROPERTY_Comment1End->isModified()*/)
    {
      QString n = (PROPERTY_Comment1End->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_Comment1End(n);
    }
  }

}

void _propertywindow::SLOTPROPERTY_Comment2Begin()
{

  if (ISFORM && PROPERTY_Comment2Begin->isVisible()){
    //if (/*!PROPERTY_Pages->text().isEmpty() && *//*PROPERTY_Comment2Begin->isModified()*/)
    {
      QString n = (PROPERTY_Comment2Begin->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_Comment2Begin(n);
    }
  }

}

void _propertywindow::SLOTPROPERTY_Keywords()
{

  if (ISFORM && PROPERTY_Keywords->isVisible()){
    //if (/*!PROPERTY_Pages->text().isEmpty() && *//*PROPERTY_Keywords->isModified()*/)
    {
      QString n = (PROPERTY_Keywords->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_Keywords(n);
    }
  }

}

void _propertywindow::SLOTPROPERTY_Commands()
{

  if (ISFORM && PROPERTY_Commands->isVisible()){
   // if (/*!PROPERTY_Pages->text().isEmpty() && *//*PROPERTY_Commands->isModified()*/)
    {
      QString n = (PROPERTY_Commands->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_Commands(n);
    }
  }

}

void _propertywindow::SLOTPROPERTY_CommentColor()
{
  if (ISFORM && PROPERTY_CommentColor->isVisible()){
    QString s = PROPERTY_CommentColor->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CommentColor(s);
  }
}

void _propertywindow::SLOTPROPERTY_KeywordColor()
{
  if (ISFORM && PROPERTY_KeywordColor->isVisible()){
    QString s = PROPERTY_KeywordColor->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_KeywordColor(s);
  }
}

void _propertywindow::SLOTPROPERTY_CommandColor()
{
  if (ISFORM && PROPERTY_CommandColor->isVisible()){
    QString s = PROPERTY_CommandColor->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CommandColor(s);
  }
}

void _propertywindow::SLOTPROPERTY_SelectionMode()
{

  if (ISFORM && PROPERTY_SelectionMode->isVisible()){
    QString s = PROPERTY_SelectionMode->text();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_SelectionMode(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnPrint()
{

  if (ISFORM && PROPERTY_OnPrint->isVisible()){
    bool n = (PROPERTY_OnPrint->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnPrint(n);
  }
}

void _propertywindow::SLOTPROPERTY_RootIsDecorated()
{

  if (ISFORM && PROPERTY_RootIsDecorated->isVisible()){
    bool n = (PROPERTY_RootIsDecorated->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_RootIsDecorated(n);
  }

}



void _propertywindow::SLOTPROPERTY_MoveOnMouseDrag()
{

  if (ISFORM && PROPERTY_MoveOnMouseDrag->isVisible()){
    bool n = (PROPERTY_MoveOnMouseDrag->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MoveOnMouseDrag(n);
  }

}

void _propertywindow::SLOTPROPERTY_MouseTracking()
{

  if (ISFORM && PROPERTY_MouseTracking->isVisible()){
    bool n = (PROPERTY_MouseTracking->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_MouseTracking(n);
  }

}
void _propertywindow::SLOTPROPERTY_DrawOnPaint()
{

  if (ISFORM && PROPERTY_DrawOnPaint->isVisible()){
    bool n = (PROPERTY_DrawOnPaint->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_DrawOnPaint(n);
  }

}

void _propertywindow::SLOTPROPERTY_AlternatingRowColors()
{

  if (ISFORM && PROPERTY_AlternatingRowColors->isVisible()){
    bool n = (PROPERTY_AlternatingRowColors->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_AlternatingRowColors(n);
  }

}

void _propertywindow::SLOTPROPERTY_ParentForm()
{

  if (ISFORM && PROPERTY_ParentForm->isVisible()){
    QString s = PROPERTY_ParentForm->text();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ParentForm(n);
  }

}

void _propertywindow::SLOTPROPERTY_ParentControl()
{

  if (ISFORM && PROPERTY_ParentControl->isVisible()){
    QString s = PROPERTY_ParentControl->text();
    QString n = s;
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ParentControl(n);
  }

}


void _propertywindow::SLOTPROPERTY_TabIndex()
{

  if (ISFORM && PROPERTY_TabIndex->isVisible()){
    QString s = PROPERTY_TabIndex->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_TabIndex(s.toInt());
  }

}

void _propertywindow::SLOTPROPERTY_ParentIndex()
{

  if (ISFORM && PROPERTY_ParentIndex->isVisible()){
    QString s = PROPERTY_ParentIndex->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ParentIndex(s.toInt());
  }

}


/*
void _propertywindow::SLOTPROPERTY_EnterImage2()
{ 

  SLOTPROPERTY_EnterImage(true); 

}*/

void _propertywindow::SLOTPROPERTY_EnterImage() //bool b)
{
  if (ISFORM && PROPERTY_EnterImage->isVisible()){
    QString s = PROPERTY_EnterImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_EnterImage(s);
  }

}

/*
void _propertywindow::SLOTPROPERTY_ExitImage2()
{ 

  SLOTPROPERTY_ExitImage(true); 

}*/

void _propertywindow::SLOTPROPERTY_ExitImage() //bool b)
{
  if (ISFORM && PROPERTY_ExitImage->isVisible()){
    QString s = PROPERTY_ExitImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ExitImage(s);
  }


}
/*
void _propertywindow::SLOTPROPERTY_DisabledImage2()
{ 

  SLOTPROPERTY_DisabledImage(true); 

}
*/
void _propertywindow::SLOTPROPERTY_DisabledImage() //bool b)
{
  if (ISFORM && PROPERTY_DisabledImage->isVisible()){
    QString s = PROPERTY_DisabledImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_DisabledImage(s);
  }


}



/*
void _propertywindow::SLOTPROPERTY_CheckEnterImage2()
{ 

  SLOTPROPERTY_CheckEnterImage(true); 

}*/

void _propertywindow::SLOTPROPERTY_CheckEnterImage() //bool b)
{
  if (ISFORM && PROPERTY_CheckEnterImage->isVisible()){
    QString s = PROPERTY_CheckEnterImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CheckEnterImage(s);
  }


}
/*
void _propertywindow::SLOTPROPERTY_CheckExitImage2()
{ 

  SLOTPROPERTY_CheckExitImage(true); 

}*/

void _propertywindow::SLOTPROPERTY_CheckExitImage() //bool b)
{
  if (ISFORM && PROPERTY_CheckExitImage->isVisible()){
    QString s = PROPERTY_CheckExitImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CheckExitImage(s);
  }

}
/*
void _propertywindow::SLOTPROPERTY_CheckDisabledImage2()
{ 

  SLOTPROPERTY_CheckDisabledImage(true); 

}*/

void _propertywindow::SLOTPROPERTY_CheckDisabledImage() //bool b)
{
  if (ISFORM && PROPERTY_CheckDisabledImage->isVisible()){
    QString s = PROPERTY_CheckDisabledImage->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_CheckDisabledImage(s);
  }

}

void _propertywindow::SLOTPROPERTY_EnterSound()
{
  if (ISFORM && PROPERTY_EnterSound->isVisible()){
    QString s = PROPERTY_EnterSound->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_EnterSound(s);
  }
}

void _propertywindow::SLOTPROPERTY_ExitSound()
{
  if (ISFORM && PROPERTY_ExitSound->isVisible()){
    QString s = PROPERTY_ExitSound->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_ExitSound(s);
  }
}



void _propertywindow::SLOTPROPERTY_Menu()
{

  if (ISFORM && PROPERTY_Menu->isVisible()){
    bool n = (PROPERTY_Menu->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Menu(n);
  }

}


void _propertywindow::SLOTPROPERTY_Interval()
{

  if (ISFORM && PROPERTY_Interval->isVisible()){
    QString s = PROPERTY_Interval->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Interval(s.toInt());
  }

}

void _propertywindow::SLOTPROPERTY_StringValue()
{

  if (ISFORM && PROPERTY_StringValue->isVisible()){
    QString s = PROPERTY_StringValue->lineedit()->text();
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_StringValue(s);
  }

}

void _propertywindow::SLOTPROPERTY_Mask()
{

  if (ISFORM && PROPERTY_Mask->isVisible()){
    {
      QString n = (PROPERTY_Mask->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_Mask(n);
    }
  }

}
void _propertywindow::SLOTPROPERTY_InputMask()
{

  if (ISFORM && PROPERTY_InputMask->isVisible()){
    {
      QString n = (PROPERTY_InputMask->text());
      my_form_newUndoRedo(f); f->controls_SETPROPERTY_InputMask(n);
    }
  }

}




void _propertywindow::SLOTPROPERTY_OpenAtStartup()
{

  if (ISFORM && PROPERTY_OpenAtStartup->isVisible()){
    bool n = (PROPERTY_OpenAtStartup->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OpenAtStartup(n);
  }

}

void _propertywindow::SLOTPROPERTY_Default()
{

  if (ISFORM && PROPERTY_Default->isVisible()){
    bool n = (PROPERTY_Default->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Default(n);
  }

}

void _propertywindow::SLOTPROPERTY_EventOnOpen()
{

  if (ISFORM && PROPERTY_EventOnOpen->isVisible()){
    bool n = (PROPERTY_EventOnOpen->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_EventOnOpen(n);
  }

}

void _propertywindow::SLOTPROPERTY_Checkable()
{

  if (ISFORM && PROPERTY_Checkable->isVisible()){
    bool n = (PROPERTY_Checkable->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_Checkable(n);
  }

  else if (ISMENUBAR && PROPERTY_Checkable->isVisible()){
    bool n = (PROPERTY_Checkable->currentText() == "True");
    EXTERN_my_menubar->controls_SETPROPERTY_Checkable(n);
  }

  else if (ISTOOLBAR && PROPERTY_Checkable->isVisible()){
    bool n = (PROPERTY_Checkable->currentText() == "True");
    EXTERN_my_toolbar->controls_SETPROPERTY_Checkable(n);
  }
}

void _propertywindow::SLOTPROPERTY_AcceptRichText()
{

  if (ISFORM && PROPERTY_AcceptRichText->isVisible()){
    bool n = (PROPERTY_AcceptRichText->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_AcceptRichText(n);
  }

}

void _propertywindow::SLOTPROPERTY_AutoDefault()
{

  if (ISFORM && PROPERTY_AutoDefault->isVisible()){
    bool n = (PROPERTY_AutoDefault->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_AutoDefault(n);
  }

}

void _propertywindow::SLOTPROPERTY_Index()
{
  if (ISTABLE && PROPERTY_Index->isVisible()){
    bool n = (PROPERTY_Index->currentText() == "True");
    EXTERN_my_table->controls_SETPROPERTY_Index(n);
  }
}

void _propertywindow::SLOTPROPERTY_Null()
{
  if (ISTABLE && PROPERTY_Null->isVisible()){
    bool n = (PROPERTY_Null->currentText() == "True");
    EXTERN_my_table->controls_SETPROPERTY_Null(n);
  }
}

void _propertywindow::SLOTPROPERTY_BooleanValue()
{
  if (ISFORM && PROPERTY_BooleanValue->isVisible()){
    bool n = (PROPERTY_BooleanValue->currentText() == "True");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_BooleanValue(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnCurrentItemChanged()
{
  if (ISFORM && PROPERTY_OnCurrentItemChanged->isVisible()){
    bool n = (PROPERTY_OnCurrentItemChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnCurrentItemChanged(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnItemActivated()
{
  if (ISFORM && PROPERTY_OnItemActivated->isVisible()){
    bool n = (PROPERTY_OnItemActivated->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnItemActivated(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnItemChanged()
{
  if (ISFORM && PROPERTY_OnItemChanged->isVisible()){
    bool n = (PROPERTY_OnItemChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnItemChanged(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnItemClicked()
{
  if (ISFORM && PROPERTY_OnItemClicked->isVisible()){
    bool n = (PROPERTY_OnItemClicked->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnItemClicked(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnItemCollapsed()
{
  if (ISFORM && PROPERTY_OnItemCollapsed->isVisible()){
    bool n = (PROPERTY_OnItemCollapsed->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnItemCollapsed(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnItemDoubleClicked()
{
  if (ISFORM && PROPERTY_OnItemDoubleClicked->isVisible()){
    bool n = (PROPERTY_OnItemDoubleClicked->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnItemDoubleClicked(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnItemEntered()
{
  if (ISFORM && PROPERTY_OnItemEntered->isVisible()){
    bool n = (PROPERTY_OnItemEntered->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnItemEntered(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnItemExpanded()
{
  if (ISFORM && PROPERTY_OnItemExpanded->isVisible()){
    bool n = (PROPERTY_OnItemExpanded->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnItemExpanded(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnItemPressed()
{
  if (ISFORM && PROPERTY_OnItemPressed->isVisible()){
    bool n = (PROPERTY_OnItemPressed->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnItemPressed(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnItemSelectionChanged()
{
  if (ISFORM && PROPERTY_OnItemSelectionChanged->isVisible()){
    bool n = (PROPERTY_OnItemSelectionChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnItemSelectionChanged(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnDockMove()
{
  if (ISFORM && PROPERTY_OnDockMove->isVisible()){
    bool n = (PROPERTY_OnDockMove->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDockMove(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnDockShow()
{
  if (ISFORM && PROPERTY_OnDockShow->isVisible()){
    bool n = (PROPERTY_OnDockShow->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDockShow(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnDockHide()
{
  if (ISFORM && PROPERTY_OnDockHide->isVisible()){
    bool n = (PROPERTY_OnDockHide->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDockHide(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnDockFloating()
{
  if (ISFORM && PROPERTY_OnDockFloating->isVisible()){
    bool n = (PROPERTY_OnDockFloating->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDockFloating(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnDockNotFloating()
{
  if (ISFORM && PROPERTY_OnDockNotFloating->isVisible()){
    bool n = (PROPERTY_OnDockNotFloating->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDockNotFloating(n);
  }
}

// EVENT


/*
void _propertywindow::SLOTPROPERTY_OnCursorPositionChanged()
{
  if (ISFORM && PROPERTY_OnCursorPositionChanged->isVisible()){
    bool n = (PROPERTY_OnCursorPositionChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnCursorPositionChanged(n);
  }
}*/
void _propertywindow::SLOTPROPERTY_OnEditingFinished()
{
  if (ISFORM && PROPERTY_OnEditingFinished->isVisible()){
    bool n = (PROPERTY_OnEditingFinished->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnEditingFinished(n);
  }
}
void _propertywindow::SLOTPROPERTY_OnReturnPressed()
{
  if (ISFORM && PROPERTY_OnReturnPressed->isVisible()){
    bool n = (PROPERTY_OnReturnPressed->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnReturnPressed(n);
  }
}
void _propertywindow::SLOTPROPERTY_OnSelectionChanged()
{
  if (ISFORM && PROPERTY_OnSelectionChanged->isVisible()){
    bool n = (PROPERTY_OnSelectionChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnSelectionChanged(n);
  }
}
void _propertywindow::SLOTPROPERTY_OnTextChanged()
{
  if (ISFORM && PROPERTY_OnTextChanged->isVisible()){
    bool n = (PROPERTY_OnTextChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnTextChanged(n);
  }
}
void _propertywindow::SLOTPROPERTY_OnTextEdited()
{
  if (ISFORM && PROPERTY_OnTextEdited->isVisible()){
    bool n = (PROPERTY_OnTextEdited->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnTextEdited(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnPage()
{
  if (ISFORM && PROPERTY_OnPage->isVisible()){
    bool n = (PROPERTY_OnPage->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnPage(n);
  }
}
void _propertywindow::SLOTPROPERTY_OnLinkHovered()
{
  if (ISFORM && PROPERTY_OnLinkHovered->isVisible()){
    bool n = (PROPERTY_OnLinkHovered->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnLinkHovered(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnLoadFinished()
{
  if (ISFORM && PROPERTY_OnLoadFinished->isVisible()){
    bool n = (PROPERTY_OnLoadFinished->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnLoadFinished(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnLoadProgress()
{
  if (ISFORM && PROPERTY_OnLoadProgress->isVisible()){
    bool n = (PROPERTY_OnLoadProgress->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnLoadProgress(n);
  }
}
void _propertywindow::SLOTPROPERTY_OnLoadStarted()
{
  if (ISFORM && PROPERTY_OnLoadStarted->isVisible()){
    bool n = (PROPERTY_OnLoadStarted->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnLoadStarted(n);
  }
}
void _propertywindow::SLOTPROPERTY_OnWindowCloseRequested()
{
  if (ISFORM && PROPERTY_OnWindowCloseRequested->isVisible()){
    bool n = (PROPERTY_OnWindowCloseRequested->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnWindowCloseRequested(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnEvent()
{
  if (ISFORM && PROPERTY_OnEvent->isVisible()){
    bool n = (PROPERTY_OnEvent->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnEvent(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnSingleShot()
{
  if (ISFORM && PROPERTY_OnSingleShot->isVisible()){
    bool n = (PROPERTY_OnSingleShot->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnSingleShot(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnAction()
{
  if (ISFORM && PROPERTY_OnAction->isVisible()){
    bool n = (PROPERTY_OnAction->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnAction(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnCursorPositionChanged()
{
  if (ISFORM && PROPERTY_OnCursorPositionChanged->isVisible()){
    bool n = (PROPERTY_OnCursorPositionChanged->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnCursorPositionChanged(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnOpen()
{
  if (ISFORM && PROPERTY_OnOpen->isVisible()){
    bool n = (PROPERTY_OnOpen->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnOpen(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnClose()
{
  if (ISFORM && PROPERTY_OnClose->isVisible()){
    bool n = (PROPERTY_OnClose->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnClose(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnGoTo()
{
  if (ISFORM && PROPERTY_OnGoTo->isVisible()){
    bool n = (PROPERTY_OnGoTo->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnGoTo(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnBeforeInsert()
{
  if (ISFORM && PROPERTY_OnBeforeInsert->isVisible()){
    bool n = (PROPERTY_OnBeforeInsert->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnBeforeInsert(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnBeforeDelete()
{
  if (ISFORM && PROPERTY_OnBeforeDelete->isVisible()){
    bool n = (PROPERTY_OnBeforeDelete->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnBeforeDelete(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnDragExit()
{
  if (ISFORM && PROPERTY_OnDragExit->isVisible()){
    bool n = (PROPERTY_OnDragExit->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDragExit(n);
  }
}

void _propertywindow::SLOTPROPERTY_OnPaint()
{
  if (ISFORM && PROPERTY_OnPaint->isVisible()){
    bool n = (PROPERTY_OnPaint->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnPaint(n);
  }
}



void _propertywindow::SLOTPROPERTY_OnDirty()
{

  if (ISFORM && PROPERTY_OnDirty->isVisible()){
    bool n = (PROPERTY_OnDirty->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDirty(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnAddNew()
{

  if (ISFORM && PROPERTY_OnAddNew->isVisible()){
    bool n = (PROPERTY_OnAddNew->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnAddNew(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnQuery()
{

  if (ISFORM && PROPERTY_OnQuery->isVisible()){
    bool n = (PROPERTY_OnQuery->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnQuery(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnTimer()
{

  if (ISFORM && PROPERTY_OnTimer->isVisible()){
    bool n = (PROPERTY_OnTimer->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnTimer(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnMove()
{

  if (ISFORM && PROPERTY_OnMove->isVisible()){
    bool n = (PROPERTY_OnMove->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnMove(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnHide()
{

  if (ISFORM && PROPERTY_OnHide->isVisible()){
    bool n = (PROPERTY_OnHide->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnHide(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnShow()
{

  if (ISFORM && PROPERTY_OnShow->isVisible()){
    bool n = (PROPERTY_OnShow->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnShow(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnEnabled()
{

  if (ISFORM && PROPERTY_OnEnabled->isVisible()){
    bool n = (PROPERTY_OnEnabled->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnEnabled(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnDisabled()
{

  if (ISFORM && PROPERTY_OnDisabled->isVisible()){
    bool n = (PROPERTY_OnDisabled->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDisabled(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnMouseWheel()
{

  if (ISFORM && PROPERTY_OnMouseWheel->isVisible()){
    bool n = (PROPERTY_OnMouseWheel->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnMouseWheel(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnScroll()
{

  if (ISFORM && PROPERTY_OnScroll->isVisible()){
    bool n = (PROPERTY_OnScroll->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnScroll(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnMultiPageShow()
{

  if (ISFORM && PROPERTY_OnMultiPageShow->isVisible()){
    bool n = (PROPERTY_OnMultiPageShow->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnMultiPageShow(n);
  }

}



void _propertywindow::SLOTPROPERTY_OnContextMenu()
{

  if (ISFORM && PROPERTY_OnContextMenu->isVisible()){
    bool n = (PROPERTY_OnContextMenu->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnContextMenu(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnDrop()
{

  if (ISFORM && PROPERTY_OnDrop->isVisible()){
    bool n = (PROPERTY_OnDrop->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDrop(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnDragMove()
{

  if (ISFORM && PROPERTY_OnDragMove->isVisible()){
    bool n = (PROPERTY_OnDragMove->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDragMove(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnDragEnter()
{

  if (ISFORM && PROPERTY_OnDragEnter->isVisible()){
    bool n = (PROPERTY_OnDragEnter->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDragEnter(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnClick()
{

  if (ISFORM && PROPERTY_OnClick->isVisible()){
    bool n = (PROPERTY_OnClick->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnClick(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnDblClick()
{

  if (ISFORM && PROPERTY_OnDblClick->isVisible()){
    bool n = (PROPERTY_OnDblClick->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnDblClick(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnMouseDown()
{

  if (ISFORM && PROPERTY_OnMouseDown->isVisible()){
    bool n = (PROPERTY_OnMouseDown->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnMouseDown(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnMouseUp()
{

  if (ISFORM && PROPERTY_OnMouseUp->isVisible()){
    bool n = (PROPERTY_OnMouseUp->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnMouseUp(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnMouseMove()
{

  if (ISFORM && PROPERTY_OnMouseMove->isVisible()){
    bool n = (PROPERTY_OnMouseMove->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnMouseMove(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnGotFocus()
{

  if (ISFORM && PROPERTY_OnGotFocus->isVisible()){
    bool n = (PROPERTY_OnGotFocus->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnGotFocus(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnLostFocus()
{

  if (ISFORM && PROPERTY_OnLostFocus->isVisible()){
    bool n = (PROPERTY_OnLostFocus->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnLostFocus(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnEnter()
{

  if (ISFORM && PROPERTY_OnEnter->isVisible()){
    bool n = (PROPERTY_OnEnter->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnEnter(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnExit()
{

  if (ISFORM && PROPERTY_OnExit->isVisible()){
    bool n = (PROPERTY_OnExit->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnExit(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnKeyDown()
{

  if (ISFORM && PROPERTY_OnKeyDown->isVisible()){
    bool n = (PROPERTY_OnKeyDown->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnKeyDown(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnKeyUp()
{

  if (ISFORM && PROPERTY_OnKeyUp->isVisible()){
    bool n = (PROPERTY_OnKeyUp->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnKeyUp(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnKeyPress()
{

  if (ISFORM && PROPERTY_OnKeyPress->isVisible()){
    bool n = (PROPERTY_OnKeyPress->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnKeyPress(n);
  }

}

void _propertywindow::SLOTPROPERTY_OnBeforeUpdate()
{

  if (ISFORM && PROPERTY_OnBeforeUpdate->isVisible()){
    bool n = (PROPERTY_OnBeforeUpdate->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnBeforeUpdate(n);
  }

}


void _propertywindow::SLOTPROPERTY_OnResize()
{

  if (ISFORM && PROPERTY_OnResize->isVisible()){
    bool n = (PROPERTY_OnResize->lineedit()->text() == "Yes");
    my_form_newUndoRedo(f); f->controls_SETPROPERTY_OnResize(n);
  }

}






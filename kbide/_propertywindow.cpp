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
#include "_inputtip_parser.h"

#include "../kbshared/_form.h"
#include "../kbshared/_report.h"
#include "../kbshared/_menubar.h"
#include "../kbshared/_toolbar.h"

#include "_resources.h"


#include "_choicedialog.h"

extern QString idePath(QString s);

extern _form *EXTERN_my_form;
extern _report *EXTERN_my_report;
extern _menubar *EXTERN_my_menubar;
extern _toolbar *EXTERN_my_toolbar;

extern _mainwindow *EXTERN_my_mainwindow;


bool bRersourcesAreSelected = false;

extern QString sSelectedResource;

// ***

bool bBuilded = false;

QVBoxLayout *re = 0;
QVBoxLayout *li = 0;
QHBoxLayout *aa = 0;


int nPropertyWindowForWhat = 0;

bool _propertywindow::newEvent(QString s)
{
  QString ss = s;
  ss = ss.replace("<b>", ""); // WORKAROUND
  ss = ss.replace("</b>", ""); // WORKAROUND

  if (EXTERN_my_form || EXTERN_my_menubar || EXTERN_my_toolbar || EXTERN_my_report){

    QString sParameter = "";

    // EVENT
    if (s == "OnOpen"){            sParameter = "";

    } else if (s == "OnCursorPositionChanged"){     sParameter = "Old As Integer, New As Integer";
    } else if (s == "OnEditingFinished"){     sParameter = "";
    } else if (s == "OnReturnPressed"){     sParameter = "";
    } else if (s == "OnSelectionChanged"){     sParameter = "";
    } else if (s == "OnTextChanged"){     sParameter = "Text As String";
    } else if (s == "OnTextEdited"){     sParameter = "Text As String";

    } else if (s == "OnPage"){     sParameter = "NewPage As String";
    } else if (s == "OnLinkHovered"){     sParameter = "Link As String, Title As String, TextContent As String";
    } else if (s == "OnLoadFinished"){     sParameter = "Ok As Boolean";
    } else if (s == "OnLoadProgress"){     sParameter = "Progress As Integer";
    } else if (s == "OnLoadStarted"){     sParameter = "";
    } else if (s == "OnWindowCloseRequested"){     sParameter = "";

    } else if (s == "OnSingleShot"){     sParameter = "";
    } else if (s == "OnClose"){     sParameter = "ByRef Cancel As Boolean";
    } else if (s == "OnContextMenu"){     sParameter = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer";
    } else if (s == "OnDragEnter"){     sParameter = "ByRef Cancel As Boolean, X As Integer, Y As Integer, Width As Integer, Height As Integer";
    } else if (s == "OnDragExit"){     sParameter = "";
    } else if (s == "OnDragMove"){     sParameter = "ByRef Cancel As Boolean, X As Integer, Y As Integer, Width As Integer, Height As Integer";
    } else if (s == "OnDrop"){     sParameter = "ByRef Cancel As Boolean, MimeData As String";
    } else if (s == "OnEnter"){     sParameter = "";
    } else if (s == "OnGotFocus"){     sParameter = "";
    } else if (s == "OnLostFocus"){     sParameter = "";
    } else if (s == "OnHide"){     sParameter = "";
    } else if (s == "OnKeyDown"){     sParameter = "KeyCode As Integer, Shift As Boolean, Control As Boolean, Alt As Boolean";
    } else if (s == "OnKeyUp"){     sParameter = "KeyCode As Integer, Shift As Boolean, Control As Boolean, Alt As Boolean";
    } else if (s == "OnKeyPress"){     sParameter = "KeyCode As Integer, Shift As Boolean, Control As Boolean, Alt As Boolean";
    } else if (s == "OnExit"){     sParameter = "";
    } else if (s == "OnGoTo"){     sParameter = "";
    } else if (s == "OnBeforeInsert"){     sParameter = "ByRef Cancel As Boolean";
    } else if (s == "OnBeforeDelete"){     sParameter = "ByRef Cancel As Boolean";
    } else if (s == "OnBeforeUpdate"){     sParameter = "ByRef Cancel As Boolean";
    } else if (s == "OnDblClick"){     sParameter = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean";
    } else if (s == "OnClick"){     sParameter = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean";
    } else if (s == "OnMouseMove"){     sParameter = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer";
    } else if (s == "OnMouseDown"){     sParameter = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean";
    } else if (s == "OnMouseUp"){     sParameter = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean";
    } else if (s == "OnMove"){     sParameter = "X As Integer, Y As Integer, OldX As Integer, OldY As Integer";
    } else if (s == "OnPaint"){     sParameter = "X As Integer, Y As Integer, Width As Integer, Height As Integer";
    } else if (s == "OnResize"){     sParameter = "Width As Integer, Height As Integer, OldWidth As Integer, OldHeight As Integer";
    } else if (s == "OnShow"){     sParameter = "";
    } else if (s == "OnEnabled"){     sParameter = "";
    } else if (s == "OnDisabled"){     sParameter = "";
    } else if (s == "OnTimer"){     sParameter = "";
    } else if (s == "OnMouseWheel"){     sParameter = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer";    
    } else if (s == "OnScroll"){     sParameter = "";        
    } else if (s == "OnMultiPageShow"){     sParameter = "Page As Integer";        
    } else if (s == "OnDirty"){     sParameter = "";
    } else if (s == "OnAddNew"){     sParameter = "";
    } else if (s == "OnQuery"){     sParameter = "";
    } else if (s == "OnDragEnter"){     sParameter = "ByRef Cancel As Boolean, X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, Width As Integer, Height As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean, Shift As Boolean, Control As Boolean, Alt As Boolean";
    } else if (s == "OnDragMove"){     sParameter = "ByRef Cancel As Boolean, X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, Width As Integer, Height As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean, Shift As Boolean, Control As Boolean, Alt As Boolean";
    } else if (s == "OnDragExit"){     sParameter = "";
    } else if (s == "OnDrop"){     sParameter = "ByRef Cancel As Boolean, MimeData As String, X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean, Shift As Boolean, Control As Boolean, Alt As Boolean";
    }


    bool b = false;
    if (EXTERN_my_form && nPropertyWindowForWhat == 0) b = EXTERN_my_form->newEvent("", ss, sParameter);
    else if (EXTERN_my_menubar && nPropertyWindowForWhat == 1) b = EXTERN_my_menubar->newEvent();
    else if (EXTERN_my_toolbar && nPropertyWindowForWhat == 2) b = EXTERN_my_toolbar->newEvent();
    else if (EXTERN_my_report && nPropertyWindowForWhat == 3) b = EXTERN_my_report->newEvent("", ss, sParameter);

    return b;

  }
}

void _propertywindow::createList()
{

  header_main = new _property_header(tr("<b>MAIN</b>"), fr, this);
  header_other2 = new _property_header(tr("<b>FORMAT</b>"), fr, this);
  header_other = new _property_header(tr("<b>DATA</b>"), fr, this);
  header_other3 = new _property_header(tr("<b>SPECIAL</b>"), fr, this);
  header_other4 = new _property_header(tr("<b>PROPERTY (CONTROL)</b>"), fr, this);
  header_event = new _property_header(tr("<b>EVENT (CONTROL)</b>"), fr, this);

  // ***

  _property_label *l = 0;
  QString sHelp = "";



  _property_event *k = 0;

  PROPERTY_Name = new _property_lineedit(fr, "Name", false);
  connect(PROPERTY_Name, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Name()));
  controls_lineedit.append(PROPERTY_Name);



  PROPERTY_ControlType = new _property_lineedit(fr, "ControlType", false);
  PROPERTY_ControlType->setReadOnly(true);

  controls_lineedit.append(PROPERTY_ControlType);
  
  

  PROPERTY_Group = new _property_lineedit(fr, "Group", false);
  connect(PROPERTY_Group, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Group()));
  controls_lineedit.append(PROPERTY_Group);

  PROPERTY_ActionId = new _property_lineedit(fr, "ActionId", false);
  connect(PROPERTY_ActionId, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ActionId()));
  controls_lineedit.append(PROPERTY_ActionId);


  


  PROPERTY_X = new _property_pixeledit(fr, "X");
  connect(PROPERTY_X->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_X()));

  controls_pixeledit.append(PROPERTY_X);

  

  PROPERTY_Y = new _property_pixeledit(fr, "Y");
  connect(PROPERTY_Y->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Y()));
  
  controls_pixeledit.append(PROPERTY_Y);


  PROPERTY_Width = new _property_pixeledit(fr, "Width");
  connect(PROPERTY_Width->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Width()));
  
  controls_pixeledit.append(PROPERTY_Width);

  

  PROPERTY_Height = new _property_pixeledit(fr, "Height");
  connect(PROPERTY_Height->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Height()));
  controls_pixeledit.append(PROPERTY_Height);

  


  PROPERTY_Enabled = new _property_booleancombobox(fr, "Enabled");
  connect(PROPERTY_Enabled, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Enabled()));
  connect(PROPERTY_Enabled, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Enabled())); 
  controls_booleancombobox.append(PROPERTY_Enabled);
  

  PROPERTY_Visible = new _property_booleancombobox(fr, "Visible");
  connect(PROPERTY_Visible, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Visible()));
  connect(PROPERTY_Visible, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Visible())); 

  PROPERTY_Visible->setToolTip(tr("Changes of the property Visible is visible at runtime only."));
  PROPERTY_Visible->getNeighbour()->setToolTip(tr("Changes of the property Visible is visible at runtime only."));
  controls_booleancombobox.append(PROPERTY_Visible);


  PROPERTY_Layout = new _property_choicebox(fr, "Layout");
  connect(PROPERTY_Layout->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Layout())); 
  PROPERTY_Layout->set("RelativeX;RelativeY;RelativeWidth;RelativeHeight");  
  controls_choicebox.append(PROPERTY_Layout);



  PROPERTY_Resizable = new _property_booleancombobox(fr, "Resizable");
  connect(PROPERTY_Resizable, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Resizable()));
  connect(PROPERTY_Resizable, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Resizable())); 
  controls_booleancombobox.append(PROPERTY_Resizable);
  
  PROPERTY_ResizableBigger = new _property_booleancombobox(fr, "ResizableBigger");
  connect(PROPERTY_ResizableBigger, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_ResizableBigger()));
  connect(PROPERTY_ResizableBigger, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_ResizableBigger())); 
  controls_booleancombobox.append(PROPERTY_ResizableBigger);
  
  PROPERTY_ResizableSmaller = new _property_booleancombobox(fr, "ResizableSmaller");
  connect(PROPERTY_ResizableSmaller, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_ResizableSmaller()));
  connect(PROPERTY_ResizableSmaller, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_ResizableSmaller())); 
  controls_booleancombobox.append(PROPERTY_ResizableSmaller);
  


  PROPERTY_ShowMode = new _property_choicebox(fr, "ShowMode");
  connect(PROPERTY_ShowMode->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ShowMode())); 
  PROPERTY_ShowMode->set("Centered;FullScreen;Maximized;Minimized;Normal");
  controls_choicebox.append(PROPERTY_ShowMode);

  PROPERTY_OpenAtStartup = new _property_booleancombobox(fr, "OpenOnRun");
  connect(PROPERTY_OpenAtStartup, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_OpenAtStartup()));
  connect(PROPERTY_OpenAtStartup, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_OpenAtStartup())); 
  controls_booleancombobox.append(PROPERTY_OpenAtStartup);


  PROPERTY_StopOnClose = new _property_booleancombobox(fr, "StopOnClose");
  connect(PROPERTY_StopOnClose, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_StopOnClose()));
  connect(PROPERTY_StopOnClose, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_StopOnClose())); 
  controls_booleancombobox.append(PROPERTY_StopOnClose);

  



  PROPERTY_StringValue = new _property_imageedit(fr, "Value (String)");
  connect(PROPERTY_StringValue->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_StringValue()));
  controls_imageedit.append(PROPERTY_StringValue);


  PROPERTY_IntegerValue = new _property_lineedit(fr, "Value (Integer)", false);
  connect(PROPERTY_IntegerValue, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_IntegerValue()));
  controls_lineedit.append(PROPERTY_IntegerValue);



  PROPERTY_BooleanValue = new _property_booleancombobox(fr, "Value (Boolean)");
  connect(PROPERTY_BooleanValue, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_BooleanValue()));
  connect(PROPERTY_BooleanValue, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_BooleanValue())); 

  controls_booleancombobox.append(PROPERTY_BooleanValue);


  PROPERTY_Caption = new _property_lineedit(fr, "Caption", true);
  connect(PROPERTY_Caption, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Caption()));
  PROPERTY_Caption->setToolTip(tr("Changes of the property Caption for a form is visible at runtime only."));
  PROPERTY_Caption->getNeighbour()->setToolTip(tr("Changes of the property Caption for a form is visible at runtime only."));
  controls_lineedit.append(PROPERTY_Caption);


  PROPERTY_Key = new _property_lineedit(fr, "Key", false);
  connect(PROPERTY_Key, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Key()));
  controls_lineedit.append(PROPERTY_Key);



  PROPERTY_Caption = new _property_lineedit(fr, "Caption", true);
  connect(PROPERTY_Caption, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Caption()));
  PROPERTY_Caption->setToolTip(tr("Changes of the property Caption for a form is visible at runtime only."));
  PROPERTY_Caption->getNeighbour()->setToolTip(tr("Changes of the property Caption for a form is visible at runtime only."));
  controls_lineedit.append(PROPERTY_Caption);



  PROPERTY_Icon = new _property_imageedit(fr, "Icon");
  connect(PROPERTY_Icon->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Icon()));
  PROPERTY_Icon->setToolTip(tr("Changes of the property Icon for a form is visible at runtime only."));
  PROPERTY_Icon->lineedit()->getNeighbour()->setToolTip(tr("Changes of the property Icon for a form is visible at runtime only."));
  controls_imageedit.append(PROPERTY_Icon);



  PROPERTY_Description = new _property_lineedit(fr, "Description", false);
  connect(PROPERTY_Description, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Description()));
  controls_lineedit.append(PROPERTY_Description);

  PROPERTY_Prefix = new _property_lineedit(fr, "Prefix", false);
  connect(PROPERTY_Prefix, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Prefix()));
  controls_lineedit.append(PROPERTY_Prefix);

  PROPERTY_Suffix = new _property_lineedit(fr, "Suffix", false);
  connect(PROPERTY_Suffix, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Suffix()));
  controls_lineedit.append(PROPERTY_Suffix);



  PROPERTY_Index = new _property_booleancombobox(fr, "Index");
  connect(PROPERTY_Index, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Index()));
  connect(PROPERTY_Index, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Index())); 
  controls_booleancombobox.append(PROPERTY_Index);

  PROPERTY_ArrowType = new _property_choicebox(fr, "ArrowType");
  connect(PROPERTY_ArrowType->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ArrowType())); 
  PROPERTY_ArrowType->set("NoArrow;UpArrow;DownArrow;LeftArrow;RightArrow ");
  controls_choicebox.append(PROPERTY_ArrowType);

  PROPERTY_PopupMode = new _property_choicebox(fr, "PopupMode");
  connect(PROPERTY_PopupMode->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_PopupMode())); 
  PROPERTY_PopupMode->set("DelayedPopup;MenuButtonPopup;InstantPopup");
  controls_choicebox.append(PROPERTY_PopupMode);

  PROPERTY_ToolBarRole = new _property_choicebox(fr, "ToolBarRole");
  connect(PROPERTY_ToolBarRole->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ToolBarRole())); 
  PROPERTY_ToolBarRole->set("WhatsThis;");
  controls_choicebox.append(PROPERTY_ToolBarRole);


  PROPERTY_MenuBarRole = new _property_choicebox(fr, "MenuBarRole");
  connect(PROPERTY_MenuBarRole->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MenuBarRole()));
  PROPERTY_MenuBarRole->set("NoRole;TextHeuristicRole;ApplicationSpecificRole;AboutQtRole;AboutRole;PreferencesRole;QuitRole");
  controls_choicebox.append(PROPERTY_MenuBarRole);


  PROPERTY_RootIsDecorated = new _property_booleancombobox(fr, "RootIsDecorated");
  connect(PROPERTY_RootIsDecorated, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_RootIsDecorated()));
  connect(PROPERTY_RootIsDecorated, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_RootIsDecorated())); 
  controls_booleancombobox.append(PROPERTY_RootIsDecorated);
  

  PROPERTY_SQL = new _property_lineedit(fr, "SQL", true);
  connect(PROPERTY_SQL, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_SQL()));
  //connect(PROPERTY_SQL, SIGNAL(lostFocus()), this, SLOT(SLOTPROPERTY_SQL()));
  controls_lineedit.append(PROPERTY_SQL);



  PROPERTY_BorderTop = new _property_pixeledit(fr, "BorderTop");
  connect(PROPERTY_BorderTop->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_BorderTop()));
  controls_pixeledit.append(PROPERTY_BorderTop);

  PROPERTY_BorderBottom = new _property_pixeledit(fr, "BorderBottom");
  connect(PROPERTY_BorderBottom->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_BorderBottom()));
  controls_pixeledit.append(PROPERTY_BorderBottom);

  PROPERTY_BorderLeft = new _property_pixeledit(fr, "BorderLeft");
  connect(PROPERTY_BorderLeft->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_BorderLeft()));
  controls_pixeledit.append(PROPERTY_BorderLeft);

  PROPERTY_BorderRight = new _property_pixeledit(fr, "BorderRight");
  connect(PROPERTY_BorderRight->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_BorderRight()));
  controls_pixeledit.append(PROPERTY_BorderRight);




  PROPERTY_Dock = new _property_choicebox(fr, "Dock");
  connect(PROPERTY_Dock->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Dock())); 
  PROPERTY_Dock->set("Closable;VerticalTitleBar;Movable;Floatable;AllFeatures;NoFeatures;All;No;Left;Right;Top;Bottom;SetLeft;SetRight;SetTop;SetBottom");
  controls_choicebox.append(PROPERTY_Dock);

  


  PROPERTY_DockTitleVisible = new _property_booleancombobox(fr, "DockCaptionVisible");
  connect(PROPERTY_DockTitleVisible, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_DockTitleVisible()));
  connect(PROPERTY_DockTitleVisible, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_DockTitleVisible())); 
  controls_booleancombobox.append(PROPERTY_DockTitleVisible);

  PROPERTY_DockOrder = new _property_lineedit(fr, "DockTabify", false);
  connect(PROPERTY_DockOrder, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_DockOrder()));
  controls_lineedit.append(PROPERTY_DockOrder);

  PROPERTY_DockSplit = new _property_lineedit(fr, "DockSplit", false);
  connect(PROPERTY_DockSplit, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_DockSplit()));
  controls_lineedit.append(PROPERTY_DockSplit);

  

  PROPERTY_DockWidth = new _property_pixeledit(fr, "DockWidth");
  connect(PROPERTY_DockWidth->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_DockWidth()));
  controls_pixeledit.append(PROPERTY_DockWidth);

  PROPERTY_DockHeight = new _property_pixeledit(fr, "DockHeight");
  connect(PROPERTY_DockHeight->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_DockHeight()));
  controls_pixeledit.append(PROPERTY_DockHeight);


  PROPERTY_MultiPageHeight = new _property_pixeledit(fr, "MultiPageHeight");
  connect(PROPERTY_MultiPageHeight->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MultiPageHeight()));
  controls_pixeledit.append(PROPERTY_MultiPageHeight);


  PROPERTY_MultiPageBorderTop = new _property_pixeledit(fr, "MultiPageBorderTop");
  connect(PROPERTY_MultiPageBorderTop->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MultiPageBorderTop()));
  controls_pixeledit.append(PROPERTY_MultiPageBorderTop);

  PROPERTY_MultiPageBorderBottom = new _property_pixeledit(fr, "MultiPageBorderBottom");
  connect(PROPERTY_MultiPageBorderBottom->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MultiPageBorderBottom()));
  controls_pixeledit.append(PROPERTY_MultiPageBorderBottom);

  PROPERTY_MultiPageBorderLeft = new _property_pixeledit(fr, "MultiPageBorderLeft");
  connect(PROPERTY_MultiPageBorderLeft->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MultiPageBorderLeft()));
  controls_pixeledit.append(PROPERTY_MultiPageBorderLeft);

  PROPERTY_MultiPageBorderRight = new _property_pixeledit(fr, "MultiPageBorderRight");
  connect(PROPERTY_MultiPageBorderRight->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MultiPageBorderRight()));
  controls_pixeledit.append(PROPERTY_MultiPageBorderRight);



  PROPERTY_ScrollX = new _property_pixeledit(fr, "ScrollX");
  connect(PROPERTY_ScrollX->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ScrollX()));
  controls_pixeledit.append(PROPERTY_ScrollX);

  PROPERTY_ScrollY = new _property_pixeledit(fr, "ScrollY");
  connect(PROPERTY_ScrollY->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ScrollY()));
  controls_pixeledit.append(PROPERTY_ScrollY);

  PROPERTY_ScrollWidth = new _property_pixeledit(fr, "ScrollWidth");
  connect(PROPERTY_ScrollWidth->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ScrollWidth()));
  controls_pixeledit.append(PROPERTY_ScrollWidth);

  PROPERTY_ScrollHeight = new _property_pixeledit(fr, "ScrollHeight");
  connect(PROPERTY_ScrollHeight->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ScrollHeight()));
  controls_pixeledit.append(PROPERTY_ScrollHeight);

  PROPERTY_ScrollBar = new _property_choicebox(fr, "ScrollBar");
  connect(PROPERTY_ScrollBar->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ScrollBar())); 
  PROPERTY_ScrollBar->set("XScrollBarAsNeeded;XScrollBarAlwaysOff;XScrollBarAlwaysOn;YScrollBarAsNeeded;YScrollBarAlwaysOff;YScrollBarAlwaysOn");  
  controls_choicebox.append(PROPERTY_ScrollBar);

    
  PROPERTY_MoveOnMouseDrag = new _property_booleancombobox(fr, "MoveOnMouseDrag");
  connect(PROPERTY_MoveOnMouseDrag, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_MoveOnMouseDrag()));
  connect(PROPERTY_MoveOnMouseDrag, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_MoveOnMouseDrag())); 
  controls_booleancombobox.append(PROPERTY_MoveOnMouseDrag);


  PROPERTY_HomeURL = new _property_fileedit(fr, "HomeURL");
  connect(PROPERTY_HomeURL->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_HomeURL()));
  controls_fileedit.append(PROPERTY_HomeURL);


  PROPERTY_OpenLinks = new _property_booleancombobox(fr, "OpenLinks");
  connect(PROPERTY_OpenLinks, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_OpenLinks()));
  connect(PROPERTY_OpenLinks, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_OpenLinks())); 
  controls_booleancombobox.append(PROPERTY_OpenLinks);

  PROPERTY_InputControl = new _property_lineedit(fr, "InputControl", false);
  connect(PROPERTY_InputControl, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_InputControl()));
  controls_lineedit.append(PROPERTY_InputControl);


  PROPERTY_IntegerMaximum = new _property_lineedit(fr, "Maximum", false);
  connect(PROPERTY_IntegerMaximum, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_IntegerMaximum()));
  controls_lineedit.append(PROPERTY_IntegerMaximum);

  PROPERTY_IntegerMinimum = new _property_lineedit(fr, "Minimum", false);
  connect(PROPERTY_IntegerMinimum, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_IntegerMinimum()));
  controls_lineedit.append(PROPERTY_IntegerMinimum);



  PROPERTY_TickPosition = new _property_choicebox(fr, "TickPosition");
  connect(PROPERTY_TickPosition->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_TickPosition())); 
  PROPERTY_TickPosition->set("NoTicks;TicksBothSides;TicksAbove;TicksBelow;TicksLeft;TicksRight");  
  controls_choicebox.append(PROPERTY_TickPosition);


  PROPERTY_InvertedAppearance = new _property_booleancombobox(fr, "InvertedAppearance");
  connect(PROPERTY_InvertedAppearance, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_InvertedAppearance()));
  connect(PROPERTY_InvertedAppearance, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_InvertedAppearance())); 
  controls_booleancombobox.append(PROPERTY_InvertedAppearance);

  PROPERTY_InvertedControls = new _property_booleancombobox(fr, "InvertedControls");
  connect(PROPERTY_InvertedControls, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_InvertedControls()));
  connect(PROPERTY_InvertedControls, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_InvertedControls())); 
  controls_booleancombobox.append(PROPERTY_InvertedControls);

  PROPERTY_Tracking = new _property_booleancombobox(fr, "Tracking");
  connect(PROPERTY_Tracking, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Tracking()));
  connect(PROPERTY_Tracking, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Tracking())); 
  controls_booleancombobox.append(PROPERTY_Tracking);

  PROPERTY_TickInterval = new _property_lineedit(fr, "TickInterval", false);
  connect(PROPERTY_TickInterval, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_TickInterval()));
  controls_lineedit.append(PROPERTY_TickInterval);

  PROPERTY_PageStep = new _property_lineedit(fr, "PageStep", false);
  connect(PROPERTY_PageStep, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_PageStep()));
  controls_lineedit.append(PROPERTY_PageStep);

  PROPERTY_SingleStep = new _property_lineedit(fr, "SingleStep", false);
  connect(PROPERTY_SingleStep, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_SingleStep()));
  controls_lineedit.append(PROPERTY_SingleStep);

  PROPERTY_StringMaximum = new _property_lineedit(fr, "Maximum", false);
  connect(PROPERTY_StringMaximum, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_StringMaximum()));
  controls_lineedit.append(PROPERTY_StringMaximum);


  PROPERTY_StringMinimum = new _property_lineedit(fr, "Minimum", false);
  connect(PROPERTY_StringMinimum, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_StringMinimum()));
  controls_lineedit.append(PROPERTY_StringMinimum);


  PROPERTY_Completer = new _property_lineedit(fr, "Completer (CSV)", true);
  connect(PROPERTY_Completer, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Completer()));
  controls_lineedit.append(PROPERTY_Completer);

  PROPERTY_ValidatorDouble = new _property_booleancombobox(fr, "ValidatorDouble");
  connect(PROPERTY_ValidatorDouble, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_ValidatorDouble()));
  connect(PROPERTY_ValidatorDouble, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_ValidatorDouble())); 
  controls_booleancombobox.append(PROPERTY_ValidatorDouble);


  PROPERTY_ValidatorInteger = new _property_booleancombobox(fr, "ValidatorInteger");
  connect(PROPERTY_ValidatorInteger, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_ValidatorInteger()));
  connect(PROPERTY_ValidatorInteger, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_ValidatorInteger())); 
  controls_booleancombobox.append(PROPERTY_ValidatorInteger);


  PROPERTY_DoubleEntry = new _property_booleancombobox(fr, "DoubleEntry");
  connect(PROPERTY_DoubleEntry, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_DoubleEntry()));
  connect(PROPERTY_DoubleEntry, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_DoubleEntry())); 
  controls_booleancombobox.append(PROPERTY_DoubleEntry);


  PROPERTY_InsertPolicy = new _property_choicebox(fr, "InsertPolicy");
  connect(PROPERTY_InsertPolicy->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_InsertPolicy())); 
  PROPERTY_InsertPolicy->set("NoInsert;InsertAtTop;InsertAtCurrent;InsertAtBottom;InsertAfterCurrent;InsertBeforeCurrent;InsertAlphabetically");  
  controls_choicebox.append(PROPERTY_InsertPolicy);


  PROPERTY_ReadOnly = new _property_booleancombobox(fr, "ReadOnly");
  connect(PROPERTY_ReadOnly, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_ReadOnly()));
  connect(PROPERTY_ReadOnly, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_ReadOnly())); 

  controls_booleancombobox.append(PROPERTY_ReadOnly);

  PROPERTY_Editable = new _property_booleancombobox(fr, "Editable");
  connect(PROPERTY_Editable, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Editable()));
  connect(PROPERTY_Editable, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Editable())); 
  controls_booleancombobox.append(PROPERTY_Editable);

  PROPERTY_Sorted = new _property_booleancombobox(fr, "Sorted");
  connect(PROPERTY_Sorted, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Sorted()));
  connect(PROPERTY_Sorted, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Sorted())); 
  controls_booleancombobox.append(PROPERTY_Sorted);


  PROPERTY_PopUp = new _property_booleancombobox(fr, "PopUp");
  connect(PROPERTY_PopUp, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_PopUp()));
  connect(PROPERTY_PopUp, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_PopUp())); 
  controls_booleancombobox.append(PROPERTY_PopUp);




  PROPERTY_EventOnOpen = new _property_booleancombobox(fr, "EventOnOpen");
  connect(PROPERTY_EventOnOpen, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_EventOnOpen()));
  connect(PROPERTY_EventOnOpen, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_EventOnOpen())); 
  controls_booleancombobox.append(PROPERTY_EventOnOpen);


  PROPERTY_AcceptRichText = new _property_booleancombobox(fr, "AcceptRichText");
  connect(PROPERTY_AcceptRichText, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_AcceptRichText()));
  connect(PROPERTY_AcceptRichText, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_AcceptRichText())); 

  controls_booleancombobox.append(PROPERTY_AcceptRichText);


  PROPERTY_AutoDefault = new _property_booleancombobox(fr, "AutoDefault");
  connect(PROPERTY_AutoDefault, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_AutoDefault()));
  connect(PROPERTY_AutoDefault, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_AutoDefault())); 

  controls_booleancombobox.append(PROPERTY_AutoDefault);


  PROPERTY_Default = new _property_booleancombobox(fr, "Default");
  connect(PROPERTY_Default, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Default()));
  connect(PROPERTY_Default, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Default())); 

  controls_booleancombobox.append(PROPERTY_Default);


  PROPERTY_Checkable = new _property_booleancombobox(fr, "Checkable");
  connect(PROPERTY_Checkable, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Checkable()));
  connect(PROPERTY_Checkable, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Checkable())); 
  controls_booleancombobox.append(PROPERTY_Checkable);

  PROPERTY_CheckableExclusive = new _property_booleancombobox(fr, "CheckableExclusive");
  connect(PROPERTY_CheckableExclusive, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_CheckableExclusive()));
  connect(PROPERTY_CheckableExclusive, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_CheckableExclusive())); 
  controls_booleancombobox.append(PROPERTY_CheckableExclusive); 



  PROPERTY_ContextMenu = new _property_lineedit(fr, "ContextMenu", false);
  connect(PROPERTY_ContextMenu, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ContextMenu()));
  controls_lineedit.append(PROPERTY_ContextMenu);



  PROPERTY_EchoMode = new _property_choicebox(fr, "EchoMode");
  connect(PROPERTY_EchoMode->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_EchoMode())); 
  PROPERTY_EchoMode->set("Normal;NoEcho;Password;PasswordEchoOnEdit");  
  controls_choicebox.append(PROPERTY_EchoMode);



  PROPERTY_InputMask = new _property_lineedit(fr, "InputMask", false);
  connect(PROPERTY_InputMask, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_InputMask()));
  //connect(PROPERTY_InputMask, SIGNAL(lostFocus()), this, SLOT(SLOTPROPERTY_InputMask()));

  //l = new _property_label(, fr, PROPERTY_InputMask);
  //PROPERTY_InputMask->setNeighbour(l);
  controls_lineedit.append(PROPERTY_InputMask);


  PROPERTY_Interval = new _property_lineedit(fr, "Interval", false);
  connect(PROPERTY_Interval, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Interval()));
  controls_lineedit.append(PROPERTY_Interval);



  PROPERTY_Format = new _property_lineedit(fr, "Format", false);
  connect(PROPERTY_Format, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Format()));
  controls_lineedit.append(PROPERTY_Format);



  PROPERTY_Pages = new _property_lineedit(fr, "Pages", false);
  connect(PROPERTY_Pages, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Pages()));
  controls_lineedit.append(PROPERTY_Pages);


  PROPERTY_Brightness = new _property_lineedit(fr, "Brightness", false);
  connect(PROPERTY_Brightness, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Brightness()));
  controls_lineedit.append(PROPERTY_Brightness);
  
  PROPERTY_Contrast = new _property_lineedit(fr, "Contrast", false);
  connect(PROPERTY_Contrast, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Contrast()));
  controls_lineedit.append(PROPERTY_Contrast);
  
  PROPERTY_Hue = new _property_lineedit(fr, "Hue", false);
  connect(PROPERTY_Hue, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Hue()));
  controls_lineedit.append(PROPERTY_Hue);
  
  PROPERTY_Saturation = new _property_lineedit(fr, "Saturation", false);
  connect(PROPERTY_Saturation, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Saturation()));
  controls_lineedit.append(PROPERTY_Saturation);
  
  
  PROPERTY_ScaleMode = new _property_choicebox(fr, "ScaleMode");
  connect(PROPERTY_ScaleMode->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ScaleMode())); 
  PROPERTY_ScaleMode->set("FitInView;ScaleAndCrop");  
  controls_choicebox.append(PROPERTY_ScaleMode);

  PROPERTY_AspectRatio = new _property_choicebox(fr, "AspectRatio");
  connect(PROPERTY_AspectRatio->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_AspectRatio())); 
  PROPERTY_AspectRatio->set("AspectRatioAuto;AspectRatioWidget;AspectRatio4_3;AspectRatio16_9");  
  controls_choicebox.append(PROPERTY_AspectRatio);

  PROPERTY_TransitionTime = new _property_lineedit(fr, "TransitionTime", false);
  connect(PROPERTY_TransitionTime, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_TransitionTime()));
  controls_lineedit.append(PROPERTY_TransitionTime);
  
  PROPERTY_Muted = new _property_booleancombobox(fr, "Muted");
  connect(PROPERTY_Muted, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Muted()));
  connect(PROPERTY_Muted, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Muted())); 
  controls_booleancombobox.append(PROPERTY_Muted);

  PROPERTY_Volume = new _property_lineedit(fr, "Volume", false);
  connect(PROPERTY_Volume, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Volume()));
  controls_lineedit.append(PROPERTY_Volume);
  
  PROPERTY_PrefinishMark = new _property_lineedit(fr, "PrefinishMark", false);
  connect(PROPERTY_PrefinishMark, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_PrefinishMark()));
  controls_lineedit.append(PROPERTY_PrefinishMark);
  
  PROPERTY_Tick = new _property_lineedit(fr, "Tick", false);
  connect(PROPERTY_Tick, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Tick()));
  controls_lineedit.append(PROPERTY_Tick);
  

  k = PROPERTY_OnTick = new _property_event(fr, "OnTick");
  PROPERTY_OnTick->setPropertyWindow(this);
  connect(PROPERTY_OnTick->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnTick()));   
  controls_event.append(k);

  k = PROPERTY_OnStateChanged = new _property_event(fr, "OnStateChanged");
  PROPERTY_OnStateChanged->setPropertyWindow(this);
  connect(PROPERTY_OnStateChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnStateChanged()));   
  controls_event.append(k);

  k = PROPERTY_OnAboutToFinish = new _property_event(fr, "OnAboutToFinish");
  PROPERTY_OnAboutToFinish->setPropertyWindow(this);
  connect(PROPERTY_OnAboutToFinish->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnAboutToFinish()));   
  controls_event.append(k);

  k = PROPERTY_OnFinished = new _property_event(fr, "OnFinished");
  PROPERTY_OnFinished->setPropertyWindow(this);
  connect(PROPERTY_OnFinished->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnFinished()));   
  controls_event.append(k);

  k = PROPERTY_OnMutedChanged = new _property_event(fr, "OnMutedChanged");
  PROPERTY_OnMutedChanged->setPropertyWindow(this);
  connect(PROPERTY_OnMutedChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnMutedChanged()));   
  controls_event.append(k);

  k = PROPERTY_OnVolumeChanged = new _property_event(fr, "OnVolumeChanged");
  PROPERTY_OnVolumeChanged->setPropertyWindow(this);
  connect(PROPERTY_OnVolumeChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnVolumeChanged()));   
  controls_event.append(k);

  k = PROPERTY_OnPlayingTitleChanged = new _property_event(fr, "OnPlayingTitleChanged");
  PROPERTY_OnPlayingTitleChanged->setPropertyWindow(this);
  connect(PROPERTY_OnPlayingTitleChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnPlayingTitleChanged()));   
  controls_event.append(k);

  k = PROPERTY_OnBufferStatus = new _property_event(fr, "OnBufferStatus");
  PROPERTY_OnBufferStatus->setPropertyWindow(this);
  connect(PROPERTY_OnBufferStatus->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnBufferStatus()));   
  controls_event.append(k);

  k = PROPERTY_OnTotalTimeChanged = new _property_event(fr, "OnTotalTimeChanged");
  PROPERTY_OnTotalTimeChanged->setPropertyWindow(this);
  connect(PROPERTY_OnTotalTimeChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnTotalTimeChanged()));   
  controls_event.append(k);

  k = PROPERTY_OnGoTo = new _property_event(fr, "OnGoTo");
  PROPERTY_OnGoTo->setPropertyWindow(this);
  connect(PROPERTY_OnGoTo->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnGoTo()));   
  controls_event.append(k);    

  k = PROPERTY_OnQuery = new _property_event(fr, "OnQuery");
  PROPERTY_OnQuery->setPropertyWindow(this);
  connect(PROPERTY_OnQuery->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnQuery()));   
  controls_event.append(k);

  k = PROPERTY_OnAddNew = new _property_event(fr, "OnAddNew");
  PROPERTY_OnAddNew->setPropertyWindow(this);
  connect(PROPERTY_OnAddNew->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnAddNew()));   
  controls_event.append(k);

  k = PROPERTY_OnDirty = new _property_event(fr, "OnDirty");
  PROPERTY_OnDirty->setPropertyWindow(this);
  connect(PROPERTY_OnDirty->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDirty()));   
  controls_event.append(k);


  k = PROPERTY_OnBeforeUpdate = new _property_event(fr, "OnBeforeUpdate");
  PROPERTY_OnBeforeUpdate->setPropertyWindow(this);
  connect(PROPERTY_OnBeforeUpdate->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnBeforeUpdate()));   

   controls_event.append(k);    


  k = PROPERTY_OnBeforeInsert = new _property_event(fr, "OnBeforeInsert");
  PROPERTY_OnBeforeInsert->setPropertyWindow(this);
  connect(PROPERTY_OnBeforeInsert->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnBeforeInsert()));   
  controls_event.append(k);    


  k = PROPERTY_OnBeforeDelete = new _property_event(fr, "OnBeforeDelete");
  PROPERTY_OnBeforeDelete->setPropertyWindow(this);
  connect(PROPERTY_OnBeforeDelete->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnBeforeDelete()));   
  controls_event.append(k);    


  k = PROPERTY_OnEvent = new _property_event(fr, "OnEvent");
  PROPERTY_OnEvent->setPropertyWindow(this);
  connect(PROPERTY_OnEvent->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnEvent()));   
  controls_event.append(k);

  // EVENT
  /*
  k = PROPERTY_OnCursorPositionChanged = new _property_event(fr, "OnCursorPositionChanged");
  PROPERTY_OnCursorPositionChanged->setPropertyWindow(this);
  connect(PROPERTY_OnCursorPositionChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnCursorPositionChanged()));   
  controls_event.append(k);
*/
  k = PROPERTY_OnEditingFinished = new _property_event(fr, "OnEditingFinished");
  PROPERTY_OnEditingFinished->setPropertyWindow(this);
  connect(PROPERTY_OnEditingFinished->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnEditingFinished()));   
  controls_event.append(k);

  k = PROPERTY_OnReturnPressed = new _property_event(fr, "OnReturnPressed");
  PROPERTY_OnReturnPressed->setPropertyWindow(this);
  connect(PROPERTY_OnReturnPressed->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnReturnPressed()));   
  controls_event.append(k);

  k = PROPERTY_OnSelectionChanged = new _property_event(fr, "OnSelectionChanged");
  PROPERTY_OnSelectionChanged->setPropertyWindow(this);
  connect(PROPERTY_OnSelectionChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnSelectionChanged()));   
  controls_event.append(k);

  k = PROPERTY_OnTextChanged = new _property_event(fr, "OnTextChanged");
  PROPERTY_OnTextChanged->setPropertyWindow(this);
  connect(PROPERTY_OnTextChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnTextChanged()));   
  controls_event.append(k);

  k = PROPERTY_OnTextEdited = new _property_event(fr, "OnTextEdited");
  PROPERTY_OnTextEdited->setPropertyWindow(this);
  connect(PROPERTY_OnTextEdited->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnTextEdited()));   
  controls_event.append(k);


  k = PROPERTY_OnPage = new _property_event(fr, "OnPage");
  PROPERTY_OnPage->setPropertyWindow(this);
  connect(PROPERTY_OnPage->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnPage()));   
  controls_event.append(k);

  k = PROPERTY_OnLinkHovered = new _property_event(fr, "OnLinkHovered");
  PROPERTY_OnLinkHovered->setPropertyWindow(this);
  connect(PROPERTY_OnLinkHovered->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnLinkHovered()));   
  controls_event.append(k);

  k = PROPERTY_OnLoadFinished = new _property_event(fr, "OnLoadFinished");
  PROPERTY_OnLoadFinished->setPropertyWindow(this);
  connect(PROPERTY_OnLoadFinished->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnLoadFinished()));   
  controls_event.append(k);

  k = PROPERTY_OnLoadProgress = new _property_event(fr, "OnLoadProgress");
  PROPERTY_OnLoadProgress->setPropertyWindow(this);
  connect(PROPERTY_OnLoadProgress->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnLoadProgress()));   
  controls_event.append(k);

  k = PROPERTY_OnLoadStarted = new _property_event(fr, "OnLoadStarted");
  PROPERTY_OnLoadStarted->setPropertyWindow(this);
  connect(PROPERTY_OnLoadStarted->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnLoadStarted()));   
  controls_event.append(k);

  k = PROPERTY_OnWindowCloseRequested = new _property_event(fr, "OnWindowCloseRequested");
  PROPERTY_OnWindowCloseRequested->setPropertyWindow(this);
  connect(PROPERTY_OnWindowCloseRequested->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnWindowCloseRequested()));   
  controls_event.append(k);


  k = PROPERTY_OnAction = new _property_event(fr, "OnAction");
  PROPERTY_OnAction->setPropertyWindow(this);
  connect(PROPERTY_OnAction->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnAction()));   
  controls_event.append(k);


  k = PROPERTY_OnCursorPositionChanged = new _property_event(fr, "OnCursorPositionChanged");
  PROPERTY_OnCursorPositionChanged->setPropertyWindow(this);
  connect(PROPERTY_OnCursorPositionChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnCursorPositionChanged()));   
  controls_event.append(k);    

  k = PROPERTY_OnCurrentItemChanged = new _property_event(fr, "OnCurrentItemChanged");
  PROPERTY_OnCurrentItemChanged->setPropertyWindow(this);
  connect(PROPERTY_OnCurrentItemChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnCurrentItemChanged()));   
  controls_event.append(k);    

  k = PROPERTY_OnItemActivated = new _property_event(fr, "OnItemActivated");
  PROPERTY_OnItemActivated->setPropertyWindow(this);
  connect(PROPERTY_OnItemActivated->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnItemActivated()));   
  controls_event.append(k);    


  k = PROPERTY_OnItemChanged = new _property_event(fr, "OnItemChanged");
  PROPERTY_OnItemChanged->setPropertyWindow(this);
  connect(PROPERTY_OnItemChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnItemChanged()));   
  controls_event.append(k);    

  k = PROPERTY_OnItemClicked = new _property_event(fr, "OnItemClicked");
  PROPERTY_OnItemClicked->setPropertyWindow(this);
  connect(PROPERTY_OnItemClicked->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnItemClicked()));   
  controls_event.append(k);    

  k = PROPERTY_OnItemCollapsed = new _property_event(fr, "OnItemCollapsed");
  PROPERTY_OnItemCollapsed->setPropertyWindow(this);
  connect(PROPERTY_OnItemCollapsed->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnItemCollapsed()));   
  controls_event.append(k);    

  k = PROPERTY_OnItemDoubleClicked = new _property_event(fr, "OnItemDoubleClicked");
  PROPERTY_OnItemDoubleClicked->setPropertyWindow(this);
  connect(PROPERTY_OnItemDoubleClicked->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnItemDoubleClicked()));   
  controls_event.append(k);    

  k = PROPERTY_OnItemEntered = new _property_event(fr, "OnItemEntered");
  PROPERTY_OnItemEntered->setPropertyWindow(this);
  connect(PROPERTY_OnItemEntered->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnItemEntered()));   
  controls_event.append(k);    

  k = PROPERTY_OnItemExpanded = new _property_event(fr, "OnItemExpanded");
  PROPERTY_OnItemExpanded->setPropertyWindow(this);
  connect(PROPERTY_OnItemExpanded->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnItemExpanded()));   
  controls_event.append(k);    

  k = PROPERTY_OnItemPressed = new _property_event(fr, "OnItemPressed");
  PROPERTY_OnItemPressed->setPropertyWindow(this);
  connect(PROPERTY_OnItemPressed->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnItemPressed()));   
  controls_event.append(k);    

  k = PROPERTY_OnItemSelectionChanged = new _property_event(fr, "OnItemSelectionChanged");
  PROPERTY_OnItemSelectionChanged->setPropertyWindow(this);
  connect(PROPERTY_OnItemSelectionChanged->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnItemSelectionChanged()));   
  controls_event.append(k);    



  k = PROPERTY_OnDockMove = new _property_event(fr, "OnDockMove");
  PROPERTY_OnDockMove->setPropertyWindow(this);
  connect(PROPERTY_OnDockMove->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDockMove()));   
  controls_event.append(k);   

  k = PROPERTY_OnDockShow = new _property_event(fr, "OnDockShow");
  PROPERTY_OnDockShow->setPropertyWindow(this);
  connect(PROPERTY_OnDockShow->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDockShow()));   
  controls_event.append(k);   

  k = PROPERTY_OnDockHide = new _property_event(fr, "OnDockHide");
  PROPERTY_OnDockHide->setPropertyWindow(this);
  connect(PROPERTY_OnDockHide->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDockHide()));   
  controls_event.append(k);   

  k = PROPERTY_OnDockFloating = new _property_event(fr, "OnDockFloating");
  PROPERTY_OnDockFloating->setPropertyWindow(this);
  connect(PROPERTY_OnDockFloating->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDockFloating()));   
  controls_event.append(k);   

  k = PROPERTY_OnDockNotFloating = new _property_event(fr, "OnDockNotFloating");
  PROPERTY_OnDockNotFloating->setPropertyWindow(this);
  connect(PROPERTY_OnDockNotFloating->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDockNotFloating()));   
  controls_event.append(k);   



  PROPERTY_SoundOnEvent = new _property_lineedit(fr, "SoundOnEvent", false);
  connect(PROPERTY_SoundOnEvent, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_SoundOnEvent()));
  controls_lineedit.append(PROPERTY_SoundOnEvent);



  PROPERTY_Comment1Begin = new _property_lineedit(fr, "Comment1Begin", false);
  connect(PROPERTY_Comment1Begin, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Comment1Begin()));
  controls_lineedit.append(PROPERTY_Comment1Begin);

  PROPERTY_Comment1End = new _property_lineedit(fr, "Comment1End", false);
  connect(PROPERTY_Comment1End, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Comment1End()));
  controls_lineedit.append(PROPERTY_Comment1End);

  PROPERTY_Comment2Begin = new _property_lineedit(fr, "Comment2Begin", false);
  connect(PROPERTY_Comment2Begin, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Comment2Begin()));
  controls_lineedit.append(PROPERTY_Comment2Begin);


  PROPERTY_Keywords = new _property_lineedit(fr, "Keywords", true);
  connect(PROPERTY_Keywords, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Keywords()));
  controls_lineedit.append(PROPERTY_Keywords);

  PROPERTY_Commands = new _property_lineedit(fr, "Commands", true);
  connect(PROPERTY_Commands, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Commands()));
  controls_lineedit.append(PROPERTY_Commands);

  PROPERTY_CommentColor = new _property_coloredit(fr, "CommentColor");
  connect(PROPERTY_CommentColor->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_CommentColor()));
  controls_coloredit.append(PROPERTY_CommentColor);

  PROPERTY_KeywordColor = new _property_coloredit(fr, "KeywordColor");
  connect(PROPERTY_KeywordColor->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_KeywordColor()));
  controls_coloredit.append(PROPERTY_KeywordColor);

  PROPERTY_CommandColor = new _property_coloredit(fr, "CommandColor");
  connect(PROPERTY_CommandColor->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_CommandColor()));
  controls_coloredit.append(PROPERTY_CommandColor);


  PROPERTY_MaximumVisible = new _property_lineedit(fr, "MaximumVisible", false);
  connect(PROPERTY_MaximumVisible, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MaximumVisible()));
  controls_lineedit.append(PROPERTY_MaximumVisible);


  PROPERTY_Shadow = new _property_booleancombobox(fr, "Shadow");
  connect(PROPERTY_Shadow, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Shadow()));
  connect(PROPERTY_Shadow, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Shadow())); 
  controls_booleancombobox.append(PROPERTY_Shadow);

  PROPERTY_Shape = new _property_booleancombobox(fr, "Shape");
  connect(PROPERTY_Shape, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Shape()));
  connect(PROPERTY_Shape, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Shape())); 
  controls_booleancombobox.append(PROPERTY_Shape);


  PROPERTY_BoxIndex = new _property_lineedit(fr, "BoxIndex", false);
  connect(PROPERTY_BoxIndex, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_BoxIndex()));
  controls_lineedit.append(PROPERTY_BoxIndex);

  PROPERTY_BoxX = new _property_lineedit(fr, "BoxX", false);
  connect(PROPERTY_BoxX, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_BoxX()));
  controls_lineedit.append(PROPERTY_BoxX);

  PROPERTY_BoxY = new _property_lineedit(fr, "BoxY", false);
  connect(PROPERTY_BoxY, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_BoxY()));
   controls_lineedit.append(PROPERTY_BoxY);

  
  PROPERTY_SplitIndex = new _property_lineedit(fr, "SplitIndex", false);
  connect(PROPERTY_SplitIndex, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_SplitIndex()));
  controls_lineedit.append(PROPERTY_SplitIndex);


  PROPERTY_Scale = new _property_booleancombobox(fr, "Scale");
  connect(PROPERTY_Scale, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Scale()));
  connect(PROPERTY_Scale, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Scale())); 
  controls_booleancombobox.append(PROPERTY_Scale);

  PROPERTY_Space = new _property_lineedit(fr, "Space", false);
  connect(PROPERTY_Space, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Space()));
  controls_lineedit.append(PROPERTY_Space);

  PROPERTY_Border = new _property_lineedit(fr, "Border", false);
  connect(PROPERTY_Border, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Border()));
   controls_lineedit.append(PROPERTY_Border);


  PROPERTY_Flat = new _property_booleancombobox(fr, "Flat");
  connect(PROPERTY_Flat, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Flat()));
  connect(PROPERTY_Flat, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Flat())); 
  controls_booleancombobox.append(PROPERTY_Flat);


  PROPERTY_ViewMode = new _property_choicebox(fr, "ViewMode");
  connect(PROPERTY_ViewMode->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ViewMode())); 
  PROPERTY_ViewMode->set("ListMode;IconMode");
  controls_choicebox.append(PROPERTY_ViewMode);


  PROPERTY_Flip = new _property_booleancombobox(fr, "Flip");
  connect(PROPERTY_Flip, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Flip()));
  connect(PROPERTY_Flip, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Flip())); 
  controls_booleancombobox.append(PROPERTY_Flip);

  PROPERTY_Separator = new _property_booleancombobox(fr, "Separator");
  connect(PROPERTY_Separator, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Separator()));
  connect(PROPERTY_Separator, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Separator())); 

  controls_booleancombobox.append(PROPERTY_Separator);


  PROPERTY_WordWrap = new _property_booleancombobox(fr, "WordWrap");
  connect(PROPERTY_WordWrap, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_WordWrap()));
  connect(PROPERTY_WordWrap, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_WordWrap())); 

  controls_booleancombobox.append(PROPERTY_WordWrap);


  PROPERTY_Alignment = new _property_choicebox(fr, "Alignment");
  connect(PROPERTY_Alignment->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Alignment())); 
  PROPERTY_Alignment->set("AlignLeft;AlignRight;AlignHCenter;AlignJustify;AlignTop;AlignBottom;AlignVCenter;AlignCenter;AlignAbsolute;AlignLeading;AlignTrailing;AlignHorizontal_Mask;AlignVertical_Mask");
  controls_choicebox.append(PROPERTY_Alignment);

  

  PROPERTY_Orientation = new _property_choicebox(fr, "Orientation");
  connect(PROPERTY_Orientation->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Orientation())); 
  PROPERTY_Orientation->set("Horizontal;Vertical");
  controls_choicebox.append(PROPERTY_Orientation);

  PROPERTY_Feature = new _property_choicebox(fr, "Feature");
  connect(PROPERTY_Feature->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Feature())); 
  PROPERTY_Feature->set("NoTextInteraction;TextSelectableByMouse;TextSelectableByKeyboard;LinksAccessibleByMouse;LinksAccessibleByKeyboard;TextEditable;TextEditorInteraction;TextBrowserInteraction");
  controls_choicebox.append(PROPERTY_Feature);


  PROPERTY_Flag = new _property_choicebox(fr, "Flag");
  connect(PROPERTY_Flag->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Flag())); 
  PROPERTY_Flag->set("Dialog;Tool;SystemMenu;Title;MinimizeButton;MaximizeButton;CloseButton;ContextHelp;Frameless;StaysOnTop;Sheet;Drawer");  
  controls_choicebox.append(PROPERTY_Flag);
  

  PROPERTY_Modal = new _property_booleancombobox(fr, "Modal");
  connect(PROPERTY_Modal, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Modal()));
  connect(PROPERTY_Modal, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Modal())); 
  controls_booleancombobox.append(PROPERTY_Modal);

  PROPERTY_Checked = new _property_booleancombobox(fr, "Checked");
  connect(PROPERTY_Checked, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Checked()));
  connect(PROPERTY_Checked, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Checked())); 
  controls_booleancombobox.append(PROPERTY_Checked);

  PROPERTY_TableView = new _property_booleancombobox(fr, "TableView");
  connect(PROPERTY_TableView, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_TableView()));
  connect(PROPERTY_TableView, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_TableView())); 
  controls_booleancombobox.append(PROPERTY_TableView);

  



  PROPERTY_SelectionMode = new _property_choicebox(fr, "SelectionMode");
  connect(PROPERTY_SelectionMode->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_SelectionMode())); 
  PROPERTY_SelectionMode->set("SingleSelection;ContiguousSelection;ExtendedSelection;MultiSelection;NoSelection");
  controls_choicebox.append(PROPERTY_SelectionMode);




  PROPERTY_AlternatingRowColors = new _property_booleancombobox(fr, "AlternatingRowColors");
  connect(PROPERTY_AlternatingRowColors, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_AlternatingRowColors()));
  connect(PROPERTY_AlternatingRowColors, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_AlternatingRowColors())); 
  controls_booleancombobox.append(PROPERTY_AlternatingRowColors);


  PROPERTY_TableViewCaption = new _property_lineedit(fr, "TableViewCaption", false);
  connect(PROPERTY_TableViewCaption, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_TableViewCaption()));
  controls_lineedit.append(PROPERTY_TableViewCaption);


  PROPERTY_TableViewWidth = new _property_lineedit(fr, "TableViewWidth", false);
  connect(PROPERTY_TableViewWidth, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_TableViewWidth()));
  controls_lineedit.append(PROPERTY_TableViewWidth);

  PROPERTY_TableViewVisible = new _property_booleancombobox(fr, "TableViewVisible");
  connect(PROPERTY_TableViewVisible, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_TableViewVisible()));
  connect(PROPERTY_TableViewVisible, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_TableViewVisible())); 
  controls_booleancombobox.append(PROPERTY_TableViewVisible);



  PROPERTY_PortName = new _property_listcombobox(fr, "PortName");
  PROPERTY_PortName->setEditable(true);
  connect(PROPERTY_PortName, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_PortName()));
  connect(PROPERTY_PortName, SIGNAL(editTextChanged (const QString &)), this, SLOT(SLOTPROPERTY_PortName()));
  controls_listcombobox.append(PROPERTY_PortName);
    
#ifdef WINDOWS
  PROPERTY_PortName->addItem("COM1");
  PROPERTY_PortName->addItem("COM2");
  PROPERTY_PortName->addItem("COM3");
  PROPERTY_PortName->addItem("Try any device name");
#else
  PROPERTY_PortName->addItem("/dev/ttyS0");
  PROPERTY_PortName->addItem("/dev/ttyS1");
  PROPERTY_PortName->addItem("Try any device name");
#endif


  PROPERTY_BaudRate = new _property_listcombobox(fr, "BaudRate");
  connect(PROPERTY_BaudRate, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_BaudRate()));
  connect(PROPERTY_BaudRate, SIGNAL(editTextChanged (const QString &)), this, SLOT(SLOTPROPERTY_BaudRate()));
  controls_listcombobox.append(PROPERTY_BaudRate);
    
  PROPERTY_BaudRate->addItem("BAUD50");
  PROPERTY_BaudRate->addItem("BAUD75");
  PROPERTY_BaudRate->addItem("BAUD110");
  PROPERTY_BaudRate->addItem("BAUD134");
  PROPERTY_BaudRate->addItem("BAUD150");
  PROPERTY_BaudRate->addItem("BAUD200");
  PROPERTY_BaudRate->addItem("BAUD300");
  PROPERTY_BaudRate->addItem("BAUD600");
  PROPERTY_BaudRate->addItem("BAUD1200");
  PROPERTY_BaudRate->addItem("BAUD1800");
  PROPERTY_BaudRate->addItem("BAUD2400");
  PROPERTY_BaudRate->addItem("BAUD4800");
  PROPERTY_BaudRate->addItem("BAUD9600");
  PROPERTY_BaudRate->addItem("BAUD14400");
  PROPERTY_BaudRate->addItem("BAUD19200");
  PROPERTY_BaudRate->addItem("BAUD38400");
  PROPERTY_BaudRate->addItem("BAUD56000");
  PROPERTY_BaudRate->addItem("BAUD57600");
  PROPERTY_BaudRate->addItem("BAUD76800");
  PROPERTY_BaudRate->addItem("BAUD115200");
  PROPERTY_BaudRate->addItem("BAUD128000");
  PROPERTY_BaudRate->addItem("BAUD256000");


  PROPERTY_DataBits = new _property_listcombobox(fr, "DataBits");
  connect(PROPERTY_DataBits, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_DataBits()));
  connect(PROPERTY_DataBits, SIGNAL(editTextChanged (const QString &)), this, SLOT(SLOTPROPERTY_DataBits()));
  controls_listcombobox.append(PROPERTY_DataBits);
    
  PROPERTY_DataBits->addItem("DATA_5");
  PROPERTY_DataBits->addItem("DATA_6");
  PROPERTY_DataBits->addItem("DATA_7");
  PROPERTY_DataBits->addItem("DATA_8");


  PROPERTY_FlowControl = new _property_listcombobox(fr, "FlowControl");
  connect(PROPERTY_FlowControl, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_FlowControl()));
  connect(PROPERTY_FlowControl, SIGNAL(editTextChanged (const QString &)), this, SLOT(SLOTPROPERTY_FlowControl()));
  controls_listcombobox.append(PROPERTY_FlowControl);
    
  PROPERTY_FlowControl->addItem("FLOW_OFF");
  PROPERTY_FlowControl->addItem("FLOW_HARDWARE");
  PROPERTY_FlowControl->addItem("FLOW_XONXOFF");


  PROPERTY_Parity = new _property_listcombobox(fr, "Parity");
  connect(PROPERTY_Parity, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Parity()));
  connect(PROPERTY_Parity, SIGNAL(editTextChanged (const QString &)), this, SLOT(SLOTPROPERTY_Parity()));
  controls_listcombobox.append(PROPERTY_Parity);
    
  PROPERTY_Parity->addItem("PAR_NONE");
  PROPERTY_Parity->addItem("PAR_ODD");
  PROPERTY_Parity->addItem("PAR_EVEN");
  PROPERTY_Parity->addItem("PAR_MARK");
  PROPERTY_Parity->addItem("PAR_SPACE");


  PROPERTY_StopBits = new _property_listcombobox(fr, "StopBits");
  connect(PROPERTY_StopBits, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_StopBits()));
  connect(PROPERTY_StopBits, SIGNAL(editTextChanged (const QString &)), this, SLOT(SLOTPROPERTY_StopBits()));
  controls_listcombobox.append(PROPERTY_StopBits);

  PROPERTY_StopBits->addItem("STOP_1");
  PROPERTY_StopBits->addItem("STOP_1_5");
  PROPERTY_StopBits->addItem("STOP_2");


  PROPERTY_TimeoutMillisec = new _property_lineedit(fr, "TimeOutMillisec", false);
  connect(PROPERTY_TimeoutMillisec, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_TimeoutMillisec()));
  controls_lineedit.append(PROPERTY_TimeoutMillisec);

  PROPERTY_PollingInterval = new _property_lineedit(fr, "PollingInterval", false);
  connect(PROPERTY_PollingInterval, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_PollingInterval()));
  controls_lineedit.append(PROPERTY_PollingInterval);





  PROPERTY_SQLName = new _property_lineedit(fr, "SQLName", true);
  connect(PROPERTY_SQLName, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_SQLName()));
  controls_lineedit.append(PROPERTY_SQLName);

  PROPERTY_SQLRelation = new _property_lineedit(fr, "SQLRelation", true);
  connect(PROPERTY_SQLRelation, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_SQLRelation()));
  controls_lineedit.append(PROPERTY_SQLRelation);



  PROPERTY_SQLInsert = new _property_booleancombobox(fr, "SQLInsert");
  connect(PROPERTY_SQLInsert, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_SQLInsert()));
  connect(PROPERTY_SQLInsert, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_SQLInsert())); 
  controls_booleancombobox.append(PROPERTY_SQLInsert);


  PROPERTY_SQLUpdate = new _property_booleancombobox(fr, "SQLUpdate");
  connect(PROPERTY_SQLUpdate, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_SQLUpdate()));
  connect(PROPERTY_SQLUpdate, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_SQLUpdate())); 
  controls_booleancombobox.append(PROPERTY_SQLUpdate);


  PROPERTY_SQLDelete = new _property_booleancombobox(fr, "SQLDelete");
  connect(PROPERTY_SQLDelete, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_SQLDelete()));
  connect(PROPERTY_SQLDelete, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_SQLDelete())); 
  controls_booleancombobox.append(PROPERTY_SQLDelete);



  PROPERTY_CSV = new _property_lineedit(fr, "CSV", true);
  connect(PROPERTY_CSV, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_CSV()));
  controls_lineedit.append(PROPERTY_CSV);

  PROPERTY_Tag = new _property_lineedit(fr, "Tag", false);
  connect(PROPERTY_Tag, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Tag()));
  controls_lineedit.append(PROPERTY_Tag);



  PROPERTY_Data = new _property_lineedit(fr, "Data", false);
  connect(PROPERTY_Data, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Data()));
  controls_lineedit.append(PROPERTY_Data);



  PROPERTY_FocusOrder = new _property_lineedit(fr, "FocusOrder", false);
  connect(PROPERTY_FocusOrder, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_FocusOrder()));
  controls_lineedit.append(PROPERTY_FocusOrder);

  PROPERTY_FocusPolicy = new _property_choicebox(fr, "FocusPolicy");
  connect(PROPERTY_FocusPolicy->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_FocusPolicy())); 
  PROPERTY_FocusPolicy->set("TabFocus;ClickFocus;StrongFocus;WheelFocus;NoFocus");  
  controls_choicebox.append(PROPERTY_FocusPolicy);


  PROPERTY_FocusProxy = new _property_lineedit(fr, "FocusProxy", false);
  connect(PROPERTY_FocusProxy, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_FocusProxy()));
  controls_lineedit.append(PROPERTY_FocusProxy);



  PROPERTY_MinimumWidth = new _property_lineedit(fr, "MinimumWidth", false);
  connect(PROPERTY_MinimumWidth, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MinimumWidth()));
  controls_lineedit.append(PROPERTY_MinimumWidth);

  PROPERTY_MinimumHeight = new _property_lineedit(fr, "MinimumHeight", false);
  connect(PROPERTY_MinimumHeight, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MinimumHeight()));
  controls_lineedit.append(PROPERTY_MinimumHeight);

  PROPERTY_MaximumWidth = new _property_lineedit(fr, "MaximumWidth", false);
  connect(PROPERTY_MaximumWidth, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MaximumWidth()));
  controls_lineedit.append(PROPERTY_MaximumWidth);

  PROPERTY_MaximumHeight = new _property_lineedit(fr, "MaximumHeight", false);
  connect(PROPERTY_MaximumHeight, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MaximumHeight()));
  controls_lineedit.append(PROPERTY_MaximumHeight);


  PROPERTY_FontName = new _property_fontedit(fr, "FontName");
  connect(PROPERTY_FontName->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_FontName()));
  controls_fontedit.append(PROPERTY_FontName);

  PROPERTY_FontSize = new _property_listcombobox(fr, "FontSize");
  connect(PROPERTY_FontSize, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_FontSize()));
  connect(PROPERTY_FontSize, SIGNAL(editTextChanged (const QString &)), this, SLOT(SLOTPROPERTY_FontSize()));
  
  
  PROPERTY_FontSize->setEditable(true);
  PROPERTY_FontSize->addItem("6");
  PROPERTY_FontSize->addItem("8");
  PROPERTY_FontSize->addItem("10");
  PROPERTY_FontSize->addItem("12");
  PROPERTY_FontSize->addItem("14");
  PROPERTY_FontSize->addItem("16");
  PROPERTY_FontSize->addItem("18");
  PROPERTY_FontSize->addItem("20");
  PROPERTY_FontSize->addItem("22");
  PROPERTY_FontSize->addItem("24");
  PROPERTY_FontSize->addItem("26");
  PROPERTY_FontSize->addItem("28");
  PROPERTY_FontSize->addItem("30");
  PROPERTY_FontSize->addItem("40");
  PROPERTY_FontSize->addItem("50");

  controls_listcombobox.append(PROPERTY_FontSize);


  PROPERTY_FontBold = new _property_booleancombobox(fr, "FontBold");
  connect(PROPERTY_FontBold, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_FontBold()));
  connect(PROPERTY_FontBold, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_FontBold())); 
  controls_booleancombobox.append(PROPERTY_FontBold);

  PROPERTY_FontItalic = new _property_booleancombobox(fr, "FontItalic");
  connect(PROPERTY_FontItalic, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_FontItalic()));
  connect(PROPERTY_FontItalic, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_FontItalic())); 
  controls_booleancombobox.append(PROPERTY_FontItalic);

  PROPERTY_FontUnderline = new _property_booleancombobox(fr, "FontUnderline");
  connect(PROPERTY_FontUnderline, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_FontUnderline()));
  connect(PROPERTY_FontUnderline, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_FontUnderline())); 
  controls_booleancombobox.append(PROPERTY_FontUnderline);



  PROPERTY_FontColor = new _property_coloredit(fr, "FontColor");
  connect(PROPERTY_FontColor->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_FontColor()));
  controls_coloredit.append(PROPERTY_FontColor);


  PROPERTY_Background = new _property_colorimageedit(fr, "Background");
  connect(PROPERTY_Background->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Background()));
  controls_colorimageedit.append(PROPERTY_Background);


  PROPERTY_BackgroundStyle = new _property_choicebox(fr, "BackgroundStyle");
  connect(PROPERTY_BackgroundStyle->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_BackgroundStyle())); 
  PROPERTY_BackgroundStyle->set("Gradient;");  
  controls_choicebox.append(PROPERTY_BackgroundStyle);


  PROPERTY_Palette = new _property_lineedit(fr, "Palette", true);
  connect(PROPERTY_Palette, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Palette()));
  controls_lineedit.append(PROPERTY_Palette);

  
  PROPERTY_DrawOnPaint = new _property_booleancombobox(fr, "DrawOnPaint");
  connect(PROPERTY_DrawOnPaint, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_DrawOnPaint()));
  connect(PROPERTY_DrawOnPaint, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_DrawOnPaint())); 
  controls_booleancombobox.append(PROPERTY_DrawOnPaint);

  
  PROPERTY_MouseTracking = new _property_booleancombobox(fr, "MouseTracking");
  connect(PROPERTY_MouseTracking, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_MouseTracking()));
  connect(PROPERTY_MouseTracking, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_MouseTracking())); 
  controls_booleancombobox.append(PROPERTY_MouseTracking);





  PROPERTY_DragDrop = new _property_booleancombobox(fr, "DragDrop");
  connect(PROPERTY_DragDrop, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_DragDrop()));
  connect(PROPERTY_DragDrop, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_DragDrop())); 
  controls_booleancombobox.append(PROPERTY_DragDrop);


  PROPERTY_StyleSheet = new _property_lineedit(fr, "StyleSheet", false);
  connect(PROPERTY_StyleSheet, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_StyleSheet()));
  controls_lineedit.append(PROPERTY_StyleSheet);


  PROPERTY_StatusTip = new _property_lineedit(fr, "StatusTip", true);
  connect(PROPERTY_StatusTip, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_StatusTip()));
  controls_lineedit.append(PROPERTY_StatusTip);

  PROPERTY_ToolTip = new _property_lineedit(fr, "ToolTip", true);
  connect(PROPERTY_ToolTip, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ToolTip()));
  controls_lineedit.append(PROPERTY_ToolTip);


  PROPERTY_WhatsThis = new _property_lineedit(fr, "WhatsThis", true);
  connect(PROPERTY_WhatsThis, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_WhatsThis()));
  controls_lineedit.append(PROPERTY_WhatsThis);

 
  PROPERTY_Mask = new _property_lineedit(fr, "Mask", false);
  connect(PROPERTY_Mask, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_Mask()));
  controls_lineedit.append(PROPERTY_Mask);

  PROPERTY_Opacity = new _property_listcombobox(fr, "Opacity");
  connect(PROPERTY_Opacity, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Opacity()));
  connect(PROPERTY_Opacity, SIGNAL(editTextChanged (const QString &)), this, SLOT(SLOTPROPERTY_Opacity()));

  PROPERTY_Opacity->setEditable(true);
  PROPERTY_Opacity->addItem("0");
  PROPERTY_Opacity->addItem("10");
  PROPERTY_Opacity->addItem("20");
  PROPERTY_Opacity->addItem("30");
  PROPERTY_Opacity->addItem("40");
  PROPERTY_Opacity->addItem("50");
  PROPERTY_Opacity->addItem("60");
  PROPERTY_Opacity->addItem("70");
  PROPERTY_Opacity->addItem("80");
  PROPERTY_Opacity->addItem("90");
  PROPERTY_Opacity->addItem("100");

  controls_listcombobox.append(PROPERTY_Opacity);

  PROPERTY_Cursor = new _property_listcombobox(fr, "Cursor");
  connect(PROPERTY_Cursor, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Cursor()));
  connect(PROPERTY_Cursor, SIGNAL(editTextChanged (const QString &)), this, SLOT(SLOTPROPERTY_Cursor()));
    
  PROPERTY_Cursor->setEditable(true);
  PROPERTY_Cursor->addItem("ArrowCursor");
  PROPERTY_Cursor->addItem("UpArrowCursor");
  PROPERTY_Cursor->addItem("CrossCursor");
  PROPERTY_Cursor->addItem("WaitCursor");
  PROPERTY_Cursor->addItem("IBeamCursor");
  PROPERTY_Cursor->addItem("SizeVerCursor");
  PROPERTY_Cursor->addItem("SizeHorCursor");
  PROPERTY_Cursor->addItem("SizeFDiagCursor");
  PROPERTY_Cursor->addItem("SizeBDiagCursor");
  PROPERTY_Cursor->addItem("SizeAllCursor");
  PROPERTY_Cursor->addItem("BlankCursor");
  PROPERTY_Cursor->addItem("SplitVCursor");
  PROPERTY_Cursor->addItem("SplitHCursor");
  PROPERTY_Cursor->addItem("PointingHandCursor");
  PROPERTY_Cursor->addItem("ForbiddenCursor");
  PROPERTY_Cursor->addItem("OpenHandCursor");
  PROPERTY_Cursor->addItem("ClosedHandCursor");
  PROPERTY_Cursor->addItem("WhatsThisCursor");
  PROPERTY_Cursor->addItem("BusyCursor");

  //l = new _property_label(, fr, PROPERTY_Cursor);
  //PROPERTY_Cursor->setNeighbour(l);
  controls_listcombobox.append(PROPERTY_Cursor);


  PROPERTY_CursorAnimation = new _property_listcombobox(fr, "CursorAnimation");
  connect(PROPERTY_CursorAnimation, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_CursorAnimation()));
  connect(PROPERTY_CursorAnimation, SIGNAL(editTextChanged (const QString &)), this, SLOT(SLOTPROPERTY_CursorAnimation()));    
  PROPERTY_CursorAnimation->setEditable(true);
  controls_listcombobox.append(PROPERTY_CursorAnimation);


  
  PROPERTY_TimerInterval = new _property_lineedit(fr, "TimerInterval", false);
  connect(PROPERTY_TimerInterval, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_TimerInterval()));
  controls_lineedit.append(PROPERTY_TimerInterval);



  k = PROPERTY_OnOpen = new _property_event(fr, "OnOpen");
  PROPERTY_OnOpen->setPropertyWindow(this);
  connect(PROPERTY_OnOpen->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnOpen()));   
  controls_event.append(k);
    


  k = PROPERTY_OnClose = new _property_event(fr, "OnClose");
  PROPERTY_OnClose->setPropertyWindow(this);
  connect(PROPERTY_OnClose->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnClose()));   
  controls_event.append(k);
    


  k = PROPERTY_OnPaint = new _property_event(fr, "OnPaint");
  PROPERTY_OnPaint->setPropertyWindow(this);
  connect(PROPERTY_OnPaint->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnPaint()));   
  controls_event.append(k);   


  k = PROPERTY_OnShow = new _property_event(fr, "OnShow");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnShow()));   
  controls_event.append(k);

  k = PROPERTY_OnHide = new _property_event(fr, "OnHide");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnHide()));   
  controls_event.append(k);


  k = PROPERTY_OnMove = new _property_event(fr, "OnMove");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnMove()));   
  controls_event.append(k);


  k = PROPERTY_OnResize = new _property_event(fr, "OnResize");
  PROPERTY_OnResize->setPropertyWindow(this);
  connect(PROPERTY_OnResize->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnResize()));   
  controls_event.append(k);

  k = PROPERTY_OnEnabled = new _property_event(fr, "OnEnabled");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnEnabled()));   
  controls_event.append(k);

  k = PROPERTY_OnDisabled = new _property_event(fr, "OnDisabled");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDisabled()));   
  controls_event.append(k);

  k = PROPERTY_OnTimer = new _property_event(fr, "OnTimer");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnTimer()));   
  controls_event.append(k);

  k = PROPERTY_OnClick = new _property_event(fr, "OnClick");
  PROPERTY_OnClick->setPropertyWindow(this);
  connect(PROPERTY_OnClick->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnClick()));   
  controls_event.append(k);


  k = PROPERTY_OnDblClick = new _property_event(fr, "OnDblClick");
  PROPERTY_OnDblClick->setPropertyWindow(this);
  connect(PROPERTY_OnDblClick->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDblClick()));   
  controls_event.append(k);

  k = PROPERTY_OnMouseDown = new _property_event(fr, "OnMouseDown");
  PROPERTY_OnMouseDown->setPropertyWindow(this);
  connect(PROPERTY_OnMouseDown->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnMouseDown()));   
  controls_event.append(k);

  k = PROPERTY_OnMouseUp = new _property_event(fr, "OnMouseUp");
  PROPERTY_OnMouseUp->setPropertyWindow(this);
  connect(PROPERTY_OnMouseUp->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnMouseUp()));   

  controls_event.append(k);
    


  k = PROPERTY_OnMouseMove = new _property_event(fr, "OnMouseMove");
  PROPERTY_OnMouseMove->setPropertyWindow(this);
  connect(PROPERTY_OnMouseMove->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnMouseMove()));   

  controls_event.append(k);
    


  k = PROPERTY_OnGotFocus = new _property_event(fr, "OnGotFocus");
  PROPERTY_OnGotFocus->setPropertyWindow(this);
  connect(PROPERTY_OnGotFocus->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnGotFocus()));   

  controls_event.append(k);
    


  k = PROPERTY_OnLostFocus = new _property_event(fr, "OnLostFocus");
  PROPERTY_OnLostFocus->setPropertyWindow(this);
  connect(PROPERTY_OnLostFocus->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnLostFocus()));   

  controls_event.append(k);
    


  k = PROPERTY_OnEnter = new _property_event(fr, "OnEnter");
  PROPERTY_OnEnter->setPropertyWindow(this);
  connect(PROPERTY_OnEnter->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnEnter()));   

  controls_event.append(k);
    


  k = PROPERTY_OnExit = new _property_event(fr, "OnExit");
  PROPERTY_OnExit->setPropertyWindow(this);
  connect(PROPERTY_OnExit->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnExit()));   

  controls_event.append(k);
    

  k = PROPERTY_OnKeyDown = new _property_event(fr, "OnKeyDown");
  PROPERTY_OnKeyDown->setPropertyWindow(this);
  connect(PROPERTY_OnKeyDown->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnKeyDown()));   

  controls_event.append(k);
    

  k = PROPERTY_OnKeyUp = new _property_event(fr, "OnKeyUp");
  PROPERTY_OnKeyUp->setPropertyWindow(this);
  connect(PROPERTY_OnKeyUp->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnKeyUp()));   

  controls_event.append(k);
    


  k = PROPERTY_OnKeyPress = new _property_event(fr, "OnKeyPress");
  PROPERTY_OnKeyPress->setPropertyWindow(this);
  connect(PROPERTY_OnKeyPress->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnKeyPress()));   

  controls_event.append(k);



  k = PROPERTY_OnMouseWheel = new _property_event(fr, "OnMouseWheel");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnMouseWheel()));   

  controls_event.append(k);

  
  k = PROPERTY_OnScroll = new _property_event(fr, "OnScroll");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnScroll()));   
  controls_event.append(k);

  
  k = PROPERTY_OnMultiPageShow = new _property_event(fr, "OnMultiPageShow");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnMultiPageShow()));   
  controls_event.append(k);


  
  k = PROPERTY_OnSingleShot = new _property_event(fr, "OnSingleShot");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnSingleShot()));   
  controls_event.append(k);

    
  k = PROPERTY_OnDragEnter = new _property_event(fr, "OnDragEnter");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDragEnter()));   
  controls_event.append(k);

  k = PROPERTY_OnDragMove = new _property_event(fr, "OnDragMove");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDragMove()));   
  controls_event.append(k);

  k = PROPERTY_OnDragExit = new _property_event(fr, "OnDragExit");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDragExit()));   
  controls_event.append(k);

  k = PROPERTY_OnDrop = new _property_event(fr, "OnDrop");
  k->setPropertyWindow(this);
  connect(k->lineedit(), SIGNAL(textChanged(const QString &)), this, SLOT(SLOTPROPERTY_OnDrop()));   
  controls_event.append(k);



  PROPERTY_SQLControls = new _property_choicebox(fr, "SQLControls");
  connect(PROPERTY_SQLControls->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_SQLControls())); 
  PROPERTY_SQLControls->set("First;Next;GoTo;Previous;Last;Update;Delete;Recordset;Info;AddNew");  
  controls_choicebox.append(PROPERTY_SQLControls);



  PROPERTY_Editable = new _property_booleancombobox(fr, "Editable");
  connect(PROPERTY_Editable, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Editable()));
  connect(PROPERTY_Editable, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Editable())); 
  controls_booleancombobox.append(PROPERTY_Editable);

  PROPERTY_Sorted = new _property_booleancombobox(fr, "Sorted");
  connect(PROPERTY_Sorted, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Sorted()));
  connect(PROPERTY_Sorted, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Sorted())); 

  controls_booleancombobox.append(PROPERTY_Sorted);






  PROPERTY_Shape = new _property_booleancombobox(fr, "Shape");
  connect(PROPERTY_Shape, SIGNAL(activated(int)), this, SLOT(SLOTPROPERTY_Shape()));
  connect(PROPERTY_Shape, SIGNAL(editTextChanged(const QString &)), this, SLOT(SLOTPROPERTY_Shape())); 

  controls_booleancombobox.append(PROPERTY_Shape);

  


  // PROPERTY



  PROPERTY_ParentForm = new _property_lineedit(fr, "ParentForm", false);
  connect(PROPERTY_ParentForm, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ParentForm()));
  controls_lineedit.append(PROPERTY_ParentForm);

  PROPERTY_ParentControl = new _property_lineedit(fr, "ParentControl", false);
  connect(PROPERTY_ParentControl, SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ParentControl()));

  controls_lineedit.append(PROPERTY_ParentControl);








  PROPERTY_EnabledImage = new _property_imageedit(fr, "EnabledImage");
  connect(PROPERTY_EnabledImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_EnabledImage()));
  controls_imageedit.append(PROPERTY_EnabledImage);

  PROPERTY_DisabledImage = new _property_imageedit(fr, "DisabledImage");
  connect(PROPERTY_DisabledImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_DisabledImage()));

  controls_imageedit.append(PROPERTY_DisabledImage);



  PROPERTY_EnterImage = new _property_imageedit(fr, "EnterImage");
  connect(PROPERTY_EnterImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_EnterImage()));

  controls_imageedit.append(PROPERTY_EnterImage);


  PROPERTY_ExitImage = new _property_imageedit(fr, "ExitImage");
  connect(PROPERTY_ExitImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ExitImage()));
  
  controls_imageedit.append(PROPERTY_ExitImage);


  PROPERTY_MouseDownImage = new _property_imageedit(fr, "MouseDownImage");
  connect(PROPERTY_MouseDownImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MouseDownImage()));
  
  controls_imageedit.append(PROPERTY_MouseDownImage);

  PROPERTY_MouseUpImage = new _property_imageedit(fr, "MouseUpImage");
  connect(PROPERTY_MouseUpImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MouseUpImage()));
  
  controls_imageedit.append(PROPERTY_MouseUpImage);



  PROPERTY_EnterSound = new _property_soundedit(fr, "EnterSound");
  connect(PROPERTY_EnterSound->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_EnterSound()));
  
  controls_soundedit.append(PROPERTY_EnterSound);



  PROPERTY_ExitSound = new _property_soundedit(fr, "ExitSound");
  connect(PROPERTY_ExitSound->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_ExitSound()));
  
  controls_soundedit.append(PROPERTY_ExitSound);

  PROPERTY_MouseDownSound = new _property_soundedit(fr, "MouseDownSound");
  connect(PROPERTY_MouseDownSound->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MouseDownSound()));
  
  controls_soundedit.append(PROPERTY_MouseDownSound);

  PROPERTY_MouseUpSound = new _property_soundedit(fr, "MouseUpSound");
  connect(PROPERTY_MouseUpSound->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_MouseUpSound()));
  
  controls_soundedit.append(PROPERTY_MouseUpSound);

  


  PROPERTY_CheckEnabledImage = new _property_imageedit(fr, "CheckedEnabledImage");
  connect(PROPERTY_CheckEnabledImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_CheckEnabledImage()));
  controls_imageedit.append(PROPERTY_CheckEnabledImage);

  PROPERTY_CheckDisabledImage = new _property_imageedit(fr, "CheckedDisabledImage");
  connect(PROPERTY_CheckDisabledImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_CheckDisabledImage()));
  controls_imageedit.append(PROPERTY_CheckDisabledImage);

  PROPERTY_CheckEnterImage = new _property_imageedit(fr, "CheckedEnterImage");
  connect(PROPERTY_CheckEnterImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_CheckEnterImage()));
  controls_imageedit.append(PROPERTY_CheckEnterImage);

  PROPERTY_CheckExitImage = new _property_imageedit(fr, "CheckedExitImage");
  connect(PROPERTY_CheckExitImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_CheckExitImage()));
  controls_imageedit.append(PROPERTY_CheckExitImage);

  PROPERTY_CheckMouseDownImage = new _property_imageedit(fr, "CheckedMouseDownImage");
  connect(PROPERTY_CheckMouseDownImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_CheckMouseDownImage()));
  controls_imageedit.append(PROPERTY_CheckMouseDownImage);

  PROPERTY_CheckMouseUpImage = new _property_imageedit(fr, "CheckedMouseUpImage");
  connect(PROPERTY_CheckMouseUpImage->lineedit(), SIGNAL(textChanged (const QString &)), this, SLOT(SLOTPROPERTY_CheckMouseUpImage()));
  controls_imageedit.append(PROPERTY_CheckMouseUpImage);




  
}



void _propertywindow::setEnabled(bool b)
{

  fr->setHidden(!b || bTREE);
  currentcontrolname->setHidden(!b || bTREE);
  setform->setHidden(!b || bTREE);
  a->setHidden(!b || bTREE);

  tb->setHidden(!b);

  tree->setHidden(!b || !bTREE);

}

void _propertywindow::paintEvent(QPaintEvent *e)
{
  
}


void _propertywindow::showProperties(bool bBuild, QString sForFile)
{
  
  if (nPropertyWindowForWhat == 4){ // code editor handling

    if (bTREE == false){
      bTREE = true;
      tree->setHidden(false);
      setform->setHidden(true);
      a->setHidden(true);

      aMain->setText(tr("All"));


      aSpecial->setText(tr("Methods"));

      aFormat->setText(tr(""));
      aFormat->setIcon(kbasicIcon(kbasicPath("ide/Variable.png")));

      aData->setText(tr(""));
      aData->setIcon(kbasicIcon(kbasicPath("ide/Constant.png")));

      aControl->setText(tr(""));
      aControl->setIcon(kbasicIcon(kbasicPath("ide/Property.png")));

      aEvent->setText(tr(""));
      aEvent->setIcon(kbasicIcon(kbasicPath("ide/Enum.png")));

      aType->setText(tr(""));
      aType->setIcon(kbasicIcon(kbasicPath("ide/Type.png")));

    }

    static QString sOldForFile = "";

    if (bBuild || (sOldForFile != sForFile && !sForFile.isEmpty())){ // WORKAROUND !sForFile.isEmpty()
      tree->clear();

      QTreeWidgetItem *t;

      t = _all = new QTreeWidgetItem(tree, QStringList(tr("All"))); 
      t->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));  
      t->setExpanded(true);

      _constants = new QTreeWidgetItem(_all, QStringList(tr("Constants")));
      _constants->setExpanded(true);

      _variables = new QTreeWidgetItem(_all, QStringList(tr("Variables")));
      _variables->setExpanded(true);

      _methods = new QTreeWidgetItem(_all, QStringList(tr("Methods")));
      _methods->setExpanded(true);

      _properties = new QTreeWidgetItem(_all, QStringList(tr("Properties")));
      _properties->setExpanded(true);

      _enums = new QTreeWidgetItem(_all, QStringList(tr("Enums")));
      _enums->setExpanded(true);

      _types = new QTreeWidgetItem(_all, QStringList(tr("Types")));
      _types->setExpanded(true);

      QList<_inputtip_info> l = EXTERN_my_mainwindow->ci_getAllForFile(sForFile);

      foreach (_inputtip_info v, l)
      {         

        QString ss = "";
        switch(v.type){
          case __sub: 
            if (v.name.contains("_On")){
              ss = "ide/Event.png"; t = _methods;
            } else {
              ss = "ide/Sub.png"; t = _methods; 
            }
            break;
          case __function: ss = "ide/Function.png"; t = _methods; break;
          case __constructor: ss = "ide/Constructor.png"; t = _methods; break;
          case __property2: ss = "ide/Property.png"; t = _properties; break;
          case __enum: ss = "ide/Enum.png"; t = _enums; break;
          case __type: ss = "ide/Type.png"; t = _types; break;
          case __constant: ss = "ide/Constant.png"; t = _constants; break;
          case __variable: 
            {
              ss = "ide/Variable.png";
              if (!v.type_name.isEmpty()){
                #ifdef MAC
                  ss = "ide/controls/mac/" + v.type_name.toLower() + ".png";    // HIDE
                #else
                #ifdef WINDOWS
                  ss = "ide/controls/windows/" + v.type_name.toLower() + ".png";    // HIDE
                #else
                  ss = "ide/controls/linux/" + v.type_name.toLower() + ".png";   
                #endif
                #endif
              }

              t = _variables; 
              break;
             }
          case __event2: ss = "ide/Event.png"; t = _methods; break;
        }

        QTreeWidgetItem *m = new QTreeWidgetItem(t, QStringList(""));
       
        m->setIcon(0, kbasicIcon(kbasicPath(ss)));          
        m->setText(0, v.name);
        m->setText(2, v.file);
        m->setText(3, QString("%1").arg(v.line));
        m->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m->setExpanded(false);
      
      }
      
  
    }


    sOldForFile = sForFile;
    return;
  }  

  this->setUpdatesEnabled(false);

  if (tree && bTREE == true ){
    bTREE = false;
    tree->setHidden(true);
    setform->setHidden(false);
    a->setHidden(false);

    aMain->setText(tr("Main"));
    aSpecial->setText(tr("Special"));
    aFormat->setText(tr("Format"));
    aData->setText(tr("Data"));
    aControl->setText(tr("Control"));
    aEvent->setText(tr("Event"));
    aType->setText(tr(""));

    aSpecial->setIcon(QIcon());
    aFormat->setIcon(QIcon());
    aData->setIcon(QIcon());
    aControl->setIcon(QIcon());
    aEvent->setIcon(QIcon());
    aType->setIcon(QIcon());

  }

  if (bBuilded){
    
    for (int i = 0; i < controls_lineedit.size(); i++) controls_lineedit[i]->undisplay();
    for (int i = 0; i < controls_coloredit.size(); i++) controls_coloredit[i]->undisplay();
    for (int i = 0; i < controls_colorimageedit.size(); i++) controls_colorimageedit[i]->undisplay();
    for (int i = 0; i < controls_imageedit.size(); i++) controls_imageedit[i]->undisplay();
    for (int i = 0; i < controls_listcombobox.size(); i++) controls_listcombobox[i]->undisplay();
    for (int i = 0; i < controls_booleancombobox.size(); i++) controls_booleancombobox[i]->undisplay();
    for (int i = 0; i < controls_fontedit.size(); i++) controls_fontedit[i]->undisplay();
    for (int i = 0; i < controls_event.size(); i++) controls_event[i]->undisplay();
    for (int i = 0; i < controls_choicebox.size(); i++) controls_choicebox[i]->undisplay();
    for (int i = 0; i < controls_soundedit.size(); i++) controls_soundedit[i]->undisplay();
    for (int i = 0; i < controls_fileedit.size(); i++) controls_fileedit[i]->undisplay();
    for (int i = 0; i < controls_pixeledit.size(); i++) controls_pixeledit[i]->undisplay();
    
  }

  if (bBuilded == false || bBuild)
{
/*
    aa->removeItem(li);
    aa->removeItem(re);
    li = new QVBoxLayout();
    re = new QVBoxLayout();
    aa->addLayout(li);
    aa->addLayout(re);    */
    if (!bBuild) createList();
//    setHidden(true);
    

    QWidget *w;


    
    bool b = true;

    int id = 0;//tb->currentIndex();
    bool bAll = id == 0;
    int y = 0;

    addRowHeader(header_main, y, bAll);

    {


      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_Name, y, b, true); 
      addRow(PROPERTY_ControlType, y, b);
      addRow(PROPERTY_Group, y, b);
      addRow(PROPERTY_ActionId, y, b);
      
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_X, y, b);
      addRow(PROPERTY_Y, y, b);
      addRow(PROPERTY_Width, y, b);
      addRow(PROPERTY_Height, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_Enabled, y, b);
      addRow(PROPERTY_Visible, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_Layout, y, b);
      addRow(PROPERTY_Resizable, y, b);      
      addRow(PROPERTY_ResizableBigger, y, b);      
      addRow(PROPERTY_ResizableSmaller, y, b);            
      addRow(PROPERTY_ShowMode, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OpenAtStartup, y, b);      
      addRow(PROPERTY_StopOnClose, y, b);
    }


   // b = true;
    addRowHeader(header_other3, y, bAll);
//    int nheader_other3 = grid->indexOf(header_other3);

 //   if (!(id == 2 || bAll)){
   //   b = false;
    //} else 
    {

     // addRow(PROPERTY_Null, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);

      addRow(PROPERTY_IntegerValue, y, b);
      addRow(PROPERTY_BooleanValue, y, b);
      addRow(PROPERTY_StringValue, y, b);
      addRow(PROPERTY_Key, y, b); 
      addRow(PROPERTY_Caption, y, b);
      addRow(PROPERTY_Icon, y, b);
      addRow(PROPERTY_Description, y, b);
      addRow(PROPERTY_Prefix, y, b);
      addRow(PROPERTY_Suffix, y, b);


      //addRow(PROPERTY_Icon, y, b);
      //addRow(PROPERTY_IconCaption, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);

       addRow(PROPERTY_Index, y, b);
       addRow(PROPERTY_ArrowType, y, b);
       addRow(PROPERTY_PopupMode, y, b);
       addRow(PROPERTY_ToolBarRole, y, b);

       addRow(PROPERTY_MenuBarRole, y, b);

      addRow(PROPERTY_RootIsDecorated, y, b);
      addRow(PROPERTY_SQL, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_BorderTop, y, b);
      addRow(PROPERTY_BorderBottom, y, b);
      addRow(PROPERTY_BorderLeft, y, b);
      addRow(PROPERTY_BorderRight, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_Dock, y, b);     
      addRow(PROPERTY_DockTitleVisible, y, b);
      addRow(PROPERTY_DockOrder, y, b);
      addRow(PROPERTY_DockSplit, y, b);      
      addRow(PROPERTY_DockWidth, y, b);
      addRow(PROPERTY_DockHeight, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_MultiPageHeight, y, b);
      addRow(PROPERTY_MultiPageBorderTop, y, b);
      addRow(PROPERTY_MultiPageBorderBottom, y, b);
      addRow(PROPERTY_MultiPageBorderLeft, y, b);
      addRow(PROPERTY_MultiPageBorderRight, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_ScrollX, y, b);
      addRow(PROPERTY_ScrollY, y, b);
      addRow(PROPERTY_ScrollWidth, y, b);
      addRow(PROPERTY_ScrollHeight, y, b);
      addRow(PROPERTY_ScrollBar, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);

      addRow(PROPERTY_MoveOnMouseDrag, y, b);

      
      addRow(PROPERTY_HomeURL, y, b);
      addRow(PROPERTY_OpenLinks, y, b);
      addRow(PROPERTY_InputControl, y, b);
      addRow(PROPERTY_IntegerMaximum, y, b);
      addRow(PROPERTY_IntegerMinimum, y, b);

      addRow(PROPERTY_TickPosition, y, b);
      addRow(PROPERTY_InvertedAppearance, y, b);
      addRow(PROPERTY_InvertedControls, y, b);
      addRow(PROPERTY_Tracking, y, b);
      addRow(PROPERTY_TickInterval, y, b);
      addRow(PROPERTY_PageStep, y, b);
      addRow(PROPERTY_SingleStep, y, b);


      addRow(PROPERTY_StringMaximum, y, b);
      addRow(PROPERTY_StringMinimum, y, b);
      addRow(PROPERTY_Completer, y, b);

      addRow(PROPERTY_ValidatorDouble, y, b);
      addRow(PROPERTY_ValidatorInteger, y, b);
      //addRow(PROPERTY_ValidatorRegEx, y, b);
      //addRow(PROPERTY_ValidatorRegEx2, y, b);

      addRow(PROPERTY_DoubleEntry, y, b);
      addRow(PROPERTY_InsertPolicy, y, b);
      addRow(PROPERTY_ReadOnly, y, b);
      addRow(PROPERTY_Editable, y, b);
      addRow(PROPERTY_Sorted, y, b);

      addRow(PROPERTY_PopUp, y, b);

      addRow(PROPERTY_EventOnOpen, y, b);
      addRow(PROPERTY_AcceptRichText, y, b);
      addRow(PROPERTY_AutoDefault, y, b);
      addRow(PROPERTY_Default, y, b);
      addRow(PROPERTY_Checkable, y, b);
      addRow(PROPERTY_CheckableExclusive, y, b);      
      addRow(PROPERTY_ContextMenu, y, b);
      addRow(PROPERTY_EchoMode, y, b);
      addRow(PROPERTY_InputMask, y, b);
      addRow(PROPERTY_Interval, y, b);

      addRow(PROPERTY_EnabledImage, y, b);
      addRow(PROPERTY_DisabledImage, y, b);
      addRow(PROPERTY_EnterImage, y, b);
      addRow(PROPERTY_ExitImage, y, b);
      addRow(PROPERTY_MouseDownImage, y, b);
      addRow(PROPERTY_MouseUpImage, y, b);

      addRow(PROPERTY_EnterSound, y, b);
      addRow(PROPERTY_ExitSound, y, b);
      addRow(PROPERTY_MouseDownSound, y, b);
      addRow(PROPERTY_MouseUpSound, y, b);

      addRow(PROPERTY_CheckEnabledImage, y, b);
      addRow(PROPERTY_CheckDisabledImage, y, b);
      addRow(PROPERTY_CheckEnterImage, y, b);
      addRow(PROPERTY_CheckExitImage, y, b);
      addRow(PROPERTY_CheckMouseDownImage, y, b);
      addRow(PROPERTY_CheckMouseUpImage, y, b);

      addRow(PROPERTY_Format, y, b);

      addRow(PROPERTY_Pages, y, b);

      addRow(PROPERTY_Brightness, y, b);
      addRow(PROPERTY_Contrast, y, b);
      addRow(PROPERTY_Hue, y, b);
      addRow(PROPERTY_Saturation, y, b);
      addRow(PROPERTY_ScaleMode, y, b);
      addRow(PROPERTY_AspectRatio, y, b);
      addRow(PROPERTY_TransitionTime, y, b);
      addRow(PROPERTY_Muted, y, b);
      addRow(PROPERTY_Volume, y, b);
      addRow(PROPERTY_PrefinishMark, y, b);
      addRow(PROPERTY_Tick, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnTick, y, b);
      addRow(PROPERTY_OnStateChanged, y, b);
      addRow(PROPERTY_OnAboutToFinish, y, b);
      addRow(PROPERTY_OnFinished, y, b);
      addRow(PROPERTY_OnMutedChanged, y, b);
      addRow(PROPERTY_OnVolumeChanged, y, b);
      addRow(PROPERTY_OnPlayingTitleChanged, y, b);
      addRow(PROPERTY_OnBufferStatus, y, b);
      addRow(PROPERTY_OnTotalTimeChanged, y, b);

      addRow(PROPERTY_OnGoTo, y, b);
      addRow(PROPERTY_OnQuery, y, b);
      addRow(PROPERTY_OnAddNew, y, b);
      addRow(PROPERTY_OnDirty, y, b);
      addRow(PROPERTY_OnBeforeUpdate, y, b);
      addRow(PROPERTY_OnBeforeInsert, y, b);
      addRow(PROPERTY_OnBeforeDelete, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);

      addRow(PROPERTY_OnEvent, y, b);

      addRow(PROPERTY_OnCursorPositionChanged, y, b);
      addRow(PROPERTY_OnEditingFinished, y, b);
      addRow(PROPERTY_OnReturnPressed, y, b);
      addRow(PROPERTY_OnSelectionChanged, y, b);
      addRow(PROPERTY_OnTextChanged, y, b);
      addRow(PROPERTY_OnTextEdited, y, b);

      

      addRow(PROPERTY_OnPage, y, b);
      addRow(PROPERTY_OnLinkHovered, y, b);
      addRow(PROPERTY_OnLoadFinished, y, b);
      addRow(PROPERTY_OnLoadProgress, y, b);
      addRow(PROPERTY_OnLoadStarted, y, b);
      addRow(PROPERTY_OnWindowCloseRequested, y, b);

      addRow(PROPERTY_OnAction, y, b);
      //addRow(PROPERTY_OnCursorPositionChanged, y, b);      
      addRow(PROPERTY_OnCurrentItemChanged, y, b);
      addRow(PROPERTY_OnItemActivated, y, b);
      addRow(PROPERTY_OnItemChanged, y, b);
      addRow(PROPERTY_OnItemClicked, y, b);
      addRow(PROPERTY_OnItemCollapsed, y, b);
      addRow(PROPERTY_OnItemDoubleClicked, y, b);
      addRow(PROPERTY_OnItemEntered, y, b);
      addRow(PROPERTY_OnItemExpanded, y, b);
      addRow(PROPERTY_OnItemPressed, y, b);
      addRow(PROPERTY_OnItemSelectionChanged, y, b);

      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnDockMove, y, b);
      addRow(PROPERTY_OnDockShow, y, b);
      addRow(PROPERTY_OnDockHide, y, b);
      addRow(PROPERTY_OnDockFloating, y, b);
      addRow(PROPERTY_OnDockNotFloating, y, b);

      addRow(PROPERTY_SoundOnEvent, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);

      addRow(PROPERTY_Comment1Begin, y, b);
      addRow(PROPERTY_Comment1End, y, b);
      addRow(PROPERTY_Comment2Begin, y, b);
      //addRow(PROPERTY_Comment2End, y, b);
      addRow(PROPERTY_Keywords, y, b);
      addRow(PROPERTY_Commands, y, b);
      addRow(PROPERTY_CommentColor, y, b);
      addRow(PROPERTY_KeywordColor, y, b);
      addRow(PROPERTY_CommandColor, y, b);

    }

   // b = true;
    addRowHeader(header_other2, y, bAll);

  //  if (!(id == 3 || bAll)){
     // b = false;
    //} else 
    {

      // PROPERTY
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_MaximumVisible, y, b);

      addRow(PROPERTY_Shadow, y, b);
      addRow(PROPERTY_Shape, y, b);
      addRow(PROPERTY_Scale, y, b);

      addRow(PROPERTY_Space, y, b);
      addRow(PROPERTY_Border, y, b);
      addRow(PROPERTY_Flat, y, b);
      addRow(PROPERTY_ViewMode, y, b);
      addRow(PROPERTY_Flip, y, b);
      addRow(PROPERTY_Separator, y, b);
      addRow(PROPERTY_WordWrap, y, b);
      addRow(PROPERTY_Alignment, y, b);       
      addRow(PROPERTY_Orientation, y, b); 
      addRow(PROPERTY_Feature, y, b); 


      addRow(PROPERTY_Flag, y, b);
      addRow(PROPERTY_Modal, y, b);
      addRow(PROPERTY_Checked, y, b);
      addRow(PROPERTY_TableView, y, b);

      
      addRow(PROPERTY_SelectionMode, y, b); 
      addRow(PROPERTY_AlternatingRowColors, y, b); 

      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_TableViewCaption, y, b);
      addRow(PROPERTY_TableViewVisible, y, b);
      addRow(PROPERTY_TableViewWidth, y, b);

      addRow(PROPERTY_PortName, y, b);
      addRow(PROPERTY_BaudRate, y, b);
      addRow(PROPERTY_DataBits, y, b);
      addRow(PROPERTY_FlowControl, y, b);      
      addRow(PROPERTY_Parity, y, b);
      addRow(PROPERTY_StopBits, y, b);
      addRow(PROPERTY_TimeoutMillisec, y, b);
      addRow(PROPERTY_PollingInterval, y, b);



    }

   // b = true;
    addRowHeader(header_other, y, bAll);

   // if (!(id == 4 || bAll)){
      //b = false;
   // } else 
    {

      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_SQLName, y, b);
      addRow(PROPERTY_SQLRelation, y, b);
      addRow(PROPERTY_SQLControls, y, b);
      addRow(PROPERTY_SQLInsert, y, b);
      addRow(PROPERTY_SQLUpdate, y, b);
      addRow(PROPERTY_SQLDelete, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      //addRow(PROPERTY_TableViewSort, y, b);
      //addRow(PROPERTY_TableViewFilter, y, b);
      //addRow(PROPERTY_TableViewOrder, y, b);

      addRow(PROPERTY_CSV, y, b);
      addRow(PROPERTY_Tag, y, b);
      addRow(PROPERTY_Data, y, b);
    }

   // b = true;
    //if (nPropertyWindowForWhat != 2 && nPropertyWindowForWhat != -1 && nPropertyWindowForWhat != 1)
    {
   
 
      addRowHeader(header_other4, y, bAll);

     // if (!(id == 5 || bAll)){
      // b = false;
      //} else 
      {
        w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);

        addRow(PROPERTY_FocusOrder, y, b);
        addRow(PROPERTY_FocusPolicy, y, b);
        addRow(PROPERTY_FocusProxy, y, b);
        w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);

        addRow(PROPERTY_MinimumWidth, y, b);
        addRow(PROPERTY_MinimumHeight, y, b);
        addRow(PROPERTY_MaximumWidth, y, b);
        addRow(PROPERTY_MaximumHeight, y, b);
        w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
    /*
        addRow(PROPERTY_BoxIndex, y, b);
        addRow(PROPERTY_BoxX, y, b);
        addRow(PROPERTY_BoxY, y, b);
        addRow(PROPERTY_SplitIndex, y, b);
    */
        //addRow(PROPERTY_FormCentered, y, b);
        //addRow(PROPERTY_FormScaled, y, b);


        addRow(PROPERTY_FontName, y, b);
        addRow(PROPERTY_FontSize, y, b);
        addRow(PROPERTY_FontBold, y, b);
        addRow(PROPERTY_FontItalic, y, b);
        addRow(PROPERTY_FontUnderline, y, b);
        addRow(PROPERTY_FontColor, y, b);
        w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
        addRow(PROPERTY_Background, y, b);
        addRow(PROPERTY_BackgroundStyle, y, b);
        w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
        addRow(PROPERTY_Palette, y, b);
        addRow(PROPERTY_DrawOnPaint, y, b);
        addRow(PROPERTY_MouseTracking, y, b);
        addRow(PROPERTY_DragDrop, y, b);


        addRow(PROPERTY_StyleSheet, y, b);
        w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
        addRow(PROPERTY_StatusTip, y, b);
        addRow(PROPERTY_ToolTip, y, b);
        addRow(PROPERTY_WhatsThis, y, b);
        w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);

        addRow(PROPERTY_Mask, y, b);
        addRow(PROPERTY_Opacity, y, b);
        w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);

        //addRow(PROPERTY_DragDrop, y, b);

        addRow(PROPERTY_Cursor, y, b);
        addRow(PROPERTY_CursorAnimation, y, b);

        w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);

        addRow(PROPERTY_TimerInterval, y, b);

        
        //addRow(PROPERTY_TabIndex, y, b);
    /*
        addRow(PROPERTY_ParentForm, y, b);
        addRow(PROPERTY_ParentControl, y, b);*/
        //addRow(PROPERTY_TabIndex, y, b);
      // addRow(PROPERTY_ParentIndex, y, b);

        
      }
    }

    // EVENT


   // b = true;
    addRowHeader(header_event, y, bAll);

    if (!(id == 6 || bAll)){
    //  b = false;
    } else {

      

      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnOpen, y, b);
      addRow(PROPERTY_OnClose, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnPaint, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnShow, y, b);
      addRow(PROPERTY_OnHide, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnMove, y, b);
      addRow(PROPERTY_OnResize, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnEnabled, y, b);
      addRow(PROPERTY_OnDisabled, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnTimer, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnClick, y, b, true);
      addRow(PROPERTY_OnDblClick, y, b);
      addRow(PROPERTY_OnMouseDown, y, b);
      addRow(PROPERTY_OnMouseUp, y, b);
      addRow(PROPERTY_OnMouseMove, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnGotFocus, y, b);
      addRow(PROPERTY_OnLostFocus, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnEnter, y, b);
      addRow(PROPERTY_OnExit, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnKeyDown, y, b);
      addRow(PROPERTY_OnKeyUp, y, b);
      addRow(PROPERTY_OnKeyPress, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnMouseWheel, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnScroll, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnMultiPageShow, y, b);

      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
      addRow(PROPERTY_OnSingleShot, y, b);
      w = new QWidget(); w->setFixedHeight(1); grid->addWidget(w, y++, 0, 1, 2);
          

      addRow(PROPERTY_OnDragEnter, y, b);
      addRow(PROPERTY_OnDragMove, y, b);
      addRow(PROPERTY_OnDragExit, y, b);
      addRow(PROPERTY_OnDrop, y, b);

      
      
      //addRow(PROPERTY_OnPrint, y, b);

      QWidget *ww;
      ww = new QWidget();
      ww->setFixedHeight(400);
      grid->addWidget(ww, y, 0);

      ww = new QWidget();
      ww->setFixedHeight(400);
      grid->addWidget(ww, y, 1);


    }

    bBuilded = true;

  }

  this->setUpdatesEnabled(true);
}

void _property_label::mouseReleaseEvent ( QMouseEvent * e ) 
{
  neighbour->setFocus();
  
  QString k = neighbour->metaObject()->className();

  if (k.compare("_property_lineedit") == 0){
    ((_property_lineedit *)neighbour)->selectAll();
  }
  else if (k.compare("_property_pixeledit") == 0){
    ((_property_pixeledit *)neighbour)->selectAll();
  }
  else if (k.compare("_property_coloredit") == 0){
    ((_property_coloredit *)neighbour)->selectAll();
  }
  else if (k.compare("_property_imageedit") == 0){
    ((_property_imageedit *)neighbour)->selectAll();
  }
  else if (k.compare("_property_event") == 0){
    ((_property_event *)neighbour)->selectAll();
  }
  else if (k.compare("_property_fontedit") == 0){
    ((_property_fontedit *)neighbour)->selectAll();
  }
  else if (k.compare("_property_booleancombobox") == 0){
 //   ((_property_booleancombobox *)neighbour)->popup();
  }
  else if (k.compare("_property_listcombobox") == 0){
 //   ((_property_listcombobox *)neighbour)->popup();
  }
  //bold();
}

void _property_event::goEvent()
{

  bool ok = true;

  my_propertywindow->newEvent(le->getNeighbour()->text());

  if (ok){
    //QString s = "Yes"; 
//    setText(s);
  }

}

// **********


void _qwidget::paintEvent(QPaintEvent *e)
{
 // if (parent->updatesEnabled() == false) return;
}

void _qgridlayout::paintEvent(QPaintEvent *e)
{
 // if (parent->updatesEnabled() == false) return;
}


class _qscrollarea : public QScrollArea
{
  
public:
  _qscrollarea(_propertywindow *_parent) : QScrollArea(_parent)
  {
    parent = _parent;
  }

void paintEvent(QPaintEvent *e)
{
  int i;
  i  = 0;
  //if (updatesEnabled() == false) return;
}

private:
_propertywindow *parent;
};

_qscrollarea *a;
void _propertywindow::lock()
{
  fr->setHidden(true);

}

void _propertywindow::unlock()
{
 
  fr->setHidden(false); grid->update();

}

_propertywindow::_propertywindow(QWidget *parent) : QWidget(parent)
{

  bTREE = false;

  fr = new _qwidget(this);

  grid = new _qgridlayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  fr->setLayout(grid);
  re = new QVBoxLayout();




  a = new _qscrollarea(this);
  a->setWidget(fr);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QVBoxLayout *j = new QVBoxLayout();
  j->setMargin(0);
  j->setSpacing(0);
  setLayout(j);


  QHBoxLayout *jj = new QHBoxLayout();
  jj->setMargin(0);
  jj->setSpacing(0);


  currentcontrolname = new QLabel("");

  setform = new QPushButton(kbasicIcon(idePath("VIEW_FORM.png")), tr(""), this); 
  setform->setToolTip(tr("Unselect all controls")); 
  setform->setFlat(true); 
  setform->setIconSize(QSize(32, 32)); 
  setform->setFixedSize(QSize(34, 34));
  connect(setform, SIGNAL(clicked(bool)), this, SLOT(settingform()));


  tree = new QTreeWidget(this);
  tree->header()->hide();
  connect(tree, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem *, int)));
  connect(tree, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
  tree->setHeaderLabel("");

  jj->addWidget(setform);
  jj->addWidget(currentcontrolname);

  j->addLayout(jj);

  tb = new QToolBar(this); j->addWidget(tb);

  j->addWidget(tree);

  j->addWidget(a);


  QActionGroup *ag = new QActionGroup(this);
  ag->setExclusive(true);

  aMain = tb->addAction(tr("Main"), this, SLOT(actionMain())); aMain->setActionGroup(ag); aMain->setCheckable(true);
  aData = tb->addAction(tr("Special"), this, SLOT(actionData())); aData->setActionGroup(ag); aData->setCheckable(true);
  aFormat = tb->addAction(tr("Format"), this, SLOT(actionFormat())); aFormat->setActionGroup(ag); aFormat->setCheckable(true);
  aSpecial = tb->addAction(tr("Data"), this, SLOT(actionSpecial())); aSpecial->setActionGroup(ag); aSpecial->setCheckable(true);
  aControl = tb->addAction(tr("Control"), this, SLOT(actionControl())); aControl->setActionGroup(ag); aControl->setCheckable(true);
  aEvent = tb->addAction(tr("Event"), this, SLOT(actionEvent())); aEvent->setActionGroup(ag); aEvent->setCheckable(true);
  aType = tb->addAction(tr("Type"), this, SLOT(actionType())); aType->setActionGroup(ag); aType->setCheckable(true);
  { // add extra space
    QWidget *ww = new QWidget();
    QSizePolicy sp;
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    ww->setSizePolicy(sp);
    tb->addWidget(ww);
  }



}

_propertywindow::~_propertywindow(void)
{
}

inline void _propertywindow::addRow(_property_pixeledit *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRow(_property_listcombobox *le, int &y, bool visible, bool bNewHeader)
{
  
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

  
}


inline void _propertywindow::addRow(_property_colorimageedit *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRow(_property_imageedit *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRow(_property_event *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRow(_property_fontedit *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRow(_property_coloredit *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();   
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRow(_property_lineedit *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRow(_property_booleancombobox *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRow(_property_soundedit *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRow(_property_fileedit *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRow(_property_choicebox *le, int &y, bool visible, bool bNewHeader)
{
  if (!bBuilded){
    QWidget *w = le->getNeighbour(y, bNewHeader);
    w->show();
    le->show();    
    
    grid->addWidget(w, y, 0);
    grid->addWidget(le, y, 1);
    y++;
  } else if (visible && le->bDisplay){
    le->getNeighbour(y, bNewHeader)->show();
    le->show();
  } else {
    le->getNeighbour(y, bNewHeader)->hide();
    le->hide();
  }

}

inline void _propertywindow::addRowHeader(_property_header *l, int &y, bool visible)
{

  if (!bBuilded){

    grid->addWidget(l, y, 0, 1, 2);
    y++; 
  } else {
    if (visible){
      l->show();
    } else {
      l->hide();
    }
  }
}
void _property_choicebox::get()
{
  QString s = _choicedialog::get(sSet, text());

  setText(s);
  le->home(false);
}


void _property_imageedit::getFile2()
{
  _resources o(this);

  bRersourcesAreSelected = true;
  //_resources *k = 0;
  do {
   // k = qobject_cast<_resources *>(qApp->activeWindow());

    qApp->processEvents();
  } while (sSelectedResource.isEmpty() || sSelectedResource.compare("KBASIC_EXIT.XYZ") == 0);

  if (sSelectedResource.compare("KBASIC_EXIT.XYZ") != 0) le->setText(EXTERN_my_mainwindow->getFilenameWithoutPath(sSelectedResource));
  selectAll();
  setFocus();    
  bRersourcesAreSelected = false;
}

void _property_colorimageedit::getFile2()
{
  _resources o(this);

  bRersourcesAreSelected = true;
  _resources *k = 0;
  do {
    k = qobject_cast<_resources *>(qApp->activeWindow());

    qApp->processEvents();
  } while (k);

  le->setText(EXTERN_my_mainwindow->getFilenameWithoutPath(sSelectedResource));
  selectAll();
  setFocus();    
  bRersourcesAreSelected = false;
}

void _property_pixeledit::getFile()
{
  QString s = "";

  QTextBrowser *b = new QTextBrowser(0);
//  b->setModal(true);
  b->setAttribute(Qt::WA_DeleteOnClose);
  b->setWindowFlags(b->windowFlags() | Qt::Tool);
  b->setWindowTitle(tr("Pixels/Inches/cm"));

  int n = le->text().toInt();

  s += QString("pixels: %1\n").arg(n);
  s += QString("inches: %1\n").arg(pixels2Inches(n));
  s += QString("cm: %1\n").arg(inches2cm(pixels2Inches(n)));
 
  b->setText(s);
  b->setGeometry(QApplication::desktop()->width() / 2 - 400 / 2, QApplication::desktop()->height() / 2 - 400 / 2, 400, 400);
  b->show();  

  
  /*
  

  if (pb->text() == "px"){
    pb->setText("in");
    le->setText(QString("%1").arg(pixelsToInches(n)));
  } else if (pb->text() == "in"){
    pb->setText("cm");
    le->setText(QString("%1").arg(pixelsToInches(n)));
  } else {
    pb->setText("px");
  }*/
  
  selectAll();
  b->setFocus();   
  qApp->setActiveWindow(b);
}

void _propertywindow::settingform()
{
  if (EXTERN_my_form){
    EXTERN_my_form->setFormSelf();
  }
  if (EXTERN_my_report){
    EXTERN_my_report->setFormSelf();
  }
}

void _propertywindow::focusInEvent(QFocusEvent * e)
{
  setform->setHidden(!EXTERN_my_form && !EXTERN_my_report);
}

void _propertywindow::itemDoubleClicked(QTreeWidgetItem *item, int column)
{   
  QString file = item->text(2);
  QString line = item->text(3);

  int n = line.toInt();
  if (n < 0){
    QMessageBox::information(this, MYAPP, tr("The selected variable is a control added during compilation automatically by KBasic.\n"));
  } 
  if (!line.isEmpty()) EXTERN_my_mainwindow->showError(file, n, "");
}

void _propertywindow::itemSelectionChanged()
{  
 
}

void _propertywindow::actionMain()
{
  if (nPropertyWindowForWhat == 4){
        _constants->setExpanded(true);
        _variables->setExpanded(true);
        _methods->setExpanded(true);
        _properties->setExpanded(true);
        _enums->setExpanded(true);
        _types->setExpanded(true);

  } else {
      a->ensureWidgetVisible(header_main);

  }

}

void _propertywindow::actionSpecial()
{
  if (nPropertyWindowForWhat == 4){
        _constants->setExpanded(false);
        _variables->setExpanded(false);
        _methods->setExpanded(true);
        _properties->setExpanded(false);
        _enums->setExpanded(false);
        _types->setExpanded(false);

  } else {
       a->ensureWidgetVisible(header_other); 

  }

}

void _propertywindow::actionFormat()
{
  if (nPropertyWindowForWhat == 4){
        _constants->setExpanded(false);
        _variables->setExpanded(true);
        _methods->setExpanded(false);
        _properties->setExpanded(false);
        _enums->setExpanded(false);
        _types->setExpanded(false);

  } else {
      a->ensureWidgetVisible(header_other2);

  }

}

void _propertywindow::actionData()
{
  if (nPropertyWindowForWhat == 4){
        _constants->setExpanded(true);
        _variables->setExpanded(false);
        _methods->setExpanded(false);
        _properties->setExpanded(false);
        _enums->setExpanded(false);
        _types->setExpanded(false);

  } else {
      a->ensureWidgetVisible(header_other3);

  }

}

void _propertywindow::actionControl()
{
  if (nPropertyWindowForWhat == 4){
        _constants->setExpanded(false);
        _variables->setExpanded(false);
        _methods->setExpanded(false);
        _properties->setExpanded(true);
        _enums->setExpanded(false);
        _types->setExpanded(false);

  } else {
       a->ensureWidgetVisible(header_other4);
  }

}
  
void _propertywindow::actionEvent()
{
  if (nPropertyWindowForWhat == 4){
        _constants->setExpanded(false);
        _variables->setExpanded(false);
        _methods->setExpanded(false);
        _properties->setExpanded(false);
        _enums->setExpanded(true);
        _types->setExpanded(false);

  } else {
       a->ensureWidgetVisible(header_event); 
  }

}

void _propertywindow::actionType()
{
  if (nPropertyWindowForWhat == 4){
        _constants->setExpanded(false);
        _variables->setExpanded(false);
        _methods->setExpanded(false);
        _properties->setExpanded(false);
        _enums->setExpanded(false);
        _types->setExpanded(true);

  } else {
    a->ensureWidgetVisible(header_main);
  }

}
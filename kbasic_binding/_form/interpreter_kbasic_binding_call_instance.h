case pcode___form___form:{ 
  getParam(v, m, n); pp = new kb_form(); myStack->pushParameter(pcode___form, pp); ((kb_form *) pp)->setInterpreter(this);

  break; }


                         

case pcode___form__METHOD_Hwnd:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_Hwnd()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__METHOD_IsFilterActive:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_IsFilterActive()); if (bReturn) pushStack(p); else delete p; break; }

                                 
            
case pcode___form__METHOD_Append:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_Append(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->tot_integer(), v[4]->tot_integer(), v[5]->tot_integer(), v[6]->tot_integer(), v[7]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_Insert1:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_Append(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->tot_integer(), v[4]->tot_integer(), v[5]->tot_integer(), v[6]->tot_integer(), v[7]->tot_boolean())); if (bReturn) pushStack(p); else delete p;  break; }
case pcode___form__METHOD_Remove:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_Remove(v[0]->toQString())); if (bReturn) pushStack(p); else delete p;  break; }

case pcode___form__SETPROPERTY_MouseTracking:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_MouseTracking(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_MouseTracking:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_MouseTracking()); if (bReturn) pushStack(p); else delete p; break; }
         
case pcode___form__SETPROPERTY_MoveOnMouseDrag:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_MoveOnMouseDrag(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_MoveOnMouseDrag:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_MoveOnMouseDrag()); if (bReturn) pushStack(p); else delete p; break; }
                 

case pcode___form__METHOD_DockIsLeft:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DockIsLeft()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_DockIsRight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DockIsRight()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_DockIsTop:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DockIsTop()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_DockIsBottom:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DockIsBottom()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__METHOD_DockSetLeft:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DockSetLeft(); break; }
case pcode___form__METHOD_DockSetRight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DockSetRight(); break; }
case pcode___form__METHOD_DockSetTop:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DockSetTop(); break; }
case pcode___form__METHOD_DockSetBottom:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DockSetBottom(); break; }

case pcode___form__METHOD_DockTabify:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DockTabify(v[0]->toQString()); break; }
case pcode___form__METHOD_DockSplit:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DockSplit(v[0]->toQString(), v[1]->toQString()); break; }

case pcode___form__METHOD_DockSetFloating:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DockSetFloating(v[0]->tot_boolean()); break; }
case pcode___form__METHOD_DockIsFloating:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DockIsFloating()); if (bReturn) pushStack(p); else delete p; break; }


case pcode___form__SETPROPERTY_DockSplit:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_DockSplit(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_DockSplit:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_DockSplit()); if (bReturn) pushStack(p); else delete p; break; }
                         
case pcode___form__METHOD_ControlFocus:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_ControlFocus()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_ControlFocusNext:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_ControlFocusNext()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_ControlSetFocusNext:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_ControlSetFocusNext()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_ControlSetFocusPrevious:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_ControlSetFocusPrevious()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_IsOpen:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(-1); interpreter_parameter *p = new interpreter_parameter(q ? q->isVisible() : false); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__METHOD_ShowCentered:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_ShowCentered(); break; }
case pcode___form__METHOD_EventSource:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_EventSource()); if (bReturn) pushStack(p); else delete p; break; }


 
case pcode___form__SETPROPERTY_ResizableSmaller:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_ResizableSmaller(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_ResizableSmaller:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ResizableSmaller()); if (bReturn) pushStack(p); else delete p; break; }
                       
case pcode___form__SETPROPERTY_ResizableBigger:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_ResizableBigger(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_ResizableBigger:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ResizableBigger()); if (bReturn) pushStack(p); else delete p; break; }
                 
case pcode___form__SETPROPERTY_ShowMode:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_ShowMode(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_ShowMode:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ShowMode()); if (bReturn) pushStack(p); else delete p; break; }
                 
case pcode___form__SETPROPERTY_FormFileName:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_FormFileName(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_FormFileName:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FormFileName()); if (bReturn) pushStack(p); else delete p; break; }
                 
case pcode___form__SETPROPERTY_FormModified:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_FormModified(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_FormModified:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FormModified()); if (bReturn) pushStack(p); else delete p; break; }
                 
case pcode___form__SETPROPERTY_FormX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_FormX(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_FormX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FormX()); if (bReturn) pushStack(p); else delete p; break; }
                 
case pcode___form__SETPROPERTY_FormY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_FormY(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_FormY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FormY()); if (bReturn) pushStack(p); else delete p; break; }
                 
case pcode___form__SETPROPERTY_FormWidth:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_FormWidth(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_FormWidth:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FormWidth()); if (bReturn) pushStack(p); else delete p; break; }
                
case pcode___form__SETPROPERTY_FormHeight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_FormHeight(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_FormHeight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FormHeight()); if (bReturn) pushStack(p); else delete p; break; }
          
                                
case pcode___form__SETPROPERTY_CursorAnimation:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_CursorAnimation(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_CursorAnimation:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_CursorAnimation()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__METHOD_DataIds:{   
  
  getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); 
   
  QList<QByteArray> l = q->dynamicPropertyNames();
  
  _strings *ss = new _strings();

  foreach(QByteArray a, l)
  {
    QString s = QString::fromUtf8(a);
    if (s.compare("__kb1979.ControlType.kb__", Qt::CaseSensitive) != 0){
      ss->METHOD_Append(s);
    }
  }

  interpreter_parameter *p = new interpreter_parameter(ss); 
    
  if (bReturn) pushStack(p); else delete p; break; 
}

case pcode___form__METHOD_DataRemove:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DataRemove(v[0]->toQString()); break; }
case pcode___form__METHOD_DataRemoveAll:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DataRemoveAll(); break; }
case pcode___form__METHOD_DataSetBoolean:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DataSetBoolean(v[0]->toQString(), v[1]->tot_boolean()); break; }
case pcode___form__METHOD_DataSetInteger:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DataSetInteger(v[0]->toQString(), v[1]->tot_integer()); break; }
case pcode___form__METHOD_DataSetString:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DataSetString(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___form__METHOD_DataSetDouble:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DataSetDouble(v[0]->toQString(), v[1]->tot_double()); break; }

case pcode___form__METHOD_DataSetLong:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DataSetLong(v[0]->toQString(), v[1]->tot_long()); break; }
case pcode___form__METHOD_DataSetDecimal:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DataSetDecimal(v[0]->toQString(), v[1]->toCurrency()); break; }
case pcode___form__METHOD_DataSetDateTime:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_DataSetDateTime(v[0]->toQString(), v[1]->toDate()); break; }

case pcode___form__METHOD_DataBoolean:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataBoolean(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_DataInteger:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataInteger(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_DataString:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataString(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_DataDouble:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataDouble(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__METHOD_DataLong:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataLong(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_DataDecimal:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataDecimal(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_DataDateTime:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataDateTime(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }


case pcode___form__METHOD_ClearFocus:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_ClearFocus(); break; }
case pcode___form__METHOD_ToggleVisible:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_ToggleVisible(); break; }
case pcode___form__METHOD_SingleShot:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_SingleShot(v[0]->tot_integer()); break; }
case pcode___form__METHOD_StartTimer:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_StartTimer(); break; }
case pcode___form__METHOD_StopTimer:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->METHOD_StopTimer(); break; }

case pcode___form__METHOD_LocalX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_LocalX(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_LocalY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_LocalY(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__METHOD_GlobalX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_GlobalX(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_GlobalY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_GlobalY(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__METHOD_UnderMouse:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_UnderMouse()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__SETPROPERTY_Mask:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_Mask(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Mask:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Mask()); if (bReturn) pushStack(p); else delete p; break; }
                         
case pcode___form__SETPROPERTY_SoundOnEvent:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_SoundOnEvent(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_SoundOnEvent:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_SoundOnEvent()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__SETPROPERTY_Left:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_X(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_Left:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form();  i = q->GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_Top:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_Y(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_Top:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form();  i =  q->GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_LocalX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_X(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_LocalX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form();  i = q->GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_LocalY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_Y(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_LocalY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form();  i =  q->GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_DrawOnPaint:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_DrawOnPaint(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_DrawOnPaint:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_DrawOnPaint()); if (bReturn) pushStack(p); else delete p; break; }
                    
case pcode___form__SETPROPERTY_Palette:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_Palette(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Palette:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Palette()); if (bReturn) pushStack(p); else delete p; break; }
                         
case pcode___form__SETPROPERTY_BackgroundStyle:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); q->SETPROPERTY_BackgroundStyle(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_BackgroundStyle:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_BackgroundStyle()); if (bReturn) pushStack(p); else delete p; break; }
                         

case pcode___form__METHOD_Load:{ 
  getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_Load(v[0]->toQString()); if (bReturn) pushStackBoolean(b); 
  break; }


case pcode___form__METHOD_IsShownFullScreen:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_IsShownFullScreen(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_IsShownMaximized:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_IsShownMaximized(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_IsShownMinimized:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_IsShownMinimized(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_IsShownNormal:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_IsShownNormal(); if (bReturn) pushStackBoolean(b); break; }


case pcode___form__METHOD_SetWithTag:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetWithTag(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean()); break; }
case pcode___form__METHOD_SetWithTag1:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetWithTag(v[0]->toQString(), v[1]->toQString(), v[2]->tot_integer()); break; }
case pcode___form__METHOD_SetWithTag2:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetWithTag(v[0]->toQString(), v[1]->toQString(), v[2]->toQString()); break; }
case pcode___form__METHOD_SetWithTag3:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetWithTag(v[0]->toQString(), v[1]->toQString(), v[2]->tot_double()); break; }

case pcode___form__METHOD_SetWithGroup:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetWithGroup(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean()); break; }
case pcode___form__METHOD_SetWithGroup1:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetWithGroup(v[0]->toQString(), v[1]->toQString(), v[2]->tot_integer()); break; }
case pcode___form__METHOD_SetWithGroup2:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetWithGroup(v[0]->toQString(), v[1]->toQString(), v[2]->toQString()); break; }
case pcode___form__METHOD_SetWithGroup3:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetWithGroup(v[0]->toQString(), v[1]->toQString(), v[2]->tot_double()); break; }



case pcode___form__SETPROPERTY_Resizable:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Resizable(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_Resizable:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b = q->GETPROPERTY_Resizable(); if (bReturn) pushStackBoolean(b); break; }

case pcode___form__METHOD_ShowMultiPage:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_ShowMultiPage(v[0]->tot_integer()); break; }
case pcode___form__METHOD_ShowNextMultiPage:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_ShowNextMultiPage(); break; }
case pcode___form__METHOD_ShowPreviousMultiPage:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_ShowPreviousMultiPage(); break; }
               
case pcode___form__METHOD_OpenPrintDialog:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_OpenPrintDialog(); break; }
case pcode___form__METHOD_OpenPrint:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_OpenPrint(); break; }
case pcode___form__METHOD_OpenPrintPreview:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_OpenPrintPreview(); break; }

case pcode___form__METHOD_Finish:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_Finish(); break; }
case pcode___form__METHOD_FocusControl:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_FocusControl()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_ControlFirst:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_ControlFirst()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_ControlNext:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_ControlNext()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_ShowFullScreen:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_ShowFullScreen(); break; }
case pcode___form__METHOD_ShowMaximized:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_ShowMaximized(); break; }
case pcode___form__METHOD_ShowMinimized:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_ShowMinimized(); break; }
case pcode___form__METHOD_ShowNormal:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_ShowNormal(); break; }
case pcode___form__METHOD_Control:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_Control(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
//case pcode___form__EVENT_OnGoTo:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->EVENT_GoTo(); break; }
//case pcode___form__EVENT_OnBeforeInsert:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->EVENT_BeforeInsert(v[0]->tot_boolean()); break; }
//case pcode___form__EVENT_OnBeforeUpdate:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->EVENT_BeforeUpdate(v[0]->tot_boolean()); break; }
//case pcode___form__EVENT_OnBeforeDelete:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->EVENT_BeforeDelete(v[0]->tot_boolean()); break; }
/*
case pcode___form__METHOD_Record:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_Record(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_Record1:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_Record()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_SetRecord:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetRecord(v[0]->toQString(), v[1]->toVariant()); break; }
case pcode___form__METHOD_Query:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_Query(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
*/
case pcode___form__METHOD_Cut:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_Cut(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_Copy:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_Copy(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_Paste:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_Paste(); if (bReturn) pushStackBoolean(b); break; }

case pcode___form__METHOD_First:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b = q->METHOD_First(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_Next:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b = q->METHOD_Next(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_Previous:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b = q->METHOD_Previous(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_Last:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b = q->METHOD_Last(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_GoTo:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b = q->METHOD_GoTo(v[0]->tot_long()); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_Insert:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b = q->METHOD_Insert(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_Update:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b = q->METHOD_Update(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_Delete:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b = q->METHOD_Delete(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_AddNew:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b = q->METHOD_AddNew(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_Len:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; l =q->METHOD_Len(); if (bReturn) pushStackLong(l); break; }
case pcode___form__METHOD_Pos:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; l = q->METHOD_Pos(); if (bReturn) pushStackLong(l); break; }
case pcode___form__METHOD_IsDirty:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_IsDirty(); if (bReturn) pushStackBoolean(b);  break; }
//case pcode___form__METHOD_Affected:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_Affected()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_Cmd:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_Cmd(v[0]->toQString()); if (bReturn) pushStackBoolean(b); break; }
//case pcode___form__METHOD_LastSQLError:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_LastSQLError()); if (bReturn) pushStack(p); else delete p; break; }
//case pcode___form__METHOD_Find:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_Find(v[0]->toQString(), v[1]->toQString(), v[2]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_Find1:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_Read(v[0]->toQString(), v[1]->toQString(), v[2]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_Get:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_Get(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_Requery:{ getParam(v, m, n);identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break;   q->METHOD_Requery(); break; }
case pcode___form__METHOD_Seek:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->METHOD_Seek(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString(), v[4]->toQString(), v[5]->toQString()); if (bReturn) pushStackBoolean(b); break; }

case pcode___form__METHOD_kbrecordid:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_kbrecordid()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_kbrecordid1:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_kbrecordid(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_PrimaryKey:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_PrimaryKey()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_PrimaryKey1:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_PrimaryKey2(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_PrimaryKeyName:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_PrimaryKeyName()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__METHOD_PrimaryKeyName1:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->METHOD_PrimaryKeyName2(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__METHOD_ClearFilter:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_ClearFilter(); break; }
case pcode___form__METHOD_SetFilter:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetFilter(v[0]->toQString()); break; }
case pcode___form__METHOD_AddFilter:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_AddFilter(v[0]->toQString()); break; }
case pcode___form__METHOD_SortAsc:{ getParam(v, m, n);  identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SortAsc(v[0]->toQString()); break; }
case pcode___form__METHOD_SortDesc:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break;  q->METHOD_SortDesc(v[0]->toQString()); break; }

                         

case pcode___form__SETPROPERTY_ScrollX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ScrollX(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_ScrollX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_ScrollX(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_ScrollY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ScrollY(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_ScrollY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_ScrollY(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_ScrollWidth:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ScrollWidth(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_ScrollWidth:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_ScrollWidth(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_ScrollHeight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ScrollHeight(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_ScrollHeight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_ScrollHeight(); if (bReturn) pushStackInteger(i); break; }


case pcode___form__SETPROPERTY_ScrollBar:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ScrollBar(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_ScrollBar:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ScrollBar()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__SETPROPERTY_Dock:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Dock(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Dock:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Dock()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__SETPROPERTY_StopOnClose:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_StopOnClose(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_StopOnClose:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->GETPROPERTY_StopOnClose(); if (bReturn) pushStackBoolean(b); break; }

case pcode___form__SETPROPERTY_OpenAtStartup:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_OpenAtStartup(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_OpenAtStartup:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->GETPROPERTY_OpenAtStartup(); if (bReturn) pushStackBoolean(b); break; }

case pcode___form__SETPROPERTY_MultiPageHeight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_MultiPageHeight(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_MultiPageHeight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_MultiPageHeight(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_MultiPageBorderLeft:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_MultiPageBorderLeft(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_MultiPageBorderLeft:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_MultiPageBorderLeft(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_MultiPageBorderRight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_MultiPageBorderRight(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_MultiPageBorderRight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_MultiPageBorderRight(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_MultiPageBorderTop:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_MultiPageBorderTop(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_MultiPageBorderTop:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_MultiPageBorderTop(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_MultiPageBorderBottom:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_MultiPageBorderBottom(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_MultiPageBorderBottom:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_MultiPageBorderBottom(); if (bReturn) pushStackInteger(i); break; }
                                    


case pcode___form__SETPROPERTY_DockTitleVisible:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_DockTitleVisible(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_DockTitleVisible:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_DockTitleVisible()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__SETPROPERTY_DockOrder:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_DockOrder(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_DockOrder:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_DockOrder()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__SETPROPERTY_DockWidth:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_DockWidth(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_DockWidth:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_DockWidth(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_DockHeight:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_DockHeight(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_DockHeight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_DockHeight(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_BorderTop:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_BorderTop(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_BorderTop:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_BorderTop(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_BorderBottom:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_BorderBottom(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_BorderBottom:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_BorderBottom(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_BorderLeft:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_BorderLeft(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_BorderLeft:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_BorderLeft(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_BorderRight:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_BorderRight(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_BorderRight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_BorderRight(); if (bReturn) pushStackInteger(i); break; }

case pcode___form__SETPROPERTY_TableView:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_TableView(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_TableView:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->GETPROPERTY_TableView(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__SETPROPERTY_Flag:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Flag(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Flag:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Flag()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_Icon:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Icon(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Icon:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Icon()); if (bReturn) pushStack(p); else delete p; break; }
//case pcode___form__SETPROPERTY_IconCaption:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_IconCaption(v[0]->toQString()); break; }
//case pcode___form__GETPROPERTY_IconCaption:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_IconCaption()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__SETPROPERTY_Caption:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Caption(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Caption:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Caption()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__SETPROPERTY_Value:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Caption(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Value:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Caption()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__SETPROPERTY_Text:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Caption(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Text:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Caption()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___form__SETPROPERTY_Modal:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Modal(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_Modal:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->GETPROPERTY_Modal(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__METHOD_Move:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_Move(v[0]->tot_integer(), v[1]->tot_integer()); break; }
case pcode___form__METHOD_Resize:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_Resize(v[0]->tot_integer(), v[1]->tot_integer()); break; }
case pcode___form__METHOD_Show:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_Show(); break; }
case pcode___form__METHOD_Hide:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_Hide(); break; }

case pcode___form__METHOD_RepaintAlways:{ 
 // MYLOG("pcode___form__METHOD_RepaintAlways");

  getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_RepaintAlways(); break; }

case pcode___form__METHOD_Repaint:{ 
   // MYLOG("pcode___form__METHOD_Repaint");
  getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_Repaint(); break; }

case pcode___form__METHOD_Raise:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_Raise(); break; }
case pcode___form__METHOD_Lower:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_Lower(); break; }
case pcode___form__METHOD_Close:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_Close(); break; }

case pcode___form__METHOD_Open:
{ 
  getParam(v, m,n); 
  identifier = popStack(); 
  kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_Open); 
  if (q == 0) break; 
  if (q->windowModality() == Qt::ApplicationModal){
    if (q->bBlockOnceOpenModal){
      q->bBlockOnceOpenModal = false;
    } else {
      q->METHOD_Open(); 
    }
  } else {
    q->METHOD_Open(); 
  }
  break; 
}
 

case pcode___form__METHOD_Open1:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_Open1); if (q == 0) break; if (q->windowModality() == Qt::ApplicationModal){ if (q->bBlockOnceOpenModal){ q->bBlockOnceOpenModal = false; } else { q->METHOD_Open(v[0]->tot_integer(), v[1]->tot_integer()); } } else { q->METHOD_Open(v[0]->tot_integer(), v[1]->tot_integer()); }  break; }
case pcode___form__METHOD_Open2:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_Open2); if (q == 0) break; if (q->windowModality() == Qt::ApplicationModal){ if (q->bBlockOnceOpenModal){ q->bBlockOnceOpenModal = false; } else { q->METHOD_Open(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer()); } } else { q->METHOD_Open(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer()); } break; }

case pcode___form__METHOD_OpenFullScreen:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_OpenFullScreen); if (q == 0) break; if (q->windowModality() == Qt::ApplicationModal){ if (q->bBlockOnceOpenModal){ q->bBlockOnceOpenModal = false; } else { q->METHOD_OpenFullScreen(); } } else { q->METHOD_OpenFullScreen(); } break; }
case pcode___form__METHOD_OpenCentered:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_OpenCentered); if (q == 0) break; if (q->windowModality() == Qt::ApplicationModal){ if (q->bBlockOnceOpenModal){ q->bBlockOnceOpenModal = false; } else { q->METHOD_OpenCentered(); } } else { q->METHOD_OpenCentered(); } break; }

case pcode___form__METHOD_OpenHidden:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_OpenHidden); if (q == 0) break; if (q->windowModality() == Qt::ApplicationModal){ if (q->bBlockOnceOpenModal){ q->bBlockOnceOpenModal = false; } else { q->METHOD_OpenHidden(); } } else { q->METHOD_OpenHidden(); }; break; }

case pcode___form__METHOD_OpenMaximized:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_OpenMaximized); if (q == 0) break; if (q->windowModality() == Qt::ApplicationModal){ if (q->bBlockOnceOpenModal){ q->bBlockOnceOpenModal = false; } else { q->METHOD_OpenMaximized(); } } else { q->METHOD_OpenMaximized(); }; break; }
case pcode___form__METHOD_OpenMinimized:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_OpenMinimized); if (q == 0) break; if (q->windowModality() == Qt::ApplicationModal){ if (q->bBlockOnceOpenModal){ q->bBlockOnceOpenModal = false; } else { q->METHOD_OpenMinimized(); } } else { q->METHOD_OpenMinimized(); }; break; }
case pcode___form__METHOD_OpenCenteredOnlyOnce:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_OpenCenteredOnlyOnce); if (q == 0) break; if (q->windowModality() == Qt::ApplicationModal){ if (q->bBlockOnceOpenModal){ q->bBlockOnceOpenModal = false; } else { q->METHOD_OpenCenteredOnlyOnce(); } } else { q->METHOD_OpenCenteredOnlyOnce(); }; break; }
case pcode___form__METHOD_OpenOnlyOnce:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_OpenOnlyOnce); if (q == 0) break; if (q->windowModality() == Qt::ApplicationModal){ if (q->bBlockOnceOpenModal){ q->bBlockOnceOpenModal = false; } else { q->METHOD_OpenOnlyOnce(); } } else { q->METHOD_OpenOnlyOnce(); }; break; }
case pcode___form__METHOD_OpenHiddenOnlyOnce:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(pcode___form__METHOD_OpenHiddenOnlyOnce); if (q == 0) break; if (q->windowModality() == Qt::ApplicationModal){ if (q->bBlockOnceOpenModal){ q->bBlockOnceOpenModal = false; } else { q->METHOD_OpenHiddenOnlyOnce(); } } else { q->METHOD_OpenHiddenOnlyOnce(); }; break; }

case pcode___form__METHOD_SetFocus:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->METHOD_SetFocus(); break; }
case pcode___form__SETPROPERTY_Name:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Name(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Name:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Name()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_Group:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Group(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Group:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Group()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_Background:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Background(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Background:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Background()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_X:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_X(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_X:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_Y:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Y(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_Y:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_Width:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Width(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_Width:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_Width(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_Height:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Height(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_Height:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_Height(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__GETPROPERTY_GlobalX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_GlobalX(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__GETPROPERTY_GlobalY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_GlobalY(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__GETPROPERTY_OldX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_OldX(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__GETPROPERTY_OldY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_OldY(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__GETPROPERTY_OldWidth:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_OldWidth(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__GETPROPERTY_OldHeight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_OldHeight(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_MinimumWidth:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_MinimumWidth(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_MinimumWidth:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_MinimumWidth(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_MinimumHeight:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_MinimumHeight(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_MinimumHeight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_MinimumHeight(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_MaximumWidth:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_MaximumWidth(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_MaximumWidth:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_MaximumWidth(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_MaximumHeight:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_MaximumHeight(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_MaximumHeight:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i = q->GETPROPERTY_MaximumHeight(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_Tag:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Tag(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Tag:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Tag()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_CSV:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_CSV(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_CSV:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_CSV()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_ParentForm:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ParentForm(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_ParentForm:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentForm()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_ParentControl:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ParentControl(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_ParentControl:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentControl()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_DragDrop:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_DragDrop(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_ParentControl1:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentControl()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_ControlType:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ControlType(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_ControlType:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ControlType()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_Focus:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Focus(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_Focus:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->GETPROPERTY_Focus(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__SETPROPERTY_FocusPolicy:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_FocusPolicy(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_FocusPolicy:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FocusPolicy()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_FocusProxy:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_FocusProxy(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_FocusProxy:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FocusProxy()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_FocusOrder:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_FocusOrder(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_FocusOrder:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_FocusOrder(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_Cursor:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Cursor(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_Cursor:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Cursor()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_FontName:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_FontName(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_FontName:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FontName()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_FontSize:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_FontSize(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_FontSize:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_FontSize(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_FontItalic:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_FontItalic(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_FontItalic:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->GETPROPERTY_FontItalic(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__SETPROPERTY_FontBold:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_FontBold(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_FontBold:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->GETPROPERTY_FontBold(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__SETPROPERTY_FontUnderline:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_FontUnderline(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_FontUnderline:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->GETPROPERTY_FontUnderline(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__SETPROPERTY_FontColor:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_FontColor(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_FontColor:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FontColor()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_Enabled:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Enabled(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_Enabled:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->GETPROPERTY_Enabled(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__SETPROPERTY_Visible:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Visible(v[0]->tot_boolean()); break; }
case pcode___form__GETPROPERTY_Visible:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; b =q->GETPROPERTY_Visible(); if (bReturn) pushStackBoolean(b); break; }
case pcode___form__SETPROPERTY_StatusTip:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_StatusTip(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_StatusTip:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StatusTip()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_ToolTip:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ToolTip(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_ToolTip:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ToolTip()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_StyleSheet:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_StyleSheet(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_StyleSheet:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StyleSheet()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_WhatsThis:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_WhatsThis(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_WhatsThis:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_WhatsThis()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___form__SETPROPERTY_TimerInterval:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_TimerInterval(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_TimerInterval:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_TimerInterval(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_Opacity:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_Opacity(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_Opacity:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_Opacity(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_BoxIndex:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_BoxIndex(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_BoxIndex:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_BoxIndex(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_SplitIndex:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_SplitIndex(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_SplitIndex:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_SplitIndex(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_TabIndex:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_TabIndex(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_TabIndex:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_TabIndex(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_BoxX:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_BoxX(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_BoxX:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_BoxX(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_BoxY:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_BoxY(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_BoxY:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_BoxY(); if (bReturn) pushStackInteger(i); break; }
case pcode___form__SETPROPERTY_ParentIndex:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ParentIndex(v[0]->tot_integer()); break; }
case pcode___form__GETPROPERTY_ParentIndex:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; i =q->GETPROPERTY_ParentIndex(); if (bReturn) pushStackInteger(i); else delete p; break; }
case pcode___form__SETPROPERTY_ControlType1:{ getParam(v, m,n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; q->SETPROPERTY_ControlType(v[0]->toQString()); break; }
case pcode___form__GETPROPERTY_ControlType1:{ getParam(v, m, n); identifier = popStack(); kb_form *q = (kb_form *) identifier->to_form(); if (q == 0) break; interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ControlType()); if (bReturn) pushStack(p); else delete p; break; }
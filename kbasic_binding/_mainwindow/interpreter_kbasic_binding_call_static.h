case pcode___mainwindow__PROPERTYSET_X:{ _mainwindow2::SETPROPERTY_X(v[0]->toInteger()); break; }

case pcode___mainwindow__PROPERTYGET_X:{ i = _mainwindow2::GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }

case pcode___mainwindow__PROPERTYSET_Y:{ _mainwindow2::SETPROPERTY_Y(v[0]->toInteger()); break; }

case pcode___mainwindow__PROPERTYGET_Y:{ i = _mainwindow2::GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }

case pcode___mainwindow__PROPERTYSET_Width:{ _mainwindow2::SETPROPERTY_Width(v[0]->toInteger()); break; }

case pcode___mainwindow__PROPERTYGET_Width:{ i =  _mainwindow2::GETPROPERTY_Width(); if (bReturn) pushStackInteger(i); break; }

case pcode___mainwindow__PROPERTYSET_Height:{ _mainwindow2::SETPROPERTY_Height(v[0]->toInteger()); break; }

case pcode___mainwindow__PROPERTYGET_Height:{ i =  _mainwindow2::GETPROPERTY_Height(); if (bReturn) pushStackInteger(i);  break; }

case pcode___mainwindow__METHOD_SetVisible:{ _mainwindow2::METHOD_SetVisible(v[0]->tot_boolean()); break; }
case pcode___mainwindow__METHOD_IsVisible:{ p = new interpreter_parameter( _mainwindow2::METHOD_IsVisible()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___mainwindow__METHOD_SetViewMode:{ _mainwindow2::METHOD_SetViewMode(v[0]->toQString()); break; }
case pcode___mainwindow__METHOD_ViewMode:{ p = new interpreter_parameter( _mainwindow2::METHOD_ViewMode()); if (bReturn) pushStack(p); else delete p; break; }
                     

case pcode___mainwindow__METHOD_Move:{ _mainwindow2::METHOD_Move(v[0]->tot_integer(), v[1]->tot_integer()); break; }

case pcode___mainwindow__METHOD_Resize:{ _mainwindow2::METHOD_Resize(v[0]->tot_integer(), v[1]->tot_integer()); break; }

case pcode___mainwindow__METHOD_Close:{ _mainwindow2::METHOD_Close(); break; }

case pcode___mainwindow__METHOD_CloseAllWindows:{ _mainwindow2::METHOD_CloseAllWindows(); break; }


case pcode___mainwindow__METHOD_ShowFullScreen:{ _mainwindow2::METHOD_ShowFullScreen(); break; }

case pcode___mainwindow__METHOD_ShowMaximized:{ _mainwindow2::METHOD_ShowMaximized(); break; }

case pcode___mainwindow__METHOD_ShowMinimized:{ _mainwindow2::METHOD_ShowMinimized(); break; }

case pcode___mainwindow__METHOD_ShowNormal:{ _mainwindow2::METHOD_ShowNormal(); break; }

case pcode___mainwindow__METHOD_IsScrollBarsEnabled:{ b = _mainwindow2::METHOD_IsScrollBarsEnabled(); if (bReturn) pushStackBoolean(b); break; }

case pcode___mainwindow__METHOD_SetFocusNextForm:{ _mainwindow2::METHOD_SetFocusNextForm(); break; }

case pcode___mainwindow__METHOD_SetFocusPreviousForm:{ _mainwindow2::METHOD_SetFocusPreviousForm(); break; }

case pcode___mainwindow__METHOD_Cascade:{ _mainwindow2::METHOD_Cascade(); break; }

case pcode___mainwindow__METHOD_CloseActiveForm:{ _mainwindow2::METHOD_CloseActiveForm(); break; }

case pcode___mainwindow__METHOD_CloseAllapplication:{ _mainwindow2::METHOD_CloseAll(); break; }

case pcode___mainwindow__METHOD_Tile:{ _mainwindow2::METHOD_Tile(); break; }

case pcode___mainwindow__METHOD_SetScrollBarsEnabled:{ _mainwindow2::METHOD_SetScrollBarsEnabled(v[0]->tot_boolean()); break; }


case pcode___mainwindow__METHOD_SetCaption:{ _mainwindow2::METHOD_SetCaption(v[0]->toQString()); break; }

case pcode___mainwindow__METHOD_SetIcon:{ _mainwindow2::METHOD_SetIcon(v[0]->toQString()); break; }

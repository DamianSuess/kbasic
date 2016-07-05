


case pcode___systemtray__METHOD_IsSystemTrayAvailable:{ interpreter_parameter *p = new interpreter_parameter( _systemtray::METHOD_IsSystemTrayAvailable()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___systemtray__METHOD_IsPrintSupported:{ interpreter_parameter *p = new interpreter_parameter( _systemtray::METHOD_IsPrintSupported()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___systemtray__METHOD_Print:{ _systemtray::METHOD_Print(v[0]->toQString()); break; }
case pcode___systemtray__METHOD_Print1:{ _systemtray::METHOD_Print1(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___systemtray__METHOD_Print2:{ _systemtray::METHOD_Print2(v[0]->toQString(), v[1]->toQString(), v[2]->toQString()); break; }
case pcode___systemtray__METHOD_Print3:{ _systemtray::METHOD_Print3(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->tot_integer()); break; }
case pcode___systemtray__METHOD_Show:{ _systemtray::METHOD_Show(); break; }
case pcode___systemtray__METHOD_Hide:{ _systemtray::METHOD_Hide(); break; }
case pcode___systemtray__METHOD_ToggleVisible:{ _systemtray::METHOD_ToggleVisible(); break; }

case pcode___systemtray__PROPERTYSET_ContextMenu:{ _systemtray::PROPERTYSET_ContextMenu(v[0]->toQString()); break; }
case pcode___systemtray__PROPERTYGET_ContextMenu:{ interpreter_parameter *p = new interpreter_parameter( _systemtray::PROPERTYGET_ContextMenu()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___systemtray__PROPERTYSET_Icon:{ _systemtray::PROPERTYSET_Icon(v[0]->toQString()); break; }
case pcode___systemtray__PROPERTYGET_Icon:{ interpreter_parameter *p = new interpreter_parameter( _systemtray::PROPERTYGET_Icon()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___systemtray__PROPERTYSET_ToolTip:{ _systemtray::PROPERTYSET_ToolTip(v[0]->toQString()); break; }
case pcode___systemtray__PROPERTYGET_ToolTip:{ interpreter_parameter *p = new interpreter_parameter( _systemtray::PROPERTYGET_ToolTip()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___systemtray__PROPERTYSET_Visible:{ _systemtray::PROPERTYSET_Visible(v[0]->tot_boolean()); break; }
case pcode___systemtray__PROPERTYGET_Visible:{ interpreter_parameter *p = new interpreter_parameter( _systemtray::PROPERTYGET_Visible()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___systemtray__PROPERTYGET_GlobalX:{ interpreter_parameter *p = new interpreter_parameter( _systemtray::PROPERTYGET_GlobalX()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___systemtray__PROPERTYGET_GlobalY:{ interpreter_parameter *p = new interpreter_parameter( _systemtray::PROPERTYGET_GlobalY()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___systemtray__PROPERTYGET_Width:{ interpreter_parameter *p = new interpreter_parameter( _systemtray::PROPERTYGET_Width()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___systemtray__PROPERTYGET_Height:{ interpreter_parameter *p = new interpreter_parameter( _systemtray::PROPERTYGET_Height()); if (bReturn) pushStack(p); else delete p; break; }

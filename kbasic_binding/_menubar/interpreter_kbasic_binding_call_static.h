case pcode___menubar__METHOD_MenuBarItem:{ p = new interpreter_parameter( _menubar::METHOD_MenuBarItem(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubar__METHOD_SetVisible:{ _menubar::METHOD_SetVisible(v[0]->tot_boolean()); break; }
case pcode___menubar__METHOD_IsVisible:{ p = new interpreter_parameter( _menubar::METHOD_IsVisible()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___menubar__METHOD_Show:{ _menubar::METHOD_Show(); break; }
case pcode___menubar__METHOD_Hide:{ _menubar::METHOD_Hide(); break; }
case pcode___menubar__METHOD_ToggleVisible:{ _menubar::METHOD_ToggleVisible(); break; }

case pcode___menubar__METHOD_Remove:{ _menubar::METHOD_Remove(v[0]->toQString()); break; }
case pcode___menubar__METHOD_RemoveAll:{ _menubar::METHOD_RemoveAll(); break; }

case pcode___menubar__METHOD_RemoveAllChilds:{ _menubar::METHOD_RemoveAllChilds(v[0]->toQString()); break; }

case pcode___menubar__METHOD_AppendMenuBarItem:{ _menubar::METHOD_AppendMenuBarItem(v[0]->toQString(), v[1]->to_menubaritem()); break; }
case pcode___menubar__METHOD_AppendMenuBarItem1:{ _menubar::METHOD_AppendMenuBarItem(v[0]->to_menubaritem()); break; }

//case pcode___menubar__METHOD_AppendSeparator:{ _menubar::METHOD_AppendSeparator(v[0]->toQString()); break; }

case pcode___menubar__METHOD_AppendMenu:{ _menubar::METHOD_AppendMenu(v[0]->to_menubaritem()); break; }
case pcode___menubar__METHOD_AppendMenu1:{ _menubar::METHOD_AppendMenu1(v[0]->toQString(), v[1]->to_menubaritem()); break; }

case pcode___menubar__METHOD_AppendChildMenu:{ _menubar::METHOD_AppendChildMenu(v[0]->toQString(), v[1]->to_menubaritem()); break; }
case pcode___menubar__METHOD_AppendChildMenu1:{ _menubar::METHOD_AppendChildMenu(v[0]->to_menubaritem()); break; }

case pcode___menubar__METHOD_AppendContextMenu:{ _menubar::METHOD_AppendContextMenu(v[0]->to_menubaritem()); break; }

case pcode___menubar__METHOD_ShowContextMenu:{ _menubar::METHOD_ShowContextMenu(v[0]->toQString(), v[1]->tot_integer(), v[2]->tot_integer()); break; }
case pcode___menubar__METHOD_ShowContextMenu1:{ _menubar::METHOD_ShowContextMenu(v[0]->tot_integer(), v[1]->tot_integer()); break; }

case pcode___menubar__METHOD_SetWithTag:{ _menubar::METHOD_SetWithTag(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean()); break; }
case pcode___menubar__METHOD_SetWithTag1:{ _menubar::METHOD_SetWithTag(v[0]->toQString(), v[1]->toQString(), v[2]->tot_integer()); break; }
case pcode___menubar__METHOD_SetWithTag2:{ _menubar::METHOD_SetWithTag(v[0]->toQString(), v[1]->toQString(), v[2]->toQString()); break; }

case pcode___menubar__METHOD_SetWithGroup:{ _menubar::METHOD_SetWithGroup(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean()); break; }
case pcode___menubar__METHOD_SetWithGroup1:{ _menubar::METHOD_SetWithGroup(v[0]->toQString(), v[1]->toQString(), v[2]->tot_integer()); break; }
case pcode___menubar__METHOD_SetWithGroup2:{ _menubar::METHOD_SetWithGroup(v[0]->toQString(), v[1]->toQString(), v[2]->toQString()); break; }

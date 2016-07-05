case pcode___toolbar__METHOD_ToolBarItem:{ p = new interpreter_parameter( _toolbar::METHOD_ToolBarItem(v[0]->toQString(), EXTERN_my_toolbar)); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbar__METHOD_InsertControl:{ _toolbar::METHOD_InsertControl(v[0]->tot_integer(), v[1]->to_control(), EXTERN_my_toolbar); break; }
case pcode___toolbar__METHOD_SetVisible:{ _toolbar::METHOD_SetVisible(v[0]->tot_boolean(), EXTERN_my_toolbar); break; }
case pcode___toolbar__METHOD_IsVisible:{ p = new interpreter_parameter( _toolbar::METHOD_IsVisible(EXTERN_my_toolbar)); if (bReturn) pushStack(p); else delete p; break; }


case pcode___toolbar__METHOD_SetWithTag:{ _toolbar::METHOD_SetWithTag(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean(), EXTERN_my_toolbar); break; }
case pcode___toolbar__METHOD_SetWithTag1:{ _toolbar::METHOD_SetWithTag(v[0]->toQString(), v[1]->toQString(), v[2]->tot_integer(), EXTERN_my_toolbar); break; }
case pcode___toolbar__METHOD_SetWithTag2:{ _toolbar::METHOD_SetWithTag(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), EXTERN_my_toolbar); break; }

case pcode___toolbar__METHOD_SetWithGroup:{ _toolbar::METHOD_SetWithGroup(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean(), EXTERN_my_toolbar); break; }
case pcode___toolbar__METHOD_SetWithGroup1:{ _toolbar::METHOD_SetWithGroup(v[0]->toQString(), v[1]->toQString(), v[2]->tot_integer(), EXTERN_my_toolbar); break; }
case pcode___toolbar__METHOD_SetWithGroup2:{ _toolbar::METHOD_SetWithGroup(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), EXTERN_my_toolbar); break; }


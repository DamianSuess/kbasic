
case pcode___statusbar__METHOD_Clear:{ _statusbar::METHOD_Clear(); break; }
case pcode___statusbar__METHOD_Remove:{ _statusbar::METHOD_Remove(v[0]->to_control()); break; }
case pcode___statusbar__METHOD_InsertControl:{ _statusbar::METHOD_InsertControl(v[0]->tot_integer(), v[1]->to_control()); break; }
case pcode___statusbar__METHOD_InsertControl1:{ _statusbar::METHOD_InsertControl(v[0]->tot_integer(), v[1]->to_control(), v[2]->tot_integer()); break; }
case pcode___statusbar__METHOD_Print:{ _statusbar::METHOD_Print(v[0]->toQString()); break; }
case pcode___statusbar__METHOD_Print1:{ _statusbar::METHOD_Print(v[0]->toQString(), v[1]->tot_integer()); break; }
case pcode___statusbar__METHOD_Open:{ _statusbar::METHOD_Open(); break; }
case pcode___statusbar__METHOD_Close:{ _statusbar::METHOD_Close(); break; }
case pcode___statusbar__METHOD_Toggle:{ _statusbar::METHOD_Toggle(); break; }


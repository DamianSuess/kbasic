
case pcode___record__METHOD_Open:{ p = new interpreter_parameter(_record::METHOD_Open(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Open1:{ p = new interpreter_parameter(_record::METHOD_Open(v[0]->toQString(), v[1]->toQString(), v[2]->to_array(), v[3]->to_array())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Open2:{ p = new interpreter_parameter(_record::METHOD_Open(v[0]->toQString(), v[1]->to_strings(), v[2]->to_array())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Open3:{ p = new interpreter_parameter(_record::METHOD_Open3(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Open4:{ p = new interpreter_parameter(_record::METHOD_Open4(v[0]->toQString(), v[1]->to_array(), v[3]->to_array())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Open5:{ p = new interpreter_parameter(_record::METHOD_Open5(v[0]->to_strings(), v[1]->to_array())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___record__METHOD_Close:{ p = new interpreter_parameter(_record::METHOD_Close(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Requery:{ p = new interpreter_parameter(_record::METHOD_Requery(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_First:{ p = new interpreter_parameter(_record::METHOD_First(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Next:{ p = new interpreter_parameter(_record::METHOD_Next(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Previous:{ p = new interpreter_parameter(_record::METHOD_Previous(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Last:{ p = new interpreter_parameter(_record::METHOD_Last(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_GoTo:{ p = new interpreter_parameter(_record::METHOD_GoTo(v[0]->toQString(), v[1]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Length:{ p = new interpreter_parameter(_record::METHOD_Length(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Position:{ p = new interpreter_parameter(_record::METHOD_Position(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_AddNew:{ p = new interpreter_parameter(_record::METHOD_AddNew(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Insert:{ p = new interpreter_parameter(_record::METHOD_Insert(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Update:{ p = new interpreter_parameter(_record::METHOD_Update(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Delete:{ p = new interpreter_parameter(_record::METHOD_Delete(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Clear:{ p = new interpreter_parameter(_record::METHOD_Clear(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Set:{ _record::METHOD_Set(v[0]->toQString(), v[1]->toQString(), v[2]->toVariant()); break; }
case pcode___record__METHOD_Get:{ p = new interpreter_parameter(_record::METHOD_Get(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_Fields:{ p = new interpreter_parameter(_record::METHOD_Fields(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_PrimaryKeyName:{ p = new interpreter_parameter(_record::METHOD_PrimaryKeyName(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___record__METHOD_PrimaryKey:{ p = new interpreter_parameter(_record::METHOD_PrimaryKey(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
  
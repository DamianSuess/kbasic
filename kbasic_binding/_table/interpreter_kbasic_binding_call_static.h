

case pcode___table__METHOD_Exists:{ p = new interpreter_parameter(_table2::METHOD_Exists(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Exists1:{ p = new interpreter_parameter(_table2::METHOD_Exists1(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Create:{ p = new interpreter_parameter(_table2::METHOD_Create(v[0]->toQString(), v[1]->toQString(), v[2]->to_array())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Create1:{ p = new interpreter_parameter(_table2::METHOD_Create1(v[0]->toQString(), v[1]->to_array())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Create2:{ p = new interpreter_parameter(_table2::METHOD_Create2(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Create3:{ p = new interpreter_parameter(_table2::METHOD_Create3(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Clear:{ p = new interpreter_parameter(_table2::METHOD_Clear(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Clear1:{ p = new interpreter_parameter(_table2::METHOD_Clear1(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Drop:{ p = new interpreter_parameter(_table2::METHOD_Drop(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Drop1:{ p = new interpreter_parameter(_table2::METHOD_Drop1(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
//case pcode___table__METHOD_Copy:{ p = new interpreter_parameter(_table2::METHOD_Copy(v[0]->toQString(), v[1]->toQString(), v[2]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
//case pcode___table__METHOD_Copy1:{ p = new interpreter_parameter(_table2::METHOD_Copy1(v[0]->toQString(), v[1]->toQString(), v[2]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Delete:{ p = new interpreter_parameter(_table2::METHOD_Delete(v[0]->toQString(), v[1]->toQString(), v[2]->to_array())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Delete1:{ p = new interpreter_parameter(_table2::METHOD_Delete1(v[0]->toQString(), v[1]->to_array())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Update:{ p = new interpreter_parameter(_table2::METHOD_Update(v[0]->toQString(), v[1]->toQString(), v[2]->to_array(), v[3]->to_array())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Update1:{ p = new interpreter_parameter(_table2::METHOD_Update1(v[0]->toQString(), v[1]->to_array(), v[2]->to_array())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Insert:{ p = new interpreter_parameter(_table2::METHOD_Insert(v[0]->toQString(), v[1]->toQString(), v[2]->to_array())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_Insert1:{ p = new interpreter_parameter(_table2::METHOD_Insert1(v[0]->toQString(), v[1]->to_array())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___table__METHOD_FieldNames:{ p = new interpreter_parameter(_table2::METHOD_FieldNames(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_FieldNames1:{ p = new interpreter_parameter(_table2::METHOD_FieldNames1(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
  
case pcode___table__METHOD_PrimaryKeyName:{ p = new interpreter_parameter(_table2::METHOD_PrimaryKeyName(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___table__METHOD_PrimaryKeyName1:{ p = new interpreter_parameter(_table2::METHOD_PrimaryKeyName1(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
  
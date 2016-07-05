
case pcode___preferences__METHOD_Has:{ p = new interpreter_parameter( _preferences::METHOD_Has(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___preferences__METHOD_Remove:{ _preferences::METHOD_Remove(v[0]->toQString()); break; }

//case pcode___preferences__METHOD_Load:{ p = new interpreter_parameter( _preferences::METHOD_Load()); if (bReturn) pushStack(p); else delete p; break; }
//case pcode___preferences__METHOD_Save:{ p = new interpreter_parameter( _preferences::METHOD_Save()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___preferences__METHOD_Ids:{ p = new interpreter_parameter( _preferences::METHOD_Ids()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___preferences__METHOD_SetBoolean:{ _preferences::METHOD_SetBoolean(v[0]->toQString(), v[1]->tot_boolean()); break; }
case pcode___preferences__METHOD_SetInteger:{ _preferences::METHOD_SetInteger(v[0]->toQString(), v[1]->tot_integer()); break; }
case pcode___preferences__METHOD_SetString:{ _preferences::METHOD_SetString(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___preferences__METHOD_SetDouble:{ _preferences::METHOD_SetDouble(v[0]->toQString(), v[1]->tot_double()); break; }


case pcode___preferences__METHOD_Boolean:{ p = new interpreter_parameter( _preferences::METHOD_Boolean(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___preferences__METHOD_Integer:{ p = new interpreter_parameter( _preferences::METHOD_Integer(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___preferences__METHOD_String:{ p = new interpreter_parameter( _preferences::METHOD_String(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___preferences__METHOD_Double:{ p = new interpreter_parameter( _preferences::METHOD_Double(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

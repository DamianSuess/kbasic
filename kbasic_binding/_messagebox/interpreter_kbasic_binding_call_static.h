
case pcode___messagebox__METHOD_Show:{ p = new interpreter_parameter(_messagebox::METHOD_Show(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString(), v[4]->toQString(), v[5]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___messagebox__METHOD_Critical:{ p = new interpreter_parameter(_messagebox::METHOD_Critical(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___messagebox__METHOD_Information:{ p = new interpreter_parameter(_messagebox::METHOD_Information(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___messagebox__METHOD_Question:{ p = new interpreter_parameter(_messagebox::METHOD_Question(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___messagebox__METHOD_Warning:{ p = new interpreter_parameter(_messagebox::METHOD_Warning(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
   
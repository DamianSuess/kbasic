//case pcode___fonts__METHOD_Font:{ interpreter_parameter *p = new interpreter_parameter( _fonts::METHOD_Font(v[0]->toConstQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___fonts__METHOD_SetFont:{ _fonts::METHOD_SetFont(v[0]->toConstQString(), v[1]->toConstQString(), v[2]->tot_integer(), v[3]->tot_boolean(), v[4]->tot_boolean(), v[5]->tot_boolean()); break; }
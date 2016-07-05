//case pcode___colors__METHOD_Color:{ interpreter_parameter *p = new interpreter_parameter( _colors::METHOD_Color(v[0]->toConstQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___colors__METHOD_SetRGBA:{ _colors::METHOD_SetColor(v[0]->toConstQString(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->tot_integer()); break; }

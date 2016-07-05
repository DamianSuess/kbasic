
case pcode___inputdialog__METHOD_GetDouble:{ p = new interpreter_parameter(_inputdialog::METHOD_GetDouble(v[0]->toQString(), v[1]->toQString(), v[2]->tot_double(), v[3]->tot_double(), v[4]->tot_double(), v[5]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___inputdialog__METHOD_GetInteger:{ p = new interpreter_parameter(_inputdialog::METHOD_GetInteger(v[0]->toQString(), v[1]->toQString(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->tot_integer(), v[5]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___inputdialog__METHOD_GetString:{ p = new interpreter_parameter(_inputdialog::METHOD_GetString(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___inputdialog__METHOD_Ok:{ p = new interpreter_parameter(_inputdialog::METHOD_Ok()); if (bReturn) pushStack(p); else delete p; break; }

                                
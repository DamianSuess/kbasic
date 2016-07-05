

case pcode___progressdialog__METHOD_Show:{ _progressdialog::METHOD_Show(); break; }
case pcode___progressdialog__METHOD_Show1:{ _progressdialog::METHOD_Show1(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___progressdialog__METHOD_Hide:{ _progressdialog::METHOD_Hide(); break; }
case pcode___progressdialog__METHOD_Canceled:{ p = new interpreter_parameter(_progressdialog::METHOD_Canceled()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___progressdialog__PROPERTYSET_Caption:{ _progressdialog::PROPERTYSET_Caption(v[0]->toQString()); break; }
case pcode___progressdialog__PROPERTYGET_Caption:{ p = new interpreter_parameter(_progressdialog::PROPERTYGET_Caption()); if (bReturn) pushStack(p); else delete p;  break; }

case pcode___progressdialog__PROPERTYSET_Text:{ _progressdialog::PROPERTYSET_Caption(v[0]->toQString()); break; }
case pcode___progressdialog__PROPERTYGET_Text:{ p = new interpreter_parameter(_progressdialog::PROPERTYGET_Caption()); if (bReturn) pushStack(p); else delete p;  break; }

case pcode___progressdialog__PROPERTYSET_CancelCaption:{ _progressdialog::PROPERTYSET_CancelCaption(v[0]->toQString()); break; }
case pcode___progressdialog__PROPERTYGET_CancelCaption:{ p = new interpreter_parameter(_progressdialog::PROPERTYGET_CancelCaption()); if (bReturn) pushStack(p); else delete p;  break; }

case pcode___progressdialog__PROPERTYSET_Value:{ _progressdialog::PROPERTYSET_Value(v[0]->tot_integer()); break; }
case pcode___progressdialog__PROPERTYGET_Value:{ i =  _progressdialog::PROPERTYGET_Value(); if (bReturn) pushStackInteger(i);  break; }

case pcode___progressdialog__PROPERTYSET_Minimum:{ _progressdialog::PROPERTYSET_Minimum(v[0]->tot_integer()); break; }
case pcode___progressdialog__PROPERTYGET_Minimum:{ i =  _progressdialog::PROPERTYGET_Minimum(); if (bReturn) pushStackInteger(i);  break; }

case pcode___progressdialog__PROPERTYSET_Maximum:{ _progressdialog::PROPERTYSET_Maximum(v[0]->tot_integer()); break; }
case pcode___progressdialog__PROPERTYGET_Maximum:{ i =  _progressdialog::PROPERTYGET_Maximum(); if (bReturn) pushStackInteger(i);  break; }

case pcode___progressdialog__PROPERTYSET_Wait:{ _progressdialog::PROPERTYSET_Wait(v[0]->tot_integer()); break; }
case pcode___progressdialog__PROPERTYGET_Wait:{ i =  _progressdialog::PROPERTYGET_Wait(); if (bReturn) pushStackInteger(i);  break; }

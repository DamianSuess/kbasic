
case pcode___colordialog__METHOD_GetColor:{ p = new interpreter_parameter(_colordialog::METHOD_GetColor()); if (bReturn) pushStack(p); else delete p; break; }

//case pcode___colordialog__METHOD_GetColor1:{ p = new interpreter_parameter(_colordialog::METHOD_GetColor1(v[0]->toQString()));if (bReturn) pushStack(p); else delete p; break; }

case pcode___colordialog__METHOD_GetColor1:{ p = new interpreter_parameter(_colordialog::METHOD_GetColor1(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer()));if (bReturn) pushStack(p); else delete p; break; }

case pcode___colordialog__METHOD_Red:{ p = new interpreter_parameter(_colordialog::METHOD_Red());if (bReturn) pushStack(p); else delete p; break; }
case pcode___colordialog__METHOD_Green:{ p = new interpreter_parameter(_colordialog::METHOD_Green());if (bReturn) pushStack(p); else delete p; break; }
case pcode___colordialog__METHOD_Blue:{ p = new interpreter_parameter(_colordialog::METHOD_Blue());if (bReturn) pushStack(p); else delete p; break; }
case pcode___colordialog__METHOD_Alpha:{ p = new interpreter_parameter(_colordialog::METHOD_Alpha());if (bReturn) pushStack(p); else delete p; break; }


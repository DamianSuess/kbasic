/*
case pcode___forms__METHOD_ShowFullScreen:{ _forms::METHOD_ShowFullScreen(); break; }

case pcode___forms__METHOD_ShowMaximized:{ _forms::METHOD_ShowMaximized(); break; }

case pcode___forms__METHOD_ShowMinimized:{ _forms::METHOD_ShowMinimized(); break; }

case pcode___forms__METHOD_ShowNormal:{ _forms::METHOD_ShowNormal(); break; }
*/

case pcode___forms__METHOD_Form:{ interpreter_parameter *p = new interpreter_parameter( _forms::METHOD_Form(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___forms__METHOD_OpenForm:{ _forms::METHOD_OpenForm(v[0]->toQString()); break; }

case pcode___forms__METHOD_CloseForm:{ _forms::METHOD_CloseForm(v[0]->toQString()); break; }

case pcode___forms__METHOD_FocusForm:{ interpreter_parameter *p = new interpreter_parameter( _forms::METHOD_FocusForm()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___forms__METHOD_FirstForm:{ interpreter_parameter *p = new interpreter_parameter( _forms::METHOD_FirstForm()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___forms__METHOD_NextForm:{ interpreter_parameter *p = new interpreter_parameter( _forms::METHOD_NextForm()); if (bReturn) pushStack(p); else delete p; break; }


case pcode___forms__METHOD_IsOpen:{ interpreter_parameter *p = new interpreter_parameter( _forms::METHOD_IsOpen(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___forms__METHOD_SetFocusForm:{ _forms::METHOD_SetFocusForm(v[0]->toQString()); break; }


case pcode___forms__METHOD_FormShowFullScreen:{ _forms::METHOD_FormShowFullScreen(v[0]->toQString()); break; }
case pcode___forms__METHOD_FormShowMaximized:{ _forms::METHOD_FormShowMaximized(v[0]->toQString()); break; }
case pcode___forms__METHOD_FormShowMinimized:{ _forms::METHOD_FormShowMinimized(v[0]->toQString()); break; }
case pcode___forms__METHOD_FormShowNormal:{ _forms::METHOD_FormShowNormal(v[0]->toQString()); break; }
case pcode___forms__METHOD_FormShow:{ _forms::METHOD_FormShow(v[0]->toQString()); break; }
case pcode___forms__METHOD_FormHide:{ _forms::METHOD_FormHide(v[0]->toQString()); break; }

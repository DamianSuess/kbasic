
void SETPROPERTY_BorderBottom(t_integer n)
{ 
  if (GETPROPERTY_BorderBottom() != n){

#if defined(_FORM)    
    repaint();
#endif
    

    _property::SETPROPERTY_BorderBottom(n);
  }
}
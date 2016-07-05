
void SETPROPERTY_BorderTop(t_integer n)
{ 
  if (GETPROPERTY_BorderTop() != n){

#if defined(_FORM)  
    repaint();
#endif
    

    _property::SETPROPERTY_BorderTop(n);
  }
}
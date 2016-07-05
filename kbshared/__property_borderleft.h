
void SETPROPERTY_BorderLeft(t_integer n)
{ 
  if (GETPROPERTY_BorderLeft() != n){

#if defined(_FORM)  
    repaint();
#endif
    

    _property::SETPROPERTY_BorderLeft(n);
  }
}
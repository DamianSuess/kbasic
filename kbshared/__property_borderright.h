
void SETPROPERTY_BorderRight(t_integer n)
{ 
  if (GETPROPERTY_BorderRight() != n){

#if defined(_FORM)  
    repaint();
#endif
    

    _property::SETPROPERTY_BorderRight(n);
  }
}
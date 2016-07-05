
void SETPROPERTY_Shape(t_boolean n)
{ 
  if (GETPROPERTY_Shape() != n){

#ifdef _LABEL
    if (n){
      setFrameShape(QFrame::StyledPanel);
    } else {
      setFrameShape(QFrame::NoFrame);
    }
#endif
    
    _property::SETPROPERTY_Shape(n);
  }
}

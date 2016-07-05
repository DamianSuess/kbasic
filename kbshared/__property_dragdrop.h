
void SETPROPERTY_DragDrop(t_boolean n)
{ 
  if (GETPROPERTY_DragDrop() != n){
    
#ifdef RUN
      setAcceptDrops(n);
#endif

    _property::SETPROPERTY_DragDrop(n);
  }
}
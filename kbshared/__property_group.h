
void SETPROPERTY_Group(const QString & n)
{ 

  if (GETPROPERTY_Group() != n){    

    sGroup = n;  
#ifdef RUN
    b = sGroup.toAscii();
    acGroup = b.data();    
#endif
    _property::SETPROPERTY_Group(n);
  }
}
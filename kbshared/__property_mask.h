
void SETPROPERTY_Mask(const QString & n)
{ 

   clearMask();
   QPixmap p = loadPixmap(n.contains(".") ? n : n + ".png"); 
   setMask(p.mask());

    _property::SETPROPERTY_Mask(n);
  
}


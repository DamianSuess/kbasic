
void SETPROPERTY_Pages(QString kk)
{ 

  if (GETPROPERTY_Pages() != kk){    

    QStringList l = kk.split(";");
    int nIndex = 0;
    int nLen = METHOD_Len();

    if (l.size() > nLen){
      for (int i = nLen; i < l.size(); i++){
        METHOD_AppendTab("", "");
      }
    } 
    else if (l.size() < nLen){
      for (int i = nLen; i > l.size(); i--){
        METHOD_RemoveTab(i);
      }
    } 

    for (int i = 0; i < l.size(); i++){
      QString k = l.at(i);
      int n = k.indexOf("|");
      QString s = k;
      QString image = "";
      if (n > 0){
        s = k.left(n);
        image = k.mid(n + 1);
      }
      METHOD_SetCaption(nIndex + 1, s);
      METHOD_SetIcon(nIndex + 1, image);
      nIndex++;
    }
  
    _property::SETPROPERTY_Pages(kk);
  }
}
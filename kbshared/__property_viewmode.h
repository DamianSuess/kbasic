
void SETPROPERTY_ViewMode(const QString & n)
{ 
  if (GETPROPERTY_ViewMode() != n){

#ifdef _LISTBOX
    if (n.contains("ListMode", Qt::CaseInsensitive)){
      setViewMode(QListView::ListMode);
    }
    else if (n.contains("IconMode", Qt::CaseInsensitive)){
      setViewMode(QListView::IconMode);   
      setSpacing(8);
      setMovement(QListView::Static);
      
    }
#endif
    
    _property::SETPROPERTY_ViewMode(n);
  }
 
}

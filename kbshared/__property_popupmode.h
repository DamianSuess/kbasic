
void SETPROPERTY_PopupMode(const QString & n)
{ 


#ifdef RUN
#ifdef _TOOLBARITEM
    if (my_qtoolbutton){
      
      if (n.contains("DelayedPopup", Qt::CaseInsensitive)) my_qtoolbutton->setPopupMode(QToolButton::DelayedPopup);
      else if (n.contains("MenuButtonPopup", Qt::CaseInsensitive)) my_qtoolbutton->setPopupMode(QToolButton::MenuButtonPopup);
      else if (n.contains("InstantPopup", Qt::CaseInsensitive)) my_qtoolbutton->setPopupMode(QToolButton::InstantPopup);

    }

#endif
 
#endif

    _property::SETPROPERTY_PopupMode(n);
  
}


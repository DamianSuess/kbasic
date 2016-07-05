
void SETPROPERTY_MenuBarRole(const QString & n)
{ 


#ifdef RUN
#ifdef _MENUBARITEM
    if (my_qaction){
      
      if (n.compare("NoRole", Qt::CaseInsensitive) == 0) my_qaction->setMenuRole(QAction::NoRole);
      else if (n.compare("TextHeuristicRole", Qt::CaseInsensitive) == 0) my_qaction->setMenuRole(QAction::TextHeuristicRole);
      else if (n.compare("ApplicationSpecificRole", Qt::CaseInsensitive) == 0) my_qaction->setMenuRole(QAction::ApplicationSpecificRole);
      else if (n.compare("AboutQtRole", Qt::CaseInsensitive) == 0) my_qaction->setMenuRole(QAction::AboutQtRole);
      else if (n.compare("AboutRole", Qt::CaseInsensitive) == 0) my_qaction->setMenuRole(QAction::AboutRole);
      else if (n.compare("PreferencesRole", Qt::CaseInsensitive) == 0) my_qaction->setMenuRole(QAction::PreferencesRole);
      else if (n.compare("QuitRole", Qt::CaseInsensitive) == 0) my_qaction->setMenuRole(QAction::QuitRole);

    }

#endif
 
#endif

    _property::SETPROPERTY_MenuBarRole(n);
  
}


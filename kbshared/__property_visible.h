
void SETPROPERTY_Visible(t_boolean n)
{ 
  
  {
    
#ifdef RUN

#if defined(_MENUITEM)
#elif defined(_MENUBARITEM)
    if (my_qaction) my_qaction->setVisible(n);
#elif defined(_TOOLBARITEM)
    if (my_qaction) my_qaction->setVisible(n);
#elif defined(_FORM)
  #ifdef RUN
      if (n){
        if (!bLoading){ 
          if (dock) dock->show(); 
          if (parentWidget() && qobject_cast<QMdiSubWindow *>(parentWidget())){
            parentWidget()->show(); 
          }
          show(); 
        }
      } else {
       if (!bLoading){ 
         if (dock) dock->hide(); 
         if (parentWidget() && qobject_cast<QMdiSubWindow *>(parentWidget())){
           parentWidget()->hide(); 
         }
         hide(); 
       }
      }
  #elif defined(IDE)
      show();
  #endif
#else
  #ifdef RUN
    QWidget *w = parentWidget();
    if (w && w == (QWidget *) EXTERN_my_toolbar){
      setVisibleToolBar(n, this, w);
    } else {
      if (my_form){
        if (n){
          show();
        } else {
          hide();
        }
      }
    }
  #elif defined(IDE)
      show();
      if (n){
        SETPROPERTY_Background("");
      } else {
        SETPROPERTY_Background("&HFFAAFF");
      }
  #endif
#endif

#endif

    _property::SETPROPERTY_Visible(n);
  }
}

#ifdef RUN

#if defined(_MENUBARITEM)
#elif defined(_TOOLBARITEM)
#else
t_boolean GETPROPERTY_Visible()
{
  return isVisible();
}
#endif

#endif
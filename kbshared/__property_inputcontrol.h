
void SETPROPERTY_InputControl(const QString & n)
{ 
  
  {  

#ifdef RUN

    QWidget *w = 0;
    if (!n.isEmpty()) w = my_form_getControl(my_form, n);

    if (w){
      setTextFormat(Qt::PlainText);
    } else {
      setTextFormat(Qt::AutoText);
    }
    if (buddy() || w) setBuddy(w);
    if (w) w->show(); // needed to make buddy visible at all
      
#endif

    _property::SETPROPERTY_InputControl(n);
  }
}


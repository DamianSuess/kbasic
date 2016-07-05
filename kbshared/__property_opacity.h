
void SETPROPERTY_Opacity(t_integer n, bool bApply = true)
{ 
  
  {    

#ifdef RUN
    if (bApply){
      double d = n;
      d = d / 100;
      
      setWindowOpacity(d);

      QVariant v = property("DockWidget");
      bool b = v.isValid();
      int m = v.toInt();
      QWidget *w = (QWidget *) (int) property("DockWidget").toInt();
      if (w == 0) w = (QWidget *) (int) property("MdiSubWindow").toInt();
      if (w == 0) w = (QWidget *) (int) property("ToolWindow").toInt();
      if (w == 0) w = parentWidget();
      
      if (w){
        
        w->setAutoFillBackground(true);
        QPalette p = w->palette();
        QColor c = QColor(0, 0, 0, n * 2.55);
        p.setColor(QPalette::Window, c);  
        
        w->setPalette(p);
      }
    }
#endif

    _property::SETPROPERTY_Opacity(n);
  }
}

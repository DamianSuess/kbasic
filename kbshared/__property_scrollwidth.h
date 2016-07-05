
void SETPROPERTY_ScrollWidth(t_integer n)
{ 
  if (GETPROPERTY_ScrollWidth() != n){

#if defined(_FORM)
#ifdef IDE
    if (XScrollBar == 0){
      XScrollBar = new QScrollBar(Qt::Horizontal, this);
      connect(XScrollBar, SIGNAL(valueChanged(int)), this, SLOT(XScrollBar_valueChanged(int)));
    }
    XScrollBar->setHidden(GETPROPERTY_ScrollBar().contains("XScrollBarAlwaysOff"));
    XScrollBar->setPageStep(my_form->width());
    XScrollBar->setMinimum(0);
    XScrollBar->setMaximum(n - my_form->width());
    this->resize(width(), height());
#else
    if (!bLoading){
      int w = n;
      if (w == 0 || w < GETPROPERTY_Width()) w = GETPROPERTY_Width();
      int h = GETPROPERTY_ScrollHeight();
      if (h == 0 || h < GETPROPERTY_Height()) h = GETPROPERTY_Height();
      if (GETPROPERTY_ScrollWidth() || GETPROPERTY_ScrollHeight()){
        main->setFixedSize(w, h);    
      } else {
        main->resize(w, h);    
      }
      this->setUpdatesEnabled(false);
      if (GETPROPERTY_ScrollWidth() || GETPROPERTY_ScrollHeight()) this->setMaximumSize(w, h);
      this->setWidget(0);
      this->setWidget(main);
      int w2 = w - this->width();
      this->horizontalScrollBar()->setMaximum(w2);
      int h2 = h - this->height();
      this->verticalScrollBar()->setMaximum(h2);
      this->setUpdatesEnabled(true);
    }
#endif
#endif

    _property::SETPROPERTY_ScrollWidth(n);
  }
}

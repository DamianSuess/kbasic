
void SETPROPERTY_ScrollHeight(t_integer n)
{ 
  if (GETPROPERTY_ScrollHeight() != n){

#if defined(_FORM)
#ifdef IDE
    if (YScrollBar == 0){
      YScrollBar = new QScrollBar(Qt::Vertical, this);
      connect(YScrollBar, SIGNAL(valueChanged(int)), this, SLOT(YScrollBar_valueChanged(int)));
    }
    YScrollBar->setHidden(GETPROPERTY_ScrollBar().contains("YScrollBarAlwaysOff"));
    YScrollBar->setPageStep(my_form->height());
    YScrollBar->setMinimum(0);
    YScrollBar->setMaximum(n - my_form->height());
    this->resize(width(), height());
#else
    if (!bLoading){
      int h = n;
      if (h == 0 || h < GETPROPERTY_Height()) h = GETPROPERTY_Height();
      int w = GETPROPERTY_ScrollWidth();
      if (w == 0 || w < GETPROPERTY_Width()) w = GETPROPERTY_Width();
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

    _property::SETPROPERTY_ScrollHeight(n);
  }
}

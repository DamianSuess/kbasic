
void SETPROPERTY_ArrowType(const QString & n)
{ 


#ifdef RUN
#ifdef _TOOLBARITEM
    if (my_qtoolbutton){
      
      if (n.contains("NoArrow", Qt::CaseInsensitive)) my_qtoolbutton->setArrowType(Qt::NoArrow);
      else if (n.contains("UpArrow", Qt::CaseInsensitive)) my_qtoolbutton->setArrowType(Qt::UpArrow);
      else if (n.contains("DownArrow", Qt::CaseInsensitive)) my_qtoolbutton->setArrowType(Qt::DownArrow);
      else if (n.contains("LeftArrow", Qt::CaseInsensitive)) my_qtoolbutton->setArrowType(Qt::LeftArrow);
      else if (n.contains("RightArrow", Qt::CaseInsensitive)) my_qtoolbutton->setArrowType(Qt::RightArrow);

    }

#endif
 
#endif

    _property::SETPROPERTY_ArrowType(n);
  
}


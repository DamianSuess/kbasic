
void SETPROPERTY_InsertPolicy(const QString & n)
{ 
  if (GETPROPERTY_InsertPolicy() != n){  

#ifdef RUN

    int i = 0;

    if (n.contains("NoInsert"), Qt::CaseInsensitive) i |= QComboBox::NoInsert;
    if (n.contains("InsertAtTop"), Qt::CaseInsensitive) i |= QComboBox::InsertAtTop;
    if (n.contains("InsertAtCurrent"), Qt::CaseInsensitive) i |= QComboBox::InsertAtCurrent;
    if (n.contains("InsertAtBottom"), Qt::CaseInsensitive) i |= QComboBox::InsertAtBottom;
    if (n.contains("InsertAfterCurrent"), Qt::CaseInsensitive) i |= QComboBox::InsertAfterCurrent;
    if (n.contains("InsertBeforeCurrent"), Qt::CaseInsensitive) i |= QComboBox::InsertBeforeCurrent;
    if (n.contains("InsertAlphabetically"), Qt::CaseInsensitive) i |= QComboBox::InsertAlphabetically;

    setInsertPolicy((QComboBox::InsertPolicy) i);
      
#endif

    _property::SETPROPERTY_InsertPolicy(n);
  }
}


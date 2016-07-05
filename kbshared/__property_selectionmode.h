
void SETPROPERTY_SelectionMode(const QString & SelectionMode)
{

#ifdef _FORMSVIEW


#else
  int i = 0;

  if (SelectionMode.contains("SingleSelection", Qt::CaseInsensitive)) i |= QAbstractItemView::SingleSelection;
  if (SelectionMode.contains("ContiguousSelection", Qt::CaseInsensitive)) i |= QAbstractItemView::ContiguousSelection;
  if (SelectionMode.contains("ExtendedSelection", Qt::CaseInsensitive)) i |= QAbstractItemView::ExtendedSelection;
  if (SelectionMode.contains("MultiSelection", Qt::CaseInsensitive)) i |= QAbstractItemView::MultiSelection;
  if (SelectionMode.contains("NoSelection", Qt::CaseInsensitive)) i |= QAbstractItemView::NoSelection;

  setSelectionMode((QAbstractItemView::SelectionMode) i);
#endif

  _property::SETPROPERTY_SelectionMode(SelectionMode);
}

#ifdef _FORMSVIEW
#else
QString GETPROPERTY_SelectionMode()
{
  QAbstractItemView::SelectionMode t = (QAbstractItemView::SelectionMode) selectionMode();

  QString i = "";

  if (t & QAbstractItemView::SingleSelection) i += "SingleSelection"; 
  else if (t & QAbstractItemView::ContiguousSelection) i += "ContiguousSelection"; 
  else if (t & QAbstractItemView::ExtendedSelection) i += "ExtendedSelection"; 
  else if (t & QAbstractItemView::MultiSelection) i += "MultiSelection"; 
  else if (t & QAbstractItemView::NoSelection) i += "NoSelection"; 

  return i;
}
#endif

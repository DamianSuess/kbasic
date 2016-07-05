

void SETPROPERTY_Feature(const QString & n)
{ 
  if (GETPROPERTY_Feature() != n){      

    int i = 0;

    if (n.contains("NoTextInteraction"), Qt::CaseInsensitive) i |= Qt::NoTextInteraction;
    if (n.contains("TextSelectableByMouse"), Qt::CaseInsensitive) i |= Qt::TextSelectableByMouse;
    if (n.contains("TextSelectableByKeyboard"), Qt::CaseInsensitive) i |= Qt::TextSelectableByKeyboard;
    if (n.contains("LinksAccessibleByMouse"), Qt::CaseInsensitive) i |= Qt::LinksAccessibleByMouse;
    if (n.contains("LinksAccessibleByKeyboard"), Qt::CaseInsensitive) i |= Qt::LinksAccessibleByKeyboard;
    if (n.contains("TextEditable"), Qt::CaseInsensitive) i |= Qt::TextEditable;
    if (n.contains("TextEditorInteraction"), Qt::CaseInsensitive) i |= Qt::TextEditorInteraction;
    if (n.contains("TextBrowserInteraction"), Qt::CaseInsensitive) i |= Qt::TextBrowserInteraction;

    setTextInteractionFlags((Qt::TextInteractionFlags) i);

    _property::SETPROPERTY_Feature(n);
  }
}

#if defined(_MENUBARITEM)
#elif defined(_TOOLBARITEM)
#else

#ifdef RUN
QString GETPROPERTY_ParentControl()
{
  QString s = _property::GETPROPERTY_ParentControl();
  if (!s.isEmpty()) return s;

  QWidget *c = parentWidget();
  if (c){
    return c->objectName();
  }
  return "";
}
#endif

#endif
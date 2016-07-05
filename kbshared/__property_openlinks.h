
void SETPROPERTY_OpenLinks(t_boolean n)
{ 
  if (GETPROPERTY_OpenLinks() != n){
    
#ifdef IDE
#ifdef _LABEL
      setOpenExternalLinks(n);
      setTextInteractionFlags(Qt::LinksAccessibleByMouse);
      QString s;
      if (n){
        s = text();
      } else {
        s = GETPROPERTY_Caption();
      }
      QString ss = s;
      if (!s.startsWith("<a href=\"")){
        s = s.prepend("<a href=\"");
        s = s.append("\">");
        s = s.append(ss);
        s = s.append("</a>");
      }
      setText(s);
#endif
#endif
#ifdef RUN
    if (n){
      setOpenExternalLinks(n);
      if (textInteractionFlags() == Qt::NoTextInteraction) setTextInteractionFlags(Qt::LinksAccessibleByMouse);
#ifdef _LABEL
      setTextFormat(Qt::RichText);
      QString s = text();
      QString ss = s;
      if (!s.startsWith("<a href=\"")){
        s = s.prepend("<a href=\"");
        s = s.append("\">");
        s = s.append(ss);
        s = s.append("</a>");
      }
      setText(s);
#endif

    } else {
      setOpenExternalLinks(n);
#ifdef _LABEL
      setTextFormat(Qt::AutoText);
#endif
      setTextInteractionFlags(Qt::NoTextInteraction);
    }
#endif

    _property::SETPROPERTY_OpenLinks(n);
  }
}
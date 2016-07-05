
void SETPROPERTY_EchoMode(const QString & n)
{ 
  if (GETPROPERTY_EchoMode() != n){    

#if defined(_TEXTBOX)

      int i = 0;

      if (n.contains("Normal")) i |= QLineEdit::Normal;
      else if (n.contains("NoEcho")) i |= QLineEdit::NoEcho;
      else if (n.contains("PasswordEchoOnEdit")) i |= QLineEdit::PasswordEchoOnEdit;
      else if (n.contains("Password")) i |= QLineEdit::Password;

      setEchoMode((QLineEdit::EchoMode) i);

#endif

    _property::SETPROPERTY_EchoMode(n);
  }
}

QString GETPROPERTY_EchoMode()
{
  QString s = _property::GETPROPERTY_EchoMode();
  if (s.isEmpty()) return "Normal";
  return s;
}

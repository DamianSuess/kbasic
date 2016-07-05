
void SETPROPERTY_BooleanValue(t_boolean n)
{ 
  bool b = GETPROPERTY_BooleanValue() != n;

#if defined(_LABEL) || defined(_TEXTBOX) || defined(_COMBOBOX) || defined(_LISTBOX) || defined(_CHECKBOX) || defined(_DATEBOX) || defined(_TIMEBOX)/* || defined(_DATETIMEBOX)*/ || defined(_EDITOR)
  if (!GETPROPERTY_SQLName().isEmpty()) b = true;
#endif

  if (b){

#if defined(_MENUBARITEM)
#elif defined(_RADIOBUTTON)
    QString s = GETPROPERTY_Group();
    if (s.isEmpty()){
      setChecked(n);
    } else {
      my_form_setRadioButtonBooleanValue(my_form, s, this, n);
    }
#else
    setChecked(n);
#endif

    _property::SETPROPERTY_BooleanValue(n);
  }
}


void SETPROPERTY_BooleanValue2(t_boolean n)
{
   _property::SETPROPERTY_BooleanValue(n);
}
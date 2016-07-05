
void SETPROPERTY_AcceptRichText(t_boolean n)
{ 
  if (GETPROPERTY_AcceptRichText() != n){
    
    setAcceptRichText(n);

    _property::SETPROPERTY_AcceptRichText(n);
  }
}

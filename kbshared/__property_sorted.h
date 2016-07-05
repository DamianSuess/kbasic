
void SETPROPERTY_Sorted(t_boolean n)
{ 
  {    

    setSortingEnabled(n);
    if (n) sortItems();

    _property::SETPROPERTY_Sorted(n);
  }
}
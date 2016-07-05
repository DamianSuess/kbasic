
void SETPROPERTY_DrawOnPaint(t_boolean n)
{ 
  if (GETPROPERTY_DrawOnPaint() != n){
    
    repaint();

    _property::SETPROPERTY_DrawOnPaint(n);
  }
}
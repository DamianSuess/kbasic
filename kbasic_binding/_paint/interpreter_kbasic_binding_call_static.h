
case pcode___paint__METHOD_Begin:{ _paint::METHOD_Begin(v[0]->tot_integer(), v[1]->tot_integer()); break; }
case pcode___paint__METHOD_End:{ interpreter_parameter *p = new interpreter_parameter(_paint::METHOD_End()  ); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__METHOD_DrawBinary:{ _paint::METHOD_DrawBinary(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString(), v[5]->tot_integer(), v[6]->tot_integer(), v[7]->tot_integer(), v[8]->tot_integer()); break; }
case pcode___paint__METHOD_DrawBinary1:{ _paint::METHOD_DrawBinary1(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString()); break; }
case pcode___paint__METHOD_DrawBinary2:{ _paint::METHOD_DrawBinary2(v[0]->toConstQString()); break; }

case pcode___paint__METHOD_PutBinary:{ _paint::METHOD_DrawBinary(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString(), v[5]->tot_integer(), v[6]->tot_integer(), v[7]->tot_integer(), v[8]->tot_integer()); break; }
case pcode___paint__METHOD_PutBinary1:{ _paint::METHOD_DrawBinary1(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString()); break; }
case pcode___paint__METHOD_PutBinary2:{ _paint::METHOD_DrawBinary2(v[0]->toConstQString()); break; }

case pcode___paint__METHOD_GetBinary:{ interpreter_parameter *p = new interpreter_parameter( _paint::METHOD_GetBinary(v[0]->to_control(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->tot_integer()) ); if (bReturn) pushStack(p); else delete p; break; }
case pcode___paint__METHOD_GetBinary1:{ interpreter_parameter *p = new interpreter_parameter( _paint::METHOD_GetBinary1(v[0]->to_control()) ); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__METHOD_LoadBinary:{ interpreter_parameter *p = new interpreter_parameter( _paint::METHOD_LoadBinary(v[0]->toConstQString()) ); if (bReturn) pushStack(p); else delete p; break; }
case pcode___paint__METHOD_LoadBinary1:{ interpreter_parameter *p = new interpreter_parameter( _paint::METHOD_LoadBinary1(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString(), v[5]->tot_integer(), v[6]->tot_integer(), v[7]->tot_integer(), v[8]->tot_integer()) ); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__METHOD_SaveBinary:{ interpreter_parameter *p = new interpreter_parameter( _paint::METHOD_SaveBinary(v[0]->to_control(), v[1]->toConstQString()) ); if (bReturn) pushStack(p); else delete p; break; }
case pcode___paint__METHOD_SaveBinary1:{ interpreter_parameter *p = new interpreter_parameter( _paint::METHOD_SaveBinary1(v[0]->to_control(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->tot_integer(), v[5]->toConstQString()) ); if (bReturn) pushStack(p); else delete p; break; }




case pcode___paint__METHOD_DrawShadowText:{ _paint::METHOD_DrawShadowText(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_boolean(), v[3]->toConstQString()); break; }

case pcode___paint__METHOD_DrawTextRect:{ _paint::METHOD_DrawTextRect(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString()); break; }
case pcode___paint__METHOD_DrawFramedTextRect:{ _paint::METHOD_DrawFramedTextRect(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->tot_boolean(), v[5]->toConstQString()); break; }
case pcode___paint__METHOD_DrawShadowTextRect:{ _paint::METHOD_DrawShadowTextRect(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->tot_boolean(), v[5]->toConstQString()); break; }


case pcode___paint__METHOD_DrawArc:{ _paint::METHOD_DrawArc(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->tot_integer(), v[5]->tot_integer()); break; }

case pcode___paint__METHOD_DrawChord:{ _paint::METHOD_DrawChord(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->tot_integer(), v[5]->tot_integer()); break; }

case pcode___paint__METHOD_DrawEllipse:{ _paint::METHOD_DrawEllipse(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer()); break; }

case pcode___paint__METHOD_DrawLine:{ _paint::METHOD_DrawLine(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer()); break; }

case pcode___paint__METHOD_DrawPie:{ _paint::METHOD_DrawPie(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->tot_integer(), v[5]->tot_integer()); break; }

case pcode___paint__METHOD_DrawPixmap:{ _paint::METHOD_DrawPixmap(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString(), v[5]->tot_integer(), v[6]->tot_integer(), v[7]->tot_integer(), v[8]->tot_integer()); break; }

case pcode___paint__METHOD_DrawTiledPixmap:{ _paint::METHOD_DrawTiledPixmap(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString(), v[5]->tot_integer(), v[6]->tot_integer()); break; }

//case pcode___paint__METHOD_DrawPixmap1:{ _paint::METHOD_DrawPixmap(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->to_pixmap(), v[5]->tot_integer(), v[6]->tot_integer(), v[7]->tot_integer(), v[8]->tot_integer()); break; }

//case pcode___paint__METHOD_DrawTiledPixmap1:{ _paint::METHOD_DrawTiledPixmap(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->to_pixmap(), v[5]->tot_integer(), v[6]->tot_integer()); break; }

case pcode___paint__METHOD_DrawPixmap2:{ _paint::METHOD_DrawPixmap(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->toConstQString()); break; }

case pcode___paint__METHOD_DrawTiledPixmap2:{ _paint::METHOD_DrawTiledPixmap(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString()); break; }

//case pcode___paint__METHOD_DrawPixmap3:{ _paint::METHOD_DrawPixmap(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->to_pixmap()); break; }

//case pcode___paint__METHOD_DrawTiledPixmap3:{ _paint::METHOD_DrawTiledPixmap(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->to_pixmap()); break; }

case pcode___paint__METHOD_DrawPoint:{ _paint::METHOD_DrawPoint(v[0]->tot_integer(), v[1]->tot_integer()); break; }

case pcode___paint__METHOD_DrawRect:{ _paint::METHOD_DrawRect(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer()); break; }

case pcode___paint__METHOD_DrawRoundRect:{ _paint::METHOD_DrawRoundRect(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->tot_integer(), v[5]->tot_integer()); break; }

case pcode___paint__METHOD_DrawText:{ _paint::METHOD_DrawText(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->toConstQString()); break; }

case pcode___paint__METHOD_DrawFramedText:{ _paint::METHOD_DrawFramedText(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_boolean(), v[3]->toConstQString()); break; }

case pcode___paint__METHOD_SetFont:{ _paint::METHOD_SetFont(v[0]->toConstQString()); break; }

//case pcode___paint__METHOD_SetFont1:{ _paint::METHOD_SetFont(v[0]->to_font()); break; }

case pcode___paint__METHOD_SetPen:{ _paint::METHOD_SetPen(v[0]->toConstQString()); break; }

case pcode___paint__METHOD_SetPen1:{ _paint::METHOD_SetPen(v[0]->toConstQString(), v[1]->tot_integer(), v[2]->tot_long(), v[3]->tot_long(), v[4]->tot_long()); break; }

case pcode___paint__METHOD_SetPen2:{ _paint::METHOD_SetPen(v[0]->to_color()); break; }

case pcode___paint__METHOD_SetPen3:{ _paint::METHOD_SetPen(v[0]->to_color(), v[1]->tot_integer(), v[2]->tot_long(), v[3]->tot_long(), v[4]->tot_long()); break; }

//case pcode___paint__METHOD_SetPenPixmap:{ _paint::METHOD_SetPenPixmap(v[0]->to_pixmap()); break; }

case pcode___paint__METHOD_SetPenPixmap1:{ _paint::METHOD_SetPenPixmap(v[0]->toConstQString()); break; }

case pcode___paint__METHOD_SetBrush:{ _paint::METHOD_SetBrush(v[0]->toConstQString()); break; }

case pcode___paint__METHOD_SetBrush1:{ _paint::METHOD_SetBrush(v[0]->toConstQString(), v[1]->tot_long()); break; }

case pcode___paint__METHOD_SetBrush2:{ _paint::METHOD_SetBrush(v[0]->to_color()); break; }

case pcode___paint__METHOD_SetBrush3:{ _paint::METHOD_SetBrush(v[0]->to_color(), v[1]->tot_long()); break; }

//case pcode___paint__METHOD_SetBrushPixmap:{ _paint::METHOD_SetBrushPixmap(v[0]->to_pixmap()); break; }

case pcode___paint__METHOD_SetBrushPixmap1:{ _paint::METHOD_SetBrushPixmap(v[0]->toConstQString()); break; }

case pcode___paint__METHOD_SetOpacity:{ _paint::METHOD_SetOpacity(v[0]->tot_double()); break; }

case pcode___paint__METHOD_SetBackgroundFilled:{ _paint::METHOD_SetBackgroundFilled(v[0]->tot_boolean()); break; }

case pcode___paint__METHOD_SetBackground:{ _paint::METHOD_SetBackground(v[0]->toConstQString()); break; }

case pcode___paint__METHOD_SetBackground1:{ _paint::METHOD_SetBackground(v[0]->to_color()); break; }

//case pcode___paint__METHOD_SetBackgroundPixmap:{ _paint::METHOD_SetBackgroundPixmap(v[0]->to_pixmap()); break; }

case pcode___paint__METHOD_SetBackgroundPixmap1:{ _paint::METHOD_SetBackgroundPixmap(v[0]->toConstQString()); break; }

case pcode___paint__METHOD_FillRect:{ _paint::METHOD_FillRect(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString()); break; }

case pcode___paint__METHOD_FillRect1:{ _paint::METHOD_FillRect(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->to_color()); break; }

case pcode___paint__METHOD_FillRectPixmap:{ _paint::METHOD_FillRectPixmap(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->toConstQString()); break; }

//case pcode___paint__METHOD_FillRectPixmap1:{ _paint::METHOD_FillRectPixmap(v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), v[4]->to_pixmap()); break; }

case pcode___paint__METHOD_SetLayoutDirection:{ _paint::METHOD_SetLayoutDirection(v[0]->tot_boolean()); break; }

case pcode___paint__GETPROPERTY_NoBrush:{ interpreter_parameter *p = new interpreter_parameter( Qt::NoBrush); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_SolidPattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::SolidPattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_Dense1Pattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::Dense1Pattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_Dense2Pattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::Dense2Pattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_Dense3Pattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::Dense3Pattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_Dense4Pattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::Dense4Pattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_Dense5Pattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::Dense5Pattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_Dense6Pattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::Dense6Pattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_Dense7Pattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::Dense7Pattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_HorPattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::HorPattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_VerPattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::VerPattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_CrossPattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::CrossPattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_BDiagPattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::BDiagPattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_FDiagPattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::FDiagPattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_DiagCrossPattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::DiagCrossPattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_LinearGradientPattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::LinearGradientPattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_ConicalGradientPattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::ConicalGradientPattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_RadialGradientPattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::RadialGradientPattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_TexturePattern:{ interpreter_parameter *p = new interpreter_parameter( Qt::TexturePattern); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_NoPen:{ interpreter_parameter *p = new interpreter_parameter( Qt::NoPen); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_SolidLine:{ interpreter_parameter *p = new interpreter_parameter( Qt::SolidLine); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_DashLine:{ interpreter_parameter *p = new interpreter_parameter( Qt::DashLine); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_DotLine:{ interpreter_parameter *p = new interpreter_parameter( Qt::DotLine); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_DashDotLine:{ interpreter_parameter *p = new interpreter_parameter( Qt::DashDotLine); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_DashDotDotLine:{ interpreter_parameter *p = new interpreter_parameter( Qt::DashDotDotLine); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_CustomDashLine:{ interpreter_parameter *p = new interpreter_parameter( Qt::CustomDashLine); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_FlatCap:{ interpreter_parameter *p = new interpreter_parameter( Qt::FlatCap); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_SquareCap:{ interpreter_parameter *p = new interpreter_parameter( Qt::SquareCap); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_RoundCap:{ interpreter_parameter *p = new interpreter_parameter( Qt::RoundCap); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_MiterJoin:{ interpreter_parameter *p = new interpreter_parameter( Qt::MiterJoin); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_BevelJoin:{ interpreter_parameter *p = new interpreter_parameter( Qt::BevelJoin); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_RoundJoin:{ interpreter_parameter *p = new interpreter_parameter( Qt::RoundJoin); if (bReturn) pushStack(p); else delete p; break; }

case pcode___paint__GETPROPERTY_SvgMiterJoin:{ interpreter_parameter *p = new interpreter_parameter( Qt::SvgMiterJoin); if (bReturn) pushStack(p); else delete p; break; }
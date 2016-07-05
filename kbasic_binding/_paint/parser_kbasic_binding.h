
new_class(pcode___paint, 0, 0); 

   new_param("Width", pcode__INTEGER, false);
   new_param("Height", pcode__INTEGER, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_Begin, pcode__VOID);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_End, pcode__QString);

	 new_param("DestinationX", pcode__t_integer, false);
	 new_param("DestinationY", pcode__t_integer, false);
	 new_param("DestinationWidth", pcode__t_integer, false);
	 new_param("DestinationHeight", pcode__t_integer, false);
	 new_param("Binary", pcode__QString, false);
	 new_param("SourceX", pcode__t_integer, false);
	 new_param("SourceY", pcode__t_integer, false);
	 new_param("SourceWidth", pcode__t_integer, false);
	 new_param("SourceHeight", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawBinary, pcode__VOID);


	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("Binary", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawBinary1, pcode__VOID);


	 new_param("Binary", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawBinary2, pcode__VOID);

	 new_param("DestinationX", pcode__t_integer, false);
	 new_param("DestinationY", pcode__t_integer, false);
	 new_param("DestinationWidth", pcode__t_integer, false);
	 new_param("DestinationHeight", pcode__t_integer, false);
	 new_param("Binary", pcode__QString, false);
	 new_param("SourceX", pcode__t_integer, false);
	 new_param("SourceY", pcode__t_integer, false);
	 new_param("SourceWidth", pcode__t_integer, false);
	 new_param("SourceHeight", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_PutBinary, pcode__VOID);


	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("Binary", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_PutBinary1, pcode__VOID);


	 new_param("Binary", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_PutBinary2, pcode__VOID);



	 new_param("Control", pcode___control, false);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_GetBinary, pcode__QString);


	 new_param("Control", pcode___control, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_GetBinary1, pcode__QString);


	 new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_LoadBinary, pcode__BOOLEAN);


	 new_param("DestinationX", pcode__t_integer, false);
	 new_param("DestinationY", pcode__t_integer, false);
	 new_param("DestinationWidth", pcode__t_integer, false);
	 new_param("DestinationHeight", pcode__t_integer, false);
	 new_param("FileName", pcode__QString, false);
	 new_param("SourceX", pcode__t_integer, false);
	 new_param("SourceY", pcode__t_integer, false);
	 new_param("SourceWidth", pcode__t_integer, false);
	 new_param("SourceHeight", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_LoadBinary1, pcode__BOOLEAN);

	 new_param("Control", pcode___control, false);
	 new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SaveBinary, pcode__BOOLEAN);

	 new_param("Control", pcode___control, false);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SaveBinary1, pcode__BOOLEAN);




	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("BlackShadow", pcode__t_boolean, false);
	 new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawShadowText, pcode__VOID);


	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawTextRect, pcode__VOID);

	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("BlackFrame", pcode__t_boolean, false);
	 new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawFramedTextRect, pcode__VOID);

	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("BlackShadow", pcode__t_boolean, false);
	 new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawShadowTextRect, pcode__VOID);


//new_method(true, pcode___paint, pcode___paint___paint, pcode___paint);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("StartAngle", pcode__t_integer, false);
	 new_param("SpanAngle", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawArc, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("StartAngle", pcode__t_integer, false);
	 new_param("SpanAngle", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawChord, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawEllipse, pcode__VOID);
	 new_param("X1", pcode__t_integer, false);
	 new_param("Y1", pcode__t_integer, false);
	 new_param("X2", pcode__t_integer, false);
	 new_param("Y2", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawLine, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("StartAngle", pcode__t_integer, false);
	 new_param("SpanAngle", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawPie, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("PixmapId", pcode__QString, false);
	 new_param("SX", pcode__t_integer, false);
	 new_param("SY", pcode__t_integer, false);
	 new_param("SWidth", pcode__t_integer, false);
	 new_param("SHeight", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawPixmap, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("PixmapId", pcode__QString, false);
	 new_param("SX", pcode__t_integer, false);
	 new_param("SY", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawTiledPixmap, pcode__VOID);
/*
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("PixmapObject", pcode___pixmap, false);
	 new_param("SX", pcode__t_integer, false);
	 new_param("SY", pcode__t_integer, false);
	 new_param("SWidth", pcode__t_integer, false);
	 new_param("SHeight", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawPixmap1, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("PixmapObject", pcode___pixmap, false);
	 new_param("SX", pcode__t_integer, false);
	 new_param("SY", pcode__t_integer, false);*/
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawTiledPixmap1, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("PixmapId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawPixmap2, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("PixmapId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawTiledPixmap2, pcode__VOID);
/*
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("PixmapObject", pcode___pixmap, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawPixmap3, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("PixmapObject", pcode___pixmap, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawTiledPixmap3, pcode__VOID);*/
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawPoint, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawRect, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("XRnd", pcode__t_integer, false);
	 new_param("YRnd", pcode__t_integer, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawRoundRect, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawText, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("BlackFrame", pcode__t_boolean, false);
	 new_param("Text", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_DrawFramedText, pcode__VOID);
	 new_param("FontId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetFont, pcode__VOID);
/*
	 new_param("FontObject", pcode___font, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetFont1, pcode__VOID);
*/
	 new_param("ColorId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetPen, pcode__VOID);
	 new_param("ColorId", pcode__QString, false);
	 new_param("Size", pcode__t_integer, false);
	 new_param("PenStyle", pcode__t_long, false);
	 new_param("PenCapStyle", pcode__t_long, false);
	 new_param("PenJoinStyle", pcode__t_long, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetPen1, pcode__VOID);

	 new_param("ColorObject", pcode___color, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetPen2, pcode__VOID);

	 new_param("ColorObject", pcode___color, false);
	 new_param("Size", pcode__t_integer, false);
	 new_param("PenStyle", pcode__t_long, false);
	 new_param("PenCapStyle", pcode__t_long, false);
	 new_param("PenJoinStyle", pcode__t_long, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetPen3, pcode__VOID);
	 new_param("PixmapObject", pcode___pixmap, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetPenPixmap, pcode__VOID);

  new_param("PixmapId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetPenPixmap1, pcode__VOID);

	 new_param("ColorId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBrush, pcode__VOID);
	 new_param("ColorId", pcode__QString, false);
	 new_param("BrushStyle", pcode__t_long, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBrush1, pcode__VOID);

	 new_param("ColorObject", pcode___color, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBrush2, pcode__VOID);
	 new_param("ColorObject", pcode___color, false);
	 new_param("BrushStyle", pcode__t_long, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBrush3, pcode__VOID);
/*
	 new_param("PixmapObject", pcode___pixmap, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBrushPixmap, pcode__VOID);*/

	 new_param("PixmapId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBrushPixmap1, pcode__VOID);

	 new_param("d", pcode__t_double, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetOpacity, pcode__VOID);
	 new_param("b", pcode__t_boolean, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBackgroundFilled, pcode__VOID);
	 new_param("ColorId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBackground, pcode__VOID);

	 new_param("ColorObject", pcode___color, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBackground1, pcode__VOID);/*
	 new_param("PixmapObject", pcode___pixmap, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBackgroundPixmap, pcode__VOID);*/
	 new_param("PixmapId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetBackgroundPixmap1, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("ColorId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_FillRect, pcode__VOID);

	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("ColorObject", pcode___color, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_FillRect1, pcode__VOID);
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("PixmapId", pcode__QString, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_FillRectPixmap, pcode__VOID);
/*
	 new_param("X", pcode__t_integer, false);
	 new_param("Y", pcode__t_integer, false);
	 new_param("Width", pcode__t_integer, false);
	 new_param("Height", pcode__t_integer, false);
	 new_param("PixmapObject", pcode___pixmap, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_FillRectPixmap1, pcode__VOID);
*/
	 new_param("b", pcode__t_boolean, false);
new_staticmethod(true, pcode___paint, pcode___paint__METHOD_SetLayoutDirection, pcode__VOID);

new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_NoBrush, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_SolidPattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_Dense1Pattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_Dense2Pattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_Dense3Pattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_Dense4Pattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_Dense5Pattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_Dense6Pattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_Dense7Pattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_HorPattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_VerPattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_CrossPattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_BDiagPattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_FDiagPattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_DiagCrossPattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_LinearGradientPattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_ConicalGradientPattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_RadialGradientPattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_TexturePattern, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_NoPen, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_SolidLine, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_DashLine, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_DotLine, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_DashDotLine, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_DashDotDotLine, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_CustomDashLine, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_FlatCap, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_SquareCap, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_RoundCap, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_MiterJoin, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_BevelJoin, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_RoundJoin, pcode__t_long);
new_staticproperty_get(pcode___paint, pcode___paint__GETPROPERTY_SvgMiterJoin, pcode__t_long);
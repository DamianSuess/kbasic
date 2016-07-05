/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#ifndef _PAINT_H
#define _PAINT_H

#include <QPainter>

#include "typedef.h"

#ifdef RUN
extern QPainter *EXTERN_myQPainter;

extern QMap<QString, QPixmap>pixmaps_map;
extern QMap<QString, QFont>fonts_map;
extern QMap<QString, QColor>colors_map;

extern bool bLockingCauseOfBinaryDrawing;
//extern QWidget *binaryDrawingWidget;
extern QPainter *SAVE;
extern QString binary;

extern QPixmap *binaryPixmap;

#endif

class _paint
{
#ifdef RUN
public:

_paint()
{
}

inline static void METHOD_Begin(t_integer Width, t_integer Height)
{
  bLockingCauseOfBinaryDrawing = true;
  binaryPixmap = new QPixmap(Width, Height);
  binaryPixmap->fill(Qt::white);

  SAVE = EXTERN_myQPainter;
  EXTERN_myQPainter = new QPainter(binaryPixmap);

  binary = "";
}

inline static QString METHOD_End()
{
  if (EXTERN_myQPainter) delete EXTERN_myQPainter;

  if (binaryPixmap){

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    binaryPixmap->save(&buffer, "PNG"); // writes pixmap into bytes in PNG format    
    binary = QString::fromLatin1((const char *) bytes.data(), bytes.size());
    
    delete binaryPixmap;
    binaryPixmap = 0;
  }

  EXTERN_myQPainter = SAVE;
  bLockingCauseOfBinaryDrawing = false;
  return binary;
}



inline static void METHOD_DrawBinary(t_integer DestinationX, t_integer DestinationY, t_integer DestinationWidth, t_integer DestinationHeight, QString Binary, t_integer SourceX, t_integer SourceY, t_integer SourceWidth, t_integer SourceHeight)
{
  QPixmap p;
  p.loadFromData(Binary.toLatin1());
  EXTERN_myQPainter->drawPixmap(DestinationX, DestinationY, DestinationWidth, DestinationHeight, p, SourceX, SourceY, SourceWidth, SourceHeight);
}

inline static void METHOD_DrawBinary1(t_integer X, t_integer Y, t_integer Width, t_integer Height, QString Binary)
{
  QPixmap p;
  p.loadFromData(Binary.toLatin1());
  EXTERN_myQPainter->drawPixmap(X, Y, Width, Height, p, 0, 0, p.width(), p.height());
}

inline static void METHOD_DrawBinary2(QString Binary)
{
  QPixmap p;
  p.loadFromData(Binary.toLatin1());
  EXTERN_myQPainter->drawPixmap(0, 0, p, 0, 0, p.width(), p.height());
}


inline static QString METHOD_GetBinary(_control *c, t_integer X, t_integer Y, t_integer Width, t_integer Height)
{

  QWidget *w = qobject_cast<QWidget *>(c);
  if (w == 0) return "";

  QPixmap p = QPixmap::grabWidget(w, X, Y, Width, Height);
  
  QByteArray bytes;
  QBuffer buffer(&bytes);
  buffer.open(QIODevice::WriteOnly);
  p.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format

  static QString s;
  s = QString::fromLatin1((const char *) bytes.data(), bytes.size());
  return s;
}

inline static QString METHOD_GetBinary1(_control *c)
{

  QWidget *w = qobject_cast<QWidget *>(c);
  if (w == 0) return "";

  QPixmap p = QPixmap::grabWidget(w, 0, 0, w->width(), w->height());
  
  QByteArray bytes;
  QBuffer buffer(&bytes);
  buffer.open(QIODevice::WriteOnly);
  p.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format

  static QString s;
  s = QString::fromLatin1((const char *) bytes.data(), bytes.size());
  return s;  
}

inline static t_boolean METHOD_LoadBinary(QString FileName)
{
  QPixmap p;
  if (!(FileName.contains("/") || FileName.contains("\\"))){    
    int nn = 0;
    t_pointer pp = loadProjectFile(FileName, &nn);
    p.loadFromData((const uchar *) pp, nn);
  } else {
    p.load(FileName);
  }
  EXTERN_myQPainter->drawPixmap(0, 0, p, 0, 0, p.width(), p.height());
  return p.isNull();
}

inline static t_boolean METHOD_LoadBinary1(t_integer DestinationX, t_integer DestinationY, t_integer DestinationWidth, t_integer DestinationHeight, QString FileName, t_integer SourceX, t_integer SourceY, t_integer SourceWidth, t_integer SourceHeight)
{
  QPixmap p;
  if (!(FileName.contains("/") || FileName.contains("\\"))){    
    int nn = 0;
    t_pointer pp = loadProjectFile(FileName, &nn);
    p.loadFromData((const uchar *) pp, nn);
  } else {
    p.load(FileName);
  }
  EXTERN_myQPainter->drawPixmap(DestinationX, DestinationY, DestinationWidth, DestinationHeight, p, SourceX, SourceY, SourceWidth, SourceHeight);
  return p.isNull();
}

inline static t_boolean METHOD_LoadBinary2(t_integer X, t_integer Y, t_integer Width, t_integer Height, QString FileName)
{
  QPixmap p;
  if (!(FileName.contains("/") || FileName.contains("\\"))){    
    int nn = 0;
    t_pointer pp = loadProjectFile(FileName, &nn);
    p.loadFromData((const uchar *) pp, nn);
  } else {
    p.load(FileName);
  }
  EXTERN_myQPainter->drawPixmap(X, Y, Width, Height, p, 0, 0, p.width(), p.height());
  return p.isNull();
}

inline static t_boolean METHOD_SaveBinary(_control *c, QString FileName)
{
  QWidget *w = qobject_cast<QWidget *>(c);
  if (w == 0) return false;

  QPixmap p = QPixmap::grabWidget(w, 0, 0, w->width(), w->height());
  return p.save(FileName);    
}

inline static t_boolean METHOD_SaveBinary1(_control *c, t_integer X, t_integer Y, t_integer Width, t_integer Height, QString FileName)
{
  QWidget *w = qobject_cast<QWidget *>(c);
  if (w == 0) return false;

  QPixmap p = QPixmap::grabWidget(w, X, Y, Width, Height);
  return p.save(FileName);    
}



inline static void METHOD_DrawArc(t_integer X, t_integer Y, t_integer Width, t_integer Height, t_integer StartAngle, t_integer SpanAngle)
{
  EXTERN_myQPainter->drawArc(X, Y, Width, Height, StartAngle, SpanAngle);
}

inline static void METHOD_DrawChord(t_integer X, t_integer Y, t_integer Width, t_integer Height, t_integer StartAngle, t_integer SpanAngle)
{
  EXTERN_myQPainter->drawChord(X, Y, Width, Height, StartAngle, SpanAngle);
}

inline static void METHOD_DrawEllipse(t_integer X, t_integer Y, t_integer Width, t_integer Height)
{
  EXTERN_myQPainter->drawEllipse(X, Y, Width, Height);
}

inline static void METHOD_DrawLine(t_integer X1, t_integer Y1, t_integer X2, t_integer Y2)
{
  EXTERN_myQPainter->drawLine(X1, Y1, X2, Y2);
}

inline static void METHOD_DrawPie(t_integer X, t_integer Y, t_integer Width, t_integer Height, t_integer StartAngle, t_integer SpanAngle)
{
  EXTERN_myQPainter->drawPie(X, Y, Width, Height, StartAngle, SpanAngle);
}

inline static void METHOD_DrawPixmap(t_integer X, t_integer Y, t_integer Width, t_integer Height, const QString & PixmapId, t_integer SX, t_integer SY, t_integer SWidth, t_integer SHeight)
{
  const QPixmap & p = pixmaps_map[PixmapId];
  if (p.isNull()) return;
  EXTERN_myQPainter->drawPixmap(X, Y, Width, Height, p, SX, SY, SWidth, SHeight);
}

inline static void METHOD_DrawTiledPixmap(t_integer X, t_integer Y, t_integer Width, t_integer Height, const QString & PixmapId, t_integer SX, t_integer SY)
{
  const QPixmap & p = pixmaps_map[PixmapId];
  if (p.isNull()) return;
  EXTERN_myQPainter->drawTiledPixmap(X, Y, Width, Height, p, SX, SY);
}

/*
inline static void METHOD_DrawPixmap(t_integer X, t_integer Y, t_integer Width, t_integer Height, _pixmap *PixmapObject, t_integer SX, t_integer SY, t_integer SWidth, t_integer SHeight)
{
  EXTERN_myQPainter->drawPixmap(X, Y, Width, Height, (const QPixmap &) PixmapObject, SX, SY, SWidth, SHeight);
}
*/

/*
inline static void METHOD_DrawTiledPixmap(t_integer X, t_integer Y, t_integer Width, t_integer Height, _pixmap *PixmapObject, t_integer SX, t_integer SY)
{
  EXTERN_myQPainter->drawTiledPixmap(X, Y, Width, Height, (const QPixmap &) PixmapObject, SX, SY);
}
*/
inline static void METHOD_DrawPixmap(t_integer X, t_integer Y, const QString & PixmapId)
{
  const QPixmap & p = pixmaps_map[PixmapId];
  if (p.isNull()) return;
  EXTERN_myQPainter->drawPixmap(X, Y, p);
}

inline static void METHOD_DrawTiledPixmap(t_integer X, t_integer Y, t_integer Width, t_integer Height, const QString & PixmapId)
{
  const QPixmap & p = pixmaps_map[PixmapId];
  if (p.isNull()) return;
  EXTERN_myQPainter->drawPixmap(X, Y, Width, Height, p);
}
  /*  
inline static void METHOD_DrawPixmap(t_integer X, t_integer Y, _pixmap *PixmapObject)
{
  //t_pointer pp = (t_pointer) PixmapObject;
  const QPixmap & p = (QPixmap) * (QPixmap *)PixmapObject;
  EXTERN_myQPainter->drawPixmap(X, Y, p);
 

}*/
/*
inline static void METHOD_DrawTiledPixmap(t_integer X, t_integer Y, t_integer Width, t_integer Height, _pixmap *PixmapObject)
{
  EXTERN_myQPainter->drawTiledPixmap(X, Y, Width, Height, (const QPixmap &) PixmapObject);
}
    */
inline static void METHOD_DrawPoint(t_integer X, t_integer Y)
{
  EXTERN_myQPainter->drawPoint(X, Y);
}

inline static void METHOD_DrawRect(t_integer X, t_integer Y, t_integer Width, t_integer Height)
{
  EXTERN_myQPainter->drawRect(X, Y, Width, Height);
}

inline static void METHOD_DrawRoundRect(t_integer X, t_integer Y, t_integer Width, t_integer Height, t_integer XRnd, t_integer YRnd)
{
  EXTERN_myQPainter->drawRoundRect(X, Y, Width, Height, XRnd, YRnd);
}

inline static void METHOD_DrawText(t_integer X, t_integer Y, const QString & Text)
{
  EXTERN_myQPainter->drawText(X, Y, Text);
}

inline static void METHOD_DrawFramedText(t_integer X, t_integer Y, t_boolean bBlack, const QString & Text)
{
  QPen p = EXTERN_myQPainter->pen();
  EXTERN_myQPainter->setPen(bBlack ? Qt::black : Qt::white);

  EXTERN_myQPainter->drawText(X, Y, Text);
  EXTERN_myQPainter->drawText(X, Y + 1, Text);
  EXTERN_myQPainter->drawText(X, Y + 2, Text);
  EXTERN_myQPainter->drawText(X + 1, Y, Text);
  EXTERN_myQPainter->drawText(X + 1, Y + 1, Text);
  EXTERN_myQPainter->drawText(X + 1, Y + 2, Text);
  EXTERN_myQPainter->drawText(X + 2, Y, Text);
  EXTERN_myQPainter->drawText(X + 2, Y + 1, Text);
  EXTERN_myQPainter->drawText(X + 2, Y + 2, Text);

  EXTERN_myQPainter->setPen(p);
  EXTERN_myQPainter->drawText(X + 1, Y + 1, Text);
}


inline static void METHOD_DrawShadowText(t_integer X, t_integer Y, t_boolean bBlack, const QString & Text)
{
  QPen p = EXTERN_myQPainter->pen();
  EXTERN_myQPainter->setPen(bBlack ? Qt::black : Qt::white);

  EXTERN_myQPainter->drawText(X + 1, Y + 1, Text);
  EXTERN_myQPainter->drawText(X + 1, Y + 2, Text);
  EXTERN_myQPainter->drawText(X + 2, Y + 1, Text);
  EXTERN_myQPainter->drawText(X + 2, Y + 2, Text);

  EXTERN_myQPainter->setPen(p);
  EXTERN_myQPainter->drawText(X + 1, Y + 1, Text);
}

inline static void METHOD_DrawTextRect(t_integer X, t_integer Y, t_integer Width, t_integer Height, const QString & Text)
{
  EXTERN_myQPainter->drawText(X, Y, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
}

inline static void METHOD_DrawFramedTextRect(t_integer X, t_integer Y, t_integer Width, t_integer Height, t_boolean bBlack, const QString & Text)
{
  QPen p = EXTERN_myQPainter->pen();
  EXTERN_myQPainter->setPen(bBlack ? Qt::black : Qt::white);

  EXTERN_myQPainter->drawText(X, Y, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X, Y + 1, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X, Y + 2, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X + 1, Y, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X + 1, Y + 1, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X + 1, Y + 2, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X + 2, Y, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X + 2, Y + 1, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X + 2, Y + 2, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);

  EXTERN_myQPainter->setPen(p);
  EXTERN_myQPainter->drawText(X + 1, Y + 1, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
}

inline static void METHOD_DrawShadowTextRect(t_integer X, t_integer Y, t_integer Width, t_integer Height, t_boolean bBlack, const QString & Text)
{
  QPen p = EXTERN_myQPainter->pen();
  EXTERN_myQPainter->setPen(bBlack ? Qt::black : Qt::white);
  
  EXTERN_myQPainter->drawText(X + 1, Y + 1, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X + 1, Y + 2, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X + 2, Y + 1, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
  EXTERN_myQPainter->drawText(X + 2, Y + 2, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);

  EXTERN_myQPainter->setPen(p);
  EXTERN_myQPainter->drawText(X + 1, Y + 1, Width, Height, Qt::TextWordWrap | Qt::TextShowMnemonic | (qApp->isRightToLeft() ? Qt::AlignRight : Qt::AlignLeft), Text);
}

inline static void METHOD_SetFont(const QString & FontId)
{
  if (!fonts_map.contains(FontId)) return;
  EXTERN_myQPainter->setFont(fonts_map[FontId]);
}

/*
inline static void METHOD_SetFont(_font *FontObject)
{
  QFont f;
  f.setFamily(FontObject->family());
  f.setBold(FontObject->bold());
  f.setItalic(FontObject->italic());
  f.setUnderline(FontObject->underline());
  f.setPointSize(FontObject->pointSize());

  EXTERN_myQPainter->setFont(f);
}
*/

inline static void METHOD_SetPen(const QString & ColorId)
{
  if (!colors_map.contains(ColorId)) return;
  EXTERN_myQPainter->setPen(colors_map[ColorId]);
}

inline static void METHOD_SetPen(const QString & ColorId, t_integer Size, t_long PenStyle, t_long PenCapStyle, t_long PenJoinStyle)
{
  if (!colors_map.contains(ColorId)) return;
  EXTERN_myQPainter->setPen(QPen(QBrush(colors_map[ColorId]), Size, (Qt::PenStyle) PenStyle, (Qt::PenCapStyle) PenCapStyle, (Qt::PenJoinStyle) PenJoinStyle));
}


inline static void METHOD_SetPen(_color *ColorObject)
{
  if ((t_integer) ColorObject < 100){    
    EXTERN_myQPainter->setPen((Qt::GlobalColor) (t_integer) ColorObject);
  } else {
    QColor c; c.setRgba(ColorObject->rgba());
    EXTERN_myQPainter->setPen(c);
  }
 
}



inline static void METHOD_SetPen(_color *ColorObject, t_integer Size, t_long PenStyle, t_long PenCapStyle, t_long PenJoinStyle)
{
  if ((t_integer) ColorObject < 100){    
    EXTERN_myQPainter->setPen(QPen(QBrush((Qt::GlobalColor) (t_integer) ColorObject), Size, (Qt::PenStyle) PenStyle, (Qt::PenCapStyle) PenCapStyle, (Qt::PenJoinStyle) PenJoinStyle));
  } else {
    QColor c; c.setRgba(ColorObject->rgba());
    EXTERN_myQPainter->setPen(QPen(QBrush(c), Size, (Qt::PenStyle) PenStyle, (Qt::PenCapStyle) PenCapStyle, (Qt::PenJoinStyle) PenJoinStyle));
  }

 // if ((t_integer) ColorObject < 100){ // Qt defined default colors
  //  EXTERN_myQPainter->setPen(QPen(QBrush(*ColorObject), Size, (Qt::PenStyle) PenStyle, (Qt::PenCapStyle) PenCapStyle, (Qt::PenJoinStyle) PenJoinStyle));
 // } else {
   // QColor c; c.setRgba(ColorObject->rgba());
    //EXTERN_myQPainter->setPen(QPen(QBrush(*ColorObject), Size, (Qt::PenStyle) PenStyle, (Qt::PenCapStyle) PenCapStyle, (Qt::PenJoinStyle) PenJoinStyle));
 // }
  
}

/*
inline static void METHOD_SetPenPixmap(_pixmap *PixmapObject)
{
//  EXTERN_myQPainter->setPen(QBrush((const QPixmap &) PixmapObject));
}
*/

inline static void METHOD_SetPenPixmap(const QString & PixmapId)
{
  QPixmap & p = pixmaps_map[PixmapId];
  if (p.isNull()) return;
  EXTERN_myQPainter->setPen(QPen(QBrush(p), p.width()));
}

inline static void METHOD_SetBrush(const QString & ColorId)
{
  if (!colors_map.contains(ColorId)) return;
  EXTERN_myQPainter->setBrush(colors_map[ColorId]);
}

inline static void METHOD_SetBrush(const QString & ColorId, t_long BrushStyle)
{
  if (!colors_map.contains(ColorId)) return;
  EXTERN_myQPainter->setBrush(QBrush(colors_map[ColorId], (Qt::BrushStyle) BrushStyle));
}


inline static void METHOD_SetBrush(_color *ColorObject)
{
  
  if ((t_integer) ColorObject < 100){    
    EXTERN_myQPainter->setBrush((Qt::GlobalColor) (t_integer) ColorObject);
  } else {
    QColor c; c.setRgba(ColorObject->rgba());
    EXTERN_myQPainter->setBrush(c);
  }

}


inline static void METHOD_SetBrush(_color *ColorObject, t_long BrushStyle)
{

  if ((t_integer) ColorObject < 100){   
    EXTERN_myQPainter->setBrush(QBrush((Qt::GlobalColor) (t_integer) ColorObject, (Qt::BrushStyle) BrushStyle));
  } else {
    QColor c; c.setRgba(ColorObject->rgba());
    EXTERN_myQPainter->setBrush(QBrush(c, (Qt::BrushStyle) BrushStyle));
  }


  
  //QColor c; c.setRgba(ColorObject->rgba());
 // EXTERN_myQPainter->setBrush(QBrush(c, (Qt::BrushStyle) BrushStyle));
  
  //EXTERN_myQPainter->setBrush(QBrush(*ColorObject, (Qt::BrushStyle) BrushStyle));

}
/*
inline static void METHOD_SetBrushPixmap(_pixmap *PixmapObject)
{
  EXTERN_myQPainter->setBrush(QBrush((const QPixmap &) PixmapObject));
}
*/
inline static void METHOD_SetBrushPixmap(const QString & PixmapId)
{
  QPixmap & p = pixmaps_map[PixmapId];
  if (p.isNull()) return;
  EXTERN_myQPainter->setBrush(QBrush(p));
}

inline static void METHOD_SetOpacity(t_double d)
{
  EXTERN_myQPainter->setOpacity(d);
}

inline static void METHOD_SetBackgroundFilled(t_boolean b)
{
  EXTERN_myQPainter->setBackgroundMode(b ? Qt::OpaqueMode : Qt::TransparentMode);
}

inline static void METHOD_SetBackground(const QString & ColorId)
{
  if (!colors_map.contains(ColorId)) return;
  EXTERN_myQPainter->setBackgroundMode(Qt::OpaqueMode);
  EXTERN_myQPainter->setBackground(QBrush(colors_map[ColorId]));
}


inline static void METHOD_SetBackground(_color *ColorObject)
{

  if ((t_integer) ColorObject < 100){   
    EXTERN_myQPainter->setBackground(QBrush((Qt::GlobalColor) (t_integer) ColorObject));
  } else {
    QColor c; c.setRgba(ColorObject->rgba());
    EXTERN_myQPainter->setBackground(QBrush(c));    
  }

  //EXTERN_myQPainter->setBackground(QBrush(*ColorObject));
  
  //QColor c; c.setRgba(ColorObject->rgba());
  //EXTERN_myQPainter->setBackground(QBrush(c));
  
}
/*
inline static void METHOD_SetBackgroundPixmap(_pixmap *PixmapObject)
{
  EXTERN_myQPainter->setBackground(QBrush((const QPixmap &) PixmapObject));
}
*/

inline static void METHOD_SetBackgroundPixmap(const QString & PixmapId)
{
  QPixmap & p = pixmaps_map[PixmapId];
  if (p.isNull()) return;
  EXTERN_myQPainter->setBackground(QBrush(p));
}

inline static void METHOD_FillRect(t_integer X, t_integer Y, t_integer Width, t_integer Height, const QString & ColorId)
{
  if (!colors_map.contains(ColorId)) return;
  EXTERN_myQPainter->fillRect(X, Y, Width, Height, colors_map[ColorId]);
}

inline static void METHOD_FillRect(t_integer X, t_integer Y, t_integer Width, t_integer Height, _color *ColorObject)
{
  
  //QColor c; c.setRgba(ColorObject->rgba());
  //EXTERN_myQPainter->fillRect(X, Y, Width, Height, c);


  if ((t_integer) ColorObject < 100){   
    EXTERN_myQPainter->fillRect(X, Y, Width, Height, (Qt::GlobalColor) (t_integer) ColorObject);
  } else {
    QColor c; c.setRgba(ColorObject->rgba());
    EXTERN_myQPainter->fillRect(X, Y, Width, Height, c);
  }

  //EXTERN_myQPainter->fillRect(X, Y, Width, Height, *ColorObject);
}

inline static void METHOD_FillRectPixmap(t_integer X, t_integer Y, t_integer Width, t_integer Height, const QString & PixmapId)
{
  QPixmap & p = pixmaps_map[PixmapId];
  if (p.isNull()) return;
  EXTERN_myQPainter->fillRect(X, Y, Width, Height, QBrush(p));
}

/*
inline static void METHOD_FillRectPixmap(t_integer X, t_integer Y, t_integer Width, t_integer Height, _pixmap *PixmapObject)
{
  EXTERN_myQPainter->fillRect(X, Y, Width, Height, QBrush((const QPixmap &) PixmapObject));
}
*/
inline static void METHOD_SetLayoutDirection(t_boolean b)
{
  EXTERN_myQPainter->setLayoutDirection(b ? Qt::RightToLeft : Qt::LeftToRight);
}

inline static t_long GETPROPERTY_NoBrush()
{
  return Qt::NoBrush;
}

inline static t_long GETPROPERTY_SolidPattern()
{
  return Qt::SolidPattern;
}

inline static t_long GETPROPERTY_Dense1Pattern()
{
  return Qt::Dense1Pattern;
}

inline static t_long GETPROPERTY_Dense2Pattern()
{
  return Qt::Dense2Pattern;
}

inline static t_long GETPROPERTY_Dense3Pattern()
{
  return Qt::Dense3Pattern;
}

inline static t_long GETPROPERTY_Dense4Pattern()
{
  return Qt::Dense4Pattern;
}

inline static t_long GETPROPERTY_Dense5Pattern()
{
  return Qt::Dense5Pattern;
}

inline static t_long GETPROPERTY_Dense6Pattern()
{
  return Qt::Dense6Pattern;
}

inline static t_long GETPROPERTY_Dense7Pattern()
{
  return Qt::Dense7Pattern;
}

inline static t_long GETPROPERTY_HorPattern()
{
  return Qt::HorPattern;
}

inline static t_long GETPROPERTY_VerPattern()
{
  return Qt::VerPattern;
}

inline static t_long GETPROPERTY_CrossPattern()
{
  return Qt::CrossPattern;
}

inline static t_long GETPROPERTY_BDiagPattern()
{
  return Qt::BDiagPattern;
}

inline static t_long GETPROPERTY_FDiagPattern()
{
  return Qt::FDiagPattern;
}

inline static t_long GETPROPERTY_DiagCrossPattern()
{
  return Qt::DiagCrossPattern;
}

inline static t_long GETPROPERTY_LinearGradientPattern()
{
  return Qt::LinearGradientPattern;
}

inline static t_long GETPROPERTY_ConicalGradientPattern()
{
  return Qt::ConicalGradientPattern;
}
 
inline static t_long GETPROPERTY_RadialGradientPattern()
{
  return Qt::RadialGradientPattern;
}

inline static t_long GETPROPERTY_TexturePattern()
{
  return Qt::TexturePattern;
}

inline static t_long GETPROPERTY_NoPen()
{
  return Qt::NoPen;
}

inline static t_long GETPROPERTY_SolidLine()
{
  return Qt::SolidLine;
}

inline static t_long GETPROPERTY_DashLine()
{
  return Qt::DashLine;
}

inline static t_long GETPROPERTY_DotLine()
{
  return Qt::DotLine;
}

inline static t_long GETPROPERTY_DashDotLine()
{
  return Qt::DashDotLine;
}

inline static t_long GETPROPERTY_DashDotDotLine()
{
  return Qt::DashDotDotLine;
}

inline static t_long GETPROPERTY_CustomDashLine()
{
  return Qt::CustomDashLine;
}

inline static t_long GETPROPERTY_FlatCap()
{
  return Qt::FlatCap;
}

inline static t_long GETPROPERTY_SquareCap()
{
  return Qt::SquareCap;
}

inline static t_long GETPROPERTY_RoundCap()
{
  return Qt::RoundCap;
}

inline static t_long GETPROPERTY_MiterJoin()
{
  return Qt::MiterJoin;
}

inline static t_long GETPROPERTY_BevelJoin()
{
  return Qt::BevelJoin;
}

inline static t_long GETPROPERTY_RoundJoin()
{
  return Qt::RoundJoin;
}

inline static t_long GETPROPERTY_SvgMiterJoin()
{
  return Qt::SvgMiterJoin;
}


#endif
};

#endif
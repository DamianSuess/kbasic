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

#include "_previewreport.h"
#include "_form.h"

#include <QAbstractScrollArea>
#include <QPrintDialog>
#include <QPrinter>
#include <QToolBar>
#include <QAction>
#include <QTextFormat>
#include <QMouseEvent>
#include <QTextFrame>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QScrollBar>
#include <QPainter>
#include <QDebug>
#include <QPageSetupDialog>
#include <QStatusBar>

extern QString idePath(QString s);

extern bool bStopDrawing;

static inline int inchesToPixels(float inches, QPaintDevice *device)
{
    return qRound(inches * device->logicalDpiY());
}

static inline qreal mmToInches(double mm)
{
    return mm * 0.039370147;
}

class _view : public QAbstractScrollArea
{
    Q_OBJECT
public:
    _view(_form *f);

    inline void updateLayout() { resizeEvent(0); viewport()->update(); }

public slots:
    void zoomIn();
    void zoom100();
    void zoomOut();

protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);

private:
    void paintPage(QPainter *painter, int page);
    _form *my_form;
    qreal scale;
    int interPageSpacing;
    QPoint mousePressPos;
    QPoint scrollBarValuesOnMousePress;
};

_view::_view(_form *f)
{
    verticalScrollBar()->setSingleStep(20);
    horizontalScrollBar()->setSingleStep(20);
    setCursor(Qt::OpenHandCursor);

    viewport()->setBackgroundRole(QPalette::Dark);

    my_form = f;
    scale = 0.5;
    interPageSpacing = 30;
}

void _view::zoomIn()
{
    if (scale <= 1.6) scale += 0.2;
    resizeEvent(0);
    viewport()->update();
}

void _view::zoom100()
{
    scale = 1.0;
    resizeEvent(0);
    viewport()->update();
}

void _view::zoomOut()
{
    if (scale >= 0.4) scale -= 0.2;
    resizeEvent(0);
    viewport()->update();
}

void _view::paintEvent(QPaintEvent *)
{
    if (bStopDrawing) return;

    QPainter p(viewport());

    p.translate(-horizontalScrollBar()->value(), -verticalScrollBar()->value());
    p.translate(interPageSpacing, interPageSpacing);

    const int pages = my_form->REPORT_pageCount();
    for (int i = 0; i < pages && bStopDrawing == false; ++i) 
    {
        p.save();
        p.scale(scale, scale);

        paintPage(&p, i);

        p.restore();
        p.translate(0, interPageSpacing + my_form->REPORT_pageSize().height() * scale);
    }

    bStopDrawing = bStopDrawing;

}

void _view::paintPage(QPainter *painter, int page)
{
    const QSizeF pgSize = my_form->REPORT_pageSize();

    QColor col(Qt::black);

    painter->setPen(col);
    painter->setBrush(Qt::white);
    painter->drawRect(QRectF(QPointF(0, 0), pgSize));
    painter->setBrush(Qt::NoBrush);

    col = col.light();
    painter->drawLine(QLineF(pgSize.width(), 1, pgSize.width(), pgSize.height() - 1));

    col = col.light();
    painter->drawLine(QLineF(pgSize.width(), 2, pgSize.width(), pgSize.height() - 2));

    QRectF docRect(QPointF(0, page * pgSize.height()), pgSize);
   // QAbstractTextDocumentLayout::PaintContext ctx;
    //ctx.clip = docRect;

    // don't use the system palette text as default text color, on HP/UX
    // for example that's white, and white text on white paper doesn't
    // look that nice
    //ctx.palette.setColor(QPalette::Text, Qt::black);

    painter->translate(0, - page * pgSize.height());
    painter->setClipRect(docRect);
    my_form->REPORT_draw(painter, page);
    //doc->documentLayout()->draw(painter, ctx);
}

void _view::resizeEvent(QResizeEvent *)
{
    const QSize viewportSize = viewport()->size();

    QSize docSize;
    docSize.setWidth(qRound(my_form->REPORT_pageSize().width() * scale + 2 * interPageSpacing));
    const int pageCount = my_form->REPORT_pageCount();
    docSize.setHeight(qRound(pageCount * my_form->REPORT_pageSize().height() * scale + (pageCount + 1) * interPageSpacing));

    horizontalScrollBar()->setRange(0, my_form->REPORT_docSize().width() * scale - viewportSize.width());
    horizontalScrollBar()->setPageStep(viewportSize.width());

    verticalScrollBar()->setRange(0, my_form->REPORT_docSize().height() * scale - viewportSize.height());
    verticalScrollBar()->setPageStep(viewportSize.height());
}

void _view::mousePressEvent(QMouseEvent *e)
{
    mousePressPos = e->pos();
    scrollBarValuesOnMousePress.rx() = horizontalScrollBar()->value();
    scrollBarValuesOnMousePress.ry() = verticalScrollBar()->value();
    e->accept();
    setCursor(Qt::ClosedHandCursor);
}

void _view::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressPos.isNull()) {
        e->ignore();
        return;
    }

    horizontalScrollBar()->setValue(scrollBarValuesOnMousePress.x() - e->pos().x() + mousePressPos.x());
    verticalScrollBar()->setValue(scrollBarValuesOnMousePress.y() - e->pos().y() + mousePressPos.y());
    horizontalScrollBar()->update();
    verticalScrollBar()->update();
    e->accept();
}

void _view::mouseReleaseEvent(QMouseEvent *e)
{
    mousePressPos = QPoint();
    e->accept();
    setCursor(Qt::OpenHandCursor);    
}

_previewreport::_previewreport(_form *f/*const QTextDocument *document*/, QWidget *parent, bool _bPreview, bool _bPrint, bool _bPrintDialog)
    : QMainWindow(parent), printer(/*QPrinter::HighResolution*/)
{
    setWindowTitle(tr("Preview Report"));

    bPreview = _bPreview;
    bPrint = _bPrint;
    bPrintDialog = _bPrintDialog;    

    my_form = f;

//    printer.setFullPage(true);
    //doc = document->clone();

    view = new _view(my_form);
    setCentralWidget(view);
    resize(800, 600);

     setup();

    //doc->setUseDesignMetrics(true);
    //doc->documentLayout()->setPaintDevice(view->viewport());
/*
    // add a nice 2 cm margin
    const qreal margin = inchesToPixels(mmToInches(20), this);
    QTextFrameFormat fmt = doc->rootFrame()->frameFormat();
    fmt.setMargin(margin);
    //doc->rootFrame()->setFrameFormat(fmt);
*/
   

    /*
    QFont f(doc->defaultFont());
    f.setPointSize(10);
    doc->setDefaultFont(f);
*/
    QToolBar *tb = addToolBar(tr("Print"));
    tb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QAction *a;
#ifdef IDE
    a = new QAction(QIcon(idePath("FILE_PRINT.png")), tr("&Print..."), this);
#else
    a = new QAction(QIcon(interpreter_loadPixmap("FILE_PRINT.png")), tr("&Print..."), this);
#endif
    a->setShortcut(Qt::CTRL + Qt::Key_P);
    connect(a, SIGNAL(triggered()), this, SLOT(print()));
    tb->addAction(a);
/*
    a = new QAction(QIcon(idePath("VIEW_OPTIONS.png")), tr("Page Setup..."), this);
#ifdef IDE
#else
#endif
    connect(a, SIGNAL(triggered()), this, SLOT(pageSetup()));
    tb->addAction(a);
*/
    tb->addSeparator();

#ifdef IDE
    a = new QAction(QIcon(idePath("VIEW_ZOOMIN.png")), tr("Zoom In"), this);
#else
    a = new QAction(QIcon(interpreter_loadPixmap("VIEW_ZOOMIN.png")), tr("Zoom In"), this);
#endif
    connect(a, SIGNAL(triggered()), view, SLOT(zoomIn()));
    tb->addAction(a);

#ifdef IDE
    a = new QAction(QIcon(idePath("VIEW_ZOOMOUT.png")), tr("Zoom Out"), this);
#else
    a = new QAction(QIcon(interpreter_loadPixmap("VIEW_ZOOMOUT.png")), tr("Zoom Out"), this);
#endif
    connect(a, SIGNAL(triggered()), view, SLOT(zoomOut()));
    tb->addAction(a);

#ifdef IDE
    a = new QAction(QIcon(idePath("VIEW_ZOOM100.png")), tr("Zoom 100%"), this);
#else
    a = new QAction(QIcon(interpreter_loadPixmap("VIEW_ZOOM100.png")), tr("Zoom 100%"), this);
#endif
    connect(a, SIGNAL(triggered()), view, SLOT(zoom100()));
    tb->addAction(a);

    tb->addSeparator();

#ifdef IDE
    a = new QAction(QIcon(idePath("VIEW_CLOSE.png")), tr("&Close"), this);
#else
    a = new QAction(QIcon(interpreter_loadPixmap("VIEW_CLOSE.png")), tr("Zoom Close"), this);
#endif
    connect(a, SIGNAL(triggered()), this, SLOT(close()));
    tb->addAction(a);

    statusBar()->setSizeGripEnabled(true);

    if (bPrintDialog) print();
}

void _previewreport::setup()
{
    QSizeF page = printer.pageRect().size();
    page.setWidth(page.width() * view->logicalDpiX() / printer.logicalDpiX());
    page.setHeight(page.height() * view->logicalDpiY() / printer.logicalDpiY());

    // add a nice 2 cm margin
    //const qreal margin = 0;//inchesToPixels(mmToInches(20), this);

    //QTextFrameFormat fmt = doc->rootFrame()->frameFormat();
    //fmt.setMargin(margin);
    //doc->rootFrame()->setFrameFormat(fmt);

   // my_form->REPORT_setMargin(margin);
    my_form->REPORT_setPageSize(page);
}

_previewreport::~_previewreport()
{
//    delete doc;
}

void _previewreport::print()
{
  QPrintDialog *dlg = new QPrintDialog(&printer, bPrintDialog ? this : 0);
    if (dlg->exec() == QDialog::Accepted){
       //QSizeF page = printer.pageRect().size();
        //my_form->REPORT_setPageSize(page);
        setup();
         view->updateLayout();
        my_form->REPORT_print(&printer);
    }
    delete dlg;
}

void _previewreport::pageSetup()
{
    QPageSetupDialog dlg(&printer, this);
    if (dlg.exec() == QDialog::Accepted) {
        setup();
        view->updateLayout();
    }
}

#include "_previewreport.moc"

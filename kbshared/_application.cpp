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


#include "../kbshared/_application.h"

#ifdef RUN
#include <QHttp>

#include <QSvgRenderer>

#include "_sounds.h"
#include "_movie.h"

extern int nCurrentFormId;
extern QMap<QString,int>forms2;

extern QString sQtException;   

#include <phonon/backendcapabilities.h>

#include "../kbasic_binding/_application/kb_application.h"
#include "../kbasic_binding/_mainwindow/kb_mainwindow.h"

#include "../kbrun/interpreter.h"
#include "../kbasic_binding/_form/kb_form.h"


QMap<QString,QString>trs;


extern QString sCurrentLanguage;

extern QLocale *qlocale;

extern QAction *aWindow;
extern QAction *aHelp;
extern QAction *aRecords;
extern QAction *aContents;
extern QAction *aAbout;

extern QAction *aCloseAct;
extern QAction *aCloseAllAct;
extern QAction *aTileAct;
extern QAction *aCascadeAct;
extern QAction *aNextAct;
extern QAction *aPreviousAct;
extern QAction *aSeparatorAct;


extern QAction *aAddFilter;
extern QAction *aAddNotFilter;

extern QAction *aSetFilter;
extern QAction *aSetNotFilter;

extern QAction *aClearFilter;
extern QAction *aSortAscending;

extern QAction *aSortDescending;
extern QAction *aSeek;

extern QAction *aRequery;
extern QAction *aAddNew;
extern QAction *aUpdate;
extern QAction *aDelete;

extern QAction *aCut;
extern QAction *aCopy;
extern QAction *aPaste;


extern _forms *my_forms;

extern QString sTranslation;

extern const QString interpreter_loadFileAsString(QString fn);

extern QMainWindow *forms_mainwindow;
extern interpreter *EXTERN_myInterpreter;
extern bool bNotApplicationRun;
extern QMdiArea *forms_workspace;

extern QMap<QString,QString>openonrun_forms;

extern QMap<QString,t_integer> projectfiles2;

extern bool bOpenonrun_forms;


/*
void _application::EVENT_Application_OnOpen()
{
  kb_application::EVENT_Application_OnOpen();
}

void _application::EVENT_Application_OnClose2(bool *Cancel)
{
  bool b = false;
  kb_application::EVENT_Application_OnClose(&b);
  if (b) b = b;
}

void _application::EVENT_Application_OnClose(bool *Cancel)
{
}*/

int nEVENT_Actions_OnAction = 0;
int nEVENT_Forms_OnFormGotFocus = 0;

int nEVENT_MenuBar_OnEvent = 0;
int nEVENT_MenuBar_OnHovered = 0;
int nEVENT_MenuBar_OnAboutToShow = 0;
int nEVENT_MenuBar_OnAboutToHide = 0;
int nEVENT_ToolBar_OnEvent = 0;
int nEVENT_SystemTray_OnEvent = 0;

void _application::METHOD_SetWaitCursor()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
}

void _application::METHOD_UnsetWaitCursor()
{
  QApplication::restoreOverrideCursor();
}

void _application::EVENT_Forms_OnFormGotFocus(QString FormName)
{
  kb_application::EVENT_Forms_OnFormGotFocus(FormName);
}

void _application::EVENT_Actions_OnAction(QString ActionId)
{
  kb_application::EVENT_Actions_OnAction(ActionId);
}

void _application::EVENT_MenuBar_OnEvent(QString MenuBarItemName)
{
  kb_application::EVENT_MenuBar_OnEvent(MenuBarItemName);
}

void _application::EVENT_MenuBar_OnHovered(QString MenuBarItemName)
{
  kb_application::EVENT_MenuBar_OnHovered(MenuBarItemName);
}

void _application::EVENT_MenuBar_OnAboutToShow(QString MenuBarItemName)
{
  kb_application::EVENT_MenuBar_OnAboutToShow(MenuBarItemName);
}

void _application::EVENT_MenuBar_OnAboutToHide(QString MenuBarItemName)
{
  kb_application::EVENT_MenuBar_OnAboutToHide(MenuBarItemName);
}

void _application::EVENT_ToolBar_OnEvent(QString MenuBarItemName)
{
  kb_application::EVENT_ToolBar_OnEvent(MenuBarItemName);
}


QString _application::METHOD_ArgumentsAsString()
{  
  static QString s; s = "";
  bool b = false;
  foreach(QString ss, qApp->arguments())
  {
    if (b) s += " ";
    b = true;
    s += ss;
  }

  return "";
}

void _application::METHOD_PrintHtml(QString Html)
{  
  QTextDocument *document = new QTextDocument();
  document->setHtml(Html);
  QPrinter printer;
  QPrintDialog *dialog = new QPrintDialog(&printer, qApp->activeWindow());
  if (dialog->exec() != QDialog::Accepted)
     return;
  document->print(&printer);
  delete document;     
}

void _application::METHOD_PrintHtmlAsPdf(QString Html, QString FileName)
{  
  QTextDocument *document = new QTextDocument();
  document->setHtml(Html);
  QPrinter printer;
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOutputFileName(FileName);

  QPrintDialog *dialog = new QPrintDialog(&printer, qApp->activeWindow());
  if (dialog->exec() != QDialog::Accepted)
     return;
  document->print(&printer);
  delete document;     
}

QString _application::METHOD_StandardIcon(QString Name)
{  
  QPixmap p;

  if (Name.contains("TitleBarMinButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_TitleBarMinButton);
  } else if (Name.contains("TitleBarMenuButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_TitleBarMenuButton);
  } else if (Name.contains("TitleBarMaxButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
  } else if (Name.contains("TitleBarCloseButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
  } else if (Name.contains("TitleBarNormalButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
  } else if (Name.contains("TitleBarShadeButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_TitleBarShadeButton);
  } else if (Name.contains("TitleBarUnshadeButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_TitleBarUnshadeButton);
  } else if (Name.contains("TitleBarContextHelpButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_TitleBarContextHelpButton);
  } else if (Name.contains("MessageBoxInformation", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MessageBoxInformation);
  } else if (Name.contains("MessageBoxWarning", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MessageBoxWarning);
  } else if (Name.contains("MessageBoxCritical", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MessageBoxCritical);
  } else if (Name.contains("MessageBoxQuestion", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MessageBoxQuestion);
  } else if (Name.contains("DesktopIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DesktopIcon);
  } else if (Name.contains("TrashIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_TrashIcon);
  } else if (Name.contains("ComputerIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_ComputerIcon);
  } else if (Name.contains("DriveFDIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DriveFDIcon);
  } else if (Name.contains("DriveFDIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DriveFDIcon);
  } else if (Name.contains("DriveHDIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DriveHDIcon);
  } else if (Name.contains("DriveCDIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DriveCDIcon);
  } else if (Name.contains("DriveDVDIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DriveDVDIcon);
  } else if (Name.contains("DriveNetIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DriveNetIcon);
  } else if (Name.contains("DirHomeIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DirHomeIcon);
  } else if (Name.contains("DirOpenIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DirOpenIcon);
  } else if (Name.contains("DirClosedIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DirClosedIcon);
  } else if (Name.contains("DirIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DirIcon);
  } else if (Name.contains("DirLinkIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DirLinkIcon);
  } else if (Name.contains("FileIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileIcon);
  } else if (Name.contains("FileLinkIcon", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileLinkIcon);
  } else if (Name.contains("FileDialogStart", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileDialogStart);
  } else if (Name.contains("FileDialogEnd", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileDialogEnd);
  } else if (Name.contains("FileDialogToParent", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileDialogToParent);
  } else if (Name.contains("FileDialogNewFolder", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileDialogNewFolder);
  } else if (Name.contains("FileDialogDetailedView", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileDialogDetailedView);
  } else if (Name.contains("FileDialogInfoView", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileDialogInfoView);
  } else if (Name.contains("FileDialogContentsView", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileDialogContentsView);
  } else if (Name.contains("FileDialogListView", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileDialogListView);
  } else if (Name.contains("FileDialogBack", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_FileDialogBack);
  } else if (Name.contains("DockWidgetCloseButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DockWidgetCloseButton);
  } else if (Name.contains("ToolBarHorizontalExtensionButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_ToolBarHorizontalExtensionButton);
  } else if (Name.contains("ToolBarVerticalExtensionButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_ToolBarVerticalExtensionButton);
  } else if (Name.contains("DialogOkButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogOkButton);
  } else if (Name.contains("DialogCancelButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogCancelButton);
  } else if (Name.contains("DialogHelpButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogHelpButton);
  } else if (Name.contains("DialogOpenButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogOpenButton);
  } else if (Name.contains("DialogSaveButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogSaveButton);
  } else if (Name.contains("DialogCloseButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogCloseButton);
  } else if (Name.contains("DialogApplyButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogApplyButton);
  } else if (Name.contains("DialogResetButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogResetButton);
  } else if (Name.contains("DialogDiscardButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogDiscardButton);
  } else if (Name.contains("DialogYesButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogYesButton);
  } else if (Name.contains("DialogNoButton", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_DialogNoButton);
  } else if (Name.contains("ArrowUp", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_ArrowUp);
  } else if (Name.contains("ArrowDown", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_ArrowDown);
  } else if (Name.contains("ArrowLeft", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_ArrowLeft);
  } else if (Name.contains("ArrowRight", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_ArrowRight);
  } else if (Name.contains("ArrowBack", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_ArrowBack);
  } else if (Name.contains("ArrowForward", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_ArrowForward);
  } else if (Name.contains("CommandLink", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_CommandLink);
  } else if (Name.contains("VistaShield", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_VistaShield);
  } else if (Name.contains("BrowserReload", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_BrowserReload);
  } else if (Name.contains("BrowserStop", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_BrowserStop);
  } else if (Name.contains("MediaPlay", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MediaPlay);
  } else if (Name.contains("MediaStop", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MediaStop);
  } else if (Name.contains("MediaPause", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MediaPause);
  } else if (Name.contains("MediaSkipForward", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MediaSkipForward);
  } else if (Name.contains("MediaSkipBackward", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MediaSkipBackward);
  } else if (Name.contains("MediaSeekForward", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MediaSeekForward);
  } else if (Name.contains("MediaSeekBackward", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MediaSeekBackward);
  } else if (Name.contains("MediaVolume", Qt::CaseInsensitive)){ p = qApp->style()->standardPixmap(QStyle::SP_MediaVolume);
  } else if (Name.contains("MediaVolumeMuted", Qt::CaseInsensitive) == 0){ p = qApp->style()->standardPixmap(QStyle::SP_MediaVolumeMuted);

  } else return "";

  QByteArray bytes;
  QBuffer buffer(&bytes);
  buffer.open(QIODevice::WriteOnly);
  p.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format

  static QString s;
  s = QString::fromLatin1((const char *) bytes.data(), bytes.size());
  return s;  
}

QString _application::METHOD_TakeScreenShot()
{  
  QPixmap p = QPixmap::grabWindow(QApplication::desktop()->winId());

  QByteArray bytes;
  QBuffer buffer(&bytes);
  buffer.open(QIODevice::WriteOnly);
  p.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format

  static QString s;
  s = QString::fromLatin1((const char *) bytes.data(), bytes.size());
  return s;  
}

_strings *_application::METHOD_Arguments()
{  
  _strings *ss = new _strings();

  foreach(QString s, qApp->arguments())
  {
    ss->METHOD_Append(s);
  }

  return ss;
}

t_boolean _application::METHOD_IsMimeTypeAvailable(QString k)
{  
  return Phonon::BackendCapabilities::isMimeTypeAvailable(k);
}

_strings *_application::METHOD_AvailableMimeTypes()
{  
  _strings *ss = new _strings();

  foreach(QString s, Phonon::BackendCapabilities::availableMimeTypes())
  {
    ss->METHOD_Append(s);
  }

  return ss;
}

_strings *_application::METHOD_AvailableLanguages()
{  
  _strings *ss = new _strings();

  QStringList l = sTranslation.split(";");

  foreach(QString s, l)
  {
    ss->METHOD_Append(s);
  }

  return ss;
}

void _application::METHOD_SetCountry(QString Country)
{   
  if (Country != sCurrentCountry){
    sCurrentCountry = Country;
    METHOD_SetLanguage(sCurrentLanguage);
  }
}

void _application::METHOD_SetLanguage(QString Language)
{     
  
  {
    sCurrentLanguage = Language;
    if (qlocale){
      if (*qlocale != QLocale::system() && *qlocale != QLocale::c()) delete qlocale;
      if (Language.isEmpty()){
        qlocale = &QLocale::system();
      } else {

        int n = 0;

        if (Language.compare("C", Qt::CaseInsensitive) == 0) n = QLocale::C;
        else if (Language.compare("Abkhazian", Qt::CaseInsensitive) == 0) n = QLocale::Abkhazian;
        else if (Language.compare("Afan", Qt::CaseInsensitive) == 0) n = QLocale::Afan;
        else if (Language.compare("Afar", Qt::CaseInsensitive) == 0) n = QLocale::Afar;
        else if (Language.compare("Afrikaans", Qt::CaseInsensitive) == 0) n = QLocale::Afrikaans;
        else if (Language.compare("Albanian", Qt::CaseInsensitive) == 0) n = QLocale::Albanian;
        else if (Language.compare("Amharic", Qt::CaseInsensitive) == 0) n = QLocale::Amharic;
        else if (Language.compare("Arabic", Qt::CaseInsensitive) == 0) n = QLocale::Arabic;
        else if (Language.compare("Armenian", Qt::CaseInsensitive) == 0) n = QLocale::Armenian;
        else if (Language.compare("Assamese", Qt::CaseInsensitive) == 0) n = QLocale::Assamese;
        else if (Language.compare("Aymara", Qt::CaseInsensitive) == 0) n = QLocale::Aymara;
        else if (Language.compare("Azerbaijani", Qt::CaseInsensitive) == 0) n = QLocale::Azerbaijani;
        else if (Language.compare("Bashkir", Qt::CaseInsensitive) == 0) n = QLocale::Bashkir;
        else if (Language.compare("Basque", Qt::CaseInsensitive) == 0) n = QLocale::Basque;
        else if (Language.compare("Bengali", Qt::CaseInsensitive) == 0) n = QLocale::Bengali;
        else if (Language.compare("Bhutani", Qt::CaseInsensitive) == 0) n = QLocale::Bhutani;
        else if (Language.compare("Bihari", Qt::CaseInsensitive) == 0) n = QLocale::Bihari;
        else if (Language.compare("Bislama", Qt::CaseInsensitive) == 0) n = QLocale::Bislama;
        else if (Language.compare("Bosnian", Qt::CaseInsensitive) == 0) n = QLocale::Bosnian;
        else if (Language.compare("Breton", Qt::CaseInsensitive) == 0) n = QLocale::Breton;
        else if (Language.compare("Bulgarian", Qt::CaseInsensitive) == 0) n = QLocale::Bulgarian;
        else if (Language.compare("Burmese", Qt::CaseInsensitive) == 0) n = QLocale::Burmese;
        else if (Language.compare("Byelorussian", Qt::CaseInsensitive) == 0) n = QLocale::Byelorussian;
        else if (Language.compare("Cambodian", Qt::CaseInsensitive) == 0) n = QLocale::Cambodian;
        else if (Language.compare("Catalan", Qt::CaseInsensitive) == 0) n = QLocale::Catalan;
        else if (Language.compare("Chinese", Qt::CaseInsensitive) == 0) n = QLocale::Chinese;
        else if (Language.compare("Cornish", Qt::CaseInsensitive) == 0) n = QLocale::Cornish;
        else if (Language.compare("Corsican", Qt::CaseInsensitive) == 0) n = QLocale::Corsican;
        else if (Language.compare("Croatian", Qt::CaseInsensitive) == 0) n = QLocale::Croatian;
        else if (Language.compare("Czech", Qt::CaseInsensitive) == 0) n = QLocale::Czech;
        else if (Language.compare("Danish", Qt::CaseInsensitive) == 0) n = QLocale::Danish;
        else if (Language.compare("Divehi", Qt::CaseInsensitive) == 0) n = QLocale::Divehi;
        else if (Language.compare("Dutch", Qt::CaseInsensitive) == 0) n = QLocale::Dutch;
        else if (Language.compare("English", Qt::CaseInsensitive) == 0) n = QLocale::English;
        else if (Language.compare("Esperanto", Qt::CaseInsensitive) == 0) n = QLocale::Esperanto;
        else if (Language.compare("Faroese", Qt::CaseInsensitive) == 0) n = QLocale::Faroese;
        else if (Language.compare("FijiLanguage", Qt::CaseInsensitive) == 0) n = QLocale::FijiLanguage;
        else if (Language.compare("Finnish", Qt::CaseInsensitive) == 0) n = QLocale::Finnish;
        else if (Language.compare("French", Qt::CaseInsensitive) == 0) n = QLocale::French;
        else if (Language.compare("Frisian", Qt::CaseInsensitive) == 0) n = QLocale::Frisian;
        else if (Language.compare("Gaelic", Qt::CaseInsensitive) == 0) n = QLocale::Gaelic;
        else if (Language.compare("Galician", Qt::CaseInsensitive) == 0) n = QLocale::Galician;
        else if (Language.compare("Georgian", Qt::CaseInsensitive) == 0) n = QLocale::Georgian;
        else if (Language.compare("German", Qt::CaseInsensitive) == 0) n = QLocale::German;
        else if (Language.compare("Greek", Qt::CaseInsensitive) == 0) n = QLocale::Greek;
        else if (Language.compare("Greenlandic", Qt::CaseInsensitive) == 0) n = QLocale::Greenlandic;
        else if (Language.compare("Guarani", Qt::CaseInsensitive) == 0) n = QLocale::Guarani;
        else if (Language.compare("Gujarati", Qt::CaseInsensitive) == 0) n = QLocale::Gujarati;
        else if (Language.compare("Hausa", Qt::CaseInsensitive) == 0) n = QLocale::Hausa;
        else if (Language.compare("Hebrew", Qt::CaseInsensitive) == 0) n = QLocale::Hebrew;
        else if (Language.compare("Hindi", Qt::CaseInsensitive) == 0) n = QLocale::Hindi;
        else if (Language.compare("Hungarian", Qt::CaseInsensitive) == 0) n = QLocale::Hungarian;
        else if (Language.compare("Icelandic", Qt::CaseInsensitive) == 0) n = QLocale::Icelandic;
        else if (Language.compare("Indonesian", Qt::CaseInsensitive) == 0) n = QLocale::Indonesian;
        else if (Language.compare("Interlingua", Qt::CaseInsensitive) == 0) n = QLocale::Interlingua;
        else if (Language.compare("Interlingue", Qt::CaseInsensitive) == 0) n = QLocale::Interlingue;
        else if (Language.compare("Inuktitut", Qt::CaseInsensitive) == 0) n = QLocale::Inuktitut;
        else if (Language.compare("Inupiak", Qt::CaseInsensitive) == 0) n = QLocale::Inupiak;
        else if (Language.compare("Irish", Qt::CaseInsensitive) == 0) n = QLocale::Irish;
        else if (Language.compare("Italian", Qt::CaseInsensitive) == 0) n = QLocale::Italian;
        else if (Language.compare("Japanese", Qt::CaseInsensitive) == 0) n = QLocale::Japanese;
        else if (Language.compare("Javanese", Qt::CaseInsensitive) == 0) n = QLocale::Javanese;
        else if (Language.compare("Kannada", Qt::CaseInsensitive) == 0) n = QLocale::Kannada;
        else if (Language.compare("Kashmiri", Qt::CaseInsensitive) == 0) n = QLocale::Kashmiri;
        else if (Language.compare("Kazakh", Qt::CaseInsensitive) == 0) n = QLocale::Kazakh;
        else if (Language.compare("Kinyarwanda", Qt::CaseInsensitive) == 0) n = QLocale::Kinyarwanda;
        else if (Language.compare("Kirghiz", Qt::CaseInsensitive) == 0) n = QLocale::Kirghiz;
        else if (Language.compare("Korean", Qt::CaseInsensitive) == 0) n = QLocale::Korean;
        else if (Language.compare("Kurdish", Qt::CaseInsensitive) == 0) n = QLocale::Kurdish;
        else if (Language.compare("Kurundi", Qt::CaseInsensitive) == 0) n = QLocale::Kurundi;
        else if (Language.compare("Laothian", Qt::CaseInsensitive) == 0) n = QLocale::Laothian;
        else if (Language.compare("Latin", Qt::CaseInsensitive) == 0) n = QLocale::Latin;
        else if (Language.compare("Latvian", Qt::CaseInsensitive) == 0) n = QLocale::Latvian;
        else if (Language.compare("Lingala", Qt::CaseInsensitive) == 0) n = QLocale::Lingala;
        else if (Language.compare("Lithuanian", Qt::CaseInsensitive) == 0) n = QLocale::Lithuanian;
        else if (Language.compare("Macedonian", Qt::CaseInsensitive) == 0) n = QLocale::Macedonian;
        else if (Language.compare("Malagasy", Qt::CaseInsensitive) == 0) n = QLocale::Malagasy;
        else if (Language.compare("Malay", Qt::CaseInsensitive) == 0) n = QLocale::Malay;
        else if (Language.compare("Malayalam", Qt::CaseInsensitive) == 0) n = QLocale::Malayalam;
        else if (Language.compare("Maltese", Qt::CaseInsensitive) == 0) n = QLocale::Maltese;
        else if (Language.compare("Manx", Qt::CaseInsensitive) == 0) n = QLocale::Manx;
        else if (Language.compare("Maori", Qt::CaseInsensitive) == 0) n = QLocale::Maori;
        else if (Language.compare("Marathi", Qt::CaseInsensitive) == 0) n = QLocale::Marathi;
        else if (Language.compare("Moldavian", Qt::CaseInsensitive) == 0) n = QLocale::Moldavian;
        else if (Language.compare("Mongolian", Qt::CaseInsensitive) == 0) n = QLocale::Mongolian;
        else if (Language.compare("NauruLanguage", Qt::CaseInsensitive) == 0) n = QLocale::NauruLanguage;
        else if (Language.compare("Nepali", Qt::CaseInsensitive) == 0) n = QLocale::Nepali;
        else if (Language.compare("Norwegian", Qt::CaseInsensitive) == 0) n = QLocale::Norwegian;
        else if (Language.compare("NorwegianBokmal", Qt::CaseInsensitive) == 0) n = QLocale::NorwegianBokmal;
        else if (Language.compare("Nynorsk", Qt::CaseInsensitive) == 0) n = QLocale::Nynorsk;
        else if (Language.compare("NorwegianNynorsk", Qt::CaseInsensitive) == 0) n = QLocale::NorwegianNynorsk;
        else if (Language.compare("Occitan", Qt::CaseInsensitive) == 0) n = QLocale::Occitan;
        else if (Language.compare("Oriya", Qt::CaseInsensitive) == 0) n = QLocale::Oriya;
        else if (Language.compare("Pashto", Qt::CaseInsensitive) == 0) n = QLocale::Pashto;
        else if (Language.compare("Persian", Qt::CaseInsensitive) == 0) n = QLocale::Persian;
        else if (Language.compare("Polish", Qt::CaseInsensitive) == 0) n = QLocale::Polish;
        else if (Language.compare("Portuguese", Qt::CaseInsensitive) == 0) n = QLocale::Portuguese;
        else if (Language.compare("Punjabi", Qt::CaseInsensitive) == 0) n = QLocale::Punjabi;
        else if (Language.compare("Quechua", Qt::CaseInsensitive) == 0) n = QLocale::Quechua;
        else if (Language.compare("RhaetoRomance", Qt::CaseInsensitive) == 0) n = QLocale::RhaetoRomance;
        else if (Language.compare("Romanian", Qt::CaseInsensitive) == 0) n = QLocale::Romanian;
        else if (Language.compare("Russian", Qt::CaseInsensitive) == 0) n = QLocale::Russian;
        else if (Language.compare("Samoan", Qt::CaseInsensitive) == 0) n = QLocale::Samoan;
        else if (Language.compare("Sangho", Qt::CaseInsensitive) == 0) n = QLocale::Sangho;
        else if (Language.compare("Sanskrit", Qt::CaseInsensitive) == 0) n = QLocale::Sanskrit;
        else if (Language.compare("Serbian", Qt::CaseInsensitive) == 0) n = QLocale::Serbian;
        else if (Language.compare("SerboCroatian", Qt::CaseInsensitive) == 0) n = QLocale::SerboCroatian;
        else if (Language.compare("Sesotho", Qt::CaseInsensitive) == 0) n = QLocale::Sesotho;
        else if (Language.compare("Setswana", Qt::CaseInsensitive) == 0) n = QLocale::Setswana;
        else if (Language.compare("Shona", Qt::CaseInsensitive) == 0) n = QLocale::Shona;
        else if (Language.compare("Sindhi", Qt::CaseInsensitive) == 0) n = QLocale::Sindhi;

        else if (Language.compare("Singhalese", Qt::CaseInsensitive) == 0) n = QLocale::Singhalese;
        else if (Language.compare("Siswati", Qt::CaseInsensitive) == 0) n = QLocale::Siswati;
        else if (Language.compare("Slovak", Qt::CaseInsensitive) == 0) n = QLocale::Slovak;
        else if (Language.compare("Slovenian", Qt::CaseInsensitive) == 0) n = QLocale::Slovenian;


        if (Language.compare("Somali", Qt::CaseInsensitive) == 0) n = QLocale::Somali;
        else if (Language.compare("Spanish", Qt::CaseInsensitive) == 0) n = QLocale::Spanish;
        else if (Language.compare("Sundanese", Qt::CaseInsensitive) == 0) n = QLocale::Sundanese;
        else if (Language.compare("Swahili", Qt::CaseInsensitive) == 0) n = QLocale::Swahili;

        else if (Language.compare("Swedish", Qt::CaseInsensitive) == 0) n = QLocale::Swedish;
        else if (Language.compare("Tagalog", Qt::CaseInsensitive) == 0) n = QLocale::Tagalog;
        else if (Language.compare("Tajik", Qt::CaseInsensitive) == 0) n = QLocale::Tajik;
        else if (Language.compare("Tamil", Qt::CaseInsensitive) == 0) n = QLocale::Tamil;

        else if (Language.compare("Tatar", Qt::CaseInsensitive) == 0) n = QLocale::Tatar;
        else if (Language.compare("Telugu", Qt::CaseInsensitive) == 0) n = QLocale::Telugu;
        else if (Language.compare("Thai", Qt::CaseInsensitive) == 0) n = QLocale::Thai;
        else if (Language.compare("Tibetan", Qt::CaseInsensitive) == 0) n = QLocale::Tibetan;

        else if (Language.compare("Tigrinya", Qt::CaseInsensitive) == 0) n = QLocale::Tigrinya;
        else if (Language.compare("TongaLanguage", Qt::CaseInsensitive) == 0) n = QLocale::TongaLanguage;
        else if (Language.compare("Tsonga", Qt::CaseInsensitive) == 0) n = QLocale::Tsonga;
        else if (Language.compare("Turkish", Qt::CaseInsensitive) == 0) n = QLocale::Turkish;

        else if (Language.compare("Turkmen", Qt::CaseInsensitive) == 0) n = QLocale::Turkmen;
        else if (Language.compare("Twi", Qt::CaseInsensitive) == 0) n = QLocale::Twi;
        else if (Language.compare("Uigur", Qt::CaseInsensitive) == 0) n = QLocale::Uigur;
        else if (Language.compare("Ukrainian", Qt::CaseInsensitive) == 0) n = QLocale::Ukrainian;

        else if (Language.compare("Urdu", Qt::CaseInsensitive) == 0) n = QLocale::Urdu;
        else if (Language.compare("Uzbek", Qt::CaseInsensitive) == 0) n = QLocale::Uzbek;
        else if (Language.compare("Vietnamese", Qt::CaseInsensitive) == 0) n = QLocale::Vietnamese;

        else if (Language.compare("Volapuk", Qt::CaseInsensitive) == 0) n = QLocale::Volapuk;
        else if (Language.compare("Welsh", Qt::CaseInsensitive) == 0) n = QLocale::Welsh;
        else if (Language.compare("Wolof", Qt::CaseInsensitive) == 0) n = QLocale::Wolof;
        else if (Language.compare("Xhosa", Qt::CaseInsensitive) == 0) n = QLocale::Xhosa;

        else if (Language.compare("Yiddish", Qt::CaseInsensitive) == 0) n = QLocale::Yiddish;
        else if (Language.compare("Yoruba", Qt::CaseInsensitive) == 0) n = QLocale::Yoruba;
        else if (Language.compare("Zhuang", Qt::CaseInsensitive) == 0) n = QLocale::Zhuang;
        else if (Language.compare("Zulu", Qt::CaseInsensitive) == 0) n = QLocale::Zulu;
        else if (Language.compare("Bosnian", Qt::CaseInsensitive) == 0) n = QLocale::Bosnian;

        else if (Language.compare("Divehi", Qt::CaseInsensitive) == 0) n = QLocale::Divehi;
        else if (Language.compare("Manx", Qt::CaseInsensitive) == 0) n = QLocale::Manx;
        else if (Language.compare("Cornish", Qt::CaseInsensitive) == 0) n = QLocale::Cornish;
        else if (Language.compare("Akan", Qt::CaseInsensitive) == 0) n = QLocale::Akan;

        else if (Language.compare("Konkani", Qt::CaseInsensitive) == 0) n = QLocale::Konkani;
        else if (Language.compare("Ga", Qt::CaseInsensitive) == 0) n = QLocale::Ga;
        else if (Language.compare("Igbo", Qt::CaseInsensitive) == 0) n = QLocale::Igbo;
        else if (Language.compare("Kamba", Qt::CaseInsensitive) == 0) n = QLocale::Kamba;
        else if (Language.compare("Syriac", Qt::CaseInsensitive) == 0) n = QLocale::Syriac;

        else if (Language.compare("Blin", Qt::CaseInsensitive) == 0) n = QLocale::Blin;
        else if (Language.compare("Geez", Qt::CaseInsensitive) == 0) n = QLocale::Geez;
        else if (Language.compare("Koro", Qt::CaseInsensitive) == 0) n = QLocale::Koro;
        else if (Language.compare("Sidamo", Qt::CaseInsensitive) == 0) n = QLocale::Sidamo;

        else if (Language.compare("Atsam", Qt::CaseInsensitive) == 0) n = QLocale::Atsam;
        else if (Language.compare("Tigre", Qt::CaseInsensitive) == 0) n = QLocale::Tigre;
        else if (Language.compare("Jju", Qt::CaseInsensitive) == 0) n = QLocale::Jju;
        else if (Language.compare("Friulian", Qt::CaseInsensitive) == 0) n = QLocale::Friulian;
        else if (Language.compare("Venda", Qt::CaseInsensitive) == 0) n = QLocale::Venda;

        else if (Language.compare("Ewe", Qt::CaseInsensitive) == 0) n = QLocale::Ewe;
        else if (Language.compare("Walamo", Qt::CaseInsensitive) == 0) n = QLocale::Walamo;
        else if (Language.compare("Hawaiian", Qt::CaseInsensitive) == 0) n = QLocale::Hawaiian;
        else if (Language.compare("Tyap", Qt::CaseInsensitive) == 0) n = QLocale::Tyap;
        else if (Language.compare("Chewa", Qt::CaseInsensitive) == 0) n = QLocale::Chewa;

        int c = QLocale::AnyCountry;
        if (!sCurrentCountry.isEmpty()){
               if (sCurrentCountry.compare("Afghanistan", Qt::CaseInsensitive) == 0) c = QLocale::Afghanistan;
          else if (sCurrentCountry.compare("Albania", Qt::CaseInsensitive) == 0) c = QLocale::Albania;
          else if (sCurrentCountry.compare("Algeria", Qt::CaseInsensitive) == 0) c = QLocale::Algeria;
          else if (sCurrentCountry.compare("AmericanSamoa", Qt::CaseInsensitive) == 0) c = QLocale::AmericanSamoa;
          else if (sCurrentCountry.compare("Andorra", Qt::CaseInsensitive) == 0) c = QLocale::Andorra;
          else if (sCurrentCountry.compare("Angola", Qt::CaseInsensitive) == 0) c = QLocale::Angola;
          else if (sCurrentCountry.compare("Anguilla", Qt::CaseInsensitive) == 0) c = QLocale::Anguilla;
          else if (sCurrentCountry.compare("Antarctica", Qt::CaseInsensitive) == 0) c = QLocale::Antarctica;
          else if (sCurrentCountry.compare("AntiguaAndBarbuda", Qt::CaseInsensitive) == 0) c = QLocale::AntiguaAndBarbuda;
          else if (sCurrentCountry.compare("Argentina", Qt::CaseInsensitive) == 0) c = QLocale::Argentina;
          else if (sCurrentCountry.compare("Armenia", Qt::CaseInsensitive) == 0) c = QLocale::Armenia;
          else if (sCurrentCountry.compare("Aruba", Qt::CaseInsensitive) == 0) c = QLocale::Aruba;
          else if (sCurrentCountry.compare("Australia", Qt::CaseInsensitive) == 0) c = QLocale::Australia;
          else if (sCurrentCountry.compare("Austria", Qt::CaseInsensitive) == 0) c = QLocale::Austria;
          else if (sCurrentCountry.compare("Azerbaijan", Qt::CaseInsensitive) == 0) c = QLocale::Azerbaijan;
          else if (sCurrentCountry.compare("Bahamas", Qt::CaseInsensitive) == 0) c = QLocale::Bahamas;
          else if (sCurrentCountry.compare("Bahrain", Qt::CaseInsensitive) == 0) c = QLocale::Bahrain;
          else if (sCurrentCountry.compare("Bangladesh", Qt::CaseInsensitive) == 0) c = QLocale::Bangladesh;
          else if (sCurrentCountry.compare("Barbados", Qt::CaseInsensitive) == 0) c = QLocale::Barbados;
          else if (sCurrentCountry.compare("Belarus", Qt::CaseInsensitive) == 0) c = QLocale::Belarus;
          else if (sCurrentCountry.compare("Belgium", Qt::CaseInsensitive) == 0) c = QLocale::Belgium;
          else if (sCurrentCountry.compare("Belize", Qt::CaseInsensitive) == 0) c = QLocale::Belize;
          else if (sCurrentCountry.compare("Benin", Qt::CaseInsensitive) == 0) c = QLocale::Benin;
          else if (sCurrentCountry.compare("Bermuda", Qt::CaseInsensitive) == 0) c = QLocale::Bermuda;
          else if (sCurrentCountry.compare("Bhutan", Qt::CaseInsensitive) == 0) c = QLocale::Bhutan;
          else if (sCurrentCountry.compare("Bolivia", Qt::CaseInsensitive) == 0) c = QLocale::Bolivia;
          else if (sCurrentCountry.compare("BosniaAndHerzegowina", Qt::CaseInsensitive) == 0) c = QLocale::BosniaAndHerzegowina;
          else if (sCurrentCountry.compare("Botswana", Qt::CaseInsensitive) == 0) c = QLocale::Botswana;
          else if (sCurrentCountry.compare("BouvetIsland", Qt::CaseInsensitive) == 0) c = QLocale::BouvetIsland;
          else if (sCurrentCountry.compare("Brazil", Qt::CaseInsensitive) == 0) c = QLocale::Brazil;
          else if (sCurrentCountry.compare("BritishIndianOceanTerritory", Qt::CaseInsensitive) == 0) c = QLocale::BritishIndianOceanTerritory;
          else if (sCurrentCountry.compare("BruneiDarussalam", Qt::CaseInsensitive) == 0) c = QLocale::BruneiDarussalam;
          else if (sCurrentCountry.compare("Bulgaria", Qt::CaseInsensitive) == 0) c = QLocale::Bulgaria;
          else if (sCurrentCountry.compare("BurkinaFaso", Qt::CaseInsensitive) == 0) c = QLocale::BurkinaFaso;
          else if (sCurrentCountry.compare("Burundi", Qt::CaseInsensitive) == 0) c = QLocale::Burundi;
          else if (sCurrentCountry.compare("Cambodia", Qt::CaseInsensitive) == 0) c = QLocale::Cambodia;
          else if (sCurrentCountry.compare("Cameroon", Qt::CaseInsensitive) == 0) c = QLocale::Cameroon;
          else if (sCurrentCountry.compare("Canada", Qt::CaseInsensitive) == 0) c = QLocale::Canada;
          else if (sCurrentCountry.compare("CapeVerde", Qt::CaseInsensitive) == 0) c = QLocale::CapeVerde;
          else if (sCurrentCountry.compare("CaymanIslands", Qt::CaseInsensitive) == 0) c = QLocale::CaymanIslands;
          else if (sCurrentCountry.compare("CentralAfricanRepublic", Qt::CaseInsensitive) == 0) c = QLocale::CentralAfricanRepublic;
          else if (sCurrentCountry.compare("Chad", Qt::CaseInsensitive) == 0) c = QLocale::Chad;
          else if (sCurrentCountry.compare("Chile", Qt::CaseInsensitive) == 0) c = QLocale::Chile;
          else if (sCurrentCountry.compare("China", Qt::CaseInsensitive) == 0) c = QLocale::China;
          else if (sCurrentCountry.compare("ChristmasIsland", Qt::CaseInsensitive) == 0) c = QLocale::ChristmasIsland;
          else if (sCurrentCountry.compare("CocosIslands", Qt::CaseInsensitive) == 0) c = QLocale::CocosIslands;
          else if (sCurrentCountry.compare("Colombia", Qt::CaseInsensitive) == 0) c = QLocale::Colombia;
          else if (sCurrentCountry.compare("Comoros", Qt::CaseInsensitive) == 0) c = QLocale::Comoros;
          else if (sCurrentCountry.compare("DemocraticRepublicOfCongo", Qt::CaseInsensitive) == 0) c = QLocale::DemocraticRepublicOfCongo;
          else if (sCurrentCountry.compare("PeoplesRepublicOfCongo", Qt::CaseInsensitive) == 0) c = QLocale::PeoplesRepublicOfCongo;
          else if (sCurrentCountry.compare("CookIslands", Qt::CaseInsensitive) == 0) c = QLocale::CookIslands;
          else if (sCurrentCountry.compare("CostaRica", Qt::CaseInsensitive) == 0) c = QLocale::CostaRica;
          else if (sCurrentCountry.compare("IvoryCoast", Qt::CaseInsensitive) == 0) c = QLocale::IvoryCoast;
          else if (sCurrentCountry.compare("Croatia", Qt::CaseInsensitive) == 0) c = QLocale::Croatia;
          else if (sCurrentCountry.compare("Cuba", Qt::CaseInsensitive) == 0) c = QLocale::Cuba;
          else if (sCurrentCountry.compare("Cyprus", Qt::CaseInsensitive) == 0) c = QLocale::Cyprus;
          else if (sCurrentCountry.compare("CzechRepublic", Qt::CaseInsensitive) == 0) c = QLocale::CzechRepublic;
          else if (sCurrentCountry.compare("Denmark", Qt::CaseInsensitive) == 0) c = QLocale::Denmark;
          else if (sCurrentCountry.compare("Djibouti", Qt::CaseInsensitive) == 0) c = QLocale::Djibouti;
          else if (sCurrentCountry.compare("Dominica", Qt::CaseInsensitive) == 0) c = QLocale::Dominica;
          else if (sCurrentCountry.compare("DominicanRepublic", Qt::CaseInsensitive) == 0) c = QLocale::DominicanRepublic;
          else if (sCurrentCountry.compare("EastTimor", Qt::CaseInsensitive) == 0) c = QLocale::EastTimor;
          else if (sCurrentCountry.compare("Ecuador", Qt::CaseInsensitive) == 0) c = QLocale::Ecuador;
          else if (sCurrentCountry.compare("Egypt", Qt::CaseInsensitive) == 0) c = QLocale::Egypt;
          else if (sCurrentCountry.compare("ElSalvador", Qt::CaseInsensitive) == 0) c = QLocale::ElSalvador;
          else if (sCurrentCountry.compare("EquatorialGuinea", Qt::CaseInsensitive) == 0) c = QLocale::EquatorialGuinea;
          else if (sCurrentCountry.compare("Eritrea", Qt::CaseInsensitive) == 0) c = QLocale::Eritrea;
          else if (sCurrentCountry.compare("Estonia", Qt::CaseInsensitive) == 0) c = QLocale::Estonia;
          else if (sCurrentCountry.compare("Ethiopia", Qt::CaseInsensitive) == 0) c = QLocale::Ethiopia;
          else if (sCurrentCountry.compare("FalklandIslands", Qt::CaseInsensitive) == 0) c = QLocale::FalklandIslands;
          else if (sCurrentCountry.compare("FaroeIslands", Qt::CaseInsensitive) == 0) c = QLocale::FaroeIslands;
          else if (sCurrentCountry.compare("FijiCountry", Qt::CaseInsensitive) == 0) c = QLocale::FijiCountry;
          else if (sCurrentCountry.compare("Finland", Qt::CaseInsensitive) == 0) c = QLocale::Finland;
          else if (sCurrentCountry.compare("France", Qt::CaseInsensitive) == 0) c = QLocale::France;
          else if (sCurrentCountry.compare("MetropolitanFrance", Qt::CaseInsensitive) == 0) c = QLocale::MetropolitanFrance;
          else if (sCurrentCountry.compare("FrenchGuiana", Qt::CaseInsensitive) == 0) c = QLocale::FrenchGuiana;
          else if (sCurrentCountry.compare("FrenchPolynesia", Qt::CaseInsensitive) == 0) c = QLocale::FrenchPolynesia;
          else if (sCurrentCountry.compare("FrenchSouthernTerritories", Qt::CaseInsensitive) == 0) c = QLocale::FrenchSouthernTerritories;
          else if (sCurrentCountry.compare("Gabon", Qt::CaseInsensitive) == 0) c = QLocale::Gabon;
          else if (sCurrentCountry.compare("Gambia", Qt::CaseInsensitive) == 0) c = QLocale::Gambia;
          else if (sCurrentCountry.compare("Georgia", Qt::CaseInsensitive) == 0) c = QLocale::Georgia;
          else if (sCurrentCountry.compare("Germany", Qt::CaseInsensitive) == 0) c = QLocale::Germany;
          else if (sCurrentCountry.compare("Ghana", Qt::CaseInsensitive) == 0) c = QLocale::Ghana;
          else if (sCurrentCountry.compare("Gibraltar", Qt::CaseInsensitive) == 0) c = QLocale::Gibraltar;
          else if (sCurrentCountry.compare("Greece", Qt::CaseInsensitive) == 0) c = QLocale::Greece;
          else if (sCurrentCountry.compare("Greenland", Qt::CaseInsensitive) == 0) c = QLocale::Greenland;
          else if (sCurrentCountry.compare("Grenada", Qt::CaseInsensitive) == 0) c = QLocale::Grenada;
          else if (sCurrentCountry.compare("Guadeloupe", Qt::CaseInsensitive) == 0) c = QLocale::Guadeloupe;
          else if (sCurrentCountry.compare("Guam", Qt::CaseInsensitive) == 0) c = QLocale::Guam;
          else if (sCurrentCountry.compare("Guatemala", Qt::CaseInsensitive) == 0) c = QLocale::Guatemala;          
          
          if (sCurrentCountry.compare("Guinea", Qt::CaseInsensitive) == 0) c = QLocale::Guinea;
          else if (sCurrentCountry.compare("GuineaBissau", Qt::CaseInsensitive) == 0) c = QLocale::GuineaBissau;
          else if (sCurrentCountry.compare("Guyana", Qt::CaseInsensitive) == 0) c = QLocale::Guyana;
          else if (sCurrentCountry.compare("Haiti", Qt::CaseInsensitive) == 0) c = QLocale::Haiti;
          else if (sCurrentCountry.compare("HeardAndMcDonaldIslands", Qt::CaseInsensitive) == 0) c = QLocale::HeardAndMcDonaldIslands;
          else if (sCurrentCountry.compare("Honduras", Qt::CaseInsensitive) == 0) c = QLocale::Honduras;
          else if (sCurrentCountry.compare("HongKong", Qt::CaseInsensitive) == 0) c = QLocale::HongKong;
          else if (sCurrentCountry.compare("Hungary", Qt::CaseInsensitive) == 0) c = QLocale::Hungary;
          else if (sCurrentCountry.compare("Iceland", Qt::CaseInsensitive) == 0) c = QLocale::Iceland;
          else if (sCurrentCountry.compare("India", Qt::CaseInsensitive) == 0) c = QLocale::India;
          else if (sCurrentCountry.compare("Indonesia", Qt::CaseInsensitive) == 0) c = QLocale::Indonesia;
          
          if (sCurrentCountry.compare("Iran", Qt::CaseInsensitive) == 0) c = QLocale::Iran;
          else if (sCurrentCountry.compare("Iraq", Qt::CaseInsensitive) == 0) c = QLocale::Iraq;
          else if (sCurrentCountry.compare("Ireland", Qt::CaseInsensitive) == 0) c = QLocale::Ireland;
          else if (sCurrentCountry.compare("Israel", Qt::CaseInsensitive) == 0) c = QLocale::Israel;
          else if (sCurrentCountry.compare("Italy", Qt::CaseInsensitive) == 0) c = QLocale::Italy;
          else if (sCurrentCountry.compare("Jamaica", Qt::CaseInsensitive) == 0) c = QLocale::Jamaica;
          else if (sCurrentCountry.compare("Japan", Qt::CaseInsensitive) == 0) c = QLocale::Japan;
          else if (sCurrentCountry.compare("Jordan", Qt::CaseInsensitive) == 0) c = QLocale::Jordan;
          else if (sCurrentCountry.compare("Kazakhstan", Qt::CaseInsensitive) == 0) c = QLocale::Kazakhstan;
          else if (sCurrentCountry.compare("Kenya", Qt::CaseInsensitive) == 0) c = QLocale::Kenya;
          else if (sCurrentCountry.compare("Kiribati", Qt::CaseInsensitive) == 0) c = QLocale::Kiribati;
          else if (sCurrentCountry.compare("DemocraticRepublicOfKorea", Qt::CaseInsensitive) == 0) c = QLocale::DemocraticRepublicOfKorea;
          else if (sCurrentCountry.compare("RepublicOfKorea", Qt::CaseInsensitive) == 0) c = QLocale::RepublicOfKorea;
          else if (sCurrentCountry.compare("Kuwait", Qt::CaseInsensitive) == 0) c = QLocale::Kuwait;
          else if (sCurrentCountry.compare("Kyrgyzstan", Qt::CaseInsensitive) == 0) c = QLocale::Kyrgyzstan;
          else if (sCurrentCountry.compare("Lao", Qt::CaseInsensitive) == 0) c = QLocale::Lao;
          else if (sCurrentCountry.compare("Latvia", Qt::CaseInsensitive) == 0) c = QLocale::Latvia;
          else if (sCurrentCountry.compare("Lebanon", Qt::CaseInsensitive) == 0) c = QLocale::Lebanon;
          else if (sCurrentCountry.compare("Lesotho", Qt::CaseInsensitive) == 0) c = QLocale::Lesotho;
          else if (sCurrentCountry.compare("Liberia", Qt::CaseInsensitive) == 0) c = QLocale::Liberia;
          else if (sCurrentCountry.compare("LibyanArabJamahiriya", Qt::CaseInsensitive) == 0) c = QLocale::LibyanArabJamahiriya;
          else if (sCurrentCountry.compare("Liechtenstein", Qt::CaseInsensitive) == 0) c = QLocale::Liechtenstein;
          else if (sCurrentCountry.compare("Lithuania", Qt::CaseInsensitive) == 0) c = QLocale::Lithuania;
          else if (sCurrentCountry.compare("Luxembourg", Qt::CaseInsensitive) == 0) c = QLocale::Luxembourg;
          else if (sCurrentCountry.compare("Macau", Qt::CaseInsensitive) == 0) c = QLocale::Macau;
          else if (sCurrentCountry.compare("Macedonia", Qt::CaseInsensitive) == 0) c = QLocale::Macedonia;
          else if (sCurrentCountry.compare("Madagascar", Qt::CaseInsensitive) == 0) c = QLocale::Madagascar;
          else if (sCurrentCountry.compare("Malawi", Qt::CaseInsensitive) == 0) c = QLocale::Malawi;
          else if (sCurrentCountry.compare("Malaysia", Qt::CaseInsensitive) == 0) c = QLocale::Malaysia;
          else if (sCurrentCountry.compare("Maldives", Qt::CaseInsensitive) == 0) c = QLocale::Maldives;
          else if (sCurrentCountry.compare("Mali", Qt::CaseInsensitive) == 0) c = QLocale::Mali;
          else if (sCurrentCountry.compare("Malta", Qt::CaseInsensitive) == 0) c = QLocale::Malta;
          else if (sCurrentCountry.compare("MarshallIslands", Qt::CaseInsensitive) == 0) c = QLocale::MarshallIslands;
          else if (sCurrentCountry.compare("Martinique", Qt::CaseInsensitive) == 0) c = QLocale::Martinique;
          else if (sCurrentCountry.compare("Mauritania", Qt::CaseInsensitive) == 0) c = QLocale::Mauritania;
          else if (sCurrentCountry.compare("Mauritius", Qt::CaseInsensitive) == 0) c = QLocale::Mauritius;
          else if (sCurrentCountry.compare("Mayotte", Qt::CaseInsensitive) == 0) c = QLocale::Mayotte;
          else if (sCurrentCountry.compare("Mexico", Qt::CaseInsensitive) == 0) c = QLocale::Mexico;
          else if (sCurrentCountry.compare("Micronesia", Qt::CaseInsensitive) == 0) c = QLocale::Micronesia;
          else if (sCurrentCountry.compare("Moldova", Qt::CaseInsensitive) == 0) c = QLocale::Moldova;
          else if (sCurrentCountry.compare("Monaco", Qt::CaseInsensitive) == 0) c = QLocale::Monaco;
          else if (sCurrentCountry.compare("Mongolia", Qt::CaseInsensitive) == 0) c = QLocale::Mongolia;
          else if (sCurrentCountry.compare("Montserrat", Qt::CaseInsensitive) == 0) c = QLocale::Montserrat;
          else if (sCurrentCountry.compare("Morocco", Qt::CaseInsensitive) == 0) c = QLocale::Morocco;
          else if (sCurrentCountry.compare("Mozambique", Qt::CaseInsensitive) == 0) c = QLocale::Mozambique;
          else if (sCurrentCountry.compare("Myanmar", Qt::CaseInsensitive) == 0) c = QLocale::Myanmar;
          else if (sCurrentCountry.compare("Namibia", Qt::CaseInsensitive) == 0) c = QLocale::Namibia;
          else if (sCurrentCountry.compare("NauruCountry", Qt::CaseInsensitive) == 0) c = QLocale::NauruCountry;
          else if (sCurrentCountry.compare("Nepal", Qt::CaseInsensitive) == 0) c = QLocale::Nepal;
          else if (sCurrentCountry.compare("Netherlands", Qt::CaseInsensitive) == 0) c = QLocale::Netherlands;
          else if (sCurrentCountry.compare("NetherlandsAntilles", Qt::CaseInsensitive) == 0) c = QLocale::NetherlandsAntilles;
          else if (sCurrentCountry.compare("NewCaledonia", Qt::CaseInsensitive) == 0) c = QLocale::NewCaledonia;
          else if (sCurrentCountry.compare("NewZealand", Qt::CaseInsensitive) == 0) c = QLocale::NewZealand;
          else if (sCurrentCountry.compare("Nicaragua", Qt::CaseInsensitive) == 0) c = QLocale::Nicaragua;
          else if (sCurrentCountry.compare("Niger", Qt::CaseInsensitive) == 0) c = QLocale::Niger;
          else if (sCurrentCountry.compare("Nigeria", Qt::CaseInsensitive) == 0) c = QLocale::Nigeria;
          else if (sCurrentCountry.compare("Niue", Qt::CaseInsensitive) == 0) c = QLocale::Niue;
          else if (sCurrentCountry.compare("NorfolkIsland", Qt::CaseInsensitive) == 0) c = QLocale::NorfolkIsland;
          else if (sCurrentCountry.compare("NorthernMarianaIslands", Qt::CaseInsensitive) == 0) c = QLocale::NorthernMarianaIslands;
          else if (sCurrentCountry.compare("Norway", Qt::CaseInsensitive) == 0) c = QLocale::Norway;
          else if (sCurrentCountry.compare("Oman", Qt::CaseInsensitive) == 0) c = QLocale::Oman;
          
          if (sCurrentCountry.compare("Pakistan", Qt::CaseInsensitive) == 0) c = QLocale::Pakistan;
          else if (sCurrentCountry.compare("Palau", Qt::CaseInsensitive) == 0) c = QLocale::Palau;
          else if (sCurrentCountry.compare("PalestinianTerritory", Qt::CaseInsensitive) == 0) c = QLocale::PalestinianTerritory;
          else if (sCurrentCountry.compare("Panama", Qt::CaseInsensitive) == 0) c = QLocale::Panama;
          else if (sCurrentCountry.compare("PapuaNewGuinea", Qt::CaseInsensitive) == 0) c = QLocale::PapuaNewGuinea;
          else if (sCurrentCountry.compare("Paraguay", Qt::CaseInsensitive) == 0) c = QLocale::Paraguay;
          else if (sCurrentCountry.compare("Peru", Qt::CaseInsensitive) == 0) c = QLocale::Peru;
          else if (sCurrentCountry.compare("Philippines", Qt::CaseInsensitive) == 0) c = QLocale::Philippines;
          else if (sCurrentCountry.compare("Pitcairn", Qt::CaseInsensitive) == 0) c = QLocale::Pitcairn;
          else if (sCurrentCountry.compare("Poland", Qt::CaseInsensitive) == 0) c = QLocale::Poland;
          else if (sCurrentCountry.compare("Portugal", Qt::CaseInsensitive) == 0) c = QLocale::Portugal;
          else if (sCurrentCountry.compare("PuertoRico", Qt::CaseInsensitive) == 0) c = QLocale::PuertoRico;
          else if (sCurrentCountry.compare("Qatar", Qt::CaseInsensitive) == 0) c = QLocale::Qatar;
          else if (sCurrentCountry.compare("Reunion", Qt::CaseInsensitive) == 0) c = QLocale::Reunion;
          else if (sCurrentCountry.compare("Romania", Qt::CaseInsensitive) == 0) c = QLocale::Romania;
          else if (sCurrentCountry.compare("RussianFederation", Qt::CaseInsensitive) == 0) c = QLocale::RussianFederation;
          else if (sCurrentCountry.compare("Rwanda", Qt::CaseInsensitive) == 0) c = QLocale::Rwanda;
          else if (sCurrentCountry.compare("SaintKittsAndNevis", Qt::CaseInsensitive) == 0) c = QLocale::SaintKittsAndNevis;
          else if (sCurrentCountry.compare("StLucia", Qt::CaseInsensitive) == 0) c = QLocale::StLucia;
          else if (sCurrentCountry.compare("StVincentAndTheGrenadines", Qt::CaseInsensitive) == 0) c = QLocale::StVincentAndTheGrenadines;
          else if (sCurrentCountry.compare("Samoa", Qt::CaseInsensitive) == 0) c = QLocale::Samoa;
          else if (sCurrentCountry.compare("SanMarino", Qt::CaseInsensitive) == 0) c = QLocale::SanMarino;
          else if (sCurrentCountry.compare("SaoTomeAndPrincipe", Qt::CaseInsensitive) == 0) c = QLocale::SaoTomeAndPrincipe;
          else if (sCurrentCountry.compare("SaudiArabia", Qt::CaseInsensitive) == 0) c = QLocale::SaudiArabia;
          else if (sCurrentCountry.compare("Senegal", Qt::CaseInsensitive) == 0) c = QLocale::Senegal;
          else if (sCurrentCountry.compare("SerbiaAndMontenegro", Qt::CaseInsensitive) == 0) c = QLocale::SerbiaAndMontenegro;
          else if (sCurrentCountry.compare("Seychelles", Qt::CaseInsensitive) == 0) c = QLocale::Seychelles;
          else if (sCurrentCountry.compare("SierraLeone", Qt::CaseInsensitive) == 0) c = QLocale::SierraLeone;
          else if (sCurrentCountry.compare("Singapore", Qt::CaseInsensitive) == 0) c = QLocale::Singapore;
          else if (sCurrentCountry.compare("Slovakia", Qt::CaseInsensitive) == 0) c = QLocale::Slovakia;
          else if (sCurrentCountry.compare("Slovenia", Qt::CaseInsensitive) == 0) c = QLocale::Slovenia;
          else if (sCurrentCountry.compare("SolomonIslands", Qt::CaseInsensitive) == 0) c = QLocale::SolomonIslands;
          else if (sCurrentCountry.compare("Somalia", Qt::CaseInsensitive) == 0) c = QLocale::Somalia;
          else if (sCurrentCountry.compare("SouthAfrica", Qt::CaseInsensitive) == 0) c = QLocale::SouthAfrica;
          else if (sCurrentCountry.compare("SouthGeorgiaAndTheSouthSandwichIslands", Qt::CaseInsensitive) == 0) c = QLocale::SouthGeorgiaAndTheSouthSandwichIslands;
          else if (sCurrentCountry.compare("Spain", Qt::CaseInsensitive) == 0) c = QLocale::Spain;
          else if (sCurrentCountry.compare("SriLanka", Qt::CaseInsensitive) == 0) c = QLocale::SriLanka;
          else if (sCurrentCountry.compare("StHelena", Qt::CaseInsensitive) == 0) c = QLocale::StHelena;
          else if (sCurrentCountry.compare("StPierreAndMiquelon", Qt::CaseInsensitive) == 0) c = QLocale::StPierreAndMiquelon;
          else if (sCurrentCountry.compare("Sudan", Qt::CaseInsensitive) == 0) c = QLocale::Sudan;
          else if (sCurrentCountry.compare("Suriname", Qt::CaseInsensitive) == 0) c = QLocale::Suriname;
          else if (sCurrentCountry.compare("SvalbardAndJanMayenIslands", Qt::CaseInsensitive) == 0) c = QLocale::SvalbardAndJanMayenIslands;
          else if (sCurrentCountry.compare("Swaziland", Qt::CaseInsensitive) == 0) c = QLocale::Swaziland;
          else if (sCurrentCountry.compare("Sweden", Qt::CaseInsensitive) == 0) c = QLocale::Sweden;
          else if (sCurrentCountry.compare("Switzerland", Qt::CaseInsensitive) == 0) c = QLocale::Switzerland;
          else if (sCurrentCountry.compare("SyrianArabRepublic", Qt::CaseInsensitive) == 0) c = QLocale::SyrianArabRepublic;
          else if (sCurrentCountry.compare("Taiwan", Qt::CaseInsensitive) == 0) c = QLocale::Taiwan;
          else if (sCurrentCountry.compare("Tajikistan", Qt::CaseInsensitive) == 0) c = QLocale::Tajikistan;
          else if (sCurrentCountry.compare("Tanzania", Qt::CaseInsensitive) == 0) c = QLocale::Tanzania;
          else if (sCurrentCountry.compare("Thailand", Qt::CaseInsensitive) == 0) c = QLocale::Thailand;
          else if (sCurrentCountry.compare("Togo", Qt::CaseInsensitive) == 0) c = QLocale::Togo;
          else if (sCurrentCountry.compare("Tokelau", Qt::CaseInsensitive) == 0) c = QLocale::Tokelau;
          else if (sCurrentCountry.compare("TongaCountry", Qt::CaseInsensitive) == 0) c = QLocale::TongaCountry;
          else if (sCurrentCountry.compare("TrinidadAndTobago", Qt::CaseInsensitive) == 0) c = QLocale::TrinidadAndTobago;
          else if (sCurrentCountry.compare("Tunisia", Qt::CaseInsensitive) == 0) c = QLocale::Tunisia;
          else if (sCurrentCountry.compare("Turkey", Qt::CaseInsensitive) == 0) c = QLocale::Turkey;
          else if (sCurrentCountry.compare("Turkmenistan", Qt::CaseInsensitive) == 0) c = QLocale::Turkmenistan;
          else if (sCurrentCountry.compare("TurksAndCaicosIslands", Qt::CaseInsensitive) == 0) c = QLocale::TurksAndCaicosIslands;
          else if (sCurrentCountry.compare("Tuvalu", Qt::CaseInsensitive) == 0) c = QLocale::Tuvalu;
          else if (sCurrentCountry.compare("Uganda", Qt::CaseInsensitive) == 0) c = QLocale::Uganda;
          
           if (sCurrentCountry.compare("Ukraine", Qt::CaseInsensitive) == 0) c = QLocale::Ukraine;
          else if (sCurrentCountry.compare("UnitedArabEmirates", Qt::CaseInsensitive) == 0) c = QLocale::UnitedArabEmirates;
          else if (sCurrentCountry.compare("UnitedKingdom", Qt::CaseInsensitive) == 0) c = QLocale::UnitedKingdom;
          else if (sCurrentCountry.compare("UnitedStates", Qt::CaseInsensitive) == 0) c = QLocale::UnitedStates;
          else if (sCurrentCountry.compare("UnitedStatesMinorOutlyingIslands", Qt::CaseInsensitive) == 0) c = QLocale::UnitedStatesMinorOutlyingIslands;
          else if (sCurrentCountry.compare("Uruguay", Qt::CaseInsensitive) == 0) c = QLocale::Uruguay;
          else if (sCurrentCountry.compare("Uzbekistan", Qt::CaseInsensitive) == 0) c = QLocale::Uzbekistan;
          else if (sCurrentCountry.compare("Vanuatu", Qt::CaseInsensitive) == 0) c = QLocale::Vanuatu;
          else if (sCurrentCountry.compare("VaticanCityState", Qt::CaseInsensitive) == 0) c = QLocale::VaticanCityState;
          else if (sCurrentCountry.compare("Venezuela", Qt::CaseInsensitive) == 0) c = QLocale::Venezuela;
          else if (sCurrentCountry.compare("VietNam", Qt::CaseInsensitive) == 0) c = QLocale::VietNam;
          else if (sCurrentCountry.compare("BritishVirginIslands", Qt::CaseInsensitive) == 0) c = QLocale::BritishVirginIslands;
          else if (sCurrentCountry.compare("USVirginIslands", Qt::CaseInsensitive) == 0) c = QLocale::USVirginIslands;
          else if (sCurrentCountry.compare("WallisAndFutunaIslands", Qt::CaseInsensitive) == 0) c = QLocale::WallisAndFutunaIslands;
          else if (sCurrentCountry.compare("WesternSahara", Qt::CaseInsensitive) == 0) c = QLocale::WesternSahara;
          else if (sCurrentCountry.compare("Yemen", Qt::CaseInsensitive) == 0) c = QLocale::Yemen;
          else if (sCurrentCountry.compare("Yugoslavia", Qt::CaseInsensitive) == 0) c = QLocale::Yugoslavia;
          else if (sCurrentCountry.compare("Zambia", Qt::CaseInsensitive) == 0) c = QLocale::Zambia;
          else if (sCurrentCountry.compare("Zimbabwe", Qt::CaseInsensitive) == 0) c = QLocale::Zimbabwe;

        }

        qlocale = new QLocale((QLocale::Language) n, (QLocale::Country) c);
      }
    }
    QLocale::setDefault(*qlocale);
  }

   const char *ac = EXTERN_myInterpreter->loadProjectFile(Language + ".kbasic_translation");
   QString s = QString::fromUtf8(ac);

    trs.clear();

  QStringList l = s.split("\n");

  foreach(QString m, l){
    int n = m.indexOf("=");
    if (n >= 0){
      QString k = m.left(n);
      if (k.contains("!\"§$%&/()")){
        k = k.replace("!\"§$%&/()", "=");
      }
      QString v = m.mid(n + 1);

      trs[k] = v;
    }
  }

  if (aWindow){ if (trs.contains("&Window")) aWindow->setText(trs["&Window"]); else aWindow->setText("&Window"); }
  if (aHelp){ if (trs.contains("&Help")) aHelp->setText(trs["&Help"]); else aHelp->setText("&Help"); }
  if (aRecords){ if (trs.contains("&Records")) aRecords->setText(trs["&Records"]); else aRecords->setText("&Records"); }

  if (aContents){ if (trs.contains("C&ontents")) aContents->setText(trs["C&ontents"]); else aContents->setText("C&ontents"); }
  if (aAbout){ if (trs.contains("A&bout")) aAbout->setText(trs["A&bout"]); else aAbout->setText("A&bout"); }

  if (aCloseAct){ if (trs.contains("Cl&ose")) aCloseAct->setText(trs["Cl&ose"]); else aCloseAct->setText("Cl&ose"); }
  if (aCloseAllAct){ if (trs.contains("Close &All")) aCloseAllAct->setText(trs["Close &All"]); else aCloseAllAct->setText("Close &All"); }
  if (aTileAct){ if (trs.contains("&Tile")) aTileAct->setText(trs["&Tile"]); else aTileAct->setText("&Tile"); }
  if (aCascadeAct){ if (trs.contains("&Cascade")) aCascadeAct->setText(trs["&Cascade"]); else aCascadeAct->setText("&Cascade"); }
  if (aNextAct){ if (trs.contains("Ne&xt")) aNextAct->setText(trs["Ne&xt"]); else aNextAct->setText("Ne&xt"); }
  if (aPreviousAct){ if (trs.contains("Pre&vious")) aPreviousAct->setText(trs["Pre&vious"]); else aPreviousAct->setText("Pre&vious"); }
  
  if (aAddFilter){ if (trs.contains("&Add Filter")) aAddFilter->setText(trs["&Add Filter"]); else aAddFilter->setText("&Add Filter"); }
  if (aAddNotFilter){ if (trs.contains("Add &NotFilter")) aAddNotFilter->setText(trs["Add &NotFilter"]); else aAddNotFilter->setText("Add &NotFilter"); }
  if (aSetFilter){ if (trs.contains("&Set Filter")) aSetFilter->setText(trs["&Set Filter"]); else aSetFilter->setText("&Set Filter"); }
  if (aSetNotFilter){ if (trs.contains("Set &NotFilter")) aSetNotFilter->setText(trs["Set &NotFilter"]); else aSetNotFilter->setText("Set &NotFilter"); }
  if (aClearFilter){ if (trs.contains("&Clear Filter")) aClearFilter->setText(trs["&Clear Filter"]); else aClearFilter->setText("&Clear Filter"); }
  if (aSortAscending){ if (trs.contains("Sort Ascen&ding")) aSortAscending->setText(trs["Sort Ascen&ding"]); else aSortAscending->setText("Sort Ascen&ding"); }
  if (aSortDescending){ if (trs.contains("Sort Desce&nding")) aSortDescending->setText(trs["Sort Desce&nding"]); else aSortDescending->setText("Sort Desce&nding"); }
  if (aSeek){ if (trs.contains("&Seek")) aSeek->setText(trs["&Seek"]); else aSeek->setText("&Seek"); }
  if (aRequery){ if (trs.contains("&Requery")) aRequery->setText(trs["&Requery"]); else aRequery->setText("&Requery"); }
 
}

void _application::METHOD_SetIcon(QString n)
{
 _mainwindow2::METHOD_SetIcon(n);
}

void _mainwindow2::METHOD_SetIcon(QString n)
{
  if (forms_mainwindow == 0) return;

   bool bMovie = false;
   QList<QByteArray> l = QMovie::supportedFormats();
   for (int i = 0; i < l.size(); ++i) {
      QString ss(l.at(i));
      if (n.endsWith("." + ss, Qt::CaseInsensitive)){
        bMovie = true;
        break;
      }
   }      
   if (bMovie){
     if (setMyMovie(0, &my_forms->movie, &my_forms->moviea, &my_forms->movieb, n)){
       QObject::connect(my_forms->movie, SIGNAL(frameChanged(int)), my_forms, SLOT(frameChanged(int)));
       my_forms->movie->start();
     } else {
       forms_mainwindow->setWindowIcon(interpreter_loadPixmap(n));
     }
     
   } else {

      if (n.length() > 200){ // QString contains binary data
        if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
          n = n.trimmed();
          QSvgWidget w(0);
          w.resize(100, 100);
          QSvgRenderer *r = w.renderer();
          if (r->load(n.toLatin1())){

            QPixmap p(100, 100);
            QPainter painter(&p);
            r->render(&painter);
            forms_mainwindow->setWindowIcon(p);       
          }
        } else {
          QPixmap p; p.loadFromData(n.toLatin1());
          forms_mainwindow->setWindowIcon(p);
        }
      } else {
        forms_mainwindow->setWindowIcon(interpreter_loadPixmap(n));
      }

   }
  
}

_form *_application::METHOD_CurrentForm()

{

  QWidget *w = 0;

  if (w == 0) w = qApp->focusWidget();
  if (w){
    _form *o = qobject_cast<_form *>(w);
    if (o){
      return o;
    }
    while(w){
      w = w->parentWidget();
      _form *o = qobject_cast<_form *>(w);
      if (o){
        return o;
      }
    }
  }

  return 0;
}

void _application::METHOD_AddLanguageTranslatorFile(QString k)
{
  tr_map[k] = new QTranslator(0); 
  int n = 0;
  t_pointer pp = EXTERN_myInterpreter->loadProjectFile(k, &n);

}

void _application::METHOD_Run()
{
  bNotApplicationRun = false;
//  _application::EVENT_Application_OnOpen();
 
  if (bOpenonrun_forms){
    bOpenonrun_forms = false;
    foreach(QString s, openonrun_forms){
      nCurrentFormId = forms2[s];
      interpreter::openForm(s.left(s.indexOf(".")));
    }
  }

  if (forms_mainwindow){

    QWidgetList it = qApp->allWidgets(); // iterate over the children
    QWidget *o;
    for (int q = 0; q < it.size(); q++){
      o = it.at(q);
      _form *f;
	  if ((f = qobject_cast<_form *>(o))){
        QString sDockParent = f->GETPROPERTY_DockOrder();
        if (!sDockParent.isEmpty()){

          QWidgetList it2 = qApp->allWidgets(); // iterate over the children
          QWidget *o;
          for (int q = 0; q < it2.size(); q++){
            o = it2.at(q);
            _form *f2;
            if ((f2 = qobject_cast<_form *>(o))){
              QString k = f2->GETPROPERTY_Name();
              if (k == sDockParent){
                QObject *o2 = f2->parent();
                QObject *o = f->parent();

                forms_mainwindow->tabifyDockWidget(((QDockWidget *) f2->parent()), ((QDockWidget *) f->parent()));
                break;
              }
            }
          }
          
        }
      }
    }

  }
 

  qApp->exec();

}

void _application::METHOD_Stop()
{
  EXTERN_myInterpreter->stop_interpret();
}

void _application::METHOD_SetStyleSheet(QString k)
{
  QString styleSheet = QString::fromUtf8(EXTERN_myInterpreter->loadProjectFile(k));
  qApp->setStyleSheet(styleSheet);
}


void _application::METHOD_SetScrollBarsEnabled(t_boolean k)
{
 _mainwindow2::METHOD_SetScrollBarsEnabled(k);
}

void _mainwindow2::METHOD_SetScrollBarsEnabled(t_boolean k)
{
  if (forms_mainwindow == 0) return;

  if (k){
    forms_workspace->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    forms_workspace->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  } else {
    forms_workspace->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    forms_workspace->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  }

}

void _application::METHOD_SetFocusNextForm()
{
 _mainwindow2::METHOD_SetFocusNextForm();
}

void _mainwindow2::METHOD_SetFocusNextForm()
{
  if (forms_mainwindow == 0) return;

  forms_workspace->activateNextSubWindow();
} 

void _application::METHOD_SetFocusPreviousForm()
{
 _mainwindow2::METHOD_SetFocusPreviousForm();
}

void _mainwindow2::METHOD_SetFocusPreviousForm()
{
  if (forms_mainwindow == 0) return;

  forms_workspace->activatePreviousSubWindow();
} 

void _application::METHOD_Cascade()
{
 _mainwindow2::METHOD_Cascade();
}

void _mainwindow2::METHOD_Cascade()
{
  if (forms_mainwindow == 0) return;

  forms_workspace->cascadeSubWindows();
} 

void _application::METHOD_CloseActiveForm()
{
 _mainwindow2::METHOD_CloseActiveForm();
}

void _mainwindow2::METHOD_CloseActiveForm()
{
  if (forms_mainwindow == 0) return;

  forms_workspace->closeActiveSubWindow();
} 

void _application::METHOD_CloseAll()
{
 _mainwindow2::METHOD_CloseAll();
}

void _mainwindow2::METHOD_CloseAll()
{
  if (forms_mainwindow == 0) return;

  forms_workspace->closeAllSubWindows();
} 

void _application::METHOD_Tile()
{
 _mainwindow2::METHOD_Tile();
}

void _mainwindow2::METHOD_Tile()
{
  if (forms_mainwindow == 0) return;

  forms_workspace->tileSubWindows();
} 

void _application::METHOD_PlaySound(QString FileName)
{
  EXTERN_my_sounds->playOnce(FileName);
}

void _application::METHOD_PlayMovie(QString FileName, t_boolean KeyAndMouseCanCancel)
{
  _movie *my_movie = new _movie(0);
  my_movie->setKeyAndMouseCanCancel(KeyAndMouseCanCancel);
  QPixmap p(1, 1);
  p.fill(QColor(0, 0, 0, 0));
  my_movie->setCursor(p);
  my_movie->enterFullScreen();
  my_movie->METHOD_Play(FileName);
  QString s;
  do {
    qApp->processEvents();
    s = my_movie->METHOD_State();
  } while (s == "LoadingState" || s == "BufferingState" || s == "PlayingState");

  if (s == "ErrorState"){
    sQtException = my_movie->METHOD_ErrorString();
  }

 // QMessageBox::information(0, my_movie->METHOD_ErrorString(), s);

  my_movie->exitFullScreen();
  my_movie->hide();
  delete my_movie;
}


QString _application::METHOD_LoadProjectFileAsString(QString k)
{
  const char *ac = EXTERN_myInterpreter->loadProjectFile(k);
  if (ac){
    return QString::fromUtf8(ac, projectfiles2[k]);
  }

  return "";
}

QString _application::METHOD_LoadProjectFileAsBinary(QString k)
{
  int n = 0;
  t_pointer p = EXTERN_myInterpreter->loadProjectFile(k, &n);
  if (p){
    return QString::fromLatin1((const char *) p, n);
  }

  return "";
}

QString _application::METHOD_LoadFileAsString(QString k)
{
  if (k.startsWith("http://", Qt::CaseInsensitive)){
    k = k.mid(QString("http://").length());
  }

  if (k.startsWith("file:///", Qt::CaseInsensitive)){
    
    QFile f(k);
    if (!f.open(QIODevice::ReadOnly)){
      QByteArray ba = QString("Application.LoadURLAsString: Could not read from %1").arg(k).toLocal8Bit();
      sQtException = ba.data();
    } else {
      QTextStream t(&f);
      
      t.setCodec("UTF-8");
      t.setAutoDetectUnicode(true);
      t.setGenerateByteOrderMark(true);

      QString s = t.readAll();      
      f.close();
      return s;
    }

  } else {

    int n = k.indexOf("/");
    if (n < 0){
      QByteArray ba = QString("Application.LoadURLAsString: Invalid URL: %1").arg(k).toLocal8Bit();
      sQtException = ba.data();
      return "";
    }
    QString sHost = k.left(n);
    QString sPath = k.mid(n);

    QHttp http;
    http.setHost(sHost);     
    QUrl url;   
    if (!url.isValid()){
      url.setUrl(sHost + sPath);
    }
    QString q = url.encodedQuery();
    if (!q.isEmpty()){
      q = q.prepend("?");
    }
    QString z = QString(url.encodedPath().mid(sHost.length())) + q;
    http.get(z);

    while(http.currentId() > 0 && http.error() == QHttp::NoError){
      qApp->processEvents();
    }
    if (http.error() != QHttp::NoError){
      QByteArray ba = QString("Application.LoadURLAsString: %1").arg(http.errorString()).toLocal8Bit();
      sQtException = ba.data();
      return "";
    }
    if (http.bytesAvailable()){
      QByteArray a = http.readAll();
      return QString::fromUtf8(a.data(), a.size());
    }


  }

  return "";
}

QString _application::METHOD_LoadURLAsBinary(QString FileName)
{
  if (FileName.startsWith("http://", Qt::CaseInsensitive)){
    FileName = FileName.mid(QString("http://").length());
  }

  if (FileName.startsWith("file:///", Qt::CaseInsensitive)){
    
    QFile f(FileName);
    bool b = false;

    if (FileName.compare("stderr", Qt::CaseInsensitive) == 0) b = f.open(stderr, QIODevice::ReadOnly);
    else if (FileName.compare("stdin", Qt::CaseInsensitive) == 0) b = f.open(stdin, QIODevice::ReadOnly);
    else if (FileName.compare("stdout", Qt::CaseInsensitive) == 0) b = f.open(stdout, QIODevice::ReadOnly);
    else b = f.open(QIODevice::ReadOnly);

    if (b){
      QByteArray ba = f.readAll();
      QString s = QString::fromLatin1(ba.data(), ba.length());
      f.close();
      return s;
    } else {
      QByteArray ba = QString("Application.LoadURLAsBinary: Could not read from %1").arg(FileName).toLocal8Bit();
      sQtException = ba.data();
    }

    return "";    

  } else {

    int n = FileName.indexOf("/");
    if (n < 0){
      QByteArray ba = QString("Application.LoadURLAsBinary: Invalid URL: %1").arg(FileName).toLocal8Bit();
      sQtException = ba.data();
      return "";
    }
    QString sHost = FileName.left(n);
    QString sPath = FileName.mid(n);

    QHttp http;
    http.setHost(sHost);     
    QUrl url;   
    if (!url.isValid()){
      url.setUrl(sHost + sPath);
    }
    QString q = url.encodedQuery();
    if (!q.isEmpty()){
      q = q.prepend("?");
    }
    QString z = QString(url.encodedPath().mid(sHost.length())) + q;
    http.get(z);

    while(http.currentId() > 0 && http.error() == QHttp::NoError){
      qApp->processEvents();
    }
    if (http.error() != QHttp::NoError){
      QByteArray ba = QString("Application.LoadURLAsBinary: %1").arg(http.errorString()).toLocal8Bit();
      sQtException = ba.data();
      return "";
    }
    if (http.bytesAvailable()){
      QByteArray a = http.readAll();
      return QString::fromLatin1(a.data(), a.length());
    }
  }

  return "";
}

void _application::METHOD_SetDefaultIcon(QString n)
{

  if (n.length() > 200){ // QString contains binary data
    QPixmap p; p.loadFromData(n.toLatin1());
    qApp->setWindowIcon(p);
  } else {
    qApp->setWindowIcon(QIcon(interpreter_loadPixmap(n)));
  }

}

void _application::METHOD_ExternalOpenFile(QString k)
{
  if (!(k.contains("/") || k.contains("\\"))){
    k = qApp->applicationDirPath() + "/" + k;
    
    k = "file:///" + k;

    QDesktopServices::openUrl(QUrl(k));
  } else {
    QDesktopServices::openUrl(QUrl(k));
  }
}

t_boolean _application::METHOD_IsScrollBarsEnabled()
{
  return _mainwindow2::METHOD_IsScrollBarsEnabled();
}

t_boolean _mainwindow2::METHOD_IsScrollBarsEnabled()
{
  if (forms_mainwindow == 0) return false;

  return forms_workspace->horizontalScrollBarPolicy() != Qt::ScrollBarAlwaysOff && forms_workspace->horizontalScrollBarPolicy() != Qt::ScrollBarAlwaysOff;
}
             

#endif




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

#include <QtGui>
#include <QtSql>

#include "_importproject.h"
#include "_mainwindow.h"
#include "_projectwindow.h"
#include "_insert.h"
#include "_typedef.h"

extern QSqlDatabase CurrentDatabase;

extern _projectwindow *EXTERN_my_projectwindow;
extern _mainwindow *EXTERN_my_mainwindow;

_importproject::_importproject(QWidget* _parent) : QDialog(_parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Dialog);

  parent = _parent;


  setWindowTitle(tr("Import..."));
  setModal(true);

 
  setupGeneral();  

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  

  
}
void _importproject::setupGeneral()
{

  QVBoxLayout *j = new QVBoxLayout();
  setLayout(j);

  bool t = false;

  QLabel *l;
  l = new QLabel(tr(
"You can start to work with your VB6 code. \n\nThe VB6 Converter will copy all source codes of your VB6 modules\n and classes in new kbasic modules and kbasic classes "
"(*.kbasic_module and *.kbasic_class).\n\n"
"Menus are not imported, but your forms will be parsed and converted automatically (*.kbasic_form). \n\nIf the VB Converter does not know how to handle something, \nit will ignore it and leave at as it was, so that you have the chance to change it manually.\n\n"
"Please enter the VB6 Source Project Directory and Destination for the new project:"

    )); j->addWidget(l);


  QWidget *d2 = new QWidget(); j->addWidget(d2);
  QHBoxLayout *dl2 = new QHBoxLayout();
  d2->setLayout(dl2);

  l = new QLabel(tr("Enter the VB6\nfolder here."), d2); dl2->addWidget(l);
  
  source2 = new QLineEdit(d2); dl2->addWidget(source2);
  ((QLineEdit *) (source2))->setDisabled(t);

  QPushButton *p;
  p = new QPushButton("...", d2); dl2->addWidget(p);
  p->setMaximumWidth(30);
  p->setDisabled(t);

  connect(p,  SIGNAL( clicked ( ) ), this, SLOT( clicked(  ) ) );

  d2 = new QWidget(); j->addWidget(d2);
  dl2 = new QHBoxLayout();
  d2->setLayout(dl2);
  
  l = new QLabel(tr("New Project Name: "), d2); dl2->addWidget(l);
  l->setMinimumWidth(100);
  
  source = new QLineEdit(d2); dl2->addWidget(source);
  ((QLineEdit *) (source))->setDisabled(t);
  ((QLineEdit *) (source))->setText( "" );
  source->setMinimumWidth(200);

  QWidget *d3 = new QWidget(); j->addWidget(d3);
  QHBoxLayout *dl3 = new QHBoxLayout();
  d3->setLayout(dl3);

  l = new QLabel(tr("Destination Path: "), d3); dl3->addWidget(l);
  l->setMinimumWidth(100);
  
  destination = new QLineEdit(d3); dl3->addWidget(destination);
  ((QLineEdit *) (destination))->setDisabled(t);
  ((QLineEdit *) (destination))->setText( "" );
  destination->setMinimumWidth(200);
  
  
  p = new QPushButton("...", d3); dl3->addWidget(p);
  p->setMaximumWidth(30);
  p->setDisabled(t);

  connect(p,  SIGNAL( clicked ( ) ),  this, SLOT( clicked2(  ) ) );

  QFrame *ff = new QFrame(); ff->setFrameShape(QFrame::HLine); ff->setFrameShadow(QFrame::Sunken); j->addWidget(ff);


  
  QWidget *f = new QWidget(); j->addWidget(f);
  QHBoxLayout *fj = new QHBoxLayout();
  f->setLayout(fj);
    
#ifdef MAC

  p = new QPushButton(tr("&Cancel"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(cancel()) );

  p = new QPushButton(tr("&Start Import"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(ok()) );
#else
  p = new QPushButton(tr("&Start Import"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(ok()) );

  p = new QPushButton(tr("&Cancel"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(cancel()) );
#endif

    
}

void _importproject::ok()
{

  if (source2->text().simplified().isEmpty()){
QMessageBox::information(this, tr("New Project"),
tr(
"Please enter the VB6 project folder first. ")
);
    source2->setFocus();
    return;
  }

  if (destination->text().simplified().isEmpty()){
QMessageBox::information(this, tr("New Project"),
tr(
"Please enter the path for the new project first. ")
);
    destination->setFocus();
    return;
  }

  if (source->text().simplified().isEmpty()){
QMessageBox::information(this, tr("New Project"),
tr(
"Please enter the name for the new project first. ")
);
    source->setFocus();
    return;
  }

  QString s = destination->text() + source->text() + ".kbasic_project";
  if (QFile::exists(s)){
QMessageBox::information(this, tr("New Project"),
tr(
"Project already exists. Please change the project path or name. ")
);
    destination->setFocus();
    return;
  }

  EXTERN_my_mainwindow->createDir(s);

  s = destination->text() + source->text() + ".kbasic_project/" + source->text() + ".kbasic_project";
  s = s.replace("\\", "/");

  EXTERN_my_mainwindow->createFile(s);

  EXTERN_my_mainwindow->loadProject(s);


  EXTERN_my_mainwindow->setProjectPreference("projectmainformname", "Form1");
  EXTERN_my_mainwindow->saveProjectPreferences(); 
   
  QMessageBox::information(this, tr("New Project Created"),
    tr(
  "Now, I'm importing all needed VB6 files...<br>"
  "<br>"
  "WARNING! The import interface is BETA software, therefore some properties of controls might not be imported.<br>"
  )
  );
  

  QDir thisDir( source2->text() );	
  QFileInfoList files = thisDir.entryInfoList();
  
  if ( files.size() ) {
      
     QFileInfo fi;
	    for (int i = 0; i < files.size(); ++i) {
	      fi = files.at(i);

        if (fi.fileName() == "." || fi.fileName() == "..")
		        ; // nothing
		    else if ( fi.isSymLink()) {
		    }
        else if ( fi.isDir() ){
        } else {
          QString s = fi.absoluteFilePath();

          if (s.endsWith(".bas", Qt::CaseInsensitive)){
            importBas(s);
          } else if (s.endsWith(".frm", Qt::CaseInsensitive)){
            importFrm(s);
          } else if (s.endsWith(".vbp", Qt::CaseInsensitive)){
            importVbp(s);
          } else {
          }
        }
      }
  }    

  QMessageBox::information(this, tr("Import finished"),
    tr(
  "All needed VB6 files have been imported.<br>"
  )
  );

  accept();
}

void _importproject::cancel()
{
  close();
}

QString _importproject::geValueFromVbp(QString s, QString sKey)
{
  QString sName = "";
  int n = s.indexOf(sKey, 0, Qt::CaseInsensitive);
  if (n >= 0){
    n = s.indexOf("=", n);
    int n2 = s.indexOf("\n", n);
    sName = s.mid(n + 1, n2 - n);
    sName = sName.simplified();
    sName = sName.replace("\"", "");
  }

  return sName;
}
QString _importproject::geValueFromFrm(QString s, QString sKey)
{
  QString sName = "";
  int n = s.indexOf(sKey, 0, Qt::CaseInsensitive);
  if (n >= 0){
    n = s.indexOf("=", n);
    int n2 = s.indexOf("\n", n);
    sName = s.mid(n + 1, n2 - n);
    sName = sName.simplified();
    sName = sName.replace("\"", "");
  }

  if (sKey.contains("Left")
    || sKey.contains("Top")
  ){
//    sName = "100";
  }

  if (sKey.contains("Height")
    || sKey.contains("Width" )
    || sKey.contains("Left")
    || sKey.contains("Top")
  ){
    sName = sName.left(sName.length() - 1);
  }

  return sName;
}

void _importproject::importVbp(QString sFile)
{
  QProgressDialog progress(tr("Importing VBP...") + sFile, tr("Cancel"), 0, 100, this);

  progress.setValue( 10 ); EXTERN_my_mainwindow->processGUI(100);

  QString s;

  QFile f(sFile);
  if (!f.open(QFile::ReadOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(sFile));
    return;
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    s = t.readAll();
    s = s.replace("\r", "");
    f.close();
  }

  progress.setValue( 60 ); EXTERN_my_mainwindow->processGUI(100);

  EXTERN_my_mainwindow->setProjectPreference("projectname", geValueFromVbp(s, "Name"));
  EXTERN_my_mainwindow->setProjectPreference("projectcompanyname", geValueFromVbp(s, "VersionCompanyName"));
  EXTERN_my_mainwindow->setProjectPreference("projectlicense", geValueFromVbp(s, "Description"));
  EXTERN_my_mainwindow->setProjectPreference("projectmainformname", geValueFromVbp(s, "Startup"));
  EXTERN_my_mainwindow->setProjectPreference("projectcontactemail", geValueFromVbp(s, "VersionLegalCopyright"));
  EXTERN_my_mainwindow->setProjectPreference("projectwebsite", geValueFromVbp(s, "VersionComments"));
    progress.setValue( 100 ); EXTERN_my_mainwindow->processGUI(100);
}

void _importproject::putFormKeyString(QString *sText, QString sKey, QString sValue, bool bIdent)
{
  putFormKey(sText, sKey, sValue, bIdent, true);
}

void _importproject::putFormKey(QString *sText, QString sKey, QString sValue, bool bIdent, bool bString)
{
  if (sValue.length() == 0) return;
  *sText += "  ";
  if (bIdent) *sText += "  ";
  *sText += sKey;
  *sText += " = ";
  if (bString) *sText += "\"";
  *sText += sValue;
  if (bString) *sText += "\"";
  *sText += "\n";
}

void _importproject::importFrm(QString sFile)
{
  QProgressDialog progress(tr("Importing FRM...") + sFile, tr("Cancel"), 0, 100, this);
  progress.setValue( 10 ); EXTERN_my_mainwindow->processGUI(100);

  QString s;
  QString s2;

  QFile f(sFile);
  if (!f.open(QFile::ReadOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(sFile));
    return;
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    s = t.readAll();
    s2 = s = s.replace("\r", "");
    f.close();
  }

  progress.setValue( 50 ); EXTERN_my_mainwindow->processGUI(100);
  QString sName = "";
  int n = s.indexOf("Attribute VB_Name", 0, Qt::CaseInsensitive);
  QString sForm = s.left(n);
  QString sFormNew = "";

  n = s.indexOf("=", n);
  int n2 = s.indexOf("\n", n);
  sName = s.mid(n + 1, n2 - n);
  sName = sName.simplified();
  sName = sName.replace("\"", "");

  n = s2.lastIndexOf("Attribute VB", -1, Qt::CaseInsensitive); // skip all attributes
  n2 = s2.indexOf("\n", n);
  QString sCode = s2.mid(n2);

  sCode.replace(" As Integer", " As Short/*Integer*/", Qt::CaseInsensitive);
  sCode.replace(" As Long", " As Integer/*Long*/", Qt::CaseInsensitive);

  sCode.replace("_Click()", "_OnClick/*_Click*/(X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean)", Qt::CaseInsensitive);
  sCode.replace("_DblClick()", "_OnDblClick/*_DblClick*/(X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean)", Qt::CaseInsensitive);
  sCode.replace("_Timer(", "_OnEvent/*_Timer*/(", Qt::CaseInsensitive);

  sCode.replace("_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)", "_OnMouseDown/*_MouseDown*/(X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean)", Qt::CaseInsensitive);
  sCode.replace("_KeyDown(KeyCode As Integer, Shift As Integer)", "_OnKeyDown/*KeyDown*/(KeyCode As Integer, Shift As Boolean, Control As Boolean, Alt As Boolean)", Qt::CaseInsensitive);
  sCode.replace("_KeyPress(KeyAscii As Integer)", "_OnKeyPress/*KeyPress*/(KeyCode As Integer, Shift As Boolean, Control As Boolean, Alt As Boolean)", Qt::CaseInsensitive);
  
  
  

  

  sCode.replace("Form_Load(", "Form_OnOpen/*Form_Load*/(", Qt::CaseInsensitive);
  sCode.replace("Unload Me", "Close/*Unload Me*/", Qt::CaseInsensitive);
  sCode.replace("Form_Unload(Cancel As Integer)", "Form_OnClose/*Form_Unload*/(ByRef Cancel As Boolean)", Qt::CaseInsensitive);  

  sCode.replace(".AddItem", ".Append/*AddItem*/", Qt::CaseInsensitive);
  sCode.replace(".Clear", ".RemoveAll/*Clear*/", Qt::CaseInsensitive);
  //sCode.replace(".Navigate", ".HomeURL/*Navigate*/ = ", Qt::CaseInsensitive);
  sCode.replace(".ListCount", ".Len/*ListCount*/", Qt::CaseInsensitive);
  sCode.replace("App.Path", "Application.DirectoryName/*App.Path*/", Qt::CaseInsensitive);

  sCode.replace(" Set ", " /* Set */", Qt::CaseInsensitive);
  sCode.replace("Me.Print", "Print/*Me.Print*/", Qt::CaseInsensitive);
  sCode.replace("Debug.Print", "Print/*Debug.Print*/", Qt::CaseInsensitive);
  sCode.replace(".ForeColor", ".FontColor/*ForeColor*/", Qt::CaseInsensitive);
  sCode.replace("KeyAscii", "KeyCode/*KeyAscii*/", Qt::CaseInsensitive);

  

  


  
  

  sCode.replace("vbAbort", "kbAbort", Qt::CaseInsensitive);
  sCode.replace("vbAbortRetryIgnore", "kbAbortRetryIgnore", Qt::CaseInsensitive);
  sCode.replace("vbArchive", "kbArchive", Qt::CaseInsensitive);
  sCode.replace("vbArray", "kbArray", Qt::CaseInsensitive);
  sCode.replace("vbBack", "kbBack", Qt::CaseInsensitive);
  sCode.replace("vbBoolean", "kbBoolean", Qt::CaseInsensitive);
  sCode.replace("vbByte", "kbByte", Qt::CaseInsensitive);
  sCode.replace("vbCancel", "kbCancel", Qt::CaseInsensitive);
  sCode.replace("vbCr", "kbCr", Qt::CaseInsensitive);
  sCode.replace("vbCrLf", "kbCrLf", Qt::CaseInsensitive);
  sCode.replace("vbCritical", "kbCritical", Qt::CaseInsensitive);
  sCode.replace("vbCurrency", "kbCurrency", Qt::CaseInsensitive);
  sCode.replace("vbDate", "kbDate", Qt::CaseInsensitive);
  sCode.replace("vbDefaultButton1", "kbDefaultButton1", Qt::CaseInsensitive);
  sCode.replace("vbDefaultButton2", "kbDefaultButton2", Qt::CaseInsensitive);
  sCode.replace("vbDefaultButton3", "kbDefaultButton3", Qt::CaseInsensitive);
  sCode.replace("vbDirectory", "kbDirectory", Qt::CaseInsensitive);
  sCode.replace("vbDouble", "kbDouble", Qt::CaseInsensitive);
  sCode.replace("vbEmpty", "kbEmpty", Qt::CaseInsensitive);
  sCode.replace("vbError", "kbError", Qt::CaseInsensitive);
  sCode.replace("vbExclamation", "kbExclamation", Qt::CaseInsensitive);
  sCode.replace("vbFriday", "kbFriday", Qt::CaseInsensitive);
  sCode.replace("vbHidden", "kbHidden", Qt::CaseInsensitive);
  sCode.replace("vbIgnore", "kbIgnore", Qt::CaseInsensitive);
  sCode.replace("vbInformation", "kbInformation", Qt::CaseInsensitive);
  sCode.replace("vbInteger", "kbInteger", Qt::CaseInsensitive);
  sCode.replace("vbLf", "kbLf", Qt::CaseInsensitive);
  sCode.replace("vbLong", "kbLong", Qt::CaseInsensitive);
  sCode.replace("vbMonday", "kbMonday", Qt::CaseInsensitive);
  sCode.replace("vbNewLine", "kbNewLine", Qt::CaseInsensitive);
  sCode.replace("vbNo", "kbNo", Qt::CaseInsensitive);
  sCode.replace("vbNormal", "kbNormal", Qt::CaseInsensitive);
  sCode.replace("vbNull", "kbNull", Qt::CaseInsensitive);
  sCode.replace("vbNullChar", "kbNullChar", Qt::CaseInsensitive);
  sCode.replace("vbNullString", "kbNullString", Qt::CaseInsensitive);
  sCode.replace("vbOK", "kbOK", Qt::CaseInsensitive);
  sCode.replace("vbOKCancel", "kbOKCancel", Qt::CaseInsensitive);
  sCode.replace("vbOKOnly", "kbOKOnly", Qt::CaseInsensitive);
  sCode.replace("vbObject", "kbObject", Qt::CaseInsensitive);
  sCode.replace("vbQuestion", "kbQuestion", Qt::CaseInsensitive);
  sCode.replace("vbReadOnly", "kbReadOnly", Qt::CaseInsensitive);
  sCode.replace("vbRetry", "kbRetry", Qt::CaseInsensitive);
  sCode.replace("vbRetryCancel", "kbRetryCancel", Qt::CaseInsensitive);
  sCode.replace("vbSaturday", "kbSaturday", Qt::CaseInsensitive);
  sCode.replace("vbShort", "kbShort", Qt::CaseInsensitive);
  sCode.replace("vbSingle", "kbSingle", Qt::CaseInsensitive);
  sCode.replace("vbString", "kbString", Qt::CaseInsensitive);
  sCode.replace("vbSunday", "kbSunday", Qt::CaseInsensitive);
  sCode.replace("vbSystem", "kbSystem", Qt::CaseInsensitive);
  sCode.replace("vbTab", "kbTab", Qt::CaseInsensitive);
  sCode.replace("vbThursday", "kbThursday", Qt::CaseInsensitive);
  sCode.replace("vbTuesday", "kbTuesday", Qt::CaseInsensitive);
  sCode.replace("vbUseSystem", "kbUseSystem", Qt::CaseInsensitive);
  sCode.replace("vbVariant", "kbVariant", Qt::CaseInsensitive);
  sCode.replace("vbVolume", "kbVolume", Qt::CaseInsensitive);
  sCode.replace("vbWednesday", "kbWednesday", Qt::CaseInsensitive);
  sCode.replace("vbYes", "kbYes", Qt::CaseInsensitive);
  sCode.replace("vbYesNo", "kbYesNo", Qt::CaseInsensitive);
  sCode.replace("vbYesNoCancel", "kbYesNoCancel", Qt::CaseInsensitive);



  sFormNew = "Begin Form ";
  sFormNew += sName;
  sFormNew += "\n";

  
  putFormKey(&sFormNew, "Height", geValueFromFrm(sForm, "ClientHeight"), false);
  putFormKey(&sFormNew, "Width", geValueFromFrm(sForm, "ClientWidth"), false);
  putFormKey(&sFormNew, "X", geValueFromFrm(sForm, "ClientLeft"), false);
  putFormKey(&sFormNew, "Y", geValueFromFrm(sForm, "ClientTop"), false);
  putFormKeyString(&sFormNew, "Caption", geValueFromFrm(sForm, "Caption"), false);
 // putFormKeyString(&sFormNew, "Background", geValueFromFrm(sForm, "Background"), false);

  sFormNew += "\n";
  sFormNew += "\n";

  int nBegin = sForm.indexOf("Begin ", 0, Qt::CaseInsensitive) + 1; 
  int nBegin2 = 0; 
  int nEnd = 0; 
  int nEOL = 0; 
  QString sControlName = "";
  QString sControlType = "";
  QString sTmp = "";
  QString sHeadline = "";

  bool bInside = false;
  int ii = 0;

  while (true){

    sControlName = "";
    sControlType = "";

    if (bInside){ // test for end of control if got controls inside
      nBegin = sForm.indexOf("Begin ", nBegin, Qt::CaseInsensitive); 
      nEnd = sForm.indexOf("End\n", nBegin, Qt::CaseInsensitive); 

      if (nEnd < nBegin){
        //sFormNew += "End\n";
        //sFormNew += "\n";
        nBegin = nEnd + 1; bInside = false;
        continue;
      }
              
  
    }
    nBegin = sForm.indexOf("Begin ", nBegin, Qt::CaseInsensitive); 
    if (nBegin == -1) break;
    nBegin++;
    nBegin2 = sForm.indexOf("Begin ", nBegin, Qt::CaseInsensitive);     
    nEnd = sForm.indexOf("End\n", nBegin, Qt::CaseInsensitive); 

    if (nBegin2 < nEnd){ // iterate
      bInside = true;
    } 

    {
      sTmp = sForm.mid(nBegin, nEnd - nBegin);

      nEOL = sTmp.indexOf("\n", 0); 

      ii++;
      sHeadline = sTmp.left(nEOL);
      sHeadline = sHeadline.simplified();
      nEOL = sHeadline.indexOf(" ", 0); 
      nEOL = sHeadline.indexOf(" ", nEOL + 1); 

      if (nEOL >= 0){
        sControlName = sHeadline.mid(nEOL);
        sControlName = sControlName.simplified();
      } else {
        sControlName = "ctrl";
        sControlName += QString("%1").arg(ii);
      }

      // CONTROL
      if (sHeadline.contains("CommandButton")) sControlType = "CommandButton";
      else if (sHeadline.contains("ToolButton")) sControlType = "ToolButton";
      else if (sHeadline.contains("RichTextBox")) sControlType = "RichTextBox";
      else if (sHeadline.contains("Frame")) sControlType = "Frame";
      else if (sHeadline.contains("TextBox")) sControlType = "TextBox";
      else if (sHeadline.contains("Label")) sControlType = "Label";
      else if (sHeadline.contains("OptionButton")) sControlType = "RadioButton";
      else if (sHeadline.contains("Image")) sControlType = "ImageBox";
      else if (sHeadline.contains("Timer")) sControlType = "Timer";
      else if (sHeadline.contains("ComboBox")) sControlType = "ComboBox";
      else if (sHeadline.contains("CheckBox")) sControlType = "CheckBox";
      else if (sHeadline.contains("ListBox")) sControlType = "ListBox";
       
      else {
        // skip unknown controls
        nBegin++;
        continue;
      }
      nBegin++;

      sFormNew += "  Begin ";
      sFormNew += sControlType;
      sFormNew += " ";
      sFormNew += sControlName;
      sFormNew += "\n";

      

      putFormKey(&sFormNew, "Height", geValueFromFrm(sTmp, "Height"));
      putFormKey(&sFormNew, "Width", geValueFromFrm(sTmp, "Width"));
      putFormKey(&sFormNew, "X", geValueFromFrm(sTmp, "Left"));
      putFormKey(&sFormNew, "Y", geValueFromFrm(sTmp, "Top"));

      putFormKeyString(&sFormNew, "Value", geValueFromFrm(sTmp, "Text"));
      putFormKeyString(&sFormNew, "ToolTip", geValueFromFrm(sTmp, "ToolTipText"));
      putFormKey(&sFormNew, "FocusOrder", geValueFromFrm(sTmp, "TabIndex"));
      //putFormKey(&sFormNew, "Visible", geValueFromFrm(sTmp, "Visible"));
      QString s = "";
      s = geValueFromFrm(sTmp, "BackColor"); if (s.endsWith("&")) s = s.left(s.length() - 1);
      putFormKeyString(&sFormNew, "Background", s);

      s = geValueFromFrm(sTmp, "ForeColor"); if (s.endsWith("&")) s = s.left(s.length() - 1);
      putFormKeyString(&sFormNew, "FontColor", s);
             
              
           


/*
      if (sControlType.contains("LabeL")
        || sControlType.contains("CommandButton" )
        || sControlType.contains("RadioButton")
        || sControlType.contains("CheckBox")
      ){
        putFormKeyString(&sFormNew, "Caption", geValueFromFrm(sTmp, "Caption"), true);
      }*/

      putFormKeyString(&sFormNew, "Caption", geValueFromFrm(sTmp, "Caption"), true);

      //if (bInside == false)
      {
        sFormNew += "  End\n";
        sFormNew += "\n";
      }
          
    }

  }

  sFormNew += "End Form\n";
  sFormNew += "\n";





/*
  
  sCode.prepend(""
" Inherits Form\n"
"' ------------------------------------------------------------------------\n\n"
""
);

  sCode.prepend(sName);

sCode.prepend(
"Class "
);

  sCode.append(""
"' ------------------------------------------------------------------------\n\n"
"End Class"
""
);*/
  progress.setValue( 60 ); EXTERN_my_mainwindow->processGUI(100);

  QString m = "";
  m = EXTERN_my_mainwindow->getProjectPath();
  m += "/";
  m += sName;
  m += ".kbasic_form";
  EXTERN_my_mainwindow->createFile(m);
  
  progress.setValue( 70 ); EXTERN_my_mainwindow->processGUI(100);

  QFile f2(m);
  if (!f2.open(QFile::WriteOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(sFile));
    return;
  } else {
    QTextStream t(&f2);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << sFormNew;
    t << sCode;
    f2.close();
  }

  progress.setValue( 100 ); EXTERN_my_mainwindow->processGUI(100);
  EXTERN_my_projectwindow->refresh();
}

void _importproject::importBas(QString sFile)
{
  QProgressDialog progress(tr("Importing BAS...") + sFile, tr("Cancel"), 0, 100, this);
  progress.setValue( 10 ); EXTERN_my_mainwindow->processGUI(100);

  QString s;
  QString s2;

  QFile f(sFile);
  if (!f.open(QFile::ReadOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(sFile));
    return;
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    s = t.readAll();
    s2 = s = s.replace("\r", "");
    f.close();
  }

  progress.setValue( 50 ); EXTERN_my_mainwindow->processGUI(100);


  QString sName = "";
  int n = s.indexOf("Attribute VB_Name", 0, Qt::CaseInsensitive);
  n = s.indexOf("=", n);
  int n2 = s.indexOf("\n", n);
  sName = s.mid(n + 1, n2 - n);
  sName = sName.simplified();
  sName = sName.replace("\"", "");

  n = s2.lastIndexOf("Attribute VB", -1, Qt::CaseInsensitive); // skip all attributes
  n2 = s2.indexOf("\n", n);

  s = s2.mid(n2);

  progress.setValue( 60 ); EXTERN_my_mainwindow->processGUI(100);

  QString m = "";
  if (s.contains("class_initialize", Qt::CaseInsensitive)){
    m = EXTERN_my_mainwindow->getProjectPath();
    m += "/";
    m += sName;
    m += ".kbasic_class";

    EXTERN_my_mainwindow->insertClass(m);
  } else {
    m = EXTERN_my_mainwindow->getProjectPath();
    m += "/";
    m += sName;
    m += ".kbasic_module";

    EXTERN_my_mainwindow->createFile(m);
  }
  
  progress.setValue( 70 ); EXTERN_my_mainwindow->processGUI(100);

  QFile f2(m);
  if (!f2.open(QFile::WriteOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(sFile));
    return;
  } else {
    QTextStream t(&f2);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << s;
    f2.close();
  }

  progress.setValue( 100 ); EXTERN_my_mainwindow->processGUI(100);
  EXTERN_my_projectwindow->refresh();

}


void _importproject::clicked()
{
     
  QString fn = QFileDialog::getExistingDirectory(this);

  if (!fn.isEmpty()){
    ((QLineEdit *) (source2))->setText(fn + "/");
  }  
}

void _importproject::clicked2()
{
     
  QString fn = QFileDialog::getExistingDirectory(this);

  if (!fn.isEmpty()){
    ((QLineEdit *) (destination))->setText(fn + "/");
  }  
}

int columncount = 0;
int rowcount = 0;
bool bWithTitle = true;

void _importproject::importCSV(QString sFile)
{
  bool bComma = false;
  bWithTitle = false;

  QString s = "";
  QFile f(sFile);
  if (!f.open(QFile::ReadOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(sFile));
    return;
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    s = t.readAll();
    s = s.replace("\r", "");
    f.close();
  }


  QMessageBox msgBox(this);
  msgBox.setWindowTitle(MYAPP);
  QPushButton *Comma = msgBox.addButton(tr("Comma"), QMessageBox::ActionRole);
  QPushButton *Semicolon = msgBox.addButton(tr("Semicolon"), QMessageBox::ActionRole);

  msgBox.setText(tr("What delemitor separates your fields?"));
  msgBox.exec();

  if (msgBox.clickedButton() == Semicolon) {
  } else if (msgBox.clickedButton() == Comma) {
    bComma = true;
  }

  if (QMessageBox::question(this, MYAPP, tr("First row contains field names?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
    bWithTitle = true;
  }


   bool bSQLite = false;
   bool bMySQL = false;
   if (CurrentDatabase.driverName().contains("sqlite", Qt::CaseInsensitive)){
     bSQLite = true;
   } else if (CurrentDatabase.driverName().contains("mysql", Qt::CaseInsensitive)){
     bMySQL = true;
   }

  columncount = 0;
  rowcount = 0;

   int nLen = s.length();

   QChar cc = bComma ? ',' : ';';
   QStringList l;
   QStringList header;
/*
1997,Ford,E350,"ac, abs, moon",3000.00
1999,Chevy,"Venture ""Extended Edition""",,4900.00
1996,Jeep,Grand Cherokee,"MUST SELL!
air, moon roof, loaded",4799.00
*/

   QString sTable = EXTERN_my_mainwindow->getFilenameWithoutPathAndExtension(sFile);

   int n = 0;
   QString a = sTable;
   while (EXTERN_my_mainwindow->existsTableFile(sTable)){
     sTable = a + QString("%1").arg(++n);
   }

   QProgressDialog progress(tr("Importing CSV...") + sTable, tr("Cancel"), 0, 100, this);
   

   for (int i = 0; i < 2; i++){
we:
     if (i == 1){
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        QString x = "CREATE TABLE " + sTable + " (\n";
        foreach(QString k, header){
          x += k;
          x += " text, ";          
        }
        if (x.contains("kbrecordid text", Qt::CaseInsensitive)){
          x = x.left(x.length() - 1);
          x = x.replace("kbrecordid text", "\nkbrecordid int NOT NULL,\nCONSTRAINT " + sTable + "_kbrecordid PRIMARY KEY (kbrecordid)\n);", Qt::CaseInsensitive);
        } else {
          x += "\nkbrecordid int NOT NULL,\nCONSTRAINT " + sTable + "_kbrecordid PRIMARY KEY (kbrecordid)\n);";
        }

        QSqlQuery r;
        if (!r.exec(x)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + x + "\n\n" + r.lastError().text()); EXTERN_my_projectwindow->refresh(); return; }

        if (bSQLite){
          x = "CREATE INDEX " + sTable + "_idx_kbrecordid ON " + sTable + " (kbrecordid);";
        } else if (bMySQL){
          x = "CREATE INDEX " + sTable + "_idx_kbrecordid USING btree ON " + sTable + " (kbrecordid);";
        } else {
          x = "CREATE INDEX " + sTable + "_idx_kbrecordid ON " + sTable + " USING btree (kbrecordid);";
        }
        if (!r.exec(x)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + x + "\n\n" + r.lastError().text()); EXTERN_my_projectwindow->refresh(); return; }

        QString q = "Begin Table *\n";     

        foreach(QString k, header){
          q += "  Begin TableItem ";
          q += k;
          q += "\n";
          q += "  Type = \"String\"\n";
          q += "  End\n\n";
          
        }

        q += "End Table\n"; 

        EXTERN_my_mainwindow->insertTable(sTable, q);
        QApplication::restoreOverrideCursor();

        l.clear();        

     }

    int index = 0;
    int index2 = 0;
    // int nString = 0;
    bool bString = false;
    bool bString2 = false;
    int nString = 0;

    QChar c;
    QChar c2;
    //QString k;
    while (index2 <= nLen){

      if (i == 1){
        progress.setValue( (index2 * 100) / nLen ); EXTERN_my_mainwindow->processGUI(100);
        if (progress.wasCanceled()){
          EXTERN_my_projectwindow->refresh();
          return;
        }
      }

      if (index2 == nLen) goto re;

      c = s.at(index2);
      c2 = index2 + 1 < nLen ? s.at(index2 + 1) : 0;
      //k = s.mid(index2);

      if (c == '\"'){

        if (c2 != '\"'){
          bString = !bString;
        } else index2++;

      } else if (!bString && c == cc){
        QString ss = s.mid(index, index2 - index);
        ss = ss.replace("\"\"", "\"");
        if (ss.startsWith("\"")) ss = ss.mid(1);
        if (ss.endsWith("\"")) ss = ss.left(ss.length() - 1);
        //ss = ss.replace("\d", "");

        l.append(ss);
        index = index2 + 1;
      } else if (!bString && c == '\n'){
  re:
        QString ss = s.mid(index, index2 - index - 1);
        ss = ss.replace("\"\"", "\"");
        if (ss.startsWith("\"")) ss = ss.mid(1);
        if (ss.endsWith("\"")) ss = ss.left(ss.length() - 1);

        l.append(ss);
        index = index2 + 1;

        if (i == 0){
          columncount = l.count();

          if (bWithTitle){
            header = l;
          } else {
            for (int y = 0; y < columncount; y++){
              header.append("field" + QString("%1").arg(y + 1));
            }
          }

          i++;
          goto we;
        }

        if (rowcount == 0 && bWithTitle){
          
          // ignore first row witht titles
        } else if (!insertCSV(sTable, header, l)){
          EXTERN_my_projectwindow->refresh();
          return;
        }

        l.clear();
        rowcount++;

      }
      index2++;
    }
    

   } 

   EXTERN_my_projectwindow->refresh();
   
   QMessageBox::information(this, tr("Import finished"),
    tr(
  "All needed data rows have been imported.<br>"
  )
  );
}

bool _importproject::insertCSV(QString & sTable, QStringList &header, QStringList &l)
{
  
  
  QString s = "";
  QString fields = "";
  QString values = "";

  bool b = true;
  foreach(QString k, l){
    if (!b){
      values += ", ";
    }
    if (b) b = false;
    if (k.isEmpty()){
      values += "NULL";
    } else {
      values += "'";
      values += k;
      values += "'";
    }
  }

  if (values == "NULL") return true; // ommit empty line

  b = true;
  foreach(QString k, header){
    if (!b){
      fields += ", ";
    }
    if (b) b = false;
    fields += k;
  }
  
  QString x = "";
  
  if (fields.contains("kbrecordid", Qt::CaseInsensitive)){
    x = "INSERT INTO " + sTable + "(" + fields + ") VALUES (" + values + ")";
  } else {
    x = "INSERT INTO " + sTable + "(" + fields + ", kbrecordid) VALUES (" + values + ", " + QString("%1").arg(bWithTitle ? rowcount : rowcount + 1) + ")";
  }
  
  QSqlQuery r;
  if (!r.exec(x)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + x + "\n\n" + r.lastError().text()); return false; }

  
  return true;



}
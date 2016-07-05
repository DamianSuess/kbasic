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

#include "_mainwindow.h"
#include "_compileproject.h"
#include "../kbshared/define.h"

extern QSqlDatabase CurrentDatabase;

extern _mainwindow *EXTERN_my_mainwindow;

extern QString runPath(QString s);
extern QString cachePath(QString s);

#ifdef MAC
extern QString contentsPath(QString s); // HIDE
#endif

QString sDestination = "";

_compileproject::_compileproject(QWidget* _parent, bool _bWindows, bool _bLinux, bool _bMac) : QDialog(_parent)
{
  bWindows = _bWindows;
  bLinux = _bLinux;
  bMac = _bMac;

  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Dialog);

  parent = _parent;
  my_mainwindow = (_mainwindow *) parent;


  setWindowTitle(tr("Make Runtime"));
  setModal(true);

  setupGeneral();  

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

  
}

void _compileproject::setupGeneral()
{


    

    QVBoxLayout *j = new QVBoxLayout();
    setLayout(j);

    bool t = false;


    QWidget *d2 = new QWidget(); j->addWidget(d2);
    QHBoxLayout *dl2 = new QHBoxLayout();
    d2->setLayout(dl2);

    QLabel *l;
    l = new QLabel(tr("Deployment Name: "), d2); dl2->addWidget(l);
    l->setMinimumWidth(70);
    
    source = new QLineEdit(d2); dl2->addWidget(source);
    ((QLineEdit *) (source))->setDisabled(t);
    ((QLineEdit *) (source))->setText( "" );
    source->setMinimumWidth(200);

    QString s = EXTERN_my_mainwindow->getProjectPreference("projectname");

    if (bWindows){
      if (s.isEmpty()) source->setText("test");
      else source->setText(s);
    } else {
      if (s.isEmpty()) source->setText("test");
      else source->setText(s);
    }

    QWidget *d3 = new QWidget(); j->addWidget(d3);
    QHBoxLayout *dl3 = new QHBoxLayout();
    d3->setLayout(dl3);

    l = new QLabel(tr("Path: "), d3); dl3->addWidget(l);
    l->setMinimumWidth(70);

    
    
    destination = new QLineEdit(d3); dl3->addWidget(destination);
    ((QLineEdit *) (destination))->setDisabled(t);
    ((QLineEdit *) (destination))->setText( "" );
    destination->setMinimumWidth(200);

    if (bWindows){
       destination->setText(QDir::homePath() + "/Desktop");
    } else if (bMac){ 
       destination->setText(QDir::homePath() + "/Desktop");
    } else {
       destination->setText(QDir::homePath());
    }

    if (!sDestination.isEmpty()){
      destination->setText(sDestination);
    }
    
    QPushButton *p;
    p = new QPushButton("...", d3); dl3->addWidget(p);
    p->setMaximumWidth(30);
    p->setDisabled(t);

    connect(p,  SIGNAL( clicked ( ) ),  this, SLOT( clicked2(  ) ) );


  pcodeinclude = new QCheckBox(tr("Separate runtime and pcode")); j->addWidget(pcodeinclude);


  QFrame *ff = new QFrame(); ff->setFrameShape(QFrame::HLine); ff->setFrameShadow(QFrame::Sunken); j->addWidget(ff);

    
    QWidget *f = new QWidget(); j->addWidget(f);
    QHBoxLayout *fj = new QHBoxLayout();
    f->setLayout(fj);
#ifdef MAC

    p = new QPushButton(tr("&Cancel"), f); fj->addWidget(p);
    connect(p, SIGNAL( clicked() ), this, SLOT(cancel()) );

    p = new QPushButton(tr("&Compile && Create"), f); fj->addWidget(p);
    connect(p, SIGNAL( clicked() ), this, SLOT(ok()) );

    
#else
    p = new QPushButton(tr("&Compile && Create"), f); fj->addWidget(p);
    connect(p, SIGNAL( clicked() ), this, SLOT(ok()) );

    p = new QPushButton(tr("&Cancel"), f); fj->addWidget(p);
    connect(p, SIGNAL( clicked() ), this, SLOT(cancel()) );

    
#endif

}

QString _compileproject::getPath()
{
  return destination->text();
}

QString _compileproject::getName()
{
  return source->text();
}

void _compileproject::ok()
{
  sDestination = destination->text();
  compile();
}

void _compileproject::cancel()
{
  close();
}

void _compileproject::clicked2()
{     
  QString fn = QFileDialog::getExistingDirectory(this);

  if (!fn.isEmpty()){
    if (!fn.endsWith("/") && !fn.endsWith("\\")) fn += "/";
    ((QLineEdit *) (destination))->setText(fn );
  }  
}

void _compileproject::compile()
{  

    QDir d;

    QString s = getPath();
    if (!s.endsWith("/") && !s.endsWith("\\")){
      s += "/";
    }
    s += getName();


    if (d.exists(s)){
      if (QMessageBox::question(EXTERN_my_mainwindow, tr("Compile Project"),
        tr(
      "Destination directory already exists. Overwrite all files? "), QMessageBox::Ok | QMessageBox::Cancel      
      ) == QMessageBox::Cancel) return;
    }
	

    if (!d.mkpath(s)){
      QMessageBox::information(EXTERN_my_mainwindow, tr("Compile Project"),
        tr(
      "Destination directory could not be created.")); return;
    } else {

      if (bWindows){
        s += "/windows";
      }
      if (bLinux){
        s += "/linux";
      }
      if (bMac){
        s += "/mac";
      }
      d.mkpath(s);
	  
    }


  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  if (EXTERN_my_mainwindow->runRun(true, false, false, true, false, true))
  {

       QString s = getPath();

       if (!s.endsWith("/") && !s.endsWith("\\")){
         s += "/";
       }

       s += getName();
      if (bWindows){
       s += "/windows/";
      }
      if (bLinux){
       s += "/linux/";
      }
      if (bMac){
       s += "/mac/";
      }
       QString k = s;
       s += getName();

if (bWindows){
       s += ".exe";
}
        
  bool bSQLite = false;
  QString q = "";
  QString z = "";
  QString ss = EXTERN_my_mainwindow->getProjectPreference("dbdriver");
  if (!ss.isEmpty()){
    
    if (CurrentDatabase.driverName().contains("sqlite", Qt::CaseInsensitive)){
      bSQLite = true;
    }
    
    if (bSQLite){
      if (q.startsWith("./")){
        z = q.mid(1);
        q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + q.mid(2);
      } else if (q.startsWith("../")){
        z = q.mid(2);
        q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + q.mid(3);
      } else {
        q = ""; // absolute sqlite files are not copied
      }

      //q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectPreference("dbname");
//      q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + "/sqlite/" + EXTERN_my_mainwindow->getProjectPreference("dbname");
    }
  }

       bool b = true;
if (bWindows){

       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("kbrun.exe"), s);//runtime_windows // HIDE

       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("msvcr90.dll"), k + "/msvcr90.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("msvcp90.dll"), k + "/msvcp90.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("msvcm90.dll"), k + "/msvcm90.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("Microsoft.VC90.CRT.manifest"), k + "/Microsoft.VC90.CRT.manifest");//runtime_windows // HIDE

       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("phonon4.dll"), k + "/phonon4.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("QtWebKit4.dll"), k + "/QtWebKit4.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("QtCore4.dll"), k + "/QtCore4.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("QtGui4.dll"), k + "/QtGui4.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("QtNetwork4.dll"), k + "/QtNetwork4.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("QtOpenGL4.dll"), k + "/QtOpenGL4.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("QtSql4.dll"), k + "/QtSql4.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("QtSvg4.dll"), k + "/QtSvg4.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("QtXml4.dll"), k + "/QtXml4.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("QtXmlPatterns4.dll"), k + "/QtXmlPatterns4.dll");//runtime_windows // HIDE

       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("libmySQL.dll"), k + "/libmySQL.dll");//runtime_windows // HIDE

       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("ssleay32.dll"), k + "/ssleay32.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("comerr32.dll"), k + "/comerr32.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("krb5_32.dll"), k + "/krb5_32.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("libeay32.dll"), k + "/libeay32.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("libintl-2.dll"), k + "/libintl-2.dll");//runtime_windows // HIDE
       if (b) b = EXTERN_my_mainwindow->copyFile(runPath("libiconv-2.dll"), k + "/libiconv-2.dll");//runtime_windows // HIDE

       if (b) b = EXTERN_my_mainwindow->copyDir(runPath("plugins"), k + "/plugins");//runtime_windows // HIDE

       if (!q.isEmpty()){ // HIDE
         if (b) b = EXTERN_my_mainwindow->createDir(k + EXTERN_my_mainwindow->getFilenamePath(z));//runtime_windows // HIDE
         if (b) b = EXTERN_my_mainwindow->copyFile(q, k + z);//runtime_windows // HIDE
    //     if (b) b = EXTERN_my_mainwindow->createDir(k + "/sqlite");//runtime_windows // HIDE
//         if (b) b = EXTERN_my_mainwindow->copyFile(q, k + "/sqlite/" + EXTERN_my_mainwindow->getProjectPreference("dbname"));//runtime_windows // HIDE
       } // HIDE

       
}
if (bLinux){
       b = EXTERN_my_mainwindow->copyFile(runPath("kbrun"), s);

       if (!q.isEmpty()){
         if (b) b = EXTERN_my_mainwindow->createDir(s + EXTERN_my_mainwindow->getFilenamePath(z));
         if (b) b = EXTERN_my_mainwindow->copyFile(q, s + z);
       }
}
if (bMac){
#ifdef MAC
      s = s + ".app"; // HIDE
	 if (b) b = EXTERN_my_mainwindow->createDir(s); // HIDE
	  
	  s = s + "/Contents"; // HIDE
      if (b) b = EXTERN_my_mainwindow->createDir(s); // HIDE
	  
      if (b) b = EXTERN_my_mainwindow->copyDir(contentsPath("Frameworks"), s + "/Frameworks"); // HIDE
      if (b) b = EXTERN_my_mainwindow->copyDir(contentsPath("Resources"), s + "/Resources"); // HIDE
	
	  QString z = ""; 
	  z += ""\
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"\
"<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n"\
"<plist version=\"1.0\">\n"\
"<dict>\n"\
"	<key>CFBundleExecutable</key>\n"\
"	<string>" + getName() + "</string>\n"\
"	<key>CFBundleGetInfoString</key>\n"\
"	<string>Created by " + MYAPP + "</string>\n"\
"	<key>CFBundlePackageType</key>\n"\
"	<string>APPL</string>\n"\
"	<key>CFBundleSignature</key>\n"\
"	<string>????</string>\n"\
"	<key>CFBundleName</key>\n"\
"	<string>" + getName() + "</string>\n"\
"	<key>CFBundleIconFile</key>\n"\
"	<string>KBMainIcon</string>\n"\
"</dict>\n"\
"</plist>\n";
	  b = EXTERN_my_mainwindow->createFile(s + "/Info.plist", z); // HIDE

	  b = EXTERN_my_mainwindow->copyFile(contentsPath("PkgInfo"), s + "/PkgInfo"); // HIDE


	  QString ss;
	  ss = s + "/MacOS";
      if (b) b = EXTERN_my_mainwindow->createDir(ss); // HIDE
	
	  if (b) b = EXTERN_my_mainwindow->copyDir(runPath("plugins/codecs"), ss + "/plugins/codecs"); // HIDE
	  if (b) b = EXTERN_my_mainwindow->copyDir(runPath("plugins/iconengines"), ss + "/plugins/iconengines"); // HIDE
	  if (b) b = EXTERN_my_mainwindow->copyDir(runPath("plugins/imageformats"), ss + "/plugins/imageformats"); // HIDE
	  if (b) b = EXTERN_my_mainwindow->copyDir(runPath("plugins/sqldrivers"), ss + "/plugins/sqldrivers"); // HIDE
	  if (b) b = EXTERN_my_mainwindow->copyDir(runPath("plugins/phonon_backend"), ss + "/plugins/phonon_backend"); // HIDE
	
	  s = ss + "/" + getName(); // HIDE
	  b = EXTERN_my_mainwindow->copyFile(runPath("kbrun"), s); // HIDE

   if (!q.isEmpty()){
     if (b) b = EXTERN_my_mainwindow->createDir(ss + EXTERN_my_mainwindow->getFilenamePath(z)); // HIDE
     if (b) b = EXTERN_my_mainwindow->copyFile(q, ss + z); // HIDE
   }


#endif
}

    QFile f (s);
    if (!pcodeinclude->isChecked() && b && f.open( QFile::WriteOnly | QFile::Append )){    
      int nSize = 0;
              
      // copy data    
      {
        QFile ff(cachePath("runtime.pcode"));
        if (ff.open(QFile::ReadOnly)){    

          char acBuffer[10240];
          int i = 0;
          int i2 = 0;
          nSize = ff.size();
          while (i2 < nSize && (i = ff.read(acBuffer, 10240)) > 0){    
            f.write(acBuffer, i);   
            i2 += i;
          }                     
          ff.close();
        } else b = false;
      }
      

      char ac[100];

      // add file size at end      
      memcpy(ac, &nSize, 4);
      f.write(ac, 4);   
      
      bool bProject = EXTERN_my_mainwindow->isProject();
      memcpy(ac, &bProject, 1);
      f.write(ac, 1);   

      f.write("KBASIC", 6);   

      f.close();


#ifdef WINDOWS
#else
      if (bWindows){
      } else {
        QString k = "chmod 755 " + s;
        system(k.toAscii().data());
      }
#endif
  
      QApplication::restoreOverrideCursor();
      if (b) QMessageBox::information(EXTERN_my_mainwindow, tr("Compile Project"),
        tr(
      "Binary file has been successfully created. "
      )
      );    
            
      if (b) QMessageBox::information(EXTERN_my_mainwindow, tr("Compile Project"),
        tr(
      "Please READ carefully the description about giving away your compiled program\n"
      "on http://www.kbasic.com/\n"

      )
      );    

    } else if (pcodeinclude->isChecked() && b){

      if (bWindows){ // HIDE
        if (b) b = EXTERN_my_mainwindow->copyFile(cachePath("runtime.pcode"), k + "/runtime.pcode");//runtime_windows // HIDE
      } // HIDE
      if (bLinux){
        b = EXTERN_my_mainwindow->copyFile(cachePath("runtime.pcode"), k + "/runtime.pcode");
      }
      if (bMac){ // HIDE
        s = s + ".app/Contents/MacOS"; // HIDE
        b = EXTERN_my_mainwindow->copyFile(cachePath("runtime.pcode"), s + "/runtime.pcode"); // HIDE
      }

   QApplication::restoreOverrideCursor();
      if (b) QMessageBox::information(EXTERN_my_mainwindow, tr("Compile Project"),
        tr(
      "Binary file has been successfully created. "
      )
      );    
            
      if (b) QMessageBox::information(EXTERN_my_mainwindow, tr("Compile Project"),
        tr(
      "Please READ carefully the description about giving away your compiled program\n"
      "on http://www.kbasic.com/\n"
      )
      );    

    } else {
      b = false;
      QApplication::restoreOverrideCursor();
    }
  }
  
}

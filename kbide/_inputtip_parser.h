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

#ifndef _inputtip_parser_H
#define _inputtip_parser_H

#include <QString>
#include <QList>

#define MAX_FIELD 512



extern QString sLastTERM;
extern QString sLastLastTERM;
extern QString sLastTERM2;

enum _inputtip_type
{
  __sub, __function, __constructor, __enum, __type, __class, __module, __constant, __variable, __event2, __property2, __dummy
};

class _inputtip_info
{
public:

_inputtip_info(QString _name, _inputtip_type _type, QString _type_name, QString _file, int _line, QString _scope, QString _scope2)
{
  name = _name;
  type_name = _type_name;
  type = _type;
  file = _file;
  line = _line;
  scope = _scope;
  scope2 = _scope2;
}

QString name;
QString type_name;
_inputtip_type type;

QString file; 
int line;
QString scope; 
QString scope2; 
};

enum _modifier
{
  _public, _private, _protected
};

enum _methodtype
{
  _sub, _function, _constructor, _event
};


struct _field
{
QString name;
QString type;
};

struct _class
{
QString name;
QString type;
_modifier modifier;

QString file; 
int line;
};

struct _module
{
QString name;
_modifier modifier;

QString file; 
int line;
};

struct _constant
{
QString name;
QString type;
QString scope;
QString scope2;
_modifier modifier;

QString file; 
int line;
};

struct _variable
{
QString name;
QString type_name;
QString type;
QString scope;
QString scope2;
_modifier modifier;

QString file; 
int line;
};

struct _property2
{
QString name;
QString type_name;
QString type;
QString scope;
QString scope2;
_modifier modifier;

QString file; 
int line;
};

struct _method
{
QString name;
QString type;
QString scope;
QString def; // (name as type,...)
_methodtype methodtype;
_modifier modifier;

QString file; 
int line;
};

struct _enum
{
QString name;
QString scope;
_field def[MAX_FIELD];
_modifier modifier;

QString file; 
int line;
};

struct _type
{
QString name;
QString scope;
_field def[MAX_FIELD];
_modifier modifier;

QString file; 
int line;
};



class _inputtip_parser
{
public:

  _inputtip_parser();
  ~_inputtip_parser();


  void parse(QString sFilename, QString sText);

  QList<_inputtip_info> getAllForFile(QString sForFile);
  QList<_inputtip_info> getAsForFile(QString sForFile, QString sScope);
  QList<_inputtip_info> getDotForFile(QString sForFile, QString sScope, QString sScope2, QString sDot);
  QList<_inputtip_info> getDotMethodForFile(QString sForFile, QString sScope, QString sScope2, QString sDot);
  QList<_inputtip_info> getFindDefinition(QString sForFile, QString sScope, QString sScope2, QString sDot, QString sBeforeDot);

  QList<_inputtip_info> framework_getEventsForClass(QString sControlType);

  QList<_inputtip_info> framework_getAsForFile(QString sScope);
  QList<_inputtip_info> framework_getDotForFile(QString sScope, QString sScope2, QString sDot);
  QList<_inputtip_info> framework_getDotMethodForFile(QString sScope, QString sScope2, QString sDot);

  QString getForF1(QString sDot, QString sDot2);

  static void framework_parse();

private:
  bool bShouldClose;
  bool bCanClose;

  QString prepareSourceCodeDefinition(QString sFile);

  void addFrameworkClasses(QList<_inputtip_info> &l, QString sName);

  void append(QList<_inputtip_info> &l, QString _name, _inputtip_type _type, QString _type_name, QString _file, int _line, QString _scope, QString _scope2)
  {
    if (_scope2 != "Framework"){
      foreach(_inputtip_info v, l){
        if ((v.name == _name)
          && (v.type == _type)
          && (v.type_name == _type_name)          
          && (v.scope == _scope)
          && (v.scope2 == _scope2)
          && (v.file == _file)
          && (v.line == _line)) return;
      }
    }
    l.append(_inputtip_info(_name, _type, _type_name, _file, _line, _scope, _scope2));
  }


  bool insideString(int n);



  bool TERM2(QString s)
  {
    int n = s.length();
    if (s.compare(sText.mid(nPos, n), Qt::CaseInsensitive) == 0){
      sLastTERM2 = s;
      nPos += n;
      return true;
    }
    return false;
  }

  bool TERM(QString s)
  {
    while(TERM2(" "));
    int n = s.length();
    if (s.compare(sText.mid(nPos, n), Qt::CaseInsensitive) == 0){
      sLastLastTERM = sLastTERM;
      sLastTERM = s;
      nPos += n;
      return true;
    }
    return false;
  }

  bool PEEK(QString s)
  {
    int n = s.length();
    if (s.compare(sText.mid(nPos, n), Qt::CaseInsensitive) == 0){
      return true;
    }
    return false;
  }

  bool TO(QString s)
  {
    int nn = sText.length();
    while(TERM2(" "));
    int n = s.length();
    do {
      if (s.compare(sText.mid(nPos, n), Qt::CaseInsensitive) == 0){
        nPos += n;
        return true;
      }
      if (fEOL()) break;
      nPos++;
    } while (nPos < nn);
    return false;
  }

  QString GETTO(QString s)
  {
    while(TERM2(" "));
    int nn = nPos;
    int n = s.length();
    do {
      if (s.compare(sText.mid(nn, n), Qt::CaseInsensitive) == 0){
        QString ss = sText.mid(nPos, nn - nPos);
        nPos = nn + n;
        return ss;
      }
      if (fEOL()) break;
      nn++;
    } while (nn < nLen);
    return "";
  }

  QString ID()
  {
    while(TERM2(" "));
    int n = nPos;
    while (nPos < nLen){
      if (fWHITESPACE()) break;
      if (PEEK(",")) break;
      if (PEEK("=")) break;
      if (PEEK("(")) break;
      if (PEEK("[")) break;
      if (PEEK(":")) break;
      nPos++;
    }   

    QString s = sText.mid(n, nPos - n);    
    return s.simplified();
  }

  int getCurrentLine()
  {
    QString s = sText.left(nPos);
    return s.count("\n") + 1;
  }

  bool fCLASS()
  {
    if (
      TERM("CLASS")
      || TERM("PUBLIC CLASS")
      || TERM("PRIVATE CLASS")
       )
    {      
      int nLine = getCurrentLine();

      sScope = ID();

      _class my_class;
     
      my_class.name = sScope;
      my_class.type = "Object";
        
      if (sLastTERM.contains("PRIVATE", Qt::CaseInsensitive)) my_class.modifier = _private;
      else my_class.modifier = _public;

      if (TO("INHERITS")){
        QString s = ID();
        my_class.type = s.isEmpty() ? "Object" : s;
      }

      my_class.file = sFilename;
      my_class.line = nLine - nLineCorrector;

      classes.append(my_class);
      return true;

    } else if (TERM("END CLASS")){
      sScope = "";
      return true;
    }
    return false;
  }

  bool fMODULE()
  {
    if (
      TERM("MODULE")
      || TERM("PUBLIC MODULE")
      || TERM("PRIVATE MODULE")
       )
    {
      int nLine = getCurrentLine();

      sScope = ID();

      _module my_module;
     
      my_module.name = sScope;
      if (sLastTERM.contains("PRIVATE", Qt::CaseInsensitive)) my_module.modifier = _private;
      else my_module.modifier = _public;

      my_module.file = sFilename;
      my_module.line = nLine - nLineCorrector;
      modules.append(my_module);

      return true;
    } else if (TERM("END MODULE")){
      sScope = "";
      return true;
    }
    return false;
  }

  bool fEOL()
  {
    if (TERM2("\n")) return true;
    return false;
  }

  bool fWHITESPACE()
  {
    if (TERM2("\n")) return true;
    if (TERM2(" ")) return true;
    return false;
  }

  bool fCONST()
  {
    int n = nPos;
    if (
      TERM("CONST")
      || TERM("PUBLIC CONST")
      || TERM("PRIVATE CONST")
       )
    {
      _constant my_constant;

      int nLine = getCurrentLine();

      do {      
        

        my_constant.name = ID();
        my_constant.type = "";
        my_constant.scope = sScope;
        my_constant.scope2 = sScope2;        
        if (sLastTERM.contains("PRIVATE", Qt::CaseInsensitive)) my_constant.modifier = _private;
        else my_constant.modifier = _public;

        my_constant.file = sFilename;
        my_constant.line = nLine - nLineCorrector;
        constants.append(my_constant);

      } while (sLastTERM2 != "\n" && TO(","));
      return true;
    }
    n = nPos;
    return false;
  }

  bool fVAR()
  {
    int n = nPos;
    QString sScope99;
    if (
      TERM("DIM")
      || TERM("PUBLIC DIM")
      || TERM("PROTECTED DIM")
      || TERM("PRIVATE DIM")
      || TERM("STATIC PUBLIC DIM")
      || TERM("STATIC PROTECTED DIM")
      || TERM("STATIC PRIVATE DIM")
      || TERM("PUBLIC STATIC DIM")
      || TERM("PROTECTED STATIC DIM")
      || TERM("PRIVATE STATIC DIM")
      || TERM("STATIC PUBLIC")
      || TERM("STATIC PROTECTED")
      || TERM("STATIC PRIVATE")
      || TERM("PUBLIC STATIC")
      || TERM("PROTECTED STATIC")
      || TERM("PRIVATE STATIC")
      || TERM("PUBLIC")
      || TERM("PROTECTED")
      || TERM("PRIVATE")
       )
    {
      _variable my_variable;

      int nLine = getCurrentLine();

      do {
        sScope99 = sLastTERM;

        my_variable.name = ID();
        my_variable.type = "Variant";
        my_variable.type_name = "";
        my_variable.scope = sScope;
        my_variable.scope2 = sScope2;        
        if (TO("AS")){
          while(TERM2(" "));
          if (PEEK("NEW")) TO("NEW");
          QString s = ID();
          my_variable.type = s.isEmpty() ? "Variant" : s;

          // CONTROL
          if (
            my_variable.type.compare("UdpSocket", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("ScrollBar", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("SpinBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("Slider", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("FormsView", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("ToolBarView", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("SvgBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("CommandLinkButton", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("ResizeBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("ToolButton", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("Label", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("Line", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("CommandButton", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("CheckBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("RadioButton", Qt::CaseInsensitive) == 0 ||

            my_variable.type.compare("TextBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("Frame", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("ComboBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("ListBox", Qt::CaseInsensitive) == 0 ||

            my_variable.type.compare("DateBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("TimeBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("DateTimeBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("Timer", Qt::CaseInsensitive) == 0 ||

            my_variable.type.compare("TabView", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("ImageBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("TreeView", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("Box", Qt::CaseInsensitive) == 0 ||

            my_variable.type.compare("RichTextBox", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("HtmlView", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("ProgressBar", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("SerialPort", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("FormView", Qt::CaseInsensitive) == 0 ||

            my_variable.type.compare("MenuBarItem", Qt::CaseInsensitive) == 0  ||
            my_variable.type.compare("ToolBarItem", Qt::CaseInsensitive) == 0  || 

			      my_variable.type.compare("Video", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("Sound", Qt::CaseInsensitive) == 0 ||
            my_variable.type.compare("WebView", Qt::CaseInsensitive) == 0 

          ){
            my_variable.type_name = my_variable.type;           
          }
        }
        if (sScope99.contains("PRIVATE", Qt::CaseInsensitive)) my_variable.modifier = _private;
        else if (sScope99.contains("PROTECTED", Qt::CaseInsensitive)) my_variable.modifier = _protected;
        else my_variable.modifier = _public;

        my_variable.file = sFilename;
        my_variable.line = nLine - nLineCorrector;
  
        variables.append(my_variable);

      } while (sLastTERM2 != "\n" && TO(","));
      return true;
    }
    n = nPos;
    return false;
  }

bool fPROPERTY()
  {
    int n = nPos;
    QString sScope99;
    bool bb = false;

    if (
      TERM("PUBLIC PROPERTY SET")
      || TERM("PROTECTED PROPERTY SET")
      || TERM("PRIVATE PROPERTY SET")
      || TERM("PUBLIC PROPERTY SET")
      || TERM("PROTECTED PROPERTY GET")
      || TERM("PRIVATE PROPERTY GET")
      || TERM("PUBLIC PROPERTY GET")
      || TERM("PROPERTY SET")
      || TERM("PROPERTY SET")
      || TERM("PROPERTY SET")
      || TERM("PROPERTY GET")
      || TERM("PROPERTY GET")
      || TERM("PROPERTY GET")
       )
    {
      bb = true;
    }

    if (
      bb 
      || TERM("PUBLIC PROPERTY")
      || TERM("PROTECTED PROPERTY")
      || TERM("PRIVATE PROPERTY")
      || TERM("PROPERTY")
       )
    {
      _property2 my_property;

      int nLine = getCurrentLine();

      do {
        sScope99 = sLastTERM;

        my_property.name = ID();
        my_property.type = "Variant";
        my_property.type_name = "";
        my_property.scope = sScope;
        my_property.scope2 = sScope2;  
        
        if (bb && TO("()")){
          my_property.name += " (Get)";
        } else if (bb){
          my_property.name += " (Set)";
        }

        /*
        if (TO("AS")){
          while(TERM2(" "));
          QString s = ID();
          my_property.type = s.isEmpty() ? "Variant" : s;          
        }*/
        if (sScope99.contains("PRIVATE", Qt::CaseInsensitive)) my_property.modifier = _private;
        else if (sScope99.contains("PROTECTED", Qt::CaseInsensitive)) my_property.modifier = _protected;
        else my_property.modifier = _public;

        my_property.file = sFilename;
        my_property.line = nLine - nLineCorrector;
  
        properties.append(my_property);

      } while (sLastTERM2 != "\n" && TO(","));
      return true;
    }
    n = nPos;
    return false;
  }

  bool fMETHOD()
  {
    int n = nPos;
    QString sScope99;

    if (
      TERM("SUB")
      || TERM("FUNCTION")
      || TERM("CONSTRUCTOR")
      )
    { 
      sLastLastTERM = "";
      goto ok;
    }

    if (
      TERM("STATIC FUNCTION")
      || TERM("FUNCTION STATIC")
      || TERM("STATIC SUB")
      || TERM("SUB STATIC")
      )
    { 
      sLastLastTERM = "";
      goto ok;
    }

    if (
      TERM("DECLARE STATIC PUBLIC")
      || TERM("DECLARE STATIC PRIVATE")
      || TERM("DECLARE PUBLIC STATIC")
      || TERM("DECLARE PRIVATE STATIC")
      || TERM("DECLARE PUBLIC")
      || TERM("DECLARE PRIVATE")        
      || TERM("STATIC PUBLIC")
      || TERM("STATIC PROTECTED")
      || TERM("STATIC PRIVATE")
      || TERM("PUBLIC STATIC")
      || TERM("PROTECTED STATIC")
      || TERM("PRIVATE STATIC")

      || TERM("PUBLIC DECLARE")
      || TERM("PRIVATE DECLARE")

      || TERM("PUBLIC")
      || TERM("PROTECTED")
      || TERM("PRIVATE")
       )
    {
      sScope99 = sLastTERM;
      if (
        TERM("SUB")
        || TERM("FUNCTION")
        || TERM("CONSTRUCTOR")
        )
      {
ok:
        _method my_method;

        int nLine = getCurrentLine();

        do {
          
          QString sType = sLastTERM;

          my_method.name = sScope2 = ID();

          my_method.scope = sScope;

          TO("(");
          my_method.def = GETTO(")");

          my_method.type = "";
          if (TERM("AS")){
            QString s = ID();
            my_method.type = s.isEmpty() ? "Variant" : s;
          }

          if (sScope99.contains("PRIVATE", Qt::CaseInsensitive)) my_method.modifier = _private;
          else if (sScope99.contains("PROTECTED", Qt::CaseInsensitive)) my_method.modifier = _protected;
          else my_method.modifier = _public;

          if (sType.contains("SUB", Qt::CaseInsensitive)) my_method.methodtype = _sub;
          else if (sType.contains("FUNCTION", Qt::CaseInsensitive)) my_method.methodtype = _function;
          else my_method.methodtype = _constructor;

          my_method.file = sFilename;
          my_method.line = nLine - nLineCorrector;

          methods.append(my_method);

        } while (sLastTERM2 != "\n" && TO(","));
        return true;
      }
    } else if (TERM("END SUB")){
      sScope2 = "";
      return true;
    } else if (TERM("END FUNCTION")){
      sScope2 = "";
      return true;
    } else if (TERM("END CONSTRUCTOR")){
      sScope2 = "";
      return true;
    }
    nPos = n;
    return false;
  }

  bool fENUM()
  {
    int n = nPos;

    if (
      TERM("ENUM")
      )
    { 
      sLastTERM = "";
      goto ok;
    }

    if (
      TERM("PUBLIC")
      || TERM("PRIVATE")
       )
    {
      if (
        TERM("ENUM")
        )
      {
ok:
        _enum my_enum;

        int nLine = getCurrentLine();

        my_enum.name = ID();
        my_enum.scope = sScope;

        if (sLastTERM.contains("PRIVATE", Qt::CaseInsensitive)) my_enum.modifier = _private;
        else my_enum.modifier = _public;

        while(TERM2(" "));
        if (PEEK("\n")) TERM("\n");

        int i = 0;

        my_enum.def[i].name = "";

        do {
          while(TERM2(" "));
          if (PEEK("\n")) TERM("\n");

          QString r = sText.mid(nPos);
          if (TERM("END ENUM")) break;


          my_enum.def[i].name = ID();
          my_enum.def[i].type = "";
          i++;
          if (sLastTERM2 != "\n") TO("\n");

        } while (i < MAX_FIELD);

        if (i < MAX_FIELD){

          my_enum.file = sFilename;
          my_enum.line = nLine - nLineCorrector;

          enums.append(my_enum);
          return true;
        }

      }
    }
    nPos = n;
    return false;
  }

  bool fTYPE()
  {
    int n = nPos;

    if (
      TERM("TYPE")
      )
    { 
      sLastTERM = "";
      goto ok;
    }

    if (
      TERM("PUBLIC")
      || TERM("PRIVATE")
       )
    {
      if (
        TERM("TYPE")
        )
      {
ok:
        _type my_type;

        int nLine = getCurrentLine();

        my_type.name = ID();
        my_type.scope = sScope;

        if (sLastTERM.contains("PRIVATE", Qt::CaseInsensitive)) my_type.modifier = _private;
        else my_type.modifier = _public;

        while(TERM2(" "));
        if (PEEK("\n")) TERM("\n");

        int i = 0;
        my_type.def[i].name = "";
        do {
          while(TERM2(" "));
          if (PEEK("\n")) TERM("\n");

          QString r = sText.mid(nPos);
          if (TERM("END TYPE")) break;

          my_type.def[i].name = ID();
          my_type.def[i].type = "";
          if (TO("AS")){
            QString s = ID();
            my_type.def[i].type = s;
          }
          i++;
          if (sLastTERM2 != "\n") TO("\n");

        } while (i < MAX_FIELD);

        if (i < MAX_FIELD){

          my_type.file = sFilename;
          my_type.line = nLine - nLineCorrector;

          types.append(my_type);
          return true;
        }
      }
    }
    nPos = n;
    return false;
  }

  

  QString debug()
  {
    QString s = "";

    foreach (_class v, classes)
    { 
      s += ("class: ");
      s += (v.modifier == _public ? "PUBLIC" : "PRIVATE");
      s += (" ");
      s += (v.name.toLatin1()); s += (" INHERITS ");
      s += (v.type.toLatin1());
      s += ("<br>");
    }
    s += ("<br>");

    foreach (_module v, modules)
    { 
      s += ("module: ");
      s += (v.modifier == _public ? "PUBLIC" : "PRIVATE");
      s += (" ");
      s += (v.name.toLatin1());
      s += ("<br>");
    }
    s += ("<br>");

    foreach (_constant v, constants)
    { 
      s += ("constant: ");
      s += (v.modifier == _public ? "PUBLIC" : "PRIVATE"); s += (" ");
      s += (v.scope.toLatin1()); s += (".");
      s += (v.scope2.toLatin1()); s += (".");
      s += (v.name.toLatin1());// s += (" AS ");
      s += ("<br>");
    }
    s += ("<br>");

    foreach (_variable v, variables)
    { 
      s += ("variable: ");
      s += (v.modifier == _public ? "PUBLIC" : v.modifier == _protected ? "PROTECTED" : "PRIVATE"); s += (" ");
      s += (v.scope.toLatin1()); s += (".");
      s += (v.scope2.toLatin1()); s += (".");
      s += (v.name.toLatin1()); s += (" AS ");
      s += (v.type.toLatin1()); s += ("");
      s += ("<br>");
    }
    s += ("<br>");

    foreach (_method v, methods)
    { 
      s += ("method:");
      s += (v.modifier == _public ? "PUBLIC" : v.modifier == _protected ? "PROTECTED" : "PRIVATE"); s += (" ");
      s += (v.methodtype == _sub ? "SUB" : v.methodtype == _function ? "FUNCTION" : "CONSTRUCTOR"); s += (" ");
      s += (v.scope.toLatin1()); s += (".");
      s += (v.name.toLatin1()); 
      if (!v.type.isEmpty()){
        s += (" AS ");
        s += (v.type.toLatin1()); 
      }
      s += ("(");
      s += (v.def.toLatin1()); s += (")");
      s += ("<br>");
    }
    s += ("<br>");

    foreach (_enum v, enums)
    { 
      s += ("enum: ");
      s += (v.modifier == _public ? "PUBLIC" : v.modifier == _protected ? "PROTECTED" : "PRIVATE");
      s += (" ");
      s += (v.scope.toLatin1()); s += (".");
      s += (v.name.toLatin1()); s += (": ");
      int i = 0;
      while(true){
        if (v.def[i].name.isEmpty()) break;
        s += (v.def[i].name.toLatin1()); s += (" , ");
       // s += (v.def[i].type.toLatin1()); s += (";");
        i++;
      }
      s += ("<br>");
    }
    s += ("<br>");

    foreach (_type v, types)
    { 
      s += ("type: ");
      s += (v.modifier == _public ? "PUBLIC" : v.modifier == _protected ? "PROTECTED" : "PRIVATE");
      s += (" ");
      s += (v.scope.toLatin1()); s += (".");
      s += (v.name.toLatin1()); s += (": ");
      int i = 0;
      while(true){
        if (v.def[i].name.isEmpty()) break;
        s += (v.def[i].name.toLatin1()); s += (" AS ");
        s += (v.def[i].type.toLatin1()); s += (" , ");
        i++;
      }
      s += ("<br>");
    }
    s += ("<br>");

    return s;
  }

  QList<_class>classes;
  QList<_module>modules;
  QList<_constant>constants; 
  QList<_variable>variables;
  QList<_property2>properties;
  QList<_method>methods;
  QList<_enum>enums;
  QList<_type>types;


  int nPos;
  int nLineCorrector;
  int nLen;

  QString sText;
  QString sScope;
  QString sScope2;

  QString sFilename;



  
  
};


#endif

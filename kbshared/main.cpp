/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3)
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
***************************************************************************
*/

#include "XIntMap.h"
#include "XIntVector.h"
#include "XFileInfo.h"


#include <stdlib.h>
#include <stdio.h>


#include <time.h>



#include "XString.h"
#include "XFile.h"



#include "../kbshared/cache.h"
#include "token.h"
#include "scanner.h"
#include "parser.h"

#include "utility.h"
#include "../kbshared/console.h"

XFile finfo;

extern XString path(XString s);

XString sProjectName;
XString sProjectType;
XString sTranslation;
XString sSQL;
XString sMenu;
XString sLogin;


XString sKBasicPath;


int MAIN_argc;
char **MAIN_argv;




XString getFilenameExtension(XString s)
{       
  int i = s.findRev('.');

  s = s.mid(i + 1);
  return s; 
}

XString getFilenameWithoutPath(XString s)
{       
  int i = s.findRev('\\');
  if (i == -1){
    i = s.findRev('/');
  }
  s = s.right(s.length() - i - 1);
  return s; 
}

XString getFilenameWithoutPathAndExtension(XString s)
{       
  XString k = getFilenameWithoutPath(s);

  int i = k.findRev('.');

  k = k.left(i);
  return k; 
}
    
void createSQLControl(XString ss, int nWidth, XString *sDefinition, XString *s, XString *sAdditional, int *X, int nBorderLeft, int nBorderBottom, int nHeight, int nFocusOrder, XString *sSQLControls)
{
  static char ac[1000];

  *sDefinition += "Private SQL";
  *sDefinition += ss;
  *sDefinition += " As ";
  
  bool bLabel = (ss == "Recordset" || ss == "Info");
  bool bTextBox = ss == "GoTo";
  bool bCommandButton = !bLabel && !bTextBox;

  if (bCommandButton) *sDefinition += "CommandButton\n";
  else if (bLabel) *sDefinition += "Label\n";
  else if (bTextBox) *sDefinition += "TextBox\n";

  *s += "SQL"; *s += ss; *s += " = New ";
  
  if (bCommandButton) *s += "CommandButton";
  else if (bLabel) *s += "Label";
  else if (bTextBox) *s += "TextBox";

  *s += "(Me)\n";  
  /*
  *s += "(Me, \"SQL";
  *s += ss;   
  *s += "\")\n";   */

  if (bLabel){
    if (ss == "Recordset"){
      *s += "SQL"; *s += ss; *s += ".Caption = \" Recordset: \"\n";   
    } else {
      *s += "SQL"; *s += ss; *s += ".Caption = \"\"\n";   
    }
  } else if (bTextBox){
    *s += "SQL"; *s += ss; *s += ".Value = \"\"\n";   
  } else if (bCommandButton){
    *s += "SQL"; *s += ss; *s += ".Caption = \"\"\n";   
  }
  *s += "SQL"; *s += ss; *s += ".Name = \""; *s += "SQL"; *s += ss; *s += "\"\n";   
  
  if (bCommandButton){
    *s += "SQL"; *s += ss; *s += ".Icon = \"SQL"; *s += ss; *s += ".png\"\n";   
  }
  *s += "SQL"; *s += ss; *s += ".X = "; sprintf(ac, "%d\n", nBorderLeft + *X); *s += XString(ac);
  *s += "SQL"; *s += ss; *s += ".Y = "; sprintf(ac, "%d\n", nHeight - nBorderBottom - 20); *s += XString(ac);
  *s += "SQL"; *s += ss; *s += ".Width = "; sprintf(ac, "%d\n", nWidth); *s += XString(ac);
  *s += "SQL"; *s += ss; *s += ".Height = 20\n";
  if (bCommandButton || bTextBox){ 
    *s += "SQL"; *s += ss; *s += ".FocusOrder = "; sprintf(ac, "%d\n", nFocusOrder); *s += XString(ac);
  }

  *s += "SQL"; *s += ss; *s += ".Layout = \"RelativeY\"\n\n";

  if (!bLabel){

    *sAdditional += "\nSub SQL";
    *sAdditional += ss;
    *sAdditional += "_OnEvent()\n";

    if (ss == "GoTo"){

      *sAdditional += "Dim n As Integer\n";
      *sAdditional += "n = Val( SQLGoTo.Value)\n";
      *sAdditional += "If n < 1 Or n > Me.Length() Then\n";
      *sAdditional += "  SQLGoTo.SelectAll()\n";
      *sAdditional += "  Return\n";
      *sAdditional += "End If\n";
      *sAdditional += "If Not Me.GoTo(n) Then\n";
      *sAdditional += "  SQLGoTo.Value = \"\" & Me.Position()\n";
      *sAdditional += "End If\n";
      *sAdditional += "\nEnd Sub\n";
    
    } else {
      *sAdditional += "  Me.";
      if (ss == "AddNotFilter"){
        *sAdditional += "AddFilter(\"<>\")\nEnd Sub\n";
      } else if (ss == "SetNotFilter"){
        *sAdditional += "SetFilter(\"<>\")\nEnd Sub\n";
      } else if (ss == "AddNew"){
        *sAdditional += "AddNew()\n";
        if (sSQLControls->isEmpty() || sSQLControls->contains("GoTo")) *sAdditional += "SQLGoTo.Value = \"*\"\n";
        *sAdditional += "\nEnd Sub\n";
      } else {
        *sAdditional += ss;
        *sAdditional += "()\nEnd Sub\n";
      }
    }

    
  }

  *X += nWidth;

}

char *prepareSourceCodeDefinition(const char *acFile, const char *acText, bool bForm)
{
  XString sText;

  sText = acText; sText = sText.replace("\r", "");
  int n = 0;

  XString sSQLName = "";
  XString sSQLControls = "";
  XString sAdditonalCode = "";
  XString sAdditional = "";

  int nBorderLeft = 0;
  int nBorderRight = 0;
  int nBorderTop = 0;
  int nBorderBottom = 0;

  int nHeight = 0;
  
  n = sText.find("Height = ");
  if (n >= 0){
    n += 9;
    int n2 = sText.find("\n", n);
    nHeight = atoi(sText.mid(n, n2 - n).ascii());
  }

  n = sText.find("BorderLeft = ");
  if (n >= 0){
    n += 13;
    int n2 = sText.find("\n", n);
    nBorderLeft = atoi(sText.mid(n, n2 - n).ascii());
  }

  n = sText.find("BorderRight = ");
  if (n >= 0){
    n += 14;
    int n2 = sText.find("\n", n);
    nBorderRight = atoi(sText.mid(n, n2 - n).ascii());
  }

  n = sText.find("BorderTop = ");
  if (n >= 0){
    n += 12;
    int n2 = sText.find("\n", n);
    nBorderTop = atoi(sText.mid(n, n2 - n).ascii());
  }

  n = sText.find("BorderBottom = ");
  if (n >= 0){
    n += 15;
    int n2 = sText.find("\n", n);
    nBorderBottom = atoi(sText.mid(n, n2 - n).ascii());
  }

  n = sText.find("SQLControls = \"");
  if (n >= 0){
    n += 15;
    int n2 = sText.find("\"", n);
    sSQLControls = sText.mid(n, n2 - n);
  }

  n = sText.find("SQLName = \"");
  if (n >= 0){
    n += 11;
    int n2 = sText.find("\"", n);
    sSQLName = sText.mid(n, n2 - n);
  }

  n = 0;

  
  n++;

  static XString sDefinition;
  sDefinition = "";
  XString sConstructor = "";

  sDefinition += "\n";



  do {
    n = sText.find("Begin ", n);
    if (n == -1) break;

    int n2 = sText.find("\n", n);
    n += 6;
    XString sLine = sText.mid(n, n2 - n);
    int n3 = sLine.find(" ");
    XString sType = sLine.mid(0, n3);
    XString sName = sLine.mid(n3 + 1);
    sName = sName.stripWhiteSpace();

    sDefinition += "Public ";
    sDefinition += sName;
    sDefinition += " As ";
    sDefinition += sType;
    sDefinition += "\n";

    sConstructor += sName;
    sConstructor += " = Control(\"";
    sConstructor += sName;
    sConstructor += "\")\n";

    n = sText.find("End\n", n); // proceed to the end of that control defintion

  } while (true);

 
  int X = 0;

  int nFocusOrder = 1000;

  if (!sSQLName.isEmpty() && bForm)
  {
    if (sSQLControls.isEmpty()){
      createSQLControl("Recordset", 90, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); 
      createSQLControl("First", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); 
      createSQLControl("Previous", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); 
      createSQLControl("GoTo", 60, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); 
      createSQLControl("Next", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); 
      createSQLControl("Last", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); 
      createSQLControl("AddNew", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); 
      X += 5;
      createSQLControl("Info", 110, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); 
      X += 20;
      createSQLControl("Update", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); 
      X += 20;
      createSQLControl("Delete", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); 

    } else {
      if (sSQLControls.contains("Recordset")){ createSQLControl("Recordset", 90, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); }
      if (sSQLControls.contains("First")){ createSQLControl("First", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); }
      if (sSQLControls.contains("Previous")){ createSQLControl("Previous", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); }
      if (sSQLControls.contains("GoTo")){ createSQLControl("GoTo", 50, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); }
      if (sSQLControls.contains("Next")){ createSQLControl("Next", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); }
      if (sSQLControls.contains("Last")){ createSQLControl("Last", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); }
      if (sSQLControls.contains("AddNew")){ createSQLControl("AddNew", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); }
      X += 5;
      if (sSQLControls.contains("Info")){ createSQLControl("Info", 90, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); }
      X += 20;
      if (sSQLControls.contains("Update")){ createSQLControl("Update", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); }
      X += 20;
      if (sSQLControls.contains("Delete")){ createSQLControl("Delete", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight, nFocusOrder++, &sSQLControls); }
      /*
      X += 20;
      if (sSQLControls.contains("Requery")){ createSQLControl("Requery", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight); }
      if (sSQLControls.contains("Seek")){ createSQLControl("Seek", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight); }
      if (sSQLControls.contains("ClearFilter")){ createSQLControl("ClearFilter", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight); }
      if (sSQLControls.contains("AddFilter")){ createSQLControl("AddFilter", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight); }
      if (sSQLControls.contains("AddNotFilter")){ createSQLControl("AddNotFilter", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight); }
      if (sSQLControls.contains("SetFilter")){ createSQLControl("SetFilter", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight); }
      if (sSQLControls.contains("SetNotFilter")){ createSQLControl("SetNotFilter", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight); }
      if (sSQLControls.contains("SortAscending")){ createSQLControl("SortAscending", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight); }
      if (sSQLControls.contains("SortDescending")){ createSQLControl("SortDescending", 20, &sDefinition, &sAdditonalCode, &sAdditional, &X, nBorderLeft, nBorderBottom, nHeight); }
      */

    }
  }

  sDefinition += "\n\nConstructor ";
  sDefinition += getFilenameWithoutPathAndExtension(acFile);
  sDefinition += "()\n";

  sDefinition += "\nLoad(\"";
  sDefinition += getFilenameWithoutPathAndExtension(acFile);
  sDefinition += "\")\n\n";

  sDefinition += sConstructor;

  sDefinition += "\nFinish()\n\n";

  sDefinition += sAdditonalCode;

  sDefinition += "\nEnd Constructor\n";

  sDefinition += sAdditional;

  if (!sSQLName.isEmpty() && bForm)
  {
    sDefinition += "Sub Form_OnGoTo2()\n";
    if (sSQLControls.isEmpty() || sSQLControls.contains("GoTo")) sDefinition += "  SQLGoTo.Value = \"\" & Me.Position()\n";    
    if (sSQLControls.isEmpty() || sSQLControls.contains("Info")){
      sDefinition += "  If IsFilterActive() Then\nSQLInfo.Caption = \"of \" & Me.Length() & \" record(s) (Filter)\"\nElse\nSQLInfo.Caption = \"of \" & Me.Length() & \" record(s)\"\nEnd If\n";
    }
    sDefinition += "End Sub\n";
  }

  return (char *) sDefinition.ascii();

}

char *prepareSourceCode(const char *acFile, const char *acText, const XString & sFile)
{
  static XString sText;
  XString sClass = "";
  bool bReport = false;
  bool bModule = false;
  bool bClass = false;

  if (sFile.endsWith(".kbasic_form")){
    sClass = "Form";
  } else if (sFile.endsWith(".kbasic_menubar")){
    sClass = "MenuBar";
  } else if (sFile.endsWith(".kbasic_toolbar")){
    sClass = "ToolBar";
  } else if (sFile.endsWith(".kbasic_module")){
    bModule = true;
  } else if (sFile.endsWith(".kbasic_class")){
    bClass = true;
  } else if (sFile.endsWith(".kbasic_report")){
    sClass = "Report";
    bReport = true;
  }

  XString sHeader = "";

  if (bModule){
    sText = acText; sText = sText.replace("\r", "");
    if (sText.contains("\nEnd Module ", false)) return (char *) sText.ascii();
    if (sText.contains("\nEnd Module\n", false)) return (char *) sText.ascii();
    if (sText.contains("\nEnd Module'", false)) return (char *) sText.ascii();
    if (sText.contains("\nEnd Module/*", false)) return (char *) sText.ascii();
    if (sText.endsWith("End Module", false)) return (char *) sText.ascii();
    if (sText.startsWith("Module ", false)) return (char *) sText.ascii();
    if (sText.startsWith("\nModule ", false)) return (char *) sText.ascii();

    sHeader = sHeader.append("Module ");
    sHeader = sHeader.append(getFilenameWithoutPathAndExtension(acFile));
    sHeader = sHeader.append(" : ");
    
    sText = sText.prepend(sHeader);

    sText = sText.append("\nEnd Module\n");
  } else if (bClass){
    sText = acText; sText = sText.replace("\r", "");
    if (sText.contains("\nEnd Class ", false)) return (char *) sText.ascii();
    if (sText.contains("\nEnd Class\n", false)) return (char *) sText.ascii();
    if (sText.contains("\nEnd Class'", false)) return (char *) sText.ascii();
    if (sText.contains("\nEnd Class/*", false)) return (char *) sText.ascii();
    if (sText.endsWith("End Class", false)) return (char *) sText.ascii();
    if (sText.startsWith("Class ", false)) return (char *) sText.ascii();
    if (sText.startsWith("\nClass ", false)) return (char *) sText.ascii();

    sHeader = sHeader.append("Class ");
    sHeader = sHeader.append(getFilenameWithoutPathAndExtension(acFile));
    if (sFile.endsWith("myEvent.kbasic_class", false)){
      sHeader = sHeader.append(" Inherits Event ");
    }
    sHeader = sHeader.append(" : ");

    
    sText = sText.prepend(sHeader);

    sText = sText.append("\nEnd Class\n");
  } else {

    XString sFind = "\nEnd " + sClass + "\n";
    sText = acText; sText = sText.replace("\r", "");
    sText = sText.mid(sText.find(sFind) + sFind.length());
    
    sHeader = sHeader.append("Class ");
    sHeader = sHeader.append(getFilenameWithoutPathAndExtension(acFile));
    sHeader = sHeader.append(" Inherits ");
    sHeader = sHeader.append(bReport ? "Form" : sClass); // actually Report is a form
    sHeader = sHeader.append("\n");

    sText = sText.prepend(sHeader);

    XString sDefinition = "";
    

    if (sFile.endsWith(".kbasic_form")){
      sDefinition = prepareSourceCodeDefinition(acFile, acText, true);  
    } else if (sFile.endsWith(".kbasic_report")){
      sDefinition = prepareSourceCodeDefinition(acFile, acText, false);  
    }

    sText = sText.append(sDefinition);
    sText = sText.append("\nEnd Class\n");
  }

  return (char *) sText.ascii();

}

void renameFile(XString s, XString d)
{
  XString k = "";
#ifdef WINDOWS // HIDE
  k = "move "; // HIDE
  k = k.append(s); // HIDE
  k = k.append(" "); // HIDE
  k = k.append(d); // HIDE
  system(k.ascii()); // HIDE
#else // HIDE
  k = "mv "; // HIDE
  k = k.append(s); // HIDE
  k = k.append(" "); // HIDE
  k = k.append(d); // HIDE
  system(k.ascii()); // HIDE
#endif // HIDE

  // UNHIDE k = "mv ";
  // UNHIDE k = k.append(s);
  // UNHIDE k = k.append(" ");
  // UNHIDE k = k.append(d);
  // UNHIDE system(k.ascii());


}



XString kbasicPath(XString s)
{
  
  //if (sKBasicPath.isNull()) sKBasicPath = "c:\\kbasic16";

  XString k = sKBasicPath;
  k = k.replace("/cache", "");
  k = k + "/"+ s; 
 
  //k = k.replace("/", "\\");
  
  //QMessageBox::information(0, "", k);


  return k;
}

XString cachePath(XString s)
{
  
  //if (sKBasicPath.isNull()) sKBasicPath = "c:\\kbasic16";
  XString k = sKBasicPath + "/"+ s; 
 
 // k = k.replace("\\", "/");
  
  //QMessageBox::information(0, "", k);


  return k;
}



int kbc()
{
  

  char ac[1024];

  
  /*
  sprintf(ac, "c:\\basic\\examples\\kbasic\\sub\\sub2.kbasic");
  sprintf(ac, "c:\\basic\\examples\\kbasic\\important\\type.kbasic");
  sprintf(ac, "c:\\basic\\examples\\kbasic\\examples\\array.kbasic");
  sprintf(ac, "c:\\basic\\examples\\kbasic\\keyword\\goto.kbasic");
  */

  bool bSilent = false;
  bool bDebug = false;
  bool bUseCache = false;   
  char *acLicense = "";
  char *acProjectName = "";
  char *acLogin = "";  
  char *acProjectType = "";
  char *acTranslation = "";
  char *acSQL = "";
  char *acMenu = "";
  
  sLogin = "";
  sProjectName = "";
  sProjectType = "";
  sTranslation = "";
  sSQL = "";
  sMenu = "";

  int i = 1;
  for (; i < MAIN_argc; i++){

    const char *ac = MAIN_argv[i];
   
    if (utility::my_stricmp(ac, "-Silent") == 0) bSilent = true;
    else if (utility::my_stricmp(ac, "-Debug") == 0) bDebug = true;
    else if (utility::my_stricmp(ac, "-UseCache") == 0) bUseCache = true;
    
    else if (utility::my_strnicmp(ac, "-License", 8) == 0){
      acLicense = (char *) ac + 8;
      if (acLicense == 0) acLicense = "";
      /*
    } else if (utility::my_strnicmp(ac, "-ProjectName", 12) == 0){
       

      acProjectName = (char *) ac + 12;
         //CONSOLE printError(ac);
       //  CONSOLE printError("\n");
      if (acProjectName == 0) sProjectName = ""; else sProjectName = acProjectName; 
*/
    } else if (utility::my_strnicmp(ac, "-Login", 6) == 0){
       
      acLogin = (char *) ac + 6;
      if (acLogin == 0) sLogin = ""; else sLogin = acLogin; 

    } else if (utility::my_strnicmp(ac, "-ProjectType", 12) == 0){
       

      acProjectType = (char *) ac + 12;
         //CONSOLE printError(ac);
       //  CONSOLE printError("\n");
      if (acProjectType == 0) sProjectType = ""; else sProjectType = acProjectType; 
        //  CONSOLE printError("2222222222\n");


    } else if (utility::my_strnicmp(ac, "-Translation", 12) == 0){


      acTranslation = (char *) ac + 12;
      if (acTranslation == 0) sTranslation = ""; else sTranslation = acTranslation; 
    
    } else if (utility::my_strnicmp(ac, "-SQL", 4) == 0){


      acSQL = (char *) ac + 4;
      if (acSQL == 0) sSQL = ""; else sSQL = acSQL; 
     // printf(acSQL);
    
    } else if (utility::my_strnicmp(ac, "-Menu", 5) == 0){

      acMenu = (char *) ac + 5;
      if (acMenu == 0) sMenu = ""; else sMenu = acMenu;      
                
    }
    else break;
  }

  /*
  bSilent = false;
  bDebug = false;
  bUseCache = true;   
  sProjectName = "KBasic Default Project";
  sProjectType = "With Forms MainWindow (you must have myMenuBar created)";
  sTranslation = "&Window;Help;C&ontents;A&bout;Cl&ose;Close &All;&Tile;&Cascade;Arrange &icons;Ne&xt;Pre&vious;";
  sSQL = "QPSQL;localhost;test;postgres;test";

*/

 // if (bUseCache) printf("!!!!!");


 // sprintf(ac, "");
  //if (MAIN_argc > 1 && i <= MAIN_argc) sprintf(ac, "%s", MAIN_argv[i]);
  
  //sprintf(ac, "C:/kbasic16/kbide/examples/kbasic/builtin/__class__.kbasic");

  //if (utility::my_stricmp(ac, "") == 0) return 0;

  //bUseCache = false;
  {
    sKBasicPath = MAIN_argv[0];  
    bool bDebug = false;
#ifdef WINDOWS // HIDE
    bDebug = sKBasicPath.contains("Debug"); // HIDE
#endif // HIDE

    sKBasicPath = sKBasicPath.replace("\\", "/");
#ifdef WINDOWS // HIDE
    sKBasicPath = sKBasicPath.replace("/Debug", "", false); // HIDE
    sKBasicPath = sKBasicPath.replace("/Release", "", false); // HIDE
    sKBasicPath = sKBasicPath.replace(".exe", "", false); // HIDE
#endif // HIDE

    if (bDebug){
      int n = sKBasicPath.findRev("/");
      if (n >= 0) sKBasicPath = sKBasicPath.left(n);

      sKBasicPath = sKBasicPath.replace("kbc", "kbide/ide/cache");
    } else {
      sKBasicPath = sKBasicPath.replace("kbc", "ide/cache");
    }
    
    if (sKBasicPath.isEmpty()) return 0;
  }

  // if (checkLicense(acLicense) == false) return 0;


//  checkSerialNo();

	textbuffer *myTextbuffer = new textbuffer(); // needed to truncate big input strings or zero terminate them
 
  cache *my_cache = new cache();
  token *myToken = new token();
	scanner *myScanner = new scanner(myToken, my_cache);

	char *acText;
  bool b = true;

  if (utility::readSourceFile(&acText, cachePath("project.name").ascii(), myTextbuffer)){
    acText = utility::eatUTF16DOM(acText);
    sProjectName = acText;
  }

//  if (b && (b = utility::readSourceFile(&acText, "c:/kbasic16/kbide/ide/cache/C__kbasic16_kbide_examples_kbasic_builtin___class__.kbasic.scanner", myTextbuffer))){}


  { // delete runtime.parser file
    XString m = cachePath("runtime.parser");
    //CONSOLE printError(cachePath("runtime.parser").ascii());
    XFile f(m.ascii());
    if (!f.open(Truncate)){
      CONSOLE printError("Could not create runtime parser file: ");
      CONSOLE printError(m.ascii());
      b = false;
    } else {
      f.close();
    }
  }

  XString m = cachePath("compiler.output");
  finfo.setName(m.ascii());  
  char acInfo[1024];

  //if (utility::my_stricmp(ac, "") == 0)
  if (b){


    {      
      if (!finfo.open(Truncate)){
        CONSOLE printError("Could not write compiler output file:");
        CONSOLE printError(m.ascii());
        b = false;
      } 
    }
    finfo.close();

    XString sFiles = "";

    if (b){ // read compiler.input file
      XString m = cachePath("compiler.input");
      XFile f(m.ascii());
      if (!f.open(ReadOnly)){
        CONSOLE printError("Could not read compiler input file:");
        CONSOLE printError(m.ascii());
        b = false;
      } else {

        int i = 0;
        char acBuffer[10240];
        int nSize = f.size();
        while (i < nSize && (i = f.readBlock(acBuffer, 10240)) > 0){  
          acBuffer[i] = 0;

          const char *ac = utility::eatUTF16DOM(acBuffer);
          sFiles += ac;
        }
        //sFiles = sFiles.appendNull();
        
        f.close();
      }
    }

    if (my_cache){
      my_cache->setMode(bSilent, bDebug); // important, setting right file name for caching

      // sort input files so that non-cached files are at the end, otherwise IDs of classes will collide
      if (bUseCache){

        #define MAX_INPUTFILES 512

        struct inputfile {
          XString sFilename;
          int nDate;
        };
        inputfile files[MAX_INPUTFILES];

        int nCounter = 0;
        
  
        int n = 0;
        int n0 = 0;

        bool bFirst = true;
        do {
          if (nCounter >= MAX_INPUTFILES){
            nCounter = 0;
            CONSOLE printError("too many input files to compile (> 512)");
            break;
          }

          n = sFiles.find("\n", n);
          XString s = sFiles.mid(n0, n >= 0 ? n - n0 : sFiles.length());
          if (n == -1 & bFirst == false) break;

          XFileInfo k(s.ascii());
          int r = k.lastModified();

          files[nCounter].sFilename = s;
          files[nCounter].nDate = r;
          nCounter++;
          
          n0 = n + 1;
          n++;

          if (bFirst) bFirst = false;

        } while (true);

        bool bRedo = false;
        do {
          bRedo = false;

          for (int i = 0; i < nCounter; i++){

            if (i + 1 < nCounter){
              if (files[i].nDate > files[i + 1].nDate){
                inputfile file = files[i + 1];
                files[i + 1] = files[i];
                files[i] = file;

                bRedo = true;
                break;
              }
            }

          }
        } while (bRedo);

        sFiles = "";
        for (int i = 0; i < nCounter; i++){
          sFiles = sFiles + files[i].sFilename + "\n";          
        }
      }
        
    }



    
    if (finfo.open(Truncate)){ sprintf(acInfo, "Scanning..."); finfo.writeBlock(acInfo, strlen(acInfo)); finfo.close(); }
    
    if (finfo.open(Truncate)){ sprintf(acInfo, "%s", cachePath("default.kbasic").ascii()); finfo.writeBlock(acInfo, strlen(acInfo)); finfo.close(); }

    if (b && (b = utility::readSourceFile(&acText, cachePath("default.kbasic").ascii(), myTextbuffer))){

      acText = utility::eatUTF16DOM(acText);
    }

    if (b && (b = myScanner->scan(acText, (char *) cachePath("default.kbasic").ascii(), bSilent, bDebug, false, bUseCache))){} // filename

    if (b){
      int n = 0;
      int n0 = 0;

      bool bFirst = true;
      do {
        n = sFiles.find("\n", n);
        XString s = sFiles.mid(n0, n >= 0 ? n - n0 : sFiles.length());
        if (n == -1 & bFirst == false) break;
        bFirst = false;
        n0 = n + 1;
        n++;
        
        const char *ac99 = s.ascii();

        if (b && (b = utility::readSourceFile(&acText, ac99, myTextbuffer))){
          acText = utility::eatUTF16DOM(acText);
        }


        XString sFile = ac99;

        if (sFile.endsWith(".kbasic_form")){
     
          XString sLanguage = "";
          XString sExt = getFilenameExtension(sFile);
          XString q = sFile.left(sFile.length() - sExt.length() - 1);

          if (q.count(".") > 1){
            sLanguage = getFilenameExtension(q);
            if (sLanguage.contains("/") || sLanguage.contains("\\")){
              sLanguage = "";
            }
          }
        
          if (sLanguage.length() == 0){
   //       if (!sTranslation.contains(sLanguage, false)){
            acText = prepareSourceCode(ac99, acText, sFile); 
          } else {
/*
            char ac[1111];
            sprintf(ac, "omit %s %s", sFile.ascii(), sLanguage.ascii());
            CONSOLE printError(ac);*/
            continue;
//            acText = "";
          }

        } else if (sFile.endsWith(".kbasic_menubar")){

          XString sLanguage = "";
          XString sExt = getFilenameExtension(sFile);
          XString q = sFile.left(sFile.length() - sExt.length() - 1);

          if (q.count(".") > 1){
            sLanguage = getFilenameExtension(q);
            if (sLanguage.contains("/") || sLanguage.contains("\\")){
              sLanguage = "";
            }
          }
        
          if (sLanguage.length() == 0){
   //       if (!sTranslation.contains(sLanguage, false)){
            acText = prepareSourceCode(ac99, acText, sFile); 
          } else {
            continue;
//            acText = "";
          }

        } else if (sFile.endsWith(".kbasic_toolbar")){

          XString sLanguage = "";
          XString sExt = getFilenameExtension(sFile);
          XString q = sFile.left(sFile.length() - sExt.length() - 1);

          if (q.count(".") > 1){
            sLanguage = getFilenameExtension(q);
            if (sLanguage.contains("/") || sLanguage.contains("\\")){
              sLanguage = "";
            }
          }
        
          if (sLanguage.length() == 0){
   //       if (!sTranslation.contains(sLanguage, false)){
            acText = prepareSourceCode(ac99, acText, sFile); 
          } else {

            continue;
//            acText = "";
          }

        } else if (sFile.endsWith(".kbasic_report")){

          XString sLanguage = "";
          XString sExt = getFilenameExtension(sFile);
          XString q = sFile.left(sFile.length() - sExt.length() - 1);

          if (q.count(".") > 1){
            sLanguage = getFilenameExtension(q);
            if (sLanguage.contains("/") || sLanguage.contains("\\")){
              sLanguage = "";
            }
          }
        
          if (sLanguage.length() == 0){
   //       if (!sTranslation.contains(sLanguage, false)){
            acText = prepareSourceCode(ac99, acText, sFile); 
          } else {
            continue;
            //acText = "";
          }

        } else if (sFile.endsWith(".kbasic_module")){
#ifdef WINDOWS // HIDE
  if (sFile.endsWith(".linux.kbasic_module")) continue; // HIDE
  if (sFile.endsWith(".mac.kbasic_module")) continue; // HIDE
#elif defined(MAC) // HIDE
  if (sFile.endsWith(".linux.kbasic_module")) continue; // HIDE
  if (sFile.endsWith(".windows.kbasic_module")) continue; // HIDE
#elif defined(LINUX) // HIDE
  if (sFile.endsWith(".windows.kbasic_module")) continue; // HIDE
  if (sFile.endsWith(".mac.kbasic_module")) continue; // HIDE
#endif // HIDE

          // UNHIDE if (sFile.endsWith(".windows.kbasic_module")) continue;
          // UNHIDE if (sFile.endsWith(".mac.kbasic_module")) continue;

          acText = prepareSourceCode(ac99, acText, sFile);
        } else if (sFile.endsWith(".kbasic_class")){
#ifdef WINDOWS // HIDE
  if (sFile.endsWith(".linux.kbasic_class")) continue; // HIDE
  if (sFile.endsWith(".mac.kbasic_class")) continue; // HIDE
#elif defined(MAC) // HIDE
  if (sFile.endsWith(".linux.kbasic_class")) continue; // HIDE
  if (sFile.endsWith(".windows.kbasic_class")) continue; // HIDE
#elif defined(LINUX) // HIDE
  if (sFile.endsWith(".windows.kbasic_class")) continue; // HIDE
  if (sFile.endsWith(".mac.kbasic_class")) continue; // HIDE
#endif // HIDE

          // UNHIDE if (sFile.endsWith(".windows.kbasic_class")) continue; // HIDE
          // UNHIDE if (sFile.endsWith(".mac.kbasic_class")) continue; // HIDE

          acText = prepareSourceCode(ac99, acText, sFile);
        } else if (sFile.endsWith(".kbasic")){
#ifdef WINDOWS // HIDE
  if (sFile.endsWith(".linux.kbasic")) continue; // HIDE
  if (sFile.endsWith(".mac.kbasic")) continue; // HIDE
#elif defined(MAC) // HIDE
  if (sFile.endsWith(".linux.kbasic")) continue; // HIDE
  if (sFile.endsWith(".windows.kbasic")) continue; // HIDE
#elif defined(LINUX) // HIDE
  if (sFile.endsWith(".windows.kbasic")) continue; // HIDE
  if (sFile.endsWith(".mac.kbasic")) continue; // HIDE
#endif // HIDE
  
  // UNHIDEif (sFile.endsWith(".windows.kbasic")) continue;
  // UNHIDEif (sFile.endsWith(".mac.kbasic")) continue;

        }
        if (finfo.open(Truncate)){ finfo.writeBlock((void *) ac99, strlen(ac99)); finfo.close(); }
        if (b && (b = myScanner->scanAdditional(acText, (char *) ac99, bSilent, bDebug, bUseCache))){} // filename
        if (!b) break;
      } while (true);
    }

    if (b) {
      if (finfo.open(Truncate)){ sprintf(acInfo, "%s", cachePath("default2.kbasic").ascii()); finfo.writeBlock(acInfo, strlen(acInfo)); finfo.close(); }

      if (b && (b = utility::readSourceFile(&acText, cachePath("default2.kbasic").ascii(), myTextbuffer))){

        acText = utility::eatUTF16DOM(acText);
      }
      if (b && (b = myScanner->scanAdditional(acText, (char *) cachePath("default2.kbasic").ascii(), bSilent, bDebug, bUseCache))){} // filename
    }

    myScanner->addEOFToken();
/*
  } else {
    if (b && (b = utility::readSourceFile(&acText, ac, myTextbuffer))){}
    if (b && (b = myScanner->scan(acText, ac, bSilent, bDebug, true, bUseCache))){} // filename*/
  }




  //delete myToken;

//	if (utility::readSourceFile(&acText, ac, myTextbuffer)){
//		if (myScanner->scanAdditional(acText, filename)){

  

  if (b){

    if (finfo.open(Truncate)){ sprintf(acInfo, "Parsing..."); finfo.writeBlock(acInfo, strlen(acInfo)); finfo.close(); }

		pcode *myPcode = new pcode("");
  //  myPcode->setInfoWindow(myInfoConsole);

		parser *myParser = new parser(myPcode, my_cache);
  //  myParser->setInfoWindow(myInfoConsole);

    
    //bool b = false;

    /*
         if (strcmp(acDir, "examples\\veryoldbasic\\") == 0 && (b = myParser->parseVeryOldBasic(myToken, bSilent, bDebug))){}
    else if (strcmp(acDir, "examples\\oldbasic\\") == 0 && (b = myParser->parseOldBasic(myToken, bSilent, bDebug))){}
    else if (strcmp(acDir, "examples\\kbasic\\") == 0 && (b = myParser->parseKBasic(myToken, bSilent, bDebug))){}
    else */
    //bUseCache = false;

  //  CONSOLE printError("myParser->parseKBasic(myToken, bSilent, bDebug, bUseCache);");
    b = myParser->parseKBasic(myToken, bSilent, bDebug, bUseCache);

		if (b){
  //    CONSOLE printError("b=true");

      XString m;// = path(sKBasicPath);
      m = cachePath("runtime.pcode");

      XFile f(m.ascii());
      if (!f.open(Truncate)){
        CONSOLE printError("Could not create runtime pcode file");
        b = false;
      } else {
        //const char *aa = myPcode->ba->getMem();
        int n = myPcode->ba->getSize();
        n = f.writeBlock (myPcode->ba->getMem(), n);

       
        f.close();
      }

    }


		delete myParser;
		delete myPcode;
   

	}	

  

  delete myScanner;
	delete myToken;
	delete myTextbuffer;
  delete my_cache;

	{

    XString m;
    m = cachePath("compiler.done");

    XFile f(m.ascii());
    if (!f.open(Truncate)){
      CONSOLE printError("Could not create runtime done file");
      b = false;
    } else {     
      f.close();
    }
  
  }

  return b ? 0 : -1;
		
}




int main(int argc, char *argv[])
{

	MAIN_argc = argc;
	MAIN_argv = argv;

  return kbc();

}

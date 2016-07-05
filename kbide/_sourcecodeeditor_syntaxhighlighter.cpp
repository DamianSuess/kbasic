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

#include "_sourcecodeeditor_syntaxhighlighter.h"
#include "_mainwindow.h"

extern _mainwindow *EXTERN_my_mainwindow;

QSet<QString> set;
QSet<QString> sql_set;

 _sourcecodeeditor_syntaxhighlighter::_sourcecodeeditor_syntaxhighlighter(QTextDocument *parent)
     : QSyntaxHighlighter(parent)
 {
     HighlightingRule rule;

     

     if (set.count() == 0){

        // create normal list
        sql_set << "First"<< /*"Next"<<*/ "Previous"<< "Last"<< "GoTo"<< "Insert"<< "Update"<< "Delete"<< "AddNew"<< "Length"<< "Position"<< "IsDirty"<< "Run"<< "Get"<< "PrimaryKey"<< "PrimaryKeyName"<< "kbrecordid"<< "kbrecordid"<< "Seek"<< "Requery"<< "ClearFilter"<< "IsFilterActive"<< "AddFilter"<< "SetFilter"<< "SortAscending"<< "SortDescending";
        sql_set << "Me.First"/*<< "Me.Next"*/<< "Me.Previous"<< "Me.Last"<< "Me.GoTo"<< "Me.Insert"<< "Me.Update"<< "Me.Delete"<< "Me.AddNew"<< "Me.Length"<< "Me.Position"<< "Me.IsDirty"<< "Me.Run"<< "Me.Get"<< "Me.PrimaryKey"<< "Me.PrimaryKeyName"<< "Me.kbrecordid"<< "Me.kbrecordid"<< "Me.Seek"<< "Me.Requery"<< "Me.ClearFilter"<< "Me.IsFilterActive"<< "Me.AddFilter"<< "Me.SetFilter"<< "Me.SortAscending"<< "Me.SortDescending";

        //sql_set << "Cut" << "Copy" << "Paste" << "SetFilter" << "SetNotFilter" << "First" /*<< "Next"*/ << "Previous" << "Last" << "GoTo" << "Insert" << "Update" << "Delete" << "AddNew" << "Len" << "Pos" << "IsDirty" << "Run" << "Get" << "Seek" << "Requery" << "ClearFilter" << "AddFilter" << "AddNotFilter" << "SortAscending" << "SortDescending";
        //sql_set << "Me.Cut" << "Me.Copy" << "Me.Paste" << "Me.SetFilter" << "Me.SetNotFilter" << "Me.First" << "Me.Next" << "Me.Previous" << "Me.Last" << "Me.GoTo" << "Me.Insert" << "Me.Update" << "Me.Delete" << "Me.AddNew" << "Me.Len" << "Me.Pos" << "Me.IsDirty" << "Me.Run" << "Me.Get" << "Me.Seek" << "Me.Requery" << "Me.ClearFilter" << "Me.AddFilter" << "Me.AddNotFilter" << "Me.SortAscending" << "Me.SortDescending";
    
        sql_set << "Form_OnGoTo" << "Form_OnGoTo2" << "Form_OnQuery" << "Form_OnAddNew" << "Form_OnDirty" << "Form_OnBeforeInsert" << "Form_OnBeforeUpdate" << "Form_OnBeforeDelete";

        // create uppercase list
        QList<QString> list = set.toList();
        foreach (QString value, list){
          sql_set << value.toUpper();
        }

        // create lowercase list
        list = set.toList();
        foreach (QString value, list){
          sql_set << value.toLower();
        }
     }

     if (set.count() == 0){

        // create normal list

         set << "$Dynamic" << "#Else" << "$End" << "#ExternalSource" << "#If" << "#Region" << "$Static (Outdated)" << "Absolute" << "Abstract" << "AddressOf" << "Alias" << "Ansi" << "As" << "Assembly" << "Auto" << "Base" << "Binary" << "ByRef" << "ByVal" << "Call" << "CallByName" << "Case" << "Catch" << "Chain" << "Choose" << "Class" << "Class_Initialize" << "Class_Terminate" << "COM" << "Common" << "Compare" << "Connect" << "Const" << "Constructor" << "Data" << "Database" << "Decimal" << "Declare" << "Def" << "Default" << "DefBool" << "DefByte" << "DefCur" << "DefDate" << "DefDbl" << "DefInt" << "DefLng" << "DefObj" << "DefSng" << "DefStr" << "DefVar" << "Delegate" << "Destructor" << "Dim" << "DirectCast" << "Disconnect" << "Do" << "Each" << "Else" << "ElseIf" << "Empty" << "End" << "EndIf" << "Enum" << "Erase" << "Event" << "Exit" << "Explicit" << "Finally" << "For" << "Friend" << "Function" << "Global" << "GoSub" << "GoTo" << "Handles" << "If" << "IIf" << "Implements" << "Imports" << "In" << "Inherits" << "Interface" << "Is" << "Iterate" << "KBasic" << "Key" << "LBound" << "Let" << "Lib" << "Like" << "Loop" << "LSet" << "Me" << "Mid" << "Module" << "MustInherit" << "MustOverride" << "My" << "MyBase" << "MyClass" << "NameSpace" << "New" << "Next" << "Nothing" << "NotInheritable" << "NotOverridable" << "Null" << "Off" << "OldBasic" << "On" << "Option" << "Optional" << "Overloads" << "Overriddable" << "Overrides" << "ParamArray" << "Parent" << "Pen" << "Play" << "Preserve" << "Private" << "Property" << "Protected" << "Public" << "Range" << "Read" << "ReadOnly" << "ReDim" << "Rem" << "/**" << "/*" << "*/" << "'" << "Repeat" << "Restore" << "Resume" << "Return" << "RSet" << "Run" << "Select" << "Set" << "Shadows" << "Shared" << "Signal" << "SizeOf" << "Slot" << "Static" << "Step" << "Stop" << "STRIG" << "Structure" << "Sub" << "Swap" << "Switch" << "SynClock" << "System" << "Text" << "Then" << "Throw" << "Throws" << "Timer" << "To" << "TROFF" << "TRON" << "Try" << "Type" << "TypeDef" << "TypeOf" << "UBound" << "UniCode" << "Until" << "VARPTR" << "VARPTR$" << "VARSEG" << "VeryOldBasic" << "Wait" << "Wend" << "While" << "With" << "WithEvents" << "WriteOnly";
         set << "Abs" << "Access" << "Acs" << "AddDays" << "AddHandler" << "AddHours" << "AddMinutes" << "AddMonths" << "AddSeconds" << "AddYears" << "AppActiviate" << "Append" << "Array" << "Asc" << "Asn" << "Atn" << "Beep" << "Bin" << "Bin$" << "Binary (Builtin)" << "BLOAD" << "BSAVE" << "CBCD" << "CBool" << "CByte" << "CChar" << "CCur" << "CDate" << "CDbl" << "CDec" << "CEXT" << "CFIX" << "ChDir" << "ChDrive" << "Chr" << "Chr$" << "CInt" << "Circle" << "Class" << "Clear" << "CLng" << "Close" << "CLS" << "CObj" << "Color" << "Command" << "Command$" << "Compare" << "Contains" << "Count" << "Cos" << "CQUD" << "CreateObject" << "CShort" << "CSng" << "CsrLin" << "CType" << "CurDir" << "CurDir$" << "CVD" << "CVDMBF" << "CVERR" << "CVI" << "CVL" << "CVS" << "CVSMBF" << "Date" << "Date$" << "DateAdd" << "DateDiff" << "DatePart" << "DateSerial" << "DateValue" << "Day" << "DayName" << "DayOfWeek" << "DayOfYear" << "DaysInMonth" << "DaysInYear" << "DDB" << "Debug" << "Deg" << "DeleteSetting" << "Decode" << "DiffDay" << "DiffSeconds" << "Dir" << "Dir$" << "DoEvents" << "DOF" << "Draw" << "Encode" << "EndsWith" << "Environ" << "Environ$" << "EOF" << "ErDev" << "ErDev$" << "Erl" << "Err" << "Error" << "Error$" << "Exp" << "Fact" << "Field" << "FileAttr" << "FileCopy" << "FileDateTime" << "FileLen" << "File" << "Files" << "Fill" << "Filter" << "Fix" << "FN" << "Format" << "Format$" << "FormatCurrency" << "FormatDateTime" << "FormatNumber" << "FormatPercent" << "Frac" << "FRE" << "FreeFile" << "Function" << "FV" << "Get" << "GetAllSettings" << "GetAttr" << "GetAutoServerSettings" << "GetObject" << "GetSetting" << "GetType" << "Hex" << "Hex$" << "Hour" << "Hypot" << "IMEStatus" << "IndexOf" << "Inkey" << "Inkey$" << "Inp" << "Input" << "Input$" << "InputBox" << "Insert" << "InStr" << "InStRev" << "Int" << "IOCtl" << "IOCtl$" << "IPMT" << "IRR" << "IsArray" << "IsBoolean" << "IsByte" << "IsCharacter" << "IsCollection" << "IsCString" << "IsCurrency" << "IsDate" << "IsDateValid" << "IsDateTimeValid" << "IsDouble" << "IsEmpty" << "IsError" << "IsInteger" << "IsMissing" << "IsLinux" << "IsMac" << "IsNull" << "IsNumeric" << "IsObject" << "IsShort" << "IsSingle" << "IsLeapYear" << "IsLong" << "IsString" << "IsTimeValid" << "IsVariant" << "IsWindows" << "Join" << "KBasicDir" << "Kill" << "LastIndexOf" << "LCase" << "LCase$" << "Left" << "Left$" << "LeftJustified" << "Len" << "Length" << "Line (Debug)" << "Ln" << "Load" << "LoadPicture" << "LoadResData" << "LoadResPicture" << "LoadResString" << "Loc" << "Locate" << "Lock" << "LOF" << "Log" << "Logb" << "Lower" << "LPos" << "LPrint" << "LTrim" << "LTrim$" << "Max" << "Mid (Builtin)" << "Mid$ (Builtin)" << "Min" << "Minute" << "MIRR" << "MKD$" << "MkDir" << "MKDMBF$" << "MKI$" << "#MKL$" << "MKS" << "MKS$" << "MKSMBF$, Module" << "Month" << "MonthName" << "MsgBox" << "MTIMER" << "Name" << "Now" << "NPER" << "NPV" << "Nz" << "Oct" << "Oct$" << "Open" << "Out" << "Output" << "Paint" << "Palette" << "Partition" << "PCopy" << "Peek" << "PMAP" << "PMT" << "Point" << "Poke" << "Pos" << "PPMT" << "Prepend" << "Preset" << "Print" << "PrintScreen" << "PSet" << "Put" << "PV" << "QBCOLOR" << "Rad" << "Raise" << "RaiseEvent" << "RaiseSignal" << "Random" << "Randomize" << "Rate" << "ReadBinary" << "Remove" << "RemoveHandler" << "Replace" << "Return" << "Reset" << "Reversed" << "RGB" << "Right" << "Right$" << "RightJustified" << "RmDir" << "RND" << "Round" << "RTrim" << "RTrim$" << "SavePicture" << "SaveSetting" << "Screen" << "Sec" << "Second" << "Section" << "Seek" << "SeekBinary" << "Seg" << "SendKeys" << "SetAttr" << "Sgn" << "Shell" << "Simplified" << "Sin" << "Size" << "Sleep" << "Sln" << "Sound" << "Space" << "Space$" << "Spc" << "Split" << "Sqr" << "Stick" << "StartsWith" << "Str" << "Str$" << "StrComp" << "StrConv" << "String" << "String$" << "StrReverse" << "Sub" << "SubDays" << "SubHours" << "SubMinutes" << "SubMonths" << "SubSeconds" << "SubYears" << "SYD" << "Tab" << "Tan" << "Time" << "Time$" << "TimeSerial" << "TimeValue" << "Trim" << "Trim$" << "Trimmed" << "Truncate" << "Type" << "TypeName" << "UCase" << "UCase$" << "Unicode" << "UnLoad" << "UnLock" << "Upper" << "Using" << "Utf8" << "Utf16" << "Val" << "Value" << "VarType" << "View" << "Weekday" << "WeekdayName" << "WeekNumber" << "Width" << "Window" << "Write" << "WriteBinary" << "Year";
         set << "BitAnd" << "BitOr" << "BitXor" << "BitNot" << "Mod" << "And" << "AndAlso" << "Or" << "OrElse" << "Not" << "Xor" << "Eqv" << "Imp";
         set << "Bits" << "Bits" << "Dictionary" << "Array" << "Strings" << "DateTime" << "Decimal" << "Boolean" << "Byte" << "CString" << "Currency" << "Date" << "Double" /*<< "Int16" << "Int32" << "Int64"*/ << "Integer" << "Long" << "Object" << "Short" << "Single" << "CString" << "String" /*<< "UInt16" << "UInt32" << "UInt64"*/ << "Variant";

   //     set << "$Dynamic" << "#Else" << "$End" << "#ExternalSource" << "#If" << "#Region" << "$Static" << "Absolute" << "Abstract" << "AddressOf" << "Alias" << "Ansi" << "As" << "Assembly" << "Auto" << "Base" << "ByRef" << "ByVal" << "Call" << "CallByName" << "Case" << "Catch" << "Chain" << "Choose" << "Class" << "Class_Initialize" << "Class_Terminate" << "COM" << "Common" << "Compare" << "Connect" << "Const" << "Constructor" << "Data" << "Database" << "Decimal" << "Declare" << "Def" << "Default" << "DefBool" << "DefByte" << "DefCur" << "DefDate" << "DefDbl" << "DefInt" << "DefLng" << "DefObj" << "DefSng" << "DefStr" << "DefVar" << "Delegate" << "Destructor" << "Dim" << "DirectCast" << "Disconnect" << "Do" << "Each" << "Echo" << "Else" << "ElseIf" << "Empty" << "End" << "EndIf" << "Enum" << "Erase" << "Event" << "Exit" << "Explicit" << "Finally" << "For" << "Friend" << "Function" << "Global" << "GoSub" << "GoTo" << "Handles" << "If" << "IIf" << "Implements" << "Imports" << "In" << "Inherits" << "Interface" << "Is" << "Iterate" << "KBasic" << "Key" << "LBound" << "Let" << "Lib" << "Like" << "Loop" << "LSet" << "Me" << "Mid" << "Module" << "MustInherit" << "MustOverride" << "MyBase" << "MyClass" << "NameSpace" << "New" << "Next" << "Nothing" << "NotInheritable" << "NotOverridable" << "Null" << "Off" << "OldBasic" << "On" << "Option" << "Optional" << "Overloads" << "Overriddable" << "Overrides" << "ParamArray" << "Parent" << "Pen" << "Play" << "Preserve" << "Private" << "Property" << "Protected" << "Public" << "Range" << "Read" << "ReadOnly" << "ReDim" << "Rem" << "/**" << "/*" << "*/" << "'" << "Repeat" << "Restore" << "Resume" << "Return" << "RSet" << "Run" << "Select" << "Set" << "Shadows" << "Shared" << "Signal" << "SizeOf" << "Slot" << "Static" << "Step" << "Stop" << "STRIG" << "Structure" << "Sub" << "Swap" << "Switch" << "SynClock" << "System" << "Text" << "Then" << "Throw" << "Throws" << "Timer" << "To" << "TROFF" << "TRON" << "Try" << "Type" << "TypeDef" << "UBound" << "UniCode" << "Until" << "VARPTR" << "VARPTR$" << "VARSEG" << "VeryOldBasic" << "Wait" << "Wend" << "While" << "With" << "WithEvents" << "WriteOnly";
  //      set << "Shl" << "Shr" << "Inc" << "Dec" << "BitAnd" << "BitOr" << "BitXor" << "BitNot" << "Mod" << "And" << "AndAlso" << "Or" << "OrElse" << "Not" << "Xor" << "Eqv" << "Imp";
  //      set << "Boolean" << "Byte" << "Character" << "Collection" << "CString" << "Currency" << "Date" << "Double" /*<< "Int16" << "Int32" << "Int64"*/ << "Integer" << "Long" << "Object" << "Short" << "Single" << "CString" << "WString" << "String" /*<< "UInt16" << "UInt32" << "UInt64"*/ << "Variant";
  //      set << "__Class__" << "__File__" << "__IsClass__" << "__IsLinux__" << "__IsMacOS__" << "__IsModule__" << "__IsSub__" << "__IsWindows__" << "__Line__" << "__Module__" << "__Scope__" << "__Sub__" << "Abs" << "Access" << "Acs" << "AddHandler" << "AppActiviate" << "Append" << "Array" << "Asc" << "Asn" << "Atn" << "Beep" << "Bin" << "Bin$" << "Binary" << "BLOAD" << "BSAVE" << "CBCD" << "CBool" << "CByte" << "CChar" << "CCur" << "CDate" << "CDbl" << "CDec" << "CEXT" << "CFIX" << "ChDir" << "ChDrive" << "Chr" << "Chr$" << "CInt" << "Circle" << "Clear" << "CLng" << "Close" << "CLS" << "CObj" << "Color" << "Command" << "Command$" << "Cos" << "CQUD" << "CreateObject" << "CShort" << "CSng" << "CsrLin" << "CType" << "CurDir" << "CurDir$" << "CVD" << "CVDMBF" << "CVERR" << "CVI" << "CVL" << "CVS" << "CVSMBF" << "Date" << "Date$" << "DateAdd" << "DateDiff" << "DatePart" << "DateSerial" << "DateValue" << "Day" << "DDB" << "Deg" << "DeleteSetting" << "Dir" << "Dir$" << "DoEvents" << "DOF" << "Draw" << "Environ" << "Environ$" << "EOF" << "ErDev" << "ErDev$" << "Erl" << "Err" << "Error" << "Error$" << "Exp" << "Fact" << "Field" << "FileAttr" << "FileCopy" << "FileDateTime" << "FileLen" << "Files" << "Filter" << "Fix" << "FN" << "Format" << "Format$" << "FormatCurrency" << "FormatDateTime" << "FormatNumber" << "FormatPercent" << "Frac" << "FRE" << "FreeFile" << "FV" << "Get" << "GetAllSettings" << "GetAttr" << "GetAutoServerSettings" << "GetObject" << "GetSetting" << "GetType" << "Hex" << "Hex$" << "Hour" << "Hypot" << "IMEStatus" << "Inkey" << "Inkey$" << "Inp" << "Input" << "Input$" << "InputBox" << "InStr" << "InStRev" << "Int" << "IOCtl" << "IOCtl$" << "IPMT" << "IRR" << "IsArray" << "IsBoolean" << "IsByte" << "IsCharacter" << "IsCollection" << "IsCString" << "IsCurrency" << "IsDate" << "IsDouble" << "IsEmpty" << "IsError" << "IsInt16" << "IsInt32" << "IsInt64" << "IsInteger" << "IsMissing" << "IsNull" << "IsNumeric" << "IsObject" << "IsShort" << "IsSingle" << "IsUInt16" << "IsUInt32" << "IsUInt64" << "IsLong" << "IsString" << "IsVariant" << "Join" << "Kill" << "LCase" << "LCase$" << "Left" << "Left$" << "Len" << "Line" << "Ln" << "Load" << "LoadPicture" << "LoadResData" << "LoadResPicture" << "LoadResString" << "Loc" << "Locate" << "Lock" << "LOF" << "Log" << "Logb" << "LPos" << "LPrint" << "LTrim" << "LTrim$" << "Max" << "Mid$" << "Min" << "Minute" << "MIRR" << "MKD$" << "MkDir" << "MKDMBF$" << "MKI$" << "MKL$" << "MKS" << "MKS$" << "MKSMBF$" << "Month" << "MonthName" << "MsgBox" << "MTIMER" << "Name" << "Now" << "NPER" << "NPV" << "Nz" << "Oct" << "Oct$" << "Open" << "Out" << "Output" << "Paint" << "Palette" << "Partition" << "PCopy" << "Peek" << "PMAP" << "PMT" << "Point" << "Poke" << "Pos" << "PPMT" << "Preset" << "Print" << "PSet" << "Put" << "PV" << "QBCOLOR" << "Rad" << "Raise" << "RaiseEvent" << "RaiseSignal" << "Random" << "Randomize" << "Rate" << "RemoveHandler" << "Replace" << "Reset" << "RGB" << "Right" << "Right$" << "RmDir" << "RND" << "Round" << "RTrim" << "RTrim$" << "SavePicture" << "SaveSetting" << "Screen" << "Sec" << "Second" << "Seek" << "Seg" << "SendKeys" << "SetAttr" << "Sgn" << "Shell" << "Sin" << "Sleep" << "Sln" << "Sound" << "Space" << "Space$" << "Spc" << "Split" << "Sqr" << "Stick" << "Str" << "Str$" << "StrComp" << "StrConv" << "String" << "String$" << "StrReverse" << "SYD" << "Tab" << "Tan" << "Time" << "Time$" << "TimeSerial" << "TimeValue" << "Trim" << "Trim$" << "TypeName" << "TypeOf" << "UCase" << "UCase$" << "UnLoad" << "UnLock" << "Using" << "Val" << "VarType" << "View" << "Weekday" << "WeekdayName" << "Width" << "Window" << "Write" << "Year";
  //      set << "DateTime";

        // create uppercase list
        QList<QString> list = set.toList();
        foreach (QString value, list){
          set << value.toUpper();
        }

        // create lowercase list
        list = set.toList();
        foreach (QString value, list){
          set << value.toLower();
        }
     }


     QString sFamily = EXTERN_my_mainwindow->getPreference("FontName");
     int nSize = EXTERN_my_mainwindow->getPreference("FontSize").toInt();
if (nSize == 0) nSize = 10;
#ifdef MAC
     nSize += 2; // HIDE
#endif

if (sFamily.isEmpty()){
#ifdef MAC
sFamily = "Monospace";
#endif
#ifdef LINUX
sFamily = "Monospace";
#endif
#ifdef WINDOWS
  sFamily = "Courier New";
#endif
}

     normalFormat.setFontFamily(sFamily); 
     normalFormat.setFontPointSize(nSize);

     sqlFormat.setForeground(Qt::darkCyan);
     sqlFormat.setFontFamily(sFamily); 
     sqlFormat.setFontPointSize(nSize);

     keywordFormat.setForeground(Qt::blue);
     //keywordFormat.setFontWeight(QFont::Bold);
     keywordFormat.setFontFamily(sFamily); 
     keywordFormat.setFontPointSize(nSize);

     /*
     keywordFormat.setForeground(Qt::darkBlue);
     //keywordFormat.setFontWeight(QFont::Bold);
     QStringList keywordPatterns;


     keywordPatterns << "\\bAbstract\\b" << "\\bAddressOf\\b" << "\\bAs\\b" << "\\bByRef\\b" << "\\bByVal\\b" <<   "\\bCase\\b" << "\\bCatch\\b" <<  "\\bChoose\\b" << "\\bClass\\b" << "\\bConnect\\b" << "\\bConst\\b" << "\\bConstructor\\b" <<    "\\bDeclare\\b" <<     "\\bDestructor\\b" << "\\bDim\\b" <<  "\\bDisconnect\\b" << "\\bDo\\b" << "\\bEach\\b" << "\\bEcho\\b" << "\\bElse\\b" << "\\bElseIf\\b" << "\\bEmpty\\b" << "\\bEnd\\b" << "\\bEndIf\\b" << "\\bEnum\\b" <<  "\\bEvent\\b" << "\\bExit\\b" << "\\bExplicit\\b" << "\\bFinally\\b" << "\\bFor\\b" <<  "\\bFunction\\b" <<  "\\bGoSub\\b" << "\\bGoTo\\b" <<  "\\bIf\\b" << "\\bIIf\\b" <<   "\\bIn\\b" << "\\bInherits\\b" <<  "\\bIs\\b" << "\\bIterate\\b" << "\\bKBasic\\b" <<  "\\bLBound\\b" <<  "\\bLib\\b" << "\\bLike\\b" << "\\bLoop\\b" <<  "\\bMe\\b" << "\\bMid\\b" << "\\bModule\\b" <<   "\\bNew\\b" << "\\bNext\\b" << "\\bNothing\\b" <<   "\\bNull\\b" << "\\bOff\\b" << "\\bOldBasic\\b" << "\\bOn\\b" << "\\bOption\\b" << "\\bOptional\\b" <<   "\\bParamArray\\b" << "\\bParent\\b" <<   "\\bPreserve\\b" << "\\bPrivate\\b" << "\\bProperty\\b" << "\\bProtected\\b" << "\\bPublic\\b" << "\\bRange\\b" << "\\bRead\\b" <<  "\\bReDim\\b" << "\\bRem\\b" <<   "\\bRestore\\b" << "\\bResume\\b" << "\\bReturn\\b" <<   "\\bSelect\\b" << "\\bSet\\b" <<   "\\bSignal\\b" << "\\bSizeOf\\b" << "\\bSlot\\b" << "\\bStatic\\b" << "\\bStep\\b" << "\\bStop\\b" <<   "\\bSub\\b" <<  "\\bSwitch\\b" <<    "\\bThen\\b" << "\\bThrow\\b" << "\\bThrows\\b" << "\\bTimer\\b" << "\\bTo\\b" << "\\bTry\\b" << "\\bType\\b" <<  "\\bUBound\\b" <<  "\\bUntil\\b" <<  "\\bVeryOldBasic\\b" <<  "\\bWend\\b" << "\\bWhile\\b" << "\\bWith\\b";

     //keywordPatterns << ""\\b#If\\b" << "\\b#Region\\b" << "\\bStatic\\b" << "\\bAbsolute\\b" << "\\bAbstract\\b" << "\\bAddressOf\\b" << "\\bAlias\\b" << "\\bAnsi\\b" << "\\bAs\\b" << "\\bAssembly\\b" << "\\bAuto\\b" << "\\bBase\\b" << "\\bByRef\\b" << "\\bByVal\\b" << "\\bCall\\b" << "\\bCallByName\\b" << "\\bCase\\b" << "\\bCatch\\b" << "\\bChain\\b" << "\\bChoose\\b" << "\\bClass\\b" << "\\bClass_Initialize\\b" << "\\bClass_Terminate\\b" << "\\bCOM\\b" << "\\bCommon\\b" << "\\bCompare\\b" << "\\bConnect\\b" << "\\bConst\\b" << "\\bConstructor\\b" << "\\bData\\b" << "\\bDatabase\\b" << "\\bDecimal\\b" << "\\bDeclare\\b" << "\\bDef\\b" << "\\bDefault\\b" << "\\bDefBool\\b" << "\\bDefByte\\b" << "\\bDefCur\\b" << "\\bDefDate\\b" << "\\bDefDbl\\b" << "\\bDefInt\\b" << "\\bDefLng\\b" << "\\bDefObj\\b" << "\\bDefSng\\b" << "\\bDefStr\\b" << "\\bDefVar\\b" << "\\bDelegate\\b" << "\\bDestructor\\b" << "\\bDim\\b" << "\\bDirectCast\\b" << "\\bDisconnect\\b" << "\\bDo\\b" << "\\bEach\\b" << "\\bEcho\\b" << "\\bElse\\b" << "\\bElseIf\\b" << "\\bEmpty\\b" << "\\bEnd\\b" << "\\bEndIf\\b" << "\\bEnum\\b" << "\\bErase\\b" << "\\bEvent\\b" << "\\bExit\\b" << "\\bExplicit\\b" << "\\bFinally\\b" << "\\bFor\\b" << "\\bFriend\\b" << "\\bFunction\\b" << "\\bGlobal\\b" << "\\bGoSub\\b" << "\\bGoTo\\b" << "\\bHandles\\b" << "\\bIf\\b" << "\\bIIf\\b" << "\\bImplements\\b" << "\\bImports\\b" << "\\bIn\\b" << "\\bInherits\\b" << "\\bInterface\\b" << "\\bIs\\b" << "\\bIterate\\b" << "\\bKBasic\\b" << "\\bKey\\b" << "\\bLBound\\b" << "\\bLet\\b" << "\\bLib\\b" << "\\bLike\\b" << "\\bLoop\\b" << "\\bLSet\\b" << "\\bMe\\b" << "\\bMid\\b" << "\\bModule\\b" << "\\bMustInherit\\b" << "\\bMustOverride/b" << "\\bMyBase\\b" << "\\bMyClass\\b" << "\\bNameSpace\\b" << "\\bNew\\b" << "\\bNext\\b" << "\\bNothing\\b" << "\\bNotInheritable\\b" << "\\bNotOverridable\\b" << "\\bNull\\b" << "\\bOff\\b" << "\\bOldBasic\\b" << "\\bOn\\b" << "\\bOption\\b" << "\\bOptional\\b" << "\\bOverloads\\b" << "\\bOverriddable\\b" << "\\bOverrides\\b" << "\\bParamArray\\b" << "\\bParent\\b" << "\\bPen\\b" << "\\bPlay\\b" << "\\bPreserve\\b" << "\\bPrivate\\b" << "\\bProperty\\b" << "\\bProtected\\b" << "\\bPublic\\b" << "\\bRange\\b" << "\\bRead\\b" << "\\bReadOnly\\b" << "\\bReDim\\b" << "\\bRem\\b" << "\\bRepeat\\b" << "\\bRestore\\b" << "\\bResume\\b" << "\\bReturn\\b" << "\\bRSet\\b" << "\\bRun\\b" << "\\bSelect\\b" << "\\bSet\\b" << "\\bShadows\\b" << "\\bShared\\b" << "\\bSignal\\b" << "\\bSizeOf\\b" << "\\bSlot\\b" << "\\bStatic\\b" << "\\bStep\\b" << "\\bStop\\b" << "\\bSTRIG\\b" << "\\bStructure\\b" << "\\bSub\\b" << "\\bSwap\\b" << "\\bSwitch\\b" << "\\bSynClock\\b" << "\\bSystem\\b" << "\\bText\\b" << "\\bThen\\b" << "\\bThrow\\b" << "\\bThrows\\b" << "\\bTimer\\b" << "\\bTo\\b" << "\\bTROFF\\b" << "\\bTRON\\b" << "\\bTry\\b" << "\\bType\\b" << "\\bTypeDef\\b" << "\\bUBound\\b" << "\\bUniCode\\b" << "\\bUntil\\b" << "\\bVARPTR\\b" << "\\bVARPTR\\b" << "\\bVARSEG\\b" << "\\bVeryOldBasic\\b" << "\\bWait\\b" << "\\bWend\\b" << "\\bWhile\\b" << "\\bWith\\b" << "\\bWithEvents\\b" << "\\bWriteOnly\\b";
     keywordPatterns << "\\bShl\\b" << "\\bShr\\b" << "\\bInc\\b" << "\\bDec\\b" << "\\bBitAnd\\b" << "\\bBitOr\\b" << "\\bBitXor\\b" << "\\bBitNot\\b" << "\\bMod\\b" << "\\bAnd\\b" << "\\bAndAlso\\b" << "\\bOr\\b" << "\\bOrElse\\b" << "\\bNot\\b" << "\\bXor\\b" << "\\bEqv\\b" << "\\bImp\\b";
     keywordPatterns << "\\bBoolean\\b" << "\\bByte\\b" << "\\bCharacter\\b" << "\\bCollection\\b" << "\\bCString\\b" << "\\bCurrency\\b" << "\\bDate\\b" << "\\bDouble\\b" << "\\bInt16\\b" << "\\bInt32\\b" << "\\bInt64\\b" << "\\bInteger\\b" << "\\bLong\\b" << "\\bObject\\b" << "\\bShort\\b" << "\\bSingle\\b" << "\\bString\\b" << "\\bUInt16\\b" << "\\bUInt32\\b" << "\\bUInt64\\b" << "\\bVariant\\b";

     foreach (QString pattern, keywordPatterns) {
       rule.pattern = QRegExp(pattern);
         rule.format = keywordFormat;
         highlightingRules.append(rule);
     }

     builtinFormat.setForeground(Qt::darkBlue);
     //builtinFormat.setFontWeight(QFont::Bold);
     QStringList builtinPatterns;

     builtinPatterns << "\\b__Class__\\b" << "\\b__File__\\b" << "\\b__IsClass__\\b" << "\\b__IsLinux__\\b" << "\\b__IsMacOS__\\b" << "\\b__IsModule__\\b" << "\\b__IsSub__\\b" << "\\b__IsWindows__\\b" << "\\b__Line__\\b" << "\\b__Module__\\b" << "\\b__Scope__\\b" << "\\b__Sub__\\b" << "\\bAbs\\b" << "\\bAccess\\b" << "\\bAcs\\b" << "\\bAddHandler\\b" << "\\bAppActiviate\\b" << "\\bAppend\\b" << "\\bArray\\b" << "\\bAsc\\b" << "\\bAsn\\b" << "\\bAtn\\b" << "\\bBeep\\b" << "\\bBin\\b" << "\\bBin \\b" << "\\bBinary\\b" << "\\bBLOAD\\b" << "\\bBSAVE\\b" << "\\bCBCD\\b" << "\\bCBool\\b" << "\\bCByte\\b" << "\\bCChar\\b" << "\\bCCur\\b" << "\\bCDate\\b" << "\\bCDbl\\b" << "\\bCDec\\b" << "\\bCEXT\\b" << "\\bCFIX\\b" << "\\bChDir\\b" << "\\bChDrive\\b" << "\\bChr\\b" << "\\bChr \\b" << "\\bCInt\\b" << "\\bCircle\\b" << "\\bClear\\b" << "\\bCLng\\b" << "\\bClose\\b" << "\\bCLS\\b" << "\\bCObj\\b" << "\\bColor\\b" << "\\bCommand\\b" << "\\bCommand \\b" << "\\bCos\\b" << "\\bCQUD\\b" << "\\bCreateObject\\b" << "\\bCShort\\b" << "\\bCSng\\b" << "\\bCsrLin\\b" << "\\bCType\\b" << "\\bCurDir\\b" << "\\bCurDir \\b" << "\\bCVD\\b" << "\\bCVDMBF\\b" << "\\bCVERR\\b" << "\\bCVI\\b" << "\\bCVL\\b" << "\\bCVS\\b" << "\\bCVSMBF\\b" << "\\bDate\\b" << "\\bDate \\b" << "\\bDateAdd\\b" << "\\bDateDiff\\b" << "\\bDatePart\\b" << "\\bDateSerial\\b" << "\\bDateValue\\b" << "\\bDay\\b" << "\\bDDB\\b" << "\\bDeg\\b" << "\\bDeleteSetting\\b" << "\\bDir\\b" << "\\bDir \\b" << "\\bDoEvents\\b" << "\\bDOF\\b" << "\\bDraw\\b" << "\\bEnviron\\b" << "\\bEnviron \\b" << "\\bEOF\\b" << "\\bErDev\\b" << "\\bErDev \\b" << "\\bErl\\b" << "\\bErr\\b" << "\\bError\\b" << "\\bError \\b" << "\\bExp\\b" << "\\bFact\\b" << "\\bField\\b" << "\\bFileAttr\\b" << "\\bFileCopy\\b" << "\\bFileDateTime\\b" << "\\bFileLen\\b" << "\\bFiles\\b" << "\\bFilter\\b" << "\\bFix\\b" << "\\bFN\\b" << "\\bFormat\\b" << "\\bFormat \\b" << "\\bFormatCurrency\\b" << "\\bFormatDateTime\\b" << "\\bFormatNumber\\b" << "\\bFormatPercent\\b" << "\\bFrac\\b" << "\\bFRE\\b" << "\\bFreeFile\\b" << "\\bFV\\b" << "\\bGet\\b" << "\\bGetAllSettings\\b" << "\\bGetAttr\\b" << "\\bGetAutoServerSettings\\b" << "\\bGetObject\\b" << "\\bGetSetting\\b" << "\\bGetType\\b" << "\\bHex\\b" << "\\bHex \\b" << "\\bHour\\b" << "\\bHypot\\b" << "\\bIMEStatus\\b" << "\\bInkey\\b" << "\\bInkey \\b" << "\\bInp\\b" << "\\bInput\\b" << "\\bInput \\b" << "\\bInputBox\\b" << "\\bInStr\\b" << "\\bInStRev\\b" << "\\bInt\\b" << "\\bIOCtl\\b" << "\\bIOCtl \\b" << "\\bIPMT\\b" << "\\bIRR\\b" << "\\bIsArray\\b" << "\\bIsBoolean\\b" << "\\bIsByte\\b" << "\\bIsCharacter\\b" << "\\bIsCollection\\b" << "\\bIsCString\\b" << "\\bIsCurrency\\b" << "\\bIsDate\\b" << "\\bIsDouble\\b" << "\\bIsEmpty\\b" << "\\bIsError\\b" << "\\bIsInt16\\b" << "\\bIsInt32\\b" << "\\bIsInt64\\b" << "\\bIsInteger\\b" << "\\bIsMissing\\b" << "\\bIsNull\\b" << "\\bIsNumeric\\b" << "\\bIsObject\\b" << "\\bIsShort\\b" << "\\bIsSingle\\b" << "\\bIsUInt16\\b" << "\\bIsUInt32\\b" << "\\bIsUInt64\\b" << "\\bIsLong\\b" << "\\bIsString\\b" << "\\bIsVariant\\b" << "\\bJoin\\b" << "\\bKill\\b" << "\\bLCase\\b" << "\\bLCase \\b" << "\\bLeft\\b" << "\\bLeft \\b" << "\\bLen\\b" << "\\bLine\\b" << "\\bLn\\b" << "\\bLoad\\b" << "\\bLoadPicture\\b" << "\\bLoadResData\\b" << "\\bLoadResPicture\\b" << "\\bLoadResString\\b" << "\\bLoc\\b" << "\\bLocate\\b" << "\\bLock\\b" << "\\bLOF\\b" << "\\bLog\\b" << "\\bLogb\\b" << "\\bLPos\\b" << "\\bLPrint\\b" << "\\bLTrim\\b" << "\\bLTrim \\b" << "\\bMax\\b" << "\\bMid \\b" << "\\bMin\\b" << "\\bMinute\\b" << "\\bMIRR\\b" << "\\bMKD \\b" << "\\bMkDir\\b" << "\\bMKDMBF \\b" << "\\bMKI \\b" << "\\bMKL \\b" << "\\bMKS\\b" << "\\bMKS \\b" << "\\bMKSMBF \\b" << "\\bMonth\\b" << "\\bMonthName\\b" << "\\bMsgBox\\b" << "\\bMTIMER\\b" << "\\bName\\b" << "\\bNow\\b" << "\\bNPER\\b" << "\\bNPV\\b" << "\\bNz\\b" << "\\bOct\\b" << "\\bOct \\b" << "\\bOpen\\b" << "\\bOut\\b" << "\\bOutput\\b" << "\\bPaint\\b" << "\\bPalette\\b" << "\\bPartition\\b" << "\\bPCopy\\b" << "\\bPeek\\b" << "\\bPMAP\\b" << "\\bPMT\\b" << "\\bPoint\\b" << "\\bPoke\\b" << "\\bPos\\b" << "\\bPPMT\\b" << "\\bPreset\\b" << "\\bPrint\\b" << "\\bPSet\\b" << "\\bPut\\b" << "\\bPV\\b" << "\\bQBCOLOR\\b" << "\\bRad\\b" << "\\bRaise\\b" << "\\bRaiseEvent\\b" << "\\bRaiseSignal\\b" << "\\bRandom\\b" << "\\bRandomize\\b" << "\\bRate\\b" << "\\bRemoveHandler\\b" << "\\bReplace\\b" << "\\bReset\\b" << "\\bRGB\\b" << "\\bRight\\b" << "\\bRight \\b" << "\\bRmDir\\b" << "\\bRND\\b" << "\\bRound\\b" << "\\bRTrim\\b" << "\\bRTrim \\b" << "\\bSavePicture\\b" << "\\bSaveSetting\\b" << "\\bScreen\\b" << "\\bSec\\b" << "\\bSecond\\b" << "\\bSeek\\b" << "\\bSeg\\b" << "\\bSendKeys\\b" << "\\bSetAttr\\b" << "\\bSgn\\b" << "\\bShell\\b" << "\\bSin\\b" << "\\bSleep\\b" << "\\bSln\\b" << "\\bSound\\b" << "\\bSpace\\b" << "\\bSpace \\b" << "\\bSpc\\b" << "\\bSplit\\b" << "\\bSqr\\b" << "\\bStick\\b" << "\\bStr\\b" << "\\bStr \\b" << "\\bStrComp\\b" << "\\bStrConv\\b" << "\\bString\\b" << "\\bString \\b" << "\\bStrReverse\\b" << "\\bSYD\\b" << "\\bTab\\b" << "\\bTan\\b" << "\\bTime\\b" << "\\bTime \\b" << "\\bTimeSerial\\b" << "\\bTimeValue\\b" << "\\bTrim\\b" << "\\bTrim \\b" << "\\bTypeName\\b" << "\\bTypeOf\\b" << "\\bUCase\\b" << "\\bUCase \\b" << "\\bUnLoad\\b" << "\\bUnLock\\b" << "\\bUsing\\b" << "\\bVal\\b" << "\\bVarType\\b" << "\\bView\\b" << "\\bWeekday\\b" << "\\bWeekdayName\\b" << "\\bWidth\\b" << "\\bWindow\\b" << "\\bWrite\\b" << "\\bYear\\b";
     foreach (QString pattern, builtinPatterns) {
         rule.pattern = QRegExp(pattern);
         rule.format = builtinFormat;
         highlightingRules.append(rule);
     }
     */
/*
     classFormat.setFontWeight(QFont::Bold);
     classFormat.setForeground(Qt::darkMagenta);
     rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
     rule.format = classFormat;
     highlightingRules.append(rule);*/

     markFormat.setForeground(Qt::red);
     markFormat.setFontFamily(sFamily); 
     markFormat.setFontPointSize(nSize);

     commentFormat.setForeground(Qt::darkGreen);
     commentFormat.setFontFamily(sFamily); 
     commentFormat.setFontPointSize(nSize);

     quotationFormat.setForeground(Qt::darkBlue);
     quotationFormat.setFontFamily(sFamily); 
     quotationFormat.setFontPointSize(nSize);
     /*
     rule.pattern = QRegExp("\"*\"");     
     rule.format = quotationFormat;
     highlightingRules.append(rule);*/

     /*
     functionFormat.setFontItalic(true);
     functionFormat.setForeground(Qt::blue);
     rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
     rule.format = functionFormat;
     highlightingRules.append(rule);*/

     /*
     rule.pattern = QRegExp("'[^\n]*");
     rule.format = singleLineCommentFormat;
     highlightingRules.append(rule);*/

     commentStartExpression = QRegExp("/\\*");
     commentEndExpression = QRegExp("\\*/");

     bSyntaxHighlighting = true;
 }

 void _sourcecodeeditor_syntaxhighlighter::highlightBlock(const QString &text)
 {
   int nLen = text.length();
  // QString ss;

     setFormat(0, nLen, normalFormat);
//     else ss = text;
     if (!bSyntaxHighlighting) return;

     int index = 0;
     int index2 = 0;
     int nString = 0;
     bool b = false;
     bool bString = false;
n:
     while (index < nLen){
       int i;
       for (i = index; i < nLen; i++){
         QChar c = text.at(i);

         if (c == '\"'){
           if (bString){
              setFormat(nString, i - nString + 1, quotationFormat);              
           } else {
             nString = i;
           }
           bString = !bString;
         }
         if (!bString && c == '\''){
           QString r = text.mid(index, i - index);

          if (sql_set.contains(r)){
            setFormat(index, i - index, sqlFormat);
          } else if (set.contains(r)){
            setFormat(index, i - index, keywordFormat);
          }

           setFormat(i, nLen - i, commentFormat);
           goto r;
         }
         if (c == '~' && bString == false){
           setFormat(i, nLen - i, markFormat);
           goto r;
         }
       
         if (!bString && ((!c.isLetter() && i == index && c != '_') || c.isSpace() || c.isMark() || c == '(')) break;

       }

       if (sql_set.contains(text.mid(index, i - index))/* && c2.isSpace()*/){
         setFormat(index, i - index, sqlFormat);
         index2 = index + (i - index);
       } else if (set.contains(text.mid(index, i - index))/* && c2.isSpace()*/){
         setFormat(index, i - index, keywordFormat);
         index2 = index + (i - index);
       }
       index = i + 1;
       
     }
t:
     index = index2;


     if (b == false && index == -1 && index2 && index2 + 1 < nLen){
       b = true;
       index = index2;
       goto n;
     }
r:

     setCurrentBlockState(0);

     int startIndex = 0;
     if (previousBlockState() != 1) startIndex = text.indexOf(commentStartExpression);

     while (startIndex >= 0) {
       int endIndex = text.indexOf(commentEndExpression, startIndex);
       int commentLength;
       if (endIndex == -1){
         setCurrentBlockState(1);
         commentLength = nLen - startIndex;
       } else {
         commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
       }
       setFormat(startIndex, commentLength, commentFormat);
       startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
     }
 }

 void _sourcecodeeditor_syntaxhighlighter::highlightBlock2(QString sFilename, QString &text)
 {
   text = text + "\n"; // WORKAROUND for last line

   int nLen = text.length();

     if (!bSyntaxHighlighting) return;

     int index = 0;
     int index2 = 0;
     int nString = 0;
     bool b = false;
     bool bString = false;
     bool bComment = false;    
n:
     while (index < nLen){
       int i;
       QChar c0 = ' ';
       for (i = index; i < nLen; i++){
         QChar c = text.at(i);

         if (c == '/' && text.at(i + 1) == '*') bComment = true;
         if (c == '*' && text.at(i + 1) == '/') bComment = false;

         if (bComment) continue;

         if (c == '\"'){
           if (bString){
             text.insert(nString + (i - nString + 1), "</font>"); 
             text.insert(nString, "<font color=\"DarkBlue\">"); nLen = text.length(); i += 30;

           } else {
             nString = i;
           }
           bString = !bString;
         }
         if (!bString && c == '\''){
           QString r = text.mid(index, i - index);

          if (sql_set.contains(r)){
            text.insert(index + (i - index),  "</font>"); 
            text.insert(index, "<font color=\"Orange\">"); nLen = text.length(); i += 26;
          } else if (set.contains(r)){
            text.insert(index + (i - index),  "</font>"); 
            text.insert(index, "<font color=\"Blue\">"); nLen = text.length(); i += 26;
          }
           

           text.insert(text.indexOf("\n", index), "</font>");
           text.insert(i, "<font color=\"DarkGreen\">"); nLen = text.length(); i += 31;
           i = text.indexOf("\n", index);
           bString = bString;

           continue;
         }
         if (c == '~' && bString == false){
           text.insert(text.indexOf("\n", index), "</font>");
           text.insert(i, "<font color=\"Red\">"); nLen = text.length(); i += 25;
           i = text.indexOf("\n", index);
           continue;
         }

          if (c == ' ' && c0 == ' '){
            text.replace(i, 1, "&nbsp;");
            
          }
          c0 = c;

         if (!bString && ((!c.isLetter() && i == index && c != '_') || c.isSpace() || c.isMark() || c == '(')) break;

       }

       if (sql_set.contains(text.mid(index, i - index))/* && c2.isSpace()*/){
         
         text.insert(index + (i - index), "</font>");
         text.insert(index, "<font color=\"Orange\">"); nLen = text.length(); i += 26;
         index2 = index + (i - index);
       } else if (set.contains(text.mid(index, i - index))){
         
         text.insert(index + (i - index), "</font>");
         text.insert(index, "<font color=\"Blue\">"); nLen = text.length(); i += 26;
         index2 = index + (i - index);
       }
       index = i + 1;
       
     }
t:
     index = index2;

     if (b == false && index == -1 && index2 && index2 + 1 < nLen){
       b = true;
       index = index2;
       goto n;
     }
r:


     int startIndex = 0;
    startIndex = text.indexOf(commentStartExpression);
     

     while (startIndex >= 0) {
       int endIndex = text.indexOf(commentEndExpression, startIndex);
       int commentLength;
       if (endIndex == -1){
         commentLength = nLen - startIndex;
       } else {
         commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
       }

       text.insert(startIndex + commentLength, "</font>"); 
       text.insert(startIndex, "<font color=\"DarkGreen\">"); nLen = text.length();

       
       startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
     }
     text.replace("\n", "<br>\n");

      QString s = "";
      s.prepend(QString("</title></head><body>\n<font face=\"Courier New, monospace\" color=\"#000000\">")); 
      s.prepend(sFilename); 
      s.prepend(QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\"><html><head><title>")); 
      text.prepend(s);

     text.append(QString("</font>\n</body></html>")); 

 }


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

#include "_qbe_sql_syntaxhighlighter.h"
#include "_mainwindow.h"

QSet<QString> set2;

 _qbe_sql_syntaxhighlighter::_qbe_sql_syntaxhighlighter(QTextDocument *parent)
     : QSyntaxHighlighter(parent)
 {
     HighlightingRule rule;

     

     if (set2.count() == 0){

        // create normal list
        set2 << "ABORT" << "ABS" << "ABSOLUTE" << "ACCESS" << "ACTION" << "ADA" << "ADD" << "ADMIN" << "AFTER" << "AGGREGATE" << "ALIAS" << "ALL" << "ALLOCATE" << "ALTER" << "ANALYSE" << "ANALYZE" << "AND" << "ANY" << "ARE" << "ARRAY" << "AS" << "ASC" << "ASENSITIVE" << "ASSERTION" << "ASSIGNMENT" << "" << "ASYMMETRIC" << "AT" << "ATOMIC" << "AUTHORIZATION" << "AVG" << "BACKWARD" << "BEFORE" << "BEGIN" << "BETWEEN" << "BIGINT" << "BINARY" << "BIT" << "BITVAR" << "BIT_LENGTH" << "BLOB" << "BOOLEAN" << "BOTH" << "BREADTH" << "BY" << "CACHE" << "CALL" << "CALLED" << "CARDINALITY" << "CASCADE" << "CASCADED" << "CASE" << "CAST" << "CATALOG" << "CATALOG_NAME" << "CHAIN" << "CHAR" << "CHARACTER" << "CHARACTERISTICS" << "CHARACTER_LENGTH" << "CHARACTER_SET_CATALOG" << "CHARACTER_SET_NAME" << "CHARACTER_SET_SCHEMA" << "CHAR_LENGTH" << "CHECK" << "CHECKED" << "CHECKPOINT" << "CLASS" << "CLASS_ORIGIN" << "CLOB" << "CLOSE" << "CLUSTER" << "COALESCE" << "COBOL" << "COLLATE" << "COLLATION" << "COLLATION_CATALOG" << "COLLATION_NAME" << "COLLATION_SCHEMA" << "COLUMN" << "COLUMN_NAME" << "COMMAND_FUNCTION" << "COMMAND_FUNCTION_CODE" << "COMMENT" << "COMMIT" << "COMMITTED" << "COMPLETION" << "CONDITION_NUMBER" << "CONNECT" << "CONNECTION" << "CONNECTION_NAME" << "CONSTRAINT" << "CONSTRAINTS" << "CONSTRAINT_CATALOG" << "CONSTRAINT_NAME" << "CONSTRAINT_SCHEMA" << "CONSTRUCTOR" << "CONTAINS" << "CONTINUE" << "CONVERSION" << "CONVERT" << "COPY" << "CORRESPONDING" << "COUNT" << "CREATE" << "CREATEDB" << "CREATEUSER" << "CROSS" << "CUBE" << "CURRENT" << "CURRENT_DATE" << "CURRENT_PATH" << "CURRENT_ROLE" << "CURRENT_TIME" << "CURRENT_TIMESTAMP" << "CURRENT_USER" << "CURSOR" << "CURSOR_NAME" << "CYCLE";
        set2 << "DATA" << "DATABASE" << "DATE" << "DATETIME_INTERVAL_CODE" << "DATETIME_INTERVAL_PRECISION" << "DAY" << "DEALLOCATE" << "DEC" << "DECIMAL" << "DECLARE" << "DEFAULT" << "DEFERRABLE" << "" << "DEFERRED" << "" << "DEFINED" << "DEFINER" << "DELETE" << "DELIMITER" << "DELIMITERS" << "DEPTH" << "DEREF" << "DESC" << "DESCRIBE" << "DESCRIPTOR" << "DESTROY" << "DESTRUCTOR" << "DETERMINISTIC" << "DIAGNOSTICS" << "DICTIONARY" << "ISCONNECT" << "" << "DISPATCH" << "DISTINCT" << "DO" << "DOMAIN" << "DOUBLE" << "DROP" << "DYNAMIC" << "DYNAMIC_FUNCTION" << "DYNAMIC_FUNCTION_CODE";
        set2 << "EACH" << "ELSE" << "ENCODING" << "ENCRYPTED" << "END" << "END-EXEC" << "EQUALS" << "ESCAPE" << "EVERY" << "EXCEPT" << "EXCEPTION" << "EXCLUSIVE" << "EXEC" << "EXECUTE" << "EXISTING" << "EXISTS" << "EXPLAIN" << "EXTERNAL" << "EXTRACT" << "FALSE" << "FETCH" << "FINAL" << "FIRST" << "FLOAT" << "FOR" << "FORCE" << "FOREIGN" << "FORTRAN" << "FORWARD" << "FOUND" << "FREE" << "FREEZE" << "FROM" << "FULL" << "FUNCTION";
        set2 << "GENERAL" << "GENERATED" << "GET" << "GLOBAL" << "GO" << "" << "GOTO" << "GRANT" << "GRANTED" << "GROUP" << "GROUPING" << "HANDLER" << "HAVING" << "HIERARCHY" << "HOLD" << "HOST" << "HOUR" << "IDENTITY" << "IGNORE" << "ILIKE" << "IMMEDIATE" << "IMMUTABLE" << "IMPLEMENTATION" << "IMPLICIT" << "IN" << "INCREMENT" << "INDEX" << "INDICATOR" << "INFIX" << "INHERITS" << "INITIALIZE" << "INITIALLY" << "INNER" << "INOUT" << "" << "INPUT" << "INSENSITIVE" << "INSERT" << "INSTANCE" << "INSTANTIABLE" << "INSTEAD" << "INT" << "INTEGER" << "INTERSECT" << "INTERVAL" << "INTO" << "INVOKER" << "IS" << "ISNULL" << "ISOLATION" << "ITERATE";
        set2 << "JOIN" << "KKEY" << "KEY_MEMBER" << "KEY_TYPE" << "LANCOMPILER" << "LANGUAGE" << "LARGE" << "LAST" << "LATERAL" << "LEADING" << "LEFT" << "LENGTH" << "LESS" << "LEVEL" << "LIKE" << "LIMIT" << "LISTEN" << "LOAD" << "LOCAL" << "LOCALTIME" << "LOCALTIMESTAMP" << "LOCATION" << "LOCATOR" << "LOCK" << "LOWER" << "MAP" << "MATCH" << "MAX" << "MAXVALUE" << "MESSAGE_LENGTH" << "MESSAGE_OCTET_LENGTH" << "MESSAGE_TEXT" << "METHOD" << "MIN" << "MINUTE" << "MINVALUE" << "MOD" << "MODE" << "MODIFIES" << "MODIFY" << "MODULE" << "MONTH" << "MORE" << "MOVE" << "MUMPS" << "NAME" << "NAMES" << "NATIONAL" << "NATURAL" << "NCHAR" << "NCLOB" << "NEW" << "NEXT" << "NO" << "NOCREATEDB" << "NOCREATEUSER" << "NONE" << "NOT" << "NOTHING" << "NOTIFY" << "NOTNULL" << "NULL" << "NULLABLE" << "NULLIF" << "NUMBER" << "NUMERIC";
        set2 << "OBJECT" << "OCTET_LENGTH" << "OF" << "OFF" << "OFFSET" << "OIDS" << "OLD" << "ON" << "ONLY" << "OPEN" << "" << "OPERATION" << "OPERATOR" << "OPTION" << "OPTIONS" << "OR" << "ORDER" << "ORDINALITY" << "OUT" << "OUTER" << "OUTPUT" << "OVERLAPS" << "OVERLAY" << "OVERRIDING" << "OWNER" << "PAD" << "PARAMETER" << "PARAMETERS" << "PARAMETER_MODE" << "PARAMETER_NAME" << "PARAMETER_ORDINAL_POSITION" << "PARAMETER_SPECIFIC_CATALOG" << "PARAMETER_SPECIFIC_NAME" << "PARAMETER_SPECIFIC_SCHEMA" << "PARTIAL" << "PASCAL" << "PASSWORD" << "PATH" << "PENDANT" << "PLACING" << "PLI" << "POSITION" << "POSTFIX" << "PRECISION" << "PREFIX" << "PREORDER" << "PREPARE" << "PRESERVE" << "PRIMARY" << "PRIOR" << "PRIVILEGES" << "PROCEDURAL" << "PROCEDURE" << "PUBLIC" << "READ" << "READS" << "REAL" << "RECHECK" << "RECURSIVE" << "REF" << "REFERENCES" << "REFERENCING" << "REINDEX" << "RELATIVE" << "RENAME" << "REPEATABLE" << "REPLACE" << "RESET" << "RESTRICT" << "RESULT" << "RETURN" << "RETURNED_LENGTH" << "RETURNED_OCTET_LENGTH" << "RETURNED_SQLSTATE" << "RETURNS" << "REVOKE" << "RIGHT" << "ROLE" << "ROLLBACK" << "ROLLUP" << "ROUTINE" << "ROUTINE_CATALOG" << "ROUTINE_NAME" << "ROUTINE_SCHEMA" << "ROW" << "ROWS" << "ROW_COUNT" << "RULE";
        set2 << "SAVEPOINT" << "SCALE" << "SCHEMA" << "SCHEMA_NAME" << "SCOPE" << "SCROLL" << "SEARCH" << "SECOND" << "SECTION" << "SECURITY" << "SELECT" << "SELF" << "SENSITIVE" << "SEQUENCE" << "SERIALIZABLE" << "SERVER_NAME" << "SESSION" << "SESSION_USER" << "SET" << "SETOF" << "SETS" << "SHARE" << "SHOW" << "SIMILAR" << "SIMPLE" << "SIZE" << "SMALLINT" << "SOME" << "SOURCE" << "SPACE" << "SPECIFIC" << "SPECIFICTYPE" << "SPECIFIC_NAME" << "SQL" << "SQLCODE" << "SQLERROR" << "SQLEXCEPTION" << "SQLSTATE" << "SQLWARNING" << "STABLE" << "START" << "STATE" << "STATEMENT" << "STATIC" << "STATISTICS" << "STDIN" << "STDOUT" << "STORAGE" << "STRICT" << "STRUCTURE" << "STYLE" << "SUBCLASS_ORIGIN" << "SUBLIST" << "SUBSTRING" << "SUM" << "SYMMETRIC" << "SYSID" << "SYSTEM" << "SYSTEM_USER";
        set2 << "TABLE" << "TABLE_NAME" << "TEMP" << "TEMPLATE" << "TEMPORARY" << "TERMINATE" << "THAN" << "THEN" << "TIME" << "TIMESTAMP" << "TIMEZONE_HOUR" << "TIMEZONE_MINUTE" << "TO" << "TOAST" << "TRAILING" << "TRANSACTION" << "TRANSACTIONS_COMMITTED" << "TRANSACTIONS_ROLLED_BACK" << "TRANSACTION_ACTIVE" << "TRANSFORM" << "TRANSFORMS" << "TRANSLATE" << "TRANSLATION" << "TREAT" << "TRIGGER" << "TRIGGER_CATALOG" << "TRIGGER_NAME" << "TRIGGER_SCHEMA" << "TRIM" << "TRUE" << "TRUNCATE" << "TRUSTED" << "TYPE" << "UNCOMMITTED" << "UNDER" << "UNENCRYPTED" << "UNION" << "UNIQUE" << "UNKNOWN" << "UNLISTEN" << "UNNAMED" << "UNNEST" << "UNTIL" << "UPDATE" << "" << "UPPER" << "USAGE" << "USER" << "USER_DEFINED_TYPE_CATALOG" << "USER_DEFINED_TYPE_NAME" << "USER_DEFINED_TYPE_SCHEMA" << "USING";
        set2 << "VACUUM" << "VALID" << "VALIDATOR" << "VALUE" << "VALUES" << "VARCHAR" << "VARIABLE" << "VARYING" << "VERBOSE" << "VERSION" << "VIEW" << "VOLATILE" << "WHEN" << "WHENEVER" << "WHERE" << "WITH" << "WITHOUT" << "WORK" << "WRITE" << "YEAR" << "ZONE";
        set2 << "ASC";

        // create normal list
        QList<QString> list = set2.toList();
        foreach (QString value, list){
          QString s = value.toLower();
          s = s.left(1).toUpper() + s.mid(1);
          set2 << s;
        }

        // create lowercase list
        list = set2.toList();
        foreach (QString value, list){
          set2 << value.toLower();
        }
     }


     QString sFamily = EXTERN_my_mainwindow->getPreference("FontName");
     int nSize = EXTERN_my_mainwindow->getPreference("FontSize").toInt();


     normalFormat.setFontFamily(sFamily); 
     normalFormat.setFontPointSize(nSize);

     keywordFormat.setForeground(Qt::blue);
     keywordFormat.setFontFamily(sFamily); 
     keywordFormat.setFontPointSize(nSize);

     quotationFormat.setForeground(Qt::darkBlue);
     quotationFormat.setFontFamily(sFamily); 
     quotationFormat.setFontPointSize(nSize);
 }

 void _qbe_sql_syntaxhighlighter::highlightBlock(const QString &text)
 {
   int nLen = text.length();

     setFormat(0, nLen, normalFormat);

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
        
         if (!bString && ((!c.isLetter() && i == index && c != '_') || c.isSpace() || c.isMark() || c == '(')) break;

       }

       if (set2.contains(text.mid(index, i - index))){
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
;
 }


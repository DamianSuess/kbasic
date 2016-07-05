
new_class(pcode___strings, 0, 0); 

new_method(true, pcode___strings, pcode___strings___strings, pcode___strings);
new_method(true, pcode___strings, pcode___strings__METHOD_Len, pcode__INTEGER);
	 new_param("Text", pcode__QString, false);
new_method(true, pcode___strings, pcode___strings__METHOD_Append, pcode__VOID);
	 new_param("Text", pcode__QString, false);
new_method(true, pcode___strings, pcode___strings__METHOD_Prepend, pcode__VOID);
	 new_param("Index", pcode__INTEGER, false);
new_method(true, pcode___strings, pcode___strings__METHOD_Get, pcode__QString);

	 new_param("Index", pcode__INTEGER, false);
	 new_param("Text", pcode__QString, false);
new_method(true, pcode___strings, pcode___strings__METHOD_Set, pcode__VOID);

	 new_param("Index", pcode__INTEGER, false);
	 new_param("Text", pcode__QString, false);
new_method(true, pcode___strings, pcode___strings__METHOD_Insert, pcode__VOID);

	 new_param("Index", pcode__INTEGER, false);
	 new_param("Text", pcode__QString, false);
new_method(true, pcode___strings, pcode___strings__METHOD_Replace, pcode__VOID);

	 new_param("Index", pcode__INTEGER, false);
new_method(true, pcode___strings, pcode___strings__METHOD_Remove, pcode__VOID);

new_method(true, pcode___strings, pcode___strings__METHOD_Sort, pcode__VOID);

new_method(true, pcode___strings, pcode___strings__METHOD_RemoveAll, pcode__VOID);

new_method(true, pcode___strings, pcode___strings__FOR, pcode__POINTER);
new_method(true, pcode___strings, pcode___strings__EACH, pcode__POINTER);

new_method(true, pcode___strings, pcode___strings__GET, pcode__QString);
new_method(true, pcode___strings, pcode___strings__SET, pcode__VOID);

  new_param("Separator", pcode__QString, false);
new_method(true, pcode___strings, pcode___strings__METHOD_Join, pcode__QString);

	 new_param("Text", pcode__QString, false);
	 new_param("CaseSensitive", pcode__BOOLEAN, true, true);
new_method(true, pcode___strings, pcode___strings__METHOD_Contains, pcode__VOID);

/*
new_method(true, pcode___strings, pcode___strings__METHOD_ReadBinary, pcode__QString);

	 new_param("Binary", pcode__QString, false);
new_method(true, pcode___strings, pcode___strings__METHOD_WriteBinary, pcode__VOID);
*/

	 new_param("Text", pcode__QString, false);
	 new_param("Position", pcode__INTEGER, true, 1);
new_method(true, pcode___strings, pcode___strings__METHOD_IndexOf, pcode__INTEGER);

	 new_param("Text", pcode__QString, false);
	 new_param("Position", pcode__INTEGER, true, -1);
new_method(true, pcode___strings, pcode___strings__METHOD_LastIndexOf, pcode__INTEGER);

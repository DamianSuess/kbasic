
new_class(pcode___dir, 0, 0); 


	 new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Create, pcode__BOOLEAN);

	 new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_RecursiveCreate, pcode__BOOLEAN);

	 new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Remove, pcode__BOOLEAN);
	 new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_RecursiveRemove, pcode__BOOLEAN);

	 new_param("Path", pcode__QString, false);
	 new_param("NameFilter", pcode__QString, false);
	 new_param("Filter", pcode__QString, true, "NoFilter");
	 new_param("Sorting", pcode__QString, true, "NoSort");
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_FindFile, pcode___strings);

	 new_param("Path", pcode__QString, false);
	 new_param("NameFilter", pcode__QString, false);
	 new_param("Filter", pcode__QString, true, "NoFilter");
	 new_param("Sorting", pcode__QString, true, "NoSort");
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_RecursiveFindFile, pcode___strings);

	 new_param("Path", pcode__QString, false);
	 new_param("NameFilter", pcode___strings, false);
	 new_param("Filter", pcode__QString, true, "NoFilter");
	 new_param("Sorting", pcode__QString, true, "NoSort");
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_FindFile1, pcode___strings);

	 new_param("Path", pcode__QString, false);
	 new_param("NameFilter", pcode___strings, false);
	 new_param("Filter", pcode__QString, true, "NoFilter");
	 new_param("Sorting", pcode__QString, true, "NoSort");
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_RecursiveFindFile1, pcode___strings);

	 new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_FileList, pcode___strings);
	 new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_RecursiveFileList, pcode___strings);

  new_param("SourcePath", pcode__QString, false);
  new_param("DestinationPath", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Copy, pcode__BOOLEAN);

  new_param("SourcePath", pcode__QString, false);
  new_param("DestinationPath", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Move, pcode__BOOLEAN);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Exists, pcode__BOOLEAN);

/*
  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_ExistsAndIsDir, pcode__BOOLEAN);
*/

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_DateTimeCreated, pcode__QString);
  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_DateTimeUpdated, pcode__QString);
  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_DateTimeRead, pcode__QString);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Owner, pcode__QString);
  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Group, pcode__QString);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_WithNativeSeparators, pcode__QString);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_WithoutNativeSeparators, pcode__QString);


  new_param("Path", pcode__QString, false);
  new_param("Who", pcode__QString, true, "User");
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_IsReadable, pcode__BOOLEAN);
  new_param("Path", pcode__QString, false);
  new_param("Who", pcode__QString, true, "User");
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_IsWriteable, pcode__BOOLEAN);
  new_param("Path", pcode__QString, false);
  new_param("Who", pcode__QString, true, "User");
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_IsExecutable, pcode__BOOLEAN);
  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_IsHidden, pcode__BOOLEAN);

new_staticmethod(true, pcode___dir, pcode___dir__METHOD_TempPath, pcode__QString);

new_staticmethod(true, pcode___dir, pcode___dir__METHOD_RootPath, pcode__QString);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_IsDir, pcode__BOOLEAN);


new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Drives, pcode___strings);

new_staticmethod(true, pcode___dir, pcode___dir__METHOD_HomePath, pcode__QString);


  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_BundleName, pcode__QString);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_SymLinkTarget, pcode__QString);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Name, pcode__QString);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Path, pcode__QString);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_Suffix, pcode__QString);


  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_IsRoot, pcode__BOOLEAN);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_IsRelative, pcode__BOOLEAN);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_IsSymLink, pcode__BOOLEAN);

  new_param("Path", pcode__QString, false);
new_staticmethod(true, pcode___dir, pcode___dir__METHOD_IsBundle, pcode__BOOLEAN);


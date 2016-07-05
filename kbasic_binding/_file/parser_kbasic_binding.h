
new_class(pcode___file, 0, 0); 


	 new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Size, pcode__LONG);

	 new_param("FileName", pcode__QString, false);
	 new_param("NewSize", pcode__LONG, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Resize, pcode__LONG);

	 new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Truncate, pcode__BOOLEAN);


  new_param("FileName", pcode__QString, false);
  new_param("Yes/No", pcode__BOOLEAN, false);
  new_param("Who", pcode__QString, true, "User");
new_staticmethod(true, pcode___file, pcode___file__METHOD_SetReadable, pcode__BOOLEAN);
  new_param("FileName", pcode__QString, false);
  new_param("Yes/No", pcode__BOOLEAN, false);
  new_param("Who", pcode__QString, true, "User");
new_staticmethod(true, pcode___file, pcode___file__METHOD_SetWriteable, pcode__BOOLEAN);
  new_param("FileName", pcode__QString, false);
  new_param("Yes/No", pcode__BOOLEAN, false);
  new_param("Who", pcode__QString, true, "User");
new_staticmethod(true, pcode___file, pcode___file__METHOD_SetExecutable, pcode__BOOLEAN);

  new_param("FileName", pcode__QString, false);
  new_param("Codec", pcode__QString, true, "UTF-8");
  new_param("AutoDetectUnicode", pcode__BOOLEAN, true, true);
  new_param("GenerateByteOrderMark", pcode__BOOLEAN, true, true);
new_staticmethod(true, pcode___file, pcode___file__METHOD_ReadText, pcode__QString);

  new_param("FileName", pcode__QString, false);
  new_param("Text", pcode__QString, false);
  new_param("Append", pcode__BOOLEAN, true, false);
  new_param("Codec", pcode__QString, true, "UTF-8");
  new_param("AutoDetectUnicode", pcode__BOOLEAN, true, true);
  new_param("GenerateByteOrderMark", pcode__BOOLEAN, true, true);
new_staticmethod(true, pcode___file, pcode___file__METHOD_WriteText, pcode__BOOLEAN);


  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_ReadBinary, pcode__QString);

  new_param("FileName", pcode__QString, false);
  new_param("Binary", pcode__QString, false);
  new_param("Append", pcode__BOOLEAN, true, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_WriteBinary, pcode__BOOLEAN);

  new_param("SourceFileName", pcode__QString, false);
  new_param("DestinationFileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Link, pcode__BOOLEAN);



	 new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Create, pcode__BOOLEAN);

   new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Remove, pcode__BOOLEAN);

  new_param("SourceFileName", pcode__QString, false);
  new_param("DestinationFileName", pcode__QString, false);
  new_param("Overwrite", pcode__BOOLEAN, true, true);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Copy, pcode__BOOLEAN);

  new_param("SourceFileName", pcode__QString, false);
  new_param("DestinationFileName", pcode__QString, false);
  new_param("Overwrite", pcode__BOOLEAN, true, true);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Rename, pcode__BOOLEAN);

  new_param("SourceFileName", pcode__QString, false);
  new_param("DestinationFileName", pcode__QString, false);
  new_param("Overwrite", pcode__BOOLEAN, true, true);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Move, pcode__BOOLEAN);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Exists, pcode__BOOLEAN);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_DateTimeCreated, pcode__QString);
  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_DateTimeUpdated, pcode__QString);
  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_DateTimeRead, pcode__QString);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Owner, pcode__QString);
  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Group, pcode__QString);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_WithNativeSeparators, pcode__QString);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_WithoutNativeSeparators, pcode__QString);


  new_param("FileName", pcode__QString, false);
  new_param("Who", pcode__QString, true, "User");
new_staticmethod(true, pcode___file, pcode___file__METHOD_IsReadable, pcode__BOOLEAN);
  new_param("FileName", pcode__QString, false);
  new_param("Who", pcode__QString, true, "User");
new_staticmethod(true, pcode___file, pcode___file__METHOD_IsWriteable, pcode__BOOLEAN);
  new_param("FileName", pcode__QString, false);
  new_param("Who", pcode__QString, true, "User");
new_staticmethod(true, pcode___file, pcode___file__METHOD_IsExecutable, pcode__BOOLEAN);
  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_IsHidden, pcode__BOOLEAN);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_IsFile, pcode__BOOLEAN);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_SymLinkTarget, pcode__QString);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Name, pcode__QString);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_NameWithoutSuffix, pcode__QString);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Path, pcode__QString);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_Suffix, pcode__QString);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_IsRelative, pcode__BOOLEAN);

  new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___file, pcode___file__METHOD_IsSymLink, pcode__BOOLEAN);


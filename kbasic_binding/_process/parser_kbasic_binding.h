
new_class(pcode___process, 0, 0); 



	 new_param("FileName", pcode__QString, false);
	 new_param("WaitForFinished", pcode__BOOLEAN, true, false);
new_staticmethod(true, pcode___process, pcode___process__METHOD_Run, pcode__BOOLEAN);

	 new_param("FileName", pcode__QString, false);
	 new_param("Arguments", pcode___strings, false);
	 new_param("WaitForFinished", pcode__BOOLEAN, true, false);
new_staticmethod(true, pcode___process, pcode___process__METHOD_Run1, pcode__BOOLEAN);

/*
	 new_param("FileName", pcode__QString, false);
	 new_param("Arguments", pcode___strings, false);
	 new_param("Environment", pcode___strings, false);
	 new_param("WaitForFinished", pcode__BOOLEAN, true, false);
new_staticmethod(true, pcode___process, pcode___process__METHOD_Run2, pcode__BOOLEAN);
*/

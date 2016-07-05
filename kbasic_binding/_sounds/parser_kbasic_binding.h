
new_class(pcode___sounds, 0, 0); 


	 new_param("Id", pcode__QString, false);
	 new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___sounds, pcode___sounds__METHOD_SetSound, pcode__t_boolean);


	 new_param("Id", pcode__QString, false);
	 new_param("FileName", pcode__QString, false);
new_staticmethod(true, pcode___sounds, pcode___sounds__METHOD_Load, pcode__t_boolean);


	 new_param("Id", pcode__QString, false);
new_staticmethod(true, pcode___sounds, pcode___sounds__METHOD_Play, pcode__t_boolean);

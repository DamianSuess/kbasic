
new_class(pcode___preferences, 0, 0); 

   new_param("PreferenceId", pcode__QString, false);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_Has, pcode__BOOLEAN);

   new_param("PreferenceId", pcode__QString, false);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_Remove, pcode__VOID);
/*
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_Load, pcode__BOOLEAN);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_Save, pcode__BOOLEAN);
*/
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_Ids, pcode___strings);


   new_param("PreferenceId", pcode__QString, false);
   new_param("Value", pcode__BOOLEAN, false);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_SetBoolean, pcode__VOID);

   new_param("PreferenceId", pcode__QString, false);
   new_param("Value", pcode__INTEGER, false);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_SetInteger, pcode__VOID);

   new_param("PreferenceId", pcode__QString, false);
   new_param("Value", pcode__QString, false);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_SetString, pcode__VOID);

   new_param("PreferenceId", pcode__QString, false);
   new_param("Value", pcode__DOUBLE, false);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_SetDouble, pcode__VOID);


   new_param("PreferenceId", pcode__QString, false);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_Boolean, pcode__BOOLEAN);

   new_param("PreferenceId", pcode__QString, false);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_Integer, pcode__INTEGER);

   new_param("PreferenceId", pcode__QString, false);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_String, pcode__QString);

   new_param("PreferenceId", pcode__QString, false);
new_staticmethod(true, pcode___preferences, pcode___preferences__METHOD_Double, pcode__DOUBLE);



new_class(pcode___menubar, 0, 0); 

new_method(true, pcode___menubar, pcode___menubar___menubar, pcode___menubar);

  new_param("Form", pcode___form, false);
new_method(true, pcode___menubar, pcode___menubar___menubar1, pcode___menubar);

	 new_param("Name", pcode__QString, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_MenuBarItem, pcode___menubaritem);



	 new_param("Tag", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__t_boolean, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_SetWithTag, pcode__VOID);

	 new_param("Tag", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__t_integer, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_SetWithTag1, pcode__VOID);

	 new_param("Tag", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__QString, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_SetWithTag2, pcode__VOID);


	 new_param("Group", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__t_boolean, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_SetWithGroup, pcode__VOID);

	 new_param("Group", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__t_integer, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_SetWithGroup1, pcode__VOID);

	 new_param("Group", pcode__QString, false);
	 new_param("PropertyName", pcode__QString, false);
	 new_param("Value", pcode__QString, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_SetWithGroup2, pcode__VOID);


	 new_param("Visible", pcode__t_boolean, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_SetVisible, pcode__VOID);

new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_IsVisible, pcode__t_boolean);

new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_Show, pcode__VOID);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_Hide, pcode__VOID);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_ToggleVisible, pcode__VOID);

   new_param("MenuBarItemName", pcode__QString, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_Remove, pcode__VOID);

new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_RemoveAll, pcode__VOID);

   new_param("ParentMenuBarItemName", pcode__QString, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_RemoveAllChilds, pcode__VOID);


   new_param("ParentMenuBarItemName", pcode__QString, false);
   new_param("MenuBarItem", pcode___menubaritem, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_AppendMenuBarItem, pcode__VOID);

   new_param("MenuBarItem", pcode___menubaritem, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_AppendMenuBarItem1, pcode__VOID);

/*
   new_param("ParentMenuBarItemName", pcode__QString, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_AppendSeparator, pcode__VOID);
*/
   new_param("MenuBarItem", pcode___menubaritem, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_AppendMenu, pcode__VOID);

   new_param("ParentMenuBarItemName", pcode__QString, false);
   new_param("MenuBarItem", pcode___menubaritem, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_AppendMenu1, pcode__VOID);

   new_param("ParentMenuBarItemName", pcode__QString, false);
   new_param("MenuBarItem", pcode___menubaritem, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_AppendChildMenu, pcode__VOID);

   new_param("MenuBarItem", pcode___menubaritem, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_AppendChildMenu1, pcode__VOID);



   new_param("MenuBarItem", pcode___menubaritem, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_AppendContextMenu, pcode__VOID);

   new_param("MenuBarItem", pcode__QString, false);
   new_param("X", pcode__INTEGER, false);
   new_param("Y", pcode__INTEGER, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_ShowContextMenu, pcode__VOID);


   new_param("X", pcode__INTEGER, false);
   new_param("Y", pcode__INTEGER, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_ShowContextMenu1, pcode__VOID);



/*
   new_param("Name", pcode__QString, false);
   new_param("Icon", pcode__QString, false);
   new_param("Caption", pcode__QString, false);
   new_param("Key", pcode__QString, false);
   new_param("Tag", pcode__QString, false);
   new_param("Enabled", pcode__t_boolean, false);
new_staticmethod(true, pcode___menubar, pcode___menubar__METHOD_AppendMenuBarItem, pcode__VOID);
*/

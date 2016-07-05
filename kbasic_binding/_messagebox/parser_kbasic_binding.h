
new_class(pcode___messagebox, 0, 0); 


    new_param("Caption", pcode__QString, false);
    new_param("Text", pcode__QString, true, "");
    new_param("Buttons", pcode__QString, true, "Ok");
    new_param("DefaultButton", pcode__QString, true, "NoButton");
    new_param("DetailedText", pcode__QString, true, "");
    new_param("Icon", pcode__QString, true, "");
new_staticmethod(true, pcode___messagebox, pcode___messagebox__METHOD_Show, pcode__QString);

    new_param("Caption", pcode__QString, false);
    new_param("Text", pcode__QString, true, "");
    new_param("Buttons", pcode__QString, true, "Ok");
    new_param("DefaultButton", pcode__QString, true, "NoButton");
new_staticmethod(true, pcode___messagebox, pcode___messagebox__METHOD_Critical, pcode__QString);

    new_param("Caption", pcode__QString, false);
    new_param("Text", pcode__QString, true, "");
    new_param("Buttons", pcode__QString, true, "Ok");
    new_param("DefaultButton", pcode__QString, true, "NoButton");
new_staticmethod(true, pcode___messagebox, pcode___messagebox__METHOD_Information, pcode__QString);

    new_param("Caption", pcode__QString, false);
    new_param("Text", pcode__QString, true, "");
    new_param("Buttons", pcode__QString, true, "Ok");
    new_param("DefaultButton", pcode__QString, true, "NoButton");
new_staticmethod(true, pcode___messagebox, pcode___messagebox__METHOD_Question, pcode__QString);

    new_param("Caption", pcode__QString, false);
    new_param("Text", pcode__QString, true, "");
    new_param("Buttons", pcode__QString, true, "Ok");
    new_param("DefaultButton", pcode__QString, true, "NoButton");
new_staticmethod(true, pcode___messagebox, pcode___messagebox__METHOD_Warning, pcode__QString);





new_class(pcode___bits, 0, 0); 

new_method(true, pcode___bits, pcode___bits___bits, pcode___bits);

	 new_param("Value", pcode__BYTE, false);
new_method(true, pcode___bits, pcode___bits__METHOD_SetByte, pcode__VOID);

	 new_param("Value", pcode__SHORT, false);
new_method(true, pcode___bits, pcode___bits__METHOD_SetShort, pcode__VOID);

	 new_param("Value", pcode__INTEGER, false);
new_method(true, pcode___bits, pcode___bits__METHOD_SetInteger, pcode__VOID);

//	 new_param("Value", pcode__LONG, false);
//new_method(true, pcode___bits, pcode___bits__METHOD_SetLong, pcode__VOID);

new_method(true, pcode___bits, pcode___bits__METHOD_Byte, pcode__BYTE);
new_method(true, pcode___bits, pcode___bits__METHOD_Short, pcode__SHORT);
new_method(true, pcode___bits, pcode___bits__METHOD_Integer, pcode__INTEGER);
//new_method(true, pcode___bits, pcode___bits__METHOD_Long, pcode__LONG);

	 new_param("Position", pcode__INTEGER, false);
	 new_param("YesNo", pcode__BOOLEAN, false);
new_method(true, pcode___bits, pcode___bits__METHOD_SetBit, pcode__VOID);

	 new_param("Position", pcode__INTEGER, false);
new_method(true, pcode___bits, pcode___bits__METHOD_Bit, pcode__BOOLEAN);

	 new_param("Position", pcode__INTEGER, false);
new_method(true, pcode___bits, pcode___bits__METHOD_TestBit, pcode__BOOLEAN);

	 new_param("Position", pcode__INTEGER, false);
new_method(true, pcode___bits, pcode___bits__METHOD_ToogleBit, pcode__VOID);

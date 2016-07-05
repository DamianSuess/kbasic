/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) 
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/



#ifndef MEMORY_VARIABLE_H
#define MEMORY_VARIABLE_H



#include <stdio.h>
#include <qmap.h>


#include <qlist.h>
 
#include "../kbshared/pcode.h"
#include "utility.h"
#include "memory_type.h"
#include "const.h"





class memory_variable;

struct variable {
	char acModule[MAX_IDENTIFIER];
	char acSub[MAX_IDENTIFIER];
	char acName[MAX_IDENTIFIER];
	int  nType;
	int  nTypeSize;
	int  nStructSize;
	int  nStructSize2;
	t_array a;
	bool bByVal;
  bool bIsMissing;

  // konstanten werden auch als memory_variable gespeichert, 

	int nId;


	char 		 *struct_;
	char 		 *struct2_; // used for qt bindings objects with are not pointers, but references

	int nVariantType;
	
	bool bReference;
	int nReferenceId;
	int nReferenceOffset;
  t_scope ReferenceScope;
  memory_variable *ReferenceVariablePool;
  t_array ReferenceArray;

	bool bStatic;
  int nScope;



};

class memory_variable
{
public:
	static int nIdCounter;


	memory_variable				();
	~memory_variable				();

  void removeAllExceptObjects			();

  void 		remove			(variable *v);

  static void resetIdCounter	();
  static int addIdCounter();
  static void setIdCounter(int n);

	int 		declare			(
                      const char *acModule, 
                      const char *acSub, 
                      const char *acName, 
                      int nType, 
                      t_array *a, 
                      bool bByVal, 
                      bool bReference, 
                      bool bStatic, 
                      bool bInit, 
                      int nScope, 
                      int nTypeSize,
                      int nId
                      );

	int 		declare			(int nType, t_array *a, bool bByVal, bool bStatic, int nId = -1);
	
  void 		declare		(int nId, bool b);
  void 		declare		(int nId, int n);

  int 		redeclare		(int nId, int nType, t_array *a, bool bPreserve);

  bool 		exist				(int nId);
	bool 		exist				(const char *acModule, const char *acSub, const char *acName);
  bool		findVar	    (int nId, const char **acModule, const char **acSub, const char **acName);

	bool 		undeclare		(int nId);
	bool 		undeclare		(const char *acModule, const char *acSub, const char *acName);
	int			type				(int nId);
	int			type				(const char *acModule, const char *acSub, const char *acName);
	
  const char   *getModule		(int nId);
	const char   *getSub			(int nId);
	const char   *getName			(int nId);

	t_array  *getArray		(int nId);

  bool isArray		(int nId);
  bool isEmpty		(int nId);


	bool	  isByVal			(int nId);
	bool	  isByRef			(int nId);
	bool	  isMissing		(int nId);

	int			getId				(const char *acModule, const char *acSub, const char *acName);
//	int			getId				(const char *acModule, const char *acSub, const char *acName, nType);

	int			getId				();

  void     setTypeSize	  (int nId, int n);
  int     getTypeSize			(int nId);
	int     getStructSize		(int nId);


	bool isStatic(int nId);

	bool isPrivate(int nId);
	bool isPublic(int nId);
	bool isProtected(int nId);

	int getScope(int nId);

  inline t_pointer		getBindingParentClassPointer()
  {
     return vBindingParentClassPointer;	
  }

  inline int getBindingParentClassType()
  {
     return nBindingParentClassType;	
  }

  //t_pointer		getBindingParentClassPointer(int nId);  
  //int getBindingParentClassType(int nId);

	//int			getVariantType();
	//bool 		setVariantType (int nId, char *s, char *s2, int nOffset);

	t_boolean	getBoolean	(int nId, int nOffset = 0);
	//t_boolean	getBoolean	(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);

  t_qstring  getQString		(int nId, int nOffset = 0);
  t_cstring  getCString		(int nId, int nOffset = 0);
	//t_string  getString		(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);

  t_qstring  getLQString		(int nId, int nOffset = 0);
  t_cstring  getLCString		(int nId, int nOffset = 0);
	//t_string  getLString		(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);

	t_byte		getByte			(int nId, int nOffset = 0);
	//t_byte		getByte			(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
  t_short		  getShort			(int nId, int nOffset = 0);
	//t_short 	  getShort 	(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
  t_integer	getInteger	(int nId, int nOffset = 0);
	//t_integer	getInteger	(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
	t_long 		getLong			(int nId, int nOffset = 0);
	//t_long 		getLong			(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);

  t_single	getSingle		(int nId, int nOffset = 0);
	//t_single	getSingle		(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
  t_double 	getDouble 	(int nId, int nOffset = 0);
	//t_double 	getDouble 	(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
/*
  t_int16			getInt16			(int nId, int nOffset = 0);
	//t_int16   	getInt16 	(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
  t_int32			getInt32			(int nId, int nOffset = 0);
	//t_int32   	getInt32 	(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
  t_int64			getInt64			(int nId, int nOffset = 0);
	//t_int64 	  getInt64 	(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
  t_uint16		getUInt16			(int nId, int nOffset = 0);
	//t_uint16 	  getUInt16 	(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
  t_uint32		getUInt32			(int nId, int nOffset = 0);
	//t_uint32 	  getUInt32 	(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
  t_uint64		getUInt64			(int nId, int nOffset = 0);
	//t_uint64   	getUInt64 	(const char *acModule, const char *acSub, const char *acName, int nOffset = 0);
*/
  t_variant		getVariant			(int nId, int nOffset = 0);

	t_boolean 		getVariant_Boolean	(int nId, int nOffset = 0);

  t_qstring 		getVariant_QString	(int nId, int nOffset = 0);
  t_cstring 		getVariant_CString	(int nId, int nOffset = 0);

  t_byte 		getVariant_Byte		  (int nId, int nOffset = 0);
	t_short 		getVariant_Short		(int nId, int nOffset = 0);
	t_integer 		getVariant_Integer	(int nId, int nOffset = 0);
	t_long 		getVariant_Long		  (int nId, int nOffset = 0);

  t_single 		getVariant_Single		(int nId, int nOffset = 0);
	t_double 		getVariant_Double		(int nId, int nOffset = 0);
/*
  t_int16 		getVariant_Int16		(int nId, int nOffset = 0);
	t_int32 		getVariant_Int32		(int nId, int nOffset = 0);
	t_int64 		getVariant_Int64		(int nId, int nOffset = 0);
	t_uint16 		getVariant_UInt16		(int nId, int nOffset = 0);
	t_uint32 		getVariant_UInt32		(int nId, int nOffset = 0);
	t_uint64 		getVariant_UInt64		(int nId, int nOffset = 0);
*/
  t_currency 		getVariant_Currency		(int nId, int nOffset = 0);

  t_date 		getVariant_Date		(int nId, int nOffset = 0);

	t_object 		getVariant_Object		(int nId, int nOffset = 0);
	t_pointer		getVariant_Pointer	(int nId, int nOffset = 0);


  t_currency	getCurrency	(int nId, int nOffset = 0);

	t_date			getDate			(int nId, int nOffset = 0);
	//t_character			getCharacter			(int nId, int nOffset = 0);
	//t_cstring			getCString			(int nId, int nOffset = 0);
	

	void 	 *getStruct		(int nId, int nOffset = 0);
	void 	 *getPointer	(int nId, int nOffset = 0);
	void 	 *getPointerPointer	(int nId, int nOffset = 0);
	memory_variable	 *getObject 	(int nId, int nOffset = 0);

	int	getVariantType	(int nId);

	void setReferenceOffset	(int nId, int n);
	int	getReferenceOffset	(int nId);

	void setReferenceArray	(int nId, t_array *n);
	t_array	*getReferenceArray	(int nId);

	void setReferenceScope	(int nId, t_scope n);
	t_scope	getReferenceScope	(int nId); 

	void setReferenceVariablePool	(int nId, memory_variable *v);
	memory_variable *getReferenceVariablePool	(int nId);

	void setReferenceId	(int nId, int n);
	int	getReferenceId	(int nId);
	bool isReference(int nId);

  void		setArray	(int nId, t_array *a);
  void		setIsMissing	(int nId, bool b);

  void		setBindingParentClassPointer(t_pointer p);  
  void   setBindingParentClassType(int n);

  //bool		setBindingParentClassPointer(int nId, t_pointer p);  
  //bool   setBindingParentClassType(int nId, int n);

	void 		setQString_Boolean		(int nId, t_qstring s, t_boolean c, int nOffset);
	void 		setQString_Boolean		(int nId, t_boolean c, t_qstring s, int nOffset);

  void 		setQString_QString		(int nId, t_qstring s, t_qstring s2, int nOffset);
  void 		setQString_CString		(int nId, t_qstring s, t_cstring s2, int nOffset);
 // void 		setQString_WString		(int nId, t_qstring s, t_cstring s2, int nOffset, int nStringLen);

  void 		setQString_Byte		  (int nId, t_qstring s, t_byte n, int nOffset);
  void 		setQString_Byte		  (int nId, t_byte n, t_qstring s, int nOffset);

	void 		setQString_Short		  (int nId, t_qstring s, t_short n, int nOffset);
	void 		setQString_Short		  (int nId, t_short n, t_qstring s, int nOffset);

	void 		setQString_Integer		(int nId, t_qstring s, t_integer n, int nOffset);
	void 		setQString_Integer		(int nId, t_integer n, t_qstring s, int nOffset);

  void 		setQString_Long		  (int nId, t_qstring s, t_long l, int nOffset);
	void 		setQString_Long		  (int nId, t_long l, t_qstring s, int nOffset);

  void 		setQString_Single		(int nId, t_qstring s, t_single f, int nOffset);
  void 		setQString_Single		(int nId, t_single f, t_qstring s, int nOffset);

  void 		setQString_Double		(int nId, t_qstring s, t_double d, int nOffset);
  void 		setQString_Double		(int nId, t_double d, t_qstring s, int nOffset);

  void 		setQString_Currency		(int nId, t_qstring s, t_currency n, int nOffset);
  void 		setQString_Currency		(int nId, t_currency n, t_qstring s, int nOffset);

  void 		setQString_Date		(int nId, t_qstring s, t_date n, int nOffset);
  void 		setQString_Date		(int nId, t_date n, t_qstring s, int nOffset);



	void 		setCString_Boolean		(int nId, t_cstring s, t_boolean c, int nOffset);
	void 		setCString_Boolean		(int nId, t_boolean c, t_cstring s, int nOffset);

  void 		setCString_QString		(int nId, t_cstring s, t_qstring s2, int nOffset);
  void 		setCString_CString		(int nId, t_cstring s, t_cstring s2, int nOffset);

  void 		setCString_Byte		  (int nId, t_cstring s, t_byte n, int nOffset);
  void 		setCString_Byte		  (int nId, t_byte n, t_cstring s, int nOffset);

	void 		setCString_Short		  (int nId, t_cstring s, t_short n, int nOffset);
	void 		setCString_Short		  (int nId, t_short n, t_cstring s, int nOffset);

	void 		setCString_Integer		(int nId, t_cstring s, t_integer n, int nOffset);
	void 		setCString_Integer		(int nId, t_integer n, t_cstring s, int nOffset);

  void 		setCString_Long		  (int nId, t_cstring s, t_long l, int nOffset);
	void 		setCString_Long		  (int nId, t_long l, t_cstring s, int nOffset);

  void 		setCString_Single		(int nId, t_cstring s, t_single f, int nOffset);
  void 		setCString_Single		(int nId, t_single f, t_cstring s, int nOffset);

  void 		setCString_Double		(int nId, t_cstring s, t_double d, int nOffset);
  void 		setCString_Double		(int nId, t_double d, t_cstring s, int nOffset);

  void 		setCString_Currency		(int nId, t_cstring s, t_currency n, int nOffset);
  void 		setCString_Currency		(int nId, t_currency n, t_cstring s, int nOffset);

  void 		setCString_Date		(int nId, t_cstring s, t_date n, int nOffset);
  void 		setCString_Date		(int nId, t_date n, t_cstring s, int nOffset);

  /*
  void 		setString_Int16		  (int nId, t_string s, t_int16 n, int nOffset);
	void 		setString_Int32		  (int nId, t_string s, t_int32 n, int nOffset);
	void 		setString_Int64		  (int nId, t_string s, t_int64 n, int nOffset);
	void 		setString_UInt16		(int nId, t_string s, t_uint16 n, int nOffset);
	void 		setString_UInt32		(int nId, t_string s, t_uint32 n, int nOffset);
	void 		setString_UInt64		(int nId, t_string s, t_uint64 n, int nOffset);
*/
/*
	void 		setBoolean_String		(int nId, t_boolean c, t_string s2, int nOffset);

  void 		setByte_String	  	(int nId, t_byte n, t_string s2, int nOffset);
  void 		setShort_String		  (int nId, t_short n, t_string s2, int nOffset);
  void 		setInteger_String		(int nId, t_integer n, t_string s2, int nOffset);
	void 		setLong_String		  (int nId, t_long l, t_string s2, int nOffset);

  void 		setSingle_String		(int nId, t_single f, t_string s2, int nOffset);
	void 		setDouble_String		(int nId, t_double d, t_string s2, int nOffset);

  void 		setInt16_String		  (int nId, t_int16 n, t_string s2, int nOffset);
	void 		setInt32_String		  (int nId, t_int32 n, t_string s2, int nOffset);
	void 		setInt64_String		  (int nId, t_int64 n, t_string s2, int nOffset);
	void 		setUInt16_String		(int nId, t_uint16 n, t_string s2, int nOffset);
	void 		setUInt32_String		(int nId, t_uint32 n, t_string s2, int nOffset);
	void 		setUInt64_String		(int nId, t_uint64 n, t_string s2, int nOffset);
*/


	void 		setLQString_Boolean		(int nId, t_qstring s, t_boolean c, int nOffset, int nLStringLen);

  void 		setLQString_QString		(int nId, t_qstring s, t_qstring s2, int nOffset, int nLStringLen);
  void 		setLQString_CString		(int nId, t_qstring s, t_cstring s2, int nOffset, int nLStringLen);
  void 		setRQString_QString		(int nId, t_qstring s, t_qstring s2, int nOffset, int RStringLen);
  void 		setRQString_CString		(int nId, t_qstring s, t_cstring s2, int nOffset, int RStringLen);

  void 		setLQString_Byte		  (int nId, t_qstring s, t_byte n, int nOffset, int nLStringLen);
	void 		setLQString_Short		  (int nId, t_qstring s, t_short n, int nOffset, int nLStringLen);
	void 		setLQString_Integer		(int nId, t_qstring s, t_integer n, int nOffset, int nLStringLen);
	void 		setLQString_Long		  (int nId, t_qstring s, t_long l, int nOffset, int nLStringLen);

  void 		setLQString_Single		(int nId, t_qstring s, t_single f, int nOffset, int nLStringLen);
	void 		setLQString_Double		(int nId, t_qstring s, t_double d, int nOffset, int nLStringLen);



	void 		setLCString_Boolean		(int nId, t_cstring s, t_boolean c, int nOffset, int nLStringLen);

  void 		setLCString_CString		(int nId, t_cstring s, t_cstring s2, int nOffset, int nLStringLen);
  void 		setLCString_QString		(int nId, t_cstring s, t_qstring s2, int nOffset, int nLStringLen);
  void 		setRCString_CString		(int nId, t_cstring s, t_cstring s2, int nOffset, int RStringLen);
  void 		setRCString_QString		(int nId, t_cstring s, t_qstring s2, int nOffset, int RStringLen);

  void 		setLCString_Byte		  (int nId, t_cstring s, t_byte n, int nOffset, int nLStringLen);
	void 		setLCString_Short		  (int nId, t_cstring s, t_short n, int nOffset, int nLStringLen);
	void 		setLCString_Integer		(int nId, t_cstring s, t_integer n, int nOffset, int nLStringLen);
	void 		setLCString_Long		  (int nId, t_cstring s, t_long l, int nOffset, int nLStringLen);

  void 		setLCString_Single		(int nId, t_cstring s, t_single f, int nOffset, int nLStringLen);
	void 		setLCString_Double		(int nId, t_cstring s, t_double d, int nOffset, int nLStringLen);



	void 		setVariant_Boolean		(int nId, t_boolean c, int nOffset);

  void 		setVariant_QString		(int nId, t_qstring s, int nOffset);
  void 		setVariant_CString		(int nId, t_cstring s, int nOffset);

  void 		setVariant_Byte		  (int nId, t_byte n, int nOffset);
	void 		setVariant_Short		  (int nId, t_short n, int nOffset);
	void 		setVariant_Integer		(int nId, t_integer n, int nOffset);
	void 		setVariant_Long		  (int nId, t_long l, int nOffset);

  void 		setVariant_Single		(int nId, t_single f, int nOffset);
	void 		setVariant_Double		(int nId, t_double d, int nOffset);

  /*
  void 		setVariant_Int16		  (int nId, t_int16 n, int nOffset);
	void 		setVariant_Int32		  (int nId, t_int32 n, int nOffset);
	void 		setVariant_Int64		  (int nId, t_int64 n, int nOffset);
	void 		setVariant_UInt16		(int nId, t_uint16 n, int nOffset);
	void 		setVariant_UInt32		(int nId, t_uint32 n, int nOffset);
	void 		setVariant_UInt64		(int nId, t_uint64 n, int nOffset);
*/
/*
  void 		setLString_Int16		  (int nId, t_string s, t_int16 n, int nOffset, int nLStringLen);
	void 		setLString_Int32		  (int nId, t_string s, t_int32 n, int nOffset, int nLStringLen);
	void 		setLString_Int64		  (int nId, t_string s, t_int64 n, int nOffset, int nLStringLen);
	void 		setLString_UInt16		(int nId, t_string s, t_uint16 n, int nOffset, int nLStringLen);
	void 		setLString_UInt32		(int nId, t_string s, t_uint32 n, int nOffset, int nLStringLen);
	void 		setLString_UInt64		(int nId, t_string s, t_uint64 n, int nOffset, int nLStringLen);
*/

  void 		setVariant_Currency		(int nId, t_currency n, int nOffset);

  void 		setVariant_Date		(int nId, t_date n, int nOffset);

  void 		setVariant_Object		(int nId, t_object n, int nOffset);
  void 		setVariant_Pointer	(int nId, t_pointer n, int nType, int nOffset);

  void 		setVariant_Empty	(int nId, t_pcode n, int nOffset);
  void 		setVariant_Error	(int nId, t_pcode n, int nOffset);

//	void 		setString_String		(const char *acModule, const char *acSub, const char *acName, t_string s, t_string s2, int nOffset);


	void		setBoolean	(int nId, t_boolean c, int nOffset = 0);
	//void		setBoolean	(const char *acModule, const char *acSub, const char *acName, t_boolean c, int nOffset = 0);

  void 		setQString		(int nId, t_qstring s, int nOffset, int nBinaryPos = -1);
  void 		setCString		(int nId, t_cstring s, int nOffset, int nStringLen);
  void 		setWString		(int nId, t_cstring s, int nOffset, int nStringLen);
	//void 		setString		(const char *acModule, const char *acSub, const char *acName, t_string s, int nOffset);

  void 		setLQString		(int nId, t_qstring s, int nOffset, int nLStringLen);
  void 		setLCString		(int nId, t_cstring s, int nOffset, int nLStringLen);
	//void 		setLString		(const char *acModule, const char *acSub, const char *acName, t_string s, int nOffset);

  void 		setRQString		(int nId, t_qstring s, int nOffset, int nRStringLen);
  void 		setRCString		(int nId, t_cstring s, int nOffset, int nRStringLen);

	void 		setSingle		(int nId, t_single f, int nOffset = 0);
	//void 		setSingle		(const char *acModule, const char *acSub, const char *acName, t_single f, int nOffset = 0);
  void 		setDouble		(int nId, t_double d, int nOffset = 0);
//	void 		setDouble		(const char *acModule, const char *acSub, const char *acName, t_double d, int nOffset = 0);

	void		setByte			(int nId, t_byte c, int nOffset = 0);
	//void		setByte			(const char *acModule, const char *acSub, const char *acName, t_byte c, int nOffset = 0);
	void 		setShort		(int nId, t_short d, int nOffset = 0);
	//void 		setShort		(const char *acModule, const char *acSub, const char *acName, t_short d, int nOffset = 0);
  void 		setInteger	(int nId, t_integer n, int nOffset = 0);
	//void 		setInteger	(const char *acModule, const char *acSub, const char *acName, t_integer n, int nOffset = 0);
	void 		setLong			(int nId, t_long l, int nOffset = 0);
	//void 		setLong			(const char *acModule, const char *acSub,const char *acName, t_long l, int nOffset = 0);
	/*
	void 		setInt16		(int nId, t_int16 d, int nOffset = 0);
	//void 		setInt16		(const char *acModule, const char *acSub, const char *acName, t_int16 d, int nOffset = 0);
	void 		setInt32		(int nId, t_int32 d, int nOffset = 0);
	//void 		setInt32		(const char *acModule, const char *acSub, const char *acName, t_int32 d, int nOffset = 0);
	void 		setInt64		(int nId, t_int64 d, int nOffset = 0);
	//void 		setInt64		(const char *acModule, const char *acSub, const char *acName, t_int64 d, int nOffset = 0);
	void 		setUInt16		(int nId, t_uint16 d, int nOffset = 0);
	//void 		setUInt16		(const char *acModule, const char *acSub, const char *acName, t_uint16 d, int nOffset = 0);
	void 		setUInt32		(int nId, t_uint32 d, int nOffset = 0);
	//void 		setUInt32		(const char *acModule, const char *acSub, const char *acName, t_uint32 d, int nOffset = 0);
	void 		setUInt64		(int nId, t_uint64 d, int nOffset = 0);
	//void 		setUInt64		(const char *acModule, const char *acSub, const char *acName, t_uint64 d, int nOffset = 0);
*/
  void 		setVariant		(int nId, t_variant s, int nOffset);

  void 		setVariantType	(int nId, t_pcode c);

  void	  setCurrency		(int nId, t_long d, int nOffset = 0);
  void	  setCurrencyDouble		(int nId, t_double d, int nOffset = 0);
	void 		setCurrency	(int nId, t_currency c, int nOffset = 0);

	void 		setDate			(int nId, t_date d, int nOffset = 0);
	//void 		setCharacter		(int nId, t_character d, int nOffset = 0);
	//void 		setCString		(int nId, t_cstring d, int nOffset = 0);

	void 		setStruct		(int nId, void *p, int nOffset, int nSize);
	void 		setPointer	(int nId, void *p, int nOffset = 0);
	void *	copyPointer	(int nId, void *p, int nOffset = 0, int nSize = 0);
	void 		setObject	(int nId, void *p, int nOffset = 0);

	bool 		first();
	bool 		next();

	void *getAddress(int nId, int nOffset, int nType);

	
	char *getKey(const char *acModule, const char *acSub, const char *acName);
  
  int getClassId();// used to call destructors by interpreter
  void setClassId(int nId);// used to call destructors by interpreter

  QString toQString(int nId);


variable	*findMemory_variable	(int nId)
{
  // * optimize
  static int _nId = -100;
  static variable *v = 0;
  static void *_this = 0;

  if (_nId == nId && _this == this){
    return v;
  }
  // *
	if (list_variable.contains(nId)){
    _nId = nId;
    _this = this;
    v = list_variable[nId];
		return v;		
	}	 
  _nId = -100;

	return 0;
}

bool 		checkOffset	(variable *v, int nOffset, int nSize)
{
  if (nOffset + nSize > v->nStructSize){ memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), ": offset out of size of struct")); return false; }

	return true;
}

private:
	bool memory_variableError(char *acMemory_variableError);
	bool 		init				();

  variable *newMemory_variable
    (
    const char *acModule, 
    const char *acSub, 
    const char *acName, 
    int nId, 
    int nType, 
    t_array *a, 
    bool bByVal, 
    bool bReference, 
    bool bStatic, 
    int nScope,
    int nTypeSize
    );
	typedef QMap<int, variable*> map9;
public: // for callLib()
	map9 list_variable;
private:
	QMap<QString, variable*> list_variable2;
  map9::Iterator it;

  bool bError;

  int nClassId; // used to call destructors by interpreter
	void *vBindingParentClassPointer; // used for parent classes which are bindings
  int nBindingParentClassType;

};



#endif

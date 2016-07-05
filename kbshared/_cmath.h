/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#ifndef _CMATH_H
#define _CMATH_H

#include <math.h>

#include "typedef.h"



class _cmath
{
  
public:

static t_double METHOD_sin(t_double d){ return sin(d); } 
static t_double METHOD_cos(t_double d){ return cos(d); } 
static t_double METHOD_tan(t_double d){ return tan(d); } 
static t_double METHOD_asin(t_double d){ return asin(d); } 
static t_double METHOD_acos(t_double d){ return acos(d); } 
static t_double METHOD_atan(t_double d){ return atan(d); } 
static t_double METHOD_atan2(t_double d, t_double d2){ return atan2(d, d2); } 
static t_double METHOD_sinh(t_double d){ return sinh(d); } 
static t_double METHOD_cosh(t_double d){ return cosh(d); } 
static t_double METHOD_tanh(t_double d){ return tanh(d); } 
static t_double METHOD_exp(t_double d){ return exp(d); } 
static t_double METHOD_log(t_double d){ return log(d); } 
static t_double METHOD_log10(t_double d){ return log10(d); } 
static t_double METHOD_pow(t_double d, t_double d2){ return pow(d, d2); } 
static t_double METHOD_sqrt(t_double d){ return sqrt(d); } 
static t_double METHOD_ceil(t_double d){ return ceil(d); } 
static t_double METHOD_floor(t_double d){ return floor(d); } 
static t_double METHOD_fabs(t_double d){ return fabs(d); } 
/*
static t_double METHOD_ldexp(t_double d){ return ldexp(d); } 

static t_double METHOD_frexp(t_double d, t_integer *d2){ return frexp(d, 2); } 
static t_double METHOD_modf(t_double d, t_double *d2){ return modf(d, 2); } 
*/
static t_double METHOD_fmod(t_double d, t_double d2){ return pow(d, d2); } 


}
;



#endif
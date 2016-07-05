

case pcode___cmath__METHOD_sin:{ p = new interpreter_parameter(_cmath::METHOD_sin(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_cos:{ p = new interpreter_parameter(_cmath::METHOD_cos(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_tan:{ p = new interpreter_parameter(_cmath::METHOD_tan(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_asin:{ p = new interpreter_parameter(_cmath::METHOD_asin(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_acos:{ p = new interpreter_parameter(_cmath::METHOD_acos(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_atan:{ p = new interpreter_parameter(_cmath::METHOD_atan(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_atan2:{ p = new interpreter_parameter(_cmath::METHOD_atan2(v[0]->tot_double(), v[1]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_sinh:{ p = new interpreter_parameter(_cmath::METHOD_sinh(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_cosh:{ p = new interpreter_parameter(_cmath::METHOD_cosh(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_tanh:{ p = new interpreter_parameter(_cmath::METHOD_tanh(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_exp:{ p = new interpreter_parameter(_cmath::METHOD_exp(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_log:{ p = new interpreter_parameter(_cmath::METHOD_log(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_log10:{ p = new interpreter_parameter(_cmath::METHOD_log10(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_pow:{ p = new interpreter_parameter(_cmath::METHOD_pow(v[0]->tot_double(), v[1]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_sqrt:{ p = new interpreter_parameter(_cmath::METHOD_sqrt(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_ceil:{ p = new interpreter_parameter(_cmath::METHOD_ceil(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_floor:{ p = new interpreter_parameter(_cmath::METHOD_floor(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_fabs:{ p = new interpreter_parameter(_cmath::METHOD_fabs(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }
/*case pcode___cmath__METHOD_ldexp:{ p = new interpreter_parameter(_cmath::METHOD_ldexp(v[0]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___cmath__METHOD_frexp:{ p = new interpreter_parameter(_cmath::METHOD_frexp(v[0]->tot_double(), v[1]->toPointerInteger())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___cmath__METHOD_modf:{ p = new interpreter_parameter(_cmath::METHOD_modf(v[0]->tot_double(), v[1]->toPointerDouble())); if (bReturn) pushStack(p); else delete p; break; }
*/
case pcode___cmath__METHOD_fmod:{ p = new interpreter_parameter(_cmath::METHOD_fmod(v[0]->tot_double(), v[1]->tot_double())); if (bReturn) pushStack(p); else delete p; break; }



/*
 * This file was generated automatically by xsubpp version 1.9508 from the
 * contents of ReWrite_pl_fb02.xs. Do not edit this file, edit ReWrite_pl_fb02.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "ReWrite_pl_fb02.xs"
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "INLINE.h"

void c_func_1(SV* text) {
    c_func_2(text);
}

void c_func_2(SV* text) {
    Inline_Stack_Vars;
    Inline_Stack_Push(newSVpvf("Plus an extra line"));
    Inline_Stack_Done;
    perl_call_pv("main::perl_sub_1", 0);
    Inline_Stack_Void;
}

#line 28 "ReWrite_pl_fb02.c"
XS(XS_main_c_func_1); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_c_func_1)
{
    dXSARGS;
    if (items != 1)
	Perl_croak(aTHX_ "Usage: main::c_func_1(text)");
    SP -= items;
    {
	SV *	text = ST(0);
#line 27 "ReWrite_pl_fb02.xs"
	I32* temp;
#line 40 "ReWrite_pl_fb02.c"
#line 29 "ReWrite_pl_fb02.xs"
	temp = PL_markstack_ptr++;
	c_func_1(text);
	if (PL_markstack_ptr != temp) {
          /* truly void, because dXSARGS not invoked */
	  PL_markstack_ptr = temp;
	  XSRETURN_EMPTY; /* return empty stack */
        }
        /* must have used dXSARGS; list context implied */
	return; /* assume stack size is correct */
#line 51 "ReWrite_pl_fb02.c"
	PUTBACK;
	return;
    }
}

XS(XS_main_c_func_2); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_c_func_2)
{
    dXSARGS;
    if (items != 1)
	Perl_croak(aTHX_ "Usage: main::c_func_2(text)");
    SP -= items;
    {
	SV *	text = ST(0);
#line 43 "ReWrite_pl_fb02.xs"
	I32* temp;
#line 68 "ReWrite_pl_fb02.c"
#line 45 "ReWrite_pl_fb02.xs"
	temp = PL_markstack_ptr++;
	c_func_2(text);
	if (PL_markstack_ptr != temp) {
          /* truly void, because dXSARGS not invoked */
	  PL_markstack_ptr = temp;
	  XSRETURN_EMPTY; /* return empty stack */
        }
        /* must have used dXSARGS; list context implied */
	return; /* assume stack size is correct */
#line 79 "ReWrite_pl_fb02.c"
	PUTBACK;
	return;
    }
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_ReWrite_pl_fb02); /* prototype to pass -Wmissing-prototypes */
XS(boot_ReWrite_pl_fb02)
{
    dXSARGS;
    char* file = __FILE__;

    XS_VERSION_BOOTCHECK ;

        newXS("main::c_func_1", XS_main_c_func_1, file);
        newXS("main::c_func_2", XS_main_c_func_2, file);
    XSRETURN_YES;
}


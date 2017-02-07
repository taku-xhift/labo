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

MODULE = main_pl_fb02	PACKAGE = main	

PROTOTYPES: DISABLE


void
c_func_1 (text)
	SV *	text
	PREINIT:
	I32* temp;
	PPCODE:
	temp = PL_markstack_ptr++;
	c_func_1(text);
	if (PL_markstack_ptr != temp) {
          /* truly void, because dXSARGS not invoked */
	  PL_markstack_ptr = temp;
	  XSRETURN_EMPTY; /* return empty stack */
        }
        /* must have used dXSARGS; list context implied */
	return; /* assume stack size is correct */

void
c_func_2 (text)
	SV *	text
	PREINIT:
	I32* temp;
	PPCODE:
	temp = PL_markstack_ptr++;
	c_func_2(text);
	if (PL_markstack_ptr != temp) {
          /* truly void, because dXSARGS not invoked */
	  PL_markstack_ptr = temp;
	  XSRETURN_EMPTY; /* return empty stack */
        }
        /* must have used dXSARGS; list context implied */
	return; /* assume stack size is correct */


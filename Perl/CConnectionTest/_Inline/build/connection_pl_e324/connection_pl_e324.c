/*
 * This file was generated automatically by xsubpp version 1.9508 from the
 * contents of connection_pl_e324.xs. Do not edit this file, edit connection_pl_e324.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "connection_pl_e324.xs"
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "INLINE.h"

void greet() {
    printf("Hello, world
");
}

#line 21 "connection_pl_e324.c"
XS(XS_main_greet); /* prototype to pass -Wmissing-prototypes */
XS(XS_main_greet)
{
    dXSARGS;
    if (items != 0)
	Perl_croak(aTHX_ "Usage: main::greet()");
   PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
#line 19 "connection_pl_e324.xs"
	I32* temp;
#line 33 "connection_pl_e324.c"
#line 21 "connection_pl_e324.xs"
	temp = PL_markstack_ptr++;
	greet();
	if (PL_markstack_ptr != temp) {
          /* truly void, because dXSARGS not invoked */
	  PL_markstack_ptr = temp;
	  XSRETURN_EMPTY; /* return empty stack */
        }
        /* must have used dXSARGS; list context implied */
	return; /* assume stack size is correct */
#line 44 "connection_pl_e324.c"
	PUTBACK;
	return;
    }
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_connection_pl_e324); /* prototype to pass -Wmissing-prototypes */
XS(boot_connection_pl_e324)
{
    dXSARGS;
    char* file = __FILE__;

    XS_VERSION_BOOTCHECK ;

        newXS("main::greet", XS_main_greet, file);
    XSRETURN_YES;
}


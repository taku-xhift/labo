/*
 * This file was generated automatically by xsubpp version 1.9508 from the
 * contents of test_pl_8f3e.xs. Do not edit this file, edit test_pl_8f3e.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "test_pl_8f3e.xs"
#ifndef bool
#include <iostream>
#endif
extern "C" {
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "INLINE.h"
}
#ifdef bool
#undef bool
#include <iostream>
#endif

#line 25 "test_pl_8f3e.c"
#ifdef __cplusplus
extern "C"
#endif
XS(boot_test_pl_8f3e); /* prototype to pass -Wmissing-prototypes */
XS(boot_test_pl_8f3e)
{
    dXSARGS;

    XS_VERSION_BOOTCHECK ;

    XSRETURN_YES;
}


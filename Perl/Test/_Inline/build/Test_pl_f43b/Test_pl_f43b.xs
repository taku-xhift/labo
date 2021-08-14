#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "INLINE.h"

void dump_hash(SV* hash_ref) {
    HV* hash;
    HE* hash_entry;
    int num_keys, i;
    SV* sv_key;
    SV* sv_val;
    
    if (! SvROK(hash_ref))
        croak("hash_ref is not a reference");
    
    hash = (HV*)SvRV(hash_ref);
    num_keys = hv_iterinit(hash);
    for (i = 0; i < num_keys; i++) {
        hash_entry = hv_iternext(hash);
        sv_key = hv_iterkeysv(hash_entry);
        sv_val = hv_iterval(hash, hash_entry);
        printf("%d", SvTYPE(SvRV(sv_val));
        printf("%s => %s\n", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
    }
    return;
}


MODULE = Test_pl_f43b	PACKAGE = main	

PROTOTYPES: DISABLE


void
dump_hash (hash_ref)
	SV *	hash_ref
	PREINIT:
	I32* temp;
	PPCODE:
	temp = PL_markstack_ptr++;
	dump_hash(hash_ref);
	if (PL_markstack_ptr != temp) {
          /* truly void, because dXSARGS not invoked */
	  PL_markstack_ptr = temp;
	  XSRETURN_EMPTY; /* return empty stack */
        }
        /* must have used dXSARGS; list context implied */
	return; /* assume stack size is correct */


#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "INLINE.h"

void dump_hash(SV* hash_ref) {
    converter(hash_ref);
}

ReciprrocateData* converter(SV* hash_ref) {
    ReciprocateData data;

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
        if (SvTYPE(SvRV(sv_val)) == SVt_PVAV) {
            AV* ar = (AV*)SvRV(sv_val);
            SV* temp;
            while (av_len(ar) != -1) {
                temp = av_shift(ar);
                printf("array, %s => %s\n", SvPV(sv_key, PL_na), SvPV(temp, PL_na));
            }
        } else if (SvTYPE(SvRV(sv_val)) == SVt_PVHV) {
            HV* hash = (HV*)SvRV(sv_val);
            converter(newRV_noinc((SV*)hash));
        } else if (SvTYPE(SvRV(sv_val)) == SVt_IV) {
            print("integer, %s => %d", SvPV(sv_key, PL_na), SvIV(sv_val));
        } else {
            printf("%s => %s\n", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
        }
    }
    return data;
}


MODULE = main_pl_e4cb	PACKAGE = main	

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


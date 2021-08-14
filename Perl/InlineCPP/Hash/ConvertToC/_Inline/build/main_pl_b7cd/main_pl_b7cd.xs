#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "INLINE.h"

void dump_hash(SV* hash_ref) {
//    converter(hash_ref);
//}
//
//ReciprrocateData* converter(SV* hash_ref) {
//    ReciprocateData data;

    HV* hash;
    HE* hash_entry;
    int num_keys, i;
    SV* sv_key;
    SV* sv_val;
    ReciprocateData* data;

    if (! SvROK(hash_ref))
        croak("hash_ref is not a reference\n");

    printf("ReferenceCheck clear!!\n");

    hash = (HV*)SvRV(hash_ref);
    num_keys = hv_iterinit(hash);

    printf("Parse start!!\n");

    for (i = 0; i < num_keys; i++) {
        hash_entry = hv_iternext(hash);
        sv_key = hv_iterkeysv(hash_entry);
        sv_val = hv_iterval(hash, hash_entry);
        printf("SV type is %d\n", SvTYPE(SvRV(sv_val)));

        if (SvTYPE(sv_val) == SVt_IV) {
            printf("Integer, %s => %d\n", SvPV(sv_key, PL_na), SvIV(sv_val));
        } else if (SvTYPE(sv_val) == SVt_NV) {
            printf("Natural, %s => %s\n", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
        } else if (SvTYPE(sv_val) == SVt_PV) {
            printf("Strings, %s => %s\n", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
        } else if (SvTYPE(SvRV(sv_val)) == SVt_PVCV) {
            printf("Code, %s => %d", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
        } else if (SvTYPE(SvRV(sv_val)) == SVt_PVGV) {
            printf("Glob, %s => %d", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
        } else if (SvTYPE(SvRV(sv_val)) == SVt_PVMG) {
            printf("Blessed or Magical Scalar, %s => %d", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
        } else {
            // 型判定の中でもリストとハッシュのリファレンスに関しては最後に判定しないとダンプだして終了する
            if (SvTYPE(SvRV(sv_val)) == SVt_PVAV) {
                AV* ar = (AV*)SvRV(sv_val);
                SV* temp;
                while (av_len(ar) != -1) {
                    temp = av_shift(ar);
                    printf("Array, %s => %s\n", SvPV(sv_key, PL_na), SvPV(temp, PL_na));
                }
            } else if (SvTYPE(SvRV(sv_val)) == SVt_PVHV) {
                HV* tempHash = (HV*)SvRV(sv_val);
                printf("Hash!!\n");
                dump_hash(newRV_noinc((SV*)tempHash));

//        for (i = 0; i < num_keys; i++) {
//            hash_entry = hv_iternext(hash);
//            sv_key = hv_iterkeysv(hash_entry);
//            sv_val = hv_iterval(hash, hash_entry);
//            printf("%s => %s\n", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
//        }

            }
            printf("Another, %s => %s\n", SvPV(sv_key, PL_na), SvPV(sv_val, PL_na));
        }
    }
    return;
}



MODULE = main_pl_b7cd	PACKAGE = main	

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


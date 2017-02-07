#define IN_STG_CODE 0
#include "Rts.h"
#include "Stg.h"
#ifdef __cplusplus
extern "C" {
#endif
 
extern StgClosure Adder_zdfadderzuau6_closure;
HsInt __attribute__((__stdcall__)) adder(HsInt a1, HsInt a2)
{
Capability *cap;
HaskellObj ret;
HsInt cret;
cap = rts_lock();
cap=rts_evalIO(cap,rts_apply(cap,(HaskellObj)runIO_closure,rts_apply(cap,rts_apply(cap,&Adder_zdfadderzuau6_closure,rts_mkInt(cap,a1)),rts_mkInt(cap,a2))) ,&ret);
rts_checkSchedStatus("adder",cap);
cret=rts_getInt(ret);
rts_unlock(cap);
return cret;
}
static void stginit_export_Adder_zdfadderzuau6() __attribute__((constructor));
static void stginit_export_Adder_zdfadderzuau6()
{getStablePtr((StgPtr) &Adder_zdfadderzuau6_closure);}
#ifdef __cplusplus
}
#endif


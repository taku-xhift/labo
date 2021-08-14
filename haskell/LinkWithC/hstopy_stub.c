#define IN_STG_CODE 0
#include "Rts.h"
#include "Stg.h"
#ifdef __cplusplus
extern "C" {
#endif
 
extern StgClosure Htop_zdffactorialzuaNf_closure;
HsInt factorial(HsInt a1)
{
Capability *cap;
HaskellObj ret;
HsInt cret;
cap = rts_lock();
cap=rts_evalIO(cap,rts_apply(cap,(HaskellObj)runIO_closure,rts_apply(cap,&Htop_zdffactorialzuaNf_closure,rts_mkInt(cap,a1))) ,&ret);
rts_checkSchedStatus("factorial",cap);
cret=rts_getInt(ret);
rts_unlock(cap);
return cret;
}
 
extern StgClosure Htop_zdfmystringzuaNe_closure;
HsPtr mystring(void)
{
Capability *cap;
HaskellObj ret;
HsPtr cret;
cap = rts_lock();
cap=rts_evalIO(cap,rts_apply(cap,(HaskellObj)runIO_closure,&Htop_zdfmystringzuaNe_closure) ,&ret);
rts_checkSchedStatus("mystring",cap);
cret=rts_getPtr(ret);
rts_unlock(cap);
return cret;
}
static void stginit_export_Htop_zdffactorialzuaNf() __attribute__((constructor));
static void stginit_export_Htop_zdffactorialzuaNf()
{getStablePtr((StgPtr) &Htop_zdffactorialzuaNf_closure);}
static void stginit_export_Htop_zdfmystringzuaNe() __attribute__((constructor));
static void stginit_export_Htop_zdfmystringzuaNe()
{getStablePtr((StgPtr) &Htop_zdfmystringzuaNe_closure);}
#ifdef __cplusplus
}
#endif


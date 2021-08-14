
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "comutil.h"
#include <stdarg.h>

HRESULT GetIDOfName(IDispatch* pDisp, OLECHAR* wszName, DISPID* pdispID)
{
    HRESULT hr;
    
    hr = pDisp->GetIDsOfNames(
            IID_NULL,
            &wszName, 
            1,
            LOCALE_USER_DEFAULT,
            pdispID);
    return hr;
}

HRESULT GetProperty(IDispatch* pDisp, OLECHAR* wszName, VARIANT* pvResult)
{
    HRESULT hr;
    DISPID dispID;
    DISPPARAMS dispParams = {NULL, NULL, 0, 0};

    hr = GetIDOfName(pDisp, wszName, &dispID);
    if (FAILED(hr)){ return hr; }

    hr = pDisp->Invoke(
                dispID, IID_NULL,
                LOCALE_USER_DEFAULT,
                DISPATCH_PROPERTYGET,
                &dispParams, pvResult,
                NULL, NULL);

    return hr;
}

HRESULT PutProperty(IDispatch* pDisp, OLECHAR* pwszName, const VARIANT* pvValue)
{
    HRESULT hr;
    DISPID dispID;
    DISPID dispIDNamedArgs[1] = { DISPID_PROPERTYPUT };

    // DISPID ‚ðŽæ“¾
    hr = GetIDOfName(pDisp, pwszName, &dispID);
    if (FAILED(hr)) { return hr; }

    VARIANTARG vArgs[1];
    VariantInit(&vArgs[0]);
    VariantCopy(&vArgs[0], const_cast<VARIANT*>(pvValue));

    DISPPARAMS dispParams;
    dispParams.rgvarg = vArgs;
    dispParams.rgdispidNamedArgs = dispIDNamedArgs;
    dispParams.cArgs = 1;
    dispParams.cNamedArgs = 1;

    hr = pDisp->Invoke(
                dispID, IID_NULL,
                LOCALE_USER_DEFAULT,
                DISPATCH_PROPERTYPUT,
                &dispParams, NULL,
                NULL, NULL);
    VariantClear(&vArgs[0]);

    return hr;
}

HRESULT Invoke(IDispatch* pDisp, OLECHAR* wszMethod, VARIANT* pvResult, int nArgs, ...)
{
    HRESULT hr;
    DISPID dispID;
    va_list ap;
    int i;

    hr = GetIDOfName(pDisp, wszMethod, &dispID);
    if (FAILED(hr)) { return hr; }

    // ˆø”‚ð VARAINT ”z—ñ‚ÉÝ’è
    VARIANTARG *pvArgs = NULL;
    if(nArgs > 0){
        pvArgs = new VARIANTARG[nArgs];

        va_start(ap, nArgs);
        for(i=0;i<nArgs;i++){
            VariantInit(&pvArgs[i]);
            VariantCopy(&pvArgs[i], &va_arg(ap, VARIANT));
        }
        va_end(ap);
    }

    // DISPPARAMS ‚ÌÝ’è
    DISPPARAMS dispParams;
    dispParams.rgvarg = pvArgs;
    dispParams.rgdispidNamedArgs = NULL;
    dispParams.cArgs = nArgs;
    dispParams.cNamedArgs = 0;

    hr = pDisp->Invoke(
                dispID, IID_NULL,
                LOCALE_USER_DEFAULT,
                DISPATCH_METHOD,
                &dispParams, pvResult,
                NULL, NULL);

    // VARIANT ”z—ñ‚ÌŒãŽn––
    for(i=0;i<nArgs;i++){
        VariantClear(&pvArgs[i]);
    }

    if(pvArgs != NULL){
        delete[] pvArgs;
        pvArgs = NULL;
    }
    return hr;
}



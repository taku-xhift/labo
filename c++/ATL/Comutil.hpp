
#ifndef COMUUTIL_HPP_INCLUDED
#define COMUUTIL_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <atlbase.h>


HRESULT GetProperty(IDispatch* pDisp, OLECHAR* wszName, VARIANT* pvResult);
HRESULT PutProperty(IDispatch* pDisp, OLECHAR* pwszName, const VARIANT* pvValue);
HRESULT Invoke(IDispatch* pDisp, OLECHAR* wszMethod, VARIANT* pvResult, int nArgs, ...);



#endif


/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2010.07.30 19:47:23
 *
 * @version 0.01, Shishido Takuya, 2010.07.30 19:47:23
 *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

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


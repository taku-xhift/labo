#include <windows.h>
#include <atlbase.h>
#include <cstdio>
#include <cassert>
using namespace std;

#include "Comutil.hpp"

int main(int argc, char** argv)
{
    HRESULT hr;

    // COM の初期化
    hr = CoInitialize(NULL);
    if(FAILED(hr)){
        printf("CoInitialize 失敗\n");
        exit(1);
    }

    // CLSID の取得
    CLSID clsid;
    hr = CLSIDFromProgID(L"InternetExplorer.Application", &clsid);
    if(FAILED(hr)){
        printf("CLSIDFromProgID 失敗\n");
        exit(1);
    }

    // インスタンス生成
    IDispatch* pDispIE = NULL;
    hr = ::CoCreateInstance(
                clsid, NULL,
                CLSCTX_ALL,
                IID_IDispatch, (void**)&pDispIE);
    if(FAILED(hr)){
        printf("CoCreateInstance 失敗\n");
        exit(1);
    }

    // objIE.Visible = True
    VARIANT vTrue;
    
    VariantInit(&vTrue);
    vTrue.boolVal = VARIANT_TRUE;
    vTrue.vt = VT_BOOL;

    hr = PutProperty(pDispIE, L"Visible", &vTrue);
    VariantClear(&vTrue);
    if(FAILED(hr)){
        printf("objIE.Visible = True 失敗\n");
        exit(1);
    }

    // objIE.Navigate("http://t4130195.konami/PlayMaker/?game_http_port=3273")
    VARIANT vResult, vStr;
    BSTR bstrURL;

    bstrURL = SysAllocString(L"http://t4130195.konami/PlayMaker/?game_http_port=3273");

    VariantInit(&vStr);
    vStr.bstrVal = bstrURL;
    vStr.vt = VT_BSTR;

    VariantInit(&vResult);
    hr = Invoke(pDispIE, L"Navigate",  &vResult, 1, vStr);
    if(FAILED(hr)){
        printf("objIE.Navigate 失敗\n");
        exit(1);
    }

    SysFreeString(bstrURL);
    VariantClear(&vResult);
    VariantClear(&vStr);

    // Busy の間待つ
    do{
        hr = GetProperty(pDispIE, L"Busy", &vResult);
        if(FAILED(hr)){
            printf("objIE.Busy の取得失敗\n");
            exit(1);
        }
        assert(vResult.vt == VT_BOOL);
    }while(vResult.boolVal == VARIANT_TRUE);

    VariantClear(&vResult);

    // Document を取得
    IDispatch* pDispDoc;
    hr = GetProperty(pDispIE, L"Document", &vResult);
    if(FAILED(hr)){
        printf("objIE.Document の取得失敗\n");
        exit(1);
    }
    assert(vResult.vt == VT_DISPATCH);
    pDispDoc = vResult.pdispVal;    
    pDispDoc->AddRef();        // (*) VariantClear で Document が解放されないよう、参照カウントを 1 増やす。
    VariantClear(&vResult);

    // タイトルをメッセージボックスで表示
    LPCTSTR lpTitle;
    
    USES_CONVERSION;                 //     OLE2CT に必要
    hr = GetProperty(pDispDoc, L"Title", &vResult);
    if(FAILED(hr)){
        printf("objIE.Document.Title の取得失敗\n");
        exit(1);
    }
    assert(vResult.vt = VT_BSTR);

    lpTitle = OLE2CT(vResult.bstrVal);
    MessageBox(NULL, lpTitle, lpTitle, MB_OK);
    
    // IE とドキュメントの解放
    pDispIE->Release();
    pDispDoc->Release();

    CoUninitialize();

    return 0;
}

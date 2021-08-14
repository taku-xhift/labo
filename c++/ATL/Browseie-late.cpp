#include <windows.h>
#include <atlbase.h>
#include <cstdio>
#include <cassert>
using namespace std;

#include "Comutil.hpp"

int main(int argc, char** argv)
{
    HRESULT hr;

    // COM �̏�����
    hr = CoInitialize(NULL);
    if(FAILED(hr)){
        printf("CoInitialize ���s\n");
        exit(1);
    }

    // CLSID �̎擾
    CLSID clsid;
    hr = CLSIDFromProgID(L"InternetExplorer.Application", &clsid);
    if(FAILED(hr)){
        printf("CLSIDFromProgID ���s\n");
        exit(1);
    }

    // �C���X�^���X����
    IDispatch* pDispIE = NULL;
    hr = ::CoCreateInstance(
                clsid, NULL,
                CLSCTX_ALL,
                IID_IDispatch, (void**)&pDispIE);
    if(FAILED(hr)){
        printf("CoCreateInstance ���s\n");
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
        printf("objIE.Visible = True ���s\n");
        exit(1);
    }

    // objIE.Navigate("http://192.168.1.1?game_http_port=3273")
    VARIANT vResult, vStr;
    BSTR bstrURL;

    bstrURL = SysAllocString(L"http://192.168.1.1/?game_http_port=3273");

    VariantInit(&vStr);
    vStr.bstrVal = bstrURL;
    vStr.vt = VT_BSTR;

    VariantInit(&vResult);
    hr = Invoke(pDispIE, L"Navigate",  &vResult, 1, vStr);
    if(FAILED(hr)){
        printf("objIE.Navigate ���s\n");
        exit(1);
    }

    SysFreeString(bstrURL);
    VariantClear(&vResult);
    VariantClear(&vStr);

    // Busy �̊ԑ҂�
    do{
        hr = GetProperty(pDispIE, L"Busy", &vResult);
        if(FAILED(hr)){
            printf("objIE.Busy �̎擾���s\n");
            exit(1);
        }
        assert(vResult.vt == VT_BOOL);
    }while(vResult.boolVal == VARIANT_TRUE);

    VariantClear(&vResult);

    // Document ���擾
    IDispatch* pDispDoc;
    hr = GetProperty(pDispIE, L"Document", &vResult);
    if(FAILED(hr)){
        printf("objIE.Document �̎擾���s\n");
        exit(1);
    }
    assert(vResult.vt == VT_DISPATCH);
    pDispDoc = vResult.pdispVal;    
    pDispDoc->AddRef();        // (*) VariantClear �� Document ���������Ȃ��悤�A�Q�ƃJ�E���g�� 1 ���₷�B
    VariantClear(&vResult);

    // �^�C�g�������b�Z�[�W�{�b�N�X�ŕ\��
    LPCTSTR lpTitle;
    
    USES_CONVERSION;                 //     OLE2CT �ɕK�v
    hr = GetProperty(pDispDoc, L"Title", &vResult);
    if(FAILED(hr)){
        printf("objIE.Document.Title �̎擾���s\n");
        exit(1);
    }
    assert(vResult.vt = VT_BSTR);

    lpTitle = OLE2CT(vResult.bstrVal);
    MessageBox(NULL, lpTitle, lpTitle, MB_OK);
    
    // IE �ƃh�L�������g�̉��
    pDispIE->Release();
    pDispDoc->Release();

    CoUninitialize();

    return 0;
}

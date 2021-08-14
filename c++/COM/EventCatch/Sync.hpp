
#include <atlbase.h>	// ATL��{�@�\�p�w�b�_�t�@�C��

// ATL���g�p���邽�߂ɕK�v�ȃO���[�o���ϐ�
// ���̕ϐ����́A�K���A���̖��O�Ŗ�����΂Ȃ�܂���B
extern CComModule	_Module;

#include <atlcom.h>		// ATL COM���ʗp�w�b�_�t�@�C��
#include <atlhost.h>	// ATL �R���e�i�@�\�T�|�[�g�p�w�b�_�t�@�C��
#include <EXDISPID.H>

// �����͔C�ӁB�ڂ�����IDispatchImpl�̃h�L�������g�Q��
#define SINKID_COUNTEREVENTS 0


class ATL_NO_VTABLE IESinc :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispEventImpl<SINKID_COUNTEREVENTS, CIESink, &DIID_DWebBrowserEvents2>
{
private:
	CComPtr<IUnknown> m_pUnkIE;

public:
	CIESink() {}

	HRESULT AdviseToIE( CComPtr<IUnknown> pUnkIE)
	{
		m_pUnkIE = pUnkIE;
		
		// �^�C�v ���C�u�����ւ̃|�C���^��o�[�W�������̐ݒ�
		AtlGetObjectSourceInterface( pUnkIE, &m_libid, &m_iid, &m_wMajorVerNum, &m_wMinorVerNum) ;

		// �C�x���g��Dispatch
		HRESULT hr = this->DispEventAdvise( pUnkIE);

		return hr ;
	}

BEGIN_COM_MAP(IESinc)
	COM_INTERFACE_ENTRY_IID(DIID_DWebBrowserEvents2, CIESink)
END_COM_MAP()

BEGIN_SINK_MAP(IESinc)
	SINK_ENTRY_EX(SINKID_COUNTEREVENTS, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, OnBeforeNavigate2)
	SINK_ENTRY_EX(SINKID_COUNTEREVENTS, DIID_DWebBrowserEvents2, DISPID_NEWWINDOW2, OnNewWindow2)
	SINK_ENTRY_EX(SINKID_COUNTEREVENTS, DIID_DWebBrowserEvents2, DISPID_ONQUIT, OnQuit)
END_SINK_MAP()

// OnBeforeNavigate2
void _stdcall OnBeforeNavigate2( IDispatch** ppDisp, VARIANT* pvUrl, VARIANT*, VARIANT* pvTarget, VARIANT*,
				   VARIANT*, VARIANT_BOOL *pbCancel)
{
	// �A�h���X�o�[�̕�����ύX
	SetWindowTextW( hwndAddressBar, pvUrl->bstrVal) ;
	return ;
}

// OnNewWindow2
void _stdcall OnNewWindow2( IDispatch** ppDisp, VARIANT_BOOL *pbCancel)
{
	// �L�����Z������
	*pbCancel = VARIANT_TRUE ;
	return ;
}

// OnQuit
void _stdcall OnQuit()
{
	DispEventUnadvise( m_pUnkIE);
	return ;
}
};


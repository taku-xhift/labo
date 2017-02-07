
#include <atlbase.h>	// ATL基本機能用ヘッダファイル

// ATLを使用するために必要なグローバル変数
// この変数名は、必ず、この名前で無ければなりません。
extern CComModule	_Module;

#include <atlcom.h>		// ATL COM共通用ヘッダファイル
#include <atlhost.h>	// ATL コンテナ機能サポート用ヘッダファイル
#include <EXDISPID.H>

// 数字は任意。詳しくはIDispatchImplのドキュメント参照
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
		
		// タイプ ライブラリへのポインタやバージョン情報の設定
		AtlGetObjectSourceInterface( pUnkIE, &m_libid, &m_iid, &m_wMajorVerNum, &m_wMinorVerNum) ;

		// イベントをDispatch
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
	// アドレスバーの文字列変更
	SetWindowTextW( hwndAddressBar, pvUrl->bstrVal) ;
	return ;
}

// OnNewWindow2
void _stdcall OnNewWindow2( IDispatch** ppDisp, VARIANT_BOOL *pbCancel)
{
	// キャンセルする
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


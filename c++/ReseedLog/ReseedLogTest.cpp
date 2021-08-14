
//
//#include <iostream>
//#include <string>

#include <ReseedEngine/Libraries/Log.hpp>
#include <ReseedEngine/Libraries/Time.hpp>


#include <windows.h>

#include <boost/format.hpp>


#include <boost/utility.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>


int main()
{
	bool forked = true;
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));

		// ロギングの設定ファイルを指定
		RESEED_LOG_CONFIGURATION("./logging.conf");

	if (!CreateProcess(NULL, "telnet localhost 20000", NULL, NULL, FALSE, CREATE_NEW_CONSOLE | IDLE_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
		int err = GetLastError();
		forked = false;
		RESEED_LOG_ERROR("Game", boost::io::str(boost::format("Fork failed. [%d]") % err).c_str());
	}
	ReseedEngine::Libraries::sleep(1000000);

	//RESEED_LOG_ERROR("Graphics", "EffectPass::EffectPass() でアルファ情報取得に失敗しました");
	RESEED_LOG_DEBUG("Graphics", "Graphics--");



		if (forked) {
		TerminateProcess(pi.hProcess, 0);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	return 0;
}


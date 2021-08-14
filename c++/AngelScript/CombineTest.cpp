

#include <iostream>
#include <fstream>
#include <string>
#include "angelscript.h"

#ifdef _DEBUG
//デバッグビルドの場合
# pragma comment(lib, "angelscriptd.lib")
#else
//リリースビルドの場合
# pragma comment(lib, "angelscript.lib")
#endif

//AngelScriptから呼び出される関数
void asPrint()
{
	std::cout<<"Hello World! AngelScript"<<std::endl;
}

//main関数
int main(int argc, char* argv[])
{
	//asIScriptEngineの作成
	asIScriptEngine *lpEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

	//AngelScriptから呼び出したい関数の登録
	int result; //結果を受け取る変数。エラーの場合、負の値が返される
	result=lpEngine->RegisterGlobalFunction("void print()", asFUNCTION(asPrint), asCALL_CDECL);

	//スクリプトの読み込み
	FILE *f = fopen("D:/PersonalTool/xyzzy/laboratory/c++/AngelScript/ASTest.as", "rb");
	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	fseek(f, 0, SEEK_SET);
	std::string script;
	script.resize(len);
	size_t c = fread(&script[0], len, 1, f);
	fclose(f);

	//asIScriptModuleをゲット
	asIScriptModule *lpModule = lpEngine->GetModule("MyModule", asGM_ALWAYS_CREATE);

	//モジュールにスクリプトを追加
	lpModule->AddScriptSection("test.as", script.c_str(), script.length());

	//ビルド
	result = lpModule->Build();

	//関数の取得
	int funcId = lpModule->GetFunctionIdByDecl("void main()");

	//asIScriptContextの生成
	asIScriptContext *lpContext = lpEngine->CreateContext();

	//関数呼び出し
	lpContext->Prepare(funcId);
	result = lpContext->Execute();

	//後片付け
	lpContext->Release();
	lpEngine->Release();

	return 0;
}

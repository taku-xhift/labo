


#include <iostream>
#include <lua/lua.hpp>

int main()
{
	// Lua の VM を生成
	lua_State* L = lua_open();

	// Lua の標準ライブラリを開く
	luaL_openlibs(L);

	// Lua スクリプトで文字を表示してみる
	luaL_dostring(L, "print('Lua スクリプト開始！')"); 

	// Lua スクリプトの終了
	lua_close(L);

	return 0;
}



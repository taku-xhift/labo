


#include <iostream>
#include <lua/lua.hpp>

int main()
{
	// Lua �� VM �𐶐�
	lua_State* L = lua_open();

	// Lua �̕W�����C�u�������J��
	luaL_openlibs(L);

	// Lua �X�N���v�g�ŕ�����\�����Ă݂�
	luaL_dostring(L, "print('Lua �X�N���v�g�J�n�I')"); 

	// Lua �X�N���v�g�̏I��
	lua_close(L);

	return 0;
}



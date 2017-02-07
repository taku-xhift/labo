


static void printStackItem(lua_State* L, int idx)
{
	int type = lua_type(L, idx);

	switch (type)
	{
	case LUA_TSTRING:
		// 文字列アイテムの内容表示
		printf("index %2d : type = %s : \"%s\" \n", idx, lua_typename(L, type), lua_tostring(L, idx));
		break;
	case LUA_TNUMBER:
		// 数値アイテムの内容表示
		printf("index %2d : type = %s : %f\n", idx, lua_typename(L, type), lua_tonumber(L, idx));
		break;
	case LUA_TBOOLEAN:
		// ブール値アイテムの内容表示
		printf("index %2d : type = %s : \"%s\" \n", idx, lua_typename(L, type), lua_toboolean(L, idx) ? "true\n" : "false\n");
		break;
	default:
		// その他ならば型だけはひょ時
		printf("index %2d : type = %s\n", idx, lua_typename(L, type));
		break;
	}
}


void printStack(lua_State *L)
{
	std::cout << "----- stack -----" << std::endl;

	int top = lua_gettop(L);

	// 正のインデックスで指定
	for (int i = top; i >= 1; --i) {
		printStackItem(L, i);
	}

	std::cout << "-------------------" << std::endl;

	// 負のインデックスで指定
	for (int i = -1; i >= -top; --i) {
		printStackItem(L, i);
	}

	std::cerr << "----------------------" << std::endl;
}



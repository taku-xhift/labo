
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctype.h>
#include <time.h>



#include <lua.hpp>
#include "printStack.hpp"

#define MAX_SHOP_ITEMS 5    // 商品リストの最大サイズ



// コンソールに > とプロンプトを表示して、
// キー入力を受け取る関数
// title は入力待ちのプロンプトに表示される
// 入力された番号を変える
int getSelection(const char* title)
{
	char input[100];  // 入力用バッファ

	printf("%s >", title);

	// コンソールから文字入力
	fgets(input, sizeof(input), stdin);
	printf("\n");

	// 異常値検出
	if (strlen(input) == 0 || !isdigit(input[0])) {
		return 0;
	}

	// 文字列から数値を取得して返す
	return atoi(input);
}

// グルー関数
int getSelectionGlue(lua_State* L)
{
	// 引数を取得
	const char* title = lua_tostring(L, 1);

	// 目的の関数を実行
	int index = getSelection(title);

	// スタックをクリア
	lua_settop(L, 0);

	// かえりちを格納
	lua_pushnumber(L, index);

	return 1;    // 戻り値の数
}



// 商品情報をあらわす構造体
struct ItemInfo
{
	char name[100];     // アイテム名
	int price;          // 価格
};



// 販売アイテムの情報
ItemInfo shop_items[MAX_SHOP_ITEMS] = {
	{ "薬草", 100 },
	{ "こんぼう", 1000 },
	{ "布の服", 2000 },
	{ "", -1 },
	{ "", -1 },
};

//---------------------------------------
//  所持金に関する項目
//---------------------------------------
static int s_money = 0;     // 所持金


int getMoney()
{
	return s_money;
}

void setMoney(int money)
{
	s_money = money;
}


// getMoney のグルーコード
int getMoneyGlue(lua_State* L)
{
	int money = getMoney();

	lua_settop(L, 0);
	lua_pushnumber(L, money);

	return 1;
}


// setMoney のグルーコード
int setMoneyGlue(lua_State* L)
{
	int index = (int)(lua_tonumber(L, 1));

	setMoney(index);
	lua_settop(L, 0);

	return 0;   // 戻り値なし

}



//---------------------------------------
// 商品の名前を得る
//---------------------------------------
const char* getItemName(int index)
{
	if (index < 0 || index >= MAX_SHOP_ITEMS) {
		return NULL;
	}

	return shop_items[index].name;
}


// グルーコード
int getItemNameGlue(lua_State* L)
{
	//std::cout << "getItemName() 関数実行" << std::endl;

	// スタックを表示(開発用)
	//printStack(L);

	// 引数を取得
	int index = (int)lua_tonumber(L, 1);

	// 目的の関数を実行
	const char* name = getItemName(index);

	// スタックをクリア
	lua_settop(L, 0);

	// 返り値を格納
	lua_pushstring(L, name);

	// スタックを表示(開発用)
	//printStack(L);

	return 1;    // 戻り値の数
}


//---------------------------------------
// 商品の価格を得る
//---------------------------------------
int getItemPrice(int index)
{
	if (index < 0 || index >= MAX_SHOP_ITEMS) {
		return -1;
	}

	return shop_items[index].price;
}

int getItemPriceGlue(lua_State* L)
{
	//std::cout << "getItemPrice() 関数実行" << std::endl;

	// スタックの状況確認と初期化用パラ保存
	//printStack(L);
	int top = lua_gettop(L);

	int index = (int)(lua_tonumber(L, 1));

	int price = getItemPrice(index);

	// スタックの初期化
	lua_settop(L, top);

	lua_pushnumber(L, price);

	//printStack(L);

	return 1;
}




// お店のやり取りを行う関数
static int shop()
{
	printf("いらっしゃいませ！ 道具屋[ C 言語]へようこそ\n");

	while (true) {
		std::cout << "何にするかい？" << std::endl;
		std::cout << "(所持金：%d円)" << s_money << std::endl;

		for (int i = 0; i < MAX_SHOP_ITEMS; ++i) {
			ItemInfo* item = &shop_items[i];
			if (item->price == -1) {
				continue;
			}

			printf("%2d. %-10s %6d円\n", i+1, item->name, item->price);
		}
		std::cout << "0. 帰る" << std::endl;

		int num = getSelection("どうする？");

		// 0 番 → 帰る
		if (num == 0) {
			std::cout << "またいらっしゃい。" << std::endl;
			return 1;
		}

		// 異常値
		if (num < 0 || num > MAX_SHOP_ITEMS || shop_items[num-1].price == -1) {
			std::cout << "え？ なんだって？" << std::endl;
			continue;
		}

		// 選択したアイテムの情報
		ItemInfo* item = &shop_items[num - 1];

		// 所持金チェック
		if (s_money < item->price) {
			// お金が足りない
			std::cout << item->name << "だね。でもお金が足りないみたいだね。またおいて。" << std::endl;
			continue;
		}

		// 購入成功！
		std::cout << item->name << "だね。じゃあ" << item->price << "円いただくよ。\n" << std::endl;
		s_money -= item->price;
	}

	return 0;
}



int main()
{
	// 乱数初期化
	srand((unsigned int) time(NULL));

	for (int i = 0; i < 100; ++i) {
		rand();
	}

	// Lua の VM を生成
	lua_State* L = lua_open();

	// Lua の標準ライブラリを開く
	luaL_openlibs(L);

	// Lua スクリプトで文字を表示してみる
	int ret = luaL_dostring(L, "print('Lua スクリプト開始！')");

    
	// Lua に関数を追加
	lua_register(L, "getItemName",  getItemNameGlue);
	lua_register(L, "getItemPrice", getItemPriceGlue);
	lua_register(L, "getSelection", getSelectionGlue);
	lua_register(L, "getMoney",     getMoneyGlue);
	lua_register(L, "setMoney",     setMoneyGlue);

	// Lua に数値をバインド
	lua_pushnumber(L, MAX_SHOP_ITEMS);
	lua_setglobal(L, "MAX_SHOP_ITEMS");

	// 所持金決定
	s_money = (rand() * 10000/RAND_MAX) + 500;

		ret = luaL_dofile(L, "lua/shopAssistant.lua");
		lua_getglobal(L, "Shop");

	//---------------------------------
	//  Lua 内部での処理
	//      道具屋開始
	//---------------------------------

	while (true)
	{
		int top = lua_gettop(L);  // スタックの要素数を取得

		// Lua 関数実行
		//ret = luaL_dostring(L, "print('商品は '..getItemName(0)..' です！')");
		ret = lua_pcall(L, 0, 0, NULL);

		if (ret != 0) {
			std::cout << "error:" << lua_tostring(L, -1) << std::endl;
			lua_settop(L, top);
			std::cout << "< Push Enter for reload script! >" << std::endl;
			getchar();
		} else {
			lua_settop(L, top);
			break;
		}

		lua_settop(L, top);    // スタックの要素数を元に戻す
	}

	//getchar();

	// Lua スクリプトの終了
	lua_close(L);

	return 0;
}


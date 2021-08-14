
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctype.h>
#include <time.h>



#include <lua.hpp>
#include "printStack.hpp"

#define MAX_SHOP_ITEMS 5    // ���i���X�g�̍ő�T�C�Y



// �R���\�[���� > �ƃv�����v�g��\�����āA
// �L�[���͂��󂯎��֐�
// title �͓��͑҂��̃v�����v�g�ɕ\�������
// ���͂��ꂽ�ԍ���ς���
int getSelection(const char* title)
{
	char input[100];  // ���͗p�o�b�t�@

	printf("%s >", title);

	// �R���\�[�����當������
	fgets(input, sizeof(input), stdin);
	printf("\n");

	// �ُ�l���o
	if (strlen(input) == 0 || !isdigit(input[0])) {
		return 0;
	}

	// �����񂩂琔�l���擾���ĕԂ�
	return atoi(input);
}

// �O���[�֐�
int getSelectionGlue(lua_State* L)
{
	// �������擾
	const char* title = lua_tostring(L, 1);

	// �ړI�̊֐������s
	int index = getSelection(title);

	// �X�^�b�N���N���A
	lua_settop(L, 0);

	// �����肿���i�[
	lua_pushnumber(L, index);

	return 1;    // �߂�l�̐�
}



// ���i��������킷�\����
struct ItemInfo
{
	char name[100];     // �A�C�e����
	int price;          // ���i
};



// �̔��A�C�e���̏��
ItemInfo shop_items[MAX_SHOP_ITEMS] = {
	{ "��", 100 },
	{ "����ڂ�", 1000 },
	{ "�z�̕�", 2000 },
	{ "", -1 },
	{ "", -1 },
};

//---------------------------------------
//  �������Ɋւ��鍀��
//---------------------------------------
static int s_money = 0;     // ������


int getMoney()
{
	return s_money;
}

void setMoney(int money)
{
	s_money = money;
}


// getMoney �̃O���[�R�[�h
int getMoneyGlue(lua_State* L)
{
	int money = getMoney();

	lua_settop(L, 0);
	lua_pushnumber(L, money);

	return 1;
}


// setMoney �̃O���[�R�[�h
int setMoneyGlue(lua_State* L)
{
	int index = (int)(lua_tonumber(L, 1));

	setMoney(index);
	lua_settop(L, 0);

	return 0;   // �߂�l�Ȃ�

}



//---------------------------------------
// ���i�̖��O�𓾂�
//---------------------------------------
const char* getItemName(int index)
{
	if (index < 0 || index >= MAX_SHOP_ITEMS) {
		return NULL;
	}

	return shop_items[index].name;
}


// �O���[�R�[�h
int getItemNameGlue(lua_State* L)
{
	//std::cout << "getItemName() �֐����s" << std::endl;

	// �X�^�b�N��\��(�J���p)
	//printStack(L);

	// �������擾
	int index = (int)lua_tonumber(L, 1);

	// �ړI�̊֐������s
	const char* name = getItemName(index);

	// �X�^�b�N���N���A
	lua_settop(L, 0);

	// �Ԃ�l���i�[
	lua_pushstring(L, name);

	// �X�^�b�N��\��(�J���p)
	//printStack(L);

	return 1;    // �߂�l�̐�
}


//---------------------------------------
// ���i�̉��i�𓾂�
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
	//std::cout << "getItemPrice() �֐����s" << std::endl;

	// �X�^�b�N�̏󋵊m�F�Ə������p�p���ۑ�
	//printStack(L);
	int top = lua_gettop(L);

	int index = (int)(lua_tonumber(L, 1));

	int price = getItemPrice(index);

	// �X�^�b�N�̏�����
	lua_settop(L, top);

	lua_pushnumber(L, price);

	//printStack(L);

	return 1;
}




// ���X�̂������s���֐�
static int shop()
{
	printf("��������Ⴂ�܂��I ���[ C ����]�ւ悤����\n");

	while (true) {
		std::cout << "���ɂ��邩���H" << std::endl;
		std::cout << "(�������F%d�~)" << s_money << std::endl;

		for (int i = 0; i < MAX_SHOP_ITEMS; ++i) {
			ItemInfo* item = &shop_items[i];
			if (item->price == -1) {
				continue;
			}

			printf("%2d. %-10s %6d�~\n", i+1, item->name, item->price);
		}
		std::cout << "0. �A��" << std::endl;

		int num = getSelection("�ǂ�����H");

		// 0 �� �� �A��
		if (num == 0) {
			std::cout << "�܂���������Ⴂ�B" << std::endl;
			return 1;
		}

		// �ُ�l
		if (num < 0 || num > MAX_SHOP_ITEMS || shop_items[num-1].price == -1) {
			std::cout << "���H �Ȃ񂾂��āH" << std::endl;
			continue;
		}

		// �I�������A�C�e���̏��
		ItemInfo* item = &shop_items[num - 1];

		// �������`�F�b�N
		if (s_money < item->price) {
			// ����������Ȃ�
			std::cout << item->name << "���ˁB�ł�����������Ȃ��݂������ˁB�܂������āB" << std::endl;
			continue;
		}

		// �w�������I
		std::cout << item->name << "���ˁB���Ⴀ" << item->price << "�~����������B\n" << std::endl;
		s_money -= item->price;
	}

	return 0;
}



int main()
{
	// ����������
	srand((unsigned int) time(NULL));

	for (int i = 0; i < 100; ++i) {
		rand();
	}

	// Lua �� VM �𐶐�
	lua_State* L = lua_open();

	// Lua �̕W�����C�u�������J��
	luaL_openlibs(L);

	// Lua �X�N���v�g�ŕ�����\�����Ă݂�
	int ret = luaL_dostring(L, "print('Lua �X�N���v�g�J�n�I')");

    
	// Lua �Ɋ֐���ǉ�
	lua_register(L, "getItemName",  getItemNameGlue);
	lua_register(L, "getItemPrice", getItemPriceGlue);
	lua_register(L, "getSelection", getSelectionGlue);
	lua_register(L, "getMoney",     getMoneyGlue);
	lua_register(L, "setMoney",     setMoneyGlue);

	// Lua �ɐ��l���o�C���h
	lua_pushnumber(L, MAX_SHOP_ITEMS);
	lua_setglobal(L, "MAX_SHOP_ITEMS");

	// ����������
	s_money = (rand() * 10000/RAND_MAX) + 500;

		ret = luaL_dofile(L, "lua/shopAssistant.lua");
		lua_getglobal(L, "Shop");

	//---------------------------------
	//  Lua �����ł̏���
	//      ����J�n
	//---------------------------------

	while (true)
	{
		int top = lua_gettop(L);  // �X�^�b�N�̗v�f�����擾

		// Lua �֐����s
		//ret = luaL_dostring(L, "print('���i�� '..getItemName(0)..' �ł��I')");
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

		lua_settop(L, top);    // �X�^�b�N�̗v�f�������ɖ߂�
	}

	//getchar();

	// Lua �X�N���v�g�̏I��
	lua_close(L);

	return 0;
}


/**
 * @file
 * @brief C ‚Æ‚Ì˜AŒg‚ğl‚¦‚Ä‚İ‚é
 *
 * @author Takuya Shishido
 * @date   2009.12.07 10:47:53
 *
 * @version 0.01, Shishido Takuya, 2009.12.07 10:47:53
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

//extern "C" {
//#include <vector>
//#include <iostream>
//#include <cstdio>
//}

#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------
//  include
//-----------------------------------------------------
typedef struct Data
{
	int power;
	int diffence;
	int balance;
};


/**----------------------------------------------------
 * @brief sample function
 *---------------------------------------------------*/
struct Data* test()
//void test()
{
	/*
	std::vector<int> intContainer;

	for (int i = 0; i < 10; ++i) {
		intContainer.push_back(i);
	}

	for (std::vector<int>::iterator ite = intContainer.begin();
		 ite != intContainer.end();
		 ++ite)
	{
		std::cout << *ite << std::endl;
	}
	*/

	struct Data* data;
	data = malloc(sizeof(struct Data));

	data->power = 1;
	data->diffence = 2;
	data->balance = 3;

	return data;
}





#endif


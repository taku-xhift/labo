
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


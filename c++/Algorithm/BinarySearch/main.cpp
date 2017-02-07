//
//  main.cpp
//  Test
//
//  Created by Kaguya on 2014/01/12.
//  Copyright (c) 2014年 Kaguya. All rights reserved.
//

#include "bsearch.h"
#include <stdio.h>
// #include <stdlib.h>


int comparere(const void* key, const void* elt) {
	int key_ = *((int*)key);
	int elt_ = *((int*)elt);

	if (key_ > elt_) {
		return 1;
	} else if (key_ == elt_) {
		return 0;
	} else {
		return -1;
	}
}


int main(int argc, const char * argv[])
{
	int array[] = {1, 2, 3, 5, 8, 13, 21, 33};

	int key = 3;
	int* result = bsearch((const void*)&key, (const void*)array, sizeof(array)/sizeof(int), sizeof(int), comparere);

	if (result == NULL) {
		printf("No Match\n");
	} else {
		printf("Match!!!\nvalue : %d", *result);
	}

	return 0;
}


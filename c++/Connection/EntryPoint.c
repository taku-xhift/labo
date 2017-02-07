/**
 * @file
 * @brief エントリーポイント。これを使って perl から呼び出しをしてもらう。
 *
 * @author Takuya Shishido
 * @date   2010.04.02 10:44:24
 *
 * @version 0.01, Shishido Takuya, 2010.04.02 10:44:24
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


#include <stdio.h>
#include "LeagueModeCushion.hpp"

int main()
{
	while (1) {
		printf("%s\n", leagueModeCushion());
	}

	return 0;
}



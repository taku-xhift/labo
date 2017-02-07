/**
 * @file
 * @brief ある Int 型のデータだけを保存するクラス。mpl 用。
 *
 * @author Takuya Shishido
 * @date   2011.01.18 19:40:37
 *
 * @version 0.01, Shishido Takuya, 2011.01.18 19:40:37
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_WEOINTTYPE_HPP_INCLUDED
#define PM_MODE_WEOINTTYPE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
//#include "weCommonHeader.h"


namespace pm_mode {

	template<int N>
	struct IntType {
		static const int value = N;
	};

}    // namespace pm_mode


#endif


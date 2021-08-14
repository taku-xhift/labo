
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


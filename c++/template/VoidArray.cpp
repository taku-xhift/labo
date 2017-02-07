


#include "VoidArray.hpp"


	template<typename T> T &value() throw()
	{
		//// 取得される予定のデータ分先に移動しておいて
		//this->offset += sizeof(T);

		//// offset が加算される前のデータのポジションを返却
		//return *(*T)(this->pointer + this->offset - sizeof(T));
		return *(T*)(this->voidData);
	}


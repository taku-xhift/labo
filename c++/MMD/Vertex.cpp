/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2012.07.10 23:43:06
 *
 * @version 0.01, Shishido Takuya, 2012.07.10 23:43:06
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include "Vertex.hpp"


namespace mmd {


// 出力用の<<演算子定義
std::ostream& operator<<(std::ostream& os, const IndexTrio& this_)
{
	os << "index(" <<
		this_.indices_.at(0) << ", " <<
			this_.indices_.at(1) << ", " <<
				this_.indices_.at(2) << ")\n";

	return os;
}



//! \brief constructor
Vertex::Vertex() throw()
	: pos_(Vec3(3))
	, normal_(Vec3(3))
	, boneWeight_(0)
	, edgeFlag_(0)
{
	memset(this->uv_, 0x00, sizeof(this->uv_));
	memset(this->boneNum_, 0x00, sizeof(this->boneNum_));
}


//! \brief destructor
Vertex::~Vertex() throw()
{

}


// 出力用の<<演算子定義
std::ostream& operator<<(std::ostream& os, const Vertex& this_)
{
	os << "pos => ("       << this_.pos_(0)     << ", " << this_.pos_(1)     << ", " << this_.pos_(2)    << ")\n";
	os << "normal => ("    << this_.normal_(0)  << ", " << this_.normal_(1)  << ", " << this_.normal_(2) << ")\n";
	os << "uv => ("        << this_.uv_[0]      << ", " << this_.uv_[1]      << ")\n";
	os << "boneNum => ("   << this_.boneNum_[0] << ", " << this_.boneNum_[1] << ")\n";
	os << "boneWeight => " << this_.boneWeight_ << "\n";
	os << "edgeFlag_ => "  << this_.edgeFlag_   << "\n";

	return os;

}


}    // namespace mmd


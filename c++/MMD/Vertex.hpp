
#ifndef MMD_VERTEX_HPP_INCLUDED
#define MMD_VERTEX_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <Windows.h>
#include <boost/numeric/ublas/vector.hpp>
#include "TypeHeader.hpp"


namespace mmd {


typedef boost::numeric::ublas::vector<float32> Vec3;


struct IndexTrio
{
	friend std::ostream& operator<<(std::ostream& os, const IndexTrio& this_);
public:

	IndexTrio() throw()
		: indices_(3)
	{
	}

	void setIndices(WORD (&array)[3]) throw() {
		this->indices_.at(0) = array[0];
		this->indices_.at(1) = array[1];
		this->indices_.at(2) = array[2];
	}

private:
	std::vector<WORD> indices_;
};



class Vertex
{
	friend std::ostream& operator<<(std::ostream& os, const Vertex& this_);

public:

	//! \brief constructor
	Vertex() throw();


	//! \brief destructor
	~Vertex() throw();


	const Vec3& getPos() const               { return this->pos_; }
	void setPos(const Vec3& pos)             { this->pos_ = pos; }
	void setPos(float32 x, float32 y, float32 z)    { this->pos_(0) = x; this->pos_(1) = y; this->pos_(2) = z; }
	const Vec3& getNormal() const            { return this->normal_; }
	void setNormal(const Vec3& normal)       { this->normal_ = normal; }
	void setNormal(float32 x, float32 y, float32 z)    { this->normal_(0) = x; this->normal_(1) = y; this->normal_(2) = z; }

	float32 getU() const                     { return this->uv_[0]; }
	float32 getV() const                     { return this->uv_[1]; }
	void setUV(float32 u, float32 v)         { this->uv_[0] = u; this->uv_[1] = v; }
	WORD getFistBone() const                 { return this->boneNum_[0]; }
	WORD getSecondBone() const               { return this->boneNum_[1]; }
	void setBoneNum(WORD first, WORD second) { this->boneNum_[0] = first; this->boneNum_[1] = second; }
	BYTE getBoneWeight() const               { return this->boneWeight_; }
	void setBoneWeight(BYTE boneWeight)      { this->boneWeight_ = boneWeight; }
	BYTE getEdgeFlag() const                 { return this->edgeFlag_; }
	void setEdgeFlag(BYTE edgeFlag)          { this->edgeFlag_ = edgeFlag; }


private:

	Vec3    pos_;
	Vec3    normal_;
	float32 uv_[2];
	WORD    boneNum_[2];
	BYTE    boneWeight_;
	BYTE    edgeFlag_;

};    // class Vertex

}    // namespace mmd


#endif


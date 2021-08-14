
#ifndef MMD_MATERIAL_HPP_INCLUDED
#define MMD_MATERIAL_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "TypeHeader.hpp"
#include <Windows.h>


namespace mmd {


class Material
{
public:

	//! \brief constructor
	Material() throw();


	//! \brief destructor
	~Material() throw();


	const float32* getDiffuseColor() const            { return this->diffuseColor_; }
	void setDiffusecolor(float32 (&diffuseColor)[3])  { this->diffuseColor_[0] = diffuseColor[0]; this->diffuseColor_[1] = diffuseColor[1]; this->diffuseColor_[2] = diffuseColor[2]; }
	float32 getAlpha() const                          { return this->alpha_; }
	void setAlpha(float32 alpha)                      { this->alpha_ = alpha; }
	float32 getSpecularity() const                    { return this->specularity_; }
	void setSpecularity(float32 specularity)          { this->specularity_ = specularity; }
	const float32* getDiffusecolor() const            { return this->specularColor_; }
	void setDiffusecolor(float32 (&specularColor)[3]) { this->specularColor_[0] = specularColor[0]; this->specularColor_[1] = specularColor[1]; this->specularColor_[2] = specularColor[2]; }
	const float32* getMirrorColor() const             { return this->mirrorColor_; }
	void setMirrorColor_(float32 (&mirrorColor)[3])   { this->mirrorColor_[0] = mirrorColor[0]; this->mirrorColor_[1] = mirrorColor[1]; this->mirrorColor_[2] = mirrorColor[2]; }
	BYTE getToonindex() const                         { return this->toonIndex_; }
	void setToonindex(BYTE toonIndex)                 { this->toonIndex_ = toonIndex; }
	BYTE getEdgeflag() const                          { return this->edgeFlag_; }
	void setEdgeflag(BYTE edgeFlag)                   { this->edgeFlag_ = edgeFlag; }
	DWORD getFacevertexcount() const                  { return this->faceVertexCount_; }
	void setFacevertexcount(DWORD faceVertexCount)    { this->faceVertexCount_ = faceVertexCount; }


private:

	float32     diffuseColor_[3];       //!< 減衰色
	float32     alpha_;
	float32     specularity_;
	float32     specularColor_[3];      //!< 光沢色
	float32     mirrorColor_[3];        //!< 環境色(ambient)
	BYTE        toonIndex_;
	BYTE        edgeFlag_;              //!< 輪郭
	DWORD       faceVertexCount_;
	std::string textureFileName_;

};    // class Material

}    // namespace mmd


#endif


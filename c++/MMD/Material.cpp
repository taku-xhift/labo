
//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "Material.hpp"


namespace mmd {

//! \brief constructor
Material::Material() throw()
	: alpha_(.0f)
	, specularity_(.0f)
	, toonIndex_(0)
	, edgeFlag_(0)
	, faceVertexCount_(0)
{
	memset(this->diffuseColor_, 0x00, sizeof(this->diffuseColor_));
	memset(this->specularColor_, 0x00, sizeof(this->specularColor_));
	memset(this->mirrorColor_, 0x00, sizeof(this->mirrorColor_));
}


//! \brief destructor
Material::~Material() throw()
{

}


}    // namespace mmd


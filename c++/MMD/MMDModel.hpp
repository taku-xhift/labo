
#ifndef MMD_MMDMODEL_HPP_INCLUDED
#define MMD_MMDMODEL_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <vector>
#include <string>
#include "TypeHeader.hpp"
#include "Vertex.hpp"
#include "Material.hpp"


namespace mmd {

struct UnFoundFileException;


class Model
{
	friend std::ostream& operator<<(std::ostream& os, const Model& this_);

public:

	static const int32 headerSize = 4;

	//! \brief constructor
	Model(const char* fileName) throw(UnFoundFileException);


	//! \brief destructor
	~Model() throw();


private:

	std::string         fileName_;
	char                header_[headerSize];
	float32             version_;
	std::string         modelName_;
	std::string         comment_;

	std::vector<Vertex>     vertices_;
	std::vector<IndexTrio>  indices_;
	std::vector<Material>   materials_;

};    // class MMDModel

}    // namespace mmd


#endif


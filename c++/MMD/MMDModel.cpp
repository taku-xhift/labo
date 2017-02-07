/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2012.07.10 23:05:33
 *
 * @version 0.01, Shishido Takuya, 2012.07.10 23:05:33
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <iostream>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include "boost/foreach.hpp"
#include <Windows.h>
#include "MMDModel.hpp"
#include "Exception.hpp"


namespace mmd {

//! \brief constructor
Model::Model(const char* fileName) throw(UnFoundFileException)
	: fileName_(fileName)
//	, header_()
{
	memset(this->header_, 0x00, sizeof(this->header_));

	std::ifstream fin(fileName, std::ios::in|std::ios::binary);

	if (!fin) {
		// error to open a file
		assert(false);
		throw UnFoundFileException();
	}

	// header 部分読み込み
	{
		const int8 pmdMagicDataSize = 3;
		fin.read(this->header_, sizeof(char)*pmdMagicDataSize);

		fin.read((char*)&this->version_, sizeof(this->version_));

		char temp[0x100 + 1] = {0};
		const uint8 modelNameSize = 20;
		fin.read(temp, sizeof(char) * modelNameSize);
		this->modelName_ = temp;

		const uint16 modelComment = 0x100;
		fin.read(temp, sizeof(char) * modelComment);
		this->comment_ = temp;
	}

	// 頂点情報取得
	{
		DWORD vertexCount = 0;
		fin.read((char*)&vertexCount, sizeof(vertexCount));
		this->vertices_.resize(vertexCount);

		float32 pos[3] = {0};
		float32 normal[3] = {0};
		float32 uv[2] = {0};
		WORD boneNum[2] = {0};
		BYTE boneWeight = 0;
		BYTE edgeFlag = 0;

		int32 sizeofPos = sizeof(pos);

		for (uint16 i = 0; i < vertexCount; ++i) {
			fin.read((char*)&pos, sizeof(pos));
			fin.read((char*)&normal, sizeof(normal));
			fin.read((char*)&uv, sizeof(uv));
			fin.read((char*)&boneNum, sizeof(boneNum));
			fin.read((char*)&boneWeight, sizeof(boneWeight));
			fin.read((char*)&edgeFlag, sizeof(edgeFlag));

			this->vertices_.at(i).setPos(pos[0], pos[1], pos[2]);
			this->vertices_.at(i).setNormal(normal[0], normal[1], normal[2]);
			this->vertices_.at(i).setUV(uv[0], uv[1]);
			this->vertices_.at(i).setBoneNum(boneNum[0], boneNum[1]);
			this->vertices_.at(i).setBoneWeight(boneWeight);
			this->vertices_.at(i).setEdgeFlag(edgeFlag);
		}
	}

	// 頂点の作り方リスト
	{
		DWORD faceVertexCount = 0;
		fin.read((char*)&faceVertexCount, sizeof(faceVertexCount));
		this->indices_.resize(faceVertexCount);

		WORD index[3] = {0};
		for (DWORD i = 0; i < faceVertexCount; ++i) {
			fin.read((char*)&index, sizeof(index));
			this->indices_.at(i).setIndices(index);
		}
	}

	// Material
	{
		DWORD materialNum = 0;
		fin.read((char*)&materialNum, sizeof(materialNum));
		this->materials_.resize(materialNum);
	}
}


//! \brief destructor
Model::~Model() throw()
{

}


// 出力用の<<演算子定義
std::ostream& operator<<(std::ostream& os, const Model& this_)
{
	os << "fileName => "  << this_.fileName_  << "\n";
	os << "header => "    << this_.header_    << "\n";
	os << "version => "   << this_.version_   << "\n";
	os << "modelName => " << this_.modelName_ << "\n";
	os << "comment => "   << this_.comment_   << "\n";

	BOOST_FOREACH(const Vertex& vertex, this_.vertices_) {
		os << vertex << "\n";
	}
	BOOST_FOREACH(const IndexTrio& index, this_.indices_) {
		os << index;
	}

	return os;
}

}    // namespace mmd


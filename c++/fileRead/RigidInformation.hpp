//! \file
//! \brief 剛体取扱用データクラス
//!
//! <詳細+構想>
//!		このクラスはあくまで剛体を取り扱うための
//!         データのためのクラスとなっています。
//!     これを使用することで Havok のデータクラスを直接見なくて済みます。
//!     しかしこれはあくまでラップクラスとなりますのでオーバーヘッドが
//!         増えるだけの形になってしまうかも。
//!
//! \author T. Shishido
//! \date	2009-01-09
//!
//! \version 0.01, Takuya Shishido, 2009-01-14
//!
//! (c) 2008 Uehara seminar


#ifndef RESEEDENGINE_PHYSICS_HAVOK_RIGID_RIGIDINFORMATION_HPP
#define RESEEDENGINE_PHYSICS_HAVOK_RIGID_RIGIDINFORMATION_HPP

//----------------------------------------------------
//	インクルード
//----------------------------------------------------
#include <boost/numeric/ublas/vector.hpp>
#include <boost/math/quaternion.hpp>

#include "PhysicsTypes.hpp"

#include <string>



namespace ReseedEngine
{
	namespace Physics
	{
		//!	\brief  剛体登録のための必須パラメータを紹介するクラス
		//!	\autor  T. Shishido
		//!	\data   2009-01-14
		class RigidInformation
		{
		public:

			//! \brief パラメータをファイルから読み取る関数
			//! \param[in]    path    ファイルまでのパス
			void readFromFile(const std::string &path);

			//! \brief    パラメータを設定するための関数
			//!               ただし giveTheData とは違う
			//! \param[out]    parameter    これを素に代入を行う
			//! \param[in]     x            parameter[0] に代入される値
			//! \param[in]     y            parameter[1] に代入される値
			//! \param[in]     z            parameter[2] に代入される値
			void setParameter(Vector3 &parameter, float x, float y, float z) throw()
			{
				parameter[0] = x;
				parameter[1] = y;
				parameter[2] = z;
			}


		public:
			//!	\brief	コンストラクタ
			RigidInformation() throw()
				: position(3),
				size(3),
				axis(3),
				velocity(3),
				vertex(3)
			{
				this->initialize();
				this->existenceForm = EXISTENCEFORM_RIGID;
				this->collisionQuality = COLLISIONQUALITY_MOVE;
			}

			//!	\brief	デストラクタ
			virtual ~RigidInformation() throw() {};

			//! \brief   初期化関数
			void initialize() throw()
			{
				this->position[0] = this->position[1] = this->position[2] = .0f;
				this->size[0] = this->size[1] = this->size[2] = 1.0f;
				this->axis[0] = this->axis[1] = this->axis[2] = .0f;
				this->velocity[0] = this->velocity[1] = this->velocity[2] = .0f;
				this->quaternion = boost::math::quaternion<float>(.0f, .0f, .0f, .0f);
				this->mass = 1.0f;
				this->angle = .0f;
				this->linearDamping = 1.0f;
				this->angularDamping = 1.0f;
				this->friction = .4f;
				this->restitution = .5f;
				this->radius = 1.0f;
				this->shape = SHAPELIST_INVALID;
				this->existenceForm = RigidInformation::EXISTENCEFORM_INVALID;
				this->collisionQuality = COLLISIONQUALITY_INVALID;
				//this->collisionGroup = COLLISIONGROUP_RIGIDBODY;

				this->vertex[0] = this->vertex[1] = this->vertex[2] = .0f;
				this->vertexArray.clear();
				/*for (int i = 0; i < 5; ++i) {
					vertexArray.push_back(this->vertex);
				}*/
			};


		public:
			//! \brief    形状(enum) 登録の際に指定が必要
			enum ShapeList
			{
				SHAPELIST_RIGID_SPHERE = 0,
				SHAPELIST_RIGID_BOX,
				SHAPELIST_RIGID_PLANE,
				SHAPELIST_RIGID_CAPSULE,
				SHAPELIST_RIGID_TRYANGLE,
				SHAPELIST_RIGID_PYRAMID,
				SHAPELIST_RIGID_GEOMETRY,

				SHAPELIST_PHANTOM_SPHERE,
				SHAPELIST_PHANTOM_BOX,
				SHAPELIST_PHANTOM_PLANE,
				SHAPELIST_PHANTOM_CAPSULE,
				//SHAPELIST_PHANTOM_TRIANGLE,
				//SHAPELIST_PHANTOM_PYRAMID,
				//SHAPELIST_PHANTOM_GEOMETRY,

				SHAPELIST_INVALID,    //!< 未指定
			};


			//! \brief    存在の在り方 登録の際に必要
			enum ExistenceForm
			{
				EXISTENCEFORM_RIGID = 0,  //!< 普通の剛体衝突として登録する場合
				EXISTENCEFORM_FIXED,      //!< 固定の物体として登録する場合
				EXISTENCEFORM_CHARACTER,  //!< キャラクタとして登録する場合

				EXISTENCEFORM_INVALID,    //!< 未指定
			};


			//! \brief    存在の在り方 登録の際に必要
			enum CollisionQuality
			{
				COLLISIONQUALITY_FIXED,       //!< 固定物用。
				COLLISIONQUALITY_MOVE,        //!< 移動するもの。一般に使う。
				COLLISIONQUALITY_CRITICAL,    //!< コリジョン抜けさせたくない場合は全ての剛体をこれにする。
				COLLISIONQUALITY_BULLET,      //!< 高速の場合。言い換えれば Move は高速の場合抜ける可能性がある。
				COLLISIONQUALITY_CHARACTER,   //!< キャラクタ用。

				COLLISIONQUALITY_INVALID,    //!< 未指定
			};



	//------------------------------------------------------
	//	公開メンバ
	//      以下のメンバは必ずデータを入れておいてください
	//------------------------------------------------------

		public:
			Vector3             position;
			Vector3             size;
			Vector3             axis;                //!< 回転軸
			Vector3             velocity;            //!< 速度
			Quaternion          quaternion;          //!< 回転
			Real                radius;              //!< 球：半径,カプセル：最初に構成される球の大きさ
			Real                mass;                //!< 質量
			Real                angle;               //!< 回転量
			Real                linearDamping;       //!< エネルギー減衰率
			Real                angularDamping;      //!< 回転エネルギー減衰率
			Real                friction;            //!< 摩擦係数
			Real                restitution;         //!< 反発係数
			ShapeList           shape;               //!< 形状
			ExistenceForm       existenceForm;       //!< 存在状態の設定
			CollisionQuality    collisionQuality;    //!< 衝突のクオリティ
			//CollisionGroup      collisionGroup;      //!< 衝突グループの設定


	//------------------------------------------------------
	//	公開メンバ
	//    以下のメンバは特殊な使い方を要求します。
	//
	//      1. box を作る場合は１番目を使いそれをサイズとします。
	//      2. capsule を作る場合は２番目までを使いそれを頂点とします。
	//      3. tryangle を作る場合は３番目までを使いそれを頂点とします。
	//      4. pyramid や geometry を作る場合は４番目までを使いそれを頂点とします。
	//
	//    例えば box を作る場合は ２番目以降が初期化されていることを要求しません。
	//      そして以下のメンバは boost→vector の容量が３、
	//      vertexArray は容量４になります。
	//------------------------------------------------------
			Vector3                 vertex;
			std::vector<Vector3>    vertexArray;


			// vertexArray アクセス用にでも使ってください。
			enum VertexName
			{
				VERTEXNAME_HALFEXTENTS = 0,    //!< box の大きさ指定のためのアクセス

				VERTEXNAME_CAPSULE_LEFT = 0,   //!< capsule の片方の頂点名
				VERTEXNAME_CAPSULE_RIGHT = 1,  //!< capsule のもう片方の頂点名

				VERTEXNAME_PLANE_A = 0,        //!< plane の１頂点目
				VERTEXNAME_PLANE_B = 1,        //!< plane の２頂点目
				VERTEXNAME_PLANE_C = 2,        //!< plane の３頂点目

				VERTEXNAME_TRYANGLE_A = 0,     //!< pyramid の１頂点目
				VERTEXNAME_TRYANGLE_B = 1,     //!< pyramid の２頂点目
				VERTEXNAME_TRYANGLE_C = 2,     //!< pyramid の３頂点目
				VERTEXNAME_TRYANGLE_D = 3,     //!< pyramid の４頂点目

				VERTEXNAME_GEOMETRY_A = 0,     //!< geometry の１頂点目
				VERTEXNAME_GEOMETRY_B = 1,     //!< geometry の２頂点目
				VERTEXNAME_GEOMETRY_C = 2,     //!< geometry の３頂点目
				VERTEXNAME_GEOMETRY_D = 3,     //!< geometry の４頂点目

				VERTEXNAME_MAX,                //!< 最大数
			};

		};

	}    // namespace Physics
}    // namespace ReseedEngine


#endif    // RESEEDENGINE_PHYSICS_HAVOK_RIGID_RIGIDINFORMATION_HPP


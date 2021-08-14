//! \file
//! \brief ���̎戵�p�f�[�^�N���X
//!
//! <�ڍ�+�\�z>
//!		���̃N���X�͂����܂ō��̂���舵�����߂�
//!         �f�[�^�̂��߂̃N���X�ƂȂ��Ă��܂��B
//!     ������g�p���邱�Ƃ� Havok �̃f�[�^�N���X�𒼐ڌ��Ȃ��čς݂܂��B
//!     ����������͂����܂Ń��b�v�N���X�ƂȂ�܂��̂ŃI�[�o�[�w�b�h��
//!         �����邾���̌`�ɂȂ��Ă��܂������B
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
//	�C���N���[�h
//----------------------------------------------------
#include <boost/numeric/ublas/vector.hpp>
#include <boost/math/quaternion.hpp>

#include "PhysicsTypes.hpp"

#include <string>



namespace ReseedEngine
{
	namespace Physics
	{
		//!	\brief  ���̓o�^�̂��߂̕K�{�p�����[�^���Љ��N���X
		//!	\autor  T. Shishido
		//!	\data   2009-01-14
		class RigidInformation
		{
		public:

			//! \brief �p�����[�^���t�@�C������ǂݎ��֐�
			//! \param[in]    path    �t�@�C���܂ł̃p�X
			void readFromFile(const std::string &path);

			//! \brief    �p�����[�^��ݒ肷�邽�߂̊֐�
			//!               ������ giveTheData �Ƃ͈Ⴄ
			//! \param[out]    parameter    �����f�ɑ�����s��
			//! \param[in]     x            parameter[0] �ɑ�������l
			//! \param[in]     y            parameter[1] �ɑ�������l
			//! \param[in]     z            parameter[2] �ɑ�������l
			void setParameter(Vector3 &parameter, float x, float y, float z) throw()
			{
				parameter[0] = x;
				parameter[1] = y;
				parameter[2] = z;
			}


		public:
			//!	\brief	�R���X�g���N�^
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

			//!	\brief	�f�X�g���N�^
			virtual ~RigidInformation() throw() {};

			//! \brief   �������֐�
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
			//! \brief    �`��(enum) �o�^�̍ۂɎw�肪�K�v
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

				SHAPELIST_INVALID,    //!< ���w��
			};


			//! \brief    ���݂݂̍�� �o�^�̍ۂɕK�v
			enum ExistenceForm
			{
				EXISTENCEFORM_RIGID = 0,  //!< ���ʂ̍��̏Փ˂Ƃ��ēo�^����ꍇ
				EXISTENCEFORM_FIXED,      //!< �Œ�̕��̂Ƃ��ēo�^����ꍇ
				EXISTENCEFORM_CHARACTER,  //!< �L�����N�^�Ƃ��ēo�^����ꍇ

				EXISTENCEFORM_INVALID,    //!< ���w��
			};


			//! \brief    ���݂݂̍�� �o�^�̍ۂɕK�v
			enum CollisionQuality
			{
				COLLISIONQUALITY_FIXED,       //!< �Œ蕨�p�B
				COLLISIONQUALITY_MOVE,        //!< �ړ�������́B��ʂɎg���B
				COLLISIONQUALITY_CRITICAL,    //!< �R���W�����������������Ȃ��ꍇ�͑S�Ă̍��̂�����ɂ���B
				COLLISIONQUALITY_BULLET,      //!< �����̏ꍇ�B����������� Move �͍����̏ꍇ������\��������B
				COLLISIONQUALITY_CHARACTER,   //!< �L�����N�^�p�B

				COLLISIONQUALITY_INVALID,    //!< ���w��
			};



	//------------------------------------------------------
	//	���J�����o
	//      �ȉ��̃����o�͕K���f�[�^�����Ă����Ă�������
	//------------------------------------------------------

		public:
			Vector3             position;
			Vector3             size;
			Vector3             axis;                //!< ��]��
			Vector3             velocity;            //!< ���x
			Quaternion          quaternion;          //!< ��]
			Real                radius;              //!< ���F���a,�J�v�Z���F�ŏ��ɍ\������鋅�̑傫��
			Real                mass;                //!< ����
			Real                angle;               //!< ��]��
			Real                linearDamping;       //!< �G�l���M�[������
			Real                angularDamping;      //!< ��]�G�l���M�[������
			Real                friction;            //!< ���C�W��
			Real                restitution;         //!< �����W��
			ShapeList           shape;               //!< �`��
			ExistenceForm       existenceForm;       //!< ���ݏ�Ԃ̐ݒ�
			CollisionQuality    collisionQuality;    //!< �Փ˂̃N�I���e�B
			//CollisionGroup      collisionGroup;      //!< �Փ˃O���[�v�̐ݒ�


	//------------------------------------------------------
	//	���J�����o
	//    �ȉ��̃����o�͓���Ȏg������v�����܂��B
	//
	//      1. box �����ꍇ�͂P�Ԗڂ��g��������T�C�Y�Ƃ��܂��B
	//      2. capsule �����ꍇ�͂Q�Ԗڂ܂ł��g������𒸓_�Ƃ��܂��B
	//      3. tryangle �����ꍇ�͂R�Ԗڂ܂ł��g������𒸓_�Ƃ��܂��B
	//      4. pyramid �� geometry �����ꍇ�͂S�Ԗڂ܂ł��g������𒸓_�Ƃ��܂��B
	//
	//    �Ⴆ�� box �����ꍇ�� �Q�Ԗڈȍ~������������Ă��邱�Ƃ�v�����܂���B
	//      �����Ĉȉ��̃����o�� boost��vector �̗e�ʂ��R�A
	//      vertexArray �͗e�ʂS�ɂȂ�܂��B
	//------------------------------------------------------
			Vector3                 vertex;
			std::vector<Vector3>    vertexArray;


			// vertexArray �A�N�Z�X�p�ɂł��g���Ă��������B
			enum VertexName
			{
				VERTEXNAME_HALFEXTENTS = 0,    //!< box �̑傫���w��̂��߂̃A�N�Z�X

				VERTEXNAME_CAPSULE_LEFT = 0,   //!< capsule �̕Е��̒��_��
				VERTEXNAME_CAPSULE_RIGHT = 1,  //!< capsule �̂����Е��̒��_��

				VERTEXNAME_PLANE_A = 0,        //!< plane �̂P���_��
				VERTEXNAME_PLANE_B = 1,        //!< plane �̂Q���_��
				VERTEXNAME_PLANE_C = 2,        //!< plane �̂R���_��

				VERTEXNAME_TRYANGLE_A = 0,     //!< pyramid �̂P���_��
				VERTEXNAME_TRYANGLE_B = 1,     //!< pyramid �̂Q���_��
				VERTEXNAME_TRYANGLE_C = 2,     //!< pyramid �̂R���_��
				VERTEXNAME_TRYANGLE_D = 3,     //!< pyramid �̂S���_��

				VERTEXNAME_GEOMETRY_A = 0,     //!< geometry �̂P���_��
				VERTEXNAME_GEOMETRY_B = 1,     //!< geometry �̂Q���_��
				VERTEXNAME_GEOMETRY_C = 2,     //!< geometry �̂R���_��
				VERTEXNAME_GEOMETRY_D = 3,     //!< geometry �̂S���_��

				VERTEXNAME_MAX,                //!< �ő吔
			};

		};

	}    // namespace Physics
}    // namespace ReseedEngine


#endif    // RESEEDENGINE_PHYSICS_HAVOK_RIGID_RIGIDINFORMATION_HPP


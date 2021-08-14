/***********************************************************
 * Hajime no Ippo --- file : hjime.cpp
 ***********************************************************/
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

#define MAX_CONTACTS 4 // $B:GBg$N>WFM8!=P2DG=?t(B
static dWorldID world; // ���[���h�̐ݒ�
static dSpaceID space; // �X�y�[�X�h�c�̐ݒ�
static dJointGroupID contactgroup;
		// �Փ˃O���[�v�̐ݒ�B���ł���Ɉ������������ꍇ�͏Փ˂��Ȃ��ݒ�ɂȂ��Ă���

static dBodyID box;    // �{�b�N�X�̐錾
static dGeomID geom;   // 
dReal  box_sizes[3] = { 2.0, 1.0, 3.0 };
                       // �����Ń{�b�N�X�̃T�C�Y�����肵�Ă��܂��Ă���

#ifdef dDOUBLE
  #define dsDrawBox dsDrawBoxD
#endif

// �R�[���o�b�N�֐��̐ݒ�
static void nearCallback( void *data, dGeomID o1, dGeomID o2 )
{
  dBodyID b1 = dGeomGetBody( o1 ); // ���� o1 �̌`��擾
  dBodyID b2 = dGeomGetBody( o2 ); // ���� o2 �̌`��擾

  if ( b1 && b2 && dAreConnectedExcluding( b1, b2, dJointTypeContact ) )
    return; // �Փ˔�����s��Ȃ��O���[�v�����������ꍇ�͂����ŏI��(���Ԃ�)

  dContact contact[MAX_CONTACTS];
  for ( int i=0; i<MAX_CONTACTS; i++ )
  {
    // �Փ˂ɕK�v�ȏ����̐ݒ�
    contact[i].surface.mode = dContactBounce | dContactSoftCFM;	// �n�ʂ̔����W����ݒ肵�Ă���炵��
    contact[i].surface.mu = dInfinity;   // �s���B�ł��K����`����Ă��Ȃ���΂Ȃ�Ȃ��炵���B
    contact[i].surface.bounce = 0.1;     // �����W���̐ݒ�(0�`1.0)
    contact[i].surface.soft_cfm = 0.5;  // �Փ˂����Ƃ��̃I�u�W�F�N�g�̕ό`�x����
  }

  // ���ۂ̌��ؕ����H
  int numc = dCollide( o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof( dContact ) ); 
  if ( numc > 0 )
  {
    for ( int i=0; i<numc; i++ )
    {
      // �R���^�N�g�W���C���g����
      dJointID c = dJointCreateContact( world, contactgroup, contact+i );
                                 // �ڐG���Ă���Q��geometry���R���^�N�g�W���C���g�ōS��
      dJointAttach( c, b1, b2 ); // �����������̂��܂��������
    }
  }
}

// start simulation - set viewpoint
static void start()
{
  static float xyz[3] = { 0.f, 5.f, 3.f };
  static float hpr[3] = { -90.f, -15.f, 0.f };

  dsSetViewpoint( xyz, hpr ); // ��ŃZ�b�g���ꂽ�p�������ɍs��
}

// simulation loop �c ���[�v����
static void simLoop( int pause )
{
  dSpaceCollide( space, 0, &nearCallback ); // �Փ˔���ɕK�v�B�����K���ŏ��ɏ����Ȃ��Ă͂����Ȃ��炵��

  // Ctl+p �|�[�Y�̐ݒ肩�ȁH
  if (!pause)
  {
    dWorldStep( world, 0.01 ); // �|�[�Y�łȂ������炱�̕������X�e�b�v���i��
  }

  dJointGroupEmpty( contactgroup ); // �W���C���g�O���[�v����ɂ���

  // �I�u�W�F�N�g�̕`��
  dsSetColor( 1, 1, 0 ); // RGB Color
  dsDrawBox( dBodyGetPosition( box ),
             dBodyGetRotation( box ),
             box_sizes );
}


int main( int argc, char* argv[] )
{
  // setup pointers to drawstuff callback functions
  dsFunctions fn;
  fn.version = DS_VERSION;
  fn.start   = &start;
  fn.step    = &simLoop;
  fn.command = 0;
  fn.stop    = 0;
  fn.path_to_textures = "../drawstuff/textures";

  // create world
  world = dWorldCreate();         // �X�y�[�X(�Փː��E)�̐���
  space = dHashSpaceCreate( 0 );  // �Փˌ��o�X�y�[�X�̐���
  contactgroup = dJointGroupCreate( 0 );     // �R���^�N�g�O���[�v(�ڐG�_���i�[�����)�̐���
  dCreatePlane( space, 0, 0, 1, 0 );         // �n�ʂƂ���2D�𐶐�
  dWorldSetGravity( world, 0.0, 0.0, -9.8 ); // �d�͉����x�̐ݒ�

  // create box
  box = dBodyCreate( world );     // �{�b�N�X�����[���h�ɐ���
  dReal pos[3] = { 0.0, 0.0, 6.0 };
  dBodySetPosition( box, pos[0], pos[1], pos[2] );
                                  // �{�b�N�X�̃|�W�V������ݒ�
  geom = dCreateBox( space, box_sizes[0], box_sizes[1], box_sizes[2] );
                                  // �{�b�N�X�̑傫����ݒ肵�Ă���H
  dGeomSetBody( geom, box );      // �����Ď��ۂɏ�Ō��߂��傫���̃{�b�N�X�𐶐����Ă���

  // starting simulation
  dsSimulationLoop( argc, argv, 320, 240, &fn );
				// �������V���~���[�V�����J�n�����B��������Փ˔���̑S�Ă��n�܂�
				// ���� fn �� Callback functions �łȂ���΂Ȃ�Ȃ��炵��

  // �������牺�̓I�u�W�F�N�g�̔j���Ȃǂ����镔��
  dJointGroupDestroy( contactgroup ); // �W���C���g�O���[�v�̔j��
  dSpaceDestroy( space );         // �X�y�[�X�̔j��
  dWorldDestroy( world );         // ���[���h�̔j��
  return 0;
}


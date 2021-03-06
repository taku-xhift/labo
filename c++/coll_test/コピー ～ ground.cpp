/***********************************************************
 * Hajime no Ippo --- file : hjime.cpp
 ***********************************************************/
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

#define MAX_CONTACTS 4 // $B:GBg$N>WFM8!=P2DG=?t(B
static dWorldID world; // ワールドの設定
static dSpaceID space; // スペースＩＤの設定
static dJointGroupID contactgroup;
		// 衝突グループの設定。下でこれに引っかかった場合は衝突しない設定になっている

static dBodyID box;    // ボックスの宣言
static dGeomID geom;   // 
dReal  box_sizes[3] = { 2.0, 1.0, 3.0 };
                       // ここでボックスのサイズを決定してしまっている

#ifdef dDOUBLE
  #define dsDrawBox dsDrawBoxD
#endif

// コールバック関数の設定
static void nearCallback( void *data, dGeomID o1, dGeomID o2 )
{
  dBodyID b1 = dGeomGetBody( o1 ); // 引数 o1 の形状取得
  dBodyID b2 = dGeomGetBody( o2 ); // 引数 o2 の形状取得

  if ( b1 && b2 && dAreConnectedExcluding( b1, b2, dJointTypeContact ) )
    return; // 衝突判定を行わないグループ動詞だった場合はここで終了(たぶん)

  dContact contact[MAX_CONTACTS];
  for ( int i=0; i<MAX_CONTACTS; i++ )
  {
    // 衝突に必要な条件の設定
    contact[i].surface.mode = dContactBounce | dContactSoftCFM;	// 地面の反発係数を設定しているらしい
    contact[i].surface.mu = dInfinity;   // 不明。でも必ず定義されていなければならないらしい。
    contact[i].surface.bounce = 0.1;     // 反発係数の設定(0〜1.0)
    contact[i].surface.soft_cfm = 0.5;  // 衝突したときのオブジェクトの変形度合い
  }

  // 実際の検証部分？
  int numc = dCollide( o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof( dContact ) ); 
  if ( numc > 0 )
  {
    for ( int i=0; i<numc; i++ )
    {
      // コンタクトジョイント生成
      dJointID c = dJointCreateContact( world, contactgroup, contact+i );
                                 // 接触している２つのgeometryをコンタクトジョイントで拘束
      dJointAttach( c, b1, b2 ); // くっつけたものをまた離す作業
    }
  }
}

// start simulation - set viewpoint
static void start()
{
  static float xyz[3] = { 0.f, 5.f, 3.f };
  static float hpr[3] = { -90.f, -15.f, 0.f };

  dsSetViewpoint( xyz, hpr ); // 上でセットされたパラを見に行く
}

// simulation loop … ループ部分
static void simLoop( int pause )
{
  dSpaceCollide( space, 0, &nearCallback ); // 衝突判定に必要。これを必ず最初に書かなくてはいけないらしい

  // Ctl+p ポーズの設定かな？
  if (!pause)
  {
    dWorldStep( world, 0.01 ); // ポーズでなかったらこの分だけステップが進む
  }

  dJointGroupEmpty( contactgroup ); // ジョイントグループを空にする

  // オブジェクトの描画
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
  world = dWorldCreate();         // スペース(衝突世界)の生成
  space = dHashSpaceCreate( 0 );  // 衝突検出スペースの生成
  contactgroup = dJointGroupCreate( 0 );     // コンタクトグループ(接触点が格納される)の生成
  dCreatePlane( space, 0, 0, 1, 0 );         // 地面として2D板を生成
  dWorldSetGravity( world, 0.0, 0.0, -9.8 ); // 重力加速度の設定

  // create box
  box = dBodyCreate( world );     // ボックスをワールドに生成
  dReal pos[3] = { 0.0, 0.0, 6.0 };
  dBodySetPosition( box, pos[0], pos[1], pos[2] );
                                  // ボックスのポジションを設定
  geom = dCreateBox( space, box_sizes[0], box_sizes[1], box_sizes[2] );
                                  // ボックスの大きさを設定している？
  dGeomSetBody( geom, box );      // そして実際に上で決めた大きさのボックスを生成している

  // starting simulation
  dsSimulationLoop( argc, argv, 320, 240, &fn );
				// ここがシュミレーション開始部分。ここから衝突判定の全てが始まる
				// この fn は Callback functions でなければならないらしい

  // こっから下はオブジェクトの破棄などをする部分
  dJointGroupDestroy( contactgroup ); // ジョイントグループの破棄
  dSpaceDestroy( space );         // スペースの破棄
  dWorldDestroy( world );         // ワールドの破棄
  return 0;
}


/***********************************************************
 * Hajime no Ippo --- file : hjime.cpp
 ***********************************************************/
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

#define MAX_CONTACTS 4 // $B:GBg$N>WFM8!=P2DG=?t(B
static dWorldID world; // ƒ[ƒ‹ƒh‚Ìİ’è
static dSpaceID space; // ƒXƒy[ƒX‚h‚c‚Ìİ’è
static dJointGroupID contactgroup;
		// Õ“ËƒOƒ‹[ƒv‚Ìİ’èB‰º‚Å‚±‚ê‚Éˆø‚Á‚©‚©‚Á‚½ê‡‚ÍÕ“Ë‚µ‚È‚¢İ’è‚É‚È‚Á‚Ä‚¢‚é

static dBodyID box;    // ƒ{ƒbƒNƒX‚ÌéŒ¾
static dGeomID geom;   // 
dReal  box_sizes[3] = { 2.0, 1.0, 3.0 };
                       // ‚±‚±‚Åƒ{ƒbƒNƒX‚ÌƒTƒCƒY‚ğŒˆ’è‚µ‚Ä‚µ‚Ü‚Á‚Ä‚¢‚é

#ifdef dDOUBLE
  #define dsDrawBox dsDrawBoxD
#endif

// ƒR[ƒ‹ƒoƒbƒNŠÖ”‚Ìİ’è
static void nearCallback( void *data, dGeomID o1, dGeomID o2 )
{
  dBodyID b1 = dGeomGetBody( o1 ); // ˆø” o1 ‚ÌŒ`óæ“¾
  dBodyID b2 = dGeomGetBody( o2 ); // ˆø” o2 ‚ÌŒ`óæ“¾

  if ( b1 && b2 && dAreConnectedExcluding( b1, b2, dJointTypeContact ) )
    return; // Õ“Ë”»’è‚ğs‚í‚È‚¢ƒOƒ‹[ƒv“®Œ‚¾‚Á‚½ê‡‚Í‚±‚±‚ÅI—¹(‚½‚Ô‚ñ)

  dContact contact[MAX_CONTACTS];
  for ( int i=0; i<MAX_CONTACTS; i++ )
  {
    // Õ“Ë‚É•K—v‚ÈğŒ‚Ìİ’è
    contact[i].surface.mode = dContactBounce | dContactSoftCFM;	// ’n–Ê‚Ì”½”­ŒW”‚ğİ’è‚µ‚Ä‚¢‚é‚ç‚µ‚¢
    contact[i].surface.mu = dInfinity;   // •s–¾B‚Å‚à•K‚¸’è‹`‚³‚ê‚Ä‚¢‚È‚¯‚ê‚Î‚È‚ç‚È‚¢‚ç‚µ‚¢B
    contact[i].surface.bounce = 0.1;     // ”½”­ŒW”‚Ìİ’è(0`1.0)
    contact[i].surface.soft_cfm = 0.5;  // Õ“Ë‚µ‚½‚Æ‚«‚ÌƒIƒuƒWƒFƒNƒg‚Ì•ÏŒ`“x‡‚¢
  }

  // ÀÛ‚ÌŒŸØ•”•ªH
  int numc = dCollide( o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof( dContact ) ); 
  if ( numc > 0 )
  {
    for ( int i=0; i<numc; i++ )
    {
      // ƒRƒ“ƒ^ƒNƒgƒWƒ‡ƒCƒ“ƒg¶¬
      dJointID c = dJointCreateContact( world, contactgroup, contact+i );
                                 // ÚG‚µ‚Ä‚¢‚é‚Q‚Â‚Ìgeometry‚ğƒRƒ“ƒ^ƒNƒgƒWƒ‡ƒCƒ“ƒg‚ÅS‘©
      dJointAttach( c, b1, b2 ); // ‚­‚Á‚Â‚¯‚½‚à‚Ì‚ğ‚Ü‚½—£‚·ì‹Æ
    }
  }
}

// start simulation - set viewpoint
static void start()
{
  static float xyz[3] = { 0.f, 5.f, 3.f };
  static float hpr[3] = { -90.f, -15.f, 0.f };

  dsSetViewpoint( xyz, hpr ); // ã‚ÅƒZƒbƒg‚³‚ê‚½ƒpƒ‰‚ğŒ©‚És‚­
}

// simulation loop c ƒ‹[ƒv•”•ª
static void simLoop( int pause )
{
  dSpaceCollide( space, 0, &nearCallback ); // Õ“Ë”»’è‚É•K—vB‚±‚ê‚ğ•K‚¸Å‰‚É‘‚©‚È‚­‚Ä‚Í‚¢‚¯‚È‚¢‚ç‚µ‚¢

  // Ctl+p ƒ|[ƒY‚Ìİ’è‚©‚ÈH
  if (!pause)
  {
    dWorldStep( world, 0.01 ); // ƒ|[ƒY‚Å‚È‚©‚Á‚½‚ç‚±‚Ì•ª‚¾‚¯ƒXƒeƒbƒv‚ªi‚Ş
  }

  dJointGroupEmpty( contactgroup ); // ƒWƒ‡ƒCƒ“ƒgƒOƒ‹[ƒv‚ğ‹ó‚É‚·‚é

  // ƒIƒuƒWƒFƒNƒg‚Ì•`‰æ
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
  world = dWorldCreate();         // ƒXƒy[ƒX(Õ“Ë¢ŠE)‚Ì¶¬
  space = dHashSpaceCreate( 0 );  // Õ“ËŒŸoƒXƒy[ƒX‚Ì¶¬
  contactgroup = dJointGroupCreate( 0 );     // ƒRƒ“ƒ^ƒNƒgƒOƒ‹[ƒv(ÚG“_‚ªŠi”[‚³‚ê‚é)‚Ì¶¬
  dCreatePlane( space, 0, 0, 1, 0 );         // ’n–Ê‚Æ‚µ‚Ä2D”Â‚ğ¶¬
  dWorldSetGravity( world, 0.0, 0.0, -9.8 ); // d—Í‰Á‘¬“x‚Ìİ’è

  // create box
  box = dBodyCreate( world );     // ƒ{ƒbƒNƒX‚ğƒ[ƒ‹ƒh‚É¶¬
  dReal pos[3] = { 0.0, 0.0, 6.0 };
  dBodySetPosition( box, pos[0], pos[1], pos[2] );
                                  // ƒ{ƒbƒNƒX‚Ìƒ|ƒWƒVƒ‡ƒ“‚ğİ’è
  geom = dCreateBox( space, box_sizes[0], box_sizes[1], box_sizes[2] );
                                  // ƒ{ƒbƒNƒX‚Ì‘å‚«‚³‚ğİ’è‚µ‚Ä‚¢‚éH
  dGeomSetBody( geom, box );      // ‚»‚µ‚ÄÀÛ‚Éã‚ÅŒˆ‚ß‚½‘å‚«‚³‚Ìƒ{ƒbƒNƒX‚ğ¶¬‚µ‚Ä‚¢‚é

  // starting simulation
  dsSimulationLoop( argc, argv, 320, 240, &fn );
				// ‚±‚±‚ªƒVƒ…ƒ~ƒŒ[ƒVƒ‡ƒ“ŠJn•”•ªB‚±‚±‚©‚çÕ“Ë”»’è‚Ì‘S‚Ä‚ªn‚Ü‚é
				// ‚±‚Ì fn ‚Í Callback functions ‚Å‚È‚¯‚ê‚Î‚È‚ç‚È‚¢‚ç‚µ‚¢

  // ‚±‚Á‚©‚ç‰º‚ÍƒIƒuƒWƒFƒNƒg‚Ì”jŠü‚È‚Ç‚ğ‚·‚é•”•ª
  dJointGroupDestroy( contactgroup ); // ƒWƒ‡ƒCƒ“ƒgƒOƒ‹[ƒv‚Ì”jŠü
  dSpaceDestroy( space );         // ƒXƒy[ƒX‚Ì”jŠü
  dWorldDestroy( world );         // ƒ[ƒ‹ƒh‚Ì”jŠü
  return 0;
}



#ifndef WEODLLMODEFIED_HPP_INCLUDED
#define WEODLLMODEFIED_HPP_INCLUDED

//#define WE_USE_EXPORTS_OF_PUBLIC_DLLS (1)	// move to pm/we_wii/MODULE/COMPILE_OPTION

#if WE_USE_EXPORTS_OF_PUBLIC_DLLS

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------

#ifdef WE_IS_MODE_DLL_COMPILING
#define WE_MODE_DLL_EXPORT __declspec(dllexport)
#else
#define WE_MODE_DLL_EXPORT __declspec(dllimport)
#endif


#ifdef WE_IS_EXE_COMPILING
#define WE_EXE_EXPORT __declspec(dllexport)
#else
#define WE_EXE_EXPORT __declspec(dllimport)
#endif



#else//WE_USE_EXPORTS_OF_PUBLIC_DLLS

#define WE_MODE_DLL_EXPORT
#define WE_EXE_EXPORT

#endif//WE_USE_EXPORTS_OF_PUBLIC_DLLS

#endif//WEODLLMODEFIED_HPP_INCLUDED


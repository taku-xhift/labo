//======================================================================
/** @file
	@brief		Type
	@author		Kazuki Araki <araki_kazuki@cobra.konami>
*/
//======================================================================
#ifndef	_WECOMMONTYPE_H_
#define	_WECOMMONTYPE_H_
typedef signed char		int8_t;
typedef short			int16_t;
typedef int				int32_t;
typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;

typedef __int64			int64_t;
typedef unsigned __int64 uint64_t;
typedef int				weBool;
typedef int				weEnum;
typedef char			weChar;
typedef signed char		weSchar;
typedef unsigned char	weUchar;
typedef int				weInt;
typedef unsigned int	weUint;
typedef short			weShort;
typedef unsigned short	weUshort;
typedef float			weFloat;
typedef double			weDouble;
typedef int64_t			weLong;
typedef uint64_t		weUlong;
typedef const char *	weString;
//----------------------------------------------------------------------
/// MAX/MIN(型使用部もあるのでここに)
//----------------------------------------------------------------------
#define INT8_MIN		(-128)
#define INT16_MIN		(-32767-1)
#define INT32_MIN		(-2147483647-1)
#define INT64_MIN		(-9223372036854775807L-1)
#define INT8_MAX		(127)
#define INT16_MAX		(32767)
#define INT32_MAX		(2147483647)
#define INT64_MAX		(9223372036854775807L)
#define UINT8_MAX		(255U)
#define UINT16_MAX		(65535U)
#define UINT32_MAX		(4294967295U)
#define UINT64_MAX		(18446744073709551615UL)

#define	WE_INT_MAXVAL		0x7FFFFFFF
#define	WE_INT_MINVAL		0x80000000
#define	WE_U_INT_MAXVAL		0xFFFFFFFF
#define	WE_U_INT_MINVAL		0x00000000
#define	WE_FLOAT_MAXVAL		(weFloat)(3.40282347e+38)
#define	WE_FLOAT_MINVAL		(weFloat)(1.17549435e-38)
#define	WE_SHORT_MAXVAL		0x7fff
#define	WE_SHORT_MINVAL		0x8000
#define	WE_U_SHORT_MAXVAL	0xffff
#define	WE_U_SHORT_MINVAL	0x0000
//----------------------------------------------------------------------
// 各種構造体
//----------------------------------------------------------------------

//======================================================================
// EOF
//======================================================================
#endif	// _WECOMMONTYPE_H_

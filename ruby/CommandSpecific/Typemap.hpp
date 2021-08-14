

#ifndef TYPEMAP_HPP
#define TYPEMAP_HPP


typedef int weInt;
typedef float weFloat;
typedef char weChar;
typedef const char *	weString;
typedef int Boolean;

typedef enum {
	USELIST_USE,
	USELIST_UNUSE,
} UseList;



#ifndef TRUE            /* TRUE が定義されていなかったら */
	#define TRUE 1
#endif

#ifndef FALSE           /* FALSE が定義されていなかったら */
	#define FALSE 0
#endif


void userAssert(int boolean, const char* strings_);

#endif // TYPEMAP_HPP

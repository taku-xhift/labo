



#include <iostream>

template<bool> struct CompileTimeChecker
{
	CompileTimeChecker(...);
};
template<> struct CompileTimeChecker<false> {};

#define STATIC_CHECK(expr, msg)\
    {\
		class ERROR_##msg {}; \
		(void)sizeof(CompileTimeChecker<(expr) != 0>((ERROR_##msg())));\
	}

template <typename To, typename From>
To safe_reinterpret_cast(From from)
{
	STATIC_CHECK(sizeof(From) <= sizeof(To),
				 Destination_Type_Too_Narrow);
	return reinterpret_cast<To>(from);
}


int main()
{
	float floating = 2.0f;
	void* somePointer = &floating;

	//char c = safe_reinterpret_cast<char>(somePointer);
	//int c = safe_reinterpret_cast<int>(somePointer);

	//std::cerr << c << std::endl;

	std::cerr << (sizeof(void*) <= sizeof(char)) << std::endl;

	return 0;
}



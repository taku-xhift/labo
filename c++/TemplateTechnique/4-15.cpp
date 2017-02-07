


#include <iostream>
#include <typeinfo>

//
//
//template<bool Cond, typename Then, typename Else>
//struct if_;
//
//template <typename Then, typename Else>
//struct if_<true, Then, Else>
//{
//	typedef Then type;
//};
//
//template<typename Then, typename Else>
//struct if_<false, Then, Else>
//{
//	typedef Else type;
//};

template<int N>
struct is_even
{
	static const bool value = N % 2 == 0;
};




template<bool Cond, typename Then, typename Else>
struct if_c;

template<typename Then, typename Else>
struct if_c<true, Then, Else>
{
	typedef Then type;
};

template<typename Then, typename Else>
struct if_c<false, Then, Else>
{
	typedef Else type;
};


template<typename Cond, typename Then, typename Else>
struct if_ : public if_c<Cond::value, Then, Else>
{
};




int main()
{
	//if_<sizeof(int), float, int>::type value;

	//std::cout << typeid(value).name() << std::endl;


	if_<is_even<3>, int, long>::type value;

	std::cout << typeid(value).name() << std::endl;

	return 0;
};



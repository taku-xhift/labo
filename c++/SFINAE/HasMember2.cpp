
#include <iostream>
#include <ostream>

struct no { };
struct yes { no no_[2]; };

// check for unambigous public member foo of any type
template <typename T>
struct has_foo{
	template <int>
	struct yes_holder { typedef yes type; };

	template<typename>
	static no test(...);

	template <typename U>
	static typename yes_holder<sizeof(&U::foo)>::type test(U*);

	static const bool value = sizeof(yes) == sizeof(test<T>((T*)NULL) );
};

// check for an unambigous public member foo of specified type
template <typename fooType, typename T>
struct has_typed_foo
{
	template <fooType>
	struct yes_holder {
		typedef yes type;
	};

	template<typename>
	static no test(...);

	template <typename U>
	static typename yes_holder<&U::foo>::type test(U*);

	static const bool value= sizeof(yes)==sizeof(test<T>((T*)0));
};

// usage examples -- classes
struct A { };
struct B { int foo; };
struct C : B { };
struct D {
	void foo() { }
	static void foo(int) { }
};

int main(){
	// usage examples -- check for member foo of any type
	std::cout << has_foo<D>::value << std::endl; //false
	//std::cout << has_foo<B> << std::endl; // true
	//std::cout << has_foo<C> << std::endl; // true
	// std::cout << has_foo< std::endl; // ambiguous

	// usage examples -- check for member foo with specified type
	//std::cout << has_typed_foo<A> << std::endl; // false
	//std::cout << has_typed_foo<B> << std::endl; // true
	//std::cout << has_typed_foo<C> << std::endl; // true
	//std::cout << has_typed_foo<D> << std::endl; // false
	//std::cout << has_typed_foo<A> << std::endl; // true
	//std::cout << has_typed_foo<B> << std::endl; // true
}


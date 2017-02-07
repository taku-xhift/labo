



#include <iostream>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <boost/static_assert.hpp>


struct Deleter {
	template<typename Type>
	void operator()(const Type& value) throw() {
		BOOST_STATIC_ASSERT(std::tr1::is_pointer<Type>::value);
		delete value;
	}
};

struct Finder {
	template<typename Type>
	bool operator()(const Type& value) throw() {
		return *value == 3;
	}
};


struct Test {
	Test(int integer) : integer_(integer) {}
	int integer_;
};



int main() {
	std::vector<Test*> container;
	for (int i = 0; i < 10; ++i) {
		container.push_back(new Test(i));
	}

	{
		std::vector<Test*>::iterator ite = std::find_if(container.begin(), container.end(), Finder());
		while (ite != container.end()) {
			delete *ite;
			*ite = NULL;
			ite = std::find_if(ite, container.end(), Finder());
		}
	}

	for (std::vector<Test*>::const_iterator ite = container.begin(); ite != container.end(); ++ite) {
		if (*ite != NULL) {
			std::cout << (*ite)->integer_ << std::endl;
		}
	}
	std::for_each(container.begin(), container.end(), Deleter());
}



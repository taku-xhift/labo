


#include <iostream>
#include <map>
#include <string>
#include <algorithm>

class Print {
public:
	template<typename ValueType>
	void operator()(const ValueType& value) throw() {
		std::cout << value.second << std::endl;
	}
};

int main() {
	typedef std::multimap<std::string, int> ContainerType;
	typedef std::multimap<std::string, int>::iterator ContainerTypeIte;

	ContainerType container;
	container.insert(std::pair<std::string, int>(std::string("データ"), 10));
	container.insert(std::pair<std::string, int>(std::string("データ"), 40));

	std::pair<ContainerTypeIte, ContainerTypeIte> itePair = container.equal_range("データ");

	//std::cout << container[std::string("データ")] << std::endl;
	std::for_each(itePair.first, itePair.second, Print());
	std::cerr << "size = " << container.size() << std::endl;
}





#include <iostream>
#include <map>


void print(std::map<int, int, std::less<int> > data) {
	for (std::map<int, int>::iterator ite = data.begin(); ite != data.end(); ++ite) {
		std::cout << "first = " << ite->first << ", second = " << ite->second << std::endl;
	}
}


int main() {

	std::map<int, int, std::less<int> > data;

	data.insert(std::pair<int, int> (3, 2));
	data.insert(std::pair<int, int> (0, 4));
	data.insert(std::pair<int, int> (2, 9));

	print(data);

	return 0;
}


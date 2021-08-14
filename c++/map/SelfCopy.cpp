
// Œ‹‰ÊA‚¾‚ß‚¾‚Á‚½
// index ‚ª“¯‚¶‚à‚Ì‚ğó‚¯•t‚¯‚È‚¢‚Ì‚Å“–‚½‚è‘O

#include <iostream>
#include <map>


int main() {
	std::map<int, int> mapContainer;

	for (int i = 0; i < 10; ++i) {
		mapContainer.insert(std::make_pair(i, i+1));
	}

	mapContainer.insert(mapContainer.begin(), mapContainer.end());

	for (std::map<int, int>::const_iterator ite = mapContainer.begin(); ite != mapContainer.end(); ++ite) {
		std::cout << "first = " << ite->first << std::endl;
		std::cout << "second = " << ite->first << std::endl;
	}
}



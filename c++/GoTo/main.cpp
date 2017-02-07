


#include <iostream>


int main() {
TOP:
	bool boolean;// = false;
	while (true) {
		while (boolean == false) {
			boolean = true;
			goto TOP;
		}
	}

	std::cout << "break" << std::endl;
}



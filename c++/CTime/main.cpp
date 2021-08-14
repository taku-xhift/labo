


#include <ctime>
#include <iostream>




int main() {

	//tm time = {0};
	//time.tm_sec = 400;
	//std::cout << asctime(&time) << std::endl;


//	time_t temp = 400;
//	tm time = *localtime(&temp);
//
//	std::cout << asctime(&time) << std::endl;


	time_t now = time(NULL);
	std::cout << ctime(&now) << std::endl;
	tm temp = *localtime(&now);
	std::cout << temp.tm_mon << std::endl;
}


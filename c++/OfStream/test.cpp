


#include <iostream>
#include <fstream>



int main() {
	std::ofstream ofs("test.txt");
	ofs << "sample" << std::endl;
	ofs.close();
}


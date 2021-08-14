#include <map>
#include <iostream>
#include <string>
#include <vector>

std::vector<float> floating;




typedef std::pair<std::string, float>    Bone;



int main()
{
	std::map<std::string, float> mapTest;
	Bone bone = std::make_pair<std::string, float>("name", 3.0f);
	mapTest.insert(bone);


	std::cout << mapTest["name"] << std::endl;

	floating.resize(4);

	std::cout << floating.size() << std::endl;

	return 0;
}


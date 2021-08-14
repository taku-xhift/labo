
#include <Personal/Split.hpp>

//std::vector<std::string> split(const std::string& strings_, char sepalator_ = ',') throw() {
//	std::string sorce = strings_;
//	std::vector<std::string> container;
//	std::string temp;
//
//	std::string::size_type result = sorce.rfind(sepalator_);
//	while (result != std::string::npos) {
//		container.push_back(sorce.substr(result+1));
//		sorce.resize(result);
//		result = sorce.rfind(sepalator_);
//	}
//	container.push_back(sorce);
//
//	return container;
//}

int main() {
	using namespace std;

	string sample = "sample";

	vector<string> container = split(sample);

	for (vector<string>::iterator ite = container.begin(); ite != container.end(); ++ite) {
		cout << *ite << endl;
	}

	return 0;
}


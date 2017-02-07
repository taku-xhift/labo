


#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>


int counter = 0;


void OutputState(std::vector<int>& from, std::vector<int>& work, std::vector<int>& to) {
	std::cout << "Step : " << counter << "\n";

	const int lengthMax = std::max(from.size(), std::max(work.size(), to.size()));

	std::vector<std::string> buffer(lengthMax);
	std::stringstream ss;

	for (int i = lengthMax; i > 0; --i) {
		if (from.size() > i) {
			ss << from.at(i) << " ";
		} else {
			ss << "  ";
		}
		if (work.size() > i) {
			ss << work.at(i) << " ";
		} else {
			ss << "  ";
		}
		if (to.size() > i) {
			ss << to.at(i) << " ";
		} else {
			ss << "  ";
		}
		ss << "\n";

		buffer.insert(buffer.begin(), ss.str());

		ss.str("");
		ss.clear(); // Clear state flags.
	}

	for (auto& str : buffer) {
		std::cout << str;
	}

	std::cout << "\n";
}



void MoveTo(int x, std::vector<int>& from, std::vector<int>& work, std::vector<int>& to) {
	OutputState(from, work, to);

	if (x == 1) {
		to.insert(to.begin(), from.front());
		from.erase(from.begin());
	} else {
		--x;
		MoveTo(x, from, to, work);
		++counter;
		MoveTo(x, work, from, to);
	}
}


int main(int argc, const char* argv[]) {
	//const int num = atoi(argv[1]);
	const int num = 4;

	std::vector<int> from(num);
	std::vector<int> to;
	std::vector<int> work;


	for (int i = 0; i < num; ++i) {
		from.at(i) = i;
	}

	MoveTo(num, from, work, to);

	std::cout << "count => " << counter << std::endl;
}



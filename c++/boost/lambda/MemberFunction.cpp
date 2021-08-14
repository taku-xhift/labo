


#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <iostream>
#include <algorithm>
#include <vector>



class RoomInfo {
public:
	//void integer(int value) throw() { this->integer_ = value; }
	int integer() const throw() { return this->integer_; }

	int integer_;
};



int main() {
	using namespace boost::lambda;

	RoomInfo roomInfo;
	std::vector<RoomInfo> container;
	container.push_back(roomInfo);
	container.push_back(roomInfo);

	//std::vector<RoomInfo>::iterator ite
	//	= std::find_if(container.begin(), container.end(), bind(&RoomInfo::roomID, _1) == roomInfo.roomID());

//	if (ite != container.end()) {
//		std::cout << ite->roomID() << std::endl;
//	}

	for (int i = 0; i < container.size(); ++i) {
		container[i].integer_ = i;
	}

	std::vector<RoomInfo>::iterator ite
		= std::find_if(container.begin(), container.end(), bind(&RoomInfo::integer, _1) == 1);

	std::cout << ite->integer_ << std::endl;

	//std::for_each(container.begin(), container.end(), std::cout << _1 << "\n");
}






#include <boost/bind.hpp>
#include <iostream>
#include <algorithm>
#include <vector>



class RoomInfo {
public:
	int roomID() const throw() { return 24; }
};


struct Equality {
	typedef bool result_type;
	bool operator()(const RoomInfo& lhs, const RoomInfo& rhs) throw() {
		return lhs.roomID() == rhs.roomID();
	}
};


int main() {

	RoomInfo roomInfo;
	std::vector<RoomInfo> container;
	container.push_back(roomInfo);
	container.push_back(roomInfo);

	std::vector<RoomInfo>::iterator ite = std::find_if(container.begin(), container.end(), boost::bind(Equality(), _1, roomInfo));

	if (ite != container.end()) {
		std::cout << ite->roomID() << std::endl;
	}
}



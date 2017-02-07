


#include <iostream>


enum Flow_Enum {
	Flow_Start,
	Flow_Next,
	Flow_Max,
};

template<unsigned int N>
class Flow;


template<>
class Flow<Flow_Start> {
public:
	static const Flow_Enum next = Flow_Start;

	Flow(int integer) {
		std::cerr << integer << std::endl;
	}
};


template<>
class Flow<Flow_Next> {
public:
	static const Flow_Enum next = Flow_Next;
};

void call(int num_) {
	switch (num_) {
	case 0: {
		Flow<0> startFlow(20);
		break;
	}
	default: {
		break;
	}
	}
}

int main() {
	using namespace std;

	//cerr << "Flow<Flow_Start>::next = " << Flow<Flow_Start>::next << endl;
	//cerr << "Flow<Flow_Next>::next = " << Flow<Flow_Next>::next << endl;
	int num = 0;
	Flow<Flow_Start> startFlow(2);
	Flow<Flow_Next> nextFlow;
	Flow<0> other(3);

	call(num);
}


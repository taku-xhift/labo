#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;



struct Float
{
	float f;
	string name;

	Float() : f(1.0f), name("Unnamed") {}
};

typedef ::std::map<int, Float> KeyState;



class Data
{
public:
	KeyState keyState;

	Float getKeyState(int action) const throw()
	{
		KeyState::const_iterator kmIterator = keyState.begin();
		while (kmIterator != keyState.end()) {
			if ((*kmIterator).first == action) {
				//return this->keyState[action];
				return (*kmIterator).second;
			}
			++kmIterator;
		}
	}


	Data()
	{
	}

};


class Input
{
public:
	boost::shared_ptr<Data> data;

	Float getFloat(int action) const throw()
	{
		return data->getKeyState(action);
	}

	Input()
	{
		boost::shared_ptr<Data> data_(new Data());
		this->data = data_;
	}

	~Input()
	{
	}

};



int main()
{



	Input input;


	std::cout << input.getFloat(0).name << endl;


	return 0;
}


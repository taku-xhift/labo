#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>



typedef ::std::map<int, float> FloatConverter;

class Data
{
public:
	FloatConverter floatConverter;
	//std::vector<float> fContainer;

	float getFloat(int action) const throw()
	{
		FloatConverter::iterator kmIterator = floatConverter.begin();
		while (kmIterator != floatConverter.end()) {
			if ((*kmIterator).first == action) {
				//return this->keyState[action];
				return (*kmIterator).second;
			}
		++kmIterator;
		}
	}


	Data()
	{
		this->floatConverter.insert(::std::map<int, float>::value_type(0, .0f));
	}

};


class Input
{
public:
	boost::shared_ptr<Data> data;




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
	//input.getData()->addName("named");


	//std::cout << input.getData()->getName(0) << std::endl;


	return 0;
}


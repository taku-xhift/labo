


#include <iostream>
#include <typeinfo>
#include <string>



class Test
{
public:

	template<typename T>
	Test(const std::string &name_, T &data_)
		: name(name_)
		, data(&data_)
		, typeInfo(typeid(T &))
	{
	}

	~Test()
	{
	}


	template<typename T>
	T *getData() const
	{
		if (typeid(T) == this->typeInfo) {
			return static_cast<T *>(this->data);
		} else {
			return NULL;
		}
	}


	const std::string &getName() const
	{
		return this->name;
	}


	const type_info &getTypeInfo()
	{
		return this->typeInfo;
	}


private:

	std::string name;
	void *data;
	const type_info &typeInfo;

};


class Sample
{
public:

	float floating;

	Sample(float floating_ = .0f)
		: floating(floating_)
	{
	}

};



int main()
{
	std::string name = "name";
	float floating = 3.0f;
	Sample sample;
	sample.floating = 34.2f;


	//Test test(name, floating);
	Test test(name, sample);


	std::cout << test.getData<float>() << std::endl;

	return 0;
}



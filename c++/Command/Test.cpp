

#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>


template<typename T>
class BindData
{

	std::string name;
	T           parameter;

public:

	BindData(std::string name_ = "", T parameter_)
		: name(name_)
		, parameter(parameter_)
	{
	}

};


class Test
{
public:

	const type_info &typeName;
	std::string typeNameString;
	std::string name;

	union
	{
		std::string *string;
		int *integer;
		float *floating;
	};


public:

	template<typename T>
	void setParameter(const std::string &string_, T &parameter) throw()
	{
		this->removeParameter();
		if (this->typeNameString == typeid(std::string &).name()) {
			*(this->string) = parameter;
			std::cout << "setParameter(string)" << std::endl;
		} else if (this->typeNameString == typeid(int &).name()) {
			this->integer = new int;
			*(this->integer) = parameter;
			std::cout << "setParameter(int)" << std::endl;
		} else if (this->typeNameString == typeid(float &).name()) {
			this->floating = new float;
			*(this->floating) = parameter;
			std::cout << "setParameter(float)" << std::endl;
		} else {
			std::cout << "Invalid class!!!" << std::endl;
		}
#if 0
		if (typeid(T) == typeid(std::string &)) {
			*(this->string) = parameter;
			std::cout << "setParameter(string)" << std::endl;
		} else if (typeid(T) == typeid(int &)) {
			this->integer = new int;
			*(this->integer) = parameter;
			std::cout << "setParameter(int)" << std::endl;
		} else if (typeid(T) == typeid(float &)) {
			this->floating = new float;
			*(this->floating) = parameter;
			std::cout << "setParameter(float)" << std::endl;
		} else {
			std::cout << "Invalid class!!!" << std::endl;
		}
#endif
	}

	void removeParameter() throw()
	{
		if (this->typeNameString == typeid(std::string &).name()) {
		} else if (this->typeNameString == typeid(int &).name()) {
			delete this->integer;
		} else if (this->typeNameString == typeid(float &).name()) {
			delete this->floating;
		} else {
		}
#if 0
		if (this->typeName == typeid(std::string &)) {
		} else if (this->typeName == typeid(int &)) {
			delete this->integer;
		} else if (this->typeName == typeid(float &)) {
			delete this->floating;
		} else {
		}
#endif
#if 0
		if (this->string != NULL) {
			delete this->string;
		} else if (this->integer != NULL) {
			delete this->integer;
		} else if (this->floating != NULL) {
			delete this->floating;
		}
#endif
	}

	template<typename T>
	Test(const std::string &string_, T &parameter_)
		: name("")
		, typeName(typeid(T))
	{
		this->typeNameString = typeid(T).name();
		this->setParameter(string_, parameter_);
	}

	~Test()
	{
		//if (this->typeName == typeid(std::string &)) {
		//	delete this->string;
		//} else if (this->typeName == typeid(int &)) {
		//	delete this->integer;
		//} else if (this->typeName == typeid(float &)) {
		//	delete this->floating;
		//}

		this->removeParameter();
	}

};


template<typename Type>
class Sample
{
public:

	std::string name;
	Type parameter;

	Sample(std::string name_, Type parameter_)
		: name(name_)
		, parameter(parameter_)
	{
	}
};


//void out(std::vector<BindData> data)
//{
//	for (std::vector<BindData>::iterator ite = data.begin(); ite != data.end(); ++ite) {
//		std::cout << "This pair is A: " << ite->name << ", B: " << ite->parameter << std::endl;
//	}
//}




void main()
{
	//std::vector<BindData> data;

	//for (int i = 0; i < 10; ++i) {
	//	BindData bindData;
	//	data.push_back(bindData);
	//}

	//out(data);
		std::string name = "Test";
		std::string string = "string";
		int integer = 3;
		float floating = 3.0f;
	// テストクラスについての実験
	Test test(name, string);
	//Test test(name, floating);

	//std::cout << typeid(string).name() << std::endl;


	//std::string name = "Test";
	//std::string string = "string";
	//int integer = 3;
	//float floating = 3.0f;

	//Sample<float> sample(name, floating);

	//std::cout << sample.parameter << std::endl;
}





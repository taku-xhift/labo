


#include "String.hpp"


namespace String
{
	StringValue::init(const char *initValue)
	{
		this->data = new char[strlen(initValue) + 1];
		strcpy(data, initValue);
	}

	StringValue::StringValue(const char *initValue)
	{
		this->init(initValue);
	}

	StringValue::StringValue(const StringValue& rhs)
	{
		this->init(rhs.data);
	}

	StringValue::~StringValue()
	{
		delete [] dasta;
	}
}    // namespace String



String::String(const char *value = "")
	: value(new StringValue(value))
{
}


char String::operator [](int index) const
{
	return this->value->data[index];
}


char& String::operator [](int index)
{
	if (this->value->isShared()) {
		this->value = new StringValue(this->value->data);
	}

	this->value->markUnshareable();

	return this->value->data[index];
}





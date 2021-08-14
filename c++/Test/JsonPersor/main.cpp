


#include "JsonParser.hpp"


struct Test {
	int integer_;
	float floating_;

	json::Value save() throw() {
		json::Value value("Test");
		value.node_.insert(json::Value());
	}
};


int main()
{
	
}



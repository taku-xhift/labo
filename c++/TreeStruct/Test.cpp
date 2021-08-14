


#include <iostream>

class Test {
public:
	static setState(Test& test_, int state_) { test_->state = state_; }

	Test* makeChild() {
		Test* temp = new Test();
		this->link = temp;
		return temp;
	}

	void ChangeFromChild() {
		
	}

private:
	int state;
	const Test* link;
};


int main() {


	
}


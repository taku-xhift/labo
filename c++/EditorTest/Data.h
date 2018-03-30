

#include <iostream>

namespace lib {

class Data
{
public:

	/**
	 * setter
	 * param value int
	 */
	void SetInteger(int value);
	int GetInteger() const;

	void Printer() const {
		std::cerr << __FUNCTION__ << std::endl;
	}

private:
	int integer_;
};

}


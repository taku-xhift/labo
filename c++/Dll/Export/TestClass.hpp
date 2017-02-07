/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2012.01.06 23:20:28
 *
 * @version 0.01, Shishido Takuya, 2012.01.06 23:20:28
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef MODE_TESTCLASS_HPP_INCLUDED
#define MODE_TESTCLASS_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
//#include <type_info>


namespace mode {


class __declspec(dllexport) TestClass
{
public:

	//! \brief constructor
	TestClass() throw();


	//! \brief destructor
	~TestClass() throw();

	int getInteger() const { return this->integer_; }
	void setInteger(int integer) { this->integer_ = integer; }

	template<typename T>
	void print() const throw() {
		std::cout << typeid(T).name() << std::endl;
	}

private:

	int integer_;

};    // class TestClass

}    // namespace mode


#endif


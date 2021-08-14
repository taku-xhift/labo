
#ifndef SPECIALIZE_HPP_INCLUDED
#define SPECIALIZE_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------


enum SomeDefine {
	HogeHuga,
	HugaHuga,
};

template<SomeDefine def, unsigned int N>
int function() {
	return N;
}
template<>
int function<HogeHuga, HugaHuga>();


class Specialize
{
public:

	/****************************************************************
	 * @brief constructor
	 ***************************************************************/
	Specialize() throw();


	/****************************************************************
	 * @brief destructor
	 ***************************************************************/
	~Specialize() throw();

	template<int i>
	int get() throw();

private:



};    // class Specialize


#endif





#include <boost/logic/tribool.hpp>
#include <iostream>


class tetra {
	enum tetra_value {
		true_value,         //!< true ‚Ìê‡
		false_value,        //!< false ‚Ìê‡
		neither_value,      //!< ‚Ç‚¿‚ç‚Æ‚à‚¢‚¦‚È‚¢ê‡
		unknown_value,      //!< ‚Ü‚¾‚Ç‚¿‚ç‚©‚í‚©‚ç‚È‚¢ê‡
		max,
	};

	/*explicit*/
	tetra(bool value) throw()
		: value_(value)
	{}

	tetra(tetra_value value) throw()
		: value_(value)
	{}

	char value_;
};

inline tetra operator!(tetra x)
{
  return x.value == tetra::false_value
	  ? tetra(true)
	  : x.value == tetra::true_value?
		  tetra(false)
		  : tribool(indeterminate);
}

int main() {
	using namespace std;

	boost::tribool tri;
	tri = boost::indeterminate;

	if( tri )       cout << "True"  << endl;
	else if( !tri ) cout << "False" << endl;
	else          cout << "Indeterminate" << endl;
5
	std::cout << tri << std::endl;
}



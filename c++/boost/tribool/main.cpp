


#include <boost/logic/tribool.hpp>
#include <iostream>


class tetra {
	enum tetra_value {
		true_value,         //!< true �̏ꍇ
		false_value,        //!< false �̏ꍇ
		neither_value,      //!< �ǂ���Ƃ������Ȃ��ꍇ
		unknown_value,      //!< �܂��ǂ��炩�킩��Ȃ��ꍇ
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



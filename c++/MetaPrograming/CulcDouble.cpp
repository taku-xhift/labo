
#include <iostream> 

using namespace std;

template <int a, int b>
struct Fract { 
	double value() const { 
		const double f = a / double(b); 
		return f; 
	} 
}; 


int main() { 
    Fract <2,5> f; 
    cout << f.value() << endl; 
} 

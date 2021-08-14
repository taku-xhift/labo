


#include <iostream>
#include <vector>
#include <algorithm>


//// コンテナ版
//template<typename Container>
//void sort(Container &c)
//{
//	std::sort(c.begin(), c.end());
//}
//
//
//// 配列版
//template<typename T, std::size_t N>
//void sort(T (&ar)[N])
//{
//	std::sort(ar, ar+N);
//}
//


//--------------------------------------
//  iterator Creator
//--------------------------------------

//---begin-----------------------

// reference
template<typename Container>
typename Container::iterator begin(Container &c)
{
	return c.begin();
}

// const reference
template<typename Container>
typename Container::const_iterator begin(const Container &c)
{
	return c.begin();
}

// array
template<typename T, std::size_t N>
T* begin(T (&ar)[N])
{
	return ar;
}

template<typename T, std::size_t N>
const T* begin(const T (&ar)[N])
{
	return ar;
}

//---end--------------------------

// reference
template<typename Container>
typename Container::iterator end(Container &c)
{
	return c.end();
}

// const reference
template<typename Container>
typename Container::const_iterator end(const Container &c)
{
	return c.end();
}

// array
template<typename T, std::size_t N>
T* end(T (&ar)[N])
{
	return ar + N;
}

// const array
template<typename T, std::size_t N>
const T* end(const T (&ar)[N])
{
	return ar + N;
}

//------------------------------
//  sort
//------------------------------
template<typename Range>
void sort(Range& r)
{
	std::sort(begin(r), end(r));
}



//---range_iterator------------------
template<typename Container>
struct range_iterator
{
	typedef typename Container::iterator type;
};

template<typename Container>
struct range_iterator<const Container>
{
	typedef typename Container::const_iterator type;
};

template<typename T, std::size_t N>
struct range_iterator< T[N] >
{
	typedef T* type;
};

template<typename T, std::size_t N>
struct range_iterator< const T[N] >
{
	typedef const T* type;
};


//--------------------------------
// find
//--------------------------------
// reference
template<typename Container, typename T>
typename range_iterator<Container>::type
    find(Container& c, const T& value)
{
	return std::find(begin(c), end(c), value);
}


// const reference
template<typename Container, typename T>
typename range_iterator<const Container>::type
    find(const Container& c, const T& value)
{
	return std::find(begin(c), end(c), value);
}

//-------------------------------------
// for each
//-------------------------------------
template<typename Range, typename Predicate>
Predicate for_each(const Range& r, Predicate pred)
{
	return std::for_each(begin(r), end(r), pred);
}



class Equaler
{
public:

	template<typename T>
	void operator()(const T& lhs)
	{
		//return lhs::value < 4;
		std::cout << lhs.integer << std::endl;
	}
};

class Sample
{
public:
	int integer;

	Sample()
		 : integer(0)
	{
	}
};



int main()
{
	float floating[10];// = new float[10];
	for (int i = 0; i < 10; ++i) {
		floating[i] = 10-i;
	}

	//std::vector<int> intContainer;
	//sort(intContainer);
	//sort(floating);
	//std::sort(begin(floating), end(floating));
	float *floats = find(floating, 3);

	for (int i = 0; i < 10; ++i) {
		//std::cout << floating[i] << std::endl;
	}

	std::cout << *floats << std::endl;


	{
		Sample sample[5];
		for (int i = 0; i < 5; ++i) {
			sample[i].integer = 5-i;
		}

		for_each(sample, Equaler());
	}

	return 0;
}



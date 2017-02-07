



#include <iostream>
#include <vector>
#include <list>
#include <string>

template<class Type>
void out(Type container)
{

	for (Type::iterator ite = container.begin();
		 ite != container.end();
		 ++ite)
	{
		std::cout << *ite << std::endl;
	}

}



std::vector<int> vectorContainer;
std::list<int> listContainer;


int main()
{
	for (int i = 0; i < 10; ++i) {
		vectorContainer.push_back(i);
		listContainer.push_back(i);
	}

	out(vectorContainer);
	out(listContainer);

	return 0;
}


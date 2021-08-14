


#include <iostream>
#include <string>


template<class T>
class Policy
{
private:

	T member_;

protected:

	T member() const {
		std::cout << "Called Policy class." << std::endl;
		return this->member_;
	}

};


template<class T, template<class> class Policy>
struct Widget : public Policy<T>
{
	void do_something() {
		T value = member();
	}
};


int main()
{
	Widget<int, Policy> hoge;

	hoge.do_something();

	return 0;
}


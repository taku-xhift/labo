

#include <iostream>


template<bool Cond, typename Then, typename Else>
struct if_;

template<true, typename Then, typename Else>
struct if_ {
	typedef Then type;
};

template<false, typename Then, typename Else>
struct if_ {
	typedef Else type;
};



struct debug_log {
	static void print(const std::string& value) {
		std::cout << value << std::endl;
	}
};

template<typename LogPolicy>
struct hoge {
	void foo() const {
		LogPolicy::print("Fatal Error!!!");
	}
};


int main() {
	hoge<debug_log>().foo();

	return 0;
}


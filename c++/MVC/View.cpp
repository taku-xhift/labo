

#include <iostream>


class Controller;


class View {
public:

	explicit View(Controller controller);

	void SetInteger(int value) {
		std::cout << value << "\n";
	}
	void SetFloat(float value) {
		std::cout << value << "\n";
	}
	void SetString(const std::string& value) {
		std::cout << value << "\n";
	}

	void Render() {
		std::cin >> 
	}

private:

	Controller* controller_;
};




#include <iostream>


class Model;
class VIew;


class Controller {
public:
	void GetInput(int value) {
		this->model_->SetIntToDB(value);
	}
	void GetInput(float value) {
		this->model_->SetFloatToDB(value);
	}
	void GetInput(const std::strig& value) {
		this->model_->SetNameToDB(value);
	}

private:

	Model* model_;
	View* view_;
};


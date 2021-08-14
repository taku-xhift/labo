

#include <string>


class Model {
public:

	explicit Model(Controller* controller);

	int GetIntByDB() const {
		return this->integer_;
	}
	void SetIntToDB(int value) {
		this->integer_ = value;
	}
	float GetFloatByDB() const {
		return this->floating_;
	}
	void SetFloatToDB(float value) {
		this->floating_ = value;
	}

	std::string GetNameByDB() const {
		return this->name_;
	}
	void SetNameToDB(const std::string& value) {
		this->name_ = value;
	}

private:

	Controller* controller_;

	int integer_;
	float floating_;
	std::string name_;
};



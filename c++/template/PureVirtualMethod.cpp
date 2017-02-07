


class Base {
public:
	template<typename ValueType>
	ValueType getAs() { ValueType(); }
};


class Delived {
public:
	template<typename ValueType>
	ValueType getAs() { return static_cast<ValueType>this->data; }

	void* data;
};



int main() {

	Delived delived;
}

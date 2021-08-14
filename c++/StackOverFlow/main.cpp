

void func2();


void func1() {
	func2();
}

void func2() {
	func1();
}


int main() {
	func1();
}






#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;


class Equal
{
public:
	Equal(int num_) : num(num_) {}

	// ˆø”‚Æƒƒ“ƒo•Ï”‚Ì’l‚ª“¯‚¶‚©
	bool operator()(int num_) const {
		return (this->num == num_);
	}

private:
	int num;
};

int main() {
	vector<int> container;

	for (int i = 0; i < 10; ++i) {
		container.push_back(i);
	}

	container.erase(remove_if(container.begin(), container.end(), Equal(3)), container.end());

	for (vector<int>::iterator ite = container.begin(); ite != container.end(); ++ite) {
		cout << *ite << endl;
	}
}



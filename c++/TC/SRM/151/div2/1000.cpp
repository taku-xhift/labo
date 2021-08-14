


#include <iostream>
#include <vector>
#include <iterator>


using namespace std;



static int compCounter = 0;


class MergeSort
{
public:

	static vector<int> merge(const vector<int>& left, const vector<int>& right) {
		vector<int> ret;
		vector<int>::const_iterator leftIte = left.begin();
		vector<int>::const_iterator rightIte = right.begin();

		while (true) {
			if (*leftIte < *rightIte) {
				ret.push_back(*leftIte);
				++leftIte;
				++compCounter;
			} else if (*leftIte > *rightIte) {
				ret.push_back(*rightIte);
				++rightIte;
				++compCounter;
			} else {
				ret.push_back(*leftIte);
				ret.push_back(*rightIte);
				++leftIte;
				++rightIte;
				++compCounter;
			}

			if (leftIte == left.end()) {
				//ret.insert(ret.end(), rightIte);
				ret.insert(ret.end(), rightIte, right.end());
				break;
			} else if (rightIte == right.end()) {
				ret.insert(ret.end(), leftIte, left.end());
				break;
			}
		}


		return ret;
	}


	static vector<int> mergeSort(const vector<int>& list) {
		if (list.size() == 1 || list.size() == 0) {
			return list;
		}

		vector<int>::const_iterator ite = list.begin();
		advance(ite, list.size()/2);
		vector<int> left(list.begin(), ite);
		left = mergeSort(left);

		vector<int> right(ite, list.end());
		right = mergeSort(right);

		return merge(left, right);
	}

	static int howManyComparisons(vector <int> numbers) {
		mergeSort(numbers);

		const int ret = compCounter;
		compCounter = 0;
		return ret;
	}


	static void test() {
		{
			vector<int> arg;
			arg.push_back(1);
			arg.push_back(2);
			arg.push_back(3);
			arg.push_back(4);

			if (howManyComparisons(arg) == 4) {
				cerr << "0.ok\n";
			}
		}
		{
			vector<int> arg;
			arg.push_back(2);
			arg.push_back(3);
			arg.push_back(2);

			if (howManyComparisons(arg) == 2) {
				cerr << "1.ok\n";
			}
		}
		{
			vector<int> arg;
			arg.push_back(-17);

			if (howManyComparisons(arg) == 0) {
				cerr << "2.ok\n";
			}
		}
		{
			vector<int> arg;

			if (howManyComparisons(arg) == 0) {
				cerr << "3.ok\n";
			}
		}
		{
			vector<int> arg;
			arg.push_back(-2000000000);
			arg.push_back(2000000000);
			arg.push_back(0);
			arg.push_back(0);
			arg.push_back(0);
			arg.push_back(-2000000000);
			arg.push_back(2000000000);
			arg.push_back(0);
			arg.push_back(0);
			arg.push_back(0);

			if (howManyComparisons(arg) == 19) {
				cerr << "4.ok\n";
			}
		}
	}


};



int main() {
	MergeSort::test();
}



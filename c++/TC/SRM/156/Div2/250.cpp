


#include <array>


#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


struct Drive {
	int max_;
	int now_;

	Drive(int max, int now)
		: max_(max)
		, now_(now)
	{
	}

	bool operator> (const Drive& other) const {
		return this->max_ > other.max_;
	}

	bool Split(Drive& other) {
		const int diff = this->max_ - this->now_;

		if (other.now_ - diff < 0) {
			this->now_ += other.now_;
			other.now_ = 0;

			return true;
		} else {
			this->now_ += diff;
			other.now_ -= diff;

			return false;
		}
	}

	bool IsMax() const {
		if (this->max_ == this->now_) {
			return true;
		} else {
			return false;
		}
	}
};



class DiskSpace {
public:
	static int minDrives(vector <int> used, vector <int> total) {
		vector<Drive> list;
		for (int i = 0; i < used.size(); ++i) {
			list.push_back(Drive(total[i], used[i]));
		}

		sort(list.begin(), list.end(), greater<Drive>());

		for (int i = 0; i < list.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				if (list[j].Split(list[i])) {
					continue;
				}
			}
		}

		int ret = 0;
		for (int i = 0; i < list.size(); ++i) {
			if (list[i].now_ != 0) {
				++ret;
			}
		}

		return ret;
	}
};



int main() {
	
}



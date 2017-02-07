


#include <iostream>


long long getCount(int m, int n, int x, int y) {
	const long long ret = (m - x + 1) * (n - y + 1);
	if (ret >= 0) {
		return ret;
	} else {
		return 0;
	}
}


class RectangularGrid {
public:
	static long long countRectangles(int width, int height) {
		long long ret = 0;    // width, height の時の分

		for (int i = 1; i <= width; ++i) {
			for (int j = 1; j <= height; ++j) {
				if (i == j) {
					continue;
				}

				const int thisCount = getCount(width, height, i, j);
				//std::cout << "(" << i << ", " << j << ") => " << thisCount << "\n";
				ret += thisCount;
				//ret += getCount(width, height, j, i);
			}
		}

		return ret;
	}
};



int main() {
	std::cout << RectangularGrid::countRectangles(1000, 1000) << std::endl;
}


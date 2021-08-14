


#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>


const int tate = 10;
const int yoko = 12;

char lake[tate][yoko];


void init() {
	srand(time(nullptr));

	for (int i = 0; i < tate; ++i) {
		for (int j = 0; j < yoko; ++j) {
			if (rand()%3 == 0) {
				lake[i][j] = 'w';
			} else {
				lake[i][j] = '.';
			}
		}
	}

	for (int i = 0; i < tate; ++i) {
		for (int j = 0; j < yoko; ++j) {
			std::cout << lake[i][j];
		}
		std::cout << "\n";
	}
}


void SearchRound(int x, int y) {
	if (lake[y][x] == '.') {
		return;
	}

	lake[y][x] = '.';

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i != 0 && j != 0
				&& 0 <= x+j && x+j < yoko
				&& 0 <= y+i && y+i < tate)
			{
				SearchRound(x+j, y+i);
			}
		}
	}
}


int main() {
	init();

	std::cout << "Start Counting\n";

	int lakeCount = 0;

	for (int i = 0; i < tate; ++i) {
		for (int j = 0; j < yoko; ++j) {
			if (lake[i][j] == 'w') {
				SearchRound(j, i);
				++lakeCount;
			}
		}
	}

	std::cout << "Lake => " << lakeCount << "\n";
}






#include <iostream>
#include <fstream>


//int N, M;
const unsigned int firstNum = 10;
const unsigned int secondNum = 10;

char input[firstNum][secondNum] = {
	{'w','w','w','.','.','.','w','.','.','w'},
	{'.','.','w','.','w','.','.','.','w','.'},
	{'.','w','.','w','.','w','.','w','.','w'},
	{'.','.','.','.','.','w','.','.','.','w'},
	{'w','w','.','w','.','w','.','.','.','.'},
	{'w','.','w','.','.','.','w','w','w','w'},
	{'.','.','w','.','.','.','.','.','.','.'},
	{'w','w','.','.','.','.','w','.','.','w'},
	{'.','.','.','.','.','w','.','.','w','w'},
	{'w','w','w','.','.','w','.','.','w','.'},
};  // 11


void dfs(int x, int y) {
	input[x][y] = '.';

	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			const int nx = x + dx;
			const int ny = y + dy;

			if (0 <= nx && nx < firstNum && 0 <= ny && ny < secondNum && input[nx][ny] == 'w') {
				dfs(nx, ny);
			}
		}
	}
}


void solve() {
	int res = 0;

	for (int i = 0; i < firstNum; ++i) {
		for (int j = 0; j < secondNum; ++j) {
			if (input[i][j] == 'w') {
				dfs(i, j);
				++res;
			}
		}
	}

	std::cout << res << "\n";
}


int main() {
	solve();

	for (int i = 0; i < firstNum; ++i) {
		for (int j = 0; j < secondNum; ++j) {
			std::cout << input[i][j];
			input[i][j] = '.';
		}
		std::cout << "\n";
	}
}



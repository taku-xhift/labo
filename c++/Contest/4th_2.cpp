


#include <iostream>
#include <algorithm>


const int arrayNum = 1000;
int result = 512;
int array[arrayNum];

int squareArray[arrayNum * arrayNum];



bool binary_search(int x) {
	int l = 0;
	int r = arrayNum * arrayNum;

	while (r - l >= 1) {
		const int i = (l + r)/2;

		if (squareArray[i] == x) {
			// Œ©‚Â‚©‚Á‚½
			return true;
		} else {
			r = i;
		}

	}

	return false;
}


void solve() {
	// array[c] + array[d] ‚Ì‚Æ‚è‚¤‚é’l‚ð—ñ‹“
	for (int c = 0; c < arrayNum; ++c) {
		for (int d = 0; d < arrayNum; ++d) {
			squareArray[c * arrayNum + d] = array[c] + array[d];
		}
	}

	std::sort(squareArray, squareArray + arrayNum * arrayNum);

	bool f = false;

	for (int a = 0; a < arrayNum; ++a) {
		for (int b = 0; b < arrayNum; ++b) {
			// “à‘¤‚Ì‚Q‚Â‚Ìƒ‹[ƒv‚Ì•Ï‚í‚è‚É“ñ•ª’Tõ
			if (binary_search(result - array[a] - array[b])) {
				f = true;
				break;
			}
		}
	}


	if (f) {
		puts("Yes");
	} else {
		puts("No");
	}
}




int main() {
	for (int i = 0; i < arrayNum; ++i) {
		const int random = rand()%result;
		array[i] = random;
	}

	solve();
}


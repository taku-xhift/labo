


#include <iostream>


const int length = 10;
const int antNum = 3;
const int dissFromLeft[antNum] = {1, 6, 7};



struct Ant
{
	bool seeLeft;
	int pos;

	Ant()
		: seeLeft(true)
		, pos(0)
	{
		
	}


	Ant(bool doMin, int pos, int length)
		: pos(pos)
	{
		if (doMin) {
			if (pos <= length/2)
				this->seeLeft = true;
			else
				this->seeLeft = false;
		} else {
			if (pos <= length/2)
				this->seeLeft = false;
			else
				this->seeLeft = true;
		}
	}


	bool walk() {
		this->seeLeft
			? --this->pos
			: ++this->pos;

		if (this->pos < 0 || length < this->pos) {
			return true;
		} else {
			return false;
		}
	}


	void seeAnother() {
		this->seeLeft ~= 1;
	}
};

int main()
{
	int minTime = 0;

	Ant ants[antNum];
	for (int i = 0; i < antNum; ++i) {
		ants[i] = Ant(true, dissFromLeft[i], length);
	}


	bool isEnd = false;
	while (!isEnd) {
		int count = 0;
		for (int i = 0; i < antNum; ++i) {
			if (ants[i].walk()) {
				++count;
			}
		}

		if (count == antNum) {
			isEnd = true;
		} else {
			++minTime;
		}
	}


	// ƒŠƒZƒbƒg
	for (int i = 0; i < antNum; ++i) {
		ants[i] = Ant(false, dissFromLeft[i], length);
	}


	isEnd = false;
	while (!isEnd) {
		int count = 0;
		for (int i = 0; i < antNum; ++i) {
			if (i-1 >= 0) {
				if (ants[i-1].pos - ants[i] <= 2) {
					if (ants[i-1].seeLeft != ants[i-1]) {
						// ‚Ô‚Â‚©‚é
						ants[i-1].seeAnother()
						ants[i].seeAnother();
						continue;
					}
				}
			}
		}
	}





	// Œ‹‰Ê
	std::cout << "Min Time => " << minTime << std::endl;

}



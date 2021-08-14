#include <iostream>
#include <map>
#include <cstring>

class Word
{
	char str[20];
public:
	Word() { strcpy(str, ""); }
	Word(char* s) { strcpy(str, s); }
	char* get() { return str; }
};

bool operator<(Word a, Word b)
{
	return strcmp(a.get(), b.get()) < 0;
}

class Opposite
{
	char str[20];
public:
	Opposite() { strcpy(str, ""); }
	Opposite(char* s) { strcpy(str, s); }
	char* get() { return str; }
};

int main()
{
	std::map<Word, Opposite> m;

	m.insert(std::pair<Word, Opposite>(Word("yes"), Opposite("no")));

	m.insert(std::pair<Word, Opposite>(Word("good"), Opposite("bad")));

	m.insert(std::pair<Word, Opposite>(Word("left"), Opposite("right")));

	m.insert(std::pair<Word, Opposite>(Word("up"), Opposite("down")));

	char str[80];
	std::cout << "単語を入力： ";
	std::cin >> str;
	
	std::map<Word, Opposite>::iterator p;

	p = m.find(Word(str));

	if (p != m.end()) {
		std::cout << "反対語：" << p->second.get(); << std::endl;
	} else {
		std::cout << "単語がマップにない" << std::endl;
	}

	return 0;
}

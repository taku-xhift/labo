#include <iostream>
using namespace std;

template <class date_t>
class list {
	date_t date;
	list* next;

public:
	list(date_t d);
	void add(list* node) { node->next = this; next = 0; }
	list* getNext() { return next; }
	date_t getDate() { return date; }
};


template <class data_t> list<data_t>::list(data_t d)
{
	date = d;
	next = 0;
}


int main()
{
	list<char> start('a');
	list<char> *p, *last;

	// リストを作成する
	last = &start;

	for (int i = 1; i < 26; ++i) {
		p = new list<char> ('a' + i);
		p->add(last);
		last = p;
	}

	// リストを追跡する
	p = &start;

	while (p) {
		cout << p->getDate();
		p = p->getNext();
	}

	return 0;
}
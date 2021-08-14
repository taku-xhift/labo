


#include <stdio.h>

typedef enum {
	Zero,
	One,
	Two,
} Number;


void print(Number num) {
	printf("%d", num);
}

int main() {
	print(1);

	return 0;
};


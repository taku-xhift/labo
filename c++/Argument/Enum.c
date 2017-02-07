


#include <stdio.h>

typedef enum {
	ENUMARG_ONE = 1,
} EnumArg;

void out(EnumArg enum_) {
	printf("%d\n", enum_);
}


int main() {
	out(6);

	return 0;
}



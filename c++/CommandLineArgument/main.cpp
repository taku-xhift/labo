#include <stdio.h>

int main(int argc,char *argv[])
{
	int i;
	
	printf("�����̑��� = %d\n", argc);
	for (i = 0; i < argc; i++) {
		printf("%d�Ԗڂ̈��� = %s\n", i, argv[i]);
	}
}

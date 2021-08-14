#include <stdio.h>

int main(int argc,char *argv[])
{
	int i;
	
	printf("ˆø”‚Ì‘ŒÂ” = %d\n", argc);
	for (i = 0; i < argc; i++) {
		printf("%d”Ô–Ú‚Ìˆø” = %s\n", i, argv[i]);
	}
}

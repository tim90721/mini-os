#include <stdio.h>
#include <stdlib.h>

void exit(s32 err)
{
	printf("Exit the program with ret code: %d\n", err);

	while (1)
		;
}

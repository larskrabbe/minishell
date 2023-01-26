#include	<unistd.h>
#include	<stdio.h>

int main(int argc, char *argv[])
{
	while(1)
	{}
	if (argc != 0)
		printf("argv[0] = %s\n", argv[0]);
	return (0);
}
#include	<unistd.h>
#include	<stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 0)
		printf("argv[0] = %s\n", argv[0]);
	return (0);
}
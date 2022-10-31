#include	<stdio.h>
#include	<readline/readline.h>
#include	<readline/history.h>

int	main()
{
	char *promt = NULL;
	char *ptr;

	ptr = readline(NULL); //reads line from terminal input
	printf("%s\n<minishell>",ptr);
	return(0);
}
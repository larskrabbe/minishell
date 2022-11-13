#include	"lexer.h"

void	print_token_chain(t_token *tokenchain)
{
	int	i;

	print_token(&tokenchain[0]);
	i = 1;
	while (tokenchain[i].tokentype != token_end)
	{
		printf("	|	\n");
		printf("	|	\n");
		printf("       \\|/	\n");
		printf("	V	\n");
		print_token(&tokenchain[i]);
		i++;
	}
	printf("	|	\n");
	printf("	|	\n");
	printf("       \\|/	\n");
	printf("	V	\n");
	print_token(&tokenchain[i]);
}

void	print_token(t_token *token)
{	
	printf("--------------\n");
	printf("tokentype = %i\n",token->tokentype);
	printf("content = %s  \n",token->content);
	printf("--------------\n");
}

void	myerror(char *str)
{
	printf("%s\n", str);
	exit (0);
}

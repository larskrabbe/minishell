#include	"lexer.h"

int main()
{
	t_token *tokenchain;

	printf("test start\n");
	create_token_chain(tokenchain);
	print_token_chain(tokenchain);
	// lexer("echo");
	printf("test end\n");
	return (0);
}
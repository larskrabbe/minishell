
#include	"lexer.h"

int	create_token_chain(t_token	*ptr)
{
	ptr = calloc(ARG_MAX, sizeof(t_token));
	if (ptr == NULL)
		return (0);
	ptr[0].tokentype = token_start;
	return (1);
}

void	free_token_chain(t_token *ptr)
{
	free(ptr);
}
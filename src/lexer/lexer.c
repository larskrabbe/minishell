#include	"lexer.h"


void	token_builtins(const char *str, int *i, t_token *tokenchain, int *cur_token)
{
	int	end_char;

	end_char = 0;
	if (str[*i] == 39 || str[*i] == 34)
		end_char = str[*i];
	while (str[*i] != '\0' && !(str[*i] == end_char))//needs is_whitespace
	{
		i += 1;
	}
	*cur_token += 1;
}

// void	token_flag(const char str, int *i, t_token *tokenchain, int *cur_token)
// {
	
// }

// void	token_arguments(const char str, int *i, t_token *tokenchain, int *cur_token)
// {
	
// }

// void	token_logic(const char str, int *i, t_token *tokenchain, int *cur_token)
// {
	
// }


void	lexer(char *str, t_token *tokenchain)
{
	int		i;
	int 	cur_token;
	if (create_token_chain(tokenchain))// will be at the beginning of minishell later
		myerror("malloc error");
	i = 0;
	tokenchain[0].tokentype = token_start;
	tokenchain[0].content = NULL;
	cur_token = 1;
	// while(str[i] != '\0')
	if (str[i] != '\0')// to test one tokenizer first 
	{
		token_builtins(str, &i, tokenchain, &cur_token);
		// token_flag(str, &i, &tokenchain, &cur_token);
		// token_arguments(str, &i, &tokenchain, &cur_token);
		// token_logic(str, &i, &tokenchain, &cur_token);
	}
	tokenchain[cur_token].tokentype = token_end;
}
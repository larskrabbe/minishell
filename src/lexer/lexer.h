//?-----------Includes------------?//

#include	"../../include/minishell.h"

//?-----------Defines------------?//

#define ARG_MAX 1000

//?-----------Enums------------?//

typedef	enum e_toektype{
builtins = 0,
excutables = 1,
token_pipe = 2,
and = 3,
or = 4,
argument = 5,
input_file = 6,
input_until = 7,//need a better name for <<
output_overwrite = 8,
output_append = 9,
token_start ,
token_end ,
}t_tokentype;

//?-----------Structs------------?//

typedef struct s_token{
t_tokentype		tokentype;
char			*content;// saving the content inside of the token is maybe more set up but its  way easier to  manipulate it later
}t_token;

//?-----------Protoypes------------?//

//------lexer_main.c------

void	lexer(char *str, t_token *tokenchain);

//------lexer_utiels.c-----

void	print_token(t_token *token);
void	print_token_chain(t_token *tokenchain);

//------lexer_memory.c-------

int		create_token_chain(t_token	*ptr);
void	free_token_chain(t_token *ptr);
void	myerror(char *str);// will be in minishell.h later



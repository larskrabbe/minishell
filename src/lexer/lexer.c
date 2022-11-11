#include	"../../include/minishell.h"

typedef	enum e_toektype{
builtins = 0,
excutables = 1,
pipe = 2,
and = 3,
or = 4,
argument = 5,
input_file = 6,
input_until = 7,//need a better name for <<
output_overwrite = 8,
output_append = 9,
}t_tokentype;


typedef struct s_token{
t_tokentype		tokentype;
t_token			*next;
t_token			*back;// not sure if  needed
char			*content;
}t_token;



void	lexer(char *str)
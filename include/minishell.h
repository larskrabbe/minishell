#include	<stdio.h>
#include	<readline/readline.h>
#include	<readline/history.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<signal.h>

//?-----------Enums------------?//

typedef enum e_signal{
	no_signal = 0,
	exit_signal = 1,
	c_signal = 2,
}t_sigal;
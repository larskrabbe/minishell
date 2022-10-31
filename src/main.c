
#include	"../include/minishell.h"

int	main()
{
	char	*str;
	char	prompt[] = "<minishell>";//need to show the path
	// sigset_t

	// sigaction();
	while (1)
	{
		str = readline(prompt);
		printf("%s\n", str);//stoneage echo version
		free(str);
	}
	return (0);
}
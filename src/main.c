
#include	"../include/minishell.h"

int	main()
{
	char	*str;
	char	prompt[] = "<minishell>";//need to show the path

	while (1)
	{
		str = readline(prompt);
		printf("%s\n", str);//stoneage echo version
	}
	return (0);
}
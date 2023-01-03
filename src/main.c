/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:20:23 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/03 18:52:45 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	g_signal;

void recieve(int signum)
{

	// printf("Signalnumber %i recieve\n",signum);
	clear_history();
	g_signal = signum;
	// rl_replace_line(NULL,0);
	// exit(0);
	write(STDOUT_FILENO, "", 1);
}

void	signal_setup(struct sigaction *signal_handler)
{
	g_signal = 0;
	signal_handler->sa_handler = (void *)recieve;
	sigemptyset (&signal_handler->sa_mask);
	//signal_handler->sa_flags = SA_SIGINFO; not sure if needed 
	sigaction(SIGINT,signal_handler,NULL);
}

void	free_before_exit(void)
{
	clear_history();

}

char	**create_argv(t_tokenchain *tokenchain, char **argv)
{
	int	i;
	int	a;

	a = 0;
	i = 1;
	while (*tokenchain->token[i].end != '\0' || \
	tokenchain->token[i].type == type_pipe)
	{
		if (tokenchain->token[i].type == type_str || tokenchain->token[i].type == type_built_exe)
		{
			argv[a] = tokenchain->token[i].str;
			a++;
		}
		i++;
	}
	return (argv);
}


int execution(t_tokenchain *tokechain, t_env *env_lst, char **tmp_env)
{
	char	*ptr;
	char	*argv[ARG_MAX];

	// check if builtins
	ptr = get_cmd_path(&env_lst, tokechain->token[1].str);
	// error if ptr == null
	create_argv(tokechain, argv);
	printf("path = %s\n", ptr);
	// need to turn all arg in a double pointer
	if (execve(ptr, argv, tmp_env) == -1)
		printf("execve failed\n");
	printf("arg = %s\n", argv[0]);
	printf("arg = %s\n", argv[1]);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char				*str;
	char				prompt[] = "<minishell>";
	struct sigaction	signal_handler;
	t_env				*env = NULL;
	t_tokenchain		*tokenchain;
	char	*s[2];

	s[0] = "ls";
	s[1] = "-la";
	if (argc <= 1 && argv == NULL)
		return (0);
	tokenchain = tokenchain_create();
	if (tokenchain == NULL)
		return (error_allocation);
	signal_setup(&signal_handler);
	env = *ft_getenv_lst(envp);
	while (g_signal == 0)
	{	
		str = readline(prompt);
		if (str != NULL)
		{
			add_history(str);
			lexer(str, tokenchain);
			expander(tokenchain, env);
			execution(tokenchain, env, envp);
			free_str_in_token(tokenchain);
		}
		free(str);
	}
	free_before_exit();
	return (0);
}
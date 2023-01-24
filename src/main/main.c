/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:20:23 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/24 17:59:04 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

// int	g_signal;

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

char	**create_argv(t_tokenchain *tokenchain, char **argv, int *i)
{
	int	a;

	a = 0;
	printf("seg maybe here\n i = %i\n", *i);
	while (*tokenchain->token[*i].end != '\0' || \
	tokenchain->token[*i].type == type_pipe)
	{
		if (tokenchain->token[*i].type == type_str || \
		tokenchain->token[*i].type == type_built_exe)
		{
			argv[a] = tokenchain->token[*i].str;
			printf("> %s\n",argv[a]);
			a++;
		}
		i++;
	}
	if (tokenchain->token[*i].type == type_str || \
	tokenchain->token[*i].type == type_built_exe)
	{
		argv[a] = tokenchain->token[*i].str;
		printf("> %s\n",argv[a]);
		a++;
	}
	argv[a] = NULL;
	return (argv);
}

void	free_redirection(t_redirection *redirection)
{
	if (redirection->infile != NULL)
		free(redirection->infile);
	if (redirection->outfile != NULL)
		free(redirection->outfile);
	redirection->infile = NULL;
	redirection->outfile = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	char				*str;
	char				prompt[] = "<minishell>";
	//struct sigaction	signal_handler;//? dont think this needs to be, should be able to in the signal set up
	t_env				*env = NULL;
	t_tokenchain		*tokenchain;// maybe use double pointer
	t_exe_data			*exe_data;// maybe use double pointer
	t_redirection		redirection;

	redirection.outfile = NULL;
	redirection.infile = NULL;
	redirection.exit_code = 0;
	int tmp_i = 0;
	if (argc <= 1 && argv == NULL)
		return (0);
	tokenchain = tokenchain_create();
	if (tokenchain == NULL)
		return (error_allocation);
	//signal_setup(&signal_handler);
	env = *ft_getenv_lst(envp);
	g_signal = 1;
	while (g_signal != 0)
	{
		set_signals();
		str = readline(prompt);
		if (!str)
		{
			write(1, "exit\n", 5);
			g_signal = 0;
		}
		if (str != NULL )
		{
			if (*str != '\0')
			{
				exe_data = NULL;
				add_history(str);
				if (lexer(str, tokenchain) == 0)
				{
					// print_token_chain(tokenchain);
					if (expander(tokenchain, env, &exe_data, &redirection) == 0)
						execution(exe_data, env, &redirection);
					free_str_in_token(tokenchain);
					free_redirection(&redirection);
				}
			}
		}
		free(str);
		str = NULL;
		reset_signals();
		// printf("Status>> %d\n", ((g_signal) >> 8) & 0x000000ff);
		// break ;
		// system("leaks minishell");
	}
	clean_env(&env);
	free_before_exit();
	// system("leaks minishell");
	return (0);
}

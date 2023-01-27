/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:20:23 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/27 16:05:01 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

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
			printf("> %s\n", argv[a]);
			a++;
		}
		i++;
	}
	if (tokenchain->token[*i].type == type_str || \
	tokenchain->token[*i].type == type_built_exe)
	{
		argv[a] = tokenchain->token[*i].str;
		printf("> %s\n", argv[a]);
		a++;
	}
	argv[a] = NULL;
	return (argv);
}

void	string_translate(t_tokenchain *tokenchain, \
t_redirection *redirection, t_env **env_lst)
{
	add_history(tokenchain->str);
	if (lexer(tokenchain) == 0)
	{
		if (expander(tokenchain, env_lst, redirection) == 0)
			execution(redirection->og_ptr, env_lst, redirection);
		free_all_t_exe_data(redirection->og_ptr);
		redirection->og_ptr = NULL;
	}
}

void	read_line_loop(t_tokenchain *tokenchain, \
t_redirection *redirection, t_env **env_lst, char *tester)
{
	char		*str;
	tester = NULL;
	while (g_signal != signal_d)
	{
		set_signals();
		str = readline(IDLE_PROMT);
		// str = tester;
		if (!str)
		{
			write(1, "exit\n", 5);
			g_signal = signal_d;
		}
		if (str != NULL && (g_signal != signal_d))
		{
			tokenchain->str = str;
			if (*str != '\0')
			{
				string_translate(tokenchain, redirection, env_lst);
			}
		}
		free(str);
		free_str_in_token(tokenchain);
		str = NULL;
		reset_signals();
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	printf("pid %i\n",getpid());
	t_env				**env;
	t_tokenchain		*tokenchain;
	t_exe_data			*exe_data;
	t_redirection		redirection;

	if (argc <= 1 && argv == NULL)
		return (0);
	exe_data = NULL;
	redirection.fd_infile = -1;
	redirection.fd_outfile = -1;
	redirection.exit_code = 0;
	redirection.og_ptr = NULL;
	tokenchain = tokenchain_create();
	if (tokenchain == NULL)
		return (error_allocation);
	redirection.tokenchain = tokenchain;
	env = ft_getenv_lst(envp);
	g_signal = 1;
	read_line_loop(tokenchain, &redirection, env, NULL);
	// if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	// {
	// 	read_line_loop(tokenchain, &redirection, env, argv[2]);
	// 	//exit(redirection.exit_code);
	// }
	clean_env(env);
	clear_history();
	tokenchain_free(tokenchain);
	return (redirection.exit_code);
}

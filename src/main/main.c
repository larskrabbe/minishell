/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:20:23 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/26 14:39:29 by bogunlan         ###   ########.fr       */
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

void	string_translate(t_exe_data *exe_data, t_tokenchain *tokenchain, \
t_redirection *redirection, t_env *env)
{
	exe_data = NULL;
	add_history(tokenchain->str);
	if (lexer(tokenchain) == 0)
	{
		if (expander(tokenchain, env, &exe_data, redirection) == 0)
			execution(exe_data, env, redirection);
		free_str_in_token(tokenchain);
	}
}

void	read_line_loop(t_exe_data *exe_data, t_tokenchain *tokenchain, \
t_redirection *redirection, t_env *env)
{
	char	*str;

	while (g_signal != signal_d)
	{
		set_signals();
		str = readline(IDLE_PROMT);
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
				string_translate(exe_data, tokenchain, redirection, env);
			}
		}
		free(str);
		str = NULL;
		reset_signals();
	}
}
 #include <stdlib.h>
int	main(int argc, char *argv[], char *envp[])
{
	//printf("pid = %i\nsizeof envp = %lu\n", getpid(), sizeof(envp));
	t_env				**env;
	t_tokenchain		*tokenchain;
	t_exe_data			*exe_data;
	t_redirection		redirection;

	// envp = NULL;
	if (argc <= 1 && argv == NULL)
		return (0);
	exe_data = NULL;
	redirection.fd_infile = -1;
	redirection.fd_outfile = -1;
	redirection.exit_code = 0;
	tokenchain = tokenchain_create();
	if (tokenchain == NULL)
		return (error_allocation);
	env = ft_getenv_lst(envp);
	printf("%p\n", env);
	if (env != NULL)
	{	
		read_line_loop(exe_data, tokenchain, &redirection, *env);
		clean_env(env);
		clear_history();
	}
	else 
		redirection.exit_code = error_allocation;
	return (redirection.exit_code);
}

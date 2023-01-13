/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:20:23 by lkrabbe           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/05 18:10:52 by lkrabbe          ###   ########.fr       */
=======
/*   Updated: 2023/01/06 18:15:55 by bogunlan         ###   ########.fr       */
>>>>>>> 08bff37d9f757a582324a029c6c523d9af75c5b0
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

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_t_exe_data(t_exe_data *ptr)
{
	free_char_array(ptr->argv);
	free(ptr->path);
}

t_exe_data	*next_t_exe_data(t_exe_data *exe_data)
{
	t_exe_data	*tmp;

	tmp = exe_data->next;
	free(exe_data);
	return (tmp);
}

void	free_all_t_exe_data(t_exe_data *ptr)
{
	while (ptr != NULL)
		ptr = next_t_exe_data(ptr);
}

void	printf_str_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%i > %s\n", i, array[i]);
		i++;
	}
}



int	execution(t_exe_data *exe_data, t_env *env_lst, char **tmp_env)
{
	pid_t	pid;
	int		status;
	int		i;

	i = 1;
	while (exe_data != NULL)
	{
		printf_str_array(exe_data->argv);
		// !check if builtins
		exe_data->path = get_cmd_path(&env_lst, exe_data->argv[0]);
		// !error if ptr == null
		// !need to turn all arg in a double pointer
		pid = fork();
		if (pid == 0)
		{
			if (execve(exe_data->path, exe_data->argv, tmp_env) == -1)
				printf("execve failed\n");
		}
		else
			waitpid(pid, &status, 0);
		exe_data = next_t_exe_data(exe_data);
	}
	exe_data = NULL;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char				*str;
	char				prompt[] = "<minishell>";
	struct sigaction	signal_handler;//? dont think this needs to be, should be able to in the signal set up
	t_env				*env = NULL;
	t_tokenchain		*tokenchain;
	t_exe_data			*exe_data;

	printf("started\n");
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
			expander(tokenchain, env, &exe_data);
			execution(exe_data, env, envp);
			free_str_in_token(tokenchain);
		}
		free(str);
	}
	free_before_exit();
	return (0);
}

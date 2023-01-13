/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:44:54 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/13 22:09:30 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// needs handel redirectin in the child process
int	execution_forking(t_exe_data *exe_data, char **tmp_env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		//redirection
		if (execve(exe_data->path, exe_data->argv, tmp_env) == -1)
			printf("execve failed\n");
		exit (0);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}

int	execution(t_exe_data *exe_data, t_env *env_lst)
{
	int		i;

	i = 1;
	while (exe_data != NULL)
	{
		//! maybe here we need to change the process so we can 
		if (cmd_is_builtin(exe_data->argv[0]))
			printf("is builtin\n"); // ! this is tmp aslong as cmd_is_builtin doesnt start thh funktion
		else
		{
			exe_data->path = get_cmd_path(&env_lst, exe_data->argv[0]);
			// !need to turn all arg in a double pointer
			if (exe_data->path == NULL)
			{
				printf("%s command not found\n", exe_data->argv[0]);// maybe needs to get printed in the errorfile
				fflush(stdout);
			}
			else
				execution_forking(exe_data, env_as_string(&env_lst));
		}
		exe_data = next_t_exe_data(exe_data);
	}
	//prints error file ?
	return (0);
}

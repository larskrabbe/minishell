/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:44:54 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/17 20:24:13 by lkrabbe          ###   ########.fr       */
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

int	pipe_start(t_exe_data *exe_data, t_redirection *redirection)
{
	int	fd[2];

	if (exe_data->fd_read == 0)
	{
		if (redirection->infile != NULL)
			fd[0] = open(redirection->infile, 0777);
		if (fd[0] < 0)
			return (error_open);
	}
	else if (exe_data->next == NULL)
	{
		if (redirection->outfile != NULL)
			fd[0] = open(redirection->outfile, 0777);
		if (fd[0] < 0)
			return (error_open);
	}
	else
	{
		if (pipe(fd))
			return (error_pipe);
		exe_data->fd_write = fd;
		exe_data->next->fd_write = fd;
	}
	return (0);
}

int	pipe_end(t_exe_data *exe_data)
{
	if (close(exe_data->fd_read[1]))
		return (1);
	if (close(exe_data->fd_write[0]))
		return (1);
	return (0);
}

int	execution(t_exe_data *exe_data, t_env *env_lst)
{
	int				i;
	t_redirection	tmp;

	tmp.infile = NULL;
	tmp.outfile = NULL;
	i = 1;
	while (exe_data != NULL)
	{
		pipe_start(exe_data, &tmp);
		//! maybe here we need to change the process so we can 
		if (cmd_is_builtin(exe_data->argv[0]))// !if builtin it shpid still be executed in a extra child // ! if it isjust one built in , dont need t o create a child ( becuase of cd and other stufft hat wouldnt work)
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
	pipe_end(exe_data);
	//prints error file ?
	return (0);
}

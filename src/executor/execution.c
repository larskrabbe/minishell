/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:44:54 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/18 17:39:34 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// needs handel redirectin in the child process
int	execution_forking(t_exe_data *exe_data, char **tmp_env)
{
	pid_t	pid;
	int		status;

	printf("start forking\n");
	pid = fork();
	if (pid == 0)
	{
		printf("fd read = %i fd writing = %i\n", exe_data->fd_read, exe_data->fd_write);
		if (exe_data->fd_read != -1)
		{
			dup2(exe_data->fd_read, STDIN_FILENO);
			close(exe_data->fd_read);
		}
		if (exe_data->fd_write != -1)
		{
			dup2(exe_data->fd_write, STDOUT_FILENO);
			close(exe_data->fd_write);
		}
		printf(">>%s\n",exe_data->argv[1]);
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

	if (exe_data->fd_read == -1)
	{
		if (redirection->infile != NULL)// this can be a separat funktion 
		{
			fd[0] = open(redirection->infile, 0777);
			if (fd[0] < 0)
				return (error_open);
			exe_data->fd_read = fd[0];
		}
	}
	if (exe_data->next == NULL)
	{
		if (redirection->outfile != NULL)
		{
			fd[0] = open(redirection->outfile, 0777);
			if (fd[0] < 0)
				return (error_open);
			exe_data->fd_write = fd[0];
		}
	}
	if (exe_data->next != NULL)// need to  split this case in
	{
		if (pipe(fd))
			return (error_pipe);
		exe_data->fd_write = fd[0];
		exe_data->next->fd_read = fd[1];
	}
	return (0);
}

int	pipe_end(t_exe_data *exe_data)
{
	// printf("fd read = %i fd writing = %i\n", exe_data->fd_read, exe_data->fd_write);
	if (exe_data->fd_read != -1)
		if (close(exe_data->fd_read))
			return (1);
	if (exe_data->fd_write != -1)
		if (close(exe_data->fd_write))
			return (1);
	return (0);
}

int	execution(t_exe_data *exe_data, t_env *env_lst)
{
	int				i;
	t_redirection	tmp;
	int				tmp_i = 0;
	// int				built_in_flag;

	tmp.infile = NULL;
	tmp.outfile = NULL;
	i = 1;
	while (exe_data != NULL && tmp_i < 10)
	{
		tmp_i++;
		printf("in execution\n");
		// need a checker to see if its just 1 builtin call and no piping, if yes DO NOT fork
		if (pipe_start(exe_data, &tmp) != 0)
			printf("error in pipe_start\n");
		printf(">>%s\n",exe_data->argv[1]);
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
			{
				execution_forking(exe_data, env_as_string(&env_lst));
			}
		}
		// return (0);
		pipe_end(exe_data);// will cause a segfault currently if ther is no fd
		exe_data = next_t_exe_data(exe_data);
	}
	//prints error file ?
	return (0);
}

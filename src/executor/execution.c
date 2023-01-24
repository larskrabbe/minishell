/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:44:54 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/23 20:06:09 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// needs handel redirectin in the child process
int	execution_forking(t_exe_data *exe_data, t_env *env_lst, int built_in_flag)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
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
		if (built_in_flag == TRUE)
		{
			handle_builtin(exe_data->argv[0], &exe_data->argv[1], &env_lst);
		}
		else
		{
			if (execve(exe_data->path, exe_data->argv, env_as_string(&env_lst)) == -1)
				printf("execve failed\n");
		}
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
		if (redirection->fd_outfile != -1)
		{
			exe_data->fd_write = redirection->fd_outfile;
		}
	}
	if (exe_data->next != NULL)// need to  split this case in
	{
		if (pipe(fd))
			return (error_pipe);
		exe_data->fd_write = fd[1];
		exe_data->next->fd_read = fd[0];
	}
	return (0);
}

int	pipe_end(t_exe_data *exe_data)
{
	if (exe_data->fd_read != -1)
	{
		dup2(STDIN_FILENO, exe_data->fd_read);
		if (close(exe_data->fd_read))
			return (1);
	}
	if (exe_data->fd_write != -1)
	{
		dup2(STDOUT_FILENO, exe_data->fd_write);
		if (close(exe_data->fd_write))
			return (1);
	}
	return (0);
}

int	execution(t_exe_data *exe_data, t_env *env_lst, t_redirection *redirection)
{
	int				built_in_flag;

	built_in_flag = FALSE;
	while (exe_data != NULL)
	{
		// need a checker to see if its just 1 builtin call and no piping, if yes DO NOT fork
		if (pipe_start(exe_data, redirection) != 0)
			printf("error in pipe_start\n");
		built_in_flag = cmd_is_builtin(exe_data->argv[0]);// !if builtin it shpid still be executed in a extra child // ! if it isjust one built in , dont need t o create a child ( becuase of cd and other stufft hat wouldnt work)
		if (built_in_flag == FALSE)
		{
			exe_data->path = get_cmd_path(&env_lst, exe_data->argv[0]);
			if (exe_data->path == NULL)
			{
				printf("%s command not found\n", exe_data->argv[0]);// maybe needs to get printed in the errorfile
			}
		}
		if (exe_data->path != NULL || built_in_flag == TRUE)
		execution_forking(exe_data, env_lst, built_in_flag);
		pipe_end(exe_data);
		exe_data = next_t_exe_data(exe_data);
	}
	//prints error file ?
	return (0);
}

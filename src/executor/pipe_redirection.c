/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:17:16 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 09:31:47 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	changing_fd_in_out(t_exe_data *exe_data)
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
		if (exe_data->next != NULL)
			close(exe_data->next->fd_read);
	}
}

int	pipe_start(t_exe_data *exe_data, t_redirection *redirection)
{
	int	fd[2];

	redirection->pipe_read = -1;
	redirection->pipe_write = -1;
	if (exe_data->next != NULL)
	{
		if (pipe(fd))
			return (error_pipe);
		if (exe_data->fd_write == -1)
			exe_data->fd_write = fd[1];
		else
			redirection->pipe_write = fd[1];
		if (exe_data->next->fd_read == -1)
			exe_data->next->fd_read = fd[0];
		else
			redirection->pipe_read = fd[0];
	}
	return (0);
}

int	close_files_and_pipes(t_exe_data *exe_data, t_redirection *redirection)
{
	if (exe_data->fd_read != -1)
	{
		close(exe_data->fd_read);
		exe_data->fd_read = -1;
	}
	if (exe_data->fd_write != -1)
	{
		close(exe_data->fd_write);
		exe_data->fd_write = -1;
	}
	if (redirection->pipe_read != -1)
	{
		close(redirection->pipe_read);
		redirection->pipe_read = -1;
	}
	if (redirection->pipe_write != -1)
	{
		close(redirection->pipe_write);
		redirection->pipe_write = -1;
	}
	return (0);
}

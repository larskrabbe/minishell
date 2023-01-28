/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 00:55:46 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 09:33:28 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	clean_exit(t_redirection *redirection, t_env **env_lst)
{
	clear_history();
	clean_env(env_lst);
	free_all_t_exe_data(redirection->og_ptr);
	tokenchain_free(redirection->tokenchain);
	exit (0);
}

int	count_exe_data(t_exe_data *ptr)
{
	int	i;

	i = 0;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

void	single_builtin(t_exe_data *exe_data, t_env **env_lst, \
t_redirection *redirection)
{
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (exe_data->fd_read != -1)
	{
		dup2(exe_data->fd_read, STDIN_FILENO);
		close(exe_data->fd_read);
		exe_data->fd_read = -1;
	}
	if (exe_data->fd_write != -1)
	{
		dup2(exe_data->fd_write, STDOUT_FILENO);
		close(exe_data->fd_write);
		exe_data->fd_write = -1;
	}
	redirection->exit_code = handle_builtin(exe_data->argv[0], \
	&exe_data->argv[1], env_lst);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

int	execution(t_exe_data *exe_data, t_env **env_lst, \
t_redirection *redirection)
{
	int	built_in_flag;
	int	exe_count;
	int	status;

	built_in_flag = FALSE;
	g_signal = 1;
	if (cmd_is_builtin(exe_data->argv[0]) && exe_data->next == NULL)
	{
		single_builtin(exe_data, env_lst, redirection);
		return (0);
	}
	while (exe_data != NULL && exe_data->argv[0] != NULL)
	{
		execution_loop(exe_data, env_lst, redirection, &built_in_flag);
		exe_data = exe_data->next;
	}
	exe_data = redirection->og_ptr;
	exe_count = count_exe_data(exe_data);
	while (exe_data != NULL && exe_count > 0)
	{
		if (waitpid(0, &status, 0) == redirection->last_pid)
			redirection->exit_code = (status);
		exe_count--;
	}
	return (0);
}

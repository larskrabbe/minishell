/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:44:54 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 09:31:59 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	final_execve(t_exe_data *exe_data, \
t_env **env_lst)
{
	struct stat		info;

	stat(exe_data->path, &info);
	if (!(info.st_mode & S_IXUSR))
		printf("%s: %s: Permission denied\n", \
		IDLE_PROMT, exe_data->path);
	else if ((info.st_mode & S_IFDIR))
		printf("%s: %s: is a directory\n", IDLE_PROMT, exe_data->path);
	else if (execve(exe_data->path, exe_data->argv, \
		env_as_string(env_lst)) == -1)
		printf("execve failed %s\n", exe_data->path);
}

int	execution_forking(t_exe_data *exe_data, \
t_env **env_lst, int built_in_flag, t_redirection *redirection)
{
	pid_t			pid;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGQUIT, signalhandler_ctrlslash);
		signal(SIGINT, signalhandler_ctrlc);
		changing_fd_in_out(exe_data);
		if (built_in_flag == TRUE)
			handle_builtin(exe_data->argv[0], &exe_data->argv[1], env_lst);
		else
			final_execve(exe_data, env_lst);
		clean_exit(redirection, env_lst);
	}
	redirection->last_pid = pid;
	exe_data->pid = pid;
	return (0);
}

void	execution_loop(t_exe_data *exe_data, t_env **env_lst, \
t_redirection *redirection, int *built_in_flag)
{
	if (pipe_start(exe_data, redirection) != 0)
		printf("error in pipe_start\n");
	*built_in_flag = cmd_is_builtin(exe_data->argv[0]);
	if (*built_in_flag == FALSE)
	{
		exe_data->path = get_cmd_path(env_lst, exe_data->argv[0]);
		if (exe_data->path == NULL)
			printf("<minishell>: %s: No such file or directory\n", \
			exe_data->argv[0]);
	}
	if (exe_data->path != NULL || *built_in_flag == TRUE)
		execution_forking(exe_data, env_lst, *built_in_flag, redirection);
	close_files_and_pipes(exe_data, redirection);
}

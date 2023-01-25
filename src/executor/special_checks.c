/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 00:55:46 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/25 20:21:22 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	execution(t_exe_data *exe_data, t_env *env_lst, \
t_redirection *redirection)
{
	int	built_in_flag;

	built_in_flag = FALSE;
	g_signal = 1;
	if (cmd_is_builtin(exe_data->argv[0]) && exe_data->next == NULL)
	{
		if (pipe_start(exe_data, redirection) != 0)
			printf("error in pipe_start\n");
		redirection->exit_code = handle_builtin(exe_data->argv[0], \
		&exe_data->argv[1], &env_lst);
		pipe_end(exe_data);
		return (0);
	}
	while (exe_data != NULL && exe_data->argv[0] != NULL)
	{
		execution_loop(exe_data, env_lst, redirection, &built_in_flag);
		exe_data = next_t_exe_data(exe_data);
	}
	return (0);
}

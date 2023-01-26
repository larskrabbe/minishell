/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:59:57 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/26 13:01:30 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	free_t_exe_data(exe_data);
	free(exe_data);
	return (tmp);
}

void	free_all_t_exe_data(t_exe_data *ptr)
{
	while (ptr != NULL)
		ptr = next_t_exe_data(ptr);
}

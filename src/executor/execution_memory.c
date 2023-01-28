/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:59:57 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 00:11:46 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
}

void	free_t_exe_data(t_exe_data *ptr)
{
	free_char_array(ptr->argv);
	if (ptr->path != NULL)
		free(ptr->path);
	ptr->path = NULL;
}

t_exe_data	*next_t_exe_data(t_exe_data *exe_data)
{
	t_exe_data	*tmp;

	tmp = exe_data->next;
	exe_data->next = NULL;
	free_t_exe_data(exe_data);
	free(exe_data);
	return (tmp);
}

	// printf("pid %i\n",getpid());
void	free_all_t_exe_data(t_exe_data *ptr)
{
	while (ptr != NULL)
		ptr = next_t_exe_data(ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:01:07 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/03 18:43:41 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	ft_export_print(t_env *env_lst)
{
	t_env	*env_curr;

	env_curr = env_lst;
	if (!env_lst)
	{
		printf("%s", NULL);
		return ;
	}
	while (env_curr)
	{
		if (!env_curr->value)
			printf("declare -x %s=\"%s\"\n", env_curr->name, "");
		else
			printf("declare -x %s=\"%s\"\n", env_curr->name, env_curr->value);
		env_curr = env_curr->next;
	}
}

int	ft_export(t_env **env_lst, char **new_env)
{
	int	error;

	error = FALSE;
	if (!env_lst)
		return (error_allocation);
	if (!new_env)
		ft_export_print(*env_lst);
	else
	{
		while (*new_env)
		{
			if (!env_id_isvalid(*new_env))
				error = TRUE;
			else
				ft_setenv(*env_lst, *new_env);
			new_env++;
		}
	}
	if (error)
		return (error_syntax);
	return (no_error);
}

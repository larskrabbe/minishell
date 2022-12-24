/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:01:07 by bogunlan          #+#    #+#             */
/*   Updated: 2022/12/23 18:03:55 by bogunlan         ###   ########.fr       */
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
			printf("declare -x %s=%s\n", env_curr->name, "");
		else
			printf("declare -x %s=%s\n", env_curr->name, env_curr->value);
		env_curr = env_curr->next;
	}
}

int	ft_export(t_env **env_lst, char *new_env)
{
	if (!new_env)
		ft_export_print(*env_lst);
	else
		if (!ft_setenv(*env_lst, new_env))
			return (0);
	return (1);
}

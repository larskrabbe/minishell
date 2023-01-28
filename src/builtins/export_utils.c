/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:25:10 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 12:25:28 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	export_error_mssg(char *new_env)
{
	printf("export: `%s': not a valid identifier \n", new_env);
}

int	valid_first_char(char *new_env)
{
	if (*(new_env) == '=')
	{
		export_error_mssg(new_env);
		return (FALSE);
	}
	return (TRUE);
}

int	valid_last_char(char *new_env)
{
	if (*(new_env) == '+')
		return (TRUE);
	return (FALSE);
}

void	ft_export_print(t_env *env_lst)
{
	t_env	*env_curr;

	if (env_lst == NULL)
		return ;
	env_curr = env_lst;
	if (!env_lst)
	{
		printf("NULL\n");
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

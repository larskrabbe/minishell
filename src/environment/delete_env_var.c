/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:11:29 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/26 14:42:41 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	free_env(t_env *env_node)
{
	if (env_node)
	{
		free(env_node->name);
		free(env_node->value);
		free(env_node);
	}
}

int	unset_first_env(t_env **env_lst, char *name)
{
	t_env	*env_prev;

	if (find_env_match(*env_lst, name))
	{
		env_prev = *env_lst;
		printf("%s\n", (*env_lst)->next->name);
		*env_lst = (*env_lst)->next;
		free_env(env_prev);
		env_prev = NULL;
		return (TRUE);
	}
	return (FALSE);
}

void	ft_unsetenv_helper(t_env *env_curr, t_env *env_prev, char *name)
{
	while (env_curr)
	{
		if (find_env_match(env_curr, name))
		{
			env_prev->next = env_curr->next;
			free_env(env_curr);
			env_curr = NULL;
			env_curr = env_prev->next;
			env_prev = env_curr;
		}
		else
		{
			env_prev = env_curr;
			env_curr = env_curr->next;
		}
	}
}

void	ft_unsetenv(t_env **env_lst, char *name)
{
	t_env	*env_curr;
	t_env	*env_prev;

	printf("Before unsetting\n");
	printf("%p\n", *env_lst);
	if (!(*env_lst) || !name)
		return ;
	if (unset_first_env(env_lst, name))
	{
		printf("After unsetting\n");
		printf("%p\n", *env_lst);
		// *env_lst = NULL;
		return ;
	}
	printf("afte loop\n");
	env_curr = *env_lst;
	env_prev = env_curr;
	*env_lst = env_prev;
	ft_unsetenv_helper(env_curr, env_prev, name);
}

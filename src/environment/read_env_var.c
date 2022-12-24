/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:10:28 by bogunlan          #+#    #+#             */
/*   Updated: 2022/12/22 10:00:37 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	ft_printenv(t_env *env_lst)
{
	t_env	*env_curr;

	env_curr = env_lst;
	if (!env_lst)
	{
		printf("%s", "No enviroment");
		return ;
	}
	while (env_curr)
	{
		printf("%s=%s\n", env_curr->name, env_curr->value);
		env_curr = env_curr->next;
	}
}

int	find_env_match(t_env *env_lst, char *name)
{
	t_env	*env_curr;

	env_curr = env_lst;
	if (!ft_strncmp(env_curr->name, name, ft_strlen(env_curr->name)))
	{
		if (!ft_strncmp(env_curr->name, name, ft_strlen(name)))
		{
			printf("Match: %s\n", env_curr->name);
			return (1);
		}
	}
	return (0);
}

t_env	*ft_getenv_lst(char **envp)
{
	t_env	*env_new;
	t_env	*env_lst;

	env_lst = NULL;
	if (!(*envp))
		return (NULL);
	while (*envp)
	{
		env_new = env_lstnew(*envp);
		env_add_back(&env_lst, env_new);
		envp++;
	}
	return (env_lst);
}

char *ft_getenv(t_env *env_lst, char *name)
{
	t_env	*env_curr;

	env_curr = env_lst;
	while (env_curr)
	{
		if (find_env_match(env_curr, name))
			return (env_curr->value);
		env_curr = env_curr->next;
	}
	return (NULL);
}
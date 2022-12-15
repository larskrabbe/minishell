/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:10:37 by bogunlan          #+#    #+#             */
/*   Updated: 2022/12/15 19:58:52 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	ft_putenv(t_env *env_list, char *name, char *value)
{
	t_env	*env_new;
	char	*content;

	if (!env_list || !name || !value)
		return ;
	content = ft_strjoin(name, "=");
	content = ft_strjoin(content, value);
	env_new = env_lstnew(content);
	env_add_back(&env_list, env_new);
}

void	ft_setenv(t_env *env_lst, char *new_env)
{
	t_env	*env_curr;
	char	*name;
	char	*value;
	char	**split;

	env_curr = env_lst;
	split = ft_slice(new_env, '=');
	if (!env_lst || !split)
		return ;
	name = split[0];
	value = split[1];
	while (env_curr)
	{
		if (find_env_match(env_curr, name))
		{
			printf("Match found\n");
			env_curr->value = value;
			free(split);
			return ;
		}
		env_curr = env_curr->next;
	}
	printf("No Match found\n");
	ft_putenv(env_lst, name, value);
	free(split);
}

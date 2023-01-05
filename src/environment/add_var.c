/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:10:37 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/04 19:21:23 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	ft_putenv(t_env *env_lst, char *name, char *value)
{
	t_env	*env_new;
	char	*content;
	char	*tmp;

	if (!env_lst || !name || !value)
		return ;
	tmp = ft_strjoin(name, "=");
	content = ft_strjoin(tmp, value);
	free(tmp);
	env_new = env_lstnew(content);
	free(content);
	env_add_back(&env_lst, env_new);
}

int	env_var_maker(t_setenv *setter, t_env *env_lst, char *new_env_var)
{
	setter->split = ft_slice(new_env_var, '=');
	if (!env_lst || !setter->split)
		return (FALSE);
	setter->name = setter->split[0];
	setter->value = setter->split[1];
	free(setter->split);
	return (TRUE);
}

int	env_var_exists(t_env *env_lst, char *name, char *value)
{
	while (env_lst)
	{
		if (find_env_match(env_lst, name))
		{
			// printf("Match found\n");
			free(env_lst->value);
			free(env_lst->name);
			env_lst->value = value;
			env_lst->name = name;
			return (TRUE);
		}
		env_lst = env_lst->next;
	}
	return (FALSE);
}

int	ft_setenv(t_env *env_lst, char *new_env_var)
{
	t_setenv	setter;

	setter.env_curr = env_lst;
	setter.split = NULL;
	if (!env_var_maker(&setter, env_lst, new_env_var))
		return (FALSE);
	if (env_var_exists(setter.env_curr, setter.name, setter.value))
		return (TRUE);
	ft_putenv(env_lst, setter.name, setter.value);
	free(setter.name);
	free(setter.value);
	return (TRUE);
}

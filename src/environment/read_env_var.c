/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:10:28 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/28 20:17:08 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	ft_printenv(t_env *env_lst)
{
	t_env	*env_curr;

	if (env_lst == NULL)
		return ;
	env_curr = env_lst;
	if (!env_lst)
	{
		return ;
	}
	while (env_curr)
	{
		if (env_curr->value && *(env_curr->value) != '\0')
			printf("%s=%s\n", env_curr->name, env_curr->value);
		env_curr = env_curr->next;
	}
}

int	find_env_match(t_env *env_lst, char *name)
{
	t_env	*env_curr;

	env_curr = env_lst;
	if (env_lst == NULL)
		return (FALSE);
	if (!ft_strncmp(env_curr->name, name, ft_strlen(env_curr->name)))
	{
		if (!ft_strncmp(env_curr->name, name, ft_strlen(name)))
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

int	oldpwd_present(t_env *env_new)
{
	t_env	*env_curr;

	env_curr = env_new;
	if (!ft_strncmp(env_curr->name, "OLDPWD", ft_strlen(env_curr->name)))
	{
		if (!ft_strncmp("OLDPWD", env_curr->name, 6))
			return (TRUE);
	}
	return (FALSE);
}

t_env	**ft_getenv_lst(char **envp)
{
	t_env			*env_new;
	static t_env	*env_lst = NULL;
	int				oldpwd;

	env_new = NULL;
	if (envp == NULL || *envp == NULL)
	{
		env_lst = no_env_case(env_new);
		return (&env_lst);
	}
	while (*envp)
	{
		env_new = env_lstnew(*envp);
		env_add_back(&env_lst, env_new);
		oldpwd = oldpwd_present(env_new);
		envp++;
	}
	if (!oldpwd)
		ft_setenv(env_lst, "OLDPWD");
	return (&env_lst);
}

char	*ft_getenv(t_env *env_lst, char *name)
{
	t_env	*env_curr;

	env_curr = env_lst;
	if (name)
	{
		while (env_curr)
		{
			if (find_env_match(env_curr, name))
			{
				return (env_curr->value);
			}
			env_curr = env_curr->next;
		}
	}
	return (NULL);
}

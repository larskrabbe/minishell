/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:11:02 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/28 02:25:15 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

t_env	*env_lstnew(char *content)
{
	t_env	*new;
	char	**split;

	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	split = ft_slice(content, '=');
	if (!split)
		return (NULL);
	new->name = split[0];
	if (!ft_strncmp("OLDPWD", new->name, 6))
	{
		if (!ft_strncmp("OLDPWD", new->name, ft_strlen(new->name)))
		{
			free(split[1]);
			new->value = NULL;
		}
	}
	else
		new->value = split[1];
	new->next = NULL;
	free(split);
	return (new);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*curr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}

t_env	*no_env_case(t_env *env_new)
{
	char	cwd[MAX_ARG];
	char	*pwd;
	t_env	*env_lst;

	getcwd(cwd, sizeof(cwd));
	pwd = ft_strjoin("PWD=", cwd);
	env_new = env_lstnew(pwd);
	env_add_back(&env_lst, env_new);
	ft_setenv(env_lst, "OLDPWD");
	free (pwd);
	return (env_lst);
}

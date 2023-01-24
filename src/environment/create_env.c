/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:11:02 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/21 20:51:13 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

t_env	*env_lstnew(char *content)
{
	t_env	*new;
	char	**split;

	new = (t_env *)malloc(sizeof(t_env));
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

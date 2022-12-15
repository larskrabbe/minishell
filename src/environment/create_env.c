/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:11:02 by bogunlan          #+#    #+#             */
/*   Updated: 2022/12/15 19:52:24 by bogunlan         ###   ########.fr       */
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
	split = ft_split(content, '=');
	new->name = split[0];
	new->value = split[1];
	new->next = NULL;
	free(split);
	return (new);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env *curr;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:36:05 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:03:30 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*last_lst;
	t_list	*start_lst;

	if (lst == NULL)
	{
		return (NULL);
	}
	last_lst = ft_lstnew(f(lst->content));
	start_lst = last_lst;
	lst = lst->next;
	while (lst != NULL)
	{
		last_lst = ft_lstnew(f(lst->content));
		if (last_lst->content)
			ft_lstadd_back(&start_lst, last_lst);
		else
			ft_lstdelone(last_lst, del);
		lst = lst->next;
	}
	last_lst = NULL;
	return (start_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:34:35 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:03:16 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp_lst;
	t_list	*lst_nxt;

	tmp_lst = *lst;
	while (tmp_lst != NULL)
	{
		lst_nxt = tmp_lst->next;
		ft_lstdelone(tmp_lst, del);
		tmp_lst = lst_nxt;
	}
	*lst = NULL;
}

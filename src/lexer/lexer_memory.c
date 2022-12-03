/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:29:10 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 19:39:15 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"lexer.h"

/**
 * @brief allocate memory for the tokens
 * 
 * @return the pointer to the tokenchain_head
 */
t_tokenchain	*tokenchain_create(void)
{
	t_tokenchain	*head;

	head = ft_calloc(sizeof(t_tokenchain), 1);
	if (head == NULL)
		return (NULL);
	head->token = ft_calloc(sizeof(t_tokenchain), ARG_MAX);
	if (head->token == NULL)
	{
		free(head);
		return (NULL);
	}
	return (head);
}

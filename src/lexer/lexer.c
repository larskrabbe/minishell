/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:50:17 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 16:44:06 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"lexer.h"

int	lexer(char *str, t_tokenchain *tokenchain)
{
	int	i;

	i = 0;
	tokenchain->str = str;
	while (str[i] != '\0')
	{
		if (is_whitespace(str[i]) != 0)
		{
			
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:44:10 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:02:00 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

void	*ft_memchr(const void *str, int chr, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)str;
	if (!len)
		return (NULL);
	while (len)
	{
		if (*temp == (unsigned char)chr)
			return (temp);
		temp++;
		len--;
	}
	return (NULL);
}

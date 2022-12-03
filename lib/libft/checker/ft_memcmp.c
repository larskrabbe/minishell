/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:34:07 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:02:05 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

int	ft_memcmp( const void *ptr1, const void *ptr2, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)ptr1;
	str2 = (unsigned char *)ptr2;
	while (len && *str1 == *str2)
	{
		len--;
		str1++;
		str2++;
	}
	if (len == 0)
		return (0);
	return (*str1 - *str2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:15:51 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:03:58 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

static void	backwards(void *dest, const void *src, size_t n)
{
	char	*dest2;
	char	*src2;

	dest2 = (char *)dest + n -1;
	src2 = (char *)src + n - 1;
	while (n)
	{
		*dest2 = *src2;
		dest2--;
		src2--;
		n--;
	}
}

static void	forwards(void *dest, const void *src, size_t n)
{
	char	*dest2;
	char	*src2;

	dest2 = (char *)dest;
	src2 = (char *)src;
	while (n)
	{
		*dest2 = *src2;
		dest2++;
		src2++;
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == src || !n)
		return (dest);
	else if (dest < src)
		forwards(dest, src, n);
	else
		backwards(dest, src, n);
	return (dest);
}

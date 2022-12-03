/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:09:17 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:04:19 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] && size > i)
		i++;
	if (i == size)
		return (i + ft_strlen(src));
	while (src[j] != '\0' && (size - 1) > j + i)
	{
		dst[j + i] = src[j];
		j++;
	}
	dst[j + i] = '\0';
	return (i + ft_strlen(src));
}

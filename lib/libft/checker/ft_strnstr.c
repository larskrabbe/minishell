/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:48:34 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:02:20 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	p1;
	int	p2;

	p1 = 0;
	p2 = 0;
	if (needle[0] == '\0')
		return ((char *)(haystack));
	while (haystack[p1] != '\0' && len > (size_t)p1)
	{	
		p2 = 0;
		while (haystack[p1 + p2] == needle[p2] && (size_t)(p1 + p2) < len)
		{
			if (needle[p2 + 1] == '\0')
				return ((char *)(haystack + p1));
			p2++;
		}
		p1++;
	}
	return (NULL);
}

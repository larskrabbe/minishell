/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:15:14 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:02:24 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

char	*ft_strrchr(const char *string, int letter)
{	
	int				i;
	int				lastc;
	unsigned char	*str;
	unsigned char	c;

	str = (unsigned char *)string;
	c = (unsigned char) letter;
	lastc = 0;
	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == c)
			lastc = i;
	}
	if (c != str[lastc])
		return (NULL);
	return ((char *)(str + lastc));
}

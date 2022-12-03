/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:10:13 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:02:08 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

char	*ft_strchr(const char *string, int letter)
{	
	unsigned char	*str;
	unsigned char	c;

	str = (unsigned char *)string;
	c = (unsigned char) letter;
	while (*str != '\0' && *str != c)
		str++;
	if (c != *str)
		return (NULL);
	return ((char *)str);
}

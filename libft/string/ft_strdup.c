/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:36:21 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:04:09 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*ptr;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	ptr = (char *) malloc(len + 1 * sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
		ptr[i] = '\0';
	return (ptr);
}

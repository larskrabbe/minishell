/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:21:22 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:04:16 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		max_len;
	char	*copy;
	int		i1;
	int		i2;

	i1 = 0;
	i2 = 0;
	if (s1 == NULL || s2 == NULL )
		return (NULL);
	max_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	copy = malloc(sizeof(char) * max_len);
	if (copy == NULL)
		return (NULL);
	while (s1[i1] != '\0')
	{
		copy[i1] = s1[i1];
		i1++;
	}
	while (s2[i2] != '\0')
	{
		copy[i1 + i2] = s2[i2];
		i2++;
	}
	copy[i1 + i2] = '\0';
	return (copy);
}

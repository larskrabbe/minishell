/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:09:39 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:04:33 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t max_len)
{
	char	*copy;
	size_t	copy_length;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	copy_length = ft_strlen(s) - start;
	if (max_len < copy_length)
		copy_length = max_len;
	copy = malloc(sizeof(char) * (copy_length + 1));
	if (copy == NULL)
		return (NULL);
	while (i < copy_length)
	{
		copy[i] = s[i + start];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

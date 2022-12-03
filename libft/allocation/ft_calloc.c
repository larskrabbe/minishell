/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:22:39 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/27 17:35:23 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
		return (ft_strdup(""));
	if (18446744073709551615UL / size < count)
		return (NULL);
	ptr = malloc(size * count);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, (size * count));
	return (ptr);
}

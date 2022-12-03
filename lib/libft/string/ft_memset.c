/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:51:57 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:04:01 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int		count;
	char	*ptr;

	ptr = (char *)s;
	count = 0;
	while (n > 0)
	{
		ptr[count] = c;
		count++;
		n--;
	}
	return (s);
}

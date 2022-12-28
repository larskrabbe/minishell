/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:07:46 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/27 19:37:00 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

size_t	ft_strlen(const char *string)
{
	int	count;

	count = 0;
	if (string == NULL)
		return (0);
	while (string[count] != '\0' )
		count++;
	return (count);
}

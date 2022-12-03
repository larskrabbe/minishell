/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:36:17 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/04/01 14:06:54 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp( const char *str1, const char *str2, int n )
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
	{
		if ((n - 1) == i)
			return (0);
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2 [i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:24:02 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:02:48 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	num;
	long int	len;

	num = n;
	len = 1;
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	if (num == 0)
		write(fd, "0", 1);
	while (num >= len)
	{
		len *= 10;
	}
	len = len / 10;
	while (len > 0)
	{
		ft_putchar_fd(((num / len) % 10 + '0'), fd);
		len /= 10;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:34:25 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/04/14 11:01:44 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	whitespace(const char *str)
{
	if (*str == ' ' || *str == '\n' || *str == '\t' )
		return (1);
	else if (*str == '\v' || *str == '\f' || *str == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long long int	num;
	int				sign;

	sign = 1;
	num = 0;
	while (whitespace(str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10;
		num = num + (*str - '0');
		str++;
		if ((sign * num) > 4294967295)
			return (-1);
		if ((sign * num) < -4294967295)
			return (0);
	}
	return (sign * num);
}

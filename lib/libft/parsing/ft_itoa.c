/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:59:44 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:03:46 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

static int	numlen(long num)
{
	int			len;
	long		max;
	long		tnum;

	tnum = num;
	len = 1;
	max = 10;
	if (tnum == 0)
		return (1);
	if (num < 0)
	{
		len++;
		num = num * -1;
	}
	while (num / max >= 1)
	{
		max = max * 10;
		len++;
	}
	return (len);
}

static char	num_in_int(long int num, int pos)
{
	long int	tnum;

	tnum = num;
	while (pos > 0)
	{
		tnum = tnum / 10;
		pos--;
	}
	tnum = tnum % 10;
	return (tnum + '0');
}

static char	*printtostr(char *str, long int tnum, int len)
{
	int	i;

	i = 0;
	if (tnum < 0)
	{
		tnum = tnum * -1;
		str[i] = '-';
		i++;
	}
	while (len >= i)
	{
		str[i] = num_in_int(tnum, (len - i - 1));
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_itoa(int num)
{
	char		*str;
	long int	tnum;
	int			len;

	if (num == 2147483647)
		return (ft_strdup("2147483647"));
	if (num == -2147483648)
		return (ft_strdup("-2147483648"));
	tnum = (long int)num;
	len = numlen(tnum);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	return (printtostr(str, tnum, len));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:44:27 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:02:35 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

//import the flags into a struct and return a pointer 
static char	*fill_flags(char *str, struct s_arg *input)
{
	set_default(input);
	while (ft_strchr("#+ -0",*str))
	{
		if (*str == '#')
			input->hash = '#';
		else if (*str == '-')
			input->side = 'r';
		else if ((*str == '+' || *str == ' ') && input->sign != '-')
			input->sign = *str;
		else if (*str == '0')
			input->wth_chr = '0';
		str++;
	}
	return (str);
}

//convert a numbers until
static char	*quick_convert(char *str, int *nbr, va_list va_ptr)
{
	char	num[32];
	int		i;

		i = 0;
	if (*str == '*')
	{
		*nbr = va_arg(va_ptr, int);
		str++;
		return (str);
	}
	while (ft_isdigit(*str))
	{
		num[i] = *str;
		i++;
		str++;
	}
		num[i] = '\0';
		*nbr = ft_atoi(num);
	return (str);
}

char	*fill_list(char *str, struct s_arg *input, va_list va_ptr)
{
	str++;
	str = fill_flags(str, input);
	if (ft_isdigit(*str) || *str == '*')
		str = quick_convert(str, &input->width, va_ptr);
	if (input->width < 0)
	{
		input->width *= -1;
		input->side = 'r';
	}
	if (input->side == 'r' && input->wth_chr == '0')
		input->wth_chr = ' ';
	if (*str == '.')
	{
		str++;
		if (ft_isdigit(*str) || *str == '*')
			str = quick_convert(str++, &input->precision, va_ptr);
		else
			input->precision = 0;
		if (input->precision < -1)
			input->precision = -2;
	}
	input->dta_typ = *str;
	return (str);
}

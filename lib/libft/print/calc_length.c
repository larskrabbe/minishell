/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:25:16 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:02:28 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

// calculate the length of the str inputstring with precision in mind
void	f_str_len(struct s_arg *input)
{
	input->max_len = ft_strlen(input->dta_str);
	if (input->max_len > input->precision && input->precision > -1)
		input->max_len = input->precision;
	input->precision = -1;
	input->dta_len = input->max_len;
}

// calculate the length of the number inputstring with precision in mind
void	f_c_len(struct s_arg *input)
{
	input->max_len = 1;
	if (input->max_len > input->precision && input->precision != -1)
		input->max_len = input->precision;
	input->dta_len = input->max_len;
}

// calculate the length of the number inputstring with precision in mind
void	f_int_len(struct s_arg *input)
{
	if (input->precision < input->width && input->precision != -1)
		input->wth_chr = ' ';
	if (input->precision == 0 && input->num[0] == '0')
		input->max_len = 0;
	else
	{
		input->max_len += ft_strlen(input->dta_str);
		input->dta_len = input->max_len;
		if (input->max_len < input->precision)
			input->max_len = input->precision;
		if (input->precision != -1)
			input->wth_chr = ' ';
		input->precision -= input->dta_len;
	}
}

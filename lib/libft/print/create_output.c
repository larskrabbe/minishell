/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:52:25 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:02:32 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

//create a empty string in the size of what should be printed in the end
void	create_str( t_arg *input, t_type *type)
{	
	type->f_len(input);
	if (input->sign == ' ' || input->sign == '+' || input->sign == '-')
		input->max_len++;
	if (input->hash == '#')
		input->max_len += type->hash_len;
	input->max_len += type->fix_len;
	input->width -= input->max_len;
	if (input->width > 0)
		input->max_len += input->width;
	input->out_str = (char *)ft_calloc(sizeof(char), (input->max_len + 1));
}

// fills n times character at the end of a string.
char	*my_strlchr(char *dst, const char c, int n)
{
	if (n == 0)
		return (dst);
	while (n > 0)
	{
		*dst = c;
		dst++;
		n--;
	}
	return (dst);
}

//ads a string at the on a string | n times
char	*my_strlstr(char *dst, const char *str, int max)
{
	char	*tmp_str;

	tmp_str = (char *)str;
	while (max > 0)
	{
		*dst = *tmp_str;
		dst++;
		tmp_str++;
		max--;
	}
	return (dst);
}

// fill a string with data from a struct 
void	fill_str( t_arg *input, t_type *type)
{
	char	*tmp_out;

	tmp_out = input->out_str;
	if (input->side == 'l' && input->width > 0 && input->wth_chr == ' ')
		tmp_out = my_strlchr(tmp_out, input->wth_chr, input->width);
	if (input->sign == '-' || input->sign == '+' || input->sign == ' ')
		tmp_out = my_strlchr(tmp_out, input->sign, 1);
	if (input->side == 'l' && input->width > 0 && input->wth_chr == '0')
		tmp_out = my_strlchr(tmp_out, input->wth_chr, input->width);
	if (input->hash == '#')
		tmp_out = my_strlstr(tmp_out, type->hash_str, type->hash_len);
	tmp_out = my_strlchr(tmp_out, '0', input->precision);
	tmp_out = my_strlstr(tmp_out, type->fix_str, type->fix_len);
	tmp_out = my_strlstr(tmp_out, input->dta_str, input->dta_len);
	if (input->side == 'r' && input->width > 0)
		tmp_out = my_strlchr(tmp_out, input->wth_chr, input->width);
}

//Set the flag_structure t o default
void	set_default(t_arg *input)
{
	input->dta_typ = 0;
	input->dta_str = NULL;
	input->dta_len = 0;
	input->width = 0;
	input->wth_chr = ' ';
	input->precision = -1;
	input->sign = 0;
	input->side = 'l';
	input->hash = 0;
	input->out_str = NULL;
	input->max_len = 0;
	input->output = 0;
	ft_bzero((void *)input->num, 64);
}

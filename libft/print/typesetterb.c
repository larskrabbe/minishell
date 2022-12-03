/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typesetterb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:42:37 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/09/02 13:06:01 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

//sets values for unsignd numbers
void	f_setter_u(t_type *type, va_list va_ptr)
{
	type->cast = va_arg(va_ptr, unsigned);
	type->hash_len = 0;
	type->base = 10;
	type->base_str = g_char_str;
	type->fix_str = "";
	type->f_len = &f_int_len;
	type->fix_len = 0;
}

//sets values for decimal and int number
void	f_setter_i(t_type *type, t_arg *input, va_list va_ptr)
{
	long	tmp;
	int		i;

	i = va_arg(va_ptr, int);
	tmp = (long)i;
	if (tmp < 0)
	{
		tmp = tmp * -1;
		input->sign = '-';
	}
	type->cast = tmp;
	type->hash_len = 0;
	type->base = 10;
	type->base_str = g_char_str;
	type->fix_str = "";
	type->f_len = &f_int_len;
	type->fix_len = 0;
}

//set values for hexnumbers
void	f_setter_x(t_type *type, va_list va_ptr, char dta_typ)
{
	type->cast = va_arg(va_ptr, unsigned);
	type->base = 16;
	if (type->cast == 0)
		type->hash_len = 0;
	else
		type->hash_len = 2;
	type->f_len = &f_int_len;
	type->fix_str = "";
	type->fix_len = 0;
	if (dta_typ == 'X')
	{
		type->base_str = g_char_str_c;
		type->hash_str = g_hash_c;
	}
	else
	{
		type->base_str = g_char_str;
		type->hash_str = g_hash;
	}
}

//sets values for pointer
void	f_setter_p(t_type *type, va_list va_ptr)
{
	void	*tmp;

	tmp = va_arg(va_ptr, void *);
	type->cast = (size_t) tmp;
	type->hash_len = 0;
	type->base = 16;
	type->base_str = g_char_str;
	type->f_len = &f_int_len;
	type->fix_str = g_hash;
	type->fix_len = 2;
}

//sets values for octal
void	f_setter_o(t_type *type, va_list va_ptr)
{
	long	tmp;

	tmp = va_arg(va_ptr, unsigned);
	type->cast = tmp;
	type->hash_str = g_char_str;
	type->hash_len = 1;
	type->base = 8;
	type->base_str = g_hash;
	type->fix_str = "";
	type->f_len = &f_int_len;
	type->fix_len = 0;
}

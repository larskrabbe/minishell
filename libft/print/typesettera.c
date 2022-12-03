/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typesettera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:14:03 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:05:14 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

//sets values for strings
void	f_setter_s(t_type *type, t_arg *input)
{
	type->hash_len = 0;
	type->f_len = &f_str_len;
	type->fix_str = "";
	type->fix_len = 0;
	input->sign = 0;
}

//sets values for chars
void	f_setter_c(t_type *type)
{
	type->hash_len = 0;
	type->f_len = &f_c_len;
	type->fix_str = "";
	type->fix_len = 0;
}

//select the type of fuktion depending on the type
void	setter_setter(t_arg *input, t_type *type, va_list va_ptr)
{
	if (input->dta_typ == 'c' || input->dta_typ == '%')
		f_setter_c(type);
	else if (input->dta_typ == 's')
		f_setter_s(type, input);
	else if (input->dta_typ == 'd' || input->dta_typ == 'i')
		f_setter_i(type, input, va_ptr);
	else if (input->dta_typ == 'x' || input->dta_typ == 'X')
		f_setter_x(type, va_ptr, input->dta_typ);
	else if (input->dta_typ == 'p')
		f_setter_p(type, va_ptr);
	else if (input->dta_typ == 'u')
		f_setter_u(type, va_ptr);
	else if (input->dta_typ == 'o')
		f_setter_o(type, va_ptr);
}

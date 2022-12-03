/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:12:23 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:02:37 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

//give the lenght to next % or \0
int	lenght_to_pcnt(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '%')
		len++;
	return (len);
}

//prints n letters of a string and returns pointer+n
char	*print(t_arg *input, char *str, int n)
{
	input->total_length += write(1, str, n);
	return ((str + n));
}

//create the base string depending on type
void	create_base_str(t_arg *input, t_type *type, va_list va_ptr)
{
	if (input->dta_typ == 's')
	{
		input->dta_str = va_arg(va_ptr, char *);
		if (input->dta_str == NULL)
			input->dta_str = (char *)g_null;
	}
	else if (input->dta_typ == 'c')
	{
		input->num[0] = va_arg(va_ptr, int);
		input->dta_str = input->num;
	}
	else if (input->dta_typ == '%' )
	{
		input->num[0] = '%';
		input->dta_str = input->num;
	}
	else
		convert_num_to_str(input, type);
	create_str(input, type);
}

// print the string of char from"" or the data stores
int	ft_printf(const char *str, ...)
{
	va_list			va_ptr;
	char			*tmp_str;
	t_arg			input;
	t_type			type;

	input.total_length = 0;
	tmp_str = (char *)str;
	va_start(va_ptr, str);
	while (*tmp_str != '\0')
	{
		if (*tmp_str == '%')
		{
			tmp_str = fill_list(tmp_str++, &input, va_ptr);
			setter_setter(&input, &type, va_ptr);
			create_base_str(&input, &type, va_ptr);
			fill_str(&input, &type);
			print(&input, input.out_str, input.max_len);
			free(input.out_str);
			tmp_str++;
		}
		else
			tmp_str = print(&input, (tmp_str), lenght_to_pcnt(tmp_str));
	}
	va_end(va_ptr);
	return (input.total_length);
}

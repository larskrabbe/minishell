/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:59:49 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:05:18 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

//recursive funktion that copy a num from the first position to the last
int	recur_base(size_t num, t_type *type, char buffer[64], int i)
{	
	if (num >= (size_t)type->base)
		i = recur_base(num / type->base, type, buffer, i);
	buffer[i] = type->base_str[num % type->base];
	i++;
	return (i);
}

//convert a number(base 10) in a string of the number but the base is not set
void	convert_num_to_str(t_arg *input, t_type *type)
{
	size_t	tnum;

	tnum = type->cast;
	input->dta_str = input->num;
	if (type->base <= 1 || type->base > 36)
		return ;
	input->num[recur_base(tnum, type, input->num, 0)] = '\0';
}

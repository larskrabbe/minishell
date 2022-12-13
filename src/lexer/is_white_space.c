/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_white_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:23:33 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/13 16:02:42 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	is_white_space(int a)
{
	if (a == ' ' || a == '\n' || a == '\t')
		return (1);
	if (a == '\f' || a == '\r' || a == '\v')
		return (1);
	return (0);
}

int	is_special_char(char a)
{
	if (a == '>')
		return (type_redirection);
	if (a == '<')
		return (type_input_file);
	if (a == '|')
		return (type_pipe);
	return (0);
}

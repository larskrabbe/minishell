/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:25:10 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/24 23:42:48 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	export_error_mssg(char *new_env)
{
	printf("export: `%s': not a valid identifier \n", new_env);
}

int	valid_first_char(char *new_env)
{
	if (*(new_env) == '=')
	{
		export_error_mssg(new_env);
		return (FALSE);
	}
	return (TRUE);
}

int	valid_last_char(char *new_env)
{
	if (*(new_env) == '+')
		return (TRUE);
	return (FALSE);
}

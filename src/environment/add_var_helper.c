/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:09:02 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/03 16:42:31 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_error_mssg(char *new_env)
{
	printf("export: not a valid identifier %s\n", new_env);
}

int	invalid_env_id(char *new_env)
{
	int	j;
	int	tmp;
	int	error;

	j = 0;
	tmp = 0;
	error = FALSE;
	while (tmp == 0 && (*(new_env + j))
	)
	{
		if (((*(new_env + j)) >= 33 && (*(new_env + j)) <= 47)
			|| ((*(new_env + j)) >= 58 && (*(new_env + j)) <= 60)
			|| ((*(new_env + j)) >= 62 && (*(new_env + j)) <= 64)
			|| ((*(new_env + j)) >= 91 && (*(new_env + j)) <= 94)
			|| ((*(new_env + j)) >= 123 && (*(new_env + j)) <= 127))
		{					
			export_error_mssg(new_env);
			error = TRUE;
			tmp = 1;
		}
		j++;
	}
	return (error);
}

int	env_id_isvalid(char *new_env)
{
	if (ft_isdigit(*new_env))
	{
		export_error_mssg(new_env);
		return (FALSE);
	}
	else if (invalid_env_id(new_env))
		return (FALSE);
	return (TRUE);
}
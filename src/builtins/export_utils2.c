/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:06:38 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/28 14:06:58 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	invalid_env_id_helper(char *new_env, int *j, int *error, int *tmp)
{
	if (((*(new_env + *j)) >= 32 && (*(new_env + *j)) <= 47)
		|| ((*(new_env + *j)) >= 58 && (*(new_env + *j)) <= 60)
		|| ((*(new_env + *j)) >= 62 && (*(new_env + *j)) <= 64)
		|| ((*(new_env + *j)) >= 91 && (*(new_env + *j)) <= 94)
		|| ((*(new_env + *j)) >= 123 && (*(new_env + *j)) <= 127))
	{					
		export_error_mssg(new_env);
		*error = TRUE;
		*tmp = 1;
	}
	return (*error);
}

int	invalid_env_id(char *new_env)
{
	int	j;
	int	tmp;
	int	error;

	j = 0;
	tmp = 0;
	error = FALSE;
	if (!valid_first_char(new_env))
		return (TRUE);
	while (tmp == 0 && (new_env[j]) && (new_env[j] != '=')
	)
	{
		if (new_env[j + 1] && *(new_env + j + 1) == '=')
		{
			if (valid_last_char(new_env + j))
				break ;
		}
		if (invalid_env_id_helper(new_env, &j, &error, &tmp))
			break ;
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

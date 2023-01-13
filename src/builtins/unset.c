/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:35:10 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/13 21:11:34 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_error(char *env_name)
{
	printf("unset `%s': not a valid identifier\n", env_name);
}

int	check_invalid_char(char *env_name)
{
	int	j;
	int	tmp;
	int	error;

	j = 0;
	tmp = 0;
	error = FALSE;
	while (tmp == 0 && (*(env_name + j))
	)
	{
		if (((*(env_name + j)) >= 32 && (*(env_name + j)) <= 47)
			|| ((*(env_name + j)) >= 58 && (*(env_name + j)) <= 64)
			|| ((*(env_name + j)) >= 91 && (*(env_name + j)) <= 94)
			|| ((*(env_name + j)) >= 123 && (*(env_name + j)) <= 127))
		{					
			unset_error(env_name);
			error = TRUE;
			tmp = 1;
		}
		j++;
	}
	return (error);
}

int	check_unset_args_name(char **env_name)
{
	int	i;
	int	error1;
	int	error2;

	error1 = FALSE;
	i = 0;
	while (env_name[i])
	{
		if (ft_isdigit(*env_name[i]))
		{
			unset_error(*(env_name + i));
			error1 = TRUE;
		}
		else
			error2 = check_invalid_char((env_name[i]));
		i++;
	}
	return (error1 || error2);
}

int	ft_unset(t_env **env_lst, char **env_name)
{
	int	error;

	if (!env_lst || !env_name)
		return (error_allocation);
	error = check_unset_args_name(env_name);
	while (*env_name)
	{
		ft_unsetenv(env_lst, *env_name);
		env_name++;
	}
	if (error)
		return (error_syntax);
	return (no_error);
}

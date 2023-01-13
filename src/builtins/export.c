/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:01:07 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/13 21:16:49 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	export_error_mssg(char *new_env)
{
	printf("export: `%s': not a valid identifier \n", new_env);
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
		if (((*(new_env + j)) >= 32 && (*(new_env + j)) <= 47)
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

void	ft_export_print(t_env *env_lst)
{
	t_env	*env_curr;

	env_curr = env_lst;
	if (!env_lst)
	{
		printf("%s", NULL);
		return ;
	}
	while (env_curr)
	{
		if (!env_curr->value)
			printf("declare -x %s=\"%s\"\n", env_curr->name, "");
		else
			printf("declare -x %s=\"%s\"\n", env_curr->name, env_curr->value);
		env_curr = env_curr->next;
	}
}

int	ft_export(t_env **env_lst, char **new_env)
{
	int	error;

	error = FALSE;
	if (!env_lst)
		return (error_allocation);
	if (!new_env)
		ft_export_print(*env_lst);
	else
	{
		while (*new_env)
		{
			if (!env_id_isvalid(*new_env))
				error = TRUE;
			else
				if (!ft_setenv(*env_lst, *new_env))
					return (error_allocation);
			new_env++;
		}
	}
	if (error)
		return (error_syntax);
	return (no_error);
}

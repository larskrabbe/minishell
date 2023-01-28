/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:01:07 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/28 14:07:18 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	add_first_env_helper(t_env **env_lst, char **new_env, \
char **tmp_new_env)
{
	t_env	*env_new;

	env_new = env_lstnew(*new_env);
	env_add_back(env_lst, env_new);
	ft_free(tmp_new_env);
}

void	add_first_env(t_env **env_lst, char **new_env)
{
	char	**tmp_new_env;
	char	*created_new_env;
	char	*join;
	char	*new_name;
	t_env	*env_new;

	tmp_new_env = ft_slice(*new_env, '=');
	if (!tmp_new_env)
		return ;
	new_name = tmp_new_env[0];
	new_name = var_name_ends_with_plus(new_name);
	if (new_name)
	{
		join = ft_strjoin(new_name, "=");
		created_new_env = ft_strjoin(join, tmp_new_env[1]);
		env_new = env_lstnew(created_new_env);
		env_add_back(env_lst, env_new);
		ft_free(tmp_new_env);
		free(join);
		free(created_new_env);
	}
	else
		add_first_env_helper(env_lst, new_env, tmp_new_env);
}

int	add_new_envs(t_env **env_lst, char **new_env, int *error)
{
	while (*new_env)
	{
		if (!env_id_isvalid(*new_env))
			*error = TRUE;
		else
		{
			if (!env_lst || !*env_lst)
				add_first_env(env_lst, new_env);
			else if (!ft_setenv(*env_lst, *new_env))
				return (error_allocation);
		}
		new_env++;
	}
	return (no_error);
}

int	ft_export(t_env **env_lst, char **new_env)
{
	int		error;

	error = FALSE;
	if (!env_lst)
		return (error_allocation);
	if (!new_env || !*new_env)
	{
		ft_export_print(*env_lst);
	}
	else
	{
		if (add_new_envs(env_lst, new_env, &error) != no_error)
			return (error_allocation);
	}
	if (error)
		return (error_builtin);
	return (no_error);
}

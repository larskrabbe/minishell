/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:43:56 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/27 20:26:38 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_home_dir(t_env *env_lst)
{
	t_cd	cd;

	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.res = chdir(ft_getenv(env_lst, "HOME"));
	if (cd.res != 0)
		return (error_builtin);
	set_old_pwd(env_lst, cd.pwd);
	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.new_pwd = ft_strjoin("PWD=", cd.pwd);
	ft_setenv(env_lst, cd.new_pwd);
	free(cd.new_pwd);
	return (no_error);
}

int	cd_old_dir(t_env *env_lst)
{
	t_cd	cd;
	char	*present_working_dir;

	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.res = chdir(ft_getenv(env_lst, "OLDPWD"));
	if (cd.res != 0)
		return (error_builtin);
	set_old_pwd(env_lst, cd.pwd);
	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.new_pwd = ft_strjoin("PWD=", cd.pwd);
	ft_setenv(env_lst, cd.new_pwd);
	present_working_dir = ft_getenv(env_lst, "PWD");
	printf("%s\n", present_working_dir);
	free(cd.new_pwd);
	return (no_error);
}

int	cd_x_dir(t_env *env_lst, char **path_name)
{
	t_cd	cd;

	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.res = chdir(*path_name);
	if (cd.res != 0)
		return (error_builtin);
	set_old_pwd(env_lst, cd.pwd);
	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.new_pwd = ft_strjoin("PWD=", cd.pwd);
	ft_setenv(env_lst, cd.new_pwd);
	free(cd.new_pwd);
	return (no_error);
}

int	cd_tilde(t_env *env_lst, char **path_name)
{
	if (*(*path_name + 1) == '\0')
	{
		if (cd_home_dir(env_lst) == error_builtin)
			return (error_builtin);
	}
	else
	{
		if (cd_tilde_with_path(env_lst, path_name) == FALSE)
			return (error_builtin);
	}
	return (no_error);
}

int	ft_cd(t_env **env_lst, char **path_name)
{
	int	ret_val;

	ret_val = no_error;
	if (!env_lst)
		return (error_allocation);
	if (!path_name || !(*path_name) || **path_name == '\0')
		ret_val = cd_home_dir(*env_lst);
	else if (!old_pwdis_set(*env_lst)
		&& **path_name == '-')
		ret_val = error_builtin;
	else if (**path_name == '-'
		&& *(*path_name + 1) == '\0')
		ret_val = cd_old_dir(*env_lst);
	else if (**path_name == '~')
		ret_val = cd_tilde(*env_lst, path_name);
	else
		ret_val = cd_x_dir(*env_lst, path_name);
	if (ret_val != no_error)
		cd_error_mssg(path_name);
	return (ret_val);
}

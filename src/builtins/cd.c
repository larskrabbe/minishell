/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:43:56 by bogunlan          #+#    #+#             */
/*   Updated: 2022/12/23 18:41:12 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_old_dir(t_env *env_lst)
{
	t_cd	cd;

	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.res = chdir(ft_getenv(env_lst, "OLDPWD"));
	if (cd.res != 0)
		return (0);
	set_old_pwd(env_lst, cd.pwd);
	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.new_pwd = ft_strjoin("PWD=", cd.pwd);
	ft_setenv(env_lst, cd.new_pwd);
	free(cd.new_pwd);
	return (1);
}

int	cd_home_dir(t_env *env_lst)
{
	t_cd	cd;

	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.res = chdir(ft_getenv(env_lst, "HOME"));
	if (cd.res != 0)
		return (0);
	set_old_pwd(env_lst, cd.pwd);
	printf("%d\n", cd.res);
	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.new_pwd = ft_strjoin("PWD=", cd.pwd);
	ft_setenv(env_lst, cd.new_pwd);
	printf("\npwd: %s\n", cd.new_pwd);
	free(cd.new_pwd);
	return (1);
}

int	cd_x_dir(t_env *env_lst, char **path_name)
{
	t_cd	cd;

	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.res = chdir(*path_name);
	if (cd.res != 0)
		return (0);
	set_old_pwd(env_lst, cd.pwd);
	printf("%d\n", cd.res);
	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.new_pwd = ft_strjoin("PWD=", cd.pwd);
	ft_setenv(env_lst, cd.new_pwd);
	printf("\npwd: %s\n", cd.new_pwd);
	free(cd.new_pwd);
	return (1);
}

int	cd_tilde(t_env *env_lst, char **path_name)
{
	if (*(*path_name + 1) == '\0')
	{
		if (cd_home_dir(env_lst) == 0)
			return (0);
	}
	else
	{
		if (cd_tilde_with_path(env_lst, path_name) == 0)
			return (0);
	}
	return (1);
}

int	ft_cd(t_env **env_lst, char **path_name)
{
	if (!path_name || !(*path_name) || **path_name == '\0')
		return (cd_home_dir(*env_lst));
	if (!old_pwdis_set(*env_lst)
		&& **path_name == '-'
	)
		cd_old_error(path_name);
	else if (**path_name == '-'
		&& *(*path_name + 1) == '\0'
	)
		return (cd_old_dir(*env_lst));
	else if (**path_name == '~')
		return (cd_tilde(*env_lst, path_name));
	else
		return (cd_x_dir(*env_lst, path_name));
	return (0);
}

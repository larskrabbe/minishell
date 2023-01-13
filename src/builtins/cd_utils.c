/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:19:06 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/06 17:38:40 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Helper functions used by the ft_cd function

void	cd_error_mssg(char **path_name)
{
	if (!path_name || !*path_name)
		return ;
	if (**path_name == '-' && *(*path_name + 1) == '\0')
		printf("cd: OLDPWD not set\n");
	else if (access(*path_name, F_OK) == 0)
		printf("cd: %s: Not a directory\n", *path_name);
	else
		printf("cd: %s: No such file or directory\n", *path_name);
}

void	set_old_pwd(t_env *env_lst, char *pwd)
{
	t_cd	cd;

	cd.tmp = "OLDPWD=";
	cd.old_pwd = ft_strjoin(cd.tmp, pwd);
	ft_setenv(env_lst, cd.old_pwd);
	free(cd.old_pwd);
}

int	old_pwdis_set(t_env *env_lst)
{
	t_cd	cd;

	cd.old_pwd = ft_getenv(env_lst, "OLDPWD");
	if (cd.old_pwd == NULL || *cd.old_pwd == '\0')
		return (FALSE);
	return (TRUE);
}

int	cd_tilde_with_path(t_env *env_lst, char **path_name)
{
	t_cd	cd;

	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.tmp = ft_getenv(env_lst, "HOME");
	cd.rest_of_path = ft_substr(*path_name, 1, ft_strlen(*path_name));
	cd.new_path = ft_strjoin(cd.tmp, cd.rest_of_path);
	cd.res = chdir(cd.new_path);
	if (cd.res != 0)
	{
		free(cd.rest_of_path);
		free(cd.new_path);
		return (FALSE);
	}
	set_old_pwd(env_lst, cd.pwd);
	getcwd(cd.pwd, sizeof(cd.pwd));
	cd.new_pwd = ft_strjoin("PWD=", cd.pwd);
	ft_setenv(env_lst, cd.new_pwd);
	free(cd.rest_of_path);
	free(cd.new_path);
	free(cd.new_pwd);
	return (TRUE);
}

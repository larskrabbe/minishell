/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:32:57 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 18:58:05 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	access_folder(char *str)
{
	char	*str_dup;
	int		valid;
	char	*last;

	str_dup = ft_strdup(str);
	if (str_dup == NULL)
		return (error_allocation);
	last = ft_strrchr(str_dup, '/');
	if (last != NULL)
		*last = 0;
	valid = access(str_dup, F_OK);
	free (str_dup);
	return (valid);
}

int	check_permission(struct stat *info, t_redirection *redirection, \
int permission, char *str)
{
	if (!(info->st_mode & permission))
	{
		printf("%s: %s: Permission denied\n", IDLE_PROMT, str);
		redirection->exit_code = error_permission;
		return (error_permission);
	}
	return (no_error);
}

int	check_filetype(char *str, int permission, t_redirection *redirection)
{
	struct stat	info;

	if (access(str, F_OK) != 0 && (ft_strrchr(str, '/') == NULL || \
	access_folder(str) == 0))
		return (no_error);
	if (access(str, F_OK) != 0 && ft_strrchr(str, '/') != NULL)
	{
		printf("%s: %s: No such file or directory\n", IDLE_PROMT, str);
		redirection->exit_code = error_nofile;
		return (error_nofile);
	}
	stat(str, &info);
	if (!(info.st_mode & S_IFREG))
	{
		printf("%s: %s: is not a regular file\n", IDLE_PROMT, str);
		redirection->exit_code = error_nofile;
		return (error_nofile);
	}
	if (str[ft_strlen(str) - 1] == '/')
	{
		printf("%s: %s: Not a directory\n", IDLE_PROMT, str);
		redirection->exit_code = error_nofile;
		return (error_nofile);
	}
	return ((check_permission(&info, redirection, permission, str)));
}

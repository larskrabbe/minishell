/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:12:35 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 14:55:19 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	reset_fd(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd))
			return (error_close);
		*fd = -1;
	}
	return (0);
}

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

int	access_filename(char *str, int permsion, t_redirection *redirection)
{
	struct stat	info;

	if (access_folder(str) != 0 || access(str, F_OK) != 0)
	{
		printf("%s: %s: No such file or directory\n", IDLE_PROMT, str);
		redirection->exit_code = error_nofile;
		return (error_nofile);
	}
	stat(str, &info);
	if ((info.st_mode & S_IFDIR))
	{
		printf("%s: %s: Is a directory\n", IDLE_PROMT, str);
		redirection->exit_code = error_nofile;
		return (error_nofile);
	}
	if (!(info.st_mode & permsion))
	{
		printf("%s: %s: Permission denied\n", IDLE_PROMT, str);
		redirection->exit_code = error_permission;
		return (error_permission);
	}
	return (no_error);
}

int	open_outfile(t_exe_data *exe_data, t_token *token, t_env **env_lst, t_redirection *redirection)
{
	char		*str;

	str = NULL;
	reset_fd(&exe_data->fd_write);
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	if (access_filename(str, S_IWUSR, redirection) == 0)
	{
		exe_data->fd_write = open(str, O_WRONLY | O_CREAT | O_TRUNC, 644);
		if (exe_data->fd_write < 0)
			return (error_open);
	}

	free(str);
	return (0);
}


int	open_outfile_app(t_exe_data *exe_data, \
t_token *token, t_env **env_lst, t_redirection *redirection)
{
	char		*str;

	str = NULL;
	reset_fd(&exe_data->fd_write);
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	if (access_filename(str, S_IWUSR, redirection) == 0)
	{
		exe_data->fd_write = open(str, O_WRONLY | O_CREAT | O_APPEND, 644);
		if (exe_data->fd_write < 0)
			return (error_open);
	}
	free(str);
	return (0);
}

int	open_infile(t_exe_data *exe_data, t_token *token, t_env **env_lst, t_redirection *redirection)
{
	char		*str;
	struct stat	info;

	str = NULL;
	reset_fd(&exe_data->fd_read);
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	stat(str, &info);
	if (access_filename(str, S_IRUSR, redirection) == 0)
	{
		exe_data->fd_read = open(str, O_RDONLY, 644);
		if (exe_data->fd_read < 0)
			return (error_open);
	}
	if (exe_data->fd_read < 0)
		return (error_open);
	free(str);
	return (0);
}

int	heredoc(t_exe_data *exe_data, t_token *token, t_env **env_lst, t_redirection *redirection)
{
	int		expend_flag;
	int		len;
	char	*str;

	str = NULL;
	len = 0;
	expend_flag = TRUE;
	len = get_here_len(token, &expend_flag);
	str = ft_calloc (len, sizeof(char));
	if (str == NULL)
		return (error_allocation);
	get_here_str(token, str);
	heredoc_read(str, expend_flag, exe_data, env_lst, redirection);
	free (str);
	return (0);
}

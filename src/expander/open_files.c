/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:12:35 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 19:07:52 by lkrabbe          ###   ########.fr       */
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

int	open_outfile(t_exe_data *exe_data, t_token *token, \
t_env **env_lst, t_redirection *redirection)
{
	char		*str;

	str = NULL;
	reset_fd(&exe_data->fd_write);
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	if (check_filetype(str, S_IWUSR, redirection) == 0)
	{
		exe_data->fd_write = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	if (check_filetype(str, S_IWUSR, redirection) == 0)
	{
		exe_data->fd_write = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (exe_data->fd_write < 0)
			return (error_open);
	}
	else
		return (-1);
	free(str);
	return (0);
}

int	open_infile(t_exe_data *exe_data, \
t_token *token, t_env **env_lst, t_redirection *redirection)
{
	char		*str;
	struct stat	info;

	str = NULL;
	reset_fd(&exe_data->fd_read);
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	stat(str, &info);
	if (check_filetype(str, S_IRUSR, redirection) == 0)
	{
		exe_data->fd_read = open(str, O_RDONLY);
		if (exe_data->fd_read < 0)
			return (error_open);
	}
	else
		return (-1);
	if (exe_data->fd_read < 0)
		return (error_open);
	free(str);
	return (0);
}

int	heredoc(t_exe_data *exe_data, t_token *token, t_redirection *redirection)
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
	heredoc_read(str, expend_flag, exe_data, redirection);
	free (str);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:12:35 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/25 19:56:08 by lkrabbe          ###   ########.fr       */
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

int	open_outfile(t_redirection *redirection, t_token *token, t_env *env_lst)
{
	char		*str;
	struct stat	info;

	str = NULL;
	reset_fd(&redirection->fd_outfile);
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	stat(str, &info);
	if (!(info.st_mode & S_IRUSR))
	{
		printf("<minishell>: %s: Permission denied\n", str);
		return (error_permission);
	}
	redirection->fd_outfile = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirection->fd_outfile < 0)
		return (error_open);
	free(str);
	return (0);
}

int	open_outfile_app(t_redirection *redirection, t_token *token, t_env *env_lst)
{
	char		*str;
	struct stat	info;

	str = NULL;
	reset_fd(&redirection->fd_outfile);
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	stat(str, &info);
	if (!(info.st_mode & S_IRUSR))
	{
		printf("<minishell>: %s: Permission denied\n", str);
		return (error_permission);
	}
	redirection->fd_outfile = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redirection->fd_outfile < 0)
		return (error_open);
	free(str);
	return (0);
}

int	open_infile(t_redirection *redirection, t_token *token, t_env *env_lst)
{
	char		*str;
	struct stat	info;

	str = NULL;
	reset_fd(&redirection->fd_infile);
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	stat(str, &info);
	if (!(info.st_mode & S_IRUSR))
	{
		printf("<minishell>: %s: Permission denied\n", str);
		return (error_permission);
	}
	redirection->fd_infile = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redirection->fd_infile < 0)
		return (error_open);
	free(str);
	return (0);
}

int	heredoc(t_redirection *redirection, t_token *token, t_env *env_lst)
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
	heredoc_read(str, expend_flag, redirection, env_lst);
	free (str);
	return (0);
}

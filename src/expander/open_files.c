/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:12:35 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/24 18:10:35 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	open_outfile(t_redirection *redirection, t_token *token, t_env *env_lst)
{
	char		*str;
	struct stat	info;

	str = NULL;
	if (redirection->fd_outfile != -1)
	{
		close(redirection->fd_outfile);
		redirection->fd_outfile = -1;
	}
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	stat(str, &info);
	if (!(info.st_mode & S_IRUSR))
	{
		printf("<minishell>: %s: Permission denied\n", str);
		return (error_permission);
	}
	redirection->fd_outfile = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
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
	if (redirection->fd_outfile != -1)
	{
		close(redirection->fd_outfile);
		redirection->fd_outfile = -1;
	}
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	stat(str, &info);
	if (!(info.st_mode & S_IRUSR))
	{
		printf("<minishell>: %s: Permission denied\n", str);
		return (error_permission);
	}
	redirection->fd_outfile = open(str, O_WRONLY | O_CREAT | O_APPEND, 0666);
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
	if (redirection->fd_infile != -1)
	{
		close(redirection->fd_infile);
		redirection->fd_infile = -1;
	}
	str = tokenstring(token, env_lst, redirection);
	if (str == NULL)
		return (error_allocation);
	stat(str, &info);
	if (!(info.st_mode & S_IRUSR))
	{
		printf("<minishell>: %s: Permission denied\n", str);
		return (error_permission);
	}
	redirection->fd_infile = open(str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (redirection->fd_infile < 0)
		return (error_open);
	free(str);
	return (0);
}

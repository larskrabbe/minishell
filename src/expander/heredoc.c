/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:57:02 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/28 10:19:02 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	heredoc_expend(char *str, t_env **env_lst, t_redirection *redirection, int fd_write)
{
	char	*tmp_str;
	t_token	tmp_token;

	tmp_token.start = str;
	tmp_token.end = str + ft_strlen(str);
	tmp_str = tokenstring(&tmp_token, env_lst, redirection);
	if (tmp_str == NULL)
		return (error_allocation);
	write(fd_write, tmp_str, ft_strlen(tmp_str));
	free (tmp_str);
	return (0);
}

int	heredoc_readline(char *delimiter, int expend_flag, \
t_redirection *redirection, t_env **env_lst, int fd_write)
{
	char	*str;

	str = NULL;
	while (g_signal != signal_c)
	{
		str = readline(HEREDOC_PROMT);
		if (!str)
		{
			g_signal = signal_d;
			break ;
		}
		if (at_eof(str, delimiter) || g_signal == signal_c || !str)
		{
			free(str);
			break ;
		}
		if (expend_flag == TRUE)
			heredoc_expend(str, env_lst, redirection, fd_write);
		else
			write(fd_write, str, ft_strlen(str));
		write(fd_write, "\n", 1);
		free(str);
	}
	return (no_error);
}

int	heredoc_read(char *delimiter, int expend_flag, \
t_exe_data *exe_data, t_env **env_lst, t_redirection *redirection)
{
	int		stdin_copy;
	int		fd[2];

	reset_fd(&exe_data->fd_read);
	if (pipe(fd) != 0)
		return (0);
	stdin_copy = dup(STDIN_FILENO);
	exe_data->fd_read = fd[0];
	if (exe_data->fd_read < 0)
		return (error_open);
	heredoc_readline(delimiter, expend_flag, redirection, env_lst, fd[1]);
	if (g_signal == signal_c || g_signal == signal_d)
	{
		dup(stdin_copy);
		g_signal = signal_default;
	}
	close(fd[1]);
	close(stdin_copy);
	return (0);
}

// int	heredoc_read(char *delimiter, int expend_flag, \
// t_exe_data *exe_data, t_env **env_lst, t_redirection *redirection)
// {
// 	int		stdin_copy;
// 	char	*file;

// 	if (redirection->heredoc_num < MAX_HEREODAC)
// 		redirection->heredoc_num++;
// 	else
// 		redirection->heredoc_num = 0;
// 	file = ft_strjoin("heredoc",ft_itoa(redirection->heredoc_num));
// 	stdin_copy = dup(STDIN_FILENO);
// 	signal(SIGINT, signalhandler_heredoc);
// 	reset_fd(&exe_data->fd_read);
// 	exe_data->fd_read = \
// 	open(file, O_CREAT | O_RDWR | O_TRUNC, 700);
// 	free(file);
// 	if (exe_data->fd_read < 0)
// 		return (error_open);
// 	if (heredoc_readline(delimiter, expend_flag, \
// 	redirection, env_lst, exe_data))
// 		return (error_allocation);
// 	if (g_signal == signal_c || g_signal == signal_d)
// 	{
// 		dup(stdin_copy);
// 		g_signal = signal_default;
// 	}
// 	close(stdin_copy);
// 	return (0);
// }

char	*get_here_str(t_token *token, char *str)
{
	char	*ptr;
	int		q;
	int		l;

	l = 0;
	q = 0;
	ptr = token->start;
	while (ptr != token->end)
	{
		if ((*ptr == '"' || *ptr == '\'' ) && q == 0)
			q = *ptr;
		else if ((*ptr == '"' || *ptr == '\'' ) && q == *ptr)
			q = 0;
		else
		{
			str[l] = *ptr;
			l++;
		}
		ptr++;
	}
	str[l] = '\0';
	return (str);
}

int	get_here_len(t_token *token, int *expend_flag)
{
	char	*ptr;
	int		q;
	int		len;

	len = 0;
	ptr = token->start;
	while (ptr != token->end)
	{
		if ((*ptr == '"' || *ptr == '\'' ) && q == 0)
		{
			q = *ptr;
			if (*ptr == '"')
				*expend_flag = FALSE;
		}
		else if ((*ptr == '"' || *ptr == '\'' ) && q == *ptr)
			q = 0;
		else
			len++;
		ptr++;
	}
	return (len + 1);
}

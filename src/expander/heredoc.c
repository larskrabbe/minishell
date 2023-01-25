/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:57:02 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/25 19:56:04 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	heredoc_expend(char *str, t_env *env_lst, t_redirection *redirection)
{
	char	*tmp_str;
	t_token	tmp_token;

	tmp_token.start = str;
	tmp_token.end = str + ft_strlen(str);
	tmp_str = tokenstring(&tmp_token, env_lst, redirection);
	if (tmp_str == NULL)
		return (error_allocation);
	write(redirection->fd_infile, tmp_str, ft_strlen(tmp_str));
	free (tmp_str);
	return (0);
}

int	at_eof(char *str, char *delimiter)
{
	if (!ft_strncmp(str, delimiter, ft_strlen(str)))
	{
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter)))
			return (TRUE);
	}
	return (FALSE);
}

int	heredoc_read(char *delimiter, int expend_flag, \
t_redirection *redirection, t_env *env_lst)
{
	char	*str;

	str = NULL;
	reset_fd(&redirection->fd_infile);
	redirection->fd_infile = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (redirection->fd_infile < 0)
		return (error_open);
	while (g_signal != signal_c)
	{
		ft_putnbr_fd(g_signal, 1);
		str = readline(HEREDOC_PROMT);
		if (!str || !delimiter)
			return (error_allocation);
		if (at_eof(str, delimiter) || g_signal == signal_c)
		{
			free(str);
			break ;
		}
		if (expend_flag == TRUE)
			heredoc_expend(str, env_lst, redirection);
		else
			write(redirection->fd_infile, str, ft_strlen(str));
		write(redirection->fd_infile, "\n", 1);
		free(str);
	}
	if (g_signal == signal_c || g_signal == signal_d)
		g_signal = signal_default;
	return (0);
}

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

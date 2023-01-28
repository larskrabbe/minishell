/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 02:24:48 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/27 21:52:10 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_signals(void)
{
	struct termios	t;
	int				fd;

	fd = 0;
	if (tcgetattr(fd, &t) == -1)
	{
		perror("tcgetattr failed");
		return ;
	}
	t.c_lflag &= ~ECHOCTL;
	if (tcsetattr(fd, TCSANOW, &t) == -1)
	{
		perror("tcsetattr failed");
		return ;
	}
	if (signal(SIGINT, signalhandler_ctrlc) == SIG_ERR)
		perror("Failed to set signal handler for SIGINT");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("Failed to set signal handler for SIGQUIT");
}

void	clear_signals(void)
{
	struct termios	term;
	int				fd;

	fd = 0;
	if (tcgetattr(fd, &term) == -1)
	{
		perror("tcgetattr failed");
		return ;
	}
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(fd, TCSANOW, &term) == -1)
	{
		perror("tcsetattr failed");
		return ;
	}
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		perror("Failed to reset signal handler for SIGINT");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("Failed to reset signal handler for SIGQUIT");
}

void	reset_signals(void)
{
	clear_signals();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 02:24:48 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/25 18:00:53 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Handling ctrl-d will be in main when null is passed to the readline
// Break from the main process loop

void	signalhandler_ctrlc(int sig)
{
	if (sig == FALSE)
		return ;
	g_signal = signal_c;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	signalhandler_ctrlslash(int sig)
{
	if (sig == FALSE)
		return ;
	g_signal = signal_escape;
	rl_replace_line("", 0);
	printf("Quit\n");
	rl_on_new_line();
	rl_redisplay();
}

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

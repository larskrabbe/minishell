/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 02:24:48 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/23 19:32:09 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Handling ctrl-d will be in main when null is passed to the readline
// Break from the main process loop

void	signalhandler_ctrlc(int sig)
{
	// printf("signal %i global %i\n",sig, g_signal);
	if (sig == SIGINT)
	{
		// write(STDOUT_FILENO, "", 2);
	}
	rl_replace_line("", 0); // This fxn is to be used instead of rl_insert_text()
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	signalhandler_ctrlslash(int sig)
{
	// printf("signal %i global %i\n",sig, g_signal);
	if (sig == SIGQUIT)
	{
		// write(STDOUT_FILENO, "Quit", 4);
	}
	rl_replace_line("", 0); // This fxn is to be used instead of rl_insert_text()
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
		return;
	}
	t.c_lflag &= ~ECHOCTL;
	if (tcsetattr(fd, TCSANOW, &t) == -1)
	{
		perror("tcsetattr failed");
		return;
	}
	if (signal(SIGINT, signalhandler_ctrlc) == SIG_ERR)
		perror("Failed to set signal handler for SIGINT");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("Failed to set signal handler for SIGQUIT");
}

void	clear_signals(void)
{
	struct	termios term;
	int		fd;

	fd = 0;
	if (tcgetattr(fd, &term) == -1)
	{
		perror("tcgetattr failed");
		return;
	}
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(fd, TCSANOW, &term) == -1)
	{
		perror("tcsetattr failed");
		return;
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
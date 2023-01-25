/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 21:34:28 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/25 21:35:34 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signalhandler_heredoc(int sig)
{
	if (sig == FALSE)
		return ;
	write(1, "\n", 2);
	close(STDIN_FILENO);
}

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

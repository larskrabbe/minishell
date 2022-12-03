/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:20:23 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 18:20:29 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	g_signal;

void recieve(int signum)
{

	// printf("Signalnumber %i recieve\n",signum);
	clear_history();
	g_signal = signum;
	// rl_replace_line(NULL,0);
	// exit(0);
	write(STDOUT_FILENO, "", 1);
}

void	signal_setup(struct sigaction *signal_handler)
{
	g_signal = 0;
	signal_handler->sa_handler = (void *)recieve;
	sigemptyset (&signal_handler->sa_mask);
	//signal_handler->sa_flags = SA_SIGINFO; not sure if needed 
	sigaction(SIGINT,signal_handler,NULL);
}

void	free_before_exit(void)
{
	//printf("start freeing");
	clear_history();

}

int	main()
{
	char	*str;
	char	prompt[] = "<minishell>";//need to show the path
	struct	sigaction signal_handler;

	signal_setup(&signal_handler);
	while (g_signal == 0)
	{	
		str = readline(prompt);
		if (str != NULL)
		{
			add_history(str);
			printf("%s\n", str);//stoneage echo version
		}
		//free(str);
	}
	free_before_exit();
	return (0);
}
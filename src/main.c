/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:20:23 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/31 14:40:04 by bogunlan         ###   ########.fr       */
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



int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	prompt[] = "<minishell>";//need to show the path
	struct	sigaction signal_handler;
	t_env	*env = NULL;
	t_tokenchain	*tokenchain;

	if (argc <= 1 && argv == NULL)
		return(0);
	tokenchain = tokenchain_create();
	if (tokenchain == NULL)
		return (error_allocation);
	signal_setup(&signal_handler);
	env = *ft_getenv_lst(envp);
	while (g_signal == 0)
	{	
		str = readline(prompt);
		if (str != NULL)
		{
			add_history(str);
			lexer(str, tokenchain);
			// print_token_chain(tokenchain);
			expander(tokenchain, env);
	 		//execve("./simple_exe",NULL,NULL);

			printf("%s\n", str);//stoneage echo version
		}
		//free(str);
	}
	free_before_exit();
	return (0);
}
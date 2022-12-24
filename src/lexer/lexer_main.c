/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:32:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/24 12:36:43 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include	"lexer.h"

int	tmain(char *s) // tmain leaks after exiting the program, the tokenchain should be freed
{
	t_tokenchain	*tokenchain;

	tokenchain = tokenchain_create();
	if (tokenchain == NULL)
		return (error_allocation);
	lexer(s, tokenchain);
	print_token_chain(tokenchain);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	prompt[] = "<minishell>";//need to show the path
	t_env	**env_lst;
	(void) argv;
	(void) argc;

	env_lst = ft_getenv_lst(envp);
	ft_env(env_lst);
	while (1)
	{	
		str = readline(prompt);
		printf("**VALUE: %s**\n",ft_getenv(*env_lst, str));
		tmain(str);
		free(str);
	}
	return (0);
}
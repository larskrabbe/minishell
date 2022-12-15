/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:32:00 by lkrabbe           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/15 20:21:54 by bogunlan         ###   ########.fr       */
=======
/*   Updated: 2022/12/13 20:34:20 by lkrabbe          ###   ########.fr       */
>>>>>>> 522d3f2dfb81c5fc67ba4d2cbd98472c86a9db03
/*                                                                            */
/* ************************************************************************** */

#include	"lexer.h"

int	tmain(char *s)
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
	t_env	*env_lst;
	(void) argv;
	(void) argc;

	env_lst = ft_getenv_lst(envp);
	ft_printenv(env_lst);
	while (1)
	{	
		str = readline(prompt);
		printf("%s\n",ft_getenv(env_lst, str));
		tmain(str);
		free(str);
	}
	return (0);
}
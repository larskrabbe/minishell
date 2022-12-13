/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:32:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/13 20:34:20 by lkrabbe          ###   ########.fr       */
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

int	main()
{
	char	*str;
	char	prompt[] = "<minishell>";//need to show the path

	while (1)
	{	
		str = readline(prompt);
		tmain(str);
		free(str);
	}
	return (0);
}
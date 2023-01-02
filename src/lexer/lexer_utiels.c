/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utiels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:35:34 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/02 11:23:44 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	print_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->start + i != token->end)
	{
		write(1, ((token->start + i)), 1);
		i++;
	}
}

void	print_token_chain(t_tokenchain *tokenchain)
{
	int	cur_token;

	cur_token = 1;
	while (tokenchain->token[cur_token].end != 0)
	{
		print_token(&tokenchain->token[cur_token]);
		printf("\ntype == %i\n", tokenchain->token[cur_token].type);
		printf("str == %s\n", tokenchain->token[cur_token].str);
		printf("\n");
		cur_token++;
	}
}

void	myerror(char *str)
{
	printf("\033[31;1m%s\n\033[0m", str);
	exit (0);
}
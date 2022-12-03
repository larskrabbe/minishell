/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utiels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:35:34 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 16:37:05 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"lexer.h"

void	print_token_chain(t_tokenchain *tokenchain)
{

}

void	print_token(t_token *token)
{	
	printf("--------------\n");
	printf("tokentype = %i\n", token->tokentype);
	printf("content = %i  \n", token->start);
	printf("content = %i  \n", token->end);
	printf("--------------\n");
}

void	myerror(char *str)
{
	printf("\033[31;1m%s\n\033[0m", str);
	exit (0);
}

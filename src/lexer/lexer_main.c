/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:32:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/11/17 18:41:48 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"lexer.h"

int	main(void)
{
	t_tokenchain	*tokenchain;

	tokenchain = NULL;
	if (create_token_chain(&tokenchain) != 0)
		myerror("create_token_chain != 1");
	print_token_chain(tokenchain);
	lexer("echo -n abc 123", tokenchain);
	return (0);
}

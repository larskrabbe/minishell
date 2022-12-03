/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:32:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 19:57:09 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"lexer.h"

int	main(void)
{
	t_tokenchain	*tokenchain;

	tokenchain = tokenchain_create();
	if (tokenchain == NULL)
		myerror("create_token_chain != 1");
	lexer("HAllO WORLD BYE", tokenchain);
	return (0);
}

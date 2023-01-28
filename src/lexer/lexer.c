/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:50:17 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 21:06:05 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	syntax_checker(t_tokenchain *tokenchain, t_redirection *redirection)
{
	int	t;
	int	last_type;

	t = 1;
	last_type = 0;
	if (tokenchain->token[t].type == type_pipe)
		return (syntax_error_message(&tokenchain->token[t], redirection));
	while (tokenchain->token[t].type != type_null)
	{
		if (last_type == type_pipe && \
		tokenchain->token[t].type == type_pipe)
			return (syntax_error_message(&tokenchain->token[t], redirection));
		if (last_type >= type_redirection && \
		tokenchain->token[t].type == type_str)
			return (syntax_error_message(&tokenchain->token[t], redirection));
		last_type = tokenchain->token[t].type;
		t++;
	}
	if (last_type >= type_redirection)
		return (syntax_error_message(&tokenchain->token[t], redirection));
	return (no_error);
}

void	token_closer(t_token *token)
{
	token->start = NULL;
	token->end = NULL;
	token->type = type_null;
	token->str = NULL;
}

int	lexer(t_tokenchain *tokenchain, t_redirection *redirection)
{
	int		t;
	char	*str;

	str = tokenchain->str;
	t = 1;
	while (*str != '\0' && t < MAX_ARG)
	{
		if (is_white_space(*str) == 0)
		{
			if (token_start(tokenchain, redirection, &t, &str))
				return (-1);
		}
		else
			str++;
	}
	token_closer(&tokenchain->token[t]);
	if (t >= MAX_ARG)
		return (error_max_arg);
	return (syntax_checker(tokenchain, redirection));
}

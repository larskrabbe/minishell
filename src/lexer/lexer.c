/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:50:17 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/24 20:30:23 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int inline static	quotes_logic(char c, char *end)
{
	if (c == '\"' && *end == ' ')
		*end = '\"';
	else if (c == '\'' && *end == ' ')
		*end = '\'';
	else if (c == '\"' && *end == '\"')
		*end = ' ';
	else if (c == '\'' && *end == '\'')
		*end = ' ';
	else if (*end == ' ' && is_special_char(c))
		return (1);
	return (0);
}

char	*find_token_end(char *str)
{
	char	end;

	end = ' ';
	if (is_special_char(*str) != 0)
	{
		while (*str == *(str + 1))
			str++;
		return (str + 1);
	}
	while (*str != '\0' && (*str != end || end != ' '))
	{
		if (quotes_logic(*str, &end))
			return (str);
		str++;
	}
	if (end != ' ')
		return (NULL);
	if (quotes_logic(*str, &end) == 1)
		return (str);
	return (str++);
}

int	syntax_checker(t_tokenchain *tokenchain)
{
	int	t;
	int	last_type;

	t = 1;
	last_type = 0;
	if (tokenchain->token[t].type == type_pipe)
		return (error_syntax);
	while (tokenchain->token[t].type != type_null)
	{
		if (last_type == type_pipe && \
		tokenchain->token[t].type == type_pipe)
			return (error_syntax);
		if (last_type >= type_redirection && \
		tokenchain->token[t].type >= type_redirection)
			return (error_syntax);
		last_type = tokenchain->token[t].type;
		t++;
	}
	if (last_type >= type_redirection)
		return (error_syntax);
	return (no_error);
}

void	token_closer(t_token *token)
{
	token->start = NULL;
	token->end = NULL;
	token->type = type_null;
	token->str = NULL;
}

int	lexer(t_tokenchain *tokenchain)
{
	int		t;
	char	*str;

	str = tokenchain->str;
	t = 1;
	while (*str != '\0' && t < MAX_ARG)
	{
		if (is_white_space(*str) == 0)
		{
			tokenchain->token[t].start = str;
			tokenchain->token[t].end = find_token_end(str);
			str = tokenchain->token[t].end;
			if (tokenchain->token[t].end == NULL)
				return (error_quotes);
			if (check_type(&tokenchain->token[t]) != 0)
				return (1);
			t++;
		}
		else
			str++;
	}
	token_closer(&tokenchain->token[t]);
	if (t >= MAX_ARG)
		return (error_max_arg);
	return (syntax_checker(tokenchain));
}

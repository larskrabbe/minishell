/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:50:17 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 14:49:11 by lkrabbe          ###   ########.fr       */
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

char	*open_quotes_error_message(char c, t_redirection *redirection)
{
	printf("%s:open quotation marks `%c` \n", \
	IDLE_PROMT, c);
	redirection->exit_code = error_quotes;
	return (NULL);
}

char	*find_token_end(char *str, t_redirection *redirection)
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
		return (open_quotes_error_message(end, redirection));
	if (quotes_logic(*str, &end) == 1)
		return (str);
	return (str++);
}

int	syntax_error_message(t_token *token, t_redirection *redirection)
{
	printf("%s:syntax error near unexpected token `%.*s' \n", \
	IDLE_PROMT, (int)(&token->start - &token->end), token->start);
	redirection->exit_code = error_syntax;
	return (error_syntax);
}

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
		tokenchain->token[t].type >= type_redirection)
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

int	lexer(t_tokenchain *tokenchain,t_redirection *redirection)
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
			tokenchain->token[t].end = find_token_end(str, redirection);
			str = tokenchain->token[t].end;
			if (tokenchain->token[t].end == NULL)
				return (error_quotes);
			if (check_type(&tokenchain->token[t]) != 0)
				return (syntax_error_message(&tokenchain->token[t], \
				redirection));
			t++;
		}
		else
			str++;
	}
	token_closer(&tokenchain->token[t]);
	if (t >= MAX_ARG)
		return (error_max_arg);
	return (syntax_checker(tokenchain, redirection));
}

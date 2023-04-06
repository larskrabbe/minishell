/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:17:37 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/04/06 18:35:33 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

char	*open_quotes_error_message(char c, t_redirection *redirection)
{
	printf("%s:open quotation marks `%c` \n", \
	IDLE_PROMT, c);
	redirection->exit_code = error_quotes;
	return (NULL);
}

int	syntax_error_message(t_token *token, t_redirection *redirection)
{
	printf("%s:syntax error near unexpected token `%.*s' \n", \
	IDLE_PROMT, (int)(&token->start - &token->end), token->start);
	redirection->exit_code = error_syntax;
	return (error_syntax);
}

inline static int	quotes_logic(char c, char *end)
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

int	token_start(t_tokenchain *tokenchain, \
t_redirection *redirection, int *t, char **str)
{
	tokenchain->token[*t].start = *str;
	tokenchain->token[*t].end = find_token_end(*str, redirection);
	*str = tokenchain->token[*t].end;
	if (tokenchain->token[*t].end == NULL)
		return (error_quotes);
	if (check_type(&tokenchain->token[*t]) != 0)
		return (syntax_error_message(&tokenchain->token[*t], \
		redirection));
	(*t)++;
	return (0);
}

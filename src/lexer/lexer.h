/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:24:10 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/13 20:33:21 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_H
# define LEXER_H

//?-----------Includes------------?//

# include	"../../include/minishell.h"

//?-----------Defines------------?//

//!max amount of 'token' not sure if needed
# define ARG_MAX 1000

//?-----------Enums------------?//

/**
 * @brief enums for error values
 * 
 */
typedef enum e_error{
	no_error = 0,
	error_quotes = 1,
	error_allocation = 2,
	error_max_arg = 3,
	error_syntax = 4,
}t_error;

//?-----------Structs------------?//

/**
 * @brief stores each position of a token inside of the input string
 * 
 * @param tokentype int that represent the type of token
 * @param start the start of the token
 * @param end the end of the token
 */
typedef struct s_token{
	char			*start;
	char			*end;
	char			*str;
	enum e_ttype	type;
}t_token;

/**
 * @brief Head structure of the tokenchain
 * 
 * @param str string that is tokenize
 * @param tokenchain the pointer to all token
 */
typedef struct s_tokenchain{
	char	*str;
	t_token	*token;
}t_tokenchain;

//?-----------Protoypes------------?//

void			myerror(char *str);
int				lexer(char *str, t_tokenchain *tokenchain);
t_tokenchain	*tokenchain_create(void);
void			print_token_chain(t_tokenchain *tokenchain);

#endif
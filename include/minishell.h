/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:21:20 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/13 20:39:15 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//?-----------Includes------------?//

# include	<stdio.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<signal.h>
# include	"libft.h"
# include	"../src/lexer/lexer.h"

//?-----------Defines------------?//

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

//?-----------ENUMS------------?//

typedef enum e_signal{
	no_signal = 0,
	exit_signal = 1,
	c_signal = 2,
}t_sigal;

typedef enum e_ttype{
	type_built_exe = 1,
	type_str = 2,
	type_redirection = 3,
	type_app_redirection = 4,
	type_input_file = 5,
	type_heredoc = 6,
	type_pipe = 10,
}t_ttype;


//?-----------PROTOTYPES------------?//

int			is_white_space(int a);
int			is_special_char(char a);

#endif

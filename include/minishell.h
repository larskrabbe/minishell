/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:21:20 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 18:22:33 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<stdio.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<signal.h>
# include	"libft.h"

//?-----------ENUMS------------?//

typedef enum e_signal{
	no_signal = 0,
	exit_signal = 1,
	c_signal = 2,
}t_sigal;

//?-----------PROTOTYPES------------?//

int			is_white_space(int a);

#endif

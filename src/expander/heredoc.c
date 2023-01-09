/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:57:02 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/09 22:23:11 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	at_eof(char *str, char *delimiter)
{
	if (!ft_strncmp(str, delimiter, ft_strlen(str)))
	{
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter)))
			return (TRUE);
	}
	return (FALSE);
}

char	**heredoc(char *delimiter)
{
	static char	*ret[ARG_MAX];
	char		*str;
	char		*new_str;
	int			i;

	i = 0;
	while (TRUE)
	{
		str = readline("> ");
		if (at_eof(str, delimiter))
		{
			free(str);
			break ;
		}
		new_str = ft_strjoin(str, "\n");
		if (!new_str)
			return (NULL);
		ret[i] = ft_strdup(new_str);
		free(new_str);
		free(str);
		i++;
	}
	return (ret);
}

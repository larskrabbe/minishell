/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:18:21 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/13 20:27:18 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

char	**ft_free(char **res)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char	**ft_gen_slice(const char *s, char c, char **res, int res_s_i)
{
	unsigned int	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == c)
		{
			res[res_s_i] = ft_substr(s, 0, i);
			if (res[res_s_i] == NULL)
				return (ft_free(res));
			res_s_i++;
			break ;
		}
		i++;
	}
	if (ft_strchr(s, '='))
		res[res_s_i] = ft_substr(s, i + 1, ft_strlen(s) - (i + 1));
	else
	{
		res[res_s_i++] = ft_substr(s, 0, ft_strlen(s));
		res[res_s_i] = ft_substr(s, ft_strlen(s), ft_strlen(s));
	}
	res[++res_s_i] = NULL;
	return (res);
}

char	**ft_slice(char const *s, char c)
{
	char	**sarray;
	int		sarray_start_index;

	sarray_start_index = 0;
	if (!s)
		return (NULL);
	sarray = (char **) malloc(sizeof(char *) * 3);
	if (!sarray)
		return (NULL);
	sarray = ft_gen_slice(s, c, sarray, sarray_start_index);
	return (sarray);
}

void	clean_env(t_env **env_lst)
{
	t_env	*tmp;

	while (*env_lst)
	{
		tmp = (*env_lst);
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		(*env_lst) = (*env_lst)->next;
		free(tmp);
	}
}

char	**env_as_string(t_env **env_lst)
{
	t_env			*head;
	t_env_string	str;
	static char		*env[1000000];
	int				i;

	head = *env_lst;
	i = 0;
	while (head)
	{
		str.name = ft_strdup(head->name);
		str.join_equal = ft_strjoin(str.name, "=");
		if (head->value)
			str.join_value = ft_strjoin(str.join_equal, head->value);
		else
			str.join_value = ft_strjoin(str.join_equal, "");
		env[i] = ft_strdup(str.join_value);
		head = head->next;
		free(str.name);
		free(str.join_equal);
		free(str.join_value);
		i++;
	}
	return (env);
}

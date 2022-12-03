/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:29:07 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/29 15:18:57 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

static char	*dup_until_c(char *str, char c)
{
	size_t	len;
	char	*dst;

	len = 0;
	while (str[len] != c && str[len] != '\0')
		len++;
	dst = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!dst)
	{
		free(dst);
		return (NULL);
	}
	ft_strlcpy(dst, str, (len + 1));
	return (dst);
}

static int	str_in_str(char	*str, char c)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			while (str[i] != '\0' && str[i] != c)
				i++;
			num++;
		}
	}
	return (num);
}

static char	*copy_n_str(char *str, char c, int n)
{
	char	*dst;	
	int		num;
	int		i;

	num = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			if (num == n)
			{
				dst = dup_until_c((str + i), c);
				if (dst == NULL)
					return (NULL);
			}
			while (str[i] != '\0' && str[i] != c)
				i++;
			num++;
		}
	}
	return (dst);
}

void static	free_ptr(char **ptr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(ptr[i]);
		i++;
	}
	free (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	len = str_in_str((char *)s, c);
	i = 0;
	dest = (char **)ft_calloc(sizeof(dest), (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = copy_n_str((char *)s, c, i);
		if (dest[i] == NULL)
		{
			free_ptr(dest, len);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

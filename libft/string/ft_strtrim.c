/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:38:34 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/22 19:04:29 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

static int	inset(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	fronttrim(const char *s1, const char *set)
{
	int	len;

	len = 0;
	while (inset(s1[len], set) == 1 && s1[len] != '\0')
		len++;
	return (len);
}

static int	backtrim(const char *s1, const char *set, int start)
{
	int	len;

	len = ft_strlen(s1);
	while (inset(s1[len - 1], set) && len >= start)
		len--;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len_copy;
	char	*copy;
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	start = fronttrim(s1, set);
	end = backtrim(s1, set, start);
	len_copy = end - start;
	if (len_copy <= 0)
		return (ft_strdup(""));
	copy = (char *)malloc(sizeof(char) * (len_copy + 1));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, (s1 + start), (len_copy + 1));
	return (copy);
}

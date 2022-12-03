/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:27:23 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/27 04:44:44 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft.h"

int	lookfor(int fd, char *buffer, char *sta_buf)
{
	ssize_t	len;
	ssize_t	i;
	ssize_t	pos;

	pos = 0;
	sta_buf[0] = '\0';
	len = read(fd, buffer, BUFFER_SIZE);
	if (len == 0 || len == -1)
		return (len);
	i = 0;
	while (i < len && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		while (pos + i < len)
		{
			sta_buf[pos] = buffer[i + pos];
			pos++;
		}
		sta_buf[pos] = '\0';
	}
	return (i);
}

char	*rec_str_join(int fd, char *ptr, ssize_t size, char *tmp_buf)
{
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		i;
	int			k;

	buffer[BUFFER_SIZE] = '\0';
	k = 0;
	i = lookfor(fd, buffer, tmp_buf);
	if (i == BUFFER_SIZE && buffer[i - 1] != '\n')
	{	
		ptr = rec_str_join(fd, ptr, size + i, tmp_buf);
		if (ptr == NULL)
			return (NULL);
	}
	else if ((i == 0 && size == 0) || i == -1)
		return (NULL);
	else
	{
		ptr = malloc (sizeof(char) * (size + 1 + i));
		if (ptr == NULL)
			return (NULL);
		ptr[size + i] = '\0';
	}
	while (i-- > 0)
		ptr[size + i] = buffer[i];
	return (ptr);
}

char	*will_not_read(ssize_t i, char *sta_buf)
{
	int		k;
	char	*ptr;

	k = 0;
	ptr = ft_calloc(sizeof(char), (i + 1));
	if (ptr == NULL)
		return (NULL);
	while (k < i)
	{
		ptr[k] = sta_buf[k];
		sta_buf[k] = sta_buf[k + i];
		k++;
	}
	ptr[k] = '\0';
	while (sta_buf[k + i] != '\0')
	{
		sta_buf[k] = sta_buf[k + i];
		k++;
	}
	while (k <= BUFFER_SIZE)
	{
		sta_buf[k] = '\0';
		k++;
	}
	return (ptr);
}

char	*will_read(char *sta_buf, int fd, char *tmp_buf, ssize_t i)
{
	int		k;
	char	*ptr;

	ptr = NULL;
	k = 0;
	ptr = rec_str_join(fd, ptr, i, tmp_buf);
	if (ptr == NULL)
		return (NULL);
	while (sta_buf[k] != '\0')
	{
		ptr[k] = sta_buf[k];
		k++;
	}
	k = 0;
	while (k <= BUFFER_SIZE + 1)
	{
		sta_buf[k] = tmp_buf[k];
		k++;
	}
	sta_buf[k] = '\0';
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	sta_buf[255][BUFFER_SIZE +1];
	ssize_t		i;
	char		tmp_buf[BUFFER_SIZE +1];

	i = 0;
	if (fd > 1024 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (sta_buf[fd][i] != '\0' && sta_buf[fd][i] != '\n')
		i++;
	if (sta_buf[fd][i] == '\n')
		return (will_not_read(i + 1, sta_buf[fd]));
	else
		return (will_read(sta_buf[fd], fd, tmp_buf, i));
}

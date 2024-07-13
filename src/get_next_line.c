/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:57:05 by jcapistr          #+#    #+#             */
/*   Updated: 2022/12/03 10:57:05 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>

char	*ft_strchr(const char *str, int chr);
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strdup(const char *src);

char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = (char *)malloc(s1_len + s2_len + 1);
	if (!dst)
		return (NULL);
	ft_strcpy(dst, s1);
	ft_strcat(dst, s2);
	free(s1);
	return (dst);
}

char	*read_fd(int fd, char *buf)
{
	char	*line;
	ssize_t	rd_bytes;

	line = ft_strdup(buf);
	while (!ft_strchr(line, '\n'))
	{
		rd_bytes = read(fd, buf, BUFFER_SIZE);
		if (rd_bytes <= 0)
			break ;
		buf[rd_bytes] = 0;
		line = ft_strjoin(line, buf);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			idx;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_fd(fd, buf);
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	newline = ft_strchr(line, '\n');
	idx = ft_strlen(line);
	if (newline)
	{
		idx = newline - line + 1;
		ft_strcpy(buf, newline + 1);
	}
	else
		*buf = 0;
	line[idx] = 0;
	return (line);
}

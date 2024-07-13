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

char	*gnl_strchr(const char *str, int chr);
size_t	gnl_strlen(const char *str);
char	*gnl_strcpy(char *dst, const char *src);
char	*gnl_strcat(char *dst, const char *src);
char	*gnl_strdup(const char *src);

static char	*gnl_strjoin(char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	dst = (char *)malloc(s1_len + s2_len + 1);
	if (!dst)
		return (NULL);
	gnl_strcpy(dst, s1);
	gnl_strcat(dst, s2);
	free(s1);
	return (dst);
}

static char	*gnl_read_fd(int fd, char *buf)
{
	char	*line;
	ssize_t	rd_bytes;

	line = gnl_strdup(buf);
	while (!gnl_strchr(line, '\n'))
	{
		rd_bytes = read(fd, buf, BUFFER_SIZE);
		if (rd_bytes <= 0)
			break ;
		buf[rd_bytes] = 0;
		line = gnl_strjoin(line, buf);
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
	line = gnl_read_fd(fd, buf);
	if (gnl_strlen(line) == 0)
		return (free(line), NULL);
	newline = gnl_strchr(line, '\n');
	idx = gnl_strlen(line);
	if (newline)
	{
		idx = newline - line + 1;
		gnl_strcpy(buf, newline + 1);
	}
	else
		*buf = 0;
	line[idx] = 0;
	return (line);
}

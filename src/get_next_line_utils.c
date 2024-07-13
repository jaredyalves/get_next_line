/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:57:13 by jcapistr          #+#    #+#             */
/*   Updated: 2022/12/03 10:57:15 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*gnl_strchr(const char *str, int chr)
{
	while (*str)
	{
		if (*str == (char)chr)
			return ((char *)str);
		str++;
	}
	if (*str == chr)
		return ((char *)str);
	return (NULL);
}

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strcpy(char *dst, const char *src)
{
	char	*ptr;

	ptr = dst;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dst);
}

char	*gnl_strcat(char *dst, const char *src)
{
	char	*ptr;

	ptr = dst;
	while (*ptr)
		ptr++;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dst);
}

char	*gnl_strdup(const char *src)
{
	size_t	len;
	char	*dst;

	len = gnl_strlen(src) + 1;
	dst = (char *)malloc(len);
	if (!dst)
		return (NULL);
	gnl_strcpy(dst, src);
	return (dst);
}

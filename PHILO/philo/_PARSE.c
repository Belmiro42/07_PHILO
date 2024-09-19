/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _PARSE.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:28:50 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/07/16 06:09:46 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │							 	PARSE/JOIN								│
//  ├───────────────────────────────────────────────────────────────────────┤

size_t	phil_strlen(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

size_t	phil_strlcpy(char *dst, const char *src, size_t buff_size)
{
	size_t	index;

	index = 0;
	if (buff_size == 0)
		return (phil_strlen(src));
	while (buff_size > 1 && src[index])
	{
		dst[index] = src[index];
		buff_size--;
		index++;
	}
	if (buff_size != 0)
		dst[index] = '\0';
	return (phil_strlen(src));
}

size_t	phil_strlcat(char *dst, const char *src, size_t buff_size)
{
	size_t	dst_len;
	size_t	src_len;

	src_len = phil_strlen(src);
	dst_len = phil_strlen(dst);
	if (buff_size <= dst_len)
		return (buff_size + src_len);
	return (dst_len + phil_strlcpy(dst + dst_len, src, buff_size - dst_len));
}

static char	*join(char *s1, const char *s2)
{
	char	*ptr;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = phil_strlen(s1) + phil_strlen(s2) + 1;
	ptr = (char *)malloc(len + 1);
	if (ptr == NULL)
		return (free(s1), NULL);
	phil_strlcpy(ptr, s1, len + 1);
	ptr[phil_strlen(s1)] = ' ';
	phil_strlcpy(ptr + phil_strlen(s1) + 1, s2, len - phil_strlen(s1));
	free(s1);
	return (ptr);
}

char	*join_all_inputs(char ***argv)
{
	char	*str;

	str = (char *)malloc(1);
	if (!str)
		my_exit(NULL);
	str[0] = '\0';
	while (**argv)
	{
		str = join(str, **argv);
		if (str == NULL)
			my_exit(NULL);
		(*argv)++;
	}
	return (str);
}

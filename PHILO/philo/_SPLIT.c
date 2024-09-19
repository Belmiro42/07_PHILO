/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _SPLIT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:41:50 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/07/18 18:26:52 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │							 	SPLIT									│
//  ├───────────────────────────────────────────────────────────────────────┤
static int	numstring(char const *s1, char c)
{
	int	count;
	int	is_on_delimiter;

	is_on_delimiter = 0;
	count = 0;
	if (*s1 == '\0')
		return (0);
	while (*s1 != '\0')
	{
		if (*s1 == c)
			is_on_delimiter = 0;
		else if (is_on_delimiter == 0)
		{
			is_on_delimiter = 1;
			count++;
		}
		s1++;
	}
	return (count);
}

static int	numchar(char const *str, char c, int i)
{
	int	length;

	length = 0;
	while (str[i] != c && str[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}

static char	**freee(char **dst, int j)
{
	while (j > 0)
	{
		j--;
		free(dst[j]);
	}
	free(dst);
	return (NULL);
}

static char	**affect(char *str, char **ret, char c, int l)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	i = 0;
	while (str[i] != '\0' && j < l)
	{
		k = 0;
		while (str[i] == c)
			i++;
		ret[j] = (char *)malloc(sizeof(char) * numchar(str, c, i) + 1);
		if (ret[j] == NULL)
			return (freee(ret, j));
		while (str[i] != '\0' && str[i] != c)
			ret[j][k++] = str[i++];
		ret[j][k] = '\0';
		j++;
	}
	ret[j] = NULL;
	free(str);
	return (ret);
}

char	**phil_split(char *s, char c, int *argc)
{
	char	**dst;
	int		l;

	if (s == NULL)
		return (NULL);
	l = numstring(s, c);
	if (l != 6 && l != 5)
		my_exit(NULL);
	*argc = l;
	dst = (char **)malloc(sizeof(char *) * (l + 1));
	if (dst == NULL)
		return (NULL);
	return (affect(s, dst, c, l));
}

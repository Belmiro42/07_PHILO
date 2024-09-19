/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _UTILS.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:44:22 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/07/16 07:09:39 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │							 	UTILS									│
//  ├───────────────────────────────────────────────────────────────────────┤

int	free_string(char **argv)
{
	int	iterator;

	iterator = -1;
	if (argv[0])
	{
		iterator = 0;
		while (argv[iterator])
			iterator++;
		while (--iterator >= 0)
			free(argv[iterator]);
	}
	free(argv);
	return (0);
}

long unsigned	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, 0);
	return ((now.tv_sec * 1000000) + now.tv_usec);
}

int	phil_atoi(char **argv, int c)
{
	long	number;
	char	*str;

	str = argv[c];
	if (str == NULL)
		return (0);
	number = 0;
	while ((48 <= *str && *str <= 57))
	{
		number = number * 10 + (*str++ - '0');
		if (number > INT_MAX || number == 0)
		{
			free_string(argv);
			my_exit(NULL);
		}
	}
	if (*str)
	{
		free_string(argv);
		my_exit(NULL);
	}
	return (number);
}

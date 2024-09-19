/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _LIBERATION.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:40:12 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/07/15 22:19:20 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │							 LIBERATION									│
//  ├───────────────────────────────────────────────────────────────────────┤
static void	kill_phils(t_universal *global)
{
	int	i;

	i = 0;
	if (global->philosophers != NULL)
		while (i <= global->phil_num)
			if (global->philosophers[i] != NULL)
				free(global->philosophers[i++]);
	if (global->philosophers != NULL)
		free(global->philosophers);
}

static void	kill_structs(t_universal *global)
{
	int	i;

	i = 0;
	if (global->structs != NULL)
		while (i < global->phil_num)
			if (global->structs[i] != NULL)
				free(global->structs[i++]);
	if (global->structs != NULL)
		free(global->structs);
}

static void	kill_forks(t_universal *global)
{
	int	i;

	i = 0;
	if (global->forks != NULL)
		while (i < global->phil_num + 1)
			pthread_mutex_destroy(&global->forks[i++]);
	if (global->forks != NULL)
		free(global->forks);
}

void	my_exit(t_universal *global)
{
	if (global == NULL)
		exit(EXIT_FAILURE);
	kill_phils(global);
	kill_structs(global);
	kill_forks(global);
	pthread_mutex_destroy(&global->end_mutex);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _INITIALISE.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:33:01 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/07/18 15:47:29 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static t_phil	**philosophers_struct_set_up(t_universal *global)
{
	t_phil	**structs;

	structs = malloc(global->phil_num * sizeof(t_phil *));
	if (!structs)
		my_exit(global);
	return (structs);
}

static pthread_mutex_t	*forks_set_up(t_universal *global)
{
	pthread_mutex_t	*mutexes;
	int				i;

	mutexes = (pthread_mutex_t *)malloc((global->phil_num + 1)
			* sizeof(pthread_mutex_t));
	if (mutexes == NULL)
		my_exit(global);
	i = -1;
	while (++i <= global->phil_num)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			if (i == 0)
				my_exit(global);
			else
				my_exit(global);
		}
	}
	return (mutexes);
}

static pthread_t	*create_individual_philosopher(t_universal *global,
		int iterator)
{
	pthread_t	*philosopher;

	philosopher = malloc(sizeof(pthread_t));
	if (!philosopher)
	{
		if (iterator == 0)
			my_exit(global);
		else
			my_exit(global);
	}
	return (philosopher);
}

static pthread_t	**philosophers_set_up(t_universal *global)
{
	pthread_t	**array;
	int			iterator;

	array = malloc(sizeof(pthread_t *) * (global->phil_num + 1));
	if (array == NULL)
		my_exit(global);
	iterator = -1;
	while (++iterator <= global->phil_num)
		array[iterator] = create_individual_philosopher(global, iterator);
	return (array);
}

void	initialise_struct(t_universal *global, char **argv)
{
	global->phil_num = phil_atoi(argv, 1);
	global->die_t = phil_atoi(argv, 2);
	global->eat_t = phil_atoi(argv, 3);
	global->sleep_t = phil_atoi(argv, 4);
	global->eat_c = phil_atoi(argv, 5) + free_string(argv);
	global->start = get_time() + 1000000;
	global->forks = forks_set_up(global);
	global->print = (global->forks)[global->phil_num];
	global->philosophers = philosophers_set_up(global);
	global->structs = philosophers_struct_set_up(global);
	global->end = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _PHILOSOPHER.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:37:43 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/07/18 18:36:46 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │							PHILOSOPHER ACTIONS							│
//  ├───────────────────────────────────────────────────────────────────────┤
void	phil_wait(long unsigned time)
{
	while (get_time() < time)
		usleep(400);
}

void	wait_till_start(t_phil *current)
{
	int				third;
	unsigned long	start_time;

	third = 0;
	if (current->global->phil_num % 2 == 1)
		if (current->id == (current->global->phil_num - 1))
			third = 2;
	if (current->global->phil_num == 1)
		third = 0;
	start_time = (current->global->start + (((current->id % 2) + third)
				* current->global->eat_t * 1002));
	phil_wait(start_time);
}

static void	philosopher_print(t_phil *current, char *str)
{
	unsigned long	time;
	int				id;
	pthread_mutex_t	*print;
	int				end;

	id = current->id + 1;
	print = &(current->global->print);
	pthread_mutex_lock(&current->global->end_mutex);
	end = current->global->end;
	pthread_mutex_unlock(&current->global->end_mutex);
	time = current->global->start / 1000;
	if (!end)
	{
		pthread_mutex_lock(print);
		pthread_mutex_lock(&current->global->end_mutex);
		end = current->global->end;
		pthread_mutex_unlock(&current->global->end_mutex);
		if (!end)
			printf("%lu\t%d\t%s\n", get_time() / 1000 - time, id, str);
		pthread_mutex_unlock(print);
	}
}

static void	philosopher_eat(t_phil *current, pthread_mutex_t *l,
		pthread_mutex_t *r)
{
	long unsigned	time;

	pthread_mutex_lock(r);
	philosopher_print(current, "has taken a fork");
	if (current->global->phil_num != 1)
	{
		pthread_mutex_lock(l);
		time = get_time();
		philosopher_print(current, "has taken a fork");
		pthread_mutex_lock(&current->last_eat_mutex);
		current->last_eat = time;
		pthread_mutex_unlock(&current->last_eat_mutex);
		philosopher_print(current, "is eating");
		phil_wait(time + current->global->eat_t * 1000);
		pthread_mutex_lock(&current->eat_count_mutex);
		current->eat_count += 1;
		pthread_mutex_unlock(&current->eat_count_mutex);
		pthread_mutex_unlock(l);
	}
	else
		phil_wait(current->global->start + current->global->die_t * 1000);
	pthread_mutex_unlock(r);
	time = get_time();
	philosopher_print(current, "is sleeping");
	phil_wait(time + current->global->sleep_t * 1000);
}

void	*philosopher(void *arg)
{
	t_phil			*c;
	int				end;

	c = (t_phil *)arg;
	wait_till_start(c);
	end = 0;
	while (!end)
	{
		philosopher_print(c, "is thinking");
		philosopher_eat(c, &(c->global->forks)[(c->id)],
			&(c->global->forks)[(c->id + 1) % (c->global->phil_num)]);
		pthread_mutex_lock(&c->global->end_mutex);
		end = c->global->end;
		pthread_mutex_unlock(&c->global->end_mutex);
	}
	phil_wait(c->global->eat_t);
	pthread_mutex_destroy(&c->eat_count_mutex);
	pthread_mutex_destroy(&c->last_eat_mutex);
	return (NULL);
}

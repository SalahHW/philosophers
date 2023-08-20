/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:19:22 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/20 16:13:49 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		printf("%lu %d is thinking\n", get_time_stamp(), philo->id);
		pthread_mutex_lock(&philo->fork);
		printf("Philo %d finished thinking\n", philo->id);
		philo->state = EATING;
		printf("%lu %d is eating\n", get_time_stamp(), philo->id);
		usleep(philo->time_to_eat * 1000);
		philo->last_meal = get_time_stamp();
		pthread_mutex_unlock(&philo->fork);
		printf("Philo %d finished eating\n", philo->id);
		philo->state = SLEEPING;
		printf("%lu %d is sleeping\n", get_time_stamp(), philo->id);
		usleep(philo->time_to_sleep * 1000);
		philo->state = THINKING;
	}
	return (NULL);
}

void	*health_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (data->philo[i].state != EATING && get_time_stamp()
				- data->philo[i].last_meal > data->time_to_die)
				data->philo[i].state = DEAD;
			if (data->philo[i].state == DEAD)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

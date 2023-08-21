/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:19:22 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/21 23:03:45 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time_stamp();
	while (philo->state != DEAD)
	{
		if (philo->state == EATING)
		{
			printf("%lu %d is eating\n", get_time_stamp(), philo->id);
			usleep(philo->time_to_eat * 1000);
			philo->last_meal = get_time_stamp();
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_unlock(&philo->next->fork);
			philo->state = SLEEPING;
		}
			
		else if (philo->state == SLEEPING)
		{
			printf("%lu %d is sleeping\n", get_time_stamp(), philo->id);
			usleep(philo->time_to_sleep * 1000);
			philo->state = THINKING;

		}
		else if (philo->state == THINKING)
		{
			printf("%lu %d is thinking\n", get_time_stamp(), philo->id);
			pthread_mutex_lock(&philo->fork);
			pthread_mutex_lock(&philo->next->fork);
			printf("%lu %d has taken a fork\n", get_time_stamp(), philo->id);
			philo->state = EATING;
		}
	}
	printf("%lu %d is dead\n", get_time_stamp(), philo->id);
	return (NULL);
}

void	*health_routine(void *arg)
{
	t_data *data;
	t_philo *philo;

	data = (t_data *)arg;
	philo = data->first_philo;
	while (philo->state != DEAD)
	{
		printf("checking philo %d\n", philo->id);
		if (get_time_stamp() - philo->last_meal > philo->time_to_die)
		{
			philo->state = DEAD;
			printf("%lu %d is dead\n", get_time_stamp(), philo->id);
			return (NULL);
		}
		philo = philo->next;
	}
	return (NULL);
}

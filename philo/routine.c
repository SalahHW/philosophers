/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 22:28:58 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/25 13:37:57 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (!philo->data->simulation_running)
		return (0);
	printf("%lu %d has taken a fork\n", get_time_stamp()
		- philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->next->fork);
	if (!philo->data->simulation_running)
		return (0);
	printf("%lu %d has taken a fork\n", get_time_stamp()
		- philo->data->start_time, philo->id);
	if (!philo->data->simulation_running)
		return (0);
	philo->last_meal = get_time_stamp();
	printf("%lu %d is eating\n", get_time_stamp() - philo->data->start_time,
		philo->id);
	my_msleep(philo->data->time_to_eat);
	philo->nb_eat_done++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	if (!philo->data->simulation_running)
		return (0);
	printf("%lu %d is sleeping\n", get_time_stamp() - philo->data->start_time,
		philo->id);
	my_msleep(philo->data->time_to_sleep);
	return (1);
}

static int	thinking(t_philo *philo)
{
	if (philo->data->simulation_running)
		printf("%lu %d is thinking\n", get_time_stamp()
			- philo->data->start_time, philo->id);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time_stamp();
	if (philo->id % 2 == 0)
		usleep(500);
	while (philo->data->simulation_running)
	{
		if (!eating(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		if (!thinking(philo))
			return (NULL);
	}
	return (NULL);
}

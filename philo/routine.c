/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 22:28:58 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/29 14:47:51 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		printf("%lu %d has taken a fork\n", get_time_stamp()
			- philo->data->start_time, philo->id);
		pthread_mutex_lock(&philo->next->fork);
		printf("%lu %d has taken a fork\n", get_time_stamp()
			- philo->data->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		printf("%lu %d has taken a fork\n", get_time_stamp()
			- philo->data->start_time, philo->id);
		pthread_mutex_lock(&philo->fork);
		printf("%lu %d has taken a fork\n", get_time_stamp()
			- philo->data->start_time, philo->id);
	}
}

static int	eating(t_philo *philo)
{
	int	sim_running;

	pthread_mutex_lock(&philo->data->sim_running_mutex);
	sim_running = philo->data->simulation_running;
	pthread_mutex_unlock(&philo->data->sim_running_mutex);
	if (!sim_running)
		return (0);
	take_fork(philo);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_stamp();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	printf("%lu %d is eating\n", get_time_stamp() - philo->data->start_time,
		philo->id);
	if (!my_msleep(philo->data->time_to_eat, philo->data))
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		return (0);
	}
	pthread_mutex_lock(&philo->nb_eat_done_mutex);
	philo->nb_eat_done++;
	pthread_mutex_unlock(&philo->nb_eat_done_mutex);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	int	sim_running;

	pthread_mutex_lock(&philo->data->sim_running_mutex);
	sim_running = philo->data->simulation_running;
	pthread_mutex_unlock(&philo->data->sim_running_mutex);
	if (!sim_running)
		return (0);
	printf("%lu %d is sleeping\n", get_time_stamp() - philo->data->start_time,
		philo->id);
	if (!my_msleep(philo->data->time_to_sleep, philo->data))
		return (0);
	return (1);
}

static int	thinking(t_philo *philo)
{
	int	sim_running;

	pthread_mutex_lock(&philo->data->sim_running_mutex);
	sim_running = philo->data->simulation_running;
	pthread_mutex_unlock(&philo->data->sim_running_mutex);
	if (sim_running)
		printf("%lu %d is thinking\n", get_time_stamp()
			- philo->data->start_time, philo->id);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		sim_running;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_stamp();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (philo->id % 2 == 0)
		if (!my_msleep(philo->data->time_to_die / 3, philo->data))
			return (NULL);
	pthread_mutex_lock(&philo->data->sim_running_mutex);
	sim_running = philo->data->simulation_running;
	pthread_mutex_unlock(&philo->data->sim_running_mutex);
	while (sim_running)
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

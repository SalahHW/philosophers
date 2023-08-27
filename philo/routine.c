/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 22:28:58 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/27 16:43:56 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eating(t_philo *philo)
{
	int	sim_running;

	pthread_mutex_lock(&philo->fork);
	sim_running = check_sim_status(&philo->data->sim_running_mutex,
			philo->data->simulation_running);
	if (!sim_running)
		return (0);
	printf("%lu %d has taken a fork\n", get_time_stamp()
			- philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->next->fork);
	sim_running = check_sim_status(&philo->data->sim_running_mutex,
			philo->data->simulation_running);
	if (!sim_running)
		return (0);
	printf("%lu %d has taken a fork\n", get_time_stamp()
			- philo->data->start_time, philo->id);
	sim_running = check_sim_status(&philo->data->sim_running_mutex,
			philo->data->simulation_running);
	if (!sim_running)
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
	int	sim_running;

	sim_running = check_sim_status(&philo->data->sim_running_mutex,
			philo->data->simulation_running);
	if (!sim_running)
		return (0);
	printf("%lu %d is sleeping\n", get_time_stamp() - philo->data->start_time,
			philo->id);
	my_msleep(philo->data->time_to_sleep);
	return (1);
}

static int	thinking(t_philo *philo)
{
	int	sim_running;

	sim_running = check_sim_status(&philo->data->sim_running_mutex,
			philo->data->simulation_running);
	if (sim_running)
		printf("%lu %d is thinking\n", get_time_stamp()
				- philo->data->start_time, philo->id);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int	sim_running;


	philo = (t_philo *)arg;
	refresh_meal(&philo->last_meal_mutex, &philo->last_meal);
	if (philo->id % 2 == 0)
		usleep(500);
	sim_running = check_sim_status(&philo->data->sim_running_mutex,
			philo->data->simulation_running);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 00:03:40 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/23 00:51:47 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating(t_philo *philo)
{
	if (!check_philo_health(philo))
		return (0);
	pthread_mutex_lock(&philo->fork);
	printf("%lu %d has taken a fork\n", get_program_time(philo->start_time),
			philo->id);
	pthread_mutex_lock(&philo->next->fork);
	printf("%lu %d has taken a fork\n", get_program_time(philo->start_time),
			philo->id);
	if (!check_philo_health(philo))
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		return (0);
	}
	philo->last_meal = get_time_stamp();
	printf("%lu %d is eating\n", get_program_time(philo->start_time),
			philo->id);
	usleep(philo->time_to_eat * 1000);
	philo->nb_eat_done++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	if (!check_philo_health(philo))
		return (0);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (!check_philo_health(philo))
		return (0);
	printf("%lu %d is sleeping\n", get_program_time(philo->start_time),
			philo->id);
	usleep(philo->time_to_sleep * 1000);
	if (!check_philo_health(philo))
		return (0);
	return (1);
}

int	thinking(t_philo *philo)
{
	printf("%lu %d is thinking\n", get_program_time(philo->start_time),
			philo->id);
	if (!check_philo_health(philo))
		return (0);
    return (1);
}

int	check_philo_health(t_philo *philo)
{
	size_t time_since_last_meal;

	time_since_last_meal = get_time_stamp() - philo->last_meal;
	if (time_since_last_meal > philo->time_to_die)
	{
		philo->dead = 1;
		printf("%lu %d died\n", get_program_time(philo->start_time), philo->id);
		return (0);
	}
	return (1);
}
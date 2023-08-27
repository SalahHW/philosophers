/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:13:21 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/27 16:15:44 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_sim_status(pthread_mutex_t *mutex, int simulation_running)
{
	int	simstatus;

	pthread_mutex_lock(mutex);
	simstatus = simulation_running;
	pthread_mutex_unlock(mutex);
	return (simstatus);
}

void	terminate_sim(pthread_mutex_t *mutex, int *simulation_running)
{
	pthread_mutex_lock(mutex);
	*simulation_running = 0;
	pthread_mutex_unlock(mutex);
}

void	increment_value(pthread_mutex_t *mutex, int *value)
{
	pthread_mutex_lock(mutex);
	value++;
	pthread_mutex_unlock(mutex);
}

void	refresh_meal(pthread_mutex_t *mutex, size_t *last_meal)
{
	pthread_mutex_lock(mutex);
	*last_meal = get_time_stamp();
	pthread_mutex_unlock(mutex);
}

size_t	get_last_philo_meal(pthread_mutex_t *mutex, size_t last_meal)
{
	size_t last_philo_meal;
	
	pthread_mutex_lock(mutex);
	last_philo_meal = last_meal;
	pthread_mutex_unlock(mutex);
	return (last_philo_meal);
}

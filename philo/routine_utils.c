/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 00:03:40 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/28 23:19:16 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo_health(t_philo *philo)
{
	size_t	last_philo_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_philo_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (get_time_stamp() - last_philo_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->sim_running_mutex);
		philo->data->simulation_running = 0;
		pthread_mutex_unlock(&philo->data->sim_running_mutex);
		printf("%lu %d died\n", get_time_stamp() - philo->data->start_time,
			philo->id);
		return (0);
	}
	return (1);
}

int	has_finished_eat(t_philo *philo)
{
	int	i;
	int	nb_eat_done;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->nb_eat_done_mutex);
		nb_eat_done = philo->nb_eat_done;
		pthread_mutex_unlock(&philo->nb_eat_done_mutex);
		if (nb_eat_done < philo->data->nb_eat)
			return (0);
		philo = philo->next;
		i++;
	}
	return (1);
}

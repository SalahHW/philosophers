/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:19:22 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/23 01:30:55 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	void stop_philo_simulation(t_data *data)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = data->first_philo;
	while (i < data->nb_philo)
	{
		philo->simulation_running = 0;
		philo = philo->next;
		i++;
	}
}

static int all_philo_stopped(t_data *data)
{
	t_philo *philo;
	int i;

	philo = data->first_philo;
	i = 0;
	while (i < data->nb_philo)
	{
		if (philo->simulation_running)
			return (0);
		philo = philo->next;
		i++;
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time_stamp();
	if (philo->id % 2 == 0)
		usleep(500);
	while (!philo->dead && philo->simulation_running && (philo->nb_eat == -1
		|| philo->nb_eat_done < philo->nb_eat))
	{
		if (!eating(philo))
			return (NULL);
		if (philo->nb_eat_done == philo->nb_eat && philo->nb_eat != -1)
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		if (!thinking(philo))
			return (NULL);
	}
	return (NULL);
}

void	*health_routine(void *arg)
{
	t_data *data;
	t_philo *philo;
	data = (t_data *)arg;
	philo = data->first_philo;
	while (data->simulation_running)
	{
		// refresh_philo_data(philo);
		if (philo->dead)
		{
			stop_philo_simulation(data);
			return (NULL);
		}
		if (!philo->simulation_running)
		{
			if (all_philo_stopped(data))
				return (NULL);
		}
		philo = philo->next;
	}
	return (NULL);
}
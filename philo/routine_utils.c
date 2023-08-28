/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 00:03:40 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/28 22:32:46 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo_health(t_philo *philo)
{
	size_t	last_philo_meal;

	last_philo_meal = get_last_philo_meal(&philo->last_meal_mutex,
			philo->last_meal);
	if (get_time_stamp() - last_philo_meal > philo->data->time_to_die)
	{
		terminate_sim(&philo->data->sim_running_mutex,
			&philo->data->simulation_running);
		printf("%lu %d died\n", get_time_stamp() - philo->data->start_time,
			philo->id);
		return (0);
	}
	return (1);
}

int	has_finished_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (philo->nb_eat_done < philo->data->nb_eat)
			return (0);
		philo = philo->next;
		i++;
	}
	return (1);
}

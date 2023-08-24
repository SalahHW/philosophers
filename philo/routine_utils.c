/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 00:03:40 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/24 21:37:10 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo_health(t_philo *philo)
{
	if (get_time_stamp() - philo->last_meal > philo->data->time_to_die)
	{
		philo->data->simulation_running = 0;
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
